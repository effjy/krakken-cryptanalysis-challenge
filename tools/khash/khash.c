/* Krakken Hash: streaming file hashing with the original eight-round core. */
#include "krakken.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { RATE_BYTES = 160, HASH_BYTES = 32, READ_BYTES = 65536 };
typedef void (*permutation_fn)(uint64_t state[32]);

static void erase(void *data, size_t length)
{
    volatile unsigned char *p = data;
    while (length--) *p++ = 0;
}

static permutation_fn select_permutation(void)
{
#ifdef KHASH_HAVE_AVX2
    __builtin_cpu_init();
    if (__builtin_cpu_supports("avx2")) return krakken_permute_avx2;
#endif
    return krakken_permute_scalar;
}

static void absorb(uint64_t state[32], const unsigned char block[RATE_BYTES],
                   permutation_fn permute)
{
    /* Explicit little-endian encoding matches the original x86 hash. */
    for (size_t i = 0; i < RATE_BYTES; ++i)
        state[i / 8] ^= (uint64_t)block[i] << (8 * (i % 8));
    permute(state);
}

static int hash_file(FILE *file, unsigned char digest[HASH_BYTES])
{
    _Alignas(32) uint64_t state[32] = {0};
    unsigned char buffer[READ_BYTES];
    unsigned char pending[RATE_BYTES] = {0};
    size_t used = 0;
    int error = 0;
    permutation_fn permute = select_permutation();

    for (;;) {
        errno = 0;
        size_t count = fread(buffer, 1, sizeof buffer, file);
        if (ferror(file)) {
            error = errno ? errno : EIO;
            break;
        }
        if (count == 0) break;

        const unsigned char *p = buffer;
        if (used != 0) {
            size_t take = RATE_BYTES - used;
            if (take > count) take = count;
            memcpy(pending + used, p, take);
            used += take;
            p += take;
            count -= take;
            if (used == RATE_BYTES) {
                absorb(state, pending, permute);
                used = 0;
            }
        }
        while (count >= RATE_BYTES) {
            absorb(state, p, permute);
            p += RATE_BYTES;
            count -= RATE_BYTES;
        }
        if (count != 0) {
            memcpy(pending, p, count);
            used = count;
        }
    }

    if (error == 0) {
        /* Always append a final padded block, even for exact rate multiples. */
        memset(pending + used, 0, RATE_BYTES - used);
        pending[used] ^= 0x06;
        pending[RATE_BYTES - 1] ^= 0x80;
        absorb(state, pending, permute);
        for (size_t i = 0; i < HASH_BYTES; ++i)
            digest[i] = (unsigned char)(state[i / 8] >> (8 * (i % 8)));
    }

    erase(state, sizeof state);
    erase(pending, sizeof pending);
    erase(buffer, sizeof buffer);
    if (error != 0) errno = error;
    return error == 0 ? 0 : -1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Krakken Hash (256-bit output, 8 rounds)\n"
                        "Usage: %s FILENAME\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "khash: cannot open '%s': %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    unsigned char digest[HASH_BYTES];
    int result = hash_file(file, digest);
    int error = errno;
    if (fclose(file) != 0 && result == 0) {
        result = -1;
        error = errno;
    }
    if (result != 0) {
        fprintf(stderr, "khash: cannot read '%s': %s\n", argv[1], strerror(error));
        erase(digest, sizeof digest);
        return EXIT_FAILURE;
    }

    char hex[2 * HASH_BYTES + 2];
    static const char digits[] = "0123456789abcdef";
    for (size_t i = 0; i < HASH_BYTES; ++i) {
        hex[2 * i] = digits[digest[i] >> 4];
        hex[2 * i + 1] = digits[digest[i] & 15];
    }
    hex[2 * HASH_BYTES] = '\n';
    hex[2 * HASH_BYTES + 1] = '\0';
    erase(digest, sizeof digest);
    if (fputs(hex, stdout) == EOF || fflush(stdout) == EOF) {
        fprintf(stderr, "khash: cannot write hash: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

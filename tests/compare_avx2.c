#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "krakken.h"

static uint64_t rng_state = 0x6b72616b6b656e32ULL;

static uint64_t rng64(void) {
    uint64_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    rng_state = x;
    return x;
}

static void fill_bytes(uint8_t *p, size_t n) {
    size_t i = 0;
    while (i < n) {
        uint64_t x = rng64();
        size_t take = n - i < 8 ? n - i : 8;
        memcpy(p + i, &x, take);
        i += take;
    }
}

int main(void) {
    for (int rounds = 1; rounds <= 8; rounds++) {
        for (int t = 0; t < 2000; t++) {
            uint64_t scalar[32], avx2[32];
            fill_bytes((uint8_t *)scalar, sizeof(scalar));
            memcpy(avx2, scalar, sizeof(scalar));

            krakken_permute_scalar_rounds(scalar, rounds);
            krakken_permute_avx2_rounds(avx2, rounds);

            if (memcmp(scalar, avx2, sizeof(scalar)) != 0) {
                fprintf(stderr, "Permutation mismatch: rounds=%d case=%d\n", rounds, t);
                return 1;
            }
        }
    }

    static const size_t lengths[] = {
        0,1,2,3,31,32,63,64,127,128,158,159,160,161,319,320,321,511,512,1000,4096
    };
    static const size_t out_lengths[] = {1,16,32,64,159,160,161,256,320,321};

    for (size_t li = 0; li < sizeof(lengths)/sizeof(lengths[0]); li++) {
        size_t n = lengths[li];
        uint8_t *msg = malloc(n ? n : 1);
        if (!msg) return 2;
        fill_bytes(msg, n);

        for (size_t oi = 0; oi < sizeof(out_lengths)/sizeof(out_lengths[0]); oi++) {
            size_t outlen = out_lengths[oi];
            uint8_t *a = malloc(outlen), *b = malloc(outlen);
            if (!a || !b) return 2;

            krakken_hash_scalar(a, outlen, msg, n);
            krakken_hash_avx2(b, outlen, msg, n);

            if (memcmp(a, b, outlen) != 0) {
                fprintf(stderr, "Hash mismatch: len=%zu outlen=%zu\n", n, outlen);
                return 1;
            }
            free(a);
            free(b);
        }
        free(msg);
    }

    for (int t = 0; t < 1000; t++) {
        size_t n = (size_t)(rng64() % 2049);
        size_t outlen = 1 + (size_t)(rng64() % 400);
        uint8_t *msg = malloc(n ? n : 1);
        uint8_t *a = malloc(outlen), *b = malloc(outlen);
        if (!msg || !a || !b) return 2;

        fill_bytes(msg, n);
        krakken_hash_scalar(a, outlen, msg, n);
        krakken_hash_avx2(b, outlen, msg, n);

        if (memcmp(a, b, outlen) != 0) {
            fprintf(stderr, "Random hash mismatch: case=%d len=%zu outlen=%zu\n", t, n, outlen);
            return 1;
        }
        free(msg);
        free(a);
        free(b);
    }

    puts("PASS: scalar and AVX2 agree on 16,000 reduced-round permutation cases, boundary/multiblock/squeeze tests, and 1,000 random hash cases.");
    return 0;
}

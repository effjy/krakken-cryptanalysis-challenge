#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "krakken.h"

struct kat {
    const char *name;
    const uint8_t *msg;
    size_t len;
    const char *expected_hex;
};

static void to_hex(const uint8_t *in, size_t n, char *out) {
    static const char h[] = "0123456789abcdef";
    for (size_t i = 0; i < n; i++) {
        out[2*i] = h[in[i] >> 4];
        out[2*i+1] = h[in[i] & 15];
    }
    out[2*n] = '\0';
}

static int run_hash_kat(const struct kat *v) {
    uint8_t out[32];
    char hex[65];

    krakken_hash_scalar(out, sizeof(out), v->msg, v->len);
    to_hex(out, sizeof(out), hex);

    if (strcmp(hex, v->expected_hex) != 0) {
        fprintf(stderr, "FAIL %-8s\n  got: %s\n  exp: %s\n",
                v->name, hex, v->expected_hex);
        return 1;
    }

    printf("PASS %-8s %s\n", v->name, hex);
    return 0;
}

int main(void) {
    static const uint8_t empty[] = {0};
    static const uint8_t abc[] = {'a','b','c'};
    static uint8_t zero1[1] = {0};
    static uint8_t zero159[159] = {0};
    static uint8_t zero160[160] = {0};
    static uint8_t zero161[161] = {0};
    static uint8_t seq159[159];

    for (size_t i = 0; i < sizeof(seq159); i++)
        seq159[i] = (uint8_t)i;

    const struct kat kats[] = {
        {"empty",   empty,   0,   "e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd"},
        {"abc",     abc,     3,   "5062b998511e180f476907438a27183ffcd657031d141b3659f9f32611d9fe7c"},
        {"zero1",   zero1,   1,   "6db6a8b8e3716f6cf2b3d922a2d00be8296d3ef539c7cc2239dbf9e7a80b1b9b"},
        {"zero159", zero159, 159, "6a7449835760839e3d2d629fc839eae6376348c8339fd0f34b8c75264083bc93"},
        {"zero160", zero160, 160, "2d87727b66f7d07827cb1ca1a705da694361b935bfb41b3a6b78cec93a837e13"},
        {"zero161", zero161, 161, "3fa9b8338730344013d01a433d1035dbd716331a4010f68b9e679118bf2bc7e9"},
        {"seq159",  seq159,  159, "3e29183ffec9cee4caad761094f11814a0e336b8edfe29b11f4824d905e2cc26"},
    };

    int failures = 0;
    for (size_t i = 0; i < sizeof(kats)/sizeof(kats[0]); i++)
        failures += run_hash_kat(&kats[i]);

    if (failures)
        return 1;

    puts("All Krakken KATs passed.");
    return 0;
}

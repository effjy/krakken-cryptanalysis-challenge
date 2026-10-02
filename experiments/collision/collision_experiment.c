#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "krakken.h"

typedef enum { ENGINE_SCALAR = 0, ENGINE_AVX2 = 1 } engine_t;

typedef struct {
    uint64_t key;
    uint64_t counter;
} table_entry_t;

typedef struct {
    int rounds[8];
    int n_rounds;
    int bits[16];
    int n_bits;
    int trials;
    uint64_t seed;
    uint64_t max_hashes;
    int max_hashes_set;
    engine_t engine;
    const char *out_dir;
} config_t;

static uint64_t mix64(uint64_t x) {
    x ^= x >> 30;
    x *= UINT64_C(0xbf58476d1ce4e5b9);
    x ^= x >> 27;
    x *= UINT64_C(0x94d049bb133111eb);
    x ^= x >> 31;
    return x;
}

static uint64_t splitmix64_next(uint64_t *x) {
    *x += UINT64_C(0x9e3779b97f4a7c15);
    return mix64(*x);
}

static void store64_le(uint8_t out[8], uint64_t x) {
    for (int i = 0; i < 8; i++) out[i] = (uint8_t)(x >> (8 * i));
}

static void make_message(uint64_t seed, uint64_t trial_tag, uint64_t counter,
                         uint8_t msg[159]) {
    memset(msg, 0, 159);
    store64_le(msg + 0, counter);
    store64_le(msg + 8, trial_tag);

    uint64_t s = seed ^ mix64(trial_tag + UINT64_C(0x123456789abcdef0))
                      ^ mix64(counter + UINT64_C(0xfedcba9876543210));
    size_t off = 16;
    while (off < 159) {
        uint64_t x = splitmix64_next(&s);
        for (int i = 0; i < 8 && off < 159; i++, off++)
            msg[off] = (uint8_t)(x >> (8 * i));
    }
}

static void reduced_hash_159(const uint8_t msg[159], int rounds, engine_t engine,
                             uint8_t digest[32]) {
    union {
        uint64_t w[32];
        uint8_t b[256];
    } state;

    memset(state.b, 0, sizeof(state.b));
    memcpy(state.b, msg, 159);
    state.b[159] = 0x86;

    if (engine == ENGINE_AVX2) {
#ifdef KRAKKEN_ENABLE_AVX2
        krakken_permute_avx2_rounds(state.w, rounds);
#else
        fprintf(stderr, "This binary was built without AVX2 support.\n");
        exit(2);
#endif
    } else {
        krakken_permute_scalar_rounds(state.w, rounds);
    }

    memcpy(digest, state.b, 32);
}

static uint64_t prefix_key(const uint8_t digest[32], int bits) {
    uint64_t x = 0;
    int full = bits / 8;
    int rem = bits % 8;
    for (int i = 0; i < full; i++) x = (x << 8) | digest[i];
    if (rem) x = (x << rem) | (digest[full] >> (8 - rem));
    return x;
}

static void to_hex(const uint8_t *in, size_t n, char *out) {
    static const char h[] = "0123456789abcdef";
    for (size_t i = 0; i < n; i++) {
        out[2*i] = h[in[i] >> 4];
        out[2*i+1] = h[in[i] & 15];
    }
    out[2*n] = '\0';
}

static int from_hex(const char *hex, uint8_t *out, size_t n) {
    if (strlen(hex) != 2*n) return -1;
    for (size_t i = 0; i < n; i++) {
        unsigned v;
        if (sscanf(hex + 2*i, "%2x", &v) != 1) return -1;
        out[i] = (uint8_t)v;
    }
    return 0;
}

static uint64_t next_pow2(uint64_t x) {
    if (x <= 2) return 2;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}

static int ensure_dir(const char *path) {
    if (mkdir(path, 0777) == 0 || errno == EEXIST) return 0;
    perror("mkdir");
    return -1;
}

static double birthday_mean_approx(int bits) {
    return sqrt(3.14159265358979323846 / 2.0) * exp2(bits / 2.0);
}

static uint64_t default_limit_for_bits(int bits) {
    double mean = birthday_mean_approx(bits);
    double lim = ceil(4.0 * mean);
    if (lim < 1000.0) lim = 1000.0;
    if (lim > (double)UINT64_MAX) return UINT64_MAX;
    return (uint64_t)lim;
}

static int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t *)a, y = *(const uint64_t *)b;
    return (x > y) - (x < y);
}

static int save_witness(const char *out_dir, int rounds, int bits, int trial,
                        uint64_t count, uint64_t seed, engine_t engine,
                        const uint8_t m1[159], const uint8_t m2[159],
                        const uint8_t d1[32], const uint8_t d2[32]) {
    char path[512];
    snprintf(path, sizeof(path), "%s/witness_r%d_b%d_t%04d.kat",
             out_dir, rounds, bits, trial);
    FILE *f = fopen(path, "w");
    if (!f) { perror("fopen witness"); return -1; }

    char hm1[319], hm2[319], hd1[65], hd2[65];
    to_hex(m1, 159, hm1); to_hex(m2, 159, hm2);
    to_hex(d1, 32, hd1); to_hex(d2, 32, hd2);

    fprintf(f, "format krakken-collision-witness-v1\n");
    fprintf(f, "source_domain H-159-byte-fixed-0x86\n");
    fprintf(f, "engine %s\n", engine == ENGINE_AVX2 ? "avx2" : "scalar");
    fprintf(f, "rounds %d\n", rounds);
    fprintf(f, "bits %d\n", bits);
    fprintf(f, "trial %d\n", trial);
    fprintf(f, "hashes_to_first_collision %" PRIu64 "\n", count);
    fprintf(f, "seed 0x%016" PRIx64 "\n", seed);
    fprintf(f, "message1 %s\n", hm1);
    fprintf(f, "message2 %s\n", hm2);
    fprintf(f, "digest1 %s\n", hd1);
    fprintf(f, "digest2 %s\n", hd2);
    fclose(f);
    return 0;
}

static int replay_witness(const char *path, engine_t replay_engine) {
    FILE *f = fopen(path, "r");
    if (!f) { perror("fopen replay"); return 2; }

    int rounds = -1, bits = -1;
    char m1hex[319] = {0}, m2hex[319] = {0};
    char tag[64], value[1024];
    engine_t recorded_engine = ENGINE_SCALAR;

    while (fscanf(f, "%63s %1023s", tag, value) == 2) {
        if (strcmp(tag, "engine") == 0) recorded_engine = strcmp(value, "avx2") == 0 ? ENGINE_AVX2 : ENGINE_SCALAR;
        else if (strcmp(tag, "rounds") == 0) rounds = atoi(value);
        else if (strcmp(tag, "bits") == 0) bits = atoi(value);
        else if (strcmp(tag, "message1") == 0) {
            size_t n = strlen(value);
            if (n >= sizeof(m1hex)) { fclose(f); fprintf(stderr, "message1 too long\n"); return 2; }
            memcpy(m1hex, value, n + 1);
        }
        else if (strcmp(tag, "message2") == 0) {
            size_t n = strlen(value);
            if (n >= sizeof(m2hex)) { fclose(f); fprintf(stderr, "message2 too long\n"); return 2; }
            memcpy(m2hex, value, n + 1);
        }
    }
    fclose(f);

    engine_t engine = replay_engine;
    if (rounds < 1 || rounds > 8 || bits < 1 || bits > 64 || !m1hex[0] || !m2hex[0]) {
        fprintf(stderr, "Malformed witness file\n");
        return 2;
    }

    uint8_t m1[159], m2[159], d1[32], d2[32];
    if (from_hex(m1hex, m1, 159) || from_hex(m2hex, m2, 159)) {
        fprintf(stderr, "Malformed message hex\n");
        return 2;
    }
    if (memcmp(m1, m2, 159) == 0) {
        fprintf(stderr, "Witness messages are identical\n");
        return 1;
    }

    reduced_hash_159(m1, rounds, engine, d1);
    reduced_hash_159(m2, rounds, engine, d2);
    uint64_t k1 = prefix_key(d1, bits), k2 = prefix_key(d2, bits);

    char hd1[65], hd2[65];
    to_hex(d1, 32, hd1); to_hex(d2, 32, hd2);
    printf("Replay %s\n", path);
    printf("  recorded engine: %s\n", recorded_engine == ENGINE_AVX2 ? "avx2" : "scalar");
    printf("  replay engine  : %s\n", engine == ENGINE_AVX2 ? "avx2" : "scalar");
    printf("  rounds : %d\n", rounds);
    printf("  bits   : %d\n", bits);
    printf("  digest1: %s\n", hd1);
    printf("  digest2: %s\n", hd2);
    printf("  prefix : %s\n", k1 == k2 ? "COLLISION CONFIRMED" : "MISMATCH");
    return k1 == k2 ? 0 : 1;
}

static int parse_int_list(const char *s, int *out, int maxn, int minv, int maxv) {
    size_t slen = strlen(s);
    char *copy = malloc(slen + 1);
    if (!copy) return -1;
    memcpy(copy, s, slen + 1);
    int n = 0;
    for (char *tok = strtok(copy, ","); tok; tok = strtok(NULL, ",")) {
        if (n >= maxn) { free(copy); return -1; }
        char *end = NULL;
        long v = strtol(tok, &end, 10);
        if (!end || *end || v < minv || v > maxv) { free(copy); return -1; }
        out[n++] = (int)v;
    }
    free(copy);
    return n;
}

static void usage(const char *argv0) {
    printf("Usage: %s [options]\n", argv0);
    printf("  --rounds 1,2,...,8     complete round counts (default 1..8)\n");
    printf("  --bits 24,32,40        output-prefix widths, 1..64 (default 24,32)\n");
    printf("  --trials N             trials per (round,bits) pair (default 20)\n");
    printf("  --seed N               deterministic seed, decimal or 0x...\n");
    printf("  --max-hashes N         cap each trial; otherwise 4x birthday mean\n");
    printf("  --engine scalar|avx2   implementation to use (default scalar)\n");
    printf("  --out DIR              output directory (default collision_results)\n");
    printf("  --replay FILE          replay one saved .kat witness and exit\n");
    printf("\nWidths above 40 bits can require very large memory/time; use --max-hashes deliberately.\n");
}

static int run_one(const config_t *cfg, int rounds, int bits, int trial,
                   uint64_t *out_count) {
    uint64_t limit = cfg->max_hashes_set ? cfg->max_hashes : default_limit_for_bits(bits);
    if (!cfg->max_hashes_set && bits > 40) {
        fprintf(stderr, "Refusing default search for %d bits: specify --max-hashes explicitly.\n", bits);
        return 2;
    }

    if (limit < 2) limit = 2;
    uint64_t need = (uint64_t)ceil((double)limit / 0.70);
    uint64_t cap = next_pow2(need);
    if (cap < need || cap > (SIZE_MAX / sizeof(table_entry_t))) {
        fprintf(stderr, "Requested table too large\n");
        return 2;
    }

    double mib = (double)cap * sizeof(table_entry_t) / (1024.0 * 1024.0);
    printf("r=%d bits=%d trial=%d limit=%" PRIu64 " table=%.1f MiB ... ",
           rounds, bits, trial, limit, mib);
    fflush(stdout);

    table_entry_t *table = malloc((size_t)cap * sizeof(*table));
    if (!table) {
        fprintf(stderr, "allocation failed for %.1f MiB\n", mib);
        return 2;
    }
    for (uint64_t i = 0; i < cap; i++) table[i].counter = UINT64_MAX;

    uint64_t trial_tag = ((uint64_t)(uint32_t)rounds << 48)
                       ^ ((uint64_t)(uint32_t)bits << 32)
                       ^ (uint64_t)(uint32_t)trial;
    uint8_t msg[159], digest[32];
    uint64_t mask = cap - 1;

    for (uint64_t counter = 0; counter < limit; counter++) {
        make_message(cfg->seed, trial_tag, counter, msg);
        reduced_hash_159(msg, rounds, cfg->engine, digest);
        uint64_t key = prefix_key(digest, bits);
        uint64_t idx = mix64(key) & mask;

        for (;;) {
            table_entry_t *e = &table[idx];
            if (e->counter == UINT64_MAX) {
                e->key = key;
                e->counter = counter;
                break;
            }
            if (e->key == key) {
                uint8_t m1[159], d1[32];
                make_message(cfg->seed, trial_tag, e->counter, m1);
                reduced_hash_159(m1, rounds, cfg->engine, d1);
                if (memcmp(m1, msg, 159) == 0) {
                    fprintf(stderr, "internal duplicate-message error\n");
                    free(table);
                    return 2;
                }
                uint64_t count = counter + 1;
                if (save_witness(cfg->out_dir, rounds, bits, trial, count,
                                 cfg->seed, cfg->engine, m1, msg, d1, digest)) {
                    free(table);
                    return 2;
                }
                printf("collision at %" PRIu64 " hashes\n", count);
                *out_count = count;
                free(table);
                return 0;
            }
            idx = (idx + 1) & mask;
        }
    }

    printf("no collision within cap\n");
    *out_count = 0;
    free(table);
    return 0;
}

int main(int argc, char **argv) {
    config_t cfg = {
        .rounds = {1,2,3,4,5,6,7,8}, .n_rounds = 8,
        .bits = {24,32}, .n_bits = 2,
        .trials = 20,
        .seed = UINT64_C(0x6b72616b6b656e31),
        .max_hashes = 0, .max_hashes_set = 0,
        .engine = ENGINE_SCALAR,
        .out_dir = "collision_results"
    };

    const char *replay = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            usage(argv[0]); return 0;
        } else if (strcmp(argv[i], "--rounds") == 0 && i + 1 < argc) {
            int n = parse_int_list(argv[++i], cfg.rounds, 8, 1, 8);
            if (n <= 0) { fprintf(stderr, "Bad --rounds\n"); return 2; }
            cfg.n_rounds = n;
        } else if (strcmp(argv[i], "--bits") == 0 && i + 1 < argc) {
            int n = parse_int_list(argv[++i], cfg.bits, 16, 1, 64);
            if (n <= 0) { fprintf(stderr, "Bad --bits\n"); return 2; }
            cfg.n_bits = n;
        } else if (strcmp(argv[i], "--trials") == 0 && i + 1 < argc) {
            cfg.trials = atoi(argv[++i]);
            if (cfg.trials < 1 || cfg.trials > 1000000) { fprintf(stderr, "Bad --trials\n"); return 2; }
        } else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            char *end = NULL;
            cfg.seed = strtoull(argv[++i], &end, 0);
            if (!end || *end) { fprintf(stderr, "Bad --seed\n"); return 2; }
        } else if (strcmp(argv[i], "--max-hashes") == 0 && i + 1 < argc) {
            char *end = NULL;
            cfg.max_hashes = strtoull(argv[++i], &end, 0);
            if (!end || *end || cfg.max_hashes < 2) { fprintf(stderr, "Bad --max-hashes\n"); return 2; }
            cfg.max_hashes_set = 1;
        } else if (strcmp(argv[i], "--engine") == 0 && i + 1 < argc) {
            const char *v = argv[++i];
            if (strcmp(v, "scalar") == 0) cfg.engine = ENGINE_SCALAR;
            else if (strcmp(v, "avx2") == 0) {
#ifndef KRAKKEN_ENABLE_AVX2
                fprintf(stderr, "This binary was built without AVX2 support; use the AVX2 build target.\n");
                return 2;
#else
                cfg.engine = ENGINE_AVX2;
#endif
            } else { fprintf(stderr, "Bad --engine\n"); return 2; }
        } else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc) {
            cfg.out_dir = argv[++i];
        } else if (strcmp(argv[i], "--replay") == 0 && i + 1 < argc) {
            replay = argv[++i];
        } else {
            fprintf(stderr, "Unknown/incomplete option: %s\n", argv[i]);
            usage(argv[0]);
            return 2;
        }
    }

    if (replay) return replay_witness(replay, cfg.engine);

    if (ensure_dir(cfg.out_dir)) return 2;
    char summary_path[512];
    snprintf(summary_path, sizeof(summary_path), "%s/summary.csv", cfg.out_dir);
    FILE *summary = fopen(summary_path, "w");
    if (!summary) { perror("fopen summary"); return 2; }
    fprintf(summary, "rounds,bits,trials,found,mean_first_collision,median_first_collision,birthday_mean_approx,ratio_mean_to_birthday,seed,engine\n");

    printf("Krakken reduced-round truncated collision experiment\n");
    printf("domain : valid 159-byte first block + fixed 0x86 pad + zero capacity\n");
    printf("engine : %s\n", cfg.engine == ENGINE_AVX2 ? "avx2" : "scalar");
    printf("seed   : 0x%016" PRIx64 "\n", cfg.seed);

    for (int ri = 0; ri < cfg.n_rounds; ri++) {
        for (int bi = 0; bi < cfg.n_bits; bi++) {
            int rounds = cfg.rounds[ri], bits = cfg.bits[bi];
            uint64_t *counts = calloc((size_t)cfg.trials, sizeof(uint64_t));
            if (!counts) { fclose(summary); return 2; }
            int found = 0;
            long double sum = 0.0;

            for (int t = 0; t < cfg.trials; t++) {
                uint64_t c = 0;
                int rc = run_one(&cfg, rounds, bits, t, &c);
                if (rc) { free(counts); fclose(summary); return rc; }
                if (c) { counts[found++] = c; sum += c; }
            }

            double baseline = birthday_mean_approx(bits);
            double mean = found ? (double)(sum / found) : NAN;
            double median = NAN;
            if (found) {
                qsort(counts, (size_t)found, sizeof(uint64_t), cmp_u64);
                median = (found & 1) ? (double)counts[found/2]
                                     : 0.5 * ((double)counts[found/2 - 1] + (double)counts[found/2]);
            }
            double ratio = found ? mean / baseline : NAN;

            printf("SUMMARY r=%d bits=%d found=%d/%d mean=%.1f median=%.1f random~=%.1f ratio=%.4f\n",
                   rounds, bits, found, cfg.trials, mean, median, baseline, ratio);
            fprintf(summary, "%d,%d,%d,%d,%.6f,%.6f,%.6f,%.9f,0x%016" PRIx64 ",%s\n",
                    rounds, bits, cfg.trials, found, mean, median, baseline, ratio,
                    cfg.seed, cfg.engine == ENGINE_AVX2 ? "avx2" : "scalar");
            fflush(summary);
            free(counts);
        }
    }

    fclose(summary);
    printf("Summary written to %s\n", summary_path);
    return 0;
}

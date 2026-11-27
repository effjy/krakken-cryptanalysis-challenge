/*
 * Krakken-2048 -- Latitude 5400 (i5-8365U) AVX2 + AES-NI optimized v3.
 *
 * This version is a drop-in implementation of the SAME Krakken-2048
 * permutation/hash as krakken_faster_lattitude_2.c. It changes scheduling
 * and data movement only; not S-box outputs, MDS coefficients, round order,
 * constants, hash padding, rate, or any cryptographic operation.
 *
 * New v3 optimizations:
 *   1. Ink Cloud: reverse the four 64-bit lanes of each input register to
 *      [0,3,2,1] only once, then route old word i to destination 7*i mod 32
 *      with three fixed blends per output register (instead of repeated
 *      64-bit lane broadcasts). ROL11 remains unchanged.
 *   2. Chi/AES-NI: overlap four independent first S-box calls before doing
 *      their four dependent second S-box calls. Each pair is still serial.
 *   3. Add a separate eight-round AES-NI code path with limited outer-loop
 *      unrolling. Indexed round constants remain unchanged; the original
 *      variable-round and AVX2-only fallback paths remain available.
 *
 * Requires AVX2. Uses runtime-detected AES-NI when present, with an AVX2
 * fallback. Never requires GFNI, VAES, AVX-512, or OS-specific libraries.
 * AES instructions use legacy AESENCLAST, not VAESENCLAST.
 *
 * Build on Dell Latitude 5400:
 *   gcc -O3 -mavx2 -mtune=skylake -pthread -DKRAKKEN_MAIN \
 *     krakken_faster_lattitude_3.c -o krakken_latitude_v3
 *   ./krakken_latitude_v3
 * Force fallback with -DKRAKKEN_FORCE_AVX2_ONLY.
 *
 * Benchmark caveat: evaluated on AMD EPYC 9V74 VM, not on the user's Intel
 * i5-8365U. The real Latitude speedup must be measured on that machine.
 * Regression testing is not a formal equivalence proof.
 */
#include <assert.h>
#include <immintrin.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define KRAKKEN_ROUNDS 8

static void krakken_memset_wrap(void *p, int c, size_t n) { memset(p, c, n); }
static void (*volatile krakken_memset_vol)(void *, int,
                                           size_t) = krakken_memset_wrap;
static void krakken_secure_zero(void *ptr, size_t n) {
  krakken_memset_vol(ptr, 0, n);
}

static inline uint64_t rotl64(uint64_t x, int n) {
  n &= 63;
  if (n == 0)
    return x;
  return (x << n) | (x >> (64 - n));
}

#define MM256_ROTR_EPI64_IMM(x, n)                                             \
  _mm256_or_si256(_mm256_srli_epi64((x), (n)), _mm256_slli_epi64((x), 64 - (n)))

#define MM256_ROTL_EPI64_IMM(x, n)                                             \
  _mm256_or_si256(_mm256_slli_epi64((x), (n)), _mm256_srli_epi64((x), 64 - (n)))

#define MM256_ROT32_EPI64(x) _mm256_shuffle_epi32((x), 0xB1)

static inline __m256i mm256_rotl_var_epi64(__m256i x, int n) {
  n &= 63;
  if (n == 0)
    return x;
  return _mm256_or_si256(_mm256_slli_epi64(x, n), _mm256_srli_epi64(x, 64 - n));
}

static const uint8_t __attribute__((aligned(32))) SBOX_LUT[16][32] = {
    {0xA5,0xB6,0xDE,0xF7,0x18,0x37,0x8C,0xC1,0x89,0xDA,0x1E,0x85,0x31,0xF0,0x97,0x77,0xA5,0xB6,0xDE,0xF7,0x18,0x37,0x8C,0xC1,0x89,0xDA,0x1E,0x85,0x31,0xF0,0x97,0x77},
    {0x41,0x14,0xE8,0xC8,0x8A,0x04,0xB5,0x69,0x1D,0x2B,0x0F,0x2C,0x4E,0x19,0xCC,0x79,0x41,0x14,0xE8,0xC8,0x8A,0x04,0xB5,0x69,0x1D,0x2B,0x0F,0x2C,0x4E,0x19,0xCC,0x79},
    {0xD7,0x4D,0x7D,0x43,0x03,0x3A,0x13,0x92,0x32,0xD9,0x75,0xDF,0xAD,0x81,0xC3,0xF1,0xD7,0x4D,0x7D,0x43,0x03,0x3A,0x13,0x92,0x32,0xD9,0x75,0xDF,0xAD,0x81,0xC3,0xF1},
    {0xF9,0xA7,0xE2,0x35,0x02,0xDD,0x61,0xA2,0x50,0xE1,0x09,0xC5,0xE3,0x71,0xCB,0x99,0xF9,0xA7,0xE2,0x35,0x02,0xDD,0x61,0xA2,0x50,0xE1,0x09,0xC5,0xE3,0x71,0xCB,0x99},
    {0x9C,0xB1,0x23,0x86,0x3B,0x93,0x24,0xE9,0xF6,0xB4,0x6A,0x66,0xFE,0x7A,0x3E,0x28,0x9C,0xB1,0x23,0x86,0x3B,0x93,0x24,0xE9,0xF6,0xB4,0x6A,0x66,0xFE,0x7A,0x3E,0x28},
    {0x6E,0xF2,0x9B,0xF8,0x3F,0x2A,0x98,0x10,0xA1,0xFB,0x45,0x36,0x64,0x57,0x8F,0x72,0x6E,0xF2,0x9B,0xF8,0x3F,0x2A,0x98,0x10,0xA1,0xFB,0x45,0x36,0x64,0x57,0x8F,0x72},
    {0x8B,0x29,0x56,0xFD,0xF4,0xA4,0xED,0xA6,0x76,0xEB,0x6B,0x4A,0xC7,0x5E,0x26,0xD0,0x8B,0x29,0x56,0xFD,0xF4,0xA4,0xED,0xA6,0x76,0xEB,0x6B,0x4A,0xC7,0x5E,0x26,0xD0},
    {0x5F,0xCA,0x87,0x52,0x01,0x16,0x67,0xB9,0x74,0x4B,0xCF,0xD2,0x60,0x2F,0x49,0x6F,0x5F,0xCA,0x87,0x52,0x01,0x16,0x67,0xB9,0x74,0x4B,0xCF,0xD2,0x60,0x2F,0x49,0x6F},
    {0x39,0x1C,0x5D,0x53,0xE6,0x3C,0xC6,0x7F,0xEA,0xE5,0xBE,0x00,0x65,0x88,0x83,0xE4,0x39,0x1C,0x5D,0x53,0xE6,0x3C,0xC6,0x7F,0xEA,0xE5,0xBE,0x00,0x65,0x88,0x83,0xE4},
    {0x0C,0x38,0x2D,0x80,0xB0,0xAB,0x44,0x84,0x08,0x0D,0xB8,0x51,0x9A,0x2E,0x91,0x68,0x0C,0x38,0x2D,0x80,0xB0,0xAB,0x44,0x84,0x08,0x0D,0xB8,0x51,0x9A,0x2E,0x91,0x68},
    {0x40,0x0A,0xFC,0x82,0xBA,0xCE,0x0B,0xFA,0x1A,0x5B,0x62,0x22,0xC9,0x3D,0x8D,0x06,0x40,0x0A,0xFC,0x82,0xBA,0xCE,0x0B,0xFA,0x1A,0x5B,0x62,0x22,0xC9,0x3D,0x8D,0x06},
    {0x55,0xD5,0x78,0xAE,0x27,0x9D,0x9E,0xAF,0xB7,0x4F,0xDC,0x9F,0x42,0xA3,0xBC,0x15,0x55,0xD5,0x78,0xAE,0x27,0x9D,0x9E,0xAF,0xB7,0x4F,0xDC,0x9F,0x42,0xA3,0xBC,0x15},
    {0xB2,0xDB,0x11,0xA9,0x5C,0xE7,0x7B,0xEF,0xFF,0xC2,0x25,0xEE,0x73,0xF5,0xD6,0x48,0xB2,0xDB,0x11,0xA9,0x5C,0xE7,0x7B,0xEF,0xFF,0xC2,0x25,0xEE,0x73,0xF5,0xD6,0x48},
    {0x4C,0x21,0x70,0xD1,0x30,0x54,0xA0,0xB3,0x94,0x07,0x58,0xAA,0x96,0x1B,0x1F,0x0E,0x4C,0x21,0x70,0xD1,0x30,0x54,0xA0,0xB3,0x94,0x07,0x58,0xAA,0x96,0x1B,0x1F,0x0E},
    {0xD8,0x17,0xE0,0xBB,0x46,0x6C,0xAC,0xA8,0x05,0x7E,0x8E,0x33,0xC4,0xD4,0x59,0xBD,0xD8,0x17,0xE0,0xBB,0x46,0x6C,0xAC,0xA8,0x05,0x7E,0x8E,0x33,0xC4,0xD4,0x59,0xBD},
    {0xBF,0xF3,0x20,0x34,0x90,0xCD,0xEC,0x63,0x47,0x95,0x12,0x6D,0xD3,0x5A,0xC0,0x7C,0xBF,0xF3,0x20,0x34,0x90,0xCD,0xEC,0x63,0x47,0x95,0x12,0x6D,0xD3,0x5A,0xC0,0x7C}};

static inline __m256i sbox8_abyssal256(__m256i x) {
  __m256i mask = _mm256_set1_epi8(0x0F);
  __m256i lo = _mm256_and_si256(x, mask);
  __m256i hi = _mm256_and_si256(_mm256_srli_epi64(x, 4), mask);

  __m256i b0 = _mm256_slli_epi16(hi, 7);
  __m256i b1 = _mm256_slli_epi16(hi, 6);
  __m256i b2 = _mm256_slli_epi16(hi, 5);
  __m256i b3 = _mm256_slli_epi16(hi, 4);

  __m256i l0 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[0]), lo);
  __m256i l1 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[1]), lo);
  __m256i m00 = _mm256_blendv_epi8(l0, l1, b0);

  __m256i l2 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[2]), lo);
  __m256i l3 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[3]), lo);
  __m256i m01 = _mm256_blendv_epi8(l2, l3, b0);
  __m256i m10 = _mm256_blendv_epi8(m00, m01, b1);

  __m256i l4 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[4]), lo);
  __m256i l5 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[5]), lo);
  __m256i m02 = _mm256_blendv_epi8(l4, l5, b0);

  __m256i l6 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[6]), lo);
  __m256i l7 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[7]), lo);
  __m256i m03 = _mm256_blendv_epi8(l6, l7, b0);
  __m256i m11 = _mm256_blendv_epi8(m02, m03, b1);

  __m256i m20 = _mm256_blendv_epi8(m10, m11, b2);

  __m256i l8 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[8]), lo);
  __m256i l9 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[9]), lo);
  __m256i m04 = _mm256_blendv_epi8(l8, l9, b0);

  __m256i l10 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[10]), lo);
  __m256i l11 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[11]), lo);
  __m256i m05 = _mm256_blendv_epi8(l10, l11, b0);
  __m256i m12 = _mm256_blendv_epi8(m04, m05, b1);

  __m256i l12 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[12]), lo);
  __m256i l13 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[13]), lo);
  __m256i m06 = _mm256_blendv_epi8(l12, l13, b0);

  __m256i l14 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[14]), lo);
  __m256i l15 =
      _mm256_shuffle_epi8(_mm256_load_si256((const __m256i *)SBOX_LUT[15]), lo);
  __m256i m07 = _mm256_blendv_epi8(l14, l15, b0);
  __m256i m13 = _mm256_blendv_epi8(m06, m07, b1);

  __m256i m21 = _mm256_blendv_epi8(m12, m13, b2);
  return _mm256_blendv_epi8(m20, m21, b3);
}

static const uint64_t rho[32] __attribute__((aligned(32))) = {
    32, 1,  62, 28, 36, 44, 15, 61, 6,  19, 24, 55, 3, 10, 43, 17,
    25, 39, 41, 59, 47, 8,  56, 14, 18, 35, 21, 33, 2, 49, 22, 51};

static const uint64_t keccak_rc[24] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808AULL,
    0x8000000080008000ULL, 0x000000000000808BULL, 0x0000000080000001ULL,
    0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008AULL,
    0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000AULL,
    0x000000008000808BULL, 0x800000000000008BULL, 0x8000000000008089ULL,
    0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
    0x000000000000800AULL, 0x800000008000000AULL, 0x8000000080008081ULL,
    0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL};

static void keccakf1600(uint64_t st[25]) {
  static const int rho_off[24] = {1,  3,  6,  10, 15, 21, 28, 36,
                                  45, 55, 2,  14, 27, 41, 56, 8,
                                  25, 43, 62, 18, 39, 61, 20, 44};
  static const int pi_idx[24] = {10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4,
                                 15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1};
  for (int r = 0; r < 24; r++) {
    uint64_t bc[5], t;
    for (int i = 0; i < 5; i++)
      bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];
    for (int i = 0; i < 5; i++) {
      t = bc[(i + 4) % 5] ^ rotl64(bc[(i + 1) % 5], 1);
      for (int j = 0; j < 25; j += 5)
        st[j + i] ^= t;
    }
    t = st[1];
    for (int i = 0; i < 24; i++) {
      int j = pi_idx[i];
      bc[0] = st[j];
      st[j] = rotl64(t, rho_off[i]);
      t = bc[0];
    }
    for (int j = 0; j < 25; j += 5) {
      for (int i = 0; i < 5; i++)
        bc[i] = st[j + i];
      for (int i = 0; i < 5; i++)
        st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
    }
    st[0] ^= keccak_rc[r];
  }
}

static void shake128_squeeze(const char *domain, uint8_t *out, size_t outlen) {
  uint64_t st[25] = {0};
  const size_t rate = 168;
  uint8_t *st8 = (uint8_t *)st;
  size_t dlen = strlen(domain);
  for (size_t i = 0; i < dlen; i++)
    st8[i] ^= (uint8_t)domain[i];
  st8[dlen] ^= 0x1F;
  st8[rate - 1] ^= 0x80;
  keccakf1600(st);
  size_t done = 0;
  while (done < outlen) {
    size_t take = outlen - done < rate ? outlen - done : rate;
    memcpy(out + done, st8, take);
    done += take;
    if (done < outlen)
      keccakf1600(st);
  }
}

static uint64_t rc[KRAKKEN_ROUNDS][32] __attribute__((aligned(32)));
static __m256i RC_VEC[KRAKKEN_ROUNDS][8] __attribute__((aligned(32)));
static __m256i RHO_VEC[8] __attribute__((aligned(32)));
static __m256i RHO_INV_VEC[8] __attribute__((aligned(32)));
static pthread_once_t g_rc_once = PTHREAD_ONCE_INIT;
static void _rc_init_impl(void) {
  uint8_t buf[KRAKKEN_ROUNDS * 32 * 8];
  shake128_squeeze("Krakken-2048 Abyssal v1 - Primary ", buf, sizeof(buf));
  for (int ir = 0; ir < KRAKKEN_ROUNDS; ir++) {
    for (int i = 0; i < 32; i++) {
      const uint8_t *p = buf + (ir * 32 + i) * 8;
      uint64_t v = (uint64_t)p[0] | ((uint64_t)p[1] << 8) |
                   ((uint64_t)p[2] << 16) | ((uint64_t)p[3] << 24) |
                   ((uint64_t)p[4] << 32) | ((uint64_t)p[5] << 40) |
                   ((uint64_t)p[6] << 48) | ((uint64_t)p[7] << 56);
      rc[ir][i] = v ? v : 0xDEADBEEFCAFEBABEULL;
    }
    for (int c = 0; c < 8; c++)
      RC_VEC[ir][c] = _mm256_load_si256((const __m256i *)&rc[ir][c * 4]);
  }
  __m256i c64 = _mm256_set1_epi64x(64);
  for (int c = 0; c < 8; c++) {
    RHO_VEC[c] = _mm256_load_si256((const __m256i *)&rho[c * 4]);
    RHO_INV_VEC[c] = _mm256_sub_epi64(c64, RHO_VEC[c]);
  }


}

void init_rc_vectors_avx2(void) { pthread_once(&g_rc_once, _rc_init_impl); }

static inline __attribute__((always_inline)) void theta_regs(__m256i cols[8]) {
  __m256i P[8];
  for (int c = 0; c < 8; c++) {
    __m256i t = _mm256_xor_si256(cols[c], _mm256_shuffle_epi32(cols[c], 0x4E));
    P[c] = _mm256_xor_si256(t, _mm256_permute2x128_si256(t, t, 0x01));
  }
  for (int c = 0; c < 8; c++) {
    __m256i d = _mm256_xor_si256(MM256_ROTL_EPI64_IMM(P[(c + 7) & 7], 63),
                                 P[(c + 1) & 7]);
    cols[c] = _mm256_xor_si256(cols[c], d);
  }
}

// GF(2^8) multiply-by-2 (reduction polynomial 0x11d) on each byte lane:
// independent packed-byte doubling plus 0x1d reduction for high input bits.
static inline __attribute__((always_inline)) __m256i gf28_dbl(__m256i x) {
  // x+x modulo 256 is an independent one-bit left shift of each byte.
  __m256i sh = _mm256_add_epi8(x, x);
  __m256i hi = _mm256_cmpgt_epi8(_mm256_setzero_si256(), x);
  return _mm256_xor_si256(sh, _mm256_and_si256(hi, _mm256_set1_epi8(0x1d)));
}

static inline __attribute__((always_inline)) void tentacle_mds_regs(__m256i cols[8]) {
  // Algebraically identical circulant GF(256) matrix.
  // Coefficients [1,1,4,1,8,5,2,9] =
  //   (all odd-offset source words) + source[c] +
  //   4*(source[c+2]+source[c+5]) + 2*source[c+6] +
  //   8*(source[c+4]+source[c+7]).  All additions are field XORs.
  // Share the four odd-offset XOR terms across four output columns.
  __m256i ev = _mm256_xor_si256(_mm256_xor_si256(cols[0],cols[2]),_mm256_xor_si256(cols[4],cols[6]));
  __m256i od = _mm256_xor_si256(_mm256_xor_si256(cols[1],cols[3]),_mm256_xor_si256(cols[5],cols[7]));
  __m256i m2[8],m4[8],m8[8];
  for(int i=0;i<8;i++) {
    m2[i]=gf28_dbl(cols[i]);
    m4[i]=gf28_dbl(m2[i]);
    m8[i]=gf28_dbl(m4[i]);
  }
  __m256i out[8];
  for(int c=0;c<8;c++) {
    __m256i acc=_mm256_xor_si256(cols[c], (c&1) ? ev:od);
    acc=_mm256_xor_si256(acc,_mm256_xor_si256(m4[(c+2)&7],m4[(c+5)&7]));
    acc=_mm256_xor_si256(acc,m2[(c+6)&7]);
    acc=_mm256_xor_si256(acc,_mm256_xor_si256(m8[(c+4)&7],m8[(c+7)&7]));
    out[c]=acc;
  }
  for(int c=0;c<8;c++)cols[c]=out[c];
}

static inline __attribute__((always_inline)) void rho_regs(__m256i cols[8]) {
  for (int c = 0; c < 8; c++) {
    cols[c] = _mm256_or_si256(_mm256_sllv_epi64(cols[c], RHO_VEC[c]),
                              _mm256_srlv_epi64(cols[c], RHO_INV_VEC[c]));
  }
}

static inline __attribute__((always_inline)) void pi_regs(__m256i cols[8]) {
  __m256i out[8];
  for (int c = 0; c < 8; c++) {
    out[c] = _mm256_blend_epi32(
        _mm256_blend_epi32(cols[c], cols[(c + 5) & 7], 0x0C),
        _mm256_blend_epi32(cols[(c + 2) & 7], cols[(c + 7) & 7], 0xC0), 0xF0);
  }
  for (int c = 0; c < 8; c++)
    cols[c] = out[c];
}

static inline __attribute__((always_inline)) void chi_regs(__m256i cols[8]) {
  for (int p = 0; p < 4; p++) {
    __m256i a = cols[p * 2];
    __m256i b = cols[p * 2 + 1];
    __m256i rb = MM256_ROT32_EPI64(b);
    __m256i ap = sbox8_abyssal256(_mm256_xor_si256(a, rb));
    __m256i ra = MM256_ROT32_EPI64(ap);
    __m256i bp = sbox8_abyssal256(_mm256_xor_si256(b, ra));
    cols[p * 2] = ap;
    cols[p * 2 + 1] = bp;
  }
}

#define BUTTERFLY_INTRA_DIST1(W, rot) ({ \
    __m256i _w = (W); \
    __m256i _s = _mm256_permute4x64_epi64(_w, 0xB1); \
    __m256i _a = _mm256_xor_si256(_w, _s); \
    __m256i _rotA = MM256_ROTL_EPI64_IMM(_a, (rot)); \
    __m256i _b = _mm256_xor_si256(_w, _rotA); \
    _mm256_blend_epi32(_a, _b, 0xCC); \
})

#define BUTTERFLY_INTRA_DIST2(W, rot) ({ \
    __m256i _w = (W); \
    __m256i _s = _mm256_permute4x64_epi64(_w, 0x4E); \
    __m256i _a = _mm256_xor_si256(_w, _s); \
    __m256i _rotA = MM256_ROTL_EPI64_IMM(_a, (rot)); \
    __m256i _b = _mm256_xor_si256(_w, _rotA); \
    _mm256_blend_epi32(_a, _b, 0xF0); \
})

static inline void butterfly_diffusion_avx2(__m256i cols[8]) {
  // Stage 0: dist = 1, rot = 13 (intra-register)
  for (int c = 0; c < 8; c++) {
    cols[c] = BUTTERFLY_INTRA_DIST1(cols[c], 13);
  }

  // Stage 1: dist = 2, rot = 23 (intra-register)
  for (int c = 0; c < 8; c++) {
    cols[c] = BUTTERFLY_INTRA_DIST2(cols[c], 23);
  }

  // Stage 2: dist = 4, rot = 37 (inter-register)
  // Pairs: (cols[0], cols[1]), (cols[2], cols[3]), (cols[4], cols[5]), (cols[6], cols[7])
  for (int c = 0; c < 8; c += 2) {
    __m256i x = cols[c];
    __m256i y = cols[c + 1];
    x = _mm256_xor_si256(x, y);
    y = _mm256_xor_si256(y, MM256_ROTL_EPI64_IMM(x, 37));
    cols[c] = x;
    cols[c + 1] = y;
  }

  // Stage 3: dist = 8, rot = 41 (inter-register)
  // Pairs: (cols[0], cols[2]), (cols[1], cols[3]), (cols[4], cols[6]), (cols[5], cols[7])
  for (int i = 0; i < 2; i++) {
    int base = i * 4;
    {
      __m256i x = cols[base];
      __m256i y = cols[base + 2];
      x = _mm256_xor_si256(x, y);
      y = _mm256_xor_si256(y, MM256_ROTL_EPI64_IMM(x, 41));
      cols[base] = x;
      cols[base + 2] = y;
    }
    {
      __m256i x = cols[base + 1];
      __m256i y = cols[base + 3];
      x = _mm256_xor_si256(x, y);
      y = _mm256_xor_si256(y, MM256_ROTL_EPI64_IMM(x, 41));
      cols[base + 1] = x;
      cols[base + 3] = y;
    }
  }

  // Stage 4: dist = 16, rot = 53 (inter-register)
  // Pairs: (cols[0], cols[4]), (cols[1], cols[5]), (cols[2], cols[6]), (cols[3], cols[7])
  for (int c = 0; c < 4; c++) {
    __m256i x = cols[c];
    __m256i y = cols[c + 4];
    x = _mm256_xor_si256(x, y);
    y = _mm256_xor_si256(y, MM256_ROTL_EPI64_IMM(x, 53));
    cols[c] = x;
    cols[c + 4] = y;
  }
}

#define PRESSURE_ROUND_VEC(a, b, c, d)                                         \
  do {                                                                         \
    a = _mm256_add_epi64(a, _mm256_xor_si256(c, _mm256_srli_epi64(c, 17)));    \
    b = _mm256_add_epi64(b, _mm256_xor_si256(d, _mm256_srli_epi64(d, 17)));    \
    c = _mm256_add_epi64(c, _mm256_xor_si256(a, _mm256_slli_epi64(a, 31)));    \
    d = _mm256_add_epi64(d, _mm256_xor_si256(b, _mm256_slli_epi64(b, 31)));    \
  } while (0)

static inline __attribute__((always_inline)) void pressure_arx_regs(__m256i cols[8]) {
  __m256i u0 = _mm256_unpacklo_epi64(cols[0], cols[1]);
  __m256i u1 = _mm256_unpackhi_epi64(cols[0], cols[1]);
  __m256i u2 = _mm256_unpacklo_epi64(cols[2], cols[3]);
  __m256i u3 = _mm256_unpackhi_epi64(cols[2], cols[3]);
  __m256i a = _mm256_permute2x128_si256(u0, u2, 0x20);
  __m256i b = _mm256_permute2x128_si256(u1, u3, 0x20);
  __m256i c = _mm256_permute2x128_si256(u0, u2, 0x31);
  __m256i d = _mm256_permute2x128_si256(u1, u3, 0x31);

  __m256i u4 = _mm256_unpacklo_epi64(cols[4], cols[5]);
  __m256i u5 = _mm256_unpackhi_epi64(cols[4], cols[5]);
  __m256i u6 = _mm256_unpacklo_epi64(cols[6], cols[7]);
  __m256i u7 = _mm256_unpackhi_epi64(cols[6], cols[7]);
  __m256i a2 = _mm256_permute2x128_si256(u4, u6, 0x20);
  __m256i b2 = _mm256_permute2x128_si256(u5, u7, 0x20);
  __m256i c2 = _mm256_permute2x128_si256(u4, u6, 0x31);
  __m256i d2 = _mm256_permute2x128_si256(u5, u7, 0x31);

  PRESSURE_ROUND_VEC(a, b, c, d);
  PRESSURE_ROUND_VEC(a2, b2, c2, d2);

  b = MM256_ROTL_EPI64_IMM(b, 7);
  d = MM256_ROTL_EPI64_IMM(d, 19);
  b2 = MM256_ROTL_EPI64_IMM(b2, 7);
  d2 = MM256_ROTL_EPI64_IMM(d2, 19);

  __m256i r0 = _mm256_unpacklo_epi64(a, b);
  __m256i r1 = _mm256_unpackhi_epi64(a, b);
  __m256i r2 = _mm256_unpacklo_epi64(c, d);
  __m256i r3 = _mm256_unpackhi_epi64(c, d);
  cols[0] = _mm256_permute2x128_si256(r0, r2, 0x20);
  cols[1] = _mm256_permute2x128_si256(r1, r3, 0x20);
  cols[2] = _mm256_permute2x128_si256(r0, r2, 0x31);
  cols[3] = _mm256_permute2x128_si256(r1, r3, 0x31);

  __m256i r4 = _mm256_unpacklo_epi64(a2, b2);
  __m256i r5 = _mm256_unpackhi_epi64(a2, b2);
  __m256i r6 = _mm256_unpacklo_epi64(c2, d2);
  __m256i r7 = _mm256_unpackhi_epi64(c2, d2);
  cols[4] = _mm256_permute2x128_si256(r4, r6, 0x20);
  cols[5] = _mm256_permute2x128_si256(r5, r7, 0x20);
  cols[6] = _mm256_permute2x128_si256(r4, r6, 0x31);
  cols[7] = _mm256_permute2x128_si256(r5, r7, 0x31);
}

static inline __attribute__((always_inline)) void beta_iota_regs(__m256i cols[8], int round) {
  for (int c = 0; c < 8; c++) {
    cols[c] = _mm256_xor_si256(cols[c], RC_VEC[round][c]);
  }
}

static inline __attribute__((always_inline)) void ink_cloud_regs(__m256i cols[8]) {
  // Ink Cloud: same 7*i mod 32 routing and ROL11 per word.
  // Each source register is permuted once from lanes [0,1,2,3] to [0,3,2,1].
  // Destination lane d receives source lane 3*d modulo four.
  __m256i t[8];
  for (int s=0;s<8;s++)
    t[s] = _mm256_permute4x64_epi64(MM256_ROTL_EPI64_IMM(cols[s], 11), 0x6c);
  __m256i o[8];
  // output 0: old source registers [0, 5, 3, 1]
  o[0] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[0], t[5], 0x0C),
      _mm256_blend_epi32(t[3], t[1], 0xC0), 0xF0);
  // output 1: old source registers [7, 4, 2, 0]
  o[1] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[7], t[4], 0x0C),
      _mm256_blend_epi32(t[2], t[0], 0xC0), 0xF0);
  // output 2: old source registers [6, 3, 1, 7]
  o[2] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[6], t[3], 0x0C),
      _mm256_blend_epi32(t[1], t[7], 0xC0), 0xF0);
  // output 3: old source registers [5, 2, 0, 6]
  o[3] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[5], t[2], 0x0C),
      _mm256_blend_epi32(t[0], t[6], 0xC0), 0xF0);
  // output 4: old source registers [4, 1, 7, 5]
  o[4] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[4], t[1], 0x0C),
      _mm256_blend_epi32(t[7], t[5], 0xC0), 0xF0);
  // output 5: old source registers [3, 0, 6, 4]
  o[5] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[3], t[0], 0x0C),
      _mm256_blend_epi32(t[6], t[4], 0xC0), 0xF0);
  // output 6: old source registers [2, 7, 5, 3]
  o[6] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[2], t[7], 0x0C),
      _mm256_blend_epi32(t[5], t[3], 0xC0), 0xF0);
  // output 7: old source registers [1, 6, 4, 2]
  o[7] = _mm256_blend_epi32(
      _mm256_blend_epi32(t[1], t[6], 0x0C),
      _mm256_blend_epi32(t[4], t[2], 0xC0), 0xF0);
  for(int c=0;c<8;c++)cols[c]=o[c];
}

// Internal permutation on an already initialized register-resident state.
// Exactly the original nine-layer round order and indexed round constants.
static inline __attribute__((always_inline)) void krakken_permute_cols(__m256i cols[8], int rounds) {
  for (int ir = 0; ir < rounds; ir++) {
    theta_regs(cols);
    tentacle_mds_regs(cols);
    rho_regs(cols);
    pi_regs(cols);
    chi_regs(cols);
    butterfly_diffusion_avx2(cols);
    pressure_arx_regs(cols);
    beta_iota_regs(cols, ir);
    ink_cloud_regs(cols);
  }
}


/* AES-NI is present on 8th-generation Intel Core processors including
 * Dell Latitude 5400 configurations. No GFNI/AVX-512 required.
 *
 * The Abyssal S-box is EXACTLY equivalent to this AES SubBytes conjugation:
 *   S(x) = M(AES_SBOX(T(x))) xor OUT_CONST
 * where T is the field isomorphism from GF(0x11D) to AES GF(0x11B),
 * M is a GF(2)-linear 8x8 output transform, and OUT_CONST aligns offsets.
 * All 256 byte values have been exhaustively checked during generation.
 */
static const uint8_t AESNI_TLO[32] __attribute__((aligned(32))) = {0x00,0x01,0x03,0x02,0x05,0x04,0x06,0x07,0x0f,0x0e,0x0c,0x0d,0x0a,0x0b,0x09,0x08,0x00,0x01,0x03,0x02,0x05,0x04,0x06,0x07,0x0f,0x0e,0x0c,0x0d,0x0a,0x0b,0x09,0x08};
static const uint8_t AESNI_THI[32] __attribute__((aligned(32))) = {0x00,0x11,0x33,0x22,0x55,0x44,0x66,0x77,0xff,0xee,0xcc,0xdd,0xaa,0xbb,0x99,0x88,0x00,0x11,0x33,0x22,0x55,0x44,0x66,0x77,0xff,0xee,0xcc,0xdd,0xaa,0xbb,0x99,0x88};
static const uint8_t AESNI_MLO[32] __attribute__((aligned(32))) = {0xe9,0x97,0x6b,0x15,0x7d,0x03,0xff,0x81,0x54,0x2a,0xd6,0xa8,0xc0,0xbe,0x42,0x3c,0xe9,0x97,0x6b,0x15,0x7d,0x03,0xff,0x81,0x54,0x2a,0xd6,0xa8,0xc0,0xbe,0x42,0x3c};
static const uint8_t AESNI_MHI[32] __attribute__((aligned(32))) = {0x00,0xc6,0x58,0x9e,0xe8,0x2e,0xb0,0x76,0x2a,0xec,0x72,0xb4,0xc2,0x04,0x9a,0x5c,0x00,0xc6,0x58,0x9e,0xe8,0x2e,0xb0,0x76,0x2a,0xec,0x72,0xb4,0xc2,0x04,0x9a,0x5c};
static const uint8_t AESNI_UNSHIFTROWS[32] __attribute__((aligned(32))) = {0x00,0x0d,0x0a,0x07,0x04,0x01,0x0e,0x0b,0x08,0x05,0x02,0x0f,0x0c,0x09,0x06,0x03,0x00,0x0d,0x0a,0x07,0x04,0x01,0x0e,0x0b,0x08,0x05,0x02,0x0f,0x0c,0x09,0x06,0x03};

/* Force the original (non-VAES) AES-NI opcode. Some compilers emit a
 * VEX-encoded VAESENCLAST for the intrinsic when AVX2 is also enabled,
 * even on targets where VAES cannot be assumed. This legacy opcode requires
 * only the AES CPU feature and works on eighth-generation Intel Core CPUs. */
static inline __m128i krakken_legacy_aesenclast(__m128i x, __m128i key) {
    __asm__("aesenclast %1, %0" : "+x"(x) : "x"(key));
    return x;
}

__attribute__((target("aes,avx2"), always_inline))
static inline __m256i krakken_aesni_sbox(__m256i x) {
    const __m256i mask = _mm256_set1_epi8(0x0f);
    __m256i lo = _mm256_and_si256(x, mask);
    __m256i hi = _mm256_and_si256(_mm256_srli_epi64(x, 4), mask);
    const __m256i tlo = _mm256_load_si256((const __m256i *)AESNI_TLO);
    const __m256i thi = _mm256_load_si256((const __m256i *)AESNI_THI);
    __m256i v = _mm256_xor_si256(_mm256_shuffle_epi8(tlo,lo), _mm256_shuffle_epi8(thi,hi));
    __m128i xlo = _mm256_castsi256_si128(v);
    __m128i xhi = _mm256_extracti128_si256(v, 1);
    const __m128i zero = _mm_setzero_si128();
    xlo = krakken_legacy_aesenclast(xlo, zero);
    xhi = krakken_legacy_aesenclast(xhi, zero);
    v = _mm256_inserti128_si256(_mm256_castsi128_si256(xlo), xhi, 1);
    // AESENCLAST performs ShiftRows after SubBytes. Undo that byte permutation.
    v = _mm256_shuffle_epi8(v, _mm256_load_si256((const __m256i *)AESNI_UNSHIFTROWS));
    lo = _mm256_and_si256(v, mask);
    hi = _mm256_and_si256(_mm256_srli_epi64(v, 4), mask);
    // MLO already includes the original 0xe9 affine offset in each entry.
    const __m256i mlo = _mm256_load_si256((const __m256i *)AESNI_MLO);
    const __m256i mhi = _mm256_load_si256((const __m256i *)AESNI_MHI);
    v = _mm256_xor_si256(_mm256_shuffle_epi8(mlo,lo),_mm256_shuffle_epi8(mhi,hi));
    return v;
}

__attribute__((target("aes,avx2"), always_inline))
static inline void krakken_chi_aesni(__m256i cols[8]) {
  __m256i a0 = cols[0];
  __m256i b0 = cols[1];
  __m256i ap0 = krakken_aesni_sbox(_mm256_xor_si256(a0,MM256_ROT32_EPI64(b0)));
  __m256i a1 = cols[2];
  __m256i b1 = cols[3];
  __m256i ap1 = krakken_aesni_sbox(_mm256_xor_si256(a1,MM256_ROT32_EPI64(b1)));
  __m256i a2 = cols[4];
  __m256i b2 = cols[5];
  __m256i ap2 = krakken_aesni_sbox(_mm256_xor_si256(a2,MM256_ROT32_EPI64(b2)));
  __m256i a3 = cols[6];
  __m256i b3 = cols[7];
  __m256i ap3 = krakken_aesni_sbox(_mm256_xor_si256(a3,MM256_ROT32_EPI64(b3)));
  cols[0] = ap0;
  cols[1] = krakken_aesni_sbox(_mm256_xor_si256(b0,MM256_ROT32_EPI64(ap0)));
  cols[2] = ap1;
  cols[3] = krakken_aesni_sbox(_mm256_xor_si256(b1,MM256_ROT32_EPI64(ap1)));
  cols[4] = ap2;
  cols[5] = krakken_aesni_sbox(_mm256_xor_si256(b2,MM256_ROT32_EPI64(ap2)));
  cols[6] = ap3;
  cols[7] = krakken_aesni_sbox(_mm256_xor_si256(b3,MM256_ROT32_EPI64(ap3)));
}

__attribute__((target("aes,avx2"), noinline))
static void krakken_permute_cols_aesni(__m256i cols[8], int rounds) {
  for (int ir = 0; ir < rounds; ir++) {
    theta_regs(cols);
    tentacle_mds_regs(cols);
    rho_regs(cols);
    pi_regs(cols);
    krakken_chi_aesni(cols);
    butterfly_diffusion_avx2(cols);
    pressure_arx_regs(cols);
    beta_iota_regs(cols, ir);
    ink_cloud_regs(cols);
  }
}

__attribute__((target("aes,avx2"), noinline))
static void krakken_permute_cols_aesni_8(__m256i cols[8]) {
  #pragma GCC unroll 2
  for (int ir = 0; ir < KRAKKEN_ROUNDS; ir++) {
    theta_regs(cols);
    tentacle_mds_regs(cols);
    rho_regs(cols);
    pi_regs(cols);
    krakken_chi_aesni(cols);
    butterfly_diffusion_avx2(cols);
    pressure_arx_regs(cols);
    beta_iota_regs(cols, ir);
    ink_cloud_regs(cols);
  }
}


/* AES-NI is standard on the Latitude 5400's Intel Core CPU families.
 * Detect it once per hash/permutation call and retain an original AVX2-only
 * path on other chips or when building with KRAKKEN_FORCE_AVX2_ONLY.
 */
static inline int krakken_has_aesni(void) {
#if defined(KRAKKEN_FORCE_AVX2_ONLY)
  return 0;
#elif defined(__GNUC__) || defined(__clang__)
  return __builtin_cpu_supports("aes") != 0;
#else
  return 0;
#endif
}

static inline void krakken_permute_cols_dispatch(__m256i cols[8], int rounds, int aesni) {
  if (aesni) { if (rounds==KRAKKEN_ROUNDS) krakken_permute_cols_aesni_8(cols); else krakken_permute_cols_aesni(cols,rounds); return; }
  krakken_permute_cols(cols,rounds);
}

void krakken_permute_avx2_rounds(uint64_t state[32], int rounds) {
  init_rc_vectors_avx2();
  if (rounds <= 0) return;
  if (rounds > KRAKKEN_ROUNDS) rounds = KRAKKEN_ROUNDS;
  __m256i cols[8];
  for (int c = 0; c < 8; c++)
    cols[c] = _mm256_loadu_si256((const __m256i *)&state[c * 4]);
  krakken_permute_cols_dispatch(cols, rounds, krakken_has_aesni());
  for (int c = 0; c < 8; c++)
    _mm256_storeu_si256((__m256i *)&state[c * 4], cols[c]);
}

void krakken_permute_avx2(uint64_t state[32]) {
  krakken_permute_avx2_rounds(state, KRAKKEN_ROUNDS);
}

void krakken_hash_avx2(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen) {
  if (outlen == 0) return;
  init_rc_vectors_avx2();
  // The entire 2048-bit sponge state remains in eight 256-bit registers.
  // Only the message blocks and final digest touch user memory.
  __m256i cols[8];
  for (int c = 0; c < 8; c++) cols[c] = _mm256_setzero_si256();
  const int aesni = krakken_has_aesni();
  const uint8_t *msg = in;
  size_t rem = inlen;
  while (rem >= 160) {
    for (int c = 0; c < 5; c++) {
      const __m256i chunk = _mm256_loadu_si256((const __m256i *)(msg + c * 32));
      cols[c] = _mm256_xor_si256(cols[c], chunk);
    }
    krakken_permute_cols_dispatch(cols, KRAKKEN_ROUNDS, aesni);
    msg += 160;
    rem -= 160;
  }
  uint8_t block[160] __attribute__((aligned(32)));
  memset(block, 0, sizeof(block));
  if (rem > 0) memcpy(block, msg, rem);
  uint8_t mask = (uint8_t)(-(rem < 159));
  block[rem] = (uint8_t)((block[rem] & ~mask) | (0x06 & mask));
  block[159] = (uint8_t)((mask & 0x80) | ((~mask) & 0x86));
  for (int c = 0; c < 5; c++) {
    const __m256i chunk = _mm256_load_si256((const __m256i *)(block + c * 32));
    cols[c] = _mm256_xor_si256(cols[c], chunk);
  }
  krakken_permute_cols_dispatch(cols, KRAKKEN_ROUNDS, aesni);

  while (outlen > 0) {
    for (int c = 0; c < 5 && outlen > 0; c++) {
      const size_t take = outlen < 32 ? outlen : 32;
      if (take == 32) {
        _mm256_storeu_si256((__m256i *)out, cols[c]);
      } else {
        uint8_t tail[32];
        _mm256_storeu_si256((__m256i *)tail, cols[c]);
        memcpy(out, tail, take);
        krakken_secure_zero(tail, sizeof(tail));
      }
      out += take;
      outlen -= take;
    }
    if (outlen > 0) krakken_permute_cols_dispatch(cols, KRAKKEN_ROUNDS, aesni);
  }
  krakken_secure_zero(cols, sizeof(cols));
  krakken_secure_zero(block, sizeof(block));
}

typedef struct {
  uint8_t *out;
  size_t outlen;
  const uint8_t *in;
  size_t inlen;
} krakken_stream_t;
typedef struct {
  const krakken_stream_t *streams;
  int start;
  int end;
} krakken_worker_arg_t;

static void *krakken_parallel_worker(void *arg) {
  const krakken_worker_arg_t *w = (const krakken_worker_arg_t *)arg;
  for (int i = w->start; i < w->end; i++)
    krakken_hash_avx2(w->streams[i].out, w->streams[i].outlen, w->streams[i].in,
                      w->streams[i].inlen);
  return NULL;
}

int krakken_hash_avx2_parallel(const krakken_stream_t *streams, int n,
                               int n_threads) {
  if (n <= 0)
    return 0;
  if (n_threads < 1)
    n_threads = 1;
  if (n_threads > n)
    n_threads = n;
  init_rc_vectors_avx2();

  pthread_t *tids = malloc((size_t)n_threads * sizeof(pthread_t));
  krakken_worker_arg_t *args =
      malloc((size_t)n_threads * sizeof(krakken_worker_arg_t));

  if (!tids || !args) {
    free(tids);
    free(args);
    return -1;
  }

  // Initialize args array completely first
  int base = n / n_threads, extra = n % n_threads, cur = 0;
  for (int t = 0; t < n_threads; t++) {
    args[t].streams = streams;
    args[t].start = cur;
    args[t].end = cur + base + (t < extra ? 1 : 0);
    cur = args[t].end;
  }

  // Create threads safely
  int rc_ret = 0;
  for (int t = 0; t < n_threads; t++) {
    if (pthread_create(&tids[t], NULL, krakken_parallel_worker, &args[t]) != 0) {
      for (int j = t; j < n_threads; j++)
        krakken_parallel_worker(&args[j]);
      for (int j = 0; j < t; j++)
        pthread_join(tids[j], NULL);
      rc_ret = -1;
      goto done;
    }
  }
  for (int t = 0; t < n_threads; t++)
    pthread_join(tids[t], NULL);
done:
  free(tids);
  free(args);
  return rc_ret;
}

#ifdef KRAKKEN_MAIN
static double get_time(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}
static void benchmark_single(void) {
  const size_t DATA = 16 * 1024 * 1024;
  const int ITER = 20;
  uint8_t *data = malloc(DATA), *hash = malloc(32);
  for (size_t i = 0; i < DATA; i++)
    data[i] = (uint8_t)(i ^ (i >> 8) ^ (i >> 16));
  printf(
      "Krakken-2048 Abyssal (8 rounds) AVX2 "
      "Single-thread\n----------------------------------------------------\n");
  krakken_hash_avx2(hash, 32, data, DATA);
  double t0 = get_time();
  for (int i = 0; i < ITER; i++)
    krakken_hash_avx2(hash, 32, data, DATA);
  double avg = (get_time() - t0) / ITER;
  double mbps = (DATA / (1024.0 * 1024.0)) / avg;
  printf("Throughput   : %.2f MB/s\n\n", mbps);
  free(data);
  free(hash);
}

static void benchmark_parallel(int n_threads) {
  const size_t DATA = 16 * 1024 * 1024;
  const int ITER = 20;
  uint8_t *all = malloc((size_t)n_threads * DATA);
  krakken_stream_t *streams =
      malloc((size_t)n_threads * sizeof(krakken_stream_t));
  uint8_t *hashes = malloc((size_t)n_threads * 32);

  for (int t = 0; t < n_threads; t++) {
    uint8_t *ptr = all + (size_t)t * DATA;
    for (size_t i = 0; i < DATA; i++)
      ptr[i] = (uint8_t)(i ^ t);
    streams[t].in = ptr;
    streams[t].inlen = DATA;
    streams[t].out = hashes + t * 32;
    streams[t].outlen = 32;
  }

  printf(
      "Parallel benchmark  (%d threads)\n----------------------------------\n",
      n_threads);
  double t0 = get_time();
  for (int i = 0; i < ITER; i++) {
    krakken_hash_avx2_parallel(streams, n_threads, n_threads);
  }
  double elapsed = get_time() - t0;
  double total_mb = ((double)DATA * ITER * n_threads) / (1024.0 * 1024.0);
  printf("Wall time        : %.3f s\n", elapsed);
  printf("Aggregate MB/s   : %.2f  (%.3f GB/s)\n\n", total_mb / elapsed,
         (total_mb / elapsed) / 1024.0);

  free(all);
  free(streams);
  free(hashes);
}

int main(void) {
  printf(
      "Krakken-2048 Abyssal (8 rounds) AVX2 + "
      "Multi-thread\n====================================================\n\n");
  init_rc_vectors_avx2();

  benchmark_single();
  benchmark_parallel(1);
  benchmark_parallel(4);
  benchmark_parallel(8);

  uint8_t empty[32];
  krakken_hash_avx2(empty, 32, (const uint8_t *)"", 0);
  printf("Empty hash   : ");
  for (int i = 0; i < 32; i++)
    printf("%02x", empty[i]);
  printf("\n");
  return 0;
}
#endif

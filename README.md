# Krakken-2048 — Open Cryptanalysis Challenge

> **Break Krakken.** Examine the implementation. Challenge the proofs. Find a weakness the existing research missed.

Krakken-2048 is an **experimental 2048-bit permutation and sponge-based hash construction** published for open cryptanalysis. Its designer reports approximately ten years of development and investigation, and is inviting independent researchers to attempt to break the construction.

**Status:** publicly available research target; **not independently certified**, **not standardized**, and **not recommended for production security**.

## The target

| Item | Specification |
| --- | --- |
| State | 2048 bits, 32 × 64-bit words |
| Full permutation | 8 rounds |
| Hash absorption | 160-byte rate |
| Default challenge output | 256-bit digest |
| Reference | [`krakken.c`](krakken.c) and [`krakken.h`](krakken.h) |
| Optimized implementation | [`krakken_multi.c`](krakken_multi.c) (AVX2/multithread) |
| Further optimized implementation | [`krakken_faster_lattitude_3.c`](krakken_faster_lattitude_3.c) (AVX2 + AES-NI, multithread; runtime AES-NI detection with AVX2-only fallback) |
| Round constants | SHAKE128-derived, public and deterministic |

The full construction, unrestricted permutation, individual layers, and reduced-round variants are all legitimate cryptanalytic targets. **Specify exactly which interface and number of rounds your result addresses.**

Reference SHA-256 pins:

```text
krakken.c                     4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6
krakken.h                     83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c
krakken_multi.c               9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2
krakken_faster_lattitude_3.c  abc8a79090897c26794dc0fb8c2cea21f70af16dff81b64b5691534e9012c917
```

The additional Latitude v3 implementation is a standalone optimization of the same permutation and hash, designed for CPUs such as the Intel Core i5-8365U. It requires AVX2 and uses legacy AES-NI when available; GFNI, VAES and AVX-512 are not required. Build its standalone benchmark with:

```sh
gcc -O3 -mavx2 -mtune=skylake -pthread -DKRAKKEN_MAIN krakken_faster_lattitude_3.c -o krakken_latitude_v3
./krakken_latitude_v3
```

Add `-DKRAKKEN_FORCE_AVX2_ONLY` to test the fallback path. The pinned research reference sources remain unchanged; this alternative implementation is not an independently certified equivalence proof.

**The implementation is the attack target; the sixteen research ledgers linked below are evidence and claims to test, not an assertion of invulnerability.** Source revisions or differing hash interface conventions must be reported.

## Start here

- [**CHALLENGE.md**](CHALLENGE.md) — what counts as a break; scope and disclosure.
- [**Known results**](docs/KNOWN_RESULTS.md) — latest bounded claims, including what remains unproved.
- [**Open attack problems**](docs/OPEN_PROBLEMS.md) — independent research opportunities.
- [**Implementation specification**](docs/REFERENCE.md) and [test vectors](docs/TEST_VECTORS.md).
- [**Research archive**](research/README.md) — **all 16 research ledgers**, including the November 18 XRBD/Pressure and exchange/Yoyo/rotational studies, the November 19–22 probability, rank and prediction research, and the November 25–26 differential and algebraic-degree certificates.
- [**Reproduction guidance**](docs/REPRODUCIBILITY.md) — build, verify, interpret, and submit results.
- [**Family witnesses**](evidence/family_witnesses.json) — 21 H159 first-round-minimal differential families with concrete message pairs.
- [**khash command-line utility**](tools/khash/README.md) — stream a file through the exact eight-round Krakken hash, with runtime scalar/AVX2 selection.

## Published lower bounds (activity, not security bits)

The research records the following **established lower bounds on active serial-Chi S-box calls** over eight rounds:

| Input domain | Certified lower bound |
| --- | ---: |
| Unrestricted nonzero state differences | **16** |
| Valid 159-byte first-block hash-message differences (**H159**) | **20** |
| H159, conditioned on exactly five first-round active S-box calls (`A1=5`) | **22** |

The complete H159 `A1=5` classification consists of **21 distinct input differences**, with the newly established conditional `A2>=5` and an eight-round activity floor of 22 for this class. The completed H159 `[6,1]` exclusion gives `A1+A2>=8` and the universal H159 eight-round floor of 20. The unrestricted eight-round floor remains 16. These are **lower bounds**, not attained minima, differential-hull probability bounds, or security-bit certifications. See [Research 07](research/KRAKKEN_RESEARCH_07.md), [Research 08](research/KRAKKEN_RESEARCH_08.md), and [Research 11](research/KRAKKEN_RESEARCH_11.md) for premises, scope, exceptions, and later refinements.

**New in [Research 12](research/KRAKKEN_RESEARCH_12.md) (November 18, 2026):** for a specific class of complete first-round output differences confined to words 0 and 14, each with bit 11 set, the next round has **`A2>=31`** active byte S-box calls. An explicit unrestricted fixed-input-difference subevent occurs with probability **`2^-48`** and satisfies **`A1+A2>=39`** and **eight-round activity `>=51`**. These are **conditional, non-H159 results** and do not change the general **16 / 20 / 22** bounds or establish security bits. Supporting replay artifacts described in the ledger have not yet been mirrored in this public repository.

**H159 first-round probability follow-up ([Research 12, §9](research/KRAKKEN_RESEARCH_12.md)):** for each of the **21 classified fixed H159 input differences**, a uniformly chosen 159-byte base message satisfies `A1=5` with **exact probability `2^-35`**. The qualifying bases form an affine space of dimension **1,237**, containing `2^1237` of the `2^1272` possible base messages. This is an **exact first-round activity-event probability**, **not** a two- or eight-round endpoint-differential bound, and it does not upgrade the 16 / 20 / 22 activity guarantees. The cited probability-foundation scripts and replay receipts are not yet mirrored in this GitHub repository.

**New in [Research 13](research/KRAKKEN_RESEARCH_13.md) (November 18, 2026):** a valid-H159 **four-message exchange square** with 32 guaranteed complete-one-round full-state parity coordinates (four inside the 256-bit reduced-round digest projection); a **carry-controlled rotational/DDT-support test through two complete rounds** for specifically constructed unrestricted related inputs; and documented exchange/Yoyo, boomerang, differential, linear and integral experiments. The two-round test has an approximate **`2^-129.448` ideal-permutation false-positive probability** for its specified 128-byte membership criterion, **not** a Krakken differential-probability bound or security-bit claim. The preserved rebound four-stage trail is a **surrogate-model** result, not a demonstrated four-round full-permutation attack. The general **16 / 20 / 22** bounds remain unchanged. The referenced `reproduce/exchange_bundle_v5_20261118/` evidence tree is not yet mirrored in this repository.

**No practical full eight-round break appears in the supplied research record.** That is not proof no break exists. Local and reduced-round distinguishers **do** exist and are published; independent generalizations are especially welcome.

**New in [Research 14](research/KRAKKEN_RESEARCH_14.md) (November 19–22, 2026):** source-specific eight-round H159 digest probability and finite-witness bounds, algebraic separation-rank lower bounds for digest parities, and restricted quartet/adaptive parity-selection analyses. For two independent pairs under each studied fixed-difference sampling model, the new samples support a **`<2^-20`** ceiling for matching full digest differences at **greater than 99% simultaneous confidence** across the two specified population panels. Other claims use different input distributions or exact finite classes. This does **not** establish a worst-case chosen-difference bound, concrete collision/preimage security bits, or changes to the general **16 / 20 / 22** active-S-box lower bounds. The referenced Research 14 reproduction directories have not been mirrored to this public repository.

**November 22 collision-hunter checkpoint ([Research 14, §14.12](research/KRAKKEN_RESEARCH_14.md#1412--full-digest-collision-hunter-checkpoint-22-november-2026)):** the operator reports **272,776,683** consecutive-counter, fixed-format messages with **zero full 256-bit digest collisions**. The prefix contains all `2^28` low-28-bit counter values. This is a finite, **reported** experiment: the live SQLite database and running binary were not audited, and deterministic counter enumeration is **not** an independent-uniform-message sample or a security-bit certificate.

**New in [Research 15](research/KRAKKEN_RESEARCH_15.md) (November 25–26, 2026):** compact four-wise independent sampling gives a reported uniform-H159 eight-round collision-probability ceiling `<2^-36` and point-probability ceiling `<2^-18.5` with joint confidence >99.188%. Fixed-difference and higher-order differential censuses provide exact finite-family certificates; separate population bounds apply only to specified directions and sampling models.

**New in [Research 16](research/KRAKKEN_RESEARCH_16.md) (November 26, 2026):** the reported exact unrestricted algebraic degree of each individual indexed round is **1443**. The unrestricted inverse-round degree is bounded by **573–882**; the cumulative two-round vectorial degree is at least 29, not known exactly. On the specified 18-dimensional message grid, all nonzero directions have maximum endpoint differential probability at most `2^-11`, with exact `2^-17` for 2,047 specified directions. These are scoped computational and analytic results, not security-bit estimates. Supporting Research 15–16 reproduction archives have not been mirrored here.

## Run the supplied tests

```sh
make test
make avx2-test  # requires a CPU/compiler supporting AVX2
```

The scalar reference and original AVX2 source remain unchanged; the additional Latitude v3 implementation is supplied separately. The repository provides known-answer tests, implementation notes and a collision experiment; these are **tests, not proofs of security**. See [Makefile](Makefile) and [Reproducibility](docs/REPRODUCIBILITY.md).

## Hash a file with `khash`

The author's original standalone file-hashing program is available at [`tools/khash/`](tools/khash/README.md). It keeps the cryptographic source files unchanged, streams files using the same hash interface, and prints a 256-bit digest:

```sh
make -C tools/khash
./tools/khash/khash /path/to/file
make -C tools/khash check
```

The `check` target compares streaming results against the reference C hash for boundary-length test files. This tool is for research and interoperability, **not a certification or recommendation to use the experimental hash to protect production systems**.

## Challenge the design

We welcome successful full-round attacks, reduced-round advances, counterexamples to documented lemmas, independent replays, corrected proofs, implementation flaws and entirely new methods. Please include a clear attack target, source version, reproducible code/data and honest complexity accounting.

Submit an issue with the supplied [cryptanalysis template](.github/ISSUE_TEMPLATE/cryptanalysis-result.md), or open a pull request. Criticism and failed replications are welcome.

> **Ten years of work is a reason to publish the evidence and invite adversarial scrutiny—not a substitute for it.**

## Design Origins and Acknowledgments

**Krakken-2048 is an original cryptographic permutation design that incorporates selected elements from established cryptographic constructions.**

The overall 2,048-bit permutation architecture, organization of its nine layers, and their integration into the complete round function are original to the Krakken project. However, several important mathematical and cryptographic components draw upon earlier work, which deserves explicit recognition.

### Keccak / SHAKE128

Krakken uses **SHAKE128**, based on the **Keccak-f[1600] permutation**, to deterministically generate its public round constants.

SHAKE128 is part of the SHA-3 family standardized in **NIST FIPS 202**.

Keccak was designed by **Guido Bertoni, Joan Daemen, Michaël Peeters, and Gilles Van Assche**.

The use of SHAKE128 for round-constant generation does not mean that Krakken's main eight-round permutation is Keccak.

### Whirlpool — Finite Field and MDS Matrix

Krakken incorporates two mathematical elements associated with the **Whirlpool cryptographic hash function**, designed by **Paulo S. L. M. Barreto and Vincent Rijmen**.

**1. Finite-field arithmetic**

Krakken uses arithmetic in GF(2⁸), defined by the irreducible polynomial:

`x⁸ + x⁴ + x³ + x² + 1` (`0x11D`)

This is the same finite-field polynomial used by Whirlpool.

Krakken's **Abyssal S-box** is constructed using multiplicative inversion in this field followed by an affine transformation. The resulting S-box is specific to Krakken and is not a copy of Whirlpool's S-box.

**2. MDS diffusion matrix**

Krakken's **Tentacle MDS** layer uses the eight-byte circulant coefficient sequence:

`01 01 04 01 08 05 02 09`

These coefficients originate from Whirlpool's diffusion matrix and are applied within Krakken's own state organization and round structure.

### Originality and Attribution

Krakken combines established mathematical ingredients with its own permutation architecture, serial nonlinear transformations, diffusion mechanisms, and round organization.

The author gratefully acknowledges the designers of **Keccak** and **Whirlpool** for their contributions to cryptography and for the mathematical foundations incorporated into this project.

These acknowledgments identify the origins of specific components. They do not imply endorsement by the original designers, nor do security analyses of Keccak or Whirlpool automatically establish the security of Krakken.

© Contributors; see repository history for authorship and license terms. No license is implied by publication where none is provided.

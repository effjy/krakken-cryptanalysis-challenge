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
| Round constants | SHAKE128-derived, public and deterministic |

The full construction, unrestricted permutation, individual layers, and reduced-round variants are all legitimate cryptanalytic targets. **Specify exactly which interface and number of rounds your result addresses.**

Reference SHA-256 pins:

```text
krakken.c       4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6
krakken.h       83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c
krakken_multi.c 9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2
```

**The implementation is the attack target; the 11 original research documents below are evidence and claims to test, not an assertion of invulnerability.** Source revisions or differing hash interface conventions must be reported.

## Start here

- [**CHALLENGE.md**](CHALLENGE.md) — what counts as a break; scope and disclosure.
- [**Known results**](docs/KNOWN_RESULTS.md) — latest bounded claims, including what remains unproved.
- [**Open attack problems**](docs/OPEN_PROBLEMS.md) — independent research opportunities.
- [**Implementation specification**](docs/REFERENCE.md) and [test vectors](docs/TEST_VECTORS.md).
- [**Research archive**](research/README.md) — **all 11 unmodified, original research ledgers** dated through November 15, 2026.
- [**Reproduction guidance**](docs/REPRODUCIBILITY.md) — build, verify, interpret, and submit results.
- [**Family witnesses**](evidence/family_witnesses.json) — 21 H159 first-round-minimal differential families with concrete message pairs.

## Published lower bounds (activity, not security bits)

The research records the following **established lower bounds on active serial-Chi S-box calls** over eight rounds:

| Input domain | Certified lower bound |
| --- | ---: |
| Unrestricted nonzero state differences | **16** |
| Valid 159-byte first-block hash-message differences (**H159**) | **19** |
| H159, conditioned on exactly five first-round active S-box calls (`A1=5`) | **21** |

The complete H159 `A1=5` classification consists of **21 distinct input differences**, with a universal conditional `A2>=4`. Certain individually specified families have stronger exclusions. None of these activity bounds is asserted to be the attained minimum or a full-round differential probability/security-bit bound. See [Research 07](research/KRAKKEN_RESEARCH_07.md), [Research 08](research/KRAKKEN_RESEARCH_08.md), and [Research 11](research/KRAKKEN_RESEARCH_11.md) for premises, scope, exceptions, and later refinements.

**No practical full eight-round break appears in the supplied research record.** That is not proof no break exists. Local and reduced-round distinguishers **do** exist and are published; independent generalizations are especially welcome.

## Run the supplied tests

```sh
make test
make avx2-test  # requires a CPU/compiler supporting AVX2
```

The scalar reference and optimized source are kept unchanged in this relaunch. The repository provides known-answer tests, implementation notes and a collision experiment; these are **tests, not proofs of security**. See [Makefile](Makefile) and [Reproducibility](docs/REPRODUCIBILITY.md).

## Challenge the design

We welcome successful full-round attacks, reduced-round advances, counterexamples to documented lemmas, independent replays, corrected proofs, implementation flaws and entirely new methods. Please include a clear attack target, source version, reproducible code/data and honest complexity accounting.

Submit an issue with the supplied [cryptanalysis template](.github/ISSUE_TEMPLATE/cryptanalysis-result.md), or open a pull request. Criticism and failed replications are welcome.

> **Ten years of work is a reason to publish the evidence and invite adversarial scrutiny—not a substitute for it.**

© Contributors; see repository history for authorship and license terms. No license is implied by publication where none is provided.

# Krakken Cryptanalysis Challenge

> **Break it.**

Krakken-2048 is an **experimental 2048-bit permutation-based hash construction** published specifically for open cryptanalysis. This repository is a research target, not a security claim and not a recommendation for production use.

The goal is simple: **analyze Krakken, find structure, improve the known attacks, or break the full construction.**

## Reference target

| Property | Current challenge target |
|---|---|
| Internal state | 2048 bits (32 × 64-bit words) |
| Full permutation | 8 rounds |
| Hash absorb rate | 160 bytes |
| Default challenge digest | 32 bytes / 256 bits |
| Reference implementation | Scalar C (`krakken.c`) |\n| Optimized implementation | AVX2 + multithread helper (`krakken_multi.c`) |
| Round constants | SHAKE128-derived |
| Source pin | `krakken.c || krakken.h` SHA-256: `6b3d5a5d416e2923379e0b38305babb4cb0471c1833d7d3a6c4e8356005d8893` |

Individual source hashes:

- `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
- `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`
- `krakken_multi.c` (AVX2): `9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2`

If those hashes change, treat the new code as a different target unless the change is explicitly documented.

## Quick start

    make test
    make benchmark

`make test` builds the scalar reference plus known-answer tests. `make avx2-test` cross-checks the optimized implementation against the scalar target over reduced-round permutation states, padding/multiblock/squeeze boundaries, and randomized hash inputs. The empty-string 256-bit digest for this source revision is:

    e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd

More vectors are in [docs/TEST_VECTORS.md](docs/TEST_VECTORS.md).

## Start here

- **[Challenge rules](CHALLENGE.md)** — what counts as a break or meaningful result.
- **[Reference construction](docs/REFERENCE.md)** — state layout, round function, absorb/padding/squeeze behavior.
- **[Known results](docs/KNOWN_RESULTS.md)** — concise summary of current source-pinned cryptanalysis.
- **[Open problems](docs/OPEN_PROBLEMS.md)** — places where new attacks would be especially interesting.
- **[Implementation notes](docs/IMPLEMENTATION_NOTES.md)** — known API/reference-code caveats that are not cryptanalytic results.
- **[Test vectors](docs/TEST_VECTORS.md)** — hash and permutation KATs.
- **[Contributing](CONTRIBUTING.md)** — how to submit analysis, code, contradictions, and implementation reports.

## Detailed research records

The concise challenge documentation is backed by a larger source-pinned theorem record. See **[research/](research/README.md)** for the current claims-for-review document, theorem program, permanent theorem inventory, and coordinated multi-cell boomerang report.

These records are published to help attackers avoid rediscovering already-closed classes and to make existing claims easy to challenge.

## Reproducible experiments

- **[Reduced-round truncated collision experiment](experiments/collision/README.md)** — compare first-collision behavior across rounds and output widths against the random-function birthday baseline, with saved replayable witnesses.

## What counts as interesting?

Full eight-round results are the main target, but reduced-round and structural work is welcome. Examples include:

- collisions, preimages, or second preimages beating the generic reference complexity for the 256-bit challenge digest;
- distinguishers against the eight-round hash or unrestricted permutation with clearly stated data/time/memory;
- improved differential, linear, differential-linear, integral, rebound, rotational, boomerang, or algebraic attacks;
- new invariants, subspaces, impossible transitions, or quantitative trail/hull bounds;
- reduced-round records that extend the known frontier;
- independent reproduction, strengthening, or falsification of a listed theorem;
- implementation bugs, reported separately from cryptanalytic breaks.

A result does **not** need to destroy all eight rounds to be useful. Precise negative results are useful too if they close a well-defined attack class.

## Current research posture

Krakken has yielded substantial exact local and reduced-round structure, but that structure has so far been difficult to extend into a useful full eight-round attack. The current research includes exact first-round activity results, Pressure carry/correlation results, differential exclusions, local and coordinated boomerang structures, one-round message-to-output correlation bounds, integral/subspace results, and several complete defined theorem classes.

That is **not evidence of a security level**. It is a map of what has and has not been ruled out.

The challenge explicitly welcomes attempts to invalidate existing claims.

## Research etiquette

Please state:

1. the exact source revision or hash you attacked;
2. whether the domain is the hash interface or unrestricted permutation;
3. the exact number of rounds/checkpoint;
4. whether the result is analytic, exhaustive, solver-backed, heuristic, or empirical;
5. time, data, memory, conditioning cost, and success probability where applicable;
6. enough code/data for someone else to reproduce the claim.

Use the GitHub issue templates for new findings. Pull requests with reproducible attacks, verifiers, test vectors, or corrected documentation are welcome.

## Security warning

**Do not use Krakken to protect real systems or data.** This repository exists to invite cryptanalysis of an experimental design.

---

If you find something ugly, please publish it. That is the point. 🐙🔨

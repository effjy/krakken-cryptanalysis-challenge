# Krakken: randomness assessment and limited certificates

Date: 2026-11-12. **Only the original `krakken.c` and `krakken.h` are evaluated
here, using the scalar implementation and all eight rounds.** No AVX2 core,
Even–Mansour layer, Kyber component, or modified permutation is used.

## Verdict

**Krakken passed the structural checks and produced no flags in the
predeclared low-order statistical tests described below. This is encouraging
evidence of diffusion, but it does not certify that Krakken behaves as an
ideal random permutation. Its concrete 128-bit collision and 256-bit
preimage security remain unproved.**

What this file can support:

| Statement | Status |
|---|---|
| The original eight-round map is a bijection on 2048-bit states | Proved by invertible layers; source and inverse controls passed |
| Uniform unrestricted full-state inputs give exactly uniform full-state outputs | Exact consequence of bijectivity; not a security guarantee |
| The sponge parameters permit the requested classical 128/256 benchmarks in the ideal-permutation model | Conditional theorem; actual Krakken ideality is not proved |
| The selected one-bit differential and correlation statistics show no flags at the chosen threshold | Observed, reproducible statistical result with stated sampling assumptions |
| Krakken is indistinguishable from an ideal permutation against all relevant cryptanalytic attacks | **Not certified** |
| Actual Krakken has 128-bit collision / 256-bit preimage security | **Not certified** |

The machine-readable report deliberately contains
`random_permutation_certified: false` and `security_bits_certified: null`.
This prevents a statistical result from being mistaken for a cryptographic
security certificate.

## 1. What the Keccak sponge result means

The Keccak team's theorem analyzes the sponge construction when its inner
primitive is an **ideal random permutation or transformation**. It does not
establish that a particular implementation is ideal because its output looks
like noise. See their [indifferentiability paper](https://keccak.team/files/SpongeIndifferentiability.pdf).

For a 256-bit random-oracle digest, the classical generic collision and
single-target preimage scales are respectively `2^128` and `2^256`. The
sponge capacity controls an additional generic limitation. The team's
[sponge explanation](https://keccak.team/sponge_duplex.html) separates this
construction-level result from attacks exploiting a concrete permutation.

### Conditional certificate KRAKKEN-RANDOM-IDEAL-SPONGE-001

For the original hash with a 32-byte digest, source inspection and independent
sponge replay establish:

```
state width b = 32 * 64 = 2048 bits
rate r        = 160 * 8 = 1280 bits
capacity c    = b - r   = 768 bits
digest n      = 32 * 8  = 256 bits
rounds                  = 8
```

The byte padding appends `0x06`, fills to a rate boundary with zeroes, and
sets the high bit of the final byte. At a 159-byte remainder this combines
to `0x86`. It is reversible on byte strings: clear the final high bit, remove
the trailing zero bytes and final delimiter byte, and recover the message.
Every padded string has a nonzero final block. Full rate multiples receive
an additional padded block. Independent sponge evaluation agrees with the
original hash at lengths 0, 1, 158, 159, 160, 161, 319, 320, 321, and 4096.

**If the core is replaced by a uniformly sampled ideal 2048-bit permutation
in the ideal-permutation model**, the corresponding Krakken-format sponge
has the conventional classical generic benchmarks

```
collision:        min(n/2, c/2) = min(128,384) = 128 bits
single preimage:  min(n,   c/2) = min(256,384) = 256 bits
```

The conservative generic bound summarized by the Keccak team adds a term
`N^2 / 2^(c-1)` to the corresponding random-oracle attack probability, with
`N` counting primitive queries. For these parameters that term is
`N^2 / 2^767`: at `N=2^128` it is `2^-511`, and at `N=2^256` it is `2^-255`.
These arithmetic examples show that capacity is not the limiting parameter
for the requested benchmarks. They do not bound attacks exploiting Krakken's
specific structure. [Generic bound and scope](https://keccak.team/sponge_duplex.html).

This conditional statement concerns an **idealized mathematical object**.
We have not shown that replacing its ideal core with actual Krakken preserves
the bound. The benchmarks are classical and single-target, not quantum or
multi-target guarantees. Efficient inversion of the full permutation is
normal; the preimage benchmark concerns the truncated sponge digest.

## 2. Why a literal fixed-permutation randomness certificate is unavailable

Let `P` be the publicly specified Krakken permutation. In a literal experiment
where an oracle is either `P` or an independently sampled uniform permutation
`Pi`, a distinguisher can compute `P(0)`, query the oracle at zero, and compare
the complete results. It accepts the real branch with probability one and
the random branch with probability `2^-2048`. Its probability gap is
`1-2^-2048`. The actual `P(0)` is saved in `zero_output.hex`.

This observation applies to any publicly specified fixed permutation. It
is **not a collision or preimage attack** on its sponge. It explains why a
standard secret-key pseudorandom-permutation assertion is the wrong literal
certificate for this unkeyed object. The useful design question is whether
there are exploitable structural properties that make the construction
weaker than its ideal-model benchmark.

Finite statistical tests cannot answer that question against every attack.
NIST likewise cautions that statistical testing does not replace
cryptanalysis. This run uses purpose-built tests and makes no claim of
NIST testing or certification. [NIST SP 800-22](https://csrc.nist.gov/pubs/sp/800/22/r1/upd1/final).

## 3. Exact structural certificate

### Theorem KRAKKEN-RANDOM-BIJECTION-001

The original full eight-round Krakken map is a bijection on `{0,1}^2048`.

Proof by layers:

* Theta is involutive: XORing the same correction into four words preserves
  their column parity, so the second application removes the correction.
* The MDS matrix has an explicitly verified inverse over the source's
  `GF(2^8)` representation. Rho and Pi are invertible rotations/permutations.
* In an aligned Chi cell, `u=S(a XOR b)` and `v=S(b XOR u)`. With the inverse
  S-box, recover `b=S^-1(v) XOR u`, then `a=S^-1(u) XOR b`.
* Every Butterfly stage consists of reversible XOR shears; undo its steps
  and stages in reverse order.
* Pressure's output rotations are reversible. Subtract the second shear
  modulo `2^64`, then subtract the first shear, independently in each branch.
* Iota is XOR with constants. InkCloud is an invertible word permutation
  and rotation. Composition preserves bijectivity.

New source checks in this run:

| Check | Coverage |
|---|---:|
| S-box values form a permutation | All 256 values |
| Serial-Chi inversion and agreement with original C | All 65,536 cell inputs |
| MDS matrix times its inverse equals identity | All 64 entries |
| Independent linear prefix and inverse agree with original C | All 2048 bit-basis vectors |
| Round constants agree with independent SHAKE128 generation | All 256 words |
| Independent full-eight-round inverse reverses original C, and conversely | 64 control states in each direction |

The local algebra proves bijectivity universally. The full-state inverse
controls check implementation; they are not exhaustive enumeration of
`2^2048` states.

### Corollary KRAKKEN-RANDOM-UNIFORM-001

If `X` is uniform over all 2048-bit states, then for every state `y`,

`Pr[P(X)=y] = Pr[X=P^-1(y)] = 2^-2048`.

This is exact, but the identity permutation also has this property. Thus a
frequency test on outputs of uniformly random unrestricted inputs provides
little evidence of cryptographic quality by itself.

The H159 input distribution has only `2^1272` possible states, so its full
2048-bit image is not uniform over all states under **any** permutation,
including an ideal one. This does not prevent its 256-bit digest or tested
bit marginals from looking uniform. Comparisons must use matching domains.

## 4. New statistical experiment on the original scalar implementation

The plan and sample files were fixed before evaluating outputs. The saved
samples came from the operating system's random source and are retained for
reproduction. No sample regeneration or hypothesis selection was used after
inspecting outcomes.

Two domains were tested:

1. **Unrestricted:** 2048 sampled 2048-bit states; every one of the 2048
   single-bit input differences.
2. **H159:** 2048 sampled 159-byte messages, followed by `0x86` and 96 zero
   bytes; every one of the 1272 permissible single-bit message differences.

For each direction `i`, base `X`, and output bit `j`, write
`D_i(X)=P(X) XOR P(X XOR e_i)`. We counted:

* `D_i(X)_j = 1`: output-bit flip probability.
* `D_i(X)_j XOR D_i(X)_(j+1) = 1`, wrapping at bit 2048: an adjacent-output
  derivative parity that can detect some dependencies missed by flip counts.
* `X_i XOR P(X)_j = 1`: single-input-bit/single-output-bit correlation.

We also recorded base-output bit frequencies. Every statistic has 2048
sample observations. Bases are reused across directions, so different
statistics are correlated; they are **not** treated as independent.

Total: **6,799,360 related-input pairs** and **20,402,176 tested marginal
probabilities**. The scalar collector links only the original `krakken.c`.

### Results

| Domain | Directions | Related-input pairs | Mean output bits changed, out of 2048 | Observed minimum–maximum |
|---|---:|---:|---:|---:|
| Unrestricted | 2048 | 4,194,304 | 1024.001014 | 907–1138 |
| H159 | 1272 | 2,605,056 | 1023.991343 | 910–1135 |

An idealized balanced derivative has mean Hamming distance approximately
1024. Agreement of the averages is descriptive evidence, not a security proof.

| Domain/statistic | Smallest observed probability | Largest observed probability | Flags at the simultaneous threshold |
|---|---:|---:|---:|
| Unrestricted bit flips | 0.443848 | 0.557129 | 0 |
| Unrestricted adjacent derivative parity | 0.438477 | 0.562988 | 0 |
| Unrestricted one-bit input/output XOR | 0.441895 | 0.555176 | 0 |
| H159 bit flips | 0.441406 | 0.555664 | 0 |
| H159 adjacent derivative parity | 0.444824 | 0.559082 | 0 |
| H159 one-bit input/output XOR | 0.443359 | 0.560059 | 0 |

Base-output frequency tests also produced zero flags. These ranges are
**empirical sample frequencies**, not exact population probabilities.

A deliberately unsuitable **identity permutation** was tested separately
with the same collector on 16 directions and 256 samples. Its flip matrix
was exactly the expected diagonal matrix, and every one of its 32,768
flip-probability entries was flagged. This verifies that the procedure can
detect obvious non-random differential structure even though the identity
preserves uniform full-state inputs.

Eight complete differential rows, including collector partition boundaries,
were independently recomputed through the original scalar C API and counted
using NumPy bit extraction. All three statistics matched exactly. This is
an implementation cross-check, not a second full sample experiment.

### Statistical certificate KRAKKEN-RANDOM-MARGINAL-001

Assume the saved base samples represent iid uniform draws in their respective
domains. For each fixed statistic, its sample mean is an average of bounded
iid Bernoulli variables. Let `M=20,402,176`, `N=2048`, and `alpha=0.01`.
Hoeffding's inequality and a union bound give

```
epsilon = sqrt(ln(2*M/alpha)/(2*N))
        = 0.07350307824379629

Pr_samples[all M empirical means differ from their true means
           by at most epsilon] >= 0.99.
```

No independence between output bits, directions, or different tests is
required. The confidence statement concerns repeated sampling, conditional
on the iid sampling model; it is not a certificate of perfect OS entropy.

A diagnostic flag is raised when an empirical probability differs from
`1/2` by more than epsilon. **There were zero flags.** This tests the balanced
marginal hypothesis; it is not a formal ideal-permutation indistinguishability
test or a statement that every ideal permutation has exactly balanced
derivatives over its full domain.

The largest observed absolute bias was `0.06298828125`. Adding epsilon gives
a simultaneous 99%-confidence upper bound of approximately **0.136492** on
the absolute population biases of these selected statistics. The width is
substantial: this run rules out some gross deviations, not subtle biases
that could matter cryptanalytically. In particular, **99% confidence here
does not mean a 99% probability that Krakken is random or secure**.

These are single-bit directions, individual output bits, adjacent derivative
parities, and one-bit linear correlations. They do not cover arbitrary
multi-bit differences or masks, differential hulls, higher-order relations,
adaptive chosen-input attacks, or general multi-block hash inputs.

## 5. How this fits the existing proofs

The separate [composable activity certificate](reproduce/COMPOSABLE_ACTIVITY_BOUNDS.md)
already proves eight-round total active-call floors of 15 for unrestricted
distinct inputs, 19 for nonzero differences confined to the first 159 bytes,
and 20 for that family when the first round has five active calls. Those are
universal deterministic exclusions and remain more substantial than passing
a noise test, but they still do not establish ideal-permutation behavior.

The finite-family collision results in [COLLISIONS.md](COLLISIONS.md) also
remain exactly scoped to their tested families or stated statistical models.
They are not upgraded to 128-bit collision security by this experiment.

The useful next steps are stronger attack-family exclusions, tighter
dependency-safe probability bounds, and external cryptanalytic review.
Increasing the statistical sample size alone cannot bridge the gap to a
general ideal-permutation or security-bit certificate.

## 6. Evidence and reproduction

Original source fingerprints:

```
krakken.c  4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6
krakken.h  83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c
```

Code, saved random samples, raw count matrices, the predeclared plan, and
reproduction instructions are in `krakken_research/randomness/README.md`.
Exact structural checks are in `structural_results.json`; measured results
and confidence limits are in `RESULTS.json` in that directory. The original
cryptographic source files were not modified.

## Higher-order extension: an exact result at two and eight rounds

A subsequent research pass extended testing to structured differences and
higher-order derivatives. Complete argument, measurements, and limits:
[higher-order report](krakken_research/higher_order/REPORT.md).

### Certificate KRAKKEN-H159-COMPONENT-DEGREE-009

Let `G_r(m)` be the full 2048-bit output after the first `r` original scalar
rounds, starting from the padded state of a 159-byte message `m`.
For **r = 2 and r = 8**, and **every nonzero 2048-bit mask `a`**, the Boolean
function `a dot G_r(m)` has algebraic degree **at least 9** in the 1272
message bits.

The finite certificate consists of 2080 nine-dimensional coordinate cubes
inside the valid message domain. For each round count, XORing all 512 output
states of each cube gives 2080 derivative vectors whose binary rank is
**2048**. The C replay enumerates the same cubes independently in Gray-code
order, and the checker compares every sum and recomputes rank with the
opposite pivot order. See the saved [verification results](krakken_research/higher_order/VERIFICATION.json).

Proof: any polynomial of degree at most 8 has identically zero ninth-order
coordinate derivatives. If a nonzero output mask selected such a polynomial,
it would annihilate every recorded derivative vector. Full rank makes that
impossible. Thus the certificate covers all `2^2048-1` nonzero masks without
independence assumptions or a probabilistic extrapolation from samples.
This is a source-pinned computational certificate, not a proof-assistant
verification of the C implementation.

For the original **256-bit hash of exactly 159-byte messages**, the digest
is the first 256 output bits of `G_8`. Consequently, every nonzero linear
combination of its digest bits also has degree at least 9. Fixing input bits
cannot increase degree, so the corresponding full-state component functions
also have degree at least 9.

This rules out degree-at-most-eight components on the stated entire input
domain. It does not exclude special balanced cubes, sparse higher-degree
terms, or stronger algebraic attacks; it does not bound the frequency of
nonzero derivatives or yield collision/preimage security bits.

The same pass tested **23 structured multi-bit differences** in each of two
domains, with 1024 bases each: **47,104 related-input pairs** and **94,208**
output flip probabilities. There were **zero flags**, with a separate 99%
simultaneous Hoeffding radius of 0.090440485 under iid base sampling.
These are coarse statistical limits, distinct from the exact degree proof.
Together with the previous statistical family, a union bound gives at least
98% simultaneous coverage under the stated assumptions, not a joint 99%.

[Code, plans, raw evidence, and reproduction commands](krakken_research/higher_order/README.md).
The prior root reports are preserved there as `prior_RANDOM.md` and
`prior_Krakken.md`; the earlier experiment's checksum manifest refers to
those historical document contents. The new manifest covers this update.

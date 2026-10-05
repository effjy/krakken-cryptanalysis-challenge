# Unconditional first-round differential bounds for three fixed differences

Permanent ID: **DIFF-RATE-008**. Analytic proof plus finite exhaustive
certificates, with a separate independent implementation audit within this
investigation. No external reproduction is recorded.

Let `F1(m)` be the full state after one complete current XRBD-enabled scalar
round, starting from the valid first block `m || 0x86 || zero capacity`, where
`m` is a uniform 159-byte message. Fix any of the three message differences
indexed `(support,difference)=(2,6),(2,9),(21,2)` in
[DIFF-RATE-003](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-003). Their exact bytes
are preserved in the certificate. There is **no activity conditioning**.

For **every** prescribed 2048-bit output difference `d`,

`Pr_m[F1(m) XOR F1(m XOR delta)=d] < 507/512000 = 1.014/1024`.

The proof bounds the selected ten-bit output projection consisting, in order,
of lane 28 bits 11–15 and lane 10 bits 11–15. These are outside the first
256 bits used as the digest. Every full-state difference implies one projected
value, giving the all-full-state-output corollary. No digest-output bound,
other input-difference bound, later-round bound or security-bit interpretation
is asserted. This is a bound on the complete differential distribution for
the three stated differences, including all compatible internal trajectories;
it is not a product of local trail probabilities.

The actual projected differential distribution is within total variation
**strictly less than `2^-145`** of the following exact finite reference law `Q`.
Its point maxima, rounded only in the display column, are:

| Fixed difference | Exact `max_y Q(y)` | Approximate maximum | Maximizing projected value |
|---|---|---:|---:|
| `(2,6)` | `4561743864564605 / 2^62` | `0.000989170522` | `16` |
| `(2,9)` | `9131790296210861 / 2^63` | `0.000990070688` | `16` |
| `(21,2)` | `1152944171538406687 / 2^70` | `0.000976581700` | `512` |

For each case, the stronger exact bound is `Pr[D=d] <= max Q + epsilon`,
where `epsilon < 2^-145`. The common rational ceiling above follows by exact
integer inequalities. The random ten-bit point reference is `1/1024`.

There is an attack-side consequence too: the maximizing points exceed
`1/1024` by more than the error enclosure. Thus these specific **one-round
nondigest projected differences are provably nonuniform**. The maximum upper
bound being close to `1/1024` does not imply a uniform distribution or absence
of a reduced-round distinguisher. This does not concern the deployed
eight-round digest distribution.

## Why the unconditional problem closes

Each fixed difference is supported on exactly five pre-Chi serial cells.
The combined message-to-cell input projection has rank **80/80**. Hence those
five two-byte inputs are independent uniform 16-bit values under a uniform
message base, even though the full state need not be uniform.

Let `X_local` denote this 80-bit collection. For each value of this collection, the
post-Chi1 difference is fixed, is zero outside the five cells, and maps through
linear XRBD to a fixed Pressure input difference. Fixing the collection is a
nonempty affine codimension-80 condition on the message. Unlike conditioning
on `A1=5`, this partition covers **every** base message and every first-round
activity case.

The target is Pressure chain 2, with input words in lanes 4 and 6. For its
low five output bits, write

`P5(a,c,h)=(a+(c XOR h), c+a+(c XOR h)) mod 32`,

where `h=c_word[17:22]`. The shifted `A<<31` term cannot enter these bits.
The three local input slices are disjoint in the full chain input.

The full five-bit input slice has fifteen coordinates. A generic Fourier
uniformity bound on it is vacuous with the current affine-image inequality.
However, its **differential** needs only twelve base coordinates. Translating
the top input bit changes the output by a constant:

`P5(z XOR 16)=P5(z) XOR (16 | (16<<5))`,
`P5(z XOR (16<<5))=P5(z) XOR 16`,
`P5(z XOR (16<<10))=P5(z) XOR (16 | (16<<5))`.

These identities hold algebraically because adding a top-bit value modulo
32 toggles only that bit. Consequently `P5(z) XOR P5(z XOR delta_z)` is
independent of all three base-input top bits. It still depends on the full
fifteen-bit **difference** `delta_z`. This distinction is essential.

Let `Z4` be the low four base bits of `a,c,h`, packed as twelve bits.
The effective-coordinate affine-image lemma gives an all-message-mask bound
`B_t` for every nonzero character of `Z4`. The finite certificate checks all
4,095 masks using actual prefix ranks and exact local Walsh maxima, and gives

`S=sum_(t!=0) B_t^2 <= 2^-448`.

For every fixed value of the affected-cell input collection, affine
conditioning and Fourier Parseval/Cauchy–Schwarz imply

`TV(Law(Z4 | X_local),Uniform(F2^12)) <= 2^79 sqrt(S) < 2^-145`.

The strict final inequality is checked against the exact saved rational `S`.
This step preserves all dependencies between the affected Chi cells and the
Pressure base. Their independence from `Z4` is not assumed.

For each conditioned value, the selected output difference is a deterministic
function of `Z4` and its fixed fifteen-bit `delta_z`. Total variation contracts
under this function. Averaging over the uniform affected-cell collection gives
the same error bound from the reference law obtained by replacing `Z4` with
an independent uniform twelve-bit value. That law is `Q`.

## Exact finite construction of Q

For each of the five independent two-byte Chi inputs:

1. Evaluate all 65,536 local bases using the source S-box and exact serial-Chi
   equations.
2. Map the resulting local output difference through XRBD into the fifteen
   observed Pressure difference bits.
3. Count its histogram exactly.

XOR-convolving the five histograms gives the exact Pressure difference law,
with denominator `2^80`. Integer Walsh convolution replaces enumeration of
all `2^80` cell-input combinations; it does not approximate them.

Enumerate all `32768 × 4096 = 134217728` effective local Pressure pairs.
Weight each projected output-difference histogram by the exact fifteen-bit
input-difference law. All sums use exact integers, with reference-law
denominator `2^80 × 2^12 = 2^92` before reduction. The complete 1,024-point
law is saved for each difference, rather than only its maximum.

Constants cancel in differences. Chain 2 has no odd-chain rotation. The final
shuffle transports the two low-five-bit outputs to the selected lane/bit
positions. Original-C replay verifies this complete-round transport.

## Independent implementation audit

The separate audit reconstructs and compares all 1,272 message-prefix columns
using an independent Python prefix and original C; reconstructs all 2,048
XRBD columns using original-C basis inputs; uses opposite-pivot elimination
and direct character sums to reproduce **all 4,095** Fourier bounds; and
independently confirms each affected-cell projection rank is 80.

It separately enumerates all local Chi bases for the fifteen case/cell
combinations (**983,040 evaluations**), uses a recursive integer transform
instead of the producer's iterative one, and checks the three complete
Pressure input-difference distributions. A separate scalar C program, using
exact unsigned 128-bit integer accumulation, reproduces every point of all
three reference output laws and checks the top-bit translation identities
on every one of the 32,768 local inputs. Both 159-byte messages are preserved
for each of **96 original-C complete-round pair replays**. The audit also
checks the common rational ceiling and the nonuniformity corollary.

This is an independent implementation audit inside this investigation,
not external cryptanalytic reproduction. The replay messages validate the
implementation; the analytic mixture/conditioning argument and exhaustive
finite certificates prove the stated bound.

## Artifacts and reproduction

- [Producer](../scripts/krakken_unconditional_round1_differential.py) and
  [ten-bit certificate](../results/krakken_unconditional_round1_differential_k5.json).
- [Separate audit](../scripts/krakken_unconditional_round1_differential_audit.py),
  [scalar C mixture counter](../scripts/krakken_pressure_mixture_audit.c), and
  [final audit report](../results/krakken_unconditional_round1_differential_k5_audit_final.json).
- [Four-bit slice-mask certificate](../results/krakken_conditioned_pressure_ch02_k4.json),
  independently fully reproduced by the new audit.
- The initial eight-bit pilot is retained in
  [its report](../results/krakken_unconditional_round1_differential.json) and
  [its original producer](../scripts/krakken_unconditional_round1_differential_initial.py).
- The vacuous full-fifteen-bit slice attempt is retained in
  [its report](../results/krakken_conditioned_pressure_ch02_k5.json); it is not
  theorem evidence. The effective twelve-bit reduction avoids that failed
  inequality.

Use fresh output names, one low-priority process at a time:

```bash
cd /home/user/sol
OPENBLAS_NUM_THREADS=1 nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_unconditional_round1_differential.py --output-bits 5 --output results/krakken_unconditional_round1_differential_replay.json
OPENBLAS_NUM_THREADS=1 nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_unconditional_round1_differential_audit.py --report results/krakken_unconditional_round1_differential_replay.json --output results/krakken_unconditional_round1_differential_audit_replay.json
```

The pinned `krakken.c/h`, ongoing AB campaign and frozen bundle were not
modified. The next frontier is more output coordinates or more input
differences, then rigorous propagation to later rounds. The unconditional
one-round target is closed for **these three differences**, not for every
possible message difference.

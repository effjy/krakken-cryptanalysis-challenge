# Conditioned first-round differential bound through Pressure

Permanent theorem ID: **DIFF-RATE-007**. Analytic proof plus finite exhaustive
certificate; separate independent implementation audit within this investigation.
No external reproduction is recorded.

For the three fixed message differences in
[DIFF-RATE-003](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-003), let `H` be the event
`A1=5`. The base is a uniform 159-byte message, padded with `0x86` at byte 159
and zero initial capacity, using the current XRBD-enabled original scalar C.
`H` is a nonempty affine message subspace of codimension 35, so `Pr(H)=2^-35`.
Its post-Chi1 difference, and hence its Pressure input difference, is fixed.

Let `D(m)=F1(m) XOR F1(m XOR delta)` be the **full 2048-bit difference after
one complete round**. For every prescribed full-state difference `d`:

| Fixed difference, indexed in the inherited certificate | Selected Pressure slice | Bound on `Pr[D=d | H]` | Bound on `Pr[H and D=d]` |
|---|---|---|---|
| support 2, difference 6 | chain 2, low four bits of both outputs | `1/4 + 2^-204` | `2^-37 + 2^-239` |
| support 2, difference 9 | chain 2, low four bits of both outputs | `1/8 + 2^-197` | `2^-38 + 2^-232` |
| support 21, difference 2 | chain 1, low five bits of both outputs | `1/16 + 2^-182` | `2^-39 + 2^-217` |

The error terms enclose exact saved rational bounds strictly. The same bounds
apply to each specified value of the selected output projection. All selected
bits are outside the 256-bit digest projection. These are **conditional
complete-round differential bounds**, not unconditional bounds for these input
differences, multi-round bounds, all-input-difference bounds, or security bits.
The result outside `H` is left open. Local uniform-slice maxima are exact;
sharpness under the actual conditioned message distribution is not claimed.

## Proof

For a Pressure chain and `k<=17`, pack its observed input slice as

`Z=a[0:k] | (c[0:k]<<k) | (c[17:17+k]<<(2k))`.

Its relevant local outputs are exactly
`A=a+(c XOR h) mod 2^k`, `C=c+A mod 2^k`. The `A<<31` term cannot reach these
bits. Odd-chain rotations and the final shuffle only transport output bits;
round constants cancel between the two states. On `H`, the slice difference
`delta_Z` is fixed, so the projected round difference is the deterministic
function `G(Z)=P_k(Z) XOR P_k(Z XOR delta_Z)`.

For each nonzero slice mask `t`, the effective-coordinate affine-image lemma
used by [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) gives a bound
`B_t` on `|E_m (-1)^(alpha·m XOR t·Z(m))|` for **every** message mask `alpha`.
Pull `t` backward through the exact XRBD transpose. Use eight effective input
coordinates `x=a XOR b` for each first-output-only serial-Chi component, and
all sixteen input coordinates when the second output is masked. If the combined
message projection has rank `r`, and `M_i` are the corresponding local maximum
unnormalized Walsh coefficients, then

`B_t = min(1, product_i M_i / 2^r)`.

This follows by expanding the affine-image indicator over its annihilator;
the local full-space Walsh coefficients factor, while the rank accounts for
all linear dependencies. It does not assume independent Chi inputs on the
message image. Fixed padding affects phases, not these magnitude bounds.

The normalized indicator of an affine codimension-35 event is a signed sum
of `2^35` message characters. Therefore

`|E[(-1)^(t·Z) | H]| <= min(1,2^35 B_t)`.

For every projected difference `y`, enumerate the local Boolean function
`f_y(z)=1[G(z)=y]` over its entire `2^(3k)`-point domain and compute
`hat(f_y)(t)=2^(-3k) sum_z f_y(z)(-1)^(t·z)`. Then exactly

`Pr[G(Z)=y | H] = hat(f_y)(0) + sum_(t!=0) hat(f_y)(t) E[(-1)^(t·Z)|H]`.

Consequently its deviation from the uniform-local-base count is at most

`sum_(t!=0) |hat(f_y)(t)| min(1,2^35 B_t)`.

All summands are exact rationals. Exhausting every locally reached `y` and
taking the largest count-plus-error gives the table. Locally absent `y` are
impossible for every base. A specified full-state difference implies one
specified projected difference, proving the full-state bound. Multiplication
by the **proved** `Pr(H)=2^-35` gives the joint-event bounds.

## Finite certificate and implementation audit

The slice producer computes all 4,095 nonzero masks for chain 2 at `k=4` and
all 32,767 for chain 1 at `k=5`. The event calculation then uses only masks
actually present in the differential-indicator spectra: 21 and 87 for the
first two selected cases, and 751 for the third. The three selected local
input differences `(da,dc,dh)` are `(0,4,0)`, `(0,6,0)`, and `(31,0,1)`.
Exact uniform-local maxima are respectively `1024/4096`, `512/4096`, and
`2048/32768`.

The audit separately reconstructs 1,272 prefix columns using a pure-Python
prefix and compares each against C; reconstructs the XRBD transpose from
2,048 original-C basis inputs instead of the producer's adjoint algorithm;
uses opposite-pivot elimination and direct byte character sums; reproduces
all used-mask bounds and event spectra with a second transform; reconstructs
the three codimension-35 events directly from source DDT fibers; and replays
48 saved actual message pairs through the original complete-round C.
The report covers six chain/case combinations, including uninformative ones,
and checks 1,458 used-mask occurrences and 32 direct 16-variable local Walsh
transforms. This is implementation independence, not external verification.

Bit numbering is LSB-first within little-endian lanes. The selected complete
round projection is lane 28 bits 11–14 followed by lane 10 bits 11–14 for
chain 2; lane 7 bits 18–22 followed by lane 21 bits 30–34 for chain 1.
Both 159-byte messages are preserved for every C replay witness.

## What failed before the event-specific bound

Bounding total variation of the **whole** Pressure input slice was too loose:
the chain-14 four-bit pilot gave a raw bound above one; chain 1 at five bits
also gave a raw bound above one. Its exceptional large Fourier bounds are
unused by the relevant differential-indicator spectra. Bounding the event
itself avoids them. Chain 2's four-bit slice also admits a useful whole-slice
bound, but the event-specific bound is sharper. These failed inequalities
are preserved and are not evidence of either weakness or security.

## Reproduction

Use fresh output names; each producer refuses to overwrite an existing report.
Run one command at a time. No AA/AB campaign files are written.

```bash
cd /home/user/sol
nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_conditioned_pressure_differential.py --bits 4 --chain 2 --output results/krakken_conditioned_pressure_ch02_k4_replay.json
nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_conditioned_pressure_differential.py --bits 5 --chain 1 --output results/krakken_conditioned_pressure_ch01_k5_replay.json
```

The event producer records root-relative paths; keep its inputs inside the
research root.

```bash
nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_conditioned_pressure_events.py --reports results/krakken_conditioned_pressure_ch02_k4_replay.json results/krakken_conditioned_pressure_ch01_k5_replay.json --output results/krakken_conditioned_pressure_events_replay.json
OPENBLAS_NUM_THREADS=1 nice -n 10 /home/user/venv/krakken/bin/python -u scripts/krakken_conditioned_pressure_audit.py --report results/krakken_conditioned_pressure_events_replay.json --output results/krakken_conditioned_pressure_audit_replay.json
```

Artifacts: [slice producer](../scripts/krakken_conditioned_pressure_differential.py),
[event producer](../scripts/krakken_conditioned_pressure_events.py),
[separate audit](../scripts/krakken_conditioned_pressure_audit.py),
[chain-2 slice](../results/krakken_conditioned_pressure_ch02_k4.json),
[chain-1 slice](../results/krakken_conditioned_pressure_ch01_k5.json),
[event certificate](../results/krakken_conditioned_pressure_events.json),
[audit report](../results/krakken_conditioned_pressure_audit.json),
[unsuccessful chain-14 pilot](../results/krakken_conditioned_pressure_ch14_k4.json).

The next open step is a useful unconditional bound for these selected message
differences, or a conditioned multi-chain bound preserving their joint base
dependencies. The present result does not multiply independent-chain probabilities.

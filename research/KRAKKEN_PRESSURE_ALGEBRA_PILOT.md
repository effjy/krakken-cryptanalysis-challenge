# Exact low-bit Pressure algebra and bounded `[1,2]` pilot

This pass uses the current XRBD-enabled scalar `krakken.c/h` pinned by
SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
and `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.
It did not modify the AA/AB/BA scan files, scalar source, or frozen review
bundle. The local Pressure classifications below are exact finite results.
The site benchmark is a selected, resource-bounded solver-engineering pilot.

## Exact low-three-bit relation

For one Pressure chain and `k=3`, its output low bits depend exactly on
three independent three-bit slices `a,c,h=(c>>17)[0:3]`:

`A=a+(c XOR h) mod 8`, `C=c+A mod 8`.

There are `2^15=32,768` possible profiles `(da,dc,dh,dA,dC)` of five
three-bit XOR differences. Exhausting all `512` local bases and `512`
input differences gives **4,376 feasible profiles**. The exact two-bit
prefix gate admits **5,888** lifted profiles, so the third bit removes
1,512 more profiles locally.

For each degree `d`, take the **complete space** of Boolean polynomials
of degree at most `d` that vanish on every feasible profile. Its common
zero set is computed by GF(2) row-space membership on the complete
monomial-evaluation matrix, then tested against all 32,768 profiles:

| Degree ≤ | Monomials | Evaluation rank | Common zeros | False positives |
|---:|---:|---:|---:|---:|
| 1 | 16 | 14 | 8,192 | 3,816 |
| 2 | 121 | 92 | 8,192 | 3,816 |
| 3 | 576 | 372 | 4,504 | 128 |
| 4 | 1,941 | 1,031 | 4,504 | 128 |
| 5 | 4,944 | 2,079 | **4,376** | **0** |

Thus no degree-two polynomial improves the two linear LSB equations.
All cubic consequences eliminate 1,384 of the 1,512 profiles that
pass the exact two-bit prefix but fail the three-bit relation. Quartic
consequences remove none of the remaining 128; degree-five equations
make the relation exact.

The fifth-degree step has a smaller explicit certificate than the
complete polynomial space suggests. The
[single-quintic producer](../scripts/krakken_pressure_low3_single_quintic.py)
finds an 82-monomial ANF that is zero on every feasible profile and one
on every one of the 128 cubic false positives. Thus **the full set of
cubic consequences plus this one quintic equation is exact**. The
[certificate](../results/krakken_pressure_low3_single_quintic.json)
lists all monomial masks. A separate
[direct audit](../scripts/krakken_pressure_low3_single_quintic_audit.py)
re-enumerates all 262,144 local transitions and evaluates the saved ANF
over all 32,768 profile values; its
[report](../results/krakken_pressure_low3_single_quintic_audit.json)
passes. The 82-term count is a construction, not a minimum-size claim.

The 128 residual profiles form **one affine seven-dimensional flat**
in the 15-bit profile space. Therefore the exact relation also has a
compact *set-theoretic* form: satisfy every vanishing cubic and avoid
that one flat. The [independent opposite-pivot audit](../scripts/krakken_pressure_low3_affine_exception_audit.py)
re-enumerates all 262,144 base/difference evaluations in a different
loop order, reproduces the degree-three and degree-five closures, and
saves the flat's eight affine defining equations and a seven-vector
direction basis in its [report](../results/krakken_pressure_low3_affine_exception_audit.json).
The [producer](../scripts/krakken_pressure_low3_polynomial.py) and
[complete degree-five certificate](../results/krakken_pressure_low3_polynomial_d5.json)
pin the source and list the row-space bases. The full-width source
correspondence of these low bits is inherited from the earlier
original-C Pressure checks and the 512 full-word low-six-bit checks
in [RESULTS4](../RESULTS4.md); this pass did not independently replay
every local profile through C.

This result concerns only a **single local chain's low-three-bit
existential relation**. It does not enforce upper carries, common
base-state reachability, Chi derivative constraints, or a complete
two-round trail. A polynomial closure is a sound relaxation: UNSAT
after composing it with site equations excludes a real trail; SAT
need not represent one.

## Bounded factored-cubic site benchmark

The [pilot script](../scripts/krakken_12_cubic_branch_pilot.py)
substitutes source-derived endpoint columns into the exact factored
two-bit gate of [PRESS-DIFF-001](KRAKKEN_SECURITY_THEOREMS.md#press-diff-001).
It first eliminates the 32 bit-zero equations, quotients invisible
difference directions, retains the existing exact hidden-fiber
nonzero-byte counter, then branches on affine factors using GF(2)
equations. It has explicit node/profile caps and returns `limit`
rather than calling a capped search UNSAT. It does not invoke SCIP
or Z3, and its process was run at low priority.

Two selected sets were compared against the existing exact carry-table
enumerator for the **same two-bit relaxation**:

| Set | Status agreement | Branch nodes | Branch profiles | Table profiles | Branch core time | Table core time |
|---|---|---:|---:|---:|---:|---:|
| Ten UNSAT + ten SAT AA/AB sites selected for both outcomes | 20/20 | 244 | 20 | 53,258 | 0.029 s | 0.575 s |
| Thirty saved AA/AB/BA three-bit-survivor sites | 30/30 | 310 | 39 | 7,776 | 0.033 s | 0.105 s |

These are per-case **core timings** after the shared source basis is
loaded, not whole-campaign wall times; selection favors manageable
visible dimensions. The scripts and exact case lists are saved in
[20-case report](../results/krakken_12_cubic_branch_pilot_20.json)
and [30-case report](../results/krakken_12_cubic_branch_pilot_30.json).
The branch and table implementations share the source basis and
hidden-fiber routine; their agreement checks the different local
decision procedures, not an independent original-C replay of all
site models. No new `[1,2]` site was excluded: each local result
was already available from the carry-table formulation.

## Three-bit composition and one complete AB position

The [selected-site pilot](../scripts/krakken_12_low3_cubic_site_pilot.py)
compares three nested necessary conditions on source-derived site kernels:
the exact two-bit local gate, every degree-at-most-three consequence of
the exact three-bit gate, and the exact three-bit local table. It keeps
the same hidden-fiber nonzero-byte test as the earlier site enumerator.
Of 35 deliberately selected AA/AB/BA sites in the
[report](../results/krakken_12_low3_cubic_site_35.json), 27 had at most
16 visible dimensions and were fully enumerated (534,528 visible
assignments total); eight were skipped at that cap. All 27 complete
sites gave identical cubic and exact three-bit counts, both before and
after the nonzero-byte condition. In 15 of the 27, the two-bit model
had an admissible nonzero-byte profile while the cubic model had none.
Those exclusions were already present in the existing exact three-bit
model; this comparison supplies an algebraic formulation, not a new
`[1,2]` theorem.

The [exception-intersection script](../scripts/krakken_12_low3_exception_intersection.py)
explains most selected agreements using only GF(2) elimination: 34 of
35 selected site spaces cannot meet the 128-profile affine exception in
any Pressure chain. The sole exception is AA position 231, site 5794,
whose projected difference space intersects the exceptional flat in
chains 9, 11, and 13. Its fully enumerated cubic and exact site counts
still agree; intersection is necessary but not sufficient for a false
site candidate. The [selected-site audit](../results/krakken_12_low3_exception_intersection_35.json)
pins the basis, source, and affine-flat certificate.

A further [complete-position scan](../scripts/krakken_12_low3_exception_position.py)
checked all 8,128 endpoint sites at **AB start position 007**. For
7,620 sites, no chain's bit-zero-constrained projected difference space
intersects the exceptional flat; hence cubic and exact three-bit local
gates coincide throughout those site spaces. The other 508 sites have
at least one possible intersection: 436 sites in one chain and 72 in
two chains. They are **not** asserted SAT in the exact site model.
The [position report](../results/krakken_12_low3_exception_ab_pos007.json)
records every intersecting site. A separate
[independent implementation audit](../scripts/krakken_12_low3_exception_position_audit.py)
used direct 40-equation column-span elimination, without constructing
the producer's bit-zero kernel or visible quotient, and reproduced all
8,128 classifications in its [PASS report](../results/krakken_12_low3_exception_ab_pos007_audit.json).
This is a complete finite classification of that **one position's
linear exception-intersection question**. It does not close AB globally,
prove full-width Pressure feasibility, or change the ongoing campaign.

## Consequence for the research program

The two-bit factored form can make some **existing** exclusions
cheaper, but it cannot strengthen the two-bit relaxation. The
three-bit cubic closure prunes more, and its only local false positives
lie on one affine flat. The selected-site composition and complete AB
position-007 intersection scan show where that algebraic representation
can exactly replace the local three-bit table. This does not yet
establish a whole-campaign speedup: the 508 possible intersections,
larger visible quotients, and full-width carry refinements remain.
For stronger multiround bounds, the larger goal remains a sound
weighted transition graph carrying more than plain S-box counts
across Pressure and the next linear prefix.

## Full-word extension and endpoint-screen barrier (RESULTS6)

[PRESS-DIFF-003](KRAKKEN_SECURITY_THEOREMS.md#press-diff-003) derives
126 necessary factored cubic equations plus two LSB equations per chain,
with an affine-graph derivative refinement. Both use all 64 bits and the
actual shifted-word overlap. They remain incomplete gates, with explicit
reduced-model false positives.
[DIFF-SCREEN-001](KRAKKEN_SECURITY_THEOREMS.md#diff-screen-001) proves
surjectivity of certified sparse endpoint spaces onto low-bit output profiles.
For q=3, 13 second-call-only cells suffice. The 48 synthetic fixture-chain
profiles accepted by the projected screen are rejected by the full-word gates.
This diagnoses information loss and provides a sound refinement route; it
establishes no actual A2 minimum. See [RESULTS6](../RESULTS6.md) and the
[fresh replay](../results/krakken_results6_promotion_replay.json). No ongoing
AA/AB/BA campaign model or result was changed.

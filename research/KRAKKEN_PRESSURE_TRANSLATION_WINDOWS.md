# Consecutive deterministic Pressure transitions: a solver-free window theorem

2026-10-06. Permanent ID: **DIFF-WINDOW-001**. Source pins are those of
[PRESS-TRANS-001](KRAKKEN_SECURITY_THEOREMS.md#press-trans-001).
This is an unrestricted differential-class exclusion, with conditional activity
consequences for actual valid-message pairs. No message reachability is assumed.

## Statement

Let U be the complete 16-dimensional deterministic Pressure translation space:
a direction toggles selected first-word top bits of the sixteen chains, with
all other bits zero. For any distinct pair of states, at any two adjacent
rounds of the current eight-round scalar permutation,

`Delta_PressureInput_r in U minus {0} => Delta_PressureInput_(r+1) not in U`.

This holds for **every base**, not merely for an average base or a universal
relation. It does not mean the actual difference vanishes. It excludes two
consecutive probability-one Pressure transitions of this classified type.
No SCIP, SAT/SMT solver, carry approximation or toy reduced-width model is used.

## Exact finite proof

Let `B=XRBD`, `L=Theta→MDS→Rho→Pi`, `Q=Inkcloud`, and let Lambda be
Pressure's deterministic output-difference map on U, including odd rotations.
For `d in U`, the fixed next pre-Chi difference is `v(d)=L Q Lambda d`.
Constants cancel in this difference; the wiring is identical at every boundary.
If the next Pressure difference were `e in U`, its required post-Chi difference
would be `B^-1 e`.

Consider any serial-Chi cell whose two input-byte differences in v(d) are zero.
Both output-byte differences are necessarily zero for every local base. Since
`B^-1 e` is linear in the sixteen direction coefficients of e, each such byte
bit supplies a homogeneous linear equation on those coefficients.

For **each of the 65,535 nonzero d**, the equations from inactive cells have
rank **16**. Thus e must be zero. But the intervening maps are bijective, so
an initially nonzero difference cannot become zero. This proves the exclusion.
The proof needs only inactive-cell constraints; the producer's additional
first-call constraints and DDT machinery are unnecessary for the final result.

### Certificate and independent implementation audit

The [producer](../scripts/krakken_pressure_translation_window.py) records
all direction ranks, both sets of sixteen transported generators, source pins
and a [scan report](../results/pressure_translation_windows_20261006/scan.json).
It checks inverse-XRBD and transported generators against original C (32 checks).
No DDT candidate survives the full-rank linear gate; no enumeration cap is hit.

The [audit](../scripts/krakken_pressure_translation_window_audit.py) imports
neither the producer nor its NumPy layer implementation. It reconstructs
inverse XRBD with scalar word operations, obtains the next generators from
original C, extracts constraints by integer state-bit positions, and uses
least-significant pivots instead of the producer's most-significant pivots.
All 65,535 inactive-cell-only ranks are 16. In its fixed cell order, full rank
requires three to eight inactive cells. Its [report](../results/pressure_translation_windows_20261006/audit.json)
also saves 128 original-C pair replays, each with the actual next Pressure
difference outside U. These replay examples validate implementation; the
complete rank argument is the exclusion proof. No external reproduction is
recorded, and no proof-assistant formalization is claimed.

## Composing short-window activity inequalities

Let `I` be the round indices whose actual Pressure input difference lies in
nonzero U. The theorem makes I nonadjacent. Existing PRESS-TRANS-001 gives
`A_i>=48` for `i in I`, and `A_i+A_(i+1)>=135`, `A_(i+1)>=30` when
the next round exists. Existing DIFF-PERM-002 / DIFF-MULTI-001 give
`A_i>=1` and no adjacent `[1,1]`. For H first-block pairs, also `A_1>=5`.
These are inequalities for actual pairs, without independence assumptions.

The resulting conservative floors are:

| Scope / condition | Three rounds | Eight rounds |
|---|---:|---:|
| P, no condition on membership in U | ≥4 | ≥12 |
| H first block, no condition on membership in U | ≥8 | ≥15 |
| P, some U occurrence anywhere in the interval | ≥51 | ≥58 |
| H, some U occurrence anywhere in the interval | ≥54 | ≥62 |
| P, some U occurrence before the final round | ≥136 | ≥143 |
| H, some U occurrence before the final round | ≥136 | ≥144 |

Three-round P bounds apply to any adjacent three-round window. H bounds
require that the window starts at the first message absorb; do not impose
`A_1>=5` on arbitrary later windows. Eight-round rows concern the full eight
source rounds. These are **bounds derived from inequalities**, not sharp
minima of actual Krakken trails, nor evidence that H realizes any U direction.
The first two rows are inherited conservative floors, not strengthened global
results. The unrestricted case with no U occurrence remains open beyond them.

For example, one U occurrence before round eight pays 135 on its two-round
window. The uncovered left/right segments have lengths adding to six. A segment
of length n with no adjacent `[1,1]` costs at least `n+floor(n/2)`. The minimum
uncovered cost is eight, so the total is at least 143. The first-block condition
raises the minimum over positions to 144. A U occurrence only in round eight
pays 48 there, plus at least ten on the first seven rounds, giving 58 for P.

For arbitrary nonadjacent I, its two-round windows are disjoint. If
`k=|I intersect {1,...,7}|` and `epsilon=1` when `8 in I`, a simpler
composable floor is `sum A_i>=8+133k+47epsilon`. The report uses all inherited
inequalities and can be stronger than this simpler expression.

The [composition script](../scripts/krakken_pressure_translation_activity_composition.py)
uses an exact finite dynamic program over the 256 possible call counts per
round. For each of five three-round and 55 eight-round nonadjacent patterns,
it enforces every inequality above. A second implementation explicitly checks
all 256×256 adjacent activity pairs and reproduces all 120 domain/pattern
results. See [composition.json](../results/pressure_translation_windows_20261006/composition.json).
This DP optimizes a small inequality system, not the full permutation.

## Reproduction

Run one job at a time, at low priority, with fresh output filenames:

```bash
nice -n 10 /home/user/venv/krakken/bin/python -u \
  /home/user/sol/scripts/krakken_pressure_translation_window.py \
  --output /home/user/sol/results/pressure_translation_windows_20261006/scan_new.json

nice -n 10 /home/user/venv/krakken/bin/python -u \
  /home/user/sol/scripts/krakken_pressure_translation_window_audit.py \
  --scan /home/user/sol/results/pressure_translation_windows_20261006/scan_new.json \
  --output /home/user/sol/results/pressure_translation_windows_20261006/audit_new.json
```

The producer's candidate cap would mark a residual case incomplete rather
than silently exclude it; this run has zero residual candidates and zero
capped directions. The composition script writes its separate report.

## What this pass establishes

A complete dangerous internal class is closed across an adjacent boundary:
Pressure's globally deterministic XOR transitions cannot chain consecutively.
It supplies a sound case-split rule and conditional three-/eight-round floors
without a large optimizer. General differences, nonunit-probability Pressure
transitions, arbitrary three-round low-total trails and full differential-hull
probabilities remain open. No call-count floor is converted into security bits.
The AA/AB/BA campaign, pinned source and frozen bundle were left unchanged.

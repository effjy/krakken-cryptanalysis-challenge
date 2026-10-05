# Effective-coordinate pilot for remaining `[1,2]` site models

**Status: solver-engineering result, not a new Krakken theorem.** This
2026-10-04 pilot uses the current pinned `krakken.c/h` and the existing
source-derived AA/AB/BA basis files. It did not alter the running scan,
the C/header, or the frozen review bundle. The exact model here is the
existing **low-`k` necessary-condition relaxation**; it omits upper
Pressure bits and Chi2 DDT compatibility. `UNSAT` in that model excludes
a real `[1,2]` trail at the named site. `SAT` remains only a relaxed
candidate.

## What is already reduced

The current scan does not send a 2,048-bit two-round permutation to
Z3 or SCIP. It first eliminates XRBD and the inter-round linear
layers using original-C basis columns. The symbolic differences are
one start byte plus target-cell bytes: **40 bits for AA**, **32 bits
for AB/BA**. The existing kernel solver eliminates 32 exact Pressure
bit-zero equations by GF(2) and retains only three low-`k` base slices
`(a,c,c>>17)` per chain. At `k=3`, that is at most 144 base-slice bits
across 16 independent chains. These earlier reductions explain why a
generic “apply LIN-RATE-004's effective coordinates” suggestion alone
does not automatically revolutionize the model.

## Further exact reductions tested

The [diagnostic and finite enumerator](../scripts/krakken_12_effective_cone.py)
first projects the bit-zero kernel onto the low-`k` Pressure-difference
profiles actually seen by the target. It splits kernel directions
into visible profile directions and a hidden fiber. Required nonzero
byte constraints on the hidden fiber are eliminated exactly by
GF(2) rank and inclusion-exclusion; they are **not** discarded.

For each chain, the observed difference equations are classified as
both additions active, first addition only, second only, or no
constraint. A first-only chain needs base coordinates `(a,c XOR h)`;
a second-only chain needs `(c,A)`; a both-additions chain needs three
base coordinates. For `k` output bits, the top base bit of each
coordinate cancels from the XOR difference, so only its low `k-1`
bits need enumeration. The script constructs exact local carry tables
and checks each visible profile, with independent chain bases exactly
as in the existing relaxed model. No SCIP or Z3 call is made by this
enumerator, and **no timeout is built into it**.

The [independent pilot audit](../scripts/krakken_12_effective_cone_audit.py)
checked 48 local carry tables against full-base enumeration, 224
hidden-fiber inclusion-exclusion counts against direct hidden-base
enumeration, and seven named cases against the existing low-`k` Z3
solver. All statuses agreed in its [report](../results/krakken_12_effective_cone_audit_20261004_v2.json).

## Measured pilot

| Case | Width | Difference bits after bit-zero | Visible / hidden | Active chains | Base-slice bits, old → effective | Exact result |
|---|---:|---:|---:|---:|---:|---|
| AA pos 0, site 847 | 3 | 26 | 18 / 8 | 12 | 144 → 68 | relaxed SAT |
| AA pos 0, site 847 | 4 | 26 | 18 / 8 | 12 | 192 → 102 | UNSAT; `2^18` profiles in 2.8 s |
| AA pos 7, site 1234 | 3 | 11 | 11 / 0 | 16 | 144 → 96 | UNSAT |
| AB pos 7, site 6596 | 3 | 12 | 12 / 0 | 10 | 144 → 56 | relaxed SAT |
| AB pos 7, site 6596 | 4 | 12 | 12 / 0 | 10 | 192 → 84 | UNSAT; `2^12` profiles in 0.1 s |
| BA pos 7, site 6596 | 3 | 13 | 5 / 8 | 10 | 144 → 56 | UNSAT |

The AA four-bit result reproduces its already saved refinement, rather
than adding a new exclusion. It shows why the quotient matters: of all
`2^18` distinct projected profiles, **one** passed the local carry
tables, but its hidden fiber could not satisfy every required nonzero
byte. Dropping those hidden constraints would have reported a false
relaxed survivor. The [case reports](../results/krakken_12_effective_cone_aa0_k4_20261004.json)
record the source pins and exact counts.

A deterministic, read-only [sample](../scripts/krakken_12_effective_cone_sample.py)
selected 50 pre-refinement three-bit relaxed survivors from the
completed AA files and 50 from the then-completed AB files; BA used
those same AB sites. Median free difference-kernel dimensions were
**23 / 19 / 19** for AA/AB/BA, whereas median visible-profile ranks
were **16 / 15 / 12**. Median effective base-slice counts were **58
bits** in each mode, compared with 144 bits in the old uniform
16-chain allocation. The [saved sample](../results/krakken_12_effective_cone_sample_20261004.json)
contains every site and source-report digest. This is a targeted
sample of relaxed survivors, not a whole-class runtime benchmark.

## Implication and next use

This approach **can help the existing AA/AB/BA round-two feasibility
campaign**, especially when the visible rank is small enough to
enumerate. It can replace the low-bit solver for those named sites
and produce the same sound UNSAT conclusion, while preserving all
hidden nonzero-byte constraints. When visible rank is too large,
the same quotient and local carry tables could feed a smaller SAT/BDD
model, but no general speedup has been measured or proved.

It does **not** yet solve the full-width two-round SCIP problem or
establish global `[1,2]` impossibility. Full-width Pressure has
cross-bit carries and the `>>17`/`<<31` dependencies; exact Chi2
DDT/base compatibility and all remaining AA/AB/BA sites still need
their own treatment. A low-`k` SAT is not a real trail.

Example isolated replay, writing a new output file:

```bash
/home/user/venv/krakken/bin/python /home/user/sol/scripts/krakken_12_effective_cone.py \
  --case aa:0:847 --prefix-bits 4 --enumerate-limit-bits 18 \
  --output /home/user/sol/results/my_effective_cone_replay.json
```

# Coordinated multi-cell serial-Chi quartets

Source-pinned pass, 2026-09-30. Current XRBD-enabled scalar source only;
no archived boomerang conclusion is used. Domain: **unrestricted permutation**.
No message pair, rate restriction, or later-absorb reachability is established.

## Exact construction and complete-round-one property

Let `X` be XRBD and let `E` contain the first output byte of each
serial-Chi cell; let `O` contain the second output byte. Each has
dimension 1024 over GF(2). Pressure has 16 disjoint 128-bit chains,
indexed `2c+h` on lanes `(4c+h,4c+h+2)`.

Partition these chains into eight units:

`{0,2}, {1,3}, {4,6}, {5,7}, {8,10}, {9,11}, {12,14}, {13,15}`.

For each unit `G`, both spaces

`K_E(G) = {U in E : support_chains(XU) is contained in G}`

`K_O(G) = {V in O : support_chains(XV) is contained in G}`

have **exact dimension 128**. The 16 outside-support projection
matrices have 1024 columns and rank 896. Original-C basis evaluations
and two elimination implementations with opposite pivot orders agree.

Choose distinct units `G,H`, nonzero `U in K_E(G)`, nonzero
`V in K_O(H)`, and any common post-Chi background `B`. Set the
ordered post-Chi quartet to

`Q = (B, B XOR V, B XOR U, B XOR U XOR V)`.

There are 56 ordered choices of distinct units; all permitted
directions and backgrounds are covered by the following proof,
not just the sampled instances.

**Serial-Chi matching.** For one cell with output `(u,v)`, inverse Chi is
`b=I(v) XOR u`, `a=I(u) XOR b`, with `I=S^-1`. The inverse is a sum
of separate functions of `u` and `v`. Hence inverse images of the
output rectangle also XOR to zero, and the `V` side has the same
diagonal input difference `(d,d)` on both `U` sides, where
`d=I(v) XOR I(v XOR epsilon)`. At cells where both directions are
nonzero this is the known perfect local serial-Chi boomerang family;
cells with one zero direction are degenerate local rectangles. The
whole quartet has four distinct states because `U,V` are nonzero in
disjoint output-coordinate spaces. The inverse linear prefix keeps
their XOR zero and yields actual distinct permutation inputs.

**Pressure matching.** After XRBD, the two directions occupy disjoint
Pressure-chain sets. Within each chain at most one direction varies.
Its four inputs therefore occur in equal pairs, so its four outputs
XOR to zero regardless of carries or background. No independence or
probability multiplication is used. The statement holds for every
common background, including all chosen nonzero backgrounds.

**Complete boundary.** Constants cancel in a four-state XOR, and
InkCloud is linear. Therefore both the complete-round input and
complete-round output XOR are exactly zero for the whole constructed
family. This is a **complete-round-one unrestricted four-state zero-sum
construction**, and an attack-side result, indexed as `BOOM-MULTI-001`.
The next round's linear prefix also preserves the rectangle.

For a fixed saved quartet, a four-query test distinguishes this
one-round property from a uniformly random 2048-bit permutation:
given three distinct outputs, their XOR is distinct from all three;
the fourth output hits it with probability `1/(2^2048-3)`. The
constructed quartet hits it deterministically in one-round Krakken.
The input construction is independent of the oracle under test.
This is a reduced-round unrestricted structural test, not an attack
on the eight-round hash. Its directions depend on selected backgrounds;
it does **not** establish a complete-round BCT entry of probability one
for a single fixed input/output difference pair across all bases.

## Systematic finite continuation experiment — not a universal exclusion

The producer used all 56 ordered unit pairs with 24 sampled direction/
background choices each: **1,344 cases**. Directions were individual
kernel basis vectors, sums of four basis vectors, or random combinations.
Common backgrounds were chosen at the Pressure input: zero, all ones,
alternating words, or random full state, then inverted through XRBD.

- All 1,344 local inbound quartets and Pressure rectangles replayed
  in original C and preserved the complete-round-one rectangle.
- Active Chi1 cells ranged from **12 to 128**. **1,047** cases had at
  least two cells with both local directions nonzero; 294 had none
  and three had only one. The latter are not counted as multiple
  nontrivial local boomerangs even though their global quartets are distinct.
- **Zero** tested quartets preserved the full XOR rectangle after
  Chi2, and **zero** after complete round two.
- The smallest sampled post-Chi2 XOR defect had **903 nonzero bits**.
  The minimum after complete round two, across the same samples, was
  **950 bits**. These are observed minima, not universal lower bounds.

The saved best-at-Chi2 quartet has 38 active Chi1 cells, five of which
have both directions nonzero. It uses units `{8,10}` and `{0,2}`
and zero Pressure background. Its complete-round-two defect is 1070
bits; it is not the sample attaining the separate 950-bit minimum.
Its four actual round-start states and every relevant checkpoint are
retained in the report. Both complete round counts were independently
replayed using the original C entry point.

The separate audit additionally exhausts all 65,536 local Chi bases
for the saved quartet's Chi2 cell `(row,pair,byte)=(0,0,0)`, finding

`N_Chi(alpha=1190, beta=1536) = 0`.

For this fixed difference pair, no changed Chi2 local base can repair
the rectangle. Changing an earlier background may change the pair,
so this is an exact obstruction for the saved pattern, not for the
whole coordinated family. The audit does not independently replay
all 1,344 sampled cases. A nonzero defect at Chi2 also does not prove
that no later nonlinear layer could restore another useful relation;
complete round two was tested separately.

## Artifacts and reproduction

- [Producer](../scripts/krakken_multicell_boomerang.py)
- [Sample report and saved quartet](../results/krakken_multicell_boomerang_sample.json)
- [Separate rank/witness audit](../scripts/krakken_multicell_boomerang_audit.py)
- [Audit report](../results/krakken_multicell_boomerang_audit.json)

```bash
nice -n 19 python3 krakken_multicell_boomerang.py \
  --samples-per-pair 24 --seed 20260930 \
  --output multicell_boomerang_repeat.json
nice -n 19 python3 krakken_multicell_boomerang_audit.py \
  --report multicell_boomerang_repeat.json \
  --output multicell_boomerang_repeat_audit.json
```

One process at a time, no solver and no parallel workers. Neither command
modifies the AA campaign or pinned C/header. Increase samples for broader
heuristic coverage; it does not turn the Chi2 search into an exhaustive proof.

## Open next step

Finite verification follow-up: [all reached-cell counts and certificates](../results/krakken_multicell_20260930/README.md).
All 1,344 saved constructions have a zero-count Chi2 cell; none has positive
counts in every cell. The follow-up counts all 172,032 cell occurrences
(172,003 distinct unordered pair keys), replays every quartet through Chi2,
and independently checks the counts. Every selected obstruction also has
a direct 65,536-base count. This certifies these **fixed reached patterns**;
it does not exhaust the direction spaces or earlier backgrounds.

A separate [first-block rate gate](../results/krakken_multicell_20261002/README.md)
proves that **896** of the same 1,344 saved U/V direction pairs cannot be
embedded by valid 159-byte first-block messages for any background. The
other **448** pass this linear necessary test but are not known reachable.

Attempt directions/backgrounds specifically chosen for compatible Chi2
rectangle pairs. The full 128-dimensional spaces and arbitrary backgrounds
have not been exhausted. Shared-chain constructions with jointly solved carries
are also open. Any two-round survivor should be saved and investigated with
its construction cost and reachability constraints, rather than discarded.
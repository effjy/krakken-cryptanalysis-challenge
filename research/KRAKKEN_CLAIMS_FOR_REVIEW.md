# Krakken: draft claims for external cryptanalytic review

Research navigation: [index](KRAKKEN_RESEARCH_INDEX.md). This working
document may be newer than the frozen review bundle; packaging happens
only on request.

These are narrowly stated, reproducible claims about the current
`krakken.c`/`krakken.h` source (combined SHA-256
`6b3d5a5d416e2923379e0b38305babb4cb0471c1833d7d3a6c4e8356005d8893`).
Unless a section states a different domain, the input domain is every
159-byte message, absorbed as one block with the fixed `0x86` pad byte
and zero initial capacity, with XRBD enabled. Several differential,
differential-linear, rotational, and four-state zero-sum claims use
unrestricted 2048-bit states as specified in their sections; the
rotational claim also analyzes a variant without round constants.
`F_r(m)` denotes the full 2048-bit state after `r` complete rounds.

**Bit conventions.** A message is bytes `m[0]..m[158]`; bit `8j+b`
means bit `b` (least significant bit is `b=0`) of byte `m[j]`.
The initial 256-byte state has those message bytes at offsets `0..158`,
the fixed padding byte `0x86` at offset `159`, and zero bytes at
offsets `160..255`. Lane `i` is the little-endian 64-bit word made from
state bytes `8i..8i+7`, and state-mask bit `64i+8k+b` means bit `b`
of lane `i`'s byte `k`. All dot products and sums of mask bits are
modulo two. Chi component `(i,j,k)` takes pre-Chi byte `k` of lane `i`
and byte `(k+4) mod 8` of lane `j`; its two post-Chi bytes occupy those
same positions. For 159-byte one-block messages, the 32-byte digest is
the first 32 state bytes after round 8. These conventions describe the
little-endian C execution used by the certificates.

| Status | Claim | Scope |
|---|---|---|
| **PROVED — GLOBAL** | No perfect affine message-to-state relation | Every message mask, every state mask, rounds 1–8 |
| **PROVED — COMPLETE DEFINED CLASS** | Exact maximum `2^(-3t)` | Every message mask and every Chi1 mask active on exactly `t=1,2,3` components |
| **PROVED — COMPLETE FOUR-CELL CLASS** | Exact maximum `2^-12` | Every message mask and every Chi1 output mask active on exactly four components; all 10,668,000 input projections rank 64 |
| **PROVED — COMPLETE DEFINED FAMILY** | Maximal boomerang uniformity `65,536` for the 16-bit serial-Chi component | Every nonzero byte pair `beta,gamma` in the 65,025-entry family `((beta,beta),(gamma,0))`; component-level, not a full-round claim |
| **PROVED — COMPLETE LOCAL CLASS** | Exactly 65,025 nontrivial perfect serial-Chi boomerang pairs; sharp nonperfect probability at most `3/128` | Every nontrivial 16-bit local input/output difference pair; unrestricted complete-Chi product corollary |
| **PROVED — COMPLETE DEFINED CLASSES** | 4,784 Pressure-surviving local quartets, zero crossing Chi2 | One fixed site, four `(d,gamma)` pairs, zero other post-Chi1 bytes, all 262,144 local `(u,v)` bases; unrestricted permutation |
| **PROVED — GLOBAL FIRST-BLOCK CLASS** | Exact `min A1 = 5` for valid 159-byte messages | Every nonzero first-absorb message difference and every base; one valid pair attains `A1=5` |
| **PROVED — GLOBAL FIRST-FULL-BLOCK CLASS** | Exact `min A = 5` at the first unpadded 160-byte absorb | Every nonzero full-block message difference and every base; common-prefix later full-block floor `A≥5` |
| **PROVED — COMPLETE SIX-DIFFERENCE CLASS** | Exact first-Chi activity law and sharp `2^-38` maximum single-output probability | Each of the six rate-reachable four-cell input-difference lines, over every valid 159-byte base message |
| **PROVED — GLOBAL FIRST-CHI CHECKPOINT** | Any prescribed post-Chi1 or post-XRBD1 full-state difference has probability at most `2^-24` by DIFF-RATE-005; strengthened to `2^-30` by CHI-RATE-001 | Every fixed nonzero valid 159-byte message difference; uniform message base; sharpness of the stronger bound open |
| **PROVED — COMPLETE CONDITIONAL CHI CLASS** | All 128 first-call bytes plus any five second-call bytes are jointly uniform; exact truncated-differential product; sharp first-only mask maximum `2^-3t` for `t≤128` | Uniform 159-/160-byte rate message, arbitrary fixed affine offset; Chi1/XRBD1 checkpoint only; at most five masked second-output bytes |
| **PROVED — COMPLETE FIXED-DIFFERENCE ACTIVITY CLASS** | Exact affine-syndrome law, all activity counts and minimum bases; conditioned specified eight-bit R1 correlation ≤`2^-211` when nonempty `A1≤5` | Every fixed full-state difference and fixed offset, uniform 159-/160-byte base; the R1 bound is for the base-state nondigest projection, not output differences |
| **PROVED — ACTIVE-FIRST-CALL CHI CLASS** | Every prescribed local transition fiber is affine; consistent hash-level event has exact probability `2^-rank` | Local components with active first S-box call; whole first-Chi transition if all nonzero components meet that condition |
| **PROVED — COMPLETE LOCAL DIFFERENTIAL CLASS** | Sharp maximum local DP is `2^-6`, `2^-7`, or `2^-12`, with 510/32,130/32,895 input differences and a unique maximizing output for each | Every nonzero 16-bit serial-Chi input difference, uniform unrestricted local base; full-Chi product only under uniform unrestricted state |
| **PROVED — COMPLETE PERFECT LOCAL DIFFERENTIAL-LINEAR CLASS** | Exactly 65,025 nontrivial perfect pairs; every other pair has `|corr|≤71/512` (not claimed sharp) | Every nonzero local serial-Chi input difference and nonzero local output mask, uniform unrestricted base |
| **PROVED — CONDITIONAL HASH-REACHABLE CLASS** | `A1=5` forces `A2>=3` for each of three fixed valid message differences | Every valid 159-byte base message attaining five Chi1 calls for one of the three selected differences; all 8,128 two-cell Chi2 supports per difference excluded by exact Pressure constraints |
| **PROVED — GLOBAL TWO-ROUND CLASS** | `[1,1]` differential trails impossible | Every nonzero unrestricted input difference and base state; total active calls over two rounds at least 3 |
| **PROVED — COMPLETE DEFINED CLASS** | `A1=1` forces all 16 Pressure chains active after XRBD | Every one-byte post-Chi1 position/value difference, all unrestricted base states; 65,280 original-C/Python XRBD cases |
| **PROVED — COMPLETE DEFINED SITE CLASS** | All 2,080,768 `[1,2]` sites with two distinct second-branch Chi2 calls excluded | All 256 single-byte post-Chi1 start locations and every pair of distinct second-branch Chi2 calls; bit-zero through five-bit Pressure constraints |
| **PROVED — COMPLETE DEFINED SITE CLASS** | All 32,768 `[1,2]` same-spatial-pair Chi2 sites excluded | All 256 single-byte post-Chi1 start locations and all 128 spatial pairs; one first-branch and its paired second-branch call |
| **PROVED — COMPLETE DEFINED SITE CLASS** | All 2,080,768 distinct-AA `[1,2]` sites excluded | All 256 single-byte post-Chi1 start locations and every pair of distinct first-branch Chi2 calls; low-bit Pressure exclusions and refinement |
| **PROVED — FIXED-START DEFINED SUBCLASS** | 2,351 additional `[1,2]` site-pair exclusions from exact two-bit Pressure carries | Chi1 post-byte location 0; all 8,128 pairs of distinct second-call Chi2 cells classified; 3,872 LSB and 2,351 additional pairs excluded, 1,905 unresolved by this screen |
| **PROVED — COMPLETE DEFINED CLASS** | No lane-rotation covariance up to fixed XOR offset | Every nonzero uniform lane rotation and rounds 1–8, with and without round constants; unrestricted state input |
| **PROVED — THETA-ONLY STRUCTURAL CLASS** | Exact fixed-space dimension 1544, rank(Theta−I)=504, and all non-fixed states in 2-cycles | Every unrestricted 2048-bit state of the current scalar Theta layer alone; no full-round implication |
| **PROVED — COMPLETE DEFINED CLASS** | Exact one-round differential-linear perfect-mask dimensions 26–29 | Every one of 128 serial-Chi cells, every nonzero diagonal byte difference, and all masks in the specified 32-dimensional Pressure-affine output space; unrestricted state input |
| **PROVED — COMPLETE DEFINED CLASS** | No perfect two-round differential-linear output mask | Every nonzero 2048-bit output mask for each of 128 specified unrestricted input differences with diagonal Chi byte difference `delta=1` |
| **PROVED — COMPLETE DEFINED CLASS** | Four-state serial-Chi zero sum and two-round balance exclusion | One fixed square at all 128 unrestricted serial-Chi byte cells: no universal round-two coordinate balance; at one cell no universal balance for any nonzero output mask |
| **PROVED — GLOBAL CHECKPOINT / COMPLETE DEFINED CUBE** | Sharp valid-message 14-cube zero-sum threshold and exact round-two coordinate exclusion | Every independent 14-or-more-dimensional affine message cube sums to zero after Chi1 and XRBD1; a valid 13-cube shows the threshold is sharp; for the fixed bit-0–13 cube, exactly 32 universal balanced round-one coordinates and none at round two |
| **PROVED — COMPLETE DEFINED CLASS** | No universal round-two coordinate balance for any one-byte message cube | All 159 message-byte coordinate cubes and all 2,048 state-output bits, with arbitrary valid base message |
| **PROVED — COMPLETE DEFINED FAMILY** | No universal round-two linear output-mask balance for the byte-0 message cube | Every nonzero 2,048-bit output mask, with arbitrary valid base message and the first byte varying over 256 values |
| **PROVED — EXACT DIVISION-PROPERTY FAMILY** | Universal balanced-mask dimension falls from 7 to 0 | All 2,048-bit linear output masks for the first-byte 256-point valid-message cube, after complete rounds one and two |
| **PROVED — COMPLETE DEFINED SUBSPACE CLASS** | Every message-byte cube has maximal affine-hull rank immediately after Chi1 | All 159 zero-base valid-message byte-coordinate subspaces; exact rank 8 pre-Chi1 and 255 after Chi1 and complete rounds one and two |
| **PROVED — COMPLETE DEFINED SUBSPACE FAMILY** | Theta-cancelling low-rank hulls end at Pressure1 | All 256 diagonal eight-dimensional cosets in the valid-message two-byte plane at positions 40 and 56; post-Chi1 ranks 238–254, post-Pressure1 rank 255 in every coset, with and without XRBD |
| **PROVED — COMPLETE DEFINED REBOUND COMPONENT CLASS** | Exact serial-Chi diagonal inbound counts and two-sided outbound spread | All nonzero diagonal byte differences and output differences in one serial-Chi cell; 128 sites × 255 cases each through inverse prefix and XRBD |
| **PROVED — HASH-INTERFACE EXCLUSION** | No one-cell Chi input/output difference from the first block | Every nonzero 1,272-bit valid-message difference and all 128 serial-Chi cells at the first absorb |
| **PROVED — COMPLETE DEFINED CLASS** | Full first-order input/output dependency after rounds one and two | Every one of 1,272 message bits can affect every one of 2,048 state bits at each round count |
| **PROVED — COMPLETE DEFINED CLASS** | Exact Pressure mask counters, nonperfect maximum `1/2`, and exact-zero pruning | Uniform-input chain masks with `u=0/bit0` or second-output mask `q=0/bit0` |
| **PROVED — COMPLETE DEFINED CLASS** | Exact joint-carry counter and sharp nonperfect maximum `1/2` for both low-17 Pressure outputs | Uniform-input chain, both output masks confined to low `k≤17` bits; every input mask; analytic induction after a 96-case base lemma |
| **PROVED — COMPLETE DEFINED CLASS** | One-round hash-message correlation at most `2^-174` | Every 1272-bit message mask and each of 16 specified two-bit state-output masks after one complete round |
| **PROVED — COMPLETE DEFINED CLASS** | One-round hash-message correlation at most `2^-162` for a five-dimensional output-mask subspace | Every 1272-bit message mask and all 31 nonzero masks in the specified subspace; five-bit output variation below `2^-32` after any 128 independent linear message constraints |
| **PROVED — COMPLETE DEFINED CLASS** | One-round hash-message correlation at most `2^-76` for a six-dimensional output-mask subspace | Every 1272-bit message mask and all 63 nonzero masks in the specified subspace; six-bit output variation below `2^-74`, or below `2^-10` after any 64 independent linear message constraints |
| **PROVED — COMPLETE DEFINED CLASS** | One-complete-round correlation at most `2^-246` for a specified eight-dimensional nonlinear-Pressure output space | Every 1272-bit message mask, all 255 nonzero output masks, and every fixed affine translate of the message embedding; selected bits are outside the digest; affine-codimension-128 TV below `2^-115` |
| **PROVED — COMPLETE DEFINED CLASS** | Valid-message algebraic-degree map | After round 1, 32 specified state bits have exact degree 13 and the other 2016 have degree at least 20; after rounds 2–8, every state bit has degree at least 20; the first-32-byte projection has vectorial degree at least 24 after each round |
| **OPEN** | Useful numerical upper bound on the complete linear hull | Every nonzero input/output mask over complete rounds |

## PROVED — GLOBAL: no perfect linear message-to-state approximation

For every `r=1,...,8`, every 1272-bit message mask `alpha`, every
2048-bit state mask `beta`, and every affine bit `c`, the identity

`alpha·m XOR beta·F_r(m) = c`

cannot hold for every message unless `alpha=beta=0`. Equivalently,
every nontrivial input/output mask pair has absolute correlation below
one. This includes masks limited to the first 256 state bits used as
the one-block digest.

**Mathematical proof and finite certificate:** 3,325 valid-message graph rows
`(1,m,F_r(m))` span all 3,321 coordinates for each `r`. A universal
identity would annihilate those rows, contradicting full rank.
The saved [certificate](../results/full_linear_rank_8rounds_messages.bin) and
[rank report](../results/full_linear_rank_8rounds.json) specify every row.
**Replay validation:** the [opposite-pivot audit](../results/full_linear_rank_8rounds_audit.json)
recomputes the ranks with [the verifier](../scripts/krakken_full_linear_rank_audit.py).

**Scope:** This closes the `|correlation|=1` case. Rank alone gives
only the weak numeric bound `|correlation| <= 1-2^-1271`; it does not
establish a useful linear attack complexity.

## PROVED — COMPLETE DEFINED CLASS: exact first-Chi sparse-mask correlations

Let `H(m)` be the state just after first-round Chi. For any output
mask active on exactly `t` serial-Chi byte-pair components with
`t=1,2,3`, and for any message mask, the absolute correlation is at
most `2^(-3t)`. The **maximum over all masks** in each of these three
classes is exactly `2^(-3t)`, namely `1/8`, `1/64`, and `1/512`.
This exhausts the entire output-mask class touching exactly one,
two, or three components; it is not a selected-mask search.

**Mathematical proof and exhaustive certificate:** Each serial-Chi component's exact 16-bit Walsh
spectrum has nonzero-output-mask maximum `1/8`. Exhaustive GF(2) rank
checks show that all `128` single components, `8,128` pairs, and
`341,376` triples have full 16-, 32-, and 48-bit projections from the
valid message space. They are therefore jointly uniform whenever
selected. Correlations factor across the selected components, and
message masks outside their input row span have correlation zero.
Locally optimal masks attain the product. For example, choose the
components `(0,4,0)`, `(0,4,1)`, and `(0,4,2)` in order. On each
selected component use pre-Chi input byte masks `(0x38,0x38)` and
post-Chi output byte masks `(0x01,0x00)`. The local signed correlation
is `-1/8`; the exact full-message masks, full-state masks, and padding
phases are in the [attaining-mask certificate](../results/chi_sparse_attaining_masks_pure.json).
The resulting signed correlations are `-1/8`, `+1/64`, and `-1/512`
for `t=1,2,3` respectively. See the
[pure-Python S-box Walsh certificate](../results/sbox_walsh_certificate.json),
and [rank report](../results/rate_chi_component_rank_3_pure_replayed.json).
**Replay validation:** the [opposite-pivot audit](../results/rate_chi_component_rank_3_pure_audit.json)
rechecks all component-subset ranks, while the attaining-mask script
checks the mask layout against the original C layers.

**Scope:** This closes the entire stated sparse-mask class at Chi1.
The four-component class is separately closed below. It does not cover masks active on five or more Chi components or
complete rounds including XRBD and Pressure.

## PROVED — COMPLETE FOUR-CELL CLASS: exact first-Chi sparse-mask correlations

For every four-component selection among the 128 serial-Chi components,
the 64 pre-Chi input bits have full rank as a projection of the valid
159-byte message space. Two complete finite rank scans independently
count all `10,668,000` selections; a separate Python implementation
reconstructs all 1,272 message-basis columns and their projected rows.
Thus, for every message mask and every post-Chi1 output mask active on
exactly four components, the sharp absolute-correlation maximum is
`(1/8)^4=2^-12`. Four copies of the local mask
`(0x38,0x38)->(0x01,0x00)` attain it. This is a Chi1 checkpoint
result, not a complete-round hull bound. See
[LIN-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-002) and its
[artifact manifest](KRAKKEN_THEOREM_ARTIFACTS.md#lin-chi-002).

## PROVED — COMPLETE DEFINED FAMILY: perfect local serial-Chi boomerangs

For the effective two-byte serial-Chi permutation

`F(a,b)=(u,v)=(S(a XOR b), S(b XOR u))`,

every nonzero byte `beta` and every nonzero byte `gamma` give the
nontrivial BCT entry

`B_F[(beta,beta),(gamma,0)] = 65,536`.

There are `255×255=65,025` specified entries in this family. A BCT
count cannot exceed the `2^16` component inputs, so the
**component's nontrivial boomerang uniformity is maximally 65,536**.
This first family theorem alone asserts at least this many maximizing
entries; the complete classification below closes whether any others
attain the same maximum.

**Proof.** The diagonal input translation `(a,b)→(a XOR beta,b XOR
beta)` leaves `a XOR b` and therefore `u` unchanged. Write
`I=S^-1`; the inverse map is
`b=I(v) XOR u`, `a=I(u) XOR b`. Under the diagonal translation,
`I(v)` changes by `beta`. XORing `(gamma,0)` into each of the two
outputs changes `u` equally, so their inverse images still differ
by `(beta,beta)` for **every** base. The argument requires only that
the byte S-box be bijective. The fresh
[current-C continuation](../scripts/krakken_boomerang_fresh.py) checks the S-box
bijection and 64,000 embedded local quartets; the algebra covers the
whole 65,025-entry family.

This is a strong **local** structure and a research target for
multi-round boomerang analysis, not a full-round or eight-round
distinguisher. No complete-round quartet claim follows from this
component theorem. A new complete defined-class continuation is in
the [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md).

## PROVED — COMPLETE LOCAL CLASS: exact serial-Chi boomerang gap

The 65,025 diagonal/first-output pairs above are **all** nontrivial
perfect pairs of the effective 16-bit serial-Chi component. Every
other nontrivial pair has BCT count at most **1,536** out of 65,536
uniform unrestricted bases, a sharp probability bound of `3/128`.
For unrestricted full-state Chi, the 128 disjoint cells factor exactly:
if `k` cells use nonperfect local pairs, the full-Chi BCT probability
is at most `(3/128)^k`, sharply.

The [analytic reduction and case split](THEOREM.md) reduce the complete
local BCT to byte S-box DDT/BCT tables. The only case not bounded
directly by the byte maxima is a 16,646,400-entry XOR convolution;
its [source-pinned certificate](../results/krakken_chi_bct_classification.json)
computes every entry by two exact integer methods and gives maximum
1,364. The verifier was reproduced byte for byte. This classification
does not bound a complete-round or hash-reachable boomerang probability;
Chi2 continuation uses a different four-state rectangle condition.

## PROVED — FOUR DEFINED BOOMERANG CLASSES: 4,784 Pressure survivors, none across Chi2

At one serial-Chi site (`y=0,p=0,j=0`), fix the nonzero local
differences `d=gamma=128` and set all other post-Chi1 bytes to zero.
The 65,536 choices of local output-base bytes `(u,v)` are a complete
finite class of genuine one-cell BCT quartets. Original-C enumeration
finds **1,300** that retain the quartet rectangle after XRBD and
Pressure, hence through the linear prefix of round 2. **None** of those
1,300 retains the required equal vertical output differences after
Chi2. This is an exact exclusion for that defined class, **not** a
universal round-2 boomerang exclusion. The [producer](../scripts/krakken_boomerang_cell_exhaust.py),
[certificate](../results/krakken_boomerang_cell_exhaust.json), and
[independent Python audit](../results/krakken_boomerang_cell_audit.json) agree.
The exclusion has a stronger local explanation: for **each** of the
1,300 Pressure survivors, at least one Chi2 serial-Chi cell has
**zero** solutions to the four-point rectangle equation over *all*
65,536 possible local bases. The [original-C local counter](../scripts/krakken_boomerang_chi2_obstruction.py),
[per-quartet certificate](../results/krakken_boomerang_chi2_obstruction.json), and
[independent Python/NumPy audit](../results/krakken_boomerang_chi2_obstruction_audit.json)
verify this base-independent obstruction for the **fixed Chi2 input
difference patterns**. Three more complete 65,536-base classes at the
same site and background, with `(d,gamma)` equal to `(255,128)`,
`(255,1)`, and `(128,1)`, contribute **1,356**, **1,196**, and **932**
Pressure survivors respectively. Their [original-C enumeration](../results/krakken_boomerang_cell_suite.json),
[independent audit](../results/krakken_boomerang_cell_suite_audit.json), and
[local obstruction certificate](../results/krakken_boomerang_cell_suite_obstruction.json)
show zero Chi2 BCT survivors and one base-independent zero-count cell
for **each** of those 3,484 additional survivors. The
[combined check](../results/krakken_boomerang_four_class_verified.json) certifies
**262,144** bases, **4,784** Pressure rectangles, and **zero** Chi2
BCT survivors across the four classes. Changing the earlier background
may change the difference patterns; this is not a universal two-round
exclusion.

Every one-cell local quartet can be embedded in unrestricted
round-start states because the current-C pre-Chi1 prefix has rank
2048/2048; a [four-state witness](../results/krakken_boomerang_embed.json)
is replayed with the original-C complete-round entry point. For the
actual first 159-byte hash block, the rate-to-pre-Chi1 map projected
outside each candidate cell has rank 1272/1272 at all 128 sites.
Consequently this one-cell inbound is **not hash-reachable at the first
absorb** for a nonzero message difference. The
[rate-gate certificate](../results/krakken_boomerang_rate_gate.json) checks the
rank in two elimination orders. Multi-cell and later-block quartets
remain open.

## PROVED — GLOBAL FIRST-BLOCK CLASS: the Chi1 minimum is exactly five

For **every** nonzero difference between valid 159-byte first-block
messages and every base message, at least **five** byte S-box calls are
active in Chi1. A valid pair with **exactly five** active calls exists,
so **`min A1 = 5`** over this complete input class.

The current-C rate-to-pre-Chi1 map has a 1272-dimensional image.
Projecting each 16-bit serial-Chi input cell into the quotient by that
image, all **128** one-cell, **8,128** two-cell, and **341,376**
three-cell supports have full ranks `16,32,48`. Of **10,668,000**
four-cell supports, exactly **six** have rank 63 rather than 64.
The [rank certificate](../results/krakken_boomerang_rate_support.json) and
[independent pure-Python/opposite-pivot audit](../results/krakken_boomerang_rate_support_audit.json)
agree on every support.

All six deficient supports have a unique nonzero reachable
difference line. The source S-box DDT counts for silencing the second
serial call in the four cells are `0,2,0,2`, forcing **at least six**
calls for any of those four-cell differences. Five-or-more-cell
differences cost at least five calls, which proves the global lower
bound. The [six concrete valid-message witnesses](../results/krakken_boomerang_four_cell_optimum.json)
attain active-call pattern `(2,1,2,1)` and therefore `A1=6`;
their [independent replay](../results/krakken_boomerang_four_cell_optimum_audit.json)
checks the prefix and Chi in Python and their full hash digests in
the original C.

The matching five-call [valid-message witness](../results/krakken_five_cell_candidates.json)
has one active call in each of five Chi1 cells. Its
[independent original-C/Python replay](../results/krakken_five_cell_witness_audit.json)
verifies the padded messages, the first complete round, Chi2, and
the full 32-byte hash digests. That witness has `A2=255`, with 216
active bytes immediately after XRBD1. These are witness values, not
universal second-round bounds.

For its **fixed input difference**, the event `A1=5` has exact
probability **`2^-35`** under a uniform valid 159-byte base message:
the five controlling first-S-box input bytes have full projection rank
40, and each required S-box derivative has two favorable values out
of 256. The [exact calculation](../results/krakken_five_cell_probability.json)
and [independent audit](../results/krakken_five_cell_probability_audit.json)
verify this result. It is an activity-event probability for that
one input difference, not a full-round trail probability.

For these six witnesses, [original-C traces](../results/krakken_boomerang_four_cell_outbound.json)
and [independent replay](../results/krakken_boomerang_four_cell_outbound_audit.json)
give **A2=253–255** for the six four-cell witnesses. These remain
useful additional trajectories, not universal second-round bounds.

## PROVED — GLOBAL FIRST-FULL-BLOCK CLASS: five calls at the first 160-byte absorb

For two distinct valid **160-byte** messages, the current hash API
absorbs the complete block without padding and then runs its first
permutation call. The minimum active serial-Chi byte-S-box count in
the first round of that call is **exactly five**, over every nonzero
full-block XOR difference and every base message. An additional
padded final permutation call follows; this claim does not cover its
activity.

The full rate gives 1,280 free difference bits. The exact source-derived
rate-image quotient has full ranks for every one-, two-, and three-cell
pre-Chi support. Of all 10,668,000 four-cell supports, exactly eight
have a one-dimensional nonzero intersection with the rate image. The
byte S-box DDT counts needed to silence their second serial call are
`(0,2,0,2)`, so every such four-cell difference requires at least six
calls. Five-or-more-cell differences require at least five. The
[original-C enumeration](../results/krakken_full_block_rate_support_c_four.json)
and [separate Python-prefix enumeration](../results/krakken_full_block_rate_support_python_four.json)
agree on every support rank and the same eight exceptions; they share
the rank enumeration code. An [opposite-pivot recount](../results/krakken_full_block_rate_support_python_low_three.json)
independently checks all supports through three cells. The
[eight-line certificate](../results/krakken_full_block_four_lines.json)
and [Python/DDT audit](../results/krakken_full_block_four_lines_audit.json)
verify the exceptional differences and call costs.

Appending the same byte `0x86` to the established 159-byte five-call
message pair yields two valid 160-byte messages whose first absorb
states are identical to the original padded absorb states. The
[original-C replay](../results/krakken_full_block_witness_audit.json)
checks both complete 160-byte hashes and confirms five first-call
Chi activations. If two longer messages share complete preceding
blocks and first differ in a subsequent complete block, the same
proof gives a floor of five at that block's first Chi for every common
base state. Differing prefixes, later padding, and later-round
activity remain outside this statement.

## PROVED — COMPLETE SIX-DIFFERENCE CLASS: exact four-cell first-Chi probabilities

For **each of the six** source-certified rate-reachable four-cell
message XOR differences, a uniformly chosen valid 159-byte base
message gives the exact law

`A1 = 6 + Binomial(2,127/128)`.

Thus `Pr[A1=6]=2^-14`. For **every specific post-Chi1 state
difference** under any one of these fixed input differences, the
probability is at most **`2^-38`**, and this maximum is attained for
each of the six. Conditioned on `A1=6`, the sharp single-output
maximum is `2^-24`.

The C-derived map from valid message bases onto the four selected
two-byte Chi inputs has rank `64/64` for every line. Hence those four
local bases are independent uniform words. Exhaustive local
`2^16`-base counts give one-call counts `[0,512,0,512]` and maximal
single-output counts `[16,512,16,512]`; multiplying these counts is
valid **because the 64-bit projection is full rank**. The
[source-pinned certificate and six attaining pairs](../results/krakken_four_cell_probability.json)
and [independent C-S-box, opposite-pivot, original-C replay audit](../results/krakken_four_cell_probability_audit.json)
reproduce the ranks, counts, and concrete transitions. This is a
first-Chi output theorem for six fixed valid-message differences; it
is not a two-round differential-hull or collision bound.

## PROVED — GLOBAL FIRST-CHI CHECKPOINT: prescribed-output concentration

For **every** fixed nonzero valid 159-byte message difference `delta`
and **every** prescribed full-state difference `eta` immediately after
Chi1, the probability over uniform valid base messages is at most
`2^-24`. The bound holds immediately after invertible linear XRBD1.
The proof combines the previously certified minimum of four active
pre-Chi components, the new rank-64 theorem for every four selected
components, and the exact local serial-Chi DDT maximum `1/64` per
active component. The six exceptional four-cell lines retain their
stronger sharp `2^-38` single-output bound. The universal `2^-24`
bound is **not claimed sharp** and does not extend through nonlinear
Pressure by bijectivity alone. See
[DIFF-RATE-005](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-005).

The independent conditional-branch theorem below improves this
numerical bound to `2^-30` for the same uniform 159-byte domain. The
original four-cell proof remains valid and retains its permanent ID.

## PROVED — COMPLETE CONDITIONAL CHI CLASS: 133-byte independence

For every fixed affine state offset, uniform valid 159-byte messages
make **all 128 first-call Chi inputs and any five selected second-call
inputs jointly uniform**. The corresponding output bytes are jointly
uniform too. Every prescribed 133-byte output tuple has exactly
`2^208` valid-message preimages. The same joint-uniformity theorem
holds for a uniform full 160-byte rate, with `2^216` preimages per
133-byte tuple.

For every nonzero rate-message difference, the theorem gives an exact
product formula for all first-output difference bytes and any five
selected second-output difference bytes. With the inherited five-call
minimum and the source S-box DDT bound, **every prescribed full
Chi1/XRBD1 difference has probability at most `2^-30`** under the
uniform message base. The result also gives exact maximum linear
correlations for masks on all first-output bytes plus at most five
second-output bytes; a mask on `t` first-output bytes alone has sharp
maximum `2^(-3t)`, including `2^-384` at `t=128`.

The finite obligation was exhausted twice over all `264,566,400`
five-cell selections, with every projected exception resolved on
full rows. Separate source-pinned prefix reconstruction and 32
original-C constructed-message replays audit the implementation.
These are first-Chi/XRBD checkpoints, not complete-round or digest
claims. See [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001),
the [full derivation](../RESULTS2.md), and the
[certificate chain](KRAKKEN_THEOREM_ARTIFACTS.md#chi-rate-001).

## PROVED — ACTIVE-FIRST-CALL CHI CLASS: affine transition fibers

For a prescribed serial-Chi difference whose first byte S-box call
is active, its compatible input-base set is empty or affine, with
size equal to the product of two byte-DDT counts. Hence any complete
first-Chi transition in which every nonzero input component has an
active first call reduces, after the message prefix, to an affine
system on message bits. The exact uniform-base probability is zero
if inconsistent, otherwise `2^-r` for that system's rank `r`.
The analytic argument and checks of all 32,385 nonempty byte derivative
fibers and 128 direct local transitions are in
[DIFF-CHI-001](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-001).
The condition does not cover cells with only the second S-box call
active, nor any Pressure transition.

## PROVED — COMPLETE LOCAL DIFFERENTIAL CLASS: maximum-DP trichotomy

For every nonzero two-byte input difference of the unrestricted
serial-Chi component, the sharp maximum over all output differences
is one of `2^-6`, `2^-7`, `2^-12`. Exactly 510, 32,130, and 32,895
input differences fall into those classes respectively, and each
has a **unique** maximizing output difference. The classification is
the explicit `D_S(da XOR db,db)` rule in
[DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002).
Its proof uses the exact two-DDT factorization and the source S-box's
complete `0/2/4` row spectrum. A separate C implementation recounts
every local input difference; 63 attaining transitions replay through
the original C Chi. The full 128-cell product applies under uniform
unrestricted pre-Chi states, not automatically to valid messages.

## PROVED — COMPLETE PERFECT LOCAL DIFFERENTIAL-LINEAR CLASS

For every nonzero local serial-Chi input difference and nonzero output
mask, absolute output-difference correlation equals one **exactly**
for diagonal input `(d,d)` and first-output-only mask `(A,0)`, with
`d,A!=0`. These are the **65,025** nontrivial perfect pairs. All other
local pairs have `|corr|≤71/512`; that numerical bound is
conservative, not claimed sharp. The proof reduces the local DLCT to
the byte S-box autocorrelation table, whose complete nontrivial
maximum is 32. Independent Python and C ACT tables agree, and 128
direct 16-bit local sums validate the reduction. See
[DL-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-local-001).
This is an unrestricted Chi statement, not a complete-round or
hash-interface differential-linear bound.

## PROVED — CONDITIONAL HASH-REACHABLE CLASS: five Chi1 calls require at least three Chi2 cells

Fix any of the three valid 159-byte **message XOR differences** indexed
`(2,6),(2,9),(21,2)` in the source-pinned selected
[five-cell candidate set](../results/krakken_five_cell_candidates.json). For
every valid base message attaining `A1=5` with any one of these
differences, **`A2>=3`**. Each event is nonempty, with an original-C
attaining pair. This is complete over all bases in each conditioned
event, not over all valid input differences. Equivalently,
`A1+A2>=8` within each event.

The five active Chi1 cells have nonzero first-S-box input differences,
so `A1=5` forces their second calls inactive. This fixes the complete
post-Chi1 difference independently of the base. After exact XRBD,
pull each hypothetical one- or two-cell Chi2 input support backward
through the inverse linear tail. Even allowing **all 16 bits in each
cell**, Pressure's 32 exact bit-zero equations exclude every one-cell
support and all 8,128 two-cell pairs for the first two differences.
For `(21,2)`, exactly two two-cell pairs survive bit zero. Their 32
and 256 affine endpoint assignments are all excluded by exact joint
low-two-bit Pressure transition tests. Thus at least three Chi2 cells
must be active in each of these three conditioned events.

The [source-pinned producer and three original-C witnesses](../results/krakken_a15_three_line_gate.json)
are checked by an [independent C replay and opposite-pivot audit](../scripts/krakken_a15_three_line_gate_audit.py)
with its [certificate](../results/krakken_a15_three_line_gate_audit.json).

## PROVED — GLOBAL TWO-ROUND CLASS: `[1,1]` differential trails are impossible

For the XRBD-enabled source snapshot, count active byte S-box calls in
the first two serial-Chi layers as `(A1,A2)`. For **every** nonzero
unrestricted 2048-bit input difference and every base state,
`(A1,A2) != (1,1)`. Since each nonzero round has at least one active
call, the total over two rounds is at least **3**. The theorem applies
to the actual first-block hash input as a subset; it does not say that
round 2 alone has at least three active calls.

The [source-pinned SCIP model](../krakken/krakken_prove_11_v2.py)
starts from every nonzero single post-Chi1 byte and compiles the exact
XRBD and inter-round linear layers. Its carry-difference conditions
**overapproximate** the real Pressure additions, and its target union
contains both possible one-active-Chi2 branches at every location.
Thus any real `[1,1]` trail would satisfy one of its 512 jobs. The
[complete log](../krakken/prove_11_full.log) records **512 infeasible,
zero unknown** SCIP results. The [independent audit](../scripts/krakken_11_audit.py)
checks complete job coverage, compares the linear maps with C, verifies
all 65,280 XRBD branch conditions and the relaxed full-adder rule, and
replays one job from each target branch; its [report](../results/krakken_11_audit_validated.json)
pins hashes of the source, model, and log. The
[theorem program](KRAKKEN_SECURITY_THEOREMS.md) gives the full
soundness argument.

This closes the stated `[1,1]` class. `[1,2]`, `[2,1]`, and useful
multi-round activity bounds remain open.

## PROVED — COMPLETE DEFINED SITE CLASS: 1,628,104 `[1,2]` sites excluded

Take one nonzero post-Chi1 byte at any of 256 locations. Require
exactly two active **second-branch** Chi2 calls in two distinct serial
16-bit cells, with every other Chi2 call inactive. Among the
`256×C(128,2)=2,080,768` possible start-location/cell-pair cases,
**1,628,104 are impossible for every nonzero start-byte value and
every base state**. Of these, 1,034,445 fail exact Pressure bit-zero
equations and another 593,659 fail exact joint low-two-bit equations
of both Pressure additions. The remaining 298,360 low-two-bit
survivors and 154,304 cases above the chosen kernel-dimension cap of
18 are unresolved by this screen, not established real trails.

The [rank verifier](../scripts/krakken_pressure_lsb_endpoint.py) compiles the
exact XRBD and inverse inter-round linear maps, then uses the 32
universal Pressure LSB differential identities. In each excluded
case, GF(2) elimination proves that every solution forces at least
one of the two selected nonzero Chi2 byte differences to zero.
The [LSB report](../results/krakken_pressure_lsb_endpoint_rank.json)
records its case counts and C comparisons of the Pressure identities;
an [independent Z3 audit](../scripts/krakken_pressure_lsb_rank_audit.py) replays
25 excluded cases across five start positions.
For the additional cases, the 32 exact bit-zero constraints leave
at most 18 free symbolic difference bits. Enumerating all assignments
with the three required bytes nonzero and testing the exact 184-of-1,024
joint low-two-bit Pressure transition table proves impossibility when
none survives. It allows unconstrained bases for different chains,
so rejection in this relaxed model excludes every real base. No
solver timeout enters the proof.

The [256-position producer summary](../results/krakken_12_joint2_all_positions/summary_k18.json)
and [independent original-C recount](../results/krakken_12_joint2_all_positions/audit_summary_k18.json)
match in every position and category. The auditor independently
derives XRBD and the inverse linear tail from C, checks all 1,024
endpoint basis columns against the C tail, uses opposite-pivot GF(2)
elimination, and re-enumerates the joint two-addition table. All 512
per-position JSON files, source hashes, and case totals were checked.
The cases left by this two-bit screen are resolved by the stronger
BB-class theorem below. First-branch targets and both-active-in-one-cell
targets remain outside it; full `[1,2]` exclusion stays open.

## PROVED — COMPLETE DEFINED SITE CLASS: all `[1,2]` BB sites excluded

The preceding 452,664 sites left by the two-bit screen were tested
with stronger **joint** low-bit Pressure equations, keeping all three
required difference bytes nonzero and allowing arbitrary independent
base slices in each Pressure chain. The [completed three-bit
campaign](../results/krakken_12_joint3_all_positions_summary.json) excludes
451,718 of them and records 946 relaxed SAT survivors. The
[refinement report](../results/krakken_12_sat_refinement.json) excludes 914 of
these at four bits and the remaining 32 at five bits. The exact
accounting is

`1,034,445 + 593,659 + 451,718 + 914 + 32 = 2,080,768`.

For `k<=5`, these are necessary conditions for original-C Pressure:
the low `k` output bits of the two additions depend on the disjoint
base slices `a[0:k]`, `c[0:k]`, `c[17:17+k]`, while `A<<31` cannot
affect those bits. The inverse inter-round target columns and XRBD
start columns are derived from the current C source. An UNSAT result
therefore excludes the named site for **all** nonzero difference-byte
values and **all** unrestricted base states, despite omitted Chi2
DDT and upper Pressure constraints.

The [independent original-C refinement audit](../scripts/krakken_12_refine_sat_audit.py)
uses its own profile and Z3 encoding, checks 100 full-width Pressure
pairs against C, and reproves all 946 refinement exclusions in its
[report](../results/krakken_12_sat_refinement_audit.json). The earlier two-bit
screen has a complete independent recount. The 451,718 three-bit
UNSAT results have complete source-pinned per-site records and a
reproducible producer, but no second full independent recount yet.

**Scope:** this closes the BB class only: exactly two second-branch
Chi2 calls at distinct sites. The same-spatial-pair and distinct-AA
classes are closed separately below. Distinct mixed `AB/BA` remain
open, as does full `[1,2]` exclusion.

## PROVED — COMPLETE DEFINED SITE CLASS: all same-spatial-pair `[1,2]` sites excluded

For each of 256 one-byte post-Chi1 difference locations and each of
128 spatial two-byte Chi pairs, require both paired Chi2 calls active
and all others inactive. A source-pinned, resumable
[split-site scan](../scripts/krakken_12_remaining_split.py) excluded 743 sites
by exact Pressure bit-zero constraints and 32,001 more by exact joint
three-bit constraints. Its 256 per-position JSON reports in
[the result directory](../results/krakken_12_remaining_split_results) cover every
site exactly once. All 24 relaxed survivors were excluded at four bits
by the [refinement](../scripts/krakken_12_remaining_refine.py) and its
[report](../results/krakken_12_same_refinement.json), giving
`743 + 32,001 + 24 = 32,768` exclusions.

The endpoint parameterization permits arbitrary paired-byte
difference—even zero—and omits Chi2 derivative constraints. These
relaxations can only admit additional solutions, so Pressure UNSAT
excludes every real trail in the class. The scan derives linear maps
from current original C and cross-checks its low-bit identities
against original-C Pressure transitions. Every position's source
hash, 128 unique site indices, and aggregate count were checked.
The 32,001 three-bit UNSAT cases have not had a second full
independent recount. This verification boundary should be considered
in external review. Distinct AA is closed separately; mixed AB/BA
classes remain open.

## PROVED — COMPLETE DEFINED SITE CLASS: all distinct-AA `[1,2]` sites excluded

For every one of 256 single-byte post-Chi1 start locations and every
pair of distinct first-branch Chi2 calls, the source-pinned
[split-site scan](../scripts/krakken_12_remaining_split.py) excludes
395,109 sites by exact bit-zero Pressure constraints and 1,670,915
more by exact joint three-bit constraints. All 14,744 relaxed-SAT
cases are UNSAT under the [refinement](../scripts/krakken_12_refine_position.py):
12,823 at four bits and 1,921 at five bits. Thus all 2,080,768
named sites are excluded under a sound low-bit relaxation, for all
nonzero difference bytes and unrestricted bases. The
[coverage audit](../results/krakken_12_aa_closure_audit.json) checks
every saved report and refinement against the pinned C/header hashes.
It does **not** independently recount the solver UNSAT results.
The full unrestricted `[1,2]` exclusion remains open: distinct mixed
AB is being scanned, and distinct mixed BA is not yet closed.

## PROVED — FIXED-START SUBCLASS: exact two-bit carries add 2,351 exclusions

Fix the one post-Chi1 difference byte at lane 0, byte 0 and require
exactly two active **second** Chi2 calls in distinct cells. For each
of the 8,128 endpoint cell pairs, use 24 symbolic bits for the three
nonzero difference bytes. After the 32 exact Pressure LSB equations,
enumerate the remaining kernel if its dimension is at most 18. The
exact joint two-bit equations in all 16 Pressure chains admit 184 of
1,024 local difference tuples. Their simultaneous feasibility
excludes **2,351 additional site pairs** beyond **3,872** excluded
by the LSB gate. These **6,223 pairs are impossible for every base and
all nonzero byte values**. The other 1,139 pairs pass this necessary
condition, and 766 exceed the chosen kernel cap; neither group is
claimed feasible.

The [source-pinned enumerator](../scripts/krakken_12_joint2_screen.py) and
[report](../results/krakken_12_joint2_start0.json) are independently checked by
an [original-C audit](../scripts/krakken_12_joint2_start0_audit.py) and its
[report](../results/krakken_12_joint2_start0_audit.json). The audit rebuilds
the 2048-bit inverse prefix from C columns, checks 1,024 target
basis columns through the C tail, uses a different GF(2) pivot order,
and reproduces all four counts. The full `[1,2]` exclusion remains
open.

## PROVED — COMPLETE DEFINED CLASS: no exact lane-rotation affine symmetry

Let `R_k` rotate all 32 state lanes left by the same `k=1,...,63`
bits. For each complete-round count `r=1,...,8`, no fixed state
constant `c` makes `P_r(R_k x)=R_k P_r(x) XOR c` hold for **every**
unrestricted state `x`. This also holds for the corresponding
constant-free round composition, so it is not just an effect of
the round constants.

The [source-pinned verifier](../scripts/krakken_rotational_affine_audit.py)
evaluates original C layers. For each of the 1,008
mode/round/rotation cases, `x=0` fixes the only possible `c`, and
the state with bit 11 set in lane 0 refutes that value. The
[certificate](../results/krakken_rotational_affine_audit.json) records every
counterexample. The claim excludes exact covariance up to an XOR
offset; it does not rule out statistical rotational distinguishers.

For the seven byte-aligned rotations, the one-round related-input
residual has an additional exact decomposition. Write `B` for the
bijection Theta→MDS→Rho→Pi→Chi→XRBD. Because `B` and InkCloud
commute with these rotations, the residual
`P_1(R_k x) XOR R_k P_1(x)` equals InkCloud applied to
`Pressure(R_k B(x)) XOR R_k Pressure(B(x)) XOR RC_0 XOR R_k RC_0`.
Thus, under a uniform unrestricted state input, **one-round bit-bias
magnitudes are exactly Pressure rotational-residual magnitudes**, up
to output-bit relabeling. XRBD cannot remove that one-round uniform-
state rotational bias by itself; the later composition must be
analyzed separately. The [C replay](../results/krakken_rotational_decomposition_validated.json)
checks the identity for all seven rotations on 100 states each.

## PROVED — THETA-ONLY STRUCTURAL CLASS: fixed states and cycles

For the current scalar Theta layer on the unrestricted 2048-bit
state, `Theta^2=I`, `rank(Theta−I)=504`, and
`dim Fix(Theta)=1544`. Thus exactly `2^1544` states are fixed and
every other state belongs to a 2-cycle. The analytic proof splits
the eight column parities into even and odd four-word recurrences;
each seed must be invariant under four-bit rotation, leaving four
bits per parity class above a 1536-dimensional parity-zero kernel.

The [full source-pinned matrix](../results/krakken_theta_fixed_space.matrix.bin)
was built from original-C `theta_scalar` on every state basis vector.
An [explicit fixed-state basis](../results/krakken_theta_fixed_space.basis.bin)
contains 1544 vectors, all replayed through C. Sixteen saved
non-fixed states form C-replayed 2-cycles. A
[separate Python reconstruction](../results/krakken_theta_fixed_space_audit.json)
matches every matrix column and basis vector and reproduces the
rank with opposite pivots. See
[LIN-THETA-001](KRAKKEN_SECURITY_THEOREMS.md#lin-theta-001).
This is a linear-layer classification only; it does not give a
complete-round invariant, distinguisher, or security-bit bound.

## PROVED — COMPLETE DEFINED CLASS: one-round differential-linear structures

For each of the 128 serial-Chi byte cells and every nonzero byte
`delta`, invert the first-round linear prefix on a diagonal
`(delta,delta)` pre-Chi difference at that cell. This defines a
nonzero **unrestricted permutation** input difference `Delta` with
exactly one active Chi1 byte S-box. Within the 32-dimensional output
mask space obtained by transporting Pressure's exact LSB affine
relations through InkCloud, the masks with perfect one-round
differential-linear autocorrelation `+1` have **exactly** these
dimensions: 29 for 8 cells, 28 for 56, 27 for 48, and 26 for 16.
For 125 cells, a single output bit attains `+1`; for the remaining
three, two bits suffice.

The proof reduces every derivative to one byte `D_delta S(t)` in the
second serial-Chi output. Exhaustive calculation of all 255
nonzero S-box input differences gives affine derivative-span rank
8 each time. The exact Pressure LSB mask identities and XRBD
transpose produce an `8×32` GF(2) projection whose rank, exhausted
over all 128 cells, is 3–6. Its kernel is **exactly** the perfect-mask
subspace, not merely a found subset. The
[counter and C verifier](../scripts/krakken_differential_linear.py) and
[certificate](../results/krakken_differential_linear_validated.json) record all
cell ranks, 3,200 Pressure-affine C checks, and a complete-round
attaining witness replayed on 1,000 bases.

The chosen `A1=1` input differences are excluded at the valid padded
first hash block by the earlier rate-only reachability theorem.
No hash-interface differential-linear claim follows.

## PROVED — COMPLETE DEFINED CLASS: round 2 removes every perfect output mask

For **each of the 128 input differences** in the preceding theorem
with diagonal byte difference fixed to `delta=1`, the set of complete
two-round output differences has **full affine span 2048**. Thus,
for every nonzero 2048-bit output mask `beta`, its derivative parity
is nonconstant and its differential-linear autocorrelation has
magnitude strictly below one. This closes the perfect-correlation
question over **all output masks** for these 128 fixed unrestricted
input differences—not just the Pressure-affine mask subspace.

The [rank certificate](../results/krakken_differential_linear_fullstate_rank_all128.json)
specifies deterministic C bases and independent derivative digests;
no cell needed more than 2,059 bases to span all 2,048 output bits.
The [independent replay](../scripts/krakken_differential_linear_fullstate_audit.py)
recomputed **262,464 original-C pairs** and obtained full rank in
all 128 cases with an opposite pivot order. Its
[audit report](../results/krakken_differential_linear_fullstate_audit_validated.json)
pins the source and generator. This is a finite certificate, not a
sampling inference. It excludes perfect correlations only: a useful
upper bound on nonperfect two-round correlations remains open, as do
other input differences and the valid padded hash interface.

## PROVED — COMPLETE DEFINED CLASS: Pressure two-shear mask families

For a 128-bit Pressure chain with **uniform unrestricted input**,
the signed correlation for every input mask `(u,v)` and output mask
`(p,0)` can be counted exactly by
[the carry-aware counter](../scripts/krakken_pressure_first_branch_walsh.py).
The first output word is `A=a+(c XOR (c>>17))`. Because
`c -> c XOR (c>>17)` is invertible and linear, its mask problem is
exactly a modular-addition mask problem after a linear change of input
mask. The complete class has only one nontrivial perfect relation,
`A[0] XOR a[0] XOR c[0] XOR c[17]=0`; **every other nonperfect
coefficient is at most `1/2` in magnitude**, and `1/2` is attained.

**Mathematical proof.** Write `t=c XOR (c>>17)` and change the input
variable from `c` to `t`. The map is invertible, with inverse
`c=t XOR (t>>17) XOR (t>>34) XOR (t>>51)`. This converts the claimed
Pressure coefficient to an ordinary addition coefficient with input
masks `(u,(f^-1)^T v)` and output mask `p`. For addition, let
`M_{u_i,v_i,p_i}[h,h']` be the signed transition from carry `h` to
carry `h'` at bit `i`, divided by four. The complete list of numerator
matrices `4M` is:

| `(u_i,v_i,p_i)` | `4M`, with rows/columns ordered carry `0,1` |
|---|---|
| `000` | `[[3,1],[1,3]]` |
| `111` | `[[3,1],[-1,-3]]` |
| `010` or `100` | `[[1,-1],[1,-1]]` |
| `110` | `[[-1,1],[1,-1]]` |
| `001` | `[[-1,1],[-1,1]]` |
| `011` or `101` | `[[1,-1],[-1,1]]` |

Every row has absolute sum `1/2` after division by four unless
`u_i=v_i=p_i`, in which case it is `1`. Thus any mismatched bit
forces total absolute correlation at most `1/2`. If all three masks
match at every bit, the sign depends only on carries. Writing `T,D`
for the sum and difference of the two signed carry-state masses, a
zero output-mask bit sends `(T,D)` to `(T,D/2)` and a one bit sends it
to `(D,T/2)`. Bit zero leaves `T=1,D=1/2`; the first one bit above
bit zero makes both magnitudes at most `1/2`, which later transitions
cannot increase. Only the bit-zero mask remains perfect. The explicit
attaining original-chain masks are `u=0x2`, `v=0x40002`, `p=0x2`:
their signed correlation is `+1/2`.

**Replay validation:** the [certificate report](../results/pressure_first_branch_walsh_full_layer.json)
compares the counter against brute force for all 4,680 mask triples
at word widths 1–4, checks all eight one-bit transition norms, and
matches both rotated and unrotated first output branches to the
original C source. These checks validate the implementation; the
matrix argument above proves the 64-bit bound.

For the full Pressure layer under a uniform 2048-bit input, its 16
chains are independent. An output mask confined to the 16 first-output
words therefore has correlation at most `2^-t` when `t` chains use
bits above their first-output LSB; the maximum over that class is
sharp. The same script evaluates each coefficient in this entire
16-chain class exactly and checks a two-chain `1/4` witness. This is
a statement about the **Pressure component under a
uniform input**, not about its input distribution inside the hash.
This is the first of two complete mask families. The extension below
covers arbitrary masks on the second output when the input mask on
`a` is zero, and all masks with only its least significant bit active.

**Second-shear extension.** For arbitrary 64-bit masks `v,p,q` and
zero mask on input word `a`, the change of variables `(a,c) -> (A,c)`
is bijective. Hence `A,c` are independent uniform words. With the
invertible linear map `g(A)=A XOR (A<<31)`, the complete coefficient is

`Corr_P((0,v),(p,q)) = Corr_ADD((v,(g^-1)^T p),q)`.

The same proved carry lemma gives a sharp nonperfect maximum `1/2`.
The only nontrivial perfect relation in this family is
`C[0] XOR c[0] XOR A[0]=0`; `v=p=q=0x2` attains `+1/2`.
Further, `C[0]=c[0] XOR A[0]` converts **any** chain mask with
second-output mask `q=0` or `q=0x1` to the first-output-only class.
The other exact LSB identity, `A[0]=a[0] XOR c[0] XOR c[17]`,
similarly removes an input mask `u=0x1`. Applying both identities
canonicalizes **every** chain mask to one with `u[0]=q[0]=0` without
altering its signed correlation.
Thus the [two-shear counter](../scripts/krakken_pressure_second_shear_walsh.py)
is exact for the union `u∈{0,0x1}` with arbitrary `v,p,q`, or
`q∈{0,0x1}` with arbitrary `u,v,p`. Every
nonperfect coefficient in the union is at most `1/2`, and the only
perfect coefficients are the four combinations of the two LSB
relations. It also computes an exact 16-chain coefficient whenever
each chain belongs to this union; `t` nonperfect chains give an upper
bound `2^-t`, attained by suitable masks.

**Replay validation:** the [updated two-shear report](../results/pressure_two_shear_affine_extended_validated.json)
contains 18,720 all-mask reduced-word brute-force checks, 200
full-width C and inverse-map checks, 4,096 exhaustive affine-LSB
canonicalization checks, and a mixed two-chain `1/4`
attaining witness. The mathematical proof is the bijective change of
variables plus the carry matrices above. The remaining unsolved
chain-mask case has, after LSB normalization, both `u≠0` and `q≠0`.

## PROVED — COMPLETE DEFINED CLASS: joint low-17 Pressure output masks

For the actual 64-bit Pressure chain, let both unrotated output masks
`p,q` be confined to bits `0..k-1`, for any `1≤k≤17`. The two low-word
outputs depend on exactly three disjoint input slices of length `k`:
`a[0:k]`, `c[0:k]`, and `c[17:17+k]`. Under a uniform unrestricted
chain input these slices are independent and uniform, with equations

`A_low = a_low + (c_low XOR c_high) mod 2^k`,
`C_low = c_low + A_low mod 2^k`.

The second equation has no `A<<31` contribution in this range.
An exact four-state signed DP retains the incoming carry for **both**
additions and sums the eight fresh input triples at each bit. For
**every** input mask supported on those three slices, the resulting
integer divided by `2^(3k)` is the exact full-chain correlation.
Explicitly, for incoming carries `(r,s)` and fresh bits `(a,c,h)`, set
`x=a+(c XOR h)+r`, `A=x mod 2`, `r'=floor(x/2)`,
`y=c+A+s`, `C=y mod 2`, `s'=floor(y/2)`. The transition from `(r,s)`
to `(r',s')` adds
`(-1)^(u_i a XOR v_i c XOR w_i h XOR p_i A XOR q_i C)`.
Starting at carries `(0,0)`, summing all four final states gives the
numerator. This recurrence counts both additions **jointly** and
includes their carry dependence.
Any input-mask bit outside those slices gives an exact zero coefficient.
The [counter](../scripts/krakken_pressure_joint_lowbit_walsh.py) is therefore a
complete arbitrary-input-mask answer for this low-output class, including
genuinely coupled two-addition masks. It does not claim a universal
bound from counting alone; the next lemma proves the sharp maximum.

**Sharp maximum, all `k≤17`.** The proof first applies to the abstract
three-independent-word map `A=a+(c XOR h)`, `C=c+A` modulo `2^k`
for **every** `k≥1`. The actual Pressure low bits instantiate this
map with `h=c[17:17+k]` for `k≤17`. Write `M_b` for the integer four-state
transition matrix of bit-mask pattern
`b=(u_i,v_i,w_i,p_i,q_i)`. Each row sums eight signed fresh-input
triples, so every absolute row sum is at most `8`. Let `j` be the
highest bit selected by either output mask. Summing the independent
fresh input bits at `j` gives zero unless their three mask bits match
the output mask: `u_j=p_j XOR q_j`, `v_j=p_j`, and
`w_j=p_j XOR q_j`; input-slice masks above `j` must be zero. This
is an exact-zero rule for all other masks. In the three nonzero
top-bit cases, the signed carry vector
is respectively

`(8,8,-8,-8)`, `(8,-8,-8,8)`, or `(8,-8,8,-8)`.

At the next lower bit, for fixed incoming carries `r,s`, the outgoing
carries are `r'=majority(a,c XOR h,r)` and
`s'=majority(c,A,s)`. Their quadratic parts in the three fresh
bits `a,c,h` are `ac XOR ah` and `ac XOR ch`; the quadratic part of
`r' XOR s'` is `ah XOR ch`. Every nonzero carry character therefore
has quadratic part equal to a product of two independent linear
forms. The lower input/output masks add only affine terms. After an
invertible linear change of variables, its Walsh coefficient is that
of `xy` plus affine terms, whose magnitude is at most `1/2`. Hence
**all four** incoming-carry components of every two-bit suffix have
magnitude at most `32=8²/2`.

The [finite-base verifier](../scripts/krakken_pressure_lowbit_half_theorem.py)
checks all `3×32=96` choices of one lower bit-mask pattern and all
four carry states. It independently enumerates the 64 two-bit input
triples for each case and checks all 12 quadratic-part ANFs.
Every additional lower bit can increase a component magnitude by at
most a factor of 8, by the row-sum bound. Induction gives
`|Corr|≤1/2` for **every** mask whose highest output bit is at least
one, for every abstract word length and hence every actual `k≤17`.
If the highest output bit is zero, the relevant one-bit truncation is
affine: only the three nontrivial perfect LSB
relations survive. Together with the trivial coefficient, these are
the **only four perfect coefficients** in the class. The bound is
sharp at every `k≥2`: masks `(u,v_low,v_high;p,q)=(3,0,2;0,2)`
give `+1/2`, including `2^50/2^51` at `k=17`. The
[proof report](../results/pressure_lowbit_half_theorem_algebraic_validated.json) records
the 96-case base, all transition row norms, and the 17-bit witness.
This proof is an induction using a small exact base table; it does
not extrapolate an empirical trend.

**Replay validation:** the [joint-carry report](../results/pressure_joint_lowbit_walsh_validated.json)
compares all 33,824 mask quintuples for `k=1,2,3` against independently
computed full Walsh spectra, reproduces the earlier `C[5]` value
`-85/256`, and matches the original C low-17 output equations on
1,000 full-width inputs. One exact coupled `k=17` example has signed
correlation `-357913941/1073741824` for masks
`(u,v_low,v_high;p,q)=(2^16,0,2^16;0,2^16)`.

**Independent exhaustive validation through six bits.** The
[all-mask verifier](../scripts/krakken_pressure_lowbit_max_certificate.py)
computes the full integer Walsh transform for each output-mask pair
at every `k=1,...,6`. Its
[certificate report](../results/pressure_lowbit_max_k6_certificate.json) exhausts
`1,108,378,656` mask quintuples, of which `1,073,741,824` belong
to `k=6`. In that six-bit class, exactly `1,060,219,244` of those
coefficients are zero, even among masks on the relevant input slices.
At `k=1`, all nonperfect correlations are zero. For each
`k=2,...,6`, the maximum absolute nonperfect correlation is
**exactly `1/2`**; the only perfect coefficients are the four known
affine LSB combinations. An attaining witness at every `k≥2` is
`(u,v_low,v_high;p,q)=(3,0,2;0,2)`, with correlation `+1/2`.
The reduction to the full 64-bit chain is mathematical. This finite
exhaustion independently validates the induction's first six widths.
The report records a SHA-256 digest of each full Walsh spectrum so
an independent replay can check the exact enumeration. Coefficients
are serialized as little-endian signed 32-bit integers; at `k=6`
their magnitudes are at most `2^18`, so this representation cannot
overflow.

For the uniform full 2048-bit Pressure input, the 16 chains factor.
If every chain's unrotated output masks lie in low 17 bits and
`t` chains use nonperfect coefficients, the full-layer magnitude is
at most `2^-t`. This is sharp for every `1≤t≤16` by placing the
attaining witness in exactly those chains. Odd-chain output rotations
only relabel the physical mask positions. This is a component theorem
under uniform Pressure input, not a complete-round hash-hull bound.

There is also an **exact-zero pruning rule** in that same uniform-input
model. The pairs `(a,A)`, `(c,A)`, `(c,C)`, and `(A,C)` are each jointly
uniform over 128 bits. Therefore a nonzero first-output-only Pressure
mask can correlate only if **both** input-word masks are nonzero; any
chain that violates this rule zeros the entire 16-chain coefficient.
Those zero coefficients remove paths exactly from the full-state
Fourier hull expansion, although they do not bound the remaining sum.
The [pairwise-independence proof report](../results/pressure_pairwise_independence_validated.json)
and [replay script](../scripts/krakken_pressure_pairwise_independence.py) give the
invertible-map argument and implementation checks.

## PROVED — COMPLETE DEFINED CLASS: 16 first-round hash output masks

This claim concerns the **actual valid 159-byte first absorb block**
with XRBD enabled, rather than a uniform Pressure input. For each
`c=0,...,7` and `h=0,1`, let `i=4c+h` and `j=i+2`. Define a two-bit
mask `beta_(c,h)` on the state **after one complete round**: it selects
lane `(7i) mod 32`, bit `11+7h`, and lane `(7j) mod 32`, bit
`11+19h`. These positions include Pressure's odd-chain output
rotations and the final round shuffle. For every message mask
`alpha∈GF(2)^1272` and every one of these 16 output masks,

`|Corr(alpha·m, beta_(c,h)·F_1(m))| ≤ 2^-174`.

The bound is uniform over **all** 159-byte messages and **all**
message input masks; it is not a sampled correlation or a selected
linear trail. It is an upper bound, not an assertion that `2^-174`
is attained.

**Proof.** Within each Pressure chain, the exact identity
`A[0] XOR C[0]=c[0]` holds pointwise. The output rotations, round
constant XOR, and final shuffle carry `beta_(c,h)` back to the
single Pressure-input bit `c[0]`, up to a fixed sign. XRBD is linear,
so its transpose gives a fixed post-Chi1 mask. For that mask, let
`S` be its active serial-Chi components, `r` the rank of the map
from the 1272 message bits to their selected pre-Chi inputs, and
`M_i` the exact **unnormalized** maximum local Walsh coefficient for
component `i`. The affine-image Fourier expansion gives, for every
message mask,

`|Corr| ≤ min(1, (product over i∈S of M_i) / 2^r)`.

If a message mask is outside the row span of the selected-input map,
its correlation is exactly zero. Otherwise the affine-image
indicator expands into `2^(16|S|-r)` characters; bounding each
factored Chi coefficient by the product of its local maxima gives
the displayed inequality. This accounts for the rate restriction
and sums every relevant intermediate mask. It does **not** assume
Pressure inputs are uniform. Applying the exact integer formula to
all 16 masks gives the following certified power-of-two ceilings:

| `c` | `h=0` | `h=1` |
|---:|---:|---:|
| 0 | `2^-216` | `2^-250` |
| 1 | `2^-299` | `2^-232` |
| 2 | `2^-252` | `2^-289` |
| 3 | `2^-354` | `2^-189` |
| 4 | `2^-276` | `2^-214` |
| 5 | `2^-313` | `2^-240` |
| 6 | `2^-325` | `2^-174` |
| 7 | `2^-252` | `2^-184` |

The [replay script](../scripts/krakken_hash_round1_pressure_affine.py) and
[source-pinned report](../results/hash_round1_pressure_affine_48_validated_v3.json)
also audit the other 32 one-chain exact-affine Pressure masks. The
16 masks above form the **complete defined class for this theorem**;
some of the other 32 receive vacuous bounds from this technique.
Validation included independent rank calculations for every mask in
the class, ten direct full-`2^16` local Chi Walsh transforms, and
original-C parity checks through XRBD, Pressure, the round suffix,
and valid padded messages. Those checks validate the implementation;
the pointwise identities and affine-image argument prove the claim.
This is a one-round, 16-output-mask theorem, not a bound on all
output masks or eight-round hash security.

## PROVED — COMPLETE DEFINED CLASS: a 31-mask first-round output subspace

Using the `beta_(c,h)` two-bit masks defined above, let `V` be the
five-dimensional GF(2) subspace generated by

`beta_(0,0), beta_(1,0), beta_(2,0), beta_(5,0), beta_(6,0)`.

These generators act on distinct Pressure chains, so they are
independent and `V` has exactly 31 nonzero masks. For **every**
`beta∈V\{0}` and every `alpha∈GF(2)^1272`, with uniform valid
159-byte first-block messages,

`|Corr(alpha·m, beta·F_1(m))| ≤ 2^-162`.

**Proof.** The exact Pressure identity `A[0] XOR C[0]=c[0]` holds
simultaneously on each of the five disjoint chains. XORing any
nonempty subset therefore pulls its round-output parity to a fixed
Pressure-input mask, up to a constant. Applying XRBD's exact transpose
and the rate-aware affine-image bound from the preceding theorem
gives `min(1, product_i M_i / 2^r)` for **every** message mask. The
[subspace verifier](../scripts/krakken_hash_round1_affine_subspace.py) evaluates
this exact integer upper bound for all 31 nonzero subsets. Its
[source-pinned report](../results/hash_round1_AC_coordinate_subspaces_128_validated_v3.json)
records each exponent; the weakest two ceilings are `2^-162`.
The report combines the previously certified single- and pair-mask
records with 84 newly computed higher-weight records, **31**
independent rate-projection rank checks, ten direct full-`2^16` local
Chi Walsh checks, and three original-C parity checks per new mask.
It also verifies that the 31 output masks are distinct. The proof is
the pointwise identities and exact affine-image inequality; the C
checks validate the mask transport and implementation.

Let `X(m)` be the five output parities selected by the generators of
`V`. For any affine message subspace `H` of codimension `d`, with `m`
uniform on `H`, its nonzero conditional Fourier coefficients are
signed sums of `2^d` correlations already bounded above. Parseval
and Cauchy–Schwarz give the complete five-bit distribution bound

`TV(Law(X(m) | m∈H), Uniform({0,1}^5)) ≤ (sqrt(31)/2)·2^(d-162) < 2^(d-160)`.

In particular, after **any 128 independent linear message
constraints**, the five selected first-round output parities are
within `2^-32` of uniform. This is a corollary of the proved all-mask
bound, not an additional sampling claim.

This is a **complete five-dimensional output-mask class**, not a
claim about arbitrary 2048-bit output masks or later rounds. The
`2^-162` ceiling is an upper bound, with no assertion of attainment.

## PROVED — COMPLETE DEFINED CLASS: a 63-mask first-round output subspace

Let `W` be the six-dimensional GF(2) subspace generated by

`beta_(0,0), beta_(1,0), beta_(2,0), beta_(4,0), beta_(5,0), beta_(6,0)`.

The `beta_(c,h)` masks are defined in the preceding first-round
theorem. These six generators are independent, so `W` contains 63
nonzero output masks. For **every** `beta∈W\{0}` and every
`alpha∈GF(2)^1272`, under uniform valid 159-byte first-block
messages,

`|Corr(alpha·m, beta·F_1(m))| ≤ 2^-76`.

**Proof.** The six exact Pressure identities combine pointwise for
every nonempty generator subset. The same affine suffix, XRBD
transpose, and rate-aware Chi affine-image inequality used above
therefore apply to each of the 63 masks. The
[subspace verifier](../scripts/krakken_hash_round1_affine_subspace.py) checks all
63 exact integer inequalities; the weakest calculated ceilings are
for generator-index subsets `{2,8}` and `{0,2,8}`, where
`index=2c+h`. The [source-pinned certificate](../results/hash_round1_AC_coordinate_subspaces_76_validated_v2.json)
combines the previously certified single- and pair-mask records with
401 newly computed higher-weight records from the full coordinate
search. It verifies all 63 output masks are distinct, recomputes
**all 63** selected rate-projection ranks independently, checks ten
local maxima by direct full-`2^16` Chi Walsh transforms, and replays
each new higher-weight mask three times through original C. The
pointwise identities and affine-image inequality prove the bound;
the independent calculations and C replays validate its certificate.

There is also a **six-bit distribution corollary**. Let `Y(m)` be the
six output parities selected by the displayed generators. Every
nonzero Fourier coefficient of `Y(m)` is at most `2^-76` in absolute
value. Parseval and Cauchy–Schwarz therefore give

`TV(Law(Y(m)), Uniform({0,1}^6)) ≤ (sqrt(63)/2)·2^-76 < 2^-74`.

The all-message-mask quantifier gives a stronger conditional form.
Let `H` be **any nonempty affine subspace** of the 1272-bit message
space with codimension `d`, and draw `m` uniformly from `H`. Expanding
the indicator of `H` in its `2^d` linear characters bounds each
nonzero Fourier coefficient of `Y|H` by `2^d·2^-76`. The same
Parseval argument gives

`TV(Law(Y(m) | m∈H), Uniform({0,1}^6)) ≤ (sqrt(63)/2)·2^(d-76) < 2^(d-74)`.

For example, after imposing **any 64 independent linear constraints**
on the message, the six output parities remain within `2^-10` of
uniform. These bounds cover every statistical test on the selected
six-bit output projection under the stated uniform input domains.
They concern **one**
round and this projection, not arbitrary output masks, later rounds,
or collision/preimage security. Neither the `2^-76` correlation
ceiling nor the distribution bound is claimed to be sharp.

## PROVED — COMPLETE DEFINED CLASS: LIN-RATE-004 eight-bit nonlinear-Pressure bridge after one round

Let `P_1` be the first complete scalar round. For any fixed 2048-bit
state `x_*`, vary all 1272 bits of a valid 159-byte message through
the embedding `J`, and extract from `P_1(x_* XOR Jm)` lane 7 bits
18–21 and lane 21 bits 30–33. For **every** message mask and **every**
nonzero mask on these eight output bits, the absolute correlation is
at most `2^-246`. This includes 252 output masks that depend
nonlinearly on Pressure carries. No uniform-Pressure-input assumption
is used.

The proof expands **all** terms of the exact 12-input-bit Pressure
spectrum, pulls each mask backward through XRBD, and applies an
effective-coordinate affine-image bound to the actual message
distribution. The [complete certificate](../discovery/pressure_bridge_k4_pilot.json)
contains all 255 output-mask bounds and 1,375 contributing input
masks; its largest upper bound is at output mask `0x94` and is below
`2^-246`. The [separate audit](../discovery/pressure_bridge_k4_audit.json)
recomputes spectra, ranks and rational inequalities and checks
original-C output-bit transport. Fresh producer and audit replays were
byte-identical to both saved artifacts. The
[full proof](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) states the
analytic lemma and source-pinned finite obligations.

For any affine message subspace of codimension `d`, the eight-bit
projection has total-variation distance at most
`min(1,sqrt(255)/2·2^(d-246))` from uniform. In particular, any
128 independent affine constraints leave it within `2^-115`.
The eight coordinates lie outside the first 256 digest bits. This
does not bound other output masks, later rounds, or hash collision
and preimage attacks; `2^-246` is an upper bound, not a sharp
correlation or security-bit estimate.

## PROVED — COMPLETE DEFINED CLASS: valid-message algebraic degree through eight rounds

Here degree means algebraic normal-form degree as a Boolean function
of the **1272 free bits of a valid 159-byte message**, with the `0x86`
pad byte and initial capacity fixed. Let `F_r(m)` be the complete
2048-bit state after `r` rounds. For every `r=1,...,8`, define its
first-32-byte projection as the reduced-round digest projection; only
`r=8` is the deployed one-block digest.

The [source-pinned audit](../results/degree_multiround_claims_audit.json) certifies:

| Output class | Proved coordinate degree |
|---|---:|
| 32 shuffled Pressure-output LSB bits of `F_1` | **exactly 13**, each |
| Other 2016 bits of `F_1` | **at least 20**, each |
| All 2048 bits of each `F_r`, `r=2,...,8` | **at least 20**, each |
| First-32-byte projection of each `F_r`, `r=1,...,8` | vectorial degree **at least 24** |

The 32 exact-degree bits are, for every chain `c=0,...,7` and half
`h=0,1`, the shuffled outputs of `A[0]` and `C[0]` from Pressure
lanes `i=4c+h` and `j=i+2`. Their state-bit indices are
`64*((7i) mod 32)+11+7h` and `64*((7j) mod 32)+11+19h`.
Four of these land in the 32-byte projection, at bit indices
`11,94,139,210`.

**Upper-bound proof for those 32 bits.** Exhaustive ANF calculation
over all `2^16` inputs of the two-byte serial-Chi component gives
degree 7 for each first-output-byte coordinate and 13 for each
second-output-byte coordinate. The preceding first-round layers are
affine in message bits, XRBD is linear, and Pressure's bit-zero
identities are carry-free:

`A[0]=a[0] XOR c[0] XOR c[17]`, `C[0]=a[0] XOR c[17]`.

The round constant and final shuffle are affine. Thus all 32
specified output bits have degree at most 13. The
[serial-Chi degree certificate](../results/serial_chi_16bit_degree_validated.json)
and [C mask-layout audit](../results/degree_hash_round1_lowbits_mapping_validated.json)
record the local ANF degrees and carry-free identities.

**Attaining and lower-bound certificates.** Eight 13-dimensional
valid-message cubes were evaluated; seven attaining witnesses give a
nonzero derivative for **each** of the 32 bits. Every attaining cube
was replayed completely through original
C, proving their lower bound 13. The
[32-bit certificate](../results/degree_round1_pressure_lsb_all32_exact13_validated.json)
records the base messages, independent direction vectors, and full
derivatives. Twelve 20-dimensional coordinate cubes plus seven
20-dimensional dense-direction cubes cover the other 2016 bits of
`F_1` and all 2048 bits of each `F_2,...,F_8`. Their
[baseline](../results/degree_hash_digest_allcoords_d20_validated_v2.json) and
[completion certificate](../results/degree_fullstate_allcoords_d20_validated.json)
record a nonzero order-20 derivative for every claimed coordinate.
One 24-dimensional valid-message cube gives a nonzero derivative in
the first 32 bytes after **each** round; its
[certificate](../results/degree_hash_cube24_validated_v3.json) proves the
vectorial lower bound 24 for every reduced-round projection.

The large-cube evaluator replaces the source's constant-time S-box
loop with the same 256-entry byte table. This is an exact
implementation substitution: the original per-byte equality mask
selects exactly the table entry whose index equals the input byte,
without inter-byte carry. The helper checks 256 Chi states and 16
eight-round states against original C; full smaller cubes are also
cross-checked against original C. The
[combined audit](../scripts/krakken_degree_multiround_audit.py) verifies source
hashes, independent cube directions, stored nonzero derivatives,
and complete coordinate coverage. Full replay of a large cube is
available with the producing scripts.

**Interpretation.** The exact-degree-13 class yields genuine
first-round higher-order integral structure: every order-14
derivative of those 32 bits is zero. The degree-20 and degree-24
lower bounds rule out globally lower-degree Boolean coordinates in
their stated classes. They do not rule out selected-cube integrals,
other distinguishers, or attacks on the eight-round hash.

## PROVED — DEFINED UNRESTRICTED ZERO-SUM CLASS: a four-state square loses all perfect output balances by round two

Fix the serial-Chi component square `01d6, 01d7, 0404, 0405`, whose
input XOR and output XOR both equal zero. Embed it at one serial-Chi
byte cell, hold every other pre-Chi component at an arbitrary common
background, and invert the linear round prefix. The resulting four
unrestricted permutation inputs XOR to zero. Their post-Chi and
post-XRBD full states XOR to zero. The 32 shuffled Pressure-output
affine coordinates XOR to zero after one complete round for **every**
background. Thus the one-round projected zero sum is exact.

At each of the **128** byte cells, at most **18** original-C
background witnesses suffice to show that no individual output bit
is balanced for every background after two complete rounds. At the
representative cell `(0,0,0)`, **2052** backgrounds give 2048
linearly independent two-round four-state XOR sums. It follows that
**no nonzero 2048-bit output mask** is balanced for every background
in that representative family at round two. This is a finite
certificate for a universal exclusion over the defined family, not
a random-sampling inference.

The [all-cell certificate](../results/krakken_zero_sum_allcells_validated.json),
[full-rank certificate](../results/krakken_zero_sum_square_validated.json), and
[independent C replay](../results/krakken_zero_sum_square_audit_validated.json)
pin the C source, specify all deterministic inputs, and validate
the round-two result. The [theorem program](KRAKKEN_SECURITY_THEOREMS.md)
states the construction and proof. The class uses unrestricted states;
its reachability from a valid padded message has not been established.
The result does not exclude other two-round or higher-order zero sums.

## PROVED — HASH-REACHABLE ZERO-SUM CLASS: 14-cube boundary and fixed-cube round-two exclusion

For every affine cube of **at least 14 independent directions** in
the valid 159-byte first-block message domain, the XOR of all
2048-bit states is zero after Chi1 and after XRBD1. Every serial-Chi
output coordinate has degree at most 13 in its 16-bit input; the
pre-Chi mapping is affine in the message, and XRBD is linear. The
same argument plus Pressure's 32 exact affine output bits proves
that those 32 shuffled state coordinates are balanced after one
complete round for every such cube.

The **dimension-14 guarantee is sharp** at those internal
checkpoints. The rate-to-one-Chi-component projection has full rank
16, so 13 valid-message directions can be chosen to isolate a
nonzero degree-13 ANF monomial in the second Chi output byte. Their
13th derivative is one for every base. The
[source-pinned 13-cube witness](../results/krakken_hash_chi_cube_threshold_validated.json)
records the explicit directions and nonzero full-state sums after
Chi1 and XRBD1; an
[independent original-C audit](../results/krakken_hash_chi_cube_threshold_audit_validated.json)
replayed all 8192 messages. Thus the all-cube full-state zero-sum
statement holds for every dimension `d>=14` and fails at `d=13`.

Fix the 14 coordinate directions at message bit indices `0..13`.
Among all base messages, **exactly those 32** coordinates have a
universal one-round balance; **no** coordinate has a universal
two-round balance. Eleven source-pinned base messages are enough to
make each of the other 2016 one-round coordinates and each of the
2048 two-round coordinates nonzero in at least one complete-cube
XOR sum. The [certificate](../results/krakken_hash_zero_sum_14cube_validated.json)
stores every base and full-state sum. The
[independent original-C replay](../results/krakken_hash_zero_sum_14cube_audit_validated.json)
checked all 180,224 cube vertices through both round counts and
verified a complete post-Chi/post-XRBD zero sum. The
[exact Chi ANF certificate](../results/serial_chi_16bit_degree_validated.json)
supplies the algebraic bound.

The all-cube checkpoint theorem and fixed-direction complete-round
theorem have different quantifiers. The round-two exclusion applies
to **coordinate bits of this one fixed direction set**; it does not
exclude all possible integrals or non-coordinate masks.

## PROVED — COMPLETE HASH-MESSAGE BYTE-CUBE CLASS: round-two coordinate exclusion

For every byte position `p=0,...,158` and output-state bit
`j=0,...,2047`, there is a valid 159-byte base message such that
varying byte `p` through all 256 values gives a **nonzero** XOR sum
at bit `j` after two complete rounds. Hence no coordinate bit is
balanced for every base in any of the 159 one-byte coordinate-cube
families. The [certificate](../results/krakken_byte_cube_all159_validated.json)
stores 1,946 explicit base cubes, with at most 18 needed for any one
position. An [independent original-C audit](../results/krakken_byte_cube_all159_audit_validated.json)
replayed all 498,176 valid-message vertices through rounds one and
two and matched every 2048-bit sum. The finite witnesses jointly
cover all 325,632 position/output-coordinate targets; they do not
classify other cube directions or non-coordinate output masks.

For the **first-byte** cube, a stronger
[full-rank certificate](../results/krakken_byte_cube_rank_p0_validated.json)
gives 2,048 round-two cube sums with GF(2) rank 2,048. Hence every
nonzero full-state output mask has a nonzero cube sum at some valid
base: no linear output mask is universally balanced in this one
fixed direction family after round two. An
[independent original-C audit](../results/krakken_byte_cube_rank_p0_audit_validated.json)
replayed the 524,288 selected valid-message vertices, matched both
round sums, and recovered full rank with the opposite pivot order.
This stronger all-mask statement is proved for byte position zero,
not for all 159 positions.

The new [from-scratch exact local division model](../scripts/krakken_division_exact_byte0.py)
closes the **round-one side** too. For the fixed first-byte cube, the
space of full-state linear output masks balanced for every valid base
has **exact dimension seven after one round and zero after two**.
For round one, exhaustive eighth derivatives of all 128 serial-Chi
cells over their complete 16-bit local domains, followed by exact
affine mask propagation through XRBD and Pressure's 32 carry-free
output bits, construct seven independent universally balanced masks.
The saved original-C cube sums have rank 2041 at round one, proving
there cannot be an eighth; their rank 2048 at round two excludes every
nonzero mask there. The [local certificate](../results/krakken_division_exact_byte0_validated.json)
contains the seven explicit masks. An [independent audit](../results/krakken_division_exact_byte0_audit_validated.json)
recomputed all local derivatives and both ranks, and checked the Chi
formula against original C. This transition is exact for the stated
cube family; other directions and nonlinear output predicates are
outside its scope.

## PROVED — COMPLETE DEFINED SUBSPACE CLASS: maximal hull after Chi1

For each of the 159 message-byte coordinate subspaces, evaluate all
256 valid padded messages with every other message byte zero. Their
2,048-bit state images have affine-hull dimension **8 before Chi1**
and the maximum possible dimension **255 immediately after Chi1**.
The rank remains 255 after complete rounds one and two. The
[original-C certificate](../results/krakken_subspace_byte_hull_validated.json)
covers all positions and ten checkpoints; an
[independent original-C audit](../results/krakken_subspace_byte_hull_audit_validated.json)
replayed all 40,704 messages with reversed enumeration, a different
affine origin, and opposite pivot order. Thus none of these byte
subspace families can map **every coset** into an affine output space
of dimension at most 254 at those checkpoints: its zero-base coset
already has rank 255. This is a complete exclusion for that
low-dimension trail class, not a claim about other input subspaces,
special bases, or distinguishing advantage.

## PROVED — COMPLETE THETA-CANCELLING SUBSPACE FAMILY: Pressure1 closes the hull

Restrict valid messages to the complete 16-bit plane in bytes 40 and
56, all other message bytes zero. The 256 diagonal cosets
`(m[40],m[56])=(delta XOR t,t)` cancel Theta parity in their varying
directions. **Every** coset has post-Chi1 affine-hull rank below 255:
two have rank 238, two rank 246, one rank 251, eleven rank 252,
94 rank 253, and 146 rank 254. XRBD preserves these ranks because
it is invertible linear. **Every** coset reaches the maximal rank
255 after Pressure1 and retains it after complete rounds one and
two. A controlled XRBD-off variant also reaches 255 at Pressure1
in every coset. The [XRBD-on certificate](../results/krakken_subspace_theta_pair_cosets_validated.json)
and [audit](../results/krakken_subspace_theta_pair_cosets_audit_validated.json),
plus the [XRBD-off certificate](../results/krakken_subspace_theta_pair_noxrbd_validated.json)
and [audit](../results/krakken_subspace_theta_pair_noxrbd_audit_validated.json),
each cover all 65,536 valid messages in this defined two-byte plane.
Thus Pressure1, rather than XRBD, is the first layer that closes
this family's **low-rank affine-hull** structure. XRBD still expands
its byte support substantially. Other message planes and
255-dimensional output trails are not classified by this claim.

## PROVED — REBOUND COMPONENT CLASS AND FIRST-BLOCK RATE GATE

For one serial-Chi cell, a diagonal input byte difference `(d,d)`
always cancels at the first S-box input. A prescribed second-output
byte difference `eps` has exactly `256*DDT_S(d,eps)` matching local
bases, at most **1,024 of 65,536** for this S-box. The selected
`(d,eps)=(101,1)` transition attains 1,024. Every one of the
`128*255=32,640` possible one-byte second-output differences
activates **all 32 lanes and at least 48 bytes** after the current
XRBD layer (maximum 196 bytes). The
[inbound/XRBD certificate](../results/krakken_rebound_inbound_validated.json)
and [independent original-C audit](../results/krakken_rebound_inbound_audit_validated.json)
cover the complete stated component and support classes.

In the **backward outbound**, the current linear prefix has full
rank 2048, so each one-cell diagonal pre-Chi difference has a
unique unrestricted permutation-input preimage. Across all
`128*255=32,640` site/`d` cases, those input differences activate
**all 32 lanes and 40–180 bytes**. The selected `(site,d)=((0,0,0),101)`
preimage has 116 active bytes. The
[inverse-prefix certificate](../results/krakken_rebound_backward_validated.json)
and [independent original-C audit](../results/krakken_rebound_backward_audit_validated.json)
recompute the full 2048-bit inverse and every support count.

This inbound family is **unreachable from a nonzero valid first-block
message difference when confined to one Chi cell**. The C-derived
rate-to-pre-Chi map, projected outside either input byte of each
cell, has full column rank `1272/1272` for **all 128 cells**.
Serial Chi is cellwise bijective, giving the same exclusion for
differences confined to one post-Chi output cell. The
[rate-gate certificate](../results/krakken_rebound_rate_gate_validated.json)
and [independent original-C rank replay](../results/krakken_rebound_rate_gate_audit_validated.json)
give the complete first-block theorem. The local matching and
outbound examples therefore concern unrestricted internal
permutation states; multi-cell hash-reachable rebound structures
remain open.

## PROVED — COMPLETE FIRST-ORDER DEPENDENCY CLASS: both rounds

For every message bit `i`, output bit `j`, and `r=1,2`, at least one
valid base message satisfies `F_r(m)[j] != F_r(m XOR e_i)[j]`.
The [certificate](../results/krakken_bit_dependency_all1272_validated.json)
contains 16,946 base contexts, at most 21 for any input bit; an
[independent original-C audit](../results/krakken_bit_dependency_all1272_audit_validated.json)
verified all 67,784 complete-round evaluations and coverage. This
is a structural dependency statement, not a quantitative avalanche
bound. Its full coverage after round one means it does not single
out round two as the first point of bitwise dependency.

## OPEN: unrestricted complete-round linear-hull maximum

For complete rounds, the desired theorem is a certified bound on
`max_{alpha!=0,beta!=0} |Corr(alpha·m,beta·F_r(m))|` for each `r`,
especially `r=8`. No useful numerical value has been proved for that
unrestricted maximum.
The one-round theorems above cover specified output masks, not this maximum.
The exact rate-restricted hull is a signed sum over `2^776`
full-state input masks for each `(alpha,beta)`; all intermediate
round-mask paths are already contained within each term. Controlling
that signed sum, including Pressure carries, is the outstanding task.
The [theorem program](KRAKKEN_SECURITY_THEOREMS.md) gives the formula
and the current mathematical obstruction.

These statements are offered for review as claims about specified
linear properties, not as collision-resistance, preimage-resistance,
or 128-bit-security claims for the concrete hash.

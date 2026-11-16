# KRAKKEN_RESEARCH_11 — Attack theorem ledger

**2026-11-15 addition:** the [VULNS(5) review](#vulns5-review--five-cell-h159-exclusion-and-complementary-evidence-2026-11-15) below adds a replayed five-cell H159 `[6,1]` exclusion and a restricted eight-round activity floor of 20. The general H159 floor remains 19.

## Import record and result index — 2026-11-14

This document incorporates **all eight entries and their complete explanations**
from `/home/user/attack/ATTACK_THEOREM_LEDGER.md`, including proofs, experiment
designs, numerical results, limitations and reproduction instructions. The
import changes the document title, adds this record, relocates artifact links,
and adds the working-directory step to shell commands. The original ledger is
preserved [unchanged here](reproduce/attack_ledger_20261114/snapshot/ATTACK_THEOREM_LEDGER.md).
No supplied attack entry is omitted or reduced to a summary.

| Entry | Main recorded result | Scope and evidence type |
|---|---|---|
| K9-001 | Dense 9D kernel cube: 32 universal R1 balanced mask directions; none at R2 | Fixed H159 cube directions; analytic inclusion and finite spanning certificate |
| BS-001 | 49,872 of 131,072 shared-unit quartets retain R1 zero XOR; none retain it at R2 | Specified unrestricted finite family; exact enumeration and spanning |
| DL-STAT-001 | Exact R1 correlation -1/8; two selected R2 predictors show no significant held-out bias | Fixed unrestricted difference; exact R1 formula and simultaneous 99% statistical intervals |
| RX-001 | Exact near-perfect R1 rotational relation; no detected selected R2 bias; no universally constant R2 linear RX parity | Rotation 32 on unrestricted states; analytic, statistical and finite-rank results |
| SUB-001 | 48/128 input flats compress below hull dimension 255 at R1, minimum 68; all reach 255 at R2 | 128 fixed unrestricted 8-flats; exhaustive finite-set ranks |
| REB-001 | Constructive inbound matches; 1,006 weak R2 byte matches; full-pattern count zero | Fixed conditioned unrestricted class; exact construction, finite witnesses and conditional statistical bounds |
| REB-001-R3 | Two pairs retain the weak byte match at R1–R3; R3 universal constant parities excluded | Same finite cohort; explicit existence witnesses and spanning |
| REB-001-R4 | Neither tracked consecutive chain persists to R4; 1,000 R4 endpoint matches and three R3/R4 matches remain | Same finite cohort; explicit transitions and R4 spanning certificate |

These results retain their original quantified domains. Most entries use
unrestricted permutation inputs; K9-001 uses valid 159-byte sponge messages.
Partial byte matches, finite-family exclusions, exact parity exclusions and
statistical confidence bounds answer different questions. None supplies a new
general eight-round collision/preimage security-bit bound. In particular, the
R3 partial survivors and R4 endpoint matches must not be described as complete
blocking of rebound attacks.

### Preservation and verification during this import

The full supplied directory is preserved under
[reproduce/attack_ledger_20261114/](reproduce/attack_ledger_20261114/README.md):
**190 files, 453,462,665 bytes**, including all sources, raw draws, plans,
reports, binary witness/rank streams, audit programs and historical logs.
The original ten ledgers are retained as provenance snapshots; they do not
replace the current project ledgers. In particular, their research 07/10 copies
predate the subsequent bounds-workspace integration. All three implementation
source files match the current project byte for byte.

Fresh import checks verified all **175** entries in the supplied manifest and
all **190** files in the import manifest; **23** GCC/Clang binary-stream pairs
match. The [read-only certificate checker](reproduce/attack_ledger_20261114/verify_import.py)
recomputed eight ordinary/augmented rank certificate pairs with both pivot
orders, all 256 subspace output hull ranks, boomerang defect counts/minima,
differential-linear validation counts and its confidence radius, and the
rebound marginal/joint/cumulative counts. See
[VERIFICATION.json](reproduce/attack_ledger_20261114/VERIFICATION.json).

Additionally, the supplied **R4 audit was rerun** in a separate working copy:
all 262,144 original pairs at R4 reproduce the stored compiler observations;
69 pairs pass independent Python checks at depths 1–4; all five explicit
transition witnesses pass the direct original APIs; and R4 ranks are again
2048/2049. See [fresh replay log](reproduce/attack_ledger_20261114/r4_replay.log)
and [fresh audit record](reproduce/attack_ledger_20261114/replay/attack_ledger/rebound_r4/audit.json).
The original frozen snapshot is unchanged. Other supplied producer/audit claims
below are inherited from the preserved research unless covered by the fresh
checks just listed; this import did not rerun every original producer or audit.
These are reproducibility and implementation checks, with no new random sample
or additional external peer review.

### Reproduction location

Every shell example below begins by entering the **working copy**. Its relative
`attack_ledger/` paths then resolve correctly alongside the pinned original
sources. Saved artifact links point to the frozen snapshot. Audit programs can
rewrite their working outputs; use the working copy for reruns. One-time
producers may refuse to overwrite frozen plans, as their entries explain.
Further usage details and checksums are in the reproduction README.

---

## Imported ledger

Started 2026-11-14. Canonical scalar, header, AVX2 and ten research documents
are preserved unchanged. Ledger identifiers here are separate from historical
WORK/NOTE identifiers.

## Research review and selection

The ten supplied research documents already record differential, truncated
differential, linear, differential-linear, rotational/RX, boomerang, integral,
division-property, zero-sum, subspace, rebound, algebraic, related-round/slide,
matching-label and collision work. A claim that one of these broad families
has never been tried would be misleading. Older open questions sometimes have
later closures: research 07/08/10 take precedence over obsolete campaign prose.

The following specific extensions remain outside recorded closures:

| Candidate | Recorded boundary | Disposition here |
|---|---|---|
| Other kernel-directed integral subspaces | Research 01, `INT-KERNEL-001`: universal R1 inclusion for dimensions 8–248; exact R2 all-mask exclusion only for one saved 8D cube | Test a newly specified dense 9D cube below |
| Shared-chain coordinated boomerangs | Research 01, `BOOM-MULTI-001`, and research 09 §8: disjoint-chain construction tested; general shared-chain carry matching open | BS-001 below tests a finite same-unit basis-pair family |
| Nonperfect differential-linear continuation | Research 09 §8 recommends fresh validation after mask selection; perfect-mask exclusions do not settle bias | DL-STAT-001 below tests an exact nonperfect R1 predictor and two held-out R2 masks |
| Rotational carry predictor | Research 01 `ROT-002` and research 09 §5: strong R1 residual biases; historical coordinate screens do not settle every R2 relation | RX-001 below derives one exact near-perfect R1 bias and tests R2 |
| Chosen affine input flats | Research 01 `SUBSPACE-001/002`: prior coordinate and Theta-cancelling H159 geometries | SUB-001 below tests 128 inverse-prefix diagonal unrestricted flats through complete R1/R2 |
| Rebound inbound/outbound matching | Research 01 `REBOUND-001/002`: exact local match and support/reachability results | REB-001 tests R1/R2; R3 and R4 extensions track endpoint matches and consecutive partial survivors |
| H159 five-/six-cell `A1=6, A2=1` differential activity | Research 10 §16 closes the four-cell class only | Not tested here |

The precise nine-direction cube below was not found recorded in the supplied
corpus. This is an unrecorded **instance of an existing integral attack**, not
a newly invented attack family. The corpus does not establish what was tried
in unpublished work. Referenced historical external evidence packages are not
present in this workspace; this entry generates its own evidence.

## K9-001 — dense nine-dimensional H159 kernel integral

**Result: succeeds at complete round 1; no universal linear-mask balance
continues to complete round 2 for this fixed direction subspace.**

**Domain.** Exactly 159 message bytes, byte 159 fixed to `0x86`, bytes 160–255
zero, little-endian words. Let `F_r` mean the first `r` complete original indexed
rounds, including Pressure, constants and Ink Cloud. This reduced-round
experiment is not the production eight-round hash API.

Let `L` be Theta → MDS → Rho → Pi. At each serial-Chi pair define the
first-call input as `a XOR rotl64(b,32)`. The 1024-bit linear map X from
1272 message-difference bits to all these inputs has rank 1024 and kernel
K of dimension 248. Our nine independent message directions lie in K.
Their complete hexadecimal encodings and deterministic construction are in
[the report](reproduce/attack_ledger_20261114/snapshot/attack_ledger/gcc_report.json) and [generator](reproduce/attack_ledger_20261114/snapshot/attack_ledger/run.py).
They are dense SHAKE256-selected combinations of a deterministic kernel basis;
there is no optimization or search over cubes based on their R2 outcomes.

For the fixed 9D subspace D and every valid base message m, define

`S_r(m) = XOR_{d in D} F_r(m XOR d)`.

Define `U_r = { beta : beta · S_r(m) = 0 for every valid m }`.
Here beta is an arbitrary 2048-bit binary mask, not just a coordinate bit.

**Exact computer-assisted statement:**

| Quantity | R1 | R2 |
|---|---:|---:|
| Vertices per cube | 512 | 512 |
| Saved base messages | 2080 | 2080 |
| Rank of complete 2048-bit cube sums | 2016 | 2048 |
| Rank of augmented vectors `(S_r(m),1)` | 2017 | 2049 |
| Dimension of universal balanced output-mask space `U_r` | **32** | **0** |
| Dimension restricted to first 256 digest-position bits | **4** | **0** |

At R1 the exact mask space is the span of unit masks at positions

```
11,94,139,210,267,350,395,466,523,606,651,722,779,862,907,978,
1035,1118,1163,1234,1291,1374,1419,1490,1547,1630,1675,1746,1803,1886,1931,2002
```

Positions are LSB-first within each 64-bit little-endian word. The four in
the first 256 bits are 11, 94, 139 and 210.

### Proof and what the finite evidence establishes

Kernel directions keep every first S-box input fixed. First S-box outputs
are constant over the cube; second S-box inputs are affine in nine variables.
Exhaustive Möbius transformation of the source S-box verifies degree seven.
Thus every post-Chi1 bit has degree at most seven on this cube, and every
post-XRBD1 bit has the same degree ceiling. Their full 512-point XORs vanish.

For each Pressure chain `A=a+(c XOR(c>>17))`,
`C=c+(A XOR(A<<31))`, the exact LSB equations are
`A_0=a_0 XOR c_0 XOR c_17` and `C_0=a_0 XOR c_17`.
These remain degree at most seven. Transport through the odd-chain rotations
and Ink Cloud gives precisely the 32 positions above; Iota constants cancel.
The nine-fold cube XOR therefore vanishes there for **every** base message.
This analytic argument is an instance of the established `INT-KERNEL-001`
inclusion, freshly checked for membership, degree and coordinate routing.

Those 32 universal zeros cap the R1 sum rank at 2016. The saved actual sums
attain rank 2016, so there can be no additional universal linear masks.
At R2 the actual sums have rank 2048. Any universally balanced beta would
annihilate their span, forcing beta=0. This is an exact universal exclusion
from finite witnesses, not an inference that random-looking samples imply
security. Augmented full rank also rules out any nonzero mask having
universally constant parity **one**, as well as zero, at R2.

### Reproduction and assurance

Run from the preserved reproduction working copy:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/run.py --compiler gcc --bases 2080
python3 attack_ledger/run.py --compiler clang --bases 2080
python3 attack_ledger/audit.py
```

[The C wrapper](reproduce/attack_ledger_20261114/snapshot/attack_ledger/evaluate.c) includes the original `krakken.c`
unchanged. It computes R1 with the original API and then explicitly executes
the complete second round with **constant index 1**. It does not accidentally
apply the first indexed round twice. All 512 vertices of the first cube are
also replayed using the direct original one-/two-round APIs.

Each compiler run evaluates 1,064,960 cube vertex instances through the two
successive rounds. GCC and Clang produce byte-identical base and R1/R2 sum
archives. Python high- and low-pivot GF(2) eliminations check all rows, including
augmented ranks. The separate [Python model](reproduce/attack_ledger_20261114/snapshot/attack_ledger/audit.py) checks all
nine directions against an independently implemented prefix and replays four
complete cubes, 2048 vertices, at bases 0, 1, 1024 and 2079. It independently
derives constants using Python SHAKE128. See [audit results](reproduce/attack_ledger_20261114/snapshot/attack_ledger/audit.json).
This is an internal implementation audit; it is not external peer review,
formal verification, or an independent Python replay of every vertex.

Reports pin the SHA-256 of all three implementation files. Binary archives
store each base as 256 bytes and each cube sum as 256 bytes in report order.
The reports include their SHA-256 values. [Artifact manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json)
also pins the research corpus and analysis files.

### Attack interpretation and limits

This is a 512-query, chosen-message reduced-round integral test with 32
universal linear balances at R1, four observable in the first 32 output bytes.
The spanning certificate settles **universal exact linear balance for this
fixed D** at R2. It does not establish that every individual cube is unbalanced,
or that there is no statistical bias, special-base integral, nonlinear output
predicate, different direction space, or other attack surviving round 2.

In particular, this extends the tested cube geometries without adding an
independent attack-family exclusion. It establishes no eight-round security
level, collision/preimage work factor, or general theorem that attacks stop at
round 2. A useful next substantially different experiment is shared-chain
boomerang carry matching; another is a preselected nonperfect differential-linear
mask tested on fresh bases.

## BS-001 — shared-unit boomerang-derived quartets with carry matching

Added 2026-11-14. **Different attack family from K9-001:** coordinated
boomerang-derived four-state zero-XOR relations on unrestricted permutation
inputs. This is a finite new shared-unit construction search, not an
extension of the H159 kernel integral.

**Result: 49,872 of 131,072 specified candidates preserve full-state zero XOR
through complete R1. None of those 49,872 does so through complete R2.**
The R2 defects also span all 2048 bits, excluding any common nonzero linear
output-mask balance across this retained finite family.

### Why select this attack?

Research 01, `BOOM-MULTI-001`, and research 09 §8 establish and test routing
the two complementary serial-Chi output directions into **distinct** Pressure
chain units. Those units cannot interact, so complete-R1 zero XOR follows
without carry conditions. They explicitly leave shared-chain carry matching
open. This entry instead puts both directions in the **same** unit and tests
the actual carry equations. It does not rerun the old disjoint-unit sample.

The tested shared unit consists of two adjacent columns' even chains or
of their odd chains, as in the historical eight-unit convention. The audit confirms that both
directions affect **both** chains for every candidate; the survivors are not
hidden instances of routing the directions into separate chains. This is not a restriction
to just one isolated 128-bit Pressure pair.

### Exact finite family and construction

Let `E` be the 1024-bit coordinate space of first serial-Chi output lanes,
and `O` the complementary space of second-output lanes. Let `B` denote the
linear Butterfly diffusion map (XRBD). Enumerate the eight chain units

`{0,2}, {1,3}, {4,6}, {5,7}, {8,10}, {9,11}, {12,14}, {13,15}`,

where chain index `2*c` uses words `(4*c,4*c+2)` and `2*c+1` uses
`(4*c+1,4*c+3)`. Each unit has four words, or 256 bits.

For every unit G, use deterministic highest-pivot column elimination to
construct bases of

`E_G = {U in E : support(B(U)) is confined to G}`

and

`O_G = {V in O : support(B(V)) is confined to G}`.

For both maps, the outside-G projection has rank 896 and the kernel has
dimension 128. The combined images of the two bases have rank 256. These
are supporting linear-algebra results, not assumed transition probabilities.
Coordinates, order, elimination and all 2048 basis directions are reproducible
from [the generator](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/run.py),
[report](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/gcc_report.json) and
[direction archive](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/gcc_directions.bin).

For each G, exhaust every **basis-vector pair** `(U_i,V_j)`, `0<=i,j<128`.
The common post-Chi1 background is fixed to zero. Form the four post-Chi states

`Q = (0, U_i, V_j, U_i XOR V_j)`.

This is `8*128*128 = 131072` candidates. It is not enumeration of all nonzero
vectors in the 128-dimensional subspaces or of arbitrary backgrounds.

Recover round-start states using inverse Chi and the inverse linear prefix.
If `(u,v)` is a serial-Chi output word pair and I is the bytewise inverse
S-box, then

```
b = I(v) XOR rotl64(u,32)
a = I(u) XOR rotl64(b,32)
  = I(u) XOR u XOR rotl64(I(v),32).
```

Each inverse coordinate is a sum of a function of u and a function of v.
Consequently the four inverse-Chi states XOR to zero. The inverse prefix is
linear and preserves that zero XOR. All four states are distinct because
U and V are nonzero vectors in complementary coordinate spaces and the
maps are bijective. The separate audit constructs the inverse from a
full-rank, independently implemented 2048-bit Python prefix matrix.

Next evaluate the **exact original 64-bit modular Pressure equations** on
`B(Q)`, without treating additions or bases as independent. Retain a quartet
if its complete Pressure outputs XOR to zero. Iota and Ink Cloud then
preserve this relation through complete R1. Both complete original indexed
rounds, including constant indices 0 and 1, are evaluated for every retained
quartet.

### Reproduced results

| Measurement | Exact result for the specified finite family |
|---|---:|
| Candidates tested | 131,072 |
| Complete-R1 zero-XOR survivors per unit | 6,234 in each of 8 units |
| Complete-R1 survivors in total | **49,872** |
| Retained quartets still zero after Chi2 | **0** |
| Retained quartets still zero after complete R2 | **0** |
| Smallest observed Chi2 XOR-defect Hamming weight | 626 |
| Smallest observed complete-R2 XOR-defect Hamming weight | 927 |
| Chi2 defect rank / augmented rank | 2048 / 2049 |
| Complete-R2 defect rank / augmented rank | **2048 / 2049** |

The Hamming-weight minima are exact **within this enumerated family**. They
are not lower bounds for arbitrary boomerangs, backgrounds or directions.
The same applies to the survivor counts; they are not an estimate of
probability under uniform unrestricted states.

For a retained candidate t let `Z_r(t)` be the XOR of the four actual
complete-round output states. All `Z_1(t)=0`. At R2 the saved `Z_2(t)`
vectors span `GF(2)^2048`. Therefore any beta satisfying
`beta · Z_2(t)=0` for **every retained t** must be zero. Augmented rank 2049
also excludes universally constant parity one for any mask. This quantifies
over the retained finite direction-pair family; it does not classify
output masks for an arbitrary fixed direction pair over all backgrounds.

### Evidence, replay and implementation checks

Run from the preserved reproduction working copy:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/boom_shared/run.py --compiler gcc
python3 attack_ledger/boom_shared/run.py --compiler clang
python3 attack_ledger/boom_shared/audit.py
python3 attack_ledger/manifest.py
```

The generator's [bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/bridge.c) includes the
canonical scalar source unchanged. GCC and Clang reproduce byte-identical
direction, R1 quartet, Chi2 defect and complete-R2 defect archives. The native
[C++ rank checker](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/rank.cpp) computes both ordinary
and augmented ranks. An independent Python lowest-pivot implementation
checks those ranks; it stops when full ambient rank has been reached,
which is sufficient to certify equality.

The [audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/audit.py) checks all 131,072 carry-matching
candidates using a separate full-32-word Python Pressure implementation,
rather than the producer's four-word local gate, and recovers exactly the
same survivor index list. It checks E/O membership, direction independence,
Butterfly support and combined image ranks with separate Python code.

For **every one of the 49,872 survivors**, the
[original-API replay](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/replay.c) reconstructs all
four round-start inputs, checks input XOR zero, compares each R1 output
with the saved quartet and compares the complete-R2 defect against the
original `krakken_permute_scalar_rounds(state,2)` API. This covers **199,488
input states** at both depths. The inverse-prefix matrix comes from the
independent Python prefix. In addition, the established separate Python
full-round model checks the first and last survivor of every unit: 16
complete quartets, 64 inputs, at both round depths.

See [audit results](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/audit.json) and
[16 explicit witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/boom_shared/witnesses.json), including
complete round-start inputs and R1/R2 output states. The reports pin all
three original implementation files; the updated
[manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json) pins the analysis and research corpus.
These are implementation audits within this investigation, not external
verification or a proof-assistant derivation.

### Interpretation and next boundary

This search finds actual one-round shared-unit quartet constructions:
carry matching succeeds for many tested directions, despite the failure
of the disjoint-chain sufficient argument to cover them. Fixed retained
quartets supply a four-query full-state R1 relation. For four fixed distinct
inputs, an ideal random permutation would satisfy output XOR zero with
probability `1/(2^2048-3)`. Offline construction and search costs are
separate from those four evaluation queries.

Every tested surviving quartet loses that relation during the second
round, and complete-R2 evaluation confirms that the final Pressure layer
does not restore it. This is a **finite-family exclusion**, with an additional
exact all-mask spanning conclusion over that finite family. No theorem
that all boomerangs stop at R2 follows. Arbitrary combinations of kernel
basis directions, changed backgrounds, more units, other boomerang predicates
and statistical advantages remain outside this entry.

No valid padded-message reachability is asserted. These are unrestricted
2048-bit inputs, unlike K9-001's H159 domain. No production eight-round
collision/preimage attack, numerical security level, or differential-hull
probability is established. The next shared-unit experiments would vary
backgrounds and linear combinations of directions; any successful R2 witness
must still be checked through the original indexed-round API.

## DL-STAT-001 — nonperfect differential-linear bias and fresh-data R2 continuation

Added 2026-11-14. **Attack family:** differential-linear prediction, measuring
a biased parity of the XOR difference of two outputs. This differs from
K9-001's integral balances and BS-001's four-state boomerang-derived relations.

**Result:** an exact one-round correlation of **−1/8** is present. The same
predictor shows no statistically significant R2 correlation in the fresh
validation sample. A different R2 mask selected from 5488 training candidates
also fails fresh validation. This is a **statistical non-detection with
quantitative confidence limits**, not an exact theorem that R2 correlation
is zero or that differential-linear attacks are excluded.

### Research boundary and fixed attack definition

Research 01's `DL-001` covers perfect one-round masks; `DL-002` excludes
perfect two-round masks for 128 differences with local byte difference 1.
The old 20,000-base screen also concerned those perfect-mask continuations.
Research 09 §8 explicitly recommends investigating **nonperfect** predictors
with selection followed by fresh validation. This entry follows that lead,
with a different fixed byte difference, an exact nonperfect R1 predictor,
and a quantitative held-out R2 measurement. The local reduction technique
is inherited; the measured configuration and validation are new here.

The domain is uniform **unrestricted 2048-bit states**. Let `P_r` mean the
first r complete original indexed rounds, and define

`AC_r(Delta,beta) = E_x[(-1)^( beta · (P_r(x) XOR P_r(x XOR Delta)) )]`.

Positive correlation means parity zero is more likely; negative means parity
one is more likely. Absolute correlation is twice the prediction advantage
over success probability 1/2.

Fix serial-Chi cell `(p,y,j)=(1,2,5)` and byte difference `delta=0x6D`.
The pre-Chi1 difference has delta in byte 5 of word 10 and byte 1 of word 14,
and is zero elsewhere. Let Delta be its unique inverse under the original
linear Theta→MDS→Rho→Pi prefix. The prefix rank is 2048; the
[plan](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/plan.json) contains the complete
256-byte Delta and physical output masks. The independent Python prefix
maps Delta back to precisely this two-byte difference.

Define W by the same 32 carry-free output coordinates used in the preceding
entries. Enumerate all **5488 masks of Hamming weight 1, 2 or 3 in W**.
Before observing any R2 data, choose the candidate with highest absolute
**nonperfect, nonzero exact R1 correlation**, breaking ties by smaller mask
weight and then numeric mask. This chooses **output bit 210**.

### Exact R1 result and proof

The diagonal pre-Chi difference cancels the first serial S-box input
difference, making that first output identical in both executions. Exactly
one second-S-box output byte, state byte 113, differs. Its difference is
`S(t) XOR S(t XOR 0x6D)`; t is uniform on 256 values under uniform full-state
input. Uniformity follows because the linear prefix and the serial Chi
coordinate change are bijections: the original second input and first
S-box output are independent uniform bytes, so their XOR is uniform.

For masks in W, Pressure's exact LSB identities and the linear Butterfly
and Ink Cloud maps pull output parity back to a linear form of that one
post-Chi difference byte. The selected output bit 210 pulls back to byte
mask `0x01`. Exhaustive enumeration of all 256 t gives the signed sum

`sum_t (-1)^((S(t) XOR S(t XOR 0x6D)) & 1) = -32`.

Consequently **`AC_1(Delta,e_210)=-32/256=-1/8`**, over the entire full-state
uniform domain. Predicting this output-difference bit to be one succeeds
with probability **9/16 = 56.25%**, rather than 50%. This is an exact R1
structural predictor, not merely a sampled bias. The independent audit
recomputes the carry-free pullback analytically and enumerates the source
S-box to check every candidate's R1 coefficient and the selection rule.

### Training, freezing and fresh validation

The [generator](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/run.py) draws each 256-byte
base directly from `os.urandom`, saving the actual bytes for exact replay.
Statistical claims assume these are independent uniform base states.

1. Save the exact-R1 selection and specified sample sizes before sampling.
2. Draw **65,536 training pairs** for the same fixed Delta and evaluate all
   5488 candidate masks at complete R2. Select the largest absolute sampled
   correlation, with the same tie-breaking rule.
3. Save a frozen local plan, including the primary and adapted masks and
   all training-data hashes, **before drawing validation bytes**.
4. Draw **262,144 fresh validation pairs**. Report exactly three fixed tests:
   the primary mask at R1, the same mask at R2, and the adapted mask at R2.

The adapted R2 mask is the XOR of output bits **11, 1419 and 1630**. Its
training signed sum is −1038, giving apparent correlation **−0.0158386230**.
Its exact R1 correlation is +1/32. The validation data is never used to
change either mask or add another tested hypothesis. The local freeze is
established by the script's write/draw order, not by an external registration.

### Fresh validation results

| Fixed validation test | Parity-zero count | Parity-one count | Estimated correlation | Simultaneous 99% interval |
|---|---:|---:|---:|---|
| Primary bit 210, complete R1 | 114468 | 147676 | −0.126678467 | [−0.133664503, −0.119692431] |
| Same bit 210, complete R2 | 130966 | 131178 | **−0.000808716** | **[−0.007794752, +0.006177320]** |
| Adapted three-bit parity, complete R2 | 131265 | 130879 | **+0.001472473** | **[−0.005513563, +0.008458510]** |

R1 agrees with its exact −0.125 coefficient. Both R2 intervals contain
zero. The training winner's apparent negative bias also changes sign on
fresh data. Neither selected R2 predictor gives evidence of a persistent
bias at this sample size.

With simultaneous confidence at least 99% under the stated sampling model,
the two true R2 absolute correlations are bounded by **0.007794752** and
**0.008458510**, respectively. Their corresponding advantages over 50%
prediction success are at most half those numbers. These bounds concern
the selected two R2 masks, **not all 5488 training candidates**.

### Why selection and confidence accounting are valid

For each fixed test, its N validation observations Y lie in {−1,+1}, with
population mean AC. Hoeffding's inequality gives

`Pr[ |mean(Y)-AC| >= epsilon ] <= 2 exp(-N*epsilon^2/2)`.

Conditional on all training data, the three validation tests are fixed and
the validation draws are independent of the training. A union bound over
K=3 tests, with alpha=0.01, therefore permits

`epsilon = sqrt(2*ln(2*K/alpha)/N) = 0.00698603608123355`.

No independence among the three test statistics is required. The 5488-mask
training search does not increase K because only its selected winner is
validated on fresh data. These intervals must not be reused as simultaneous
bounds for the unvalidated masks, other differences, or future searches.
No inference that the entire R2 output distribution is uniform is made.

### Replay and assurance

For the preserved experiment, run:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/differential_linear/audit.py
python3 attack_ledger/manifest.py
```

The one-time generator refuses to overwrite an existing frozen plan. To
launch a genuinely new sample, use a separate directory and separately
record its hypotheses and confidence accounting. The preserved raw input
files make this completed experiment exactly replayable without drawing
new randomness or increasing the statistical sample size.

The [C bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/bridge.c) includes the original
scalar source unchanged and uses `krakken_permute_scalar_rounds` directly
at depths 1 and 2 for **both members of every pair**. There are no ablated
layers or manually reset round constants. GCC and Clang produce identical
32-bit difference projections for **all 327,680 training and validation
pairs**, at both complete depths.

The [independent audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/audit.py) also:

- Checks Delta and the analytic carry-free byte-to-mask pullback with the
  separately written Python model.
- Recomputes all exact R1 candidate coefficients and confirms the primary
  selection before R2 measurement.
- Recomputes all 5488 training scores using a separate
  [C++ parity checker](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/check_scores.cpp),
  confirming the selected adapted mask.
- Replays 64 base pairs (128 actual input states) through the independent
  Python full permutation at both depths.
- Independently recounts every validation parity and recalculates all three
  confidence intervals from the saved projections.

See [results](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/result.json),
[audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/differential_linear/audit.json), and
[artifact manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json). Source hashes match the
original scalar, header and AVX2 files. The replay is an internal audit;
recompilation and replay of the same samples provide implementation checks,
not additional independent statistical evidence.

### Interpretation and remaining attacks

The substantial nonperfect R1 predictor is verified exactly. The two tested
R2 continuations show no validated bias, with explicit bounds at the stated
confidence level. This is weaker than proving exact zero correlation, but
more informative about possible small biases than a perfect-mask exclusion.

The input difference has nonzero capacity bytes and cannot connect two
valid H159 first blocks. No digest-only chosen-message exploit or valid-message
reachability is claimed, even though bit 210 itself is a digest-position bit.
The adapted R2 parity additionally uses nondigest state bits. Other masks,
input differences, conditional populations, weaker correlations, other attack
families, and eight-round security remain outside this entry.

## RX-001 — near-perfect one-round rotational carry predictor

Added 2026-11-14. **Attack family:** rotational/RX related inputs. Pair x
with `T(x)`, where T rotates every 64-bit word left by 32 bits. This is a
different relation from a fixed-XOR differential, an integral, or a quartet.

**Result:** a selected R1 bit relation succeeds with exact probability
**99.9969482421882%** on uniform unrestricted states. It has seven failures
in 262,144 sampled pairs. At complete R2, the same selected relation is
close to balanced, with no significant bias at the stated confidence level.
Additionally, an exact R2 certificate excludes **every perfectly constant
linear RX parity**, with arbitrary output-mask weight, for this rotation.

The first result is an analytic probability statement with source-derived
witnesses; the R2 bias result is statistical; the R2 perfect-parity exclusion
is a separate deterministic finite-rank theorem. These assurances must not
be conflated.

### Research boundary and attack definition

Research 01 `ROT-002` proves the complete-R1 byte-rotation residual reduces
exactly to Pressure under uniform unrestricted inputs. Research 09 §5
reports empirical coordinate biases and no R2 flags in its historical
screens. It specifically warns that sample-perfect coordinates have rare
counterexamples. Research 02 `WORK-RX-FULL2048-R8-049` gives operation-level
characteristic bounds and an all-mask exact-parity exclusion at **R8**;
those are not R2 bias bounds.

This entry uses the existing rotational family and reduction. Its additional
content is an exact, very high R1 carry-bias formula for a specified bit,
a deliberately constructed failure witness, a fresh R2 continuation test,
and a new local R2 all-mask certificate for rotation 32. It does not claim
that rotational analysis was previously untried.

Let `P_r` be the first r **complete original indexed rounds**, with all
layers and constants. Let Ink be the original Ink Cloud map. Define

```
gamma_r = Ink(rc[r-1] XOR T(rc[r-1]))
E_r(x) = P_r(T(x)) XOR T(P_r(x)) XOR gamma_r
```

Gamma removes the known **last-round** constant discrepancy at each depth.
At R2 it does not cancel the nonlinear effects of earlier constants. The
same output coordinate **25** is tested at both depths. The candidate and
sample size are fixed in [the plan](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/plan.json)
before drawing any random sample; there is no R2 mask search.

For clarity, the tested bit relation is

`P_r(T(x))[25] XOR P_r(x)[57] XOR gamma_r[25] = 0`.

The domain is uniform unrestricted 2048-bit states. H159 padding and
capacity restrictions are not imposed.

### Analytic R1 probability

Write `B = Theta → MDS → Rho → Pi → Chi → Butterfly`, the full prefix before
Pressure. The established `ROT-002` proof shows B is bijective and commutes
with T. Linear lane operations commute with common rotations; bytewise MDS
and S-box operations commute with a four-byte rotation; the serial-Chi
32-bit rotations also commute. Ink commutes as well. Hence, for `z=B(x)`,

`E_1(x) = Ink(Pressure(T(z)) XOR T(Pressure(z)))`.

Uniform x gives exactly uniform z. In the even Pressure chain at column
zero, set `f(c)=c XOR(c>>17)` and `A=a+f(c) mod 2^64`.
Under uniform z, a and c are independent uniform words. The map f is
invertible, so a and b=f(c) are also independent uniform words.

For bit positions `j=0,...,14`,

`f(T(c))[j] = c[32+j] XOR c[49+j] = T(f(c))[j]`.

Thus the first 15 low operand bits in the rotated addition equal the
corresponding original operand bits 32–46. The discrepancy between the two
bit-14 sums comes solely from the carry entering original bit 32. That
carry is one with exact probability

`Pr[carry_32=1] = (2^32-1)/2^33`.

It changes the result at bit 46 only if it propagates through all 14
preceding positions 32–45. The propagation probability is `2^-14`.
These events are independent because they depend on disjoint low/high
slices of the independent uniform words a and **f(c)**. No independence
of overlapping raw-c slices or of different rounds is assumed.

Ink sends Pressure word-zero bit 14 to final output bit 25. Therefore

```
q = Pr[E_1(x)[25]=1] = (2^32-1)/2^47
                        = 0.0000305175781178946...
Pr[E_1(x)[25]=0] = 1-q = 0.999969482421882...
correlation = 1-2*q = 0.999938964843764...
```

This is a near-perfect relation, **not** a perfect identity.

### Explicit rare-event controls

The [carry witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/carry_witnesses.json) include
complete original round-start inputs for both a success and a failure.
They are recovered through inverse Butterfly, inverse serial Chi and the
inverse source-derived linear prefix from the following Pressure inputs:

- All words zero: the corrected selected R1 bit is zero.
- `a=2^46-1`, `c=1` in column zero's even chain, all other words zero:
  the selected R1 bit is **one**. Adding f(c)=1 generates the low carry and
  propagates it through the 14 required upper positions.

The original full-round APIs and the separate Python model confirm both
outcomes. These two deterministic controls are constructed before the random
experiment and are not part of its statistical sample. Their R2 flags are
also preserved, but are not used to choose the test or sample size.

The elementary addition lemma is additionally checked exhaustively at
half-word widths h=1,...,4, totaling **69,904 operand pairs**. For each
propagation length j<h, the observed count agrees with the formula
`(2^h-1)*2^(3*h-j-1)` out of `2^(4*h)` possibilities. These small controls
check the implementation of the argument; the full-width probability
follows from the analytic carry/propagation proof.

### Fresh complete-round measurements

Draw 262,144 independent uniform base states, assuming the 256-byte draws
from `os.urandom` follow that sampling model. Save the actual raw bases.
For each, run both x and T(x) through the original scalar API at depths 1
and 2 and compute the corrected residual.

| Test | Residual bit zero | Residual bit one | Estimated correlation |
|---|---:|---:|---:|
| Complete R1 | **262137** | **7** | +0.999946594238281 |
| Complete R2 | **131129** | **131015** | **+0.000434875488281** |

The exact R1 formula predicts approximately eight failures on average at
this sample size. The observed seven are consistent with that behavior;
the exact probability is supplied by the proof, not inferred from those
seven events.

For the two fixed signed-correlation tests, Hoeffding and a union bound
with K=2, N=262144 and alpha=0.01 give

`epsilon = sqrt(2*ln(2*K/alpha)/N) = 0.00676100930704018`.

The simultaneous 99% R2 interval is
**[−0.006326133818759, +0.007195884795321]**. It includes zero. With that
simultaneous confidence, the tested true R2 absolute correlation is at
most **0.007195884795322**. No independence between the two depth statistics
is needed; independence of the sampled bases is the sampling assumption.
Replaying the same sample adds no statistical observations.

### Exact R2 all-mask perfect-parity exclusion

For the first **2080 saved bases**, preserve each complete 2048-bit vector
`E_2(x)` rather than just coordinate 25. The
[raw archive](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/gcc_r2_residuals.bin) has:

- GF(2) rank of residual vectors: **2048**.
- GF(2) rank of augmented vectors `(E_2(x),1)`: **2049**.

For any beta and bit c, a universally constant relation
`beta · E_2(x)=c` would make `(beta,c)` annihilate every augmented row.
Full rank forces beta=0 and c=0. Thus, for this rotation and zero input
XOR correction, **every nonzero full-state linear output mask takes both
parity values somewhere over the full input domain at complete R2**.
The conclusion also holds for the uncorrected RX residual: a fixed output
correction changes only the parity's fixed sign.

This is a deterministic existence-of-counterexamples proof for all output
masks, including arbitrary Hamming weight. Random discovery of the rows
introduces no sampling assumption into the rank conclusion. It excludes
perfect constant parities, not small correlations or nonlinear predicates.

### Reproduction and assurance

Replay the preserved experiment with:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/rotational/audit.py
python3 attack_ledger/manifest.py
```

[The one-time generator](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/run.py) refuses to overwrite
its saved plan. The [C bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/bridge.c) includes the
canonical scalar implementation unchanged and invokes the original complete
one-/two-round APIs for both executions of every pair. It computes the last
round correction from the actual source constants and original Ink Cloud.

GCC and Clang produce byte-identical selected-bit flags for **all 262144
pairs** and identical complete R2 residuals for all 2080 certificate bases.
The separate [Python audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/audit.py):

- Checks the reduced-width carry counts and exact full-width formula.
- Computes both constant corrections independently using Python SHAKE128.
- Replays 33 sampled pairs at both complete depths using the independent
  Python model, and checks B's rotational commutation on those inputs.
- Replays both deliberately constructed carry controls.
- Recomputes R2 ranks with independent Python high- and low-pivot elimination,
  checking the native C++ producer's ranks.
- Recounts every stored flag and independently recalculates both confidence
  intervals.

See [result](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/result.json),
[audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rotational/audit.json) and
[manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json). These are internal implementation
audits, not external peer review or proof-assistant verification. The
analytic R1 proof inherits the established source commutation/bijectivity
premise from `ROT-002`; sampled commutation controls do not replace that
proof. All original permutation and research files remain unchanged.

### Interpretation and remaining boundary

This fourth ledger family provides a strong positive R1 structural
predictor. The tested bit shows no validated R2 continuation, with an
explicit confidence bound. The separate rank certificate rules out every
**perfectly constant linear RX parity** at R2 for rotation 32.

The rank theorem does not exclude weak or strong nonperfect correlations
on other masks. The selected-bit confidence interval does not apply to
untested masks, rotations, input XOR corrections, conditioned populations
or nonlinear/joint observations. No universal statement that all rotational
attacks stop at R2 follows, and no eight-round security level is established.

Both compared output coordinates happen to lie in the first 256 state bits,
but the uniform full-state input population is not the H159 message domain.
This is a permutation distinguisher component, not a demonstrated chosen-
message hash attack. A separate valid-padding related-input experiment would
need its own reachability and probability analysis.

## SUB-001 — chosen-affine-flat subspace / affine-hull attack

Added 2026-11-14. **Attack family:** subspace propagation, testing whether
256 inputs forming an eight-dimensional affine flat retain an unusually
small output affine hull. This is an exact finite-set test, not a statistical
bias estimate or another integral XOR-balance experiment.

**Result:** **48 of 128** constructed affine input flats have output hull
dimension below 255 after complete R1. The smallest dimension is **68**.
Every one of the 128 sets has hull dimension **255 after complete R2**, the
maximum possible for 256 points. The best set reaches that maximum at Chi2.
Thus the extra R1 affine compression does not continue through R2 in this
specified family.

### Research boundary

Research 01 `SUBSPACE-001` evaluates the 159 H159 coordinate-byte families,
which already reach hull dimension 255 at Chi1. `SUBSPACE-002` treats a
particular valid-message Theta-cancelling two-byte plane, whose compression
ends at Pressure1. `PRESS-TRANS-001` studies affine translation cosets at
an **internal Pressure input** boundary with nonlinear round-start pullback.

This entry constructs different **actual affine flats at the unrestricted
permutation input**: their diagonal directions cancel the first serial-Chi
call, and their post-Chi1 background is chosen to be zero. Some of their
low hull dimensions survive the **complete first round**, including Pressure.
The result is a new specified geometry for the existing subspace family;
it is not an exclusion of arbitrary subspace attacks.

### Exact input construction

Let L be the original invertible linear Theta→MDS→Rho→Pi prefix. Its
source-derived 2048-bit matrix has full rank. Let S be the original byte
S-box and `h=S^-1(0)=0x8B`.

Define a pre-Chi base s with every first-output-side lane zero and every
second-output-side lane equal to the repeated-byte word `0x8B8B8B8B8B8B8B8B`.
In lane-index notation, s[i] has that repeated value when `(i//4)%2=1`,
and is zero otherwise. The whole Chi output of s is zero.

For each of the **128 second-output byte positions**, choose its odd-side
lane b and byte j. Vary t over all byte values by XORing t into pre-Chi
byte j of b and into byte `(j+4)%8` of its paired lane `a=b-4`.
The first-call input `a XOR rotl64(b,32)` is unchanged. Its output stays
zero. The only variable Chi output is the chosen second-side byte

`v = S(h XOR t)`.

S is a permutation, so v ranges over every byte exactly once. All other
post-Chi bytes stay zero. Pulling this pre-Chi affine flat back through
`L^-1` gives **256 distinct original input states forming an exact 8-flat**.
The eight initial directions are the inverse images of the eight diagonal
unit-byte directions. This is an affine **set** even when its saved vertex
ordering uses the nonlinear labels `v=0..255`; the affine parameter is
`t=S^-1(v) XOR h`.

The [reports](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/gcc_report.json) give the exact site
mapping. Site number is `32*p+8*y+j`, with post-Chi second lane `8*p+4+y`.
All 128 flats share the same original input origin. There are 32768 vertex
evaluations per depth, covering **32641 distinct input states** because the
common origin is repeated across flats.

### Exact full-round results

For a set Y with a chosen origin y0, its affine hull dimension is
`rank_GF2 { y XOR y0 : y in Y }`. This is independent of the chosen origin.
For 256 points that dimension is at most **255**, even though the output
state has 2048 bits.

| Measurement | Result |
|---|---:|
| Constructed input flats | 128 |
| Input dimension / points per flat | 8 / 256 |
| Flats with R1 output hull dimension <255 | **48** |
| Flats already at dimension 255 after R1 | 80 |
| Smallest complete-R1 hull dimension | **68** |
| Flats at dimension 255 after complete R2 | **128** |

Every vertex is enumerated; these are exact ranks of the defined finite
sets, not estimates from sampled vertices. The complete R1 rank histogram
and per-site results are preserved in the report.

The strongest case is **site 7**, varying post-Chi word 4, byte 7. Its
pre-Chi diagonal directions affect word 4 byte 7 and word 0 byte 3.
Its measured checkpoint dimensions are:

| Checkpoint | Affine hull dimension |
|---|---:|
| Original permutation input | 8 |
| Chi1 / Butterfly1 | 8 |
| Complete R1 | **68** |
| Second-round linear prefix | **68** |
| Chi2 | **255** |
| Butterfly2 | 255 |
| Complete R2 | **255** |

The first two entries follow from the construction and invertible linear
maps. Subsequent dimensions are exact complete-set computations. The
independent Python model also confirms the Chi2 rank 255. Pressure2's
actual complete-round result confirms that the final layers do not restore
the low affine dimension.

### Concrete disappearing relation and the limits of rank 255

For the strongest flat, **output bit 0 is zero for all 256 states after
complete R1**. After complete R2, it is zero on **138** states and one on
**118**. The [explicit witness](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/witness.json) includes
the original input origin, all eight original input directions and the
output mask. This is one concrete consequence of the larger hull growth.

However, rank 255 **does not mean that every output linear relation has
disappeared**. For a fixed 256-point set in 2048 bits, at least 1793
independent mask directions are constant on its affine hull even at the
maximum dimension. In the strongest case:

- The R1 constant-mask space has dimension `2048-68=1980`.
- The R2 constant-mask space has dimension `2048-255=1793`.
- Their intersection has dimension **1725**: the union of the R1 and R2
  anchored difference spans has rank **323**. A mask in the intersection
  is constant separately at both depths; its two constants may differ.

Those remaining relations are compatible with a generic finite set of
this size. The attack being tested is the **extra compression below the
255-dimensional ceiling**, not the impossible requirement that a
256-point set have no affine relations at all. Nor does affine-hull growth
imply uniformity, independence of output coordinates, or a security level.

### Distinguisher interpretation

Fix the strongest flat's 256 inputs and test whether their full output
hull dimension is below 255. The original R1 accepts; the original R2
rejects for this flat and for every other flat tested here.

For a uniform ideal permutation on 2048-bit states and a fixed list of
256 distinct inputs, a union bound during sequential output sampling gives

`Pr[affine hull dimension <255] <= (2^255-1)/(2^2048-255)`.

Indeed, at step i the previous i output points lie in an affine space
of size at most `2^(i-1)`, out of `2^2048-i` remaining possible outputs.
Summing those upper bounds for i=1,...,255 gives the displayed bound.
This explains why the R1 compression is a structural distinguisher
component in a full-state chosen-input model. It is not a collision attack,
a hash-message attack, or a numerical security claim for eight rounds.

### Reproduction and assurance

Run from the preserved reproduction working copy:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/subspace/run.py --compiler gcc
python3 attack_ledger/subspace/run.py --compiler clang
python3 attack_ledger/subspace/audit.py
python3 attack_ledger/manifest.py
```

The [bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/bridge.c) includes the canonical scalar
source unchanged. It uses the source-derived inverse L to reconstruct
**every actual initial state**, then evaluates the original public
`krakken_permute_scalar_rounds` API at both complete depths. For every
vertex, those results are also checked against the direct post-Chi tail
construction with the correct original constants 0 and 1.

GCC and Clang produce identical complete input streams, complete R1/R2
output streams, affine origins and directions. Each compiler evaluates
all 32768 vertex instances through both original APIs. The independent
[audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/audit.py) checks:

- Every input flat's affine origin and all eight directions under the
  separately written Python prefix: **1152** source-to-model comparisons.
- Membership and parameter coverage for **all 32768** stored input vertices,
  including the nonlinear v-to-affine-t ordering.
- All **256** complete output-hull ranks, using both pivot orders.
- Three entire flats, **768 original inputs**, through both complete rounds
  of the independent Python permutation: the strongest flat, an R1-saturated
  flat, and another R1-compressed flat.
- The strongest flat's Chi2 growth, common-mask-space dimension, and the
  explicit R1-constant/R2-varying output parity.

See [audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/audit.json),
[explicit flat and relation](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/witness.json), and
[artifact manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json). These are internal
implementation audits, not external verification or a proof-assistant result.
The initial [probe](reproduce/attack_ledger_20261114/snapshot/attack_ledger/subspace/probe.py) is preserved as discovery
history; the documented producer performs the complete original-input replay.

### Scope and next boundary

This is a positive R1 affine-compression construction in 48 selected
unrestricted input flats and an exact loss of that compression by complete
R2 in this defined family. For the other 80 flats, this particular
compression attack already fails at R1.

Other initial flats, different post-Chi backgrounds, larger subspaces,
nonlinear observation functions and approximate relations remain open.
These fixed-flat certificates are not an exclusion over all cosets of
the input direction spaces. The selected origin has nonzero capacity
bytes, and no valid-H159 message realization is asserted. No production
hash attack, eight-round work factor, or general subspace-family stopping
round follows. The original implementation and ten research documents
remain unchanged.

## REB-001 — rebound-style inbound construction and conditioned outbound tests

Added 2026-11-14. **Attack family:** rebound-style differential construction:
solve a prescribed nonlinear Chi transition efficiently, then test the
outbound relation through complete rounds. This is an attack component,
not a demonstrated full rebound collision attack.

**Result:** all 262144 constructed inbound-matched pairs retain a fixed
32-bit projection and an unchanged output byte at complete R1. At complete
R2, **zero** retain the full 32-bit pattern, but **1006** retain the unchanged
byte. That partial-match frequency, **0.3837585%**, is compatible with the
generic **1/256 = 0.390625%** reference. Thus partial continuations exist;
this experiment does not demonstrate an advantage from them.

The R1 guarantees and local counts are exact. The two R2 frequencies have
conditional sampling-model confidence bounds. A separate exact R2 rank
certificate excludes universal constant linear parities in the inbound class.

### Research boundary

Research 01 `REBOUND-001` establishes the local serial-Chi inbound formula,
its selected `(d,eps)=(101,1)` example, and dense forward/backward support.
`REBOUND-002` excludes nonzero single-cell input or output differences for
valid H159 first blocks. Neither supporting result by itself measures the
conditioned complete-R2 endpoint distribution.

This entry uses a **different prescribed transition**, `(0x53,0x5D)`,
and carries actually reconstructed matched input pairs through the original
complete APIs. It combines the rebound inbound construction with the known
carry-free observations and zero-byte guarantee, then tests their persistence
on a fresh conditional population. The S-box formula and truncation lemmas
are inherited mechanisms, not new independent security premises.

### Exact inbound class and efficient construction

Use cell `(p,y,j)=(0,0,0)`: first pre-Chi byte 0 of lane 0 and aligned
second byte 4 of lane 4, physical pre-Chi byte 36. In aligned local byte
coordinates, write

```
u = S(a XOR b)
v = S(b XOR u)
```

Fix input difference `(d,d)` with **d=0x53**. The first output difference
is zero. The second difference is prescribed to be **eps=0x5D**.
Put `x=a XOR b` and `y=b XOR S(x)`. The exact source S-box satisfies

`S(y) XOR S(y XOR 0x53) = 0x5D`

at precisely **y in {0x00,0x25,0x53,0x76}**. Consequently there are
`256*4=1024` ordered matching local bases out of 65536, and the unconditioned
uniform-local match probability is exactly **1/64**.

A match needs no rejection search: choose x freely and one of those four
y values, then set `b=y XOR S(x)` and `a=x XOR b`. This enumerates each
ordered matching base exactly once. A separate exhaustive C++ enumeration
of all 65536 local bases agrees point for point with the Python producer's
1024 matches.

Let L be the original linear prefix. Inverting L maps the diagonal two-byte
difference to one fixed 2048-bit original input difference Delta. The
[plan](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/plan.json) stores Delta, the roots, exact cell
coordinates, source hashes and both endpoint tests. The full source-derived
prefix matrix has rank 2048. The independent Python audit checks every one
of its 2048 inverse columns.

### Sampling population and why the conditioning is correct

For each pair, draw 256 raw bytes directly from `os.urandom`, under the
assumption that they are independent uniform bytes. Use raw pre-Chi byte 0
to select x and the low two bits of raw byte 36 to select one of the four
y roots. Replace those two bytes with the constructed a,b and leave the
other 254 bytes unchanged. Apply `L^-1` to obtain the actual initial state
X, and pair it with `X XOR Delta`.

The resulting bases are uniform on the **prescribed Chi1 differential
class of size 2^2042**: 2032 free background bits plus ten uniform local
selection bits. The construction is a bijection from those parameters to
the 1024 local matches and their backgrounds. This is not a uniform draw
from every unrestricted input; all R2 probability claims below explicitly
condition on the inbound class. Each raw record is independent, and no
pair is selected based on an R2 outcome.

Both tests and N=262144 are saved before drawing the sole random sample.
The raw draws are preserved for exact replay. Conditioning is implemented
constructively, rather than by multiplying assumed independent transition
probabilities across stages.

### Guaranteed complete-R1 outbound relations

Every constructed pair has exactly the prescribed **one-byte** post-Chi1
XOR difference eps at physical byte 36. Butterfly transforms it linearly.
The 32 carry-free Pressure LSB output coordinates, transported through the
original odd-chain rotations and Ink Cloud, are exactly the W coordinates
listed in the earlier ledger entries.

For every inbound-matched base, their complete-R1 difference is the fixed
32-bit pattern **0x00440100**, using the plan's sorted W-coordinate order.
This follows from the exact first/second Pressure LSB identities; no
assumption about independence of the selected base or carries is needed.
The independent audit derives the pattern analytically from the post-Chi
byte difference and separate Python Butterfly code.

The complete-R1 difference at **output byte 252 is also always zero**.
The inherited `DIFF-TRUNC-001` congruence proof applies to every nonzero
second-output byte difference at this site. A fresh support replay over all
eight byte basis bits gives 22 guaranteed unchanged low bits in Pressure
word 9 and 45 in word 11. Thus its odd-chain first output has 22 unchanged
low bits. The combined rotation by 7+11 maps these to bits 18–39 of output
word 31, including the whole byte at state position 252.

### Complete-round measurements and surviving partial matches

Every pair is evaluated through both original complete APIs, including
Pressure, the correct indexed constants, and Ink Cloud.

| Fixed outbound condition | Complete-R1 matches | Complete-R2 matches |
|---|---:|---:|
| W difference equals fixed pattern 0x00440100 | **262144 / 262144** | **0 / 262144** |
| Byte-252 difference equals zero | **262144 / 262144** | **1006 / 262144** |

The full pattern has no observed R2 continuation. The byte condition does:
1006 actual partial matches survive both rounds. The
[explicit witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/witnesses.json) include a pair
with such an R2 partial continuation, reconstructed as complete original
permutation inputs. A partial byte match is not a full-state collision.

The predeclared generic references are approximately `2^-32` for the
specified full W pattern and `1/256` for one zero-difference byte. These
are comparison baselines, not assumptions about Krakken. For distinct
outputs sampled from a uniform ideal 2048-bit permutation, a prescribed
nonzero k-bit difference has exact probability
`2^(2048-k)/(2^2048-1)`; a zero k-bit difference has probability
`(2^(2048-k)-1)/(2^2048-1)`. The difference from the references here is
negligible. No independence between the two tests is assumed.

### Conditional R2 confidence bounds

Use two fixed Bernoulli event tests and simultaneous alpha=0.01. For N
independent bases in the inbound class and observed proportion q, invert

`N * KL(q || p) <= ln(2*K/alpha)`, with K=2,

where `KL(q||p)=q ln(q/p)+(1-q)ln((1-q)/(1-p))`, with the usual endpoint
limits. Chernoff's binomial tail bounds and a union bound give at least
99% simultaneous coverage of both true conditional event probabilities.
No normal approximation is used. No independence between the test
statistics is required.

| R2 event | Observed frequency | Simultaneous 99% conditional interval |
|---|---:|---|
| Fixed 32-bit W pattern | 0 | **[0, 0.0000228553622371]** |
| Unchanged byte 252 | 0.00383758544922 | **[0.00343454318284, 0.00427086361557]** |

The byte interval contains **1/256**, so these observations do not show an
excess partial-match probability over that reference. They do not prove
the probability equals the reference. The zero-count full-pattern upper
bound remains much larger than `2^-32`; it cannot exclude weaker rare-event
advantages. Zero observed continuations is not a proof of impossibility.

These bounds describe uniform sampling **within the prescribed inbound
class**, not all input differences, arbitrary adaptive background searches,
or an optimal attacker's success probability. Cheap construction of the
inbound class must also be distinguished from the 1/64 probability of
hitting it by an unconditioned random input pair.

### Exact conditioned R2 perfect-parity exclusion

Save the first 2080 actual full-state R2 difference vectors. Their GF(2)
rank is **2048**, and the augmented vectors `(difference,1)` have rank
**2049**, verified with both pivot orders.

A nonzero mask beta whose parity were constant for **every** base in the
prescribed inbound class would supply an affine equation annihilating all
augmented rows. Full rank makes that impossible. Thus every nonzero
full-state output parity takes both values somewhere in the conditioned
class at complete R2. Random discovery of these witnesses introduces no
sampling assumption into this finite-rank proof.

This excludes universal constant linear parities. It does not exclude
partial matches such as the 1006 observed byte continuations, small biases,
nonlinear predicates, or specially selected backgrounds.

### Replay and assurance

For the saved experiment:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/rebound/audit.py
python3 attack_ledger/manifest.py
```

The [one-time generator](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/run.py) refuses to overwrite
its frozen plan. The [C bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/bridge.c) includes the
canonical scalar source unchanged, reconstructs actual initial states via
the inverse prefix, and invokes `krakken_permute_scalar_rounds` separately
at depths 1 and 2 for **both members of every pair**. It uses the original
permutation implementation throughout; the analysis lookup table is only
for the linear inverse used in constructing chosen inputs.

GCC and Clang agree on every R1/R2 projection and byte-event flag across
all **262144 matched pairs**, and on every complete R2 certificate vector.
The [independent audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/audit.py) additionally checks:

- All local ordered matches through a separate
  [C++ enumeration](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/local_check.cpp), and the exact
  bijection from uniform construction parameters to those matches.
- All 2048 inverse-prefix columns using the independent Python prefix.
- The constant R1 W pattern and byte-252 support argument independently.
- Actual input reconstruction, Chi1 prescribed differences and both
  complete rounds on the saved control pairs, including a weak R2 survivor,
  using the separately written Python permutation.
- Both conditioned R2 rank certificates with independent high-/low-pivot
  elimination, every event count, and the KL confidence-set endpoints.

See [results](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/result.json),
[audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/audit.json),
[matched input witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound/witnesses.json), and
[manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json). Recompilation and replay validate
implementation consistency; they do not add statistical sample size or
constitute external verification.

### Interpretation and next boundary

The rebound-style inbound match is efficiently attainable and gives exact
R1 outbound constraints. The full tested projection has no observed R2
continuation, while a weaker one-byte relation does continue at a measured
rate compatible with the generic reference. This is a scoped result,
not a statement that all rebound attacks stop at R2.

The chosen original input difference has nonzero fixed-padding or capacity
coordinates, independently checked from Delta, so this pair class cannot
connect two valid H159 first-block embeddings. This agrees with the existing
`REBOUND-002` exclusion. No hash collision, preimage attack, eight-round work
factor or general rebound-family exclusion follows. Multi-cell inbound
matching, targeted carry/background optimization and later-block reachability
remain separate research targets. All original implementation and research
files remain unchanged.

## REB-001-R3 — round-three extension and consecutive partial-match witnesses

Added 2026-11-14 at the researcher's request to check whether REB-001 is
"completely blocked" at round 3. **The evidence does not establish complete
blocking. Two explicit pairs retain the weak unchanged-byte condition
through rounds 1, 2 and 3.** No useful three-round rebound advantage is
demonstrated by those partial matches.

This extends the **same attack**, not a new attack family. The original
REB-001 files and R1/R2 results are preserved unchanged.

### Fixed experiment and original cohort

Reuse all **262144 original inbound-matched pairs**, with the same Delta,
Chi1 transition `(0x53,0x5D)`, fixed W target **0x00440100**, and output byte
**252**. No new predicate, mask, input difference or background is selected
based on R3 outcomes. The extension plan is saved before evaluating R3.

The [new bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/bridge.c) includes the preserved
REB-001 chosen-input constructor and calls the original
`krakken_permute_scalar_rounds(state,3)` API on **both initial states**.
Thus every evaluation uses complete original rounds with constant indices
0, 1 and 2. It does not append a new first round or infer R3 from the R2
result. The [plan](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/plan.json) pins the original
source files and all parent inputs, constructor, matrix and observation
files used by the extension.

### Observed continuation through complete R3

| Fixed condition | R1 matches | R2 matches | R3 matches |
|---|---:|---:|---:|
| W difference equals target 0x00440100 | 262144 | 0 | **0** |
| Byte-252 difference equals zero | 262144 | 1006 | **1032** |

The R3 byte-match frequency across the whole cohort is
**1032/262144 = 0.3936767578125%**, close to the generic one-byte reference
**1/256 = 0.390625%**. This is a descriptive comparison, not proof of equal
population probabilities or a statistical advantage.

Crucially, the R2 and R3 byte-match sets are not identical:

- **2 pairs** match the byte condition at **both R2 and R3**.
- 1004 of the previous R2 matches do not match at R3.
- 1030 R3 matches did not match at R2.

Every pair already meets the byte condition at R1. Therefore those two
shared pairs are genuine consecutive weak partial continuations through
**all three rounds**. They occur at original cohort indices **71790** and
**138563**. The conditional fraction within the 1006 R2 survivors is
`2/1006`, approximately **0.198807%**; this is a finite-cohort count, not an
estimate certified here with a new population confidence interval.

[Both explicit witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/survivor_witnesses.json)
contain the complete original input pairs and **all six output states**
(two executions at each of R1, R2 and R3). For each witness, the output XOR
at byte 252 is zero at every one of the three depths. The independent
Python model and the direct original C APIs verify each saved state.
These are truncated byte matches, not full-state collisions, digest
collisions, or matches of the stronger W pattern.

### Exact R3 exclusion of universal constant linear parities

The first **2080** full R3 difference vectors are preserved in the
[rank archive](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/gcc_r3_differences.bin). They have
GF(2) rank **2048**; the augmented vectors `(difference,1)` have rank
**2049**, reproduced using both pivot orders.

As in the R2 proof, any nonzero output mask with a parity constant on
**every base in the prescribed inbound class** would define a nonzero
affine equation annihilating all augmented rows. Full rank excludes it.
Thus every nonzero full-state linear output parity takes both values
somewhere in this inbound class at complete R3.

This is a new deterministic certificate at R3. It is not inferred from
R2: nonlinear composition could otherwise change which relations hold.
It excludes universal constant parities, not occasional partial matches,
nonperfect biases, special backgrounds or general rebound attacks.
The two explicit continuations are fully compatible with this theorem.

### Evidence scope and replay

This extension reuses the original cohort. It supplies exact finite counts,
existence witnesses and a deterministic rank exclusion. **No fresh population
confidence intervals are claimed**, and the original R2 confidence bounds
are not transferred to R3. Neither replay nor extending the depth increases
the number of independently drawn bases. Independence of byte events at
successive depths is not assumed.

Replay with:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/rebound_r3/audit.py
python3 attack_ledger/manifest.py
```

The one-time [producer](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/run.py) refuses to overwrite
its saved plan. GCC and Clang produce identical R3 projections and byte
flags for all 262144 pairs, and identical full R3 rank vectors. The
[independent audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/audit.py) also:

- Verifies every parent/source hash and independently recounts all marginal
  and joint R2/R3 matches.
- Replays **66 input pairs**, including both consecutive survivors, through
  the separate Python permutation at **all three complete depths**.
- Rechecks both explicit survivor pairs with the original C APIs at depths
  1, 2 and 3, comparing the entire output states.
- Reproduces the ordinary and augmented R3 ranks with independent Python
  high- and low-pivot GF(2) elimination.

See [result](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/result.json),
[audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/audit.json),
[consecutive survivors](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r3/survivor_witnesses.json),
and [artifact manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json).

### Answer to the blocking question

**Not completely blocked in the literal sense of no surviving partial
matches:** two witnessed pairs retain the weak byte condition through R3.
**No effective three-round rebound attack has been demonstrated:** the
marginal byte rate is close to the generic reference, and no full W-target
match was observed. **Complete rebound-family exclusion remains unproved.**
Zero full-pattern matches in a finite cohort cannot prove that a full-pattern
continuation is impossible elsewhere. These are unrestricted permutation
inputs; the inherited H159 reachability limitation still applies. No
three-round hash collision attack, general work-factor lower bound or
statement about all rebound strategies follows. Original implementation,
research documents and parent REB-001 evidence remain unchanged.

## REB-001-R4 — round-four endpoint and consecutive-chain extension

Added 2026-11-14. **Neither of the two prior consecutive weak matches
survives the same byte condition at complete round 4.** No pair in the
preserved cohort meets that condition at every round through R4. However,
R4 endpoint matches and R3→R4 partial matches still exist. These finite
results do **not** prove that the rebound family is completely blocked.

This extends REB-001 and REB-001-R3, preserving all previous evidence.
It is not a new attack family, a new random sample, or a general security
proof.

### Fixed construction and complete-round evaluation

Use exactly the same 262144 original input pairs, prescribed Chi1 inbound
transition, fixed initial Delta, W target **0x00440100**, and output byte
**252**. The new [plan](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/plan.json) is saved before
computing R4 and pins the original sources, parent input construction,
raw draws, inverse prefix, and saved R1/R2/R3 observations.

The [bridge](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/bridge.c) includes the unchanged
original REB-001 constructor, reconstructs both original initial states,
and evaluates `krakken_permute_scalar_rounds(state,4)` on each. This uses
all layers and original constant indices **0,1,2,3**. It does not append a
new round with reset constants or extrapolate a result from R3.

### Exact finite-cohort counts

| Complete depth | Full fixed W-pattern matches | Byte-252 endpoint matches | Byte-252 matches at every depth so far |
|---|---:|---:|---:|
| R1 | 262144 | 262144 | 262144 |
| R2 | 0 | 1006 | 1006 |
| R3 | 0 | 1032 | 2 |
| **R4** | **0** | **1000** | **0** |

The endpoint count answers whether the byte matches **at that depth**.
The cumulative count imposes the additional requirement that it matched
at **every earlier depth** as well. Those are different events.

The original consecutive survivors, indices **71790** and **138563**,
both lose the byte condition at R4. Their full initial pairs and all eight
output states (two executions at each of four depths) are preserved in
[the transition witnesses](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/chain_witnesses.json).
The independent Python model and direct original APIs verify the outcomes.

There are nevertheless **3 pairs** matching the byte at both R3 and R4:
indices **19237, 108336, 108440**. All three fail the byte condition at R2,
so none is a four-round consecutive survivor. Their complete input/output
witnesses are preserved in the same file and independently checked.

The R4 endpoint rate is **1000/262144 = 0.3814697265625%**, close to the
one-byte generic reference **1/256 = 0.390625%**. This descriptive comparison
does not establish equal population probabilities, nor does it demonstrate
a useful advantage. No full W-pattern continuation or reappearance is
observed at R4 in this cohort; zero observed matches is not an impossibility
proof over the much larger inbound domain.

### What the disappearing chains do and do not mean

Requiring the **same physical byte** to remain unchanged at every round
is an extra trail condition. A general differential or rebound attack need
not satisfy it: intermediate differences and predicates may change. Thus
zero cumulative survivors here does not rule out all useful four-round
endpoints, other characteristics, special backgrounds, nonlinear predicates,
or other rebound constructions.

Conversely, a single-byte endpoint match is a weak partial event that can
occur for generic outputs. It need not disappear completely as the round
count increases. The observed R3/R4 partial matches therefore do not by
themselves demonstrate a weakness. No independence of successive round
events is assumed, and no generic independence benchmark is promoted to
a theorem about Krakken.

### Fresh exact R4 constant-parity certificate

The first **2080** actual full R4 XOR-difference vectors are saved in the
[rank archive](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/gcc_r4_differences.bin). Their GF(2)
rank is **2048**; augmenting every row with a final 1 gives rank **2049**.
The native checker and independent Python eliminations with opposite
pivot orders agree.

Any output parity constant on **every base in the prescribed Chi1 inbound
class** would supply an affine equation annihilating all augmented rows.
Full rank excludes every such nonzero output mask at complete R4. This is
an exact exclusion of **universal constant linear parities** for this
specific conditioned class, freshly checked at R4 rather than inferred
from earlier depths.

It is compatible with occasional endpoint matches and proves no numerical
bound on nonperfect biases, rare-event probabilities or an optimal attacker's
work. The certificate does not exclude the whole rebound family.

### Replay, checks and statistical scope

Replay the extension with:

```sh
cd ~/security/reproduce/attack_ledger_20261114/replay
python3 attack_ledger/rebound_r4/audit.py
python3 attack_ledger/manifest.py
```

The one-time [producer](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/run.py) refuses to overwrite
its saved plan. The new [audit](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/audit.py):

- Replays **all 262144 pairs** at complete R4 with Clang and compares every
  projection, byte flag and full rank vector with the GCC stream.
- Independently recounts endpoint, adjacent-depth and cumulative matches.
- Replays **69 pairs** through all four complete depths with the independent
  Python model, including both prior consecutive survivors and all three
  R3/R4 partial survivors.
- Verifies the full output states of every explicit transition witness
  using the original C APIs independently at depths 1,2,3,4.
- Recomputes the ordinary and augmented R4 ranks with both pivot orders.

See [results](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/result.json),
[audit record](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/audit.json),
[explicit transitions](reproduce/attack_ledger_20261114/snapshot/attack_ledger/rebound_r4/chain_witnesses.json), and
[manifest](reproduce/attack_ledger_20261114/snapshot/attack_ledger/MANIFEST.json).

This reuses the original cohort and adds no independent random draws.
The counts are exact for that finite cohort; **no new population confidence
bounds are claimed**, and the original R2 bounds are not transferred to
R4. Compiler replay adds implementation assurance, not statistical sample
size. These are internal audits, not external proof verification.

### Scoped conclusion

**The two tracked chains stop at R4, and no tested pair satisfies the weak
byte condition at every depth through R4.** But partial R4 endpoint matches
remain, and complete blocking of the class or rebound family is unproved.
No useful four-round rebound advantage has been demonstrated by these tests.
The inherited unrestricted-state/H159 reachability limits still apply;
no hash collision attack, general work-factor bound or eight-round security
claim follows. Original implementation, research documents and all parent
ledger evidence remain unchanged.


## VULNS(5) review — five-cell H159 exclusion and complementary evidence (2026-11-15)

Reviewed [VULNS(5).md](<reproduce/vulns5_20261115/VULNS(5).md>) and its supplied
companions against research 01–11. The source-only pass initially ignored the
existing ledgers; its early “new” or “unresolved” labels must therefore be read
in their historical context. This section records the useful additions and
separates them from existing or stronger results. The full original document,
three campaign archives, companion programs, CSVs and rebound witnesses are
preserved under [reproduce/vulns5_20261115/](reproduce/vulns5_20261115/README.md).

### V5-H159-61-FIVE — five-cell exclusion, replayed

**Computer-assisted restricted-family theorem.** For every pair of distinct
valid exactly 159-byte messages, with fixed padding byte `0x86` and zero initial
capacity, whose first-Chi input difference occupies **exactly five aligned
serial cells**,

> **A1=6 implies A2>=2.**

Here activity counts the individual byte S-box calls, two per serial cell.
This excludes `[6,1]` throughout that quantified five-cell population, for
all admissible base-message pairs. It extends NOTE-015's four-cell exclusion.
The precise proof and all source-to-model limitations are preserved in
[the five-cell report](reproduce/vulns5_20261115/packages/krakken_61_fivecell/KRAKKEN_H159_61_FIVECELL_2026-11-14.md),
record label `WORK-H159-61-FIVECELL-2026-11-14` (K-15 in VULNS).

| Stage | Recorded/reproduced result |
|---|---:|
| Complete five-cell census, inherited full support sweep | C(128,5)=264,566,400 |
| Rank-deficient supports / overlapping kernel assignments | 899 / 2,681 |
| Exactly-five-cell nonzero differences | 1,937 |
| Differences locally admitting A1=6 | 140 (21 with minimum 5, 119 with minimum 6) |
| Enumerated post-Chi1 differences for A1=6 | **3,599,561** |
| Complete one-active-Chi2 target inventory | **4,177,920** |
| Source-target pairs satisfying all 32 carry-free equations | **36,727** |
| Survivors of all 32 independent full-width addition support tests | **0** |

**Proof mechanism.** Pull the 16 bits of each candidate serial cell backward
through the exact linear prefix. H159 reachability requires bits 1272–2047
of the inverse image to vanish, giving a 776-by-80 homogeneous system for
each five-cell support. A projected full-rank test can safely reject supports;
retained supports use the complete syndrome. Exhaust the nonzero kernels and
retain only differences nonzero in all five cells.

For all 140 six-call-eligible differences each occupied cell has nonzero
first-call input difference. Thus A1=6 requires four first-only cells and
one double-active cell. In aligned coordinates `u=S(a XOR b)`,
`v=S(b XOR u)`, enumerate supported `du` at `dx=da XOR db`, and supported
`dv` at `db XOR du`, with the actual shared `du` retained. This covers all
necessary local post-Chi possibilities without assuming independent actual
message bases across cells.

Map these source differences through Butterfly; map every one-active Chi2
input target backward through the next linear prefix and inverse Ink. The
round constant cancels in XOR differences. Only 36,727 pairs satisfy Pressure's
32 exact carry-free bit-zero relations. Each is then checked against the
exact XOR-differential support relation of each isolated 64-bit addition.
For one addition set `q=dx XOR dy XOR dz`: `q[0]=0`, and for bits `i=0..62`,
`dx[i]=dy[i]=q[i]` requires `q[i+1]=dx[i]`. These conditions characterize one
addition's support. Testing the 32 additions separately relaxes shared-base
compatibility; every actual Pressure transition must still pass all tests.
None does, establishing the exclusion for this class.

**Fresh checks in this review.** All 19 embedded archive checksums verified;
C/H match the original project. GCC and Clang each rebuilt and reran the
classifier and the full endpoint enumeration. Their three generated CSVs
(classification, 140 eligible differences, endpoint results) match the original
archive **byte for byte**. The supplied Python verifier passed and replayed
an actual valid H159 **[A1,A2]=[6,256]** control pair, counting S-box inputs
independently in Python and comparing the complete two-round original API.

The 264-million-support scan was **not repeated**. Instead, all 899 retained
supports and their exact nullities were compared with our existing independently
reviewed classification and match exactly after coordinate translation:
new ID `32*p+8*y+q` corresponds to old ID `32*y+8*p+q`. This cross-check matters:
the two raw integer lists initially look different. See
[SUPPORT_CROSSCHECK.json](reproduce/vulns5_20261115/SUPPORT_CROSSCHECK.json).
The replay uses the supplied C algorithms; it is not a separately authored
source-to-model proof or proof-assistant formalization. CSV summaries alone
are not proof objects for every arithmetic rejection. Full assurance details,
controls and original compiler-coverage limitations remain in the report.

### V5-H159-20 — composable eight-round corollary for supports of at most five cells

Accept the established global adjacent-round floor `A_r+A_(r+1)>=4`, the
H159 first-round minimum 5, all-family `A1=5 => A2>=4`, NOTE-015 and the
five-cell theorem above. Every valid H159 pair whose pre-Chi1 difference
occupies **at most five cells** then satisfies

> **A1+A2>=8 and sum(A1..A8)>=20.**

Proof: if A1=5, the first pair totals at least 9. If A1=6, the four-/five-cell
exclusions give A2>=2; smaller supports are excluded by the established H159
classification. If A1>=7, bijectivity gives A2>=1. In every case the first
pair totals at least 8. Pair `(A3,A4)`, `(A5,A6)`, `(A7,A8)` to add at least
12. The A1=5 subclass retains its stronger existing floor 21.

**Remaining global case:** an H159 `[6,1]` trail must now have **exactly six
occupied pre-Chi1 cells**, each contributing precisely one active S-box.
More than six cells would force A1>6. This is a necessary structure for the
remaining case, not an existence claim. The number of six-cell supports is
C(128,6)=5,423,611,200; no complete six-cell exclusion is supplied here.
The global unrestricted/H159 floors remain **16/19**. Activity counts do not
by themselves give differential-hull, collision or preimage security bits.

The earlier selection table's “five-/six-cell … not tested here” row describes
the original imported attack ledger; this addendum supersedes it for the
five-cell class only. It does not change any earlier completed campaign status.

### V5-CAMPAIGNS — complementary methods; historical open cases already closed

K-11 through K-14 are useful source-only campaign records, preserved with
full programs, CSVs and mathematical notes. They do not replace the stronger
current ledger results.

| Entry | Preserved contribution | Relation to current research |
|---|---|---|
| K-11 | 6,171/32,768 [1,1] location pairs excluded by support/linear gates | Historical partial stage, superseded by K-12 and existing complete exclusions |
| K-12 | All 32,768 [1,1] locations excluded; 2,699,281,108 nonzero assignments; zero survivors | Alternative full exclusion; its stated total floor 3 is weaker than our established adjacent-round floor 4 |
| K-13 | Same-word-pair restricted [1,2]/[2,1] filters: 182,169/360,448 supports excluded; 178,279 cutoff-unknown | Method/coverage records; **does not reopen the previously completed global [1,2] or [2,1] exclusions** |
| K-14 | Full two-/three-bundle [1,3] support census: 29,501,296 linear exclusions plus 47,427 selected addition exclusions | Complementary necessary-condition support certificates; no complete [1,3] exclusion |

K-14 ultimately reports **29,548,723 excluded / 59,924,301 unknown** support
configurations. These counts measure this filter's support coverage, not a
fraction of attacks covered or individual trails. Its global sweeps comprise
2,080,768 two-bundle and 87,392,256 three-bundle supports. This review freshly
recounted the two aggregate 256-position CSVs; the large exhaustive engines
and selected carry scans were **not rerun**. The archive records GCC/Clang
agreement for the complete two-bundle totals and selected byte-0 detailed
carry table; not all full triple-support scans received a second compiler
run. Preserve those limits when using the counts.

The reusable algorithm avoids enumerating every vector in a large nullspace:
use inclusion–exclusion over required nonzero source/target blocks. For a
kernel of dimension d and a subset T of blocks constrained to zero, the
number of compatible vectors is `2^(d-rank(restriction_T))`. Alternating the
sum over T counts vectors nonzero in every required block exactly. A zero
count excludes that support; a positive count need not be a real nonlinear
trail. Then enumerate only bounded small kernels through exact isolated-addition
conditions, leaving larger kernels explicitly unknown. This is a useful
carry-aware alternative to monolithic optimization, with source maps and
compiler limits documented in
[campaign 03](reproduce/vulns5_20261115/packages/krakken_campaign03/KRAKKEN_TWO_ROUND_BOUND_03.md)
and [campaign 04](reproduce/vulns5_20261115/packages/krakken_campaign04_release/KRAKKEN_TWO_ROUND_BOUND_04.md).

### V5-STRUCTURE — local observations and internal rebound matches

K-01/K-02's diagonal Chi cancellation is already the mechanism behind
`DIFF-TRUNC-001` and several entries above. The particular fixed difference
uses pre-Chi lane 0 bit 32 and lane 4 bit 0, cancelling the first S-box
argument and confining the post-Chi difference to the low byte of lane 4.
The supplied PoC carries a conservative **122-zero-output-bit R1 mask**.
This is another instance/control of our existing unrestricted one-round
truncation family, not a new R2 bound. The older 200-bit set in research 01
uses a different aligned byte site; those numbers should not be compared
as if the difference and location were identical.

The supplied PoC was freshly compiled against unchanged scalar C. It passed
10,000 Chi controls, 10,000 R1 zero-mask pair checks, 20,000 local Pressure
MSB controls and Theta parity/involution checks. All 1,000 tested R2 pairs
violate the same R1 mask. These samples validate implementation behavior;
the universal R1 claim relies on the report's algebraic/dependency argument,
not merely the tests. K-03's deterministic MSB Pressure differences are
instances of the existing local translation structure (`PRESS-TRANS-001`),
not full-round trails. Theta parity conservation and last-round constant
cancellation are also already represented in our analysis.

The follow-up rebound PoC enforces Chi1 `DDT[01,13]=4` by construction and
then targets a preselected Chi2 internal transition. In 1,000,000 conditioned
trials it reports **56** matches of `dx=01,dy=13` at that second site, and
**10** matches forcing two specified Chi2 input-byte differences to zero.
These are useful actual internal matching witnesses, but the remaining
Chi2 is dense and no predeclared output-only distinguisher follows.
The supplied baseline comparisons are explicitly heuristic; no independence
of intermediate differences is proved. These are inherited campaign counts,
not rerun during this review. Both full-state witness files and the C
constructor are preserved. They are distinct parameter choices from REB-001
above, not evidence of a new hash-message attack or enhanced R2 probability.

The empirical bit-bias screens (eight differences, 50,000 pairs each),
coordinate-only integral screens, and unstable sample-zero sets are preserved
in the original VULNS document. No raw datasets or full screening scripts are
supplied for all those historical measurements; they are reported observations,
not promoted to new certificates. In particular, sampled extra zero bits that
vanish with more data are not universal invariants. Existing all-mask spanning
certificates are stronger for their own specified domains and cube directions.

### V5-IMPLEMENTATION — useful engineering notes, not new cryptanalytic bounds

- **rc_get:** current scalar source directly returns `rc[round]` without
  initialization or validation. A fresh-process PoC confirms zero constants
  before initialization. For out-of-range indices, pointer arithmetic/access
  can violate the C contract (index 8 can form a one-past pointer, which must
  not be dereferenced). The normal permutation initializes constants first.
  Initialize/validate in a hardened accessor or make it private in a future
  implementation change; no source changes are made by this document review.
- **Native endianness:** the byte/word sponge union and SHAKE state-byte casts
  merit explicit little-endian loads/stores for portability. This is already
  noted in the architecture review; no big-endian replay is supplied here.
- **Reduced-round API:** the original scalar research entry point permits
  reduced counts. The supported Krakken–Kyber wrapper was already fixed to
  eight rounds; that wrapper contract does not remove raw research entry points.
- **Scalar performance:** the reported 1.99 MiB/s is a historical host/compiler
  measurement, not a security theorem or a current benchmark of this machine.
  Fixed traversal of S-box entries alone proves neither timing leakage nor
  complete constant-time behavior.
- **AVX2 visibility:** K-10 saw only scalar C/H. This project includes
  `krakken_multi.c`; missing definitions in that two-file subset do not establish
  a missing implementation in our project. Existing scalar/AVX2 equivalence
  checks remain the relevant evidence.

No whole-permutation break or security-bit certification was found in this
review. The main advance is the replayed five-cell exclusion, its composable
restricted floor 20, and reduction of the outstanding `[6,1]` case to six
single-active cells. See [review checks](reproduce/vulns5_20261115/REVIEW_CHECKS.json)
and the reproduction README for precise replay scope.

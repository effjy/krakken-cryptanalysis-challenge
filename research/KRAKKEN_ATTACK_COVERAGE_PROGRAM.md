# Krakken attack-family coverage and round-margin research program

Working research program, 2026-10-06. This document states the publication
objective and the evidence needed to reach it. It introduces no new theorem
or numerical security claim. Current proved scopes are authoritative in the
[theorem ledger](KRAKKEN_SECURITY_THEOREMS.md), with certificates in the
[artifact manifest](KRAKKEN_THEOREM_ARTIFACTS.md). The
[attack-versus-round map](KRAKKEN_ATTACK_ROUND_MAP.md) records demonstrated
structures; this document guides how to extend that coverage.

## At a glance: where a defined structure stops

**There is no current theorem that round two defeats most attack families.**
There are multiple exact exclusions for complete **defined classes**. These
are the results behind the recurring round-two pattern.

**Reading key:** H = valid padded 159-byte first block; P = unrestricted
permutation; U = uniform unrestricted Pressure base.

“Excluded” below means the stated property is impossible under the theorem's
quantifiers. For a universal balance or relation, it means that no fixed
mask/relation works for every base; special bases or nonperfect biases may
remain. It does not mean every individual quartet, cube or differential
trajectory disappears. **Chi2 is inside R2; Pressure1 is inside R1.**

### Excluded before or within round one

| Defined structure / family | Structure before the obstruction | First certified obstruction | Exact scope and result | Theorem |
|---|---|---|---|---|
| One-cell first-block boomerang / rebound embedding | Perfect local Chi structures exist in unrestricted states | **First-block reachability gate, before Chi1** | No nonzero H first-block input difference confined to one Chi cell; rebound also excludes one-cell post-Chi support | [BOOM-EMBED-001](KRAKKEN_SECURITY_THEOREMS.md#boom-embed-001), [REBOUND-002](KRAKKEN_SECURITY_THEOREMS.md#rebound-002) |
| Fewer than five active first-Chi calls | Arbitrary candidate valid-message difference | **Chi1** | Every nonzero H difference has A1≥5, sharp; first full 160-byte block also has minimum 5 | [DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001), [DIFF-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004) |
| Low affine hull of a single message-byte plane | Input hull dimension 8 | **Chi1** | All 159 zero-base byte planes reach hull dimension 255; excludes universal containing spaces of dimension ≤254, not special cosets | [SUBSPACE-001](KRAKKEN_SECURITY_THEOREMS.md#subspace-001) |
| Theta-cancelling two-byte affine structure | For all 256 defined cosets, post-Chi1 hull dimension 238–254; XRBD preserves it | **Pressure1** | Every coset in the bytes-40/56 plane reaches maximal hull dimension 255; also true with XRBD off | [SUBSPACE-002](KRAKKEN_SECURITY_THEOREMS.md#subspace-002) |
| Perfect full-message affine relation | Proposed fixed message/state affine masks | **Complete R1**, and separately each R2–R8 | No nontrivial perfect relation for any masks over H. Nonperfect correlations remain open; rank bound is numerically weak | [LIN-GLOBAL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-global-001) |
| Perfect uniform lane-rotation covariance | Proposed common rotation plus fixed correction | **Complete R1**, and separately each R2–R8 | All 63 nontrivial rotations excluded, with constants on and off; statistical rotational bias is not bounded | [ROT-001](KRAKKEN_SECURITY_THEOREMS.md#rot-001) |
| Missing first-order input/output dependency | Hypothesis that an output bit never responds to one message bit | **Complete R1**, also R2 | Every one of the 1272×2048 pairs has an influence witness; this is dependency coverage, not an attack exclusion | [DEPEND-001](KRAKKEN_SECURITY_THEOREMS.md#depend-001) |

### Exact exclusions at or by round two

| Defined structure / family | Last demonstrated structure | Certified stopping point | What is actually excluded | What remains open / theorem |
|---|---|---|---|---|
| One-cell boomerang continuations | Local perfect family embedded and propagated in the defined campaign | **Chi2** | Required quartet relation for the four fixed choices/one-site/zero-background family; 4,784 saved reached patterns each have an all-local-base obstruction | Other sites, backgrounds and coordinated embeddings; [BOOM-ROUND-001/002](KRAKKEN_SECURITY_THEOREMS.md#boom-round-001) |
| Unrestricted `[1,1]` differential activity | One active Chi1 call can occur | **Chi2 activity** | Every unrestricted two-round `[1,1]` trail is impossible; total activity ≥3 | This does not exclude general differentials; [DIFF-PERM-002](KRAKKEN_SECURITY_THEOREMS.md#diff-perm-002) |
| Defined `[1,2]` activity classes | Candidate one-call then two-call supports | **Chi2 activity** | Complete distinct AA, distinct BB and same-pair mixed classes excluded | Distinct AB ongoing, BA open: global `[1,2]` remains open; [DIFF-12-004](KRAKKEN_SECURITY_THEOREMS.md#diff-12-004), [005](KRAKKEN_SECURITY_THEOREMS.md#diff-12-005), [006](KRAKKEN_SECURITY_THEOREMS.md#diff-12-006) |
| Three selected minimum-A1 message differences | Valid A1=5 first-round activity | **Chi2 activity** | Under A1=5, A2≤2 is impossible for these three fixed H differences | Universal implication for all A1=5 pairs open; [DIFF-RATE-003](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-003) |
| Perfect differential-linear output masks | Defined large perfect-mask spaces after complete R1 | **Complete R2** | For each of 128 fixed unrestricted delta=1 differences, every nonzero output mask has nonconstant derivative parity | Other differences and useful nonperfect correlations; [DL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-001), [DL-002](KRAKKEN_SECURITY_THEOREMS.md#dl-002) |
| Byte-0 integral / division-property masks | Exactly seven universal masks after complete R1 | **Complete R2** | No nonzero universal linear output-mask balance, including digest masks, for this fixed H cube | Other cubes, special-base balances and nonlinear output functions; [INT-BYTE-002](KRAKKEN_SECURITY_THEOREMS.md#int-byte-002), [DIV-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#div-byte-001) |
| All one-byte coordinate cube families | R1 universal balances are not claimed for every byte | **Complete R2** | Every one of 159 byte families has no universally balanced output coordinate: all 325,632 byte/output-bit combinations covered | Non-coordinate masks and special bases; [INT-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#int-byte-001) |
| Defined 14-direction H cube | Exactly 32 universal coordinate balances after complete R1 | **Complete R2** | None of the 2048 coordinates is universally balanced for the fixed directions at message bits 0–13 | Other directions and non-coordinate output masks; [INT-CUBE-001](KRAKKEN_SECURITY_THEOREMS.md#int-cube-001) |
| Saved kernel-directed eight-dimensional H cube | Exactly 32 universal linear-mask generators at complete R1 | **Complete R2** | Universal mask space has dimension zero for the saved direction set | Other direction sets in the 248D kernel and special cosets; [INT-KERNEL-001](KRAKKEN_SECURITY_THEOREMS.md#int-kernel-001) |
| Nonlinear predicates of a saved kernel cube | Exactly 64 universal R1 predicates (56 nonlinear), per eight-bit projection | **Complete R2**, and separately **R3–R8** | Among all 2^256 truth tables of each of 16 projections, only constants retain base-independent parity | Other cubes, joint/wider windows, special backgrounds and statistical integrals; [INT-NONLINEAR-001](KRAKKEN_SECURITY_THEOREMS.md#int-nonlinear-001) |
| Perfect checkpoint-to-output nonlinear common labels | Sixteen matching R1 pairs have q^16 solutions, including nonlinear Boolean predicates | **Complete R2**, separately **R3–R8** | All specified 175 × 48 observation pairs admit only constant common labels; arbitrary label truth tables covered | Wider/joint observations, statistical labels and special message subsets; [PARTITION-001](KRAKKEN_SECURITY_THEOREMS.md#partition-001) |
| Mixed first-checkpoint/output Boolean equations | Sixteen matching R1 cases have exact ideal <e0,e1>; 2,047 nonzero equations of degree ≤2 | **Complete R2**, separately **R3–R8** | All 175 × 48 four-bit/four-bit pairs have full joint support, excluding every nonzero universal Boolean equation in those eight coordinates | Wider/joint windows, special subsets, statistical equations and algebraic solving complexity; [ALG-REL-001](KRAKKEN_SECURITY_THEOREMS.md#alg-rel-001) |
| Fixed four-state zero-sum square | Full-state zero sum through Chi1/XRBD1; 32 projected R1 balances | **Complete R2** | No universal coordinate at all 128 sites; no universal nonzero output mask at the one representative site | Other sets, masks at other sites, special backgrounds; [ZERO-001](KRAKKEN_SECURITY_THEOREMS.md#zero-001) |
| Complete Pressure deterministic translations | All 16D internal cosets remain affine through first-round suffix | **Complete R2** | All 65,535 nonzero directions lose universal vector differences, even in first 256 bits; two saved cosets have full output/graph hulls | Hash reachability, other cosets and nonperfect behavior; [PRESS-TRANS-001](KRAKKEN_SECURITY_THEOREMS.md#press-trans-001) |
| Two consecutive deterministic Pressure transitions | First Pressure transition is deterministic in nonzero U | **Next Chi/XRBD, before Pressure2** | Every base and all 65,535 U directions: the next Pressure difference is outside U | Other Pressure directions and nonunit probabilities; [DIFF-WINDOW-001](KRAKKEN_SECURITY_THEOREMS.md#diff-window-001) |
| Globally low-degree state-coordinate model | Exactly 32 R1 coordinates have degree 13 | **Complete R2**, separately R3–R8 | Every coordinate has degree ≥20; hence no coordinate has a global degree≤19 polynomial | Does not imply every low-order cube is unbalanced or defeat all algebraic attacks; [ALG-DEG-001](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-001) |

The direct-interface subclass of [PARTITION-001](KRAKKEN_SECURITY_THEOREMS.md#partition-001)
excludes nonconstant perfect labels between any raw message byte and any
raw digest-projection byte already at **complete R1**, and separately at
R2–R8 (40,704 pairings). R8 uses the public digest. This does not assert
statistical independence or exclude arbitrary joint nonlinear relations.

[ALG-REL-001](KRAKKEN_SECURITY_THEOREMS.md#alg-rel-001) likewise proves
full support already at **complete R1** for all raw message/digest low-nibble
pairs, separately through R8. It covers arbitrary mixed equations, with
narrower observations than PARTITION-001. Both statements concern the full
valid159 domain; neither asserts statistical independence.

### Finite tested patterns and empirical screens: separate from class exclusions

| Structure | Last positive result | Where the recorded continuation fails | Evidence status and remaining space |
|---|---|---|---|
| Coordinated multi-cell boomerangs | Exact P full-state four-state zero sum after complete R1 | **Chi2** for all 1,344 saved reached patterns | Every saved pattern has an exact zero-count local cell. Finite patterns are exhausted; the whole direction/background family is not. H linear gate excludes 896, leaves 448 unresolved. [BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001) and [round map](KRAKKEN_ATTACK_ROUND_MAP.md) |
| Truncated differential continuations | Defined exact R1 zero projections; sampled H projected biases | **Complete R2** in the specified projection screens | No detected significant continuation is empirical, not a theorem excluding all R2 biases. [DIFF-TRUNC-001](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001) and [screen report](KRAKKEN_TRUNCATED_DIFFERENTIAL.md) |

### Which “global round-two theorem” might this refer to?

The closest broad round-two exclusions are:

- **INT-NONLINEAR-001:** all predicates of each specified eight-bit output
  projection, for the one saved H cube. The exclusion holds at each R2–R8
  separately; it is not an all-cube or joint-projection integral theorem.

- **INT-BYTE-001:** all 159 one-byte cube families and all 2048 output
  coordinates. Global within that coordinate-cube class; not all integrals.
- **DL-002:** every output mask, but only 128 fixed input differences.
  Global over masks within that differential-linear class; not all differences.
- **PRESS-TRANS-001:** every nonzero member of the complete deterministic
  Pressure translation space, but not every permutation difference.
- **ALG-DEG-001:** every state coordinate at R2–R8 has degree at least 20.
  This excludes globally low-degree coordinate models, not most attack types.
- **LIN-GLOBAL-001:** all message/output affine masks, already at R1 and
  separately through R8. It excludes perfect linear relations, not every
  linear distinguisher.

No combination of those statements proves “most attacks fail at R2”: there
is no defined measure on attacks that makes “most” meaningful here. The
accurate visible pattern is **multiple defined structures have exact R2
exclusions, and some have earlier R1 exclusions**.

### Inventory review: results that do not establish an attack endpoint

All **69 permanent IDs** in the current inventory were reviewed for this
classification. The tables above highlight structure-loss results. The
remaining results supply quantitative bounds, local descriptions, positive
structures, intermediate exclusions or proof tools; they must not be presented
as attacks ending at a round:

| Result group | IDs reviewed | Why it is not a stopping-round claim |
|---|---|---|
| Local Chi, rebound and boomerang spectra/fibers | LIN-CHI-001/002, BOOM-LOCAL-001/002, DIFF-CHI-001/002, DL-LOCAL-001, REBOUND-001 | Local maxima, exact fibers or perfect local structures; full-round continuation needs additional reasoning |
| Checkpoint and complete-R1 differential probability | DIFF-RATE-002, 005–008, CHI-RATE-001, DIFF-ACT-001 | Exact laws/bounds with stated differences, projections and distributions; a small point probability is not disappearance of all attacks |
| Initial `[1,2]` campaign filters | DIFF-12-001/002/003 | Earlier partial exclusions superseded in coverage by the complete BB class; not extra independent attack families |
| Diffusion and accumulated activity | DIFF-PERM-001, DIFF-MULTI-001 | Chain activation and conservative multiround totals; trajectories remain possible |
| Pressure mask/carry/projection tools | PRESS-WALSH-001/002/003, PRESS-DIFF-001/002/003, PRESS-HULL-001, PRESS-ZERO-001, DIFF-SCREEN-001 | Defined local counters/bounds, zeros, necessary gates or method limitations; no universal complete-round endpoint |
| Exact layer structure and residual identities | LIN-THETA-001, ROT-002 | Fixed spaces, cycles or exact residual equations of defined layers/transforms; no full-round attack exclusion |
| Degree and hull foundations | ALG-DEG-002, LIN-HULL-001 | Coordinate degree maps or signed Fourier identities, not all-attack resistance |
| Selected-space complete-R1 linear bounds | LIN-RATE-001/002/003/004 | Quantitative one-round statements for selected masks; useful all-mask multiround hull remains open |

This is a documentation review against the ledger, not a new rerun of all
cryptanalytic certificates. Grouped entries retain their original audit limits.
The detailed coverage matrix below remains the place to plan the next searches.


## Publication objective

The intended eventual statement is:

> We systematically evaluated the major known cryptanalytic attack families
> against the current Krakken-2048 construction. No demonstrated attack or
> exact exploitable structure has been propagated beyond two complete rounds.
> The full construction uses eight rounds, leaving six rounds beyond the
> deepest presently known structural attack.

**This is a research target, not an established finding.** Before publication,
define “attack,” “exploitable structure,” the interface, resource model and
round boundaries, and check the statement against all recorded positive
results and relevant outside cryptanalysis. “Deepest presently known” needs a
dated literature review; our own campaign alone establishes “deepest
reported in this campaign.” The ledger does not currently establish a single
maximum attack depth across all families.

An exact local relation, an activity witness, or an algebraic-degree
certificate is not automatically a complete attack. Conversely, failure to
preserve one convenient structure does not exclude another attack in its
family. Distinguish chosen internal-state distinguishers from attacks at the
hash interface, and distinguish a full-state observation from a digest attack.

A statement supported by the current record is:

> Across several precisely defined cryptanalytic classes, Krakken exposes
> identifiable first-round structure, while the second round often prevents
> the universal closure or exact continuation required by those constructions.
> The accompanying certificates state which classes are excluded and which
> continuations remain open.

## What a round margin would mean

If the deepest demonstrated attack in a specified model reaches two complete
rounds and the deployed construction has eight, `8−2=6` is a descriptive
round-count gap relative to that model's known attack depth. It does not
establish six independently secure rounds, an attack-complexity lower bound,
or any number of security bits. Margins can change when new attacks appear.
Report separate depths for unrestricted permutation, first-block hash, and
variable-length hash models rather than combining their evidence.

Loss of a structure at round two is worth proving. It is **not** a general
monotonic attrition theorem: later layers may create or restore a different
structure, and an attacker may target a later internal boundary or use a
hybrid construction. A failed forward continuation also does not exclude a
backward, meet-in-the-middle, or globally coordinated attack. Continue to test
later-round reconvergence and constructions designed across several layers.

## Coverage matrix and open continuations

**P:** unrestricted permutation states. **H:** valid 159-byte first block,
fixed `0x86` pad and zero initial capacity. **U:** uniform unrestricted
Pressure bases. Checkpoints such as Chi2 are not complete round two.
A row describes the cited class, not every attack carrying that family name.

| Family | Existing structure or exact result | Boundary and scope | Next obligation / possible hybrid |
|---|---|---|---|
| Differential | [DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001): exact H first-Chi minimum 5; [DIFF-RATE-008](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-008): unconditional complete-R1 point bound for three fixed differences | Checkpoint activity and fixed-difference R1 bounds; not all-difference complete-round hulls | Complete the distinct AB/BA activity campaign; seek sound coarse H bounds and useful differential hulls |
| Truncated differential | [DIFF-TRUNC-001](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001): guaranteed R1 zero projections | P one-cell class; R2 bias screen is empirical | Search other projections, correlated supports and boomerang/truncated hybrids; preserve positive findings |
| Impossible differential | [DIFF-PERM-002](KRAKKEN_SECURITY_THEOREMS.md#diff-perm-002): unrestricted `[1,1]` excluded; defined `[1,2]` classes closed | Activity exclusions do not exhaust forward/backward impossible differentials; AA closed, AB ongoing, BA open | Explore incompatible middle constraints with both directions propagated; quantify every exhausted endpoint class |
| Linear | [LIN-GLOBAL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-global-001): no perfect H affine relations at R1–8; [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004): strong selected-space complete-R1 bound | Global perfect-relation exclusion; useful quantitative all-mask hull still open | Arbitrary coupled Pressure masks and signed rate-restricted hull sums; carry-aware multi-round masks |
| Differential-linear | [DL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-001): defined perfect R1 spaces; [DL-002](KRAKKEN_SECURITY_THEOREMS.md#dl-002): defined all-mask perfect R2 continuations excluded | P specified differences; nonperfect correlations remain open | Measure or bound nonperfect continuations and hybrid differential prefixes |
| Boomerang / rectangle | [BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001): coordinated P one-round four-state zero sums | All 1,344 saved Chi2 patterns obstructed; backgrounds not exhausted; H gate leaves 448 unresolved candidates | Jointly chosen backgrounds and carries; actual valid-message quartets; broader multi-cell continuations |
| Rebound | [REBOUND-001](KRAKKEN_SECURITY_THEOREMS.md#rebound-001): exact defined inbound counts; [REBOUND-002](KRAKKEN_SECURITY_THEOREMS.md#rebound-002): H single-cell support exclusion | Local/Chi1/XRBD1 results, not universal complete-round attack depth | Outbound differential probability, multi-cell matching and forward/backward composition |
| Integral / higher-order / cube | [INT-CUBE-001](KRAKKEN_SECURITY_THEOREMS.md#int-cube-001), [INT-KERNEL-001](KRAKKEN_SECURITY_THEOREMS.md#int-kernel-001): exact defined R1 balances and R2 universal-mask exclusions | H defined cube families; other cubes, special cosets and statistical balances open | Adversarial directions, higher-dimensional cubes and differential-integral hybrids |
| Nonlinear-output integral | [INT-NONLINEAR-001](KRAKKEN_SECURITY_THEOREMS.md#int-nonlinear-001): exact 64-predicate R1 space with 56 nonlinear functions | Fixed H cube; only constants at every R2–R8 in each specified eight-bit projection | Joint/wider projections, other cubes and statistical/special-base continuations |
| Perfect nonlinear partition / common label | [PARTITION-001](KRAKKEN_SECURITY_THEOREMS.md#partition-001): exact q^16 matching R1 label families; complete arbitrary byte-label classification | H; all other pairings constant-only, including all R2–R8; direct message/digest-byte subclass excluded already at R1 | Wider/joint observations, nonperfect statistical partitions, special subsets and multiblock inputs |
| Mixed algebraic equations | [ALG-REL-001](KRAKKEN_SECURITY_THEOREMS.md#alg-rel-001): exact R1 matching ideal and full-support exclusions for every Boolean equation on specified eight coordinates | H; all specified R2–R8 pairings full support; raw message/digest low-nibble subclass full already at R1 | Wider/joint windows, equations on special subsets, approximate relations, message-pair equations and large-system algebraic attacks |
| Division property | [DIV-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#div-byte-001): byte-0 family exact universal mask dimensions 7 at R1, 0 at R2 | H defined byte family only | Other division-property families and higher-order continuations |
| Subspace / invariant-subspace | [SUBSPACE-001/002](KRAKKEN_SECURITY_THEOREMS.md#subspace-001): full affine hulls for defined H subspaces/cosets | Defined families; not classification of all invariant subspaces | Deliberately aligned subspaces, special cosets, affine partitions and nonlinear invariants |
| Pressure translations | [PRESS-TRANS-001](KRAKKEN_SECURITY_THEOREMS.md#press-trans-001): complete 16D deterministic space; sharp neighboring cost 135; exact Chi2 point maximum `2^-184` | U for probability; all 65,535 P directions lose universal R2 vector differences; two coset rank certificates | [RESULT8](../RESULT8.md) reachability problem; nonperfect and restricted-base behavior; probability after Pressure2 |
| Rotational / symmetry | [ROT-001](KRAKKEN_SECURITY_THEOREMS.md#rot-001): defined universal affine covariance excluded at R1–8 | P specified rotations; absence of exact covariance is not absence of rotational bias | Approximate symmetry probabilities, broader transformations and hybrid trails |
| Algebraic degree / algebraic attacks | [ALG-DEG-001/002](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-001): source-specific degree bounds and witnesses | H coordinate/projection statements; degree does not itself establish equation-solving complexity | Algebraic relations, elimination and cube-based attacks beyond these degree certificates |
| Zero-sum | [ZERO-001](KRAKKEN_SECURITY_THEOREMS.md#zero-001): defined square and universal balance spaces | P specified sites/classes, not all possible zero-sum sets | General constrained zero sums, special bases and partition-based constructions |
| Hash collision / preimage / distinguishers | [Truncated collision experiment](KRAKKEN_COLLISION_EXPERIMENT.md) and source/interface audits | Scaled experiments and construction checks; not a full-digest complexity lower bound | First-block versus multiblock attacks, capacity evolution, backward search and model-specific reductions |

This matrix intentionally includes gaps. Representing a family in a row does
not mean it has been fully evaluated. Related rows can share lemmas and must
not be counted as independent confirmations without explaining their overlap.

## Campaign workflow

1. Specify the source revision, interface, round interval, observed output,
   attack objective, data/work/memory limits and allowed input choices.
2. Construct the strongest plausible adversarial family using known local
   structure. Try to make the attack work, including compatible hybrid paths.
3. Record its exact invariant or exploitable bias and follow it through each
   checkpoint. Include later-round reconvergence rather than assuming R2 ends
   every possibility.
4. Classify the evidence: analytic proof, finite exhaustive proof,
   solver-backed exclusion, empirical screen, or unresolved solver result.
   A relaxed SAT result is a candidate; an unknown/timeout is unresolved.
5. Preserve concrete positive witnesses, even if they contradict the preferred
   round-two picture. For exclusions, name the exact exhausted class and
   quantify the bases, directions, masks and cosets covered.
6. Replay against original C and retain source hashes, scripts, certificates
   and independent implementation audit status. Record actual construction
   and continuation costs; solver difficulty is not attack resistance.
7. Update the coverage matrix and attack-depth records. Promote only the
   closed mathematical statement, with an append-only theorem ID where needed.

For each demonstrated attack or candidate, retain a depth record containing:
source hash/date; P/H/multiblock domain; input and output access; complete-round
count and intermediate checkpoints; distinguisher/attack success criterion;
data, work and memory; precise proved class; reproducible artifact; audit status;
and open continuation. A reduced-round observation becomes a claimed attack
only with a justified success advantage and cost in that model.

## Gate before publishing the proposed six-round margin

- Complete a dated, explicitly scoped coverage review, including outside
  cryptanalysis and hybrid gaps. Name omitted families rather than saying
  “every known attack” without qualification.
- Reconcile all positive examples and identify the deepest actual attack,
  rather than using the deepest theorem checkpoint as its substitute.
- Keep the pinned current XRBD design separate from older designs and their
  historical exposure or attack depths.
- Confirm which statements concern full-state access, digest access, H inputs
  or multiblock hashing. Internal constructions must not silently become hash
  attacks or hash exclusions.
- Give each round-two exclusion its precise quantifiers. Do not infer that
  statistical/nonperfect behavior is absent from absence of perfect closure.
- If the evidence supports only our tested constructions, publish “among the
  constructions evaluated in this campaign, none has demonstrated a useful
  continuation beyond …,” with the boundary and date. Use a stronger sentence
  only when its broader coverage is actually justified.

The objective is a defensible account of known attack depth and proved
resistance classes. The useful result may be a broad round-two pattern, a
later-round surviving construction, or a mixture of both. The documentation
must follow the evidence in each case.

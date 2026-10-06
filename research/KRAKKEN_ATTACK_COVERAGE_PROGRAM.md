# Krakken attack-family coverage and round-margin research program

Working research program, 2026-10-06. This document states the publication
objective and the evidence needed to reach it. It introduces no new theorem
or numerical security claim. Current proved scopes are authoritative in the
[theorem ledger](KRAKKEN_SECURITY_THEOREMS.md), with certificates in the
[artifact manifest](KRAKKEN_THEOREM_ARTIFACTS.md). The
[attack-versus-round map](KRAKKEN_ATTACK_ROUND_MAP.md) records demonstrated
structures; this document guides how to extend that coverage.

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

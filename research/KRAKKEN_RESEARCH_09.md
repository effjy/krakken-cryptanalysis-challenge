# Krakken research 09 — consolidation of the original supporting documents

Date: 2026-11-13. Scope: document comparison and evidence preservation for the
unchanged scalar Krakken permutation. This continues
[KRAKKEN_RESEARCH_08.md](KRAKKEN_RESEARCH_08.md).

## 1. What this integration adds

Twenty documents from `reproduce/docs/` were compared with research ledgers 01–08.
`reproduce/docs/KRAKKEN_SECURITY_THEOREMS.md` was excluded as requested. All **80 theorem
identifiers** found in the other documents already occur in the eight ledgers.
Consequently this integration creates **no new cryptographic theorem ID** and
claims no new security exponent. Identifier coverage is not proof that every
supporting detail was already recorded: the useful additions below are the
experimental detail, proof techniques, counterexamples, model-engineering
results, and evidence provenance that the shorter ledger entries omit.

This file is the consolidated reading account. The complete incoming documents,
directly linked supporting files, and eight collision-trial files are preserved
under [reproduce/docs_integration/](reproduce/docs_integration/README.md).
The [document disposition table](reproduce/docs_integration/README.md#document-disposition)
accounts for every incoming document. The
[theorem locator](reproduce/docs_integration/THEOREM_LOCATOR.md) maps the 80 IDs
to the pre-existing ledgers. Original documents are retained byte-for-byte;
old campaign status and old paths inside them remain historical.

**Evidence level for this pass:** imported mathematical and computational
claims retain their original scope and assurance. Copy hashes and collision
record accounting were checked during integration; the earlier cryptanalytic
experiments, solver decisions, and mathematical certificates were not rerun.
A recorded producer result, a separately implemented audit, and an independently
checked UNSAT proof are different evidence levels. The preservation manifest
makes no assertion that a historical script is currently runnable without
its other dependencies or original path configuration.

## 2. Current results take precedence over old progress reports

| Older source statement | Current interpretation |
|---|---|
| AA, AB, BA or BB `[1,2]` sites remain open | Historical intermediate snapshots. Global closure is recorded in `DIFF-PERM-003` in research 01. Do not resume those campaigns from the notebook's old commands. |
| `[2,1]` is pending or has missing refinements | Superseded. The current research 08 header records **all 255 positions / 8,355,840 configurations excluded, zero unresolved**. The completed records are in `reproduce/two_one_campaign_records/`. |
| Eight-round cumulative floors 12 unrestricted / 15 H159 | Older valid but weaker corollaries. Research 07 derives **16 unrestricted / 19 H159 / 21 H159 conditioned on A1=5**, using its stated established premises. Its selected family has a 22-call conditional floor. These are lower bounds, not attained minima. |
| Only three selected A1=5 differences have a second-round bound | Superseded by research 08's complete 21-family minimum-activity classification and `A1=5 ⇒ A2≥4`; research 07 composes it. |
| The selected `[5,1]` global solver job is unfinished | That particular old job need not have completed, but its desired exclusion now follows from the stronger all-family result. An unfinished historical job does not make the present mathematical question open. |
| Old first-Chi single-byte estimates or a 235-call unrestricted two-round witness are the frontier | Later ledgers contain stronger first-Chi estimates; the notebook itself improves that old witness to `[32,121]`, total 153. Witnesses are upper bounds on minima, not lower bounds. |
| No AVX2 implementation was included in an old scalar-only package | A historical packaging issue. The current project includes `krakken_multi.c`, with comparison results in research 08. |
| All useful structure disappears after round two | Not established. The records contain genuine local and one-round structures, restricted exclusions, statistical screens, and an exact nonlinear cyclic-schedule conjugacy that survives eight rounds. Their scopes must remain distinct. |

H159 means the exactly 159-byte padded first-block domain, with fixed padding
and zero initial capacity. Unrestricted permutation inputs, a uniform internal
Pressure input, later sponge blocks, and H159 are not interchangeable domains.
No imported activity figure is multiplied by the S-box differential exponent
to obtain a hash-security level.

## 3. A separate truncated-collision campaign

Source: [KRAKKEN_COLLISION_EXPERIMENT.md](reproduce/docs_integration/legacy/docs/KRAKKEN_COLLISION_EXPERIMENT.md).
This is additional evidence alongside the different collision experiments in
research 04 and research 08; it must not be counted as the same dataset.

Each trial fixes 151 message bytes from a seeded background and varies an
eight-byte little-endian counter, producing distinct H159 messages. The worker
compares a 24-bit digest prefix and stops at the first collision. The wrapper
uses 1–8 complete scalar rounds, byte 159 set to `0x86`, and zero capacity;
at eight rounds this is the actual hash mapping for these messages. Three
separately seeded campaigns together contain **1,000 completed trials per
round, 8,000 total, with no censored trial in their saved records**.

| Rounds | Mean hashes to first 24-bit collision | Ratio to ideal reference |
|---:|---:|---:|
| 1 | 5,287.765 | 1.0300 |
| 2 | 5,215.695 | 1.0160 |
| 3 | 5,128.773 | 0.9991 |
| 4 | 5,145.413 | 1.0023 |
| 5 | 5,042.970 | 0.9824 |
| 6 | 5,189.225 | 1.0108 |
| 7 | 5,137.894 | 1.0008 |
| 8 | 5,099.426 | 0.9933 |

The ideal first-collision approximation is `sqrt(pi/2) * 2^12 ≈ 5133.5747`.
The integration checker recomputes these means from all eight JSONL files,
checks distinct 159-byte messages, matching first three digest bytes, and
unequal complete digests. This is a **record check**, not a fresh C evaluation
of the stored hashes. The original document reports C replay and an additional
R8 public-interface check.

This adds evidence about one small projection and one message generator;
it does not establish 128-bit collision resistance. The source's censoring
rule is useful for future experiments: a mean computed only from successful
trials must not be compared uncritically with an unconditional ideal mean
when many trials hit a resource cap. Store the censored count explicitly.

## 4. Differential and linear screens: retain the positive findings too

Source: [KRAKKEN_TRUNCATED_DIFFERENTIAL.md](reproduce/docs_integration/legacy/docs/KRAKKEN_TRUNCATED_DIFFERENTIAL.md).
Four fixed input-difference cases were screened using 20,000 discovery bases
and 100,000 fresh validation bases at R1 and R2. Cases include a simple H159
byte difference, a four-cell H159 direction, an A1=5 witness's direction
**without conditioning on that rare activity event**, and an unrestricted
one-cell construction.

Useful recorded contrasts are:

| Fixed case / selected observable | R1 validation | R2 validation |
|---|---:|---:|
| H four-cell direction, byte 114 difference `0x70` | 700 / 100,000 | 381 / 100,000 |
| H five-cell direction, byte 7 difference `0x03` | 616 / 100,000 | 374 / 100,000 |
| Unrestricted one-cell direction, byte 252 difference zero | 100,000 / 100,000 | 394 / 100,000 |
| H four-cell selected bit, absolute difference correlation | 0.2728 | No significant surviving bit in the declared familywise screen |
| H five-cell selected bit, absolute difference correlation | 0.1330 | No significant surviving bit in the declared familywise screen |

A uniform byte-difference reference is `100000/256 = 390.625`. The largest
reported R2 byte count was 478; the cited adjusted p-value for its panel was
about 0.66. The largest R2 bit correlation was 0.01252. The coordinate-bit
validation family included four cases, two round counts, and 2,048 bits;
these are empirical screens, not all-mask or all-difference exclusions.
The unrestricted R1 zero projection has a separate exact interpretation in
`DIFF-TRUNC-001`; a frequency of 100% by itself would not prove it.

The notebook also retains controlled **Butterfly/XRBD-on versus off** results:

- For six specified 16-variable message cubes and ten selected output targets,
  exact restricted-input Walsh transforms found nonzero-mask R1 peaks up to
  **1** without Butterfly but at most **0.02051** with Butterfly. One off-mode
  state coordinate was perfectly linear on two selected `(72,73)` contexts.
  At R2–R3 the largest recorded peak across the tested tables was **0.02191**,
  below the chosen 0.02511 reference. These are exact finite truth-table
  measurements, not a bound over all 1,272 message variables.
- One- and two-byte differential bit/byte/adjacent-byte screens detected many
  R1 off-mode effects and no declared significant on-mode effects in those
  selected panels. A 24,576-test bit screen used a 0.00878 absolute-bias
  threshold; its R1 off-mode flagged counts were 1,116 and 1,606 for the two
  selected differences. At R2–R3 neither variant flagged a bit in that screen.
- The adversarial bytes-40/56 plane is an important counterweight to attributing
  every improvement to Butterfly: **Pressure raises all 256 tested plane
  cosets to maximal affine hull dimension 255 even with Butterfly omitted**.
  Butterfly preserves affine rank and changes support spread; it cannot
  itself increase that rank. The exact class is already `SUBSPACE-002`.

These controls explain what a layer contributes in a defined experiment.
They do not prove that omitting it is safe, or that every improvement is caused
by it. Full settings, seeds, checkpoints, and supporting file references are
preserved in [KRAKKEN_PROBE.md](reproduce/docs_integration/legacy/docs/KRAKKEN_PROBE.md).

## 5. Rotational screens add a different one-round warning

The perfect rotational-affine exclusion `ROT-001` and the exact one-round
Pressure reduction `ROT-002` are already in research 01. The notebook supplies
additional empirical detail: 100,000 seeded unrestricted bases for each of
seven byte-aligned rotations, with and without Butterfly.

| Lane rotation | R1 flagged coordinate correlations, each variant | R2 flags, each variant |
|---:|---:|---:|
| 8 | 1,376 | 0 |
| 16 | 736 | 0 |
| 24 | 544 | 0 |
| 32 | 448 | 0 |
| 40 | 544 | 0 |
| 48 | 736 | 0 |
| 56 | 1,376 | 0 |

The declared familywise threshold was 0.01670 over 28,672 tests per variant.
There were **5,760/14,336 R1 flags** and no R2 flag; maximum observed R2
absolute correlations were 0.01384 on and 0.01498 off. Under uniform
unrestricted input, the exact reduction explains why preceding invertible
Butterfly diffusion does not change the one-round rotational-residual
law. Sample-perfect R1 coordinates had rare counterexamples in direct
Pressure testing; they must not be promoted to identities.

This is useful attack-side information even though the tested R2 coordinate
biases were not significant. It is neither an H159 result nor a proof that
all two-round rotational distinguishers fail.

## 6. Useful exact reductions for future activity work

Sources: [effective-coordinate pilot](reproduce/docs_integration/legacy/docs/KRAKKEN_EFFECTIVE_CONE_PILOT.md),
[Pressure algebra pilot](reproduce/docs_integration/legacy/docs/KRAKKEN_PRESSURE_ALGEBRA_PILOT.md),
and the kernel/deduplication sections of the notebook. These results concern
**engineering an existing necessary-condition model**, not new activity
exclusions to add to the completed campaign totals.

### 6.1 Eliminate linear constraints, then preserve hidden nonzero constraints

The historical endpoint models already reduced the difference variables to
40 bits for AA and 32 for AB/BA, rather than modeling the entire permutation
as unrelated state bits. Solve the 32 exact Pressure bit-zero equations over
GF(2), write `x = N z` for a basis of their kernel, and reconstruct every
required nonzero endpoint byte. This substitution preserves the model exactly.
The recorded audit includes 40 small exhaustive kernel checks and 184
comparisons with the old solver. Forty-case samples measured original/kernel
seconds of 3.969/1.144 (AA), 3.621/1.111 (AB), 2.708/0.798 (BA), and
3.811/1.402 (same-cell). These are selected timings, not guaranteed speedups.

Project that kernel onto the low-bit difference profiles actually observed
by the Pressure constraints. Split visible profile directions from the hidden
fiber. Eliminate required nonzero-byte constraints on that fiber by exact
rank and inclusion–exclusion; **do not drop them**. For each chain, first-only
observations need `(a,c XOR h)`, second-only observations `(c,A)`, and joint
observations three base coordinates. For k observed bits, the top base bit
of each such coordinate cancels from its XOR derivative, reducing the base
enumeration to the low k−1 bits.

| Named pilot | Width | Visible / hidden difference dimensions | Old → effective base bits | Outcome |
|---|---:|---:|---:|---|
| AA position 0, site 847 | 3 | 18 / 8 | 144 → 68 | Relaxed SAT |
| Same site | 4 | 18 / 8 | 192 → 102 | UNSAT; 2^18 profiles, reported 2.8 s |
| AB position 7, site 6596 | 3 | 12 / 0 | 144 → 56 | Relaxed SAT |
| Same site | 4 | 12 / 0 | 192 → 84 | UNSAT; 2^12 profiles, reported 0.1 s |
| BA position 7, site 6596 | 3 | 5 / 8 | 144 → 56 | UNSAT |

At the AA four-bit site **one visible profile passed the carry tables but had
no hidden assignment satisfying all nonzero bytes**. This is a concrete reason
why projecting away hidden variables carelessly weakens the conclusion.
The independent pilot checked 48 carry tables, 224 hidden-fiber counts, and
seven Z3 comparisons. A targeted 50-AA/50-AB/same-sites-BA sample had median
visible ranks 16/15/12 and median effective base size 58 rather than 144 bits.
It was not a representative whole-campaign benchmark.

Exact site deduplication is another distinct optimization: the notebook
records status/count agreement for all 80 completed AA reports then available,
and an estimated 23.1% site-computation saving at position 063. Preserve worker
hashes and resumable-file formats; do not interchange workers in an unfinished
position merely because the mathematical relaxation is equivalent.

### 6.2 The low-three-bit algebra has a small, structured exception

`PRESS-DIFF-002` already proves the local classification. Its engineering
consequences deserve retention. Among 32,768 profiles `(da,dc,dh,dA,dC)`,
4,376 are feasible. The common-zero set of every vanishing polynomial up to
the indicated degree has this size:

| Maximum degree | Evaluation rank | Common zeros | False positives |
|---:|---:|---:|---:|
| 1 | 14 | 8,192 | 3,816 |
| 2 | 92 | 8,192 | 3,816 |
| 3 | 372 | 4,504 | 128 |
| 4 | 1,031 | 4,504 | 128 |
| 5 | 2,079 | 4,376 | 0 |

The 128 residual cubic false positives form one affine seven-flat. All cubic
consequences plus exclusion of this flat are exact; alternatively add the
saved 82-monomial quintic. The 82-term representation is not claimed minimal.
This gives a practical choice between table, polynomial, and affine-exception
encodings without changing the local feasible set.

Additional results in the pilot, beyond the local theorem statement:

- Two selected factored-cubic versus table benchmarks agree on all 20 and 30
  cases. Branching visits 20 versus 53,258 profiles and 39 versus 7,776;
  reported core times are 0.029/0.575 s and 0.033/0.105 s respectively.
  Shared basis/fiber code limits independence; selection and setup time limit
  performance generalization. Capped searches report `limit`, not UNSAT.
- Of 35 selected sites, 27 fit a 16-visible-bit cap and were fully enumerated,
  totaling 534,528 assignments. Cubic and exact three-bit counts agree for
  those 27; eight were skipped. Fifteen improve on the two-bit relaxation.
- At **AB position 007**, all 8,128 linear site spaces were classified:
  7,620 cannot meet the exceptional flat in any chain; 508 can potentially
  meet it (436 in one chain, 72 in two). A separate direct 40-equation
  elimination reproduces that classification. An intersection does not prove
  a feasible complete site. These are not additional global exclusions.

Full-word `PRESS-DIFF-003` supplies necessary cubic constraints, not a complete
carry model. `DIFF-SCREEN-001` explains a limitation of low-bit endpoint
projection: sparse endpoint spaces can already surject onto the observed
profiles. Adding more low-bit searches without retaining lost information
need not improve the desired activity bound.

## 7. Proof techniques and failed shortcuts worth carrying forward

The corresponding named theorems are already in research 01; the documents
make their reusable proof mechanisms and limitations easier to recover.

**Keep signed hull cancellation.** A four-bit coupled-Pressure example has
actual correlation zero while the sum of absolute path contributions is 7/8.
This blocks a proposed absolute-sum proof of a uniform 1/2 bound; it is not
itself a strong full-width attack. Similarly, multiplying the two additions'
marginal differential probabilities is invalid: the notebook records exact
joint counts exceeding the product, including a factor-eight example.
Use a joint carry-state counter or a justified distribution bound.

**Low-bit Walsh transfer proof.** The low-17 joint-output class admits a
four-state carry automaton. The highest selected output bit fixes the initial
support; 96 two-bit cases bound every normalized carry-vector component by
1/2. Subsequent transitions have absolute row sum at most one. Quadratic
carry characters of rank two explain the base case. This proves the existing
sharp component bound for its specified mask class without enumerating all
64-bit masks. The low-six-bit exhaustive spectra remain validation, not a
second independent security claim.

**Condition on a small observation, not a huge entire state.**
[Conditioned Pressure analysis](reproduce/docs_integration/legacy/docs/KRAKKEN_CONDITIONED_PRESSURE_DIFFERENTIAL.md)
uses a weighted Fourier bound for the selected event indicator. Affine
conditioning on the A1=5 event incurs its codimension-35 cost explicitly;
whole-slice bounds can be vacuous. Its three selected conditional full-round
target bounds are `1/4+2^-204`, `1/8+2^-197`, and `1/16+2^-182`, already
`DIFF-RATE-007`. They are not eight-round or digest-specific bounds.

[Unconditional analysis](reproduce/docs_integration/legacy/docs/KRAKKEN_UNCONDITIONAL_ROUND1_DIFFERENTIAL.md)
partitions on the five affected cells, controls all 4,095 nonzero characters
of a 12-bit base observation, and propagates an **exact nonuniform** idealized
law Q. It establishes the existing ten-bit projection TV error `<2^-145`
and prescribed complete-round target bound `<507/512000` for three fixed
H159 differences (`DIFF-RATE-008`). The projection is outside the digest.
Its nonuniform Q is informative structure, not evidence to erase because a
randomness narrative would be simpler. The later bounds in research 02/03/08
must be consulted before calling these older numbers the frontier.

**Separate existential witnesses from universal negatives.** Finite C outputs
of full affine rank can exclude a universal affine relation over the whole
domain: any universal relation must hold on those witnesses. A finite list
of roughly balanced samples cannot similarly prove a small global bias.
This distinction underlies the rank-based integral, dependency, label, and
algebraic certificates already in the ledgers.

**Keep model controls and invalid prototypes visible.** The notebook records
an initial unified two-call checker with a wrong branch pairing; its prototype
results are invalid, and corrected cache filenames have the `v2` marker.
The independent BB and spatial-pair models were unaffected. A division-property
kit's `UNSOUND` validation message arose from empty input-cube cases in the
small checked widths; no nonempty counterexample was found there, which is
not a full-width soundness proof. Conversely a division trail can exist when
the actual output sum is zero. “No balance certified” is not “no integral
exists.” A known positive one-round control also timed out in a large model;
that timeout measures the solver, not Krakken's security.

## 8. Attack-side constructions and reachability agenda

Sources: [multi-cell boomerangs](reproduce/docs_integration/legacy/docs/KRAKKEN_MULTICELL_BOOMERANG.md),
[ASTRA.md](reproduce/docs_integration/legacy/docs/ASTRA.md),
[Pressure translation windows](reproduce/docs_integration/legacy/docs/KRAKKEN_PRESSURE_TRANSLATION_WINDOWS.md),
and the [attack coverage program](reproduce/docs_integration/legacy/docs/KRAKKEN_ATTACK_COVERAGE_PROGRAM.md).

`BOOM-MULTI-001` is a genuine positive construction: complementary post-Chi
direction spaces can be routed to disjoint Pressure-chain units, preserving
four-state full-state zero XOR through R1 for arbitrary common backgrounds.
The 56 ordered distinct unit choices were sampled 24 times each. All 1,344
saved patterns fail at Chi2; their minimum sampled Chi2/full-R2 defects are
903/950 bits, **not** class-wide lower bounds. The saved-pattern local
obstructions cover those patterns, not every direction/background choice.
The H159 linear necessary gate excludes 896 and leaves 448 unresolved
**by that gate**. Passing it does not produce four compatible messages.

For a selected candidate with post-Chi vertices
`Q = (B, B XOR V, B XOR U, B XOR U XOR V)`, impose all four actual-message
constraints `L^-1 Chi^-1(Q_i) = J m_i XOR c`, using the source's affine-prefix
convention. A difference-only rate constraint loses common-base compatibility.
The historical candidate 1211 pilot satisfied 99 of 112 active-cell constraints
before its full attempt timed out; this is not a witness, not an exclusion,
and not a reason to repeat a long solve without a better reduction.

`PRESS-TRANS-001` classifies the internal deterministic translation space U;
`DIFF-WINDOW-001` proves nonzero U directions cannot occur at consecutive
Pressure inputs, for every base. The proof uses full-rank inactive-cell
constraints for all 65,535 directions, rather than independent probabilities.
The conditional adjacent activity cost is at least 135. Historical eight-round
conditional corollaries include 143 unrestricted / 144 H159 when U occurs
before the final round. These are **conditional bounds for this special
internal class**, not replacements for the current unconditional bounds.
The source's attaining unrestricted pair is not a padded-message witness.

The old review's other productive directions remain methodological options:
nonperfect differential-linear measurements selected before fresh validation;
backward/shared-base reachability; and later-block constraints with correlated
capacity. Exactly 160-byte messages entail the hash's extra padding block;
the 160-byte first absorb is not a complete exactly-160-byte hash. For an
attack claim, count rejected candidates, construction work, and queries, and
specify whether the attacker observes the digest or hidden internal state.

These suggestions are retained as research leads, not freshly launched
campaigns. The latest conditional composition gates in research 07 are the
starting point for further activity work; old suggestions to close already
completed `[1,2]`, `[2,1]`, or minimum-A1 cases are obsolete.

## 9. Additional notebook observations retained for future use

These details are useful to keep discoverable even where a later theorem
supersedes their original motivation. They are historical results with their
original evidence level; the complete source notebook and linked reports
remain the primary account.

- **Sparse searches can miss attainable activity values.** The alignment
  heuristic missed A1=11–23. All 2,544 one-sided single-bit mutations of its
  A1=5 seed jumped to A1=62–113, while common-base moves preserved the
  five-cell difference geometry. Constructed C-replayed pairs attain every
  A1=5–26. Failure to reach intermediate bins was a search-basin artifact.
- **Butterfly can compress specially structured support.** The notebook
  exhausts single-byte propagation and 15,552 equal-bit affine-face cases;
  the minimum input-plus-output support in the latter class is 12, not a
  global branch-number theorem. The `[32,121]` two-round witness has total
  153 on unrestricted inputs. Its hash reachability is not established.
  Under the specified single-byte Butterfly-output restriction, the historical
  H159 gate excludes the smaller A1 cases and gives a conditional floor 80;
  this is not a general first-round floor.
- **First-Chi exact-point versus activity events differ.** Historical selected
  pairs have exact prescribed post-Chi probabilities `2^-147` and `2^-363`,
  with conditional probabilities `2^-98` and `2^-293` after conditioning on
  their minimum activity events. These do not bound every endpoint target or
  compose automatically. Stronger later first-Chi class bounds take precedence.
- **Cube sample size limits affine hull rank.** A set of 256 outputs has affine
  dimension at most 255 even in a 2,048-bit state. Achieving 255 rules out a
  smaller containing affine space for that set; it does not prove full-state
  randomness. The maximal-rank byte-plane results and special Theta-cancelling
  plane results should therefore be reported with the plane size and quantifier.
- **Local S-box quality does not describe the serial pair completely.** The
  supplied `THEOREM.md` gives the complete local boomerang classification and
  proof reduction, already `BOOM-LOCAL-002`. Keep that full proof, not just the
  byte S-box's BCT maximum: the serial Chi has a perfect local family. A
  local perfect structure and an H159 reachability obstruction can both be true.

## 10. Review and implementation provenance

[The September review follow-up](reproduce/docs_integration/legacy/docs/KRAKKEN_REVIEW_FOLLOWUP_20260930.md)
corrects an important notebook assertion: the cited `[1,1]` audit JSON has
`replayed_scip_jobs: {}`. Original 512-job producer evidence and model/C checks
must not be described as newly rerun SCIP jobs. The corrected ledger entry
already distinguishes these; this integration follows the correction.
This concerns `[1,1]` audit wording, not the completion of the separate `[2,1]`
campaign.

The source review also records API and portability considerations: the raw
round-constant accessor needs initialization and a valid index; reduced-round
research interfaces have edge-count behavior requiring caller validation;
native byte views need an explicit little-endian specification. These are
historical source-review findings retained for deliberate implementation work,
not newly fixed defects or a reason to change the pinned implementation during
a document merge. The separate AVX2 translation unit is present now.

The integration leaves the original C/H/AVX2 files and research 01–07
unchanged. Research 08 receives an append-only integration entry. Checksums of
the pre-integration eight ledgers, every preserved file, and the current sources
are available in the reproduction bundle. Earlier review, proof, and empirical
claims remain attributable to their original records rather than to a new
external peer review or a new solver campaign.

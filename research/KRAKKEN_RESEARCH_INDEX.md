# Krakken research index

This is the entry point for continuing the cryptanalysis. The working
documents stay separate because they answer different questions:

AA campaign workflow (user preference): when the user posts a completed
position/batch, check the saved reports, refine any pending relaxed SAT
cases from that batch and earlier completed batches, then report the actual
remaining cases and give the next eight-position scan command. A completed
three-bit scan is not a closed position while relaxed survivors remain.
Do not treat a pasted batch-end position as evidence that intermediate
positions had no survivors. Preserve the pinned scan/refinement scripts and
existing results; refinements save to separate per-position files.

| Document | Purpose | When to update it |
|---|---|---|
| [Research notebook](KRAKKEN_PROBE.md) | Experiments, witnesses, negative searches, and detailed observations | As new work is done; label exact results and empirical screens distinctly |
| [Theorem program](KRAKKEN_SECURITY_THEOREMS.md) | Formal statements, proofs, proof obligations, and precise obstacles | When a mathematical claim is proved, strengthened, disproved, or a proof route fails |
| [Permanent theorem inventory](KRAKKEN_THEOREM_INVENTORY.md) | ID-keyed scopes, proof classifications, and implementation-audit coverage | Append new IDs; never reuse or renumber existing IDs |
| [Theorem artifact manifest](KRAKKEN_THEOREM_ARTIFACTS.md) | Scripts and certificates cited by each theorem ID | When working theorem references change; does not rebuild the frozen bundle |
| [Claims for review](KRAKKEN_CLAIMS_FOR_REVIEW.md) | Short, source-pinned statements suitable for independent cryptanalytic review | Only when a defined theorem class is closed and its certificates are ready |
| [Truncated collision experiment](KRAKKEN_COLLISION_EXPERIMENT.md) | Reproducible reduced-round birthday screens and saved collision pairs | Empirical observations only; keep separate from theorem claims |
| [Truncated differential screen](KRAKKEN_TRUNCATED_DIFFERENTIAL.md) | Fixed-difference one-byte and single-bit output projections through two rounds | Empirical observations only; follow up on any surviving bias |
| [Attack-versus-round map](KRAKKEN_ATTACK_ROUND_MAP.md) | Strongest demonstrated structures, construction costs, exact boundaries, and open continuations across attack families | Update when a structure reaches a new complete-round or hash-reachable checkpoint |
| [Effective-coordinate two-round pilot](KRAKKEN_EFFECTIVE_CONE_PILOT.md) | Measured AA/AB/BA low-bit quotient and exact carry-table enumeration, with explicit relaxed-model boundary | Solver-engineering follow-up; no theorem promotion from runtime reduction alone |
| [NEW.md review triage](KRAKKEN_NEW_REVIEW_TRIAGE.md) | Which fresh reviewer candidates closed, duplicate a prior theorem, or remain research targets | Update as those candidate scopes change |

The [review bundle](../krakken_review_bundle/README.md) and
[ZIP archive](../results/krakken_review_bundle.zip) are **frozen snapshots** of the
claims and source at the time they were packaged. They are not live
copies of the working documents. **Rebuild a bundle only when the user
explicitly asks for a new one.** Editing any working document does not
trigger packaging.

## Current theorem status

[RESULTS4.md](../RESULTS4.md) adds two bounded local/first-round
results. [PRESS-DIFF-001](KRAKKEN_SECURITY_THEOREMS.md#press-diff-001)
replaces the exact two-bit Pressure difference table by two LSB
equations and three factored cubic equations; it also proves that
all standalone quadratic consequences together prune no more than
the LSB equations. [ALG-DEG-002](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-002)
gives exact local degrees for the low six bits of both Pressure
outputs and upper bounds for 192 specified complete-round-one state
bits. Neither result raises an eight-round activity floor. The
report's abstract calculation shows that closing unrestricted
`[1,2]` alone would raise the **presently derivable** eight-round
valid-159-byte activity floor only from 15 to 18; this is a
hypothetical implication, not a newly proved Krakken floor. Its
bounded next test is factored-affine branching against the existing
effective-coordinate enumerator on selected cases, before any
campaign-scale run.

The follow-up [Pressure algebra pilot](KRAKKEN_PRESSURE_ALGEBRA_PILOT.md)
completed that bounded two-bit comparison and established
[PRESS-DIFF-002](KRAKKEN_SECURITY_THEOREMS.md#press-diff-002): the
complete local low-three-bit relation has exactly 4,376 profiles;
all cubic consequences leave 128 false profiles forming one affine
seven-dimensional flat, while one explicit degree-five equation makes
the cubic closure exact. The
selected 50-site factored-branch benchmark agreed with the existing
carry-table enumerator and reduced candidate-profile work on its
tested cases, but yielded **no new global `[1,2]` exclusion**.

The [DIFF-RATE-006 first-round differential corollary](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-006)
uses the all-message-mask certificate of `LIN-RATE-004` and the exact
Fourier autocorrelation identity. For any fixed pad/capacity offset,
all but fewer than `2^1039` of the `2^1272` valid-message differences
have an eight-bit **nondigest** round-one output-difference
distribution within `2^-125` total variation of uniform; every
projected value has probability at most `2^-8+255·2^-136`. This is a
complete-round **almost-all-differences** theorem, not a guarantee
for a selected input difference, the hash digest, or later rounds.

The [LIN-THETA-001 fixed-space theorem](KRAKKEN_SECURITY_THEOREMS.md#lin-theta-001)
closes Candidate 4 of `NEW.md`: the current scalar Theta layer is an
involution with `rank(Theta−I)=504` and a 1544-dimensional fixed
space; every non-fixed state is in a 2-cycle. The exact 2048-column
original-C matrix, all 1544 explicit fixed-basis vectors, 16
non-fixed original-C cycles, and a separate Python reconstruction
are saved. This is a **Theta-only structural result**, not an
invariant or distinguisher for a complete Krakken round.

The [NEW.md triage](KRAKKEN_NEW_REVIEW_TRIAGE.md) closed two new
**local, unrestricted-Chi** classes. [DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002)
classifies the exact maximum probability for every nonzero 16-bit
serial-Chi input difference into `2^-6`, `2^-7`, or `2^-12`, with
counts 510/32,130/32,895 and a unique maximizing output each.
[DL-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-local-001) proves that
the only nontrivial perfect local differential-linear pairs are the
65,025 diagonal-input/first-output-mask pairs; all other pairs have
absolute correlation at most `71/512` (a conservative, nonsharp
bound). These statements are **not** hash-interface or complete-round
security estimates.

The new [CHI-RATE-001 conditional-branch theorem](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001)
proves that all 128 first-call Chi bytes plus **any five** second-call
Chi bytes are jointly uniform for uniform 159-byte messages (and for
the full 160-byte rate), under any fixed affine state offset. Every
133-byte value has exactly `2^208` preimages in the 159-byte domain.
This yields an exact truncated-differential product and strengthens the
universal prescribed Chi1/XRBD1 difference bound to `2^-30`. It also
gives a sharp `2^-384` maximum for masks on all 128 first-output
bytes, over every message mask. Two source-pinned complete five-subset
rank scans and separate audits support the finite obligation. These
are **first-Chi checkpoints**; neither Pressure nor round two is
covered. The earlier `DIFF-RATE-005` `2^-24` theorem remains valid but
is numerically superseded in the same 159-byte checkpoint domain.

The [LIN-RATE-004 nonlinear-Pressure bridge](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004)
now gives a **one-complete-round** quantitative linear theorem beyond
the carry-free Pressure identities. For a specified eight-bit state
projection outside the digest, all 255 nonzero output masks have
absolute correlation at most `2^-246` against **every** valid
159-byte message mask, even after an arbitrary fixed state offset.
Any 128 independent affine message constraints leave that projection
within `2^-115` of uniform. The proof retains the complete exact
low-four-bit Pressure spectrum and the actual message-image ranks;
it does not infer uniform Pressure inputs. The result does not cover
all output masks, the digest projection, or later rounds.

[DIFF-ACT-001](KRAKKEN_SECURITY_THEOREMS.md#diff-act-001) now gives the
exact first-Chi activity distribution and the full affine set of
minimum-activity bases for **every fixed state difference** on a
uniform 159-/160-byte rate plane, including fixed capacity differences.
Its exact activity-conditioning Fourier norm combines with
LIN-RATE-004: after any nonempty `A1<=5` event, the specified
eight-bit **base-state, nondigest** projection after one complete
round has correlation at most `2^-211` against every message mask
and TV `<2^-208` from uniform. This does not bound the difference
of the two round outputs or any digest projection.

The [LIN-CHI-002 four-cell projection theorem](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-002)
certifies rank 64 for **all 10,668,000** selections of four serial-Chi
inputs from the valid 159-byte first-block message space. It extends
the exact sparse-mask Chi1 maximum to `2^-12` for every message mask
and every output mask on exactly four cells. Combined with the known
minimum four-cell support and exact local Chi DDT, this gives the
[DIFF-RATE-005 global first-Chi concentration theorem](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-005):
for every nonzero fixed valid-message difference, every prescribed
full-state post-Chi1 (or post-XRBD1) difference has probability at most
`2^-24` under a uniform message base. `CHI-RATE-001` strengthens this
to `2^-30` in the same domain. It is a **checkpoint** bound;
Pressure and additional rounds remain open. The
[DIFF-CHI-001 affine-fiber theorem](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-001) gives
an exact rank count for prescribed first-Chi transitions whose active
cells all have an active first S-box call. The next round-bound step is
to count Pressure output transitions **conditioned on those actual
message-base fibers** and sum over all Chi1 differences reaching a
target. The checkpoint `2^-30` bound cannot be multiplied by a
uniform-Pressure component bound or repeated across rounds.

The [DIFF-RATE-004 full-block theorem](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004)
extends the exact five-call first-Chi minimum to the **first unpadded
160-byte absorb call**. The full rate adds two exceptional four-cell
supports to the six in the 159-byte domain, but all eight require at
least six calls by exact local DDT counts. A valid 160-byte message
pair attains five calls, with original-C hash replay. The same `A≥5`
floor holds at a later differing full block after an identical prefix;
the ensuing padding call and differing earlier blocks are outside
this theorem. The [attack-versus-round map](KRAKKEN_ATTACK_ROUND_MAP.md)
now presents the strongest proved and observed reach of each studied
family without converting them into an eight-round security margin.

The new [BOOM-LOCAL-002 complete-class theorem](KRAKKEN_SECURITY_THEOREMS.md#boom-local-002)
closes the local serial-Chi boomerang spectrum's perfect-pair question:
the 65,025 known diagonal/first-output pairs are the only nontrivial
perfect ones. Every other local pair succeeds with probability at most
`3/128` under a uniform unrestricted cell base, and the bound is sharp.
For unrestricted Chi, each cell outside the perfect class contributes
one such factor. This supplies a local classification for future searches;
hash-interface and complete-round boomerang probabilities remain open.

New attack-side construction:
[BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001) proves that
coordinated multi-cell quartets can preserve a full-state four-state zero
sum through **one complete unrestricted round**, for arbitrary common
backgrounds within the stated direction spaces. The
[continuation report](KRAKKEN_MULTICELL_BOOMERANG.md) found no Chi2 or
complete-round-two survivor in 1,344 sampled cases; a general two-round
exclusion and valid-message reachability remain open.

The [finite reached-pattern classification](../results/krakken_multicell_20260930/README.md)
subsequently certified a zero-count Chi2 cell in every one of those 1,344
patterns, with exact counts for all reached cells and original-C replay.
No pattern has positive local counts everywhere. This applies to the saved
patterns at any Chi2 base; it does not exhaust earlier backgrounds or the
coordinated construction's direction spaces.

A [first-block rate-gate classification](../results/krakken_multicell_20261002/README.md)
also excludes **896** of the same 1,344 saved direction pairs from valid
159-byte first-block embedding at *every* common background. The other
448 remain unresolved at the hash interface; passing the linear gate is
not a construction of valid messages.
The [targeted nonlinear edge model](../results/krakken_multicell_20261002/README.md#targeted-nonlinear-edge-test-on-the-448-linear-gate-survivors)
has begun on one of those 448 directions. Partial-cell witnesses are
audited, while the complete edge and four-message embedding remain open.

Review follow-up: [2026-09-30 triage](KRAKKEN_REVIEW_FOLLOWUP_20260930.md).
The new [DIFF-TRUNC-001 theorem](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001)
classifies guaranteed zero-output-bit projections for all 128 unrestricted
diagonal one-cell Chi1 sites through one complete round. One site has 15
guaranteed zero-difference bytes, including byte 252 from the empirical
truncated-differential screen. This is attack-side one-round structure;
the first-block hash interface excludes that one-cell starting difference,
and no two-round zero-byte guarantee is claimed.
The [DIFF-RATE-001 common-prefix corollary](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001)
also carries the `A≥5` Chi-entry floor to a later **final partial-block**
permutation call after any number of identical complete message blocks.
It does not cover differing prefixes or a differing full 160-byte block.
The inherited [multi-round activity corollary](KRAKKEN_SECURITY_THEOREMS.md#diff-multi-001)
gives eight-round total floors of 12 unrestricted, 15 for the precise
159-byte first-block domain, and 17 for three selected differences under
`A1=5`. These are conservative activity floors, not probability or security-bit
bounds. Its parent `[1,1]` audit records no independent solver reruns; the
working ledger now makes that evidence limit explicit.

The review document states several closed linear theorem classes, one
closed algebraic-degree class, one local boomerang family, two
defined differential exclusions, one exact six-difference
first-Chi probability class, a rotational-symmetry exclusion,
two differential-linear classes, two defined zero-sum classes, a
complete one-byte integral class, one all-output-mask byte-cube
family, two complete defined subspace classes, and a full first-order
dependency class, plus two defined rebound component/rate-gate
claims:

1. No perfect affine message-to-state relation for any complete round
   count 1–8 on the valid 159-byte first-block input domain.
2. The exact maximum correlation `2^(-3t)` for every first-Chi output
   mask active on exactly `t=1,2,3` serial-Chi components, over all
   valid-message masks.
3. Exact counters and a sharp nonperfect maximum `1/2` for two
   complete Pressure-chain mask families under a uniform unrestricted
   input: mask on input `a` confined to its LSB, or a second-output
   mask confined to its LSB. Exact-zero mask families provide further
   hull pruning. Both exact affine LSB relations can canonicalize any
   chain coefficient to one with those two LSB mask bits cleared.
4. An exact four-state joint-carry counter **and a sharp nonperfect
   maximum `1/2`** for every uniform-input Pressure-chain coefficient
   with both output masks confined to low `k≤17` bits. This includes
   coupled two-addition masks. A 96-case two-bit base lemma and a
   row-norm induction prove the bound for all 17 widths; an earlier
   billion-mask certificate independently validates the first six.
   Input masks on irrelevant bits give exact zeros.
5. A **complete one-round hash-message** correlation upper bound:
   every 1272-bit message mask has absolute correlation at most
   `2^-174` with each of 16 specified two-bit state masks after
   one full round. This uses actual padding, rate restriction, XRBD,
   Chi, Pressure, constants, and shuffle. It is the first numerical
   bound here that crosses a complete round at the valid-message
   interface; its output-mask class is precisely defined.
6. A **five-dimensional one-round output-mask subspace** generated by
   five of those exact-affine two-bit masks. All 31 nonzero masks in
   this subspace have complete valid-message correlation at most
   `2^-162` against every 1272-bit message mask. The verifier checks
   every nonzero subspace mask with the rate-aware affine-image bound;
   the [updated certificate](../results/hash_round1_AC_coordinate_subspaces_128_validated_v3.json)
   independently checks all 31 ranks. Under codimension-`d` affine
   message conditioning, its five-bit output projection remains
   within `2^(d-160)` of uniform after one round; under any 128
   independent linear message constraints this is `2^-32`.
7. A **six-dimensional one-round output-mask subspace** generated by
   six exact-affine two-bit masks. Every one of its 63 nonzero masks
   has complete valid-message correlation at most `2^-76` against
   every 1272-bit message mask. Its six output parities are within
   total variation `2^-74` of uniform after one round. The theorem
   also holds conditionally on **any** affine message subspace of
   codimension `d`, with output variation below `2^(d-74)`; fixing
   any 64 independent message parities gives below `2^-10`. It covers
   this complete defined projection, not the full state. Its
   [source-pinned certificate](../results/hash_round1_AC_coordinate_subspaces_76_validated_v2.json)
   includes independent rank and C replay checks.
8. A **valid-message algebraic-degree map** for all complete round
   counts 1–8. Of the 2048 first-round state bits, 32 shuffled
   Pressure-output LSBs have exact degree 13 and the other 2016 have
   degree at least 20. Every state bit after rounds 2–8 has degree
   at least 20. The first-32-byte projection has vectorial degree at
   least 24 after every round, including the actual eight-round
   digest. The [degree audit](../results/degree_multiround_claims_audit.json)
   and [theorem section](KRAKKEN_SECURITY_THEOREMS.md) identify the
   witnesses and the four-bit digest subset of the low-degree class.
9. The effective **16-bit serial-Chi component** has maximal
   nontrivial boomerang uniformity `65,536`: every one of 65,025
   specified input/output difference pairs is a perfect local
   boomerang. A fresh current-C derivation is in the
   [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md). In a complete
   **four complete 65,536-base continuations** at one fixed site and
   background, **4,784** quartets reach Chi2 as rectangles and
   **none** satisfy its output condition. The
   [combined certificate](../results/krakken_boomerang_four_class_verified.json)
   links the original-C enumerations and independent audits. A stronger
   [local obstruction certificate](../results/krakken_boomerang_chi2_obstruction.json)
   and [suite extension](../results/krakken_boomerang_cell_suite_obstruction.json)
   show that **each** Pressure survivor has a Chi2 cell with zero
   rectangle solutions for *any* local base at its fixed input
   differences. Other embeddings remain open.
10. An independently audited **two-round differential exclusion**:
    no unrestricted nonzero trail has active-call vector `[1,1]`.
    Thus every nonzero two-round trail has at least three active byte
    S-box calls **in total**. The [complete SCIP log](../krakken/prove_11_full.log)
    covers all 512 start-position/Chi2-branch cases, and the
    [source-pinned audit](../results/krakken_11_audit_validated.json) checks log
    coverage and model soundness against C; its saved report records **no
    independent SCIP solver reruns**. A cheap exact
    Pressure-LSB sieve independently excludes 18,349 of 65,536
    one-active endpoint cases; it does not settle `[1,2]`.
11. A fast complete-class **partial `[1,2]` exclusion**: among
    2,080,768 start-location/two-second-branch-Chi2-cell site cases,
    exact Pressure LSB identities exclude **1,034,445** for every
    start-byte value and base. The [rank certificate](../results/krakken_pressure_lsb_endpoint_rank.json)
    enumerates the entire stated subclass. The full `[1,2]` question
    remains open, and [Astra's optimized oracle](../scripts/oracle_optimized.py)
    incorporates these LSB identities in its master model.
    A new exact joint-two-bit Pressure screen completely accounts for
    the **8,128** endpoint site pairs at Chi1 post-byte position 0:
    3,872 excluded by LSB, **2,351 additionally excluded by carries**,
    1,139 low-two-bit survivors, and 766 deliberately capped kernels.
    The [producer](../results/krakken_12_joint2_start0.json) and
    [independent original-C audit](../results/krakken_12_joint2_start0_audit.json)
    agree. The 6,223 excluded pairs are a proved fixed-start subclass.
    The [all-position campaign](../results/krakken_12_joint2_all_positions/summary_k18.json)
    has now finished all 256 locations: **1,034,445** LSB exclusions,
    **593,659** additional joint-two-bit exclusions, **298,360**
    low-two-bit survivors, and **154,304** kernel-capped cases, across
    all 2,080,768 endpoint site cases. The
    [independent original-C audit](../results/krakken_12_joint2_all_positions/audit_summary_k18.json)
    has now recounted **every** case using opposite-pivot GF(2)
    elimination and C-derived layer maps. All 256 per-position
    producer/audit counts, current source pins, and aggregate totals
    match. Therefore **1,628,104** named site cases are proved
    impossible, leaving **452,664** unresolved by this screen;
    survivors are not trails. The theorem and reviewer ledger now
    contain the exact claim. A [three-bit selected-site Z3 gate](../scripts/krakken_12_jointk_selected_z3.py)
    has provisionally excluded all 1,905, 1,896, and 1,886
    two-bit-unresolved cases at positions 0, 1, and 2 respectively, with
    [position-0](../results/krakken_12_joint3_selected_pos000.json) and
    [position-1](../results/krakken_12_joint3_selected_pos001.json) and
    [position-2](../results/krakken_12_joint3_selected_pos002.json) per-case
    outputs. The [resumable all-position driver](../scripts/krakken_12_joint3_all_positions.py)
    completed all 256 positions. Its [summary](../results/krakken_12_joint3_all_positions_summary.json)
    records 451,718 further UNSAT cases and 946 relaxed survivors.
    The [refinement](../scripts/krakken_12_refine_sat.py) excludes all 946 at four
    or five bits, and an [independent original-C audit](../scripts/krakken_12_refine_sat_audit.py)
    reproduces those 946 results. Together with the audited two-bit
    screen, this closes the entire 2,080,768-site distinct-second-branch
    (`BB`) class. The 451,718 three-bit UNSAT records have not had a
    second full independent recount; the [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md)
    records that verification boundary.
    The remaining Chi2 shapes now have a [source-derived LSB
    prefilter](../scripts/krakken_12_missing_shapes_lsb.py) for distinct-cell
    `AA/AB/BA` and both calls in one cell. Its small
    [pilot](../results/krakken_12_missing_shapes_lsb_pilot.json) and
    [full 128-site same-cell start-0 slice](../results/krakken_12_same_cell_lsb_start0.json)
    identify cheap exclusions without launching a competing long
    campaign. A [unified two-call checker](../scripts/krakken_12_union2_z3.py)
    now covers all four branch arrangements in one symbolic job per
    start position, with exact low-bit Pressure and no solver timeout.
    Its [probe note](KRAKKEN_PROBE.md) records the correct byte-pair
    indexing and pilot results. These are research screens, not theorem
    claims; the separate BB three-bit relaxed SAT cases were all
    eliminated at four or five bits, while other two-call shapes remain
    open. A [split-site worker](../scripts/krakken_12_remaining_split.py) now
    handles `AA`, `AB`, `BA`, and same-spatial-pair cases one site at a
    time, with a rank prefilter and resumable per-position reports.
    Its [pilot](KRAKKEN_PROBE.md) is substantially faster than the
    all-shape union. The complete 256-position `same` scan and
    [24-case refinement](../results/krakken_12_same_refinement.json) now exclude
    all 32,768 same-spatial-pair sites. A subsequent
    [distinct-AA closure](KRAKKEN_SECURITY_THEOREMS.md#diff-12-006)
    excludes all 2,080,768 AA sites, with the saved-result coverage
    audit and no second full solver recount. The distinct mixed AB
    scan is ongoing; distinct mixed BA remains open.
    Separately, an [exact one-byte XRBD/Pressure-chain
    certificate](../results/krakken_xrbd_onebyte_pressure_chains.json) establishes
    that `A1=1` at the unrestricted permutation level forces all 32
    XRBD output lanes and all 16 Pressure chains active, for every
    one-byte position/value difference. This is a cross-layer
    activity floor, not an eight-round security-bit estimate.
12. **Exact rotation-with-XOR-offset symmetries are absent** for every
    nonzero uniform lane rotation and every round count 1–8, both
    with and without round constants. All 1,008 cases have C-derived
    counterexamples in the [rotational certificate](../results/krakken_rotational_affine_audit.json).
    For byte-aligned rotations, an [exact one-round decomposition](../results/krakken_rotational_decomposition_validated.json)
    identifies Pressure as the source of all uniform-state one-round
    rotational bit biases. Statistical related-input correlations
    after two rounds are a separate question.
13. A **complete one-round differential-linear mask classification**
    for 128 unrestricted serial-Chi diagonal input-difference sites
    and all 255 nonzero byte differences. Within Pressure's specified
    32-dimensional affine-output mask space, the perfect derivative
    subspace has exact dimension 26–29 by site. For 125 sites a
    single output bit suffices. The [certificate](../results/krakken_differential_linear_validated.json)
    gives every site rank. These `A1=1` differences are excluded by
    the first-block rate-only hash interface.
14. A **two-round perfect differential-linear exclusion over every
    output mask** for the 128 fixed `delta=1` input differences from
    item 13. Their two-round derivative sets have full affine span
    2048; the [certificate](../results/krakken_differential_linear_fullstate_rank_all128.json)
    and [independent replay](../results/krakken_differential_linear_fullstate_audit_validated.json)
    verify all 128 cases using 262,464 C input pairs. Nonperfect
    correlations and other input differences remain open.
15. A **four-state zero-sum class** across Chi/XRBD and complete
    rounds. One exact serial-Chi input/output square produces a
    full-state zero sum at the post-Chi and post-XRBD checkpoints and
    32 guaranteed balanced output coordinates after one complete
    round. At all 128 Chi byte cells, finite C witnesses exclude
    every universally balanced coordinate bit after round two; the
    [all-cell certificate](../results/krakken_zero_sum_allcells_validated.json)
    needs at most 18 backgrounds per cell. At one representative
    cell, 2052 four-state round-two sums have full linear rank 2048,
    excluding **every** nonzero universal output-mask balance in
    that fixed-square family. The [rank certificate](../results/krakken_zero_sum_square_validated.json)
    and [independent C replay](../results/krakken_zero_sum_square_audit_validated.json)
    give the complete defined-class claim. Four exact valid-message
    byte cubes were also checked separately; none was a full-state
    zero sum after either complete round.
16. A **hash-reachable 14-cube zero-sum theorem**. Every affine cube
    of at least 14 independent valid-message directions has a
    full-state zero sum after Chi1 and XRBD1; 32 specified coordinates
    remain balanced after one complete round. For the fixed cube
    varying message bits `0..13`, those are **exactly** the universal
    one-round balanced coordinates, while **none** are universally
    balanced after two complete rounds. Eleven explicit base cubes
    certify the exclusions. The [report](../results/krakken_hash_zero_sum_14cube_validated.json)
    and [independent original-C replay](../results/krakken_hash_zero_sum_14cube_audit_validated.json)
    cover all 180,224 enumerated valid-message vertices. This does
    not classify other two-round cubes or non-coordinate output masks.
    The internal full-state threshold is **sharp**: an explicit valid
    [13-cube witness](../results/krakken_hash_chi_cube_threshold_validated.json)
    has nonzero post-Chi and post-XRBD sums, with an
    [independent original-C audit](../results/krakken_hash_chi_cube_threshold_audit_validated.json).
17. A **complete valid-message one-byte coordinate-cube class**. For
    every one of 159 message-byte positions and every one of 2048
    state-output bits, an explicit valid base makes the complete
    256-point cube sum nonzero after two rounds. The
    [certificate](../results/krakken_byte_cube_all159_validated.json) covers all
    325,632 targets with 1,946 base cubes; the
    [independent original-C audit](../results/krakken_byte_cube_all159_audit_validated.json)
    replays all 498,176 vertices through both round counts. Other
    direction sets and non-coordinate masks remain open.
18. A **complete first-order bit-dependency class**. Every 159-byte
    message bit can influence every full-state output bit after
    **one and two** complete rounds. The
    [certificate](../results/krakken_bit_dependency_all1272_validated.json) and
    [independent original-C audit](../results/krakken_bit_dependency_all1272_audit_validated.json)
    cover all `1272 * 2048` input/output bit pairs at each round
    count. First-order influence is already complete at round one;
    this class does not support a round-two-only threshold.
19. A **full-output-mask exclusion for the first-byte message cube**.
    After two complete rounds, 2,048 valid-base cube sums have rank
    2,048, so no nonzero 2,048-bit output mask is balanced for every
    base in this fixed direction family. The
    [rank certificate](../results/krakken_byte_cube_rank_p0_validated.json) and
    [independent original-C audit](../results/krakken_byte_cube_rank_p0_audit_validated.json)
    replay 524,288 valid-message vertices and recover full rank with
    opposite pivot orders. All-output-mask claims for the other 158
    byte positions remain open.
20. A **from-scratch exact division-property theorem** closes the
    first-byte cube across both rounds: the universal balanced
    linear-output-mask space has dimension **7 after round one** and
    **0 after round two**. Exhaustive local eighth derivatives of all
    128 serial-Chi cells plus exact propagation through 32 affine
    Pressure output coordinates construct the seven universal masks;
    original-C cube-sum ranks 2041 and 2048 prove the dimensions
    exact. The [local certificate](../results/krakken_division_exact_byte0_validated.json)
    and [independent audit](../results/krakken_division_exact_byte0_audit_validated.json)
    document the proof.
21. A **complete byte-subspace affine-hull class**. For each of the
    159 zero-base valid-message byte-coordinate subspaces, the image
    hull rank jumps from 8 pre-Chi1 to the maximum 255 at post-Chi1,
    and remains 255 after complete rounds one and two. The
    [original-C report](../results/krakken_subspace_byte_hull_validated.json) and
    [independent replay](../results/krakken_subspace_byte_hull_audit_validated.json)
    cover all 40,704 messages. This excludes universal trails into
    output affine spaces of dimension at most 254 for these 159
    input families; special bases and other subspaces are open.
22. A **complete adversarial Theta-cancelling subspace family** in
    valid message bytes 40 and 56. All 256 cosets of the diagonal
    eight-dimensional subspace have post-Chi1 hull ranks 238–254;
    XRBD preserves rank, while Pressure1 raises **all 256** to the
    maximum 255. The XRBD-off control also reaches 255 at Pressure1.
    Both variants enumerate all 65,536 messages in the two-byte
    plane and have independent original-C-layer replays:
    [XRBD-on certificate](../results/krakken_subspace_theta_pair_cosets_validated.json),
    [audit](../results/krakken_subspace_theta_pair_cosets_audit_validated.json),
    [XRBD-off certificate](../results/krakken_subspace_theta_pair_noxrbd_validated.json),
    [audit](../results/krakken_subspace_theta_pair_noxrbd_audit_validated.json).
    This precisely separates XRBD's byte-support diffusion from
    Pressure's affine-hull rank growth for this family.
23. An **exact local rebound inbound and two-sided outbound
    class** built solely from current C/header sources. A diagonal
    serial-Chi input difference `(d,d)` matches prescribed second
    output difference `eps` for exactly `256*DDT_S(d,eps)` local
    bases, at most 1024. All 32,640 one-byte second-output XRBD
    differences reach all 32 lanes and 48–196 bytes. In the
    backward direction, all 32,640 one-cell diagonal differences
    pull through the invertible prefix to unrestricted input
    differences with all 32 lanes and 40–180 active bytes. The
    [certificate](../results/krakken_rebound_inbound_validated.json) and
    [independent original-C audit](../results/krakken_rebound_inbound_audit_validated.json)
    cover the forward class; the [inverse-prefix certificate](../results/krakken_rebound_backward_validated.json)
    and [audit](../results/krakken_rebound_backward_audit_validated.json)
    cover the backward class.
24. A **first-block hash reachability gate** independently derived
    from the current C prefix: for every one of 128 Chi cells, the
    1,272 message-bit map projected outside that cell has full
    rank 1,272. A nonzero valid first-block difference therefore
    cannot be confined to one pre- or post-Chi cell. The
    [rank certificate](../results/krakken_rebound_rate_gate_validated.json)
    and [opposite-pivot original-C audit](../results/krakken_rebound_rate_gate_audit_validated.json)
    prove this scope. Multi-cell inbound structures remain open.
25. A **fresh four-class boomerang continuation** from current C:
    across 262,144 local bases at one unrestricted site and four
    nonzero difference pairs, **4,784** quartets reach Chi2 as
    rectangles but **zero** satisfy its output condition. Every one
    of those 4,784 has a Chi2 cell with zero rectangle solutions for
    any local base at the fixed input differences. The
    [combined certificate](../results/krakken_boomerang_four_class_verified.json)
    links original-C enumeration and independent Python audits.
26. An **exact global valid-first-block activity minimum**:
    `min A1 = 5` over every nonzero difference between valid 159-byte
    messages and every base message.
    All 128 one-cell, 8,128 two-cell, and 341,376 three-cell supports
    are excluded by quotient rank. Exactly six of 10,668,000
    four-cell supports are reachable, each on a one-dimensional
    difference line; their S-box DDT constraints force at least six
    calls. A five-cell valid-message pair attains `A1=5`, with
    `A2=255` for that witness. For its fixed input difference, the
    event `A1=5` has exact probability `2^-35` under a uniform valid
    base message. Six additional four-cell pairs attain `A1=6` and
    have `A2=253–255`. The [rank certificate](../results/krakken_boomerang_rate_support.json),
    [independent rank audit](../results/krakken_boomerang_rate_support_audit.json),
    [attaining witnesses](../results/krakken_boomerang_four_cell_optimum.json),
    [independent four-cell replay](../results/krakken_boomerang_four_cell_optimum_audit.json),
    [five-cell witness](../results/krakken_five_cell_candidates.json),
    [independent original-C/Python replay](../results/krakken_five_cell_witness_audit.json),
    and [probability audit](../results/krakken_five_cell_probability_audit.json)
    document the scopes.
    For **each of the six** exceptional four-cell input differences,
    a new exact theorem gives `A1=6+Binomial(2,127/128)` under a
    uniform valid base and a **sharp `2^-38`** maximum probability for
    any one post-Chi1 difference. The [certificate](../results/krakken_four_cell_probability.json)
    and [independent C audit](../results/krakken_four_cell_probability_audit.json)
    include full-rank input projections and six attaining pairs.
    The [research notebook](KRAKKEN_PROBE.md) also records a
    constructive check of the heuristic's missing `11..23` bins:
    valid original-C pairs realize every `A1` from 5 through 26.
    Its [22-pair data](../results/krakken_a1_spectrum_5_26.json) and
    [replay audit](../results/krakken_a1_spectrum_5_26_audit.json) remain available
    as search diagnostics, outside the theorem and review claims.
27. A **conditional hash-reachable two-round theorem** for three fixed
    `A1=5` message differences in the selected five-cell dataset:
    every valid base message attaining `A1=5` with any of those
    differences has **at least three active Chi2 cells**, hence
    `A2>=3`. The five first calls fix the post-Chi1 difference.
    Pressure's 32 exact LSB identities reject every two-cell Chi2
    support for two lines. Two pairs survive for the third line; exact
    joint low-two-bit Pressure transitions exclude all 288 remaining
    endpoint assignments. The [producer](../results/krakken_a15_three_line_gate.json)
    and [independent original-C audit](../results/krakken_a15_three_line_gate_audit.json)
    certify the result. It does not bound all valid-message differences.

These statements have their own scopes. They do not combine into an
eight-round numerical security bound by multiplying their maxima.

## Next proof targets

The main linear target is a certified numerical bound on the maximum
**complete** message-to-state linear-hull correlation for each round
count, especially round 8, **over every output mask**. The new
one-round mask-class theorems do not cover that maximum. The immediate
missing Pressure case has,
after exact LSB canonicalization, nonzero masks on both input `a` and
second output `C`. The coupled additions now have an exact counter
and a sharp `1/2` nonperfect bound when **both** output masks lie
within the low 17 bits. An arbitrary 64-bit output-mask theorem is
still missing: above bit 16, the shifted `c` slice overlaps future
input bits, and above bit 30 the shifted `A` term enters the second
addition.
The exact two-addition signed convolution is known, and a reduced-width
counterexample shows why taking absolute values term by term cannot
generally prove the desired `1/2` component bound.
After that, the rate-restricted `2^776`-term signed coset sum and all
intermediate-mask paths still need a rigorous bound. The theorem program
records the exact formula and the failed generic norm/product routes.

A separate differential target is a certified bound on the maximum
hash-reachable differential-hull probability over all nonzero input
differences and all output differences. Existing activity, reachability,
and selected-trail probability results in the notebook are possible
lemmas; they are not that global bound.
The fresh rebound component pass closes one-cell diagonal inbound
matching and its two-sided support, but the first-block rate gate
excludes that inbound class at the real hash interface. The new
support theorem narrows any first-block hash-reachable inbound to at
least four Chi cells, and the exact global Chi1 activity minimum is
now **five**. The next rebound target is a **multi-cell, hash-reachable
inbound** with controlled outbound activity through Chi2; the known
five-call witness has `A2=255`.

Distinct attack classes still underexplored here include
**multi-round differential-linear distinguishers** beyond the defined
classes, **general zero-sum and division-property integrals** beyond
the defined four-state, degree, and byte-0 exact division-property
families, **subspace trails beyond the defined byte-coordinate
class**, and **slide/related-round structures** involving the round
constants.
The [division-property gate audit](../results/krakken_divprop_gate_audit_validated.json)
checks the archived model's C wiring and reduced local rules before
any full-round MILP campaign. It also records why model-reachable
trails cannot be treated as proof that a real cube is unbalanced;
the archived README currently overstates a `K=0` result.
Fixed points and short cycles are also open but are a lower priority
for the hash interface. The new rotational pass closes exact affine
rotation symmetries and empirically screens seven related-input
rotations; it does not cover arbitrary related-input transformations
or statistical rotational hulls. The next differential-linear target
is a hash-reachable or certified multi-round bound; the one-round
unrestricted perfect relations are filtered out at the first padded
hash block.

For each future pass: keep the exact question and input model fixed,
record the proof or counterexample and source hash, update the theorem
program, and add a short public claim only once its complete stated
class is closed. Empirical screens can guide a proof but stay in the
research notebook.

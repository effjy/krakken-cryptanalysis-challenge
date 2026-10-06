# Krakken theorem artifact manifest

This manifest indexes references already cited in each ledger section. It does
not certify their contents or promote a validation report into a proof. Read the
linked theorem for each artifact's exact role and replay coverage. An inherited
dependency may cite artifacts in another theorem's section. Existence was checked
when this navigation refactor was made; source hashes and certificate digests
remain in the original reports. The frozen bundle is not updated.

## LIN-GLOBAL-001

[LIN-GLOBAL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-global-001) — Theorem proved: no perfect relation for rounds 1–8

- [full_linear_rank_8rounds.json](../results/full_linear_rank_8rounds.json) — present.
- [full_linear_rank_8rounds_audit.json](../results/full_linear_rank_8rounds_audit.json) — present.
- [full_linear_rank_8rounds_messages.bin](../results/full_linear_rank_8rounds_messages.bin) — present.
- [krakken_full_linear_rank.py](../scripts/krakken_full_linear_rank.py) — present.
- [krakken_full_linear_rank_audit.py](../scripts/krakken_full_linear_rank_audit.py) — present.

## LIN-CHI-001

[LIN-CHI-001](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-001) — Theorem proved: exact sparse-mask Chi1 correlations

- [krakken_rate_chi_component_rank.py](../scripts/krakken_rate_chi_component_rank.py) — present.
- [krakken_rate_chi_component_rank_audit.py](../scripts/krakken_rate_chi_component_rank_audit.py) — present.
- [rate_chi_component_rank_3_pure_audit.json](../results/rate_chi_component_rank_3_pure_audit.json) — present.
- [rate_chi_component_rank_3_pure_replayed.json](../results/rate_chi_component_rank_3_pure_replayed.json) — present.
- [sbox_walsh_certificate.json](../results/sbox_walsh_certificate.json) — present.

## LIN-CHI-002

[LIN-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-002) — every four-component first-Chi input projection has rank 64; sharp mask maximum 2^-12.

- [THEOREMS.md](../review_extensions_20261003/THEOREMS.md) — analytic proof and exact scope.
- [preparation.json](../review_extensions_20261003/preparation.json), [full_rows.json](../review_extensions_20261003/full_rows.json), [projected_rows.bin](../review_extensions_20261003/projected_rows.bin) — source-pinned rank input certificate.
- [rank_scan.c](../review_extensions_20261003/rank_scan.c), [rank_audit.c](../review_extensions_20261003/rank_audit.c), [rank4.out](../review_extensions_20261003/rank4.out), [rank4_audit.out](../review_extensions_20261003/rank4_audit.out) — two complete four-subset rank enumerations; both rerun in this pass.
- [krakken_rank4_extension_audit.py](../scripts/krakken_rank4_extension_audit.py), [krakken_rank4_extension_audit.json](../results/krakken_rank4_extension_audit.json) — independent Python prefix/row reconstruction and local Walsh check.

## BOOM-LOCAL-001

[BOOM-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#boom-local-001) — Theorem proved: maximal local serial-Chi boomerang family

- [krakken_boomerang_fresh.py](../scripts/krakken_boomerang_fresh.py) — present.

## BOOM-LOCAL-002

[BOOM-LOCAL-002](KRAKKEN_SECURITY_THEOREMS.md#boom-local-002) — Complete local serial-Chi BCT classification and unrestricted full-Chi product corollary.

- [THEOREM.md](THEOREM.md) — analytic reduction, exhaustive case split, full scope and limitations.
- [krakken_chi_bct_classification.py](../scripts/krakken_chi_bct_classification.py) — source-pinned finite verifier and original-C implementation audit.
- [krakken_chi_bct_classification.json](../results/krakken_chi_bct_classification.json) — completed finite certificate, reproduced byte for byte in a fresh run.

## BOOM-EMBED-001

[BOOM-EMBED-001](KRAKKEN_SECURITY_THEOREMS.md#boom-embed-001) — Theorem proved: one-cell boomerang embedding and first-block exclusion

- [krakken_boomerang_embed.json](../results/krakken_boomerang_embed.json) — present.
- [krakken_boomerang_rate_gate.json](../results/krakken_boomerang_rate_gate.json) — present.

## DIFF-RATE-001

[DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001) — Theorem proved: exact first-block Chi1 minimum is 5

- [krakken_boomerang_four_cell_optimum.json](../results/krakken_boomerang_four_cell_optimum.json) — present.
- [krakken_boomerang_four_cell_optimum_audit.json](../results/krakken_boomerang_four_cell_optimum_audit.json) — present.
- [krakken_boomerang_four_cell_outbound.json](../results/krakken_boomerang_four_cell_outbound.json) — present.
- [krakken_boomerang_four_cell_outbound_audit.json](../results/krakken_boomerang_four_cell_outbound_audit.json) — present.
- [krakken_boomerang_four_cell_witness.json](../results/krakken_boomerang_four_cell_witness.json) — present.
- [krakken_boomerang_rate_support.json](../results/krakken_boomerang_rate_support.json) — present.
- [krakken_boomerang_rate_support_audit.json](../results/krakken_boomerang_rate_support_audit.json) — present.
- [krakken_five_cell_candidates.json](../results/krakken_five_cell_candidates.json) — present.
- [krakken_five_cell_probability.json](../results/krakken_five_cell_probability.json) — present.
- [krakken_five_cell_probability_audit.json](../results/krakken_five_cell_probability_audit.json) — present.
- [krakken_five_cell_witness_audit.json](../results/krakken_five_cell_witness_audit.json) — present.
- [krakken_common_prefix_gate_audit.py](../scripts/krakken_common_prefix_gate_audit.py) — source-pinned later-final-absorb replay of inherited rate-only corollary.
- [krakken_common_prefix_gate_audit.json](../results/krakken_common_prefix_gate_audit.json) — 288 paired common-prefix checks; analytic proof remains in the theorem body.

## DIFF-RATE-002

[DIFF-RATE-002](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-002) — Theorem proved: exact sparse-output probabilities for all six four-cell rate lines

- [krakken_four_cell_probability.json](../results/krakken_four_cell_probability.json) — present.
- [krakken_four_cell_probability_audit.json](../results/krakken_four_cell_probability_audit.json) — present.

## DIFF-RATE-003

[DIFF-RATE-003](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-003) — Theorem proved: three fixed valid-message differences satisfy `A1=5 => A2>=3`

- [krakken_a15_three_line_gate.json](../results/krakken_a15_three_line_gate.json) — present.
- [krakken_a15_three_line_gate.py](../scripts/krakken_a15_three_line_gate.py) — present.
- [krakken_a15_three_line_gate_audit.json](../results/krakken_a15_three_line_gate_audit.json) — present.
- [krakken_a15_three_line_gate_audit.py](../scripts/krakken_a15_three_line_gate_audit.py) — present.
- [krakken_five_cell_candidates.json](../results/krakken_five_cell_candidates.json) — present.
- [krakken_sponge_a15_rank_all.json](../results/krakken_sponge_a15_rank_all.json) — present.

## DIFF-RATE-004

[DIFF-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004) — Exact first-full-absorb five-call minimum and inherited common-prefix later-full-block floor.

- [krakken_full_block_rate_support.py](../scripts/krakken_full_block_rate_support.py) — exhaustive C and independent Python prefix support-rank producer.
- [krakken_full_block_rate_support_c_four.json](../results/krakken_full_block_rate_support_c_four.json) — all one- through four-cell original-C support ranks.
- [krakken_full_block_rate_support_python_four.json](../results/krakken_full_block_rate_support_python_four.json) — independent pure-Python prefix full enumeration.
- [krakken_full_block_rate_support_python_low_three.json](../results/krakken_full_block_rate_support_python_low_three.json) — opposite-pivot Python recount of all one- through three-cell supports.
- [krakken_full_block_four_lines.py](../scripts/krakken_full_block_four_lines.py) — all eight exceptional difference lines and DDT lower bounds.
- [krakken_full_block_four_lines.json](../results/krakken_full_block_four_lines.json) — line certificate.
- [krakken_full_block_four_lines_audit.py](../scripts/krakken_full_block_four_lines_audit.py) — separate Python-prefix/DDT replay.
- [krakken_full_block_four_lines_audit.json](../results/krakken_full_block_four_lines_audit.json) — eight-line audit result.
- [krakken_full_block_witness_audit.py](../scripts/krakken_full_block_witness_audit.py) — original-C replay of actual 160-byte hash messages.
- [krakken_full_block_witness_audit.json](../results/krakken_full_block_witness_audit.json) — five-call attaining messages and full API digests.

## CHI-RATE-001

[CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001) — 133-byte first-Chi joint-uniformity theorem and exact differential/linear corollaries.

- [RESULTS2.md](../RESULTS2.md) — analytic statement, proof, scope and replay instructions.
- [branch_rank.py](../discovery2/branch_rank.py), [branch_rank.json](../discovery2/branch_rank.json) — original-C prefix rows and 1024/1272 rank certificate.
- [conditional_rank.py](../discovery2/conditional_rank.py), [conditional_rank.json](../discovery2/conditional_rank.json) — quotient rows for conditional second-byte projections.
- [conditional_scan.c](../discovery2/conditional_scan.c), [conditional_scan_5.json](../discovery2/conditional_scan_5.json), [conditional_resolution.json](../discovery2/conditional_resolution.json) — complete projected producer scan and full-row resolution of all 21 projected defects.
- [conditional_audit_prepare.py](../discovery2/conditional_audit_prepare.py), [conditional_scan_audit.c](../discovery2/conditional_scan_audit.c), [conditional_scan_audit_5.json](../discovery2/conditional_scan_audit_5.json), [conditional_resolution_audit.json](../discovery2/conditional_resolution_audit.json) — separate prefix, quotient, projection, reverse enumeration, and full-row resolution of all 11 projected defects.
- [linear_certificate.py](../discovery2/linear_certificate.py), [linear_certificate.json](../discovery2/linear_certificate.json) — complete local Walsh maxima and attaining `-2^-384` mask witness.
- [validate_structure.py](../discovery2/validate_structure.py), [structure_validation.json](../discovery2/structure_validation.json) — original-C constructed-message replay, byte-DDT audit and reduced correlated-fiber logic test.
- [integrity_check.json](../discovery2/integrity_check.json) — saved artifact/source hashes and coverage bookkeeping; does not rerun exhaustive scans.
- [krakken_chi_rate_promotion_audit.py](../scripts/krakken_chi_rate_promotion_audit.py), [krakken_chi_rate_promotion_audit.json](../results/krakken_chi_rate_promotion_audit.json) — read-only current-source/hash/rank/exception check with 200 reproducible full-row samples; not a scan replay.
- [DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001), [DIFF-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004) — inherited five-call floors for 159-/160-byte rate differences.

## DIFF-ACT-001

[DIFF-ACT-001](KRAKKEN_SECURITY_THEOREMS.md#diff-act-001) — exact activity syndrome and conditioned specified eight-bit complete-round projection.

- [RESULTS3.md](../RESULTS3.md) — analytic proof, exact scope, limitations, and replay plan.
- [activity_fibers.py](../discovery3/activity_fibers.py), [activity_fibers.json](../discovery3/activity_fibers.json) — source-pinned DDT fibers, exact activity constructor, and original-C samples.
- [activity_audit.py](../discovery3/activity_audit.py), [activity_audit.json](../discovery3/activity_audit.json) — separate prefix/rank/DDT reconstruction and original-C implementation audit.
- [activity_spectrum.py](../discovery3/activity_spectrum.py), [activity_spectrum.json](../discovery3/activity_spectrum.json) — grouped Fourier formula and finite direct-transform checks.
- [conditioning_bounds.py](../discovery3/conditioning_bounds.py), [conditioning_bounds.json](../discovery3/conditioning_bounds.json) — exact event probabilities and rational bounds for constructed cases.
- [differing_prefixes.py](../discovery3/differing_prefixes.py), [differing_prefixes.json](../discovery3/differing_prefixes.json) — actual-message differing-prefix and original-C hash-API replay.
- [integrity.json](../discovery3/integrity.json) — saved source/dependency/report hashes; integrity check only, not full computation replay.
- [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) — inherited complete-round all-message-mask bound and Pressure certificate.

## DIFF-RATE-005

[DIFF-RATE-005](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-005) — global prescribed-difference concentration at Chi1/XRBD1.

- [THEOREMS.md](../review_extensions_20261003/THEOREMS.md) — local DDT lemma, four-cell factorization, conditioning and Pressure boundary.
- [LIN-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-002), [DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001) — inherited four-cell base independence and minimum support.
- [krakken_rank4_extension_audit.json](../results/krakken_rank4_extension_audit.json) — separate source S-box derivative and projection-row checks.

## DIFF-RATE-006

[DIFF-RATE-006](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-006) — one-complete-round almost-all-input-differences bound on a specified eight-bit nondigest projection.

- [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) — inherited all-input-mask linear bound and source/implementation audit.
- [krakken_round1_almost_all_differentials.py](../scripts/krakken_round1_almost_all_differentials.py), [krakken_round1_almost_all_differentials.json](../results/krakken_round1_almost_all_differentials.json) — exact rational-square sum and Fourier/Markov corollary arithmetic.
- [krakken_round1_almost_all_differentials_audit.py](../scripts/krakken_round1_almost_all_differentials_audit.py), [krakken_round1_almost_all_differentials_audit.json](../results/krakken_round1_almost_all_differentials_audit.json) — separate integer arithmetic audit.

## DIFF-RATE-007

[DIFF-RATE-007](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-007) — conditioned
complete-round differential bounds for the three DIFF-RATE-003 differences.

- [Proof/reproduction note](KRAKKEN_CONDITIONED_PRESSURE_DIFFERENTIAL.md).
- [Slice producer](../scripts/krakken_conditioned_pressure_differential.py), [chain-2 four-bit report](../results/krakken_conditioned_pressure_ch02_k4.json), [chain-1 five-bit report](../results/krakken_conditioned_pressure_ch01_k5.json): all slice-mask bounds and actual-message witnesses.
- [Event producer](../scripts/krakken_conditioned_pressure_events.py), [event certificate](../results/krakken_conditioned_pressure_events.json): exact local differential-event spectra and rational bounds.
- [Separate implementation audit](../scripts/krakken_conditioned_pressure_audit.py), [audit report](../results/krakken_conditioned_pressure_audit.json): independently reconstructed matrices, ranks, spectra, event fibers and original-C pair replays.
- [Unsuccessful chain-14 pilot](../results/krakken_conditioned_pressure_ch14_k4.json): vacuous whole-slice bound retained outside theorem evidence.
- Inherited: DIFF-RATE-003 fixed differences and fixed post-Chi differences; DIFF-ACT-001 affine activity fibers; LIN-RATE-004 effective-coordinate affine-image lemma. The new report is conditional on A1=5; no unconditional or multi-round claim.

## DIFF-RATE-008

[DIFF-RATE-008](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-008) — unconditional
first-complete-round all-output point bound for the three fixed differences.

- [Proof/reproduction note](KRAKKEN_UNCONDITIONAL_ROUND1_DIFFERENTIAL.md).
- [Producer](../scripts/krakken_unconditional_round1_differential.py), [ten-bit certificate](../results/krakken_unconditional_round1_differential_k5.json): five-cell input ranks, local histograms, exact convolution, all projected output counts and actual-message witnesses.
- [Independent implementation audit](../scripts/krakken_unconditional_round1_differential_audit.py), [separate scalar C mixture counter](../scripts/krakken_pressure_mixture_audit.c), [final audit report](../results/krakken_unconditional_round1_differential_k5_audit_final.json): all slice-character bounds, exact mixtures and original-C replays.
- [Inherited four-bit slice report](../results/krakken_conditioned_pressure_ch02_k4.json): all 4,095 bounds, independently fully reconstructed in the new audit.
- [Initial eight-bit pilot](../results/krakken_unconditional_round1_differential.json), [original pilot producer](../scripts/krakken_unconditional_round1_differential_initial.py): historical stage of this pass, not the final ten-bit certificate.
- [Vacuous fifteen-bit whole-slice pilot](../results/krakken_conditioned_pressure_ch02_k5.json): failed inequality, not theorem evidence.
- Dependencies: the effective-coordinate affine-image lemma of LIN-RATE-004 and the fixed message differences identified by DIFF-RATE-003. The A1=5 event and conditional DIFF-RATE-007 probability bounds are not premises of the unconditional result.

## DIFF-CHI-001

[DIFF-CHI-001](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-001) — affine active-first-call transition fibers and exact hash-base rank count.

- [THEOREMS.md](../review_extensions_20261003/THEOREMS.md) — analytic fiber argument and boundaries.
- [local_fibers.py](../review_extensions_20261003/local_fibers.py), [local_fibers.json](../review_extensions_20261003/local_fibers.json) — derivative-fiber exhaustion, 128 local direct transition checks, original-C representatives.
- [krakken_rank4_extension_audit.json](../results/krakken_rank4_extension_audit.json) — separately reproduced derivative histogram.

## DIFF-CHI-002

[DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002) — exact unrestricted local serial-Chi maximum-DP trichotomy and unique maximizers.

- [NEW.md](../NEW.md) — provisional candidate and motivating classification; proof status is in the ledger.
- [krakken_serial_chi_differential_trichotomy.py](../scripts/krakken_serial_chi_differential_trichotomy.py), [krakken_serial_chi_differential_trichotomy.json](../results/krakken_serial_chi_differential_trichotomy.json) — pinned source DDT, complete 65,535-difference/maximizer enumeration and 63 original-C transition replays.
- [krakken_serial_chi_differential_trichotomy_audit.c](../scripts/krakken_serial_chi_differential_trichotomy_audit.c), [krakken_serial_chi_differential_trichotomy_audit.json](../results/krakken_serial_chi_differential_trichotomy_audit.json) — separate complete C DDT/maximizer recount.

## DL-LOCAL-001

[DL-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-local-001) — complete perfect local serial-Chi differential-linear class and conservative bound elsewhere.

- [NEW.md](../NEW.md) — provisional candidate; precise proof and bound are in the ledger.
- [krakken_serial_chi_dlct.py](../scripts/krakken_serial_chi_dlct.py), [krakken_serial_chi_dlct.json](../results/krakken_serial_chi_dlct.json) — complete source S-box ACT, 128 direct exhaustive local-formula checks and analytic class inputs.
- [krakken_serial_chi_dlct_audit.c](../scripts/krakken_serial_chi_dlct_audit.c), [krakken_serial_chi_dlct_audit.json](../results/krakken_serial_chi_dlct_audit.json) — separate complete byte-ACT histogram/max audit.
- [DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002) — inherited original-C local-map transition replays.

## BOOM-ROUND-001

[BOOM-ROUND-001](KRAKKEN_SECURITY_THEOREMS.md#boom-round-001) — Theorem proved: four defined boomerang classes do not cross Chi2

- [krakken_boomerang_cell_audit.json](../results/krakken_boomerang_cell_audit.json) — present.
- [krakken_boomerang_cell_exhaust.json](../results/krakken_boomerang_cell_exhaust.json) — present.
- [krakken_boomerang_cell_suite.json](../results/krakken_boomerang_cell_suite.json) — present.
- [krakken_boomerang_cell_suite_audit.json](../results/krakken_boomerang_cell_suite_audit.json) — present.
- [krakken_boomerang_four_class_verified.json](../results/krakken_boomerang_four_class_verified.json) — present.
- [krakken_boomerang_fresh_audit.json](../results/krakken_boomerang_fresh_audit.json) — present.
- [krakken_boomerang_fresh_report.json](../results/krakken_boomerang_fresh_report.json) — present.

## BOOM-ROUND-002

[BOOM-ROUND-002](KRAKKEN_SECURITY_THEOREMS.md#boom-round-002) — Stronger certificate: each Pressure survivor has a base-independent Chi2 obstruction

- [krakken_boomerang_cell_suite_audit.json](../results/krakken_boomerang_cell_suite_audit.json) — present.
- [krakken_boomerang_cell_suite_obstruction.json](../results/krakken_boomerang_cell_suite_obstruction.json) — present.
- [krakken_boomerang_chi2_obstruction.json](../results/krakken_boomerang_chi2_obstruction.json) — present.
- [krakken_boomerang_chi2_obstruction.py](../scripts/krakken_boomerang_chi2_obstruction.py) — present.
- [krakken_boomerang_chi2_obstruction_audit.json](../results/krakken_boomerang_chi2_obstruction_audit.json) — present.

## DIFF-PERM-001

[DIFF-PERM-001](KRAKKEN_SECURITY_THEOREMS.md#diff-perm-001) — Theorem proved: one active Chi1 call reaches every Pressure chain

- [krakken_xrbd_onebyte_pressure_chains.json](../results/krakken_xrbd_onebyte_pressure_chains.json) — present.
- [krakken_xrbd_onebyte_pressure_chains.py](../scripts/krakken_xrbd_onebyte_pressure_chains.py) — present.

## DIFF-PERM-002

[DIFF-PERM-002](KRAKKEN_SECURITY_THEOREMS.md#diff-perm-002) — Theorem proved: no unrestricted two-round `[1,1]` differential trail

- [oracle_optimized.py](../scripts/oracle_optimized.py) — byte-identical local copy of the historical optimized oracle; its `--self-test` passes, but this is not an independent solver replay.
- [krakken_prove_12_oracle_v7.py](../scripts/krakken_prove_12_oracle_v7.py) — byte-identical adjacent dependency required by the optimized oracle; pass `--source-dir /home/user/sol` when running the copied driver.
- [../krakken/krakken_prove_11_v2.py](../krakken/krakken_prove_11_v2.py) — present.
- [../krakken/prove_11_full.log](../krakken/prove_11_full.log) — present.
- [krakken_11_audit.py](../scripts/krakken_11_audit.py) — present.
- [krakken_11_audit_validated.json](../results/krakken_11_audit_validated.json) — present.
- [krakken_pressure_lsb_endpoint_rank.json](../results/krakken_pressure_lsb_endpoint_rank.json) — present.

## DIFF-12-001

[DIFF-12-001](KRAKKEN_SECURITY_THEOREMS.md#diff-12-001) — Defined `[1,2]` subclass excluded without a carry solver

- [krakken_pressure_lsb_endpoint.py](../scripts/krakken_pressure_lsb_endpoint.py) — present.
- [krakken_pressure_lsb_endpoint_rank.json](../results/krakken_pressure_lsb_endpoint_rank.json) — present.
- [krakken_pressure_lsb_rank_audit.py](../scripts/krakken_pressure_lsb_rank_audit.py) — present.

## DIFF-12-002

[DIFF-12-002](KRAKKEN_SECURITY_THEOREMS.md#diff-12-002) — Exact two-bit carry exclusion for one complete start-position slice

- [krakken_12_joint2_screen.py](../scripts/krakken_12_joint2_screen.py) — present.
- [krakken_12_joint2_start0.json](../results/krakken_12_joint2_start0.json) — present.
- [krakken_12_joint2_start0_audit.json](../results/krakken_12_joint2_start0_audit.json) — present.
- [krakken_12_joint2_start0_audit.py](../scripts/krakken_12_joint2_start0_audit.py) — present.

## DIFF-12-003

[DIFF-12-003](KRAKKEN_SECURITY_THEOREMS.md#diff-12-003) — Theorem proved: exact two-bit Pressure gate excludes 1,628,104 `[1,2]` site cases

- [krakken_12_joint2_all_positions.py](../scripts/krakken_12_joint2_all_positions.py) — present.
- [krakken_12_joint2_all_positions/audit_summary_k18.json](../results/krakken_12_joint2_all_positions/audit_summary_k18.json) — present.
- [krakken_12_joint2_all_positions/summary_k18.json](../results/krakken_12_joint2_all_positions/summary_k18.json) — present.
- [krakken_12_joint2_all_positions_audit.py](../scripts/krakken_12_joint2_all_positions_audit.py) — present.

## DIFF-12-004

[DIFF-12-004](KRAKKEN_SECURITY_THEOREMS.md#diff-12-004) — Theorem proved: no unrestricted `[1,2]` trail with two distinct Chi2 second-branch calls

- [krakken_12_joint3_all_positions_summary.json](../results/krakken_12_joint3_all_positions_summary.json) — present.
- [krakken_12_refine_sat.py](../scripts/krakken_12_refine_sat.py) — present.
- [krakken_12_refine_sat_audit.py](../scripts/krakken_12_refine_sat_audit.py) — present.
- [krakken_12_sat_refinement.json](../results/krakken_12_sat_refinement.json) — present.
- [krakken_12_sat_refinement_audit.json](../results/krakken_12_sat_refinement_audit.json) — present.

## DIFF-12-005

[DIFF-12-005](KRAKKEN_SECURITY_THEOREMS.md#diff-12-005) — Theorem proved: no unrestricted `[1,2]` trail with both Chi2 calls in one spatial pair

- [krakken_12_remaining_split.py](../scripts/krakken_12_remaining_split.py) — present.
- [krakken_12_remaining_split_results](../results/krakken_12_remaining_split_results) — present.
- [krakken_12_same_refinement.json](../results/krakken_12_same_refinement.json) — present.

## DIFF-12-006

[DIFF-12-006](KRAKKEN_SECURITY_THEOREMS.md#diff-12-006) — Complete distinct-AA `[1,2]` endpoint exclusion.

- [krakken_12_remaining_split.py](../scripts/krakken_12_remaining_split.py) — source-pinned split-site producer.
- [krakken_12_remaining_split_results](../results/krakken_12_remaining_split_results) — 256 AA position reports.
- [krakken_12_refine_position.py](../scripts/krakken_12_refine_position.py) — low-four/five-bit relaxed-SAT refinement.
- [krakken_12_aa_closure_audit.py](../scripts/krakken_12_aa_closure_audit.py) — complete saved-result coverage and integrity audit; not an independent solver recount.
- [krakken_12_aa_closure_audit.json](../results/krakken_12_aa_closure_audit.json) — source pins, per-file hashes, and final counts.

## ROT-001

[ROT-001](KRAKKEN_SECURITY_THEOREMS.md#rot-001) — Theorem proved: no exact lane-rotation covariance through eight rounds

- [krakken_rotational_affine_audit.json](../results/krakken_rotational_affine_audit.json) — present.
- [krakken_rotational_affine_audit.py](../scripts/krakken_rotational_affine_audit.py) — present.

## ROT-002

[ROT-002](KRAKKEN_SECURITY_THEOREMS.md#rot-002) — Exact one-round byte-rotation residual decomposition

- [krakken_rotational_decomposition.py](../scripts/krakken_rotational_decomposition.py) — present.
- [krakken_rotational_decomposition_validated.json](../results/krakken_rotational_decomposition_validated.json) — present.

## LIN-THETA-001

[LIN-THETA-001](KRAKKEN_SECURITY_THEOREMS.md#lin-theta-001) — exact fixed-space dimension, image rank, and cycle decomposition of the current scalar Theta layer alone.

- [krakken_theta_fixed_space.py](../scripts/krakken_theta_fixed_space.py) — source-pinned original-C 2048-column matrix and explicit-basis producer.
- [krakken_theta_fixed_space.matrix.bin](../results/krakken_theta_fixed_space.matrix.bin) — exact 2048×2048 GF(2) map, encoded as 2048 little-endian 256-byte output columns.
- [krakken_theta_fixed_space.basis.bin](../results/krakken_theta_fixed_space.basis.bin) — explicit 1544-vector fixed-state basis, 256 little-endian bytes per vector.
- [krakken_theta_fixed_space.json](../results/krakken_theta_fixed_space.json) — source/matrix/basis hashes, all-basis C checks and 16 explicit non-fixed C two-cycle witnesses.
- [krakken_theta_fixed_space_audit.py](../scripts/krakken_theta_fixed_space_audit.py), [krakken_theta_fixed_space_audit.json](../results/krakken_theta_fixed_space_audit.json) — independent pure-Python reconstruction of every column and basis vector with opposite-pivot rank checks.

To reproduce without overwriting the saved artifacts:

```bash
/home/user/venv/krakken/bin/python scripts/krakken_theta_fixed_space.py --output-prefix /tmp/krakken_theta_replay
/home/user/venv/krakken/bin/python scripts/krakken_theta_fixed_space_audit.py --input-prefix /tmp/krakken_theta_replay --output /tmp/krakken_theta_replay_audit.json
```

## DL-001

[DL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-001) — Theorem proved: complete one-round differential-linear mask class

- [krakken_differential_linear.py](../scripts/krakken_differential_linear.py) — present.
- [krakken_differential_linear_round2_20k.json](../results/krakken_differential_linear_round2_20k.json) — present.
- [krakken_differential_linear_validated.json](../results/krakken_differential_linear_validated.json) — present.

## DL-002

[DL-002](KRAKKEN_SECURITY_THEOREMS.md#dl-002) — Theorem proved: no perfect two-round output mask for 128 fixed differences

- [krakken_differential_linear_fullstate_audit.py](../scripts/krakken_differential_linear_fullstate_audit.py) — present.
- [krakken_differential_linear_fullstate_audit_validated.json](../results/krakken_differential_linear_fullstate_audit_validated.json) — present.
- [krakken_differential_linear_fullstate_rank_all128.json](../results/krakken_differential_linear_fullstate_rank_all128.json) — present.

## PRESS-WALSH-001

[PRESS-WALSH-001](KRAKKEN_SECURITY_THEOREMS.md#press-walsh-001) — Theorem proved: complete first-output Pressure mask class

- [krakken_pressure_first_branch_walsh.py](../scripts/krakken_pressure_first_branch_walsh.py) — present.
- [pressure_first_branch_walsh_full_layer.json](../results/pressure_first_branch_walsh_full_layer.json) — present.

## PRESS-WALSH-002

[PRESS-WALSH-002](KRAKKEN_SECURITY_THEOREMS.md#press-walsh-002) — Theorem extension: second shear and second-output LSB

- [krakken_pressure_second_shear_walsh.py](../scripts/krakken_pressure_second_shear_walsh.py) — present.
- [pressure_two_shear_affine_extended_validated.json](../results/pressure_two_shear_affine_extended_validated.json) — present.

## PRESS-WALSH-003

[PRESS-WALSH-003](KRAKKEN_SECURITY_THEOREMS.md#press-walsh-003) — Theorem proved: exact joint-carry counter for all low-17 output masks

- [krakken_pressure_joint_lowbit_walsh.py](../scripts/krakken_pressure_joint_lowbit_walsh.py) — present.
- [krakken_pressure_lowbit_half_theorem.py](../scripts/krakken_pressure_lowbit_half_theorem.py) — present.
- [krakken_pressure_lowbit_max_certificate.py](../scripts/krakken_pressure_lowbit_max_certificate.py) — present.
- [krakken_pressure_lowbit_top_support.py](../scripts/krakken_pressure_lowbit_top_support.py) — present.
- [pressure_joint_lowbit_walsh_validated.json](../results/pressure_joint_lowbit_walsh_validated.json) — present.
- [pressure_lowbit_half_theorem_algebraic_validated.json](../results/pressure_lowbit_half_theorem_algebraic_validated.json) — present.
- [pressure_lowbit_max_k6_certificate.json](../results/pressure_lowbit_max_k6_certificate.json) — present.
- [pressure_lowbit_top_support_validated.json](../results/pressure_lowbit_top_support_validated.json) — present.

## PRESS-DIFF-001

[PRESS-DIFF-001](KRAKKEN_SECURITY_THEOREMS.md#press-diff-001) — exact local two-bit Pressure difference gate and complete quadratic obstruction.

- [RESULTS4.md](../RESULTS4.md) — analytic carry-rank derivation, scope and bounded next tests.
- [carry_relation_polynomials.py](../discovery4/carry_relation_polynomials.py), [carry_relation_polynomials.json](../discovery4/carry_relation_polynomials.json) — full degree≤4 vanishing-polynomial spaces and common-zero checks.
- [three_cubic_gate.py](../discovery4/three_cubic_gate.py), [three_cubic_gate.json](../discovery4/three_cubic_gate.json) — exact 1024-profile cubic verification.

## PRESS-DIFF-002

[PRESS-DIFF-002](KRAKKEN_SECURITY_THEOREMS.md#press-diff-002) — exact low-three-bit Pressure relation, polynomial hierarchy and affine exception.

- [KRAKKEN_PRESSURE_ALGEBRA_PILOT.md](KRAKKEN_PRESSURE_ALGEBRA_PILOT.md) — proof scope, complete counts and separate bounded site benchmark.
- [krakken_pressure_low3_polynomial.py](../scripts/krakken_pressure_low3_polynomial.py), [krakken_pressure_low3_polynomial_d5.json](../results/krakken_pressure_low3_polynomial_d5.json) — full local profile and degree≤5 polynomial-space producer.
- [krakken_pressure_low3_affine_exception_audit.py](../scripts/krakken_pressure_low3_affine_exception_audit.py), [krakken_pressure_low3_affine_exception_audit.json](../results/krakken_pressure_low3_affine_exception_audit.json) — separate difference-first enumeration, opposite-pivot closures and affine-flat certificate.
- [krakken_pressure_low3_single_quintic.py](../scripts/krakken_pressure_low3_single_quintic.py), [krakken_pressure_low3_single_quintic.json](../results/krakken_pressure_low3_single_quintic.json) — explicit 82-term quintic separating the cubic false profiles.
- [krakken_pressure_low3_single_quintic_audit.py](../scripts/krakken_pressure_low3_single_quintic_audit.py), [krakken_pressure_low3_single_quintic_audit.json](../results/krakken_pressure_low3_single_quintic_audit.json) — separate direct local enumeration and full ANF truth-table audit.
- [bounded_checks.json](../discovery4/bounded_checks.json) — inherited original-C full-word low-six-bit slice audit for source correspondence.

## PRESS-HULL-001

[PRESS-HULL-001](KRAKKEN_SECURITY_THEOREMS.md#press-hull-001) — Exact coupled-chain hull identity and a failed bound

- [krakken_pressure_coupled_hull.py](../scripts/krakken_pressure_coupled_hull.py) — present.
- [pressure_coupled_hull_w4_r3_l3_checked.json](../results/pressure_coupled_hull_w4_r3_l3_checked.json) — present.

## PRESS-ZERO-001

[PRESS-ZERO-001](KRAKKEN_SECURITY_THEOREMS.md#press-zero-001) — Exact-zero Pressure mask families

- [krakken_pressure_pairwise_independence.py](../scripts/krakken_pressure_pairwise_independence.py) — present.
- [pressure_pairwise_independence_validated.json](../results/pressure_pairwise_independence_validated.json) — present.

## LIN-RATE-001

[LIN-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-001) — Theorem proved: 16 complete first-round hash-mask bounds

- [KRAKKEN_CLAIMS_FOR_REVIEW.md](KRAKKEN_CLAIMS_FOR_REVIEW.md) — present.
- [hash_round1_pressure_affine_48_validated_v3.json](../results/hash_round1_pressure_affine_48_validated_v3.json) — present.
- [hash_round1_pressure_affine_AC_pairs_validated.json](../results/hash_round1_pressure_affine_AC_pairs_validated.json) — present.

## LIN-RATE-002

[LIN-RATE-002](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-002) — Theorem proved: a five-dimensional first-round hash-output subspace

- [hash_round1_AC_coordinate_subspaces_128_validated_v3.json](../results/hash_round1_AC_coordinate_subspaces_128_validated_v3.json) — present.
- [hash_round1_pressure_affine_48_validated_v3.json](../results/hash_round1_pressure_affine_48_validated_v3.json) — present.
- [hash_round1_pressure_affine_AC_pairs_validated.json](../results/hash_round1_pressure_affine_AC_pairs_validated.json) — present.
- [krakken_hash_round1_affine_subspace.py](../scripts/krakken_hash_round1_affine_subspace.py) — present.

## LIN-RATE-003

[LIN-RATE-003](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-003) — Theorem proved: a six-dimensional first-round hash-output subspace

- [hash_round1_AC_coordinate_subspaces_76_validated_v2.json](../results/hash_round1_AC_coordinate_subspaces_76_validated_v2.json) — present.
- [hash_round1_pressure_affine_48_validated_v3.json](../results/hash_round1_pressure_affine_48_validated_v3.json) — present.
- [hash_round1_pressure_affine_AC_pairs_validated.json](../results/hash_round1_pressure_affine_AC_pairs_validated.json) — present.

## LIN-RATE-004

[LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) — Complete-first-round eight-bit nonlinear-Pressure bridge and affine-conditioned output-distribution bound.

- [RESULTS.md](../RESULTS.md) — full analytic proof, certificate obligations, assumptions, and limitations.
- [pressure_bridge.py](../discovery/pressure_bridge.py) — source-pinned producer; fresh replay saved to a separate temporary path was byte-identical.
- [pressure_bridge_k4_pilot.json](../discovery/pressure_bridge_k4_pilot.json) — complete 4-bit chain certificate, including all 255 chain-1 rational bounds.
- [pressure_bridge_audit.py](../discovery/pressure_bridge_audit.py) — separately implemented rank, Walsh, XRBD, and original-C output audit.
- [pressure_bridge_k4_audit.json](../discovery/pressure_bridge_k4_audit.json) — PASS report; fresh audit replay was byte-identical.

## ALG-DEG-001

[ALG-DEG-001](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-001) — Theorem proved: valid-message coordinate-degree map through eight rounds

- [degree_fullstate_allcoords_d20_validated.json](../results/degree_fullstate_allcoords_d20_validated.json) — present.
- [degree_hash_cube24_validated_v3.json](../results/degree_hash_cube24_validated_v3.json) — present.
- [degree_hash_digest_allcoords_d20_validated_v2.json](../results/degree_hash_digest_allcoords_d20_validated_v2.json) — present.
- [degree_hash_round1_lowbits_mapping_validated.json](../results/degree_hash_round1_lowbits_mapping_validated.json) — present.
- [degree_round1_pressure_lsb_all32_exact13_validated.json](../results/degree_round1_pressure_lsb_all32_exact13_validated.json) — present.
- [krakken_degree_multiround_audit.py](../scripts/krakken_degree_multiround_audit.py) — present.
- [serial_chi_16bit_degree_validated.json](../results/serial_chi_16bit_degree_validated.json) — present.

## ALG-DEG-002

[ALG-DEG-002](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-002) — exact low-six-bit local Pressure degrees and 192 first-round coordinate upper bounds.

- [RESULTS4.md](../RESULTS4.md) — analytic degree-composition proof and limitations.
- [bounded_checks.py](../discovery4/bounded_checks.py), [bounded_checks.json](../discovery4/bounded_checks.json) — full 18-variable ANF, inverse transform and original-C slice checks.
- [ALG-DEG-001](KRAKKEN_SECURITY_THEOREMS.md#alg-deg-001) — inherited exact bit-zero and lower-degree certificates on valid 159-byte messages.

## LIN-HULL-001

[LIN-HULL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-hull-001) — Exact formula for the full rate-restricted hull

No direct artifact path is cited in this subsection; use the proof or parent section and dependency map.

## ZERO-001

[ZERO-001](KRAKKEN_SECURITY_THEOREMS.md#zero-001) — Proved: a four-state Chi/XRBD zero sum and its two-round exclusion

- [krakken_zero_sum_allcells_validated.json](../results/krakken_zero_sum_allcells_validated.json) — present.
- [krakken_zero_sum_hash_cube_validated.json](../results/krakken_zero_sum_hash_cube_validated.json) — present.
- [krakken_zero_sum_square.py](../scripts/krakken_zero_sum_square.py) — present.
- [krakken_zero_sum_square_audit_validated.json](../results/krakken_zero_sum_square_audit_validated.json) — present.
- [krakken_zero_sum_square_validated.json](../results/krakken_zero_sum_square_validated.json) — present.

## INT-CUBE-001

[INT-CUBE-001](KRAKKEN_SECURITY_THEOREMS.md#int-cube-001) — Proved: hash-reachable 14-cube zero sums and exact round-two coordinate exclusion

- [krakken_hash_chi_cube_threshold.py](../scripts/krakken_hash_chi_cube_threshold.py) — present.
- [krakken_hash_chi_cube_threshold_audit_validated.json](../results/krakken_hash_chi_cube_threshold_audit_validated.json) — present.
- [krakken_hash_chi_cube_threshold_validated.json](../results/krakken_hash_chi_cube_threshold_validated.json) — present.
- [krakken_hash_zero_sum_14cube_audit_validated.json](../results/krakken_hash_zero_sum_14cube_audit_validated.json) — present.
- [krakken_hash_zero_sum_14cube_validated.json](../results/krakken_hash_zero_sum_14cube_validated.json) — present.
- [serial_chi_16bit_degree_validated.json](../results/serial_chi_16bit_degree_validated.json) — present.

## INT-KERNEL-001

[INT-KERNEL-001](KRAKKEN_SECURITY_THEOREMS.md#int-kernel-001) — sharp
kernel-directed checkpoint integral threshold eight; exact 32/0 universal
mask spaces at complete rounds one/two for one saved eight-direction cube.

- [RESULTS5.md](../RESULTS5.md): full statement, analytic proof, scope and reproduction commands; unchanged original report.
- [Kernel construction producer](../discovery5/kernel_cube_setup.py), [construction certificate](../discovery5/kernel_cube.json): all 248 kernel directions, eight cube directions, seven sharpness directions, S-box ANF and balanced-bit positions.
- [Original-C cube engine](../discovery5/cube_engine.c), [rank producer](../discovery5/cube_rank.py), [original rank certificate](../discovery5/cube_rank_certificate.json): all 2,049 bases and complete-round sums.
- [Independent implementation audit](../discovery5/audit_kernel_cubes.py), [original full audit](../discovery5/cube_audit.json): separate NumPy/GF(256)/SHAKE derivation and complete replay.
- [Fresh C replay](../results/krakken_kernel_integral_c_replay.json), [fresh full implementation replay](../results/krakken_kernel_integral_promotion_audit.json): repeated during promotion; all records/ranks agree.
- [Promotion checker](../scripts/krakken_kernel_integral_promotion_check.py), [promotion report](../results/krakken_kernel_integral_promotion_check.json): provenance, fresh record equality, opposite-pivot ranks, exact balanced positions and digest-projection generators. Requires the fresh replay artifacts; does not itself evaluate cubes.
- [Original manifest](../discovery5/manifest.json): unchanged 24-file **pre-promotion** source/artifact/documentation snapshot. All hashes matched before promotion; documentation hashes are historical after the authorized edits.
- Dependencies: CHI-RATE-001 first-branch rank/surjectivity, source S-box degree seven, exact Pressure LSB identities. Generic INT-CUBE-001 and byte-family INT-BYTE-002 are comparison results, not premises of the new integral.

## INT-BYTE-001

[INT-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#int-byte-001) — Proved: complete one-byte coordinate-cube class has no universal round-two coordinate balance

- [krakken_byte_cube_all159_audit_validated.json](../results/krakken_byte_cube_all159_audit_validated.json) — present.
- [krakken_byte_cube_all159_validated.json](../results/krakken_byte_cube_all159_validated.json) — present.

## INT-BYTE-002

[INT-BYTE-002](KRAKKEN_SECURITY_THEOREMS.md#int-byte-002) — Proved: no universal round-two linear output-mask balance for the byte-0 cube

- [krakken_byte_cube_rank_p0_audit_validated.json](../results/krakken_byte_cube_rank_p0_audit_validated.json) — present.
- [krakken_byte_cube_rank_p0_validated.json](../results/krakken_byte_cube_rank_p0_validated.json) — present.

## DIV-BYTE-001

[DIV-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#div-byte-001) — Proved: exact byte-0 division-property balance threshold, rounds one and two

- [krakken_byte_cube_rank_p0_audit_validated.json](../results/krakken_byte_cube_rank_p0_audit_validated.json) — present.
- [krakken_byte_cube_rank_p0_validated.json](../results/krakken_byte_cube_rank_p0_validated.json) — present.
- [krakken_division_exact_byte0.py](../scripts/krakken_division_exact_byte0.py) — present.
- [krakken_division_exact_byte0_audit_validated.json](../results/krakken_division_exact_byte0_audit_validated.json) — present.
- [krakken_division_exact_byte0_validated.json](../results/krakken_division_exact_byte0_validated.json) — present.

## SUBSPACE-001

[SUBSPACE-001](KRAKKEN_SECURITY_THEOREMS.md#subspace-001) — Proved: maximal affine-hull growth of every message-byte subspace at Chi1

- [krakken_subspace_byte_hull.c](../source/krakken_subspace_byte_hull.c) — present.
- [krakken_subspace_byte_hull_audit_validated.json](../results/krakken_subspace_byte_hull_audit_validated.json) — present.
- [krakken_subspace_byte_hull_validated.json](../results/krakken_subspace_byte_hull_validated.json) — present.

## SUBSPACE-002

[SUBSPACE-002](KRAKKEN_SECURITY_THEOREMS.md#subspace-002) — Proved: Theta-cancelling two-byte subspace trails end at Pressure1

- [krakken_subspace_theta_pair_cosets_audit_validated.json](../results/krakken_subspace_theta_pair_cosets_audit_validated.json) — present.
- [krakken_subspace_theta_pair_cosets_validated.json](../results/krakken_subspace_theta_pair_cosets_validated.json) — present.
- [krakken_subspace_theta_pair_noxrbd_audit_validated.json](../results/krakken_subspace_theta_pair_noxrbd_audit_validated.json) — present.
- [krakken_subspace_theta_pair_noxrbd_validated.json](../results/krakken_subspace_theta_pair_noxrbd_validated.json) — present.

## REBOUND-001

[REBOUND-001](KRAKKEN_SECURITY_THEOREMS.md#rebound-001) — Proved: serial-Chi rebound inbound count and one-byte XRBD outbound support

- [krakken.c](../source/krakken.c) — present.
- [krakken.h](../source/krakken.h) — present.
- [krakken_rebound_backward_audit_validated.json](../results/krakken_rebound_backward_audit_validated.json) — present.
- [krakken_rebound_backward_validated.json](../results/krakken_rebound_backward_validated.json) — present.
- [krakken_rebound_inbound_audit_validated.json](../results/krakken_rebound_inbound_audit_validated.json) — present.
- [krakken_rebound_inbound_validated.json](../results/krakken_rebound_inbound_validated.json) — present.

## REBOUND-002

[REBOUND-002](KRAKKEN_SECURITY_THEOREMS.md#rebound-002) — Proved: the one-cell Chi inbound class is unreachable from a first hash block

- [krakken_rebound_rate_gate_audit_validated.json](../results/krakken_rebound_rate_gate_audit_validated.json) — present.
- [krakken_rebound_rate_gate_validated.json](../results/krakken_rebound_rate_gate_validated.json) — present.

## DEPEND-001

[DEPEND-001](KRAKKEN_SECURITY_THEOREMS.md#depend-001) — Proved: full first-order message-bit dependency after rounds one and two

- [krakken_bit_dependency_all1272_audit_validated.json](../results/krakken_bit_dependency_all1272_audit_validated.json) — present.
- [krakken_bit_dependency_all1272_validated.json](../results/krakken_bit_dependency_all1272_validated.json) — present.

## DIFF-MULTI-001

[DIFF-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#diff-multi-001) — Corollary proved: conservative activity floors through eight rounds

- [krakken_multiround_activity.py](../scripts/krakken_multiround_activity.py) — present.
- [krakken_multiround_activity_validated.json](../results/krakken_multiround_activity_validated.json) — present.
- [krakken_multiround_activity_audit.py](../scripts/krakken_multiround_activity_audit.py) — present.
- [krakken_multiround_activity_audit_validated.json](../results/krakken_multiround_activity_audit_validated.json) — present.

## BOOM-MULTI-001

[BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001) — Theorem proved: coordinated multi-cell quartets cross complete round one

- [KRAKKEN_MULTICELL_BOOMERANG.md](KRAKKEN_MULTICELL_BOOMERANG.md) — present.
- [krakken_multicell_boomerang.py](../scripts/krakken_multicell_boomerang.py) — present.
- [krakken_multicell_boomerang_sample.json](../results/krakken_multicell_boomerang_sample.json) — present.
- [krakken_multicell_boomerang_audit.py](../scripts/krakken_multicell_boomerang_audit.py) — present.
- [krakken_multicell_boomerang_audit.json](../results/krakken_multicell_boomerang_audit.json) — present.
- [krakken_multicell_20260930/README.md](../results/krakken_multicell_20260930/README.md) — present.
- [krakken_multicell_20260930/patterns.json](../results/krakken_multicell_20260930/patterns.json) — present.
- [krakken_multicell_20260930/classification.json](../results/krakken_multicell_20260930/classification.json) — present.
- [krakken_multicell_20260930/classification_audit.json](../results/krakken_multicell_20260930/classification_audit.json) — present.
- [krakken_multicell_obstructions.py](../scripts/krakken_multicell_obstructions.py) — present.
- [krakken_multicell_rectangle_counts.c](../source/krakken_multicell_rectangle_counts.c) — present.
- [krakken_multicell_obstructions_audit.py](../scripts/krakken_multicell_obstructions_audit.py) — present.

## DIFF-TRUNC-001

[DIFF-TRUNC-001](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001) — Theorem proved: guaranteed zero-output projections for diagonal one-cell differences

- [krakken_truncated_zero_theorem.py](../scripts/krakken_truncated_zero_theorem.py) — exhaustive XRBD basis support and analytic Pressure low-prefix certificate.
- [krakken_truncated_zero_certificate.json](../results/krakken_truncated_zero_certificate.json) — all 128 per-site guaranteed bit/byte sets.
- [krakken_truncated_zero_audit.py](../scripts/krakken_truncated_zero_audit.py) — independent Python XRBD plus original-C tail and full-round replay.
- [krakken_truncated_zero_audit.json](../results/krakken_truncated_zero_audit.json) — completed implementation-audit counts.
- [KRAKKEN_TRUNCATED_DIFFERENTIAL.md](KRAKKEN_TRUNCATED_DIFFERENTIAL.md) — discovery observation and empirical two-round boundary; these sampled results are not the theorem proof.
- [krakken_theorem_registry_current.json](../results/krakken_theorem_registry_current.json) — append-only current working registry; archived original preserved.
- [verify_krakken_theorem_registry_current.py](../scripts/verify_krakken_theorem_registry_current.py) — working theorem navigation/body-hash check.

## PRESS-DIFF-003

[PRESS-DIFF-003](KRAKKEN_SECURITY_THEOREMS.md#press-diff-003) — 126 factored cubic gates and two LSB equations per chain; affine derivative inconsistency excludes the profile.

- [RESULTS6.md](../RESULTS6.md) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/fullword_affine_gate.py](../discovery6/fullword_affine_gate.py) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/fullword_affine_gate.json](../discovery6/fullword_affine_gate.json) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/affine_gate_cores.py](../discovery6/affine_gate_cores.py) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/affine_gate_cores.json](../discovery6/affine_gate_cores.json) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/factored_word_gate.py](../discovery6/factored_word_gate.py) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/factored_word_gate.json](../discovery6/factored_word_gate.json) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/manifest.json](../discovery6/manifest.json) — present; proof/certificate or replay as scoped in ledger.
- [scripts/krakken_results6_replay.py](../scripts/krakken_results6_replay.py) — present; proof/certificate or replay as scoped in ledger.
- [results/krakken_results6_promotion_replay.json](../results/krakken_results6_promotion_replay.json) — present; proof/certificate or replay as scoped in ledger.

## DIFF-SCREEN-001

[DIFF-SCREEN-001](KRAKKEN_SECURITY_THEOREMS.md#diff-screen-001) — Second-call-only supports of 5/8/13/16 cells project surjectively to 32q bits; arbitrary-cell supports 3/5/8/11.

- [RESULTS6.md](../RESULTS6.md) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/endpoint_projection.py](../discovery6/endpoint_projection.py) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/endpoint_projection.json](../discovery6/endpoint_projection.json) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/audit_projection.py](../discovery6/audit_projection.py) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/projection_audit.json](../discovery6/projection_audit.json) — present; proof/certificate or replay as scoped in ledger.
- [discovery6/manifest.json](../discovery6/manifest.json) — present; proof/certificate or replay as scoped in ledger.
- [scripts/krakken_results6_replay.py](../scripts/krakken_results6_replay.py) — present; proof/certificate or replay as scoped in ledger.
- [results/krakken_results6_promotion_replay.json](../results/krakken_results6_promotion_replay.json) — present; proof/certificate or replay as scoped in ledger.

## PRESS-TRANS-001

[PRESS-TRANS-001](KRAKKEN_SECURITY_THEOREMS.md#press-trans-001) — Complete Pressure translations, sharp neighboring activity, checkpoint probability and finite round-two affine/deterministic exclusions.

- [RESULT7.md](../RESULT7.md) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/translation_scan.py](../discovery7/translation_scan.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/translation_scan.json](../discovery7/translation_scan.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/activity_scan.py](../discovery7/activity_scan.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/activity_scan.json](../discovery7/activity_scan.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/audit_translations.py](../discovery7/audit_translations.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/translation_audit.json](../discovery7/translation_audit.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/affine_cosets.py](../discovery7/affine_cosets.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/affine_cosets.json](../discovery7/affine_cosets.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/two_round_activity.py](../discovery7/two_round_activity.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/two_round_activity.json](../discovery7/two_round_activity.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/activity_witness.py](../discovery7/activity_witness.py) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/activity_witness.json](../discovery7/activity_witness.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/pressure_tail.c](../discovery7/pressure_tail.c) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery7/manifest.json](../discovery7/manifest.json) — proof/certificate or implementation audit as scoped in the ledger.
- [discovery5/audit_kernel_cubes.py](../discovery5/audit_kernel_cubes.py) — proof/certificate or implementation audit as scoped in the ledger.
- [scripts/krakken_results7_replay.py](../scripts/krakken_results7_replay.py) — proof/certificate or implementation audit as scoped in the ledger.
- [results/krakken_results7_promotion_replay.json](../results/krakken_results7_promotion_replay.json) — proof/certificate or implementation audit as scoped in the ledger.

The original discovery7 manifest also hashes working-document snapshots at discovery time. Those historical hashes are preserved; later ledger edits may differ. The replay requires immutable source/report/script pins to match and records snapshot matches separately.

### PRESS-TRANS-001 companion scope analysis

- [RESULT8.md](../RESULT8.md) — exact reachability formulation and domain-transfer limitations; no reachability search.
- [krakken_results8_scope_check.py](../scripts/krakken_results8_scope_check.py) — read-only source/witness/spectrum checks; saves a separate report.
- [krakken_results8_scope_check.json](../results/krakken_results8_scope_check.json) — confirms the invalid saved embeddings and inherited 135→145 spectrum gap; no exclusion theorem.

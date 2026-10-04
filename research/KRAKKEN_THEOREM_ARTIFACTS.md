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

## DIFF-RATE-005

[DIFF-RATE-005](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-005) — global prescribed-difference concentration at Chi1/XRBD1.

- [THEOREMS.md](../review_extensions_20261003/THEOREMS.md) — local DDT lemma, four-cell factorization, conditioning and Pressure boundary.
- [LIN-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#lin-chi-002), [DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001) — inherited four-cell base independence and minimum support.
- [krakken_rank4_extension_audit.json](../results/krakken_rank4_extension_audit.json) — separate source S-box derivative and projection-row checks.

## DIFF-CHI-001

[DIFF-CHI-001](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-001) — affine active-first-call transition fibers and exact hash-base rank count.

- [THEOREMS.md](../review_extensions_20261003/THEOREMS.md) — analytic fiber argument and boundaries.
- [local_fibers.py](../review_extensions_20261003/local_fibers.py), [local_fibers.json](../review_extensions_20261003/local_fibers.json) — derivative-fiber exhaustion, 128 local direct transition checks, original-C representatives.
- [krakken_rank4_extension_audit.json](../results/krakken_rank4_extension_audit.json) — separately reproduced derivative histogram.

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

## ROT-001

[ROT-001](KRAKKEN_SECURITY_THEOREMS.md#rot-001) — Theorem proved: no exact lane-rotation covariance through eight rounds

- [krakken_rotational_affine_audit.json](../results/krakken_rotational_affine_audit.json) — present.
- [krakken_rotational_affine_audit.py](../scripts/krakken_rotational_affine_audit.py) — present.

## ROT-002

[ROT-002](KRAKKEN_SECURITY_THEOREMS.md#rot-002) — Exact one-round byte-rotation residual decomposition

- [krakken_rotational_decomposition.py](../scripts/krakken_rotational_decomposition.py) — present.
- [krakken_rotational_decomposition_validated.json](../results/krakken_rotational_decomposition_validated.json) — present.

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
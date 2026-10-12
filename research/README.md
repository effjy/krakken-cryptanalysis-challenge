# Krakken research records

This directory contains the current public Markdown research records for Krakken. **Every file presently tracked in `research/` is listed below**, including this README. For a guided research workflow, begin with the [research index](KRAKKEN_RESEARCH_INDEX.md); for exact theorem statements and quantifiers, use the [security theorem ledger](KRAKKEN_SECURITY_THEOREMS.md).

## Complete file index

The descriptions identify each file's role; they are **not additional security claims**. A paper trail may include analytic proofs, finite exhaustive certificates, solver-backed exclusions, implementation audits, provisional pilots, and empirical screens. See each record for its exact scope.

| File | Description | Kind |
|---|---|---|
| [`KRAKKEN_ATTACK_COVERAGE_PROGRAM.md`](KRAKKEN_ATTACK_COVERAGE_PROGRAM.md) | Research plan for attack-family coverage, exact stopping points, round margins, and evidence still required. | Research program |
| [`KRAKKEN_ATTACK_ROUND_MAP.md`](KRAKKEN_ATTACK_ROUND_MAP.md) | Attack-versus-round summary of demonstrated structures, quantified scopes, costs, and open continuations. | Round map |
| [`KRAKKEN_CLAIMS_FOR_REVIEW.md`](KRAKKEN_CLAIMS_FOR_REVIEW.md) | Concise, source-pinned theorem claims and carefully limited statements prepared for external cryptanalysis. | Review claims |
| [`KRAKKEN_COLLISION_EXPERIMENT.md`](KRAKKEN_COLLISION_EXPERIMENT.md) | Reproducible reduced-round truncated-collision birthday experiments, recorded pairs, and interpretation cautions. | Empirical experiment |
| [`KRAKKEN_CONDITIONED_PRESSURE_DIFFERENTIAL.md`](KRAKKEN_CONDITIONED_PRESSURE_DIFFERENTIAL.md) | Proof and finite-certificate details for DIFF-RATE-007: conditional one-round differential bounds through Pressure for three fixed differences. | Theorem detail |
| [`KRAKKEN_EFFECTIVE_CONE_PILOT.md`](KRAKKEN_EFFECTIVE_CONE_PILOT.md) | Solver-engineering study of effective-coordinate reductions and exact low-bit carry tables for remaining [1,2] activity sites; not a new theorem. | Engineering pilot |
| [`KRAKKEN_MULTICELL_BOOMERANG.md`](KRAKKEN_MULTICELL_BOOMERANG.md) | Coordinated multi-cell serial-Chi quartet constructions for unrestricted permutation states and their continuation tests. | Focused cryptanalysis |
| [`KRAKKEN_NEW_REVIEW_TRIAGE.md`](KRAKKEN_NEW_REVIEW_TRIAGE.md) | Disposition and audit notes for five candidates from an earlier reviewer note; preserve its historical snapshot context. | Review triage |
| [`KRAKKEN_PRESSURE_ALGEBRA_PILOT.md`](KRAKKEN_PRESSURE_ALGEBRA_PILOT.md) | Exact low-bit Pressure algebra, polynomial constraints, and a bounded [1,2] site-model pilot. | Algebra / pilot |
| [`KRAKKEN_PRESSURE_TRANSLATION_WINDOWS.md`](KRAKKEN_PRESSURE_TRANSLATION_WINDOWS.md) | Solver-free DIFF-WINDOW-001 proof excluding two consecutive nonzero deterministic Pressure translations. | Theorem detail |
| [`KRAKKEN_PROBE.md`](KRAKKEN_PROBE.md) | Detailed research notebook of experiments, witnesses, solver campaigns, negative searches, and certified findings; statuses are distinguished inside. | Research notebook |
| [`KRAKKEN_RESEARCH_INDEX.md`](KRAKKEN_RESEARCH_INDEX.md) | Starting point for continuing the cryptanalysis: document roles, research workflows, results, and update conventions. | Research navigation |
| [`KRAKKEN_REVIEW_FOLLOWUP_20260930.md`](KRAKKEN_REVIEW_FOLLOWUP_20260930.md) | Follow-up on the 2026-09-30 review, including audit corrections, source/API issues, and proposed research directions. | Review follow-up |
| [`KRAKKEN_SECURITY_THEOREMS.md`](KRAKKEN_SECURITY_THEOREMS.md) | Authoritative theorem ledger with exact statements, proof classes, quantified domains, validation boundaries, and limitations. | Theorem ledger |
| [`KRAKKEN_SOLVER_FREE_BASELINES.md`](KRAKKEN_SOLVER_FREE_BASELINES.md) | Solver-free diffusion and counting baselines: exact source MDS branch number (LIN-MDS-001), random-pair activity, and generic coding/Fourier identities with scope limits. | Theorem detail / reference baselines |
| [`KRAKKEN_THEOREM_ARTIFACTS.md`](KRAKKEN_THEOREM_ARTIFACTS.md) | Per-theorem guide to referenced scripts, datasets, certificates, and implementation audits; some artifacts are not mirrored. | Artifact manifest |
| [`KRAKKEN_THEOREM_INVENTORY.md`](KRAKKEN_THEOREM_INVENTORY.md) | Permanent append-only theorem IDs, proof classifications, scopes, and implementation-audit coverage. | Theorem inventory |
| [`KRAKKEN_TRUNCATED_DIFFERENTIAL.md`](KRAKKEN_TRUNCATED_DIFFERENTIAL.md) | Empirical one- and two-round truncated-differential screens on fixed differences, output bytes, and individual bits. | Empirical experiment |
| [`KRAKKEN_UNCONDITIONAL_ROUND1_DIFFERENTIAL.md`](KRAKKEN_UNCONDITIONAL_ROUND1_DIFFERENTIAL.md) | Proof and finite-certificate details for DIFF-RATE-008: unconditional complete-R1 differential bounds for three fixed message differences. | Theorem detail |
| [`README.md`](README.md) | This guide to all Markdown files currently tracked in the research/ directory and their roles. | Directory guide |

## Source pins, proof status, and reproducibility

The research records are tied to the source revisions and input domains specified in the documents and the repository root. **A complete-round result, a Chi/Pressure checkpoint result, and an empirical screen are not interchangeable.** The theorem ledger is authoritative for what is actually established; the attack-versus-round map and coverage program are summaries and research plans rather than blanket security or attack-cost guarantees.

The original working research tree includes additional `scripts/`, `results/`, solver outputs, JSON certificates, replay audits, and a frozen review bundle. **Some relative artifact links inside the public Markdown documents point to files not yet mirrored in this GitHub repository.** The artifact manifest is a navigation aid, not proof that every referenced certificate can be downloaded here. The activity/probe notebook **is** published here as [`KRAKKEN_PROBE.md`](KRAKKEN_PROBE.md), although some of its linked supporting materials remain outside this repository.

## External reproduction

Internal replays, alternative implementations, opposite-pivot rank checks, and reviewer comments do **not** establish independent external academic reproduction. Independent reproduction, counterexamples, and corrected proofs are welcome.

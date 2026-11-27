# Krakken research — sixteen ledgers

These sixteen files form the Krakken cryptanalysis research corpus. Research **07, 08 and 11** contain November 17–18, 2026 theorem updates; **Research 12** records XRBD, conditional round-two activity, Pressure compatibility, and the exact H159 first-round probability foundation (`Pr[A1=5]=2^-35`); **Research 13** documents exchange squares, Yoyo tests, rotational/DDT constructions, and a full-versus-surrogate rebound audit; and **Research 14** records scoped eight-round probability, finite-witness, decomposition-rank and adaptive parity-selection results through November 20, plus the reported November 22 full-digest collision-hunter checkpoint. **Research 15** records compact probability certificates, exact derivative and higher-order differential grids; **Research 16** extends those grids analytically and computationally and reports exact individual-round degree 1443, cumulative-round degree bounds and inverse-degree certificates. Earlier sections may preserve historical bounds superseded by these updates. The records are published for independent reproduction, scrutiny and challenge.

| Original ledger | Principal role |
| --- | --- |
| [KRAKKEN_RESEARCH_01.md](KRAKKEN_RESEARCH_01.md) | Security theorem program: formal attack families, scope, open proof obligations |
| [KRAKKEN_RESEARCH_02.md](KRAKKEN_RESEARCH_02.md) | Computational cryptanalysis working record and pressure/differential investigations |
| [KRAKKEN_RESEARCH_03.md](KRAKKEN_RESEARCH_03.md) | New theorem notes and independently scoped claims |
| [KRAKKEN_RESEARCH_04.md](KRAKKEN_RESEARCH_04.md) | Collision experiments, parameters and interpretation |
| [KRAKKEN_RESEARCH_05.md](KRAKKEN_RESEARCH_05.md) | Randomness assessment and limits of empirical certificates |
| [KRAKKEN_RESEARCH_06.md](KRAKKEN_RESEARCH_06.md) | NIST SP 800-22 statistical test certificate; November 27 provenance update: 125 MB tested prefix, exact parameters and local reproduction package; replay pending |
| [KRAKKEN_RESEARCH_07.md](KRAKKEN_RESEARCH_07.md) | Eight-round activity-bound corollaries and November 18 status addenda |
| [KRAKKEN_RESEARCH_08.md](KRAKKEN_RESEARCH_08.md) | Differential campaign, H159 family classification and updated bound status |
| [KRAKKEN_RESEARCH_09.md](KRAKKEN_RESEARCH_09.md) | Consolidation and provenance of earlier supporting research |
| [KRAKKEN_RESEARCH_10.md](KRAKKEN_RESEARCH_10.md) | Review, source-sensitive checks, output/correlation results |
| [KRAKKEN_RESEARCH_11.md](KRAKKEN_RESEARCH_11.md) | Attack theorem ledger, completed H159 [6,1] exclusion and all-family A1=5 continuation |
| [KRAKKEN_RESEARCH_12.md](KRAKKEN_RESEARCH_12.md) | XRBD exact structure, conditional `A2>=31` and 51-call activity floors, Pressure compatibility, and exact H159 `Pr[A1=5]=2^-35` first-round population |
| [KRAKKEN_RESEARCH_13.md](KRAKKEN_RESEARCH_13.md) | Exact one-round H159 exchange square; constructed-input two-round rotational/DDT test; Yoyo, rebound-model, integral, linear, and differential audit |
| [KRAKKEN_RESEARCH_14.md](KRAKKEN_RESEARCH_14.md) | Eight-round H159 probability and fixed-difference sampling bounds; finite-witness equations; digest separation-rank, prediction, quartet and adaptive parity-selection studies; reported fixed-counter collision-hunter checkpoint (November 19–22) |
| [KRAKKEN_RESEARCH_15.md](KRAKKEN_RESEARCH_15.md) | Compact four-wise independent sampling; scoped fixed-difference probability bounds; exact first- and second-order differential grids (November 25–26) |
| [KRAKKEN_RESEARCH_16.md](KRAKKEN_RESEARCH_16.md) | Differential packing and grid extensions; exact individual-round degree 1443; cumulative and inverse-round degree bounds (November 26) |

## Reading order

1. Start with [Known Results](../docs/KNOWN_RESULTS.md) for a brief current-status map.
2. Read the **current-status** updates in ledgers 07, 08, 10, 11, 12, 13, 14, 15 and 16 before relying on older work-in-progress summaries.
3. Inspect theorem hypotheses and explicit quantifiers in the original statement.
4. Check whether evidence is analytic, exhaustive, solver-backed, empirical or an independently replayed implementation audit.
5. Try to falsify it. Submit witnesses, corrected proofs or independent reproductions.

## Important caveats

Research 06's November 27 provenance update identifies the local `reproduce/nist_sts/` package and the 125,000,000-byte tested prefix of the original 10 GB source; the extracted-prefix replay is pending and the package is not yet publicly mirrored.

These research records retain historical section names, references, source paths and links to scripts, logs, JSONs and certificates from the researcher's private working tree. **Not all referenced supporting artifacts are present in this GitHub repository.** In particular, Research 12 refers to local `reproduce/xrbd_studies_20261118/` and `reproduce/probability_foundation_20261118/` evidence trees containing source archives, calculation scripts, and replay receipts; those files are **not yet mirrored here**. Research 13 similarly references a local `reproduce/exchange_bundle_v5_20261118/` evidence tree with the five supplied ZIPs, scripts, checks, and campaign records, also **not mirrored here**. Research 14 additionally refers to local `reproduce/related_digest_14/`, `reproduce/nibble_prediction_14/`, `reproduce/split_bounds_14/`, `reproduce/quartet_probability_14/` and `reproduce/affine_selection_14/` directories, which are also not supplied as public evidence here. Research 14 §14.12 additionally references a collision-hunter source path in the author's local Downloads directory; that absolute local path is **not a public GitHub reproduction link**, and the live SQLite database and executable were not reviewed here. Research 15 and 16 reference additional local reproduction directories and ZIP archives, including exact algebraic certificates. Those supporting archives have not been mirrored with these two ledgers. Relative links to those evidence trees may not resolve on GitHub. We have included the [21-family H159 witnesses](../evidence/family_witnesses.json), but the availability of a Markdown theorem statement alone does not imply that every supporting certificate is mirrored.

Statements from earlier dates can be superseded by later completed campaigns. The current high-level status is summarized in [Known Results](../docs/KNOWN_RESULTS.md) with explicit pointers.

These are author-produced research records and internal audits, **not a claim of independent peer review**.

For reproduction advice, see [Reproducibility](../docs/REPRODUCIBILITY.md).

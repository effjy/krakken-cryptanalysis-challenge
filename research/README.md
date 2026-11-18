# Krakken research — twelve ledgers

These twelve files form the Krakken cryptanalysis research corpus. Research **07, 08 and 11** contain November 17–18, 2026 theorem updates, and **Research 12** records XRBD, conditional round-two, Pressure compatibility, and the 21-family H159 first-round probability foundation (`Pr[A1=5]=2^-35`), as replayed within the research project. Earlier sections may preserve historical bounds superseded by these updates. The records are published for independent reproduction, scrutiny and challenge.

| Original ledger | Principal role |
| --- | --- |
| [KRAKKEN_RESEARCH_01.md](KRAKKEN_RESEARCH_01.md) | Security theorem program: formal attack families, scope, open proof obligations |
| [KRAKKEN_RESEARCH_02.md](KRAKKEN_RESEARCH_02.md) | Computational cryptanalysis working record and pressure/differential investigations |
| [KRAKKEN_RESEARCH_03.md](KRAKKEN_RESEARCH_03.md) | New theorem notes and independently scoped claims |
| [KRAKKEN_RESEARCH_04.md](KRAKKEN_RESEARCH_04.md) | Collision experiments, parameters and interpretation |
| [KRAKKEN_RESEARCH_05.md](KRAKKEN_RESEARCH_05.md) | Randomness assessment and limits of empirical certificates |
| [KRAKKEN_RESEARCH_06.md](KRAKKEN_RESEARCH_06.md) | NIST SP 800-22 statistical test certificate |
| [KRAKKEN_RESEARCH_07.md](KRAKKEN_RESEARCH_07.md) | Eight-round activity-bound corollaries and November 18 status addenda |
| [KRAKKEN_RESEARCH_08.md](KRAKKEN_RESEARCH_08.md) | Differential campaign, H159 family classification and updated bound status |
| [KRAKKEN_RESEARCH_09.md](KRAKKEN_RESEARCH_09.md) | Consolidation and provenance of earlier supporting research |
| [KRAKKEN_RESEARCH_10.md](KRAKKEN_RESEARCH_10.md) | Review, source-sensitive checks, output/correlation results |
| [KRAKKEN_RESEARCH_11.md](KRAKKEN_RESEARCH_11.md) | Attack theorem ledger, completed H159 [6,1] exclusion and all-family A1=5 continuation |
| [KRAKKEN_RESEARCH_12.md](KRAKKEN_RESEARCH_12.md) | XRBD exact structure, conditional `A2>=31` and 51-call activity floors, Pressure compatibility, and exact H159 `Pr[A1=5]=2^-35` first-round population |

## Reading order

1. Start with [Known Results](../docs/KNOWN_RESULTS.md) for a brief current-status map.
2. Read the **current-status** updates in ledgers 07, 08, 10, 11 and 12 before relying on older work-in-progress summaries.
3. Inspect theorem hypotheses and explicit quantifiers in the original statement.
4. Check whether evidence is analytic, exhaustive, solver-backed, empirical or an independently replayed implementation audit.
5. Try to falsify it. Submit witnesses, corrected proofs or independent reproductions.

## Important caveats

These research records retain historical section names, references, source paths and links to scripts, logs, JSONs and certificates from the researcher's private working tree. **Not all referenced supporting artifacts are present in this GitHub repository.** In particular, Research 12 refers to local `reproduce/xrbd_studies_20261118/` and `reproduce/probability_foundation_20261118/` evidence trees containing source archives, calculation scripts, and replay receipts; those files are **not yet mirrored here**, so those relative links may not resolve on GitHub. We have included the [21-family H159 witnesses](../evidence/family_witnesses.json), but the availability of a Markdown theorem statement alone does not imply that every supporting certificate is mirrored.

Statements from earlier dates can be superseded by later completed campaigns. The current high-level status is summarized in [Known Results](../docs/KNOWN_RESULTS.md) with explicit pointers.

These are author-produced research records and internal audits, **not a claim of independent peer review**.

For reproduction advice, see [Reproducibility](../docs/REPRODUCIBILITY.md).

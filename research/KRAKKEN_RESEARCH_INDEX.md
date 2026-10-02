# Krakken public research index

This is the public navigation page for the source-pinned Krakken cryptanalysis records.

## Start here

| Document | Purpose |
|---|---|
| [KRAKKEN_CLAIMS_FOR_REVIEW.md](KRAKKEN_CLAIMS_FOR_REVIEW.md) | Concise, narrowly scoped statements intended for outside cryptanalytic review |
| [KRAKKEN_SECURITY_THEOREMS.md](KRAKKEN_SECURITY_THEOREMS.md) | Formal theorem program, proofs, proof obligations, domains, and limitations |
| [KRAKKEN_THEOREM_INVENTORY.md](KRAKKEN_THEOREM_INVENTORY.md) | Permanent theorem IDs, proof classifications, and implementation-audit scopes |
| [KRAKKEN_THEOREM_ARTIFACTS.md](KRAKKEN_THEOREM_ARTIFACTS.md) | Index of scripts/certificates referenced by theorem ID; many referenced artifacts are not yet mirrored here |
| [KRAKKEN_MULTICELL_BOOMERANG.md](KRAKKEN_MULTICELL_BOOMERANG.md) | Coordinated multi-cell serial-Chi quartet construction and continuation work |

For a shorter attacker's overview, see [../docs/KNOWN_RESULTS.md](../docs/KNOWN_RESULTS.md) and [../docs/OPEN_PROBLEMS.md](../docs/OPEN_PROBLEMS.md).

## Publication boundary

The original working research tree is larger than this public challenge repository. It includes a long probe notebook, solver campaigns, scripts, JSON reports, certificates, replay audits, and frozen review bundles.

This directory publishes the theorem-facing records first. Relative links into `../scripts/`, `../results/`, or a review bundle may therefore be unresolved until those artifacts are deliberately mirrored.

The absence of an artifact from this repository is not evidence for or against the mathematical claim; it means only that the artifact has not yet been published here.

## Scope discipline

The research distinguishes:

- valid first-block hash inputs from unrestricted permutation inputs;
- complete rounds from internal checkpoints;
- analytic proofs from finite exhaustive and solver-backed proofs;
- empirical probes from theorem claims;
- implementation audits from independent external reproduction.

No theorem in these records should be read as a global security-bit estimate unless it explicitly states one.

## External review

Independent reproduction, counterexamples, stronger attacks, corrected proofs, and implementation findings are welcome through the repository issue templates.

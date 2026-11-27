# Public supporting evidence

The authoritative 16 research ledgers are in [research/](../research/README.md). Those ledgers cite additional private working-tree material not yet mirrored here.

The November 27 [Research 06 update](../research/KRAKKEN_RESEARCH_06.md) describes the locally prepared `reproduce/nist_sts/` package, including the 125,000,000-byte extracted dataset, historical NIST STS report and configuration, software archive and replay instructions. The operator's November 27 replay reproduced the original report byte for byte; the dataset and report SHA-256 fingerprints are recorded in Research 06, and replay metadata and report are archived locally in `reproduce/nist_sts/replay_20261127/`. These files are not yet mirrored here.

## Available artifact

- [family_witnesses.json](family_witnesses.json) — 21 H159 input-difference families attaining the minimum first-round serial-Chi call count `A1=5`, including archived 159-byte message pairs, recorded round activity and affine-base metadata. See [Research 08](../research/KRAKKEN_RESEARCH_08.md) and [Research 10](../research/KRAKKEN_RESEARCH_10.md).

Use [Reproducibility](../docs/REPRODUCIBILITY.md) for basic structural checks. Replaying the reference C permutation is required to independently verify activity claims.

**A witness is not a lower-bound certificate.** Missing auxiliary artifacts remain unavailable; do not infer they exist in this repository solely because the ledgers reference them.

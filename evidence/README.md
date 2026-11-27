# Public supporting evidence

The authoritative 16 research ledgers are in [research/](../research/README.md). The operator's preserved working-tree evidence is now distributed via the [Research 01–16 evidence release](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/tag/research-evidence-v1.0). Download the [archive](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst) and [checksum manifest](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst.sha256); see [verification and extraction instructions](../docs/REPRODUCIBILITY.md#download-the-research-evidence).

The November 27 [Research 06 update](../research/KRAKKEN_RESEARCH_06.md) describes the locally prepared `reproduce/nist_sts/` package, including the 125,000,000-byte extracted dataset, historical NIST STS report and configuration, software archive and replay instructions. The operator's November 27 replay reproduced the original report byte for byte; the dataset and report SHA-256 fingerprints are recorded in Research 06, and replay metadata and report are archived locally in `reproduce/nist_sts/replay_20261127/`. These files are included in the public release; the archived NIST package was verified locally before publication.

## Artifact directly available in Git

- [family_witnesses.json](family_witnesses.json) — 21 H159 input-difference families attaining the minimum first-round serial-Chi call count `A1=5`, including archived 159-byte message pairs, recorded round activity and affine-base metadata. See [Research 08](../research/KRAKKEN_RESEARCH_08.md) and [Research 10](../research/KRAKKEN_RESEARCH_10.md).

Use [Reproducibility](../docs/REPRODUCIBILITY.md) for basic structural checks. Replaying the reference C permutation is required to independently verify activity claims.

**A witness is not a lower-bound certificate.** The release is separate from Git-tracked files. Do not infer that every historical auxiliary artifact is included or independently verified solely because the ledgers reference it; inspect the archive inventory.

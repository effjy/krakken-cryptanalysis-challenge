# Reproduce and challenge Krakken results

This document distinguishes the Git checkout, the published research evidence release and historical artifacts whose inclusion or independent validation is not established.

## Download the research evidence

The [Research 01–16 evidence archive v1.0](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/tag/research-evidence-v1.0) was published November 27, 2026. The release contains the operator's preserved `reproduce/` tree, separate from the Git checkout.

- [Download Krakken_reproduce_complete.tar.zst](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst) — 1,712,820,163 bytes (approximately 1.60 GiB).
- [Download Krakken_reproduce_complete.tar.zst.sha256](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst.sha256) — 101 bytes.
- Uncompressed TAR size: 4,389,038,080 bytes.
- SHA-256 of the compressed archive: `721c4f1875b63d6d65616a3bd8379c8cbd475d0ea675bd5e14f1f7f31a01f6e1`. GitHub reports the same asset digest as the operator's locally verified archive.

On Linux, install `zstd` and ensure GNU tar and sha256sum are available. Download the assets into a working directory:

```sh
curl -fLO 'https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst'
curl -fLO 'https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst.sha256'
sha256sum -c Krakken_reproduce_complete.tar.zst.sha256
zstd -t Krakken_reproduce_complete.tar.zst
tar --zstd -tf Krakken_reproduce_complete.tar.zst > archive_inventory.txt
mkdir -p reproduce
tar --zstd -xf Krakken_reproduce_complete.tar.zst -C reproduce/
```

Use a fresh working directory and inspect the archive inventory before extraction or execution. Allow space for both compressed and extracted files. The archive contains the **contents** of the reproduction tree, not an outer `reproduce/` directory; extract into that directory to resolve historical paths. Never execute unfamiliar archived binaries or scripts without inspection; use a suitable isolated environment for replays.

The operator verified the archived NIST package, including the dataset and both reports, before publication. The following commands repeat that integrity check (see Research 06 for the pinned individual digests):

```sh
(cd reproduce/nist_sts && sha256sum -c SHA256SUMS && \
  (cd replay_20261127 && sha256sum -c SHA256SUMS) && \
  cmp finalAnalysisReport.txt replay_20261127/finalAnalysisReport.txt)
```

The release and server-reported asset digest have been checked; the entire archive has not been independently downloaded, inventoried or scientifically replayed here. The archive is a fixed publication baseline, not a guarantee that every historical file referenced by every ledger is included. Record the release tag, archive digest, relevant source pins and exact commands when reporting a reproduction.

## Build the reference target

```sh
git clone https://github.com/effjy/krakken-cryptanalysis-challenge.git
cd krakken-cryptanalysis-challenge
make test
make avx2-test   # x86 with AVX2 support only
```

The scalar `krakken.c`, `krakken.h`, and optimized `krakken_multi.c` were **not changed** in the November relaunch. The Makefile and existing `tests/kat.c`, `tests/compare_avx2.c` are retained. For AVX2-disabled hosts, `make test` remains the portable smoke test.

Verify the version:

```sh
sha256sum krakken.c krakken.h krakken_multi.c
```

Compare against [README](../README.md). The default challenge hash output is **32 bytes**; `docs/REFERENCE.md` describes the interface; `docs/TEST_VECTORS.md` lists expected output.

## The sixteen ledgers

[research/README.md](../research/README.md) links the 16 published research files. Research 07, 08, and 11 include dated updates; Research 12 documents the XRBD/Pressure/H159 probability research and internal replays; Research 13 documents five attack-research bundles, including H159 exchange squares, Yoyo experiments, a constructed-input two-round rotational/DDT test, and a rebound-surrogate audit; [Research 14](../research/KRAKKEN_RESEARCH_14.md) covers eight-round probability estimates, finite-witness equations, digest separation ranks, quartets, adaptive parity selection, and a November 22 full-digest collision-hunter checkpoint. [Research 15](../research/KRAKKEN_RESEARCH_15.md) covers compact probability sampling and exact differential grids; [Research 16](../research/KRAKKEN_RESEARCH_16.md) extends the differential certificates and records exact individual-round and bounded cumulative/inverse algebraic degrees. Historical links, script names and campaign notes remain in the ledgers. A later completed result may supersede an older open work-in-progress entry; prefer the newest quantified statement.

Research 12 references `reproduce/xrbd_studies_20261118/` (XRBD/Pressure archives, scripts, compiler logs, and replays) and `reproduce/probability_foundation_20261118/` (H159 21-family first-round probability/fiber verification). Research 13 references `reproduce/exchange_bundle_v5_20261118/`, a preservation/replay directory for five attack ZIPs, checksums, scripts, witnesses, and aggregate JSONL campaigns. Research 12's probability follow-up records `Pr[A1=5]=2^-35` for each fixed H159 difference under uniform 159-byte base messages, not a two- or eight-round endpoint-differential probability bound. Research 14 cites `reproduce/related_digest_14/`, `reproduce/nibble_prediction_14/`, `reproduce/split_bounds_14/`, `reproduce/quartet_probability_14/` and `reproduce/affine_selection_14/`. These directories were listed by the operator in the reproduction tree now distributed via the release. Historical links may still not resolve in the GitHub source browser; consult the extracted inventory. Research 14 §14.12 records **operator-reported** collision-hunter progress, not an independently reproduced audit. Its source paths point outside the reproduction tree to `/home/user/Downloads/khash_collision_hunter/`; inclusion of the live SQLite database, WAL and executable is not established and they have not been audited. The input sequence is consecutive counters, so independent-uniform-message statistical claims are inapplicable. Read the evidence class and reproduce claims independently where possible. A numerical theorem must not be interpreted more broadly than its quantified population.

**Research 15–16 reproduction boundary.** The published Markdown ledgers reference local `reproduce/research15/`, `reproduce/research15_fixed_diff/`, `reproduce/research15_subspace/`, `source_continuation/`, and multiple Research 16 degree-certificate ZIPs and scripts. The released reproduction tree includes the operator-listed `reproduce/research_15_16/` directory; consult the archive inventory for the actual paths of individual packages and historical aliases. Their complete contents have not been independently checked. The ledgers describe original-source checks and local independent implementations; the GitHub upload verifies document identity, not the underlying experiments. Use the pinned original source fingerprints, archived inputs and complete certificate verifiers from the companion packages for a full replay. Some Research 16 analyses have optional AVX-512 paths and documented portable alternatives. Read the specific scope and replay limitations of each certificate.

## H159 21-family witnesses

`evidence/family_witnesses.json` stores 21 difference families. Each entry includes `family_id`, `delta_hex`, two hex-encoded 159-byte messages, observed activity vector, and additional affine constraints.

A basic check of the archived pairs:

```python3 - <<'PY'
import json
from pathlib import Path
d=json.loads(Path('evidence/family_witnesses.json').read_text())
assert len(d['families']) == 21
ids = set()
for f in d['families']:
    i=f['family_id']
    assert i not in ids
    ids.add(i)
    m0, m1 = bytes.fromhex(f['msg0_hex']), bytes.fromhex(f['msg1_hex'])
    delta=bytes.fromhex(f['delta_hex'])
    assert len(m0) == len(m1) == len(delta) == 159
    assert bytes(x^y for x,y in zip(m0,m1)) == delta
    assert f['activity'][0] == 5
print('PASS: 21 archived H159 witness records, XORs, and A1 metadata')
PY
```

**This verifies file consistency, not the actual round activity.** The latter must be replayed with the original C permutation and suitable round-level instrumentation; a recorded array is evidence to test, not a proof.

## Collision and randomness experiments

The retained `experiments/collision/` subdirectory supports one reproducible subset of the collision work:

```sh
make collision-smoke
```

Read [Research 04](../research/KRAKKEN_RESEARCH_04.md) for exact experimental scope and [Research 05](../research/KRAKKEN_RESEARCH_05.md) / [06](../research/KRAKKEN_RESEARCH_06.md) for statistical test details. An STS pass is **not** a security proof.

**Research 06 provenance update (November 27, 2026).** The historical run `run_K1lVgTJu` used NIST STS 2.1.2 with 1,000 sequences of 1,000,000 bits, binary mode and all 15 test families. The run metadata records 125,000,000 bytes tested from a 10,000,000,000-byte source. The operator has prepared `reproduce/nist_sts/` containing `krakken_nist_tested_125MB.bin`, the historical configuration and report, wrapper, installation helper and STS archive. See Research 06 for the file inventory, checksum and replay commands. The operator completed the extracted-prefix replay (`run_t7rjuobx`) on November 27 with a byte-for-byte identical final report, confirmed by `cmp` and matching SHA-256 fingerprints. Research 06 records the extracted dataset SHA-256 and the archived replay directory `reproduce/nist_sts/replay_20261127/`. This is a same-dataset reproduction, not an independent statistical sample. The package is publicly available in the research evidence release, and its archived checksums and report comparison were verified locally before upload. Do not infer that a 10 GB download is required for the configured test, or that the later 250 MB dataset was its input.

## Submit evidence

Include the exact source pin, messages/states/masks, attack domain, full commands, software/solver versions, wall time, memory, RNG seeds and a minimal independent verifier. If a solver terminates with a relaxation-SAT assignment, label it **unvalidated**, and only call it a cipher trail after the original-C witness reproduces it.

See the [challenge rules](../CHALLENGE.md) and [issue templates](../.github/ISSUE_TEMPLATE/cryptanalysis-result.md).

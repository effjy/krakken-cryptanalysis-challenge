# Reproduce and challenge Krakken results

This document describes **what is available** in this public repository and distinguishes it from certificates that are referenced by research ledgers but not yet mirrored here.

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

## The twelve ledgers

[research/README.md](../research/README.md) links the 12 published research files. Research 07, 08, and 11 include dated updates, and the newly published Research 12 documents the XRBD/Pressure study and SOL's internal replay of five supplied verification/exploration programs. Historical links, script names and campaign notes remain in the ledgers. A later completed result may supersede an older open work-in-progress entry; prefer the newest quantified statement.

Research 12 references preserved local evidence trees `reproduce/xrbd_studies_20261118/` (XRBD/Pressure archives, scripts, compiler logs, and replays) and `reproduce/probability_foundation_20261118/` (H159 21-family first-round probability/fiber verification). **Neither evidence tree has been mirrored to the public repository**, so their relative links currently do not resolve. The research ledger itself is published. Its probability follow-up records `Pr[A1=5]=2^-35` for each fixed H159 difference under uniform 159-byte base messages, not a two- or eight-round endpoint-differential probability bound. The other ledgers likewise sometimes reference supporting scripts, large solver logs, JSON certificates and specialized executables **not all published in this repo**. Read the evidence class and reproduce claims independently where possible. A numerical theorem must not be interpreted more broadly than its quantified population.

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

## Submit evidence

Include the exact source pin, messages/states/masks, attack domain, full commands, software/solver versions, wall time, memory, RNG seeds and a minimal independent verifier. If a solver terminates with a relaxation-SAT assignment, label it **unvalidated**, and only call it a cipher trail after the original-C witness reproduces it.

See the [challenge rules](../CHALLENGE.md) and [issue templates](../.github/ISSUE_TEMPLATE/cryptanalysis-result.md).

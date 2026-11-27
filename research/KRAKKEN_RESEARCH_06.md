# Krakken — NIST SP 800-22 STS Test Certificate

**Record ID:** `KRAKKEN-NIST-STS-2026-11-12`  
**Recorded:** 2026-11-12  
**Status:** **PASS — 188 / 188 reported statistical evaluations**  
**Document type:** Research experiment certificate / results record (not an official NIST certification)

## Certified result statement

> **NIST SP 800-22 STS: 15 statistical test families, 188 individual evaluations, 1,000 input sequences (625 applicable to Random Excursions), α = 0.01. All 188 evaluations satisfied the reported pass-proportion and P-value-uniformity acceptance criteria. No statistical failures detected.**

## Source-file provenance

| Role | Filename | Provenance |
| --- | --- | --- |
| **Original source data** | **`krakken.bin`** | Original Krakken data file identified by the experiment owner. |
| File supplied to the test wrapper | `krakken_perm_10GB.bin` | Filename appearing in the recorded invocation of `run.sh`; described as a 10 GB file. |
| Internal NIST STS input alias | `krakken-input.bin` | Filename appearing in `finalAnalysisReport.txt` (`generator is <krakken-input.bin>`). The experiment owner states that this internally created file contains the same data as the original source file. |
| Primary evidence | `finalAnalysisReport.txt` | NIST STS result report supplied for this record. |

**Provenance qualification:** The relationships between the differently named data files are recorded from the experiment owner's account. The data files themselves were not supplied for a byte-for-byte comparison, and no source-data hash is asserted here. The presence of the internal filename in the report does **not** change the recorded original source: **`krakken.bin`**.

## Execution and evaluation

- **Suite:** NIST Statistical Test Suite (STS), SP 800-22.
- **Test families represented:** 15.
- **Individual reported evaluations:** 188.
- **Input sequences:** 1,000, of which 625 were eligible for the Random Excursions / Random Excursions Variant evaluations.
- **Reported input format:** binary.
- **Significance level:** α = 0.01.
- **Pass-proportion thresholds printed by STS:** approximately 980/1,000 for ordinary evaluations and 611/625 for Random Excursions evaluations.
- **P-value uniformity acceptance threshold used for this assessment:** 0.0001.
- **Results-directory path reported by the wrapper:** `/home/user/security/nist_sts/runs/run_K1lVgTJu`.
- **Suite completion marker:** `Statistical Testing Complete!!!!!!!!!!!!`.

### Evaluation inventory

| Statistical test family | Reported evaluations |
| --- | ---: |
| Frequency | 1 |
| Block Frequency | 1 |
| Cumulative Sums | 2 |
| Runs | 1 |
| Longest Run of Ones | 1 |
| Binary Matrix Rank | 1 |
| Discrete Fourier Transform (FFT) | 1 |
| Nonoverlapping Template Matching | 148 |
| Overlapping Template Matching | 1 |
| Maurer's Universal Statistical | 1 |
| Approximate Entropy | 1 |
| Random Excursions | 8 |
| Random Excursions Variant | 18 |
| Serial | 2 |
| Linear Complexity | 1 |
| **Total** | **188** |

### Observed margins

| Statistic | Observation | Acceptance criterion | Result |
| --- | --- | --- | --- |
| Lowest uniformity P-value | **0.001509**, Nonoverlapping Template | ≥ 0.0001 | PASS |
| Lowest pass count among 1,000-sequence evaluations | **982/1,000**, Runs | ≥ approximately 980/1,000 | PASS |
| Lowest pass count among 625-sequence evaluations | **613/625**, Random Excursions Variant | ≥ approximately 611/625 | PASS |
| All reported evaluations | **188/188** | Both criteria satisfied | **PASS** |

All 188 report rows were counted and checked against both acceptance criteria. None failed.

## Evidence integrity

**Primary report:** `finalAnalysisReport.txt`  
**SHA-256 of the supplied report:**

```text
220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739
```

This SHA-256 identifies the **report attachment only**, not `krakken.bin` or any staged input data file.

## Interpretation and limits

This experiment found **no statistical failures under the NIST STS checks reported here**. It provides empirical evidence that the tested bitstream is consistent with the evaluated statistical expectations at the selected significance level. It is not a proof of cryptographic pseudorandomness, permutation security, or resistance to differential, linear, integral, or other cryptanalytic attacks.

The 10 GB source-file size is reported by the experiment owner. The STS report does not itself specify the bit length of each of the 1,000 sequences; therefore the exact amount of data actually consumed by the suite is **not independently established** by this record.

**Record conclusion: PASS — 15 families; 188/188 reported evaluations met both criteria; zero detected statistical failures.**

## Provenance and reproduction update — 27 November 2026

**Status:** original 188/188 reported PASS unchanged; operator-supplied run records clarify the tested data length and input alias; extracted-prefix replay **completed with a byte-for-byte identical final report**, as demonstrated by the operator's supplied terminal transcript. This addendum supersedes the earlier uncertainty about configured sequence length and byte count.

### Original run and exact configured data extent

The experiment owner supplied the original `RUN_INFO.txt`, `answers.txt`, `console.log`, directory listing, and the current `run.sh` wrapper. The historical run was `runs/run_K1lVgTJu/`. Its run record states:

```text
Source: /home/user/security/nist_sts/krakken_perm_10GB.bin
Size bytes: 10000000000
Sequence bits: 1000000
Sequences: 1000
Bytes tested: 125000000
```

The directory listing shows that `krakken-input.bin` is a symbolic link to `/home/user/security/nist_sts/krakken_perm_10GB.bin`, not a separate generated copy. The earlier name `krakken.bin` remains historical owner-reported provenance; byte identity with that differently named file has not been established.

| Parameter | Value |
| --- | --- |
| Suite | NIST STS 2.1.2 (operator's software archive `sts-2_1_2.zip`) |
| Source size | 10,000,000,000 bytes (decimal 10 GB) |
| Sequence length | 1,000,000 bits |
| Number of sequences | 1,000 |
| Total configured input | 1,000,000,000 bits = 125,000,000 bytes (125 MB, approximately 119.21 MiB) |
| Fraction of original source | 1.25% |
| Input mode | Binary, user-prescribed file |
| Tests | All 15 families |
| Random Excursions eligible sequences | 625 (original report) |
| Original result | 188/188 reported evaluations passed |

The original interactive answers were `0`, `krakken-input.bin`, `1`, `0`, `1000`, `1` on successive lines. The console recorded these default test parameters: Block Frequency M=128, Nonoverlapping Template m=9, Overlapping Template m=9, Approximate Entropy m=10, Serial m=16 and Linear Complexity M=500. It ended with `Statistical Testing Complete!!!!!!!!!!!!`. The current wrapper invokes `./assess 1000000`, creates a separate run directory and uses a symlink to the supplied input. The historical records and current wrapper agree on the relevant configuration; the historical executable and binary-reader implementation have not been independently audited here.

### Preserved local reproduction package

The operator reports preparing the following directory in the master research archive: `reproduce/nist_sts/` (locally `~/security/reproduce/nist_sts/`). The paths below are relative to the research archive root containing `reproduce/`, not individual GitHub source-tree download links; see the public release below.

| File under `reproduce/nist_sts/` | Purpose |
| --- | --- |
| `krakken_nist_tested_125MB.bin` | First 125,000,000 bytes extracted from the original 10 GB source |
| `RUN_INFO.txt` | Historical run metadata |
| `answers.txt` | Historical interactive test selections |
| `console.log` | Historical completion record and parameters |
| `finalAnalysisReport.txt` | Historical full statistical report |
| `run.sh` | Test wrapper |
| `install.sh` | Suite installation/build helper |
| `README.md` | Original suite documentation |
| `sts-2_1_2.zip` | STS software distribution |
| `ARCHIVE_SHA256.txt` | Software archive checksum record |
| `SHA256SUMS` | Dataset and report checksums (reported values recorded below; verify the manifest locally before use) |

The prefix extraction was performed using the following prescribed command from the original `nist_sts/` directory:

```sh
head -c 125000000 krakken_perm_10GB.bin > ~/security/reproduce/nist_sts/krakken_nist_tested_125MB.bin
```

For the standard sequential binary reader, the configured test consumes precisely this prefix. The completed replay below reproduces the original final report exactly. This packaging avoids distributing the untested remainder of the 10 GB source. The separate `krakken_perm_250MB.bin` and `volume.krakken` are not the identified input of the historical run and are not required for this replay.

### Integrity checks and replay

From the original installation (where the existing suite is already built), the operator ran:

```sh
cd ~/security/nist_sts
./run.sh ~/security/reproduce/nist_sts/krakken_nist_tested_125MB.bin 1000 all
```

For a new installation, review the archived README and installation script, verify the suite archive checksum, and build/configure STS in a suitable local environment before invoking the wrapper with the extracted dataset. Do not reuse a stale absolute `suite.path` from another computer. Check the dataset's exact byte length and record its SHA-256:

```sh
cd ~/security/reproduce/nist_sts
stat -c %s krakken_nist_tested_125MB.bin
sha256sum krakken_nist_tested_125MB.bin finalAnalysisReport.txt
# If the saved manifest is present:
sha256sum -c SHA256SUMS
```

The historical report matches the SHA-256 already recorded in this ledger (`220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739`). To compare a newly generated report with the preserved original, use the new run directory printed by the wrapper:

```sh
cmp ~/security/reproduce/nist_sts/finalAnalysisReport.txt \
    /path/to/new/run/experiments/AlgorithmTesting/finalAnalysisReport.txt
```

If the reports differ, inspect the difference and compare all evaluation rows, eligibility counts, pass proportions and uniformity P-values before claiming reproduction. A matching report would reproduce the reported statistical outputs under this configuration, not prove cryptographic security or independently establish the original data generation process.

### Completed extracted-prefix replay — 27 November 2026

**Result: PASS — byte-identical reproduction of the historical final statistical report (operator-executed).**

The operator completed the replay in `runs/run_t7rjuobx/` using the archived 125,000,000-byte prefix, all 15 test families and 1,000 sequences of 1,000,000 bits. The supplied console transcript records the same default test parameters and the successful completion marker. The following comparison was executed on the operator's machine:

```sh
cd ~/security/nist_sts
cmp runs/run_K1lVgTJu/experiments/AlgorithmTesting/finalAnalysisReport.txt \
    runs/run_t7rjuobx/experiments/AlgorithmTesting/finalAnalysisReport.txt \
    && echo "SUCCESS: Reports are byte-for-byte identical!"
```

Observed output:

```text
SUCCESS: Reports are byte-for-byte identical!
```

The operator then supplied these SHA-256 results, with original and replay report paths distinguished:

```text
a8d0ca5e7fdb29b9bf0e0d58ef5a21ee6475084f984436af4d93ee1b7c43b3b1  krakken_nist_tested_125MB.bin
220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739  runs/run_K1lVgTJu/experiments/AlgorithmTesting/finalAnalysisReport.txt
220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739  runs/run_t7rjuobx/experiments/AlgorithmTesting/finalAnalysisReport.txt
```

Both reports match the original November 12 report fingerprint recorded above. Thus the reported 188/188 passing evaluations, their reported pass proportions, P-value uniformity results and Random Excursions eligibility counts were reproduced exactly at the report level. The repeat uses the same input data and is a reproducibility check, **not a new independent statistical sample**.

The operator also archived the replay metadata and report at:

```text
reproduce/nist_sts/replay_20261127/
    RUN_INFO.txt
    answers.txt
    console.log
    finalAnalysisReport.txt
    SHA256SUMS
```

The replay manifest was generated locally with `sha256sum RUN_INFO.txt answers.txt console.log finalAnalysisReport.txt > SHA256SUMS`. From the root of the extracted reproduction tree containing `nist_sts/`, verify the dataset and both reports with:

```sh
cd nist_sts
printf '%s  %s\n' \
  'a8d0ca5e7fdb29b9bf0e0d58ef5a21ee6475084f984436af4d93ee1b7c43b3b1' krakken_nist_tested_125MB.bin \
  '220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739' finalAnalysisReport.txt \
  '220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739' replay_20261127/finalAnalysisReport.txt | sha256sum -c -
(cd replay_20261127 && sha256sum -c SHA256SUMS)
cmp finalAnalysisReport.txt replay_20261127/finalAnalysisReport.txt
```

**Reproduction conclusion:** the extracted 125 MB package suffices to reproduce the historical final report in the tested environment; distribution of the remaining 98.75% of the 10 GB source is unnecessary for this configured experiment. The dataset fingerprint is now recorded. The full 10 GB file's fingerprint and the original data-generation provenance remain unverified here. This update is grounded in the supplied operator terminal transcript, not a separate third-party execution or direct inspection of the local dataset, manifest or executable. The actual NIST evidence package is now distributed in the [Research 01–16 evidence release](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/tag/research-evidence-v1.0), published November 27, 2026. The statistical result is not official NIST certification or proof of cryptographic security.

## Public archive publication — 27 November 2026

The operator verified the compressed archive with `zstd -t`, checked its SHA-256 manifest, extracted `./nist_sts/` into a temporary directory, verified the original and replay manifests and confirmed `cmp finalAnalysisReport.txt replay_20261127/finalAnalysisReport.txt` succeeded. The archive listing also included `nist_sts/ORIGINAL_SOURCE_SHA256.txt`; the full-source digest value has not been supplied to this ledger.

- [Public release v1.0](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/tag/research-evidence-v1.0)
- [Evidence archive](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst) (1,712,820,163 bytes)
- [SHA-256 manifest](https://github.com/effjy/krakken-cryptanalysis-challenge/releases/download/research-evidence-v1.0/Krakken_reproduce_complete.tar.zst.sha256)
- Archive SHA-256: `721c4f1875b63d6d65616a3bd8379c8cbd475d0ea675bd5e14f1f7f31a01f6e1` (matches the GitHub asset digest and operator's local checksum).

Extract into `reproduce/` as described in [Reproducibility](../docs/REPRODUCIBILITY.md#download-the-research-evidence). The NIST evidence and replay are under `reproduce/nist_sts/` and `reproduce/nist_sts/replay_20261127/` respectively. The archive publication and server-reported digest were verified via GitHub; the archived NIST verification was operator-executed, not an independent third-party replay.

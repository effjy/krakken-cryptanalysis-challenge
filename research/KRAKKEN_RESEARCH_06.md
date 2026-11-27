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

**Status:** original 188/188 reported PASS unchanged; operator-supplied run records clarify the tested data length and input alias; extracted-prefix replay in progress. This addendum supersedes the earlier uncertainty about configured sequence length and byte count, but does not establish a completed new replay.

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

The operator reports preparing the following directory in the master research archive: `reproduce/nist_sts/` (locally `~/security/reproduce/nist_sts/`). The paths below are relative to the research archive root containing `reproduce/`, not live GitHub download links.

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
| `SHA256SUMS` | Dataset and report checksums (values not yet supplied to this ledger; verify existence before use) |

The prefix extraction was performed using the following prescribed command from the original `nist_sts/` directory:

```sh
head -c 125000000 krakken_perm_10GB.bin > ~/security/reproduce/nist_sts/krakken_nist_tested_125MB.bin
```

For the standard sequential binary reader, the configured test consumes precisely this prefix. Confirmation against the original report is the purpose of the replay. This packaging avoids distributing the untested remainder of the 10 GB source. The separate `krakken_perm_250MB.bin` and `volume.krakken` are not the identified input of the historical run and are not required for this replay.

### Integrity checks and replay

From the original installation (where the existing suite is already built), the operator is running:

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

The historical report is expected to match the SHA-256 already recorded in this ledger (`220e598006b3cd8070e90f93c134a403f94d639cb86c190710ac11a9ddecf739`). Once the replay completes, compare the newly generated report with the preserved original, using the new run directory printed by the wrapper:

```sh
cmp ~/security/reproduce/nist_sts/finalAnalysisReport.txt \
    /path/to/new/run/experiments/AlgorithmTesting/finalAnalysisReport.txt
```

If the reports differ, inspect the difference and compare all evaluation rows, eligibility counts, pass proportions and uniformity P-values before claiming reproduction. A matching report would reproduce the reported statistical outputs under this configuration, not prove cryptographic security or independently establish the original data generation process.

**Pending verification:** The extracted dataset and report checksum values have not been supplied for this update, the local archive files have not been independently inspected, and the new replay has not yet completed. A SHA-256 of the full original 10 GB file may also be retained locally without publishing that file; no such value is asserted here. The public GitHub repository currently contains this ledger and reproduction directions, not the actual `reproduce/nist_sts/` package. The original November 12 result remains a reported historical result, not an official NIST certification.

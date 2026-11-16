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

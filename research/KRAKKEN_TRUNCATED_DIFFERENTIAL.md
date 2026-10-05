# Two-round truncated differential screen

**Status: empirical screen, not a theorem.** This begins the revised to-do's truncated-differential line. It uses complete original-C rounds with XRBD enabled and counts every possible one-byte output difference at every one of the 256 state-byte positions. It also checks every individual output-difference bit. Domain **H** means a uniformly sampled valid 159-byte first-block message base with fixed `0x86` padding and zero initial capacity. Domain **P** means a uniformly sampled unrestricted 2048-bit base state. Sampling is reproducible using SplitMix64; the reported probabilities are under an ideal independent-output reference, not cryptographic probability bounds.

Four nonzero input differences were fixed before sampling:

| Case | Domain | Fixed difference |
|---|---|---|
| `h_onebyte` | H | message byte 0 XOR `01` |
| `h_fourcell` | H | first of the six certified four-cell-support message difference lines |
| `h_fivecell` | H | message difference from the certified `A1=5` attaining pair |
| `p_onecell` | P | unrestricted one-cell serial-Chi difference from the existing differential-linear certificate |

For `h_fivecell`, **the difference** comes from an `A1=5` witness; a randomly sampled base message usually does not realize `A1=5`. No conditioning on that rare event was imposed.

The [20,000-base discovery report](../results/krakken_truncated_diff_20k_20261002/report.json) and a [fresh-seed 100,000-base validation report](../results/krakken_truncated_diff_100k_20261002/report.json) use identical fixed differences. Each stores source hashes, seeds, complete `2 × 256 × 256` byte histograms, and the top observed bins. The [bit analysis](../results/krakken_truncated_diff_100k_20261002/bit_analysis.json) covers all `4 × 2 × 2048` individual difference-bit tests. An [independent implementation audit](../results/krakken_truncated_diff_100k_20261002/audit.json) regenerated 128 bases per case in Python, evaluated one and two rounds via the public original-C permutation API, and reproduced every histogram bin from a separate 128-base worker run. The producer also self-tests its direct calls to the original-C round functions against that API.

## Findings

For three output projections selected from the discovery run, the independent 100,000-base run measured:

| Fixed input difference | Output projection | Round 1 | Round 2 | Ideal reference |
|---|---|---:|---:|---:|
| H four-cell line | byte 114, difference `0x70` | 700 | 381 | 391 per exact byte value |
| H five-cell witness difference | byte 7, difference `0x03` | 616 | 374 | 391 per exact byte value |
| P one-cell difference | byte 252, difference `0x00` | 100,000 | 394 | 391 per exact byte value |

The corresponding strongest single-bit derivative correlations were also reproducible: the H four-cell difference at output byte 114 bit 2 measured absolute correlation **0.2697** in discovery and **0.2728** in validation; the H five-cell difference at byte 117 bit 1 measured **0.1403** and **0.1330**. The P one-cell case's byte 252 remained zero in every sampled one-round pair. The latter observation has since been promoted to the exact, carefully scoped [DIFF-TRUNC-001 theorem](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001): for the chosen unrestricted cell, byte 252 and 14 other bytes have zero difference after one complete round for **every** base and every nonzero diagonal byte difference. The H biases remain empirical.

Across **all** 256 output-byte positions and 256 exact byte differences in each of the four 100,000-base round-two screens, the largest bin had 478 hits against expectation 390.625. Its one-screen Bonferroni-adjusted upper-tail value was about 0.66; allowing all four screens only weakens significance. Across the corresponding individual-bit screens, the largest absolute round-two correlation was **0.01252** (H four-cell, byte 75 bit 4); no round-two bit passed the familywise threshold covering all four cases, both rounds, and 2,048 bits per case. Thus this screen found no repeatable unusually large **one-byte-value or single-bit** round-two bias in these four fixed-difference classes. It does not rule out smaller biases, multi-byte projections, other input differences, or conditioned rare `A1=5` bases.

Reproduce with [the producer](../scripts/krakken_truncated_differential.py), [the bit analyzer](../scripts/krakken_truncated_diff_bit_analysis.py), and [the independent audit](../scripts/krakken_truncated_diff_audit.py). The C [worker](../scripts/krakken_truncated_diff_worker.c) invokes the current original-C layers. A modest new run is:

```bash
/home/user/venv/krakken/bin/python -u \
  /home/user/sol/scripts/krakken_truncated_differential.py \
  --samples 20000
```

The worker runs at lower CPU priority so it can coexist with the AB scan. No theorem ledger or frozen review bundle was changed.

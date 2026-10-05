# Truncated collision experiment

Run from the current pinned `krakken.c` and `krakken.h`:

```bash
/home/user/venv/krakken/bin/python -u \
  /home/user/sol/scripts/krakken_collision_experiment.py \
  --rounds 1,2,3,4,5,6,7,8 --bits 24,32 --trials 20 \
  2>&1 | tee /home/user/sol/logs/krakken_collision_run.log
```

For a short trial, use `--rounds 1,2,8 --bits 24 --trials 3`. A run creates a new directory under `results/`; `metadata.json` records the source SHA-256 hashes, parameters, seed, and summary. Each `round*_bits*.jsonl` row records the hash count and, for a collision, both complete 159-byte messages and both 256-bit digests. The C worker replays each truncated collision, and eight-round results are additionally checked through the original `krakken_hash_scalar()` interface. The wrapper tests that its reduced-round eight-round mapping matches that interface before any trials.

Each trial fixes 151 message bytes from a recorded pseudorandom background and enumerates an eight-byte little-endian counter, giving distinct valid 159-byte messages. The first `n` output bits are compared in byte order, least-significant-bit first within each byte. The reduced-round wrapper places `0x86` at rate byte 159, sets the capacity to zero, applies 1–8 complete original-C rounds, and reads the first 32 output bytes. This is the actual hash mapping at eight rounds for this message length, and a defined reduced-round analogue below eight rounds.

The ideal-random reference for the mean first-collision count is approximately `sqrt(pi/2) * 2^(n/2)`. The report counts trials that reach `--max-hashes` without a collision as **censored**; its observed mean includes only trials that found one. Do not compare that conditional mean to the ideal reference when censoring is substantial. Small widths and few trials cannot establish a full 256-bit collision claim. Widths near 48 bits may need substantial time and memory; the wrapper rejects tables over 512 MiB unless `--allow-large-memory` is explicit, and `--max-hashes` can bound a trial.

To repeat exactly, pass `--seed` with the recorded seed and the same flags. The script refuses to overwrite an existing output directory.

## 24-bit screen, 1,000 trials per round (2026-10-02)

The saved JSONL rows were recounted independently from the summary. Each of the eight configurations found a collision in all 1,000 trials; each saved pair contains distinct messages with equal first 24 digest bits. The runs used the same pinned C, header, and worker source hashes, recorded in their metadata. Rounds 1, 2, and 8 are in [run A](../results/krakken_collision_20261002T213742Z/metadata.json); rounds 4–7 are in [run B](../results/krakken_collision_20261002T215942Z/metadata.json); round 3 is in [run C](../results/krakken_collision_20261002T224044Z/metadata.json). These are three separately seeded campaigns.

| Rounds | Mean hashes to first collision | Ratio to ideal 24-bit reference |
|---:|---:|---:|
| 1 | 5,287.765 | 1.0300 |
| 2 | 5,215.695 | 1.0160 |
| 3 | 5,128.773 | 0.9991 |
| 4 | 5,145.413 | 1.0023 |
| 5 | 5,042.970 | 0.9824 |
| 6 | 5,189.225 | 1.0108 |
| 7 | 5,137.894 | 1.0008 |
| 8 | 5,099.426 | 0.9933 |

The ideal-random reference is about 5,134 hashes. The largest observed mean deviation is about 3.0% (round 1), within ordinary trial-to-trial variation for 1,000 first-collision counts. This is an **empirical screen of one 24-bit prefix projection and one message-generation family**, not a collision-resistance theorem or evidence that every projection behaves ideally. The actual eight-round full 256-bit collision question remains open to cryptanalysis.

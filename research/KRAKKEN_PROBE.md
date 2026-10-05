# Krakken activity probes

Research navigation: [index](KRAKKEN_RESEARCH_INDEX.md).

These probes answer different questions. They use the current `krakken.c` and
`krakken.h` in this directory.

For the full-domain linear theorem target, the certified exclusion of all
perfect input/output mask relations through rounds 1–8, and the precise
remaining obstacle to a quantitative linear-hull bound, see
[`KRAKKEN_SECURITY_THEOREMS.md`](KRAKKEN_SECURITY_THEOREMS.md).
The concise externally reviewable statements are in
[`KRAKKEN_CLAIMS_FOR_REVIEW.md`](KRAKKEN_CLAIMS_FOR_REVIEW.md).
The frozen pinned-source snapshot, certificates, and one-command verifier are in
[`krakken_review_bundle/README.md`](../krakken_review_bundle/README.md).

## Differential spread from valid hash inputs

`krakken_hash_input_probe.c` samples pairs of padded 159-byte messages that
differ in one message byte. Thus both initial capacity portions are zero and
the pairs are directly accessible through the hash API. It measures active
Chi S-box inputs in rounds one and two, plus the Hamming distance of the
two-round 256-bit digest. On and off runs use the same input pairs.

```bash
cc -O3 -pthread krakken_hash_input_probe.c -o krakken_hash_input_probe
./krakken_hash_input_probe 100000 on > hash_input_on.json
./krakken_hash_input_probe 100000 off > hash_input_off.json
# Optional fixed byte position and XOR difference, after a seed:
./krakken_hash_input_probe 100000 on 0x6b72616b6b656e31 72 8 > fixed72.json
```

In the included 10,000-pair pilot, first-round activity was the same in both
modes: minimum 62, median 100, mean 104.53. With XRBD on, second-round
minimum/median/mean were 250/255/255.01; without it, 249/255/254.99.
Two-round digest Hamming distance had median 128 of 256 bits in both modes.
The saved best-total-activity message pairs were replayed separately through
the original C layers. This sample says that a one-byte *message* difference
is already dense before XRBD. It does not cover multi-byte cancellations,
longer messages, or targeted differential trails.
For position 72 and difference 0x08, 100,000 random base messages found
minimum A1=59; the linear construction below reached A1=52.

`krakken_rate_a1_bound.py` adds an exhaustive first-round result for this
input-difference class. It checks all 160 positions in the first absorb block
and all 255 nonzero byte XOR differences. The linear prefix fixes the
difference entering Chi. The S-box DDT support then tells which second-branch
Chi inputs must also differ for **every** base message. The weakest summed
bound is **A1 >= 52** for any pair whose first absorbed blocks differ in
exactly one byte. The first-branch input difference alone forces at least 31
active calls. The script tests its bound against 100 concrete pairs and saves
the full distribution in `rate_a1_bound.json`.

`krakken_rate_a1_construct.py` proves this bound is **tight for valid 159-byte
messages**. For the weakest difference (byte 72 XOR 0x08), ten second-branch
S-box calls can potentially cancel. Their first-branch input values form an
80-bit linear image of the 159 message bytes; its rank is 80. The script
chooses ten DDT-compatible input values, solves the binary linear system,
and produces two real messages differing in one byte. Python S-box-input
counting and a separate C Chi-output count both give **A1=52**. Independent
original-C layer replay gives `[A1,A2]=[52,255]` with XRBD and `[52,256]`
without it. The concrete messages are in `rate_a1_constructed.json`.
The construction leaves a 1192-bit nullspace of other valid messages that
preserve A1=52. With `--samples 50000`, uniform nullspace sampling found
verified pairs with `[A1,A2]=[52,249]` for both XRBD modes; the best messages
are in `rate_a1_nullspace_50000.json`. These A2 values are observed upper
bounds within the constructed class, not two-round minima.

`krakken_rate_a1_exclusion.py` covers a broader input class. Any A1=1 Chi
transition would require a pre-Chi difference supported in one of 128
two-byte paired-lane patterns. For each pattern, the linear prefix map from
the 1280 rate input bits has full rank 1280 after those two output bytes are
removed. Thus **A1=1 is impossible for any nonzero rate-only input
difference** at an absorb step. This does not determine the minimum for
arbitrary multi-byte rate differences. The rank checks are saved in
`rate_a1_exclusion.json`.

```bash
~/venv/krakken/bin/python krakken_rate_a1_bound.py --output new_rate_bound.json
~/venv/krakken/bin/python krakken_rate_a1_construct.py --output new_constructed_pair.json
~/venv/krakken/bin/python krakken_rate_a1_construct.py --samples 50000 --output new_nullspace_search.json
~/venv/krakken/bin/python krakken_rate_a1_exclusion.py --output new_exclusion.json
```

## Theta-cancelling two-byte hash inputs

The one-byte minimum above does not extend to multi-byte differences.
`krakken_rate_two_byte_scan.py` exhaustively checks 61,200 structured
differences: two equal nonzero byte XOR differences in distinct rows of one
rate column, at the same byte offset. Their column parity cancels in Theta.
For each fixed difference, the script computes a base-independent lower bound
from the first-round Chi S-box DDT support. The smallest bound is **A1 >= 21**,
reached by eight input differences (byte positions 104+k and 120+k, with
k=0..7 and difference 0x08). The histogram is in `rate_two_byte_scan.json`.

`krakken_rate_two_byte_construct.py` makes that bound tight for actual padded
159-byte hash messages. At positions 111 and 127 with difference 0x08, the
first Chi branch has 14 active calls; seven second-branch calls are forced
active. A rank-56/56 linear solve sets all seven other possible second-branch
calls to zero. Python input counting and original C Chi-output counting both
verify **A1=21**. The same pair has A2=255 with XRBD and A2=254 without it;
these are counts for one pair, not two-round minima. The reproducible messages
and source hash are in `rate_two_byte_constructed.json`.

Thus **21 is the exact first-round minimum in this Theta-cancelling two-byte
class of valid 159-byte messages**. It is also a concrete upper bound on the
minimum over all valid message pairs; other multi-byte patterns may do better.
The cancellation is a useful structural finding, while the selected pair's
second round remains dense in both XRBD modes.

The seven possible cancellations each have two satisfying S-box inputs out
of 256. The 56-bit map from uniform message bytes to these seven inputs has
full rank, so the events are independent for this fixed input difference.
Consequently, for a uniformly random 159-byte base message,
**A1 = 28 - Binomial(7, 1/128)** exactly, and Pr[A1=21] = **2^-49**.
`krakken_rate_cancellation_probability.py` verifies the rank and DDT counts;
the derivation is saved in `rate_two_byte_probability.json`. The analogous
fixed one-byte difference at position 72 has
A1 = 62 - Binomial(10, 1/128), giving Pr[A1=52] = **2^-70**
(`rate_one_byte_probability.json`). These are random-base probabilities for
two particular fixed XOR differences, not probabilities of complete trails.
The linear construction deliberately chooses one of the rare bases.

As a check, `krakken_rate_two_byte_random.py` drew 20,000 uniform base
messages for positions 111 and 127, XOR 0x08. It observed A1 counts 28:18,968,
27:1,008, and 26:24; their predicted counts are approximately 18,932,
1,043, and 25. Its A2 minimum/median/mean was 248/255/255.00 with XRBD
and 249/255/255.00 without it (`rate_two_byte_random_20000.json`).
Separately, 20,000 samples from the subspace constructed to retain A1=21
found best A2=249 with XRBD and 250 without it
(`rate_two_byte_nullspace_20000.json`). These are observed upper bounds,
not proven second-round minima.

The original C-layer profile of the constructed A1=21 pair clarifies XRBD's
immediate effect. After round-one Chi, 21 of 256 state bytes differ. XRBD
raises this to 253; after ARX and shuffle, 255 bytes differ at the round-two
input. With XRBD omitted, ARX and shuffle bring it to only 78 bytes, but
round-two Theta raises it to 250. The Chi input counts then become 255/254
with XRBD on/off. These numbers describe one pair; they do not compare
minimum activity in the two permutations. Profiles for both the one- and
two-byte witnesses are in `rate_one_byte_layer_profile.json` and
`rate_two_byte_layer_profile.json`.

As a neighboring search, `krakken_rate_parity_scan.py` tried 156,000 sampled
three-byte XOR-zero differences and 39,000 sampled four-byte XOR-zero
differences at common offsets in one rate column. Their weakest local DDT
bounds were 37 and 58. It exhaustively checked 9,945 valid four-equal-byte
patterns, whose weakest bound was 49. The sampled figures are not lower
bounds on their entire families; all results are in `rate_parity_scan_1000.json`.

```bash
~/venv/krakken/bin/python krakken_rate_two_byte_scan.py --output new_two_byte_scan.json
~/venv/krakken/bin/python krakken_rate_two_byte_construct.py --output new_two_byte_pair.json
~/venv/krakken/bin/python krakken_rate_two_byte_construct.py --samples 20000 --output new_two_byte_subspace.json
~/venv/krakken/bin/python krakken_rate_cancellation_probability.py --witness rate_two_byte_constructed.json --output new_two_byte_probability.json
~/venv/krakken/bin/python krakken_rate_two_byte_random.py --samples 20000 --output new_two_byte_random.json
~/venv/krakken/bin/python krakken_layer_profile.py --witness rate_two_byte_constructed.json --output new_two_byte_profile.json
~/venv/krakken/bin/python krakken_rate_parity_scan.py --samples-per-pattern 1000 --output new_parity_scan.json
```

These conditions are much narrower than the full permutation problem. An
arbitrary one-byte difference *after Chi1* can have A1=1, but it need not be
realizable from a rate-only difference at the first hash absorb block.

## Integral screening at the real hash input

`krakken_integral_scan.py` varies one or two bytes of a padded 159-byte
message through all possible values. This keeps the hash's initial 96-byte
capacity portion fixed at zero, unlike the arbitrary post-Chi pair searches.
After each reduced round it XORs the first 32 state bytes across the cube.
An output bit whose XOR is zero across every tested random message base is an
**integral candidate**. Testing bases cannot prove the property for all bases.

```bash
# Eight one-byte cubes, 1 through 4 rounds, actual XRBD.
~/venv/krakken/bin/python krakken_integral_scan.py --position 0 --rounds 4 --bases 8 --xrbd on --output integral_on.json

# A larger two-byte cube: 65,536 evaluations per base per round.
~/venv/krakken/bin/python krakken_integral_scan.py --position 0 --second-position 1 --rounds 2 --bases 16 --xrbd on --output integral_two_bytes.json
```

The scanner checks its eight-round one-block implementation against
`krakken_hash_scalar` before starting. In 32-base one-byte screens at input
positions 0, 42, and 158, the common balanced-bit counts were:

| Input byte | XRBD on, round 1 | XRBD off, round 1 | Round 2, either variant |
|---:|---:|---:|---:|
| 0 | 0 | 98 | 0 |
| 42 | 0 | 56 | 0 |
| 158 | 1 | 104 | 0 |

The one surviving XRBD-on bit at position 158 remained balanced across 256
random bases. This is a **one-round candidate only**; it was not proven for
all bases and did not survive the two-round screen. The six 32-base reports
are saved as `integral_p{position}_{on|off}.json`. In a 16-base two-byte cube
at positions 0 and 1, four first-round output bits remained balanced with
XRBD on and 82 with it off. No bit remained balanced after two rounds in
either variant. These are still empirical candidates, and deeper cubes may
take substantially longer.

## Hash-interface audit and differential-bias screen

`krakken_hash_boundary_audit.py` reconstructs scalar sponge absorb, padding,
and squeeze separately from the hash API, using the original C permutation.
It matched `krakken_hash_scalar` on 25 message lengths spanning 0, 159, 160,
320, and other rate boundaries, each at six output lengths from 1 to 320
bytes: 150 comparisons. All 25 output-prefix checks passed. Independently,
Python's `hashlib.shake_128` generated the same 256 64-bit round constants
as Krakken's C Keccak-f/SHAKE code. These are implementation consistency
checks for the scalar code on this machine, not a security proof; the full
record is `hash_boundary_and_constants_audit.json`.

`krakken_differential_bias.c` tests a different observable from active S-box
counts. For 100,000 pseudorandom valid 159-byte base messages per fixed XOR
difference, it measures how often each of the 2,048 state bits flips after
one, two, and three reduced rounds, with XRBD on/off on the same message
pairs. The two differences were byte 72 XOR 0x08, and bytes 111 and 127 both
XOR 0x08. The latter is the Theta-cancelling class with attainable A1=21;
the random bases in this screen usually have A1=28. Before sampling, the C
driver checks its manual eight-round result against the full hash API.

Across both differences, both XRBD modes, and all three rounds, there are
24,576 bit tests. `krakken_bias_analyze.py` uses a two-sided Hoeffding union
bound with familywise alpha 0.01, giving a flip-fraction threshold of
**0.00878 away from 1/2** at this sample size. The observations were:

| Difference | XRBD | Round 1 flagged bits | Rounds 2 and 3 flagged bits | Largest observed bias in rounds 2–3 |
| --- | --- | ---: | ---: | ---: |
| Byte 72 | on | 0 | 0, 0 | 0.00617 |
| Byte 72 | off | 1,116 | 0, 0 | 0.00610 |
| Bytes 111,127 | on | 0 | 0, 0 | 0.00579 |
| Bytes 111,127 | off | 1,606 | 0, 0 | 0.00649 |

For XRBD-on, even round 1 had no flagged bits in the full state; its largest
observed bias across these two differences was 0.00662. XRBD-off round 1
retained many deterministic or strongly biased bits. By round 2, neither
variant had a flagged marginal bit at this resolution. The full-state
Hamming-distance mean was near 1024 of 2048 bits in the unflagged cases, and
the observed Hamming variance was 0.997–1.012 times the 512-bit independent
reference variance. `bias_analysis_full_variance_100000.json` summarizes
the runs; the raw per-bit counts are in the two
`bias_{one,two}_byte_full_variance_100000.json` files. An independent run
recording only the first 32 state bytes produced exactly matching per-bit
counts for those bytes.

This is a targeted **differential-bias screen**, not evidence that all input
differences or output statistics behave ideally. It tests two fixed input
differences and single-bit marginals/Hamming weights, not correlations,
high-order integrals, collision resistance, or the full eight-round digest.
The familywise threshold assumes independently sampled uniform bases;
pseudorandom sampling and finite sample size make the inference heuristic.
[NIST's statistical-testing guidance](https://csrc.nist.gov/pubs/sp/800/22/r1/upd1/final)
also emphasizes that statistical tests cannot replace cryptanalysis.

```bash
~/venv/krakken/bin/python krakken_hash_boundary_audit.py --output new_hash_audit.json
cc -O3 -pthread krakken_differential_bias.c -o krakken_differential_bias
./krakken_differential_bias 100000 0x6b72616b6b656e31 111 127 8 3 256 > new_two_byte_bias.json
./krakken_differential_bias 100000 0x6b72616b6b656e31 72 -1 8 3 256 > new_one_byte_bias.json
~/venv/krakken/bin/python krakken_bias_analyze.py new_two_byte_bias.json new_one_byte_bias.json --output new_bias_analysis.json
```

### Whole-byte and adjacent-byte correlation screen

`krakken_byte_pair_screen.c` extends the valid-message fixed-difference
screen beyond single-bit flip rates. It records the full 256-value XOR
difference histogram for each of the first 32 reduced-round state bytes
and equal-value collision counts for each of their 31 adjacent byte pairs.
The two differences are byte 72 XOR 0x08 and bytes 111/127 XOR 0x08;
XRBD on/off use the same bases. A byte Pearson chi-square statistic tests
departure from a uniform byte difference. A pair statistic compares the
observed joint collisions with their **exact conditional mean and variance
under shuffling one byte column**, calculated from the two observed byte
marginals. This distinguishes pair dependence from single-byte bias.

Across the original two 100,000-base runs (rounds 1–3), an independent
100,000-base two-byte run (rounds 1–3), and a 1,000,000-base two-byte run
(rounds 1–2), the combined screen covers 704 byte tests and 682 pair tests.
The analyzer uses Bonferroni-adjusted *asymptotic* cutoffs at nominal
familywise alpha 0.01: byte chi-square above 360.85 and pair absolute
shuffle `z` above 4.33. These are approximate statistical-screen
cutoffs, not exact finite-sample guarantees.

| Input difference / sample count | XRBD and round | Flagged bytes | Flagged adjacent pairs |
| --- | --- | ---: | ---: |
| One byte / 100k | off, round 1 | 25/32 | 13/31 |
| Two bytes / 100k | off, round 1 | 28/32 | 7/31 |
| Two bytes, independent seed / 100k | off, round 1 | 29/32 | 8/31 |
| Two bytes / 1m | off, round 1 | 32/32 | 11/31 |
| All XRBD-on panels, rounds 1–3 | on | 0 | 0 |
| All tested round-2 and round-3 panels | on or off | 0 | 0 |

In the 1,000,000-base two-byte run, round 2's largest byte chi-square
was 299.5 with XRBD on and 294.9 off; the largest absolute pair shuffle
`z` was 2.43. The first 100k two-difference runs reproduced **exactly**
the first 256 bit counts of the earlier independent bit-bias C driver.
An independent 1,000-sample replay using a Python SplitMix generator and
the original C layer calls matched all 378 recorded byte histograms and
pair-collision counts. The shuffle mean/variance formula also matched an
exhaustive six-sample permutation check.

The result is another independent negative screen after round 2, now for
within-byte and adjacent-byte structure in the first 32 state bytes. It
does not rule out smaller biases, distant-byte/high-order dependencies,
special message classes, rare trails, or attacks on the full hash.
The raw runs are `byte_pair_{one,two}_100000.json`,
`byte_pair_two_seed2_100000.json`, and `byte_pair_two_1000000.json`;
`byte_pair_all_analysis.json` contains the combined analysis and
`byte_pair_smoke_replay.json` the independent replay.

```bash
cc -O3 -pthread krakken_byte_pair_screen.c -o krakken_byte_pair_screen
./krakken_byte_pair_screen 1000000 0x6b72616b6b656e33 111 127 8 2 > new_byte_pair_screen.json
~/venv/krakken/bin/python krakken_byte_pair_analyze.py new_byte_pair_screen.json --output new_byte_pair_analysis.json
```

## Exact Pressure addition probabilities

`krakken_pressure_probability.py` moves from activity counts to differential
probability for the two modular additions in each 128-bit Pressure chain.
For `A = a + (c XOR (c >> 17))` and
`C = c + (A XOR (A << 31))` modulo `2^64`, let the prescribed XOR
differences be `(da,dc) -> (dA,dC)`. A four-carry-state bit DP exactly counts
the bases realizing each **individual** addition transition:

```text
P1 = xdp_add(da, dc XOR (dc >> 17) -> dA)
P2 = xdp_add(dc, dA XOR ((dA << 31) mod 2^64) -> dC)
```

The first transformed addend is a bijective linear function of uniform `c`;
the pair `(A,c)` is uniform when `(a,c)` is uniform. Thus `P1` and `P2` are
exact marginals for a uniform 128-bit chain base. The **complete chain**
success event is their intersection, so its probability is at most
`min(P1,P2)`. Multiplying them is generally invalid: a brute-forced six-bit
analogue in the script has exact joint probability 1/64, while the product of
its exact marginals is 1/128. The DP itself passed 72 exhaustive small-word
comparisons. This approach is consistent with the primary work on
[differential probabilities of modular addition](https://eprint.iacr.org/2001/001).

The script extracted and checked all 16 chains against the original C
Pressure function for two **valid 159-byte message pairs**: the constructed
A1=21 Theta-cancelling pair and the constructed A1=52 one-byte pair. Results
for their specified Pressure input/output differences are:

| Valid-message fixture | XRBD | Nontrivial Pressure chains | Product of rigorous per-chain bounds, under uniform full Pressure input |
| --- | --- | ---: | ---: |
| A1=21 two-byte pair | on | 16/16 | <= 2^-780 |
| A1=21 two-byte pair | off | 7/16 | <= 2^-163 |
| A1=52 one-byte pair | on | 16/16 | <= 2^-778 |
| A1=52 one-byte pair | off | 16/16 | <= 2^-483 |

For the A1=21 pair with XRBD on, each individual chain's upper-bound weight
is 41–54 bits; without XRBD, nine chains have unchanged input and output
differences and cost zero. Under a **uniform full-state Pressure input**, the
16 disjoint chains are independent, so multiplying their rigorous upper
bounds is valid for that *fully specified Pressure-layer transition*. The
four per-chain reports are `pressure_two_byte_on_validated.json`,
`pressure_two_byte_off_validated.json`, `pressure_one_byte_on_validated.json`,
and `pressure_one_byte_off_validated.json`.

These exponents are **not hash-input trail probabilities**. The two actual
messages merely furnish feasible intermediate transitions; their Pressure
base values are conditioned by the preceding hash layers and need not be
uniform independent chains. Exact joint counting for a full 128-bit Pressure
chain, then for the 16 chains under the reachable hash-message distribution,
remains open. Also, these bounds concern one fully prescribed output
difference, not the sum over all trails or collision/preimage resistance.

### Audited bound and exact joint low-bit counts

The bound combines the components without an independence assumption **inside**
a chain. Writing `E1` and `E2` for the two prescribed addition transitions,
`P(E1 and E2) <= min(P(E1),P(E2))`. For a uniformly random full 2048-bit
Pressure input, the 16 chains use disjoint input words, so their joint
transition probability is a product of the 16 chain probabilities. Replacing
each factor by its `min` upper bound gives the four exponents above. This
audit did not find a conditioning or multiplication error in that claim.

`krakken_pressure_prefix.py` now counts `E1 and E2` **jointly** for the low
`k <= 17` output bits of each chain, without multiplying their marginals.
For these bits, the low bits of `c` and `c XOR (c >> 17)` are independent
uniform words, while `A XOR (A << 31)` has the same low bits as `A`. A
16-carry-state DP can therefore count the joint event exactly using the
three independent low-bit words `(a, c XOR (c >> 17), c)`. Its 36 small-word
checks matched exhaustive enumeration. These are exact prefix results under
uniform Pressure input, and upper bounds on the full chain probability;
they do not replace an exact 64-bit joint count.

In the valid `A1=52`, XRBD-off witness, column 2's `(b,d)` chain has a
17-bit joint probability `2^-20`; the two marginal probabilities are
`2^-12` and `2^-11`. Their product, `2^-23`, is eight times **smaller**
than the true joint prefix probability. For the `A1=21`, XRBD-on witness,
column 1's `(a,c)` chain has a joint/product ratio of six. Across the 16
chains, observed exact 17-bit ratios range from 1–6 (`A1=21`, on), 1–2
(`A1=21`, off), 0.5–6 (`A1=52`, on), and 1–8 (`A1=52`, off). Thus the
within-chain dependence is measurable in both directions on actual
witness-derived transitions.

`krakken_pressure_conditional.py` independently samples uniformly among
first-addition solutions using backward carry-DP weights. For the first
`A1=21`, XRBD-on chain, 766/100,000 conditional samples matched the second
addition's low 8 prescribed bits, 19/100,000 matched 16 bits, and none
matched 24 bits. These are conditional empirical frequencies; the exact
prefix DP above conditions only on the corresponding *first-addition
prefix*, so the two experiments answer different questions. The sampler
has no timeout and accepts `--samples` and `--seed`. On the exhaustively
counted six-bit toy chain, it sampled 5,037/10,000 successes against the
exact conditional probability 1/2.

```bash
~/venv/krakken/bin/python krakken_pressure_prefix.py --report pressure_two_byte_on_validated.json --bits 17 --output new_pressure_prefix.json
~/venv/krakken/bin/python krakken_pressure_conditional.py --report pressure_two_byte_on_validated.json --chain 0 --samples 100000 --seed 1172 --prefix-bits 8 16 24 --output new_pressure_conditional.json
```

The saved exact-prefix reports are `pressure_prefix_two_byte_on.json`,
`pressure_prefix_two_byte_off.json`, `pressure_prefix_one_byte_on.json`, and
`pressure_prefix_one_byte_off.json`. The two sampling reports are
`pressure_conditional_two_byte_on_chain0.json` and
`pressure_conditional_two_byte_off_chain1.json`.

```bash
~/venv/krakken/bin/python krakken_pressure_probability.py --witness rate_two_byte_constructed.json --xrbd on --output new_pressure_two_byte_on.json
~/venv/krakken/bin/python krakken_pressure_probability.py --witness rate_two_byte_constructed.json --xrbd off --output new_pressure_two_byte_off.json
~/venv/krakken/bin/python krakken_pressure_probability.py --witness rate_a1_constructed.json --xrbd on --output new_pressure_one_byte_on.json
~/venv/krakken/bin/python krakken_pressure_probability.py --witness rate_a1_constructed.json --xrbd off --output new_pressure_one_byte_off.json
```

### Exact joint low-31-bit Pressure count and stronger bound

`krakken_pressure_prefix31.c` and its Python driver extend the exact joint
prefix count from 17 to **31 bits**. The DP scans bits from low to high,
retaining the last 17 `c` bits and the four carries of the two paired
additions. At each bit it assigns the new high `c` bit and the current `a`
bit, then requires both prescribed output-difference bits. For `k <= 31`,
the left shift by 31 contributes nothing to the counted output prefix.
The input count therefore uses exactly `17+2k` independent bits: the
initial 17 `c` bits and one new `c` and `a` bit per step. At `k=31`, the
denominator is `2^79`. This is an exact joint count for the first 31 bits
under a uniform Pressure-chain base; a full 64-bit transition must satisfy
it, so the prefix probability is a valid upper bound on that transition.

For every chain, `krakken_pressure_bound_combine.py` takes the smaller of
the original full-addition marginal bound and this exact joint-prefix bound.
The 16 chains remain disjoint under a uniform full Pressure input, yielding:

| Specified witness Pressure transition | Previous bound | Combined bound | Improvement |
| --- | ---: | ---: | ---: |
| `A1=21`, XRBD on | `2^-780` | **`3 × 2^-785`** (`≈2^-783.415`) | `32/3` |
| `A1=21`, XRBD off | `2^-163` | `2^-163` | 1 |
| `A1=52`, XRBD on | `2^-778` | `2^-778` | 1 |
| `A1=52`, XRBD off | `2^-483` | **`2^-484`** | 2 |

For the `A1=21`, XRBD-on case, the first two chain bounds improve by
factors `8/3` and `4`; their product gives the `32/3` improvement. These
figures are still **upper bounds for one specified Pressure-layer output
difference under uniform full-state input**, not hash-message differential
or differential-hull probabilities. An exact full-chain count could only
lower these probabilities further: in particular, the exact probability
exponent for the `A1=21`, XRBD-on specified transition must be **at least**
`785-log2(3) ≈ 783.415`, never smaller.

Validation: each of the 64 witness-chain 17-bit counts matched the earlier
independent Python DP; four six-bit toy cases with a two-bit right shift
matched exhaustive enumeration across the shift-window overlap; the zero
input/output difference at 31 bits counted all `2^79` bases. An earlier
fixed-17-bit-window implementation and the generalized implementation
agreed on all 64 low-31-bit witness counts. The validated exact-prefix
reports are `pressure_prefix31_{two_byte,one_byte}_{on,off}_validated.json`;
the combined exact-rational reports are
`pressure_combined_{two_byte,one_byte}_{on,off}.json`.

```bash
~/venv/krakken/bin/python krakken_pressure_prefix31.py --report pressure_two_byte_on_validated.json --bits 31 --output new_pressure_prefix31.json
~/venv/krakken/bin/python krakken_pressure_bound_combine.py --marginals pressure_two_byte_on_validated.json --prefix new_pressure_prefix31.json --output new_pressure_combined.json
```

### A broad Pressure output-weight hull

The preceding bounds prescribe *every* Pressure output difference bit. To
measure a much broader output family, `krakken_pressure_weight_hull.py`
counts all possible XOR differences of the **16 first-addition output
words** by total Hamming weight. These are the `a` and rotated `b` outputs,
1024 bits altogether; rotation preserves Hamming weight. A carry DP counts
each 64-bit word's entire output-weight distribution exactly for the fixed
input difference from a valid-message witness. Under a **uniform full
Pressure input**, the 16 disjoint word pairs are independent, so exact
integer convolution gives the complete 1024-bit weight distribution. It is
a truncated differential hull for **half** the Pressure output, not a full
Pressure or hash-level hull.

| Witness input difference | XRBD | Exact mean weight | Median | 1%–99% weight | Minimum possible |
| --- | --- | ---: | ---: | ---: | ---: |
| `A1=21` pair | on | 516.20 | 516 | 482–551 | 138 |
| `A1=21` pair | off | 91.40 | 91 | 76–110 | 46 |
| `A1=52` pair | on | 510.19 | 510 | 476–544 | 128 |
| `A1=52` pair | off | 246.82 | 247 | 221–275 | 114 |

For the `A1=21` XRBD-on difference, the exact probability that this output
half has weight at most 384 is about `2^-62.600`; with XRBD off, the
probability of weight **above** 384 is about `2^-304.872`. For the `A1=52`
XRBD-on difference, `P(weight <= 384) ≈ 2^-58.341`. These are probabilities
of large *families* of output differences; the particular XRBD-on
`A1=21` Pressure transition bounded by `3 × 2^-785` is one tiny member of
a much larger space. Thus its tiny component probability alone cannot
measure the probability of a useful differential hull. Nor does the
weight threshold by itself define an attack.

The weight DP matched exhaustive brute force in 60 small-word cases. For
the two-byte witness difference, 20,000 samples from the original C
Pressure layer gave mean weights 516.077 (XRBD on) and 91.389 (off),
against exact means 516.203 and 91.404; sampled and exact medians were
516 and 91. Reports are `pressure_weight_hull_{two_byte,one_byte}_{on,off}_validated.json`
and `pressure_weight_hull_pilot_two_byte_{on,off}.json`. Their fixed input
differences come from genuine hash-message pairs, but the probabilities
use **uniform Pressure bases**, not the conditioned hash-message base
distribution.

```bash
~/venv/krakken/bin/python krakken_pressure_weight_hull.py --report pressure_two_byte_on_validated.json --output new_pressure_weight_hull.json
~/venv/krakken/bin/python krakken_pressure_weight_hull_pilot.py --report pressure_two_byte_on_validated.json --exact new_pressure_weight_hull.json --samples 20000 --seed 4041 --output new_pressure_weight_pilot.json
```

To inspect **reachable hash-message bases** rather than a uniform Pressure
base, `krakken_rate_pressure_weight.py` sampled 10,000 messages uniformly
from one 1,216-dimensional affine coset constructed to retain `A1=21` for
the two-byte difference at positions 111 and 127. Every sampled valid
159-byte pair was checked to retain `A1=21`, then original C Chi, XRBD,
and Pressure functions supplied the weights. The two modes use the **same**
sampled message pairs:

| XRBD | Mean Pressure-input weight / 2048 | Mean first-output weight / 1024 | First-output 1%–99% | Mean full Pressure-output weight / 2048 |
| --- | ---: | ---: | ---: | ---: |
| on | 1002.44 | 511.56 | 474–549 | 1023.50 |
| off | 64.30 | 99.39 | 79–121 | 227.01 |

This is an empirical distribution over **one selected affine coset**, not
all bases that yield `A1=21`. The Pressure input difference itself varies
across the sampled messages, whereas the exact uniform-Pressure hull above
holds its input difference fixed to one witness value. Thus their similar
XRBD-on first-output means (511.56 and 516.20) should not be interpreted
as proof of a uniform conditioned Pressure base. The coset report is
`rate_pressure_weight_coset_10000_validated.json` (seed 9362); a different
seed or a different choice of optional-Chi targets may produce different
figures. The observed near-half-bit full output weight with XRBD on is a
diffusion screen, not a collision or pseudorandomness bound.

```bash
~/venv/krakken/bin/python krakken_rate_pressure_weight.py --samples 10000 --seed 9362 --output new_rate_pressure_weight.json
```

## Long-running full-width pair search

`krakken_search.py` is a Python driver with a compiled C inner loop. It samples
actual 2048-bit post-Chi1 state pairs with exactly one differing byte, measures
the second-round S-box input activity, and keeps the best pair. **There is no
trial or time limit by default.** It stops when you press Ctrl-C or when an
optional target is reached. It prints improvements and progress, and writes
atomic JSON checkpoints. On its first run it compiles
`krakken_search_kernel.c` into a cached shared library under `/tmp`.

```bash
# Run until Ctrl-C, with XRBD enabled.
~/venv/krakken/bin/python krakken_search.py --xrbd on --output search_on.json

# Same starting seed, XRBD disabled. Use a different checkpoint file.
~/venv/krakken/bin/python krakken_search.py --xrbd off --output search_off.json

# Stop once any pair with A2 <= 240 is found; Ctrl-C still works.
~/venv/krakken/bin/python krakken_search.py --xrbd on --target 240 --output target240.json

# Continue a previous run from exactly its saved random state.
~/venv/krakken/bin/python krakken_search.py --xrbd on --resume --output search_on.json
```

The default C batch is 100,000 pairs; Ctrl-C is handled after the current
batch. `--batch-size 10000` gives faster interruption response. Checkpoints
are written on every new best and every 30 seconds; the interval can be set
with `--checkpoint-seconds`. A forced kill can lose work since the last
checkpoint. `--max-trials` offers a bounded run for comparisons or testing,
but is absent by default. The JSON records trial count, histogram, best
post-Chi1 pair, random state, and source fingerprints. Replaying a checkpoint
verifies the best pair through the original C layers and independent Python
S-box counting. The same initial seed gives the same input pairs for separate
XRBD-on and XRBD-off runs.

Validation: 10,000-pair searches in both modes exactly matched the older
fixed-sample C probe's best pair and mean. Resuming an on-mode checkpoint from
10,000 to 20,000 pairs matched an uninterrupted 20,000-pair run. A SIGINT test
saved an `interrupted` checkpoint with a verified pair. As with any random
search, its best count is an upper bound on a minimum, not proof of one.

## Exact reduced pair search (SCIP)

`krakken_probe.py` keeps all 32 lanes, the actual 8-bit Abyssal S-box, bytewise
GF(256) MDS, layer order, and XRBD. It scales each 64-bit lane to 8 bits. For
rotations and shifts other than Chi, it uses
`max(1, min(7, floor((r*8+32)/64)))`; Chi rotates by 4. Round constants use
the low byte of each original 64-bit constant. Its output records all scaled
parameters and a hash of the original source. A source change requires
auditing the hardcoded layer constants before the script will run.

This **K8 is a different 256-bit permutation**, not a restriction of the
2048-bit original. Four-bit lanes would require replacing the actual 8-bit
S-box and GF(256) layer, so a four-bit minimum would be even less informative.

The model represents two concrete executions bit for bit. Binary XOR parity,
bitwise GF multiplication, modular-addition carries, and S-box truth tables
are enforced exactly. The S-box tables use continuous row weights: binary
inputs select their unique row, fixing the output. The post-Chi1 states are
free variables. Because the preceding layers and Chi are bijective, every
such pair corresponds to an external input pair, and their differing bytes
equal the number of active first-round S-box calls. The default minimizes
**A1+A2 over any distinct pair**. `--mode first1` fixes A1=1 and minimizes
the second-round count, a useful view of how far one active byte spreads.

```bash
# Proven one-round control; normally finishes immediately.
~/venv/krakken/bin/python krakken_probe.py --rounds 1 --output one_round.json

# Global two-round active-call minimum. Potentially very long; NO time limit.
~/venv/krakken/bin/python krakken_probe.py --rounds 2 --output two_round.json

# Fixed A1=1, minimizing A2.
~/venv/krakken/bin/python krakken_probe.py --rounds 2 --mode first1 --output first1.json
```

Choose a fresh output filename for each run. The script writes its best
concrete seed before optimization, then writes SCIP's status, numerical lower
bound, and independently replayed best pair when optimization returns.
SCIP's live console output shows progress during long runs. Ctrl-C is handled
when control returns to Python, retaining at least the seed report. A verified
pair is an **upper bound** on the minimum. Only an `optimal` result with a
matching lower bound closes this model's gap; `searching`, interruption, and
other incomplete statuses do not.

The first-round minimum is one for distinct pairs. This was also solved by
SCIP on K8. A separate rank check found full rank for K8 Theta (256 over
GF(2)) and MDS (8 over GF(256)); Chi is explicitly invertible because each
half uses a bijective S-box in sequence. The two-round exact model has about
17,000 variables. A 20-second local smoke run built and validated its seed,
but did not finish optimization. This is expected to be a difficult model.

## Actual 2048-bit permutation sampling

The C probe uses the original 64-bit implementation and starts with one
differing byte immediately after first-round Chi. It runs the rest of round
one and the prefix of round two, then counts the actual second-round S-box
input differences. The `off` option omits only XRBD for a controlled variant.
Both runs use the same deterministic sampled input pairs.

```bash
cc -O3 -pthread krakken_full_probe.c -o krakken_full_probe
./krakken_full_probe 100000 on > full_on.json
./krakken_full_probe 100000 off > full_off.json
```

The included `full_on_10000.json` and `full_off_10000.json` use the same 10,000
sampled pairs. XRBD-on had minimum/median/mean second-round activity
249/255/254.9698 of 256 calls. With XRBD removed, the corresponding figures
were 70/220/209.5155. The saved best pairs were independently replayed with
the original C layer functions. These are empirical observations on the full
permutation and its modified variant. They do not prove a minimum or quantify
a distinguisher's probability. Larger samples can improve the observed upper
bound but cannot prove it optimal.

## XRBD's structured differential behavior

`krakken_xrbd_single_byte.py` exhaustively applies the original C XRBD layer
to all 256 post-Chi byte positions and 255 nonzero byte differences: 65,280
cases. Every such difference reaches **all 32 lanes**; the number of active
output bytes ranges from **32 to 196**. XRBD is XOR-linear, verified against
100 random state pairs. Its pairwise butterfly update is
`(a,b) -> (a XOR b, b XOR rot(a XOR b))`. Thus equal differences in a paired
set of lanes can cancel the first output. The exhaustive results are in
`xrbd_single_byte_lanes.json`.

This complete support observation has now been independently replayed
and promoted to a [cross-layer theorem](KRAKKEN_SECURITY_THEOREMS.md):
for `A1=1` in the unrestricted permutation, XRBD activates all 32
lanes and hence all 16 independent Pressure chains. The
[source-pinned certificate](../results/krakken_xrbd_onebyte_pressure_chains.json)
checks all 65,280 one-byte differences against both original C and a
separate Python butterfly implementation, and checks Pressure's
algebraic inverse against 1,600 original-C chain executions. This
quantifies unavoidable component participation; it does not assign
security bits or exclude a sparse Chi2 trail by itself.

`krakken_xrbd_faces.py` exhaustively checks 15,552 equal-single-bit
differences placed on affine faces of the five-bit lane-index cube, over all
64 bit positions. Within this **structured family**, input versus XRBD
output active-byte counts are:

| Input active bytes | Output active bytes across tested faces |
| ---: | ---: |
| 1 | 32–145 |
| 2 | 16–66 |
| 4 | 8–27 |
| 8 | 4–9 |
| 16 | 2–3 |
| 32 | 1 |

The minimum input-plus-output count within this family is 12, attained by
4-to-8 and 8-to-4 patterns. This is **not** a proven global byte branch
number. For example, matching bit differences in all 32 lanes collapse to
one byte in lane 31. The full enumeration is in `xrbd_faces.json`.
`krakken_xrbd_inverse_scan.py` independently implements and checks XRBD's
inverse, then scans all 65,280 one-byte *output* differences. Their inverse
inputs occupy 32–200 bytes; an output byte in lane 31 can have a 32-byte
preimage (`xrbd_inverse_single_byte.json`).

Controlled second-round tests use the same random post-Chi1 base states with
XRBD on and off. For the one-byte difference that expands to XRBD's minimum
32 bytes, 5,000 pairs had median A2 **255 on / 140 off**. For the difference
that expands to 196 bytes, medians were **255 on / 224 off**
(`xrbd_bridge_min_5000.json`, `xrbd_bridge_max_5000.json`). These are
location-specific samples, not lower bounds.

The canonical butterfly-face tests make the opposite effect visible. With
32 matching active bytes after Chi1 and just one after XRBD, 5,000 random
bases at bit position 0 gave median A2 **186 on / 254 off**
(`xrbd_face_d5_5000.json`). Scanning all 64 bit positions with 500 bases
each, then 30,000 bases at each of four promising positions, produced a
verified XRBD-on pair with **[A1,A2]=[32,121]**, or **153 active calls over
two rounds** (`xrbd_face_d5_bit15_30000.json`). The best post-Chi1 state is
saved there and replayed through the original C layers, with a separate
Python/C check of second-round Chi activity. The other canonical face results
for 2, 4, 8, and 16 active input bytes are saved in
`xrbd_face_d1_5000.json` through `xrbd_face_d4_5000.json`.

These pairs are valid for the unrestricted permutation-input model: first
Chi is bijective, and each differing post-Chi output byte corresponds to one
active S-box call. They are **not** shown reachable from a padded hash message
with zero capacity. The 153 total is an observed **upper bound** for a
two-round active-call minimum, not an optimal value, differential-trail
probability, or attack on eight rounds. XRBD strongly spreads isolated bytes
but can concentrate correlated differences; analysis must account for both.

### Can the hash input reach the collapsing face?

`krakken_rate_xrbd_face_reachability.py` answers this for the matching-bit
faces above at the **first absorb block**. More generally, suppose every
post-Chi1 difference is confined to a single common byte offset `k` across
the 32 lanes, with arbitrary values and any subset of lanes active. Inverting
the two serial Chi S-boxes shows that the pre-Chi difference can occupy only
byte offsets `k` and `k+4 (mod 8)` in each lane. This necessary support rule
was checked on 160 random post-Chi state pairs and replayed through original
C Chi.

For each of the eight choices of `k`, the script removes those 64 allowed
pre-Chi bytes and computes the GF(2) rank of the map from all 1280 rate-input
bits to the other 192 pre-Chi bytes. **Every restricted map has full column
rank 1280/1280.** Its kernel is zero, so **no nonzero rate-only first-absorb
difference can produce any post-Chi1 difference confined to one common byte
offset.** The exact `32 -> 1` matching-bit face, and every other face in the
same-byte family above, are therefore unreachable from the first padded hash
block with zero capacity difference. The source hash, eight ranks, and
inverse-Chi check are in `rate_xrbd_face_reachability_checked.json`.

> **First-absorb same-byte-offset exclusion (proved for this C source):**
> For two first-block states with equal initial capacity and a nonzero
> rate-only XOR difference, the post-Chi1 XOR difference cannot have all its
> nonzero bytes at one common byte offset across the lanes.

This is a support exclusion, not a general proof that XRBD cannot collapse a
hash-input difference. Patterns spanning multiple byte offsets, later absorb
steps, and arbitrary permutation inputs remain outside the claim. The valid
two-byte hash-message witness with A1=21 shows that other structured
first-round differences certainly are reachable.

`krakken_rate_xrbd_one_output_byte.py` extends this necessary-support method
to **every one-byte XRBD output difference**: 256 positions times 255 nonzero
values. It inverts XRBD, determines the exact post-Chi difference, derives a
value-independent pre-Chi support superset through inverse Chi, and ranks the
rate-to-pre-Chi map outside that support. The post-Chi active-byte count is
the first-round active S-box count because Chi's two serial S-box outputs are
bijective. The 160 sampled inverse-Chi support checks replayed through C;
independent high- and low-pivot rank methods agreed for all 44 distinct masks
that could possibly have full rank.

Of the 65,280 XRBD one-byte output differences, 2,040 have A1=32. **All
2,040 are excluded** for a nonzero first-block rate-only difference, and no
one-byte XRBD-output pattern has A1 between 33 and 47. The support test
initially gave the conditional bound A1>=48. At A1=48, however, 2,904
patterns survived that **necessary support screen**. For example, XRBD output
position 120 with XOR difference 0x01 has A1=48 and an allowed pre-Chi
support of 96 bytes; its restricted map has rank 1248/1280, leaving 32
linear degrees of freedom. The support-screen counts are in
`rate_xrbd_one_output_byte_final.json`.

`krakken_rate_xrbd_candidate_linear.py` adds exact conditions from the
**inactive Chi S-box calls**. An unchanged first-branch output byte requires
its pre-S-box input XOR difference to be zero. An unchanged second-branch
output byte similarly fixes a linear expression in the pre-Chi difference
and the specified first-branch output difference. These are value-independent
affine equations in the 1280 rate-difference bits. A random-target check of
100 pairs matched direct inverse Chi; an independent low-pivot augmented-rank
calculation confirmed that the A1=48 example above is inconsistent despite
its earlier support-rank survivor status
(`rate_xrbd_candidate_120_01_linear.json`).

`krakken_rate_xrbd_inactive_scan.py` applies these exact inactive-call
equations exhaustively at the low-activity levels:

| A1 | One-byte XRBD-output differences | Inconsistent with rate-only input |
| ---: | ---: | ---: |
| 32 | 2,040 | 2,040 (prior support-rank exclusion) |
| 48 | 2,960 | 2,960 |
| 56 | 520 | 520 |
| 64 | 352 | 352 |
| 72 | 2,024 | 2,024 |
| 76 | 56 | 56 |

There are no other A1 values below 80 for an XRBD output difference in one
byte. Thus the stronger result is:

> **Conditional first-block diffusion lower bound (proved for this C
> source):** if a nonzero rate-only first-absorb difference produces exactly
> one active byte after XRBD, then **A1 >= 80**.

This does **not** show that A1=80 is attainable, or that a one-byte XRBD
output is reachable at all. The next case requires further work, including
the active S-box DDT constraints. The exhaustive records are in
`rate_xrbd_inactive_a1_48.json`, `rate_xrbd_inactive_a1_56.json`,
`rate_xrbd_inactive_a1_64.json`, `rate_xrbd_inactive_a1_72.json`, and
`rate_xrbd_inactive_a1_76.json`.

```bash
~/venv/krakken/bin/python krakken_xrbd_single_byte.py --output new_xrbd_single_byte.json
~/venv/krakken/bin/python krakken_xrbd_faces.py --output new_xrbd_faces.json
~/venv/krakken/bin/python krakken_xrbd_inverse_scan.py --output new_xrbd_inverse.json
~/venv/krakken/bin/python krakken_xrbd_bridge_profile.py --position 0 --difference 1 --samples 5000 --output new_bridge_min.json
~/venv/krakken/bin/python krakken_xrbd_face_probe.py --dimension 5 --bit-position 15 --samples 30000 --output new_face_d5.json
~/venv/krakken/bin/python krakken_rate_xrbd_face_reachability.py --output new_face_reachability.json
~/venv/krakken/bin/python krakken_rate_xrbd_one_output_byte.py --mode all --output new_one_byte_output_screen.json
~/venv/krakken/bin/python krakken_rate_xrbd_candidate_linear.py --output new_candidate_linear.json
~/venv/krakken/bin/python krakken_rate_xrbd_inactive_scan.py --min-a1 48 --max-a1 76 --output new_inactive_screen.json
```

## Algebraic degree and XRBD-face subspace checks

An external research summary formerly at `/home/user/Downloads/SUMMARY.md`
(not retained in this working tree) pointed to two later
probes in `~/krakken`: `krakken_degree.py` and
`krakken_invariant_subspace.py`. Their source locks match this directory's
`krakken.c` and `krakken.h` byte for byte (SHA-256 prefixes `4d659644…`
and `83f891b6…`). We reran the degree analyzer against this directory and
independently replayed every recorded subspace rejection through the
current C permutation.

The S-box's eight output-coordinate ANFs each have exact degree **7**.
The symbolic full-round analyzer propagates **upper bounds**: after one
round its coordinate bounds range from 49 to 2047, with median 2047; after
two rounds all reach the 2047 permutation-coordinate ceiling. This fast
bound saturation is *not* a measurement of the actual degree. A separate
16-variable cube derivative on the real C function was nonzero for **all
10 of 10 tested cubes** at both one and two rounds, proving the vectorial
degree of each reduced-round permutation is **at least 16**. The fresh source-locked reports are
`degree_symbolic_audit.json` and `degree_cube16_10_audit.json`.

The invariant-subspace family has 243 affine faces of the five-bit lane
index cube, each paired with eight byte offsets: **1,944 candidates**.
For one candidate, `V` contains all states formed by placing the same
8-bit value at that offset in every lane of the face, zero elsewhere.
Each `V` has dimension eight. The source report exhaustively checks all
256 members of each `V` for both setwise invariance `F^r(V)=V` and
zero-base difference closure `F^r(v) XOR F^r(0) in V`. It records zero
survivors for every reduced-round count **1 through 8**.

`krakken_invariant_witness_audit.py` independently replayed **all 15,552
candidates per property** from the source report through the current C
implementation, verified each reported output, and used a direct
equal-byte-face membership check. Every candidate has a concrete
counterexample to both properties. The full 32-lane equal-byte face is
included for all eight rounds. The 64-dimensional equal-word 32-lane
face was sampled for rounds 1–4; a replayed counterexample in each round
also rules out closure of that specific candidate.

An additional independent scan, `krakken_xrbd_face_generator_scan.py`,
tested one common-bit generator from each of the 1,944 input faces for
every round count 1–8. In every case,
`F^r(v) XOR F^r(0)` had **at least 250 active bytes** (median 255). Hence
none of these input faces can map into *any* affine output subspace whose
difference space is confined to at most 32 byte positions after 1–8 rounds. This excludes
one-step trails from these faces into any other equal-byte XRBD face,
not merely `V -> V`. It does **not** exclude dense output subspaces,
other input subspaces, arbitrary-base trails, or attacks on the actual
hash interface. The compact reports are `invariant_witness_audit.json`
and `xrbd_face_generator_all_rounds.json`; the original exhaustive
report is `~/krakken/krakken_invariant_all.json`.

```bash
~/venv/krakken/bin/python ~/krakken/krakken_degree.py --source-dir . --round 1 --round 2 --cube-degree 16 --cube-samples 10 --json new_degree_audit.json
~/venv/krakken/bin/python krakken_invariant_witness_audit.py ~/krakken/krakken_invariant_all.json ~/krakken/krakken_invariant_face32.json --output new_invariant_audit.json
~/venv/krakken/bin/python krakken_xrbd_face_generator_scan.py --output new_face_generator_scan.json
```

## Exact first-round hash-message differential probabilities

`krakken_hash_chi_probability.py` counts one **fully specified post-Chi1
XOR difference** for each of the two previously constructed valid 159-byte
message pairs. The XOR difference between the messages is fixed; the base
message is uniform over all 159-byte strings, with the same fixed `0x86`
padding byte. Results are in `hash_chi_probability_affine.json`.

| Witness | A1 | Affected two-byte Chi components | Pre-Chi base map rank | Independent message constraints | Exact probability of this post-Chi1 difference |
|---|---:|---:|---:|---:|---:|
| Theta-cancelling two-byte difference | 21 | 14 | 220/224 | 147 | **2^-147** |
| One-byte difference | 52 | 31 | 459/496 | 363 | **2^-363** |

Each Chi component maps an input byte pair `(a,b)` to
`(S(a XOR b), S(b XOR S(a XOR b)))`. Exhaustive enumeration of all 65,536
bases for each affected component found that the bases producing the
witness's prescribed output difference form an affine GF(2) set. Pulling
those local linear conditions back through the actual
message-to-pre-Chi prefix yields consistent systems of ranks 147 and 363.
The exact probabilities are therefore `2^-147` and `2^-363`. The
pre-Chi component input bytes themselves are **not** independent: their
respective maps have four and 37 linear relations. The script handles
these relations by ranking the full pulled-back system. For the two-byte
case, a separate 16-term character sum over its four relations gives the
same `2^-147` answer. The local Chi mapping is checked against the C
implementation on both recorded witnesses, and the script also runs the
existing full-hash C self-check.

The two-byte `A1=21` event has probability `2^-49` for that fixed message
difference, so the specific post-Chi1 difference above has conditional
probability `2^-98` *given* that event. Likewise the specific one-byte
post-Chi1 difference has conditional probability `2^-293` given its
`A1=52` event of probability `2^-70`. These are exact probabilities of
two **chosen one-round trails**, not upper bounds on all differences with
that activity, differential hulls, collisions, or the eight-round hash.
An attacker may accept many post-Chi1 differences; summing or bounding
those alternatives is a separate problem.

The next pass bounds **every individual post-Chi1 difference**, not just
the two selected witness differences. For one local two-byte Chi component,
set `u=a XOR b` and `v=b XOR S(u)`. This is a bijective change of base
variables. For input difference `(da,db)` and output difference
`(dap,dbp)`, its exact uniform-base transition count is

`DDT[da XOR db,dap] × DDT[db XOR dap,dbp]`.

`krakken_hash_chi_max_dp_bound.py` maximizes that count independently at
each affected component, then allows for the full rank defect of the
message-to-pre-Chi component map. This yields rigorous, conservative bounds
for a uniform 159-byte base message and each **fixed** input difference:

| Fixed message XOR difference | Affected components | Map rank defect | Maximum probability of any *one* post-Chi1 XOR difference |
|---|---:|---:|---:|
| Two bytes at 111 and 127, XOR `0x08` | 14 | 4 | **≤ 2^-129** |
| One byte at 72, XOR `0x08` | 31 | 37 | **≤ 2^-285** |

Equivalently, the post-Chi1 difference distributions for these fixed inputs
have min-entropy at least 129 and 285 bits. Conditional on the rare
`A1=21` or `A1=52` event respectively, the same bounds imply at least
80 and 215 bits of min-entropy for the specified post-Chi1 difference.
The local DDT product formula matched exhaustive 65,536-base enumeration
for all 45 affected components in the two recorded witnesses. Results are
in `hash_chi_max_dp_bounds.json`. The bound says nothing by itself about
the probability of a **set** of useful output differences.

We also broadened the empirical second-round check for the two-byte
`A1=21` family. The earlier 20,000-pair nullspace scan covered one of
128 cancellation choices. `krakken_a1_minimum_conditional_scan.py` samples
the entire event uniformly: the seven independent control bytes each have
two satisfying values, all 128 affine cosets have equal size, and random
nullspace coordinates choose a uniform base within the selected coset.
Each sampled pair was checked to retain `A1=21`; all 128 cosets were
visited in 100,000 samples (`a1_21_conditional_all_cosets_100000.json`).

| XRBD | Observed A2 minimum | Median | Mean | A2=256 samples |
|---|---:|---:|---:|---:|
| On | 249 | 255 | 255.0003 | 36,754/100,000 |
| Off | 249 | 255 | 255.0057 | 36,880/100,000 |

The paired comparison gave 34,671 samples with lower A2 when XRBD was on,
34,456 with lower A2 when off, and 30,873 ties. Grouping the activity
histogram into `A2<=251,252,253,254,255,256` and comparing it with the
simple independent-byte reference `Binomial(256,255/256)` gives Pearson
chi-square values 4.65 (on) and 6.88 (off), with five-degree-of-freedom
reference tail areas about 0.46 and 0.23. This reference is a diagnostic,
not a model proved for Krakken. The observed minimum 249 is an upper bound
on the unknown minimum over this conditioned family, not a lower bound.
The near-identical A2 distributions do not erase XRBD's large immediate
effect earlier in the round; Theta and later layers also spread the
difference before Chi2.

```bash
python3 krakken_hash_chi_probability.py rate_two_byte_constructed.json rate_a1_constructed.json --output new_hash_chi_probability.json
python3 krakken_hash_chi_max_dp_bound.py rate_two_byte_constructed.json rate_a1_constructed.json --output new_hash_chi_max_dp_bounds.json
python3 krakken_a1_minimum_conditional_scan.py --samples 100000 --seed 17149 --output new_a1_21_conditional_scan.json
```

## A first linear-hull analysis

A **differential hull** adds the probabilities of many allowed output
differences for one input difference. A **linear hull** instead sums the
signed contributions of many linear paths between fixed input and output
masks. The local Walsh transform computes that sum exactly, without
enumerating intermediate S-box approximations. This pass analyzes one
complete two-byte Chi component at the first hash block; it does not
calculate a multi-round linear hull.

Write the component input as `(a,b)`, its output as
`(S(a XOR b), S(b XOR S(a XOR b)))`, the input masks as `(alpha,beta)`,
and output masks as `(A,B)`. With unnormalized 8-bit S-box Walsh
coefficients `W_S`, the exact 16-bit component Walsh coefficient is

`W_Chi(alpha,beta; A,B) = W_S(alpha XOR beta,B) × W_S(alpha,A XOR alpha XOR beta)`.

This follows by changing variables to `u=a XOR b` and
`v=b XOR S(u)`, which are independent uniform bytes. Exhaustive
65,536-base sums for five mask quadruples confirmed the identity.
`krakken_chi_linear_hull.py` then maximizes the absolute correlation
over **all 65,535 nonzero 16-bit output masks** and all input masks:

| Chi output-mask family | Masks checked | Largest absolute correlation |
|---|---:|---:|
| First output byte only | 255 | **1/8** for every mask |
| Second output byte only | 255 | **1/64** for every mask |
| Both output bytes | 65,025 | at most **1/8** |

The second serial S-box therefore squares the relevant S-box Walsh
bound for a mask confined to its output byte. This is a **local linear
property**, not a claim that the complete round has bias 1/64.
The map from a uniform padded 159-byte message to *each* of the 128
two-byte Chi input components has rank **16/16**. Thus each of these
local spectra is exactly accessible at the first-block hash interface
by a suitable linear mask of message bits. One explicit first-output-bit
mask uses 135 message bits and has exact signed correlation `-1/8` with
that internal Chi output bit; another uses 162 message bits and has
correlation `1/64` with a second-output bit. In 100,000 C-checked
uniform messages the observed correlations were `-0.12952` and
`0.01696`, respectively (`chi_linear_hull_first_block_validated.json`).

XRBD is invertible and linear, so it moves these output masks without
changing their correlations. `krakken_xrbd_linear_mask.py` calculated
the inverse-adjoint masks: the one-bit Chi masks become **189-bit** and
**126-bit** masks after XRBD. The mask identity passed 100 direct C
checks per mask, and a separate 20,000-message test observed signed
correlations `-0.1319` and `0.021` against exact expectations `-1/8`
and `1/64` (`xrbd_linear_mask_validated.json`). This demonstrates why
looking only at single output bits can miss a linear approximation after
a diffusion layer.

Finally, `krakken_linear_bias_scan.c` screened those two fixed message
masks against all **2,048 single output bits** after one and two
*complete* reduced rounds, with XRBD on and off. In 100,000 message
bases, the largest absolute empirical correlation among 16,384 tests
was `0.01536`; zero exceeded the two-sided 5% familywise Hoeffding
threshold `0.01637` (`linear_bias_full_round_analysis_100000.json`).
This is a negative statistical screen for those masks and single-bit
outputs only. It does not rule out smaller biases, multi-bit output
masks, other input masks, or a multi-round linear hull.

```bash
python3 krakken_chi_linear_hull.py --sample-bases 100000 --seed 6321 --output new_chi_linear_hull.json
python3 krakken_xrbd_linear_mask.py --linear-report new_chi_linear_hull.json --samples 20000 --seed 7741 --output new_xrbd_linear_masks.json
python3 krakken_linear_bias_run.py --linear-report new_chi_linear_hull.json --samples 100000 --output new_linear_bias_raw.json
python3 krakken_linear_bias_analyze.py --raw new_linear_bias_raw.json --linear-report new_chi_linear_hull.json --output new_linear_bias_analysis.json
```

### Pressure's exact linear relations and low-bit correlations

Pressure does **not** erase every linear approximation. For one of its
independent 128-bit chains, with 64-bit words
`A=a+(c XOR (c>>17))` and `C=c+(A XOR (A<<31))`, the least significant
bits satisfy two exact identities:

`A[0] XOR a[0] XOR c[0] XOR c[17] = 0`

`C[0] XOR c[0] XOR A[0] = 0`.

`krakken_pressure_exact_linear.py` proves these are the **only affine
input/output relations** for a full chain. It forms 257-bit graph rows
`(1,a,c,A,C)` from 1,024 deterministic inputs, checks every output
against original C Pressure, and obtains GF(2) rank **255** by both high-
and low-pivot elimination. Every universal affine relation must lie in
this sampled graph's two-dimensional nullspace. The two identities above
hold algebraically for *all* inputs and are independent, so they span
that nullspace. The report stores the 255 independent certificate inputs.
Because the 16 chains use disjoint words, the complete uniform-input
Pressure mapping has exactly **32 independent exact affine relations**;
the odd chains' output rotations only move the two output bit positions.

Neither of our two XRBD-propagated Chi masks can continue through
Pressure with **correlation magnitude one** under a uniform full-state
Pressure input. Both fall outside that exact-affine input-mask span on
all 16 chains; their minimum Hamming distances to it are 173 and 126
bits (`pressure_exact_linear_relations_validated.json`). Distance from
the span is not a bound on smaller correlations, and hash-reachable
Pressure bases need not be uniform.

For correlations below one, `krakken_pressure_lowbit_walsh.py` computes
an exact low-bit spectrum. For `k<=17`, the low `k` bits of a full 64-bit
chain depend only on the **independent** bit blocks
`a[0:k]`, `c[0:k]`, and `c[17:17+k]`; the `A<<31` term cannot affect
them. A fast Walsh transform exhausts all `2^18` such inputs for `k=6`.
The best uniform-chain correlation for each single output bit is:

| Output bit | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---:|---:|---:|---:|---:|---:|
| `A` | 1 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 |
| `C` | 1 | 1/2 | 1/4 | 5/16 | 21/64 | 85/256 |

All 255 nonzero output masks within the low four bits of each `A,C` were also
scanned; exactly three have perfect correlation, matching the two-
dimensional exact-relation space. The reduced low-bit model passed 5,120
checks against original C Pressure. On 100,000 uniform full-width chain
bases, the predicted `A[5]` correlation `1/2` measured `0.5002`, and
the predicted `C[5]` correlation `-85/256` measured `-0.33194`
(`pressure_lowbit_walsh_6_validated.json`). These sizable local biases
make it especially important to analyze how preceding layers restrict
their input masks.

One such bridge is in `krakken_pressure_linear_bridge.py`. The best
uniform-chain input mask for output `C[5]` is just `a[5] XOR c[22]`,
with signed correlation `-85/256`. Pulling that *input mask* backward
through XRBD's exact transpose produces an **80-bit post-Chi1 mask**
spread across 80 serial-Chi components: 40 first-output-byte masks and
40 second-output-byte masks. The `C[5]` bit itself becomes round-one
output state lane 14, bit 16 after the affine Beta/Iota and shuffle
layers. Original C verified both mask mappings on 100 arbitrary states
each. The map from valid 159-byte message bits to
those 80 component inputs has rank **1195/1280**, a defect of 85.
The local Chi maximum correlations multiply to `2^-360` under independent
uniform component inputs; allowing for all 85 rate-image relations gives
the rigorous hash-message bound **`2^-275`** on correlation between this
*specific post-Chi1 mask* and **any** linear mask of a uniform
159-byte base message (`pressure_c5_chi_linear_bridge_checked.json`).

This is a bound on the **Chi side of one proposed linear path**. It
cannot be multiplied by `85/256` to obtain a full-round correlation:
the actual Pressure input is hash-conditioned, and the full linear hull
sums all intermediate masks with signs. It does show the central
tension quantitatively: a relatively strong low-bit Pressure mask
pulls back through XRBD to a Chi mask whose correlation with the real
first-block message interface is very small.

We also tested four **multi-bit masks at the output of one complete
round**, chosen by replacing Pressure's additions with XOR solely to
generate candidate masks. Under that carry-free model, the two exact
Chi1 message-mask correlations would be preserved at the round output
(up to the Beta/Iota constant phase). `krakken_pressure_carryfree_hull_probe.py`
checked each candidate's full carry-free mask identity on 100 valid
messages using original C Chi, XRBD, Beta/Iota, and shuffle, then used
**real C Pressure** on 100,000 fresh valid messages:

| Original Chi mask | XRBD | Final output-mask weight | Carry-free predicted correlation | Actual observed correlation |
|---|---|---:|---:|---:|
| First-output bit, `-1/8` | Off | 3 | -0.125 | -0.00308 |
| First-output bit, `-1/8` | On | 335 | -0.125 | +0.00398 |
| Second-output bit, `1/64` | Off | 5 | -0.015625 | -0.00064 |
| Second-output bit, `1/64` | On | 259 | -0.015625 | +0.00244 |

None exceeded the four-test 5% familywise Hoeffding threshold `0.01008`
(`pressure_carryfree_hull_100000_checked.json`). The actual modular
additions therefore do **not** preserve these four carry-free candidate
approximations at a detectable level in this experiment. This does not
bound the full linear hull: other output masks, including masks selected
with carry information, could correlate more strongly.

```bash
python3 krakken_pressure_exact_linear.py --samples 1024 --seed 119091 --output new_pressure_exact_linear.json
python3 krakken_pressure_lowbit_walsh.py --bits 6 --full-width-samples 100000 --seed 47121 --output new_pressure_lowbit_walsh.json
python3 krakken_pressure_linear_bridge.py --pressure-report new_pressure_lowbit_walsh.json --output new_pressure_linear_bridge.json
python3 krakken_pressure_carryfree_hull_probe.py --samples 100000 --seed 80421 --output new_pressure_carryfree_hull.json
```

### Exact restricted-input linear hulls across three rounds

The first full-round linear-hull calculation uses **actual valid padded
hash messages and actual C Pressure**, with a deliberately restricted
message distribution. For each of two message-byte layouts—positions
`(111,127)` (the Theta-cancelling pair) and `(72,73)`—we fixed the other
157 bytes to three separately seeded contexts and enumerated all
`2^16 = 65,536` values of the two free bytes. We ran one, two, and three
complete reduced rounds, with XRBD on and off. Eight preselected state
bits (seven within the first 256 bits and bit 912) and the two earlier
carry-free multi-bit output masks for each XRBD variant were observed
after each round.

For each of the **360 Boolean truth tables**, a complete 16-bit Walsh
transform gives every linear input-mask correlation on that cube. This
is a genuine, exact linear hull **for the restricted chosen-message
cube**: it sums all behavior of Chi, XRBD, carries, and later layers,
without choosing a particular intermediate trail. The driver checked
the eight-round hash API against the manual C round sequence; Python
replayed four input values per cube, and an independent audit checked
Walsh Parseval for all 360 truth tables. Raw cube binaries, the main
report (`linear_cube_hull_3contexts.json`), and the nonzero-input-mask
audit (`linear_cube_hull_3contexts_nonzero.json`) are saved.

For calibration, 100 random Boolean truth tables on 16 bits had median
maximum absolute Walsh correlation **0.01717**. A conservative
two-sided 5% familywise random-function reference across all
23,592,960 cube coefficients is **0.02511**. This is a reference for
interpreting the scan, not a security threshold for Krakken.

| Message-byte cube | XRBD-off round 1: constant targets / 30 | XRBD-off round 1: nonzero input-mask peaks above reference / 30 | XRBD-on round 1: peaks above reference / 30 |
|---|---:|---:|---:|
| `(111,127)` | 12 | 18 | 0 |
| `(72,73)` | 10 | 13 | 0 |

In the `(72,73)` cube, state bit 7 after one XRBD-off round was
**perfectly linear** in cube input bit 0 in two of the three contexts.
The strongest nonzero-mask one-round correlation across the three
contexts was `0.515625` for `(111,127)` and `1.0` for `(72,73)` with
XRBD off. With XRBD on, every tested round-one nonzero-mask maximum
was at most `0.02051`. After **rounds two and three**, none of the
240 tested truth tables in either XRBD mode exceeded `0.02511`; their
largest maximum was `0.02191`. The striking first-round contrast is
consistent with XRBD rapidly removing simple chosen-message linear
structure in these targets, while the other layers also remove it by
round two when XRBD is omitted.

These are exact statements about the six specified 16-bit cubes and
ten preselected targets per XRBD variant, **not** an exact hull over all
1,272 free message bits,
all output masks, or eight rounds. Other fixed-message contexts,
larger cubes, and carry-aware output masks could behave differently;
random-like Walsh maxima on these cubes do not establish collision or
preimage security.

```bash
python3 krakken_linear_cube_hull.py --contexts 3 --seed 95017 --output new_linear_cube_hull.json
python3 krakken_linear_cube_nonzero_audit.py --report new_linear_cube_hull.json --output new_linear_cube_nonzero.json
```

## What these numbers do and do not say

The Abyssal S-box has no fixed points, maximum DDT entry 4/256, maximum
nontrivial absolute Walsh correlation 32/256 (nonlinearity 112), and maximum
BCT entry 6. All square minors of the bytewise 8×8 MDS matrix are nonzero,
giving byte branch number 9 for that layer in isolation. Those are useful
component checks, but multiplying
them across active calls does not give a general full-permutation attack bound:
the two Chi S-boxes in each pair are serial, and the ARX additions create
value-dependent differences. The minimum number of active calls also says
nothing directly about integral or rebound complexity.

The C implementation of Keccak-f[1600] is called only while SHAKE generates
Krakken's constants. The permutation rounds themselves use Keccak-like
Theta/Rho/Pi operations, followed by Krakken's own Chi, XRBD, ARX and other
layers. Consequently, a Keccak round-security result does not transfer to
Krakken's round function.

A solver failing to find a trail does not establish an eight-round security
margin. In particular, an old rebound search stopping at round four shows the
reach of that search, not a proven four-round margin. For a stronger assessment,
the next experiments should target (1) certified lower bounds on actual
full-width differential activity across the linear XRBD bridge, (2) exact
or bounded XOR-difference probabilities through the modular additions, (3)
multi-round linear hulls including Pressure, (4) integral/division-property
analysis, and (5) hash-level collision or preimage claims with the actual
160-byte rate and 96-byte capacity. Each
requires a clearly stated attack model and success measure. The probes here
provide witnesses and a controlled XRBD comparison to guide that work.

## Carry-aware Pressure linear-hull work

The theorem program now contains a proved extension of the exact
Pressure mask counter. Besides all first-output-only masks, the
second-addition substitution covers **every** chain mask with zero
`a`-input mask and arbitrary two-word output masks. The carry-free
identity `C[0]=c[0] XOR A[0]` also covers all masks whose second
output mask is zero or its LSB. The report
`pressure_two_shear_walsh_validated.json` checks these identities
against 18,720 exhaustive reduced-word mask cases and the original
C implementation. In the union of those complete classes, every
nonperfect uniform-chain-input coefficient is at most `1/2`, and
the bound is sharp. This is a theorem with the scope given in
`KRAKKEN_SECURITY_THEOREMS.md`, not a claim about the conditional
Pressure input distribution reached by a valid hash message.

For the remaining coupled-mask class, the exact signed two-addition
convolution was checked against every mask quadruple of several
4-bit analogues. An instructive counterexample appears with shifts
`>>3` and `<<3`: input masks `(u,v)=(8,0)`, output masks
`(p,q)=(1,8)` have **exact correlation zero**, while summing
absolute path contributions gives `7/8`. The exhaustive report is
`pressure_coupled_hull_w4_r3_l3_checked.json`. Thus that generic
absolute-value argument cannot establish a `1/2` coupled-chain bound
even at this reduced width. It is an obstruction to a proof method,
not evidence of a strong 64-bit distinguisher. The arbitrary-output
64-bit coupled-chain bound and the eight-round rate-restricted hull
remain open; the low-17 output subclass is now closed below.

## Exact coupled low-bit Pressure counter

The joint-carry work closes a complete mask class inside that
previously open coupled region. For both output-word masks restricted
to low `k≤17` bits, the actual full-width Pressure chain reduces
exactly to three independent `k`-bit input slices and two jointly
tracked carries. [The counter](../scripts/krakken_pressure_joint_lowbit_walsh.py)
returns the exact signed Walsh numerator for **every** input/output
mask in this class in time linear in `k`, with denominator `2^(3k)`.
Input masks touching bits outside the three relevant slices have
exact zero correlation. The [report](../results/pressure_joint_lowbit_walsh_validated.json)
checks all 33,824 mask quintuples at `k=1,2,3` against full Walsh
transforms, reproduces `-85/256` for the earlier `C[5]` mask, and
matches original C on 1,000 low-17 evaluations.

An exact genuinely coupled `k=17` example has correlation
`-357913941/1073741824`, about `-1/3`. It shows why this class needed
a joint counter; it is a component correlation under uniform Pressure
input, not a complete-round hash result. The other new improvement uses both perfect
affine LSB relations to clear `u[0]` and `q[0]` from any chain-mask
problem; the [extended two-shear report](../results/pressure_two_shear_affine_extended_validated.json)
checks all 4,096 masks of a three-bit analogue after this
canonicalization.

The subsequent [all-mask certificate](../scripts/krakken_pressure_lowbit_max_certificate.py)
closed the numerical maximum for low `k≤6`. Its
[report](../results/pressure_lowbit_max_k6_certificate.json) contains exact
integer Walsh spectra for all `1,108,378,656` relevant mask
quintuples across `k=1,...,6`, including more than a billion at
`k=6`. The maximum nonperfect absolute correlation is zero at
`k=1` and **exactly `1/2`** at each `k=2,...,6`; a single mask
`(u,v_low,v_high;p,q)=(3,0,2;0,2)` attains `+1/2` at all those
widths. The only perfect coefficients are the four combinations of
the already classified LSB relations. This is an exhaustive theorem
for those six defined classes of the real 64-bit chain. It was then
superseded by the analytic low-17 proof below; it remains independent
validation of the first six widths.

## Sharp low-17 Pressure theorem

The [top-bit support rule](../scripts/krakken_pressure_lowbit_top_support.py)
forces three input-mask bits at the highest selected output bit and
rules out all input-mask bits above it. The
[report](../results/pressure_lowbit_top_support_validated.json) checks the rule
against full spectra through `k=5` and 1,000 forbidden `k=17` masks.

More importantly, the four-state suffix automaton revealed a short
induction. A nonzero highest output bit leaves one of three signed
carry vectors. All `3×32=96` ways to prepend the next bit produce
vectors whose **four components** each have magnitude at most
`32/64=1/2` after normalization. Every further bit transition has
absolute row sum at most one, so this `1/2` bound persists through
`k=17`. The base has an algebraic explanation: the three nonzero
outgoing-carry characters have quadratic parts
`a(c XOR h)`, `c(a XOR h)`, and `h(a XOR c)` in the three fresh
bits. Each is a rank-two quadratic form, so every affine-masked
Walsh coefficient has magnitude at most `1/2`. The
[proof script](../scripts/krakken_pressure_lowbit_half_theorem.py) checks this
quadratic classification and checks the 96-case base by both matrix
multiplication and independent two-bit input enumeration. Its
[report](../results/pressure_lowbit_half_theorem_algebraic_validated.json) verifies the
`k=17` attaining witness `+1/2`. Thus the nonperfect maximum is
**exactly `1/2` for every `2≤k≤17`**, with only the four affine LSB
perfect coefficients. This result is for a uniform unrestricted
Pressure input; it does not by itself bound a hash-conditioned or
complete-round linear hull.

The exact [suffix-automaton run](../results/pressure_lowbit_suffix_depth13_validated.json)
also aggregated complete mask classes through 13 bits and reproduced
the six-bit exhaustive certificate's nonzero counts and maxima. The
96-case induction is the proof covering all 17 widths; the larger
automaton run is a separate implementation cross-check.

## First complete-round valid-message linear bound

The next pass crossed Pressure by an **exact** affine identity rather
than a uniform-input approximation. In each of its 16 chains,
`A[0] XOR C[0]=c[0]`. After accounting for odd-chain rotations,
round constants, and the final shuffle, that identity defines one
two-bit output mask after a **complete first round**. Pulling its
single Pressure-input bit back through XRBD gives a fixed post-Chi1
mask. The actual rate-to-selected-pre-Chi rank and exact local
serial-Chi Walsh maxima then bound its correlation with **every**
1272-bit mask of a uniform valid 159-byte message.

The [48-mask audit](../scripts/krakken_hash_round1_pressure_affine.py) and
[report](../results/hash_round1_pressure_affine_48_validated_v3.json) show that
all 16 masks of this `A[0] XOR C[0]` class have bounds at most
**`2^-174`**; individual ceilings range from `2^-354` to
`2^-174`. This is a rigorous one-round hash-message theorem for a
complete specified output-mask class, not a sample or a selected
linear trail. The other 32 single-chain affine Pressure masks give
37 nonvacuous bounds across all 48 masks, but some are vacuous under
the same inequality, so they are not included in the uniform claim.

The [two-chain audit](../scripts/krakken_hash_round1_pressure_affine_pairs.py)
checked all 120 XORs of distinct masks in the 16-mask class. Its
[report](../results/hash_round1_pressure_affine_AC_pairs_validated.json) has
106 nonvacuous and 14 vacuous bounds. A vacuous bound is a limitation
of the triangle inequality and affine-rank correction; it is not a
found high-correlation distinguisher. The remaining research target
is to control signed Fourier cancellation across larger output-mask
classes and across later rounds.

## Five-dimensional first-round output-mask subspace

The [coordinate-subspace verifier](../scripts/krakken_hash_round1_affine_subspace.py)
combined the 16 exact-affine `AC` Pressure identities and checked every
nonzero XOR in candidate coordinate subspaces of those 16 output
masks. At the `2^-128` target, pair bounds left 54 candidate triples,
25 quadruples, and five quintuples. The verifier computed the 84
distinct higher-weight mask bounds needed for these sets. Two
five-generator sets passed; the stronger is indexed
`[0,2,4,10,12]`, corresponding to
`beta_(0,0), beta_(1,0), beta_(2,0), beta_(5,0), beta_(6,0)`.

The [source-pinned report](../results/hash_round1_AC_coordinate_subspaces_128_validated_v3.json)
certifies a bound of **`2^-162`** for every one of the 31 nonzero
output masks in that five-dimensional subspace, against **every**
1272-bit mask of a uniform valid 159-byte message after one complete
round. All 31 masks are distinct. The weakest calculated ceilings are
for subsets `[0,2,12]` and `[0,2,4,12]`. All 31 selected rate
projection ranks agree with the independent rank routine, ten local
Chi maxima agree with direct complete 16-bit Walsh calculations, and
each new higher-weight mask passed three original-C parity replays.

The other three pair-qualified quintuples failed this **proof method**:
their worst calculated ceilings were `2^0`, `2^-124`, and `2^-5`.
That is no evidence of actual high correlation. This result enlarges
the complete first-round hash-level mask class; it does not bound all
2048-bit output masks or later-round hulls.

As a strict corollary, the five generator output parities are within
total variation `2^(d-160)` of uniform when a valid 159-byte message
is sampled uniformly subject to **any** codimension-`d` affine
message constraint. At `d=128`, the ceiling is `2^-32`. The proof
uses the all-message-mask correlation bound, indicator expansion for
the affine constraint, and Fourier Parseval; it adds no sampling
assumption.

## Six-dimensional first-round output-mask subspace

The coordinate-subspace search was extended from the `2^-128`
threshold to `2^-96` and then `2^-76`, checking every nonzero XOR in
every pair-qualified candidate of dimensions three through seven.
At `2^-96`, no six- or seven-generator coordinate set passed the
complete-subspace bound, so the previously certified five-dimensional
class remained best. At `2^-76`, exactly one of 21 pair-qualified
six-generator sets passed and neither of the two pair-qualified
seven-generator sets passed. This is a limit of the **coordinate-set
search and this affine-image bound**, not a lower bound on actual
correlations or on all possible subspaces.

The passing generators have indices `[0,2,4,8,10,12]`, or
`beta_(0,0), beta_(1,0), beta_(2,0), beta_(4,0), beta_(5,0), beta_(6,0)`.
The [final certificate](../results/hash_round1_AC_coordinate_subspaces_76_validated_v2.json)
proves that every one of their **63 nonzero XORs** has absolute
one-round correlation at most `2^-76` with **every** message mask,
under uniform valid 159-byte first-block messages. The weakest
calculated pair/triple ceilings are `{2,8}` and `{0,2,8}`. Both
touch 104 Chi components and have full 1272-bit message-projection
rank. The verifier recomputed all 63 selected ranks independently,
ten local Chi maxima by direct 16-bit Walsh transforms, and all new
higher-weight mask transports through original C. The 63-mask bound
also implies total variation less than `2^-74` between the joint
six-bit output-parity distribution and uniform.

The uniform correlation bound over **all** message masks yields an
affine-conditioning corollary without another cryptanalytic search.
For any codimension-`d` affine subspace of valid 159-byte messages,
conditioning the uniform message on that subspace expresses each
six-bit output Fourier coefficient as a signed sum of `2^d` already
bounded message-mask correlations. Thus the six-bit projection has
total variation below `2^(d-74)` from uniform. In particular, after
fixing any 64 independent message parities, the bound is below
`2^-10`. This is a proved consequence of the 63-mask theorem and
Fourier inversion, not an additional empirical measurement.

## Valid-message algebraic degree through eight rounds

The earlier 16-variable derivative witness concerned the unrestricted
permutation and only the first two rounds. This pass moved the cube
domain to **valid padded 159-byte messages**, recorded a nonzero
24-variable derivative in the first 32 state bytes after every
complete round 1–8, and then sought per-coordinate certificates.
The [24-cube report](../results/degree_hash_cube24_validated_v3.json) records
all `2^24` vertices through the original round structure and proves
vectorial degree at least 24 for each reduced-round projection,
including the real eight-round one-block digest.

The per-coordinate picture is more nuanced. Twelve 20-bit coordinate
cubes reached 1983 of 2048 round-one state bits; 65 were still
uncovered. After rounds 2–8, they reached every state bit except
two at round 7. Dense-direction 20-bit cubes resolved the non-LSB
gaps. The [baseline](../results/degree_hash_digest_allcoords_d20_validated_v2.json)
and [dense completion](../results/degree_fullstate_allcoords_d20_validated.json)
now contain a nonzero order-20 derivative for **all 2016 round-one
state bits outside the 32 Pressure LSB positions** and for **all
2048 state bits at every round 2–8**. Coordinate-only cubes missing
a bit did not establish a low degree; the dense-direction witnesses
show why the distinction matters.

The 32 excluded bits reveal a real first-round structure. Exhaustive
ANF of the two-byte serial Chi finds degree 7 in its first output
byte and degree 13 in its second. Pressure's `A0` and `C0` identities
have no carry, so after the affine suffix all 32 corresponding state
bits have degree at most 13. Eight dense 13-variable message cubes
were evaluated; seven attaining witnesses cover **each** of the 32
bits, with complete original-C cube replay for every witness. They therefore
have **exact degree 13**. The [local ANF report](../results/serial_chi_16bit_degree_validated.json),
[C mask-layout audit](../results/degree_hash_round1_lowbits_mapping_validated.json),
and [all-32 attaining certificate](../results/degree_round1_pressure_lsb_all32_exact13_validated.json)
give the proof pieces. Four of these positions land in the first
32-byte projection at bit indices `11,94,139,210`.

This provides an exact first-round higher-order integral on those 32
bits: **every** 14-dimensional message derivative is zero there.
The round-two lower bound says each coordinate polynomial has some
nonzero 20-dimensional derivative; it does **not** say that all
20-dimensional cubes are nonzero or that no other integral attack
exists. The fast table-based cube evaluator is equivalent to the
original constant-time S-box scan byte by byte and is checked against
original C for Chi, full rounds, and complete smaller cubes. The
[structural audit](../scripts/krakken_degree_multiround_audit.py) verifies
source hashes and derivative coverage.

## Astra's September 20 dossier: local boomerang structure and review leads

The [continuity dossier](/home/user/krakken/DOSSIER.md) predates the
later rate-aware and algebraic-degree theorems in this workspace. Its
strongest locally reproducible new result is a perfect boomerang
family of the effective two-byte serial-Chi component. For every
nonzero `beta,gamma∈GF(2)^8`, the BCT entry at input difference
`(beta,beta)` and output difference `(gamma,0)` equals **65,536**.
The [independent source-pinned verifier](../scripts/krakken_serial_chi_boomerang.py)
replayed the full 16-bit inverse and four representative complete
BCT entries; the [certificate](../results/serial_chi_boomerang_max_family_validated.json)
records them. The algebraic commuting-translation argument proves
all **65,025** specified entries. This is a genuine maximal
**local** boomerang property, not a full-round distinguisher.

The dossier reports that Pressure breaks the universal fixed-
difference continuation of this local family, yet a carefully chosen
base can form a real one-round quartet; its tested quartet fails at
the next Chi. The named quartet support files are absent from the
local source directories, so these particular complete-round witness
claims remain **unreplayed leads** here. Likewise, the dossier's
`[1,1]` exclusion references a proof script present in `~/krakken`.
That model was not audited in the dossier handoff; the independent
audit recorded below has now checked it. The sound conclusion is a
**two-round total** activity minimum of three, not `A2≥3` alone.

The dossier's two-round unrestricted upper bound **235** is older
than the already C-verified `[32,121]` witness in this notebook,
whose total is **153**. It should not overwrite that newer bound.
Source inspection confirms the dossier's separate portability
warning: the SHAKE helper and sponge use native byte views of
`uint64_t` state, so a cross-endian specification needs explicit
serialization. This is an implementation/specification concern, not
a demonstrated little-endian cryptanalytic break.

## Two-round sparse-differential proof audit and fast endpoint sieve

The [independent `[1,1]` audit](../scripts/krakken_11_audit.py) pins the C, header,
model, and 512-job log hashes. It checked all 65,280 one-byte XRBD
start differences against the model's branch-nonzero cuts, compared
each compiled linear layer and the full inverse tail to C, tested
768 generated one-active Chi2 target shapes, exhausted the 64 local
full-adder difference pairs used by the relaxed Pressure model, and
replayed one SCIP infeasibility job for each Chi2 branch. The
[report](../results/krakken_11_audit_validated.json) records the outcome. The
model overapproximates all real `[1,1]` trails, and the original log
contains 512 distinct infeasible jobs with no unknowns. The global
two-round `[1,1]` exclusion is therefore promoted to the
[theorem program](KRAKKEN_SECURITY_THEOREMS.md) and
[review claims](KRAKKEN_CLAIMS_FOR_REVIEW.md).

For a cheaper route toward `[1,2]`, the
[Pressure-LSB endpoint rank program](../scripts/krakken_pressure_lsb_endpoint.py)
uses the 32 exact bit-zero Pressure differential identities plus
exact XRBD and inverse-tail maps. Rank with nonzero-byte projection
excludes 18,349 of 65,536 one-active Chi2 site/branch cases; the
full-column-rank test alone excludes none. More usefully, among all
2,080,768 choices of post-Chi1 start byte location and **two distinct
second-branch Chi2 active cells**, it excludes **1,034,445** cases
for all byte values and bases. The
[report](../results/krakken_pressure_lsb_endpoint_rank.json) gives complete
counts and validates the identities against C-derived Pressure
transitions. This is a closed `[1,2]` **subclass**, not full `[1,2]`
impossibility: 1,046,323 site cases in that subclass and other branch
patterns remain open.

Astra's [optimized oracle](../scripts/oracle_optimized.py) already has
these exact bit-zero equations in its sparse master, then uses exact
128-bit Pressure-chain oracles and full C replay. Its wider
`[1,2]` support search remains valid research, but the 8,256
supports per start location make a global campaign expensive. The
rank sieve is an explicit, no-timeout accounting of the portion that
the cheap equations can exclude. It identifies where stronger
carry-aware or cross-layer arguments are needed before another large
oracle run.

The [joint-two-bit Pressure screen](../scripts/krakken_12_joint2_screen.py)
implements that next necessary condition. For each 128-bit Pressure
chain, the first two bits of both additions have an exact 184-of-1,024
feasible difference table under arbitrary base slices. The screen
first solves the 32 bit-zero equations over the one post-Chi1 and two
second-call Chi2 byte differences; it then exhausts the resulting
GF(2) kernel when its dimension is at most 18. With the sole
post-Chi1 byte at lane 0, byte 0, the complete 8,128 distinct Chi2
cell-pair accounting is: **3,872 LSB exclusions; 2,351 more exact
two-bit exclusions; 1,139 low-two-bit survivors; 766 capped cases**.
Thus the first two categories, 6,223 named support pairs, are
impossible for all nonzero endpoint-byte values and any base state.
The [producer report](../results/krakken_12_joint2_start0.json) is reproduced
exactly by an [independent original-C/opposite-pivot audit](../results/krakken_12_joint2_start0_audit.json).
The audit rederives the inverse prefix from the full C matrix and
checks all 1,024 target basis columns against the C tail. The
survivors remain necessary-condition candidates, not actual trails;
the capped cases are unknown. Other Chi1 positions are covered by the
all-position certificate below; other two-call shapes are not.
Reproduce
the fixed-position calculation with
`/home/user/venv/krakken/bin/python krakken_12_joint2_screen.py --start-position 0 --output krakken_12_joint2_start0.json`,
then run `krakken_12_joint2_start0_audit.py` with the same Python.
The [sequential all-position driver](../scripts/krakken_12_joint2_all_positions.py)
finished all 256 positions on 2026-09-26, one worker at a time with
no runtime timeout. Its [log](../logs/krakken_12_joint2_all_positions.log),
[source-pinned summary](../results/krakken_12_joint2_all_positions/summary_k18.json),
and 256 per-position JSON files account for every
`256 × C(128,2) = 2,080,768` site case in this defined class:

| Screen outcome | Cases | Meaning |
|---|---:|---|
| Bit-zero excluded | 1,034,445 | Previously certified LSB obstruction |
| Additionally excluded by exact joint low-two-bit Pressure test | 593,659 | No assignment survives the necessary carry constraints |
| Low-two-bit survivor | 298,360 | Necessary condition passes; no real trail established |
| Kernel dimension above the chosen cap of 18 | 154,304 | Not evaluated by the joint-two-bit enumeration |

The two exclusion categories total **1,628,104 / 2,080,768 = 78.2453%**;
**452,664** site cases remain unresolved by this screen. A fresh
file-integrity pass checked all 256 source pins, the 8,128 cases per
position, and agreement of every per-position count with the summary.
The additional all-position joint-two-bit count has now been
independently recounted in full and is recorded in the theorem and
review claims. A survivor is not a real `[1,2]` trail, and this class
does not include other two-call Chi2 shapes.

The [independent all-position auditor](../scripts/krakken_12_joint2_all_positions_audit.py)
now derives XRBD and the inverse tail from original C, replays the
inverse target columns through C, uses opposite-pivot GF(2) elimination,
and independently enumerates the two-bit Pressure relation. **All 256
positions match the producer exactly.** The resumable audit writes one
`audit_position_###_k18.json` per completed position and an
[audit summary](../results/krakken_12_joint2_all_positions/audit_summary_k18.json).
It has no runtime timeout and runs one process. To reproduce from
scratch or recheck cached certificates, run
`/home/user/venv/krakken/bin/python -u /home/user/sol/krakken_12_joint2_all_positions_audit.py --start 0 --end 255`.
The script itself appends progress to
[the audit log](../logs/krakken_12_joint2_all_positions_audit.log).

### Three-bit Pressure gate for unresolved `[1,2]` sites

The [selected-site Z3 script](../scripts/krakken_12_jointk_selected_z3.py) uses
current original C to derive XRBD and the inverse inter-round linear
tail. It then models the **joint low `k≤17` bits of both Pressure
additions** for all 16 chains, with the three symbolic difference
bytes required nonzero. The base slices of different chains are free,
making this a necessary-condition relaxation: `unsat_excluded`
proves the named site impossible, while `sat_relaxed` does not prove
a trail. There is no solver timeout. It selects `survivor` and/or
kernel-capped `large` cases from the audited two-bit classification,
saves each result immediately, and resumes by skipping saved cases.

For **position 0**, all 1,905 cases left unresolved by the two-bit
gate (`1,139` survivors and `766` capped) returned `unsat_excluded`
at `k=3`. For **position 1**, all 1,896 unresolved cases (`1,335`
survivors and `561` capped) did likewise; **position 2** also returned
UNSAT on all 1,886 unresolved cases (`970` survivors and `916`
capped). Thus the two-bit exclusions plus the three-bit producer
results account for all 8,128 pairs at each of these three start
positions. Their [position-0](../results/krakken_12_joint3_selected_pos000.json),
[position-1](../results/krakken_12_joint3_selected_pos001.json), and
[position-2](../results/krakken_12_joint3_selected_pos002.json) per-site files
record every new result. The script checked 32 original-C
Pressure transitions at three bits and replays every inverse-tail
endpoint column through original C. These findings are **not yet
promoted to the theorem/review ledger**: they still need an independent
three-bit recount and model audit. The three-bit screen has not been
run over all 256 positions. The `--limit` option counts only newly
selected unresolved cases, not all 8,128 endpoint pairs. The
[single-worker all-position driver](../scripts/krakken_12_joint3_all_positions.py)
checks the source-pinned two-bit baseline, skips complete positions,
launches one worker per remaining position without a timeout, and
writes a [campaign summary](../results/krakken_12_joint3_all_positions_summary.json).
Positions 0–2 passed the driver check. Resume the campaign with
`/home/user/venv/krakken/bin/python -u /home/user/sol/krakken_12_joint3_all_positions.py --start 3 --end 255`;
progress goes to [the campaign log](../logs/krakken_12_joint3_all_positions.log).

### Remaining Chi2 two-call shapes: source-derived LSB prefilter

The BB campaign above covers two **second-only** calls in distinct
serial-Chi cells. For each cell, write its pre-Chi input-byte
differences as `(dx,dy)`, the first-S-box input difference as
`alpha=dx XOR dy`, and its output difference as `delta_u`. The current
C serial order gives the other shapes exactly:

| Chi2 shape | Necessary pre-Chi difference form |
|---|---|
| First-only call (A) | `(dx,dy)=(alpha XOR delta_u,delta_u)`, with `alpha,delta_u ≠ 0` |
| Second-only call (B) | `(dx,dy)=(v,v)`, with `v ≠ 0` |
| Both calls in one cell | `(dx,dy)=(alpha XOR v,v)`, with `alpha ≠ 0`; `v` is unrestricted in this relaxation |

The [new original-C LSB screen](../scripts/krakken_12_missing_shapes_lsb.py)
uses these forms for distinct-cell `AA`, `AB`, `BA`, and the
both-calls-in-one-cell class. For every named site, GF(2)
inclusion-exclusion counts **exactly** how many symbolic byte
assignments satisfy the 32 Pressure bit-zero identities and the
stated nonzero-byte requirements. A zero count is an exclusion;
a nonzero count is only a necessary-condition survivor. This screen
deliberately omits the S-box DDT and the same-cell second-call
condition, so it cannot turn a survivor into a trail. The script
checks 100 original-C local-Chi constructions, 100 original-C
Pressure transitions, and every inverse-tail basis column by C
replay. Its inclusion-exclusion counter also matched 100 small
brute-force systems.

The lightweight [30-cases-per-shape pilot](../results/krakken_12_missing_shapes_lsb_pilot.json)
found `9/30` AA, `12/30` AB, and `14/30` BA exclusions; its 30
same-cell samples all survived. The full **128 same-cell sites at
start position 0** gave 3 exclusions and 125 survivors in the
[finite report](../results/krakken_12_same_cell_lsb_start0.json). These are
producer results for narrowly stated cases, not a full `[1,2]`
theorem. No large second sweep was started while the user’s
three-bit BB campaign was running.

## Exact rotational-affine symmetry screen

The [rotational verifier](../scripts/krakken_rotational_affine_audit.py) tested the
uniform lane rotations `R_k`, `k=1,...,63`, against every reduced-round
permutation `P_r`, `r=1,...,8`. It also repeated the test with round
constants omitted. A proposed fixed-offset relation
`P_r(R_k x)=R_k P_r(x) XOR c` has its only possible `c` fixed by
`x=0`. In **all 1,008** rotation/round/mode cases, the single
additional state with bit 11 in lane 0 set violates that relation.
The [source-pinned certificate](../results/krakken_rotational_affine_audit.json)
records the mismatch weight for every case. Thus the complete
**perfect rotational-affine** class is excluded, including when round
constants are absent. This says nothing yet about a weaker
statistical rotational distinguisher; a related-input bias screen is
the next separate question.

The [exact decomposition verifier](../scripts/krakken_rotational_decomposition.py)
also confirms, for all seven byte-aligned rotations, that the
one-round related-input residual equals a shuffled Pressure-only
residual plus a fixed round-constant offset. All preceding round
layers commute with byte rotation and form a bijection. The
[C report](../results/krakken_rotational_decomposition_validated.json) checked
700 identities. Consequently, for a uniform unrestricted input,
one-round rotational bit-bias magnitudes are **exactly** Pressure's
bit-bias magnitudes up to bit relabeling; adding or removing XRBD
before Pressure cannot alter that uniform-input distribution.

The empirical follow-up used 100,000 deterministically seeded
pseudorandom full-state bases for each of the seven byte-aligned
rotations and round counts 1–2. For each related pair `(x,R_k x)`,
it measured every bit of `P_r(R_k x) XOR R_k P_r(x)`. With 28,672
bit tests per variant, the model-based familywise 5% Hoeffding
threshold for absolute correlation was `0.01670`. The
[XRBD-on report](../results/krakken_rotational_bias_allbyte_100k.json) and
[XRBD-off report](../results/krakken_rotational_bias_noxrbd_allbyte_100k.json)
gave the same flag counts by rotation:

| Lane rotation | Round-1 flagged bits, each variant | Round-2 flagged bits, each variant |
|---:|---:|---:|
| 8 | 1,376 | 0 |
| 16 | 736 | 0 |
| 24 | 544 | 0 |
| 32 | 448 | 0 |
| 40 | 544 | 0 |
| 48 | 736 | 0 |
| 56 | 1,376 | 0 |

Across all seven rotations that is **5,760/14,336** round-1 bit
tests flagged and **0/14,336** round-2 bit tests flagged, both with
and without XRBD. The largest observed absolute round-2 correlation
was `0.01384` with XRBD and `0.01498` without it. The
[no-XRBD wrapper audit](../scripts/krakken_noxrbd_wrapper_audit.py) matched 60
manually assembled C layer sequences at round counts 1, 2, and 8.
The source-pinned screens are empirical: the seed is deterministic,
the threshold assumes independent uniform draws as a statistical
model, and no absence-of-bias theorem follows. Sample-perfect
round-1 bits are not automatically exact identities; direct
Pressure testing found rare counterexamples. This class therefore
supports the recurring **round-2 loss of detectable structure**,
but unlike some earlier classes it does **not** show XRBD to be the
unique reason: the same effect appears with XRBD omitted. The
unrestricted full-state related-input experiment also does not
directly model the valid padded hash-message interface.

## Differential-linear autocorrelation: exact one-round family and round-two screen

For each of the 128 serial-Chi byte cells, choose the pre-Chi
diagonal difference `(delta,delta)` for any nonzero byte `delta`,
then invert the round's linear prefix to obtain an unrestricted
permutation input difference. Chi's first call is inactive; its
second call is the sole active byte S-box. In the 32-dimensional
output-mask space induced by Pressure's exact LSB relations,
the [differential-linear counter](../scripts/krakken_differential_linear.py)
finds and proves an exact perfect-derivative subspace of dimension
**26–29** for **every** cell and **every** nonzero `delta`.
The distribution of dimensions is 16 cells at 26, 48 at 27, 56 at
28, and 8 at 29. In 125 cells, a single output bit belongs to the
perfect subspace; the other three admit a two-bit mask. The
[source-pinned certificate](../results/krakken_differential_linear_validated.json)
lists every cell, exhausts all 255 byte-S-box derivative affine
spans, verifies 3,200 Pressure identities against C, and replays
one complete-round witness on 1,000 bases. The proof is in the
[theorem program](KRAKKEN_SECURITY_THEOREMS.md).

This is a genuine **attack-side one-round structure** of the
unrestricted permutation. It is not reachable as a nonzero
rate-only first-block hash difference, because every construction
has `A1=1` and the earlier rate-to-preChi rank theorem excludes
that activity at the actual padded hash interface.

The [two-round continuation screen](../scripts/krakken_differential_linear_screen.py)
selected a minimum-weight perfect one-round mask in each cell, fixed
`delta=1`, and evaluated 20,000 deterministically seeded
pseudorandom unrestricted bases per case through the original C
permutation. It checked the exact one-round parity on a C base for
all 128 cells. After two rounds, **0/128** masks crossed the
model-based familywise 5% threshold `0.02922`; the maximum observed
absolute correlation was `0.02060`. The
[report](../results/krakken_differential_linear_round2_20k.json) records each
cell's count. This is a negative statistical screen for those 128
continuations, not a bound on all two-round differential-linear
masks or a proof that their true correlations are zero.

The follow-up replaced the selected-mask screen with a **full-state
rank certificate**. For each of the same 128 `delta=1` input
differences, the [producer](../scripts/krakken_differential_linear_fullstate_rank.py)
computed complete 2048-bit two-round output differences and found
affine rank **2048/2048**. Every cell reached full rank within at
most 2,059 bases. The
[compact certificate](../results/krakken_differential_linear_fullstate_rank_all128.json)
stores generator seeds, accepted base indices, and derivative-sequence
digests. The [independent auditor](../scripts/krakken_differential_linear_fullstate_audit.py)
replayed **262,464** real C input pairs, checked the digests, and
recomputed every rank with the opposite pivot order; its
[report](../results/krakken_differential_linear_fullstate_audit_validated.json)
passed. Full affine span proves that **no nonzero output mask of any
weight** retains perfect (+1 or -1) differential-linear correlation
at round 2 for any of those 128 fixed input differences. This is
strictly stronger than the 32-mask-coordinate pilot and is a
deterministic finite theorem, not a statistical screen. It does not
quantify nonperfect correlations, and it does not cover all possible
input differences or valid first-block hash differences.

## Four-state zero sums: Chi/XRBD, complete rounds, and valid-message cubes

The [zero-sum producer](../scripts/krakken_zero_sum_square.py) enumerated the
16-bit effective serial-Chi component for an input difference in
its first byte and found an affine input square with an affine
output square:

```text
component inputs:  01d6 01d7 0404 0405
component outputs: 78b3 0aa0 0aa5 78b6
XOR of all four:  0000          0000
```

Inverting the linear round prefix makes this a four-state
**unrestricted-permutation input** zero sum. At post-Chi and post-XRBD,
the full 2048-bit state XOR remains zero for any common background
outside the chosen Chi component. After one complete round, 32
specific shuffled Pressure-output bits are still guaranteed balanced
by Pressure's exact affine LSB relations. The four-point XOR of the
*full* complete-round state need not be zero: in the representative
first context, 241 of 2048 output bits have XOR one.

The [representative report](../results/krakken_zero_sum_square_validated.json)
evaluated 2052 deterministic background contexts with original C.
Across them, 902 one-round coordinate bits happened to remain
balanced; only the 32 exact-affine positions are asserted to be
universal by the algebraic proof. At round two, the first 16
backgrounds already had no common balanced output coordinate. The
2052 round-two full-state sums span all 2048 bits, which excludes
**every** universal nonzero linear output mask for this one fixed
square at this one cell. The
[independent audit](../results/krakken_zero_sum_square_audit_validated.json)
replayed all 16,416 original-C round calls, checked the ordered-sum
digest and obtained rank 2048 using low-pivot elimination rather
than the producer's high-pivot elimination.

The [all-cell extension](../results/krakken_zero_sum_allcells_validated.json)
placed the same square in every one of the 128 Chi byte cells. All
128 sites lost every universally balanced **coordinate bit** after
round two; each required at most 18 deterministic C-evaluated
backgrounds. This all-cell result does not claim a full linear-mask
rank for every site.

For the actual hash interface, the
[valid-message cube script](../scripts/krakken_zero_sum_hash_cube.py) checked
four complete byte cubes with valid 159-byte padding. Each input
cube has XOR zero. None had a full-state output XOR of zero at round
one or two. The exact balanced-bit counts were:

| Message cube and base | Dimension | Round 1 / round 2 balanced full-state bits | Round 1 / round 2 balanced digest bits |
|---|---:|---:|---:|
| first byte, zero base | 8 | 1014 / 1035 | 126 / 115 |
| last byte, zero base | 8 | 1001 / 1017 | 119 / 130 |
| first two bytes, zero base | 16 | 1046 / 1041 | 140 / 129 |
| first two bytes, seeded base | 16 | 1081 / 1012 | 141 / 126 |

Those near-half bit counts concern **one cube each**; they are not
universal integral claims. The 8-bit cubes were replayed point by
point with original C; the 16-bit cubes used a table-equivalent Chi
implementation that passed the original-C selftest. The
[full report](../results/krakken_zero_sum_hash_cube_validated.json) stores the
base messages, all 2048-bit sums, and source hashes. No general
hash-reachable zero-sum exclusion follows from four finite cubes.

## Hash-reachable 14-cube zero sums across the first two rounds

The preceding four-state square used unrestricted permutation
inputs. A larger, **valid-message** zero-sum class follows from the
exact serial-Chi degree bound. A 159-byte message enters pre-Chi1
through an affine map. Each serial-Chi output bit is a Boolean
polynomial of degree at most 13 in its two input bytes. Therefore
the full 2048-bit post-Chi1 state XOR is zero over **every** affine
message cube of dimension at least 14, whatever its base and
independent message directions. XRBD preserves that full-state
zero sum. Pressure's 32 affine LSB relations preserve exactly
specified coordinate balances through the remainder of round 1.

The [14-cube producer](../scripts/krakken_hash_zero_sum_14cube.py) chose the
fixed directions at message bits `0,...,13`, enumerated all `2^14`
vertices for each base, and searched bases until the common
balanced-bit sets were closed:

| Bases checked | Common balanced state bits after round 1 | After round 2 |
|---:|---:|---:|
| 1 | 1066 | 1000 |
| 4 | 157 | 128 |
| 8 | 39 | 8 |
| 10 | 33 | 0 |
| 11 | **32** | **0** |

The 32 round-one positions match the exact Pressure affine-output
positions. The algebra proves they balance for every base; the
eleven complete cubes prove no other coordinate does. The ten-base
round-two set excludes every **coordinate-bit** balance from being
universal for this fixed direction set. This does **not** rule out a
non-coordinate output mask or some other direction set.

The [full report](../results/krakken_hash_zero_sum_14cube_validated.json)
stores each base and both 2048-bit sums. The
[independent original-C auditor](../scripts/krakken_hash_zero_sum_14cube_audit.py)
replayed **180,224 message vertices** through both round counts and
matched every sum. It also directly XORed a complete 14-cube at the
original-C Chi1 and XRBD1 checkpoints, finding all 2048 bits zero
at both. Its [report](../results/krakken_hash_zero_sum_14cube_audit_validated.json)
pins the C source and the producer report. The universal checkpoint
claim is mathematical, via the exact 16-bit Chi ANF certificate;
the C checkpoint replay validates the implementation path.

The [sharpness construction](../scripts/krakken_hash_chi_cube_threshold.py)
then used the full-rank `16/16` projection from valid messages to
one pre-Chi component. It pulled 13 selected local input-bit
directions back to 13 independent 159-byte message directions,
matching a nonzero degree-13 ANF monomial in the second serial-Chi
output byte. Its 8192-message original-C cube sum has **6 nonzero
post-Chi bits** and **288 nonzero post-XRBD bits**. The
[witness](../results/krakken_hash_chi_cube_threshold_validated.json) stores all
13 message masks and full-state sums, and an
[independent C replay](../results/krakken_hash_chi_cube_threshold_audit_validated.json)
matched both sums. Thus the universal internal zero-sum threshold
`d>=14` is exact: at `d=13` there exists a valid-message cube that
does **not** balance the full state. This does not assert that every
13-cube fails or address complete-round output balance.

## Division-property kit audit before a full-round campaign

The archived [division-property kit](../../data/github/krakken-cryptanalysis/division/krakken_divprop.py)
is the next distinct attack class to investigate. Its bundled C and
header match the current Krakken source byte-for-byte. The
[local-gate audit](../scripts/krakken_divprop_gate_audit.py) copied the kit into a
temporary directory, compiled its original C, and checked the
concrete serial-Chi and Pressure circuit interpreters against C on
200 random states each. Both passed. The 2040 nonempty S-box
input-pattern/single-output-bit cases matched the ANF-derived
division-trail table exactly.

For reduced modular adders, the audit exhausts input activity
patterns and output unit bits at widths 3, 4, and 5. **No nonempty
input pattern** produced an exact-reachable output bit that the MILP
called impossible in those small widths. The kit's own validation
gate nevertheless prints `UNSOUND` at width 4: all four mismatches
come from the **empty input cube** `u=0`, which is not an integral
cube with any active direction. This identifies a validation-gate
edge case, not a proved fault in nonempty full-width cube claims.
The [source-pinned audit report](../results/krakken_divprop_gate_audit_validated.json)
records the counts and exact copied-source hashes. It is **not** a
full-round soundness certificate.

The conservative model has the opposite, expected looseness too:
for the 3-bit adder with active input bits `x0,x1`, output bit zero
is exactly balanced over the four-point cube because it ignores
`x1`, yet the MILP admits a division trail to that output bit.
Thus **MILP reachable does not imply a real nonzero cube sum**.
The archived README's statement that `K=0` proves no integral
distinguisher survives is too strong; it means only that the model
certified no balanced bit in the tested output range. A future
division-property campaign must report `infeasible`, `reachable`,
and `unknown` separately and cross-check every positive balance
certificate against the C permutation when cube size permits.

## Complete valid-message byte-cube integral class and first-order dependency

The [targeted division-property runner](../scripts/krakken_divprop_targeted.py)
was built with the archived kit's 661 exact S-box facets. It accepts
optional SCIP time and memory limits; its defaults have **no time
limit**. A bounded control run on the known 14-cube balance at
round-one state bit 11 built a model with 218,614 variables and
98,575 constraints in 10.85 seconds, then returned `timelimit`
after 45 seconds. The [report](../results/krakken_divprop_r1_bit11_validated.json)
records `interpretation=unknown`. Since even this known-positive
control was not certified promptly, the same model was not extended
to two rounds here. Solver difficulty is not a security claim.

The exact-C path instead exhausted the **complete one-byte
coordinate-cube position class**. For each `p=0,...,158`, the
[producer](../scripts/krakken_byte_cube_allpositions.py) varied byte `p` through
all 256 values at deterministic valid base messages and saved both
full-state XOR sums. It continued until the bitwise OR of the
round-two sums covered every one of 2048 output bits. All 159
positions closed with at most 18 bases each, 1,946 cubes total. The
[certificate](../results/krakken_byte_cube_all159_validated.json) contains
every base and sum. An [independent original-C auditor](../scripts/krakken_byte_cube_allpositions_audit.py)
replayed all 498,176 valid-message cube vertices, running both one
and two complete rounds for 996,352 original-C evaluations. Its
[report](../results/krakken_byte_cube_all159_audit_validated.json) matched
every 2048-bit sum. The saved finite witnesses prove that **no
state-output coordinate is a universal round-two balance for any
one-byte message-coordinate cube family**. They do not exclude
balances for specific bases, other cubes, or non-coordinate masks.

Among these same finite contexts, 113 of 159 positions still had
some common round-one balanced bits because the search stopped at
round-two closure. Those residual bits are *unclassified*, not
proved integrals. The first-order dependency class points in a
different direction: the [producer](../scripts/krakken_bit_dependency_all.py)
found finite valid-message witnesses for **every** message-bit /
state-bit influence pair at both one and two rounds. There are
`1272 * 2048 = 2,605,056` such pairs per round count. The
[certificate](../results/krakken_bit_dependency_all1272_validated.json) uses
16,946 base contexts, at most 21 per input bit. An
[independent original-C audit](../scripts/krakken_bit_dependency_all_audit.py)
replayed all 67,784 evaluations and confirmed complete coverage at
both rounds in its [report](../results/krakken_bit_dependency_all1272_audit_validated.json).
Thus first-order influence is already complete after round one; this
class **does not** exhibit a round-two-only threshold.

The stronger [byte-cube rank search](../scripts/krakken_byte_cube_rank.py)
then fixed message byte 0 and retained only linearly independent
round-two full-state cube sums. It reached rank **2048/2048** after
2,050 valid base cubes, with 2,048 independent sums recorded in the
[certificate](../results/krakken_byte_cube_rank_p0_validated.json). The
[independent original-C rank audit](../scripts/krakken_byte_cube_rank_audit.py)
replayed all 2,048 selected cubes, checked both saved full-state
sums, and eliminated with the opposite bit order; its
[report](../results/krakken_byte_cube_rank_p0_audit_validated.json) again gives
rank 2048. That is a deterministic exclusion of **every nonzero
linear output mask** as a universal round-two balance for this
fixed byte-0 cube family. The same saved bases span rank 2041 at
round one. The seven-dimensional orthogonal space for these sampled
round-one sums is not automatically a space of universal integrals;
it needs an algebraic proof or counterexamples from more bases.

## Fresh exact division-property model: byte-0 balances close at round two

The [new model](../scripts/krakken_division_exact_byte0.py) uses no archived
division-property kit or SCIP. It treats the 256-point first-message-
byte cube's XOR sum as the coefficient of the full eight-variable
monomial. The first-round prefix maps the eight cube directions
linearly into 128 serial-Chi two-byte cells. For each cell, the script
computes the eighth derivative of its **exact** 16-bit truth table
at all 65,536 possible local base values. These local derivative
sets are then propagated through the 32 exact-affine output bits of
XRBD → Pressure → constants → shuffle. Their constraints have rank
25 in 32 output-mask dimensions, giving seven independent masks
that balance for **every valid base message** after one round.

The previously saved 2,048 original-C byte-0 cube sums have rank
2041 after round one. Thus the seven constructed masks exhaust the
entire 2,048-bit universal linear-mask balance space; they are not
merely examples. The same cubes have rank 2048 after round two, so
that space becomes zero. In notation, `dim U_1=7` and `dim U_2=0`.
The [new certificate](../results/krakken_division_exact_byte0_validated.json)
records the seven masks (including single output bit 907) and all
128 local direction sets. An
[independent audit](../results/krakken_division_exact_byte0_audit_validated.json)
recomputed the local derivatives, checked 384 local Chi cases against
original C, and matched the finite ranks using opposite pivots.
The [full original-C cube audit](../results/krakken_byte_cube_rank_p0_audit_validated.json)
had already replayed all selected base cubes. This is an exact
round-one-to-round-two loss of universal linear-mask integrals for
the defined hash-reachable byte-0 cube family; it is not a global
all-cube claim.

## Subspace-trail pilot: affine hulls of all 159 valid-message byte cubes

This uses the affine-hull view of
[subspace trails](https://eprint.iacr.org/2016/592.pdf), while fixing
Krakken's actual padded hash-message domain.

The [new original-C enumerator](../source/krakken_subspace_byte_hull.c)
computes the affine hull of the 256 states from each zero-base
message-byte coordinate cube at ten checkpoints across rounds one
and two. The [source-pinned report](../results/krakken_subspace_byte_hull_validated.json)
has the **same rank vector for every one of 159 positions**:

| Checkpoint | Affine-hull dimension |
|---|---:|
| pre-Chi1 | 8 |
| post-Chi1 and post-XRBD1 | 255 |
| after Pressure1 and complete round 1 | 255 |
| every measured checkpoint in round 2 | 255 |

The maximum possible affine dimension of 256 points is 255. An
[independent original-C audit](../results/krakken_subspace_byte_hull_audit_validated.json)
replayed all 40,704 valid messages in reverse byte-value order,
used byte value 255 as affine origin rather than zero, and used
lowest-first rather than highest-first GF(2) pivots. It reproduced
rank 255 after Chi1 and after complete rounds one and two at every
position. Thus the **first Chi layer already destroys low-dimensional
affine-hull closure** for this defined family: no trail that maps
every coset of one of these input byte subspaces to output affine
spaces of dimension at most 254 can hold. This does not exclude
selected special cosets, 255-dimensional trails, or other structured
input subspaces. A random permutation would normally give rank 255
for 256 distinct outputs, so the result is a class exclusion rather
than evidence of a numerical distinguishing advantage.

## Adversarial subspaces: Theta cancellation survives Chi1, not Pressure1

The [adversarial subspace search](../scripts/krakken_subspace_adversarial.py)
constructed 27 **valid-message eight-dimensional subspaces**:
ten equal-byte Theta-cancelling pairs, ten byte pairs chosen for
sparse pre-Chi serial-Chi support, four four-byte Theta-cancelling
groups, and three ordinary byte controls. The score was computed
from the actual source-pinned rate-to-pre-Chi linear map. Six cosets
per subspace—zero, all-`ff`, alternating, sparse external, and two
seeded random bases—gave 162 exact original-C jobs. The
[report](../results/krakken_subspace_adversarial_validated.json) saves every
base, eight message directions, rank at ten checkpoints, and active
byte-support totals. Across these jobs, the lowest post-Chi1 hull
rank was **238** for the Theta pair in message bytes **40 and 56**;
all 162 reached rank 255 after Pressure1. The sparse-pre-Chi pairs,
four-byte Theta groups, and ordinary controls all had post-Chi1
rank 255 in the selected cosets. These 162 jobs are a search screen,
not a complete claim about every coset of every tested subspace.

The promising pair was then **closed exactly** over its entire
two-byte message plane. For each `delta=0,...,255`, enumerate all
`(m[40],m[56])=(delta XOR t,t)` with `t=0,...,255` and all other
message bytes zero. Their equal varying directions cancel Theta's
column parity. The [XRBD-on certificate](../results/krakken_subspace_theta_pair_cosets_validated.json)
gives post-Chi1 rank histogram `238:2, 246:2, 251:1, 252:11,
253:94, 254:146`. XRBD leaves these ranks unchanged, as any
invertible linear layer must. **Pressure1 raises all 256 cosets to
rank 255**, retained after complete rounds one and two. The
[independent original-C audit](../results/krakken_subspace_theta_pair_cosets_audit_validated.json)
replayed all 65,536 messages with an opposite pivot order and
different affine origin, matching ranks and support totals.

The [XRBD-off control](../results/krakken_subspace_theta_pair_noxrbd_validated.json)
and [independent audit](../results/krakken_subspace_theta_pair_noxrbd_audit_validated.json)
also cover every message in that plane. Pressure1 gives rank 255
for all 256 cosets **without XRBD** as well. XRBD is therefore not
the cause of this family's affine-rank escape. It changes a
different metric: differences across each cube have about **44
active bytes on average post-Chi1**, and nearly **255 active bytes
post-XRBD1**. The layer responsible for rank growth and the layer
responsible for byte-support spread differ here.

This is a deliberately adversarial, hash-reachable subspace family
whose low-dimensional post-Chi1 closure is real, not an artifact of
ordinary byte cubes. Its low-rank closure ends **within round one**
at Pressure. The theorem does not cover other message planes,
cosets with additional nonzero message bytes, or 255-dimensional
trails.

## Fresh-source rebound-style inbound and outbound pass

This pass used only the **current** `krakken.c` and `krakken.h` to
derive and run the analysis; archived rebound scripts and their
conclusions were not inspected or reused. The inbound is an
**unrestricted internal pre-Chi1 state** construction. A first-block
hash-reachability test is reported separately below.

**Exact component constraints.** A serial-Chi cell maps two bytes
as `A=S(a XOR b), B=S(b XOR A)`. A diagonal input difference `(d,d)`
cancels at the first S-box and gives a prescribed second-output
difference `eps` for exactly `256*DDT_S(d,eps)` of 65,536 local
bases. The current S-box has maximum nontrivial DDT entry 4, so a
specified transition in this family has uniform-local-base
probability at most `1/64`. The chosen `(d,eps)=(101,1)` reaches
that bound, yielding **1,024 matched bases**. Exhaustive local
enumeration confirms the count. Across all 128 second-output-byte
sites and 255 nonzero `eps` values, original-C XRBD sends the
single post-Chi active byte to **all 32 lanes and 48–196 active
bytes**. The [producer](../scripts/krakken_rebound_inbound.py),
[certificate](../results/krakken_rebound_inbound_validated.json),
[independent replay](../scripts/krakken_rebound_inbound_audit.py), and
[audit report](../results/krakken_rebound_inbound_audit_validated.json) cover
the complete 32,640-case support class. These are proved
component/support statements, not a two-round rebound bound.

The backward outbound was computed independently from the current
linear prefix. Its 2048-bit basis matrix has full rank 2048, so
every pre-Chi1 one-cell difference has one unrestricted permutation
input difference. Across all 128 sites and all 255 nonzero diagonal
byte values, the inverse-prefix difference has **all 32 lanes and
40–180 active bytes**. The selected `(site,d)=((0,0,0),101)` case
has **116 active bytes** at the permutation input. The
[backward certificate](../results/krakken_rebound_backward_validated.json)
and [independent inverse/C replay](../results/krakken_rebound_backward_audit_validated.json)
cover all 32,640 cases. The producer also pulls back one concrete
matched base pair and confirms its complete first round against
the original C permutation, establishing an unrestricted-state
witness rather than only an internal difference pattern.

**Finite exhaustive outbound class.** The `(101,1)` transition at
serial-Chi site `(0,0,0)` attains XRBD's 48-byte minimum in this
class. With every other pre-Chi1 byte fixed to zero, all **1,024**
matched local bases were propagated through XRBD, Pressure,
constants, shuffle, the next linear prefix, and Chi2. The
minimum second-round activity was **251 of 256 ABYSSAL S-box
calls** (median 255). This is exact for that fixed background.
Seven additional fixed backgrounds—`ff`, alternating, one sparse,
and four seeded random states—were each exhausted over the same
1,024 local matches. Across these **8,192** pair continuations,
the smallest observed Chi2 activity was **250**. The
[producer](../scripts/krakken_rebound_outbound.py) and
[report](../results/krakken_rebound_outbound_validated.json) store histograms,
backgrounds, per-background minima, and exact witness data; an
[independent original-C replay](../results/krakken_rebound_outbound_audit_validated.json)
re-enumerated all eight sets in a different order and matched the
histograms and witnesses. The seven nonzero backgrounds were
selected, so their combined minimum is **not** a global lower
bound over arbitrary internal states. For the eight best saved
Chi2 witnesses, an [original-C extension](../results/krakken_rebound_extend_validated.json)
found Chi3 activities from **254 to 256**. These are eight concrete
continuations, not a complete third-round search.

**First-block hash restriction.** Independently deriving the
1272-column message-to-pre-Chi1 linear map from the current C
prefix showed rank `1272/1272` after projecting outside **each**
of the 128 serial-Chi input cells. Thus no nonzero first-block
rate-only input difference can produce this one-cell inbound
starting difference. The [certificate](../results/krakken_rebound_rate_gate_validated.json)
and [opposite-pivot C audit](../results/krakken_rebound_rate_gate_audit_validated.json)
cover all cells. This does not exclude multi-cell hash-reachable
inbound conditions or later absorb blocks.

**Solver status.** No SCIP or Z3 job was used in this pass, so
there are no solver unknowns or timeouts to interpret. The open
rebound question is whether a *multi-cell, hash-reachable*
inbound can simultaneously match through Chi and preserve a useful
outbound structure across the surrounding layers.

## Fresh current-source serial-Chi boomerang continuation (September 25, 2026)

This pass started from the current `krakken.c` and `krakken.h` only.
It did not reuse archived boomerang scripts, handoff statements, or
earlier quartet conclusions. The exact source SHA-256 values are in
the new JSON certificates. The local relation follows directly from
the current serial-Chi equations: diagonal effective input difference
`(d,d)` fixes the first output byte, and a common first-output-byte
translation `gamma` gives a perfect BCT switch for every nonzero
`d,gamma` and every local base.

The [fresh producer](../scripts/krakken_boomerang_fresh.py) used the original C
functions for Chi, XRBD, Pressure, constants, shuffle, and the next
round's prefix and Chi. Its 64,000-case deterministic grid covered
all 128 serial-Chi byte sites, all 25 combinations of five nonzero
`d` values and five nonzero `gamma` values,
four local `(u,v)` bases, and five full-state post-Chi1 backgrounds.
All four-state rectangles survived XRBD, as linearity requires. **65**
remained rectangles after Pressure and through the round-2 prefix;
none remained one after Chi2. The [independent Python replay](../results/krakken_boomerang_fresh_audit.json)
matched the full original-C Pressure defect histogram and all 65
Pressure-surviving Chi2 continuations.
This grid is a finite screen, not a complete search of all differences
or backgrounds.

The strongest complete finite class fixes one site `y=p=j=0`,
`d=gamma=128`, and zeroes every other post-Chi1 byte, then exhausts
all `2^16=65,536` local output bases `(u,v)`. Exactly **1,300**
quartets reach Chi2 with equal horizontal input differences; **none**
of those 1,300 has equal vertical output differences after Chi2.
The [original-C certificate](../results/krakken_boomerang_cell_exhaust.json) and
[independent Python audit](../results/krakken_boomerang_cell_audit.json) agree
on the entire Pressure defect histogram, all 1,300 survivors, and
zero Chi2 BCT survivors. This is an exact defined-class exclusion.
It also shows that Pressure can preserve a meaningful subset of the
local rectangles, so “the quartet always dies at Pressure” is false.

The current-C prefix has rank **2048/2048**, so every local quartet
can be pulled back to unrestricted round-start states. The
[embedding certificate](../results/krakken_boomerang_embed.json) stores one
four-state witness and checks it through the original-C complete-round
entry point; it reaches Chi2 as a rectangle and leaves Chi2 with a
1,017-bit defect. The hash restriction is different: outside each
one-cell pre-Chi1 support, the first-block 1272-bit rate-image map
has rank **1272/1272**. The [dual-pivot rank certificate](../results/krakken_boomerang_rate_gate.json)
therefore excludes all one-cell inbounds for nonzero first-block valid
159-byte message differences. It does not exclude multi-cell or later
absorb-block boomerangs.

To reproduce the certificates from the source files in this directory,
run these scripts in order with `/home/user/venv/krakken/bin/python`:
`krakken_boomerang_fresh.py`, `krakken_boomerang_fresh_audit.py`,
`krakken_boomerang_cell_exhaust.py`, `krakken_boomerang_cell_audit.py`,
`krakken_boomerang_rate_gate.py`, and `krakken_boomerang_embed.py`.
The scripts have no solver time limit because they use exact enumeration
and GF(2) elimination, not a solver.

### Follow-up: exact local Chi2 obstruction for the Pressure survivors

The 1,300 Pressure survivors were not merely unlucky at their
particular Chi2 base values. For each survivor, the two full-state
Chi2 input differences were decomposed into the 128 independent
two-byte serial-Chi cells. All 128 cells had both differences active.
At least one cell in **every** survivor had **zero** four-point
rectangle solutions across the entire 65,536-value local base domain.
Thus the quartet cannot be repaired by changing that Chi2 cell's base
while keeping its input difference pair fixed.

The [current-C producer](../scripts/krakken_boomerang_chi2_obstruction.py)
builds the 65,536-entry local map using the original-C `chi_scalar`;
its [certificate](../results/krakken_boomerang_chi2_obstruction.json) gives one
zero-count cell per survivor. It evaluated 323 distinct local mask
pairs while finding those obstructions; 319 had zero count. The
[independent Python/NumPy audit](../results/krakken_boomerang_chi2_obstruction_audit.json)
recomputed every count and every full-layer input difference. This
sharpens the fixed-class Chi2 exclusion, but says nothing universal
about backgrounds that produce different Pressure output differences.

Three further complete classes at the same site and zero post-Chi1
background were then exhausted: `(d,gamma)=(255,128), (255,1),
(128,1)`. Their 196,608 local bases yielded **1,356**, **1,196**,
and **932** Pressure rectangles, respectively. None satisfied the
Chi2 BCT condition. The [original-C suite](../results/krakken_boomerang_cell_suite.json)
and [independent Python audit](../results/krakken_boomerang_cell_suite_audit.json)
agree on every Pressure defect histogram and all Chi2 continuations.
The [suite local-obstruction certificate](../results/krakken_boomerang_cell_suite_obstruction.json)
finds a zero-solution Chi2 cell for each of those 3,484 survivors;
the independent audit recomputes the exact local counts. The
[combined verifier](../results/krakken_boomerang_four_class_verified.json)
records the four-class total: **262,144** bases, **4,784** Pressure
survivors, **zero** Chi2 BCT survivors, and a base-independent
obstructing cell for each survivor. This is a theorem for four named
difference classes, not an exclusion of the other 65,021 nonzero
`(d,gamma)` pairs, other backgrounds, or multi-cell inbounds.
For reproduction, run `krakken_boomerang_chi2_obstruction.py`,
`krakken_boomerang_chi2_obstruction_audit.py`,
`krakken_boomerang_cell_suite.py`,
`krakken_boomerang_cell_suite_obstruction.py`,
`krakken_boomerang_cell_suite_audit.py`, and
`krakken_boomerang_four_class_verify.py` in that order.

### First-block hash reachability: exact five-call minimum

The current-source [support counter](../scripts/krakken_boomerang_rate_support.py)
quotients the 2048-bit pre-Chi1 state by the 1272-bit valid-message
rate image. It exhausts every support comprising up to four complete
serial-Chi input cells. All supports of size one, two, or three have
full quotient ranks `16,32,48`. Among **10,668,000** four-cell
supports, exactly **six** have rank `63/64`; all others have full rank.
The [independent audit](../results/krakken_boomerang_rate_support_audit.json)
reimplements the prefix in Python and repeats the complete support
enumeration with the opposite GF(2) pivot order. It found the same
six exceptions.

The [message-difference construction](../results/krakken_boomerang_four_cell_witness.json)
solves the rate map at each exception and gives six actual 159-byte
message differences with exactly four active pre-Chi1 cells. Their
four effective byte input differences are rotations of
`(110,4), (0,90), (5,32), (16,3)`. Exact S-box DDT counts for
silencing the second S-box call are `0,2,0,2`, so these four-cell
differences need at least **six** active Chi1 calls. All differences
using five or more cells need at least five calls. This proves the
global first-block lower bound `A1>=5`.

The [optimized valid-message bases](../results/krakken_boomerang_four_cell_optimum.json)
attain **A1=6** on all six difference lines. Their
[independent audit](../results/krakken_boomerang_four_cell_optimum_audit.json)
replays the Python prefix/Chi and original-C full hash digests.
Original-C [outbound traces](../results/krakken_boomerang_four_cell_outbound.json)
and [independent replay](../results/krakken_boomerang_four_cell_outbound_audit.json)
show those six sparse first-round witnesses becoming **242–247
active bytes immediately after XRBD1** and **253–255 active Chi2
calls**. These are concrete witness trajectories, not a universal
round-two lower bound.

The lower bound five is sharp. A restricted search of reachable
five-cell supports found a [valid 159-byte message pair](../results/krakken_five_cell_candidates.json)
with exactly one active Chi1 byte-S-box call in each of five cells.
Its [independent Python/original-C replay](../results/krakken_five_cell_witness_audit.json)
confirms **A1=5**, hence the exact minimum over all nonzero valid
first-block message differences is **five**. This witness has
**216 active bytes after XRBD1 and A2=255**; neither number is a
universal second-round lower bound. The restricted search is a
witness-finding procedure; completeness of that five-cell search is
not needed for the global minimum theorem.

For the witness's fixed XOR input difference, the five controlling
first-S-box input bytes are jointly uniform (projection rank 40/40),
and each has two favorable byte bases out of 256. Thus the exact
probability of the activity event **A1=5 is 2^-35** under a uniform
valid 159-byte base message. The [source-pinned count](../results/krakken_five_cell_probability.json)
and [independent audit](../results/krakken_five_cell_probability_audit.json)
verify this value. It is an activity-event probability for one fixed
difference, not a specified full-round trail probability.
To reproduce this hash-level theorem, run
`krakken_boomerang_rate_support.py`,
`krakken_boomerang_rate_support_audit.py`,
`krakken_boomerang_four_cell_witness.py`,
`krakken_boomerang_four_cell_optimum.py`,
`krakken_boomerang_four_cell_optimum_audit.py`,
`krakken_boomerang_four_cell_outbound.py`, and
`krakken_boomerang_four_cell_outbound_audit.py` in that order using
`/home/user/venv/krakken/bin/python`. The four-cell rank enumeration
takes a few minutes and runs as one foreground process.
For the five-call witness and probability, run
`krakken_five_cell_restricted.py`, `krakken_five_cell_candidates.py`,
`krakken_five_cell_witness_audit.py`, `krakken_five_cell_probability.py`,
and `krakken_five_cell_probability_audit.py` in that order. The
original-C rank certificate plus five-cell witness suffices to
reproduce the global minimum.

### Fixed five-call hash difference: round-two two-cell exclusion

For the fixed valid-message XOR difference in the `A1=5` witness,
the event `A1=5` forces all five second serial-Chi1 calls inactive.
Because each of the five first input differences is nonzero, this
fixes the **whole post-Chi1 difference** independent of the valid
base message. The [source-pinned rank scan](../results/krakken_sponge_a15_rank_all.json)
then uses exact XRBD, the exact inverse inter-round linear tail, and
Pressure's 32 exact LSB identities. It overapproximates a Chi2 input
difference supported in two cells by allowing **all 32 bits** in
those cells. Every one of the 8,128 cell pairs fails the necessary
LSB equations, so for this fixed message difference and every base
with `A1=5`, **at least three Chi2 cells and at least three Chi2 calls
are active**.

The [independent original-C audit](../results/krakken_sponge_a15_rank_audit.json)
reconstructs the full 2048-bit inverse prefix from C basis columns,
checks 2,048 inverse-tail target columns by C replay, and repeats all
8,128 rank tests using the opposite pivot order. The pair ranks are
at most 29/32 and the fixed syndrome lies outside each span. This
is a conditional fixed-difference theorem, not a global two-round
activity minimum. Reproduce it with
`krakken_sponge_a15_pressure4_scip.py --rank-scan-all` and then
`krakken_sponge_a15_rank_audit.py` using the Krakken venv Python.

The same script can also **build** a tiny exact low-four-bit Pressure
SCIP feasibility model for a selected two-second-call Chi2 endpoint
pair: `--build-pair 0 1` produced 1,040 binary variables and 1,090
constraints. `--solve-pair` has no time limit. The fixed-difference
LSB theorem already excludes every such two-cell endpoint, so a SCIP
solve would be redundant for this particular threshold. It was not
run while the user’s separate all-position search was occupying the
machine. A feasible low-four-bit model would be only a necessary-
condition survivor, not a real hash trail.

### Three fixed five-call hash differences: two-round extension

The selected [155-support five-cell candidate set](../results/krakken_five_cell_candidates.json)
contains three difference lines with local minimum `A1=5`, indexed
`(2,6),(2,9),(21,2)`. For each **fixed** valid-message XOR difference,
`A1=5` fixes the complete post-Chi1 difference for every valid base.
All three events have constructed valid-message witnesses, replayed
through original C, with `A2=256,254,256` respectively.

The [new producer](../scripts/krakken_a15_three_line_gate.py) checks all 128
one-cell and 8,128 two-cell Chi2 pre-input supports per line, allowing
arbitrary 16-bit differences within each cell. Exact Pressure bit-zero
identities exclude every one-cell support and all pairs for the first
two lines. For `(21,2)`, only cell pairs `(10,54)` and `(20,107)` pass
the bit-zero equations, leaving 32 and 256 affine endpoint assignments.
An exhaustive joint low-two-bit check of both Pressure additions
excludes all 288. The [certificate](../results/krakken_a15_three_line_gate.json)
and [independent opposite-pivot/original-C audit](../results/krakken_a15_three_line_gate_audit.json)
therefore prove `A1=5 => A2>=3` for each of these three fixed input
differences. They do not prove that implication for every valid
message difference. Reproduce with the Krakken venv Python by running
`krakken_a15_three_line_gate.py` and then
`krakken_a15_three_line_gate_audit.py` from this directory.

### Fast source-pinned gate for a specified sponge trail

The [specified-trail gate](../scripts/krakken_sponge_trail_gate.py) accepts a
159-byte valid first-block message XOR difference and proposed
256-byte post-Chi1 and pre-Chi2 differences in a JSON file. It
computes the rate-to-pre-Chi1 difference with original C, checks
every serial-Chi1 local transition against the source S-box DDT,
propagates the proposed post-Chi1 difference through original-C
XRBD, and pulls the proposed pre-Chi2 difference back through the
linear inter-round tail. For each of the 16 Pressure chains it then
tests exact low-bit joint-addition feasibility, by default through
four bits and optionally through six. `IMPOSSIBLE` gives an explicit
local DDT or Pressure obstruction. `UNKNOWN` means only that these
necessary conditions passed; full 64-bit Pressure and rate-conditioned
base feasibility remain open. This checks a **specified intermediate
trail**, not an arbitrary endpoint differential hull.

Run `krakken_sponge_trail_gate.py --make-fixture --bits 4` to create
the [C-derived valid trail fixture](../results/krakken_sponge_trail_fixture.json)
and confirm that it is not falsely excluded. The
[fixture check](../results/krakken_sponge_trail_fixture_check.json) reports
`UNKNOWN`. Altering the first bit of that fixture's proposed
pre-Chi2 difference gives an `IMPOSSIBLE` Pressure certificate at
low bit 3 (column 0, `b/d` branch). For a new specified trail, supply
the same three hexadecimal difference fields in a JSON file and run
`krakken_sponge_trail_gate.py --trail path/to/trail.json --bits 4`.

### Global first-block two-round activity model

The [global SCIP script](../scripts/krakken_sponge_two_round_scip.py) answers a
different question from the specified-trail gate. SCIP chooses all
1,272 message-difference bits for a nonzero valid 159-byte first
block and all intermediate differences. It minimizes `A1+A2`, or
`--max-active K` asks whether **any** such two-round trail has total
activity at most `K`. The 159th-byte `0x86` padding and initial
96-byte capacity have zero XOR difference. Linear prefix, XRBD, and
inter-round maps are extracted from current `krakken.c` basis calls.

The model is a **sound overapproximation**: serial Chi enforces
bijection-based activity equivalence but not the full S-box DDT;
Pressure enforces sound low-bit carry-difference constraints with
`--pressure-prefix-bits` and leaves its higher output bits free.
Consequently, a SCIP `INFEASIBLE` result at threshold `K` certifies
the real first-block bound `A1+A2>=K+1`. A feasible solution or an
optimal objective value in this relaxed model does **not** give a real
trail or an exact real minimum. There is no script time limit.

`--check-source` passed linearity, C Chi/S-box, C Pressure, and
carry-difference checks. `--build-only --pressure-prefix-bits 1`
built 18,457 binary variables and 23,765 constraints. The default
four-bit model built 18,553 variables and 24,053 constraints. A
baseline `--max-active 5` SCIP run returned `INFEASIBLE` in presolve,
confirming the already-known `A1>=5` and nonzero `A2>=1` total floor
of six. This is **not a new two-round lower bound**; thresholds six
and above remain to be solved. The user already has a separate
sequential all-position job running, so no long solve was started.

The script also accepts `--fix-a1 5 --fix-a2 1` as **explicit SCIP
equalities**, with no fixed message difference. Under the proved
global floors `A1>=5` and `A2>=1`, this class contains every possible
real total-six trail. Therefore `INFEASIBLE` for this fixed pair
certifies the global bound `A1+A2>=7`; for other fixed pairs the
result excludes only that pair. This mode is a feasibility test, so
omit `--minimize`. The default four-bit fixed-pair model built
successfully with 18,553 binary variables and 24,054 constraints;
the actual `[5,1]` solve has not been completed here.

### Exact probabilities on all six exceptional four-cell rate differences

The [source-pinned exact counter](../scripts/krakken_four_cell_probability.py)
and [independent C-S-box audit](../scripts/krakken_four_cell_probability_audit.py)
close a new fixed-input class. For each of the six valid first-block
message differences whose pre-Chi1 input is confined to four cells,
the four selected two-byte base inputs have C-derived projection rank
`64/64`. Exact local `2^16` enumerations give the activity law
`A1=6+Binomial(2,127/128)`. Hence the minimum six calls occurs with
probability `2^-14` under a uniform valid base for any one fixed
difference. The exact maximum probability of **any one specified
post-Chi1 difference** is `2^-38`, attained for every line; conditioned
on `A1=6`, its sharp maximum is `2^-24`. The
[certificate](../results/krakken_four_cell_probability.json) contains six
valid-message attaining pairs, all replayed by the original C.

The follow-up [Pressure bit-zero screen](../scripts/krakken_four_cell_a16_lsb_screen.py)
finds, for **each** line, a valid-message `A1=6` pair whose post-Chi1
difference satisfies the 32 exact Pressure bit-zero equations with
**some hypothetical one-cell Chi2 input support**. These are
necessary-condition survivors, not full Pressure transitions or
`A2=1` trails. Original-C replay of those same six valid pairs gives
actual `A2=255,255,256,256,254,255`. Thus bit-zero support ranks
alone cannot exclude a one-cell endpoint for this class; stronger
carry or full-transition constraints are needed for a round-two
theorem. The [screen certificate](../results/krakken_four_cell_a16_lsb_screen.json)
stores each valid pair, syndrome, and hypothetical support.

### Why the targeted A1 search missed 11–23

The user's exact searcher is
`/home/user/Downloads/krakken_alignment_target.c`, built against
`krakken.c/h` files with the **same SHA-256 hashes** as this workspace.
Its ten-million-trial target-17 output has 239 observed A1 bins and
misses exactly `11..23`. Inspection of the source shows that it seeds
from an `A1=5` pair, normally makes one to four individual bit-flip
operations, and retains only one best-A2 parent per observed A1 bin.
Those choices favor a local search basin; the bin count does not
measure the global activity spectrum.

The [exhaustive one-bit seed screen](../scripts/krakken_alignment_seed_onebit_audit.py)
checked **all 2,544** one-sided one-bit message mutations of that
five-call seed under the current original-C prefix. Their A1 values
range from `62` to `113`; none lies in `11..23`. Common-base mutations preserve
the five-cell input difference and can change only its five second
calls, so they stay in `5..10`. This gives a concrete mechanism for
the heuristic's low-activity gap: the desired middle counts require
coordinated changes to the message-difference geometry, while a
single geometry-bit change jumps far away. The
[screen report](../results/krakken_alignment_seed_onebit.json) gives the exact
histogram. It does not characterize every multi-bit move the heuristic
can make.

The [constructive spectrum check](../results/krakken_a1_spectrum_5_26.json)
settles the actual mathematical question in the opposite direction:
valid message pairs attain **every A1 from 5 through 26**, including
all of `11..23`. They are built from XORs of source-certified sparse
rate differences, solved through full-rank pre-Chi projections, and
replayed independently through original C. The
[independent audit](../results/krakken_a1_spectrum_5_26_audit.json) reproduces
all 22 activity values. The observed A2 values of these pairs are
`253..256`; that is a witness observation, not a universal bound.
As a separate implementation check, the user's exact
`krakken_alignment_target` binary was given only each constructed
`A1=17,18,19,20` pair as its seed with `--trials 0`; it reported
**FOUND** at all four targets with the same A2 values. The
[cross-check script](../scripts/krakken_alignment_target_crosscheck.py) and
[result](../results/krakken_alignment_target_crosscheck.json) preserve the binary
hash and replay. This confirms the heuristic's evaluator accepts the
witnesses; the earlier non-find arose from its search path.
### Unified unrestricted [1,2] two-call necessary-condition model (2026-09-26)

The [new union checker](../scripts/krakken_12_union2_z3.py) chooses a nonzero
post-Chi1 byte and **two distinct Chi2 calls from all 256 calls** in one
symbolic job per starting byte position. Its second-round endpoint
parameterization includes AA, BB, both mixed orders, and two calls
sharing a spatial two-byte pair. Original-C-derived columns implement
XRBD and the inverse linear inter-round tail. The two Pressure additions
are modeled jointly and exactly in their low `k<=17` bits. Chi2 DDT
compatibility and upper Pressure bits are omitted, making this a sound
necessary-condition relaxation: only `unsat` excludes real trails.

The `--sites I J` mode checks a named call pair (`0..127` denotes the
first serial-Chi call, `128..255` the second). It agrees with the
independent BB per-site model on an excluded site and on its relaxed
survivor at start position 20, cells 0 and 99: the latter is `sat`,
not a trail witness. A small `k=1` whole-position pilot was `sat` in
3.79 s; a whole-position `k=3` pilot did not finish within the
researcher's 20-second external limit. The user-facing script has no
solver timeout. No position-wide UNSAT result is claimed yet.

After the BB class was closed, the sequential, resumable union campaign
defaults to the remaining AA/AB/BA shapes. Run it with:

```bash
/home/user/venv/krakken/bin/python -u /home/user/sol/krakken_12_union2_z3.py --all-positions --prefix-bits 3 --output-dir /home/user/sol/krakken_12_union2_results 2>&1 | tee /home/user/sol/krakken_12_union2_run.log
```

Each finished position gets its own JSON report, and
`summary_k3_remaining.json` is updated after each one.
`all_256_positions_proved_unsat` becomes true only if every remaining
shape is excluded at every position. A `sat` or `unknown` position
remains open; neither may be relabeled UNSAT. `--include-bb` restores
the original full union for auditing.

An initial prototype reversed the byte-4 pairing for the second call.
That prototype's result files are invalid and are not evidence. The
corrected checker uses separate first-call and second-call basis
columns; its cache filenames carry the `v2` marker. The existing
independent BB campaign and spatial-pair LSB pilot use the correct
pairing and are unaffected. In the spatial-pair pilot, a B call at
byte `j+4` shares the pair with an A call at byte `j`; the unified
checker labels B by its actual call byte.

### BB `[1,2]` three-bit survivors resolved (2026-09-27)

The completed [256-position three-bit summary](../results/krakken_12_joint3_all_positions_summary.json)
records 451,718 additional UNSAT site cases, 946 `sat_relaxed`, zero
unknown, and no pending cases. The [resumable refinement](../scripts/krakken_12_refine_sat.py)
selected exactly those 946 SAT records, rebuilt the C-derived columns,
and increased the exact joint low-bit Pressure width until exclusion.
Its [report](../results/krakken_12_sat_refinement.json) gives 914 UNSAT at four
bits and 32 UNSAT at five bits. An [independent original-C
audit](../scripts/krakken_12_refine_sat_audit.py) rebuilt the target columns and
low-bit equations separately, checked 100 full-width C Pressure
transitions, and reconfirmed all 946 UNSAT in its
[report](../results/krakken_12_sat_refinement_audit.json).

The complete distinct-second-branch Chi2 site accounting is now
`1,628,104 + 451,718 + 914 + 32 = 2,080,768`, with no BB survivor.
This is a computationally proved *defined-class exclusion*, not a
global `[1,2]` theorem: AA, AB/BA, and same-spatial-pair cases remain.
The 451,718 three-bit UNSAT records are complete and source-pinned but
have not been independently re-solved one by one; that validation
boundary is explicit in the [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md).

### Split-site search for the remaining `[1,2]` shapes (2026-09-27)

The first [symbolic all-shape union](../scripts/krakken_12_union2_z3.py) took
14,602.92 seconds at start position 0 and found only relaxed SAT,
so it is not a practical campaign format. The new
[split-site worker](../scripts/krakken_12_remaining_split.py) enumerates `AA`,
`AB`, `BA`, and `same` spatial-pair modes separately. It applies the
exact Pressure bit-zero rank test before one low-bit Z3 instance per
surviving site, caches source-derived C columns, runs a single solver
at a time, and saves resumable per-position JSON. Its solver has no
timeout. A relaxed SAT remains unresolved.

For start position 0, the complete 128-site `same` slice had 3
bit-zero exclusions and 125 additional three-bit UNSAT results. In
30-site pilots, AA had 6 bit-zero plus 24 three-bit exclusions, AB
had 12 plus 18, and BA had 6 plus 24. An AA timing sample processed
roughly 900 sites in one minute and found one relaxed SAT. These are
finite checks of named site cases, not a complete class theorem;
the timing varies with position and site.

The user then completed the full AA start-position-000 slice:
1,462 bit-zero exclusions, 6,664 three-bit exclusions, and two
relaxed SAT sites (indices 847 and 7924). The
[single-position refinement](../scripts/krakken_12_refine_position.py) excluded
both at four bits in its [report](../results/krakken_12_aa_pos000_refinement.json),
closing all 8,128 AA sites at **this one start position**. Other AA
start positions remain to be scanned.

The next AA slice, start position 001, gave 1,051 bit-zero exclusions,
7,072 three-bit exclusions, and five relaxed SAT sites. All five were
excluded at four bits in
[the position-001 refinement](../results/krakken_12_aa_pos001_refinement.json),
so both AA start positions 000 and 001 are closed individually.

AA positions 002–005 were then completed with **no** relaxed survivors:
position 002 had 1,834 bit-zero and 6,294 three-bit exclusions;
003 had 1,726 and 6,402; 004 had 1,444 and 6,684; 005 had 1,754
and 6,374. Thus all 8,128 AA sites at each of positions 000–005
are excluded. The other 250 starting positions remain open.

AA positions 006–015 were completed next. Positions 007, 008, 009,
and 015 had 15, 2, 5, and 15 three-bit relaxed SAT cases; each of
those 37 was excluded at four bits by the single-position refiner.
The other six positions had no relaxed survivors. Across AA positions
000–015, all **130,048** named sites are excluded: 25,160 at bit zero,
104,844 at three bits, and 44 three-bit survivors at four bits.
The remaining 240 start positions are not included in this claim.

AA positions 016–023 were completed and integrity-checked next. The
three-bit screen left 1 relaxed survivor at position 019, 170 at
020, and 495 at 022; all others had none. The position-specific
refiner excluded all 666 survivors, some requiring five bits. Across
AA positions 000–023, all **195,072** named sites are excluded:
37,657 at bit zero, 156,705 at three bits, 598 at four bits, and
112 at five bits. The large three-bit survivor count at position 022
is a relaxation artifact, not a witnessed trail. The remaining 232
AA start positions are open.

AA positions 024–031 were completed and integrity-checked. The
three-bit screen left 1, 170, and 495 relaxed survivors at positions
027, 028, and 030; all 666 were excluded at four or five bits. Across
AA positions 000–031, all **260,096** named sites are excluded:
50,429 at bit zero, 208,291 at three bits, 1,152 at four bits, and
224 at five bits. Survivor sets repeat across some eight-position
offsets but not all: among positions 000–031, only 18 of 24 pairs
separated by eight positions have identical three-bit survivor sets.
No positional symmetry reduction is claimed.

AA positions 032–039 were then completed. The three-bit screen left
2, 5, and 49 relaxed survivors at positions 032, 033, and 039; all
56 were excluded at four or five bits. Across AA positions 000–039,
all **325,120** named sites are excluded: 62,711 at bit zero, 260,977
at three bits, 1,206 at four bits, and 226 at five bits. No claim is
made for the remaining 216 AA start positions.

AA positions 040–047 were completed and checked next. Positions 040,
041, and 047 had 2, 5, and 49 three-bit relaxed survivors; all 56
were excluded at four or five bits. Across AA positions 000–047,
all **390,144** named sites are excluded: 75,208 at bit zero, 313,448
at three bits, 1,260 at four bits, and 228 at five bits. The remaining
208 AA start positions are open.

AA positions 048–055 were completed and source-pin/integrity checked.
Positions 051, 052, and 054 left 1, 170, and 495 three-bit relaxed
survivors, respectively; all 666 were excluded at four or five bits.
Across AA positions 000–055, all **455,168** named sites are excluded:
87,246 at bit zero, 365,768 at three bits, 1,814 at four bits, and
340 at five bits. The remaining 200 AA start positions are open.

AA positions 056–063 were completed and source-pin/integrity checked.
Positions 059, 060, and 062 left 1, 170, and 495 three-bit relaxed
survivors, respectively; all 666 were excluded at four or five bits.
Across AA positions 000–063, all **520,192** named sites are excluded:
99,460 at bit zero, 417,912 at three bits, 2,368 at four bits, and
452 at five bits. The remaining 192 AA start positions are open.

AA positions 064–071 were completed and source-pin/integrity checked.
Positions 064, 065, and 071 left 8, 5, and 13 three-bit relaxed
survivors; all 26 were excluded at four bits. Across AA positions
000–071, all **585,216** named sites are excluded: 111,511 at bit
zero, 470,859 at three bits, 2,394 at four bits, and 452 at five
bits. The remaining 184 AA start positions are open.

AA positions 072–079 were completed and source-pin/integrity checked.
Positions 072, 073, and 079 left 8, 5, and 14 three-bit relaxed
survivors; all 27 were excluded at four bits. Across AA positions
000–079, all **650,240** named sites are excluded: 123,800 at bit
zero, 523,567 at three bits, 2,421 at four bits, and 452 at five
bits. The remaining 176 AA start positions are open.

AA positions 080–087 were completed using the exact low-bit
site-deduplication worker and source-pin/integrity checked. Positions
081, 084, and 086 left 1, 170, and 495 three-bit relaxed survivors;
all 666 were excluded at four or five bits by the existing refiner.
The orbit audit confirmed status and bit-zero-count agreement across
all 8,128 named sites at each of these eight positions. Across AA
positions 000–087, all **715,264** named sites are excluded: 136,213
at bit zero, 575,512 at three bits, 2,975 at four bits, and 564 at
five bits. The remaining 168 AA start positions are open.

AA positions 088–095 were completed with the deduplicating worker and
source-pin/integrity checked. Positions 089, 092, and 094 left 1, 170,
and 495 three-bit relaxed survivors; all 666 were excluded at four or
five bits. The orbit audit confirmed agreement across all named sites.
Across AA positions 000–095, all **780,288** named sites are excluded:
148,888 at bit zero, 627,195 at three bits, 3,529 at four bits, and
676 at five bits. The remaining 160 AA start positions are open.

AA positions 096–103 were completed with the deduplicating worker and
source-pin/integrity checked. Positions 096, 097, and 103 left 8, 5,
and 114 three-bit relaxed survivors; all 127 were excluded, with 123
at four bits and 4 at five bits. The orbit audit confirmed agreement
across all named sites. Across AA positions 000–103, all **845,312**
named sites are excluded: 160,893 at bit zero, 680,087 at three bits,
3,652 at four bits, and 680 at five bits. The remaining 152 AA start
positions are open.

AA positions 104–111 were completed with the kernel worker. All eight
reports had complete named-site coverage, matching current source and
worker hashes, and passed the orbit agreement audit. Positions 104,
105, and 111 left 8, 5, and 115 relaxed survivors; all 128 were
excluded by the original refiner, with 123 at four bits and 5 at five
bits. Across AA positions 000–111, all **910,336** named sites are
excluded: 173,125 at bit zero, 732,751 at three bits, 3,775 at four
bits, and 685 at five bits. The remaining 144 AA start positions are
open.

AA positions 112–119 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 113, 116, and 118 left 1, 170,
and 495 relaxed survivors; all 666 were excluded by the original
refiner, with 554 at four bits and 112 at five bits. Across AA
positions 000–119, all **975,360** named sites are excluded: 185,256
at bit zero, 784,978 at three bits, 4,329 at four bits, and 797 at
five bits. The remaining 136 AA start positions are open.

AA positions 120–127 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 120, 121, 124, and 126 left
14, 1, 170, and 495 relaxed survivors; all 680 were excluded by
the original refiner, with 567 at four bits and 113 at five bits.
Across AA positions 000–127, all **1,040,384** named sites are
excluded: 197,579 at bit zero, 836,999 at three bits, 4,896 at four
bits, and 910 at five bits. This closes exactly half the AA start
positions; the remaining 128 are open.

AA positions 128–135 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 128, 129, 131, and 135 left
2, 75, 1, and 17 relaxed survivors; all 95 were excluded by the
original refiner, with 94 at four bits and 1 at five bits. Across
AA positions 000–135, all **1,105,408** named sites are excluded:
209,900 at bit zero, 889,607 at three bits, 4,990 at four bits,
and 911 at five bits. The remaining 120 AA start positions are open.

AA positions 136–143 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 136, 137, 139, and 143 left
2, 75, 1, and 22 relaxed survivors; all 100 were excluded by the
original refiner, with 99 at four bits and 1 at five bits. Across
AA positions 000–143, all **1,170,432** named sites are excluded:
222,552 at bit zero, 941,879 at three bits, 5,089 at four bits,
and 912 at five bits. The remaining 112 AA start positions are open.

AA positions 144–151 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 145, 147, 148, and 150 left
4, 20, 354, and 495 relaxed survivors; all 873 were excluded by
the original refiner, with 761 at four bits and 112 at five bits.
Across AA positions 000–151, all **1,235,456** named sites are
excluded: 234,724 at bit zero, 993,858 at three bits, 5,850 at four
bits, and 1,024 at five bits. The remaining 104 AA start positions
are open.

AA positions 152–159 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 153, 155, 156, and 158 left
4, 20, 354, and 495 relaxed survivors; all 873 were excluded by
the original refiner, with 761 at four bits and 112 at five bits.
Across AA positions 000–159, all **1,300,480** named sites are
excluded: 247,204 at bit zero, 1,045,529 at three bits, 6,611 at
four bits, and 1,136 at five bits. The remaining 96 AA start positions
are open.

AA positions 160–167 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 160, 161, 163, and 167 left
2, 81, 1, and 57 relaxed survivors; all 141 were excluded by the
original refiner, with 137 at four bits and 4 at five bits. Across
AA positions 000–167, all **1,365,504** named sites are excluded:
259,496 at bit zero, 1,098,120 at three bits, 6,748 at four bits,
and 1,140 at five bits. The remaining 88 AA start positions are open.

AA positions 168–175 were completed with the kernel worker and passed
source/worker-hash checks, complete named-site coverage checks, and
the orbit agreement audit. Positions 168, 169, 171, and 175 left
4, 81, 1, and 63 relaxed survivors; all 149 were excluded by the
original refiner, with 145 at four bits and 4 at five bits. Across
AA positions 000–175, all **1,430,528** named sites are excluded:
272,009 at bit zero, 1,150,482 at three bits, 6,893 at four bits,
and 1,144 at five bits. The remaining 80 AA start positions are open.

### Exact low-bit site-model deduplication (2026-09-29)

The [orbit worker](../scripts/krakken_12_orbit_split.py) groups sites whose
source-derived target-column profiles give identical joint Pressure
low-bit equations. In `AA`, exchanging the two identical A-cell
groups is also allowed. This is an exact equivalence of the stated
low-bit *relaxation*, not a symmetry theorem for complete Krakken
trails. At three bits, the 8,128 named sites per start position reduce
to 5,674 distinct AA models, or 5,802 models for either AB or BA.
The output still records every named site and identifies copied cases
by `equivalent_to_site_index`; copied SAT remains relaxed.

The [audit](../scripts/krakken_12_orbit_audit.py) checked all 80 completed AA
position reports, finding identical status and bit-zero solution
counts inside every equivalence class. A 100-site execution pilot of
the new worker matched the original records. At position 063, summing
the old report's per-site elapsed times gives 548.3 seconds for all
sites versus 421.5 seconds for one representative per class, a
**23.1% estimated site-computation saving** for that position. Actual
wall-clock speed depends on machine load and report writes. This does
not remove the need to scan unresolved positions or refine relaxed
survivors at higher bit widths.
For unstarted positions, the orbit worker can write into the existing
`krakken_12_remaining_split_results` directory; its reports retain the
same site schema and can be read by the existing position refiner.

### Exact bit-zero nullspace elimination (2026-09-29)

The [kernel solver](../scripts/krakken_12_kernel_solver.py) first solves Pressure's
32 homogeneous bit-zero equations by GF(2) elimination. If the byte
difference variables have bit vector x and the bit-zero matrix is M,
it substitutes x=Nz, where the columns of N form a basis of ker(M).
The incremental column-elimination algorithm produces independent
kernel vectors (each has a distinct newest bit) and exactly n-rank(M)
such vectors, so this substitution represents every allowed x exactly
once. It reconstructs and enforces every required nonzero byte, then
imposes the same joint low-k carry equations as the original solver.
Thus the model's SAT/UNSAT meaning is preserved exactly.

The [kernel worker](../scripts/krakken_12_kernel_split.py) combines this reduction
with the existing exact site deduplication for three-bit campaigns.
It emits the existing per-site schema and a worker-source manifest;
the existing position refiner remains applicable. All solvers have
unlimited time. Use it for unstarted batches: reports from different
worker versions have distinct worker hashes and cannot be resumed by
interchanging workers halfway through a position.

The [reproducible audit](../scripts/krakken_12_kernel_audit.py) and its
[report](../results/krakken_12_kernel_audit.json) include 40 exhaustive small
nullspace checks and 184 comparisons with the original solver, covering
AA, AB, BA, same-cell cases, and selected relaxed survivors at widths
3, 4, and 5. All statuses agreed. For 40 random three-bit cases per
mode, original/kernel elapsed seconds were AA 3.969/1.144,
AB 3.621/1.111, BA 2.708/0.798, and same 3.811/1.402. These are
sampled performance measurements, approximately 2.7–3.5 times faster
for these samples; full-campaign speed is not yet measured. A separate
200-site worker pilot matched the old position-095 records, including
a stop/resume check. These checks validate an optimization; no new
site exclusion theorem is inferred from them.

The user completed the full `same` scan over all 256 positions. An
integrity check found all 256 source-pinned reports, exactly 128 site
records in each, with **743** bit-zero exclusions, **32,001** further
three-bit UNSAT results, and **24** relaxed SAT survivors. The
[resumable refinement](../scripts/krakken_12_remaining_refine.py) then excluded
all 24 at four bits in its [report](../results/krakken_12_same_refinement.json).
Thus every one of the `256 × 128 = 32,768` named same-spatial-pair
sites is excluded by a sound necessary-condition model. This is a
complete computational defined-class result for the current C source;
an independent full recount of the 32,001 three-bit UNSAT results has
not been performed. The AA and mixed classes remain open.

## 2026-09-30: coordinated multi-cell boomerang/zero-sum pass

The new [construction report](KRAKKEN_MULTICELL_BOOMERANG.md) gives an
attack-side theorem, `BOOM-MULTI-001`: two correlated post-Chi direction
spaces can be mapped through XRBD to disjoint Pressure-chain units.
All 16 first/second output projection kernels have exact dimension 128,
independently rechecked. Quartets from distinct units preserve zero full-state
XOR at the round input, after Chi/XRBD/Pressure, and after complete round one,
for arbitrary common backgrounds. This extends beyond projected one-round
zero sums. It is unrestricted, with no hash-message reachability result.

The systematic sampled continuation covered all 56 ordered distinct unit
pairs, 24 choices each (1,344 total); 1,047 had at least two nontrivial
overlapping local boomerang cells. None retained full-state XOR zero after
Chi2 or complete round two. Observed minimum defects were 903 and 950 bits;
these are sampled values, not class-wide lower bounds. The best-at-Chi2
quartet has 38 active cells, five overlapping, and is retained as four
actual round-start states with C checkpoint replay. Its Chi2 cell `(0,0,0)`
has difference pair `(1190,1536)` with exact local rectangle count zero
over all 65,536 bases, independently counted. Changing earlier backgrounds
may change that pair, so the obstruction is specific to the saved pattern.

The [producer](../scripts/krakken_multicell_boomerang.py),
[sample](../results/krakken_multicell_boomerang_sample.json),
[separate audit](../scripts/krakken_multicell_boomerang_audit.py), and
[audit report](../results/krakken_multicell_boomerang_audit.json) are source pinned.
Only one low-priority process ran at a time; no solver was started and
the AA campaign and C/header were not modified. Full multi-cell Chi2
continuation, shared-chain carry matching, and sponge reachability remain open.

## 2026-10-04: AB `[1,2]` positions 000–063 refined

The first 64 AB start positions now have complete source-pinned
three-bit reports, each covering all 8,128 named sites. Across their
**520,192** sites, the initial pass recorded **177,893** exact
bit-zero exclusions, **341,357** further three-bit UNSAT exclusions,
and **942** relaxed SAT candidates. Every one of the 942 was refined:
**860** became UNSAT at four bits and the other **82** at five bits.
For the latest eight-position batch, 056–063, only positions 060 and
062 had relaxed survivors (57 and 174); their
[position-060](../results/krakken_12_ab_pos060_refinement.json) and
[position-062](../results/krakken_12_ab_pos062_refinement.json) reports
exclude all 231. An integrity pass found no missing or unresolved
case in positions 000–063. This is a completed quarter of the AB
site enumeration, **not** a global AB or unrestricted `[1,2]`
theorem; AB positions 064–255 and BA retain their separate campaign
status.

The [effective-coordinate pilot](KRAKKEN_EFFECTIVE_CONE_PILOT.md)
shows a way to shrink the exact low-bit relaxation further and, for
small visible ranks, replace Z3 with finite carry enumeration. Its
named exclusions reproduce existing refinements and are not counted
again as new exclusions here.

# Reduced-round truncated collision experiment

This experiment measures **first-collision behavior of truncated output prefixes** across Krakken round counts.

It is a statistical probe, not a claim of a full collision attack.

## Domain

Every generated input is a valid 159-byte first-block message:

- bytes `0..158`: generated message;
- byte `159`: fixed `0x86` padding;
- bytes `160..255`: zero initial capacity.

The tool applies exactly `r` complete Krakken rounds, then treats the first 32 state bytes as the reduced-round digest.

## What it measures

For each selected pair `(rounds, bits)`, the program generates distinct deterministic messages until two digests share the same first `bits` output bits.

It repeats this over multiple trials and records:

- hashes to the first truncated collision;
- mean and median first-collision count;
- the random-function birthday baseline
  `sqrt(pi/2) * 2^(bits/2)`;
- the ratio of the measured mean to that baseline;
- a replayable witness containing both 159-byte messages and both full 256-bit reduced-round digests.

A single unusually early collision is **not evidence of a weakness**. First-collision counts have high variance. Useful evidence would require repeated experiments, scaling across output widths, and careful statistical analysis.

## Build

Portable scalar build:

    make collision-tool

Optional AVX2 build on a compatible x86/x86-64 CPU:

    make collision-tool-avx2

## Quick smoke test

    ./krakken-collision --rounds 1,8 --bits 16,20 --trials 3 --out collision_results

A more useful starting experiment:

    ./krakken-collision --rounds 1,2,3,4,5,6,7,8 \
        --bits 24,32,40 --trials 50 --out collision_results

For AVX2:

    ./krakken-collision-avx2 --engine avx2 \
        --rounds 1,2,3,4,5,6,7,8 \
        --bits 24,32,40 --trials 50 --out collision_results_avx2

The 40-bit class is much more expensive than 24/32 bits and can use substantial memory.

Widths above 40 bits require an explicit `--max-hashes` value so an accidental command does not allocate enormous tables.

## Determinism

The default seed is:

    0x6b72616b6b656e31

The message generator embeds a counter and a trial tag into each 159-byte message, making messages within a trial distinct and making the experiment reproducible.

Change the seed with:

    --seed 0x123456789abcdef0

## Output

Each output directory contains:

    summary.csv
    witness_r<rounds>_b<bits>_t<trial>.kat
    ...

The CSV contains one aggregate row per `(rounds,bits)` class.

Each witness contains:

- source domain;
- implementation used to discover it;
- rounds;
- truncation width;
- trial number;
- hashes to first collision;
- seed;
- both messages;
- both full 256-bit reduced-round digests.

## Replay

A saved witness can be replayed using the portable scalar binary even if it was discovered with AVX2:

    ./krakken-collision --replay collision_results/witness_r8_b32_t0000.kat

A successful replay prints:

    prefix : COLLISION CONFIRMED

The full digests should normally be different. The witness establishes a collision only in the stated truncated prefix.

## Interpretation

For an ideal random `n`-bit function, the expected first-collision scale is approximately:

    sqrt(pi/2) * 2^(n/2)

So the experiment should be interpreted by **scaling**, not by one run.

Interesting follow-up questions include:

- Do the means converge toward the birthday baseline as rounds increase?
- Does any output width show a stable deviation across independent seeds?
- Do selected state-byte projections behave differently from the first-prefix projection?
- Do structured low-activity message-difference families behave differently from independent generated messages?
- Does a reduced-round deviation persist when moving from 24 to 32 to 40+ bits?

A repeatable deviation would be a lead for cryptanalysis, not by itself a full 256-bit collision result.

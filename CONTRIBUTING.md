# Contributing to the Krakken Cryptanalysis Challenge

Cryptanalysis is the contribution.

You are welcome to submit:

- attacks and distinguishers;
- proofs and impossibility results;
- improved bounds;
- solver models;
- reproduction scripts;
- counterexamples to existing claims;
- independent implementations;
- test vectors;
- implementation/portability bugs;
- documentation corrections.

## Before submitting a cryptanalytic result

Please include:

1. **Target source** — commit and/or pinned source hash.
2. **Domain** — hash interface, unrestricted permutation, local component, etc.
3. **Rounds/checkpoint** — exact complete rounds or named internal layer boundary.
4. **Claim** — quantified as precisely as possible.
5. **Evidence type** — analytic, finite exhaustive, solver-backed, or empirical.
6. **Complexity** — time, data, memory, conditioning cost, and probability where relevant.
7. **Artifacts** — code, solver input, certificate, witness, seed, and command line where possible.
8. **Limitations** — what the result does *not* establish.

## Pull requests

Keep attack tooling and certificates separate from the pinned reference implementation unless the change is specifically an implementation correction.

Do not silently change `krakken.c` or `krakken.h` in a PR that claims only to add research tooling.

If a source correction is necessary, explain whether existing test vectors and source-pinned research still apply.

## Negative results

Well-defined negative results are welcome.

Examples:

- exhaustive exclusion of an attack family;
- proof that a proposed invariant cannot cross a layer;
- exact obstruction for a finite candidate class.

State the quantified class so a finite search is not mistaken for a global theorem.

## Independent reproduction

If you reproduce an existing result, please say what was independently reimplemented versus reused from the original artifacts.

A clean independent verifier is particularly valuable.

## Conduct

Technical disagreement is expected. Keep criticism directed at claims, models, code, and evidence—not people.

The point of this repository is to make Krakken fail publicly if it can fail.

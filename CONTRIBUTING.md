# Contributing to the Krakken cryptanalysis challenge

**Adversarial review is the purpose of this repository.** The most useful contribution might be a full break, a reduced-round advance, a proof improvement, an independently reproducible result, or a precise counterexample to something in the research archive.

## Before submitting

1. Identify the tested revision of `krakken.c` and `krakken.h` (commit SHA or file hashes).
2. Define the scope: hash interface (**H**), 159-byte first-block (**H159**), unrestricted permutation (**P**), local component (**L**) or modified/reduced model (**R**).
3. Identify the exact number of complete rounds and any internal layer boundary.
4. Distinguish provable results from statistical evidence and heuristic search.
5. Supply concrete witnesses and independent replay commands whenever possible.
6. State realistic computational complexity and the cost of any conditioning event.
7. Clearly separate code bugs from cryptanalytic results.

## Questions or potential breaks

Open an issue using the relevant template. Attach a minimal reproduction and point to the exact theorem/section you challenge; the 16 ledgers are [indexed here](research/README.md).

Do not claim a full eight-round hash break from a local serial-Chi property, reduced-round distinguisher or unrestricted-permutation relation without establishing hash-interface reachability.

## Pull requests

PRs with attacks, tests, alternate implementations, proof-certificate checkers or corrected descriptions are welcome. Source changes must come with known-answer tests and a clear explanation of whether the cryptographic target changes. New mathematical results should be annotated with hypotheses and evidence classifications.

**No acceptance criterion requires praise or positive findings.** Refutations and well-supported negative outcomes are equally useful.

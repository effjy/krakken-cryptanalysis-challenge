# Break Krakken-2048

This is an open invitation to **independent, adversarial cryptanalysis** of the full eight-round Krakken permutation and the public 256-bit sponge-hash interface.

## Priority targets

1. **Full hash**: a reproducible collision, preimage, second preimage or distinguisher beating an appropriate generic baseline.
2. **Full permutation**: a distinguisher, invariant, differential, linear, integral, boomerang, rotational, rebound, subspace or algebraic structure with quantified advantage and cost.
3. **Reduced rounds and internal layers**: a meaningful advance beyond the records, including successful extensions of known one- or two-round distinguishers.
4. **Theorem audit**: invalidate, tighten or independently reproduce a published statement. Concrete counterexamples matter.
5. **Implementation audit**: correctness, portability and memory-safety reports (separate from mathematical attacks).

For a 256-bit digest, idealized generic reference complexities are approximately 2^128 hashes for collision search and 2^256 for single-target preimage search. **These are comparison baselines, not certified Krakken security levels.**

## Mandatory scope labels

- **H:** real hash API, with padding, message length, capacity initialization and output size stated.
- **H159:** exactly 159 message bytes at the defined first-block interface; the padding byte and other restrictions matter.
- **P:** unrestricted 2048-bit permutation state.
- **L:** local component or internal checkpoint, not necessarily a complete round.
- **R:** reduced-width, reduced-round or hypothetical modified construction.

Please specify rounds **and** exact beginning/end layer boundaries. A fixed difference or a solver-satisfying activity pattern isn't necessarily a reachable, valid message-pair trail. A model admitting nonrealizable carry transitions is a relaxation, not a counterexample.

## What to submit

- Exact source commit or source hashes and interface/domain.
- Claim, experimental hypothesis or counterexample; proof or analysis.
- Data/time/memory complexity; success probabilities and conditioning/embedding costs.
- Full input/output witnesses when applicable, including distinct messages for collision claims.
- Reproduction commands, code, seeds, parameters, solver name/version, termination status and logs.
- Whether evidence is analytic, finite exhaustive, complete-solver exclusion, or empirical.
- A careful distinction between local structure, reduced-round observation and a full-round attack.

**Negative results matter when their quantification is precise**: “no survivors among these N tested cases” is not “no survivor exists.”

## Current status

The eleven [research ledgers](research/README.md) document multiple local and reduced-round distinguishers plus numerous restrictions on their investigated continuations. They do **not** certify 128-bit collision resistance, 256-bit preimage resistance, a global eight-round differential probability or general full-round indistinguishability.

## Disclosure

Open, reproducible publication is encouraged. No embargo is imposed by this research challenge. Please report implementation bugs clearly and separately; see [implementation notes](docs/IMPLEMENTATION_NOTES.md).

**Do not deploy Krakken to protect real data based on this challenge.**

# Krakken Cryptanalysis Challenge

This document defines the research target and the standard for reporting results.

## Primary target

The primary target is the exact scalar source revision pinned in the repository README:

- eight-round Krakken-2048 permutation;
- the hash interface implemented by `krakken_hash_scalar`;
- 32-byte / 256-bit output as the default challenge digest unless a submission states otherwise.

The unrestricted 2048-bit permutation is also an explicit attack surface.

## Reference generic complexities

For a hypothetical ideal 256-bit hash, the usual generic reference costs are approximately:

| Goal | Generic reference cost |
|---|---:|
| Collision | 2^128 evaluations |
| Preimage | 2^256 evaluations |
| Second preimage | 2^256 evaluations |

These numbers are comparison baselines, **not claimed Krakken security levels**.

For distinguishers and internal-permutation results, state the random-function or random-permutation experiment being compared against.

## Full breaks

The strongest submissions would establish any of the following for the full eight-round construction:

- a collision attack materially below the generic 2^128 reference;
- a preimage or second-preimage attack materially below the generic 2^256 reference;
- a practical or asymptotic distinguisher with explicit advantage and complexity;
- a structural property inconsistent with the intended random-function/permutation model and useful at nontrivial complexity;
- a multi-block attack exploiting the sponge/hash interface;
- a full-round differential, linear, differential-linear, integral, boomerang, rebound, rotational, algebraic, or related attack with a quantified advantage.

## Reduced-round and structural results

Reduced-round work is welcome and should not be downplayed. In particular, useful contributions include:

- extending a known one-round structure through additional nonlinear layers or complete rounds;
- finding lower-activity trails or better probabilities/correlations than the current records;
- proving impossible classes;
- discovering invariant or weak subspaces;
- finding new integral/division-property behavior;
- characterizing Pressure's carries, Walsh spectrum, or differential behavior more completely;
- constructing hash-reachable versions of unrestricted-permutation structures;
- proving that a currently open family cannot occur.

Always state whether a checkpoint is a **complete round** or an internal layer boundary.

## Domains

Please use one of these scope labels when possible:

- **H** — valid hash input under the public hash interface;
- **P** — unrestricted 2048-bit permutation input;
- **L** — local component result;
- **U** — uniform-input component/layer analysis;
- **R** — explicitly reduced-width model.

For first-block research, be precise about message length, padding, and fixed initial capacity.

## Evidence classes

Submissions should identify the evidence type:

- **Analytic** — mathematical derivation/proof;
- **Finite exhaustive** — complete enumeration/rank/certificate over the stated finite class;
- **Solver-backed** — SAT/SMT/MILP/CP/etc. complete exclusion or construction, with solver/model details;
- **Empirical** — sampled experiment or heuristic search.

Empirical findings are welcome, but do not present them as universal exclusions.

## Reproducibility requirements

A serious result should include as much of the following as applicable:

- source commit or source hash;
- exact input/domain definition;
- exact rounds and layer boundaries;
- attack algorithm;
- seeds and parameters;
- solver version/options;
- scripts or pseudocode;
- witnesses/counterexamples;
- independent replay or verifier if available;
- complexity and success probability.

If a result depends on a very rare conditioned set, include the cost of obtaining that conditioning.

## Contradictions are first-class results

If you find that a claimed theorem, test vector, source description, or certificate is wrong, open an issue. A clean counterexample is more useful than quietly working around a bad claim.

## Implementation bugs

Memory-safety, API, portability, constant-initialization, or build problems are valuable reports but are tracked separately from mathematical cryptanalysis. See [docs/IMPLEMENTATION_NOTES.md](docs/IMPLEMENTATION_NOTES.md).

## Disclosure

There is no embargo requirement for attacks on this public research target. Reproducible public disclosure is encouraged.

Please do not frame a reduced-round result as a full-hash break, or a permutation-only result as hash-reachable unless you establish the interface constraints.

# Known Cryptanalytic Results

This is a **concise attacker's map**, not a substitute for the full theorem/certificate record.

The claims summarized here refer to the source revision pinned in the repository README. They come from the current source-pinned research record supplied with the project. Unless a result has been independently reproduced by an outside researcher, it should not be described as external validation.

## Important interpretation

- A local/component theorem is not automatically a full-round result.
- An unrestricted-permutation construction is not automatically reachable from the hash interface.
- An empirical search with no survivor is not a universal exclusion.
- Activity counts are not security-bit estimates.
- No result below establishes a global eight-round security level.

## Current highlights

### Linear / correlation

- For valid 159-byte first-block messages, no nontrivial perfect affine message-to-state relation exists after any complete round count 1 through 8.
- For first-Chi output masks active on exactly `t=1,2,3` serial-Chi components, the exact maximum absolute correlation is `2^(-3t)`.
- Defined Pressure-chain mask families have exact counters with sharp nonperfect maximum absolute correlation `1/2`.
- A joint-carry theorem covers both Pressure outputs confined to low `k <= 17` bits, again with sharp nonperfect maximum `1/2` for the stated class.
- For one complete hash round, 16 specified two-bit state masks have message-to-output correlation at most `2^-174`; defined 5D and 6D output-mask subspaces have complete-class bounds `2^-162` and `2^-76`, respectively.
- A useful numerical bound on the **complete unrestricted linear hull over all masks and rounds remains open**.

### Differential

- Over every nonzero difference between valid 159-byte first-block messages and every base message, the exact first-Chi activity minimum is `A1 = 5`.
- Exactly six exceptional rate-reachable four-cell difference lines have a separate exact activity/probability law; for each, the sharp maximum probability of a prescribed post-Chi1 difference is `2^-38`.
- For three fixed valid-message differences, conditioned on `A1=5`, the existing exact gate proves `A2 >= 3`.
- Unrestricted `[1,1]` differential trails across two rounds are excluded.
- Complete defined `[1,2]` site classes have been excluded for the distinct-second-branch and same-spatial-pair families currently listed in the theorem program.
- The conservative inherited eight-round activity floors are 12 unrestricted, 15 for the precise 159-byte first-block domain, and 17 for three selected conditioned differences. These are activity floors, not probability bounds.

### Boomerang / four-state structure

- The 16-bit serial-Chi component has a complete 65,025-entry family with maximal boomerang uniformity `2^16 = 65,536` for the stated diagonal/first-output form.
- Earlier defined one-cell/four-class continuations have exact Chi2 obstructions.
- A coordinated **multi-cell unrestricted construction** preserves a full-state four-state XOR zero sum through one complete round for arbitrary common backgrounds inside its stated direction spaces.
- In a systematic finite continuation experiment over 1,344 saved coordinated constructions, none preserved the rectangle through Chi2 or complete round two.
- A later exact reached-pattern audit found at least one zero-count Chi2 cell in every one of those 1,344 fixed patterns.
- A first-block linear reachability gate excludes 896 of those 1,344 saved U/V direction pairs for every common background. The remaining 448 pass only the linear necessary conditions and are **not known hash-reachable**.
- The full 128-dimensional coordinated direction spaces, arbitrary earlier backgrounds, and general two-round exclusion remain open.

### Differential-linear / integral / algebraic structure

- Defined one-round differential-linear classes have exact perfect-mask kernel dimensions 26–29.
- For 128 specified unrestricted input differences, no perfect two-round differential-linear output mask exists.
- Defined one-byte message-cube and byte-subspace classes lose universal round-two balance; the current division-property result for the byte-0 cube drops the universal balanced-mask dimension from 7 after round one to 0 after round two.
- Every one of the 1,272 valid first-block message bits can affect every one of the 2,048 state bits after both one and two complete rounds, in the precise existential sense of the certificate.
- The current valid-message algebraic-degree map establishes the stated first-round low-degree coordinates and degree lower bounds through rounds 2–8.

## What has *not* been established

There is currently no public claim here of:

- an eight-round collision, preimage, or second-preimage attack;
- a useful global eight-round differential probability;
- a useful global complete linear-hull bound;
- a two-round coordinated multi-cell boomerang survivor;
- hash reachability of the 448 saved multi-cell directions that passed the linear gate;
- a full security-bit estimate for Krakken.

See [OPEN_PROBLEMS.md](OPEN_PROBLEMS.md) for attack directions.

## Reproduction status

The internal research record contains source pinning, finite certificates, separate Python/C replays, opposite-pivot rank checks, solver-backed exclusions, and analytic proofs depending on the theorem.

Those are **implementation/proof audits**, not a claim of external academic reproduction.

Independent reproduction is explicitly invited.

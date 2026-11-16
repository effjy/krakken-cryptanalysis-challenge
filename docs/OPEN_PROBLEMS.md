# Open cryptanalysis questions

The goal is to find **new** attacks or independently falsify published claims, not to confirm that Krakken is secure. All eleven ledgers are preserved at [research/](../research/README.md).

## Full eight-round targets

**1. Cryptanalyze the actual hash interface.** Find a collision, preimage, second preimage, distinguisher or multi-block strategy with clearly stated advantage and cost, relative to an appropriate generic baseline. Include padding and capacity/reachability constraints; unrestricted-permutation trails are not necessarily hash attacks.

**2. Distinguish the full 2048-bit permutation.** Differential, linear, algebraic, integral, rotational/RX, rebound, subspace or adaptive attacks are welcome. Explain data, time, memory and the null model used.

**3. Extend the best local and reduced-round phenomena.** The documented serial-Chi boomerang/differential-linear relations, rotational predictors, balanced masks, low-dimensional affine hulls, and rebound partial matches suggest concrete starting points. Some selected continuations are already excluded; study different degrees of freedom instead of relabeling old failures.

## Exact mathematical targets

**4. Complete H159 two-round activity.** For all valid 159-byte pairs with `A1=5`, the established universal bound is `A2>=4`; 21 input-difference families are classified. Exclude `A2=4` universally (or construct a real reachable witness), retaining real Pressure carry constraints. [Families and examples](../evidence/family_witnesses.json); [Research 08](../research/KRAKKEN_RESEARCH_08.md).

**5. Close the H159 `[6,1]` boundary.** An unrestricted exclusion over all valid H159 inputs would improve the current global eight-round activity floor of 19 to at least 20 under existing lemmas. A restricted five-cell class has been closed, but not the entire domain. [Research 07](../research/KRAKKEN_RESEARCH_07.md), [Research 11](../research/KRAKKEN_RESEARCH_11.md).

**6. Strengthen unrestricted short-window activity bounds.** Study unclosed `[2,2]`, `[1,3]` or other necessary patterns; any new inequality must apply to the real permutation, not only a modeled XOR surrogate.

**7. Quantify complete differential and linear hulls.** Activity is not a differential probability. Obtain all-mask/all-difference bounds that account for nonlinear trail clustering, Pressure carries and cancellations. A selected-mask or selected-difference statement is not a universal bound.

**8. Explore multi-block hash reachability.** Most sharp H159 theorems concern first-block messages with a fixed initial capacity. Later absorbing blocks may change the available conditional state distribution.

## Reproducibility challenges

**9. Independently verify a published theorem.** Reproduce a full finite classification using an independently written implementation, ideally with a compact certificate that outsiders can check.

**10. Break a theorem, not just the cipher.** Find a counterexample to an asserted equality, scope, rank, probability or modeling soundness. Document the exact ledger section, source revision, and witness.

**11. Find something we missed.** No existing research program enumerates all conceivable attacks.

## Research reporting discipline

Specify whether your result addresses a full round, an internal checkpoint, a modified construction, the unrestricted state or the actual hash interface. **An SMT/MILP model that returns SAT only demonstrates model feasibility until an original-C witness is constructed.** See [CHALLENGE](../CHALLENGE.md) and [REPRODUCIBILITY](REPRODUCIBILITY.md).

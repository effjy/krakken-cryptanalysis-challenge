# Open cryptanalysis questions

The goal is to find **new** attacks or independently falsify published claims, not to confirm that Krakken is secure. All sixteen ledgers are preserved at [research/](../research/README.md).

## Full eight-round targets

**1. Cryptanalyze the actual hash interface.** Find a collision, preimage, second preimage, distinguisher or multi-block strategy with clearly stated advantage and cost, relative to an appropriate generic baseline. Include padding and capacity/reachability constraints; unrestricted-permutation trails are not necessarily hash attacks.

**2. Distinguish the full 2048-bit permutation.** Differential, linear, algebraic, integral, rotational/RX, rebound, subspace or adaptive attacks are welcome. Explain data, time, memory and the null model used.

**3. Extend the best local and reduced-round phenomena.** The documented serial-Chi boomerang/differential-linear relations, rotational predictors, balanced masks, low-dimensional affine hulls, rebound partial matches, and Research 13's H159 exchange square and two-round constructed related-input rotational/DDT test suggest concrete starting points. Some selected continuations are already excluded; study different degrees of freedom instead of relabeling old failures.

## Exact mathematical targets

**4. Raise the general H159 two-round activity bound.** Research 11 records the completed exclusions of `[5,4]` across all 21 `A1=5` input-difference families and of `[6,1]` across the valid H159 domain. Consequently `A1=5 => A2>=5`, while the general H159 bounds are `A1+A2>=8` and eight-round activity `>=20`. The remaining first-two-round activity-total-eight cases are **`[6,2]` and `[7,1]`**. Exclude both universally (or construct a real valid-message witness); under the established unrestricted adjacent-round premises this would improve the general H159 bounds to `A1+A2>=9` and eight-round activity `>=21`. **These proposed improvements are open, not proved.** Use exact H159 reachability, serial-Chi support, and Pressure carry conditions; do not infer realizability from a relaxed solver model. [Families and examples](../evidence/family_witnesses.json); [Research 11](../research/KRAKKEN_RESEARCH_11.md).

**5. Determine whether the H159 activity floors are attainable.** The established general eight-round floor `>=20` and the conditional `A1=5` floor `>=22` are **lower bounds, not exact minima**. Construct actual distinct valid 159-byte message pairs attaining a candidate activity total, or derive stronger universal exclusions; verify witnesses against the unchanged original C permutation and all eight indexed rounds. The completed `[6,1]` and all-family `[5,4]` exclusions must not be reopened as unfinished campaigns. [Research 11](../research/KRAKKEN_RESEARCH_11.md); [Known Results](KNOWN_RESULTS.md).

**6. Strengthen unrestricted short-window activity bounds.** Study unclosed `[2,2]`, `[1,3]` or other necessary patterns; any new inequality must apply to the real permutation, not only a modeled XOR surrogate.

**7. Quantify complete differential and linear hulls.** Activity is not a differential probability. Obtain all-mask/all-difference bounds that account for nonlinear trail clustering, Pressure carries and cancellations. A selected-mask or selected-difference statement is not a universal bound.

**8. Explore multi-block hash reachability.** Most sharp H159 theorems concern first-block messages with a fixed initial capacity. Later absorbing blocks may change the available conditional state distribution.

**Additional algebraic targets (Research 16).** The exact unrestricted vectorial degree of each individual indexed round is reported as 1443, but exact cumulative-round degrees remain open. Strengthen the cumulative two-round vectorial lower bound of 29, determine the unrestricted inverse-round degree (currently bounded by 573 and 882), resolve the remaining 112 first-round coordinate degrees, and determine the minimum degree over arbitrary nonzero output parities. Investigate whether symbolic composition, inverse-moment duality, or rank certificates can establish stronger results without exhaustive high-dimensional cubes. These degree questions are distinct from differential probabilities and attack-work estimates. See [Research 16](../research/KRAKKEN_RESEARCH_16.md), §§16.21–16.32.

**Extend the endpoint differential certificates (Research 15–16).** The exact finite-grid probabilities and population bounds for specified directions do not establish a universal worst-case eight-round differential bound. Seek a concrete-function bound for arbitrary nonzero input differences, including rare conditioned populations, or a counterexample to a proposed bound. See [Research 15](../research/KRAKKEN_RESEARCH_15.md) and [Research 16](../research/KRAKKEN_RESEARCH_16.md).

## Reproducibility challenges

**9. Independently verify a published theorem.** Reproduce a full finite classification using an independently written implementation, ideally with a compact certificate that outsiders can check.

**10. Break a theorem, not just the cipher.** Find a counterexample to an asserted equality, scope, rank, probability or modeling soundness. Document the exact ledger section, source revision, and witness.

**11. Find something we missed.** No existing research program enumerates all conceivable attacks.

## Research reporting discipline

Specify whether your result addresses a full round, an internal checkpoint, a modified construction, the unrestricted state or the actual hash interface. **An SMT/MILP model that returns SAT only demonstrates model feasibility until an original-C witness is constructed.** See [CHALLENGE](../CHALLENGE.md) and [REPRODUCIBILITY](REPRODUCIBILITY.md).

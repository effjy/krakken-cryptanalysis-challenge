# Current research map (November 15, 2026)

**Read this as an attacker's index, not a security certification.** The 11 unmodified ledgers in [research/](../research/README.md) remain authoritative for exact quantified statements. Claims below summarize the supplied research and do not imply outside validation.

## Established activity bounds

Write `A_r` for the number of active serial-Chi **byte S-box calls** in round `r`.

| Domain / condition | Established statement | Main record |
| --- | --- | --- |
| Nonzero unrestricted permutation input difference | `sum(A1..A8) >= 16` | [07](../research/KRAKKEN_RESEARCH_07.md) |
| Nonzero valid H159 message-pair difference | `sum(A1..A8) >= 19` | [07](../research/KRAKKEN_RESEARCH_07.md) |
| H159, conditional on `A1=5` | `sum(A1..A8) >= 21` | [07](../research/KRAKKEN_RESEARCH_07.md) |
| H159, `A1=5` | Universal `A2>=4`; exactly **21 input-difference families** achieve `A1=5` | [08](../research/KRAKKEN_RESEARCH_08.md) |
| Specific archived `A1=5` families | Some have `A2>=5` and hence a stronger 22-call conditional floor; **not universal** | [07](../research/KRAKKEN_RESEARCH_07.md), [10](../research/KRAKKEN_RESEARCH_10.md) |
| Restricted five-cell `[6,1]` class | A new restricted exclusion yields a **20-call floor for that specific population**; general H159 floor remains 19 | [11](../research/KRAKKEN_RESEARCH_11.md) |

The integers are **necessary lower bounds**, not attained minima or bits of security. An abstract low-activity assignment may be impossible to realize in the full permutation. The exact eight-round activity minimum and useful global differential probabilities remain unknown.

The archived [21-family witness catalog](../evidence/family_witnesses.json) includes real H159 pairs with `A1=5`. Its observed high second-round activities are **witness values**, not lower-bound certificates.

## Cryptanalytic structures worth investigating

- **Local serial Chi:** exact differential/nonperfect linear properties and perfect nontrivial local boomerang/differential-linear families. These are **real local distinguishers**, not full-round attacks. [01](../research/KRAKKEN_RESEARCH_01.md)
- **Differential:** detailed [1,1], [1,2] and [2,1] restrictions, domain-sensitive H159 classifications, and unresolved continuation boundaries. [01](../research/KRAKKEN_RESEARCH_01.md), [08](../research/KRAKKEN_RESEARCH_08.md)
- **Integral and subspace:** selected one-round balanced-mask spaces, affine compression and explicit sampled/exhaustive continuation studies. Some given relations disappear by round two, but a finite failed continuation does not exclude all integrals/subspace attacks. [01](../research/KRAKKEN_RESEARCH_01.md), [11](../research/KRAKKEN_RESEARCH_11.md)
- **Rotational/RX, boomerang, rebound:** strong local or one-round structures, selected two-round obstructions, and longer restricted partial matches. Broader attacks remain possible. [09](../research/KRAKKEN_RESEARCH_09.md), [11](../research/KRAKKEN_RESEARCH_11.md)
- **Collision experiments:** reproducible datasets and bounds for stated digest widths and numbers of rounds; no generic full-digest security proof. [04](../research/KRAKKEN_RESEARCH_04.md)
- **Statistical testing:** reported NIST SP 800-22 results are **188/188 evaluations passed** under the documented setup; statistical passes do not establish ideal-permutation behavior. [05](../research/KRAKKEN_RESEARCH_05.md), [06](../research/KRAKKEN_RESEARCH_06.md)

## Not established

The record does **not** certify:

- 128-bit collision resistance or 256-bit preimage resistance of the real eight-round hash.
- Absence of any eight-round distinguisher or exploitable structural weakness.
- A quantitative all-mask/all-difference eight-round differential or complete linear-hull bound.
- Exact eight-round minimum active-S-box counts, beyond stated lower bounds.
- Complete exclusion of all boomerang, rebound, rotational, integral or multi-block attacks.
- Independent public replication of every mathematical or computational certificate.

**A full break has not been demonstrated in the supplied records.** That is narrower than a universal assertion that no break exists.

## Evidence classes

- **Proved:** analytic derivation or fully documented finite exhaustion under exact hypotheses.
- **Solver certificate:** valid only for the modeled original constraints and verified solver termination; a relaxed SAT solution may be spurious.
- **Observed:** reproducible finite experiments with specified samples, not universal claims.
- **Open:** relevant security question not settled by the documents.

To challenge a claim, report the exact theorem identifier and a reproducible contradictory witness or argument. [Challenge instructions](../CHALLENGE.md).

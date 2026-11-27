# Current research map (November 26, 2026)

**Read this as an attacker's index, not a security certification.** The 16 ledgers in [research/](../research/README.md), including November 17–18 updates to Research 07, 08 and 11, Research 12's XRBD/Pressure/H159 probability results, Research 13's exchange/Yoyo/rotational/rebound audit, Research 14's November 19–22 probability, separation-rank, adaptive-selection and collision-hunter checkpoint analyses, and Research 15–16's November 25–26 differential and algebraic certificates, remain the primary records for exact quantified statements. Claims below summarize the supplied research and do not imply outside validation.

## Established activity bounds

Write `A_r` for the number of active serial-Chi **byte S-box calls** in round `r`.

| Domain / condition | Established statement | Main record |
| --- | --- | --- |
| Nonzero unrestricted permutation input difference | `sum(A1..A8) >= 16` | [07](../research/KRAKKEN_RESEARCH_07.md) |
| Nonzero valid H159 message-pair difference | `A1+A2 >= 8`; `sum(A1..A8) >= 20` | [11](../research/KRAKKEN_RESEARCH_11.md) |
| H159, conditional on `A1=5` | `A2 >= 5`; `sum(A1..A8) >= 22` (all 21 classified input differences) | [11](../research/KRAKKEN_RESEARCH_11.md), [08](../research/KRAKKEN_RESEARCH_08.md) |
| H159, conditional on `A1=6` | `A2 >= 2` (global `[6,1]` exclusion) | [11](../research/KRAKKEN_RESEARCH_11.md) |
| R1 output difference confined to words 0 and 14, with bit 11 set in both | **`A2 >= 31`** for every qualifying state pair | [12](../research/KRAKKEN_RESEARCH_12.md) |
| Specific unrestricted fixed-input-difference subevent (probability `2^-48`) | `A1=8`; `A1+A2 >= 39`; **`sum(A1..A8) >= 51`** for that subevent | [12](../research/KRAKKEN_RESEARCH_12.md) |

The new Research 12 bounds apply **only to their stated restricted differential classes**; its 51-call subevent is **not H159** and does not strengthen the unrestricted or general H159 bounds. The integers are **necessary lower bounds**, not attained minima or bits of security. An abstract low-activity assignment may be impossible to realize in the full permutation. The exact eight-round activity minimum and useful global differential probabilities remain unknown.

The archived [21-family witness catalog](../evidence/family_witnesses.json) includes real H159 pairs with `A1=5`. Its observed high second-round activities are **witness values**, not lower-bound certificates.

## Exact H159 first-round activity-event probability (Research 12 follow-up)

For **each of the 21 classified fixed H159 input differences**, a uniform 159-byte base message activates exactly five first-round byte S-box calls with **`Pr[A1=5]=2^-35`**. The qualifying base messages form an affine subspace of dimension **1,237** (`2^1237` messages out of `2^1272`); the finite audit also reports 80-bit paired local input rank and checks all 1,272 message-bit prefix columns against the original C under GCC and Clang. See [Research 12, §9](../research/KRAKKEN_RESEARCH_12.md).

**Scope limitation:** the `A1=5` event has only `2^-35` of the base-message probability mass. Endpoint probabilities require counting both this subset **and its complement**; this certificate establishes **no new two-round or eight-round differential endpoint-probability bound**. Uniform H159 base messages are not the same distribution as uniform unrestricted permutation states. The dedicated probability-foundation replay package is not yet mirrored in this repository.

## New reduced-round attack constructions (Research 13)

**EXCH-H159-001 (one complete round):** four distinct valid 159-byte messages can be arranged as an exchange square whose quartet XOR vanishes at 32 specified full-state output bits after one round. Exactly **four** of those positions lie in the first 256 bits (a reduced-round hash projection). This is a deterministic **quartet parity relation**, not a pairwise hash collision or an eight-round statement. The associated four-bit parity event has ideal-random reference probability **1/16**. See [Research 13, §3](../research/KRAKKEN_RESEARCH_13.md).

**ROT-DDT-R2-001 (two complete rounds):** specifically constructed unrestricted *related-input* pairs satisfy a 128-byte DDT-support membership test after two rounds, with approximate independent-ideal false-positive probability **`(127/256)^128 ≈ 2^-129.448`**. Inputs are selected through carry-controlled public preprocessing, and their XOR difference is **not fixed across bases**. This is a reduced-round related-input distinguisher, **not a fixed-difference differential probability**, eight-round distinguisher, or security-bit certificate. See [Research 13, §5](../research/KRAKKEN_RESEARCH_13.md).

**Rebound-model limitation:** a reported four-stage sparse S-box/MDS surrogate trail was reproduced, but it omits important original Krakken layers. The supplied full-permutation checks **did not reproduce a four-round rebound distinguisher**; they do not exclude all such attacks. The tested exchange/Yoyo, boomerang, integral, and other signatures similarly show limited measured continuation at rounds 2–8, not universal impossibility. See [Research 13, §§4, 6–11](../research/KRAKKEN_RESEARCH_13.md).

**The universal eight-round activity floors remain 16 / 20 / 22.** Research 13 establishes no new unrestricted eight-round endpoint-differential probability bound. Its reproduction tree `reproduce/exchange_bundle_v5_20261118/` is not yet publicly mirrored.

## Eight-round H159 probability and prediction results (Research 14)

**Precisely quantified populations, not a general security level.** [Research 14](../research/KRAKKEN_RESEARCH_14.md) adds (a) an injectivity-based upper bound on a specified full-state difference **averaged over independently uniform nonzero H159 input differences**, (b) an over-99%-confidence **`<2^-30.5`** collision-probability bound for 64-bit digest prefixes at each of eight depths under the Research 04 independent-uniform-message sampling assumption, and (c) fixed-difference finite-witness and sampling analyses for all 21 H159 first-round five-call families, across two through eight rounds. For independently sampled same-difference pairs in its two specified population panels, the probability of matching *full digest differences* is bounded **`<2^-20`** at greater than 99% simultaneous confidence. The sampling claims do not control the worst adversarially chosen message difference.

The ledger also records deterministic **separation-rank** bounds across every contiguous H159 message-byte cut: at least **64** separable product terms for any nonzero digest parity and at least **252** for an individual digest bit; plus restricted quartet and adaptive parity-based selection certificates. These statements have their own exact input and observation models. They are not cryptographic attack-work lower bounds or collision/preimage security guarantees. Supporting Research 14 evidence directories have **not** been mirrored publicly; inspect the ledger's proofs and reproduction requirements before treating them as independently checked.

**The general 16 / 20 / 22 active-S-box lower bounds are unchanged.** The repository still does not certify 128-bit collision resistance, 256-bit preimage resistance, or an eight-round worst-case differential bound.

**November 22 collision-hunter checkpoint ([Research 14, §14.12](../research/KRAKKEN_RESEARCH_14.md#1412--full-digest-collision-hunter-checkpoint-22-november-2026)):** the operator reports **272,776,683** distinct 48-byte counter-derived messages checked without a full 256-bit collision. This implies **37,203,559,257,852,903** tested pairs, including complete coverage of the `2^28`-message low-counter affine family, **conditional on the reported counts and implementation**. The live SQLite database and executable have **not** been independently audited. Consecutive counter enumeration does **not** justify an independent-random-draw confidence estimate or a 50.5-bit resistance claim.

## Compact probability and differential certificates (Research 15)

[Research 15](../research/KRAKKEN_RESEARCH_15.md) reports uniform-H159 eight-round collision probability `<2^-36` and maximum digest point probability `<2^-18.5` (joint confidence >99.188% under its four-wise independent random-coefficient model). For eight prescribed differences, uniform-H159 maximum differential point probability is `<2^-16.5`, zero probability `<2^-17.5`, and matching-difference probability `<2^-32` (joint confidence >99.10%). Separate 255-direction/651-plane population and exact grid results have their own quantifiers; the exact first- and second-order grid maxima are `2^-17` and `2^-16` for the specified directions and planes. These are not chosen-difference universal bounds or attack-work estimates.

## Differential extensions and exact algebraic degree (Research 16)

[Research 16](../research/KRAKKEN_RESEARCH_16.md) reports exact maximum DP `2^-13` for all 16,383 nonzero directions on its 14D grid and derivative parity degree at least 10 for those directions on H159. On the specified 18D grid, exact DP `2^-17` holds for 2,047 directions; all 262,143 nonzero directions have DP at most `2^-11`. Zero quartet XOR is excluded for 266,906,283 plane directions on that grid. These finite-family results do not extend to arbitrary H159 bases.

The ledger's exact unrestricted **individual indexed-round vectorial algebraic degree is 1443** (§§16.21–16.24), supported by the described symbolic composition and rank certificates. The cumulative two-round vectorial degree is at least 29, each coordinate at least 28, and each nonzero output parity at least 26. The unrestricted inverse-round degree lies in `[573,882]` (§§16.27–16.32). Exact cumulative-round and unrestricted inverse degrees remain open. Algebraic degree is not security bits. The activity floors remain **16 / 20 / 22**. The accompanying Research 15–16 evidence archives are not publicly mirrored; these summaries report the ledger's results rather than independent replays.

## Cryptanalytic structures worth investigating

- **Local serial Chi:** exact differential/nonperfect linear properties and perfect nontrivial local boomerang/differential-linear families. These are **real local distinguishers**, not full-round attacks. [01](../research/KRAKKEN_RESEARCH_01.md)
- **Differential:** detailed [1,1], [1,2] and [2,1] restrictions, domain-sensitive H159 classifications, and unresolved continuation boundaries. [01](../research/KRAKKEN_RESEARCH_01.md), [08](../research/KRAKKEN_RESEARCH_08.md)
- **XRBD / Pressure structure:** exact standalone XRBD collapse, invariant subspace, first-round truncated differential, solver-free conditional next-round activity floor, and carry-compatibility exclusions. These do not demonstrate an eight-round distinguisher. [12](../research/KRAKKEN_RESEARCH_12.md)
- **Integral and subspace:** selected one-round balanced-mask spaces, affine compression and explicit sampled/exhaustive continuation studies. Some given relations disappear by round two, but a finite failed continuation does not exclude all integrals/subspace attacks. [01](../research/KRAKKEN_RESEARCH_01.md), [11](../research/KRAKKEN_RESEARCH_11.md)
- **Rotational/RX, boomerang, rebound:** strong local or one-round structures, a two-round constructed related-input rotational/DDT test, selected two-round obstructions, and longer restricted partial matches. The four-stage rebound surrogate is not a verified full-permutation four-round attack. Broader attacks remain possible. [09](../research/KRAKKEN_RESEARCH_09.md), [11](../research/KRAKKEN_RESEARCH_11.md), [13](../research/KRAKKEN_RESEARCH_13.md)
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

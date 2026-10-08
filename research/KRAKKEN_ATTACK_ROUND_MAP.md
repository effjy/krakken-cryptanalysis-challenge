# Krakken attack-versus-round map

Working synthesis, updated 2026-10-07, for current `krakken.c` SHA-256
`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
and `krakken.h` SHA-256
`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.
The exact proof scopes remain in the [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md).
“Round reached” below identifies the checkpoint actually proved or tested;
it is not a claim about the best possible attack.

| Attack family | Strongest demonstrated structure and domain | Cost or quantified class | Round boundary and evidence status |
|---|---|---|---|
| Boomerang / four-state | [BOOM-LOCAL-002](KRAKKEN_SECURITY_THEOREMS.md#boom-local-002) classifies every nontrivial local serial-Chi pair: 65,025 are perfect; every other pair has uniform-base probability at most 3/128. [BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001) constructs complete **one-round** four-state zero sums for unrestricted permutation inputs. | Four chosen internal inputs give a one-round reduced-permutation distinguisher; construction uses inverse prefix and coordinated kernel directions. This is not a valid-message quartet. | All 1,344 saved continuation patterns have a certified zero-count Chi2 cell, but the directions/background spaces are not exhausted. Of those saved directions, 896 cannot enter through a valid 159-byte first block; 448 pass only a linear necessary gate. No hash-reachable complete-round quartet is known. |
| Differential activity | Exact `A1=5` minimum for valid 159-byte first blocks ([DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001)); the first full 160-byte absorb is addressed by [DIFF-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004). [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001) bounds each prescribed Chi1/XRBD1 full difference by `2^-30` under a uniform rate-message base. [DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002) classifies each unrestricted local input difference's sharp maximum. | A concrete five-call message pair attains the first-block minimum. For its fixed 159-byte difference, the `A1=5` activity event has probability `2^-35` over uniform base messages; that is not a full trail probability. The local `2^-6/2^-7/2^-12` trichotomy cannot simply be multiplied under the rate-restricted base. | The five-call 159-byte witness has `A2=255`. Three fixed differences satisfy `A1=5 ⇒ A2≥3`; the global minimum `A2` for all hash-reachable pairs is open. Unrestricted `[1,1]`, distinct AA, AB and BB `[1,2]`, and same-pair mixed `[1,2]` are excluded; distinct BA keeps global `[1,2]` open. [AB](KRAKKEN_SECURITY_THEOREMS.md#diff-12-007). |
| Differential-linear | [DL-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-local-001) classifies every **perfect local** serial-Chi pair: exactly 65,025 diagonal-input/first-output-mask pairs. [DL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-001) gives large perfect output-mask spaces for defined one-round unrestricted differences. | All other nontrivial local pairs have `|corr|≤71/512` under a uniform local base; the bound is nonsharp. The one-round statement covers 128 sites and 255 nonzero diagonal bytes per site, with specified affine spaces. | [DL-002](KRAKKEN_SECURITY_THEOREMS.md#dl-002) excludes perfect two-round output autocorrelations for 128 fixed differences and all output masks. Nonperfect useful complete-round correlations and other differences remain open. |
| Integral / division | The valid-message byte-0 cube has seven universal linear-mask balances after one round ([INT-BYTE-002](KRAKKEN_SECURITY_THEOREMS.md#int-byte-002), [DIV-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#div-byte-001)). | A complete byte cube uses 256 messages. This is one precisely defined cube, with every base and linear output mask covered by the rank theorem. | After round two, that cube has no nonzero universal linear-mask balance. Other integral and division-property families are not excluded. |
| Kernel-directed integral | [INT-KERNEL-001](KRAKKEN_SECURITY_THEOREMS.md#int-kernel-001) fixes all first Chi inputs using directions in a 248D message kernel. Every dimension-8–248 kernel cube balances the full Chi1/XRBD1 state and 32 complete-round-one coordinates; eight is a sharp checkpoint threshold. | One eight-dimensional cube uses 256 valid messages. The saved cube has exactly 32 universal R1 output-mask generators, including four in the first 256 bits; all bases and linear masks are quantified for that cube. | At round two the saved cube has **no nonzero universal linear-mask balance**, certified by full sum rank 2048 and fresh C/NumPy replays. Other kernel direction spaces, special cosets, statistical balances and higher-dimensional integrals remain open. |
| Nonlinear-output integral | [INT-NONLINEAR-001](KRAKKEN_SECURITY_THEOREMS.md#int-nonlinear-001): 64 universal R1 predicates, including 56 nonlinear, per specified eight-bit projection of a saved H kernel cube | 256-message cubes; all 2^256 Boolean predicates of each of 16 projections, independently | At every complete R2–R8 only constants have universal parity; each round separately certified. Other cubes, joint/wider windows and statistical balances remain open; observations are not digest-only. |
| Perfect nonlinear partition / common labels | [PARTITION-001](KRAKKEN_SECURITY_THEOREMS.md#partition-001): 16 matching checkpoint/output pairs have q^16 exact R1 label pairs; 65,532 Boolean output predicates are nonlinear | H; all label truth tables on 175 source × 48 destination byte observations, separately at each complete round | Every specified pairing at R2–R8 has constants only. Raw message-byte/raw digest-byte pairings already have constants only at R1. Perfect separable labels only; joint observations, nonperfect biases and multiblock inputs remain open. |
| Mixed algebraic relations | [ALG-REL-001](KRAKKEN_SECURITY_THEOREMS.md#alg-rel-001): 16 matching R1 projections have exact ideal generated by one linear and one mixed quadratic equation | H; every Boolean function on each specified four-bit/four-bit window; 67,200 cases | At each complete R2–R8 every joint pattern is reachable, excluding all nonzero universal equations in these windows. Raw message/digest low-nibble pairs already have full support at R1. Wider/joint windows, special subsets and statistical relations remain open; full support is not independence. |
| Linear | [LIN-GLOBAL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-global-001) excludes every perfect affine message-to-state relation at rounds 1–8 for valid 159-byte messages. [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001) closes the first-Chi class with arbitrary masks on all first-output bytes and at most five second-output bytes. [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) crosses nonlinear Pressure carries in a selected eight-bit one-round output space. | At Chi1, first-only masks on `t` bytes have sharp maximum `2^-3t`, reaching `2^-384` for all 128 bytes. After a complete round, each of the 255 nonzero masks in the selected eight-bit space has correlation at most `2^-246` against every message mask; these bits are outside the digest. | The first-only result stops before Pressure. The eight-bit result is a quantitative **one-complete-round** theorem. The numerical consequence of global rank alone remains only `1−2^-1271`; a useful global eight-round linear-hull bound remains open. |
| Related-round / cyclic schedule affine relations | [SCHEDULE-AFF-001](KRAKKEN_SECURITY_THEOREMS.md#schedule-aff-001): exact R1 full-state offsets between all 28 cyclic schedule pairs | Same valid159 message, every independent pair of output masks; 196 paired rank4096 certificates | No nontrivial perfect affine relation at complete R2–R8 separately. Exact nonlinear transformed-input conjugacy survives R8. Modified schedules are not production APIs; nonperfect relations and general slide attacks remain open. |
| Primitive byte-S-box algebra | [SBOX-ALG-001](KRAKKEN_SECURITY_THEOREMS.md#sbox-alg-001): exact affine inversion, analytic differential uniformity 4 and boomerang uniformity 6 | All byte inputs; full local Walsh/ANF tables give 32/112/7 | S-box-only supporting theorem. It establishes no round boundary and must not be counted as another attack that fails at R2. Serial-Chi and full-round composition remain separate. |
| Truncated differential | [DIFF-TRUNC-001](KRAKKEN_SECURITY_THEOREMS.md#diff-trunc-001) certifies one-round zero-output-bit projections for all 128 unrestricted one-cell starts. | The selected site has 15 guaranteed zero-difference output bytes for every base and nonzero byte difference. | Its one-cell start is not first-block hash-reachable. A separate fixed-difference two-round projection screen found no significant surviving bias in its tested sample; that screen is empirical and narrow. |

The most direct attack-side next question is whether any of the 448
linear-gate surviving coordinated directions admits four **actual valid
messages** with compatible Chi bases and Pressure carries. A positive
witness should be replayed through Chi2 and all eight rounds, with its
construction cost recorded. A negative result needs an exact exclusion
of the fully specified direction/background class. For the variable-length
hash, differing earlier blocks remain a separate reachability problem:
the later capacity difference then need not be zero.

This map does not convert activity, local correlation, or sampled
round-two failure into an eight-round attack complexity or security margin.

## Complete Pressure deterministic translation family

[PRESS-TRANS-001](KRAKKEN_SECURITY_THEOREMS.md#press-trans-001) exposes
a genuine local probability-one differential space of dimension 16. The first
round suffix preserves every affine coset of this space exactly. Its surrounding
Chi cost is nevertheless sharp total 135, with attaining `[72,63]`; individual
minima 48 and 30 occur at different directions. This condition is at Pressure
input, not a fixed initial message difference.

At Chi2/XRBD2, uniform unrestricted bases give sharp maximum point probability
`2^-184`. By complete R2, every nonzero direction has a saved counterexample
to universal deterministic output difference, even for the first 256 bits.
Two saved 16D internal cosets have full output affine hull 2048 and graph
hull 2064. Other cosets, statistical/nonperfect continuations, valid-message
reachability and later-round probability remain open. This is a closed defined
translation class, not universal two-round differential security.

RESULT8 sharpens this family's hash-interface boundary: the saved attaining
pair is invalidly padded and has nonzero capacity, so it establishes no valid
message sharpness. Reachability is an intersection of the nonlinear message
image with its translation. Neither unrestricted R2 counterexamples nor full
internal coset ranks exclude behavior on the restricted reachable subset.
A focused open direction is `0x4000`; excluding it entirely would leave a
conditional 145-call total floor, whereas excluding its minimizing bases alone
would not. No reachability result is asserted, and A1=5 lies outside this class.
See [RESULT8](../RESULT8.md).

## Consecutive deterministic Pressure transitions

[DIFF-WINDOW-001](KRAKKEN_SECURITY_THEOREMS.md#diff-window-001) strengthens
the defined translation frontier: a nonzero U difference cannot land in U at
the next Pressure input for **any base**, already through Chi2/XRBD2. Full-rank
inactive-cell constraints exclude all 65,535 starting directions. This supplies
conditional activity composition, not exclusion of arbitrary two-round trails.

**Cyclic-conjugacy continuation (RESULTS13).** The eight-round nonlinear
identity survives. An exact 776-bit criterion now describes valid159
input companions; fixed-prefix Fourier upper bounds are `1/16+
(15/16)*2^-246` per phase and `7/16+(27/16)*2^-246` for phase
selection. Zero companions in the saved 33,024 cases does not exclude
the full domain. The rate-only output correction obstruction is
unrestricted, not proved on reachable hash fibers. No attack stopping
round or general slide exclusion is added by this corollary.
[Details](KRAKKEN_SECURITY_THEOREMS.md#schedule-aff-001) ·
[RESULTS13](../RESULTS13.md).

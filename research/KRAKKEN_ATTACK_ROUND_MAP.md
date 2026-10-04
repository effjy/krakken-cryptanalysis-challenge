# Krakken attack-versus-round map

Working synthesis, 2026-10-03, for current `krakken.c` SHA-256
`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
and `krakken.h` SHA-256
`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.
The exact proof scopes remain in the [theorem ledger](KRAKKEN_SECURITY_THEOREMS.md).
“Round reached” below identifies the checkpoint actually proved or tested;
it is not a claim about the best possible attack.

| Attack family | Strongest demonstrated structure and domain | Cost or quantified class | Round boundary and evidence status |
|---|---|---|---|
| Boomerang / four-state | [BOOM-LOCAL-002](KRAKKEN_SECURITY_THEOREMS.md#boom-local-002) classifies every nontrivial local serial-Chi pair: 65,025 are perfect; every other pair has uniform-base probability at most 3/128. [BOOM-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#boom-multi-001) constructs complete **one-round** four-state zero sums for unrestricted permutation inputs. | Four chosen internal inputs give a one-round reduced-permutation distinguisher; construction uses inverse prefix and coordinated kernel directions. This is not a valid-message quartet. | All 1,344 saved continuation patterns have a certified zero-count Chi2 cell, but the directions/background spaces are not exhausted. Of those saved directions, 896 cannot enter through a valid 159-byte first block; 448 pass only a linear necessary gate. No hash-reachable complete-round quartet is known. |
| Differential activity | Exact `A1=5` minimum for valid 159-byte first blocks ([DIFF-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-001)); the first full 160-byte absorb is addressed by [DIFF-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#diff-rate-004). [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001) bounds each prescribed Chi1/XRBD1 full difference by `2^-30` under a uniform rate-message base. | A concrete five-call message pair attains the first-block minimum. For its fixed 159-byte difference, the `A1=5` activity event has probability `2^-35` over uniform base messages; that is not a full trail probability. The `2^-30` figure is a checkpoint bound, not attack complexity. | The five-call 159-byte witness has `A2=255`. Three fixed differences satisfy `A1=5 ⇒ A2≥3`; the global minimum `A2` for all hash-reachable pairs is open. Unrestricted `[1,1]` is excluded; `[1,2]` is not globally closed. |
| Differential-linear | [DL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-001) gives large perfect output-mask spaces for defined one-round unrestricted differences. | The statement covers 128 sites and 255 nonzero diagonal bytes per site, with specified affine spaces. | [DL-002](KRAKKEN_SECURITY_THEOREMS.md#dl-002) excludes perfect two-round output autocorrelations for 128 fixed differences and all output masks. Nonperfect useful correlations and other differences remain open. |
| Integral / division | The valid-message byte-0 cube has seven universal linear-mask balances after one round ([INT-BYTE-002](KRAKKEN_SECURITY_THEOREMS.md#int-byte-002), [DIV-BYTE-001](KRAKKEN_SECURITY_THEOREMS.md#div-byte-001)). | A complete byte cube uses 256 messages. This is one precisely defined cube, with every base and linear output mask covered by the rank theorem. | After round two, that cube has no nonzero universal linear-mask balance. Other integral and division-property families are not excluded. |
| Linear | [LIN-GLOBAL-001](KRAKKEN_SECURITY_THEOREMS.md#lin-global-001) excludes every perfect affine message-to-state relation at rounds 1–8 for valid 159-byte messages. [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001) closes the first-Chi class with arbitrary masks on all first-output bytes and at most five second-output bytes. [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) crosses nonlinear Pressure carries in a selected eight-bit one-round output space. | At Chi1, first-only masks on `t` bytes have sharp maximum `2^-3t`, reaching `2^-384` for all 128 bytes. After a complete round, each of the 255 nonzero masks in the selected eight-bit space has correlation at most `2^-246` against every message mask; these bits are outside the digest. | The first-only result stops before Pressure. The eight-bit result is a quantitative **one-complete-round** theorem. The numerical consequence of global rank alone remains only `1−2^-1271`; a useful global eight-round linear-hull bound remains open. |
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

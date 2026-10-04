# Triage of `NEW.md` theorem candidates

Source pins: `krakken.c` SHA-256
`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`;
`krakken.h` SHA-256
`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.
This tracks the five candidates in the [reviewer note](../NEW.md). The
[theorem ledger](KRAKKEN_SECURITY_THEOREMS.md) is authoritative for
proved scopes; the frozen review bundle is unchanged.

| Candidate | Disposition | Exact boundary |
|---|---|---|
| 1. Serial-Chi maximum differential probability | **Closed as [DIFF-CHI-002](KRAKKEN_SECURITY_THEOREMS.md#diff-chi-002).** | All 65,535 nonzero local input differences: sharp maxima `2^-6`, `2^-7`, `2^-12` with counts 510, 32,130, 32,895 and unique maximizing output. Uniform unrestricted local bases only; hash-level correlation remains separate. |
| 2. Local differential-linear connectivity | **Perfect class closed as [DL-LOCAL-001](KRAKKEN_SECURITY_THEOREMS.md#dl-local-001).** | Exactly 65,025 nontrivial perfect local pairs. Others have a proved conservative `71/512` bound; the sharp nonperfect maximum remains open. |
| 3. Digest-coordinate LIN-RATE-004 analogue | **Open.** | No digest-coordinate complete-round mask-space certificate was produced in this pass. The current [LIN-RATE-004](KRAKKEN_SECURITY_THEOREMS.md#lin-rate-004) selected bits lie outside the digest. |
| 4. Theta fixed space and 2-cycles | **Closed as the supporting layer theorem [LIN-THETA-001](KRAKKEN_SECURITY_THEOREMS.md#lin-theta-001).** | Exact `dim Fix(Theta)=1544`, `rank(Theta−I)=504`, and every non-fixed state in a 2-cycle. This is Theta alone, with no complete-round or hash-security consequence. |
| 5. Strengthen `2^-24` to `2^-30` | **Already closed as [CHI-RATE-001](KRAKKEN_SECURITY_THEOREMS.md#chi-rate-001).** | The reviewer note predates the completed conditional-rank audit. The stronger bound is a first-Chi/XRBD checkpoint result for uniform rate-message bases, not a Pressure or complete-round bound. |

Candidate 1 used the exact two-DDT serial-Chi factorization and a
fresh complete DDT of the current header's S-box. The
[producer](../scripts/krakken_serial_chi_differential_trichotomy.py)
and [separate C audit](../scripts/krakken_serial_chi_differential_trichotomy_audit.c)
both enumerated all nonzero input differences. The producer also
replayed 63 attaining transitions through original-C `chi_scalar`.
Candidate 2 used the complete byte autocorrelation table, whose
nontrivial magnitude is at most 32, and verified the local DLCT
identity against 128 direct exhaustive 16-bit sums. Its
[Python report](../results/krakken_serial_chi_dlct.json) and
[separate C ACT audit](../results/krakken_serial_chi_dlct_audit.json)
agree on the complete byte-ACT histogram. The separate
implementation audits validate the source mapping and finite tables;
the analytic arguments in the ledger explain the universal claims.

Candidate 4 is now backed by a [2048-column original-C matrix](../results/krakken_theta_fixed_space.matrix.bin),
an [explicit 1544-vector fixed basis](../results/krakken_theta_fixed_space.basis.bin),
16 saved non-fixed two-cycle witnesses, and a
[separate Python audit](../results/krakken_theta_fixed_space_audit.json)
that reconstructs every matrix column and basis vector. The
analytic parity-recurrence argument proves the dimension; the finite
checks tie it to the pinned scalar source. Involutivity alone had
appeared in the corpus, but the full fixed-space classification had not.

Neither new theorem crosses XRBD, Pressure or a complete round as a
probability/correlation bound. The unrestricted full-Chi product
corollaries require uniform independent component bases and cannot
be applied directly to valid-message first-block inputs. A natural
follow-up is to combine `DIFF-CHI-002`'s local classes with
`CHI-RATE-001`'s conditional rank structure for **specified
hash-reachable differences**, with the message-base dependencies
retained exactly.

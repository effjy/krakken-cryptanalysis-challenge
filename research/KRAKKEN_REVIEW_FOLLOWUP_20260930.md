# Follow-up to the 2026-09-30 source review

Review input: `/home/user/Desktop/Krakken/REVIEW.md`. A provenance-preserving
copy and the available review helper/reports are retained in
[krakken_review_20260930](../results/krakken_review_20260930/), with hashes in its
[provenance manifest](../results/krakken_review_20260930/provenance.json).
This is a review record, not a replacement or rebuild of the frozen review bundle.

## Addressed in the working research

- **Solver-audit discrepancy confirmed and corrected.** The cited
  `krakken_11_audit_validated.json` has `replayed_scip_jobs: {}`. The
  `DIFF-PERM-002` ledger and inventory now distinguish original 512-job
  producer evidence, implementation/model checks, and optional but unrecorded
  solver reruns. No SCIP rerun was performed in this follow-up. The correction
  changes the audit coverage description, not the recorded producer result.
- **Round-index invariance and activity corollary added:**
  [DIFF-MULTI-001](KRAKKEN_SECURITY_THEOREMS.md#diff-multi-001).
  It inherits the existing `[1,1]` theorem, rather than creating a new solver
  certificate. Eight-round total activity floors are 12 unrestricted, 15 for
  the exact 159-byte first-block domain, and 17 for the three selected fixed
  differences under `A1=5`. The report and separate arithmetic audit record
  original-C wiring/constant validation and abstract-pattern enumeration.
  These floors need not be attainable and cannot be converted into security bits.

## Confirmed source/API issues requiring a deliberate source revision

The current pinned C/header remain unchanged so the in-progress AA campaign
and existing certificates retain their source identity. These issues are not
fixed merely by documenting them. Normal eight-round scalar entry points are
distinct from the problematic research/API edge cases.

| Issue | Current source behavior | Proposed revision / interim research requirement |
|---|---|---|
| `rc_get(round)` | Direct `rc[round]` return; no initialization or bounds check | Initialize with `pthread_once` through `init_rc_vectors`; reject invalid indices with documented policy. Until revised, explicitly initialize and validate `0..7` before access. |
| Reduced-round API | Nonpositive rounds return identity; counts above eight clamp | Reject negative and >8; deliberately specify whether zero is permitted as an identity. Research wrappers must validate the requested count before entering C. |
| Missing AVX2 definitions | Header declarations have no definitions in the supplied scalar C | Identify and test the separate translation unit, or conditionally expose/remove declarations in a new revision. |
| Native byte views | Absorb/squeeze and SHAKE helper depend on host byte order | Specify little-endian reference; reject other hosts in current research harnesses. A portable revision needs explicit little-endian encoding throughout, with constant and hash-vector regression checks. |

The new corollary checker initializes constants explicitly, requests only
rounds 1–8, and does not use the unsafe constant accessor. A production source
change would require new hashes and evidence migration; it should not be
silently mixed with certificates for the present revision.

## Attack hypotheses to investigate next

1. **Multi-cell boomerangs with jointly chosen backgrounds.** Start from the
   known perfect local family, solve the real XRBD/Pressure carries jointly,
   require compatible positive local Chi2 rectangle counts, then replay an
   explicit quartet in original C. Positive local counts alone do not ensure
   globally compatible bases. Preserve any survivor and measure construction
   cost. Treat message reachability as an additional constraint.
2. **Nonperfect differential-linear correlations.** Perfect-mask exclusions
   leave useful nonperfect correlations open. State the base distribution,
   include conditioning cost, and confirm exploratory statistical discoveries
   on independent data before claiming advantage.
3. **Backward and multi-block differential reachability.** The 159-byte
   first-block domain does not cover full 160-byte rate blocks or later
   absorbs with correlated capacity. Capacity bits are not freely controllable.

These are hypotheses and scope gaps, not demonstrated attacks or closed
exclusions. The running AA scan is not interrupted or replaced by this list.

## Interpretation of the review checks

The supplied review reports component enumeration, a separate inverse,
graph-certificate replay and boundary/constant replay. These are independent
implementation checks of the stated objects; agreement with the ledger is not
blinded rediscovery, exhaustive attack coverage or external academic validation.
Temporary review outputs are preserved with their provenance, without asserting
that every result was rerun in this follow-up. No new global security level or
round-margin claim follows from this review.

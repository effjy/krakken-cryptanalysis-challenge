# Krakken research record

## Current [2,1] campaign status — reconciled 2026-11-13

**COMPLETE: all 255 starting positions (000–254), covering all 8,355,840
spatial configurations, are recorded as excluded after refinement. Zero
unresolved configurations remain. The exclusion campaign is finished.**

This is supported by the saved records, not merely a progress report.
Position 001 is stored as `krakken_21_tiered_i001.json`, followed by
`krakken_21_low5_i001.json` and `krakken_21_low6_i001.json`: its 1000 survivors
are reduced to 250 and then zero. Position 000 is closed by its complete
low-three-bit record and four-bit closure. Positions 002–254 are in
`krakken_21_campaign/`; their 2000 final survivors are closed by the special
`krakken_21_low7_i002.json` and the records in `krakken_21_seven_bit/`.

A fresh **record-only audit** checked all 253 general checkpoint payloads,
decompressed-record hashes and counts, source fingerprints, survivor-to-child
coordinate matching, and refinement parent hashes. It also checked the special
001 chain and 000 closure accounting. No solver was invoked, and no four-day
campaign was repeated. Copies of all records used are preserved locally.

Earlier statements that the scan is ongoing, that positions or refinements
remain unprocessed, or that the special records are unavailable are
**historical and superseded by this status**. The recorded exclusion result
must not be described as an unfinished search. Prior qualifications concerning
independent proof checking and the universal source-to-model argument concern
proof assurance, not whether the campaign finished or whether survivors remain.
This record audit does not claim a new formal UNSAT proof or change security-bit
bounds.

[Saved records and no-solver reproduction](reproduce/two_one_campaign_records/README.md).
[Audit result](reproduce/two_one_campaign_records/RESULTS.json).


Started 2026-11-08. Scope: the supplied, unchanged eight-round implementation.
This file records work performed in this workspace, evidence, proofs, limitations,
and priorities. It does not replace the two historical ledgers.

## Current status

**No overall security level has been established.** We are developing quantitative
bounds for explicitly defined events, with particular attention to the difference
between a prescribed differential trace and an endpoint differential containing
many traces. The original C files and historical ledgers are unchanged.

Completed so far:

- Rebuilt the actual scalar and AVX2 implementations together.
- Independently checked the byte S-box DDT and LAT.
- Checked all 2,048 basis vectors for the linear prefix and Butterfly against a
  separate Python implementation.
- Independently verified all 12,869 square minors of the 8×8 byte MDS matrix.
- Compared scalar and AVX2 full states at all eight round depths on 194 inputs:
  1,552 comparisons, all equal. These are finite regression checks, not an
  exhaustive implementation-equivalence proof.
- Exhausted all 65,280 single-byte full-state input-difference classes to obtain
  a sharp first-Chi maximum differential-probability exponent of **322**.
- Developed a message-domain coordinate-rank proof: all 128 first-call input
  bytes together with selected sets of 31 companion input bytes form a full-rank
  coordinate system on the 1,272 message bits.
- Final 256-set calculation certified a **310-bit first-Chi differential
  probability exponent** for every one of the 40,545 single-byte valid159
  difference classes. Separately written C maximization reproduced every bound
  under GCC and Clang. This is not 310-bit hash security.
- Continuation: proved a **complete-round** differential ceiling below
  `2^-16 + 2^-45` for every single-byte full-state input difference, under
  uniform full-state bases. This sums over all internal first-round differences
  and carries. The actual 16-bit output projection is pointwise within `2^-45`
  of uniform. See NOTE-005; this is not an eight-round endpoint bound.
- 2026-11-09: proved an **actual eight-round, full-digest differential bound
  of 2^-12 on one explicitly specified 8,192-message affine family**. This
  bound is sharp on that finite domain; see NOTE-006.
- 2026-11-09: completed a predeclared **eight-round statistical population
  test** covering all 1,272 single-bit H159 input differences. Under independent
  uniform base sampling, the result supports a simultaneous maximum
  differential-probability ceiling of **2^-13 at at least 99% confidence**.
  This concerns all H159 bases as a population, but is not a deterministic
  theorem or a claim of 13-bit attack security. See STAT-001.
- Proved **sharp complete-round differential column
  bounds of 2^-288 or smaller on a 16-dimensional output-difference space**,
  for every input difference. This also gives an eight-round bound when both
  the round-7 and round-8 differences are prescribed. See NOTE-007 below.
- Independently verified and proved **NOTE-009**, a
  two-complete-round endpoint bound `< 1/2 + 2^-56` for all 65,280 single-byte
  full-state input differences and the specific final difference with bits
  93 and 1233 set. It applies to all seven adjacent indexed round windows,
  with uniform unrestricted bases and all intermediate differences summed.
  This is a ceiling near one half, **not 56-bit security**, and does not give
  an eight-round marginal endpoint bound.
- Replayed the supplied **NOTE-010** evidence: its two-parity bound
  `< 1/4 + 2^-44` for the same target passes locally.
- Proved **NOTE-011**, strengthening that two-round
  endpoint ceiling to **303976528439193 / 2^56 < 0.004219**, approximately
  **7.889 bits of differential-probability exponent for this specific event**.
  It covers all 65,280 nonzero single-byte full-state input differences,
  all seven adjacent indexed round windows, and uniform unrestricted bases.
  Eight backward parity constraints are combined using affine Fourier
  certificates and exact arithmetic. This is not a general eight-round or
  hash-security bound; the specified final difference still has only bits
  93 and 1233 set.
  A broader corollary covers every input difference with at least 64 active
  first-call bytes, giving `< 2^-8 + 2^-81` for that target. Fewer than a
  `2^-396` fraction of all full-state differences fail this activity condition;
  this count does not settle attacker-chosen exceptional differences.
- Latest small pass: proved **NOTE-012**, a different attack-family result.
  For all input masks, complete-round linear-hull correlations are `< 2^-293`
  on the 255 nonzero output masks in the selected eight-dimensional space,
  and `< 2^-220` on the full ten-dimensional space's 1,023 nonzero masks.
  These also bound the summed contribution to an eight-round linear hull
  restricted to that mask space at the first-round output. The unrestricted
  eight-round correlation remains unbounded by this argument. A limited
  eight-output-parity observation game has prediction advantage `< 2^-294`.
- Collision continuation: `COLLISIONS.md` records all one- through eight-round
  tests. **KRAKKEN-COLL-001** proves digest injectivity on an explicit
  1,048,576-message affine H159 family at every depth. **KRAKKEN-STAT-002**
  supports a simultaneous 99%-confidence random-message collision-probability
  ceiling `<2^-29` at every depth, from 262,144 preserved uniform H159 samples.
  This is a collision-entropy statement, not 29-bit collision-search security.
  All 927 reduced-round 32-bit collision pairs were replayed at eight rounds;
  none retained that truncated equality. No full-digest collisions were found
  in either dataset. Details, exact counts, proof, and limitations are in the
  separate report; the unrestricted collision-work question remains open.

## Exact source and environment

| File | SHA-256 |
|---|---|
| `krakken.c` | `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` |
| `krakken.h` | `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c` |
| `krakken_multi.c` | `9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2` |

The scalar C/header fingerprints agree with the historical ledgers. Python:
`/home/user/venv/krakken/bin/python`; NumPy 2.5.3 and Z3 5.1.0 were importable.
This investigation's finite computations use NumPy, integer GF(2)/GF(256)
arithmetic, and the original C. No large solver campaign was started.

Only the five supplied source/ledger files were initially available. Historical
certificate archives and solver scripts mentioned in those ledgers are absent
from this workspace. Their prior verification statements are reported history,
not work repeated here. The `.git` directory is not a usable Git repository.

## Important correction to the initial assessment

The old ledger's eight-round activity floors of 12 unrestricted / 15 H159 were
superseded in the newer ledger by **15 unrestricted / 18 H159**, using the
reported exclusion of both `[1,1]` and `[1,2]`. The proposed `[2,1]` improvement
of unrestricted 15 to 16 remains certification-dependent. We did not rerun or
independently certify those historical exclusions.

The newer ledger also reports an eight-round addition-resolved **linear-trail
contribution** bound of 2^-36. This is not an actual differential trace
probability and not a linear-hull correlation bound. These quantities must not
be put into one interchangeable column of “security bits.”

## Definitions

`L = Pi ∘ Rho ∘ MDS ∘ Theta` is the linear prefix before Chi. `B` denotes
Butterfly. A complete round is InkCloud ∘ Iota ∘ Pressure ∘ B ∘ Chi ∘ L.

For each `p=0..3`, `y=0..3`, `b=0..7`, one serial-Chi cell pairs:

- byte `b` in lane `8p+y`, denoted `a`;
- byte `(b+4) mod 8` in lane `8p+4+y`, denoted `b_local`.

In those coordinates the exact cell is

```
x = a XOR b_local
u = S(x)
y_local = b_local XOR u
v = S(y_local)
```

All 128 cells are disjoint. A **specified differential trace** fixes the
differences at the checkpoints it names, including pre-/post-Chi where used
below. Its probability is the fraction of original base inputs whose actual
paired executions realize all those differences. A round-boundary-only trail
need not fix post-Chi differences; the bounds below require that distinction.

H159 means a uniformly chosen 159-byte message, followed by padded byte `0x86`
and 96 zero capacity bytes. There are exactly 2^1272 equally likely inputs.
An input difference in one message byte preserves this domain.

## Reverified component facts

These are reproductions of component facts already present in the old ledgers,
not claims of new cryptographic discoveries.

The S-box is a permutation. Each nonzero DDT row contains exactly 129 zeros,
126 twos, and one four. Thus its maximum nontrivial differential probability
is 4/256 = 2^-6. The maximum absolute unnormalized Walsh entry for nonzero
output masks is 32, giving absolute correlation at most 1/8.

The byte field uses polynomial `0x11D`. Every square minor of the circulant
matrix with coefficients `(1,1,4,1,8,5,2,9)` is nonsingular. Counts by size:
`64, 784, 3136, 4900, 3136, 784, 64, 1`. Its byte branch number is exactly 9.
This does not mean nine active S-box calls at a later round boundary.

All layers are bijections: Theta is involutive because it XORs the same
correction into four words per column, preserving column parity; MDS is
invertible; rotations/shuffles are invertible; Butterfly consists of reversible
XOR shears; Chi is inverted by `b_local=S^-1(v) XOR u`, then
`a=S^-1(u) XOR b_local`; and Pressure is reversed by undoing output rotations
and its modular additions in reverse order. Round constants are translations.
Consequently a uniform full-state base stays uniform at every fixed internal
checkpoint. This statement concerns the **unconditioned** base distribution.

## KRAKKEN-NOTE-001: dependence-safe cut bound for actual differential traces

**Status: analytic lemma, not a new general cryptographic technique.**

Fix a nonzero initial XOR difference and a specified trace. At round r let its
fixed pre-Chi cell differences be `(a_i,b_i)` and its fixed post-Chi differences
be `(u_i,v_i)`. Define

```
p_r = product_i [ DDT[a_i XOR b_i, u_i]
                  * DDT[b_i XOR u_i, v_i] / 65536 ].
```

For a uniform unrestricted original state, the probability of that entire
trace is at most `min_r p_r`. If any factor is zero the trace is impossible.

Proof: the original base is carried by a bijection to a uniform pre-Chi base
at round r. Any execution realizing the trace must belong to the set on which
the *synthetic fixed* pre-Chi difference maps to the prescribed post-Chi
difference. That set has uniform measure p_r. Its 128 independent cell counts
factor; each cell count is exactly the product of the two displayed DDT entries
because `(x,y_local)` are independent uniform byte coordinates. The actual
trace event is a subset of that set. Minimize over r. We never assert that the
second actual execution has that fixed difference outside the trace event.

This proof does not condition the base on earlier trace events and does not
multiply probabilities across rounds. If A_r calls are active, it gives the
weaker bound `2^(-6 max_r A_r)`, not `2^(-6 sum_r A_r)`.

For H159 the generic change-of-measure version is
`min(1, 2^776 * min_r p_r)`: the base is uniform on a subset of size 2^1272
inside 2^2048 states at each checkpoint. This generic bound is often useless;
NOTE-003 below avoids that loss at the first Chi using actual message ranks.

## KRAKKEN-NOTE-002: sharp 322-bit first-Chi exponent for all single-byte state differences

**Status: proved within the stated scope by analytic reduction and complete
finite enumeration; independently implemented numerical replay passed.**

For every nonzero difference supported on one of the 256 input-state bytes,
and every prescribed full post-Chi1 difference e,

```
Pr_uniform_2048_X[Chi(L(X)) XOR Chi(L(X XOR delta)) = e] <= 2^-322.
```

The maximum over this input-difference class and all e is exactly 2^-322.
This is a **checkpoint** bound. The first round's Pressure has not yet been
applied. Subsequent nonlinear maps can merge different difference events, so
the same bound is not asserted for a complete-round endpoint differential.

Proof: for a local input difference `(a,b)`, put d=a XOR b. The exact maximum
cell probability is 2^-k, where:

| Condition | k |
|---|---:|
| a=b=0 | 0 |
| d=0 and b nonzero | 6 |
| d nonzero and DDT[d,b]=4 | 6 |
| d nonzero and DDT[d,b]=2 | 7 |
| d nonzero and DDT[d,b]=0 | 12 |

For d nonzero, choosing u=b silences the second derivative when allowed;
otherwise both factors are nontrivial and their unique maxima of four can be
attained successively. For d=0 only u=0 is possible. This derives the table.

For fixed delta the exact global maximum is the product of these 128 maxima,
since L(X) is uniform and the cells are disjoint. Enumerating all
256×255=65,280 deltas gives minimum exponent 322, attained for input byte
72 with XOR value `0x08`. The full per-difference exponents are archived in
`krakken_research/single_byte_bounds.csv`. A constructed attaining pre-Chi
base/output-difference witness is replayed through original `chi_scalar` and
stored in `audit_results.json`. Bijectivity of L supplies its initial state.

**Eight-round corollary:** any specified actual eight-round trace starting
with such a delta and fixing its post-Chi1 difference has probability at most
2^-322. More generally the same statement holds if a specified trace has a
single-byte round-input difference at any round, under uniform unrestricted
original bases, by NOTE-001. It does not require cross-round independence.

This is a new calculation in this workspace; the local trichotomy and the
52-active-call single-byte minimum were already known in the supplied ledgers.
We make no claim of novelty in the wider literature.

## KRAKKEN-NOTE-003: actual-message independent-coordinate cut

**Status: analytic proof plus source-derived finite rank certificates.**

Let x_i and b_i be the first-call input and companion input of cell i before
Chi1, as affine functions of the 1,272 message bits. The 1,024 linear forms in
all x_i have rank 1,024. Each certified selected set J contains 31 cells and
the combined forms `(all x_i, b_j for j in J)` have rank **1,272**.

Therefore those 159 bytes are independent and uniform under H159. The change
of variables `y_j=b_j XOR S(x_j)` is triangular and bijective, so all x_i
together with the selected y_j are also independent uniform bytes. Applying S
bytewise shows that the projection onto all 128 first-call outputs and those
31 second-call outputs is itself a bijection of the H159 message domain onto
1,272 bits. This is a coordinate fact, not a pseudorandomness claim.

For a fixed message difference, let `(a_i,b_i)` be its pre-Chi differences and
d_i=a_i XOR b_i. For a fixed full post-Chi target `(u_i,v_i)`, the exact
probability of its selected-output projection is

```
product_(i not in J) DDT[d_i,u_i]/256
 * product_(i in J) DDT[d_i,u_i]*DDT[b_i XOR u_i,v_i]/65536.
```

The full target event is a subset of this projected event. Maximizing its
probability over targets gives the upper bound 2^-W_J(delta), with

```
W_J(delta) = sum_(i not in J) 6*[d_i != 0]
            + sum_(i in J) k(a_i,b_i).
W(delta) = max_(certified J) W_J(delta).
```

The maximizing selection may depend on the **fixed difference**, but never on
the sampled base message. Taking the maximum of valid exponents is valid:
there is no probability-independence assumption between different selections.

The initial 128 certified selections yielded a universal exponent 241 across
all 159×255=40,545 single-byte message differences. Using only the first-call
outputs yields 186. A bounded follow-up search adds 128 selections focused on
the weakest covered difference; the resulting **256 selections certify 310**.
Every selection has exactly 31 companion bytes and combined rank 1,272.
This is a lower bound on the probability exponent, not an optimality claim.

Thus, for every fixed single-byte message difference delta and every full
post-Chi1 target e, with m uniform over **all** 159-byte messages:

```
Pr[Chi(L(pad(m))) XOR Chi(L(pad(m XOR delta))) = e] <= 2^-310.
```

The smallest certified exponent occurs, for example, at message byte 75,
XOR value `0x10`, using selected set 170 (zero-based). The largest certified
per-difference exponent in the table is 573. Neither is claimed sharp for
the full post-Chi distribution on H159.

**Eight-round corollary:** any specified eight-round trace fixing its first
post-Chi difference inherits the first-checkpoint probability bound over all
uniform H159 bases with one of these single-byte differences. This covers all
base messages, not a small sampled affine family. It still concerns specified
internal differences, not the endpoint differential hull.
The same containment argument works for any number of subsequent rounds;
**the later seven rounds provide no additional exponent in this proof**.

## KRAKKEN-NOTE-004: finite collections of checkpoint events

If a fixed difference has a proved bound 2^-w for every first-Chi target, an
event whose executions can reach at most N distinct such targets has probability
at most `min(1,N*2^-w)`. Proof: union bound over those targets. In particular a
collection of at most N specified traces satisfies the same bound. Counting
distinct checkpoint differences is tighter than counting traces sharing one.

An eight-round endpoint differential is not known to have sufficiently small N.
No useful hull bound follows until that count, or a stronger dependence-aware
counting argument, is proved. No adaptive chosen-base attack bound follows
from these uniform-base probabilities either.

## What this work does not establish

- No claim of 128-bit collision or 256-bit preimage security for concrete Krakken.
- No unrestricted full-eight-round maximum differential probability bound.
- No multiplication of S-box probabilities across rounds.
- No linear-hull bound from the historical 2^-36 individual contribution bound.
- No promotion of the historical `[2,1]` campaign to a certified theorem.
- No inference that long solver runtime is an attack-work lower bound.

## Next work with a measurable payoff

1. Package and independently replay these local-coordinate certificates. Their
   small verifier is a useful reproducibility baseline.
2. For a selected endpoint class, upper-bound the number or weighted mass of
   first-Chi differences that can reach it. This is the missing input to
   NOTE-004; reaching eight rounds alone is not enough.
3. For linear hulls, inspect weighted trail counts on short complete windows.
   A bound `sum_w N_w(alpha,beta) 2^-w` is useful only when all omitted weights
   have a rigorous remainder bound. Abandon an absolute-sum approach if it is
   already vacuous; do not silently assume cancellation.
4. Historical artifact-recovery task: **resolved on 2026-11-13**. The completed
   `[2,1]` records and all refinement chains are available and archived under
   `reproduce/two_one_campaign_records/`. The campaign has zero unresolved sites;
   proof-assurance questions do not imply that its search must be restarted.

For construction-level context only: rate=1,280 and capacity=768. Ideal-permutation
sponge theorems supply a capacity-dependent generic term of order q²/2^768;
256-bit output has usual classical generic targets of 128 collision-work bits
and 256 preimage-work bits. These are ideal-model targets, not a theorem about
this concrete permutation. Reference: [Keccak team's sponge security framework](https://keccak.team/sponge_duplex.html).
For the dependence problem in ARX probability calculations, see
[Qin and Wu, Towards non-independence of modular additions](https://arxiv.org/abs/2203.09741).

## Reproduction

Run from `/home/user/security`:

```bash
/home/user/venv/krakken/bin/python krakken_research/audit.py
/home/user/venv/krakken/bin/python krakken_research/hash_cut.py
/home/user/venv/krakken/bin/python krakken_research/verify_cut.py
/home/user/venv/krakken/bin/python krakken_research/verify_hash.py
```

The scripts compile the unchanged C into analysis binaries. They use deterministic
seeds and exact integer arithmetic for all claimed bounds and ranks. Floating
point estimates, random sampling, and solver timeout status are not used to
prove those bounds. The randomized coordinate ordering is only a deterministic
certificate-search heuristic; every resulting selection is rank checked.

Primary files:

- `krakken_research/audit.py`, `audit_results.json`, `audit.log`;
- `krakken_research/hash_cut.py`, `hash_cut_results.json`, `hash_cut_rows.json`;
- `krakken_research/single_byte_bounds.csv`, `hash_single_byte_bounds.csv`;
- `krakken_research/verify_cut.py`, `verify_bounds.c`, `verify_cut.log`.

## Completion and verification record

All computations in this section finished successfully in this session.

| Result | Verification performed here |
|---|---|
| Full-state first-Chi single-byte exponent ≥322 | All 65,280 cases in Python; separately written direct-DDT-maximization C checker, compiled and run with GCC and Clang, agrees on every exponent |
| H159 first-Chi single-byte exponent ≥310 | All 40,545 cases in Python; the same independent C checker agrees on every exponent and selected-set index under both compilers |
| 256 selected coordinate sets | Every set has 31 cells; both high-pivot and independently implemented low-pivot GF(2) elimination give rank 1,272 |
| First-call coordinate rank | Both rank checkers return 1,024 |
| Original scalar/AVX2 permutation comparison | 1,552 complete-state comparisons across R1–R8, zero mismatches |
| Hash wrapper/padding/squeezing | 120 length/output-length combinations agree between original scalar, original AVX2, and an independently written wrapper using the original scalar permutation |
| Actual scalar S-box/serial-Chi expressions | 256 broadcast byte values and 65,536 mixed-byte word-pair cases match direct table evaluation under GCC and Clang |
| Original-source preservation | All three C/header source hashes still match the initial fingerprints |

Hash test message lengths: `0,1,2,158,159,160,161,318,319,320,321,479,480,481,1024`.
Output lengths: `0,1,32,159,160,161,320,321`. This covers both sides of the
padding and squeeze-block boundaries. The empty-message 256-bit output is
`e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd`.
These checks were performed on this x86-64 little-endian AVX2 host; they are not
a cross-platform portability proof or a constant-time timing audit.

The SWAR byte-S-box's source-level equivalence also has a direct argument:
each byte of `(diff & 0x7f...) + 0x7f...` is at most 254, so addition cannot
carry into another byte. Its zero-byte marker therefore tests equality in
each byte independently. Multiplying the resulting byte-LSB mask by a byte
table entry fills nonoverlapping bytes. This justifies using the header's
byte table in the component proofs; the finite word checks are regression
evidence in addition to that argument.

The separate C verifier enumerates all 256 candidate first-output differences
for each of the 65,536 local input differences and maximizes the actual integer
DDT product; it does not merely copy the producer's 6/7/12 classification.
It then recomputes every full prefix difference through unchanged original C.
The independent rank checker uses the opposite pivot order. These are
independent implementations written in this investigation, not external peer
review and not a machine-checked proof-assistant development.

The bounded coordinate-search progression is saved in
`hash_cut_results.json`: the minimum improves from 241 to 310. The initial
241 calculation was independently replayed before extending the selection
pool; the final logs and certificates contain the stronger 310 calculation.
No additional search is left running.

## Artifact integrity and handoff

`krakken_research/MANIFEST.sha256` fingerprints the original inputs, this
document, and all portable research scripts, tables, certificates, and logs.
[Krakken_research_evidence.zip](reproduce/Krakken_research_evidence.zip) packages those files and the manifest, excluding
machine-specific binaries and Python bytecode. Regenerate with:

```bash
/home/user/venv/krakken/bin/python krakken_research/seal_evidence.py
```

The substantive remaining gap is unchanged: turning the internal checkpoint
bounds into a useful bound for the **union** of all compatible internal traces
of an eight-round endpoint event. The new work supplies small, reproducible,
dependence-safe ingredients for that problem; it does not solve it.

## Continuation: from a checkpoint to a complete round

The next investigation explicitly included Pressure and the final affine
layers. It sought a full-round endpoint differential bound, rather than another
bound that fixes a post-Chi difference. The numerical exponent is smaller
because the event is much less restrictive.

The first approach partitioned live Chi cells into disjoint sets whose output
columns span the 32 carry-free Pressure output bits. Across all input-difference
patterns, a simple greedy partition certified at least three such sets. This
would give only a weak correlation bound `(71/512)^3`. The construction and
results are retained as a preliminary calculation, but the stronger final
theorem uses exhaustive masks on a selected 16-bit projection instead.

### KRAKKEN-NOTE-005: near-uniform 16-bit differential projection after a complete round

**Status: proved by analytic reduction and exhaustive integer support scans,
with a separately implemented complete NumPy recount and original-C checks.**

Let F_r be any one of the eight original indexed round functions, acting on
an unrestricted 2048-bit state. Let X be uniform on all states, and let delta
be any fixed nonzero difference supported in one state byte. Define Z to be
the 16-bit projection of
`F_r(X) XOR F_r(X XOR delta)` described below. For every 16-bit value t,

```
|Pr[Z=t] - 2^-16| <= (1 - 2^-16)*(71/512)^16 < 2^-45.
```

Consequently, for **every full 2048-bit round-output target Gamma**,

```
Pr[F_r(X) XOR F_r(X XOR delta)=Gamma]
  <= [1 + 65535*(71/512)^16] / 65536
  < 2^-16 + 2^-45.
```

The sharper displayed rational upper bound is approximately
`0.000015258789081198534`, with differential-probability exponent at least
`15.999999998232083`. The rational is authoritative; decimal values are only
for readability. It is not exactly a 2^-16 upper bound and is not a claim
of 16-bit security against all attacks.

There is also a total-variation bound:

```
TV(Law(Z), Uniform_16) <= sqrt(65535)/2 * (71/512)^16 < 2^-38.
```

These are population bounds over all 2^2048 bases, not empirical estimates.
In particular, all 65,536 projected targets have positive probability for
every permitted input difference.

#### Which output bits are covered

Pressure consists of 16 disjoint pairs. For pair `j=2c+h`, with `c=0..7`
and `h=0,1`, let a be word `4c+h` and z be word `4c+h+2` at Pressure input.
Its unrotated outputs are

```
u = a + (z XOR (z >> 17)) mod 2^64
v = z + (u XOR (u << 31)) mod 2^64.
```

At bit zero there is no incoming carry:

```
u_0 = a_0 XOR z_0 XOR z_17
v_0 = z_0 XOR u_0.
```

The final theorem selects **u_0 from each of the 16 pairs**, in increasing j.
For an even pair it appears after InkCloud at bit 11 of word
`7*(4c) mod 32`; for an odd pair it appears at bit 18 of word
`7*(4c+1) mod 32`. Number state bits by `64*word + bit`. Iota only XORs
constants, which cancel in the differential. Thus these are actual bits of
the complete round output, not intermediate observations supplied to an attacker.
In projection order, their full-state bit indices are
`[11,466,1803,210,1547,2002,1291,1746,1035,1490,779,1234,523,978,267,722]`.

#### Proof: local derivative-character ceiling

Let `AC_S(d,q) = sum_x (-1)^(q dot (S(x) XOR S(x XOR d)))`.
Exact integer DDT/character multiplication verifies
`|AC_S(d,q)| <= 32` for all nonzero d and q. For d=0 the value is 256.

For one serial-Chi cell with fixed input difference `(a,b)`, let
d=a XOR b, and let `(p,q)` be a character on its output difference `(U,V)`.
Independent uniform coordinates x and y for the two calls give the exact identity

```
E[(-1)^(p dot U XOR q dot V)]
  = sum_u DDT[d,u] * (-1)^(p dot u) * AC_S(b XOR u,q) / 65536.
```

If d is nonzero and q is nonzero, the only possible summand with zero
second-call difference is u=b. Its DDT count is at most four. The triangle
inequality therefore bounds the absolute expectation by

```
(4*256 + 252*32)/65536 = 71/512.
```

If d is nonzero, q=0 and p is nonzero, the sharper bound is 32/256=1/8.
If d=0 and b is nonzero, U is always zero and any q nonzero has the same
1/8 bound. A mask with q=0 is then inactive, regardless of p. A zero input
difference makes the whole cell inactive. These cases exhaust all possibilities.

#### Proof: exact counting of contributing cells

Pull each selected output character back through the two exact bit-zero
identities and Butterfly. This gives a pair of byte masks `(p_i,q_i)` on
each Chi cell. For a fixed input difference, call a cell contributing when:

- `d_i != 0` and `(p_i,q_i) != (0,0)`; or
- `d_i = 0`, `b_i != 0` and `q_i != 0`.

Every contributing cell has absolute derivative-character expectation at most
71/512. Under uniform unrestricted X, the linear prefix L(X) is uniform, so
the 128 pre-Chi cells are independent. Consequently the complete projection's
character expectation is bounded by `(71/512)^m` if m cells contribute.
This product uses **independence of disjoint cells within one round**, not
independence between rounds or after conditioning on a trace.

All 65,280 single-byte input differences reduce to exactly **34,944 distinct
three-state cell patterns**: d nonzero; d zero and b nonzero; or both zero.
Exhausting all 65,535 nonzero characters of the 16-bit projection against
all 34,944 patterns gives **at least 16 contributing cells in every case**.
This minimum is attained at the combinatorial support level, for example
pattern 26321 and character 17. This does not claim that the analytic
correlation upper bound itself is attained.

The scan has exactly **2,290,055,040** pattern/character combinations. It uses
bitsets and population counts, not SAT or floating-point optimization. A C
implementation iterates characters in Gray-code order. An independently
implemented NumPy checker constructs characters by binary-mask expansion and
recomputes the minimum for **every** pattern; the full vectors agree. GCC and
Clang builds of the C scanner also agree byte-for-byte.

#### Proof: Fourier inversion

Put epsilon=(71/512)^16. Every nonzero character of Z has absolute expectation
at most epsilon. Fourier inversion gives
`|Pr[Z=t]-2^-16| <= 65535*epsilon/65536`. Parseval and Cauchy–Schwarz give
the total-variation bound above. Finally `71^16 < 2^99` proves
`epsilon < 2^-45` exactly. A specified full-state output difference implies
its 16-bit projection, yielding the full-round bound.

This calculation **sums over all possible first-round internal differences**.
It does not select one Chi output difference or assume any conditional
uniformity at Pressure. The carry-free identities are exact for every state,
so all higher carries are already covered.

#### Source and computation checks performed here

- Independently reconstructed all 2,048 cut columns using Python Butterfly;
  all agree with the original-C-derived columns.
- Recomputed all 65,280 direction-to-pattern assignments through unchanged
  original C, independently of the producer's linear-column recurrence.
- Replayed 512 complete-round input pairs through unchanged original C and
  checked all 32 derived cut bits against the actual endpoint differences.
  These source checks passed under both GCC and Clang.
- Exhaustively checked the S-box autocorrelation ceiling using exact integers.
- Completed an initial 12-bit projection scan: 143,095,680 combinations, also
  minimum 16 contributing cells; its independent NumPy recount passed.
- Completed the final 16-bit scan and the independent complete NumPy recount.
  The per-pattern minima and attaining-mask file SHA-256 is
  `dce767871fea173c48b35bc1843ff5a7b5b0f89aab23d0353cf1060b59dfd810`.

Both 12- and 16-bit scans give the same per-pattern minima and first attaining
mask: adding the four projected bits did not reduce those minima. This is a
checked finite result, not an assumption about untested projections.

#### Scope and eight-round implication

NOTE-005 applies to **each indexed complete round** under uniform unrestricted
round-input bases and single-byte input differences. It does not apply directly
to the H159 padded-message distribution. It does not bound an eight-round
endpoint differential by this number, let alone its eighth power.

It does give a bound for any eight-round **round-boundary-only trace** that
starts with a single-byte difference and fixes its first complete-round output
difference. Such a trace is a subset of the first-round event bounded above.
Unlike NOTE-002/003, this corollary does not require fixing a post-Chi difference.
Again, subsequent rounds add no exponent through this containment argument.

#### Reproduction and retained artifacts

After the initial `audit.py` run:

```bash
/home/user/venv/krakken/bin/python krakken_research/round_projection.py
/home/user/venv/krakken/bin/python krakken_research/projection_scan.py 12
/home/user/venv/krakken/bin/python krakken_research/projection_scan.py 16
/home/user/venv/krakken/bin/python krakken_research/seal_evidence.py
```

`projection_scan.py` compiles and runs both original-C source checkers and
both scanner builds, then runs the independent NumPy recount. The certificates,
input-pattern maps, exact rational bounds, binary minimum/witness tables, and
logs are all retained in `krakken_research/` and included in the evidence ZIP.
No historical solver certificates were promoted or modified.

## 2026-11-09: reaching the actual eight-round endpoint

This continuation produced two endpoint results with deliberately different
quantifiers. They should not be merged into a single “security level.”

| Result | Input differences | Base-input domain | Type of guarantee |
|---|---|---|---|
| NOTE-006, maximum DP = 2^-12 | All 8,191 nonzero directions inside one 13-dimensional affine family | Exactly 8,192 specified messages | Exact deterministic finite-domain theorem, full eight rounds and full 256-bit digest |
| STAT-001, maximum DP ≤2^-13 | All 1,272 single-bit message differences | Uniform distribution on **all** 2^1272 H159 messages | Simultaneous statistical confidence statement, full eight rounds; not a deterministic theorem |

Both concern actual endpoint differences and include all contributing internal
traces. Neither establishes an unrestricted differential maximum over all
message differences, nor a collision/preimage work lower bound.

### KRAKKEN-NOTE-006: an exact eight-round Sidon-family differential theorem

Let `m_x`, for x=0..8191, be the following valid 159-byte message:

```
start with m[i] = (37*i + 11) mod 256, i=0..158;
m[0] = x & 255;
m[1] = (m[1] & 0xe0) | (x >> 8).
```

This is a fixed 13-dimensional affine family; all other message bits are fixed.
Let H be the unchanged original eight-round hash with a 256-bit digest, and
let Y(x) be the first 64 digest bits.

**Exhaustively verified property:** the 33,550,336 values
`Y(x) XOR Y(y)`, for all unordered pairs x<y, are pairwise distinct.
The 8,192 Y(x) values themselves are also distinct. Equivalently, this output
set is a Sidon set in the XOR group: each unordered pair has a unique sum.
In particular, no four distinct messages in this family have digest XOR zero.

For every nonzero delta in the 13-bit index space and every 256-bit target t,

```
Pr_uniform_x[H(m_x) XOR H(m_(x XOR delta)) = t] is either 0 or 2/8192.
```

Thus the maximum full-digest differential probability on this family is
**exactly 2^-12**, for every nonzero delta.

Proof: a nonzero delta partitions the 8,192 indices into 4,096 unordered
pairs. Pairwise uniqueness of their 64-bit output XORs implies uniqueness of
their full 256-bit output XORs. Each attained target is counted at exactly
the two orientations of one pair. No internal checkpoints are fixed.

Verification performed:

- Generated all 8,192 full digests using the original AVX2 hash wrapper.
- Independently recomputed **every** digest with the original scalar hash
  wrapper and compared all 256 bits, with zero mismatches.
- C generated and sorted all 33,550,336 pair XORs and found zero duplicates.
- A separately written NumPy implementation regenerated every pair XOR from
  the saved digest archive, sorted them independently, and also found zero
  duplicates. No probabilistic fingerprint was substituted for exact comparison.

Digest archive: `sidon_family_digests.bin`, SHA-256
`85c42646a4261a38cf8f3a8d0cc5f5da7b8e52653070aab282088e9c31140d0f`.
The 64-bit values are actual digest projections, so their pair-XOR uniqueness
is a sufficient deterministic certificate for full-digest pair-XOR uniqueness.

**Limits:** this does not extrapolate to other affine families or the full
H159 population. Also, 2/N is the smallest possible nonzero XOR differential
probability on a delta-closed domain of size N, because inputs occur in pairs.
The achieved exponent therefore reflects the finite domain's resolution; it
is not a 12-bit security rating for the hash.

### KRAKKEN-STAT-001: full-H159 population bound for single-bit differences

**Classification: statistical confidence statement. The exact test inequality
is proved; the conclusion about the population depends on the sampling model.**

Define, for bit j=0..1271 and 64-bit target t,

```
p(j,t) = Pr_uniform_m_in_H159[
    prefix64(H(m)) XOR prefix64(H(m XOR e_j)) = t
].
p_star = max_(j,t) p(j,t).
```

The predeclared test supports the assertion `p_star <= 1/8192 = 2^-13` at
**at least 99% confidence**, under independent uniform sampling of the base
messages. Hence it also supports the same ceiling for every full 256-bit
digest difference and each of these single-bit input differences.

The base distribution here is the entire H159 message domain, not the finite
family of NOTE-006. The covered difference class is only the 1,272 unit-bit
directions, not all single-byte values and not arbitrary multi-bit differences.

#### Experiment fixed before examining its results

`population_design.json` was written before sampling. It specifies:

- N=65,536 independent uniform 159-byte base messages, implemented with
  `os.urandom`; the actual sampled bytes are archived.
- Reuse the same bases across all 1,272 input-difference classes. This creates
  cross-class dependence, which the proof below explicitly permits.
- Observe the first 64 digest bits after all eight original rounds.
- Target u=1/8192, error budget 1/100.
- Pass only if **no projected target repeats within any difference class**.
- Do not resample after a failure until a passing sample is obtained.

The random-byte source is an implementation of the independent-uniform model,
not a mathematical certification of physical randomness. A deterministic
pseudorandom seed was not substituted for the archived OS-generated sample.

#### Proof of the simultaneous confidence statement

Suppose the true p_star exceeds u. Fix a maximizing pair `(j_star,t_star)`
according to the fixed underlying hash distribution, **before drawing the
sample**. Such a maximizer exists because the class and output alphabet are
finite. Its sample count C has distribution Binomial(N,p_star), since the
base messages are independent uniform draws within that one class.

If the global test passes, every target in every class has count at most one;
in particular C≤1. Therefore

```
Pr[global pass when p_star > u]
  <= Pr[Binomial(N,u) <= 1]
  = (1-u)^N + N*u*(1-u)^(N-1).
```

For N=65,536 and u=1/8,192, this is

```
(8191 + 65536) * 8191^65535 / 8192^65536
  ~= 0.0030180171703148295 < 0.01.
```

The strict inequality was checked with arbitrary-precision integers:
`100*(8191+65536)*8191^65535 < 8192^65536`.

No factor of 1,272 or 2^64 is necessary in this particular global test:
one fixed population maximizer witnesses any false global assertion, and
global passage implies its low observed count. This argument does not require
independence between classes or between counts of different targets.

As a separate conservative check, applying a union bound over the 1,272 classes
also certifies a weaker **2^-12** ceiling at 99% confidence:
`100*1272*(4095+65536)*4095^65535 < 4096^65536`.

This is a frequentist false-pass guarantee. It does not assign a 99% posterior
probability to “Krakken is secure,” and it is not a deterministic upper bound
proved from the permutation's algebra.

#### Observed results and verification

A preliminary timing of 100,000 original AVX2 eight-round permutations took
approximately 0.133 seconds on this host. That informed the bounded study size;
it is a performance measurement, not security evidence.

- Archived **10,420,224** OS-generated sample bytes: 65,536 complete base
  messages of 159 bytes each.
- Evaluated all base digests and **83,361,792** changed-message digests through
  the unchanged original eight-round AVX2 permutation.
- For every one of the 1,272 difference classes, all 65,536 projected output
  differences were distinct. **Maximum observed multiplicity = 1.** The
  predeclared test passed without replacement sampling.
- A separate NumPy implementation recounted **every** class from the archived
  raw observations and matched all distinct counts and maxima.
- Independently replayed 1,272 base/changed-message pairs using the original
  scalar **hash API**, one pair for every input-bit position. Each baseline
  and projected difference matched. These selected source checks are not a
  claim that all 83 million mutant outputs were independently recomputed with
  the scalar implementation.
- Original C/header hashes still match the initial source fingerprints.

Base sample SHA-256:
`8fa2e2e19996ad1b5dcc62feb699d5874d7eafa5f7d1d6636bfb59e539135fb6`.
Raw observation SHA-256:
`28bb39ecbf61a0bde68ff10b7331b2b82dc8db1729b081b1407d94904192a386`.
Raw observations occupy **666,894,336 bytes**, stored locally at
`krakken_research/bulk/population_differences_u64.bin`.

No collision/preimage work lower bound follows from this confidence result.
It bounds uniform-base differential concentration for the stated class; a
chosen-base attack can select unusual messages and is not governed by that
sampling model. It does not test arbitrary multi-bit differences.
For comparison, an exactly uniform 64-bit projection has point probability
2^-64. The certified statistical ceiling 2^-13 is therefore coarse; the number
13 reflects this experiment's resolution, not an estimate of Krakken's actual
strength or evidence that a 2^13-work attack exists.

### Why naive checkpoint counting still fails

An exact additional audit exhausted all 65,280 single-byte full-state
differences and counted their possible first-Chi output differences. A local
cell has support size:

| Input-difference condition | Number of possible output differences |
|---|---:|
| Zero input difference | 1 |
| d=a XOR b=0, b nonzero | 127 |
| d nonzero and DDT[d,b]>0 | 16003 = 1 + 126×127 |
| d nonzero and DDT[d,b]=0 | 16129 = 127² |

Full-state cell independence makes the total support size the product of
these local values. There are 633 distinct count classes among the 65,280
directions. The smallest support has size `16003^10 * 16129^21`, approximately
2^433.1853, at byte 72 / XOR `0x08`; its largest point probability is 2^-322.
Thus even this smallest support gives a naive count-times-cap factor of
about 2^111.1853, far above one.

Checking each difference with **its own** exact maximum point probability,
the smallest naive factor across the whole class is still about 2^84.174,
at byte 208 / XOR `0x18`. Exact integer comparisons confirm every such factor
is at least one. These are direct calculations, not solver-timeout evidence.

This identifies the missing ingredient: a suffix-compatibility theorem must
discard or strongly reweight intermediate differences for a fixed final
target. Merely enumerating the first checkpoint's possible differences and
applying its largest-atom bound is vacuous. The audit does **not** prove that
a stronger suffix theorem is impossible.

### What is worthwhile next, and what will not scale

The population test supplies an actual eight-round endpoint statement with
explicit statistical qualifications. Increasing its precision by one bit
roughly doubles the sample cost at fixed false-pass probability. This cannot
be extrapolated into a 128-bit proof: the same rare-event method would need
on the order of 2^128 samples per tested difference, not merely a faster solver.

The exact Sidon-family test scales quadratically with the number of messages.
It is useful as a rigorous finite-domain endpoint certificate, but a larger
finite sample does not become a theorem over all 2^1272 message bases.

For a deterministic population-wide eight-round bound, the highest-value
target remains a **source-specific suffix-counting or conditional-distribution
lemma** with explicit domains and a useful numerical inequality. Activity
exclusions alone cannot supply it. The new support-budget calculation gives
a concrete test for proposed composition arguments: they must improve on an
unfiltered count-times-cap factor that is at least 2^84 in this restricted
single-byte class.

Before claiming general “security bits,” the attack game must also be fixed:
collision versus preimage, output length, allowed messages, whether
precomputation is charged, time/memory limits, and classical versus quantum
adversaries. The differential bounds recorded here have precise games and
distributions; they are not interchangeable with those attack-work claims.

### Reproduction and evidence packaging for this continuation

Use the archived base messages for replay. **Do not call `population_prepare.py`
to replace them.** That script intentionally refuses to overwrite an existing
study. The initial design and sample provenance are archived.

```bash
mkdir -p krakken_research/bulk
gcc -O3 -mavx2 -pthread krakken_research/population_scan.c krakken_multi.c -o krakken_research/population_scan
krakken_research/population_scan 65536 krakken_research/population_bases.bin krakken_research/bulk/population_differences_u64.bin krakken_research/population_counts.csv krakken_research/population_baselines_u64.bin
/home/user/venv/krakken/bin/python krakken_research/population_verify.py
gcc -O3 -mavx2 -pthread krakken_research/sidon_family.c krakken.c krakken_multi.c -o krakken_research/sidon_family
krakken_research/sidon_family krakken_research/sidon_family_digests.bin > krakken_research/sidon_family.log
/home/user/venv/krakken/bin/python krakken_research/sidon_verify.py
/home/user/venv/krakken/bin/python krakken_research/support_budget.py
/home/user/venv/krakken/bin/python krakken_research/update_bulk_manifest.py
/home/user/venv/krakken/bin/python krakken_research/seal_evidence.py
```

`population_verify.py` requires the analysis shared library produced by the
earlier `audit.py`. The compact evidence ZIP includes the sampled messages,
design, digests, scripts, summaries, row hashes and logs. The 636-MiB raw
observation file remains local and is **omitted from the compact ZIP**;
`bulk_artifacts.json` records its size, SHA-256 and reproduction command.
It is reproducible from the archived sample and unchanged original C.

All computations described in this continuation completed; no search remains
running. The original permutation files and historical theorem ledgers remain
unchanged.

## Latest pass: backward bounds and an explicit restart point

**Work stopped at the user's request to conserve usage.** Verified results are
recorded below. The last exploratory Fourier calculation is not promoted to a
theorem. No computation needs to remain running and no additional campaign
should be started before the user resumes.

### KRAKKEN-NOTE-007: sharp backward complete-round bounds

Let B be Butterfly and Q be InkCloud. For j=2c+h, c=0..7 and h=0,1,
let d_j toggle only bit 63 of word `4c+h` at Pressure input. For a 16-bit
label t, write d(t) for the XOR of its selected generators. Let Gamma(t)
be the following completed-round output difference, XORed over selected j:

- h=0: toggle bit 10 of words `7*(4c) mod 32` and `7*(4c+2) mod 32`;
- h=1: toggle bit 17 of word `7*(4c+1) mod 32` and bit 29 of word
  `7*(4c+3) mod 32`.

These 16 generators are independent, giving 65,535 nonzero output differences.
Put `g(t)=B^-1(d(t))` and `A(t)=wt_byte(g(t))`.

For every original indexed complete round R_r, under a uniform unrestricted
2048-bit input base,

```
max_a Pr[R_r(X) XOR R_r(X XOR a) = Gamma(t)] = 2^(-6*A(t)).
```

The maximum is **sharp**, not merely an upper bound. Across all nonzero t,
A(t) ranges from **48 to 228**, so the corresponding maximum-probability
exponents range from **288 to 1368**. The unique minimum-activity label is
`t=0x8000`, with A=48. Its completed-round output difference toggles only
full-state bits **721 and 1629**.

This is an exact complete-round DDT-column statement: every input difference
is covered, while the final output difference is restricted to the specified
space. It does not apply directly to H159's restricted base distribution.

#### Proof

In an unrotated Pressure pair, toggling the top bit of a while leaving z
unchanged toggles the top bit of both outputs u and v, for every base. Top-bit
XOR equals addition of 2^63 modulo 2^64; the left shift by 31 kills the top
bit in its shifted term. Undoing the output rotations and Q therefore gives

```
Pressure^-1(Y XOR Lambda(d(t))) = Pressure^-1(Y) XOR d(t).
```

The translation property holds for every base, so the inverse round maps a
fixed Gamma(t) through its suffix to the fixed post-Chi difference g(t).

In aligned byte-cell coordinates, with T=S^-1,

```
b = T(v) XOR u
a = T(u) XOR T(v) XOR u.
```

The byte inputs u,v to inverse S-boxes are independent uniform coordinates
when the inverse-round base is unrestricted uniform. The derivative of T at
each nonzero byte difference has exact maximum probability 4/256=2^-6,
with a unique maximizing output difference. Inactive bytes have deterministic
zero derivative. The remaining inverse-Chi mixing and inverse linear prefix
are affine bijections on the difference variables. Thus the inverse round's
maximum probability for input difference Gamma(t) is exactly 2^(-6*A(t)).

For any permutation R, `DP_R(a,b)=DP_(R^-1)(b,a)` by changing the uniform
base variable from X to R(X). This proves the forward column formula.
Round constants do not change the argument.

#### Verification completed

- Reconstructed the inverse S-box DDT independently and checked it equals the
  transpose of the forward DDT. Every nonzero row has exactly one entry four.
- Implemented all inverse layers independently in Python. Checked all 2,048
  inverse-prefix basis identities and all 2,048 inverse-Butterfly basis
  identities against unchanged original C.
- Checked 272 full inverse/forward round trips across round depths 1–8,
  plus separate Chi and Pressure inverse checks.
- Exhausted all 65,535 labels and archived every A(t) and sharp exponent.
- A separate C verifier recomputed **all** activities, checked Butterfly
  inversion against original C, and replayed Pressure translations at one
  explicit base per label. GCC and Clang builds both passed. The universal
  translation property rests on the algebra above; the replays validate wiring.
- Constructed a base/input-difference pair attaining the worst column maximum
  and replayed its output difference through all eight indexed round functions.

The minimum A=48 was already present as an activity fact in the old
`PRESS-TRANS-001` ledger. This pass independently reproduces it and derives
the sharp **inverse/full-round probability** statement. No claim of literature
novelty is made.

### Eight-round consequences that are actually justified

Fix any original input difference a, and let Delta_7 and Delta_8 be the paired
execution differences after seven and eight complete rounds. For every fixed
round-7 target d and every nonzero label t,

```
Pr_uniform_X[Delta_7=d AND Delta_8=Gamma(t)] <= 2^(-6*A(t)) <= 2^-288.
```

**Earlier internal differences are unrestricted and summed over.** The proof
uses the unconditioned uniform base after the first seven bijective rounds.
The joint event is a subset of the fixed-difference last-round event. It does
not assume that conditioning on Delta_7=d leaves the base uniform.

This is a genuine bound on a specified **joint round-7/round-8 event**, not a
bound on the marginal event `Delta_8=Gamma(t)`. Summing over all possible d
does not give a useful endpoint-only bound. The seven-round prefix contributes
no additional exponent in this proof.

There is also an unconditional structural eight-round theorem. Any pair ending
in Gamma(t) has **exactly A(t) active S-box calls in round 8**, because inverse
Pressure and inverse Butterfly fix its post-Chi8 difference. Every earlier
round has at least one active call by bijectivity. Consequently:

```
total active S-box calls over eight rounds >= 7 + A(t) >= 55.
```

If the initial difference is additionally a single byte, the independently
reverified first-round activity floor 52 gives `total >= 52+6+A(t) >= 106`.
These are activity bounds, not probability exponents, and their total minima
are not claimed attainable. Neither uses the historical solver-backed sparse
transition exclusions.

Five actual eight-round state pairs were constructed using the new inverse
and replayed with original C. For t=0x8000 the observed activity vector was
`[255,255,256,253,256,256,256,48]`, total 1835. This verifies reachability and
the exact last-round activity, not sharpness of the total lower bound 55.

### KRAKKEN-NOTE-008: where a forward/backward composition can begin

For fixed Gamma(t), the exact support of predecessor differences has affine
hull dimension **8*A(t)**. Each nonzero inverse-S-box derivative has 127
possible output differences with full eight-dimensional affine span; this
was checked for all 255 nonzero byte differences. The independent byte
supports combine by an invertible affine map through inverse Chi and L^-1.

Project that predecessor affine hull onto the **32 carry-free completed-round
coordinates** used by the forward analysis. For **every one of the 65,535
labels**, the projected affine rank is **32**. Python elimination with both
pivot orders and an independently implemented C elimination agree on every
label; GCC and Clang source checks pass.

Therefore there is no nonconstant fixed affine parity on those 32 coordinates
that all predecessors must obey. The affine relaxation permits every projected
value. This does **not** prove that the actual nonlinear support is surjective;
it identifies a limitation of this particular linear relaxation.

The next calculation included the lowest k bits of all 32 **unrotated Pressure
output words**, for k=1..32, on the 16 generator labels. The first affine
constraints appear at these widths:

| Label | A(t) | First k with an affine constraint |
|---|---:|---:|
| 0x0001 | 138 | 11 |
| 0x0002 | 114 | 5 |
| 0x0004 | 114 | 5 |
| 0x0008 | 84 | 5 |
| 0x0010 | 124 | 5 |
| 0x0020 | 96 | 5 |
| 0x0040 | 104 | 5 |
| 0x0080 | 72 | 5 |
| 0x0100 | 108 | 5 |
| 0x0200 | 80 | 5 |
| 0x0400 | 84 | 5 |
| 0x0800 | 56 | **3** |
| 0x1000 | 92 | 5 |
| 0x2000 | 64 | **4** |
| 0x4000 | 72 | 5 |
| 0x8000 | 48 | **4** |

All **512** rank profiles were independently reproduced by a C bitset
eliminator, which also checked every inverse-prefix basis column using original
C. All 16 archived parity witnesses annihilate their predecessor direction
spaces. A further 64 original-C paired one-round replays satisfy their stated
affine constants.

For label 0x0800, the low-three-bit projection has rank **94 of 96**. One
verified necessary parity has constant zero and uses these `(word,bit)`
positions in the aligned, unrotated Pressure-output coordinates:

```
(0,0),(0,1),(2,2),(4,0),(6,0),(8,0),(8,2),(10,2),
(14,0),(14,1),(16,0),(16,1),(16,2),(18,0),(20,2),
(22,0),(22,2),(24,0),(28,2),(30,0),(30,1),(30,2).
```

This is a necessary middle-difference condition for a two-round final target,
and is the starting point for NOTE-009 below. A
necessary condition alone does not supply a probability bound.

### Historical candidate: a two-complete-round Fourier bound

**Historical checkpoint, superseded by NOTE-009 below.** At the earlier usage
pause these exploratory calculations awaited independent verification and a
proof audit. The user subsequently requested completion; both now pass. The
following records what was pending at that checkpoint.

For the 0x0800 low-three-bit parity, write g for its Boolean value on a first
round's Pressure output. Any two-round execution ending at Gamma(0x0800)
must satisfy `g(X_first) XOR g(X_first_partner)=0`.

The current Python calculation finds:

- The maximum nontrivial mixed Walsh coefficient
  `sum_x (-1)^(p dot S(x) XOR q dot S(x XOR d))`, over d nonzero and
  `(p,q)!=(0,0)`, is **32**. This is new finite data in this pass and needs
  an independently implemented checker before use in a promoted theorem.
- The local low-three-bit Pressure Fourier supports have sizes
  `[40,1,13,4,10,13,1,13]` across the eight involved even pairs.
- Their product spectrum has exactly **3,515,200** characters and normalized
  Fourier L1 norm **3087/2**.
- Exhausting that spectrum in Python after Butterfly transpose gives at least
  **124 nonzero serial-Chi cell masks in every character**.
- The earlier source-verified input-pattern archive gives at least **31
  nonzero first-call differences** for every single-byte full-state difference.
  Thus at least `124-(128-31)=27` cells should contribute to the proposed
  mixed-character bound for this input-difference class.

The proposed analytic argument is:

1. Extend the local derivative-character ceiling to *different* characters
   on the two tracks. Conditioning on the first-call input and applying the
   mixed byte Walsh ceiling should give a per-contributing-cell absolute bound
   of **71/512**, with the zero-mask and zero-first-difference cases handled
   separately.
2. For every pair of Fourier characters, the 27 contributing cells identified
   by one character suffice; adding the other character cannot invalidate
   their contribution under the proposed local lemma.
3. Bound the double Fourier sum by the squared L1 norm. The resulting candidate
   autocorrelation ceiling is
   `epsilon = (3087/2)^2 * (71/512)^27`.
4. If the proof and full computation pass independent checks, the candidate
   two-round endpoint bound would be
   `DP_(R_(r+1) o R_r)(a, Gamma(0x0800)) <= (1+epsilon)/2`
   for every single-byte a and uniform unrestricted bases.

Unlike a fixed-trace bound, this would sum over the intermediate difference
of **two complete rounds**. It would still concern one specified final
difference, would not automatically apply to H159, and would not imply an
eight-round endpoint bound. Do not quote it as established yet.

The spectrum and local Fourier data are saved, so the next pass need not
repeat discovery. This is the immediate restart task, ahead of any new long
solver or sampling campaign.

### Reproduction and restart checklist

Verified backward work:

```bash
/home/user/venv/krakken/bin/python krakken_research/backward_cut.py
/home/user/venv/krakken/bin/python krakken_research/backward_bridge.py
gcc -O3 -pthread krakken_research/verify_backward.c -o krakken_research/verify_backward_gcc
krakken_research/verify_backward_gcc krakken_research/backward_column_bounds.csv krakken_research/backward_bridge_columns.bin krakken_research/backward_bridge_ranks.csv
/home/user/venv/krakken/bin/python krakken_research/backward_eight_round.py
/home/user/venv/krakken/bin/python krakken_research/backward_lowbits.py
gcc -O3 -pthread krakken_research/verify_lowbits.c -o krakken_research/verify_lowbits_gcc
krakken_research/verify_lowbits_gcc krakken_research/inverse_prefix_columns.bin krakken_research/backward_lowbit_ranks.csv
/home/user/venv/krakken/bin/python krakken_research/verify_backward_parities.py
```

Exploratory producer commands, **not independent certification**:

```bash
/home/user/venv/krakken/bin/python krakken_research/two_round_probe.py
/home/user/venv/krakken/bin/python krakken_research/two_round_fourier.py
```

`resume.json` now records the completed verification and remaining research limits.
No original C or historical ledger was modified. A development-time undefined
slice variable in `backward_bridge.py` was caught before any result was produced,
fixed, and the entire bridge computation then passed the independent C checks.

### KRAKKEN-NOTE-009: a verified two-complete-round endpoint bound

Completed 2026-11-09 after the user requested resumption. The pending finite
enumeration has now been reproduced independently against the original C,
and the mixed-character argument below handles all mask cases. This is a
computer-assisted theorem for the supplied permutation, not a claim of
literature novelty or an externally peer-reviewed security assessment.

#### Statement and precise scope

Number the original indexed round functions R_0 through R_7. Let Gamma be
the 2,048-bit difference with **only bits 93 and 1233 set**, numbering bit
`64*j+k` as bit k of state word j. This is Gamma(0x0800) in NOTE-007.
For every r in {0,...,6}, every nonzero input difference a confined to one
byte of the full state, and X uniform on all 2,048-bit states,

```
Pr[R_(r+1)(R_r(X)) XOR R_(r+1)(R_r(X XOR a)) = Gamma]
    <= (1 + epsilon)/2
    < 1/2 + 2^-56,

epsilon = (3087/2)^2 * (71/512)^27
        approximately 1.6244252693662017e-17.
```

There are 256*255 = **65,280** such input differences. The intermediate
difference is completely unrestricted: this is an endpoint bound across
**two complete rounds**, including Pressure and its carries in both rounds.
The numerical ceiling is just above one half; the small additive correction
is **not a 56-bit differential exponent**. The result concerns this specific
full-state target, not arbitrary targets, the extracted digest, H159 bases,
or an eight-round marginal endpoint probability.

#### 1. Mixed byte and serial-Chi character lemma

Let S be the original byte S-box, with dot products over GF(2), and define

```
M_d(p,p') = E_x (-1)^(p dot S(x) XOR p' dot S(x XOR d)).
```

Exhaustive exact transforms over all 255 nonzero d and all 65,535 nonzero
mask pairs establish `abs(M_d(p,p')) <= 32/256 = 1/8`. This includes pairs
where exactly one mask is zero. For d=0, bijectivity gives M=1 when p=p'
and M=0 otherwise. The independently checked differential uniformity of S
is 4: for d nonzero, any prescribed derivative value occurs at most four
times among the 256 inputs.

Align the byte rotation in one serial-Chi cell. For uniform independent
input bytes A,B, write x=A XOR B and y=B XOR S(x). This is a bijective
change of coordinates, so x,y are also independent uniform bytes. With
fixed input differences da,db and d=da XOR db, the two cell output pairs are

```
(S(x), S(y)),
(S(x XOR d), S(y XOR db XOR S(x) XOR S(x XOR d))).
```

Suppose d is nonzero. For ANY output masks lambda=(p,q), mu=(p',q'),
not both zero, the absolute mixed-character expectation is at most
`rho = 71/512`. To prove this, condition on x and put
`e(x)=db XOR S(x) XOR S(x XOR d)`:

- If q=q'=0, at least one of p,p' is nonzero. Averaging over x gives
  the byte mixed-character bound 1/8.
- If q differs from q', the inner y expectation is zero when e=0,
  and has magnitude at most 1/8 when e is nonzero. Its average, even
  multiplied by the first-output sign depending on x, is at most 1/8.
- If q=q' is nonzero, the inner expectation is 1 when e=0 and has
  magnitude at most 1/8 otherwise. The DDT bound gives `Pr[e=0]<=4/256`.
  The triangle inequality therefore gives
  `4/256 + (252/256)*(1/8) = 71/512`.

These exhaust the cases. For d=0, or when both cell masks are zero, use
the trivial bound 1. No independence of e(x) and the first-output sign
is assumed. The lemma permits DIFFERENT Fourier characters on the two
executions, which is essential for the double Fourier expansion below.

#### 2. Necessary backward parity and exact forward Boolean function

Let T undo InkCloud and the fixed odd-word Pressure output rotations on
differences, and let m be the 22-bit parity mask listed in NOTE-008.
Define the linear functional `ell(z)=m dot T(z)`. The verified backward
affine-support calculation in NOTE-008 proves, for every indexed round,

```
R_(r+1)(z) XOR R_(r+1)(z') = Gamma  implies  ell(z XOR z') = 0.
```

The affine constant is zero. This implication holds for every state pair;
it is not inferred from sampled replays. Define
`h_r(X)=(-1)^ell(R_r(X))`. The desired two-round event is consequently a
subset of `h_r(X)*h_r(X XOR a)=1`.

Write L for the invertible linear prefix Theta/MDS/Rho/Pi, C for serial
Chi, and B for Butterfly. Up to a constant sign from the round constant,
`h_r(X)=G(B C L X)`. G is the parity sign of the selected low three bits
of the unrotated Pressure outputs. It factors into eight functions on
disjoint nine-bit sets. In even pair c, let a,z be the low three input
bits of words 4c and 4c+2, and let h be bits 17..19 of word 4c+2. The
relevant Pressure outputs are exactly

```
u = (a + (z XOR h)) mod 8,
v = (z + u) mod 8.
```

The left shift by 31 cannot affect these low bits. The parity masks
`(pu,pv)` for c=0..7 are
`[(3,4),(1,1),(5,4),(0,3),(7,1),(4,5),(1,0),(4,7)]`.
Each factor is `(-1)^((pu dot u) XOR (pv dot v))`. Round constants only
contribute a fixed sign, which cancels in the product of two executions.

#### 3. Exhaustive Fourier certificate

Use normalized Fourier coefficients. Exhaustion of each factor's 512-entry
truth table gives:

| Quantity | Values for the eight factors |
|---|---|
| Nonzero Fourier coefficients | 40, 1, 13, 4, 10, 13, 1, 13 |
| Unnormalized Walsh L1 sum | 3072, 512, 1792, 1024, 1536, 1792, 512, 1792 |
| Normalized Fourier L1 norm | 6, 1, 7/2, 2, 3, 7/2, 1, 7/2 |

Since the factors use disjoint input bits, their Fourier product has
exactly **3,515,200** nonzero characters and L1 norm **3087/2**. Pulling
characters back through the invertible B preserves this norm and support
size. Exhaustion of every pulled-back character establishes that every
character has a nonzero output mask on at least **124 of the 128
serial-Chi cells**. The first character attaining 124 has enumeration
index 439420 in both implementations.

Independently applying the original C prefix to every single-byte input
difference establishes that at least **31** cells have nonzero first-call
difference d=da XOR db. Thus, for each Fourier character lambda, at least
`124+31-128=27` cells have BOTH nonzero lambda mask and nonzero d.

#### 4. Compose the mixed-character bounds

Expand `G(B C L X)` on each execution, with coefficients c_lambda and
c_mu. For any character pair lambda,mu, the 27 cells selected using
lambda satisfy the local lemma regardless of mu. All remaining cells
have absolute expectation at most 1. Since X is uniform and L is
invertible, the 128 pre-Chi base cells are independent and uniform;
the fixed difference L(a) does not change this. Therefore each mixed
expectation in the double expansion has absolute value at most rho^27.
Triangle inequality gives

```
abs(E_X h_r(X)*h_r(X XOR a))
 <= sum_(lambda,mu) abs(c_lambda)*abs(c_mu)*rho^27
  = (3087/2)^2*(71/512)^27 = epsilon.
```

For a sign-valued product, the probability that it equals 1 is
`(1+E[h_r(X)*h_r(X XOR a)])/2`. Applying the necessary backward parity
proves the stated endpoint bound. Exact rational arithmetic verifies
`epsilon < 2^-55`, hence `(1+epsilon)/2 < 1/2+2^-56`.
The exact numerator and denominator are archived in
`two_round_verified_results.json`.

The only product of expectations here is across independent cells of
ONE uniformly based Chi layer. There is no multiplication of round
differential probabilities, no conditioning-and-uniformity assumption,
and no enumeration or restriction of the middle difference.

#### 5. Broader input class and a valid eight-round joint consequence

The proof actually requires only that t(a), the number of nonzero
first-call difference bytes after L, be at least 31. It therefore covers
every full-state difference satisfying that criterion, not just the
single-byte class. The coordinate map from a to the 128 first-call
difference bytes and 128 companion bytes is invertible. The number of
differences outside this sufficient class, including zero, is exactly

```
2^1024 * sum_(k=0)^30 binomial(128,k)*255^k.
```

As a fraction of all 2^2048 differences this is strictly less than
`2^-687`, verified with integers. This counting fact does not provide a
worst-case bound for attacker-chosen exceptional differences, and does
not enlarge the set of final targets covered by the theorem.

For an eight-round execution with any fixed original input difference,
write Delta_j for the difference after j complete rounds. For every
fixed a satisfying t(a)>=31, the theorem also implies

```
Pr_uniform_X[Delta_6=a AND Delta_8=Gamma] <= (1+epsilon)/2.
```

The intermediate Delta_7 is unrestricted. To justify this corollary,
the unconditioned first execution after six rounds is uniform by
bijectivity. The displayed joint event is a subset of the two-round
fixed-input-difference event for that uniform base. Conditioning on
Delta_6=a is neither required nor asserted to preserve uniformity.
This remains a JOINT event bound, not an eight-round marginal bound.

#### Independent verification and reproduction

`verify_two_round.c` includes the unchanged original `krakken.c`. It
reconstructs the spectra and Butterfly transpose itself, without loading
Python-generated Fourier masks. GCC and Clang give identical results.

| Check | Result |
|---|---|
| All nonzero-d byte mixed Walsh tables | Maximum absolute coefficient 32 |
| Original S-box DDT | Maximum nonzero-input entry 4 |
| Additional direct byte-sum checks | 1,020 passed |
| Original C low-bit Pressure evaluations | 4,096 passed |
| Local spectra compared with Python | All 8 complete spectra identical |
| Product-spectrum cell-support records | All 3,515,200 identical |
| Single-byte first-call activity counts | All 65,280 identical; minimum 31 |
| Direct 16-bit serial-cell checks | 72 passed; supplemental to the lemma |
| Indexed two-round windows versus original prefix API | 28 passed across all 7 windows |
| Constructed final-Gamma pairs via inverse, replayed in original C | 28 passed |
| Forward Boolean identity on original-C state pairs | 1,792 passed across all 7 windows |

The last four rows are implementation consistency checks; they are not
statistical estimates or substitutes for the proof. The local finite
certificates are exhaustive where explicitly stated. The source identity
follows algebraically from the displayed low-bit formulas and cancellation
of constants; sampled replays additionally check indexing and alignment.

Reproduce from the repository root, retaining the existing producer data:

```bash
mkdir -p krakken_research/bulk
gcc -O3 -march=native -pthread krakken_research/verify_two_round.c -o krakken_research/verify_two_round_gcc
krakken_research/verify_two_round_gcc krakken_research/bulk/two_round_support_c.bin krakken_research/two_round_spectra_c.bin krakken_research/two_round_first_active_c.csv > krakken_research/verify_two_round_gcc.log
/home/user/venv/krakken/bin/python krakken_research/verify_two_round.py
/home/user/venv/krakken/bin/python krakken_research/two_round_source_checks.py
/home/user/venv/krakken/bin/python krakken_research/update_bulk_manifest.py
/home/user/venv/krakken/bin/python krakken_research/seal_evidence.py
```

`verify_two_round.py` compares all producer/C outputs, independently builds
and runs the Clang checker, compares all its output files, and checks the
probability arithmetic exactly. Its report and both compiler logs are
archived. `two_round_source_checks.py` records the source/coordinate checks
in `two_round_source_checks.json`. The raw C support certificate has
112,486,400 bytes and SHA-256
`b32a603736c7fa87133a7a24854de7e58e1bbe96ce871adeb56643565b992bc9`.
It remains in `bulk/`, with its reproduction instructions recorded in
`bulk_artifacts.json`; the equivalent Python `.npy` is included in the ZIP.

This completes the theorem that was pending at the usage pause. No solver
campaign or new statistical sample was required. Further progress toward
an eight-round marginal bound would require controlling the unrestricted
middle differences, or a stronger multi-round argument; NOTE-009 alone
does not supply that step. The original permutation and historical ledgers
remain unchanged.


### NOTE-010 import and local replay

The user supplied `note10/Krakken_with_NOTE_010.md` and its evidence archive.
The NOTE-010 statement below is preserved from the companion standalone note,
whose SHA-256 is `87f13c500529c420e527b71ed5eeb687ec6912fb956aa152f344af933b953d34`.
The original supplied files remain unchanged. `replay_note010.py` reproduced
the source-based rank, all local spectra, all three exhaustive product scans
under GCC and Clang, the 65,280 input-activity checks, the 48 affine-offset
replays, and the exact rational bound. All passed; see `note010_replay.json`.
The three scans cover 692,224,000, 104,857,600, and 3,515,200 characters.
The dependence-safe proof was reviewed and its scope retained. The forward
character-count facts are superseded for our new bound by smaller affine
certificates in NOTE-011, but NOTE-010 remains a valid stronger result than
NOTE-009 for its stated wider input class.

# KRAKKEN-NOTE-010 — Two-parity, two-complete-round endpoint differential bound

**Created:** 2026-11-09  
**Scope:** The original unchanged Krakken-2048 scalar source (`krakken.c` / `krakken.h`); all seven adjacent pairs of indexed rounds; uniform unrestricted 2048-bit bases; fixed final difference `Gamma` with exactly state bits **93 and 1233** set.  
**Classification:** Source-pinned analytic proof with exhaustive finite Fourier/support computations and cross-compiler audits performed in this investigation. Not an externally peer-reviewed statement, a global security level, or a hash-domain bound.  
**Relationship to previous work:** Strengthens Astra's NOTE-009 for the same specific target `Gamma`. Depends on the NOTE-008 inverse-Chi derivative affine-support fact and the NOTE-009 mixed-character lemma, both treated as established historical premises; reconstructs the relevant ranks and forward finite spectra independently.

## Statement

Write `R_0,...,R_7` for the original indexed full rounds. Let `a` be any nonzero full-state XOR difference supported in one byte, and let `X` be uniform over all `2^2048` states. For each `r=0,...,6`, define

`D = R_(r+1)(R_r(X)) XOR R_(r+1)(R_r(X XOR a))`.

Then

```text
Pr[D = Gamma] <= (1 + E0 + E1 + E01)/4 < 1/4 + 2^-44,

E0  = 21168^2 * (71/512)^25,
E1  =  9216^2 * (71/512)^29,
E01 = (3087/2)^2 * (71/512)^27.
```

The exact excess over 1/4 is approximately `3.9726855804559335e-14`; thus the numerical ceiling is approximately `0.2500000000000397268558`.

**Wider quantified input class:** The same result holds for every nonzero input difference `a` for which at least 31 first-call byte differences are nonzero after applying the original invertible linear prefix `L` and aligning the first S-box inputs in serial Chi. It is **not** a bound for every possible attacker-chosen full-state difference.

**Not asserted:** no statement about other endpoint differences, H159 padded-message bases, the 256-bit digest differential distribution, a marginal eight-round endpoint event, all differential hulls, or classical/quantum attack complexity. The value 44 is an additive-error exponent, **not 44 security bits**.

## Backward affine constraints — the two bits of information

The predecessor difference of `Gamma` through one complete inverse round has a restricted affine support. For `Gamma=Gamma(0x0800)`, NOTE-007 shows a deterministic inverse-Pressure translation. Its fixed inverse-Butterfly post-Chi difference activates exactly 56 inverse byte S-box derivatives. Their individual derivative-value supports have full eight-dimensional affine spans. The resulting 448-dimensional direction space, mapped through `L^-1` and projected onto the 96 low-three-bit coordinates of the 32 **unrotated Pressure output words**, has **rank 94**.

A fresh elimination of the exact 96-by-448 projected basis produced the following two independent annihilating parity masks, with `(word, bit)` addressing those unrotated Pressure output coordinates:

**q0** (24 positions):

```text
    (2,0), (2,1), (2,2), (4,1), (6,0), (6,1), (8,2), (10,1)
    (10,2), (12,0), (12,2), (16,1), (18,1), (20,0), (20,1), (20,2)
    (22,2), (24,0), (24,1), (26,0), (26,2), (28,1), (28,2), (30,1)
```

**q1** (26 positions):

```text
    (0,0), (0,1), (2,0), (2,1), (4,0), (4,1), (6,1), (8,0)
    (10,1), (12,0), (12,2), (14,0), (14,1), (16,0), (16,2), (18,0)
    (18,1), (20,0), (20,1), (22,0), (24,1), (26,0), (26,2), (28,1)
    (30,0), (30,2)
```

Their XOR `q01 = q0 XOR q1` has 22 positions and is exactly the necessary parity listed in NOTE-008:

```text
    (0,0), (0,1), (2,2), (4,0), (6,0), (8,0), (8,2), (10,2)
    (14,0), (14,1), (16,0), (16,1), (16,2), (18,0), (20,2), (22,0)
    (22,2), (24,0), (28,2), (30,0), (30,1), (30,2)
```

Choose the post-Chi base state zero and its paired post-Chi state differing by the prescribed inverse-Butterfly vector; invert Chi and `L` to construct one valid predecessor pair. The corresponding affine syndromes are **q0·Delta = 1, q1·Delta = 1, q01·Delta = 0**. These syndromes are universal for the fixed target because the masks annihilate all affine-hull directions; the single constructed pair determines their fixed offsets. Forty-eight constructed full-round pairs under original scalar C were also checked and all gave the required complete-round target and same syndrome. Round constants cancel in the difference.

Therefore a two-round execution whose final difference is `Gamma` necessarily satisfies **both** parity equations on the intermediate difference. The intermediate difference is otherwise unrestricted.

## Forward correlations: finite Fourier certificate

Let `T(z)` undo the output InkCloud and Pressure output rotations, so `T` exposes the unrotated Pressure output bits. Define the sign functions on first-round outputs `h_i(z) = (-1)^(q_i · T(z))`, for `i=0,1`, and `h_01 = h_0 h_1`. On complete first-round outputs the relevant functions reduce, up to a fixed sign from Iota, to Boolean functions of the eight **even** Pressure pairs. Their low-three-bit equations are exact:

```text
u = (a + (z XOR h)) mod 8,
v = (z + u) mod 8,
```

where `a` is the low three bits of word `4c`, `z` the low three bits of word `4c+2`, and `h` bits 17–19 of word `4c+2`. Every even pair factor is a sign of `(p_u·u XOR p_v·v)` for explicit local three-bit masks. These depend on disjoint sets of nine Pressure-input bits, so their normalized Fourier coefficients factor exactly over the eight pairs. Both the Python Walsh implementation and a separately written direct C Walsh/Butterfly-transpose implementation produced byte-for-byte identical Fourier-mask tables.

| Nonzero backward parity | Product Fourier support | Normalized Fourier L1 | Minimum nonzero serial-Chi cell masks | Minimum guaranteed overlap with active first S-boxes |
|---|---:|---:|---:|---:|
| `q0` | 692,224,000 | 21,168 | 122 | 25 |
| `q1` | 104,857,600 | 9,216 | 126 | 29 |
| `q01` | 3,515,200 | 3,087/2 | 124 | 27 |

The independent Python truth-table code gives the eight per-pair Fourier supports:

```text
q0 : 40, 4, 13, 10, 4, 13, 40, 16
q1 :  4, 4,  4, 16,16,  4, 40, 40
q01: 40, 1, 13,  4,10, 13,  1, 13
```

The **complete** product supports of 692,224,000, 104,857,600, and 3,515,200 characters were scanned. On each character, its transpose-pulled-back 2048-bit mask was grouped into 128 aligned 16-bit serial-Chi cells, and the number of nonzero cells was counted exactly. GCC and Clang independently compiled the exhaustive scanner and agreed on the minima 122, 126, and 124. A separately authored C generator derived the same 93,024-byte primitive mask tables as the Python producer, without loading Python Fourier masks.

The original-C scalar linear prefix was separately evaluated on all `256*255=65,280` single-byte nonzero input differences. The minimum number of nonzero first-call difference bytes was **31**, checked under GCC and Clang. For any Fourier character from row i, at least `min_support_i + 31 - 128` cells both carry a nonzero character mask and have a nonzero first-call difference. That yields the respective guaranteed overlaps **25, 29, 27**.

## Dependence-safe probability proof

Set `rho=71/512`. The previously established NOTE-009 local mixed-character lemma states that when a serial-Chi cell has nonzero first-call difference, the mixed expectation for ANY two output-mask characters (with at least one nonzero) has absolute value at most `rho`. Characters are permitted to differ between the two executions. Other cells may be trivially bounded by one.

Because the first base state is uniform and `L` is invertible, the 128 serial-Chi base cells are uniform and mutually independent **within this one round**. There is no assumption that the middle difference is uniform or independent of the first execution.

For `i` among `0,1,01`, write `H_i(X)=h_i(R_r(X))`. Expand both `H_i(X)` and `H_i(X XOR a)` as Fourier series in the post-Butterfly Pressure input, pulling their masks backward through Butterfly. For each pair of Fourier characters `lambda,mu`, the first character `lambda` alone guarantees `k_i` contributing Chi cells independently of the other character. The local lemma and independence across Chi cells give

```text
| E[chi_lambda(X) * chi_mu(X XOR a)] | <= rho^k_i.
```

The triangle inequality over the **double** Fourier expansion then yields

```text
| E[H_i(X) * H_i(X XOR a)] | <= L1_i^2 * rho^k_i = E_i.
```

Define `sigma_i=H_i(X)H_i(X XOR a)`; these are signs `+1/-1`, and `sigma_01 = sigma_0 sigma_1`. The fixed-target two-round event implies `sigma_0=-1` and `sigma_1=-1`. The indicator for satisfying **both** conditions is

```text
1{sigma_0=-1 and sigma_1=-1}
   = (1 - sigma_0 - sigma_1 + sigma_01)/4.
```

By event inclusion, taking expectations, and bounding all three nontrivial signed correlations absolutely,

```text
Pr[D=Gamma]
 <= (1 + |E sigma_0| + |E sigma_1| + |E sigma_01|)/4
 <= (1 + E0 + E1 + E01)/4.
```

Exact rational arithmetic proves the claimed `<1/4+2^-44`. **We never multiply probabilities from different Krakken rounds.** The two-round intermediate difference is summed over in the endpoint event.

## Eight-round joint corollary (not marginal)

For any fixed original full-state difference `alpha`, let `Delta_j` be its paired-execution difference after `j` original complete rounds. Then for every fixed `a` with at least 31 active aligned first-call difference bytes,

```text
Pr_uniform_original_X[Delta_6 = a AND Delta_8 = Gamma]
  <= (1 + E0 + E1 + E01)/4 < 1/4 + 2^-44.
```

Proof: `R_5∘...∘R_0(X)` is unconditionally uniform because the six-round prefix is bijective. The joint event is included in the fixed-`a` two-round event for that uniform first-execution base. This does **not** assert that the base remains uniform when conditioned on `Delta_6=a`. Summing over `a` without controlling its distribution does not produce a useful eight-round marginal probability bound.

## Audit record and reproduction

Original source SHA-256:

- `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
- `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`

Evidence: `KRAKKEN_NOTE_010_EVIDENCE.zip` (see its `README.md` for the exact commands). Main files:

- `explore_krakken_ranks.py` — original scalar source-based `L` matrix/inverse, inverse Butterfly translation, 448-direction affine hull, 96-bit projection, rank and two independent parity masks.
- `verify_low3_affine.py` — 48 constructed complete-round input pairs through unchanged original C, verifying target Gamma and universal affine offsets after established affine-support lemma.
- `explore_spectra.py` + `prepare_chi_spectra.py` — independent Python truth tables/Walsh coefficients and exact Butterfly transposed primitive masks.
- `verify_note010_independent.c` — separately implemented C truth tables, Walsh transform, and transpose; raw primitive masks are equal byte-for-byte to Python output.
- `scan_chi_support.c` — exhaustive product spectrum min-support calculation; GCC/Clang agree.
- `verify_note010_first_active.c` — all 65,280 one-byte differences checked against the scalar source; GCC/Clang agree.
- `check_note010_bound.py` — exact rational calculation.

The exhaustive finite computations are not a replacement for the analytical argument, and this work has not received independent external peer review. It is a documented in-session computer-assisted theorem, respecting its explicit scope.

## Next attack/research decision

A follow-up source-derived exploration of the same fixed final Gamma shows the 128-dimensional **low-four-bit** predecessor projection has affine rank **118**, hence 10 independent linear constraints; the low-three-bit result has only 2. This 128×448 rank calculation has not yet received the same standalone independent audit as NOTE-010 and is **not** promoted as a new theorem here. A natural next step is to select a low-cost third/fourth parity, bound their entire signed joint distribution (all `2^k-1` nonzero characters) through compressed/tensorized Fourier support enumeration, and seek `1/8`, `1/16`, or stronger bounds. Merely counting additional constraints is not enough. Any wider endpoint-security claim additionally requires covering more than this one selected Gamma or establishing a rigorous suffix transition bound across more rounds.

### KRAKKEN-NOTE-011: eight backward parities and a stronger two-round bound

Completed in the continuation reviewing NOTE-010. The low-four-bit rank and
parity extension proposed there has now received an independent source-based
audit. A different Fourier certificate avoids enumerating the enormous
product spectra: affine hulls certify individual nonzero cell masks and
groups in which two masks cannot vanish together. These certificates support
eight simultaneous backward constraints and the bound below.

#### Statement

Keep the original round functions R_0,...,R_7 and Gamma with only full-state
bits **93 and 1233** set. For every r=0,...,6, every nonzero full-state
difference a supported in one byte, and uniform unrestricted 2,048-bit X,

```
Pr[R_(r+1)(R_r(X)) XOR R_(r+1)(R_r(X XOR a)) = Gamma]
 <= 303976528439193 / 72057594037927936
  = 303976528439193 / 2^56
  approximately 0.004218521760235197
  < 0.004219 < 1/237 < 2^-7.
```

All **65,280** single-byte differences and all seven adjacent indexed
two-round windows are covered. The middle difference is unrestricted and
summed over. Both rounds are complete, including Pressure and its carries.
The negative base-two logarithm of this ceiling is approximately **7.8890467**.
This is a differential-probability exponent for the stated event, not a
global security level, attack-work exponent, or 56-bit security claim.
The improvement over NOTE-010's ceiling is approximately **59.26-fold**.

The final target is one specific 2,048-bit difference. The theorem does not
cover arbitrary final targets, the extracted digest, H159 padded-message
bases, or an eight-round marginal endpoint event. In particular, the wider
`t(a)>=31` input class in NOTE-010 is not automatically inherited: this
stronger bound uses the exact locations of the active first-call bytes for
the single-byte input class.

#### The eight parity masks and the backward implication

As before, T undoes InkCloud and the odd-word Pressure output rotations.
The relevant coordinates are the low four bits of each unrotated Pressure
output word. For a compact 64-bit mask M below, define a 2,048-bit parity
mask q by

```
q[word 2j]   = (M >> (4*j)) & 15,  j=0,...,15,
q[word 2j+1] = 0.
```

Thus each hexadecimal digit specifies the low-four-bit mask of one even
word, with the least significant digit belonging to word zero. These eight
masks are linearly independent:

| i | Compact M_i | Required syndrome c_i |
|---|---|---:|
| 0 | `5706322518f14001` | 1 |
| 1 | `25f6a8800d7a6002` | 1 |
| 2 | `263758c061457404` | 0 |
| 3 | `40935ac6a3a71608` | 0 |
| 4 | `775a68a52fd48020` | 0 |
| 5 | `51092f872ab0b250` | 1 |
| 6 | `57f8e1350f7e8310` | 1 |
| 7 | `35bf51412975fc90` | 0 |

For EVERY state pair z,z' and every indexed suffix round,

```
R_(r+1)(z) XOR R_(r+1)(z') = Gamma
 implies q_i dot T(z XOR z') = c_i for all eight i.
```

Proof of the implication: inverse Pressure gives the fixed translation
from NOTE-007; inverse Butterfly gives a post-Chi difference activating
56 inverse S-box derivatives. The predecessor affine hull therefore has
448 directions before projection, as proved in NOTE-008. Its projection
onto the 128 low-four-bit coordinates has rank **118**. The independent
C checker verifies all 2,048 inverse-prefix columns against original C,
constructs all 448 projected directions, reproduces rank 118, and checks
that a ten-dimensional parity basis annihilates them. It checks the basis
rank as well. The eight masks above are independent combinations of that
basis. A direct inverse-Chi calculation determines the affine offsets and
agrees with every producer syndrome. This proves universality of the
implication; the additional source replays are implementation checks.

The selected coefficient subspace is the annihilator of labels **464 and
640** in the ten-dimensional basis archived in
`multiparity_probe_k4.json` and `multiparity_certificate.bin`. One independent
generating set is `[1,2,4,8,32,80,272,656]`. Its 255 nonzero elements give
all nontrivial characters needed for the joint eight-bit distribution.

#### Low-four-bit Pressure spectra and their affine relaxations

For any one of the 255 nonzero combined parity masks q, let

```
H_q(X) = (-1)^(q dot T(R_r(X))).
```

Up to a fixed sign from the round constant, H_q is a function of B C L X,
where L is the linear prefix, C is serial Chi, and B is Butterfly. The
function factors over eight even Pressure pairs. Each factor depends on
twelve bits: low four bits a,z of the two words and bits 17..20, h, of
the second word. Its exact equations are

```
u = (a + (z XOR h)) mod 16,
v = (z + u) mod 16,
factor = (-1)^((p_u dot u) XOR (p_v dot v)).
```

All 4,096 local inputs and all 256 choices `(p_u,p_v)` are evaluated and
Walsh-transformed exactly. Original C independently verifies the truth
tables and spectra. If w_c is a factor's unnormalized Walsh table, the
normalized Fourier L1 norm of the full product is exactly

```
L_q = product_(c=0)^7 [ sum_m abs(w_c(m)) / 4096 ].
```

For each local nonzero Fourier support S_c, choose one element s_c and
form the GF(2) span V_c of all `s XOR s_c`, s in S_c. Then
`S_c` is contained in the affine space `s_c + V_c`. After combining the
eight factors and applying B transpose, every actual Fourier character
lies in a known affine space

```
A_q = v_q + span(D_q).
```

This is a SUPERSET relaxation. It need not equal the Fourier support.
Every statement proved for all masks in A_q is therefore valid for every
actual Fourier character. B transpose is reconstructed from all original-C
Butterfly basis images; it does not load producer Fourier masks.

#### Certifying nonzero cell masks without product enumeration

Group each mask in A_q into the 128 aligned 16-bit serial-Chi cells.
There are two elementary, exactly checkable consequences:

1. **Individually guaranteed cells.** Cell j can be zero only if the
   projection of v_q onto that cell belongs to the projected span of D_q.
   If membership fails, that cell is nonzero in EVERY character. Denote
   the certified set of such cells by G_q.
2. **Pairwise exclusions.** Project onto two cells j,k together, a
   32-bit space. If the projected offset is outside the projected span,
   no character can have BOTH cell masks zero. A clique of such pairwise
   exclusions has at most one zero cell mask in any character.

The producer partitions some cells outside G_q into disjoint cliques
`C_(q,1), C_(q,2), ...`. The independent verifier checks every pair in
every supplied clique, verifies disjointness, and verifies that none of
the vertices is already in G_q. Singleton groups contribute nothing and
are omitted. No graph-optimality claim is needed: any checked partition
gives a valid lower bound.

Let A(a) be the fixed set of cells with nonzero first S-box input
difference after applying L to a. For each character in A_q, at least

```
k_q(a) = |A(a) intersect G_q|
       + sum_j max(0, |A(a) intersect C_(q,j)| - 1)
```

cells have BOTH nonzero first-call difference and nonzero character mask.
The reason for each clique term is simply that among its active first-call
cells at most one character mask can vanish. Disjointness prevents double
counting. Cells not certified by either method are safely ignored.

The original C prefix independently generates A(a) for all 65,280
single-byte differences. Every 128-bit activity mask agrees with the
previous archive. There are 34,944 archived activity-pattern records;
the original-C scan covers every input class directly, so the final
bound does not rely on assuming that an unexamined input shares a pattern.

#### Mixed-character bound and the joint probability proof

The NOTE-009 serial-Chi lemma gives absolute mixed expectation at most
`rho=71/512` when the first-call difference is nonzero and at least one
of the two cell output masks is nonzero. The two Fourier characters
may differ. For each pair of characters lambda,mu in the double Fourier
expansion of `H_q(X) H_q(X XOR a)`, lambda alone certifies at least k_q(a)
contributing cells, regardless of mu.

Because X is uniform and L is invertible, the pre-Chi cell bases are
independent and uniform within this one layer. Taking absolute values,
factoring over these cells, and applying the triangle inequality gives

```
abs(E_X H_q(X) H_q(X XOR a))
 <= E_q(a) := min(1, L_q^2 * rho^k_q(a)).
```

Define the eight-bit syndrome of the first completed-round difference by
`W_i = q_i dot T(R_r(X) XOR R_r(X XOR a))`. For any fixed syndrome c,
the character expansion of its indicator is

```
1{W=c} = 2^-8 * sum_(u in GF(2)^8) (-1)^(u dot (W XOR c)).
```

The zero character contributes one; each of the other 255 expectations
is bounded by the corresponding E_q(a). Consequently

```
Pr[W=c] <= [1 + sum_(q nonzero in selected parity space) E_q(a)] / 256.
```

This holds for EVERY syndrome c. The two-round endpoint event for Gamma
is a subset of the event for the particular syndrome in the mask table,
which proves the desired reduction. In particular this is also a
point-probability bound on the selected eight-bit projection of the
one-round difference; its min-entropy is at least approximately 7.889 bits
under the specified base distribution.

All products of expectations are within one independent-cell Chi layer.
No probabilities of different rounds are multiplied, no middle difference
is fixed, and no conditioning on a middle difference is assumed to leave
the base uniform.

#### Exact arithmetic and why the reported numerator is valid

The floating-point search was used only to choose candidate parity spaces.
The promoted result uses integer arithmetic with rigorously upward-rounded
per-character error tables. For each selected q and k=0,...,128, define

```
U_q(k) = ceil(2^48 * min(1, L_q^2 * (71/512)^k)).
```

Every L_q is rational, and every table entry is computed using exact
integers and fractions. The verifier checks all **32,895** selected
entries and proves that the rounding error per entry lies in `[0,2^-48)`.
For each input difference a, form the integer

```
N(a) = 2^48 + sum_q U_q(k_q(a)).
```

Independent C accumulation over all 65,280 input differences and Python
accumulation over the archived activity patterns agree that

```
max_a N(a) = 303976528439193.
```

Dividing by `256*2^48 = 2^56` proves the displayed bound with no
floating-point uncertainty. Original-C GCC and Clang executions produce
identical certificates, activity masks, sums, and witness. The first
maximizing input class in the source scan is **byte 153, value 8**; its
archived activity-pattern index is 20750. This witnesses the maximum of
our CERTIFIED UPPER ESTIMATE, not an actual differential probability and
not an attack attaining that probability.

If one takes the worst input separately for each character before summing,
the same certificate gives the weaker ceiling approximately
0.004492742919871414. Keeping a single common input through the sum is
legitimate and gives the stronger final bound.

The optional exact finite selection analysis considered all **174,251**
eight-dimensional subspaces of this ten-dimensional parity space, using
the same affine/clique certificates. Four rounds of constraint generation
selected the annihilator of labels 464 and 640. This establishes optimality
only among those fixed certified estimates, not among all parity methods
or actual differential probabilities. The theorem requires only the
selected space and its independent verification, not search optimality.

#### Broader input classes with explicit, exact bounds

The certificates also provide bounds for arbitrary differences meeting
an activity threshold. Let `t(a)=|A(a)|` and put

```
K_q = |G_q| + sum_j (|C_(q,j)| - 1).
```

For the selected 255 characters, K_q ranges from **104 to 126**. Removing
one active first-call cell reduces the support certificate by at most one,
so for EVERY difference a,

```
k_q(a) >= max(0, K_q - (128-t(a))).
```

Substituting this lower bound in the already proved correlation formula
gives a deterministic bound for any fixed activity threshold, without
enumerating its input differences. `multiparity_class_bounds.py` evaluates
the resulting rational sums exactly. Selected consequences are:

| Sufficient input condition | Two-round endpoint ceiling for Gamma |
|---|---|
| t(a) >= 31 | `< 7/64` (exact certificate approximately 0.10925742) |
| t(a) >= 40 | `< 2^-8 + 2^-13` |
| t(a) >= 48 | `< 2^-8 + 2^-36` |
| t(a) >= 64 | **`< 2^-8 + 2^-81`** |
| t(a) >= 80 | `< 2^-8 + 2^-127` |

The t>=31 corollary improves NOTE-010 on its wider input class, while the
location-sensitive certificate remains much stronger on the single-byte
class. The t>=64 corollary is essentially an eight-bit differential
exponent for this target; the additive exponent 81 is not a security level.

The linear map from the input difference to its 128 first-call difference
bytes and 128 companion bytes is invertible. Thus the number of full-state
differences failing t(a)>=t, including zero, is exactly

```
2^1024 * sum_(j=0)^(t-1) binomial(128,j)*255^j.
```

For t=64 this count divided by 2^2048 is strictly less than **2^-396**,
as verified using integers. This describes coverage among differences;
an adversary can choose a difference in the excluded set. It does not
upgrade the result to a maximum over all differences or all output targets,
and it does not make the uniform full-state base assumption valid for H159.

#### Eight-round joint corollary and the remaining composition obstacle

For any fixed original input difference alpha and any fixed nonzero
single-byte difference a, let Delta_j denote the paired-execution difference
after j complete original rounds. Then

```
Pr_uniform_X[Delta_6=a AND Delta_8=Gamma]
 <= 303976528439193 / 2^56.
```

Delta_7 is unrestricted. The first execution after six rounds is
unconditionally uniform by bijectivity, and the joint event is included
in the fixed-a two-round event for that base. This does not claim
uniformity after conditioning on Delta_6=a.

This corollary still does not bound the marginal event `Delta_8=Gamma`:
Delta_6 can range over many differences, most outside the single-byte
class, and naive summation is vacuous. Nor can the two-round ceiling be
raised to the fourth power. Extending the result to three or eight full
rounds requires a dependence-safe argument for the preceding rounds or
control of the boundary differences. The new certificates make the
two-round calculation much cheaper, but do not resolve that separate
composition problem.

The broader activity corollaries similarly give joint bounds with
`Delta_6=a` for any fixed a satisfying their threshold. They also cannot
be summed over the unrestricted boundary difference without losing the
useful bound.

#### Verification record, files, and reproduction

| Independent check | Result |
|---|---|
| Supplied NOTE-010 reproduction | All finite checks and exact bound passed |
| Inverse-prefix columns checked through original C | All 2,048 passed |
| Low-four-bit backward projection | Rank 118; 10 independent annihilators |
| Low-four-bit local Pressure inputs | All 4,096 passed |
| Local Walsh spectra | All 256 local mask pairs checked |
| Combined affine Fourier certificates | All 1,023 nonzero ten-bit labels checked |
| Pairwise exclusions used by clique certificates | All 33,809 checked |
| Full input activity masks | All 65,280 match original C and prior archive |
| Selected rational rounding-table entries | All 32,895 verified upward |
| Integer bound accumulation | Python, GCC, and Clang agree exactly |
| Indexed windows versus original prefix API | 28 checks across all 7 windows |
| Constructed target-Gamma state pairs | 28 replays across all 7 windows |
| Eight-parity forward source identity | 1,792 pair checks across all 7 windows |

The source replays are supplemental consistency checks, not statistical
evidence for the theorem. The proof rests on the algebraic reductions and
the exhaustive finite certificates explicitly described above. Original
scalar, header, and AVX2 SHA-256 fingerprints still match the initial record.
The historical ledgers and supplied NOTE-010 files are unchanged.

Primary new evidence:

- `multiparity_probe.py`: constructs the low-four-bit nullspace and local
  affine Fourier relaxations; its report preserves the discovery data.
- `multiparity_pairs.py`: builds disjoint-clique certificates.
- `multiparity_certificate.bin`: the ten parity masks and all clique lists.
- `verify_multiparity.c`: independently reconstructs local truth tables,
  Fourier affine hulls and transpose rows from original C; checks the
  backward constraints, certificates, and all input classes.
- `multiparity_bound.py`: computes exact rational upward tables and the
  final bound for the selected space.
- `verify_multiparity.py`: builds both compilers, compares all outputs,
  verifies the rational tables, and checks the exact bound.
- `multiparity_verified_results.json`, both compiler CSV/log files, and
  `multiparity_source_checks.json`: completed verification reports.
- `multiparity_class_bounds.py` and its JSON report: exact arbitrary-input
  activity-threshold bounds and excluded-difference counts.
- `optimize_multiparity.py` and its report: finite parity-space selection,
  which is unnecessary to trust or reproduce the selected theorem.

With the archived certificates, reproduce the theorem checks directly:

```bash
/home/user/venv/krakken/bin/python krakken_research/multiparity_bound.py
/home/user/venv/krakken/bin/python krakken_research/verify_multiparity.py
/home/user/venv/krakken/bin/python krakken_research/multiparity_source_checks.py
/home/user/venv/krakken/bin/python krakken_research/multiparity_class_bounds.py
```

To regenerate discovery certificates from the previously verified matrices:

```bash
/home/user/venv/krakken/bin/python krakken_research/multiparity_probe.py 4
/home/user/venv/krakken/bin/python krakken_research/multiparity_pairs.py
/home/user/venv/krakken/bin/python krakken_research/prepare_multiparity_certificate.py
/home/user/venv/krakken/bin/python krakken_research/multiparity_bound.py
/home/user/venv/krakken/bin/python krakken_research/verify_multiparity.py
```

Replay the supplied NOTE-010 using `replay_note010.py`; it extracts the
unchanged supplied evidence archive if needed. No replacement statistical
sample was generated, no long solver campaign was started, and no original
permutation source was modified. All work for NOTE-011 is complete. Further
research can extend the certified target/input classes, improve the affine
relaxations, or attempt a new multi-round composition argument; none of
those extensions is asserted here.


### KRAKKEN-NOTE-012: complete-round linear-hull and restricted multi-round bounds

This was deliberately a small continuation in a different attack family:
linear cryptanalysis. It reuses the independently checked affine Fourier
certificates of NOTE-011, adds an exact serial-Chi linear-character lemma,
and computes new rational bounds. No solver campaign or new random study
was run. The result is a computer-assisted theorem with the scope below.

#### Statements and scope

Let X be uniform over all 2,048-bit states and R_r any original indexed
complete round, r=0,...,7. For full-state masks a,b define normalized linear
correlation by

```
Corr_F(a,b) = E_X (-1)^((a dot X) XOR (b dot F(X))).
```

Let T be the linear output-coordinate alignment used in NOTE-011: undo
InkCloud and the fixed odd-word Pressure output rotations. Let V_8 be the
span of the eight explicit parity masks in NOTE-011's compact-mask table,
and V_10 the full ten-dimensional low-four-bit annihilator space verified
there. Physical full-state output masks are `b=T^transpose q`, q in V_d.
Thus `b dot R_r(X) = q dot T(R_r(X))`.

For EVERY input mask a and every nonzero q in the indicated space,

| Output-mask class | Complete-round absolute linear correlation |
|---|---|
| q in V_8, 255 nonzero masks | **`abs(Corr_Rr(a,T^transpose q)) < 2^-293`** |
| q in V_10, 1,023 nonzero masks | **`abs(Corr_Rr(a,T^transpose q)) < 2^-220`** |

There is no restriction on the weight of a. These are complete-round
LINEAR-HULL bounds, with the internal mask contributions summed; they
are not merely bounds on individual S-box or addition-resolved trails.
The selected output masks are a very small subset of all output masks.
This is not an unrestricted eight-round linear bound, an H159 bound,
a digest bound, or a global claim of 293-bit security.

Two further consequences are proved below:

1. The total signed contribution to an actual eight-round linear hull
   from intermediate masks in this space at the FIRST-round output is
   `<2^-293` for V_8 and `<2^-220` for V_10. All masks deeper in the suffix
   are unrestricted and summed. This is a restricted part of the hull.
2. If an observer receives ONLY the eight selected output parities of
   R_r(X), its advantage over one half in predicting ANY FIXED nonzero
   linear input parity is `<2^-294`, even with arbitrary processing of
   those eight bits. For the ten-bit observation the corresponding
   advantage is `<2^-221`. No side information or conditioned input
   distribution is included in this prediction game.

#### Exact local linear-character lemma

Let the byte S-box normalized LAT be

```
U(r,t) = E_z (-1)^((r dot z) XOR (t dot S(z))).
```

The exhaustive original-source check of all 65,536 byte LAT entries gives
`U(0,0)=1` and `abs(U(r,t))<=1/8` whenever `(r,t)!=(0,0)`.
In particular, entries with exactly one zero mask vanish by bijectivity.
The maximum nontrivial unnormalized entry is 32.

Align the byte rotation in a serial-Chi cell and write its actual mapping
as

```
C(A,B) = (S(A XOR B), S(B XOR S(A XOR B))).
```

For input masks (r,s) and output masks (p,q), its normalized linear
correlation is EXACTLY

```
Corr_C((r,s),(p,q)) = U(r, p XOR r XOR s) * U(r XOR s, q).
```

To prove this, put `x=A XOR B`, `y=B XOR S(x)`. This is a bijective change
of variables, with inverse `B=y XOR S(x)`, `A=x XOR y XOR S(x)`.
The exponent separates into a function of x and a function of y:

```
(r dot x) XOR ((p XOR r XOR s) dot S(x))
XOR ((r XOR s) dot y) XOR (q dot S(y)).
```

Uniform A,B therefore make the expectation the displayed product. If
(p,q) is nonzero, both byte factors cannot be the trivial U(0,0): the
conditions for that would force r=s=p=q=0. At least one factor has
absolute value at most 1/8, and the other is at most one. Consequently

```
abs(Corr_C((r,s),(p,q))) <= 1/8
```

for EVERY input mask and every nonzero output mask. This statement is
about a full local linear hull. It is distinct from NOTE-009's mixed
TWO-execution differential-character lemma with constant 71/512.

The new C checker evaluates all 65,536 cell inputs through original Chi.
It also performs complete 65,536-entry Walsh transforms for 16 specified
output masks, covering zero masks, first-only masks, second-only masks,
and masks active on both outputs. All **1,048,576** resulting input-mask
entries agree with the factorization. These transforms supplement the
algebraic proof; they are not claimed to enumerate the full 2^32 local
LAT. GCC and Clang outputs agree.

#### From the local lemma to a complete-round hull bound

Use the verified notation of NOTE-011. For each nonzero q in V_10,
`(-1)^(q dot T(R_r(X)))`, up to a constant sign, has a Fourier expansion
in the serial-Chi output after pulling the Pressure masks through
Butterfly. Its normalized coefficient L1 norm is the exactly known L_q.
Every actual Fourier character lies in its certified affine relaxation.

Let G_q be the individually nonzero cell masks and let C_(q,j) be the
verified disjoint cliques of pairwise zero exclusions. For EVERY Fourier
character, the total number of nonzero serial-Chi cell masks is at least

```
K_q = |G_q| + sum_j (|C_(q,j)| - 1).
```

This time every cell with a nonzero character mask contributes to the
linear bound: there is no input-difference activity condition. After the
invertible prefix L, a fixed input mask a becomes another fixed mask,
and the base cell coordinates are independent uniform bytes. Applying
the local linear lemma in each of at least K_q cells yields at most
`8^-K_q` for each Fourier character. Summing the full expansion gives

```
abs(Corr_Rr(a,T^transpose q)) <= kappa_q := L_q * 8^-K_q.
```

The coefficient norm appears ONCE, because this is an input/output
linear correlation. NOTE-011's autocorrelation expansion used two
Fourier series and therefore an L1 norm squared; that formula is not
being transferred to this setting.

The certified K_q range is 82..126 over V_10 and 104..126 over V_8.
All values of L_q, K_q, and rational kappa_q are saved in
`linear_hull_character_bounds.json`. Exact fraction arithmetic proves
both the individual bounds above and the stronger aggregate inequalities

```
sum_(q in V_8, q!=0) kappa_q^2  < 2^-586,
sum_(q in V_10, q!=0) kappa_q^2 < 2^-440.
```

These aggregate inequalities are computed directly. They do NOT follow
merely by multiplying the largest individual bound by the number of
masks. For reference, the negative log2 of the aggregate square root is
approximately 293.0422535 for V_8 and 220.0919947 for V_10. The largest
individual certified cap occurs at archived label 329 in V_8 and label
401 in V_10. These are worst certificates, not claims that those actual
correlations attain the bounds.

All indexed rounds obey the same absolute bounds: the round constant
contributes only a fixed sign, and the other round operations are the
same original functions. No key randomization or cross-round
independence assumption is used.

#### A restricted eight-round linear-hull sum, not just one trail

Let `F=G composed with R_0` be the original eight-round permutation, with
`G=R_7 composed with ... composed with R_1`. For fixed endpoint masks a,b,
Fourier composition gives the exact full-hull identity

```
Corr_F(a,b) = sum_beta Corr_R0(a,beta) * Corr_G(beta,b).
```

Let S_d be the nonzero physical masks `T^transpose q` for q in V_d, and
restrict ONLY the first-round intermediate mask:

```
H_(S_d)(a,b) = sum_(beta in S_d) Corr_R0(a,beta) * Corr_G(beta,b).
```

Each Corr_G already includes every internal linear-mask contribution of
all seven suffix rounds. Thus H_(S_d) sums the entire eight-round family
of linear trails passing through S_d at that first boundary.

Parseval gives `sum_beta Corr_G(beta,b)^2 = 1`: the output parity pulled
back through G is a sign-valued function of its uniformly ranged input.
Cauchy-Schwarz and the verified aggregate bounds therefore give

```
abs(H_(S_8)(a,b))  <= sqrt(sum_(q in V_8, q!=0) kappa_q^2)  < 2^-293,
abs(H_(S_10)(a,b)) <= sqrt(sum_(q in V_10, q!=0) kappa_q^2) < 2^-220.
```

This also holds for suffixes of one through six rounds, hence for the
corresponding restricted two- through seven-round hulls. The actual
endpoint correlation includes all intermediate masks OUTSIDE S_d as
well. Their contribution is not controlled by this proof, so these
inequalities must not be described as unrestricted eight-round linear
correlation bounds. Multiplying the one-round ceiling across rounds
would not fix this gap.

#### Limited-observation prediction bound

Fix a nonzero full-state input mask a BEFORE drawing uniform X. Let
`Y=(q_0 dot T(R_r(X)),...,q_(d-1) dot T(R_r(X)))` for a basis of V_d.
The round is bijective and the q_i are independent, so Y is uniform on
all d-bit strings. Let `f(X)=(-1)^(a dot X)` and
`m(y)=E[f(X) | Y=y]`.

The Fourier coefficient of m at nonzero u is exactly the correlation
between f(X) and the corresponding output parity u dot Y, hence is
bounded by kappa_q. Its zero coefficient vanishes because a is nonzero
and X is uniform. Parseval and Cauchy-Schwarz give

```
E_Y m(Y)^2 <= sum_(q!=0) kappa_q^2,
E_Y abs(m(Y)) <= sqrt(sum_(q!=0) kappa_q^2).
```

The optimal prediction success from Y alone is
`1/2 + (1/2)*E_Y abs(m(Y))`. Therefore

```
Pr[guess a dot X correctly from the selected 8 output parities alone]
    < 1/2 + 2^-294,

Pr[guess a dot X correctly from the full 10 output parities alone]
    < 1/2 + 2^-221.
```

This allows arbitrary, even computationally unlimited processing of
those selected observations. It does not allow observing the full
permutation output (which determines X), receiving other side
information, choosing a as a function of the observation, or changing
the base distribution. It is not a hash-preimage security claim.

#### Evidence and reproduction

- `verify_linear_local.c`: original-source byte LAT, all local Chi inputs,
  and selected complete 16-bit LAT transforms; no new model of Pressure.
- `linear_hull_bounds.py`: builds/runs GCC and Clang checks and computes
  every per-character and aggregate bound using exact fractions from the
  previously independently verified affine certificates.
- `linear_hull_character_bounds.json`: all 1,023 rational component caps.
- `linear_hull_results.json`: exact aggregate sums, scope, source hashes,
  and passed verification counts.
- `verify_linear_local_gcc.log`, `verify_linear_local_clang.log`, and
  `linear_hull_bounds.log`: completed run logs.

Reproduce from the repository root with the NOTE-011 certificates present:

```bash
/home/user/venv/krakken/bin/python krakken_research/linear_hull_bounds.py
```

The original permutation files, historical ledgers, supplied NOTE-010
files, and statistical samples remain unchanged. This small run ends
with NOTE-012 complete. An unrestricted multi-round linear-hull bound
would still require control of the complementary intermediate mask
space; that is not claimed solved here.

### Informal per-round estimation request

At the user's request, `ESTIMATION.md` records a speculative per-round
assessment for classical collision and preimage attacks on reduced-round
H159 hashing with a 256-bit digest. It separates transparent slower/working/
faster scenario curves from the actual theorem scopes and explains that no
calibrated per-round attack-work estimate follows from the present evidence.
No new theorem or security level is promoted, and no attack experiment was
run for that assessment. The proved status above is unchanged.

### Collision continuation: KRAKKEN-COLL-001 and KRAKKEN-STAT-002

The user requested actual reduced-round collision experiments and extension
of candidates to the full eight-round hash. `COLLISIONS.md` is the detailed
record. The original H159 padding and first 32 output bytes were retained,
with the first r original indexed rounds for r=1,...,8.

An exhaustive 20-dimensional affine message family (1,048,576 messages)
has no 48-bit projected collisions at any depth, proving full-digest
injectivity on that family. A separate predeclared experiment preserved
262,144 OS-random uniform H159 messages; all eight 64-bit output projections
had no repeats. A distribution-free Poissonization argument then gives a
simultaneous 99%-confidence ceiling of 2^-29 for the probability of equal
digests of independent uniform H159 messages. The predeclared ceiling was
2^-26; 2^-29 is an analytic strengthening using the same pass event and
sample, explicitly identified as such in the report. The rigorous false-pass
upper bound is less than 0.003999. This is not an adaptive collision-attack
work bound or an estimate of bits gained per round.

C and NumPy agree on all 80 truncated-collision count rows and all candidate
lists. Clang regenerated all 10,485,760 checkpoint digests with matching
full-archive SHA-256 hashes. All 2,118 candidate input messages were replayed
through original scalar and AVX2 prefix APIs at every depth, giving 16,944
full-state comparisons; their eight-round digests also match both hash APIs.
There are 927 distinct pairs with 32-bit collisions selected at depths one
through seven; none retains that collision at depth eight. The seven 40-bit
candidate rows are subsets of these pairs. Other 32-bit collisions occur at
eight rounds. No 256-bit digest collision was found in either dataset.

The experiment, proofs, a concrete two-round 40-bit example and its full
eight-round replay, exact per-round counts, statistical limits, source
fingerprints, and reproducibility commands are in `COLLISIONS.md`, supported
by `collision_results.json` and `collision_witnesses.json`. The new sample
is `collision_random_messages.bin`; all previous statistical samples remain
unchanged. The two digest archives remain in `bulk/`, with reproduction
instructions in `bulk_artifacts.json`. No original permutation or historical
ledger was modified. This continuation is complete.

### Separate keyed-permutation construction: Even–Mansour study

On 2026-11-10 the user requested a comparison of Even–Mansour, CENC, and
PMAC, an implementation in `krakken_hardened.c` and `.h`, and deferral of
security experiments to a second pass. The user explicitly confirmed that
the new API may be a separate keyed permutation.

The selected construction is the original two-mask Even–Mansour form,
`E(X)=Krakken(X XOR Kin) XOR Kout`, with two independent secret 256-byte
masks and the complete original eight-round permutation. CENC is a
downstream nonce-based encryption mode and PMAC a downstream authentication
mode, both relying on a keyed primitive; neither is the direct permutation
wrapper requested. Primary references, implementation details, build commands,
and scope are in `KRAKKEN_HARDENED.md`.

This is a keyed adapter, not a demonstrated increase in the strength of the
public hash. For every fixed key under uniform unrestricted full-state bases,
`DP_E(a,b)=DP_P(a,b)` and
`Corr_E(a,b)=(-1)^(a.Kin XOR b.Kout)*Corr_P(a,b)`.
Thus whitening does not improve the original full-state differential table
or absolute linear correlations. Ideal-permutation construction results do
not establish a concrete new Krakken security level. No earlier theorem is
promoted or strengthened by this implementation.

The code exposes forward word and little-endian byte permutation APIs,
explicit initialization and clearing, and optional AVX2 compilation. It
imports 512 raw secret bytes rather than inventing a short-key expansion.
Original permutation and hash sources are unchanged. Small functional/API
checks, distinct whitening-mask vectors, and scalar/AVX2 agreement pass under
GCC and Clang; see `hardened_smoke_results.json`. Cryptanalytic and side-channel
testing remains deferred at the user's request. Evidence for this separate
implementation is packaged in `Krakken_hardened_evidence.zip`; the earlier
research archive remains its historical snapshot.


## Krakken–Kyber Chi-only experiment — 2026-11-10

At the user's request, a separate implementation now lives in
`krakken_kyber/`. It retains the exact original Chi/S-box map, removes all
other original layers, and wraps 1..8 Chi repetitions in Even–Mansour.
A complete locally available CRYSTALS-Kyber KEM establishes the shared secret;
SHAKE256 derives transcript-bound whitening masks. Default Kyber768; full
Kyber512 and Kyber1024 are also supported. Kyber is used during key setup,
not misrepresented as a permutation layer. Original source files are unchanged.

The C API includes key generation, encapsulation, decapsulation, forward and
inverse block transforms, and context clearing. The full local KEM dependency
is imported unchanged with per-file hashes; upstream commit authentication
could not be completed because shell network/DNS access was unavailable.
This is pre-standardization Kyber, not a claim of ML-KEM conformance.
See `krakken_kyber/PROVENANCE.md` for exact provenance and its limitations.

Functional tests pass with GCC for all three Kyber parameter sets and with
Clang address/undefined-behavior sanitizers for Kyber768. LeakSanitizer itself
was disabled because it cannot run under this environment's ptrace conditions.
Each run checks 128 original-source Chi/EM vectors across 1..8 repetitions,
1024 cell-locality cases, inverse/overlap and API behavior, KDF consistency,
and the imported KEM test's 1000 valid, 1000 invalid-secret-key and 1000
invalid-ciphertext cases. Results and commands: `krakken_kyber/TEST_RESULTS.json`.

Four exact structural results are proved in `krakken_kyber/SECURITY.md`:

- KYBER-CHI-001: the new full block map is a direct product of 128 independent
  bijections on 16-bit cells, for every context and every supported depth.
- KYBER-CHI-002: two queries distinguish it from an ideal 2048-bit permutation
  with acceptance-probability gap `1 - (2^16-1)/(2^2048-1)`.
- KYBER-CHI-003: 65,536 chosen-input queries recover all cell tables in parallel,
  reproducing the entire keyed map, with 16 MiB of table storage.
- KYBER-CHI-004: every nonzero single-cell input difference has some exact output
  difference of probability at least `2^-15` under uniform full-state inputs.
  Whitening leaves the Chi-only full-state DDT and absolute LAT unchanged.

These are weakness/attack bounds for the NEW stripped construction, not attacks
on Kyber, not positive security lower bounds, and not results about the original
complete eight-round permutation. The codebook attack is proved but was not
executed in this first implementation pass. Keeping only Chi does not provide
full-state diffusion, regardless of the KEM strength. No earlier security claim
is promoted by this experiment. The source, API guide, logs and proofs remain
in the separate directory; old research/evidence archives are not overwritten.


## Krakken–Kyber v2: exact MDS addition — 2026-11-10

Added the original MDS layer to each experimental round in `krakken_kyber/`,
in the order MDS → Chi. The coefficients are `(01,01,04,01,08,05,02,09)` in
hexadecimal, with the original circulant orientation and field polynomial
`0x11D`. The inverse coefficients are `(04,AF,0E,A4,C2,C2,CB,3E)`. An inverse
round applies inverse Chi followed by inverse MDS. The Kyber KEM and outer
Even–Mansour wrapper remain; no butterfly layer is included in this revision.

The new KDF label is `Krakken-Kyber-MDS-Chi-EM-v2`, and the context marker is
versioned. Both endpoints need fresh v2 contexts. Original full Krakken sources
remain unchanged. The prior Chi-only source, documentation, test logs and hashes
are preserved in `krakken_kyber/history/chi_only_v1.zip` (build files excluded).

Tests establish exact MDS equivalence to `tentacle_mds_scalar` and both inverse
compositions on all 2048 bit basis vectors. Linearity extends these checks to
all inputs. Chi, the composed MDS–Chi core and the EM formula each agree with
original-source references on 128 vectors across 1..8 rounds. Inverse, overlap,
API and KEM tests also pass. All three Kyber parameter sets pass GCC checks;
Kyber768 passes Clang ASan/UBSan with LeakSanitizer disabled for the previously
recorded environment restriction. See `krakken_kyber/TEST_RESULTS.json`.

New exact results, proved in `krakken_kyber/SECURITY.md`:

- MDS-CHI-001: MDS and Chi preserve row `y` and byte position modulo four.
  Thus the new keyed permutation decomposes into 16 independent 128-bit groups
  at every supported depth, even though MDS mixes the old 16-bit cells.
- MDS-CHI-002: two inputs differing only within one such group give a full-state
  PRP distinguisher with acceptance-probability gap
  `1 - (2^128-1)/(2^2048-1)`, including at eight rounds.

All 256 byte perturbation positions at all eight depths were checked (2048
cases) for group confinement; one-round spreading beyond old Chi cells was
also verified. Universal statements follow from the index algebra, not sample
extrapolation. These are structural weaknesses of this reduced construction,
not attacks on the original full permutation or Kyber. The v1 65,536-query
codebook bound is not claimed for v2. Group width does not establish 128-bit
security. Further cross-group diffusion is required for full-state PRP security.


## Krakken–Kyber v3: exact Pressure addition — 2026-11-10

At the user's request, each experimental round now applies MDS → Chi → Pressure.
The Pressure layer preserves `pressure_arx_scalar` exactly: unsigned 64-bit
modular additions, right shift 17, left shift 31, and output rotations 7 and 19
on rows 1 and 3. Its inverse first undoes the rotations, then subtracts the
updates in reverse dependency order. Both directions are exposed through
`krakken_kyber_pressure`; the composed inverse uses Pressure^-1, Chi^-1, MDS^-1.

The KDF label is now `Krakken-Kyber-MDS-Chi-Pressure-EM-v3`; the context marker
is also versioned. Both endpoints need fresh v3 contexts. The complete v2
source/docs/test snapshot (excluding build products) is preserved in
`krakken_kyber/history/mds_chi_v2.zip`; v1 remains archived. Original Krakken
sources and the complete local Kyber dependency are unchanged. Butterfly is
not included in this revision.

Validation passes under GCC for Kyber512/768/1024 and Clang ASan/UBSan for
Kyber768 (LeakSanitizer disabled for the recorded ptrace environment issue).
Pressure agrees with original-source output on 4608 vectors: basis and
complemented-basis inputs, carry-chain patterns and reproducible pseudorandom
inputs. Both inverse compositions pass. Since Pressure is nonlinear, these
are regression checks, not a proof by linear basis; universal inversion follows
from the subtraction algebra in `krakken_kyber/SECURITY.md`. MDS still passes
all 2048 basis comparisons and inverse identities. Chi, composed core and EM
formula each pass 128 original-source vectors across 1..8 rounds, along with
inverse/overlap/API, SHAKE/KDF and full KEM checks. Reports and commands are in
`krakken_kyber/TEST_RESULTS.json`.

Exact new structural findings:

- PRESSURE-CHI-001: the data mapping preserves even and odd rows separately.
  MDS and Chi preserve row indices; Pressure only couples rows 0/2 and 1/3.
  Thus the full keyed map splits into two independent 1024-bit halves at
  every supported round count. These halves are interleaved in serialization.
- PRESSURE-CHI-002: choosing two inputs that differ only in one half yields
  a two-query distinguisher with acceptance-probability gap
  `1 - (2^1024-1)/(2^2048-1)`, including at eight rounds.

Tests check all 256 byte perturbation positions at each depth (2048 cases),
confirming even/odd confinement and observing mixing beyond the old v2 groups.
The universal claims follow from the layer indexing, not these observations.
Pressure adds mixing, but does not connect even to odd rows in this reduced
construction. This does not establish 1024-bit security or a positive attack
cost lower bound. These results concern v3 only, not the original complete
Krakken or Kyber. Prior v1/v2 smaller partitions are not asserted for v3.


## Krakken–Kyber v4: complete original core restored — 2026-11-10

At the user's request, `krakken_kyber` now restores every original round layer:
Theta → MDS → Rho → Pi → Chi → Butterfly → Pressure → Iota → InkCloud.
The production forward core calls the unchanged original
`krakken_permute_scalar_rounds` directly, using the original round indices
0 through r-1, for r=1..8. The static library now includes the original scalar
object and links with pthread support. A full inverse reverses every layer
and processes round indices r-1 down to zero. Its algebra is documented in
`krakken_kyber/SECURITY.md`.

Keccak is included in its exact original role: the complete 24-round
Keccak-f[1600] produces SHAKE128 round constants from the fixed original domain
`Krakken-2048 Abyssal v1 - Primary `, with its trailing space preserved. It is
not a new 1600-bit data layer on the 2048-bit Krakken state. All 256 constant
words, including the zero-word fallback convention, were compared against the
independent SHAKE128 implementation in the Kyber dependency. A 32-byte stream
prefix was separately reproduced with Python hashlib.shake_128.

Kyber key establishment and outer Even–Mansour whitening remain. The new KDF
label is `Krakken-Kyber-Full-EM-v4`; the context marker is versioned too. Fresh
contexts are required at both endpoints. The prior version is archived in
`krakken_kyber/history/mds_chi_pressure_v3.zip`; older versions remain preserved.
Original Krakken files and vendored Kyber source hashes are unchanged.

All checks pass under GCC for Kyber512/768/1024 and Clang ASan/UBSan for
Kyber768, with LeakSanitizer disabled for the previously documented environment
restriction. Tests include 128 core/EM vectors across all eight depths,
full-core inversion in both directions, zero/all-one states, overlapping
buffers, constants, KDF, invalid arguments, and the complete KEM functional
suite. Existing MDS basis and 4608 Pressure component checks still pass.
Forward wrapper/reference agreement tests source wiring and serialization;
both paths deliberately call the same original forward implementation.

All 2048 sampled byte perturbations across 1..8 depths produce output changes
across the former even/odd boundary. These are regression probes, not a proof
of avalanche or a security level. The prior stripped-design partition proofs
no longer apply to the restored sequence, whose Theta and Butterfly mix rows.
No absence-of-all-structures claim is made.

For each fixed context, the full-state DDT remains exactly that of original
P_r, and absolute linear correlations are unchanged by whitening. Thus this
returns to the original design's intended diffusion and existing theorem scopes;
it does not strengthen the original unkeyed permutation or establish a new
unrestricted eight-round security bound. Kyber establishes secret keys rather
than repairing or proving the data permutation. See `krakken_kyber/README.md`,
`SECURITY.md`, and `TEST_RESULTS.json` for the current construction and evidence.


## Krakken–Kyber v4 AVX2 backend and benchmark — 2026-11-10

Switched the forward core to unchanged `krakken_multi.c`, calling
`krakken_permute_avx2_rounds`. The inverse remains scalar; scalar code also
supplies its round constants and the test reference. The mathematical
construction, v4 KDF label, context marker and byte outputs are unchanged.
The AVX2 source alone compiles with `-mavx2`; a runtime CPU/OS check rejects
unsupported forward calls with -2 before changing output. There is no silent
scalar fallback. Original source and Kyber dependency hashes are unchanged.
Prior scalar-v4 source/docs/logs are in `krakken_kyber/history/full_scalar_v4.zip`.

Direct comparison passes on 1024 scalar/AVX2 states across 1..8 rounds,
including zero/all-one and reproducible pseudorandom inputs. Existing wrapper,
constants, full inverse, component and KEM checks pass under GCC for all three
Kyber parameter sets and Clang ASan/UBSan for Kyber768. The original AVX2 file's
unused static helpers required disabling that warning for its translation
unit under Clang -Werror; source files were not changed. No new security claim
is made by this backend substitution.

Added the separate `krakken_kyber/benchmark.c` program. Build/run:

```sh
make -C /home/user/security/krakken_kyber benchmark
/home/user/security/krakken_kyber/build/k3/benchmark
```

Default sizes are 1, 10, 100 and 1000 decimal MB (1 GB), eight rounds, one
thread and one pass each. It processes a complete allocated buffer in place,
with full 256-byte calls; final partial blocks are zero-padded for measurement.
Requested and processed sizes are both reported. Bulk timing includes whitening
and API overhead but excludes real Kyber setup, allocation/fill, warmup and
output checksums. Setup timings are printed separately. Options support round
count, repeated passes and one selected size. It is a permutation benchmark,
not a hash, authenticated encryption or file format.

One run on the Intel Core i5-8365U with GCC 13.3.0, -O2 and Kyber768 measured:

| Requested size | Seconds | Processed MB/s |
|---|---:|---:|
| 1 MB | 0.021366 | 46.812 |
| 10 MB | 0.150284 | 66.542 |
| 100 MB | 1.505917 | 66.405 |
| 1 GB | 12.960309 | 77.159 |

This is a single unpinned local run, not controlled statistical evidence.
Benchmark help/invalid-option/overflow/rounding/repeat tests pass; repeated
output checksums agree. A separate two-pass 1 MB benchmark under ASan/UBSan
also passes. The measurement, commands and methodology are in
`krakken_kyber/BENCHMARK.md`, `BENCHMARK_RESULTS.json` and `benchmark_results.log`.


## Krakken–Kyber: restrict supported API to eight rounds — 2026-11-10

At the user's request, the supported public API now permits exactly eight
complete rounds. Removed round-count arguments from `krakken_kyber_init`,
`encaps`, `decaps` and `core`. Forward calls the original fixed-eight
`krakken_permute_avx2`; inverse executes round indices 7 down through zero.
The KDF encodes a literal round byte of 8. `KK_ROUNDS` is fixed to 8 and a
conflicting compiler definition is rejected. Former Chi/MDS/Pressure public
helpers are now private implementation details. The context's retained
`rounds` field is a read-only validation tag; non-eight values are rejected by
forward/inverse with unchanged output, and the core has no parameter allowing
fewer rounds. The benchmark rejects `--rounds`, even when its value is 8.

The construction/KDF for existing v4 eight-round use is unchanged. Source
callers must remove their final round argument and recompile. Reduced-round
contexts are unsupported. The prior variable-round version is preserved in
`krakken_kyber/history/variable_round_avx2_v4.zip`. Original research source
files and their raw interfaces remain untouched; direct calls into those raw
dependencies or historical copies are outside this supported wrapper API.
This is misuse prevention, not a sandbox against modified C code.

Validation passes under GCC for all three Kyber parameter sets and Clang
ASan/UBSan for Kyber768. Tests include 1024 direct eight-round scalar/AVX2
vectors, 128 core/EM vectors over eight independent KEM contexts, inverses,
overlap, KDF/constants, full KEM and 2048 cross-half probes. Non-eight tags
0..7, 9 and UINT_MAX reject both directions with disjoint and in-place buffers
(40 checks), leaving outputs unchanged. The new API contract test checks that
old round-selecting calls and component helpers fail compilation, non-eight
build overrides fail, removed component helpers have no global symbols, and
benchmark round options fail. Two fixed-eight 1 MB benchmark passes produce
matching checksums. Reports: `krakken_kyber/TEST_RESULTS.json` and
`API_CONTRACT_RESULTS.json`.

Earlier component-specific test evidence and bulk benchmark measurements are
retained as historical records; no new bulk timing claim is made. Fixing the
round count prevents this configuration mistake, but does not establish a
security-bit bound or turn this experimental permutation into authenticated
file encryption. Kyber key establishment does not supply data authentication.


## Research-method assessment: ePrint 2026/2746 — 2026-11-10

Checked the user-supplied `2026-2746.pdf`, especially Sections 2.2.1 and 3.1–3.2.
The assessment and proposed Krakken adaptation are recorded in
`krakken_research/SPEEDY_2026_2746_ASSESSMENT.md`, with a PDF fingerprint and
[source link](https://eprint.iacr.org/2026/2746). No new solver run or theorem
was produced in this assessment.

The proposed direction is to certify local activity exclusions and reuse them
in an eight-round activity-count lower bound, with complete coverage below the
claimed threshold. Pressure needs carry-aware modeling or a proved conservative
relaxation; actual witnesses require global compatibility. Historical ledger
exclusions must be replayed or stated as premises, not silently promoted to
new certificates. Minimum activity, multiplied local DDT score, actual trace
probability, summed endpoint differential probability and overall security bits
remain distinct quantities. Short-window analysis will not reopen reduced-round
options in the fixed-eight public API.


## Complete H159 minimum-activity classification and second-round bound — 2026-11-10

**New universal conditional theorem:** for every pair of distinct, exactly
159-byte messages with the original sponge padding, **`A1=5 => A2>=4`**.
Thus `A1+A2>=9` when the first round attains its minimum. The exact conditional
minimum A2 is still unknown; the certified interval is **[4,245]**, with the
upper endpoint supplied by an actual original-C message pair.

**New unconditional two-round activity floor:** all distinct valid159 pairs
satisfy **`A1+A2>=7`**. For A1=5 use the new theorem; otherwise A1>=6 and
bijectivity gives A2>=1. This does not claim that A2 alone is always at least
four when A1 is unrestricted, or that seven is an attained minimum total.

The key coverage advance was a complete classification of the input XOR
differences attaining A1=5. Two opposite-pivot scans each exhausted all
**264,566,400 five-cell supports**. Full 776-bit syndrome checks left 899
rank-deficient supports and 2,681 nonzero residual kernel assignments,
counted with overlap. Exact local Chi feasibility left **21 distinct input
differences**, rather than the three previously investigated. Every one was
given an actual valid159 attaining pair, replayed through all eight original
rounds and checked against the complete original permutation call.

For all 21 families, A1=5 determines the entire post-Chi1 difference. Each
family's favorable base messages form an affine set of dimension 1237,
specified by 35 independent bit equations. Thus the first-round **activity
event** A1=5 has exact probability 2^-35 for a uniform base message under
each of these fixed differences. The complete constraints and witnesses are
saved for future searches; this is not a full-trail probability statement.

Extended carry-free low-prefix gates yield 36–90 linear equations per family.
The complete three-cell round-two support scans cover **7,168,896
family/support combinations** in each pivot order. Their 1,149 survivors have
122,184,832 affine endpoint assignments. Of these, 16,319,756 permit at most
three Chi calls locally; **none passes the necessary full-width Pressure
conditions**. C and independent Python enumeration are cross-checked.

For the archived fixed difference delta_id=1 (family 4 in the new list), all
10,668,000 four-cell supports are already excluded by its 70-equation gate,
giving the additional family-specific bound A2>=5. A five-cell relaxed
candidate survives; it is not an actual trail or an activity upper bound.

This implements the paper's support/activity partitioning and short-core
reuse discipline with Krakken-specific carry modeling. No activity count is
converted into an overall security-bit or collision bound, and no improvement
to the historical eight-round activity floor is claimed in this pass.

Full theorem and derivation: [A2_ACTIVITY_BOUNDS.md](reproduce/A2_ACTIVITY_BOUNDS.md).
Reproduction: [research README](krakken_research/a2_activity/README.md).
Final machine-readable cross-audit:
[VERIFIED_RESULTS.json](krakken_research/a2_activity/VERIFIED_RESULTS.json).

Next focused work: exclude A2<=4 across all 21 classified families, or exclude
the pattern (A1,A2)=(6,1) to improve the unconditional two-round total. Both
remain open. Original permutation sources and the fixed-eight Kyber API were
left unchanged.

Final cross-audit completed on 2026-11-11: `verify_results.py` returned PASS,
including agreement of both complete first-round scans and all C/Python
second-round enumeration counts. The standalone evidence bundle is
`krakken_research/Krakken_A2_activity_evidence_20261111.zip`.


## Broad-family, composable eight-round activity bound — 2026-11-11

**New eight-round floor: 19 active byte S-box calls**, simultaneously for
every nonzero full-state input difference supported in bytes 0–158 and
**every full-state base**. This covers all `2^1272-1` differences in the rate
subspace, on every affine coset, including all distinct valid159 message
pairs. The later differences need not remain in that subspace. If the first
round has exactly five active calls, the eight-round floor is **20**.

For completely unrestricted distinct inputs the independently re-established
floor is **15**. These are activity lower bounds, not exact minima or
security-bit exponents. The 19 result improves the historical global H159
floor of 18 without inheriting an unrerun solver exclusion.

The reusable local lemma `A_r=1 => A_(r+1)>=3` was re-proved in this run
using finite carry-aware enumeration. For each post-Chi source byte and all
255 values, every next-Chi two-cell support was covered, including smaller
supports by containment. Both pivot orders exhaust **530,595,840** cases.
There are 12,559 surviving linear spaces, with **75,684,589** affine endpoint
assignments. Of these, 20,106,900 allow one or two calls locally; **zero** pass
the necessary full-width Pressure conditions. No case was capped or left
unresolved. Independent Python column elimination and full enumeration
reproduce every residual count from the C row-based scans.

Source controls include all 2048 Butterfly and prefix/inverse basis vectors,
all 65,280 source-byte difference profiles on actual original-C transitions,
and 147 conditioned pairs covering the 21 minimum-first-round differences
on arbitrary affine rate offsets at adjacent-round indices 0–6.

The earlier first-window bounds generalize to arbitrary bases because their
classification constrains only the input **difference**, and every local
exclusion already permits arbitrary base values. Thus any nonzero rate
difference gives A1>=5 and A1=5 implies A2>=4 at any suitable starting round.

Composition is pointwise: nonzero activity plus `A_r=1 => A_(r+1)>=3` gives
the unrestricted suffix bound `sum A_r>=2R-1` by a telescoping potential.
For the rate family, A1>=6 gives `6+2(R-1)-1=2R+3`; A1=5 gives A2>=4 and
the stronger `5+4+2(R-2)-1=2R+4` for R>=3. Handle R=1,2 directly. Full-range
dynamic programming and independent capped exhaustive enumeration verify all
prefix bounds 1–8. No uniformity, Markov, round independence, or probability
multiplication assumption is used. Same-key outer XOR whitening preserves
this internal activity result.

Report: [COMPOSABLE_ACTIVITY_BOUNDS.md](reproduce/COMPOSABLE_ACTIVITY_BOUNDS.md).
Code and reproduction:
[composable_activity/README.md](krakken_research/composable_activity/README.md).
Final checks:
[VERIFIED_RESULTS.json](krakken_research/composable_activity/VERIFIED_RESULTS.json).
Evidence bundle:
`krakken_research/Krakken_composable_activity_evidence_20261111.zip`.

No original permutation or public fixed-eight API source was changed. The
the unrestricted [2,1] campaign is computationally closed, as recorded in the
current-status note above. Its stronger proof-assurance questions and stronger
probability-composition results are separate; this particular activity proof
did not use the historical campaign as a premise.


## Original-scalar randomness assessment — 2026-11-12

Created [RANDOM.md](RANDOM.md) for the original `krakken.c`/`krakken.h` only.
All new cryptographic evaluations use the scalar implementation and eight
rounds; no AVX2 core, Even–Mansour wrapper, or Kyber layer is linked.

Exact component certificates and controls passed: S-box bijectivity; all
65,536 serial-Chi cell inputs checked against original C and inverted;
MDS inverse identity; all 2048 prefix/inverse basis checks; all 256 constant
words checked against independent SHAKE128; and 64 full-state inverse
controls in each direction. Independent sponge replay matches the original
32-byte hash at ten lengths including padding/rate boundaries. The layer
algebra proves bijectivity; uniform full-state input therefore produces
uniform full-state output, a property also shared by the identity map.

A predeclared statistical run used 2048 saved OS-random bases per domain:
unrestricted full states and valid159 padded inputs. It covered all 2048 and
1272 single-bit directions respectively, totaling **6,799,360 related-input
pairs**. Flip probabilities, adjacent derivative parities, one-bit
input/output correlations, and output frequencies provide **20,402,176**
measured marginal probabilities. There were **zero flags** at the stated
simultaneous threshold. Mean changed bits were 1024.001014 / 1023.991343
out of 2048. The identity control was detected; eight complete rows were
independently recounted through original scalar C.

Under the stated iid sampling model, Hoeffding plus a union bound gives
simultaneous 99% confidence intervals with radius 0.07350307824379629.
No independence among output bits, directions, or tests is assumed. This
is a deliberately limited, relatively coarse statistical statement; it
does not exclude subtle or higher-order structure or adaptive attacks.

The actual sponge parameters are b=2048, r=1280, c=768, n=256. Replacing
the core with an ideal random permutation permits the conventional classical
128-bit collision / 256-bit single-target preimage benchmarks. **The actual
Krakken ideality assumption and these concrete security levels remain
unproved.** The new report includes the fixed-public-permutation distinction,
official Keccak/NIST sources, and explicit machine-readable fields
`random_permutation_certified=false` and `security_bits_certified=null`.

Evidence, samples, raw counts, and reproduction instructions:
[randomness/README.md](krakken_research/randomness/README.md).
Final results: [RESULTS.json](krakken_research/randomness/RESULTS.json).
No original cryptographic sources or production APIs were modified.

## Higher-order derivative span certificate — 2026-11-12

The unchanged original scalar core now has a computational degree certificate
at **2 and 8 rounds** on the full H159 message domain. At each depth, 2080
order-nine coordinate derivative vectors span all 2048 output dimensions.
Therefore **every nonzero linear combination of output bits has algebraic
degree at least 9** in the 1272 message bits. This also covers every nonzero
linear combination of the original eight-round 256-bit digest at message
length 159 bytes. It is an exact lower bound backed by finite witnesses,
not a statistical claim or a security-bit bound.

Binary-order Python enumeration and Gray-code C enumeration are compared
for every derivative sum; binary rank is checked with opposite pivot orders.
Sources, inputs, sums, and verification are preserved. An additional 47,104
structured-difference pairs produced zero flags at the predeclared threshold;
the separate statistical confidence bounds and their limitations are stated.

See [RANDOM.md](RANDOM.md), the
[detailed report](krakken_research/higher_order/REPORT.md), and
[reproduction instructions](krakken_research/higher_order/README.md).
Original cryptographic source files and production APIs remain unchanged.

## NIST STS empirical certificate — 2026-11-12

**Certificate ID: KRAKKEN-NIST-STS-20261112-001**

**Result: all 188 reported component rows across all 15 NIST STS test
families meet the suite's aggregate acceptance criteria.** There are no
flagged aggregate pass proportions or p-value uniformity results in this run.
This is a reproducible empirical test certificate authored for this ledger,
not a NIST-issued certification or a theorem of cryptographic security.

### Dataset and configuration

- Run: `nist_sts/runs/run_K1lVgTJu`.
- Dataset: user-supplied `nist_sts/krakken_perm_10GB.bin`, 10,000,000,000 bytes.
- Tested region: **first 125,000,000 bytes (125 MB, 1.25% of the file)**.
- Sequences: **1000 successive non-overlapping sequences of 1,000,000 bits**.
- Input mode: binary; all 15 test families selected; original default parameters.
- Suite: official NIST STS 2.1.2 archive supplied by the user, rebuilt with
  GCC `-O2 -fcommon`; the run preserves its source and executable.
- Individual-sequence significance threshold: alpha = 0.01.
- Aggregate uniformity threshold: p >= 0.0001.
- Pass-proportion criteria: the suite's three-sigma interval with its
  implemented integer rounding, including both lower and upper endpoints.
- Defaults: block frequency M=128; non-overlapping and overlapping template
  lengths m=9; approximate entropy m=10; serial m=16; linear complexity M=500.

The tested prefix SHA-256 is:

```
a8d0ca5e7fdb29b9bf0e0d58ef5a21ee6475084f984436af4d93ee1b7c43b3b1
```

The prefix fingerprint was calculated during this audit, after the run. It
identifies the currently available bytes; linking them to the completed run
assumes the input file was not modified in between. The user describes this
file as Krakken permutation output. This audit validates the statistical
record, but does not independently reconstruct its generator, seed, input
schedule, round count, or generation-time source. Consequently it does not
attribute a stronger, independently verified generator-provenance claim.

### Results by test family

The ranges below summarize all component rows within a family. A passing
aggregate row does not mean every individual sequence passed; individual
failures are expected at alpha = 0.01.

| Test family | Component rows | Passing sequences per component | Lowest uniformity p-value |
|---|---:|---:|---:|
| Frequency | 1 | 988/1000 | 0.862883 |
| BlockFrequency | 1 | 994/1000 | 0.836048 |
| CumulativeSums | 2 | 985–991/1000 | 0.336111 |
| Runs | 1 | 982/1000 | 0.442831 |
| LongestRun | 1 | 990/1000 | 0.996677 |
| Rank | 1 | 984/1000 | 0.420827 |
| FFT | 1 | 987/1000 | 0.299736 |
| NonOverlappingTemplate | 148 | 983–997/1000 | 0.001509 |
| OverlappingTemplate | 1 | 985/1000 | 0.112047 |
| Universal | 1 | 991/1000 | 0.011626 |
| ApproximateEntropy | 1 | 987/1000 | 0.674543 |
| RandomExcursions | 8 | 615–622/625 | 0.033526 |
| RandomExcursionsVariant | 18 | 613–623/625 | 0.112900 |
| Serial | 2 | 990–992/1000 | 0.322135 |
| LinearComplexity | 1 | 991/1000 | 0.454053 |

The smallest aggregate uniformity p-value is **0.001509**, above the suite's
0.0001 threshold. Ordinary components used all 1000 sequences; their
implemented accepted pass-count interval is 980–999. Random Excursions and
Random Excursions Variant used **625 eligible sequences**, with accepted
counts 611–626 before the natural maximum of 625 is applied. The other 375
sequences were inapplicable to those tests, not failures; the saved excursion
statistics contain 375 applicability warnings. No independence between the
188 component results is asserted, and their p-values are not multiplied
into a probability that Krakken is secure.

### Verification and interpretation

The audit independently parsed all 188 rows and checked them against the
saved per-sequence p-values: denominators, passing counts, ten-bin histograms,
and uniformity p-values all agree. It reproduces the legacy implementation's
integer `expCount = sampleSize/10` and float input parsing, rather than silently
substituting a different statistical calculation. Uniformity was independently
recomputed using the half-integer incomplete-gamma recurrence. The run's
console records completion.

**Certified empirical statement:** the recorded 1000-sequence prefix of the
user-supplied Krakken dataset passed every aggregate criterion reported by
this NIST STS configuration. This adds positive statistical evidence for
that dataset. It is not a test of the remaining 9.875 GB, a proof of ideal
permutation behavior, or a 128-bit collision / 256-bit preimage guarantee.
It is separate from the exact activity and algebraic-degree theorems above.

Evidence:

- [Original final report](nist_sts/runs/run_K1lVgTJu/experiments/AlgorithmTesting/finalAnalysisReport.txt)
- [Run configuration](nist_sts/runs/run_K1lVgTJu/RUN_INFO.txt)
- [Machine-readable audited certificate](nist_sts/certificates/run_K1lVgTJu.json)
- [Independent audit script](nist_sts/certificates/audit_run.py)
- [Evidence checksums](nist_sts/certificates/SHA256SUMS)

Reproduce the audit with `python3 nist_sts/certificates/audit_run.py` from the
repository root. It reads existing results and hashes the tested prefix;
it does not rerun the lengthy statistical campaign. Source context:
[NIST's official suite page](https://csrc.nist.gov/projects/random-bit-generation/documentation-and-software).

## NIST STS empirical certificate — 2026-11-13, full 250 MB dataset

**Certificate ID: KRAKKEN-NIST-STS-20261113-002**

**All 188 component rows across all 15 test families passed the suite's
aggregate pass-proportion and uniformity criteria.** This is an audited
empirical certificate, not a NIST-issued endorsement or a security theorem.

### Scope and provenance

Run `run_LNISIAlt` processed **all 250,000,000 bytes** of
`nist_sts/krakken_perm_250MB.bin` as **2000 successive non-overlapping
1,000,000-bit sequences**. Binary input and all tests were selected with
the default parameters of NIST STS 2.1.2. The console records completion.

The file SHA-256 matches the fingerprint recorded before testing:

```
e7fbf852479144109556d5b089a7cddd96143cb441a8ea26b6fe2d98604ab3bd
```

Unlike the earlier user-supplied dataset, this dataset has preserved generator
provenance: `generate_250mb.c` invokes the original eight-round scalar
`krakken_permute_scalar` from `krakken.c`/`krakken.h`. Each input has a distinct
counter in word 0, domain tag `0x4b52414b4e495354` in word 1, and a saved fresh
32-byte nonce in words 4–7; remaining words are zero. Full output states are
serialized little endian, with the last truncated to 128 bytes. Generation
covered 976,563 distinct input states. The generator, nonce, source hashes,
and sampled-block verification are retained in the dataset metadata.
The audit rechecked the dataset hash and recorded source fingerprints.

This is a structured counter-input experiment, not an experiment with uniform
independent full-state inputs. A new nonce does not establish independence
from other campaigns using the same deterministic permutation.

### Audited results

| Test family | Component rows | Passing sequences per component | Lowest uniformity p-value |
|---|---:|---:|---:|
| Frequency | 1 | 1979/2000 | 0.389855 |
| BlockFrequency | 1 | 1984/2000 | 0.007862 |
| CumulativeSums | 2 | 1975–1977/2000 | 0.096578 |
| Runs | 1 | 1973/2000 | 0.302657 |
| LongestRun | 1 | 1984/2000 | 0.107512 |
| Rank | 1 | 1979/2000 | 0.370262 |
| FFT | 1 | 1980/2000 | 0.513130 |
| NonOverlappingTemplate | 148 | 1970–1988/2000 | 0.000947 |
| OverlappingTemplate | 1 | 1970/2000 | 0.501263 |
| Universal | 1 | 1973/2000 | 0.134944 |
| ApproximateEntropy | 1 | 1978/2000 | 0.339271 |
| RandomExcursions | 8 | 1195–1210/1218 | 0.182624 |
| RandomExcursionsVariant | 18 | 1199–1207/1218 | 0.090257 |
| Serial | 2 | 1980–1987/2000 | 0.502247 |
| LinearComplexity | 1 | 1973/2000 | 0.590375 |

The minimum aggregate uniformity p-value is **0.000947**, above the suite's
0.0001 threshold. Individual sequence decisions use alpha=0.01. For the
ordinary components, the suite's implemented three-sigma pass-count interval
is **1966–1993 out of 2000**. Excursion components use **1218 eligible
sequences**, with implemented interval **1195–1216**;
the other 782 sequences are excluded from these components' aggregate
calculations by the suite's applicability/positive-p-value selection.
Individual sequence failures are compatible with an aggregate pass.

The independent audit recomputed every passing count, histogram, and
uniformity p-value from the saved per-sequence results. It matches the suite's
float parsing, integer expected-bin counts, and integer-rounded proportion
thresholds. Uniformity was recomputed with a half-integer incomplete-gamma
recurrence. All 188 report rows agree. This checks post-processing; it does
not independently reimplement each underlying statistical test.

**Certified empirical statement:** the complete recorded 250 MB original-scalar
counter dataset satisfies all aggregate acceptance criteria reported by this
NIST STS configuration. This adds positive statistical evidence alongside
the earlier 125 MB-prefix campaign. Neither run proves ideal-permutation
behavior or a collision/preimage security exponent. No combined probability
of security is inferred from the tests or from the two campaigns.

Evidence and reproduction:

- [Final report](nist_sts/runs/run_LNISIAlt/experiments/AlgorithmTesting/finalAnalysisReport.txt)
- [Run configuration](nist_sts/runs/run_LNISIAlt/RUN_INFO.txt)
- [Audited results](nist_sts/certificates/run_LNISIAlt.json)
- [Audit script](nist_sts/certificates/audit_250mb.py)
- [Evidence checksums](nist_sts/certificates/SHA256SUMS_250MB)
- [Dataset provenance](nist_sts/krakken_perm_250MB.json)

From the repository root, run `python3 nist_sts/certificates/audit_250mb.py`
to repeat the audit without repeating the statistical campaign. Earlier
reports and certificates are preserved unchanged.

## Joint-observation theorem — 2026-11-13

**Certificate: KRAKKEN-JOINT-OBSERVATION-20261113.**

A new analytic corollary of NOTE-012 upgrades its individual linear
correlation bounds to a bound covering **every decision rule on a joint
observation**, including nonlinear rules.

For uniform full-state X, a complete indexed original round R_r, and any
fixed rank-k linear input observation U=A X, let Y be the d-bit output
projection defined by NOTE-012's certified mask basis (d=8 or d=10).
Then, relative to independent uniform k-bit and d-bit strings,

```
TV(Law(U,Y), Uniform_k x Uniform_d)
 <= (1/2) sqrt((2^k-1) * sum_(q in V_d, q!=0) kappa_q^2).
```

Proof: both marginals are uniform by rank and bijectivity. Every mixed
Fourier coefficient is bounded by the corresponding complete-round
kappa_q. Parseval followed by Cauchy–Schwarz gives the displayed total
variation bound. No cross-round independence or multiplication of local
trail probabilities is assumed.

| Input observation bits | Selected output bits | Strict total-variation bound |
|---:|---:|---:|
| 128 | 8 | 2^-230 |
| 256 | 8 | **2^-166** |
| 384 | 8 | 2^-102 |
| 512 | 8 | 2^-38 |
| 128 | 10 | 2^-157 |
| 256 | 10 | **2^-93** |
| 384 | 10 | 2^-29 |

Every classifier receiving only these observations has acceptance-probability
gap at most this distance. Predicting all d selected output bits from U has
success at most 2^-d plus this distance, averaged over X. For Q independent
fresh bases, a sequential hybrid gives at most Q times the bound, even when
A is selected from previous observations before the next base is drawn.
This sampling model does not grant chosen inputs or additional access to X.

The theorem also applies to `(A X_7, projection(X_8))` at the last boundary
of an actual eight-round execution from a uniform full-state base, because
X_7 is uniform. It does **not** establish the same bound for
`(A X_0, projection(X_8))`, for H159 inputs, or for arbitrary digest bits.
The exponents above are restricted statistical-distance exponents, not
collision/preimage security levels.

Verification reconstructed all 1023 rational correlation caps from the saved
verified Fourier norms and cell-count certificates, checked mask-space ranks
and the selected 255-character span, and proved the displayed inequalities
with exact fractions. Original-C local linear-factorization checks were
replayed successfully. The large prior Fourier certificates are inherited
from NOTE-012, not claimed to have been rerun in this pass.

Full proof, observation model, Keccak comparison, and limitations:
[JOINT_OBSERVATION_BOUND.md](reproduce/JOINT_OBSERVATION_BOUND.md).
[Exact results and masks](krakken_research/joint_observation/RESULTS.json).
[Verifier](krakken_research/joint_observation/verify.py).

Keccak's published security claim likewise distinguishes ideal-model generic
proofs, concrete structural bounds, and independent cryptanalytic evidence;
it does not assert that a finite catalogue of attack types has been exhausted.
For Krakken, 128-bit collision and 256-bit preimage resistance remain design
targets and ideal-model benchmarks, rather than established concrete bounds.

## One-round full-coordinate dependency certificate — 2026-11-13

**Certificate: KRAKKEN-ONE-ROUND-DEPENDENCY-20261113.**

For the original scalar permutation on unrestricted 2048-bit input states,
every output bit depends on every input bit after the six-layer prefix ending
at Butterfly, and again after the complete original round indexed zero.

Formally, for each i,j in {0,...,2047}, the reproducible set S of 128
deterministically generated bases contains a witness x such that

```
bit_j(F6(x)) != bit_j(F6(x XOR e_i)),
```

and (possibly with a different witness) the same holds for F9, the complete
first round. Thus every one of the **4,194,304 input/output coordinate pairs**
has a direct witness at each checkpoint. The checker calls the original
unmodified stage functions, including the original Chi implementation.
One witness suffices to prove functional dependence; a random-sampling
assumption is unnecessary for this existential statement.

| Checkpoint | Witnessed pairs | Mean changed bits over the 128-base experiment |
|---|---:|---:|
| After Butterfly, layer 6 | 4,194,304 / 4,194,304 | 1023.986072540283 |
| After Ink Cloud, layer 9 | 4,194,304 / 4,194,304 | 1023.926002502441 |

The principal original-source certificate was independently replayed, then
rerun from the new self-contained reproduction bundle. The stronger
reference/optimized-evaluator comparison also passes: 67,584 S-box word
comparisons and 2,049 complete-round comparisons. Original krakken.c and
krakken.h match the root sources byte-for-byte. Two printf arguments in the
copied checker were cast to uint64_t for format portability only.

The supplied note additionally reports a 1024-base average of
1023.977828502655 changed bits; this integration did not rerun that larger
campaign. It is a sampled avalanche measurement, distinct from the exact
existential dependency theorem. All bases and generator warmup are fully
specified in the harnesses.

**Interpretation:** full dependency is first *observed* at the Butterfly
checkpoint. Absence of earlier sampled witnesses is not generally proof of
independence. Complete dependency does not mean every perturbation changes
every output bit, establish strict avalanche, exclude exploitable algebraic
relations, or supply an eight-round or hash-security exponent. The domain
is unrestricted full states, not H159 padded messages.

Reproduce:

```bash
cd ~/security/reproduce/one_round_dependency
sha256sum --check SHA256SUMS
make check
```

Optional `make extended` reruns the stage profile and larger avalanche campaign.
[Self-contained bundle and instructions](reproduce/one_round_dependency/README.md).
[Review](reproduce/one_round_dependency/REVIEW.md).
Future reproduction bundles are indexed in [reproduce/README.md](reproduce/README.md).

## Original supporting documents consolidated — 2026-11-13

Compared the **20 other Markdown documents in `reproduce/docs/` with all eight research
ledgers**, excluding `reproduce/docs/KRAKKEN_SECURITY_THEOREMS.md` as the duplicate of
research 01. All **80 theorem identifiers** in the included documents already
occur in the existing ledgers. The additional useful material is supporting
proof detail, experimental results, solver-model reductions, counterexamples
to proposed proof shortcuts, and provenance—not a new set of security theorems.

The consolidated continuation is
[KRAKKEN_RESEARCH_09.md](KRAKKEN_RESEARCH_09.md). It records:

- A separate **8,000-trial, 24-bit first-collision campaign**, 1,000 trials at
  each depth R1–R8; mean counts range from 5,042.970 to 5,287.765 against the
  ideal approximation 5,133.5747. All eight saved trial files were recounted,
  with zero censored trials. This is a small-prefix empirical result.
- Additional truncated-differential, rotational, and restricted-cube Walsh
  screens, including real R1 structure and controlled Butterfly-on/off results.
- Exact endpoint-kernel reduction, visible/hidden-fiber elimination preserving
  nonzero-byte constraints, and polynomial/table encodings of low-bit Pressure.
  Selected speed measurements and the complete AB-position-007 exceptional-flat
  classification are retained with their limited scope.
- Joint-carry/Fourier proof techniques, failures of independence and absolute-hull
  shortcuts, invalid prototype warnings, and actual-message reachability
  requirements for coordinated boomerangs.
- A document-by-document disposition and a map from every inherited theorem ID
  to the earlier ledgers. Positive constructions and limitations are preserved
  alongside exclusions.

**Current results take precedence over historical snapshots.** `[1,2]` and
`[2,1]` are completed exclusions; the latter has all 8,355,840 configurations
recorded excluded and zero unresolved. Old progress reports do not reopen
those campaigns. Research 07 supplies the current compositional eight-round
floors under its stated premises: **16 unrestricted, 19 H159, 21 H159 conditioned
on A1=5**, and a selected-family conditional bound of 22. These are activity
lower bounds, not attained minima or hash-security bits.

The [preservation bundle](reproduce/docs_integration/README.md) contains the
20 source documents and available directly linked supporting files, plus the
collision trial records: **618 files, 280,652,066 bytes**, with hashes and a
source/link manifest. It preserves direct references, not the recursive runtime
dependency closure of every historical script. Original documents are unchanged;
the ignored duplicate ledger was not copied. Research 01–07 and the original
C/H/AVX2 sources are unchanged. This entry is appended to research 08.

No cryptanalytic experiment or solver campaign was rerun during consolidation.
The new checks verify archive integrity, theorem-ID coverage, saved collision
record accounting, and preservation of the existing ledgers/source files.
[Integration check results](reproduce/docs_integration/INTEGRATION_CHECK.json).

```bash
cd ~/security/reproduce/docs_integration
python3 verify.py
```

This checks preserved records; it does not certify the underlying permutation's
randomness, recompute the stored hashes through C, or establish a new overall
security level.

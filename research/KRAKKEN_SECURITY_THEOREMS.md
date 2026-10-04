# Krakken security theorem program

Research navigation: [index](KRAKKEN_RESEARCH_INDEX.md).

This file separates proved global statements from the quantitative bounds
still needed to assess the full eight-round construction. All statements
refer to the current `krakken.c` and `krakken.h` source. A message in this
program is exactly 159 bytes, followed by the fixed `0x86` padding byte in
the first absorb block. Let `F_r(m)` be the full 2048-bit state after `r`
complete Krakken rounds starting from that block, with XRBD enabled.

<!-- BEGIN THEOREM NAVIGATION -->
## Theorem map and audit conventions

[Full inventory and audit scopes](KRAKKEN_THEOREM_INVENTORY.md) ·
[Certificate/script manifest](KRAKKEN_THEOREM_ARTIFACTS.md) ·
[Machine-readable permanent registry](../results/krakken_theorem_registry.json).

IDs are permanent and append-only. New results receive new IDs; moving a section
does not change its ID. The statements below, including all restrictions and
validation boundaries, remain authoritative. This map is not a certificate audit.

**Domains:** H = valid 159-byte first hash block with fixed padding and zero
initial capacity; P = unrestricted permutation; L = local Chi; U = uniform
Pressure input; R = reduced-width analogue. **Proof:** A = analytic proof;
F = finite exhaustive proof (also finite counterexample/rank certificates);
S = solver-backed exhaustive exclusion; E = empirical probe. A checkpoint such
as Chi1 is not a complete round. Audit coverage is detailed in the inventory.

Throughout this ledger, separate Python/C replays, opposite-pivot elimination,
and alternate derivations are **independent implementation audits**. Existing
uses of “independent” for these checks have that meaning, not external independent
verification. External reviewer comments do not establish external reproduction;
no external certificate reproduction is recorded here. Proof and implementation
validation remain distinct even when both use exhaustive computation.

### Compact theorem-status matrix

Each result column is the cryptanalytic implication within the quantified class;
none implies a global security-bit estimate. External status “—” means no recorded
external reproduction. Audit “scope” links to the exact coverage, including
partial replays. Supporting identities are indexed alongside theorem classes.

| ID | Family | Domain | Rounds/checkpoint | Quantified class | Result | Proof | Implementation audit | External | Implication |
|---|---|---|---|---|---|---|---|---|---|
| [LIN-GLOBAL-001](#lin-global-001) | Linear | H | 1–8 | All message/state affine masks | No perfect affine relation; only 1−2^-1271 numerical bound | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-global-001) | — | Perfect relations excluded; no useful security bits |
| [LIN-CHI-001](#lin-chi-001) | Linear | H | Chi1 | Exactly t=1,2,3 cells; all masks | Sharp maximum 2^-3t | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-chi-001) | — | Stated class/checkpoint only |
| [LIN-CHI-002](#lin-chi-002) | Linear | H | Chi1 | Exactly four cells; all message/output masks | Sharp maximum 2^-12 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-chi-002) | — | Complete four-cell checkpoint class; not a full-round bound |
| [BOOM-LOCAL-001](#boom-local-001) | Boomerang | L | Chi | 255² diagonal/first-output entries | BCT=2^16; family need not exhaust maximizers | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-local-001) | — | Attack-side local structure |
| [BOOM-LOCAL-002](#boom-local-002) | Boomerang | L / unrestricted Chi | Chi | Every local nontrivial input/output difference pair; exact full-Chi product | Perfect iff diagonal/first-output; otherwise sharp BCT≤1536 (probability≤3/128) | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-local-002) | — | Complete local classification; no round-two or hash-interface bound |
| [BOOM-EMBED-001](#boom-embed-001) | Boomerang | P/H | Chi1 | One-cell family | Unrestricted embedding; first-block nonzero one-cell input excluded | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-embed-001) | — | Stated class/checkpoint only |
| [DIFF-RATE-001](#diff-rate-001) | Differential | H / shared-prefix later final absorb | Chi1 | All nonzero first-block differences; later same-length partial suffix differences after common prefix | Exact first-block min A1=5; later-block A≥5 corollary | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-rate-001) | — | Rate-only difference condition; differing prefixes open |
| [DIFF-RATE-002](#diff-rate-002) | Differential | H | Chi1 | Six fixed differences, uniform message base | Exact A1 distribution; sharp prescribed-output max 2^-38 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-rate-002) | — | Stated class/checkpoint only |
| [DIFF-RATE-003](#diff-rate-003) | Differential | H | 1→2 | Three fixed differences conditioned on A1=5 | A2≥3; not all A1=5 pairs | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-rate-003) | — | Stated class/checkpoint only |
| [DIFF-RATE-004](#diff-rate-004) | Differential | First full 160-byte absorb / common-prefix later full absorb | Chi of that call | All nonzero rate-only full-block differences | Exact first-full-block min A=5; later shared-prefix full-block floor A≥5 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-rate-004) | — | Does not cover differing earlier blocks or later padded call |
| [DIFF-RATE-005](#diff-rate-005) | Differential | H / common-prefix final 159-byte suffix | Chi1/XRBD1 | Every fixed nonzero message difference and every prescribed full-state difference | Probability at most 2^-24 under uniform message base; sharpness open | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-rate-005) | — | Checkpoint concentration, not a complete-round bound |
| [DIFF-CHI-001](#diff-chi-001) | Differential | Local Chi / H | Chi1 | Prescribed local transitions with active first S-box; hash transitions where every active first call is active | Affine base fibers; consistent hash event has exact probability 2^-rank | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-chi-001) | — | Counting shortcut; no Pressure conclusion |
| [BOOM-ROUND-001](#boom-round-001) | Boomerang | P | 1→Chi2 | Four fixed choices, one site, zero background, all local bases | No required quartet survives Chi2 | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-round-001) | — | Stated class/checkpoint only |
| [BOOM-ROUND-002](#boom-round-002) | Boomerang | P | Chi2 | 4,784 surviving patterns from BOOM-ROUND-001 | Each pattern has a local obstruction for every Chi2 base | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-round-002) | — | Stated class/checkpoint only |
| [DIFF-PERM-001](#diff-perm-001) | Differential | P | XRBD1/Pressure1 | All 65,280 one-byte post-Chi differences | All 16 Pressure chains active for every base | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-perm-001) | — | Stated class/checkpoint only |
| [DIFF-PERM-002](#diff-perm-002) | Differential | P | 1→2 | All unrestricted [1,1] trails | Impossible; A1+A2≥3 | S | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-perm-002) | — | Stated class/checkpoint only |
| [DIFF-12-001](#diff-12-001) | Differential | P | 1→2 | LSB-obstructed BB sites | 1,034,445 sites excluded | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-12-001) | — | Stated class/checkpoint only |
| [DIFF-12-002](#diff-12-002) | Differential | P | 1→2 | Start 0, distinct BB sites | 6,223 sites excluded; remaining sites unresolved here | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-12-002) | — | Stated class/checkpoint only |
| [DIFF-12-003](#diff-12-003) | Differential | P | 1→2 | All 256 starts, BB low-two-bit gate | 1,628,104 excluded; 452,664 deferred/surviving | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-12-003) | — | Stated class/checkpoint only |
| [DIFF-12-004](#diff-12-004) | Differential | P | 1→2 | Complete distinct BB class | All 2,080,768 sites excluded | A+F+S | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-12-004) | — | Stated class/checkpoint only |
| [DIFF-12-005](#diff-12-005) | Differential | P | 1→2 | Complete same-pair mixed class | All 32,768 sites excluded | A+S | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-12-005) | — | Stated class/checkpoint only |
| [ROT-001](#rot-001) | Rotational | P | 1–8 | All nontrivial lane rotations; constants on/off | No universal affine covariance | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#rot-001) | — | Stated class/checkpoint only |
| [ROT-002](#rot-002) | Rotational | P | 1 | Byte rotations 8,…,56 | Exact residual identity; uniform full-state scope | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#rot-002) | — | Stated class/checkpoint only |
| [DL-001](#dl-001) | Differential-linear | P | 1 | 128 cells ×255 diagonal differences; 32D affine output space | Exact perfect-mask kernels of dimensions 26–29 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#dl-001) | — | Stated class/checkpoint only |
| [DL-002](#dl-002) | Differential-linear | P | 2 | 128 fixed delta=1 differences; all output masks | No perfect output autocorrelation | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#dl-002) | — | Stated class/checkpoint only |
| [DIFF-TRUNC-001](#diff-trunc-001) | Truncated differential | P | 1 | All 128 diagonal one-cell sites; every base and nonzero byte difference | Certified per-site zero-output-bit sets; selected site has 15 zero bytes | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-trunc-001) | — | Attack-side one-round structure; no R2 claim |
| [PRESS-WALSH-001](#press-walsh-001) | Linear | U | Pressure | q=0; arbitrary 64-bit u,v,p | Exact counter; sharp nonperfect max 1/2 | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#press-walsh-001) | — | Stated class/checkpoint only |
| [PRESS-WALSH-002](#press-walsh-002) | Linear | U | Pressure | u∈{0,bit0} or q∈{0,bit0}; other masks arbitrary | Exact counter; sharp nonperfect max 1/2 | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#press-walsh-002) | — | Stated class/checkpoint only |
| [PRESS-WALSH-003](#press-walsh-003) | Linear | U | Pressure | Both outputs low k≤17; all input masks | Exact joint counter; sharp nonperfect max 1/2 for k≥2, zero at k=1; top-bit zero rule | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#press-walsh-003) | — | Stated class/checkpoint only |
| [PRESS-HULL-001](#press-hull-001) | Linear | U/R | Pressure | Arbitrary 64-bit masks; separate 4-bit counterexample | Exact signed identity; triangle bound fails in reduced model | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#press-hull-001) | — | Identity / failed proof route |
| [PRESS-ZERO-001](#press-zero-001) | Linear | U | Pressure | Pairwise word projections and specified masks | Exact pair-uniformity and zero coefficients | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#press-zero-001) | — | Stated class/checkpoint only |
| [LIN-RATE-001](#lin-rate-001) | Linear | H | 1 | 16 specified output masks; every message mask | Per-mask bounds at least 2^-174, strongest 2^-354 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-rate-001) | — | Stated class/checkpoint only |
| [LIN-RATE-002](#lin-rate-002) | Linear | H | 1 | 31 nonzero masks in specified 5D space; every message mask | ≤2^-162; stated conditional/TV corollaries | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-rate-002) | — | Stated class/checkpoint only |
| [LIN-RATE-003](#lin-rate-003) | Linear | H | 1 | 63 nonzero masks in specified 6D space; every message mask | ≤2^-76; stated conditional/TV corollaries | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-rate-003) | — | Stated class/checkpoint only |
| [ALG-DEG-001](#alg-deg-001) | Algebraic | H | 1–8 | All coordinates; separate 256-bit projection | 32 R1 bits degree 13; other R1 and all R2–8 ≥20; projection ≥24 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#alg-deg-001) | — | Stated class/checkpoint only |
| [LIN-HULL-001](#lin-hull-001) | Linear | H/P | 1–8 | All message/state masks | Exact signed coset sum of 2^776 full-state coefficients | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#lin-hull-001) | — | Global proof obligation identified |
| [ZERO-001](#zero-001) | Zero-sum | P | Chi1/1/2 | Fixed square, all backgrounds; sites as specified | R1 projected balance; no universal R2 coordinate at 128 sites, no mask at site 0 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#zero-001) | — | Stated class/checkpoint only |
| [INT-CUBE-001](#int-cube-001) | Integral | H | Chi1/1/2 | Every d≥14 cube at checkpoints; fixed 14-direction family at complete rounds | Sharp threshold 14; fixed family exactly 32 universal R1 coordinates, none R2 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#int-cube-001) | — | Stated class/checkpoint only |
| [INT-BYTE-001](#int-byte-001) | Integral | H | 2 | All 159 byte cubes, arbitrary bases, coordinate masks | No universal coordinate balance | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#int-byte-001) | — | Stated class/checkpoint only |
| [INT-BYTE-002](#int-byte-002) | Integral | H | 1/2 | Byte-0 cube, all bases/output masks | R1 sum rank 2041; R2 rank 2048, no universal nonzero mask | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#int-byte-002) | — | Stated class/checkpoint only |
| [DIV-BYTE-001](#div-byte-001) | Division property | H | 1/2 | Byte-0 defined direction family and linear masks | Exact universal balance spaces: dimensions 7 and 0 | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#div-byte-001) | — | Stated class/checkpoint only |
| [SUBSPACE-001](#subspace-001) | Subspace | H | Chi1/1/2 | 159 byte-coordinate subspaces, zero-base coset | Affine hull rank 255 at stated checkpoints | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#subspace-001) | — | Stated class/checkpoint only |
| [SUBSPACE-002](#subspace-002) | Subspace | H | Chi1/Pressure1/2 | Bytes 40,56 diagonal planes; all 256 defined cosets | Chi rank 238–254; Pressure and complete R1/R2 rank 255 | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#subspace-002) | — | Stated class/checkpoint only |
| [REBOUND-001](#rebound-001) | Rebound | L/P | Chi1/XRBD1 | Diagonal inbound family; all one-byte second-output differences | Exact 256×DDT count; outbound support ranges as stated | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#rebound-001) | — | Stated class/checkpoint only |
| [REBOUND-002](#rebound-002) | Rebound | H | Chi1 | All single-cell input or output difference supports | Nonzero first-block reachability excluded | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#rebound-002) | — | Stated class/checkpoint only |
| [DEPEND-001](#depend-001) | Dependency | H | 1/2 | All 1,272 input bits ×2,048 output bits | Possible influence for every pair; not probability | F | [scope](KRAKKEN_THEOREM_INVENTORY.md#depend-001) | — | Possible influence only |
| [DIFF-MULTI-001](#diff-multi-001) | Differential corollary | P/H | 1–8 | All distinct unrestricted inputs; H; three selected differences under A1=5 | Eight-round totals ≥12 / ≥15 / ≥17 respectively; inherited premises | A | [scope](KRAKKEN_THEOREM_INVENTORY.md#diff-multi-001) | — | Total activity only; no security-bit conversion |
| [BOOM-MULTI-001](#boom-multi-001) | Boomerang / zero-sum | P | 1 | 56 ordered disjoint chain-unit classes; all nonzero directions in specified 128D kernels and all common backgrounds | Constructed four distinct inputs and complete R1 outputs both XOR to zero | A+F | [scope](KRAKKEN_THEOREM_INVENTORY.md#boom-multi-001) | — | Attack-side one-round construction; R2 and hash reachability open |

### Dependency map

Arrows indicate proof inputs or stated refinements, not multiplication of security
bounds. This is a map of the major chains, not a claim that every theorem depends
on every earlier result. Local spectra, source identities and rank certificates
are proof inputs in their own right. Artifact paths are in the manifest.

```mermaid
flowchart TD
  spectra["Exact local Chi Walsh spectra"] --> sparse["LIN-CHI-001: sparse Chi1 classes"]
  rank["Certified message-to-Chi projection ranks"] --> sparse
  rank4["All 10,668,000 four-cell input projections rank 64"] --> sparse4["LIN-CHI-002: sharp four-cell mask maximum"]
  spectra --> sparse4
  rank --> rate["DIFF-RATE-001: exact A1 minimum 5"]
  ddt["Exact local Chi DDT constraints"] --> rate
  rank4 --> concentration["DIFF-RATE-005: prescribed Chi1/XRBD1 difference <= 2^-24"]
  rate --> concentration
  ddt --> concentration
  ddt --> fibers["DIFF-CHI-001: affine active-first-call fibers"]
  rate --> prob["DIFF-RATE-002: six fixed-line distributions"]
  rate --> selected["DIFF-RATE-003: three selected A1=5 gates"]
  rate --> fullrate["DIFF-RATE-004: full 160-byte absorb minimum 5"]
  fullrank["Independent 1280-bit rate-image support ranks"] --> fullrate
  aff["Pressure affine LSB identities + exact XRBD transpose"] --> bridge["LIN-RATE-001: 16 complete-round masks"]
  spectra --> bridge
  image["Rate-aware affine-image inequality + certified ranks"] --> bridge
  bridge --> five["LIN-RATE-002: specified 5D mask space"]
  image --> five
  bridge --> six["LIN-RATE-003: specified 6D mask space"]
  image --> six
  localboom["BOOM-LOCAL-001: local perfect family"] --> embed["BOOM-EMBED-001: embedding / rate gate"]
  localboom --> completeboom["BOOM-LOCAL-002: complete local BCT classification"]
  localboom --> roundboom["BOOM-ROUND-001: four defined continuation classes"]
  roundboom --> obstruction["BOOM-ROUND-002: base-independent Chi2 obstructions"]
  no11["DIFF-PERM-002: adjacent no-[1,1]"] --> multi["DIFF-MULTI-001: eight-round totals 12 / 15 / 17"]
  rate --> multi
  selected --> multi
  localboom --> coordinated["BOOM-MULTI-001: complete R1 quartets"]
  separation["Certified XRBD projection kernels + disjoint Pressure chains"] --> coordinated
  lsb["DIFF-12-001: LSB exclusions"] --> low2["DIFF-12-003: all-site low-two-bit gate"]
  low2 --> bb["DIFF-12-004: complete BB exclusion + refinements"]
  anf["Exact serial-Chi ANF + derivative certificates"] --> degree["ALG-DEG-001: coordinate degree map"]
  anf --> cubes["INT-CUBE-001: checkpoint threshold / fixed cube"]
  byte["INT-BYTE-002: byte-0 cube-sum ranks"] --> division["DIV-BYTE-001: exact balance spaces"]
  tables["Exact local derivative tables + Pressure pullback"] --> division
  carry["Joint carry recurrence + analytic suffix bound"] --> low17["PRESS-WALSH-003: exact low-17 class"]
  coset["LIN-HULL-001: signed rate coset identity"] --> open["OPEN: useful global quantitative hull bound"]
  low17 -. "partial component control only" .-> open
  six -. "restricted mask class only" .-> open
```

### OPEN / RESEARCH TARGET — not proved claims

- **Global linear hull:** the all-mask `lambda_r` target below remains open;
  `2^-128` at eight rounds is a target. The signed `2^776`-term coset sum
  [LIN-HULL-001](#lin-hull-001) and intermediate-mask interference remain
  proof obligations, not security estimates.
- **General Pressure:** arbitrary coupled 64-bit output masks remain outside
  the closed two-shear and low-17 classes.
- **Two-round activity:** unrestricted `[1,2]` is not globally closed; AA and
  distinct mixed AB/BA remain open. BB and same-pair exclusions do not cover them.
- **Hash activity and differential hulls:** the three fixed-difference gates
  do not prove a universal `A1=5 ⇒ A2≥3`; all-difference/all-output probabilities
  and multi-round hull bounds remain separate targets.
- **Other attack families:** the exclusions below apply only to their defined
  families. Selected cubes, backgrounds, masks and reduced analogues do not
  exclude all integrals, boomerangs, rebound attacks or subspaces.

The original detailed targets and failed inequalities appear in “Proof work
remaining” and “Why the existing local lemmas do not yet yield a useful global
bound” below. E-labelled examples in theorem sections remain examples.
<!-- END THEOREM NAVIGATION -->

## Global linear-correlation target

For 1272-bit message mask `alpha` and 2048-bit state mask `beta`, define

`Corr_r(alpha,beta) = 2^-1272 sum_m (-1)^(alpha·m XOR beta·F_r(m))`.

The desired theorem is a **numerically useful** upper bound

`max_{alpha != 0, beta != 0} |Corr_r(alpha,beta)| <= 2^-lambda_r`

for each `r=1..8`, especially `r=8`, with no selected-mask or
selected-message restriction. The Walsh sum already includes the complete
linear hull—all intermediate masks, with their signs. A bound around
`2^-128` at eight rounds would address one strong form of linear
distinguishing resistance for this fixed hash input class. It would not
by itself prove collision or preimage security, and the number `128`
is a research target, not an established result.

<a id="lin-global-001"></a>
## Theorem proved: no perfect relation for rounds 1–8

<!-- THEOREM METADATA LIN-GLOBAL-001 -->
**Permanent ID:** `LIN-GLOBAL-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-GLOBAL-001 -->

**Theorem.** For each `r=1,...,8`, there is no nontrivial affine relation

`alpha·m XOR beta·F_r(m) XOR c = 0`

holding for every valid 159-byte message `m`, for any masks `alpha,beta`
not both zero and any bit `c`. Equivalently, the absolute correlation is
**strictly less than one** for every nontrivial mask pair. This includes
all masks of the first 256 output bits (the digest-length portion) as a
special case.

**Certificate.** A graph row is the 3321-bit vector
`(1, m[1272], F_r(m)[2048])`. Any universal affine relation must be
orthogonal to every such row. `krakken_full_linear_rank.py` found 3,325
valid messages for which the graph rows have rank **3321/3321** for
every `r=1..8`. The first full ranks occurred between messages 3,321
and 3,325. The certificate is `full_linear_rank_8rounds_messages.bin`
(concatenated 159-byte messages), with a digest in
`full_linear_rank_8rounds.json`. The script uses the original C layers
and verifies the manual eight-round one-block result against the hash
API. `krakken_full_linear_rank_audit.py` replayed the entire certificate
through the same source and confirmed rank 3321 in a different, low-pivot
elimination order (`full_linear_rank_8rounds_audit.json`).

This is a **deterministic proof from a finite certificate**, not a
statistical claim: if a relation held for all `2^1272` messages, it
would hold on these 3,325, contradicting full rank.

The resulting numeric bound is only
`|Corr_r| <= 1 - 2^-1271` by the even-integer spacing of a Walsh sum.
That is formally global but far too weak to estimate attack complexity.
The theorem closes the correlation-`1` case; it does **not** establish
a useful `lambda_r`.

<a id="lin-chi-001"></a>
## Theorem proved: exact sparse-mask Chi1 correlations

<!-- THEOREM METADATA LIN-CHI-001 -->
**Permanent ID:** `LIN-CHI-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-CHI-001 -->

For each serial-Chi byte-pair component, the exact 16-bit Walsh table has
maximum absolute correlation `1/8` for a nonzero output mask (see the
pure-Python `sbox_walsh_certificate.json`). The new
`krakken_rate_chi_component_rank.py` certificate checked **every** set of
one, two, and three such components in the first padded hash block:

| Components `t` | Sets checked | Message-to-selected-input rank | Sharp maximum over masks |
|---:|---:|---:|---:|
| 1 | 128 | 16/16 | `2^-3` |
| 2 | 8,128 | 32/32 | `2^-6` |
| 3 | 341,376 | 48/48 | `2^-9` |

**Theorem.** Let `H(m)` be the state immediately after first-round Chi,
before XRBD and Pressure. For *every* message mask `alpha` and *every*
post-Chi output mask `beta` active on exactly `t=1,2,3` serial-Chi
byte-pair components,

`|Corr(alpha·m, beta·H(m))| <= 2^(-3t)`.

For each `t`, this bound is attained by some masks, so the maximum for
that complete sparse-mask class is exact. To prove it, the certified
rank `16t` makes the selected Chi inputs independent and uniform. A
message mask outside the row span of those selected inputs has zero
correlation; a mask in the span gives a product of `t` exact local Chi
coefficients, each of magnitude at most `1/8`. Choosing locally optimal
masks in each component attains the product. The fixed padding changes
only the sign. The report is `rate_chi_component_rank_3_pure_replayed.json`.
`krakken_rate_chi_component_rank_audit.py` replayed all 349,632 subset
ranks with the opposite pivot order; its report is
`rate_chi_component_rank_3_pure_audit.json`.
This closes the stated sparse-mask class at **Chi1**; this theorem by
itself makes no claim about complete rounds or masks touching four or
more components. The four-component class is separately closed below.

<a id="lin-chi-002"></a>
## Theorem proved: exact four-component sparse-mask Chi1 correlations

<!-- THEOREM METADATA LIN-CHI-002 -->
**Permanent ID:** `LIN-CHI-002` · **Proof classification:** analytic proof plus finite exhaustive rank certificate. No external certificate reproduction is recorded.
<!-- END THEOREM METADATA LIN-CHI-002 -->

For a uniform valid 159-byte padded first-block message, **every** four
distinct serial-Chi components have jointly uniform 64-bit pre-Chi inputs.
The message-to-selected-input projection has rank 64 for all
`C(128,4)=10,668,000` selections. An explicit SHAKE-derived 128-bit
projection of each full 1,272-bit coordinate row makes these rank checks
compact: rank 64 after projection proves rank 64 before projection. Two
complete C scanners use separate enumeration and opposite-pivot elimination;
an [independent Python prefix audit](../results/krakken_rank4_extension_audit.json)
reconstructs all 1,272 message-basis columns and all 2,048 coordinate and
projected rows. This is **base-input projection rank**, not the distinct
outside-support quotient rank that has six 63-dimensional exceptions.

Let `H(m)` be the state immediately after Chi1. For every message mask
`alpha` and every post-Chi output mask `beta` active on exactly four
components, `|Corr(alpha·m,beta·H(m))|<=2^-12`; the maximum over this
entire class equals `2^-12`. A mask outside the selected-input row span
cancels on its kernel. Inside the span, the four independent local Walsh
coefficients factor and each has magnitude at most `1/8`. The mask
`(0x38,0x38)` to `(0x01,0x00)` attains `-1/8` locally, so its lift over
any four cells attains the product. This concerns Chi1, before Pressure;
no full-round or eight-round bound follows.

<a id="boom-local-001"></a>
## Theorem proved: maximal local serial-Chi boomerang family

<!-- THEOREM METADATA BOOM-LOCAL-001 -->
**Permanent ID:** `BOOM-LOCAL-001` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA BOOM-LOCAL-001 -->

Let the effective two-byte serial-Chi permutation be
`F(a,b)=(u,v)=(S(a XOR b),S(b XOR u))`, with a bijective byte S-box
`S`. For every nonzero byte `beta` and nonzero byte `gamma`,

`B_F[(beta,beta),(gamma,0)]=2^16=65,536`.

The family contains `255²=65,025` nontrivial entries. Since a BCT
entry counts at most `2^16` bases, the component's nontrivial
boomerang uniformity is exactly the maximal value `65,536`. This
theorem alone does not establish completeness; `BOOM-LOCAL-002` below
closes that question.

**Proof.** Diagonal input translation by `(beta,beta)` leaves
`a XOR b`, hence `u`, fixed. With `I=S^-1`, the inverse is
`b=I(v) XOR u`, `a=I(u) XOR b`. The diagonal translation changes
`I(v)` by `beta`. Now XOR `(gamma,0)` into both output points; the
changed `u` is equal in both, so the inverse points still differ by
`(beta,beta)` for every base. This establishes the BCT equality
independently of ABYSSAL's other statistics. The fresh
[original-C continuation](../scripts/krakken_boomerang_fresh.py) parses and
verifies the current S-box bijection and checks 64,000 embedded local
quartets at all 128 byte-cell sites. The argument, rather than a
selection of examples, proves the whole family.

This is an **attack-side component theorem**, not a complete-round
boomerang distinguisher. The fresh continuation and its exact finite
scope are stated below; no historical quartet result is used.

<a id="boom-local-002"></a>
## Theorem proved: complete local serial-Chi boomerang classification

<!-- THEOREM METADATA BOOM-LOCAL-002 -->
**Permanent ID:** `BOOM-LOCAL-002` · **Proof classification:** analytic reduction plus finite exhaustive proof of the remaining byte-table case. The separate original-C truth-table and direct-BCT checks are implementation audits; no external certificate reproduction is recorded.
<!-- END THEOREM METADATA BOOM-LOCAL-002 -->

For the same effective two-byte serial-Chi permutation `F` as in
`BOOM-LOCAL-001`, the **only** nontrivial perfect boomerang pairs are
`alpha=(d,d)`, `beta=(r,0)` with `d,r` nonzero. There are exactly
`255²=65,025` such pairs. Every other nontrivial pair has
`B_F[alpha,beta]≤1,536`, or uniform unrestricted-base success probability
at most `3/128`; this bound is sharp, for example at
`alpha=(01,01), beta=(01,05)` in hexadecimal byte notation.

**Proof.** The [full derivation](THEOREM.md) changes coordinates to
`t=a XOR b` and `z=b XOR S(t)`, and expresses each 16-bit BCT entry as a
sum of byte S-box BCT entries. With `p=da XOR db`, `q=db`, and
`T_r(t)=S^-1(S(t) XOR r)`, the exact count is

`B_F[(da,db),(r,s)] = Σ_{t: T_r(t) XOR T_r(t XOR p)=p} B_S[q XOR S(t) XOR S(t XOR p),s]`.

The byte S-box has nonzero DDT maximum 4 and nontrivial BCT maximum 6.
For `p=0`, the formula is `256 B_S[q,s]`, yielding precisely the perfect
family when `s=0`, and at most 1,536 otherwise. For `p,r≠0,s=0`, it is
`256 B_S[p,r]≤1,536`. For `p,r,s≠0`, at most four of at most six admitted
terms can equal 256, so the count is at most `4·256+2·6=1,036`.
For `p≠0,r=0,s≠0`, the exact count is the XOR convolution
`Σ_d D_S[p,d] B_S[q XOR d,s]`. All `255·256·255=16,646,400` entries of
this last case were exhaustively computed with two exact integer
implementations, which agree entry for entry and give maximum 1,364.
The first two cases attain 1,536. This exhausts all nontrivial pairs.

The 128 effective cells of unrestricted `chi_scalar` use disjoint bytes,
so their uniform-base BCT probabilities multiply exactly. A full-Chi
pair is perfect exactly when each cell has zero input difference, zero
output difference, or belongs to the perfect family above. If `k` cells
fail those conditions, its BCT probability is at most `(3/128)^k`,
sharply. The exact count of full-Chi perfect pairs with both global
differences nonzero is `196096^128−2·2^2048+1`.

The [source-pinned verifier](../scripts/krakken_chi_bct_classification.py)
and [certificate](../results/krakken_chi_bct_classification.json) use the
current original C Chi mapping and independently implement the finite
convolution in C and integer Walsh arithmetic. The certificate was rerun
byte for byte. This is a local/unrestricted-Chi result under a uniform
base. It does not bound a full-round or hash-reachable boomerang, and it
does not replace the different Chi2 rectangle condition used in the
multi-cell continuation work.

<a id="boom-embed-001"></a>
## Theorem proved: one-cell boomerang embedding and first-block exclusion

<!-- THEOREM METADATA BOOM-EMBED-001 -->
**Permanent ID:** `BOOM-EMBED-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA BOOM-EMBED-001 -->

In the current C source, each serial-Chi cell at row `y`, pair `p`,
byte offset `j` has effective input `(a,b)` and output `(u,v)` as above;
the second word's byte lies at offset `(j-4) mod 8` because of the
32-bit rotation. For nonzero `d,gamma` and arbitrary `u,v`, put
`e = v XOR S(S^-1(v) XOR d)`. The four post-Chi1 states with local
output bytes `(u,v)`, `(u,v XOR e)`, `(u XOR gamma,v)`, and
`(u XOR gamma,v XOR e)` form a rectangle. Inverting Chi shows the two
horizontal input pairs both have effective difference `(d,d)`;
the two vertical post-Chi1 differences are both `(gamma,0)`.

**Unrestricted embedding.** Every such local quartet, with any common
post-Chi1 background in the other bytes, has a valid four-state
unrestricted permutation embedding at the start of round 1. Chi is
bijective cellwise. The current-C linear prefix
`Theta → MDS → Rho → Pi` has GF(2) rank **2048/2048**, so each of
the four pre-Chi1 states has a unique round-start preimage. The
[embedding certificate](../results/krakken_boomerang_embed.json) contains one
four-state round-start witness and replays its complete first round
through the original-C entry point. An independent Python prefix
implementation matches all 2,048 original-C basis columns. The rank
argument applies to every
local family member; the file stores only one concrete witness.

**First-block hash exclusion.** This one-cell horizontal difference
cannot be obtained from any nonzero difference of two valid 159-byte
messages in their first absorb block. For each of the **128** cell
sites, the C-derived 1272-column rate-to-pre-Chi1 map, projected
outside that cell's two input bytes, has rank **1272/1272**. Hence
zero outside the cell forces the input-message difference to zero.
The [rate-gate certificate](../results/krakken_boomerang_rate_gate.json) recomputes
all ranks with highest-pivot and lowest-pivot GF(2) elimination;
its Python prefix independently matches all 1,272 original-C columns.
This excludes the one-cell inbound at the first absorb only; it does
not cover multi-cell structures or later absorb blocks.

<a id="diff-rate-001"></a>
## Theorem proved: exact first-block Chi1 minimum is 5

<!-- THEOREM METADATA DIFF-RATE-001 -->
**Permanent ID:** `DIFF-RATE-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-RATE-001 -->

Consider all nonzero XOR differences between valid 159-byte first-block
messages, with the fixed `0x86` byte and initial capacity unchanged.
Let `A1` count active byte-S-box **inputs** in serial Chi1. Then

`min A1 = 5`.

The support part is exact. The 1272-bit message-to-pre-Chi1 image was
computed from the current original-C `Theta → MDS → Rho → Pi` prefix.
Quotienting the 2048-bit state by that image maps each 16-bit serial-Chi
input cell to 16 syndrome vectors. A rate-reachable nonzero difference
confined to a set of cells exists exactly when those vectors are
linearly dependent. Exhaustive GF(2) rank checks give:

| Support size | Cell sets | Minimum quotient rank | Full rank |
|---:|---:|---:|---:|
| 1 | 128 | 16 | 16 |
| 2 | 8,128 | 32 | 32 |
| 3 | 341,376 | 48 | 48 |
| 4 | 10,668,000 | 63 | 64 |

Exactly **six** four-cell supports have rank 63; every other four-cell
support has rank 64. Each exception has a one-dimensional reachable
difference intersection. The [original-C rank enumeration](../results/krakken_boomerang_rate_support.json)
and [independent Python prefix/opposite-pivot audit](../results/krakken_boomerang_rate_support_audit.json)
agree on all **10,668,000** four-cell supports and the same
six exceptions. The [message-difference certificate](../results/krakken_boomerang_four_cell_witness.json)
solves the rate map for each exception and replays all six valid
159-byte differences against the original C.

Every active serial-Chi input cell costs at least one active S-box call.
For each of the six four-cell differences, the four effective input
byte differences `(da,db)` are rotations of
`(110,4), (0,90), (5,32), (16,3)`. The first S-box input differences
are `da XOR db = 106,90,37,19`. To silence the second S-box, the
byte S-box derivative would need output difference `db`. The exact
DDT counts for these four requests are **`0,2,0,2`**. Therefore the
first and third cells necessarily cost two calls each, and the other
two cost at least one: every four-cell reachable difference has
`A1 >= 6`. A difference involving at least five cells has `A1 >= 5`.
This proves the universal **lower bound 5**.

The matching **upper bound 5** is attained by an actual valid
159-byte message pair. The [attaining certificate](../results/krakken_five_cell_candidates.json)
stores both messages and their five active Chi1 cells, each with
exactly one active call. The [independent original-C/Python audit](../results/krakken_five_cell_witness_audit.json)
replays the padding, prefix, Chi1, first complete round, Chi2, and
full 32-byte hash digests. The witness has **A1=5, A2=255**; its
five post-Chi1 active bytes become **216 active bytes after XRBD1**.
These A2 and XRBD figures describe that witness, not every five-call
input.

As an intermediate exact subfamily result, every reachable difference
confined to four Chi cells needs **at least six** calls. For each of
the six such difference lines, the
[constructed valid-message pair](../results/krakken_boomerang_four_cell_optimum.json)
uses the two nonzero DDT entries to silence the second S-box in the
other two cells; original-C replay gives active-call pattern
`(2,1,2,1)`. The [independent audit](../results/krakken_boomerang_four_cell_optimum_audit.json)
recomputes the C-derived prefix and Chi in Python and reproduces the
original-C complete-hash digests for all six message pairs.

For these **six witnesses only**, the original-C [outbound trace](../results/krakken_boomerang_four_cell_outbound.json)
and [independent Python replay](../results/krakken_boomerang_four_cell_outbound_audit.json)
find **242–247 active bytes after XRBD1** and **A2=253–255**. This
is concrete cross-round behavior, not a universal A2 bound. These
four-cell differences are hash-reachable but are not the one-cell
perfect local boomerang inbound.

For the **fixed message XOR difference of the five-call witness**, the
five relevant first-S-box input bytes form a rank-40 linear projection
of the 1272 free message bits, so they are jointly uniform under a
uniform valid base message. Each of the five required S-box derivatives
has exactly two favorable byte bases out of 256. Consequently the
probability of the event `A1=5` for this **fixed difference** is
exactly **`(2/256)^5 = 2^-35`**, or `2^1237` favorable base messages
among `2^1272`. The [source-pinned calculation](../results/krakken_five_cell_probability.json)
and [independent Python audit](../results/krakken_five_cell_probability_audit.json)
verify the derivative counts and rank 40/40. This is an activity-event
probability, not the probability of a specified full-round
differential trail.

**Common-prefix later-absorb corollary (same `DIFF-RATE-001` ID).** Let two
equal-length hash messages share any number of complete 160-byte prefix
blocks and differ nontrivially only in their final partial block of
length `1..159` bytes. At the Chi layer of the permutation call for that
final padded block, the two states have **at least five active serial-Chi
byte-S-box calls**, regardless of the populated common capacity state.
The one-, two-, and three-cell support exclusions also carry over.
This is a property of the first round of the **later permutation call**,
not a claim that the overall multi-block hash has only one round.

**Proof.** After each shared complete block the two sponge states are
identical. At the final absorb, identical-length padding cancels in the
XOR difference, leaving a nonzero difference confined to at most the
first 159 rate bytes and zero capacity difference. The next
Theta→MDS→Rho→Pi map is linear, so its pre-Chi difference is exactly
the same rate-image vector as for a first padded block with that suffix
difference. The `A1>=5` support/DDT proof above quantifies over **all**
base values at Chi and therefore applies despite the new common base
state. This argument does not cover messages with different earlier
blocks or a differing complete 160-byte block; in those cases the
capacity difference need not be zero. A [source-pinned original-C audit](../results/krakken_common_prefix_gate_audit.json)
checked 288 paired executions over 0–3 shared full blocks and final
lengths 1, 17, and 159, verified identical pre-Chi differences with
and without the shared prefix, and replayed their full hash outputs.
Those finite checks validate the implementation; the absorb identity
and the existing `DIFF-RATE-001` theorem give the universal claim.

<a id="diff-rate-002"></a>
## Theorem proved: exact sparse-output probabilities for all six four-cell rate lines

<!-- THEOREM METADATA DIFF-RATE-002 -->
**Permanent ID:** `DIFF-RATE-002` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-RATE-002 -->

Fix any one of the six valid 159-byte first-block message XOR
differences in the complete four-cell support exception certificate
above, and choose the base message uniformly from all `2^1272`
valid messages. The first-Chi activity has the **exact distribution**

`A1 = 6 + Binomial(2,127/128)`.

Equivalently, `Pr[A1=6]=2^-14`, `Pr[A1=7]=254/2^14`, and
`Pr[A1=8]=16129/2^14`. For **every specified 256-byte post-Chi1
difference** under the fixed input difference,

`Pr[that post-Chi1 difference] <= 2^-38`,

and the bound is **sharp for each of the six differences**. Conditioned
on `A1=6`, the sharp maximum for one specified post-Chi1 difference
is `2^-24`.

**Proof.** The original-C message-to-pre-Chi1 basis gives rank `64/64`
on the eight selected input bytes of the four active serial-Chi
components, independently for all six message differences. These
four two-byte bases are therefore mutually uniform and independent
under the uniform valid-message base distribution, despite the fixed
padding and initial capacity. Exhaustive enumeration of all `2^16`
two-byte bases per distinct local input difference gives exactly
`[0,512,0,512]` one-call bases across the four cells. The other two
cells always cost two calls. Thus the two possible second-call
cancellations are independent, each with probability `512/65536=1/128`,
giving the stated activity distribution.

The same exact local enumeration gives maximal counts
`[16,512,16,512]` for **one prescribed output-byte pair** in the
four cells. Uniform independence makes the largest complete
post-Chi1 probability exactly

`(16*512*16*512)/2^64 = 2^-38`.

The local maximizing output pairs are simultaneously attainable
because the selected-input projection has full rank. Dividing this
sharp probability by `Pr[A1=6]=2^-14` gives the conditional sharp
maximum `2^-24`. This is an exact **one-Chi-layer differential-output
distribution theorem for six fixed hash-reachable differences**, not
a differential-hull probability across a complete round.

The [producer and six attaining valid-message witnesses](../results/krakken_four_cell_probability.json)
and [independent C-S-box/opposite-pivot audit](../results/krakken_four_cell_probability_audit.json)
verify all six rank calculations, the local counts, and original-C
Chi1 and Chi2 replays. The six maximizing witnesses have `A2`
values `256,256,256,251,256,255`; those are witness values, not a
universal round-two lower bound. This theorem does not cover other
first-block input differences or later absorb blocks.

<a id="diff-rate-003"></a>
## Theorem proved: three fixed valid-message differences satisfy `A1=5 => A2>=3`

<!-- THEOREM METADATA DIFF-RATE-003 -->
**Permanent ID:** `DIFF-RATE-003` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-RATE-003 -->

Fix any of the three 159-byte message XOR differences indexed
`(support,difference)=(2,6),(2,9),(21,2)` in the source-pinned
[five-cell candidate set](../results/krakken_five_cell_candidates.json). These are
the three minimum-five lines in that **selected 155-support set**, not
an enumeration of all valid message differences. For every valid base
message for which any one of these differences attains `A1=5`, the
second round satisfies **`A2>=3`**: its pre-Chi2 difference touches at
least three distinct 16-bit serial-Chi cells. Consequently
`A1+A2>=8` within each of these three conditioned events.

The five nonzero pre-Chi1 cells each have a nonzero first-S-box input
difference. Thus `A1=5` forces the second S-box call inactive in all
five. In a serial cell, that fixes the first-S-box output difference
to the known second input-byte difference, so the **entire post-Chi1
difference is fixed** for every base message in each event. All three
events are attained by valid-message pairs replayed through original C.

Propagate each fixed post-Chi1 difference through exact XRBD. For a
hypothetical pre-Chi2 difference supported in at most two serial-Chi
cells, allow **arbitrary 16-bit differences in both cells**. Pull each
cell's full 16-bit basis backward through the exact inverse of
`shuffle → Theta → MDS → Rho → Pi` to Pressure's output. Pressure
obeys 32 exact bit-zero XOR identities, two for each 128-bit chain.
All 128 one-cell supports are excluded for each difference. Of the
`C(128,2)=8,128` two-cell supports per difference, the bit-zero
identities exclude all pairs for the first two lines and all but two
for `(21,2)`. Those two pairs are cells `(10,54)` and `(20,107)`.
Their bit-zero equations leave respectively 32 and 256 affine
endpoint assignments. For each assignment, an **exact joint low-two-bit
Pressure transition test** enumerates the 64 possible independent
two-bit base slices in each relevant chain, including both additions
and their carry dependence. None survives. Thus even the enlarged
family allowing arbitrary 16-bit differences in two Chi2 cells is
excluded, and `A2>=3` follows.

The [three-line producer](../scripts/krakken_a15_three_line_gate.py) and
[certificate](../results/krakken_a15_three_line_gate.json) record the complete
support scan and three attaining pairs. The
[independent audit](../scripts/krakken_a15_three_line_gate_audit.py) and
[audit certificate](../results/krakken_a15_three_line_gate_audit.json) rebuild
the 2048-bit inverse with the opposite GF(2) pivot order, replay the
witnesses and Pressure checks through original C, and independently
enumerate the low-two-bit transitions. The witness `A2` values are
`256,254,256`; these do not assert a universal value. The earlier
[one-line rank certificate](../results/krakken_sponge_a15_rank_all.json) remains
valid for `(2,6)`. The present theorem covers only these three fixed
hash-reachable differences and says nothing about the global minimum
of `A1+A2`.

<a id="diff-rate-004"></a>
## Theorem proved: exact five-call minimum at the first full 160-byte absorb

<!-- THEOREM METADATA DIFF-RATE-004 -->
**Permanent ID:** `DIFF-RATE-004` · **Proof classification:** analytic support/DDT argument plus finite exhaustive proof of all one- through four-cell supports. Separate original-C and Python-prefix implementations agree; the five-call attaining messages are replayed through original C. No external certificate reproduction is recorded.
<!-- END THEOREM METADATA DIFF-RATE-004 -->

For two distinct valid 160-byte messages starting from Krakken's zero
state, let `A` count active serial-Chi byte-S-box calls in the **first
round of the first permutation call**, immediately after absorbing the
un-padded complete 160-byte block. Then

`min A = 5`, over every nonzero 160-byte message XOR difference and
every pair of base messages. The hash API subsequently performs a
separate padded final permutation call for these 160-byte messages;
this theorem concerns the first call only.

**Proof.** The first complete block supplies 1,280 free rate-difference
bits and zero capacity difference. The actual linear
Theta→MDS→Rho→Pi prefix maps these bits injectively to pre-Chi state
differences. Quotient by that image and enumerate supports in the 128
disjoint two-byte serial-Chi cells. The quotient rank equals the full
coordinate dimension for all 128 single cells, 8,128 pairs, and
341,376 triples: no nonzero full-block rate difference can touch fewer
than four cells. Among all 10,668,000 four-cell supports, exactly
**eight** have rank 63 rather than 64. They form one eight-offset
family; the 159-byte domain admits six of these eight, while the
extra byte makes the remaining two reachable. Every exceptional
support has a one-dimensional reachable difference intersection.

For each of the eight difference lines, the four local input-byte
differences are `(110,4), (0,90), (5,32), (16,3)` in decimal. To
silence the second S-box in each serial cell, the byte S-box derivative
for input difference `da XOR db` must output `db`. The exact DDT counts
for those four requests are `(0,2,0,2)`. Thus the first and third
cells each require two active calls and the other two at least one:
every reachable four-cell difference has `A≥6`. Any difference
touching at least five cells has `A≥5`.

For attainment, append the **same byte `0x86`** to both 159-byte
messages in the existing `DIFF-RATE-001` five-call witness. The first
full absorb of each resulting valid 160-byte message is byte-for-byte
identical to that witness's padded 159-byte absorb, so its first-round
activity is exactly five. The [original-C replay](../results/krakken_full_block_witness_audit.json)
confirms the five calls and both complete 160-byte hash executions,
including the extra final padding call.

The [original-C support certificate](../results/krakken_full_block_rate_support_c_four.json)
and [independent Python-prefix certificate](../results/krakken_full_block_rate_support_python_four.json)
agree on every support count, rank minimum, and exceptional four-cell
support. These two complete enumerations share the support-enumeration
and high-pivot rank code; their **prefix implementations** are separate.
A [Python low-pivot recount](../results/krakken_full_block_rate_support_python_low_three.json)
separately confirms all one- through three-cell ranks. The [line certificate](../results/krakken_full_block_four_lines.json)
solves all eight pre-Chi differences back to actual 160-byte rate
differences; its [Python-prefix/DDT audit](../results/krakken_full_block_four_lines_audit.json)
independently replays their linear images and local derivative counts.

**Later full-block corollary.** If two hash messages have identical
complete preceding blocks and first differ in the next complete
160-byte block, the first round of that block's permutation call has
`A≥5`, whatever common state the earlier blocks produced. The states
before this absorb are identical; XORing different rate blocks adds a
nonzero rate-only difference with zero capacity difference. The
support/DDT proof above depends on that difference and holds for every
common base. This corollary does **not** cover differing earlier
blocks, where capacity differences may already exist, nor does it
bound the subsequent final padding call or later rounds.

<a id="diff-rate-005"></a>
## Theorem proved: global prescribed-difference concentration at first Chi

<!-- THEOREM METADATA DIFF-RATE-005 -->
**Permanent ID:** `DIFF-RATE-005` · **Proof classification:** analytic proof using finite exhaustive support, projection-rank, and local-DDT certificates. No external certificate reproduction is recorded.
<!-- END THEOREM METADATA DIFF-RATE-005 -->

For every fixed nonzero difference `delta` between valid 159-byte
first-block messages, every prescribed 2,048-bit difference `eta`, and
uniform valid 159-byte base message `m`, let `H(m)` be the state immediately
after Chi1. Then

`Pr[H(m) XOR H(m XOR delta) = eta] <= 2^-24`.

The same bound holds immediately after XRBD1: its linear invertibility
maps a prescribed output difference to one prescribed Chi1 difference.
Sharpness of the universal bound is **not** established. This is the first
such concentration bound covering **every** nonzero first-block message
difference, rather than six selected four-cell lines.

For a serial-Chi component `F(a,b)=(S(a XOR b),S(b XOR S(a XOR b)))`,
input difference `(da,db)`, and requested output difference `(du,dv)`,
write `dx=da XOR db` and `dy=db XOR du`. The exact number of matching
local bases is `D_S[dx,du] D_S[dy,dv]`. The triangular coordinate
change `(a,b)->(a XOR b,b XOR S(a XOR b))` is bijective, and the two
derivative equations separate in these coordinates. The current S-box
has maximum nonzero DDT entry four. Hence an active local component's
specified output transition has probability at most `1/64` under a
uniform 16-bit base.

`DIFF-RATE-001` excludes any nonzero rate difference supported on at
most three pre-Chi components. Choose four of the active components.
Their 64 base bits are jointly uniform by `LIN-CHI-002`, so the four
specified local output events factor and contribute at most
`(1/64)^4=2^-24`. Ignoring all remaining components only weakens the
upper bound. For a particular `delta,eta`, the exact product of the
four local DDT probabilities is available; if the selected cells
contain `q` active S-box calls, the coarse bound improves to `2^(-6q)`.
The six exceptional four-cell input lines retain their stronger sharp
`2^-38` maximum from `DIFF-RATE-002`.

The same proof applies to the first Chi checkpoint of a final padded
159-byte suffix after any number of **identical** preceding full blocks:
the common pre-absorb state translates the affine base image. On a
message affine subspace of codimension `d`, conditioning alone yields
the weaker `min(1,2^(d-24))` bound. This does not cover differing
prefixes. It cannot be carried through nonlinear Pressure by
bijectivity alone, and cannot be multiplied across rounds. In
particular, `2^-24` is neither a complete-round differential bound
nor 24 bits of hash security.

<a id="diff-chi-001"></a>
## Theorem proved: affine fibers for active-first-call Chi transitions

<!-- THEOREM METADATA DIFF-CHI-001 -->
**Permanent ID:** `DIFF-CHI-001` · **Proof classification:** analytic proof; exhaustive byte derivative checks and selected original-C local transitions are implementation audits. No external certificate reproduction is recorded.
<!-- END THEOREM METADATA DIFF-CHI-001 -->

Fix a local serial-Chi input/output difference with `dx=da XOR db != 0`.
Its set of matching `(a,b)` bases is empty or an affine subspace of
16 bits, of size exactly `D_S[dx,du] D_S[db XOR du,dv]`.
For a bijective 4-uniform byte S-box, each nonempty derivative root
set at nonzero input difference has two or four elements. The roots
form an affine line or plane because they occur in pairs separated by
the input difference. On a four-root plane, the four S-box outputs XOR
to zero, making the restricted S-box affine. Under the bijective
coordinates `x=a XOR b`, `y=b XOR S(x)`, the first and second root
sets form an affine product. The inverse `(a,b)=(x XOR y XOR S(x),
y XOR S(x))` is affine on that product, proving the claim.

Consequently, if a prescribed first-Chi differential has `dx!=0`
in every nonzero input component, the complete valid-message base
condition is an affine GF(2) system after substituting the linear
message-to-pre-Chi map. It has probability **zero if inconsistent**
and otherwise exactly `2^-r`, where `r` is the system rank. This
computes one prescribed transition, without assuming component-base
independence. When `dx=0` and only the second S-box call is active,
the affine-fiber guarantee does not apply. No Pressure constraint is
included.

The [source-pinned extension](../review_extensions_20261003/THEOREMS.md)
checks all 32,385 nonempty nonzero byte derivative fibers, 128 direct
65,536-base local transitions, and original-C representatives. A
[separate prefix/S-box audit](../results/krakken_rank4_extension_audit.json)
rechecks the byte derivative histogram and the four-cell input rows.

<a id="boom-round-001"></a>
## Theorem proved: four defined boomerang classes do not cross Chi2

<!-- THEOREM METADATA BOOM-ROUND-001 -->
**Permanent ID:** `BOOM-ROUND-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA BOOM-ROUND-001 -->

Fix the local site `y=0, p=0, j=0`, differences `d=gamma=128`, and
set every other **post-Chi1** byte to zero. Exhaust every pair of
local output-base bytes `(u,v)` in `0..255` (all **65,536** choices).
For each, form the four-state local boomerang rectangle above, then
apply the original C's `XRBD → Pressure → constants → shuffle →
Theta2 → MDS2 → Rho2 → Pi2 → Chi2` to all four states. The necessary
Chi2 boomerang condition is equal horizontal differences at Chi2 input
and equal vertical differences at Chi2 output. Equivalently, the
four-state XOR defect must vanish before **and** after Chi2.

Exactly **1,300/65,536** choices have zero defect after Pressure and
therefore also at Chi2 input; **zero of those 1,300** has zero defect
after Chi2. Thus **no member of this complete defined class satisfies
the Chi2 boomerang condition**. Pressure does *not* universally kill
the quartet: it preserves 1,300 of them. One unrestricted round-start
witness with `u=v=0` survives to Chi2 input and has 1,017 defect bits
after Chi2. The complete [original-C enumeration](../results/krakken_boomerang_cell_exhaust.json)
and [independent Python audit](../results/krakken_boomerang_cell_audit.json)
agree on the full Pressure histogram, all 1,300 survivors, and the
Chi2 exclusion. The [broader finite grid](../results/krakken_boomerang_fresh_report.json)
and [independent audit](../results/krakken_boomerang_fresh_audit.json) additionally
cover all 128 sites, five independently varied nonzero input and
switch differences (25 pairs), four local bases, and five complete-state
backgrounds: **64,000** quartets, **65** surviving Pressure, none
satisfying the Chi2 condition. That grid is a finite
screen, not a theorem about untested differences or backgrounds.

Three more complete classes use the same site and zero post-Chi1
background, with the following fixed difference pairs:

| `(d,gamma)` | Local bases exhausted | Pressure rectangles | Chi2 BCT survivors |
|---|---:|---:|---:|
| `(128,128)` | 65,536 | 1,300 | 0 |
| `(255,128)` | 65,536 | 1,356 | 0 |
| `(255,1)` | 65,536 | 1,196 | 0 |
| `(128,1)` | 65,536 | 932 | 0 |

The **complete union of these four defined classes** has **262,144**
local base choices, **4,784** Pressure-surviving rectangles, and
**zero** Chi2 BCT survivors. The [additional original-C enumeration](../results/krakken_boomerang_cell_suite.json),
[independent full-base audit](../results/krakken_boomerang_cell_suite_audit.json),
and [combined certificate check](../results/krakken_boomerang_four_class_verified.json)
give their exact scopes. These four pairs are selected attack families,
not all nonzero `(d,gamma)` pairs.

All of these continuation results are **unrestricted permutation**
statements. The exclusion theorem fixes one site, four `(d,gamma)` pairs,
and zero post-Chi1 background. Other local boomerang embeddings,
multi-cell quartets, and hash-reachable multi-cell constructions remain
open. In particular, there is no global claim that boomerangs die at
round 2.

<a id="boom-round-002"></a>
### Stronger certificate: each Pressure survivor has a base-independent Chi2 obstruction

<!-- THEOREM METADATA BOOM-ROUND-002 -->
**Permanent ID:** `BOOM-ROUND-002` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA BOOM-ROUND-002 -->

For the two-byte serial-Chi map `F`, define the exact local rectangle
count

`N_F(a,b) = #{x in {0,1}^16 : F(x) XOR F(x XOR a) XOR F(x XOR b) XOR F(x XOR a XOR b) = 0}`.

The **4,784** Pressure survivors in the four classes enter Chi2 as full-state
rectangles, so their horizontal and vertical input differences decompose
into 128 local mask pairs `(a_j,b_j)`. For **every** one of these 4,784
quartets, at least one Chi2 cell has `N_F(a_j,b_j)=0`. Thus the Chi2
failure is not merely an unlucky value of that cell's 16-bit base:
**no possible base at the obstructing cell can preserve the quartet
while its two input differences remain fixed**. In the first class,
every quartet has nonzero horizontal and vertical differences in all
128 Chi2 cells; the other classes need only one obstructing cell.

The [current-source producer](../scripts/krakken_boomerang_chi2_obstruction.py)
constructs the complete 65,536-entry local `F` table by calling the
original-C `chi_scalar`, checks it against the source-derived two-byte
formula, and counts the local equation exactly. It tested 323 distinct
local mask pairs while finding one zero-count cell for every Pressure
survivor in the first class; 319 of those distinct pairs have zero
count. The [additional obstruction certificate](../results/krakken_boomerang_cell_suite_obstruction.json)
finds one zero-count cell for each of the other 3,484 Pressure
survivors. Across the four classes, the producers counted **1,025**
distinct local mask pairs; **1,019** have zero count. The
[independent audit](../results/krakken_boomerang_chi2_obstruction_audit.json)
recomputes all 323 counts from an independently generated Python/NumPy
table and independently replays the full-layer input differences for
all 1,300 first-class quartets. The
[suite audit](../results/krakken_boomerang_cell_suite_audit.json) independently
recomputes the other 702 local counts and replays all 3,484 additional
quartets. The [first-class certificate](../results/krakken_boomerang_chi2_obstruction.json)
and suite certificate record each obstructing cell and its masks.

This conditional theorem fixes the **difference patterns produced by
the specified 4,784 Pressure-surviving quartets**. A different
post-Chi1 background can change Pressure's output differences, and
multi-cell or hash-reachable inbounds remain outside this claim.

<a id="boom-multi-001"></a>
## Theorem proved: coordinated multi-cell quartets cross complete round one

<!-- THEOREM METADATA BOOM-MULTI-001 -->
**Permanent ID:** `BOOM-MULTI-001` · **Proof classification:** analytic proof + finite exhaustive proof of the stated projection ranks. Independent implementation audit: all 16 ranks, saved complete-round C quartet, and follow-up classification of all 1,344 reached Chi2 patterns/counts; no full independent replay of every complete-round-two sample.
<!-- END THEOREM METADATA BOOM-MULTI-001 -->

This is an **attack-side unrestricted-permutation theorem**. Let `E,O`
be the 1024-dimensional first/second serial-Chi output-coordinate
spaces and `X` the current XRBD map. For each Pressure-chain unit
`G` in `{0,2}, {1,3}, {4,6}, {5,7}, {8,10}, {9,11}, {12,14}, {13,15}`,
both spaces of `U in E` and `V in O` whose XRBD images are confined
to `G` have exact dimension **128** (outside-support rank 896).

For any distinct units `G,H`, any nonzero permitted directions `U,V`
respectively, and any common post-Chi background `B`, the quartet
`(B,B XOR V,B XOR U,B XOR U XOR V)` has inverse-prefix/inverse-Chi
round-start states whose XOR is zero and complete-round-one outputs
whose XOR is zero. These four states are distinct.

**Proof.** Inverse serial Chi is `b=I(v) XOR u`, `a=I(u) XOR b`, a
sum of functions of the two separate output bytes. Its mixed rectangle
XOR vanishes, and the `V` sides give matching diagonal input
differences, embedding the local perfect family wherever both
directions are nonzero. The inverse linear prefix preserves zero XOR.
XRBD maps the directions to disjoint Pressure chains. Within each
chain the four bases occur in equal pairs, so their output XOR is
zero for every background and every carry behavior. Constant XOR and
the linear shuffle preserve it. The 16 projection ranks were computed
from original-C columns and independently reproduced with opposite
pivot elimination. No local probability product is assumed.

This closes the **complete defined one-round construction class**;
it does not establish a fixed complete-round BCT entry across all
bases, a two-round continuation, or valid-message reachability.
Input/output direction values can change with the background.
A fixed saved quartet supplies a four-query one-round full-state
zero-sum test: random-permutation acceptance is `1/(2^2048-3)`, whereas
the constructed quartet accepts deterministically for round one.
This is not a distinguisher for eight-round Krakken.

The [detailed construction](KRAKKEN_MULTICELL_BOOMERANG.md),
[producer](../scripts/krakken_multicell_boomerang.py), and
[report](../results/krakken_multicell_boomerang_sample.json) also record a
**finite systematic sample**, separately from the theorem: all 56
ordered unit pairs, 24 choices each, 1,344 original-C quartets;
1,047 have at least two nontrivial overlapping local cells. None of
these samples preserves the rectangle after Chi2 or complete round
two. The observed minimum defects are 903 and 950 bits, respectively;
neither is a proved class-wide lower bound.

The [separate audit](../scripts/krakken_multicell_boomerang_audit.py) and
[report](../results/krakken_multicell_boomerang_audit.json) replay the saved
four round-start states through both complete C round counts and
recompute all 16 ranks. For that saved pattern only, exhaustive local
counting gives zero compatible Chi2 rectangles at cell `(0,0,0)`
with differences `(1190,1536)`. This obstruction covers every local
base for that fixed pair; it does not exclude changed earlier
backgrounds or other members of the coordinated family. The audit
does not replay every sampled continuation. General multi-cell
boomerangs through round two and shared-chain carry matching remain open.

**Finite verification follow-up, same 1,344 constructions.** The
[classification report](../results/krakken_multicell_20260930/README.md) now records
all 172,032 reached Chi2 cell occurrences (172,003 distinct unordered
pair keys). Every construction has at least one exact zero-count cell,
and none has positive counts in every cell; each has 111–128 zero-count
cells. All selected obstruction pairs were directly enumerated over
65,536 local bases. A new original-C replay checks every quartet through
Chi2, and a separate Python implementation checks every reached count
and certificate. This extends the finite verification beyond the one
saved pattern above. It excludes a repaired Chi2 rectangle for each
fixed reached difference pattern, not other earlier backgrounds or
directions in the whole coordinated family. No general two-round
exclusion or hash reachability claim is added.

**First-block rate-gate follow-up, same 1,344 saved directions.** The
[source-pinned classification](../results/krakken_multicell_20261002/README.md)
uses the exact inverse-Chi byte relations and the 1,272-bit valid-message
prefix image. It excludes **896** saved U/V direction pairs from valid
159-byte first-block embedding for *every* common background; the
other **448** pass only these linear necessary tests and are not known
reachable. Original-C prefix columns and an independent Python-prefix,
opposite-pivot audit agree on every record. This is a complete finite
classification of those saved directions, not a universal claim about
the full 128-dimensional direction spaces or later absorb blocks.

<a id="diff-perm-001"></a>
## Theorem proved: one active Chi1 call reaches every Pressure chain

<!-- THEOREM METADATA DIFF-PERM-001 -->
**Permanent ID:** `DIFF-PERM-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-PERM-001 -->

For the current XRBD-enabled **unrestricted permutation**, suppose
exactly one of the 256 serial-Chi byte S-box calls in round 1 has a
nonzero input difference. Its post-Chi1 difference is one nonzero
byte. After XRBD, the difference has nonzero bytes in **all 32
64-bit lanes**, at least **32 active bytes**, and nonzero input in
**all 16 disjoint 128-bit Pressure chains**. For every pair of base
states realizing that difference, all 16 Pressure-chain output
differences are also nonzero. This is a chain-activity statement,
not a lower bound on Chi2 S-box calls or a trail probability.

The [complete certificate](../results/krakken_xrbd_onebyte_pressure_chains.json)
enumerates every one of `256 × 255 = 65,280` one-byte
position/value differences. An independent Python implementation of
the five XRBD butterfly stages agrees with current original C in
all 65,280 cases; the active-byte range is **32–196** and the
active-lane and active-chain counts are exactly **32** and **16**
throughout. The certificate pins the C/header hashes and an ordered
digest of the full XRBD output table.

Pressure's 128-bit chain is bijective: from outputs `A,C`, recover
`c=C−(A XOR (A<<31)) (mod 2^64)` and then
`a=A−(c XOR (c>>17)) (mod 2^64)`. The other chain has the same
form after undoing its output rotations. Hence a nonzero pair input
difference cannot map to a zero pair output difference. The
[certificate script](../scripts/krakken_xrbd_onebyte_pressure_chains.py)
checks this inverse against 1,600 original-C chain executions.
The first padded hash block has its own stronger rate-interface
restrictions; this theorem is stated for unrestricted permutation
differences.

<a id="diff-perm-002"></a>
## Theorem proved: no unrestricted two-round `[1,1]` differential trail

<!-- THEOREM METADATA DIFF-PERM-002 -->
**Permanent ID:** `DIFF-PERM-002` · **Proof classification:** solver-backed exhaustive exclusion. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-PERM-002 -->

For the source-pinned XRBD-enabled permutation, let `A1,A2` count
active byte S-box calls in serial Chi of rounds 1 and 2. For **every**
nonzero unrestricted 2048-bit input difference and every choice of base
state, `(A1,A2) != (1,1)`. Consequently every nonzero two-round
differential trail has `A1+A2 >= 3`. This includes first-block
hash-reachable differences as a subset, but the lower bound is on the
two-round **total**, not on round 2 alone.

**Exhaustive model argument.** One active Chi1 call has exactly one
nonzero post-Chi1 byte. The [SCIP model](../krakken/krakken_prove_11_v2.py)
allows every nonzero value at every one of the 256 byte locations.
XRBD is exact. For each 128-bit Pressure branch, the modular-addition
XOR difference at bit `i` obeys
`dz_i=dx_i XOR dy_i XOR dc_i`, where `dc_i` is the difference of
the two carry bits and `dc_0=0`. Its allowed next-carry difference
is a **superset** of the real full-adder behavior: it is zero if all
three input differences are zero, one if all three are one, and
unrestricted otherwise. The extra condition that each branch output
difference be nonzero is sound because XRBD gives every branch a
nonzero input for all 65,280 location/value choices and each Pressure
branch is bijective. The subsequent InkCloud→Theta→MDS→Rho→Pi
difference map is compiled exactly. Inverse-mapping both one-active
Chi2 support families—first or second S-box, every component and byte
location—gives a superset of all real `[1,1]` trails. Round constants
cancel in XOR differences.

The [complete run log](../krakken/prove_11_full.log) records
`512/512` SCIP `INFEASIBLE` jobs: 256 start byte positions times both
Chi2 branches, with no timeout or unknown result. The
[independent audit](../scripts/krakken_11_audit.py) verifies the source and log
hashes, exact job coverage, all 65,280 XRBD branch cuts, the relaxed
carry truth table, 768 constructed one-active Chi shapes, and C-vs-model
linear layers. The [audit report](../results/krakken_11_audit_validated.json)
pins the artifacts, but its `replayed_scip_jobs` field is empty:
**no independent solver reruns are recorded in this cited report**.
The audit script offers optional representative replays through `--replay`;
that capability is not evidence that they were performed. The original
512-job producer log and the implementation/model checks are distinct
from an independent solver replay or a formally checked UNSAT proof object.
The result is a solver-backed exhaustive
impossibility theorem for the stated class; an independent reviewer can
rerun all 512 jobs from the source script.

This does **not** prove `[1,2]` or `[2,1]` impossible, nor a useful
large eight-round active-S-box minimum. The conservative multi-round
corollary below follows separately from this adjacent-round exclusion.
A faster sieve using just Pressure's
32 exact LSB relations was tested across all 65,536
start-position/one-active-target cases. Simple full-column rank
excludes none, but adding the required nonzero-byte condition excludes
**18,349 endpoint cases**: 12,820 second-branch cases and 5,529
first-branch cases. This is an independent necessary-condition proof
for those cases, and a cheap prefilter; it does not replace the full
`[1,1]` solver result or prove any `[1,2]` claim. The
[rank report](../results/krakken_pressure_lsb_endpoint_rank.json) records the
complete counts. The [optimized oracle](../scripts/oracle_optimized.py)
includes exact LSB equations in its master, so the prefilter
quantifies a portion of its likely early pruning rather than a new
oracle capability. A stronger batched bound must incorporate carry
feasibility or additional layer structure for the much larger `[1,2]`
endpoint family.

<a id="diff-multi-001"></a>
## Corollary proved: conservative activity floors through eight rounds

<!-- THEOREM METADATA DIFF-MULTI-001 -->
**Permanent ID:** `DIFF-MULTI-001` · **Proof classification:** analytic proof, inheriting the solver-backed premise `DIFF-PERM-002`. C replay and finite arithmetic enumeration are independent implementation audits, not a fresh differential-feasibility proof.
<!-- END THEOREM METADATA DIFF-MULTI-001 -->

Let `A_i` count active serial-Chi byte-S-box inputs in round `i` for
two distinct full-state inputs to the current XRBD-enabled permutation.
For `1 <= R <= 8`, the following conservative lower bounds hold:

| Domain | Bound on `sum_(i=1)^R A_i` | At eight rounds |
|---|---|---:|
| Unrestricted distinct inputs | `floor(3R/2)` | **12** |
| Distinct valid 159-byte first-block messages, domain H | `5 + floor(3(R-1)/2)` | **15** |
| The three fixed differences of `DIFF-RATE-003`, conditioned on `A1=5`, `R>=2` | `8 + floor(3(R-2)/2)` | **17** |

**Round-index lemma.** The original C round applies the same ordered
layers at every index: Theta, MDS, Rho, Pi, Chi, XRBD, Pressure,
round-constant XOR, then InkCloud. Only the constant vector depends
on the index. The transition from a post-Chi difference to the next
pre-Chi difference is therefore XRBD → Pressure → constant XOR →
InkCloud → Theta → MDS → Rho → Pi. The XOR constant cancels between
the two trajectories; the remaining differential wiring is index
independent. Constants can change the actual next-round bases, but
`DIFF-PERM-002` quantifies over arbitrary bases and uses necessary
conditions containing every real Pressure carry transition. Hence a
real adjacent `[1,1]` at any round index would satisfy an instance
already excluded by that theorem. It follows that
`A_i + A_(i+1) >= 3` for every adjacent pair within the eight rounds.

**Nonzero activity lemma.** The prefix and every completed round are
bijections: Theta is involutive, MDS invertible, rotations/shuffles
bijective, XRBD an invertible XOR-shear network, Pressure reversible
by undoing rotations and subtracting in reverse order, and serial
Chi bijective using the inverse byte S-box. Thus distinct states stay
distinct. If all first Chi-call inputs agreed in a round, their first
outputs would agree; if all second-call inputs also agreed, the
paired input bytes would agree too. Zero active calls would therefore
force equal pre-Chi states. Consequently `A_i >= 1` in every round.

**Arithmetic proof.** Pair consecutive rounds and sum the inequality
`A_i+A_(i+1)>=3`; for an odd leftover round use `A_i>=1`. This gives
`3 floor(R/2)+(R mod 2)=floor(3R/2)`. For H use the already proved
`A1>=5` from `DIFF-RATE-001`, then pair the `R-1` remaining rounds.
For the three selected differences under `A1=5`, additionally use
`A2>=3` from `DIFF-RATE-003`, then pair the `R-2` remaining rounds.
The last row does not apply to all hash-reachable five-call pairs.

The [source-pinned checker](../scripts/krakken_multiround_activity.py) confirms
the round loop's ordering, checks 256 original-C constant/suffix
difference identities and 256 original-C indexed-round prefixes, and
computes the necessary-inequality minima by dynamic programming.
Its [report](../results/krakken_multiround_activity_validated.json) records source
hashes and all round counts. A [separate enumerator](../scripts/krakken_multiround_activity_audit.py)
exhausts abstract admissible activity patterns for rounds 1–8 and
matches every bound in its [audit report](../results/krakken_multiround_activity_audit_validated.json).
These finite checks validate the derivation's implementation; the
lemmas and pairing argument are the proof. No SCIP job was rerun.

This corollary inherits the source/model/log premises and the audit
limits of its parent theorems, including the absence of recorded
independent solver replay for `DIFF-PERM-002`. The floors are not
claimed attainable by real Krakken trails. They are total-activity
bounds, not per-round minima, differential probabilities, hull bounds,
or security bits. The unrestricted row applies within any permutation
call starting from distinct states; the H-specific row does not
automatically extend to other message lengths or later absorbs.

<a id="diff-12-001"></a>
### Defined `[1,2]` subclass excluded without a carry solver

<!-- THEOREM METADATA DIFF-12-001 -->
**Permanent ID:** `DIFF-12-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-12-001 -->

The same rank method covers a two-active Chi2 subclass. Suppose Chi2
has exactly two active **second** S-box calls in two distinct 16-bit
serial cells, and every other Chi2 call is inactive. Each selected
cell has a single nonzero pre-Chi byte variable `v`, replicated in
the pair's two lane bytes by the exact first-S-box-inactive condition.
There are `C(128,2)=8,128` choices of cell pair for each of 256
one-byte post-Chi1 start positions, or **2,080,768 site cases**.
For **1,034,445** of these cases, Pressure's exact 32 LSB differential
equations force at least one selected `v` byte to zero. This
contradicts its required activity, so **no real `[1,2]` trail of
those specified site/branch patterns exists for any base or nonzero
start-byte value**. Every exclusion is a GF(2) rank calculation,
without a timed carry solver. The [rank program](../scripts/krakken_pressure_lsb_endpoint.py)
and [report](../results/krakken_pressure_lsb_endpoint_rank.json) enumerate the
class; the program also checks the LSB equations against C-derived
Pressure transitions. An [independent Z3 audit](../scripts/krakken_pressure_lsb_rank_audit.py)
replays 25 excluded site cases at five dispersed start positions with
explicit nonzero-byte constraints.

The LSB-only screen leaves 1,046,323 site cases; these are **not**
claimed feasible, and the joint-two-bit theorem below excludes many
of them.
Other `[1,2]` patterns—first-branch calls, or both calls within one
serial cell—are outside this subclass. A full `[1,2]` impossibility
theorem remains open.

<a id="diff-12-002"></a>
### Exact two-bit carry exclusion for one complete start-position slice

<!-- THEOREM METADATA DIFF-12-002 -->
**Permanent ID:** `DIFF-12-002` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-12-002 -->

Fix the sole nonzero **post-Chi1** difference byte at lane 0, byte 0.
Allow every nonzero value in that byte. At Chi2, require exactly two
active **second** S-box calls in distinct serial cells and every other
call inactive. Enumerate all `C(128,2)=8,128` choices of those cells.
This is an unrestricted-permutation, `[1,2]` endpoint-support class.

For each of the 16 Pressure chains, its low two output bits obey the
exact joint relations

`A = a + (c XOR h) (mod 4),  C = c + A (mod 4)`,

where `h` is bits 17–18 of the original `c` word. Under a pairwise XOR
difference, only **184 of 1,024** possible five-tuples
`(delta-a, delta-c, delta-h, delta-A, delta-C)` occur. The low-bit
`A<<31` shear does not enter these equations. This is an exact
existential condition on the chain's two-bit base slices; allowing
different unconstrained bases for the 16 chains is a sound relaxation.

After exact XRBD and inverse `shuffle → Theta → MDS → Rho → Pi` maps,
the one Chi1 byte and the two Chi2 cell bytes give 24 symbolic bits.
Solving Pressure's 32 exact bit-zero equations and enumerating each
kernel through dimension 18 gives the following **complete accounting
of this fixed start-position slice**:

| Endpoint cell pairs | Count | Meaning |
|---|---:|---|
| LSB excluded | 3,872 | A required byte is forced zero |
| Additionally excluded by exact joint two-bit carries | 2,351 | Every nonzero LSB-kernel assignment violates a chain relation |
| Low-two-bit survivors | 1,139 | Necessary conditions pass; no real trail established |
| Kernel dimension above 18 | 766 | Enumeration deliberately deferred |

Thus **6,223 named site pairs cannot realize a real `[1,2]` trail**
at this fixed Chi1 byte location, for any nonzero byte differences or
base state. The [source-pinned enumerator](../scripts/krakken_12_joint2_screen.py)
and [complete report](../results/krakken_12_joint2_start0.json) use exact low-two-bit
carry feasibility. The [independent audit](../scripts/krakken_12_joint2_start0_audit.py)
derives the linear columns and inverse prefix from original C, uses
opposite-pivot GF(2) elimination, checks all 1,024 target basis
columns through the C tail, and reproduces all four counts in its
[audit report](../results/krakken_12_joint2_start0_audit.json). Both programs
check the low-two-bit rule against 200 original-C Pressure
transitions. This fixed-start certificate alone does **not** exclude
the 1,139 survivors, the 766 capped cases, the other 255 Chi1 byte
locations, or other Chi2 two-call patterns. The all-position theorem
below extends the screen to every start location.

<a id="diff-12-003"></a>
### Theorem proved: exact two-bit Pressure gate excludes 1,628,104 `[1,2]` site cases

<!-- THEOREM METADATA DIFF-12-003 -->
**Permanent ID:** `DIFF-12-003` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-12-003 -->

In the unrestricted permutation, place the sole nonzero post-Chi1
difference byte at **any** of the 256 state-byte locations. At Chi2,
require exactly two active **second** S-box calls in two distinct
serial-Chi cells, with every other call inactive. There are exactly
`256 × C(128,2) = 2,080,768` start-location/endpoint-cell-pair
site cases in this defined class. A site case ranges over **all
nonzero values** of the three symbolic difference bytes and every
base state; excluding one means none can realize a real trail.

For each site case, solve Pressure's 32 exact bit-zero differential
equations. If a required byte is forced to zero, the case is
impossible. Otherwise, for bit-zero kernel dimension at most 18,
enumerate all assignments with all three bytes nonzero and test the
exact *joint* low-two-bit relation of both Pressure additions in all
16 chains. The relation permits 184 of 1,024 local difference tuples.
Its use as a necessary condition is sound even when the full chain
bases are correlated. An empty result excludes the real trail; a
surviving assignment establishes no trail.

| Outcome over all 256 start locations | Site cases | Status |
|---|---:|---|
| Excluded by bit-zero equations | 1,034,445 | Proved impossible |
| Additionally excluded by joint low-two-bit equations | 593,659 | Proved impossible |
| Low-two-bit survivor | 298,360 | Unresolved |
| Kernel dimension above 18 | 154,304 | Unresolved by this screen |

Therefore **1,628,104 of 2,080,768 site cases (78.2453%) are
impossible for every base and every nonzero start-byte value**.
The other **452,664** cases are not claimed feasible. The theorem
does not cover Chi2 first-branch calls, two active calls within one
cell, or other `[1,2]` endpoint shapes; full `[1,2]` impossibility
remains open.

The 452,664 cases left by this *two-bit screen* are resolved for this
BB class by the stronger theorem immediately below.

The [sequential producer](../scripts/krakken_12_joint2_all_positions.py) and
[source-pinned 256-position summary](../results/krakken_12_joint2_all_positions/summary_k18.json)
record all cases. The [independent auditor](../scripts/krakken_12_joint2_all_positions_audit.py)
derives XRBD and the inverse tail from original C, replays all 1,024
endpoint basis columns through the C tail, uses opposite-pivot GF(2)
elimination and an independently enumerated two-addition relation,
then recounts every site case. Its [256-position certificate](../results/krakken_12_joint2_all_positions/audit_summary_k18.json)
matches each producer count exactly. A separate integrity check read
all 256 producer and 256 audit files, verified their current source
hashes, all 8,128 cases per position, and the aggregate totals.

<a id="diff-12-004"></a>
### Theorem proved: no unrestricted `[1,2]` trail with two distinct Chi2 second-branch calls

<!-- THEOREM METADATA DIFF-12-004 -->
**Permanent ID:** `DIFF-12-004` · **Proof classification:** analytic proof + finite exhaustive proof + solver-backed exhaustive exclusion. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-12-004 -->

For the current XRBD-enabled C permutation, let the sole active
first-round Chi call produce a nonzero byte at any of the 256
post-Chi1 locations. There is **no** two-round differential trail
whose Chi2 activity consists of exactly two second-branch calls in
distinct serial-Chi cells and no other active calls. This covers all
`256 × C(128,2) = 2,080,768` named start-location/site-pair cases,
every nonzero start byte, both nonzero Chi2 input bytes, and every
unrestricted base state.

The proof uses a chain of sound necessary-condition exclusions. The
independently recounted bit-zero/joint-two-bit screen excludes
`1,628,104` cases. The completed [three-bit producer
summary](../results/krakken_12_joint3_all_positions_summary.json) excludes
another `451,718`, leaving `946` relaxed SAT cases and no unknowns.
For each of those 946, the [resumable refinement
script](../scripts/krakken_12_refine_sat.py) jointly models both Pressure
additions at successively more low bits. It proves 914 cases UNSAT at
four bits and the remaining 32 at five bits. Thus
`1,628,104 + 451,718 + 914 + 32 = 2,080,768`.

These low-bit equations are necessary for the original 64-bit
Pressure map: for `k<=5`, the low bits depend on the disjoint slices
`a[0:k]`, `c[0:k]`, and `c[17:17+k]`; the `A<<31` shear has no effect
there. Each per-site Z3 problem lets the three required difference
bytes and all 16 Pressure-chain base slices vary freely, so UNSAT of
this relaxation excludes every real base. The two selected Chi2
second-call input bytes are required nonzero; Chi2 S-box DDT
compatibility is omitted, which can only admit more candidates.

The refinement's [946-case report](../results/krakken_12_sat_refinement.json)
is source-hashed and gives the first excluding width for every
survivor. An [independent original-C audit](../scripts/krakken_12_refine_sat_audit.py)
rebuilds the columns using a separate Pressure-profile and Z3
encoding, checks 100 full-width original-C Pressure pairs, and
reproves all 946 UNSAT outcomes in its [audit report](../results/krakken_12_sat_refinement_audit.json).
The 451,718 three-bit exclusions have a source-pinned resumable
producer and complete per-site records; they have not yet received a
second full independent recount. This is a computational theorem
under the stated C source and solver model, with that verification
boundary recorded for external review.

This theorem closes **only the distinct-second-branch (`BB`) Chi2
class**. It does not exclude `AA`, mixed `AB/BA`, or two active calls
sharing a spatial pair; hence full `[1,2]` impossibility remains open.

<a id="diff-12-005"></a>
### Theorem proved: no unrestricted `[1,2]` trail with both Chi2 calls in one spatial pair

<!-- THEOREM METADATA DIFF-12-005 -->
**Permanent ID:** `DIFF-12-005` · **Proof classification:** analytic proof + solver-backed exhaustive exclusion. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-12-005 -->

Place the sole nonzero post-Chi1 difference byte at any of 256
locations. At Chi2, require exactly one first-branch call and the
paired second-branch call in the **same spatial two-byte pair**, with
all other calls inactive. There are `256 × 128 = 32,768` named
start-location/pair cases. None is realizable for any nonzero start
byte or unrestricted base state.

For a spatial pair, write `alpha` for the first-call input difference
and `dy` for the paired input byte difference. The pre-Chi2 difference
is the XOR of `alpha` in the first byte and `dy` in both paired bytes.
The [split-site source-pinned scan](../scripts/krakken_12_remaining_split.py)
allows all nonzero start bytes and `alpha`, and **even allows `dy=0`**;
omitting the nonlinear Chi derivative and second-call nonzero
requirement makes it a safe relaxation. Its 256 per-position reports
in [the results directory](../results/krakken_12_remaining_split_results) cover
all 128 sites per position: 743 fail exact Pressure bit-zero equations
and 32,001 more fail exact joint three-bit equations. The 24 remaining
relaxed SAT cases all fail exact joint four-bit equations in the
[refinement report](../results/krakken_12_same_refinement.json). Therefore
`743 + 32,001 + 24 = 32,768` sites are excluded.

The scan builds XRBD and inverse-tail columns from the current C
source, cross-checks bit-zero signatures between independently built
column representations, and checks random full-width original-C
Pressure transitions against the low-bit equations. All 256 output
files were checked for source hashes, unique site indices, and
complete accounting. A second full independent recount of the
32,001 three-bit solver exclusions has not yet been done; this is the
stated validation boundary for external review.

Together with the BB theorem, this closes two defined Chi2 shapes.
`AA` and mixed `AB/BA` arrangements across distinct spatial pairs
remain open, so a global `[1,2]` exclusion is not claimed.

<a id="rot-001"></a>
## Theorem proved: no exact lane-rotation covariance through eight rounds

<!-- THEOREM METADATA ROT-001 -->
**Permanent ID:** `ROT-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA ROT-001 -->

Let `R_k` rotate **every** 64-bit state lane left by `k` bits, where
`k=1,...,63`. Let `P_r` be the unrestricted 2048-bit permutation
after `r=1,...,8` source rounds. No fixed 2048-bit correction `c`
can satisfy

`P_r(R_k x) = R_k P_r(x) XOR c`

for **all** states `x`, for any of the `63×8=504` `(k,r)` choices.
The same result holds for `Q_r`, the composition of the same round
layers with `beta_iota` omitted, so round constants alone do not
explain the exclusions.

**Finite witness proof.** At `x=0`, any such `c` is forced to equal
`P_r(0) XOR R_k P_r(0)` (or the analogous `Q_r` value). The single
additional input with bit 11 set in lane 0 violates the resulting
equality in **every one** of the 1,008 mode/round/rotation cases.
The [source-pinned verifier](../scripts/krakken_rotational_affine_audit.py)
evaluates the original C layers and records each mismatch Hamming
weight and both witness states in its
[certificate](../results/krakken_rotational_affine_audit.json).
This closes the precise *perfect rotational affine symmetry* class
for the unrestricted permutation. It does not bound statistical
rotational correlations, related-input distinguishers, or cycles.

<a id="rot-002"></a>
### Exact one-round byte-rotation residual decomposition

<!-- THEOREM METADATA ROT-002 -->
**Permanent ID:** `ROT-002` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA ROT-002 -->

For `k∈{8,16,24,32,40,48,56}`, write the first round as
`P_1 = Ink ∘ Xor(RC_0) ∘ Pressure ∘ B`, where `B` is the exact
Theta→MDS→Rho→Pi→Chi→XRBD prefix. Every layer of `B`, and Ink,
commutes with `R_k`; `B` is bijective. Therefore, for every state
`x`, with `z=B(x)`, the following identity holds **exactly**:

`P_1(R_k x) XOR R_k P_1(x)
 = Ink(Pressure(R_k z) XOR R_k Pressure(z)
       XOR RC_0 XOR R_k RC_0)`.

Under a uniform unrestricted state input, `z` is uniform. Thus the
entire one-round rotational-residual distribution is precisely the
Pressure-only residual distribution, with bits relabeled by Ink and
some signs flipped by the fixed constant. This attributes any
one-round byte-rotation bit bias to Pressure's ARX behavior; the
preceding layers do not erase it on a uniform full-state domain.
The source-level commutation proof follows directly from the bytewise
MDS/S-box wiring, lane permutations, and commuting bit rotations.
The [C verifier](../scripts/krakken_rotational_decomposition.py) and
[report](../results/krakken_rotational_decomposition_validated.json) check the
identity for all seven rotations on 100 random states each. The
identity does not apply unchanged to the restricted hash-message
input distribution, and it makes no claim that a two-round residual
has a useful bias.

<a id="dl-001"></a>
## Theorem proved: complete one-round differential-linear mask class

<!-- THEOREM METADATA DL-001 -->
**Permanent ID:** `DL-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DL-001 -->

Define the differential-linear autocorrelation of an output mask
`beta` at input difference `Delta` by
`AC_r(Delta,beta)=2^-2048 sum_x (-1)^(beta·(P_r(x) XOR P_r(x XOR Delta)))`,
where `x` ranges over **all unrestricted 2048-bit states**. Select
one of the 128 two-byte serial-Chi cells and any nonzero byte
`delta`. Invert the linear Theta→MDS→Rho→Pi prefix on the pre-Chi
difference `(delta,delta)` at that cell to define `Delta`. Its first
Chi call is inactive, its second is active, and all other Chi calls
are inactive: `A1=1`.

Let `W` be the 32-dimensional output-mask space generated by the two
exact Pressure LSB output masks in each of its 16 independent word
pairs, transported through the round's final InkCloud shuffle.
Within **every** `(cell,delta)` case, the masks in `W` with
`AC_1(Delta,beta)=+1` form a linear subspace of exact dimension:

| Serial-Chi cells | Perfect-mask subspace dimension |
|---:|---:|
| 8 | 29 |
| 56 | 28 |
| 48 | 27 |
| 16 | 26 |

These are **exact classifications within `W`**, not lower-bound
search results. In 125 of the 128 cells, this perfect subspace
contains a single-bit one-round output mask; the other three cells
have a two-bit attaining mask.

**Proof.** The diagonal pre-Chi difference leaves the first serial
S-box input unchanged. The only post-Chi difference is one byte of
the form `D_delta S(t)=S(t) XOR S(t XOR delta)` in the second output.
As the unrestricted base varies, `t` spans all 256 values. Exhaustive
source-S-box calculation proves that the **affine span** of
`{D_delta S(t):t∈GF(2)^8}` has rank 8 for every one of the 255
nonzero `delta`. For a mask in `W`, Pressure's carry-free LSB
identities pull its output parity back to an input parity; XRBD pulls
that mask back to the one variable post-Chi byte. Let `T_cell` map
the 32 basis-mask coefficients to the resulting eight-bit mask.
The derivative parity is constant exactly when `T_cell lambda=0`:
if the eight-bit mask is nonzero, the rank-8 affine-span fact makes
its parity nonconstant. Exhaustive GF(2) elimination gives
`rank(T_cell)=3,4,5,6` in `8,56,48,16` cells respectively, so
`dim ker(T_cell)=32-rank(T_cell)` as tabulated. Every kernel mask
has derivative parity zero, hence autocorrelation `+1`.

The [source-pinned counter](../scripts/krakken_differential_linear.py) records
all 128 cell ranks and attaining low-weight masks in its
[certificate](../results/krakken_differential_linear_validated.json). It checks
all 255 S-box derivative spans, 3,200 Pressure affine-relation
instances against C, and a representative complete one-round
relation on 1,000 original-C bases. The theorem is about the
unrestricted permutation. Its chosen input differences have `A1=1`,
which the earlier first-block rate-only exclusion rules out for valid
padded hash inputs. The theorem does not imply a two-round
differential-linear distinguisher. A separate
[20,000-base screen](../results/krakken_differential_linear_round2_20k.json)
found no familywise-significant round-two continuation among 128
minimum-weight masks at `delta=1`; that empirical result is recorded
in the research notebook, not used in this proof.

<a id="dl-002"></a>
### Theorem proved: no perfect two-round output mask for 128 fixed differences

<!-- THEOREM METADATA DL-002 -->
**Permanent ID:** `DL-002` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DL-002 -->

For each of the 128 input differences `Delta` above with **`delta=1`**,
the affine span of the complete 2048-bit two-round derivative set

`{P_2(x) XOR P_2(x XOR Delta) : x∈GF(2)^2048}`

is the entire `GF(2)^2048`. Therefore **for every nonzero 2048-bit
output mask `beta`**, the derivative parity
`beta·(P_2(x) XOR P_2(x XOR Delta))` is nonconstant as `x` varies;
equivalently, `|AC_2(Delta,beta)| < 1`. This covers **all** output
masks, not just the 32-dimensional Pressure-affine space used in the
one-round theorem. It does not give a useful numerical upper bound
below one or cover other input differences.

**Finite rank proof.** For each `Delta`, the
[source-pinned certificate](../results/krakken_differential_linear_fullstate_rank_all128.json)
specifies a reference two-round derivative and 2,048 additional
derivatives by the exact base-state generator seeds and accepted
indices, with a digest of the full derivative sequence.
Their differences have GF(2) rank 2,048. Every one of the 128 cases
reaches full rank after at most 2,059 base evaluations. No
statistical assumption is involved: these are concrete C input
pairs and a finite rank calculation. The
[independent audit](../scripts/krakken_differential_linear_fullstate_audit.py)
replayed **262,464 original-C pairs**, checked the stored derivative
digests, and reproduced every rank using least-significant pivots
instead of the producer's most-significant pivots. Its
[report](../results/krakken_differential_linear_fullstate_audit_validated.json)
records source hashes and completion. This is a complete-class
two-round **perfect-correlation exclusion** for the stated 128
unrestricted input differences. The earlier hash-interface theorem
still excludes those `A1=1` differences from the first padded absorb.

<a id="press-walsh-001"></a>
## Theorem proved: complete first-output Pressure mask class

<!-- THEOREM METADATA PRESS-WALSH-001 -->
**Permanent ID:** `PRESS-WALSH-001` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA PRESS-WALSH-001 -->

For one 128-bit Pressure chain write

`A = a + f(c) mod 2^64`, `C = c + (A XOR (A << 31)) mod 2^64`,
where `f(c)=c XOR (c >> 17)`. For arbitrary input masks `(u,v)` and
an arbitrary first-output-word mask `p`, with the second-output-word
mask fixed to zero, the **exact** uniform-chain-input coefficient is

`Corr_P((u,v),(p,0)) = Corr_ADD((u,(f^-1)^T v),p)`.

The linear map `f` is invertible:
`f^-1(t)=t XOR (t>>17) XOR (t>>34) XOR (t>>51)`.
`krakken_pressure_first_branch_walsh.py` evaluates the right side
exactly for **any 64-bit masks** with a two-carry-state signed dynamic
program; there is no search or sampling in this count.

**Theorem.** Every nonperfect coefficient in this entire output-mask
class has absolute value at most `1/2`, and the bound is attained.
The only nontrivial perfect relation is
`A[0] XOR a[0] XOR c[0] XOR c[17] = 0`.

For the addition proof, process bits from low to high. If an input-mask
bit differs from the corresponding output-mask bit, that bit's signed
carry transition has normalized absolute row sum exactly `1/2` for
both carry states, so it contracts the `l1` norm by at least `1/2`.
If all input and output masks match, the sign depends only on carry
bits. Write `T=w0+w1` and `D=w0-w1` for the signed carry-state masses.
A bit with output mask zero maps `(T,D)` to `(T,D/2)`; a bit with
output mask one maps it to `(D,T/2)`. Starting at `(1,1)`, bit zero
leaves `T=1` and gives `|D|=1/2`, regardless of its output-mask bit.
The first selected carry above bit zero makes both coordinates at
most `1/2` in magnitude; later updates cannot increase that bound.
Selecting bit 1 on both addition inputs and the output attains `1/2`.
The script checked **all** `8+64+512+4096=4680` small-word mask triples
for word widths 1–4 against brute force, checked 100 full-width
Python/C first-branch evaluations on both rotated and unrotated chains,
checked all eight one-bit signed carry transition norms, and saved
`pressure_first_branch_walsh_full_layer.json`.

The 16 Pressure chains use disjoint inputs. Under a uniform full
2048-bit Pressure input, this coefficient factors across chains.
Consequently, for output masks confined to the 16 first-output words,
the coefficient is at most `2^-t` if `t` chains have a first-output mask
containing any bit above the LSB; the maximum over that complete class
is sharp by using bit 1 in each such chain. Odd chains' output rotations
only relabel mask bit positions. The script provides an exact
16-chain counter and verifies a two-active-chain `1/4` witness.
This theorem is about **uniform
unrestricted Pressure input**, not the distribution after Chi/XRBD
from a valid hash message. Masks involving Pressure's second output
word remains open for an arbitrary-mask theorem across both outputs.

<a id="press-walsh-002"></a>
### Theorem extension: second shear and second-output LSB

<!-- THEOREM METADATA PRESS-WALSH-002 -->
**Permanent ID:** `PRESS-WALSH-002` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA PRESS-WALSH-002 -->

`krakken_pressure_second_shear_walsh.py` closes two further **complete**
chain-mask classes. With the input mask on `a` fixed to zero, change
variables from `(a,c)` to `(A,c)`. This is a bijection, so `A` and `c`
are independent uniform words. Since `g(A)=A XOR (A<<31)` is invertible,
the substitution `t=g(A)` gives

`Corr_P((0,v),(p,q)) = Corr_ADD((v,(g^-1)^T p),q)`

for **all** 64-bit masks `v,p,q`. Here
`g^-1(t)=t XOR (t<<31) XOR (t<<62)` modulo `2^64`, and
`(g^-1)^T p = p XOR (p>>31) XOR (p>>62)`. The same signed carry
counter therefore evaluates every coefficient in this second class
exactly. Its only nontrivial perfect relation is
`C[0] XOR c[0] XOR A[0]=0`; every nonperfect coefficient has
absolute value at most `1/2`, attained with `v=p=q=bit1`.

There is an additional carry-free bridge: `C[0]=c[0] XOR A[0]`.
For **arbitrary** input masks `(u,v)`, first-output mask `p`, and
second-output mask `q` equal to zero or bit zero,

`Corr_P((u,v),(p,q)) = Corr_P((u,v XOR q),(p XOR q,0))`.

The other exact LSB identity, `A[0]=a[0] XOR c[0] XOR c[17]`, also
lets us toggle `u[0]` without changing the signed coefficient.
Toggling both identities gives a canonical representative with
`u[0]=q[0]=0` for **every** chain mask. In particular, the exact
counter covers the larger union `u∈{0,bit0}` with arbitrary `v,p,q`,
or `q∈{0,bit0}` with arbitrary `u,v,p`. The only perfect
coefficients in this union are the four
combinations of the two known affine LSB identities; **all other
coefficients have magnitude at most `1/2`**.

For the full 16-chain Pressure layer under a uniform 2048-bit input,
`pressure_layer_two_shear_numerator` multiplies the exact chain counts
whenever **each** chain lies in this union. If `t` chains have
nonperfect coefficients, the full coefficient is at most `2^-t`;
the bound is sharp, including mixed first-shear/second-shear choices.
The updated report `pressure_two_shear_affine_extended_validated.json`
records **18,720**
all-mask reduced-word brute-force identity checks (widths 1–4, two
shift pairs), **4,096** exhaustive reduced affine-canonicalization mask
checks, 200 full-width C/inverse checks, and a mixed two-chain
`1/4` witness. These checks validate the implementation; the two
bijective substitutions and the carry lemma prove the 64-bit claims.

The remaining arbitrary chain-mask case, after LSB canonicalization,
has `u≠0` **and** `q≠0`. Both
additions then contribute nonlinear carry constraints. The two-shear
theorem alone does not assign a bound below one to every coefficient
in that case; the low-17 theorem below closes a further complete
subclass. The full-width arbitrary-mask task remains open.

<a id="press-walsh-003"></a>
### Theorem proved: exact joint-carry counter for all low-17 output masks

<!-- THEOREM METADATA PRESS-WALSH-003 -->
**Permanent ID:** `PRESS-WALSH-003` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA PRESS-WALSH-003 -->

For `1≤k≤17`, restrict **both** unrotated output-word masks `p,q` to
their low `k` bits. In the full 64-bit chain, those outputs depend only
on three disjoint `k`-bit input words: `a[0:k]`, `c[0:k]`, and
`c[17:17+k]`. They are independent and uniform for a uniform
unrestricted chain input. The exact low-bit equations are

`A_low = a_low + (c_low XOR c_high) mod 2^k`,
`C_low = c_low + A_low mod 2^k`.

The `A<<31` term cannot affect these bits. At each bit position, an
exact signed dynamic program sums the eight possible fresh input-bit
triples while retaining the **two carry bits jointly**. Its four-state
numerator divided by `2^(3k)` is therefore the exact complete-chain
Walsh coefficient for **every** supported input mask. Any input-mask
bit outside those three `k`-bit words gives exact zero by independent
uniformity. This is a closed, arbitrary-mask theorem for the entire
defined low-output class, including masks coupled across both
additions; it is not an arbitrary 64-bit-output theorem.

The [counter](../scripts/krakken_pressure_joint_lowbit_walsh.py) and
[report](../results/pressure_joint_lowbit_walsh_validated.json) compare all
**33,824** reduced-width mask quintuples at `k=1,2,3` against complete
Walsh transforms, reproduce the earlier exact `C[5]` correlation
`-85/256`, and check the low-17 equations on 1,000 original-C
full-width inputs. For example, the genuinely coupled `k=17` masks
`(u,v_low,v_high;p,q)=(2^16,0,2^16;0,2^16)` have exact correlation
`-357913941/1073741824`, approximately `-1/3`. This example is a
component correlation under a uniform Pressure input, not a hash
message-to-state correlation.

**Sharp maximum for the entire low-17 class.** The argument actually
proves a standalone theorem for the three-independent-word map
`Phi_k(a,c,h)=(A,C)`, where `A=a+(c XOR h)` and `C=c+A` modulo
`2^k`, for **every integer `k≥1`** under uniform independent
`a,c,h`. Krakken's real Pressure chain realizes this map exactly
on its low `k≤17` bits, with `h=c[17:17+k]`.

Let `M_b` be the
integer `4×4` signed transition matrix for one bit-mask pattern
`b=(u_i,v_i,h_i,p_i,q_i)`, with rows and columns indexed by the two
carry bits. Each row sums the signs of exactly eight fresh input-bit
triples, so its absolute row sum is at most `8`. Let `j` be the
highest bit selected by either output mask. Summing the three fresh
input bits at `j` leaves either zero or one of exactly **three**
top-bit carry-character vectors:

`(8,8,-8,-8)`, `(8,-8,-8,8)`, `(8,-8,8,-8)`.

The two-bit base has a short algebraic proof. For fixed incoming
carries `r,s` and fresh bits `a,c,h`, the outgoing carries are
`r'=majority(a,c XOR h,r)` and `s'=majority(c,A,s)`, with
`A=a XOR c XOR h XOR r` at that bit. Their quadratic parts over
GF(2) are respectively `ac XOR ah` and `ac XOR ch`; the quadratic
part of `r' XOR s'` is `ah XOR ch`. Each is the product of two
independent linear forms: `a(c XOR h)`, `c(a XOR h)`, or
`h(a XOR c)`. The lower input/output masks contribute only affine
terms in `a,c,h`. Every nonzero outgoing-carry character plus any
affine term therefore has normalized Walsh magnitude at most `1/2`:
after an invertible linear variable change it is `xy` plus affine
terms, and the two-variable `xy` sign sum has magnitude two out of
four. Thus **every** two-bit suffix component has magnitude at most
`32=8²/2`.

The [finite-base proof script](../scripts/krakken_pressure_lowbit_half_theorem.py)
also checks all `3×32=96` ways to prepend one arbitrary lower mask-bit
pattern, for all four incoming carry states. It verifies the three
quadratic parts for each incoming-carry pair, and independently
enumerates all 64 two-bit input triples for each base case. Thirty-two
base patterns give the zero vector and 64 attain component magnitude
32. Every still-lower bit applies a transition with absolute row
sum at most 8. Induction therefore keeps all four suffix components
at most `8^(j+1)/2` in magnitude. Dividing by the `8^(j+1)` input
triples gives **`|Corr|≤1/2` whenever `j≥1`**, for every mask and
every abstract word length; it applies to Krakken for `k≤17`.
If `j=0`, the relevant one-bit truncation is affine and its three nonzero
coefficients are precisely the known perfect LSB relations; all
other coefficients vanish. The bound is sharp for every `k≥2`:
`(u,v_low,v_high;p,q)=(3,0,2;0,2)` gives `+1/2`, including at
`k=17` where the numerator is `2^50` over `2^51`. The
[proof report](../results/pressure_lowbit_half_theorem_algebraic_validated.json) records
the finite base and witness. This is an analytic induction after a
small exact base table, not an extrapolation from six-bit enumeration.

The earlier single-addition proof's per-bit `1/2` row contraction
does **not** transfer verbatim: one joint-carry row has normalized
absolute sum `3/4`. The successful argument first groups the top
**two** masked bit positions, where the signed cancellations give
the `1/2` bound, then uses only the universal row-sum bound `1` for
all lower positions.

**Independent exhaustive validation through six bits.** The
[all-mask certificate](../scripts/krakken_pressure_lowbit_max_certificate.py)
computes an integer Walsh transform for **every** pair of low-`k`
output masks and thereby checks all `2^(5k)` input/output mask
quintuples, for each `k=1,...,6`. Its
[source-pinned report](../results/pressure_lowbit_max_k6_certificate.json) records
**1,108,378,656** exact coefficients in total, including all
**1,073,741,824** at `k=6`. At `k=1`, all nonperfect coefficients are
zero. For **each** `k=2,...,6`, the exact maximum nonperfect absolute
correlation is `1/2`; the only perfect coefficients are the four
combinations of the two affine LSB relations. The witness
`(u,v_low,v_high;p,q)=(3,0,2;0,2)` attains `+1/2` at every `k≥2`.
This is an independent exact exhaustive check of the analytic theorem
for the first six widths. The [top-bit support rule](../scripts/krakken_pressure_lowbit_top_support.py)
also proves that a mask not meeting three forced highest-bit input
conditions is exactly zero for every `k≤17`; its
[report](../results/pressure_lowbit_top_support_validated.json) checks the rule
against full Walsh spectra through `k=5` and 1,000 forbidden
`k=17` counter cases. Explicitly, if `j` is the highest bit of
`p OR q`, then `u_j=p_j XOR q_j`, `v_j=p_j`, and
`h_j=p_j XOR q_j`, while all three input-slice masks must vanish
above `j`. Among the `32^k` relevant mask quintuples, this rule leaves
only `1+3(32^k-1)/31` candidates; all others are **exact zeros**.

Under a uniform 2048-bit Pressure-layer input, the 16 chains are
independent. Restrict both unrotated output masks in **each** chain
to low `k≤17` bits (undo the fixed output rotations on odd chains).
If `t` chains use nonperfect coefficients, the complete layer
correlation has absolute value at most `2^-t`, and this bound is
attainable for every `t=1,...,16` by putting the witness above in
exactly `t` chains and trivial masks in the others. This remains a
uniform-input component theorem, not a hash-conditioned hull bound.

<a id="press-hull-001"></a>
### Exact coupled-chain hull identity and a failed bound

<!-- THEOREM METADATA PRESS-HULL-001 -->
**Permanent ID:** `PRESS-HULL-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA PRESS-HULL-001 -->

Let `T(x,y;z)` be the normalized 64-bit modular-addition Walsh
coefficient. Inserting every intermediate mask `(s,t)` between the
two Pressure shears gives the **exact full-width identity**

`Corr_P((u,v),(p,q)) = sum_{s,t} T(u,(f^-1)^T(v XOR t);s)
                             * T(t,(g^-1)^T(s XOR p);q)`.

The sum has `2^128` mask pairs before exploiting zero entries or
cancellations. It explicitly contains the dependency between the two
additions; multiplying two selected addition coefficients would omit
other paths. The two complete classes above are special cases where
the expression reduces to one addition coefficient.

The reduced-width checker `krakken_pressure_coupled_hull.py` compared
this signed convolution with direct exhaustive evaluation for **all
65,536** input/output mask quadruples at width four. For the analogue
with right shift 3 and left shift 3, the coupled mask
`(u,v;p,q)=(8,0;1,8)` has **true correlation zero**, while summing
the absolute values of the convolution terms gives `7/8`.
`pressure_coupled_hull_w4_r3_l3_checked.json` records this exact
counterexample and all-mask audit. Among coupled masks in that model,
96 have an absolute-term bound above `1/2`, although none has true
correlation above `1/2`. This proves that a generic proof of a
`1/2` full-chain bound cannot simply take absolute values of the
individual two-addition hull terms and use their reduced-model
component maxima. It does **not** establish any 64-bit coupled-case
bound, nor does it rule out a specialized bound for Krakken's actual
shift constants. Signed cancellation remains the key unresolved step.

<a id="press-zero-001"></a>
### Exact-zero Pressure mask families

<!-- THEOREM METADATA PRESS-ZERO-001 -->
**Permanent ID:** `PRESS-ZERO-001` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA PRESS-ZERO-001 -->

A further distribution theorem follows from the same invertible maps.
Under a uniform 128-bit chain input, each pair `(a,A)`, `(c,A)`,
`(c,C)`, and `(A,C)` is jointly uniform on 128 bits. For example,
`A` is uniform for fixed `a` because `f(c)` is uniform; `A` is uniform
for fixed `c` because `a` is uniform. Thus `A` and `c` are independent.
Since `g(A)=A XOR (A<<31)` is also invertible, `g(A)` is uniform
independent of `c`, so `C=c+g(A)` is uniform for fixed `c`.

**Corollary.** Every nontrivial linear mask coefficient involving only
one of those four pairs is exactly **zero**. In particular, for a
nonzero first-output-only mask, a nonzero correlation requires
nonzero masks on **both** input words. Because the 16 chains factor
under a uniform full Pressure input, any chain violating this rule
zeros the whole Pressure coefficient. This is an exact hull-pruning
rule within the stated model. Full-state hull composition uses these
uniform-input Pressure Walsh coefficients, so a zero entry removes
that mask path **exactly**, even when the final question concerns the
rate-restricted hash input. It does not by itself bound the sum of
the remaining paths. `krakken_pressure_pairwise_independence.py`
checks all four pair-bijection families at reduced widths 1–6 and
validates the 64-bit formulas against original C; the report is
`pressure_pairwise_independence_validated.json`.

<a id="lin-rate-001"></a>
## Theorem proved: 16 complete first-round hash-mask bounds

<!-- THEOREM METADATA LIN-RATE-001 -->
**Permanent ID:** `LIN-RATE-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-RATE-001 -->

The first quantitative **complete-round, valid-message** linear claim
now follows from Pressure's exact affine relations. For each chain
`c=0,...,7`, `h=0,1`, put `i=4c+h`, `j=i+2`. Define the two-bit
output mask after round 1 on lane `(7i) mod 32`, bit `11+7h`, and
lane `(7j) mod 32`, bit `11+19h`. The rotations and shuffle are those
of the actual C round. For every 1272-bit mask `alpha` on a uniform
valid 159-byte message and each of these 16 state masks `beta`,

`|Corr(alpha·m, beta·F_1(m))| ≤ 2^-174`.

This holds for **all** input masks in the class, not only a selected
message approximation. The pointwise Pressure identity
`A[0] XOR C[0]=c[0]` pulls the two-bit output mask back to one
Pressure-input bit, up to the round-constant phase. XRBD transpose
then gives a fixed post-Chi1 output mask. If `t` serial-Chi components
are active, their selected pre-Chi inputs form an affine image of the
1272-bit message space with linear rank `r`. For each active
component, let `M_i` be the **unnormalized** largest absolute Walsh
coefficient for its specified two-byte output mask. The exact
affine-image indicator expansion and triangle inequality give

`|Corr| ≤ min(1, (product_i M_i)/2^r)`

for **every** message mask: those outside the projection's row span
give zero; the others have `2^(16t-r)` signed Fourier lifts, each
bounded by the product of normalized local maxima. This is a
dependence-safe bound for a complete round at the actual hash
interface. It does not multiply a Pressure probability into a
hash-conditioned Chi probability; Pressure is crossed by an exact
identity. The [48-mask report](../results/hash_round1_pressure_affine_48_validated_v3.json)
gives the exact integer products, ranks, and individual bounds. All
16 two-bit masks above have nonvacuous bounds between `2^-354` and
`2^-174`; the worst is chain `(c,h)=(6,1)`. The
[review claim](KRAKKEN_CLAIMS_FOR_REVIEW.md) lists all 16 values.

The replay compared every class rank with the independent established
rank routine, checked ten selected local Chi maxima by full
`2^16` Walsh transforms, and replayed each mask through the C XRBD,
Pressure, suffix, and valid-message round. These are validation;
the pointwise identities, exact local Walsh calculation, and
affine-image inequality form the proof. A separate
[120-pair audit](../results/hash_round1_pressure_affine_AC_pairs_validated.json)
found nonvacuous bounds for 106 two-chain mask XORs; 14 are vacuous
under this inequality. This marks a proof-method boundary, not a
detected strong correlation. The 16-mask theorem does not imply a
maximum over all state-output masks or later rounds.

<a id="lin-rate-002"></a>
## Theorem proved: a five-dimensional first-round hash-output subspace

<!-- THEOREM METADATA LIN-RATE-002 -->
**Permanent ID:** `LIN-RATE-002` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-RATE-002 -->

Let `beta_(c,h)` denote the complete-round two-bit output mask defined
in the preceding theorem. Set

`V = span{beta_(0,0), beta_(1,0), beta_(2,0), beta_(5,0), beta_(6,0)}`.

The five generators occupy distinct Pressure chains and are linearly
independent. For every nonzero `beta∈V` and every 1272-bit message
mask `alpha`, under the uniform distribution on all valid 159-byte
first-block messages,

`|Corr(alpha·m, beta·F_1(m))| ≤ 2^-162`.

There are exactly 31 nonzero `beta` in this class. XORing the exact
Pressure identities for any generator subset pulls that round-output
mask back to a fixed post-Chi1 mask through the affine round suffix
and XRBD transpose. For each subset, the selected pre-Chi1 input
projection has rank `r` and exact local serial-Chi maxima `M_i`; the
preceding affine-image proof gives the complete-hull bound
`min(1, product_i M_i / 2^r)` for every `alpha`. The
[subspace verifier](../scripts/krakken_hash_round1_affine_subspace.py) checks
all 31 integer inequalities. The [source-pinned certificate](../results/hash_round1_AC_coordinate_subspaces_128_validated_v3.json)
records the exact ranks, local-maxima products, and dyadic ceilings,
using the [single-mask](../results/hash_round1_pressure_affine_48_validated_v3.json)
and [pair-mask](../results/hash_round1_pressure_affine_AC_pairs_validated.json)
certificates for subsets of size one and two. The largest certified
ceiling is `2^-162`, reached by the bound calculation for subsets
`{0,2,12}` and `{0,2,4,12}` in the 16-mask index convention
`index=2c+h`. This describes the **bound's** worst case, not an
attaining correlation.

All 31 selected ranks were recomputed independently, ten local Chi
maxima were checked by direct 16-bit Walsh transforms, and each new
higher-weight mask was replayed three times through original C. These
checks validate the certificate's implementation. The result is a
complete defined output-mask class after **one** full round; it does
not yield a maximum over arbitrary 2048-bit output masks or eight
rounds.

Let `X(m)` be the vector of the five generator parities. For any
codimension-`d` affine message subspace `H={m:Lm=b}`, each nonzero
Fourier coefficient of `X` conditioned on `H` is a signed sum over
the `2^d` message masks in the row span of `L`, hence has magnitude
at most `2^(d-162)`. Fourier Parseval and Cauchy–Schwarz give

`TV(Law(X|H),Uniform({0,1}^5)) ≤ sqrt(31)/2 · 2^(d-162) < 2^(d-160)`.

In particular, **any 128 independent linear restrictions** on valid
messages leave this five-bit first-round projection within `2^-32`
of uniform. This uses the theorem's quantifier over every message
mask; it is not a claim about arbitrary nonlinear message subsets.

<a id="lin-rate-003"></a>
## Theorem proved: a six-dimensional first-round hash-output subspace

<!-- THEOREM METADATA LIN-RATE-003 -->
**Permanent ID:** `LIN-RATE-003` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-RATE-003 -->

With the same exact-affine two-bit masks `beta_(c,h)` as above, let

`W = span{beta_(0,0), beta_(1,0), beta_(2,0), beta_(4,0), beta_(5,0), beta_(6,0)}`.

The generators act on distinct Pressure chains and are independent.
For every nonzero `beta∈W` and every 1272-bit message mask `alpha`,
under uniform valid 159-byte first-block messages,

`|Corr(alpha·m, beta·F_1(m))| ≤ 2^-76`.

The proof is the same pointwise Pressure-identity and rate-aware
affine-image argument as for the five-dimensional class, evaluated
for **all 63** nonzero `W` masks. The [source-pinned certificate](../results/hash_round1_AC_coordinate_subspaces_76_validated_v2.json)
records the integer local-Chi-maxima product, selected rate rank, and
ceiling for every subset, using the [single](../results/hash_round1_pressure_affine_48_validated_v3.json)
and [pair](../results/hash_round1_pressure_affine_AC_pairs_validated.json)
certificates for subsets of size one or two. The two weakest bound
calculations are subsets `{2,8}` and `{0,2,8}` in the convention
`index=2c+h`, both with ceiling `2^-76`. The certificate
independently rechecks all 63 projection ranks, ten selected local
Chi Walsh maxima, and the mask transport through original C. These
are validation; the exact identities and affine-image inequality are
the mathematical proof.

If `Y(m)` lists the six generator parities of `F_1(m)`, every nonzero
Fourier coefficient of its six-bit law is at most `2^-76`. Thus

`TV(Law(Y),Uniform({0,1}^6)) ≤ sqrt(63)/2 · 2^-76 < 2^-74`.

Indeed, Fourier Parseval gives
`sum_y (Pr[Y=y]-1/64)^2 ≤ (63/64)·2^-152`, and Cauchy–Schwarz
turns this into the displayed total-variation bound. It applies to
the complete six-bit projection under uniform valid messages after
one round, not the complete state or later rounds.

The premise is uniform over **every** message mask, so it survives
arbitrary linear restrictions on the message with an explicit loss.
For an affine message subspace `H={m:Lm=b}` of codimension `d`, let
`m` be uniform on `H`. Character orthogonality gives, for every
nonzero six-bit output mask `s`,

`E[(-1)^(s·Y) | m∈H] = sum_{lambda∈GF(2)^d}
  (-1)^(lambda·b) E[(-1)^(s·Y + (L^T lambda)·m)]`.

Each term is one of the proved all-message-mask correlations and has
magnitude at most `2^-76`. The conditional coefficient is therefore
at most `2^(d-76)`. Applying Parseval and Cauchy–Schwarz as above,

`TV(Law(Y|H),Uniform({0,1}^6)) ≤ sqrt(63)/2 · 2^(d-76) < 2^(d-74)`.

In particular, **any 64 independent linear message constraints**
leave this six-bit first-round output projection within `2^-10` of
uniform. The bound may become vacuous for very large codimension;
it is not an assertion about arbitrary nonlinear message subsets.

<a id="alg-deg-001"></a>
## Theorem proved: valid-message coordinate-degree map through eight rounds

<!-- THEOREM METADATA ALG-DEG-001 -->
**Permanent ID:** `ALG-DEG-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA ALG-DEG-001 -->

For the valid 159-byte first-block message space, let `F_r` be the
complete 2048-bit state after `r` rounds, with the fixed pad and zero
initial capacity. The following statements hold for the current C
source and all `r=1,...,8`:

1. Exactly the **specified 32 Pressure-output LSB positions** after
   round one have proved degree **exactly 13**. Their positions are
   `64*((7i) mod 32)+11+7h` and
   `64*((7j) mod 32)+11+19h`, with `i=4c+h`, `j=i+2`,
   `c=0,...,7`, `h=0,1`. This says those 32 positions have exact
   degree 13; it does not claim that no other position has degree 13
   without the lower-bound certificates below.
2. Every other first-round state coordinate has degree **at least 20**.
3. Every coordinate after each complete round `r=2,...,8` has degree
   **at least 20**.
4. The first-32-byte projection has vectorial degree **at least 24**
   after every `r=1,...,8`; `r=8` is the actual one-block digest.

The first three items together do establish that these 32 are the
only first-round state coordinates of degree below 20. The local
[serial-Chi ANF certificate](../results/serial_chi_16bit_degree_validated.json)
exhausts all `2^16` inputs and finds degree 7 in every first-output
byte coordinate and degree 13 in every second-output byte coordinate.
Theta, MDS, Rho, Pi, and XRBD are affine or linear, while the first
Pressure output bits obey exact carry-free identities
`A0=a0 XOR c0 XOR c17` and `C0=a0 XOR c17`. The constant and shuffle
are affine. Thus the 32 selected state bits have degree **at most
13**. The [mask-layout audit](../results/degree_hash_round1_lowbits_mapping_validated.json)
checks the four positions landing in the first 32 state bytes against
1000 original-C Pressure/suffix states.

The lower bounds use the identity

`D_{v_1,...,v_d}f(x)= XOR_{u∈GF(2)^d} f(x+sum_i u_i v_i)`.

A nonzero order-`d` derivative proves that at least one output
coordinate has degree at least `d`; when the derivative's bit at a
specified coordinate is nonzero, it proves that coordinate's degree
at least `d`. All direction vectors in the certificates are linearly
independent and lie wholly within the 1272 message bits.

The [32-coordinate attaining certificate](../results/degree_round1_pressure_lsb_all32_exact13_validated.json)
evaluated eight dense 13-dimensional message cubes; seven attaining
witnesses cover all 32 coordinates, each replayed as a full cube
through original C. The
[20-dimensional baseline](../results/degree_hash_digest_allcoords_d20_validated_v2.json)
and [dense completion](../results/degree_fullstate_allcoords_d20_validated.json)
combine twelve coordinate cubes and seven dense cubes; their union
has a nonzero derivative at each of the other 2016 round-one bits
and every one of the 2048 bits at rounds two through eight. The
[24-dimensional cube](../results/degree_hash_cube24_validated_v3.json) has a
nonzero derivative in the first 32 bytes after each round. Its
`2^24` vertices provide the vectorial lower bound; a zero bit in
that derivative says nothing about that coordinate's degree.

The fast enumerator uses direct `ABYSSAL_SBOX[x]` for each byte in
place of the source's constant-time 256-index scan. In the source,
each byte equality mask is one exactly when its input equals the
scanned index and zero otherwise; the additions constructing each
mask cannot carry between bytes. Consequently both methods compute
the same byte substitution. The helper independently compares 256
Chi states and 16 full eight-round states to original C, and the
certificate scripts compare complete smaller cubes to original C.
The [structural audit](../scripts/krakken_degree_multiround_audit.py) checks
the source hashes and coverage arithmetic; independent full replay
uses the producer scripts and saved messages/directions.

This theorem exposes an attack-side structure as well: **every**
order-14 derivative of each of the 32 exact-degree-13 round-one bits
vanishes, while some order-13 derivatives do not. The round-two
degree lower bound does not imply that every order-14 or order-20
cube derivative is nonzero; it rules out a globally low-degree
coordinate polynomial. Neither lower bound is a collision or
preimage-security claim.

<a id="lin-hull-001"></a>
## Exact formula for the full rate-restricted hull

<!-- THEOREM METADATA LIN-HULL-001 -->
**Permanent ID:** `LIN-HULL-001` · **Proof classification:** analytic proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA LIN-HULL-001 -->

Let `J` embed the 1272 message bits in the 2048-bit state, let `c` be
the fixed padded state, and let `P_r` be `r` complete full-state rounds.
Then `F_r(m)=P_r(Jm+c)`. Define the unrestricted full-state coefficient

`C_{P_r}(gamma,beta) = 2^-2048 sum_x (-1)^(gamma·x XOR beta·P_r(x))`.

Fourier expansion gives the **exact identity**

`Corr_r(alpha,beta) = sum_{gamma: J^T gamma = alpha}
                      (-1)^(gamma·c) C_{P_r}(gamma,beta)`.

There are exactly `2^776` terms: 8 mask bits at the fixed padding byte
and 768 at initial capacity positions. The formula includes every
intermediate-mask path inside each full-state coefficient. It makes
the missing proof obligation concrete: a useful global bound must
control the *signed* sum over this whole coset for all `alpha,beta`.
Replacing it with the largest single coefficient, or summing absolute
values without a strong structural bound, does not establish the target.

## Why the existing local lemmas do not yet yield a useful global bound

For permutations on a uniform `n`-bit state, the matrix of normalized
linear correlations obeys the exact composition law

`C_(Q∘P)(alpha,gamma) = sum_beta C_P(alpha,beta) C_Q(beta,gamma)`.

Each permutation's correlation matrix is orthogonal. Its operator norm
is therefore one, so multiplying operator-norm bounds cannot prove
correlation decay. Nor can one multiply only the largest entries of
component Walsh tables: many intermediate masks can sum coherently.
For example, a nonlinear S-box followed by its inverse is the identity
and has perfect global correlations even when either component has
nontrivial local spectra. A proof for Krakken must control the **entire
signed hull sum** using its specific layer structure.

The first hash block adds another obstacle: its 1272 message bits map
into a 2048-bit pre-Chi state with **776 linear constraints**. For a
mask that activates all 128 Chi components only on their first output
bytes, multiplying the local maxima gives `2^(-3×128)=2^-384`
under independent uniform component inputs. The general affine-image
correction `2^776` makes that elementary bound vacuous. This does not
show a large real correlation; it shows precisely why the current
rate-aware product-bound technique cannot establish a global theorem.

## Comparison with established design claims

The [AES wide-trail analysis](https://www.iacr.org/archive/eurocrypt2002/23320102/Rijndaeleurocrypt.pdf)
proves a 25-active-S-box lower bound for four-round *trails*. The
[Keccak team's trail analysis](https://keccak.team/2017/new_differential_trail_bounds.html)
proves lower bounds on differential *trail weight*. These are rigorous,
publishable claims with precisely stated scope. A Krakken result of
that type need not solve the stronger maximum-*hull* problem first.
The new Chi1 theorem above is an example of a closed claim, but its
one-layer and sparse-mask scope is much narrower than a full-round
trail bound or an eight-round hull bound. The long-term goal remains
a rigorous bound that supports an explicit attack model and number.

Pressure's exact affine relations, enlarged two-shear mask classes,
and a sharp `1/2` bound plus exact joint-carry counter for both
low-17 output words are known, and XRBD mask propagation is exact.
The missing component is a
certified arbitrary-mask Walsh transition bound for the full-width
coupled-carry case after LSB canonicalization,
followed by a method that combines **all** intermediate masks without
an invalid independence assumption or a vacuous absolute-value sum.

## Proof work remaining

1. Extend the sharp low-17 Pressure result to arbitrary 64-bit output
   masks. At bit 17, the `c[i+17]` slice overlaps later low-word
   `c` variables; at bit 31, `A<<31` adds a second long-range
   dependency. Both break the three-fresh-bit recurrence used here.
   Prove a useful all-mask bound by a dependency-aware method. Validate
   it on exhaustively enumerable word widths and C identities.
2. Prove a rate-aware mask-spread or correlation bound across
   Chi→XRBD→Pressure that holds for **every** nonzero output mask,
   including combinations of components with dependent pre-Chi bases.
3. Bound the signed sum over all intermediate masks through successive
   rounds. This is the step that turns trail/component results into a
   genuine full-hull bound. A certificate must state which masks were
   covered and why omitted masks cannot dominate.
4. Report the strongest certified `lambda_r` for each round count. If
   the bound is vacuous at some round, identify the exact failed
   inequality rather than replacing it with a selected-mask screen.

The differential analogue is a separate target:
`max_{Delta m != 0, Delta y} Pr[F_r(m) XOR F_r(m XOR Delta m)=Delta y]`.
The existing activity and fixed-difference probability theorems are
lemmas toward it, but do not yet bound all differences or hulls. A
sponge-style construction bound under an **ideal** 2048-bit permutation
would also be separate; it cannot establish that this concrete
permutation behaves ideally.

<a id="zero-001"></a>
## Proved: a four-state Chi/XRBD zero sum and its two-round exclusion

<!-- THEOREM METADATA ZERO-001 -->
**Permanent ID:** `ZERO-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA ZERO-001 -->

This claim concerns the **unrestricted 2048-bit permutation**, not
the padded first hash block. A zero sum is a set of states whose bitwise
XOR is zero. For the effective two-byte serial-Chi component, let
`S(a,b)=(Sbox(a XOR b), Sbox(b XOR Sbox(a XOR b)))`. The four distinct
component inputs `01d6, 01d7, 0404, 0405` (low byte `a`, high byte
`b`) XOR to zero, and their component outputs `78b3, 0aa0, 0aa5,
78b6` XOR to zero. The [producer](../scripts/krakken_zero_sum_square.py) derives
this square by an exact enumeration of the 16-bit component
derivative at input difference `0001`.

Place this square in any one serial-Chi byte cell, hold all other
pre-Chi bytes at an arbitrary common background, then apply the
inverse of the round's linear prefix to each state. The four resulting
permutation inputs XOR to zero. Their complete post-Chi states XOR
to zero because the other components are identical; their post-XRBD
states XOR to zero because XRBD is linear. The **32 Pressure affine
output coordinates**, after constants and shuffle, also XOR to zero
after one complete round for every background. This is an exact
four-state *projected* zero sum after round one, and an exact
full-state zero sum at the Chi and XRBD checkpoints. It does not
assert a full-state zero sum after complete round one.

The same fixed square was embedded at all **128** serial-Chi byte
cells. For each cell, a finite list of at most **18** background
states makes every one of the 2048 complete-round-two coordinate
bits nonzero in at least one four-state XOR sum. Consequently **no
round-two coordinate bit is a universal zero sum** over the entire
background family at any of those 128 sites. This is a deterministic
counterexample certificate, not a statistical estimate. The
[all-cell report](../results/krakken_zero_sum_allcells_validated.json) stores the
source hashes, seed, cell mapping, and number of C-evaluated contexts
needed at each site; the original C prefix and Chi were checked on
the first context of every site.

At the representative cell `(pair,row,byte)=(0,0,0)`, a stronger
certificate uses **2052** background states. The 2048-bit
round-two four-state XOR sums have **linear rank 2048**. Therefore,
for every nonzero output mask `beta`, at least one background has
`beta·(XOR of its four P_2 outputs)=1`: **no nonzero linear output
mask is universally balanced** over this fixed-square family after
round two. The [source-pinned certificate](../results/krakken_zero_sum_square_validated.json)
contains the deterministic generator, one complete input/output
witness, progression and a digest of the ordered sums. An
[independent original-C replay](../results/krakken_zero_sum_square_audit_validated.json)
checks 16,416 round evaluations and recomputes rank with opposite
pivot order. The first 16 backgrounds already exclude all individual
coordinate bits at this representative site; full rank requires 2052.

The theorem is deliberately about a **defined four-state family**.
It does not exclude other zero-sum sets, larger cubes, valid-message
constructions, or nonperfect statistical biases. In four exact
valid-159-byte-message cubes of dimension 8 or 16, neither the
complete one-round nor two-round state XOR was zero; the
[hash-cube report](../results/krakken_zero_sum_hash_cube_validated.json)
records those finite checks and original-C validation of the 8-bit
cubes. Those four observations are examples, not a general
hash-interface exclusion.

<a id="int-cube-001"></a>
## Proved: hash-reachable 14-cube zero sums and exact round-two coordinate exclusion

<!-- THEOREM METADATA INT-CUBE-001 -->
**Permanent ID:** `INT-CUBE-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA INT-CUBE-001 -->

This theorem uses **valid padded 159-byte first-block messages**.
Let `Q(m;v_1,...,v_d)` be the `2^d` messages in an affine cube with
linearly independent directions `v_i` in the 1272 message bits.
The initial state and the complete prefix through Theta, MDS, Rho,
and Pi are affine functions of the message. Each independent
two-byte serial-Chi component has algebraic coordinate degree at
most **13**, proved by the
[exhaustive 16-bit ANF certificate](../results/serial_chi_16bit_degree_validated.json).
Consequently **every** `d>=14` valid-message affine cube has XOR sum
zero in **all 2048 post-Chi1 state bits**. XRBD is linear, so the
full-state XOR sum is also zero after XRBD1. This applies to every
base message and every set of independent message directions, not
just the cube tested below. The 32 exact-affine Pressure output
coordinates also remain balanced after one **complete** round for
every such cube; constants cancel and the final shuffle only moves
those positions.

The universal **14-dimensional threshold is sharp** for the
post-Chi1 and post-XRBD1 *full-state* zero sum. The serial-Chi
component's second byte has a nonzero degree-13 ANF monomial. The
first-block message-to-one-component pre-Chi map has full rank
`16/16`, so 13 independent valid-message directions can be selected
whose component images are exactly the 13 bit directions in that
monomial. Their order-13 derivative of the chosen Chi output bit is
one for every base, hence the full post-Chi sum is nonzero; invertible
XRBD keeps it nonzero. The [construction](../scripts/krakken_hash_chi_cube_threshold.py)
gives all 13 message masks. The
[original-C witness](../results/krakken_hash_chi_cube_threshold_validated.json)
has 6 nonzero post-Chi bits and 288 nonzero post-XRBD bits after
`2^13=8192` inputs. An
[independent C replay](../results/krakken_hash_chi_cube_threshold_audit_validated.json)
verified the 13 component-direction images and both complete sums.
Thus dimension 14 is the **smallest dimension at which every valid
affine message cube is guaranteed to have a full-state zero sum at
these two checkpoints**. This sharpness statement is about the
checkpoint property, not complete-round integral resistance.

For a sharper complete-round statement, fix the **14 direction
vectors at message bit positions `0,...,13`**, and allow the base
message to vary over all 159-byte messages. For this fixed cube:

* After one complete round, **exactly 32** state coordinates are
  balanced for **every** base. The algebra above proves those 32
  balances. Eleven concrete base messages make each of the other
  2016 coordinates nonzero in at least one full-cube XOR sum.
* After two complete rounds, **no state coordinate** is balanced for
  every base. The same eleven bases give a nonzero full-cube XOR sum
  at least once for each of the 2048 coordinates. Ten bases already
  suffice for the round-two exclusion.

These are universal statements about a **fixed-direction cube with
arbitrary base**, proved by an algebraic inclusion and finite
counterexamples for all excluded coordinates. The
[producer report](../results/krakken_hash_zero_sum_14cube_validated.json)
records all eleven complete 2048-bit sums and their base messages.
The [independent original-C audit](../results/krakken_hash_zero_sum_14cube_audit_validated.json)
replayed all `11*2^14=180,224` message vertices through both complete
round counts, exactly matching every saved sum. It additionally
replayed the first complete cube at the original-C post-Chi1 and
post-XRBD1 checkpoints, obtaining full-state XOR zero at both.

This is a hash-interface result, unlike the preceding unrestricted
four-state construction. It excludes **universal coordinate-bit
balances for this one direction set at round two**. It does not
exclude other direction sets, larger cubes, base-dependent zero
sums, or universally balanced non-coordinate output masks at round
two. Coordinate exclusion alone does not establish full linear
span of all possible cube sums.

<a id="int-byte-001"></a>
## Proved: complete one-byte coordinate-cube class has no universal round-two coordinate balance

<!-- THEOREM METADATA INT-BYTE-001 -->
**Permanent ID:** `INT-BYTE-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA INT-BYTE-001 -->

For each message-byte position `p=0,...,158`, let `Q_p(b)` contain the
256 valid 159-byte messages obtained by varying byte `p` through all
values while holding the other 158 bytes at a base `b`. For every
state-output coordinate `j=0,...,2047`, **there exists a valid base**
`b` such that

`XOR_{m in Q_p(b)} F_2(m)[j] = 1`.

Thus no individual output bit is balanced for **every** base in any
of the 159 one-byte coordinate-cube families after two complete
rounds. The quantifiers cover all `159 * 2048 = 325,632`
position/output-bit combinations. This is a finite counterexample
proof: for each position, the bitwise OR of the saved full-state cube
sums is all ones. At most 18 bases are needed per position. The
[producer certificate](../results/krakken_byte_cube_all159_validated.json) saves
the bases and complete 2048-bit sums for all 1,946 cubes. An
[independent original-C replay](../results/krakken_byte_cube_all159_audit_validated.json)
recomputed all `1,946 * 256 = 498,176` valid-message vertices at
both round counts, matching every saved sum (996,352 complete-round
evaluations). The certificate is deterministic once saved; its
initial randomized base search is not used as a statistical
inference.

This does not exclude a balance for a particular base, a different
direction set, or a non-coordinate output mask. In the saved
contexts, 113 byte positions retain at least one common round-one
balanced coordinate; those finite observations do not establish a
universal round-one integral.

<a id="int-byte-002"></a>
## Proved: no universal round-two linear output-mask balance for the byte-0 cube

<!-- THEOREM METADATA INT-BYTE-002 -->
**Permanent ID:** `INT-BYTE-002` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA INT-BYTE-002 -->

Fix the eight coordinate directions of the **first message byte**.
Let `S_2(b)` be the 2048-bit XOR sum of `F_2` over its 256-point
cube at valid base `b`. There are 2048 explicit bases `b_i` such
that the vectors `S_2(b_i)` have GF(2) rank **2048**. Therefore, for
every nonzero full-state linear output mask `beta`, at least one of
these bases has `beta·S_2(b_i)=1`. Equivalently, **no nonzero
linear output mask is balanced for every valid base** in this fixed
one-byte cube family after two complete rounds. This includes all
output masks restricted to the 256-bit digest projection.

The [rank certificate](../results/krakken_byte_cube_rank_p0_validated.json)
stores every base and both complete-round sums; 2,050 contexts were
tried to obtain the 2,048 independent round-two vectors. An
[independent original-C audit](../results/krakken_byte_cube_rank_p0_audit_validated.json)
replayed the 2,048 selected cubes (524,288 valid-message vertices),
matched every saved round-one and round-two sum, and recovered rank
2048 with the opposite pivot order. This is a complete defined-family
exclusion, not an assertion about all cube directions or higher-order
integrals. The same 2,048 saved bases give round-one sum rank 2041;
the exact local-division proof below establishes that its seven
orthogonal masks are indeed universal round-one balances.

<a id="div-byte-001"></a>
## Proved: exact byte-0 division-property balance threshold, rounds one and two

<!-- THEOREM METADATA DIV-BYTE-001 -->
**Permanent ID:** `DIV-BYTE-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIV-BYTE-001 -->

For the fixed eight coordinate directions of **message byte zero**,
let `U_r` be the vector space of all 2048-bit linear output masks
whose 256-point cube sum is zero for **every valid base message**
after `r` complete rounds. Then

`dim(U_1)=7`, while `dim(U_2)=0`.

The new [exact local division script](../scripts/krakken_division_exact_byte0.py)
proves the inclusion `dim(U_1)>=7` without sampling bases. It
propagates the eight input directions through the *linear* first-round
prefix using the pinned C layers. For each of the 128 serial-Chi
two-byte cells, it evaluates the exact eighth derivative of that
cell's 16-bit truth table over **all 65,536 local base values**. This
is the coefficient of the full eight-variable cube monomial: a zero
masked coefficient is precisely a balanced integral. The 32 exact
affine Pressure-output bits are pulled back to post-Chi by original-C
basis evaluations of XRBD, Pressure, constants and shuffle. The
exhaustive local derivative values impose a 25-rank linear constraint
system on those 32 output-mask bits, leaving seven independent
masks. Each annihilates the derivative of **every** Chi cell for
every local base, so each annihilates their XOR for every reachable
message base. The [certificate](../results/krakken_division_exact_byte0_validated.json)
records all eight local input directions at every cell and seven
attaining 2048-bit masks; one is the single state bit at position
907 (LSB-first numbering).

To prove **equality**, the earlier
[finite original-C cube-sum certificate](../results/krakken_byte_cube_rank_p0_validated.json)
has round-one rank 2041 across 2,048 valid bases. Hence the space of
universal masks has dimension at most `2048-2041=7`. Its round-two
rank is 2048, proving `dim(U_2)=0`. An
[independent audit](../results/krakken_division_exact_byte0_audit_validated.json)
recomputed all 128 local derivative tables, checked 384 local Chi
cases against original C, verified the seven masks against every
saved round-one sum, and recovered ranks 2041/2048 with opposite
pivot order. The earlier [original-C cube replay](../results/krakken_byte_cube_rank_p0_audit_validated.json)
verified every saved sum at both round counts.

This is an exact **division-property/integral theorem for a defined
hash-input cube family**. It does not imply that all integrals vanish
at round two; other cube directions or nonlinear output functions
may behave differently. It does establish a complete transition
from seven universal linear-mask balances to none for this family.

<a id="subspace-001"></a>
## Proved: maximal affine-hull growth of every message-byte subspace at Chi1

<!-- THEOREM METADATA SUBSPACE-001 -->
**Permanent ID:** `SUBSPACE-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA SUBSPACE-001 -->

For each message-byte position `p=0,...,158`, let `V_p` be the
eight-dimensional coordinate subspace that varies only byte `p` of
an otherwise zero **valid padded 159-byte message**. Its 256 images
have affine-hull dimension **8** at the pre-Chi1 checkpoint and
**255**, the largest possible dimension for 256 points, immediately
after Chi1. The dimension is also 255 after XRBD1, after one
complete round, and after two complete rounds.

The [source-pinned original-C enumerator](../source/krakken_subspace_byte_hull.c)
evaluates all `159 * 256 = 40,704` valid inputs at ten layer
checkpoints and performs exact GF(2) elimination on the 2,048-bit
state differences. The [report](../results/krakken_subspace_byte_hull_validated.json)
records rank 8 pre-Chi1 and rank 255 at **every later checkpoint for
every position**. An [independent original-C audit](../results/krakken_subspace_byte_hull_audit_validated.json)
re-enumerates all 40,704 messages in reverse order, changes the
affine origin, and eliminates with opposite pivot order. It confirms
rank 255 after Chi1 and after complete rounds one and two at all
159 positions.

Consequently none of these 159 coordinate byte-subspace families can
have a **universal subspace trail into affine spaces of dimension at
most 254** after Chi1, round one, or round two: the zero-base coset
already contradicts such a trail. This does **not** exclude a
special-base coset with a smaller image hull, a 255-dimensional
trail, or other input subspaces. Maximal rank for 256 random-looking
outputs is expected, so this is an exact structural class result,
not a numerical security bound. In this class, the observed hull
growth occurs at the first nonlinear layer, not at round two.

<a id="subspace-002"></a>
## Proved: Theta-cancelling two-byte subspace trails end at Pressure1

<!-- THEOREM METADATA SUBSPACE-002 -->
**Permanent ID:** `SUBSPACE-002` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA SUBSPACE-002 -->

Consider valid 159-byte messages with only bytes **40 and 56**
variable and all other message bytes zero. Partition this full
16-bit plane into 256 affine eight-dimensional cosets

`V_delta = {(m[40],m[56])=(delta XOR t,t): t in GF(2)^8}`.

The two varied bytes occupy lanes in the same Theta column and the
same byte offset. Their equal `t` directions cancel that column's
parity exactly. For **every** `delta=0,...,255`, the affine hull of
the 256 post-Chi1 states has dimension **strictly below 255**. The
complete rank histogram is:

| Post-Chi1 rank | 238 | 246 | 251 | 252 | 253 | 254 |
|---:|---:|---:|---:|---:|---:|---:|
| Number of cosets | 2 | 2 | 1 | 11 | 94 | 146 |

XRBD is invertible linear, so every post-XRBD1 hull has the **same
rank** as its post-Chi1 hull. Yet after **Pressure1**, every one of
the 256 cosets has the maximal rank **255**; that remains true after
complete rounds one and two. Thus this entire structured family has
genuine low-dimensional affine structure through Chi1 and XRBD1,
and loses that structure at Pressure1. The
[all-coset certificate](../results/krakken_subspace_theta_pair_cosets_validated.json)
enumerates every one of its 65,536 valid messages. An
[independent original-C audit](../results/krakken_subspace_theta_pair_cosets_audit_validated.json)
replayed every message with opposite elimination order and a
different affine origin, matching all five checked checkpoint ranks
and full-state byte-support sums.

A controlled **XRBD-off** variant keeps the same post-Chi1 ranks
and still gives rank **255 after Pressure1 in all 256 cosets**, as
recorded in its [certificate](../results/krakken_subspace_theta_pair_noxrbd_validated.json)
and [independent original-C-layer audit](../results/krakken_subspace_theta_pair_noxrbd_audit_validated.json).
Therefore XRBD is **not required for this particular affine-hull
escape**. It changes the support geometry markedly: over nonzero
cube points, the mean active-byte count is about 44 post-Chi1 and
about 255 post-XRBD1. Support expansion and affine-rank growth are
different properties.

The conclusion is exact for the stated two-byte message plane and
its 256 diagonal cosets. It does not exclude 255-dimensional trails,
other Theta-cancelling planes, or exceptional cosets obtained by
setting additional message bytes. Maximal affine rank is not a
security-bit bound.

<a id="rebound-001"></a>
## Proved: serial-Chi rebound inbound count and one-byte XRBD outbound support

<!-- THEOREM METADATA REBOUND-001 -->
**Permanent ID:** `REBOUND-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA REBOUND-001 -->

This analysis was rebuilt from the current `krakken.c` and
`krakken.h`, without archived rebound scripts. In one 16-bit
serial-Chi component, write

`A=S(a XOR b),   B=S(b XOR A)`.

For a diagonal input XOR difference `(d,d)`, `d!=0`, the first
output difference is **always zero**. A prescribed second-output
difference `eps!=0` occurs for exactly

`256 * DDT_S(d,eps)` of the `65,536` local bases `(a,b)`.

Indeed, choose `x=a XOR b` arbitrarily, set `y=b XOR S(x)`, and
the second output difference is `S(y) XOR S(y XOR d)`. The two
variables `x,y` independently range over all byte values. The
current S-box has maximum nontrivial DDT entry **4**, so the
probability of any one prescribed transition in this family under
a uniform local 16-bit base is at most **`4/256=1/64`**. The
selected `(d,eps)=(101,1)` transition attains this maximum with
**1,024** exact local matches; exhaustive enumeration of all
65,536 bases independently reproduces that count. This describes
an **efficient inbound match inside Chi**, not a full-round trail
probability.

For every one of the **128** serial-Chi cells and every nonzero
second-output byte difference `eps`, the current C XRBD layer was
applied to the resulting one-byte post-Chi difference. All
`128*255=32,640` cases activate **all 32 lanes**, with **48–196
active bytes**. The lower bound 48 is attained at the selected
site `(y,p,k)=(0,0,0)`, `eps=1`. The
[source-pinned producer](../results/krakken_rebound_inbound_validated.json)
stores all 32,640 byte and lane counts, S-box DDT distribution,
and selected inbound witness parameters. An
[independent original-C replay](../results/krakken_rebound_inbound_audit_validated.json)
checks every XRBD case in reverse order, recomputes all local DDT
entries, and validates 64 matched Chi pairs against `chi_scalar`.
The full-width XRBD support statement is exact for this
**one-active-second-output-byte class**. It does not bound more
correlated post-Chi differences.

The **backward outbound** through the exact inverse of the
Theta–MDS–Rho–Pi prefix is also closed for all 128 sites and all
255 nonzero diagonal input bytes `d`. The source-C prefix has full
GF(2) rank **2048**. Pulling a pre-Chi1 difference `(d,d)` confined
to one cell back to the unrestricted permutation input yields **all
32 active lanes and 40–180 active bytes** across the same 32,640
site/`d` cases. For selected site `(0,0,0)` and `d=101`, the
unrestricted input difference has **116 active bytes**. The
[inverse-prefix certificate](../results/krakken_rebound_backward_validated.json)
records all counts and a full original-C one-round witness replay;
an [independent low-pivot audit](../results/krakken_rebound_backward_audit_validated.json)
rebuilds the 2048 inverse columns and rechecks every case. Thus
this selected inbound match has dense deterministic outbound
support on **both** sides of Chi1, although support alone is not
a rebound attack-complexity bound.

<a id="rebound-002"></a>
## Proved: the one-cell Chi inbound class is unreachable from a first hash block

<!-- THEOREM METADATA REBOUND-002 -->
**Permanent ID:** `REBOUND-002` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA REBOUND-002 -->

The valid first-block message difference occupies only the 1,272
message bits; padding and initial capacity have zero difference.
For each of the 128 serial-Chi cells, project the source-C linear
rate-to-pre-Chi1 map onto every state bit **outside** that cell's
two input bytes. The resulting `1272`-column matrix has rank
**1272 at every cell**. Hence its kernel is zero: **no nonzero
valid first-block message difference can be confined to a single
serial-Chi input cell before Chi1**. Serial Chi is a bijection on
each independent cell (invert `B` for `b`, then invert `A` for
`a`), so a nonzero difference confined to one *output* cell also
cannot be reached from the first hash block.

The [source-pinned rank certificate](../results/krakken_rebound_rate_gate_validated.json)
records all 128 projected ranks and a digest of the 1,272 C-derived
columns. An [independent original-C audit](../results/krakken_rebound_rate_gate_audit_validated.json)
rebuilds the columns in reverse order and verifies every rank using
opposite pivot order. Thus the one-cell rebound construction above
is an **unrestricted internal-permutation** phenomenon. This gate
does not exclude multi-cell inbound constructions or later absorb
blocks, where the capacity is no longer the fixed initial state.

<a id="depend-001"></a>
## Proved: full first-order message-bit dependency after rounds one and two

<!-- THEOREM METADATA DEPEND-001 -->
**Permanent ID:** `DEPEND-001` · **Proof classification:** finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DEPEND-001 -->

For every message bit `i=0,...,1271`, every state bit
`j=0,...,2047`, and each `r` in `{1,2}`, there is a valid message
`m` for which `F_r(m)[j] != F_r(m XOR e_i)[j]`. The finite certificate
stores at most 21 base messages per input bit and the full-state XOR
differences. Taking the OR of the differences for each input bit
gives all 2048 output bits at **both** round counts. The
[producer](../results/krakken_bit_dependency_all1272_validated.json) records
16,946 contexts; an [independent original-C replay](../results/krakken_bit_dependency_all1272_audit_validated.json)
verified all 67,784 complete-round evaluations and the complete
coverage. This result concerns *possible influence*, not influence
probability, algebraic degree, or cryptanalytic resistance. Since
round one already has full coverage, it supplies no special
round-two threshold for this class.

<a id="diff-trunc-001"></a>
## Theorem proved: guaranteed zero-output projections for diagonal one-cell differences

<!-- THEOREM METADATA DIFF-TRUNC-001 -->
**Permanent ID:** `DIFF-TRUNC-001` · **Proof classification:** analytic proof + finite exhaustive proof. Scope and audit limits are stated below.
<!-- END THEOREM METADATA DIFF-TRUNC-001 -->

This is an **attack-side one-round theorem for the unrestricted permutation P**.
Index a serial-Chi cell by `pair p=0..3`, `row y=0..3`, and first-input
byte `j=0..7`. Put a nonzero byte `delta` at byte `j` of lane
`ca=8p+y` and the same byte at byte `(j+4) mod 8` of lane
`cb=8p+4+y` in the **pre-Chi1 difference**, with all other bytes zero.
Invert the actual linear Theta→MDS→Rho→Pi prefix to obtain the unique
round-input difference `Delta`. This defines `128 × 255` unrestricted
input differences. For **every** base state `x` and all those differences,
the complete one-round output difference has zero bits in the exact
per-site **guaranteed sets** listed by the
[certificate](../results/krakken_truncated_zero_certificate.json). The
catalogue is a sound set of guaranteed zeros, not a claim that every
other bit can change.

For `p=0, y=0, j=0`, the guaranteed set contains **200 output bits**, including
all bits of these **15 bytes** (zero-based state-byte positions):

`2, 3, 4, 108, 109, 114, 115, 116, 130, 131, 236, 242, 243, 251, 252`.

Thus the sampled byte-252 zero difference in the truncated-differential
screen is **universal for that unrestricted input-difference family**,
not merely a 100,000-base observation. Across all 128 cells, the
certificate guarantees at least one complete zero-difference output byte
in **73** cells. In the other 55, this particular low-prefix method gives
no full-byte guarantee; it does not assert that no such byte exists.

**Proof.** In the serial Chi, the first S-box input difference cancels:
`delta XOR rotl64(delta at second lane,32)=0` at byte `j`.
Its output is equal for the two bases, so the second S-box output
difference is confined to byte `(j+4) mod 8` of `cb`, whatever its
nonzero value. XRBD is linear. For each of the 128 cells, the producer
applies the original-C XRBD to all eight basis bits of that one byte;
their OR is an exhaustive bit-support superset for **every** possible
second-S-box output difference.

Let `ell_a,ell_b,ell_c,ell_d` be the number of guaranteed unchanged low
bits in the four XRBD input words of a Pressure chain. Congruence
modulo `2^k` proves that Pressure's unrotated first outputs have at
least

`ell_A=min(ell_a,max(0,ell_c-17))`,
`ell_B=min(ell_b,max(0,ell_d-17))`

unchanged low bits. The second outputs have at least
`ell_C=min(ell_c,ell_A)` and `ell_D=min(ell_d,ell_B)`.
These formulas are conservative when a word has no difference.
The `A<<31` and `B<<31` shears cannot introduce a changed lower bit
than `A` or `B` themselves. Pressure's rotations, the fixed round
constant, and InkCloud's final rotation/permutation then map those
low-bit zeros to the certificate's stated output positions. In the
selected cell, XRBD leaves Pressure words 9 and 11 unchanged below
bits 22 and 45 respectively. Therefore odd-chain word `B` is unchanged
below bit 22; its combined 7+11 rotation maps those bits to output
lane 31, including byte 252. The other 14 guaranteed bytes follow by
the same per-chain calculation. Round constants cancel in XOR differences.

The [producer](../scripts/krakken_truncated_zero_theorem.py) enumerates
all `128×8=1,024` local XRBD basis vectors and applies the analytic
low-prefix lemma. An [independent implementation audit](../results/krakken_truncated_zero_audit.json)
recomputes all 1,024 XRBD basis outputs in separate Python code,
checks 2,048 random post-Chi tail pairs against the original C,
and replays 256 complete one-round unrestricted pairs for the selected
site, including its one-cell Chi embedding. Those replay counts validate
the implementation; the exhaustive basis support and modular-congruence
argument prove the theorem. The result is **not hash-first-block
reachable** via this one-cell input difference, as the existing
`BOOM-EMBED-001` / `REBOUND-002` rate-support exclusion shows. It
does not give a round-two zero-output guarantee or a collision attack.

## Reproduction commands for earlier linear certificates

```bash
python3 krakken_full_linear_rank.py --max-messages 4000 --seed 492091 --rounds 8 --output new_full_linear_rank.json --certificate new_full_linear_rank_messages.bin
python3 krakken_full_linear_rank_audit.py --report new_full_linear_rank.json --output new_full_linear_rank_audit.json
python3 krakken_sbox_walsh_certificate.py --output new_sbox_walsh.json
python3 krakken_rate_chi_component_rank.py --max-components 3 --output new_rate_chi_rank.json
python3 krakken_rate_chi_component_rank_audit.py --report new_rate_chi_rank.json --output new_rate_chi_rank_audit.json
python3 krakken_pressure_first_branch_walsh.py --output new_pressure_first_branch.json
python3 krakken_pressure_second_shear_walsh.py --output new_pressure_two_shear.json
python3 krakken_pressure_pairwise_independence.py --output new_pressure_pairwise.json
```
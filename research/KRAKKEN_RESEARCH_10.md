# Krakken research 10 — Atlas review and one-round output theorems

Reviewed 2026-11-13 against research ledgers 01–09 and the unchanged scalar
`krakken.c` / `krakken.h`. Sources: the seven Atlas volumes in `reproduce/atlas/` and
five supplied reproduction ZIPs for volumes III–VII. Preserved copies,
extracted packages, replay outputs and exact commands are in
[reproduce/atlas_integration/](reproduce/atlas_integration/README.md).

## 1. Findings and evidence status

The principal additions are **new one-round, H159 output-projection results**,
not more statistical randomness tests:

- An exact differential-autocorrelation formula for digest-position bit 11,
  including a complete 120-dimensional translation-period space.
- Exact counts over all message differences, plus the complete one-byte census.
- A stronger one-round bit-139 correlation bound and the previously missing
  mixed bit-11/139 bound, giving a quantitative two-bit joint distribution.
- Seven Fourier bounds giving a three-bit joint distribution, together with
  worst-case guarantees on all affine message restrictions of codimension ≤10.
- Explicit limitations of the current four-bit certificate and of transporting
  these conclusions through the next round.

Retain the original `ATLAS-*` labels below to preserve provenance. These are
assistant-authored, source-specific computer-assisted results whose supplied
proof arguments were reviewed and selected computations replayed here. This
is not external peer review or proof-assistant verification.

**Fresh checks performed:** all ten packaged C/H copies match the current
source; all 111 valid entries in the supplied checksum manifests match.
Volume IV's derivative audit, Volume V's exact census and kernel audit, and
Volume VII's complete 15-character certificate and source checks were rerun
in separate working copies. Volume VII's GCC/Clang depth traces also match
each other and the archive. The inherited audits are separately implemented
within their packages; replaying them here is not independent rediscovery.
[Detailed results](reproduce/atlas_integration/REVIEW_CHECKS.json).

**Historical status corrections:** Atlas III's older 15/19/20 cumulative
activity figures and comments about completing minimum-A1 families must not
replace current results. Research 07 gives 16 unrestricted / 19 H159 / 21
H159 conditioned on A1=5 under its stated established premises, with a
selected-family 22-call result. The `[2,1]` campaign is complete: 255 positions,
8,355,840 configurations excluded, zero unresolved. Research 08 already
covers all 21 minimum-A1 families. No old campaign is reopened here.

## 2. Common notation and why the selected bits are tractable

Let `E(m)` embed a 159-byte message into the 2,048-bit state with byte 159
set to `0x86` and bytes 160–255 zero. Let `R0` be the first indexed **complete
nine-layer round**, and write `F_b(m)` for its output bit b, using little-endian
bit numbering. These positions lie in the first 256 output bits, but `F_b`
is a reduced-round observable, not the production eight-round digest bit.

For aligned serial-Chi bytes, use

```
x = a XOR b;  u = S(x);  v = S(b XOR u).
```

Undoing Ink Cloud's bit relocation and the constant XOR maps positions
11, 94, 139 and 210 to Pressure output least-significant bits. Those bits have
exact carry-free formulas. Pull their parities back through Butterfly's
transpose to obtain parities on serial-Chi outputs. The prefix before Chi
is linear, so every required local argument is an affine function of m.
This uses the actual layer order and serial substitutions; it does not
model two independent S-box calls or independent rounds.

For bit 11, the resulting parity observes 48 first-only cells and 48
second-only cells, disjoint. In each group masks `0x01,0x02,0x04` occur
8, 24 and 16 times. The required coordinates are 48 eight-bit x arguments
and 48 sixteen-bit (x,b) arguments: **1,152 coordinates with rank 1,152**
over the 1,272 message bits. This rank proves their joint uniformity and
independence under uniform H159 messages. The earlier exact marginal balance
of bit 11 in research 03/08 is a premise, not a newly discovered result.

## 3. ATLAS-IV-DERIV-001 — exact all-difference autocorrelation

Define the local Boolean functions

```
g_alpha(x) = alpha · S(x)
h_beta(x,b) = beta · S(b XOR S(x))
```

and their normalized autocorrelations `A_alpha(dx)` and `B_beta(dx,db)` by
averaging `(-1)` raised to the XOR of the function at the original and shifted
arguments, over all 256 or 65,536 local bases respectively. For **every**
message difference Delta,

```
C_11(Delta) = E_m (-1)^[F_11(m) XOR F_11(m XOR Delta)]
            = product of the 48 selected A factors
              times product of the 48 selected B factors.
Pr[bit 11 flips] = (1 - C_11(Delta))/2.
```

**Proof:** full row rank makes the 96 local base groups independent and
uniform. A fixed message difference induces a fixed translation in each
group. The sign of the XOR is the product of the local derivative signs;
its expectation therefore factors exactly. Fixed affine offsets and output
constants do not change this derivative law. This independence is established
for these particular coordinates, not assumed about intermediate states.

For all three relevant masks, the maximum nontrivial magnitude of either
local autocorrelation is exactly 1/8. If Delta changes t observed local
argument groups, then `|C_11(Delta)| ≤ 2^(-3t)`. An exactly zero local factor
makes the whole correlation zero. The formula covers arbitrary-weight
message differences without enumerating all `2^1272` possibilities.

The same argument covers any fixed assignment to input bytes 159–255 and
any isolated indexed round applied directly to that affine input plane.
It does not apply automatically to the nonlinear state distribution entering
round two of an actual evaluation.

## 4. ATLAS-IV-PERIOD-003 — a complete reduced-round period space

Let L be the rank-1,152 observed-coordinate map above. Then

```
{Delta : F_11(m XOR Delta) = F_11(m) for every m} = ker L,
dim ker L = 120.
```

There are exactly `2^120` periods, including zero. There is **no** difference
that universally toggles this bit.

**Proof:** kernel directions leave every local argument unchanged. Outside
the kernel, at least one local factor has magnitude at most 1/8, so the exact
product has magnitude below one; neither a constant-zero nor constant-one
derivative is possible.

This is a genuine **attack-side one-round structure**. It distinguishes the
reduced-round Boolean output from a typical random Boolean function. It is
not a full-state period or a hash collision, and it coexists with tiny
correlations for low-weight differences.

The archived 120-vector kernel basis has rank 120, and every vector satisfies
all 1,152 equations. Volume V improves the exhibited nonzero vector from
534 bits / 145 active bytes to **495 bits / 143 active bytes**. The replayed
kernel audit confirms membership and weight. Thus the binary code's minimum
distance satisfies `d_min ≤ 495`; equality or a lower bound was not proved.
The heuristic search itself was not rerun here.

The saved 534-bit witness has original-C counterexamples to periodhood at
each depth 2–8: among 64 bases the bit-flip counts are
`0,25,23,29,33,39,33,28` at depths 1–8. Those archived examples refute
continued universal periodhood for **that difference**. They do not exclude
all periods or bound every later-round bias. These depth experiments were
not rerun in this integration.

## 5. ATLAS-IV-CENSUS-002 — exact one-bit and one-byte census

These are expectations over all uniform H159 base messages, computed using
the exact formula, rather than averages from sampled bases.

| Difference class | Directions | Exactly balanced derivatives | Nonzero autocorrelation |
|---|---:|---:|---:|
| One message bit | 1,272 | 1,133 | 139 |
| Nonzero difference inside one message byte | 40,545 | 38,293 | 2,252 |

For both classes the sharp maximum is

```
max |C_11(Delta)| = 33707585835 / 2^141,
max |Pr[flip] - 1/2| = 33707585835 / 2^142 < 2^-107.
```

It is attained at message byte 94 XOR `0x02`. The supplied audit rerun here
reconstructs the tables and census, verifies coordinate rank with two pivot
orders, and checks the bit identity through GCC and Clang. The package also
contains a separate direct-C all-one-byte-prefix audit; that additional audit
was not rerun here.

**Terminology:** bit 11 does not satisfy exact strict avalanche on every unit
direction: 139 unit directions have small but nonzero autocorrelation.
“Extremely close to half” and “exactly half” remain different statements.

## 6. ATLAS-V-CENSUS-001 and ATLAS-V-TAIL-002 — all message differences

The local zero-autocorrelation counts for masks `01,02,04` are respectively
32/32/32 among 256 first-only shifts and 1041/1037/1018 among 65,536
second-only shifts. Every observed-coordinate shift has exactly `2^120`
message-difference preimages. Therefore the number of exactly balanced
directions is

```
N_bal = 2^1272 - 2^120 * 224^48 * 64495^8 * 64499^24 * 64518^16.
```

The fraction among all differences is
`N_bal/2^1272 = 0.999231357944274318059…`, or **99.9231357944274%**.
Zero is not balanced; among nonzero differences the denominator is instead
`2^1272−1`. This is an exact coverage fraction of a defined difference
population, **not a fraction of attacks excluded**.

Two generating polynomials give more information:

```
Z(z) = (224+32z)^48 (64495+1041z)^8
       (64499+1037z)^24 (64518+1018z)^16;
Q(z) = (1+255z)^48 (1+65535z)^48.
```

`2^120 [z^k]Z` counts message differences having exactly k zero factors.
`2^120 [z^t]Q` counts differences changing exactly t local argument groups.
Both polynomials sum to `2^1152` at z=1 before the fiber multiplier.
The expected counts are 6.75537109375 zero factors and 95.811767578125
changed groups. Exactly counting the tail gives

```
Pr_uniform_Delta[t ≥ 92] = 0.999998617868818111947…;
on that set: |C_11(Delta)| ≤ 2^-276,
             |Pr[flip]−1/2| ≤ 2^-277.
```

This is an almost-all-direction theorem, not a worst-case bound: the period
space still has correlation one. Exact local moments also yield
`log2 E_Delta|C_11| ≈ −566.4805707998` and
`log2 E_Delta C_11² ≈ −1004.7790349239`; these are population averages.

**Text correction:** Volume V §10 prints the second-moment denominator as
`2^(31152)`. The supplied program and the correct product calculation use
`2^(3*1152) = 2^3456` before reducing the rational fraction. The first absolute
moment has denominator `2^(2*1152)` before reduction. The archive is unchanged;
this ledger uses the corrected mathematical expression.

## 7. The affine-frequency-fiber bound: composition within one round

For a local serial-Chi output character with masks alpha,beta, let
`W(r,q) = sum_x (-1)^[r·x XOR q·S(x)]`. Its normalized 16-bit Fourier
coefficient at input mask (r,s) is exactly

```
W(r, alpha XOR s) W(s,beta) / 2^16.
```

Substitute `y=b XOR S(x)` to separate the two sums. If beta=0, retain only
x and use the eight-bit coefficient. This accounts for the serial dependency.

Let all required formal local coordinates be `z=A m XOR t`, with N rows
and rank r. For the product h of the local sign functions and **any** input
mask a,

```
E_m (-1)^(a·m) h(A m XOR t)
    = sum_{w:A^T w=a} hhat(w) (-1)^(w·t).
```

Each nonempty fiber has `2^(N−r)` elements. If the local unnormalized Walsh
maxima are `m_i`, their coordinate dimensions sum to N, giving

```
|correlation| ≤ min(1, product_i m_i / 2^r).
```

This replaces an unjustified full-independence argument with an explicit
rank-deficiency cost. It is related to the earlier affine Fourier methods,
but the Atlas supplies new source-derived masks and exact local maxima for
these particular output parities. The fresh Volume VII replay matches all
211 relevant local maxima by direct transforms: 198 full 16-bit and 13
first-only eight-bit functions.

## 8. ATLAS-VI-JOINT-001 — two-bit joint law and stronger bit-139 bound

Put `F=F_11`, `G=F_139`, `g=466948881/2^400`, `h=2401/2^268`.
Over all uniform H159 messages,

```
E(-1)^F = 0;
|E(-1)^G| ≤ g < 2^-371;
|E(-1)^(F XOR G)| ≤ h < 2^-256.
```

The bit-139 envelope strengthens the earlier `2^-124` bound in research 03/08.
The mixed-character envelope supplies information absent from separate
marginals. These bounds follow from the fiber lemma; the generic all-input-mask
bound for bit 11 is `2^-432`, while its unconditional expectation is zero.

For every two-bit value t,

```
|Pr[(F,G)=t]−1/4| ≤ (g+h)/4 < 2^-258;
TV((F,G), uniform_2) ≤ h/2 = 2401/2^269 < 2^-257.
```

The sharper TV formula uses exact balance of F:
`TV = max(|E(-1)^G|, |E(-1)^(F XOR G)|)/2`.
These are distributional-distance exponents for **two bits after one round**,
not security-bit claims.

The formula also bounds population collision probability for two independent
uniform messages by `(1+g²+h²)/4`. Full one-round digest equality implies
projection equality, so this yields a full one-round digest collision-entropy
lower bound `2−log2(1+g²+h²)`, close to two bits. This is not chosen-message
collision-search hardness.

The all-input-mask envelopes imply, on every nonempty affine message subspace
of codimension d, point error at most
`2^d(2^-432+g+h)/4`. At d=128 this is `<2^-130`.
Arbitrary fixed complement-state bytes are allowed; arbitrary message-dependent
capacity values or nonlinear restrictions are not covered.

The two principal numerical envelopes were reproduced as part of Volume VII's
broader certificate. Volume VI's separate period experiment was not rerun.

## 9. ATLAS-VII-FOURIER-001 — a complete three-bit joint certificate

For `T=(F_11,F_139,F_210)`, the seven required all-input-mask envelopes are:

| Selected parity | Exact envelope B |
|---|---|
| 11 | `2^-432` (unconditional expectation exactly zero) |
| 139 | `466948881/2^400` |
| 210 | `64596985700625/2^264` |
| 11 XOR 139 | `2401/2^268` |
| 11 XOR 210 | `140772351307849566219140625/2^152` |
| 139 XOR 210 | `13286025/2^136` |
| 11 XOR 139 XOR 210 | `630829938482666015625/2^80` |

Let S be the sum of the six envelopes excluding bit 11. Exact Fourier inversion
and the triangle inequality give, for every t,

```
(1−S)/8 ≤ Pr[T=t] ≤ (1+S)/8;
TV(T, uniform_3) ≤ S/2 < 0.000260905147465441;
|Pr[T=t]−1/8| ≤ S/8 < 0.000065226286866361.
```

The three-way parity dominates this conservative bound. The exact rationals,
not rounded decimals, define the certificate. Consequences include

```
H_infinity(T) ≥ 3−log2(1+S) > 2.99924738 bits;
Pr[T(M)=T(M')] ≤ (1 + sum B_s²)/8;
H_2(T) ≥ approximately 2.99999960717 bits,
```

where the square sum excludes the exactly zero unconditional bit-11 term and
M,M' are independent uniform H159 messages. These are entropy floors for a
three-bit projection, not a full-hash security level.

**Whole-family affine restriction corollary.** Let `S_aff=S+2^-432`.
On every affine message subspace of codimension d,

```
Pr[T=t] ≥ (1−2^d S_aff)/8.
```

Since `2^10 S_aff < 1`, **all eight output patterns occur on every affine
subspace of codimension at most 10**. At codimension ten every pattern has
probability greater than 0.05820828. The failure of this sufficient test at
codimension eleven does not exhibit a missing pattern there. The bound also
holds for every fixed 97-byte complement of the 159 variable input bytes.

## 10. Four-bit frontier: informative failure of a proof method

Adding position 94 requires all fifteen characters. The following deficiencies
and log2 envelopes were regenerated exactly before taking display logarithms:

| Parity | N | Rank | N−rank | log2 envelope |
|---|---:|---:|---:|---:|
| 11 | 1152 | 1152 | 0 | −432 |
| 94 | 1680 | 1272 | 408 | −145.199 |
| 11,94 | 1856 | 1272 | 584 | +5.750 |
| 139 | 1376 | 1272 | 104 | −371.201 |
| 11,139 | 1600 | 1272 | 328 | −256.771 |
| 94,139 | 1904 | 1272 | 632 | +19.332 |
| 11,94,139 | 1936 | 1272 | 664 | +64.971 |
| 210 | 1568 | 1272 | 296 | −218.123 |
| 11,210 | 1728 | 1272 | 456 | −65.137 |
| 94,210 | 1744 | 1272 | 472 | −85.313 |
| 11,94,210 | 1856 | 1272 | 584 | +8.978 |
| 139,210 | 1760 | 1272 | 488 | −112.337 |
| 11,139,210 | 1824 | 1272 | 552 | −10.904 |
| 94,139,210 | 1904 | 1272 | 632 | +12.982 |
| 11,94,139,210 | 1936 | 1272 | 664 | +59.687 |

Six raw envelopes exceed one. They do not show large true bias; they show
that counting every frequency in the fiber at the product of local maxima
is too loose. Volume III's rank-only diagnostic is thus superseded as a
proof strategy by VI/VII, while its exact ranks remain useful and consistent.
The projection `(11,139,210)` was selected because all seven of its characters
have informative envelopes. No four-bit near-uniformity theorem is claimed.

## 11. Finite experiments preserved separately

Volume III supplies original-C traces for two H159 pairs differing in one
input bit. Their first-round changed-bit counts progress through
`1 → 9 → 146 → 146 → 146 → 377/370 → 1033/1078 → 1027/1015`, with the last
two affine layers preserving these weights. Their R8 state differences weigh
1050 and 1064. These are illustrative trajectories, not minimum diffusion.

Volume V exhausts two selected 12-dimensional kernel cosets (4096 messages
each). Bit-11 one-counts at R1–R8 are:

| Depth | Coset 0 | Coset 1 |
|---|---:|---:|
| 1 | 0 | 4096 |
| 2 | 2017 | 2026 |
| 3 | 2071 | 2067 |
| 4 | 2034 | 2055 |
| 5 | 2033 | 2018 |
| 6 | 2052 | 2060 |
| 7 | 2082 | 2054 |
| 8 | 2050 | 2046 |

Constancy at R1 follows from kernel membership; later nonconstancy is proved
for those particular finite cosets. All recorded full 256-bit cube XORs are
nonzero. This is not an all-coset theorem or a general integral exclusion.
These archived coset evaluations were not rerun in this pass.

Volume VII supplies 2048 deterministic messages and three-bit counts at all
depths 1–8. **That experiment was rerun** using GCC and Clang; both CSVs match
the archived outputs byte-for-byte. Those finite counts provide implementation
controls, not a population extension of the one-round bound.

## 12. Why this does not automatically cross the next round

The H159 state image has `2^1272` elements. Invertibility preserves that size
but not any digest projection: a 256-bit fixed-output fiber contains `2^1792`
full states. Abstractly, an arbitrary set of `2^1272` states can be injected
into that fiber and the injection extended to a permutation of the complete
state space. Thus bijectivity and support size alone cannot transport a
first-round projection bound. This counterexample is a logical obstruction,
not a model of the actual next Krakken round.

Useful next proof targets from the Atlas are:

1. Bound the six presently vacuous four-bit characters using actual dual-code
   constraints or signed cancellation instead of a product-of-maxima envelope.
2. Improve the three-way character, which dominates the three-bit error.
3. Pull a second-round character back through the actual next round and bound
   the specific joint observation it queries on the first-round nonlinear
   image. A small controlled Fourier operator or explicit carry conditioning
   could suffice; a fresh uniform-state assumption cannot.
4. Use the exact period code as an adversarial test family, distinguishing
   minimum bit weight, minimum byte support and later-round activity objectives.

These are retained research directions, not completed new experiments or
promises of eight-round security. Current activity and endpoint theorems in
research 02/03/07/08 remain separate from these output-law results.

## 13. Atlas disposition and reproduction qualifications

| Volume | Treatment |
|---|---|
| I | Preserve architectural diagrams, constants, source map and `abc` trace as explanatory reference; no new security theorem promoted. |
| II | Preserve layer rationale, inverses and interface explanation; component facts already occur in earlier ledgers. Design rationale remains distinct from proof. |
| III | Retain exact fifteen-mask rank diagnostic and two finite layer traces; later VI/VII resolve part of its proposed Fourier work. Historical campaign status corrected above. |
| IV | Incorporate exact derivative law, complete period classification and low-weight census; replayed its supplied derivative audit. |
| V | Incorporate exact all-difference census, tails, moments, improved period witness and scoped coset data; replayed census/kernel audit, not heuristic search or coset experiment. |
| VI | Incorporate stronger marginal/mixed bounds, two-bit law and affine restrictions; principal envelopes reproduced in VII's broader calculation. |
| VII | Incorporate three-bit law, affine-surjectivity corollary, four-bit barrier and round-transfer obstruction; core certificate/source/depth calculations replayed. |

Reproduction issues are recorded rather than hidden:

- Volume IV's `derivative_probe.py` reads a Volume III basis path absent from
  its standalone ZIP. The replay directory supplies that exact file from the
  supplied Volume III ZIP; original packages and sources remain unchanged.
- Volume VII's supplied full shell script exits at the **plotting** stage
  because `matplotlib` is unavailable in the venv. All preceding certificate,
  source, compiler and depth checks completed. A core-only replay wrapper is
  supplied; no successful plotting or complete original-script exit is claimed.
- The Volume V second-moment denominator typo is corrected in §6 above.
- Original text versions, ZIPs and extracted package files are preserved;
  generated replay outputs are separate. Source changes were neither needed
  nor made. Earlier research ledgers are unchanged.

## 14. Follow-up review of ~/security/reproduce/attack/ — 2026-11-13

The four reports, analysis programs, result records, two compressed certificates
and rotational input sample in `~/security/reproduce/attack/` were compared with research 01–10.
**No new headline attack-family theorem or improved global bound was found.**
The principal linear, integral and rotational results are already recorded in
research 02 under `-046`, `-047` and `-049`, with existing independent-audit
qualifications. The linear certificate and rotational sample have the exact
hashes recorded there, so they are not independent additional datasets.

All 37 files are now preserved in
[reproduce/attack_review/](reproduce/attack_review/README.md), with a
[report-by-report coverage table](reproduce/attack_review/README.md#coverage-and-disposition),
hashes, source checks and the fresh replay log. The originals are unchanged.
The useful additional material is as follows.

### 14.1 A compact alternative sparse differential certificate

The supplied certificate covers every combination of 256 single-byte post-Chi
source positions and 128 next-Chi byte-pair gates, allowing arbitrary values
in both target bytes. It uses 24 boundary variables and homogeneous linear
implications derived from necessary modular-addition conditions. Each of the
32,768 records gives 24 independent implication steps reaching rank 24, hence
only the all-zero boundary assignment remains.

The supplied Python verifier was **rerun successfully** on every record,
checking all 786,432 steps without invoking a solver. This is a replay of an
existing separately implemented verifier, not independent rediscovery or a
new source-to-model audit. Certificate SHA-256:

```
e1c40130a4d015408ed706a807a5c19caf50593d004d5c417ed5e0c34f1bffd7
```

The stated exclusion is broader than just a one-call next-Chi endpoint: it
allows the whole target cell before applying its nonlinear constraints. But
such a cell contains at most two active byte S-box calls, so the later global
`[1,1]`/`[1,2]` exclusions already rule it out. Its value here is compact,
transparent supporting evidence. The report's older eight-round floor of 12
and additive S-box weight 72 do not replace the current research 07 activity
floors and do not establish a differential-probability or security exponent.

### 14.2 Exact streaming ANF computation worth reusing

The integral report explains how its existing 24-variable, 2048-bit-output
witness avoids a 4-GiB truth table. Split 24 parameters into 16 low and eight
high variables. To recover all coefficients of total degree at least 21,
retain only low monomials of degree at least 13 after each low-variable
Möbius transform: there are `sum_{k=13}^{16} binom(16,k)=697`.
Transforming the high variables cannot mix low-monomial columns, so discarding
the others is exact. The retained tensor needs `697*256*256 = 45,678,592`
bytes (about 43.6 MiB), plus a 16-MiB temporary block. This is a useful method,
not a new degree theorem; the prior full replay is already recorded in -047.

The local inverse-degree asymmetry is also already known: forward serial-Chi
components have degrees 7 or 13, whereas inverse components all have degree 7.
The report supplies the explanatory loose one-round bounds **1651 forward /
889 inverse**: a bijective 128-bit Pressure pair has coordinate degree at most
127, so compose `13*127` or `7*127` with the affine layers. Simple two-round
composition already saturates the generic full-permutation ceiling 2047;
these upper bounds do not certify useful small full-round zero sums.

### 14.3 The linear report in this directory is already corrected

Research 02 documents a historical error in the zero-addition-weight Pressure
mask condition. The present `~/security/reproduce/attack/analysis/LINEAR_REPORT.md` and its utility
code both use the corrected expression:

```
Ua,Vc in {0,1}; Va=Ua XOR Vc;
Uc=(Ua XOR Vc) XOR (Ua << 17).
```

Thus the earlier warning describes a previous report version, not an error
still present in this copy. The existing 36-bit addition-resolved trail-weight
result and its distinction from a linear-hull bound are unchanged.

The preserved word-support solver outputs are historical diagnostics: an
8-round timeout with relaxed objectives 8/31, and a 2-round relaxation optimum
2, show the loss of information in that model. They are not actual trails,
exact activity minima, or reasons to repeat a long solve. No large integral,
linear, RX-sample or solver campaign was rerun during this review.

## 15. Follow-up review of ~/security/reproduce/codex/ — 2026-11-14

Reviewed the two historical ledgers, 14 other Markdown documents, saved result
records, scripts and model variants in `~/security/reproduce/codex/` against research 01–10.
All 198 files are preserved in
[reproduce/codex_review/](reproduce/codex_review/README.md), with per-file hashes,
a document-disposition table and bounded-check results. The original scalar,
header and AVX2 files match this project's sources.

**No new headline security bound was found.** The Pressure affine rulebook and
its standalone probability lemma are already research 02's `-019`; the 22-bit
raw one-round relation is already incorporated and strengthened to a
210-coordinate reference-site guarantee in `-005`. None of the named theorem
IDs in the historical ledgers is missing from the current corpus. The useful
additions concern exact encodings, verification methods and interpretation of
experiments. They are recorded below without duplicating theorem IDs.

### 15.1 Exact local DDT support in a compact circuit

The source S-box has the verified representation
`S(x)=A(Inv(x)) XOR 0xA5` over GF(256) with modulus `0x11D`, where
`A(z)_i=z_i XOR z_(i−1) XOR z_(i+4)` (indices modulo eight). Its inverse
linear map is `A^-1(b)_i=b_(i+2) XOR b_(i+1) XOR b_(i+6)`.
For nonzero input/output differences a,b, put `t=a*A^-1(b)`. Then

```
DDT(a,b)>0 iff t!=0 and Tr(Inv(t))=0.
DDT(a,b)=4 for t=1; otherwise an admitted nonzero pair has DDT=2.
At a=0, only b=0 is admitted.
```

The inversion derivative reduces to `u²+u=1/t`, with the t=1 exceptional
bases included. This local algebra is related to existing S-box results;
the reusable implementation is a 64-AND carryless byte product with linear
field reduction and a reduced decision graph for the eight-bit membership
predicate. It avoids a 65,536-entry symbolic lookup and does not introduce
complete S-box base variables.

**Fresh replay:** the supplied circuit's bit-parallel evaluator agrees with
the source DDT at every one of 65,536 difference pairs. There are 32,386
admitted pairs including `(0,0)`; among the 65,025 nonzero/nonzero pairs,
32,385 are possible and 32,640 impossible. This verifies support, not
independence, shared-base compatibility or a transition probability model.

For a sole active next-Chi call, a first-only cell has input differences
`(alpha XOR u,u)` with `DDT(alpha,u)>0`, hence 32,385 possible boundaries;
a second-only cell has `(beta,beta)`, beta nonzero, hence 255. Across 128
cells this gives **4,177,920 locally possible pre-Chi boundaries**. It is
not a count of realizable message trajectories or a 22-bit attack cost.

The supplied controlled case-016 forward comparison found both the baseline
and DDT-strengthened model unknown at roughly 120 seconds. Internal SAT
variables increased from 103,787 to 244,310. Adding exact support is sound,
but that experiment did not demonstrate faster solving. Those timings were
not rerun here.

### 15.2 Eliminate the inverse tail before asking the solver

Fix the sole next-Chi endpoint and parameterize its pre-Chi difference by
8 or 16 bits. Apply the inverse next-round prefix and inverse Ink Cloud to
express **every Pressure output-difference bit** in those parameters. This
removes the forward second-prefix circuit and unused final Chi output variables.
It retains first-round message reachability and necessary nonlinear constraints;
every actual trajectory still embeds in the reduced model.

Historical implementation controls cover all 3,072 endpoint basis images,
all 256 endpoint labels, original-C necessary-condition acceptance, and the
actual dense `[5,255]` witness. Recorded comparisons include:

| Named pilot | Earlier model | Reduced/refined model |
|---|---|---|
| Case 016 | Forward activity-only: unknown at 300 s | Backward activity-only: UNSAT in 14.85 s; backward DDT: 23.61 s |
| Case 000 | Simpler backward: unknown at 120 s | Joint low-five-bit Pressure: UNSAT in 79.68 s |
| Case 008 | Simpler/joint-five-bit: unknown at 120 s | Joint low-seventeen-bit Pressure: UNSAT in 49.17 s |

These are selected machine/model measurements, not guaranteed speedups or
independently checked UNSAT proofs. The 17-bit formulation respects the
nonoverlapping low-c and shifted-c slices and the vanishing low bits of
`A<<31`; extending that independent-slice model above width 17 would require
new justification.

A separate translation removes 26,616 isolated integer parity-quotient
variables by replacing `sum(bits)−output=2q` with exact Boolean XOR parity;
the removed q is uniquely recovered. This is an encoding reduction, not a
cryptographic assumption. The original constraints must still be checked
when interpreting a relaxed satisfying assignment.

### 15.3 Carry automata and bounded independent spot audits

`LOCAL_AUDIT.md` describes a sixteen-state automaton tracking both addition
carries in both executions. For each local difference symbol it enumerates
eight choices of `(a,c,h)` base bits, begins with zero carries and accepts
any final carry state modulo `2^k`. A site's exact bit-zero kernel is then
enumerated with nonzero endpoint-byte restrictions preserved.

The saved audit checked 18 named `[1,2]` sites with a separate Boolean encoding;
15 were also excluded solver-free, covering 26,112,497 nonzero kernel
assignments, of which 22,589,918 satisfy the required nonzero-byte restrictions.
Three large kernels were explicitly skipped by the solver-free cap, not
silently marked excluded by that route. Two width-five BB cases each have
one relaxed width-four assignment and none at width five: useful positive
controls. The source's exhaustive small-width automaton comparisons cover
1,082,400 profiles against 17,043,520 base/difference executions.

These are **saved spot-audit results**, not newly rerun here or a complete
independent recount of every global exclusion. The BB coordinate convention
converts the branch byte by XOR 4; preserving this convention prevents a
mislabelled replay. None of these historical spot-audit limitations reopens
the completed global `[1,2]` or `[2,1]` campaigns.

### 15.4 Learned Pressure guards must beat an existing exact baseline

The affine-learning review proves 79 saved guards symbolically, but they
represent only **25 distinct rules**: six width-ten and nineteen width-22
guards. Its comparison with the exact joint low-two-bit gate is informative:

| Synthetic dataset | Full affine rejections | Learned-guard rejections | Exact low-two-bit rejections |
|---|---:|---:|---:|
| 1152 training profiles | 79 | 79 | 60 |
| 1728 holdout profiles | 114 | 93 | 93 |

On holdout, the learned and low-two-bit filters reject **the same 93 profiles**.
Thus the learned guards add zero holdout exclusions beyond that baseline;
21 further contradictions are found by full affine elimination. Both sets
share the same 144 input profiles, so a fresh RNG seed alone is not a test
of generalization to new difference families.

The later 14–16-circuit rulebook resolves the entire affine gate, not just
learned examples. Its theorem and reported ~42× local Python timing are
already covered in research 02. **Fresh finite replay here:** all eight row
libraries and their enumerated minimal circuits match the saved certificate
exactly. Their ranks are `[111,112,112,111,112,111,111,112]` and circuit counts
`[15,14,14,16,14,15,15,14]`. This repeats a supporting finite computation,
not a new full-width source-to-model audit or a new activity lower bound.

### 15.5 Campaign records are history, not the current theorem frontier

Recounted from the supplied files, rather than inferring status from old prose:

| Historical invocation | Recorded cases | UNSAT | Unknown | Unrecorded of 256 |
|---|---:|---:|---:|---:|
| `day_campaign` | 18 | 0 | 18 | 238 |
| `backward_joint17_campaign` | 134 | 104 | 30 | 122 |
| `backward_joint17_unlimited` | 134 | 107 | 27 | 122 |

All have invocation phase `finished`; none is an all-256-case closure.
The unlimited runner can inherit earlier results, so these counts must not
be added as independent exclusions. Their old H159 `[5,1]` target is now
superseded by research 08's all-family `A1=5 ⇒ A2≥4`. Research 07 supplies
the current 16/19/21 compositional floors under its stated premises. No old
launcher was resumed and no unknown result was converted to UNSAT.

### 15.6 Legacy encoding warnings and architecture corrections

The historical workspace review reports two bugs in the specific old external
`/home/user/sol/1.py`: signed bit-vector comparison in a lookup tree and
arithmetic right shift in a purported rotation. Its examples are byte `0x80`
misrouted under an identity-table test and rotation of `0x8000000000000000`
by one yielding all ones instead of one. This review **did not rerun or verify
that external historical script**. Preserve the warning as a reason to use
unsigned comparisons/logical shifts and source controls when reusing it;
it says nothing by itself about other audited models or the user's long run.

The corrected `VISUALS.md` is also useful documentation: Pressure consists
of two independent chains per four-word column; Theta injects neighboring
column parities; Butterfly's sequential updates remain bit-linear; exact
rate-multiple messages still need their padding-only block; native-byte
serialization is little-endian-specific. The source guide records 32
instrumented hash-boundary checks and all 256 SHAKE-derived constants.
These are inherited implementation checks, not new security claims. Both
original and corrected guide versions are preserved.

Several scripts contain absolute `/home/user/codex` or `/home/user/sol` paths.
The snapshot is a provenance archive, not a fully relocated runtime package.
The new [bounded replay helper](reproduce/codex_review/replay_checks.py) invokes
only the exact support and finite-library calculations and writes outside the
snapshot. Other campaigns require a separately reviewed working copy before
execution. No permutation source or earlier theorem ledger was changed.


## 16. NOTE-015: replayed H159 four-cell [6,1] exclusion

**Imported and replayed 2026-11-14. Evidence status:** source-pinned,
computer-assisted restricted-family certificate, with successful source-derived
regeneration and two arithmetic checker replays. The evidence archive arrived
after the initial document import, resolving the earlier missing-evidence
limitation. All 22 archive manifest entries verified. Six regenerated evidence
files, including the complete serialized affine cases, matched the archive
byte for byte. Both addition checkers reproduced zero four-bit survivors.
This is a replay of the supplied proof pipeline, not an independently rebuilt
model or proof-assistant verification.

Full original material is preserved in
[the NOTE-015 proof](reproduce/note_015/KRAKKEN_NOTE_015_H159_FOUR_CELL_61_EXCLUSION.md),
[results JSON](reproduce/note_015/KRAKKEN_NOTE_015_RESULTS.json), and
[NEW_THEOREMS.md](reproduce/note_015/NEW_THEOREMS.md), with
[provenance and availability notes](reproduce/note_015/README.md).
The first 344 lines of the latter exactly duplicate research 05; only NOTE-015
is new. The source SHA-256 values in the proof and JSON match the current
`krakken.c` and `krakken.h`.

### 16.1 Statement and scope

For distinct valid exactly 159-byte messages (fixed padding byte `0x86`, zero
initial capacity), let `A_r` count active byte-level Abyssal S-box calls in
complete round `r`. NOTE-015 reports that, when the pre-Chi1 difference occupies
exactly four aligned serial-Chi cells,

> `A1 = 6 => A2 >= 2`.

The claimed scope is all six nonzero difference lines in the archived H159
four-cell classification, for every admissible base-message pair. Combined
with their established `A1 >= 6` and the universal adjacent-round bound
`A_r + A_(r+1) >= 4`, this gives **`A1+A2 >= 8` and eight-round total >= 20
for these six lines**. Indeed, `A1=6` uses the new exclusion; `A1>=7` uses
`A2>=1` by bijectivity. In either case, the remaining disjoint pairs
`(A3,A4)`, `(A5,A6)`, `(A7,A8)` contribute at least 12.

This is an activity count, not 20 bits of security. Five- and six-cell
pre-Chi1 supports with `A1=6` are not excluded by this result. The existing
unrestricted eight-round floor **16**, general H159 floor **19**, and H159
`A1=5` floor **21** (22 for the previously identified special difference)
remain unchanged under their existing premises. No attained minimum,
differential-hull probability, or collision/preimage security bound follows.

### 16.2 Coordinates and proof mechanism

The document gives the six supports, indexed by `q=2,3,4,5,6,7`, as
`(0,1,q), (1,1,(q+3)%8), (2,1,(q+5)%8), (3,1,q)` in serial-cell coordinates
`(p,y,q)`. A cell pairs byte `(8p+y,q)` with `(8p+4+y,(q+4)%8)`.
Their aligned input byte differences, in increasing `p`, are
`(6E,04), (00,5A), (05,20), (10,03)` (hexadecimal).
The reported local DDT entries for silencing each second serial S-box are
`(0,2,0,2)`. Thus `A1=6` forces exactly the first and third cells to be
double-active and fixes two first-output differences to `5A` and `03`.
Four post-Chi1 output bytes remain variable.

The proof uses the carry-free bit-zero equations of each Pressure branch:
`delta A[0] = delta a[0] XOR delta c[0] XOR delta c[17]` and
`delta C[0] = delta a[0] XOR delta c[17]`, derived from
`A=a+(c XOR (c>>17))` and `C=c+(A XOR (A<<31))` modulo `2^64`.
After undoing output rotations these give 32 base-independent linear
constraints. They connect the four source output bytes to each candidate
single-active Chi2 cell through the intervening invertible linear maps.

A single-active Chi2 cell has 32,640 possible nonzero input differences:
255 of form `(t,t)` and `255*127` of form `(dx XOR du,du)` with nonzero
`dx` and supported first-S-box difference `du`. Linear elimination is
followed by exact local serial-Chi DDT support, then necessary low-bit
modular-addition support tests for all 32 Pressure additions. Allowing local
choices and addition bases independently enlarges the feasible set; it does
not assume independence of actual message pairs. Emptiness of that relaxed
set would therefore exclude the actual pairs as well.

### 16.3 Reproduced finite evidence and assurance boundary

| Stage | Reproduced count |
|---|---:|
| Four-cell supports searched during coordinate recovery | 10,668,000 |
| Families / Chi2 sites per family | 6 / 128 |
| Family-site combinations excluded by the linear projection | 754 / 768 |
| Remaining sites / target difference values | 14 / 78 |
| Enumerated affine assignments (dimensions 14–16) | 2,310,144 |
| Assignments passing local Chi1 DDT support | 117,579 |
| Surviving all addition tests at width 1 | 117,579 |
| At width 2 | 1,284 |
| At width 3 | 24 |
| At width 4 | **0** |

These counts were reproduced from the supplied source-derived pipeline on
2026-11-14. The four-state carry-pair automaton and exhaustive four-bit addition
truth-table checker agreed. Both consume the same serialized affine enumeration;
rebuilding that enumeration byte for byte strengthens reproducibility but does
not constitute an independently implemented source-to-model proof. The fresh
1,000 original-C Pressure pair controls also passed, as did the deterministic
100 Pressure-pair and 100 linear forward/inverse controls invoked by the model
module. Sampled controls are checks, not exhaustive equivalence proofs.

### 16.4 Preserved package, replay and portability fix

- [Original evidence ZIP](reproduce/note_015/KRAKKEN_NOTE_015_EVIDENCE.zip)
  (SHA-256 `5b1c99de05b38818d40bdf3fa21cf24f8881b5126290368b4a2b4e7801c4d671`).
- [Verification record](reproduce/note_015/VERIFICATION.json), including hashes
  for all six byte-identical regenerated artifacts.
- [Working replay instructions](reproduce/note_015/README.md) and
  [path-only patch](reproduce/note_015/relocation.patch).
- [Regenerated arithmetic/control replay log](reproduce/note_015/replay/regenerated_checks.stdout.log),
  [carry-checker log](reproduce/note_015/replay/add_carry4.log), and
  [truth-table-checker log](reproduce/note_015/replay/add_independent4.log).

The original ZIP and extracted archive remain unchanged. The working copy fixes
three hardcoded `/mnt/data` paths in the coordinate-recovery script to resolve
relative to the script. The initial regeneration attempt stopped at the NumPy
import because system Python lacks NumPy; the DDT and serialization stages were
then completed using `~/venv/krakken/bin/python3`, followed by both arithmetic
checkers. No mathematical code was changed. The README supplies a full rerun
command using that environment from the outset.

No long-running solver or previous exclusion campaign was restarted. The next
research target remains the five-/six-cell `A1=6` families; NOTE-015 does not
settle them or improve the general H159 eight-round floor of 19.


## 17. Bounds workspace review — additional fixed-family evidence (2026-11-14)

Reviewed all 48 files in `/home/user/bounds` (9,395,275 bytes), including seven
Markdown documents, solver scripts, finite reports, original scalar sources,
and historical Python caches. Preserved the complete directory in
[the bounds snapshot](reproduce/bounds_review/snapshot/README.md), with
[hash manifest](reproduce/bounds_review/manifest.json),
[review checks](reproduce/bounds_review/REVIEW_CHECKS.json), and
[reproduction instructions](reproduce/bounds_review/README.md).
All available report source pins match their supplied files; scalar C/H match
the project's original source. Historical caches are preserved only as records.

### 17.1 Additional family-specific A2>=5 report and eight-round corollary

The saved attaining-witness input difference is exactly **family ID 18** in
`krakken_research/a2_activity/family_witnesses.json` and zero-based group index
18 in `family_gates.json` (the **19th family**, whose existing gate has 87
equations). It is distinct from research 07's special `delta_id=1`, family 4.
Use the exact delta below to avoid confusing identifiers from different lists:

```text
a000000000000000a000000000000000a000000000000000a000000000000000bd000000000000001d00000000000000bd00000000000000bd0000000000000034000000000000008900000000000000340000000000000034000000000000005e000000000000803a000000000000805e000000000000805e0000000000008032000000000000003200000000000000320000000000000032000000000000
```

[ROUND2_A2_FIVE_ATTEMPT.md](reproduce/bounds_review/snapshot/ROUND2_A2_FIVE_ATTEMPT.md)
and [the saved Z3 report](reproduce/bounds_review/snapshot/krakken_a15_witness_a2_five_z3.json)
record **UNSAT** for all endpoints on at most four pre-Chi2 cells, for this
fixed difference conditioned on `A1=5`. The model permits arbitrary values
on those cells, imposes 32 carry-free Pressure equations, all 16 exact local
low-two-bit tables, and lazily adds necessary full-word addition identities.
The fixed five-cell source has nonzero first-call input differences in every
cell; `A1=5` silences all second calls and fixes the post-Chi1 difference.
Thus UNSAT of the necessary-condition relaxation implies **A2>=5** for every
valid H159 base in this fixed-difference conditioned class.

**Evidence status:** inherited source-pinned solver result, with model and
record inspection in this review; the multi-hour SMT proof was **not rerun**,
and no independently checkable UNSAT proof object accompanies the JSON.
Its 16,787.754-second run records three checks (`sat,sat,unsat`), two synthetic
candidates violating 347 and 261 full-word gates, and 64 necessary cuts. The
separate four-cell screen reports 10,668,000 supports and 130,087 passing its
bit-zero relaxation. These counts are inherited, not fresh measurements.

Under this archived UNSAT result and the established universal adjacent-round
activity exclusions, the analytic corollary is

> **For this fixed difference, A1=5 implies sum(A1..A8)>=22.**

Proof: `A1+A2>=10`; the disjoint pairs `(A3,A4)`, `(A5,A6)`, `(A7,A8)` each
contribute at least four. This is research 07's `NEW-BND-007` with `k=5`.
It adds a second explicitly identified family to the family-specific 22-call
register, with the solver-assurance qualification above. It does not improve
the general H159 floor 19, the all-family `A1=5` floor 21, or NOTE-015's
separate four-cell-family floor 20. No A2=5 attaining pair is established.
Activity counts alone do not establish security bits or trail probabilities.

### 17.2 Finite predecessor and new bounded replay

The folder supplies a useful staged, solver-free predecessor proof for this
same fixed delta:

1. All 128 one-cell and 8,128 two-cell Chi2 supports are excluded by exact
   Pressure bit-zero constraints.
2. All 341,376 three-cell supports are scanned; 662 pass that screen.
3. Exact low-two-bit feasibility leaves three supports, with 67,072 affine
   endpoint completions (1,024 + 512 + 65,536).
4. No completion passes the necessary full-word Pressure identities. Together
   these steps give `A1=5 => A2>=4` for this fixed difference.

The saved independent audit uses an original-C inverse prefix with the opposite
pivot order, direct local transition enumeration, and original-C Pressure
controls. Its full 341,376-support audit was not rerun here. This review **did
rerun the final finite completion stage**, using the original supplied code in
a working copy: all **67,072** completions were examined and **zero** survived.
See [fresh full-gate log](reproduce/bounds_review/replay/fullgate_replay.log).
This replay consumes the saved earlier-stage reports; it is not a new replay
of the entire support scan. Research 08 already proves A2>=4 for all 21
families, so the predecessor adds an alternative proof route and reproduction
materials rather than a stronger universal theorem.

### 17.3 Saved empirical witness and unresolved searches

| Record | Saved outcome | Research interpretation |
|---|---|---|
| Conditional sampler, three fixed differences | 3,188,611 pairs, all A1=5; smallest A2=246 | Empirical coverage; one actual attaining pair |
| Exact message-pair A1=5,A2=5 search | Interrupted at 6,704.424 s | No SAT witness or UNSAT conclusion |
| Relaxed search to prove A2>=6 | Unknown/canceled at 33,316.926 s; three synthetic candidates, 96 cuts | No A2>=6 theorem |
| Global A2 minimization through SCIP | User interruption; dual bound 1; saved actual upper bound 246 | Global A2 minimum unresolved |

The conditional sampler's histogram sums exactly to 3,188,611. This review
compiled the supplied unchanged C and **replayed its saved 159-byte pair**,
confirming the input XOR difference and actual activity **[5,246]**. The full
saved histogram and messages remain in
[the sampling JSON](reproduce/bounds_review/snapshot/krakken_a15_a2_sampling.json).
Research 08 already has a better actual upper bound **245** for the conditional
global minimum, so the historical 246 does not replace it. Neither sample
minima nor synthetic endpoints prove an optimum or an attack lower bound.
The global report's lower-bound label refers only to the trivial floor 1;
it is not a completed global optimization certificate.

### 17.4 Scope separation and reusable methodology

The README and VISUALS also describe `krakken_no_mds_scip_pulp_v4_unlimited.py`.
That program intentionally removes MDS/Tentacle, Butterfly/XRBD and Pressure;
its Theta/Rho/Pi/Chi/Iota/Ink model describes a **modified permutation**.
It supports valid159 or unrestricted states, restricted message-difference
subspaces, and iterative local DDT refinement with optional source replay.
Its geometry self-tests or exact modified-round results must not be used as
full production-round bounds. No result JSON for a newly completed modified
variant solve is present here. The separate `krakken_sponge_two_round_scip.py`
and endpoint work above include the production diffusion/Pressure setting
with explicitly documented relaxations.

The useful transferable technique is to fix a rare first-round activity
class so its post-Chi difference becomes deterministic, pull sparse round-two
endpoints backward through invertible linear layers, then progressively add
carry-free, low-bit and full-word necessary arithmetic conditions. Empty
relaxations exclude real pairs without independence assumptions; surviving
relaxations require actual base-message feasibility. This technique complements
the existing all-family classification and NOTE-015; their quantified scopes
must remain explicit. This review resumed no unlimited solver or sampler.

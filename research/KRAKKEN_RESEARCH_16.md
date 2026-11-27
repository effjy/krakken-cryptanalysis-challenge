# Krakken research 16 — Differential packing and higher-order exclusions beyond the enumerated directions

**26 November 2026 — initial continuation.** Scope: the original indexed eight-round Krakken hash on H159 (exactly 159 message bytes, padding byte 0x86 and zero initial capacity). This ledger develops analytic corollaries of the actual-function computational certificates in Research 15, and a population packing inequality. No C implementation was supplied in this turn; no hash evaluation, SAT query, old campaign, or source-level verification was performed. The deterministic theorems inherit the correctness of the specified earlier certificates. They are not newly source-replayed theorems or an external peer review.

## 16.1 — Research frontier and duplicate-work screen

All fifteen uploaded ledger texts were loaded and indexed by headings. Relevant theorem statements, current-status entries and proof passages were examined, with particular attention to the five outstanding questions. This is a targeted literature/ledger screen, not a full proof-by-proof audit of the historical archive. Original files are unchanged. The input manifest in the companion package identifies the exact ledger snapshots.

| Research | Prior results or methods not to duplicate |
|---|---|
| 01 | Local Chi DDT/BCT and inversion structure; first-block activity and differential fibers; [1,1]/[1,2] exclusions; Pressure equations and deterministic translations; integral, symmetry and nonlinear-label results. |
| 02 | Completed [2,1] campaign; restricted complete-round probabilities; reduced-width counterexamples; eight-round algebraic and finite 22-dimensional cube differential certificates. |
| 03 | Two-round endpoint parity bounds; Fourier/autocorrelation consequences of restricted linear-hull bounds; first-round H159 digest balance. |
| 04 | Exact finite-family digest injectivity; reduced-round truncated collision replay; statistical collision ceiling. |
| 05 | Ideal-sponge conditional benchmarks and original-scalar randomness screen. |
| 06 | NIST STS experiment record, not official NIST certification. |
| 07 | Abstract activity composition and low-total boundary vectors; some historical floors superseded. |
| 08 | Dependence-safe single-cut trace bounds; first-Chi coordinate independence; 13-dimensional Sidon family; all 1,272 unit-message difference statistical bounds; further complete-round and conditioned-family results. |
| 09 | Consolidation, attack-side observations, failed proof shortcuts and completed campaign status. |
| 10 | Exact first-round autocorrelation, period spaces, low-dimensional Fourier certificates and conditioned restrictions. |
| 11 | Rebound, rotational and subspace attack constructions; completed H159 [6,1] campaign; all 21 minimum-first-round families exclude A2 <= 4. |
| 12 | XRBD exact structures; special conditional activity; exact mass 2^-35 of A1=5 for each classified difference; affine population/fiber proof. |
| 13 | Exchange squares, Yoyo, rotational/DDT hybrids and full-round rebound-model audit. |
| 14 | Uniform-H159 collision/point ceilings; 21 minimum-activity difference populations and their conditional experiments; split predictors and adaptive-parity selection. |
| 15 | Four-wise independent probability certificate, fixed-difference sampling and exact grids; 255-direction first-order and 651-plane second-order common-grid certificates. |

The historical records contain actual reduced-round/local structures and partial attack-side witnesses (e.g. Research 01's perfect local boomerang family and Research 11's rebound partial survivors), not solely negative attack results. These are not production-hash breaks and must not be discarded in a security assessment.

Current activity floors: **16 unrestricted, 20 H159, 22 H159 conditioned on A1=5**. The [2,1] campaign (8,355,840 configurations) and H159 [6,1] campaign (5,423,611,200 supports) are recorded as completed; do not restart them. The abstract H159 20-call frontier after closing [6,1] consists of the four [6,2] sequences and one [7,1] sequence in Research 07 §14. Closing [6,2] and [7,1] at the actual H159 first window suffices for a 21-call floor; excluding only their low-total continuations could also suffice. This is inherited planning, not a new activity result.

## 16.2 — Result board

| ID | New conclusion | Evidence class |
|---|---|---|
| R16-GRID-ALLDIR-001 | All 262,143 nonzero directions on the Research 15 18-dimensional grid F: maximum eight-round digest differential point probability <= 2^-8; for the original 255 directions exactly 2^-17 | Analytic corollary of exact finite census; 261,888 newly covered directions |
| R16-GRID-PLANEZERO-002 | All 33,401,515 two-dimensional planes in F meeting W nontrivially: zero quartet XOR impossible everywhere on F | Analytic corollary; includes 33,400,864 beyond the original 651 U planes |
| R16-GRID-PLANEPOINT-003 | All 8,256,171 two-dimensional planes meeting U nontrivially: maximum second-order point probability <= 2^-5; for the 651 planes contained in U exactly 2^-16 | Analytic corollary; 8,255,520 additional planes |
| R16-GRID-THIRDZERO-004 | All 42,654,915 three-dimensional subspaces of F meeting U in at least a plane: zero eight-message XOR impossible everywhere on F | Analytic corollary of second-order census |
| R16-POP-PACK-005 | Over the entire uniform H159 population, in every coset of W in the difference space, at most 16 offsets can have maximum eight-round derivative probability >= 2^-4; more thresholds below | Analytic corollary of statistical population certificate; inherits its fixed-rule confidence >99.22% |
| R16-SIDON-PLANE-006 | Prior Sidon certificates exclude identically zero second derivatives on full H159 for all 2,794,155 planes of the 12D family (R2/R8), and 11,180,715 planes of the 13D family (R8) | Explicit counting corollary, not a new Sidon computation |

No result claims an improved unrestricted activity minimum, universal all-H159 point ceiling, or overall attack-work exponent. All finite-grid probabilities concern the actual endpoint (including every contributing trail), not a prescribed internal characteristic.

## 16.3 — Premises and notation

Let V=GF(2)^1272, H=H_8:V -> GF(2)^256, and Y be its first 64 output bits. All XORs below are in characteristic two. Define D_d f(x)=f(x) XOR f(x XOR d). For a linear subspace P define D_P f(x)=XOR_(v in P) f(x XOR v). In particular for a plane P=span(a,b), D_P=D_a D_b. These difference operators commute. D_P is constant on each coset x+P.

Use exactly the Research 15 §§15.12–15.14 spaces: W has basis w_j toggling bit j in bytes (0,19,39,59,79,99,119,158) for j=0..7. U is spanned by w_0..w_5. F contains W and ten extra coordinate bits: all eight bits of byte 70 and the two low bits of byte 71. Thus dim F=18, dim W=8, dim U=6.

Inherited deterministic premise A (R15-GRID-DP-013): for every w in W\{0}, D_w Y is nonzero and injective on F/span(w), i.e. two bases have equal derivative exactly if their difference lies in span(w).

Inherited deterministic premise B (R15-GRID-QDP-014): for every plane P contained in U, D_P Y is nonzero and injective on F/P.

Inherited statistical premise C (R15-SUBSPACE-DP-011, §15.12): for all nonzero w in W and every prefix target t, Pr_uniform V[D_w Y=t] < 2^-13. The reported fixed-rule confidence is >99.22% jointly with the other ceilings of that panel. The primary 255-direction design was recorded before sampling. The following population corollary uses only this primary point ceiling, not independence of shifted messages, secondary-plane tests or additional sample reuse. All events in that corollary are evaluated on a uniform base in V, not F.

Use of the 64-bit prefix is deliberate: inequality or nonzeroness in these bits implies inequality or nonzeroness of the full 256-bit digest and also of the full 2048-bit endpoint on the same padded messages.

## 16.4 — R16-GRID-ALLDIR-001: extend the endpoint bound to every grid direction

**Theorem.** For every d in F\{0} and every target b, under a uniform base x in F,

    Pr[D_d H(x)=b] <= 2^-8.

For the 255 directions inside W the sharper exact maximum 2^-17 remains. For all 261,888 directions outside W the displayed 2^-8 is a newly derived upper bound, not claimed attained. The same bound holds for Y and the complete output state.

**Proof.** Take d outside W. If D_d Y(x)=D_d Y(x+w) for some nonzero w in W, commuting derivatives gives

    0 = D_w D_d Y(x) = D_d D_w Y(x),

so D_w Y(x)=D_w Y(x+d). Premise A forces d in span(w), contrary to d outside W. Therefore D_d Y restricted to any coset of W in F is injective. For any target, at most one base in each of the 2^(18-8)=1024 W-cosets attains it. Divide by 2^18 to obtain 2^-8. For d in W\{0}, premise A gives the inherited 2^-17 directly. Refinement gives the full output conclusions. QED.

In particular every nonzero grid direction has at least 256 attainable derivative values. For d outside W a collision with a fixed d is not excluded, but its density on F is <= 1/256. This proof extends the quantifier to every direction of this F without hashing any new messages or enumerating the 261,888 extra directions. It does not quantify directions outside F. The stronger 22D restricted projection certificates in Research 02 concern a different family; this is not a claim of a record-sized input space.

## 16.5 — R16-GRID-PLANEZERO-002: exclude zero four-message XORs on 33 million plane directions

Let P be any two-dimensional subspace of F with P intersect W nontrivially. Choose nonzero w in P intersect W and another d in P outside span(w). If D_P Y(x)=0 then D_w Y(x)=D_w Y(x+d), contradicting premise A. Thus D_P Y, D_P H and the full-state quartet XOR are nonzero at every x in F.

Count planes entirely inside W by the binary Gaussian binomial [8 choose 2]_2=10,795. For planes meeting W in exactly a line, there are 255 choices of that line and (2^18-2^8)/2 choices of the outside vector modulo the line. Total:

    10,795 + 255*(262,144-256)/2 = 33,401,515.

These are plane directions, not independently sampled trials. Each has 2^16 affine cosets of bases in F; all are covered by the proof. The result is not a Sidon theorem for F: arbitrary four-message XORs, and planes not meeting W, are not covered.

## 16.6 — R16-GRID-PLANEPOINT-003: bound second-order endpoint multiplicities on 8.25 million planes

**Theorem.** If P is any plane in F with nontrivial intersection with U, then for uniform x in F,

    max_b Pr[D_P H(x)=b] <= 2^-5,

and the zero target is impossible. The same holds for Y and full-state outputs. For P contained in U, the sharper exact maximum is 2^-16.

**Proof.** Only the case P intersect U=span(a), a nonzero, needs analysis. Write P=span(a,d), d outside U. If two bases in the same U-coset, x and x+e, have equal D_P Y and e is outside span(a), then

    0 = D_e D_a D_d Y(x) = D_d D_Q Y(x),
    Q=span(a,e) contained in U.

Premise B forces d in Q, impossible. Consequently within each U-coset any target has at most two preimages, separated by a (the inherent invariance). There are 2^12 such cosets, so the total number of bases attaining a target is at most 2^13 of 2^18, yielding 2^-5. Zero exclusion follows from §16.5 because U is a subspace of W. QED.

Number of planes:

    [6 choose 2]_2 + (2^6-1)*(2^18-2^6)/2
    = 651 + 8,255,520 = 8,256,171.

Unlike §16.5, this also bounds nonzero target multiplicities. No independence of four related messages or of internal S-box calls is asserted.

## 16.7 — R16-GRID-THIRDZERO-004: deterministic eight-message higher-order exclusions

Let T be any three-dimensional subspace of F such that dim(T intersect U)>=2. Choose a plane P inside T intersect U, and t in T outside P. Then D_T Y(x)=D_P Y(x) XOR D_P Y(x+t). Premise B makes this nonzero for every x in F because t is outside P. The same holds for the complete digest and full state. There is no identically zero third derivative on full H159 for those T, since every grid base supplies a counterexample to that identity.

The number of such three-dimensional subspaces is

    [6 choose 3]_2 + [6 choose 2]_2*(2^18-2^6)/4
    = 1,395 + 651*65,520
    = 42,654,915.

The first term counts spaces inside U; the second chooses their exact two-dimensional intersection with U and one outside vector modulo that plane. Each space has 2^15 affine cosets in F. This is a new order of derivative exclusion from the inherited census; it is not a claim that arbitrary eight-message XORs are nonzero, nor a bound on all third-order targets or their probability on V.

## 16.8 — R16-POP-PACK-005: packing of high-probability directions over the entire H159 domain

The earlier deterministic grid arguments do not bound the entire V. Here is a different inference that does use all H159 bases, under premise C. Define

    M(d)=max_b Pr_uniform V[D_d Y(x)=b].

Fix any coset c+W in V and any threshold p>sqrt(epsilon), where epsilon=2^-13. Suppose k distinct offsets d_i in that coset satisfy M(d_i)>=p. Choose one maximizing target b_i per offset. Let E_i={x:D_(d_i)Y(x)=b_i}. The offsets and targets may be chosen arbitrarily as population parameters; they are fixed before drawing the base x in this proof.

If i!=j, membership in E_i intersect E_j implies

    D_(d_i XOR d_j) Y(x XOR d_i)=b_i XOR b_j.

Since d_i XOR d_j is nonzero in W, translation of a uniform base and premise C give Pr[E_i intersect E_j]<epsilon. No independence of E_i is needed.

Let Z=sum_i 1_E_i and q=E[Z]/k>=p. For k>=2,

    (kq)^2 <= E[Z^2] < kq + k(k-1)*epsilon,
    k*(q^2-epsilon) < q-epsilon.

On q>sqrt(epsilon), the function (q-epsilon)/(q^2-epsilon) decreases: its derivative is -(q^2-2q*epsilon+epsilon)/(q^2-epsilon)^2<0. Thus

    k < (p-epsilon)/(p^2-epsilon)    (k>=2).

The trivial k<=1 case is always treated separately. This inequality covers every coset simultaneously, with no further confidence loss beyond premise C. The reason is that it is a deterministic implication for the entire collection of population distributions once C holds, not a new set of sampled tests. The same cap applies to the number of offsets whose full-digest or full-state maximum reaches p, because a full-output target event implies a prefix-target event.

| Threshold p | Maximum offsets per 256-element coset |
|---|---:|
| 1/2 | 2 |
| 1/4 | 4 |
| 1/8 | 8 |
| 1/16 | 16 |
| 1/32 | 36 |
| 1/64 | 126 |

In particular, among all 2^1272 directions (including zero), at most 16*2^1264=2^1268 directions can have a maximum full-digest DP >=2^-4. This is at most a fraction 1/16 of all directions. More significantly, the same cap holds inside **every** coset of the specified W, even one whose location was never sampled as an input-difference family. For any fixed target, an alternative elementary bound follows from pairwise intersection, but the result above allows a different maximizing target for each offset. The all-zero offset is included and consumes one slot in its own coset; it is never a nontrivial collision.

**Limits.** This is a distribution-of-maximum bound, not a maximum bound. An isolated highly probable differential is compatible with it. It does not identify bad directions, prove their existence, or control adaptively chosen individual bases. It is a new analytic population constraint, not independent statistical confirmation. The inherited confidence refers to a fixed reporting rule under the OS-random anchor model, not a probability that Krakken is secure.

## 16.9 — R16-SIDON-PLANE-006 and a proof limitation

Research 15 §15.6 proves the 12D endpoint family is Sidon at R2 and R8. Research 08 NOTE-006 proves a different 13D affine family is Sidon at R8. For any independent a,b in the associated direction space, all four points in a plane coset are distinct, so the quartet XOR is nonzero by the Sidon property. Hence the corresponding second derivative is not identically zero on V. The exact plane counts are [12 choose 2]_2=2,794,155 and [13 choose 2]_2=11,180,715 respectively. The counts are separate; no disjointness across the two families is claimed. This is a recorded analytic counting consequence of older results, not a new hash experiment.

The verification script also constructs a small *non-Krakken* countermodel that satisfies analogues of both grid premises A/B but contains a digest collision along an untested direction outside W. It uses distinct basis-vector labels except for one repeated label across W-cosets. The script verifies the inherited properties and the collision by exact enumeration. Thus the premises alone do not justify extending the zero-first-derivative exclusion to arbitrary directions. No attack on Krakken is inferred from that toy model.

## 16.10 — Remaining research: concrete next steps for the five original questions

1. **Universal differential endpoint ceiling.** The first grid theorem extends to all directions of one F, and the packing theorem constrains arbitrary offsets over V but does not bound the worst offset. For an unrestricted full-state theorem, use uniform 2048-bit states, not H159. A source-specific continuation should test whether the derivative-coset injection argument can be certified over larger domains or whether structural kernels supply a counterexample. Do not extrapolate the grid theorem to all V or to all 2048-bit states.
2. **Worst-case characteristic/hull bound.** Research 08 NOTE-001 already gives the safe maximum-single-round activity cut, not the sum of round exponents. Research 01/08 supply exact local probabilities. A new source-based project should tackle the remaining H159 [6,2] and [7,1] low-total continuations or unrestricted 16-call abstract boundary. The necessary-condition exclusion must be complete and distinguish solver UNSAT certificates from timeouts. A hull theorem additionally needs a certified count or bound of compatible internal traces, or a direct endpoint count. No activity-to-security multiplication is licensed.
3. **128-bit collision security.** The ideal-permutation sponge result is already documented in Research 05/15. Work on actual adversarial shortcuts; distinguish generic ideal-model bounds from concrete lower bounds. None of the current results proves 2^128 attack cost.
4. **256-bit preimage security.** Analyze the actual inverse on partially specified output states and the padded-message reachability constraint. Full-state invertibility is not a proof of one-wayness after digest truncation. No 2^256 concrete lower bound is obtained here.
5. **Rare and selected populations.** Research 12 shows the 21 A1=5 qualifying populations are affine and each has mass 2^-35; Research 14 already samples them and investigates selected branches. Their rarity does not make them hard to construct. Prefer genuinely new conditioned properties, e.g. excluding the remaining low-total continuations, certifying additional projected endpoint bounds on a precisely defined conditioned population, and explicitly investigating negative findings. A population average cannot replace adversarially selected bases.

**Inputs required for a fresh source-level campaign:** the unchanged krakken.c, krakken.h, krakken_multi.c and the evidence directories for Research 07/11/12 (activity models, prefix matrices, solver/support scripts), and Research 15 (grid archive or collector and population evidence). Historical source fingerprints are recorded in Research 15 §15.15, but those fingerprints have not been reverified here. Before an expensive search, pin source identity, freeze the design, and retain reproducible SAT witnesses, exclusions and unresolved cases. Do not modify the primitive to make a proof easier.

## 16.11 — Reproduction and assurance

The companion ZIP includes this ledger, input snapshot hashes and a standard-library Python checker. Run `python3 verify.py > actual.json` and compare with `results.json`. The checker verifies Gaussian-binomial counts by independent recurrences and intersection formulas, exhaustively checks counts and derivative identities on a small illustrative model, verifies the limitation countermodel, and computes the packing caps by exact rational arithmetic. It does **not** rerun Krakken or independently establish the inherited computational premises. The proof of the new implications is given in the text above; no random-permutation or cross-round independence assumptions are used in the deterministic results. The statistical corollary inherits only the stated population certificate.

**Conclusion:** the new results broaden the quantifiers of existing exact certificates without redundant hashing, provide genuine endpoint constraints (not individual trail probabilities), and give a concrete population-level restriction on clusters of high-probability differentials. The universal chosen-difference bound, worst-case concrete hull bound, and overall collision/preimage security claims remain open.

---

## 16.12 — Source-based continuation (26 November 2026)

The three original source files have now been supplied. Their SHA-256 fingerprints exactly match Research 15 §15.15:

```
4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6  krakken.c
83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c  krakken.h
9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2  krakken_multi.c
```

The earlier §§16.1–16.11 remain the initial analytic continuation and accurately describe its original inputs. This addendum provides actual fresh evaluations and deterministic endpoint certificates, not merely new interpretations of old data. The frozen local designs and code commitments, original sources, full digest archives, per-case results and replay scripts are in `source_continuation/`. The designs were recorded locally before each run; this is not external preregistration.

| Result | Scope and quantifiers | Bound |
|---|---|---|
| R16-GRID14-DP-007 | Eight rounds, all 16,383 nonzero directions on specified 14D subspace J | Exact maximum DP = 2^-13; zero impossible |
| R16-GRID14-DEG-008 | Each such direction, every nonzero digest mask, on full H159 | First-derivative algebraic degree >=10 |
| R16-GRID18-W11-009 | Eight rounds, 2,047 specified directions on original 18D F | Exact maximum DP = 2^-17; zero impossible |
| R16-GRID18-ALLDIR-010 | Every one of 262,143 nonzero directions on F | Maximum DP <= 2^-11, improving §16.4 by factor 8 |
| R16-GRID18-PLANEZERO-011 | All planes in F meeting W11 nontrivially | Zero four-message XOR impossible, 266,906,283 planes |

All results are deterministic computational theorems or analytic consequences of such theorems, conditional on the correct execution of the source and verifiers. The numerical values refer to endpoint differential distributions on explicitly stated finite message families (all contributing internal trails), not bounds for the unrestricted permutation or adversarial attack work.

## 16.13 — Exact all-direction 14D probability and algebraic-degree certificate

Retain the definitions of W and F in §16.3. Define J as the 14-dimensional subspace spanned by W and the six low unit bits of byte 70. In particular J is a subset of the earlier 18D F, and not an independent statistical population. Encode x=0..16383 by putting its low eight bits into W (bit j of byte p_j, p=(0,19,39,59,79,99,119,158)) and x>>8 into byte 70. All other message bits are zero. H(x) is the original eight-round 256-bit digest of the resulting 159-byte message.

All 16,384 digests were obtained using the unchanged public AVX2 hash API; GCC AVX2, Clang AVX2 and GCC scalar recomputed the **complete 256-bit array**, matching every byte. The ordered array `source_continuation/digests.bin` has SHA-256 `a02763bf6a7101f2132f4805aa75a0af5184b3989bf3fb0eab52dcbe3980c0d3`.

For every d=1..16383, let p be its highest set bit and choose all x whose bit p is zero. This gives exactly one representative per unordered pair {x,x XOR d}. For each representative, compute the 256-bit derivative and check equality of the actual low 64 bits, using an open-addressed table with full-key comparisons. The slot hash serves only for indexing; it is not an equality surrogate. Compute the exact vector ANF by a Boolean Möbius transform on the 13 remaining index coordinates, then the GF(2) rank of the degree >=10 coefficient vectors.

| Quantity | Observed result |
|---|---:|
| Nonzero directions | 16,383 |
| Unordered pairs per direction | 8,192 |
| Total pair representatives | 134,209,536 |
| Total zero prefixes | 0 |
| Total repeat excess within directions | 0 |
| Minimum rank of degree >=10 coefficient vectors | 256/256 |

**R16-GRID14-DP-007.** For every nonzero d in J, the first derivative on uniform J takes exactly 8192 distinct nonzero values, each with probability 2^-13. Equality of derivatives on the two orientations of each pair is inherent, and all unordered pairs for that d have distinct 64-bit prefixes. Consequently full digest and full-state derivatives have the same distributional cardinality and point probabilities. This is the smallest possible maximum DP for a function on J in that direction. There are no digest collisions anywhere within J, and every plane in J has nonzero quartet XOR at every base: if D_a D_b H(x)=0 for independent a,b, the derivatives for direction a agree at two different pair cosets, a contradiction. This covers all (16383*16382)/6 = **44,731,051 planes**. These conclusions do not assert global uniqueness of pair XORs across different directions (not a Sidon census).

**R16-GRID14-DEG-008.** For every such d and every nonzero 256-bit output mask beta, the Boolean derivative parity beta·(H(m) XOR H(m XOR d)) has degree at least 10 on full H159. Proof: on the 13-bit quotient there are sum_{k=10..13} C(13,k)=378 possible coefficient vectors of degree >=10. Their rank is 256 for every d. A nonzero mask cannot annihilate all those coefficient vectors, so the restricted derivative has degree >=10. Restriction to an affine subspace cannot increase degree, proving the full-H159 claim. Only 92 monomials have degree >=11, so this particular quotient cannot certify a uniform degree >=11 for all 256-bit masks using this rank test alone. The theorem excludes every exact degree-<=9 polynomial predictor of any nonzero digest derivative parity for those specified differences. It neither bounds approximate prediction nor replaces the prior global degree floor for the undifferentiated hash. The Research 15 degree >=7 result concerns a different 12D family and both R2 and R8; no new R2 claim is made here.

The separately written Python audit reads the full ordered digest archive, enumerates representatives by a different loop, checks actual prefix sets, performs the Möbius transform with a different traversal and uses low rather than high pivots for elimination. All 16 fixed direction cases passed. It also checks completeness of the main case table. The primary all-direction C rank census was not fully repeated in Python. All case rows are retained in `source_continuation/census.csv`.

## 16.14 — Stronger all-direction bound on the original 18D grid

Define W11 = W + span of the three low unit bits of byte 70, dimension 11. Its 2047 nonzero directions include all 255 original W directions. On exactly the earlier F (all eight bits of byte 70 plus two low bits of byte 71 in addition to W), regenerate all 262,144 full digests using the unchanged public hash API. The complete GCC and Clang AVX2 streams matched, and their SHA-256 was exactly `23e6450f921b61cc040961c286597f9ce411fd1992d94dfb072d3ce0063dabd7`, the recorded Research 15 §15.13 commitment. The first 16,384 entries match the full scalar-checked J array byte for byte. No full scalar replay of the remaining F entries was performed.

For each d=1..2047, compare the actual first 64 bits of all 131,072 representative derivative values (same quotient method as above). All cases had 131,072 distinct nonzero values. This is 268,304,384 pair observations, with zero repeats within any case and zero zero prefixes. Of the 2,047 directions, 1,792 were not in Research 15's direct first-order F panel. The count includes the 255 deliberately replayed prior directions as controls; it is not 268 million independent hash evaluations or entirely new observations. The independently written NumPy checker sorts actual prefix XORs for twelve fixed directions and validates all counts and digest commitments. Per-case outputs are retained in `source_continuation/grid.csv`.

**R16-GRID18-W11-009.** For uniform x in F and every nonzero d in W11, the derivative on the complete digest (and on its 64-bit prefix and the full state) is uniform on exactly 2^17 distinct nonzero values. Its maximum DP is exactly 2^-17. Proof: each pair has two orientations; distinct representative prefixes force distinct full outputs.

**R16-GRID18-ALLDIR-010.** For *every* nonzero d in F and every target b,

    Pr_uniform x in F[D_d H(x)=b] <= 2^-11.

For d in W11, the exact 2^-17 bound is stronger. For d outside W11, if D_d Y(x)=D_d Y(x+w) for nonzero w in W11, commutativity implies D_w Y(x)=D_w Y(x+d), contradicting the just-established quotient injection for w because d is not in span(w). Therefore D_d Y is injective on each W11 coset. At most one base per coset, i.e. at most 2^7 bases in F, can yield a fixed target. Divide by 2^18. This improves §16.4's conservative ceiling by a factor 8 for the broad all-direction F statement. The bound need not be attained. It also applies to full-state outputs from these padded messages, not arbitrary unrestricted permutation states.

**R16-GRID18-PLANEZERO-011.** For any plane P within F meeting W11 nontrivially, choose nonzero w in the intersection and d in P outside span(w). If D_P Y(x)=0 then D_w Y(x)=D_w Y(x+d), impossible by R16-GRID18-W11-009. The plane count is [11 choose 2]_2 + (2^11-1)*(2^18-2^11)/2 = **266,906,283**. Each plane has 2^16 cosets, and all have nonzero four-message XOR. This supersedes the narrower count in §16.5, not the different second-order point ceilings in §§16.6–16.7. For full H159 these witnesses rule out an identically zero vector second derivative for the specified planes, not individual zero events outside F. No general Sidon property or cross-plane uniqueness on F follows.

## 16.15 — Reproduction and open boundaries

The source continuation directory contains actual digest bytes, all case counts and ranks, the three source files, two design documents, exact checking code, audit outputs and a SHA-256 manifest. See `source_continuation/README.md` for the two replay commands. No old source or ledger was overwritten. The 14D and 18D pair-observation totals overlap by design and must not be represented as independent tests. The primary 14D census is independently source-evaluated in all three builds, with selected independent rank/count rechecks; the entire 18D grid is verified in two builds with selected independent sort checks and the scalar-verified 14D subset. This is local reproducibility, not external review.

The new work is targeted at the previously suggested larger-family algebraic certificate and the finite-grid all-direction endpoint frontier. It does **not** close [6,2] or [7,1], raise the 20-call global H159 activity floor, establish a worst-case eight-round differential hull on full H159, bound rare A1-conditioned populations further, or prove 128/256-bit adversarial security. The actual support/solver campaign evidence for Research 11 and 12 was not supplied in this turn. For that frontier, the next practical step is to use the existing verified six-cell support scanner, retained eligible-candidate data and endpoint model to avoid repeating billions of completed support classifications. The newly supplied sources are now pinned for such work. No solver campaign is running or claimed complete.

---

## 16.16 — Exact unrestricted first-round degree: 832 (26 November 2026)

**R16-ALG-R1-EXACT832-012.** New computer-assisted exact algebraic theorem, not a statistical inference or a degree-trail upper estimate. Let R0 be the first complete indexed round on the unrestricted 2048-bit input. For each first-updated Pressure word `a ∈ {0,1,4,5,...,28,29}` and each bit `k=0,...,63` before optional rotation, define `j(a,k)=64*((7*a) mod 32)+((k+11+7*(a mod 2)) mod 64)`. Then

    deg(R0_j(a,k)) = 13*(k+1).

These are **1024 distinct coordinates with exact global degrees**. In particular 16 have exact degree **832**, 1008 of these exceed degree 23, and 400 have degree at least 520. The vectorial degree of R0 is at least 832 (upper bound 2047 by bijectivity). The remaining 1024 coordinates from the second addition in each chain have not been assigned exact degrees. The new result is on the unrestricted domain, not the H159 rate plane or full R8; the previous R8 ≥23 coordinate and ≥21 all-mask bounds remain unchanged.

### 16.17 — Proof and reproducibility

The original scalar source SHA-256 commitments from §16.12 match. The linear prefix L=Pi∘Rho∘MDS∘Theta has rank 2048 from all basis columns, independently reproduced; it preserves exact Boolean degrees. In the independent pre-Chi coordinates the 128 serial-Chi cells have disjoint 16-bit variable sets. Local exhaustive ANF finds maximal degrees 7 and 13 in the respective output bytes, with rank 8 of the degree-13 second-byte coefficient vectors. The original C local audit verifies all 65,536 inputs in each cell (8,388,608 comparisons).

For the first Pressure sum U+V, `V=c XOR (c>>17)`, the degree-(k+1) homogeneous part of output bit k>=1 before Chi substitution is `U_0 V_0 product_{i=1}^{k-1}(U_i XOR V_i)`; k=0 is linear. All forms are linear in the post-Chi state via Butterfly. The degree of the substituted coordinate is at most 13(k+1). For each chain the new C producer finds 64 distinct local cells and actual degree-13 vector ANF coefficients q_j whose embedded Butterfly/carry columns `(U0,V0,U1 XOR V1,...,U62 XOR V62)` have full rank 64. For each bit k the first k+1 rows admit a nonsingular minor on k+1 distinct cells (k=0 uses row0 XOR row1). The selected local degree-13 masks concatenate to a specific degree-13(k+1) monomial in pre-Chi variables. Any post-Chi monomial contributing to it must have at least one factor from every selected cell; by the post-Chi upper degree bound, it has exactly one from each and none elsewhere. Its resulting coefficient is therefore exactly the determinant of the selected carry matrix (permanent equals determinant over GF(2)), namely 1. This proves the matching lower bound despite possible cancellations. Affine suffix operations only relocate the coordinate or add a constant.

The package `KRAKKEN_RESEARCH_16_DEGREE832.zip` includes the complete `THEOREM.md` proof, small C producers `degree_exact.c` and `degree_round.c`, an independent Python verifier, source files, replay script, and 1024 explicit monomial certificates. GCC and Clang certificates match byte-for-byte. Python independently checks the rank, local ANF, seven distinct selected degree-13 local coefficients by direct subset XOR, and every selected monomial minor. A separate affine-slice certificate establishes degree k+1 for the same 1024 coordinates on respective 64-dimensional families, with 2048 original full-round multi-direction control cases per compiler. It is a weaker independent construction, not the reason for degree 832. The new evidence does not enumerate 2^832 inputs; the algebraic proof is what avoids that cost.

| Artifact | SHA-256 |
|---|---|
| `exact_certificate.csv` | `53accbdddffa89c8aa88ae2b56cd6fb8d96c023f4969aa30167cff0dc62560cf` |
| `exact_monomials.csv` | `b6919312a3eabfae914adfd844d3bce25d2921fec7f1b4d96fe10ffc7fb28afe` |
| `certificate.txt` | `6f17067274c1b7bac40f0983a474a000d3367af89156c4b7745439216c09b626` |

**Remaining research:** extend exact coefficient certificates to the second Pressure addition, establish unrestricted R2 and R8 bounds beyond current cube certificates, then separately analyze H159 restrictions and general output parities. A high coordinate degree does not imply high minimum parity degree, a particular differential probability, or collision/preimage security. Degrees need not be monotone under composition. No new differential bounds are claimed in this continuation; §§16.1–16.15 remain intact. The prior-work screen targeted Research 01/02 algebraic findings and the Research 16 frontier, not a complete re-audit of all ledgers. No external reproduction or peer review has occurred.

---

## 16.18 — Exact degree 871 and all-parity classification on 1,584 coordinates (26 November 2026)

**R16-ALG-R1-PARITY871-013.** Analytic composition theorem plus independently recomputed finite rank/ANF certificates. Let R0 be the first complete indexed round on the unrestricted 2048-bit input. For each chain `a ∈ {0,1,4,5,...,28,29}`, write `A=U+V`, `V=C XOR (C>>17)`, `D=C+(A XOR (A<<31))`, with additions modulo 2^64. The pre-rotation bit `k` maps to `j_A=64*((7*a) mod 32)+((k+11+7*(a mod 2)) mod 64)` or `j_D=64*((7*(a+2)) mod 32)+((k+11+19*(a mod 2)) mod 64)`. Define J as the union of 1024 A bits (all k=0..63) and 560 D bits (k=0..34 in every chain). Define weights `w(j_A)=13*(k+1)`, `w(j_D)=13,26` for k=0,1 and `13*(2*k-1)` for k=2..34. Then for **every nonzero beta supported in J**,

    deg(beta dot R0) = max_{j: beta_j=1} w(j).

This strengthens theorem -012: 1,584 distinct coordinates (77.34375% of the state) have exact degrees and **all 2^1584-1 nonzero parities** supported there have exact degree given by the maximum selected weight. In particular 16 D coordinates have exact degree **871**, 16 have exact degree **845**, and the 16 A coordinates at degree 832 remain certified. 1,552 covered coordinates have degree >23. The unrestricted vectorial R0 degree is **at least 871**, at most 2047; it is not claimed to equal 871. Minimum degree over nonzero J-supported masks is exactly 13; this is not a minimum over the entire output space.

### 16.19 — Proof: second addition, shift ceiling, and simultaneous noncancellation

Before the shift boundary the D word equals the triple sum U+V+C. The bit-k ANF in independent formal bits is obtained by taking the coefficient of z^(2^k) in the product of (1+x_i z^(2^i)) over the three words (Lucas' identity). The maximum number of selected variables for k>=2 is 2k-1. For k>=3 the unique maximum count pattern is 2 at bit 0, 3 at bit 1, 2 each at bits 2..k-2, and 0 at bits k-1,k. The highest-degree homogeneous form factors into `(U0+V0)(U0+C0) U1 V1 C1 product_{i=2}^{k-2}(Ui+Vi)(Ui+Ci)` in the square-free associated graded ring; the smaller k=0,1,2 forms are detailed in THEOREM.md. For k=31..34, expand shifted occurrences of A in the same generating function. For nonempty shifted mask h, put t=h>>31 and let l be a submask of t accounting for new A variables. The A monomial mask a contains t and avoids h; the total integer weight of selected U,V,C variables is `2^k-h+l`. A four-state two-carry DP gives correction-degree upper bounds **1,61,64,66**, respectively, strictly below the unshifted degrees 61,63,65,67. Independent forward Python and backward C DPs agree. Thus the top forms are unchanged through bit 34; no claim beyond it.

As in -012, the invertible prefix permits independent pre-Chi variables, the 128 cells are disjoint, and every coordinate of Chi has degree <=13. For each local degree level d select d distinct cells and actual degree-13 vector ANF coefficients. The determinant of each top-form matrix is exactly the coefficient of the concatenated degree-13d pre-Chi monomial, because no lower-degree term can involve every selected cell. The C producer found 1,584 independent coefficient vectors grouped into 66 full-rank degree levels: 32-dimensional groups for d=1,2 and odd d=3..63; 16-dimensional groups for even d=4..64 and d=65,67. For a nonzero mask, the highest selected degree group cannot be orthogonal to every saved vector, while lower groups cannot affect these coefficients. This proves the exact maximum-degree formula for every J-supported mask, including cancellation checks rather than merely a count of possible trails.

### 16.20 — Evidence and limits

Source hashes match §16.12. GCC and Clang produce identical `parities.csv` and results; Python independently recomputes local ANFs, all 1,584 coefficient vectors and all ranks, and verifies all eight distinct used local coefficients by direct subset XOR. The original scalar C audit checks 8,388,608 local Chi inputs; 4,096 original complete-round control states per compiler match the independently written Pressure and suffix expressions. The degree proof does not enumerate 2^871 states. Reproduce using `KRAKKEN_RESEARCH_16_DEGREE871.zip`, `degree16_next/reproduce.sh`. Certificate SHA-256 `2f2a393d713914ce722ea82f395cb755f0af7562ec84002fb74939cff519222f`; coordinate table SHA-256 `d1d6eede34a7f856c27368024af03e0d084f8b84be21bd484a7fac27b7a54b16`.

Open: the remaining 464 D coordinates (k=35..63), masks involving these coordinates, exact maximum degree of R0, later rounds, inverse, and H159 restriction. The strict shift-bound argument may fail at bit 35 and above, requiring a different treatment of the top corrections. High degree is not necessarily monotonic across rounds, and does not establish differential probability, collision/preimage or algebraic attack complexity. The full-R8 degree lower bounds from previous work remain unchanged. This is a targeted prior-work screen, no third-party reproduction or external peer review. All earlier sections preserved.

---

## 16.21 — Exact first-round vectorial algebraic degree: 1443 (26 November 2026)

**R16-ALG-R1-EXACT1443-014.** The first complete indexed round `R0` on the unrestricted 2048-bit input has **exact vectorial algebraic degree 1443**. Every coordinate and every nonzero output parity has degree at most 1443; eight individual coordinates attain exactly 1443 (zero-based output bit indices `349,394,861,906,1373,1418,1885,1930`). This closes the maximum-degree question left open by -012 and -013. It is an analytic composition theorem with exact finite Boolean-polynomial, carry-state and rank certificates, not statistical extrapolation or a security-bit estimate.

For each Pressure chain, with independent 128-bit input `(U,C)`, write `V=C XOR (C>>17)`, `A=U+V`, `D=C+(A XOR (A<<31))` (64-bit modular additions). Before rotation, the exact local coordinate degrees are:

| Output | Bit range | Exact local degree |
|---|---|---:|
| A | 0..63 | k+1 |
| D | 0 | 1 |
| D | 1 | 2 |
| D | 2..49 | 2k-1 |
| D | 50..63 | k+48 |

The maximum local degree is **111**, attained by D63. Every global coordinate is bounded by 13 times its local degree. Exact attainment of this bound is now established for 1,936 of 2,048 global coordinates: all A bits, all D bits through 49 in all chains, and every D bit in chains `a=0,1,8,9,16,17,24,25`. The other 112 coordinates have explicit upper bounds, not claimed exact. The extension D35..49 also establishes full-rank degree-group certificates and expands the -013 exact maximum-degree rule to all nonzero output masks supported on the 1,824-coordinate A/D0..49 subspace. Arbitrary masks including high D bits are not classified.

## 16.22 — Proof: exact carry polynomial and highest-degree cancellation

In independent formal variables U,V,C, expand bit k of C+Q (`Q=A XOR (A<<31)`) by Lucas' identity, selecting C and Q masks with integer sum `2^k`. Each selected Q product has an exact Boolean ANF in A; its coefficients separate into 31 shift chains of positions `i,i+31,i+62`. For a resulting A mask a, Lucas' identity converts its monomial to selected U/V masks with integer sum a. A finite carry-state graph (two binary carries per stream, at most three streams and 64 states; all boundary carries enumerated exactly) represents this expansion. Exact max-plus DP in formal variables yields `2k-1` for k31..49. For k35..49 the top homogeneous form is `(U0+C0)(V0+C0)U1 V1 C1` times the product over `i=2..k-2` of `(Ui+Ci+s_i)(Vi+Ci+s_i)`, where `s_i=0` for i<33 and `C_(i-31)` otherwise. All 15 groups have independent rank-16 coefficient certificates through actual Chi and Butterfly (240 new vectors). The factored form and formal optimal count-pattern language are checked independently of the rank computation.

For k50..63 the formal ceiling cannot be treated as the real degree. The proof substitutes the actual V relation into each transition polynomial in an invertible linear coordinate system `X',C'` (`C_i=C'_i XOR C'_(i-48)` if i>=50; `X_i=X'_i XOR C_(i-31)` if i>=33; otherwise unchanged, `U=X XOR C`). For each boundary, rational weights `0<=w_j<=1` bound the support size of every product of transition monomials by `sum(1-w_j)+sum_selected_monomials sum_{j in monomial} w_j`. The largest path score is computed with exact integer arithmetic and all boundary states covered. The LP used during discovery supplies weights only; its numerical answer and optimality are not used in the certificate. This gives ceiling `k+49`. Equality requires all variables with weight <1 to occur and every variable with weight >0 to occur at most once, on a maximum-score path. Computing the corresponding residual polynomial by GF(2) XOR of union masks (not OR counting) shows it vanishes identically in every boundary reaching this ceiling. In particular D63's only degree-112 candidate boundaries, 11 and 15, both cancel. Independent Python and C++ computations certify all 14 such cancellations and nonzero degree-(k+48) witness coefficients. D63's explicit degree-111 monomial mask in the primed coordinates is `ffffffffffff7fff3ffffffeffffc002`; coefficient exactly one. Thus the actual local maximum is 111, not the formal ceiling 125 or support ceiling 112.

## 16.23 — Lifting theorem and complete reproduction

The linear prefix is invertible (rank 2048). The 128 disjoint serial-Chi cells have exact maximum degree 13 (first byte degree 7, second byte degree 13). Linear Butterfly and affine suffix operations do not raise the upper bound `13*111=1443`. To establish attainment, the new original-C producer selects one actual degree-13 local monomial from each of 128 distinct cells. For each of the eight chains above, the 128 mapped coefficient vectors projected onto U,C form an invertible 128x128 GF(2) matrix B. All 1,024 columns and ranks are independently recomputed in Python. If H is a nonzero degree-d local homogeneous part, its degree-d part after invertible substitution B is nonzero. Some square-free monomial on d selected cells therefore has coefficient one. Concatenate their degree-13 local masks: the resulting degree-13d global monomial has the same coefficient, because any contributing post-Chi term must use exactly one factor from each of those distinct cells, and no lower-degree term can do so. This proves exact 13d for the covered chains without expanding the full global ANF. Taking d=111 yields exact degree 1443 and the matching global upper bound. The C search's best witnessed rank 126 on the other eight chains is not a proof that rank 128 is impossible; those high-coordinate degrees remain open.

Evidence: `KRAKKEN_RESEARCH_16_DEGREE1443.zip`, `degree16_close/THEOREM.md`, `reproduce.sh`. Unchanged sources match §16.12. The new package contains the exact rational weight and monomial-witness files, Python verifier, independent C++ auditor, C producers, all 1,024 basis columns, 240 additional coefficient vectors, and the coordinate table. The included prior 871 archive preserves replay of earlier lower-coordinate certificates. GCC/Clang reproduce C certificates byte-for-byte; g++/clang++ reproduce the exact upper-bit audit; original-C local Chi checks cover 8,388,608 comparisons and full-round controls cover 4,096 states per compiler. SHA-256: `basis.csv` `b480792d31818e503b0a43d949b958229cc46a60563961502874e7fb28c00177`; `high.csv` `0a74882e70ece856cd29a16399d573cdcd19b9f422e4a73df0a8e740ad4712ff`; `coordinate_degrees.csv` `3b7f6f5b00b4a4182d76e26c4180071668d59a53614f62cd8f1ed23561a3e7d9`.

**Limits and next research:** exact vectorial R0 degree is closed. R2/R3/R8 remain open, as do 112 individual R0 coordinate degrees, unrestricted full-output minimum parity degree, H159 restriction and inverse degrees. Degree is not necessarily monotone under nonlinear composition; 1443 is not a number of security bits. Early unrestricted ZDD attempts did not complete; the exact weighted-carry certificate supersedes them. No differential bound is newly claimed and no external review or third-party reproduction is recorded. §§16.1–16.20 preserved.

---

## 16.24 — Exact indexed-round recurrence and cumulative R2 degree certificates (26 November 2026)

**R16-ALG-R2-CUBE29-015.** Write `R_i` for indexed round i and `F_r=R_(r-1)∘...∘R_0`. The exact `deg(R_0)=1443` theorem -014 extends to **every individual indexed round**, since `R_i(x)=R_0(x) XOR InkCloud(rc[i] XOR rc[0])`. This is an affine output translation, not a claim about compositions. On the actual cumulative two-round permutation F2, fresh exact ANF witnesses give **vectorial degree ≥29**, **all 2,048 individual coordinate degrees ≥28**, and **every nonzero full-state output parity degree ≥26**. The statements hold on the valid H159 affine plane and hence on unrestricted inputs. The first 256 output bits have a degree-29 witness as well. The unrestricted upper bound remains 2047; the exact cumulative two-round degree is open.

A 27-dimensional H159 cube was also evaluated at every cumulative depth 1..8. The full-state coefficient weights were `975,1013,1042,1063,1046,1041,1055,1002`; the first-256-bit coefficient weights were `121,123,130,148,123,122,136,135`. Thus every depth has a nonzero degree-27 witness, including the actual eight-round H159 digest. This improves the earlier common depth-24 witness. R1's exact unrestricted degree and the stronger R2-specific lower bounds are unchanged by this common-depth result.

## 16.25 — Memory-bounded near-top ANF and rank proof

Use the first d positions of `0,157,311,465,619,773,927,1081,1235,59,213,367,521,675,829,983,1137,19,173,327,481,635,789,943,1097,1251,75,229,383,537` (zero-based word-major bit order). All are distinct message bits below 1272. Fix all other bits to zero except byte159=0x86. On this affine d-dimensional cube, let `c_M = XOR_{x: x&M=0} F2(x)`. This is the exact vector ANF coefficient of the monomial with support complement(M), of degree `d-popcount(M)`. Retain every mask with at most three missing variables. Recursively split on the last variable: a coefficient including it is the XOR of the two child coefficients; one excluding it is the low child coefficient. Three-bit leaves use full Möbius transform. This gives exact near-top coefficients without storing the entire state truth table, using only polynomially many retained vectors per recursion level.

| Cube | Vertices | Degree thresholds (descending) | Cumulative coefficient ranks |
|---|---:|---|---|
| 28D | 268435456 | 28,27,26,25 | 1,29,407,2048 |
| 29D | 536870912 | 29,28,27,26 | 1,30,436,2048 |

All 3683 and 4090 coefficient vectors respectively are nonzero. The 29D top coefficient has weight 1037 (digest projection weight 127); the union of all 30 vectors of degree ≥28 covers all 2048 coordinates. Full GF(2) rank at degree threshold 26 excludes a nonzero output mask orthogonal to every high-degree coefficient, proving the uniform lower bound. The 407 overlapping coefficients of the nested 28D and 29D cubes agree. Coefficient archives SHA-256: `coeff28.csv` `e66106e169e4e75af4b8e2955f962c8625d36a2dce152e11dcd7585c2150a5c7`; `coeff29.csv` `e470890e17b615cbbc6e7ad4f82f2aad57427a557bc63c869c71b0b08ca0fa3d`. An independent full direct XOR over all 2^29 vertices reproduces the entire top coefficient exactly.

## 16.26 — Recurrent intermediate bounds and verification

Let `T_r` denote the cumulative state just after Chi and Butterfly but before Pressure in indexed round r−1. Inverting the prefix, Chi and Butterfly shows `deg(F_(r−1)) ≤ 7 deg(T_r)`, because serial Chi inverse is the XOR of inverse byte substitutions and linear expressions (inverse byte ANF degree 7, directly recomputed). Thus `ceil(deg(F_(r−1))/7) ≤ deg(T_r) ≤ min(2047,13 deg(F_(r−1)))` for r≥2. From -014 this proves **deg(T_2) ≥207**. This checkpoint bound is not a final F2 bound. For an individual inverse round, each inverse Pressure chain is a 128-bit permutation (reverse its two modular additions); degree ≤127. Combined with inverse Chi degree 7 and affine layers, `deg(R_i^-1)≤889`. Consequently `ceil(deg(F_(r−1))/889)≤deg(F_r)≤min(2047,1443 deg(F_(r−1)))`. The endpoint recurrence is valid but presently weak compared to the fresh cube witnesses; it does not assert monotonicity.

Evidence: `KRAKKEN_RESEARCH_16_R2_DEGREE29.zip`, `degree16_r2/THEOREM.md`, `reproduce.sh`. Source SHA-256 values match §16.12. The analysis-only AVX-512 VBMI evaluator compares all 256 S-box entries and 1024 full original-C states at each of eight depths. The separate portable backend calls original linear, Pressure and suffix routines and uses direct table lookup in Chi. A separately coded flat original-C 15D full Möbius transform exactly matches all 576 near-top coefficients from both recursive backends. Python independently verifies GF(2) ranks and coverage with opposite pivot order to C. All principal runs completed individually; `reproduce.sh quick` passed. Full 29D near-top replay using a separately implemented backend has not been performed; an attempted 29D eight-round run timed out without output, superseded by completed 27D all-depth run. No external peer review. Full replay is provided, including portable fallback for CPUs lacking AVX-512. Earlier degree-1443 theorem is inherited, not re-proved in this continuation. Prior §§16.1–16.23 preserved. No new differential probability or security-bit claim.

---

## 16.27 — Exact affine-slice inverse-round degree certificates (26 November 2026)

**R16-ALG-INVERSE447-DUAL-R2-016.** For every indexed round R_i, define E_i as its affine suffix (Pressure rotations, round constant, InkCloud), P as unrotated Pressure, B as Butterfly, L as the linear prefix, so R_i=E_i∘P∘B∘Chi∘L. In each of the 16 chains, write A=U+(C XOR C>>17), D=C+(A XOR A<<31), modulo 2^64. Its inverse is C=D-(A XOR A<<31), U=A-(C XOR C>>17). On the affine slice A=0 with all D words free (dimension 1024), the restriction of R_i^-1 to E_i(slice) has **exact vectorial degree 438**. On the extended slice A=e*(2^64-1) with one independent bit e per chain and D free (dimension 1040), the restriction has **exact vectorial degree 447**. On the unrestricted domain, the new bounds are **447<=deg(R_i^-1)<=882**. All indexed inverse round degrees coincide because indexed constants only translate the inverse input. The unrestricted exact inverse degree remains open.

Proof outline: inverse serial Chi has degree seven and is an invertible linear output combination of independent inverse byte S-boxes plus linear terms. Any contributing monomial spanning seven distinct Pressure chains must select exactly one factor from each chain in an inverse byte of degree seven. For local vector coefficients projected through B^-1 to that byte, the global coefficient equals the seventh derivative of the inverse S-box in the seven projected directions, and is zero for dependent directions. On the first slice, parameterize D=g^-1(t), g(t)=t XOR t>>17. Then U=-t and the nonlinear coefficient with greatest selected index k-1 is the U suffix 2^64-2^k. Terms involving <=6 chains have degree <=384; degree >=439 requires a rank-seven transversal with total loss <=2 from 7*63. All 256 byte projections have zero such choices. Prefix lengths [63,63,63,63,63,62,61] in chain words [13,28,24,0,16,9,12] give projected columns [8,16,17,169,33,12,18] in word0 byte1; their direct 128-vertex inverse-byte XOR is 0x4e. This matches the degree-438 ceiling.

For the extended slice, each fixed-e C(D) and U(D) is a balanced-coordinate 64-bit permutation, hence degree <=63 in D and <=64 including e. Degree >=448 requires exactly seven distinct chains each contributing a degree-64 coefficient. At e=0, U=-g(D); the coefficient of a nonlinear D support M in U_k equals one iff g projected to its low k bits has independent columns on M. At e=1, C=D-(2^31-1), U=~g(C); borrow into k>31 equals `(1+prod D_0..30)*prod(1+D_31..k-1)`. XOR the fixed-e coefficients for a monomial involving e. All 64 degree-64 candidate supports are enumerated: only two nonzero vectors, U63 (missing D indices 12,29,46) and U46+C63 (missing D63). Every rank-seven transversal in each of 256 byte projections is excluded, proving ceiling 447. A matching degree-447 witness uses six degree-64 local monomials and one degree-63 monomial (chain words [0,1,4,5,8,9,16]; missing masks [0x1000,0x1000,0x1000,0x8000000000000000,0x1000,0x1800,0x8000000000000000], each including e). Projected coefficients in word0 byte1 are [169,40,8,16,25,12,50]; the seventh derivative equals 0x4e. Thus the exact restricted degree is 447, not the formal composition ceiling 448. No 2^447 enumeration is required.

## 16.28 — Inverse-moment duality and structural two-round ceilings

For a permutation P of n bits and Boolean g, the ANF coefficient of g∘P on support complementary to M equals `XOR_y g(y)*prod_{j in M}(1+(P^-1(y))_j)`. It vanishes if `deg(g)+|M| deg(P^-1)<n`, by parity of polynomials of degree <n over the full space. For local inverse Pressure, the inherited exact forward maximum degree 111 (theorem -014) implies all degree-127 inverse coordinate coefficients vanish: substitute forward coordinates, and the integrand is x_i*(1+P_j(x)), degree <=112<128. Degree128 vanishes by balance. Hence inverse Pressure degree <=126; inverse Chi degree7 and affine layers give `deg(R_i^-1)<=882`, improving §16.26's generic 889. The resulting generic degree-growth recurrence may use denominator 882; it does not imply monotonicity.

For F2=R1∘R0, apply duality with n=2048 and inverse degree ceiling b=882. For each R1 coordinate with inherited ceiling e, the F2 coordinate ceiling is `2047-floor((2047-e)/882)`. The exact index and first-round ceilings are independently regenerated and matched to all 2048 rows of -014. Coordinates with e<=1165 have F2 degree <=2046, and with e<=283 have F2 degree <=2045. Disjoint coordinate counts: **528 at ceiling 2045, 1232 at ceiling 2046, 288 at ceiling 2047**. Therefore the rank of all degree-2047 vector ANF coefficients is at most 288, and the rank at degree >=2046 is at most 1520. Every nonzero mask supported on the 1760-coordinate subspace has degree <=2046; every mask in the 528-coordinate subspace has degree <=2045. This rules out maximal degree for these coordinates and masks but does not establish whether any of the remaining 288 coordinates reaches 2047. The prior F2 lower bounds from -015 (vectorial >=29, all coordinates >=28, all nonzero parities >=26) are unchanged.

## 16.29 — Verification and research frontier

Evidence: `KRAKKEN_RESEARCH_16_INVERSE447_DUAL_R2.zip`, `degree16_inverse/THEOREM.md`, `extended_witness.json`, `round2_degree_ceilings.csv`, `reproduce.sh`. Original source hashes match §16.12. Python rank elimination and independent C subset-span enumeration agree on both exact slice maxima. The extended coefficient oracle uses kernel-intersection and explicit factored borrow polynomial in Python; C uses direct column rank and two-state borrow parity. All 64 degree-64 candidates and the seven degree-447 local witnesses are audited. Original C forward Butterfly verifies coefficient columns; original linear-prefix basis inversion and full source round trips check 1024 unrestricted states, 1024 first-slice states, 1024 extended-slice states across all eight indexed rounds. GCC and Clang reproduce matching logs. Prior -014 archive is included as the dependency for local forward degree111 and round-coordinate ceilings. No new massive cube, unrestricted exact inverse degree, exact F2 degree, differential probability, security-bit claim, or external peer review. Further work may extend the symbolic inverse arithmetic coefficient oracle to the unrestricted local 128-bit input, or use more precise products of inverse coordinates in the duality identity. All previous ledger entries are preserved.

---

## 16.30 — Affine-coordinate rank oracle for inverse Pressure (26 November 2026)

**R16-ALG-INVERSE573-AFFINE-RANK-017.** For the unrotated local inverse Pressure map, set `T=D XOR h(A)`, `h(A)=A XOR (A<<31)`, `g(C)=C XOR (C>>17)`, all words 64 bits. This is an invertible linear coordinate change. Then `C=(T XOR h(A))-h(A)`, `U=A-g(C)`. For fixed T, the borrow recurrence `b_(i+1)=T_i h(A)_i+(1+T_i)b_i`, `C_i=T_i+b_i`, is affine in A. Thus G=g(C) is affine in A. The borrow into bit k of U equals `sum_{j<k}(1+A_j)G_j prod_{j<i<k}(1+A_i+G_i)` over GF(2). To obtain the coefficient of the full monomial on a unit-coordinate A slice of dimension a>=2, XOR only products with at least a factors. Each product's coefficient is one iff its affine factor-equals-one system is consistent and of rank a; otherwise zero. This computes the entire full-A coefficient without 2^a evaluations. XOR these exact coefficients over an independent d-dimensional affine T cube to obtain the degree-(a+d) top coefficient. Nonzero gives exact degree on the restricted domain. The C producer uses a fixed SplitMix64 seed 20261126 and 19-dimensional T cubes, 3 trials, 3 A masks. Used rows (0-based) in `witnesses.csv`:

| Row | A bits | T bits | Exact restricted degree | U coefficient | C coefficient |
|---:|---:|---:|---:|---|---|
| 0 | 63 | 19 | 82 | c000000000000000 | 0 |
| 3 | 63 | 19 | 82 | 8000000000000000 | 0 |
| 4 | 62 | 19 | 81 | a000000000000000 | 0 |

The unrestricted local inverse degree is therefore at least 82 (prior upper bound 126 retained). The exact unrestricted local degree is not known. All affine bases, directions, masks and coefficient vectors are archived. This is deterministic coefficient evidence, not an estimate of the unrestricted degree.

## 16.31 — Exact 573-dimensional inverse-round restriction and new unrestricted lower bound

Choose independent slices in chain words `[0,1,4,5,8,9,12]`, corresponding to rows `[0,0,0,3,3,4,3]`; fix the remaining chains to A=D=0. Apply affine suffix E_i to obtain an affine restriction of the actual indexed inverse round's input, dimension `6*82+81=573`. The seven local full-monomial coefficient vectors project through inverse Butterfly onto byte 1 of word 0 as `[253,60,12,8,25,10,24]` (rank seven). The seventh inverse Abyssal derivative in these directions equals **0xc4**. Since the seven parameter groups are disjoint, a monomial spanning all seven must take one factor from each group in an inverse S-box term of degree seven; no lower-degree term or linear term contributes. The inverse Chi output combination and inverse linear prefix preserve a nonzero vector coefficient (decomposition and invertibility inherited from -014/-016). Consequently the inverse round's degree on this explicit affine restriction is **exactly 573**, the domain dimension. This proves the improved unrestricted bound **573 <= deg(R_i^-1) <= 882** for every indexed round. Previous 438 and 447 exact restricted results remain valid. No assertion is made that unrestricted inverse degree is exactly 573 or that degrees grow monotonically under round composition.

## 16.32 — Independent verification, scope and next step

Evidence: `KRAKKEN_RESEARCH_16_INVERSE573.zip`, `degree16_inverse_next/THEOREM.md`, `scan.c`, `audit.c`, `witnesses.csv`, `lift.json`, `verify_lift.py`, `reproduce.sh`. Source files unchanged, hashes match §16.12. The producer constructs affine rows using the borrow identity; independent C audit constructs columns from direct modular subtraction at zero and A basis points, and solves in equation space with opposite pivot order. Three full 19D coefficient replays (1,572,864 T assignments) match; 256 original Pressure round trips and 256 exhaustive small-A cube controls pass. All seven inverse Butterfly coefficient columns are checked with original forward Butterfly. Separate Python confirms the used affine direction ranks, inverse S-box degree seven and nonzero derivative 0xc4. The old inverse upper bound 882 and all F2 ceilings/lower bounds are unchanged; this does not resolve unrestricted inverse Pressure or exact cumulative round-two degree. No security-bit estimate, external peer review, or new differential bound. The next useful target is an unrestricted symbolic bound on the T dependence of these rank coefficients or exact analysis of inverse coordinate products for F2 duality. All previous ledger entries preserved byte-for-byte.

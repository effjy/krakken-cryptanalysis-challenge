# NEW_THEOREMS.md — Krakken research (assistant-authored notes)

**Established:** 2026-11-09. This is the separate living theorem record for work authored in this conversation thread, as requested. The original `krakken.c`, `krakken.h`, and `krakken_multi.c` remain unchanged.

## Ledger boundaries and navigation

- **NOTE-010 (this assistant):** two-parity, two-complete-round differential bound for `Gamma` with bits 93 and 1233 set. The original full text is preserved below. Astra subsequently reproduced the evidence, as recorded in `Krakken(2).md`.
- **NOTE-011 (Astra, established):** eight backward parities; two-round bound `303976528439193 / 2^56` for the specified `Gamma` and one-byte differences. This supersedes NOTE-010 numerically for that *narrower* input class. The detailed proof remains in Astra's own `Krakken(2).md`.
- **NOTE-012 (Astra, established):** full-round restricted-output-mask linear-hull bounds, including the aggregate ten-dimensional squared correlation bound `<2^-440`. The detailed proof remains in Astra's own `Krakken(2).md`.
- **NOTE-013 (this assistant):** new analytic corollary from NOTE-012 via Fourier fourth moments: for almost every full-state input difference, a ten-bit *complete-round differential projection* is extremely close to uniform and all full-state output target probabilities are `<2^-10 + 2^-133`; gives a corresponding two-round bound for the specified `Gamma`. The full proof is preserved below.
- **NOTE-014 (this assistant, 2026-11-10):** deterministic first-round **actual H159 digest** result. Digest bit 11 is perfectly balanced over all `2^1272` messages; bit 139 has absolute sign bias `<=2^-124`; therefore two independent uniform messages collide on their complete 256-bit one-round digest with probability `<=1/2`, establishing `H_2 >=1` deterministically. It also holds with arbitrary fixed state-complement bytes; bit-11 balance needs only 145 uniformly varying prefix message bytes. Proof, independent GF(2) rank certificates, source checks, and limitations are in `KRAKKEN_NOTE_014_H159_DIGEST_BALANCE.md`. No eight-round bound follows.

**Historical annotation:** NOTE-010's preserved final section calls the low-four-bit nullspace exploration unverified. That statement was true at the time NOTE-010 was written; Astra subsequently verified the relevant rank and developed NOTE-011 and NOTE-012. It is not the present research status.

**Scope warning:** None of these proves a full eight-round marginal differential ceiling, H159 hash security level, or general attack-work lower bound. Established historical theorems are treated as previously verified; no wholesale re-audit is requested.

---

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


---

# KRAKKEN-NOTE-013 — Almost-everywhere complete-round differential uniformity from a certified linear-hull spectrum

**Date:** 2026-11-09  
**Authoring research thread:** this assistant, continuing from Astra's verified NOTE-011 and NOTE-012.  
**Status:** exact analytic corollary of the already verified computer-assisted NOTE-012 and NOTE-011. No new large numerical proof certificate is required. A small independent exhaustive test of the general Fourier identities is included in `verify_note013.py`.  
**Source-pinned Krakken implementation:** `krakken.c` SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`; `krakken.h` SHA-256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

## Theorem statement

Let `R_r`, `0 <= r <= 7`, be an actual indexed **complete** round of the unchanged 2048-bit Krakken permutation. Let `X` be uniform on all `2^2048` full-state inputs. Let `V_10` be the verified ten-dimensional linear space of output parities from Astra's NOTE-011/NOTE-012, with physical output masks `b_q = T^transpose q` for `q in V_10`. Choose any basis `q_1,...,q_10` of `V_10`, and define the selected ten-bit projection of a complete-round XOR difference:

```
W_(r,a)(X)[i] = b_(q_i) dot (R_r(X) XOR R_r(X XOR a)),  i=1,...,10.
```

There exists a set `BAD` of full-state input differences, **including the zero difference**, of cardinality

```
|BAD| < 2^(2048-184) = 2^1864,
```

such that, simultaneously for **each indexed round r**, every `a` outside `BAD` obeys:

```
(1)  TV(Law_X(W_(r,a)(X)), Uniform_10) < 2^-129.
(2)  For every y in GF(2)^10,
     |Pr_X[W_(r,a)(X)=y] - 2^-10| < 2^-133.
(3)  For EVERY full 2048-bit round-output difference beta,
     DP_Rr(a,beta) := Pr_X[R_r(X) XOR R_r(X XOR a)=beta]
                      < 2^-10 + 2^-133.
```

**Two-round corollary.** Let `Gamma` be the final difference with only full-state bits 93 and 1233 set, as in NOTE-009 through NOTE-011. For any `r=0,...,6` and every `a` outside the same `BAD`:

```
Pr_X[(R_(r+1) composed R_r)(X)
   XOR (R_(r+1) composed R_r)(X XOR a) = Gamma]
   < 2^-10 + 2^-133.
```

The intermediate difference is not prescribed. This is a point bound for the **specified** two-round target `Gamma`, not for all two-round output differences.

**Quantifier warning:** The exceptional set is extremely small **as a fraction of the full difference space**, but remains enormous in absolute terms. An attacker can intentionally choose a difference in `BAD`. No bound is claimed for those differences, or for H159 padded messages, digest collisions/preimages, or any eight-round marginal differential event. Neither 129 nor 133 is an attack-security exponent; the certified point-probability ceiling is close to `2^-10`.

## Verified historical premises

Astra's NOTE-012, established for each complete indexed round and all input linear masks `u`, proves the existence of explicit nonnegative rational caps `kappa_q` for every nonzero `q in V_10` such that

```
|Corr_Rr(u,b_q)| <= kappa_q   for every u,
sum_(q in V_10, q != 0) kappa_q^2 < 2^-440.
```

The second, **aggregate** inequality is essential: it is stronger than merely multiplying a uniform cap for one q by 1023. No new exhaustive reconstruction of NOTE-012's affine Fourier certificates is needed here. NOTE-011 also proves that the one-round predecessor differences of `Gamma` satisfy a **fixed ten-bit affine syndrome** on this same output-parity space. Those facts are accepted as verified earlier research, within their explicitly stated scope.

## Proof — linear-hull-to-differential duality

Fix one indexed round `R=R_r` and any nonzero `q in V_10`. Let

```
f_q(x) = (-1)^(b_q dot R(x))
C_q(u) = E_x[(-1)^(u dot x) f_q(x)] = Corr_R(u,b_q).
D_q(a) = E_x[f_q(x) f_q(x XOR a)].
```

All expectations in this proof are over uniform unrestricted full-state inputs/differences, of dimension `n=2048`.

For any sign-valued Boolean function, Walsh orthogonality, Fourier inversion and Parseval give the exact **Wiener–Khinchin identities**

```
D_q(a) = sum_u C_q(u)^2 (-1)^(u dot a),
sum_u C_q(u)^2 = 1,
E_(a uniform) D_q(a)^2 = sum_u C_q(u)^4.
```

Because `|C_q(u)| <= kappa_q`, it follows that

```
E_a[D_q(a)^2]
   = sum_u C_q(u)^4
   <= (max_u C_q(u)^2) * sum_u C_q(u)^2
   <= kappa_q^2.
```

Now put `S_r(a) = sum_(q in V_10, q != 0) D_q(a)^2`, summing all 1023 nonzero selected output parities. By **linearity of expectation**, not independence,

```
E_a[S_r(a)] <= sum_(q != 0) kappa_q^2 < 2^-440.
```

Apply Markov's inequality to the nonnegative `S_r(a)` at threshold `2^-256`:

```
Pr_(uniform a)[S_r(a) >= 2^-256]
   <= E_a[S_r(a)] / 2^-256 < 2^-184.
```

This proves the exceptional-set count. For every other `a`, one has `S_r(a) < 2^-256`.

The nontrivial Fourier character of the 10-bit difference projection `W_(r,a)(X)` indexed by `q` is exactly `D_q(a)`, since

```
(-1)^(q dot W_(r,a)(X))
  = (-1)^(b_q dot R(X)) (-1)^(b_q dot R(X XOR a))
  = f_q(X) f_q(X XOR a).
```

Ten-bit Fourier inversion followed by Cauchy–Schwarz gives, **for every** `y`:

```
|Pr[W=y] - 2^-10|
 = |2^-10 * sum_(q != 0) (-1)^(q dot y) D_q(a)|
 <= (sqrt(1023)/1024) * sqrt(S_r(a))
 < (1/32) * 2^-128 = 2^-133.
```

For the third inequality, use `sqrt(1023) < 32`. Ten-bit Parseval and Cauchy–Schwarz also give the total variation estimate

```
TV(Law(W),Uniform_10)
  <= (1/2) * sqrt(sum_(q != 0) D_q(a)^2)
  < 2^-129.
```

A full-state output difference `beta` necessarily fixes the selected ten projected output-difference bits, so its probability is at most the point probability of that projection. This proves the complete-round full-target inequality (3).

**Same good set across all eight indexed rounds.** The Krakken source implements each indexed round as the same nonlinear prefix through Pressure, followed by XOR with the indexed `rc[r]` and the same *linear* `ink_cloud_shuffle`. Therefore for every input state and difference,

```
R_r(X) XOR R_r(X XOR a)
```

is pointwise independent of `r`: the round constants cancel after XOR, even after the final linear shuffle. Consequently `W_(r,a)`, `D_q(a)` and `S_r(a)` are all independent of the round index. We may choose **one common** `BAD` set satisfying the count above; no additional union bound over eight rounds is needed.

**Two-round consequence.** NOTE-011 establishes that a final difference `Gamma` after the second round forces the ten-bit syndrome of the first-round intermediate difference to equal a fixed vector `c` (obtained from the predecessor affine-support calculation). Thus the two-round endpoint event is a subset of `W_(r,a)(X)=c`. The just-proved complete-round point bound applies, and **all possible intermediate differences are included**. No cross-round probability multiplication or conditional-uniformity assumption is made.

## General accuracy/coverage tradeoff

Replacing 128 by any positive real `s<220` in the Markov threshold gives a uniform statement:

```
Exceptional fraction < 2^(2s-440).
For all nonexceptional a:
    TV(Law(W_a),Uniform_10) < 2^(-s-1),
    max_y |Pr(W_a=y) - 2^-10| < 2^(-s-5),
    max_beta DP_Rr(a,beta) < 2^-10 + 2^(-s-5).
```

This is an **almost-everywhere statement** under counting measure on input differences, not a guarantee against adaptive or chosen-difference attacks.

## Eight-parity companion from the stronger aggregate V_8 certificate

Astra's NOTE-012 also proves the *stronger aggregate* bound

```
sum_(q in V_8, q != 0) kappa_q^2 < 2^-586,
```

for the eight-dimensional subspace `V_8` selected in NOTE-011. Repeating the same argument on the **255** nonzero parities with `s=192` gives a (generally different) exceptional set `BAD_8`, of cardinality `<2^(2048-202)`, such that for every `a` outside `BAD_8` and every indexed round:

```
TV(8-bit selected difference projection, Uniform_8) < 2^-193,
max_y |Pr[8-bit projection = y] - 2^-8| < 2^-196,
max_beta DP_Rr(a,beta) < 2^-8 + 2^-196.
```

Likewise the specified two-round `Gamma` probability is `<2^-8+2^-196` for these inputs. The pointwise estimate uses `sqrt(255)/256 < 1/16`; the exceptional fraction is `<2^(2*192-586)=2^-202`. Choosing `s=128` instead for the eight-parity space yields the alternative tradeoff: exceptional fraction `<2^-330`, projection TV `<2^-129`, pointwise error `<2^-132`, and all-target complete-round probability `<2^-8+2^-132`.

The ten-parity result has the smaller main probability ceiling (`~2^-10`), while the eight-parity companion can have a smaller exceptional fraction and correction term. Both retain their separate stated scopes; do not combine their exceptional sets without accounting for the union.

## Checks and evidence boundary

- `verify_note013.py` uses an unrelated, seeded 8-bit permutation to **exhaustively check** the Wiener–Khinchin, fourth-moment, and projection-Fourier identities and checks the exact exponent manipulations. It is a sanity check of the general derivation, not a new Krakken proof certificate.
- `verify_note013_round_translation.c` builds against unchanged original Krakken C. It checked 32 paired full-state inputs across eight indexed rounds under **GCC and Clang**, confirming that the complete-round output differences do not depend on the index. This is implementation regression evidence for the algebraic constant-cancellation argument.
- The substantive numeric premise `sum_q kappa_q^2 < 2^-440` and ten-parity predecessor implication are the already-verified Astra NOTE-011/NOTE-012, in uploaded `Krakken(2).md`, SHA-256 `f324da644ede967c596cdf58fef023cab09bcb115a2981c29f05a39e09235224`.
- The scalar source hash matches the source recorded there. We did **not** re-run the large NOTE-011/NOTE-012 evidence archive or change the original permutation.

**Research importance:** This gives a deterministic mathematical theorem about the *population of input differences*, yielding a full-target complete-round endpoint bound for almost all difference directions, and a two-round bound for the selected `Gamma`. It does not solve the worst-case input-difference or eight-round marginal-hull problem. A valuable next question is whether a source-specific argument can prove a comparable bound for every nonzero input difference (or the actual H159 domain) without dropping the exceptional class.



---

# KRAKKEN-NOTE-014 — Deterministic one-round H159 digest-bit balance and collision-entropy floor

**Author:** This assistant, in the separate `NEW_THEOREMS.md` program  
**Date:** 2026-11-10  
**Classification:** Exact source-specific, computer-assisted GF(2) rank theorem with analytic proof; full-rate population, not statistical.  
**Source:** The unchanged `krakken.c` (`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`) and `krakken.h` (`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`).

## The statement

Let `pad159(m)` denote the 2048-bit state in which bytes 0..158 are arbitrary message bytes, byte 159 is fixed `0x86`, and bytes 160..255 are zero. Let `R_0` be the **first complete indexed round** in the supplied original scalar implementation, including Theta, MDS, Rho, Pi, serial Chi, Butterfly, Pressure, Iota, and InkCloud. Let `H_1(m)` be the **first 256 output bits** of `R_0(pad159(m))`. The bit numbering `64*word+bit` is little-endian within each 64-bit state word; bit 11 is bit 3 of the second digest byte, and bit 139 is bit 3 of the eighteenth digest byte.

For `M` uniform over **all** `2^1272` valid 159-byte messages:

1. **Exact balance**: `Pr[H_1(M)[11]=0]=Pr[H_1(M)[11]=1]=1/2`.
2. **A second explicit population-wide marginal bound:**
   `|E_M (-1)^(H_1(M)[139])| <= 2^-124`. Thus, for either bit value `b`, `|Pr[H_1(M)[139]=b]-1/2| <= 2^-125`.
3. **Digest consequence:** For independent uniform H159 messages `M,M'`,
   `Pr[H_1(M)=H_1(M')] <= 1/2`; equivalently the full one-round 256-bit digest distribution has collision entropy `H_2 >= 1 bit` and min-entropy `H_infinity >= 1 bit`.

All three are deterministic mathematical consequences of a finite source-derived rank certificate and the original S-box's permutation/Walsh properties. They concern the actual 256-bit extracted digest at the first indexed round, not a Chi-only checkpoint and not unrestricted 2048-bit bases. They **do not** establish two bits of joint digest entropy, a later-round H159 population bound, or meaningful resistance against chosen-message collision attacks. The first result is far weaker in numerical collision-entropy magnitude than the existing *statistical* `KRAKKEN-STAT-002` result, which supports `H_2>29` at 99% confidence; the advantage here is complete-domain determinism.

**Offset generalization:** The same bit-11 exact-balance and bit-139 `2^-124` sign-bias bounds hold for every fixed assignment of input-state bytes 159..255, while all first 159 bytes vary uniformly. Round Iota constants do not affect the magnitude or exact balance. For bit 11, even **only input bytes 0..144 (145 bytes) need vary uniformly**, with all remaining state bytes fixed arbitrarily; the coordinate rank remains full. In the analogous 145-variable-byte domain, the available bound for bit 139 is `|E(-1)^bit| <= 2^-12`.

## Source mapping to two real digest bits

Write `L=Pi o Rho o MDS o Theta`, `C=serial Chi` and `B=Butterfly`. The original Pressure pair in words `(a,z)` has the unrotated expressions

```
u = a + (z XOR (z>>17)) mod 2^64
v = z + (u XOR (u<<31)) mod 2^64.
```

At bit zero, addition has no incoming carry, while `(u<<31)_0=0`:

```
u_0 = a_0 XOR z_0 XOR z_17,
v_0 = a_0 XOR z_17.
```

InkCloud sends input word `i` to output word `7i mod 32`, rotating its bits left by 11. Hence:

- **Digest bit 11:** post-InkCloud `(word0,bit11)` corresponds to *unrotated Pressure* `u_0` of the pair `(word0,word2)`.
- **Digest bit 139:** `(word2,bit11)` corresponds to pre-InkCloud `word14,bit0`, namely *unrotated Pressure* `v_0` of the pair `(word12,word14)`.

XORing the indexed round constants changes only fixed signs, never bias magnitude. Pull the two pressure-input linear forms backward by the exact transpose `B^T` to obtain byte masks on the **actual post-Chi** state. The masks are derived independently by reversing the five XOR/rotation Butterfly stages. On 512 deterministic one-round states (256 H145 and 256 H159), under both GCC and Clang, the masked post-Chi parity plus the original Iota constant reproduces each actual digest bit; the manually assembled round also matches the original `krakken_permute_scalar_rounds(state,1)` API.

## Serial-Chi coordinate lemma

For each of the 128 disjoint Chi cells, align the 32-bit byte rotation. Denote its **pre-Chi** input bytes by `(a,b)`, first S-box input by `x=a XOR b`, first output by `U=S(x)` and second output by `V=S(b XOR U)`, with the byte indexes rotated appropriately. Since the original Abyssal S-box `S` is a permutation, for **any selected sets** of first outputs `U_C` and second outputs `V_J` satisfying `J subset C`, the map

```
(x_C, b_J) -> (U_C, V_J)
```

is bijective, by first computing all `U_C`, then computing `V_J` using the known `U_J` and `b_J`.

The left-side coordinates are **affine-linear forms of the first 159 message bytes** under the source `L`. If their GF(2) row rank is the total number of coordinates, their joint distribution is exactly uniform and independent over the full H159 message space. Affine offsets (including padding/capacity choices) never change the row rank.

### Exact certificate for digest bit 11

The Butterfly-transposed output parity has nonzero masks on **48 first-Chi byte outputs** and **48 second-Chi byte outputs**, in **disjoint** cell positions. Let `J` be the 48 cells whose second outputs occur, and let `C` be the union of those cells with the 48 cells whose first outputs occur: `|C|=96`, `|J|=48`, `J subset C`.

The original C linear prefix yields exactly `8*96+8*48=1152` coordinate rows `(x_C,b_J)` in 1,272 message-bit columns. **Source-derived exact rank: `1152/1152`.** Independent high-pivot and low-pivot GF(2) eliminators agree, as do complete GCC/Clang recalculations. The full row-archive SHA-256 is

`b6dbc6968f06ba86bc0c76b2cb51da81324f21046476a8596d390233ca8e12c7`.

The rank remains 1152 when restricted to the **first 145 varying bytes** (1160 columns); at 144 prefix bytes the same certificate has rank 1151, so this specific full-coordinate-independence proof stops there. That does not show the bit is biased for 144-byte messages.

Thus `(U_C,V_J)` consists of 1,152 **independent uniform bits**. The selected digest bit is a **nonzero linear parity** of these bits (plus a fixed Iota bit). Any nonzero parity of independent uniform bits is perfectly balanced. This proves the first claim **exactly**, without a random-input sampling assumption.

### Exact certificate and Fourier bound for digest bit 139

The Butterfly-transposed parity mask now touches **52 first-Chi output bytes** and **76 second-Chi output bytes**. The required union of first-output cells and second-output partner cells has `|C|=96`, while `|J|=76` and `J subset C`. The source-derived `x_C` coordinate rank is **768** bits. Adjoining the 608 component bits of all 76 companion pre-S-box inputs `b_J` gives total rank **1272**, so the conditional rank of `b_J` after fixing `x_C` is **504**. Identical high/low elimination and GCC/Clang checks passed; full row-archive SHA-256:

`28214cd552849ce8eb7e20c7165701ce7b1a791600751d5b85a10aac8ff68af0`.

Condition on `x_C` (equivalently on `U_C`). The remaining conditional message distribution is a uniform affine space of 504 bits. The 76 selected second-S-box inputs `b_j XOR U_j` therefore lie uniformly on an affine coset of a binary linear code `D` in `76*8=608` bits, with **dimension 504 and dual dimension 104**.

For each active byte-output mask `q_j != 0`, write `f_j(t)=(-1)^(q_j dot S(t))`. Because `S` is a bijection, the zero-frequency normalized Walsh coefficient of `f_j` is zero. The original S-box's complete LAT has maximum nonzero absolute unnormalized Walsh entry **32**, so every Fourier coefficient has magnitude at most `32/256=1/8`. Expand the product `prod_j f_j(b_j XOR U_j)` into characters and average over the affine coset `D`. Only frequency vectors in `D^perp` survive; there are exactly `2^104` of them. Each term has absolute magnitude at most `(1/8)^76=2^-228`. Hence

```
abs(E[(-1)^digest_bit139 | x_C])
  <= 2^104 * 2^-228
   = 2^-124.
```

The bound holds **for every conditioning value** and every fixed complement-byte offset, so it holds unconditionally as well. The first-output Chi parity becomes a constant upon conditioning and cannot enlarge the absolute bound. No independence between the 76 second outputs is assumed. We used an exact affine-code Fourier identity, not an unjustified product of probabilities.

For 145 varying prefix message bytes, the same rank calculation gives `rank(x_C,b_J)=1160`, with 768 fixed first-S-box input ranks, leaving conditional rank 392, hence dual dimension 608−392=216 and bias bound `2^216*2^-228=2^-12`.

## Digest collision probability

For two independent uniform H159 messages `M,M'`, equality of their **full 256-bit first-round digests** implies equality of bit 11. Since that bit is exactly fair and the two messages are independent,

```
Pr[H_1(M)=H_1(M')] <= Pr[H_1(M)[11]=H_1(M')[11]]
                       = (1/2)^2+(1/2)^2 = 1/2.
```

The collision probability includes the negligible event `M=M'`; its upper bound remains valid for genuine `M!=M'` collisions. Likewise, for every digest target `t`, `Pr[H_1(M)=t] <= 1/2`, giving min-entropy ≥1 bit. NOTE-014 **does not** claim these bounds are tight or that a `2^1`-work attack exists.

## Reproduction record and limits

- The unmodified canonical scalar C/H fingerprints match the historical ledgers.
- Every one of the 255 nonzero output-mask Walsh transforms of `ABYSSAL_SBOX` was independently recomputed using an eight-stage integer Walsh–Hadamard transform; the maximum is 32, and zero-frequency entries are zero.
- The exact 2048-by-1272 prefix matrix is extracted via **1,272** calls to the unchanged C Theta/MDS/Rho/Pi functions on single-bit message directions.
- Both rank certificates are independently eliminated with highest and lowest pivot conventions.
- GCC and Clang builds produce identical rank counts and **byte-identical saved certificate SHA-256 digests**.
- At each of H145 and H159, 256 deterministic source comparisons per compiler check the actual one-round outputs and both selected bit identities (512 rounds and 1024 bit identities per compiler).
- The proof of exact balance is based on full rank and bijectivity; the **512 tested messages are not a population balance test**, nor are they substituted for the algebraic proof.
- This certificate uses the little-endian byte-to-word layout of the existing C implementation. The original sources were not modified.

**New files:** `verify_note014.py` and `note014_scalar_bridge.c`, plus the compact binary row certificates `NOTE014_ROWS_BIT11.bin` and `NOTE014_ROWS_BIT139.bin`. The script recompiles the original scalar C with GCC and Clang and checks all of the facts above; it does not need Astra's large evidence ZIPs or the historical solver campaigns.

**Open:** A 2-bit selected digest projection would additionally require control of the XOR parity of bits 11 and 139. The elementary full-coordinate-rank or simple dual-code triangle bounds here do *not* control that joint parity; the certificate is not a two-bit output-uniformity theorem. Later-round prefixes similarly require new arguments because the H159 state distribution is no longer an affine rate-plane immediately before the second round's Chi.


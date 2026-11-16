## WORK-SAT-PRESSURE-PILOT — Exact clasp-ready Pressure-pair XOR differential search (2026-11-06)

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


**Scope: one isolated 128-bit Pressure shear pair only. No theorem ID consumed; next is 050.** Built a direct DIMACS-CNF, exact 64-bit two-track XOR-differential encoding of the actual Pressure equations `u=a+(c XOR(c>>17))`, `v=c+(u XOR(u<<31))`, including optional output rotations 7/19. A uniform input XOR difference `(da,dc)=(1,0)` yields **at least 3 active output bytes** (counted across both output words) for either even or odd pair: K≤2 UNSAT, K≤3 SAT, both checked independently by libZ3. The two SAT witnesses reproduce on unchanged Krakken C; 30 full CNF gate-trace self-tests and 128 original-C reference comparisons passed. The user-installed clasp can independently run the four archived queries; **clasp was not installed here**, so actual clasp replay is pending. This is not a two-round active-Chi-S-box bound; SAT solutions for this component do not imply whole-permutation compatibility. Artifacts `KRAKKEN_CLASP_PRESSURE_PILOT.zip`, direct generator `pressure_cnf.py`, bounded scanner `scan_pressure.py`, source verifier `verify_original.py`. The existing eight-million-case `[2,1]` campaign is unchanged and should not be rerun.

## WORK-RX-FULL2048-R8-049 — Exact eight-round rotational/RX characteristic bounds and parity/symmetry exclusions (2026-11-06)

**Classification: independently audited source-pinned, computer-assisted exact statements on the full eight-round 2048-bit permutation, plus separately classified statistical endpoint data.** Original scalar C/H hashes unchanged. For `s=1..63`, fixed-operation-level RX characteristics specifying the four internal offsets `c,f(c),u,g(u)` on **each first-round Pressure pair** have uniform-base probability ≤`2^{-B_s}`, `B_s=16(rank K_f+rank K_g)`, where `rank K_f=2min(s,64-s,17,47)` and `rank K_g=2min(s,64-s,31,33)`. Consequently `B_s≥64` for all rotations, `B_s≥512` for byte-aligned rotations. This uses the joint `(c,u)` bijection and **no cross-round probability multiplication**. Independent GF(2) *row-based* rank audit checks all 63×2 commutators; original evaluator validation and results match GCC/Clang.

**Exact symmetry exclusions:** For `F(Px XOR alpha)=QF(x) XOR beta`, with independently arbitrary input/output coordinate permutations `P,Q`, original C's 2049 baseline states give **unique invariant graph neighbor-degree profiles for all 2048 vertices on each side**, excluding nontrivial `(P,Q)` for `alpha=0`. Another **2560 specified nonzero** input corrections (all 2048 unit vectors, eight constants, 504 constant-rotation errors) are excluded by exact derivative-column weight-multiset obstructions; 350316 evaluated columns; complete replay with GCC and Clang PASS. Other α and general invertible linear transforms remain open.

**Exact RX-defect parity exclusion:** For all 63 rotations, with `D_s(x)=F(R_s x) XOR R_s F(x)` and zero input correction, finitely many `D_s(x) XOR D_s(0)` vectors have GF(2) rank **2048**. Thus no nonzero full-output parity is universally constant, regardless of mask Hamming weight. **All 63 witness ranks, counts, and SHA-256 streams independently recomputed**, four cross-compiler spot checks PASS. This excludes *exact constant* RX parities, not statistical RX bias.

**Statistical data, separate from theorem:** Uploaded 64-MiB sample input SHA-256 `bc8191b13aee9939981a233a9a074c5607cc668ded09343b77da9f995c701990`; saved original endpoint experiment reports no repeated full RX defects in 262144 independent uniform inputs for each of 63 rotations. A binomial max-atom/Bonferroni argument gives a **simultaneous 99%-confidence upper bound `4.29304168573174e-5`** for all rotations/all 2048-bit output XOR corrections **when input correction is zero**; not deterministic or attack security bits. Raw experiment independently replayed for **nine full rotations** including GCC/Clang, not all 63; remaining 54 use archive records. Code/evidence in `KRAKKEN_THEOREM_049.md`, `KRAKKEN_THEOREM_049_EVIDENCE.zip`. No full RX hull or general security bound. **Next theorem identifier: 050.** All earlier theorem IDs and `[2,1]` status unchanged.

# Krakken — Attack-Family Theorems & Security Boundaries

## WORK-INT-FULL2048-R4-BIDIRECTIONAL-MIDBYTE-048 — Four-round forward/backward affine-integral exclusion (2026-11-06)

**Status: original-source-pinned exact finite-witness theorem, independently verified; not a discovered zero-sum distinguisher.** Define the exact original four-round permutation `F4=R3∘R2∘R1∘R0`. For each of four selected full-state **middle byte positions** `j∈{0,17,128,255}`, take the **complete 256-value affine byte cube** at the boundary after round 2, and compute its full 2048-bit **input** XOR after inverses `R1^-1,R0^-1` and full 2048-bit **output** XOR after `R2,R3`. Over 4097/4097/4101/4097 deterministic middle bases respectively, the **concatenated 4096-bit pair** of cube sums has affine dimension **4096** (augmented rank 4097). Therefore for **every nonzero pair `(a,b)` of arbitrary-weight 2048-bit masks and either constant `c`**, the parity `a·input_cube_sum ⊕ b·output_cube_sum` is **not universally constant** in any of those four middle-byte families; a finite witness refutes each such relation. **16,392 complete cubes / 4,196,352 middle-state members**, all original-map transforms, all joint ranks 4096. This is stronger than checking the two endpoints independently, but it **does not** rule out occasional simultaneous zero-sums, other cube geometries, conditional structures, nonlinear/inverse division-property attacks, or general four-round distinguishers; it supplies **no security bits**.

**Audit:** separately implemented inverse full-round evaluator (reverse InkCloud/Iota/Pressure/Butterfly/Chi/Pi/Rho/MDS/Theta) includes unchanged canonical `krakken.c/h`; 512 independent middle-state two-/four-round bridges agree with the unmodified original C compiled with **both GCC and Clang**; another 32 full byte cubes have matching GCC/Clang XOR outputs and raw archives. An independent C++ GF(2) bitset verifier obtains rank4096 with both opposite pivot orders at all 4 locations. Exploratory 162 smaller 8/12-dimensional four-round midpoint cubes across 3 splits yielded no full-state double zero-sum; this is *not* exhaustive and cannot establish attack absence. Exact proof, binaries, raw witnesses and reproducer: `KRAKKEN_THEOREM_048.md`, `KRAKKEN_THEOREM_048_EVIDENCE.zip`. Previous -047/-046 and `[2,1]` findings remain unchanged. **Next working theorem ID: -049.** Earlier next-ID references are superseded.


## WORK-INT-FULL2048-R8-DEGREE21-CUBE-047 — Full eight-round ANF-degree and integral evidence (2026-11-06)

**Status: source-pinned exact computer-assisted degree/cube theorem; full `2^24` affine-degree replay plus independently written local and selected byte-cube checks.** On the unrestricted 2048-bit input to the **actual eight-round permutation**, all **2,048** output coordinates have algebraic degree **≥23**, and every nonzero **2048-bit output parity** has degree **≥21**. The principal witness is a deterministic 24D affine restriction of **16,777,216** inputs: its **2,325** high-degree (≥21) vector ANF coefficients span rank **2048**. The original-user full-degree verifier was rerun end-to-end against the canonical original-source-equivalent C and matched the stored coefficient-stream SHA-256 and JSON exactly, including degree≥24/23/22/21 ranks `1/25/301/2048` and component-degree distribution 1023×24, 1025×23. The same independently reproduced 24D data show that for each of four selected 8D active cubes the remaining 16D superpolynomial has degree **≥12** for every nonzero output parity, via 2,447 available degree≥12 coefficients spanning rank 2048. These are **algebraic degrees, not security bits**.

**Independent verification:** Reran original-source GCC and Clang 12D Möbius/evaluator controls, checking 1,024 direct full states, 65,536 original-byte-cube evaluations and all 592 retained 12D coefficients. A separately written 16-bit local-gate ANF implementation exhaustively verified all 65,536 gate inputs, yielding **forward degrees 7 (255 nonzero parities) or 13 (65,280), inverse degree 7 for all 65,535 nonzero parities**. A different GF(2)/SHA-256 checker recomputed all saved byte-cube streams for input byte positions 0,1,248, with full **rank2048** on bytes **0 and 248**, matching those archived witnesses. The supplied 8-round byte-integral archive covers all **524,288** coordinate input-byte/output-bit pairs and all nonzero output masks at **32 specified** input bytes (0,8,...,248); the remaining archived byte positions were not all independently replayed. Its **68,633** cube records passed a full internal consistency/count check. The complete new full 24D degree calculation was rerun, but a separately coded second full 24D ANF transform was not implemented. **No claims about all integral/cube attacks, full-degree exact values, linear hulls, differential hulls, security-bit margins or full-state PRP security.** Proof, audit levels, and reproduction: `KRAKKEN_THEOREM_047.md`; `KRAKKEN_THEOREM_047_EVIDENCE.zip`. Previous -046 and `[2,1]` analyses unchanged. **Next working ID: -048.** Earlier next-ID references superseded.


## WORK-LIN-FULL2048-R8-TRAIL-046 — Independently certified eight-round linear-trail and perfect-relation results (2026-11-06)

**Status: original-source-pinned exact computer-assisted theorem; independent full-certificate replay plus fresh full-state rank witness.** The uploaded `linear_sparse_certificate.bin.gz` (SHA-256 `48f2c60d6c5d81d68904c270a692c7c3fb93dbea15d58c27fa079ae941ae9c77`) contains **32,768** complete sparse one-active→one-active mask-placement traces. Independently regenerated `B^{-T}` and `K^T` from the unchanged original C, and checked **6,483,387 individual sound modular-addition implication steps** with a separately written C++ `bitset<152>` GF(2) checker rather than using the supplied closure program. **32,766/32,768** yield full 24-bit boundary rank, excluding any nonzero such transition. Only gates **31→123** (dimension8) and **75→89** (dimension12), both destination equal-mask shape, remain; neither can chain into another exception. Independently enumerated 256/4096 residual assignments, obtaining exactly **123/1923** LAT-compatible cases, and checked all 16 Pressure pairs for each: **zero candidates have even one zero-addition-weight pair**. Thus every nonzero full **eight-round linear trail** has ≥**10 active byte S-box calls** and unresolved-block absolute contribution ≤`2^-30`; every **addition-resolved** full eight-round trail has ≥**36 bits** of correlation weight, absolute contribution ≤`2^-36`, squared weight ≥**72**. An independent shortest-path DP reproduced all 1–8-round bounds. **This is not a bound on linear hull correlations, attack/query complexity or security bits.**

**Separate exact full-round theorem:** New finite witness consisting of **4,112 full-state eight-round inputs** plus zero, evaluated through the **unchanged original C**, has affine graph matrix rank **4096/4096** under independently implemented Python high-/low-pivot GF(2) elimination. All **4,112/4,112** saved source-C results replayed byte-for-byte through **Clang-compiled original C**, and independently written C++ rank agrees. Hence **no nontrivial perfect (+1 or −1 correlation) input/output affine parity relation** for the full eight-round state permutation. Does not rule out biased approximations.

**Important verified correction to reviewer's report:** the correct **zero-addition-weight** condition for an unrotated Pressure pair is `Ua,Vc∈{0,1}; Va=Ua⊕Vc; Uc=(Ua⊕Vc)⊕(Ua<<17)`, **not** `Uc=(Ua⊕Vc)⊕((Ua⊕Vc)<<17)` as written in `LINEAR_REPORT.md`. Direct zero-cost counterexample `(Ua,Uc,Va,Vc)=(0,1,1,1)` disproves the written identity; **both finite exceptional-case enumerations still pass with the corrected condition**, so the 36-bit trail-weight result survives. Detailed statement/proof: `KRAKKEN_THEOREM_046.md`; original-C source, user certificate, full graph-rank witness, 3 independent verifiers, manifest: `KRAKKEN_THEOREM_046_EVIDENCE.zip`. The unrelated `[2,1]` differential theorem/16-active-call audit is unchanged. **Next working ID: -047.** Earlier `next -046` references below superseded.

## WORK-INT-FULL2048-BYTE-ALLMASK-R2-045 — Universal all-mask single-byte integrals excluded at two rounds (2026-11-06)

**Status: original-source-pinned, exact finite-witness computer-assisted theorem; independently dual-pivot certified across every input-byte position.** Let `P2` be **exactly two complete rounds** of the unchanged original Krakken 2048-bit permutation, `p∈{0,...,255}`, and `D_p(x)=⊕_{v=0}^{255}P2(x[p←v])`. Then for **every** nonzero **2048-bit output parity mask** `m` (any Hamming weight), both `m·D_p(x)=0` and `m·D_p(x)=1` occur for some 2048-bit base states `x`. Hence **no universally constant byte-coordinate integral parity survives R2 for any nonzero full-state output mask**, with no output-mask weight limitation. This is a full-input-state theorem, not a statement that all integral distinguishers or all full-round attacks disappear.

**Certificate:** At **all 256 input-byte positions** `p`, between **2,049 and 2,057** explicitly generated complete 256-state byte-cube derivatives yield **GF(2) rank 2049/2049** for the augmented 2049-bit vectors `(D_p(x),1)`. Exactly **524,967** cube bases, **134,391,552** complete two-round trajectories. The original-source-equivalent, research-only optimized C computes these original-map derivatives; an independently implemented Python **highest-bit pivot** elimination agrees on the full 2049 rank at **all 256 positions** with the C **lowest-bit pivot** builder; 256 source-pinned output SHA-256 fingerprints and each base count saved. Source-level `diff` shows only the bytewise-equivalent S-box lookup replacement; an additional **131,072/131,072 complete 2048-bit R1/R2 outputs** across 256 positions ×256 active-byte values are identical between the unmodified original C and optimized C. A separate exhaustive-byte/mixed-lane S-box equivalence test passes **67,840/67,840** words. **24/24** original-C complete-cube XOR derivative replays match six saved full raw witness matrices (positions 0,1,17,63,128,255; base indices 0 and 2048; depths R1 and R2). Six full binary derivative archives included; all other position matrices are reproducible from the pinned generator and SHA fingerprints. Archive self-audit passes.

**Mathematical corollary:** For every `m != 0` and **every input byte p**, the ANF of the Boolean function `x↦m·P2(x)` has a monomial containing all **8 bits of byte p** plus some bit outside p; in particular **degree ≥9** for **all 2^2048−1 nonzero output parities**. This strengthens the reviewer's weight≤2 R2 result but does **not** automatically extend to R3..R8, non-byte-aligned input cubes, biased/nonlinear integrals, or **valid159 padded hash inputs**. Invertible publicly known rounds also let a full-state adversary invert known outer rounds: this structural exclusion is **not** a pseudorandom-permutation security-bit or seven-round security-margin theorem. The separate `[2,1]` audit remains unchanged. **Full proof and limits:** `KRAKKEN_THEOREM_045.md`; reproducible data/scripts `KRAKKEN_THEOREM_045_EVIDENCE.zip`. **Next working theorem identifier: -046.** Historical next-ID references below are superseded.

## INDEPENDENT REVIEW: full-state 1-byte/weight≤2 fixed-parity integrals, R2–R8 (2026-11-06; no theorem ID consumed)

**Precisely scoped, computation-backed exclusion confirmed:** Reviewer archive `Krakken_Integral_Audit_Rounds_2-8.tar(1).gz` pins original source C/H SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` / `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. For every full-state **input byte p=0..255** and every complete round depth **R2..R8**, no 2048-bit output parity mask of Hamming weight 1 or 2 has a universal **constant-zero or constant-one** 256-value input-byte-cube XOR over arbitrary 2048-bit base states. The archive's **256×64×256=4,194,304** full eight-round trajectories yield no fixed-parity signatures; for any candidate mask, finite base witnesses show both parity values, refuting universality. R1 has 409 single-bit and 3,148 two-bit fixed-zero **sample candidates**, NOT proven universal identities. Reader must distinguish post-round output-parity constraints from full-state round-inverted attacks.

**Independent audit:** All eight archived source hashes PASS; 1,024 original-vs-fast random/patterned state permutations PASS. Independently parsed every one of 4,194,304 rows in the 32-base raw count table, matching R1 409/R2–R8 zero one-bit candidate counts. Wrote and ran separately coded **full-256-position 64-base replay** at the archive's original seed with **explicit all-pairs 2-bit signature comparisons**, obtaining *exactly* 409/0/3148/0 at R1 and **0/0/0/0 at each R2..R8**, matching all archived aggregate counts. Fresh independent seed at six positions also excludes low-weight constants R2..R8. Eight complete 256-input cubes (2,048 inputs) directly replayed with unmodified original C against optimized C at R2/R8, zero mismatches. Exact finite-witness corollary: every weight≤2 nonzero full-state output parity after R2–R8 has ANF degree at least 9 and an ANF monomial containing all 8 bits of each fixed input byte plus another input bit. **Not** full integral/PRP/hash indistinguishability, not probability/security bits, not coverage of arbitrary output masks or input subspaces. Full standalone report: `KRAKKEN_REVIEWER_INTEGRAL_INDEPENDENT_AUDIT.md`, evidence `KRAKKEN_REVIEWER_INTEGRAL_AUDIT_EVIDENCE.zip`. **The `[2,1]` theorem and working ID -045 remain unchanged.**

## `[2,1]` independent certification audit — small batch 02 (2026-11-06; NO theorem promotion)

**Full bit-zero stage independently closed:** A fresh standalone C GF(2) kernel/inclusion–exclusion verifier reconstructed all **8,355,840** archived `(i<j,q,first/second)` support labels from SHA-verified checkpoint records (including repaired i000 source lists). For every site, zero bit-zero solutions held **if and only if** its archived status was `lsb_unsat`: **2,006,843/2,006,843 bit-zero exclusions independently reproduced; 6,348,997/6,348,997 other sites independently verified bit-zero compatible; zero discrepancies**. This relies on the previously audited original-C linear transport and Chi endpoint mapping, and theorem `WORK-PRESSURE-LOWK-OVERAPPROX-038` for Pressure necessity; it is not a global `[2,1]` exclusion by itself.

**Independent low3 stage:** A new Boolean ripple-carry SMT-LIB2 formulation (rather than the campaign's BitVec `bvadd` equations) re-solved **1,020 low3 UNSAT cases covering every one of the 255 starting positions**. Independently written C Boolean full-adder enumeration of **262,144** local base/difference assignments exactly reproduced all **32,768** local three-bit signatures (4,376 allowed), zero discrepancies. The independent low3 SMT still uses libz3 as the underlying solver; this is independent constraint encoding, not an independent SMT solver.

**Five consecutively certified starting positions:** i=250..254 have **3,840/3,840** source-mapped support labels independently excluded: 920 LSB, 2,919 low3, and one low4 (`i=251,j=252,q=104,first`) checked with an independently built four-bit Boolean adder; the case is low3-SAT and low4-UNSAT. These are source-and-solver-conditional exact finite computations for the **restricted** first-active-post-Chi-byte index range `250..254`, not a theorem for all 8,355,840 sites.

**Checkpoint encoding nuance:** The `i001` parent records encode 1,000 `low4_sat` refinements as numeric code 3 (not `low5_unsat`); 750 are subsequently low5-UNSAT and 250 low6-UNSAT in child certificates. Hence raw code counts 40,898/23,278 become final low5/low6 counts 40,648/23,528; the LSB code0/nonzero verification is unaffected.

**Remaining blocker:** The recorded global campaign is complete with zero unresolved, but **6,128,697** original low3 exclusions are not independently replayed in full, nor the bulk of 154,124 low4, 40,648 low5 and 23,528 low6 classifications (earlier high-refinement replays covered 4,141 special cases). The eight-round active-call abstract DP improvement from **15 to 16** is **conditional** on independently certifying the universal `[2,1]` exclusion. **Do NOT promote 16 as a concrete bound or security bits yet.** Detailed audit/reproduction: `KRAKKEN_21_SMALL_BATCH_AUDIT_02.md`, `KRAKKEN_21_BATCH02_EVIDENCE.zip`. **Next working theorem ID stays `-045`.** Older audit notes below are historical.

## WORK-INT-H159-DIGEST-SPLIT44-R2-044 — All digest-side split-nibble two-round universal nonlinear integrals excluded (2026-11-06)

**Status: exact, source-pinned finite-witness mathematical theorem, with independent spot replay.** On the original valid159 first-block hash input family (zero capacity, `0x86` terminal padding), form the full 256-message coordinate-byte cube for **each of all 159 input-byte positions**. For each one, consider **all 4×C(32,2)=1,984 distinct 4+4-bit output windows comprising one nibble from each of two distinct bytes of the first 256 digest-state bits after exactly two original rounds**. For **each of all 315,456 `(input byte, digest split-nibble window)` families**, 290 specifically recorded valid message bases yield a parity-histogram affine-difference rank of **255/255** in `GF(2)^256`. Therefore **every nonconstant Boolean function of the selected eight output bits has nonconstant 256-cube XOR parity as the valid message base varies**; neither universal constant-zero nor universal constant-one nonlinear integrals of this precisely specified form exist at R2. This is a finite-existence proof via spanning, not a claim based on random sampling.

**Original-C evidence:** unchanged scalar `krakken.c` / `krakken.h` pinned SHA-256; **11,804,160** two-round original-C calls; high- and low-pivot GF(2) elimination both return rank255 for **all 315,456 families** (**630,912** rank checks); no exceptions. SHA-256 for all 159 saved output streams and per-position base, rank and witness files; read-only all-position SHA/rank/position check PASS. Five independently source-regenerated complete 290-cube datasets (`p=0,1,24,80,158`) match archived output digests; independent Python reconstructs **34,800 exact histograms and 120 full-rank window certificates**, all PASS. Twenty direct-original-C 8-round hash-wrapper equivalence checks PASS. The original first-round one-byte cube universal linear balances from `WORK-INT-ALL159-001` are *not* thereby classified for every new R1 output projection; theorem -044 proves a new **R2 exclusion**, not a universal R1→R2 count.

**Limits:** Only exactly 159-byte valid first-block inputs; one varied whole input byte; 4+4 nibbles in **distinct digest bytes**, arbitrary Boolean predicate of the resulting **eight bits**, and base-*independent constant* cube-parity attacks at **two rounds**. No claim about other cube geometries, biased integrals, 16-bit full-byte-pair predicates, whole-state all-pair windows, unrestricted two-/eight-round distinguishers, or security bits. The `[2,1]` global transition and eight-round 16-active-S-box theorem remain **unpromoted**. Exact write-up: `KRAKKEN_THEOREM_044.md`; reproducibility: `KRAKKEN_THEOREM_044_EVIDENCE.zip`, including source, 159 position certificates and generator/auditors. **Next available working theorem identifier: -045.** Historical next-ID lines below are superseded.


## WORK-INT-H159-CUBE12-DISTANCE7-043 — Quantitative *finite-witness* residual integral bound (2026-11-06)

**Status: exact finite-source certificate; R2/R4/R8, original valid159 12-bit cube, 320 deterministic message bases.** Building on `-042`, all 320 previously original-C-verified 256-bit cube derivatives at each round depth define a 320×257 augmented binary matrix (256 output coordinates plus constant column), of rank **257**. Its 63-dimensional left nullspace yields a parity-check matrix. For each of rounds 2, 4, and 8, **all 5,461,601 XOR sums of 0–3 distinct parity-check columns are pairwise different**, proved by exhaustive exact C++ enumeration (16,384,803 total verified subset sums). Any nonzero codeword must therefore have Hamming weight **≥7**. Thus **for every nonzero 256-bit digest-output parity mask**, among the 320 fixed 4,096-message cubes, at least **7** have XOR parity zero and at least **7** have XOR parity one. The finite-set empirical absolute parity bias is bounded by **306/320 = 0.95625**. Independent high-/low-pivot GF(2) dependency bases have identical 63-dimensional nullspace; an extra 30,000 parity-mask probes per depth passed. Original-source derivative values are **reused from theorem -042**, not new hash evaluations. This is **not a population bias bound over random messages**, a full eight-round distinguishing-security exponent, or an analysis of the three conditioned `A₁=5` deltas. Full proof and regeneration: `KRAKKEN_THEOREM_043.md`, `KRAKKEN_THEOREM_043_EVIDENCE.zip`. The `[2,1]` campaign remains computationally complete but its universal exclusion and conditional minimum of 16 active S-boxes remain **unpromoted**. **Next unused theorem ID: -044.** Historical “next ID” references below are superseded.


## WORK-INT-H159-CUBE12-AFFINE-042 — Exact exclusion of constant 0 AND constant 1 cube parities (2026-11-06)

**Status: source-backed exact finite-witness theorem.** For the original valid159 12-bit cube varying message byte0 and the low nibble of byte1, the original-C 258-base derivative matrix at depths R1/R2/R4/R8 has ranks `255/256/256/256`; augmenting every row by a constant 1 gives ranks `256/257/257/257`. Thus R1 has exactly the inherited bit11 constant-zero linear balance, while at R2, R4 and full R8 **every nonzero 256-bit output parity assumes BOTH cube-XOR values 0 and 1 across valid bases**. A concrete odd-numbered zero-XOR subset of rows (sizes R2=131, R4=129, R8=131) excludes every universal constant-one parity; full linear rank excludes universal zero. This extends theorem -041's zero-only result, but **does not bound statistical biases, all integral geometries, or any security-bit exponent**. A new original-C replay on bases 256–319 matches the prior original-C archive in the 8 overlapping rows and independently agrees with the optimized computation in all 256 fresh derivative rows. Thus 320 distinct 4096-message cubes (1,280 derivative vectors) are now source-C covered; 258 suffice for the theorem. Two independent rank-checker implementations PASS. Full mathematical proof `KRAKKEN_THEOREM_042.md`; reproducibility package `KRAKKEN_THEOREM_042_EVIDENCE.zip`. Global `[2,1]` exclusion and the proposed 16-active-S-box bound **remain unpromoted**. **Next unused working theorem ID: -043.** Historical older “next ID” references below are superseded.



## WORK-INT-H159-CUBE12-ALLMASK-R2R4R8-041 — Exact round-2 elimination of all universal output-linear balances (2026-11-06)

**Promoted exact finite-witness theorem on pinned original source (not general security bits).** For one fixed **12-bit valid159 message cube** (vary all of byte 0 and low nibble of byte 1), take the 256-bit digest XOR derivative over all 4096 cube values. Across **258 deterministic, distinct message-cube bases**, the derivative-row GF(2) ranks at round depths **R1/R2/R4/R8 are `255/256/256/256`** respectively. The known exact R1 integral `bit11` universally balances; the rank-255 certificate proves it is the **only** universally zero-balanced linear digest mask for this input cube at R1. At **R2, R4 and R8**, full rank proves that **no nonzero 256-bit output parity mask** is universally XOR-balanced on this particular cube. In addition, every nonzero parity of the reduced R2 and R4 digest has ANF degree **≥12**. All **1,032** derivative row vectors (258 bases ×4 depths, each with 4096 chosen valid messages) were replayed through **unchanged original `krakken.c`**; optimized backend, independently coded low-/high-pivot Python elimination and a separate reverse-pivot C++ verifier agree; 256 earlier original-C theorem-040 rows match. There is **no probability/security-bit bound** or generic distinguisher exclusion; the result does not concern arbitrary cube supports, biased or nonlinear integrals, or the separate `[2,1]` campaign. Full proof and reproducible evidence: `KRAKKEN_THEOREM_041.md` and `KRAKKEN_THEOREM_041_EVIDENCE.zip`. **Next theorem ID `-042`.** Historical older “next ID” references below are superseded.

## WORK-INT-H159-CUBE12-R1R2R4R8-040 — Original-C 12-bit integral non-persistence through R8 (2026-11-06)

**Status: source-pinned exact finite counterexamples and finite 64-cube diagnostic, not general eight-round security theorem.** We independently evaluated 64 disjoint 4096-message cubes (valid 159-byte messages, varying byte 0 and the low nibble of byte 1) through **R1/R2/R4/R8** of the original scalar permutation. For the inherited universal R1 integral on digest/state bit **11**, the number of cubes with an odd XOR output parity was **0/64 (R1), 28/64 (R2), 31/64 (R4), 32/64 (R8)**; ideal random-function reference is Binomial(64, 1/2), mean 32. The two other inherited R1 universally balanced full-state bits 907 and 1374 were 0/64 at R1 and nonconstant at R2/R4/R8. Across all 256 digest bits, **no bit** had a constant cube parity on the 64 chosen cubes at R2/R4/R8. Source-C explicit counterexamples to universal bit11 balance: cube index 1 at R2; 2 at R4; 0 at R8. Their complete 4096-query cubes were independently recomputed using the unchanged original `krakken_permute_scalar_rounds` and exactly matched, as did nine additional full-depth cube replays: **12/12** source-C cube-depth checks, **49,152** original-C permutation calls. The first-stage per-round harness additionally matched the original multi-round implementation on **80** random states. The specific R1 integral therefore does **not** remain universally balanced at depths 2, 4 or 8. The R2 nonuniversality was already known in `-017`; R4/R8 counterexamples and this 64-cube comparison are additional evidence. This is **not** a general proof of absence of multi-round integral attacks, a 30-bit differential-security claim, or an unrestricted 8R security exponent. Full report `KRAKKEN_CUBE12_ROUND_DEPTH_AUDIT_040.md`; evidence `KRAKKEN_CUBE12_ROUND_DEPTH_AUDIT_040_EVIDENCE.zip`. The `[2,1]` campaign remains complete computationally but unpromoted mathematically. **Next available working theorem identifier: -041.**


## Exact R1 / R2 / R8 comparison on a fixed 17-bit family — 2026-11-06 (`-039`)

**New narrowly scoped finite-domain theorem `WORK-DIFF-H159-R1R2R8-REFERENCE8-039`:** For the pinned 17-variable valid159 reference message family and the eight digest bits `[11,94,139,210,0,52,128,242]`, exhaustive differential distributions of *all* 131,071 nonzero input-direction differences and all 256 output patterns give maximum frequencies **698/131072 (R1)**, **692/131072 (R2)**, and **690/131072 (R8)**. Minimum frequencies are **356, 344, 344**; all output patterns occur for every permitted input difference. The resulting finite-domain maximum-differential min-entropy floors are **7.55292, 7.56537, 7.56955 bits**, respectively. The maximum TV distances are **7976/262144**, **7868/262144**, **7960/262144**. Two distinct complete exact global DDT algorithms agreed at every depth; 417 source-C projection replays and 24,576 independent direct histogram-bin checks passed. The theorem characterizes a selected eight-bit projection on **one fixed input family** and **does not prove 30-bit two-round security, unrestricted full-round differential probability, or additional 8R attack complexity**. This family does not contain the previously studied three conditioned `A1=5` differences. Full report `KRAKKEN_R1_R2_DIFFERENTIAL_COMPARISON_039.md`; evidence `KRAKKEN_R1_R2_DIFFERENTIAL_039_EVIDENCE.zip`. The universal `[2,1]` exclusion and eight-round 16-active-call proposal remain **unpromoted**. **Next unused working theorem identifier: -040.**


**Living research supplement · created 2026-11-03 · source-pinned to Krakken-2048 Abyssal (8 rounds)**

> **Canonical living-ledger policy (confirmed by research owner, 2026-11-05):** **This document, `KRAKKEN_ATTACK_FAMILY_THEOREMS.md` (successor to uploaded `KRAKKEN_ATTACK_FAMILY_THEOREMS(23).md`), is the primary theorem ledger for ongoing Krakken research.** Record every new proof-backed theorem, scoped finite certificate, correction, verified counterexample, and material campaign-status change here, with unique working IDs, precise domains, evidence and unresolved assumptions. Update `RESTORE.md` in parallel for conversation recovery. Preserve historical entries and keep IDs in the older permanent `KRAKKEN_SECURITY_THEOREMS.md` unchanged unless explicitly promoted after separate audit. Reproducible checks are not external peer review; this ledger does not certify full eight-round attack-complexity security.

## `[2,1]` final certification audit — small batch 01 (2026-11-06)

**Status: source-transport checks PASS; selective independently coded LSB audit PASS; universal `[2,1]` exclusion NOT YET PROMOTED.** Newly checked all **2,048** original-C Butterfly basis vectors and all **2,048** inverse-tail-to-original-C-forward basis identities, plus **256** original-C Chi endpoint constructions (one each first-only and second-only for all 128 byte-lane cells). The independent row-elimination/inclusion-exclusion checker tested **360** saved bit-zero UNSAT cases and verified valid LSB solutions for **96** low3-classified plus **22** low4-classified cases, across twelve starting positions: **478/478** expected results. A separate eight-round activity dynamic program confirms the **conditional** arithmetic `15→16` if universal `[2,1]` exclusion is eventually certified.

**Blocking work:** independent certification of the large earlier-stage SMT exclusions, especially all **6,128,697** low3 cases; complete source-to-model proof integration. Do not infer 16 as an established concrete-permutation lower bound yet. Evidence: `KRAKKEN_21_SMALL_BATCH_AUDIT_01.md`, `krakken_21_source_transport_audit.py`, `KRAKKEN_21_SOURCE_TRANSPORT_AUDIT.json`, `krakken_21_lsb_independent_audit.py`, `KRAKKEN_21_LSB_INDEPENDENT_AUDIT.json`, `KRAKKEN_21_ACTIVITY_DP_CHECK.json`. **No new theorem ID assigned; next candidate remains -039.**

## Completed `[2,1]` differential-configuration campaign — authoritative closeout (2026-11-06)

**Status classification: computational campaign complete; record-integrity audit complete; selected SMT replay complete; global mathematical exclusion not yet certified.** This section supersedes the preliminary archive-audit notes and earlier live positions (`i=176`, `183`, `191`, `228`) retained below for research history.

**Source pinning:** original scalar `krakken.c` SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`; `krakken.h` SHA-256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. The user-supplied final archives are `KRAKKEN_21_COMPLETE_AUDIT.zip`, `KRAKKEN_21_MISSING_CORE.zip`, `1.tar.gz`, `2.tar.gz`, and `last_run_summary.json`. The two initially missing Python modules (`krakken_screen_21.py`, `krakken_screen_21_low2.py`) and the completed position-0 JSON (`krakken_21_low4_first0_closure.json`) are **now present**; do not carry forward the preliminary claim that they are missing.

The search exhaustively enumerates the **spatial support labels** `0≤i<j≤255`, next-round Chi byte-lane cell `0≤q<128`, and `first/second` call branch, totaling `C(256,2)×128×2 = 8,355,840` labels across **255 starting positions** `i=0..254`. The supplied final checkpoints/report chain records every enumerated label as excluded by a necessary-condition model, with **zero remaining SAT/UNKNOWN after applicable refinements**:

| First decisive exclusion tier | Recorded sites |
|---|---:|
| LSB (bit zero) | 2,006,843 |
| Low-three-bit SMT | 6,128,697 |
| Low-four-bit SMT | 154,124 |
| Low-five-bit SMT | 40,648 |
| Low-six-bit SMT | 23,528 |
| Low-seven-bit SMT | 2,000 |
| **All reported excluded spatial sites** | **8,355,840** |
| **Reported unresolved after final tier** | **0** |

**Coverage evidence:** `i000`: 65,280 labels, including final 1,141 low4 exclusions; `i001`: 65,024 labels, including 750 low5 and 250 low6 exclusions; `i002..i254`: 253 complete parent JSONs covering 8,225,536 labels, with 2,000 six-bit relaxation survivors all reported UNSAT at low7 (1,875 in 15 generic low7 children plus 125 in the special i002 child). The last auto-invocation's independent `last_run_summary.json` covers only positions `i008..i254` and records `247/247 CLOSED`, `7,840,768` examined/excluded, zero unresolved and no interruption; do not mislabel that narrower summary as a 255-position single-run report. Included TAR members matched the original checkpoint bytes.

**Independent checks completed in the prior extended audit:** Parent raw-status checksums, payload lengths, counts, source/model fingerprints and child-parent SHA-256 linkages were checked. A fresh local Z3 context, using regenerated source-pinned model formulas, returned **UNSAT for all 4,141 targeted saved final-tier cases** (`i000 low4: 1,141`; `i001 low5: 750`; `i001 low6: 250`; main low7: `2,000`), with zero discrepancies. Source/Python layer checks (12,468), actual full-width Pressure pairs projected to seven bits (1,000), and separately coded Pressure-chain checks (16,000) passed. These are *model-replay and source-validation checks*, **not independently checkable UNSAT certificates for all 8.35 million recorded exclusions**; earlier-stage decisions were not all independently re-solved.

**Related theorem `WORK-PRESSURE-LOWK-OVERAPPROX-038` (source-derived, analytic; previously recorded):** For `k∈{1,3,4,5,6,7}`, any real 64-bit XOR differential through a Pressure word-pair shear satisfies the corresponding existential low-`k` model because reduction modulo `2^k` preserves the relevant additions and nullifies `A<<31`. Thus the low-bit *Pressure arithmetic constraints*, when correctly encoded, are necessary conditions. This does **not** by itself establish correctness of every linear transport, all Chi endpoint assignments, or every UNSAT classification. See `KRAKKEN_21_FULL_CAMPAIGN_EXTENDED_AUDIT.md` for the proof and its exact scope.

**Unpromoted global conclusion:** No universal theorem of the form `A_r=2 ⇒ A_{r+1}≥2` is recorded as proved yet. Before promotion, independently certify (or check proof logs for) the large earlier-tier UNSAT population; finish a standalone source-to-model transport/endpoint-completeness audit (including zero-input-word serial-Chi cases); then audit the composition with inherited active-S-box lemmas. The proposed unrestricted eight-round activity improvement `15→16` is **conditional**, and even a sound activity theorem would not establish a concrete 128-bit collision or 256-bit preimage security bound for the actual hash.

**Audit artifacts:** `KRAKKEN_21_FULL_CAMPAIGN_EXTENDED_AUDIT.md`, `KRAKKEN_21_EXTENDED_AUDIT_RESULTS.json`, `krakken_21_extended_audit.py`, ten `KRAKKEN_21_EXTENDED_AUDIT_BATCH_*.json` files, and `KRAKKEN_21_EXTENDED_AUDIT_EVIDENCE.zip`. **Next unassigned working theorem number: `-039`**. The campaign completion itself is a **research-status record**, not a newly promoted universal `[2,1]` theorem.


**Current independent `[2,1]` scan status — user report, 2026-11-05 (`i=228`):** The running spatial campaign has reached **starting-byte position `228`**. If slices `0..227` have each finished with all necessary-condition configurations excluded and no SAT/UNKNOWN, then **8,259,072 / 8,355,840 = 98.84191%** of spatial configurations are closed; **96,768** spatial configurations remain across **27** positions `228..254`, including **6,912** configurations for current position `228`. This is *conditional coverage based on user-reported progress*, not a new verification of checkpoint reports or a global `[2,1]` theorem. Do not interrupt the running campaign. Preserve the outstanding support-completeness, Pressure-model soundness, and UNSAT evidence audits. No new theorem ID is assigned; next working ID remains **`-038`**.

**Latest research update — 2026-11-05 (`WORK-DIFF-H159-R8-MULTIFAMILY-8BIT-037`):** New exact **full eight-round** eight-bit projected differential theorem across **five deliberately different 17-dimensional valid159-message affine families**, rather than the earlier one 22D support. Exact global extrema over `5×(2^17−1)×256=167,770,880` DDT cells: **`310/131072 ≤ Pr[ΔY=t] ≤ 706/131072`** for every nonzero within-family delta and each eight-bit target, all 256 target patterns appear for each delta, and worst TV distance from uniform is **`8120/262144=0.030975341796875`**. Four new families were generated with **524,288 complete unchanged original-C 8R hash calls**; the earlier reference 17D subset was completely regenerated using original C. **Two distinct full-domain integer algorithms** verified all five DDTs (output characters versus 2D class indicators), with 47 directly counted full-base deltas per family and 250 independent original-C hash spot replays. Theorems -035/-036 remain valid with their different domains. This result **does not cover arbitrary message/state deltas or a full-hash collision/preimage exponent**. Evidence: `KRAKKEN_R8_DIFFERENTIAL_THEOREM_037.md`, `KRAKKEN_R8_DIFF8_MULTIFAMILY_037_EVIDENCE.zip`. The running `[2,1]` scan remains **last user-reported i=191, not independently checkpoint-audited**. **Next working ID: -038.**

**Latest research update — 2026-11-05 (`WORK-DIFF-H159-R8-CUBE22-8BIT-036`):** Exact actual-source **full-eight-round** restricted-domain differential-hull theorem for the *same* fixed `2^22` valid159-message input family as `-035`, now observing **eight** digest bits `[11,94,139,210,0,52,128,242]`. All **1,073,741,568** cells `(nonzero Δ, eight-bit target t)` were enumerated by exact integer Walsh/autocorrelation transform. Over uniformly chosen bases in that precisely specified family, **`15308/4194304 ≤ Pr[ΔY=t] ≤ 17464/4194304`**, and **`max_Δ TV(ΔY,U₈)=46884/8388608=0.005589008331298828125`**. Every eight-bit target occurs at every permitted nonzero delta. Independently verified: complete original-C digest archives' hashes, all 4,194,304 eight-bit extraction bytes, all lower-nibble bytes versus previous `-035`, 39 directly enumerated delta histograms (9,984 bins), 96 complete original-C hash replays, and a source-only 1,024-message pilot. **The entire billion-entry global scan currently has one complete integer-FWHT implementation; the independent checks are selected, not a second distinct full global algorithm.** This is NOT an unrestricted 8R differential-probability, collision/preimage hardness, or 256-bit digest-wide bound. Evidence and proof: `KRAKKEN_R8_DIFFERENTIAL_THEOREM_036.md`, `KRAKKEN_R8_DIFF8_036_EVIDENCE.zip`. **Next unused ID: `-037`.**

**Newest separate `[2,1]` campaign update (user-reported 2026-11-05):** The running scan has reached **starting position `i=191`** (previous `i=183`). If all starting positions 0..190 were fully excluded under the necessary-condition models, this is **7,823,360/8,355,840 = 93.62745%** of the spatial enumeration; **532,480** configurations across positions `191..254` remain. This is **conditional coverage math**, NOT a new audited checkpoint, solver-soundness certificate, complete call-level `[2,1]` theorem, or reason to touch/restart the running job.

**Latest research update — 2026-11-05 (`WORK-DIFF-H159-R8-CUBE22-4BIT-035`):** An exact **full-eight-round**, actual-source **restricted-domain differential-hull** theorem now evaluates **all 67,108,848** entries `(Δ,t)` for nonzero 22-bit message differences within one precisely specified `2^22` valid159 affine family, observing digest bits `[11,94,139,210]`. For each `Δ≠0` and all 16 four-bit output patterns `t`, the exact probability over the uniformly chosen 22-bit base satisfies **`258234/4194304 ≤ Pr[ΔY=t] ≤ 266314/4194304`** (global extrema certified), and the **max total-variation distance from uniform** across all such Δ is **`19328/(2·4194304) = 0.0023040771484375`**. Both global extrema and worst-TV Δ were independently reproduced by distinct full-domain integer-FWHT algorithms (character autocorrelations vs output-class convolution); 12 entire `2^22`-pair direct-count Δ checks, 28 source-C spot replays, source/archive hashes, and a 4096-message new original-C compact-projection replay all pass. This is **not** an unrestricted 2048-bit-state, full-256-bit-output, or general 8R differential security bound and does **not** cover the specially conditioned `A1=5` differences from `-025`. Exact proof/data/scripts: `KRAKKEN_R8_DIFFERENTIAL_THEOREM_035.md` and `KRAKKEN_R8_DIFF4_035_EVIDENCE.zip`. **Next unused ID: `-036`.**

**Latest research update — 2026-11-05 (`WORK-LIN-R1-CARRYFREE-034`):** A new exact **single-complete-round** linear-correlation theorem for the actual scalar Krakken source. For each of 32 output coordinates that pull back through Pressure's carry-free bit-zero shears, and **every** 2048-bit input parity mask `α`, uniform unrestricted full-state input has `|Corr(α·X, F_r(X)_j)|≤2^-360` at **any** of the eight round-index constant choices. The 32 individually optimal absolute correlations are explicit products of exactly enumerated 16-bit serial-Chi Walsh maxima; two coordinates attain `2^-360` exactly. This is **not an eight-round correlation/security bound** and does not transfer to the restricted H159 input distribution. Source-tested `72×32=2,304` selected complete-round output bits and independent exhaustive 16-bit FWHT of all **320** distinct active local masks. Full proof and scripts: `KRAKKEN_LINEAR_CARRYFREE_THEOREM_034.md`, `KRAKKEN_LINEAR_CARRYFREE_AUDIT.py`, `KRAKKEN_LINEAR_CARRYFREE_INDEPENDENT.cpp`, `KRAKKEN_LINEAR034_DATA/linear034_result.json`. **Next unused ID: `-035`.**

**Updated independent `[2,1]` spatial campaign (user report, 2026-11-05):** Running at starting position **`i=183`**, advanced from previously reported `i=176`. The **reported position is not a verified checkpoint result**. If slices `i=0..182` are fully closed, then **7,683,072/8,355,840 = 91.95%** of spatial sites have been screened and excluded (more exactly 91.94853%); **672,768** sites remain across positions `183..254`, including **18,432** in slice 183. No solver output for `i=176..182` was supplied or audited here; do not treat them as proved UNSAT and do not modify the ongoing process.

## Current security assessment — 2026-11-05 (qualified, source-pinned)

> **Krakken-256's tested full-eight-round statistical behavior is consistent with that of an ideal random hash in the collision, diffusion, and specially chosen `A₁=5` differential experiments performed. Its 2048-bit state, 1280-bit rate, and 768-bit capacity support conventional 256-bit-digest *security targets*—approximately `2^128` generic collision and `2^256` generic single-target preimage work—**under the ideal-random-permutation sponge assumption**. This is evidence and a conditional design-level guarantee, **not** a proof that the actual deterministic eight-round Krakken achieves these attack-complexity bounds.**

The new 2026-11-05 extension adds three independently classified results:

- **Actual construction, mathematical (`-021`):** Eight-round `K` is bijective; messages differing in exactly one 160-byte padded absorption block never merge to the same **full 2048-bit internal state**, regardless of the number of later identical blocks. Distinct one-block padded messages have distinct full states. **This does not exclude equal 256-bit truncated digests.**
- **Actual construction, mathematical but *reduced one round* (`-022`):** For each of the three pinned valid-159-byte differences conditioned on `A₁=5`, the four one-round digest-coordinate bits 11–14 are within **`(53/2)·2^-392 < 2^-387` total-variation distance** of uniform. This rigorously follows from permanent `LIN-RATE-005` and fresh independent exact 40-rank verification; **it is not a full-eight-round security exponent**.
- **Actual construction, empirical (`-023`):** **1,572,864 deliberately conditioned chosen-message pairs**, measured at rounds 1/2/4/8. At **eight rounds**: zero-difference rates for 12/16 digest prefix bits occurred **384/24 times**, exactly the respective ideal random-hash expectations, and the six groupwise output difference Hamming-weight means ranged **127.974–128.022**. Across R2/4/8, no output-bit bias survived familywise Bonferroni correction. **This tested only three differences** and does not establish general security.

**Inherited full-eight-round affine exclusion (`LIN-GLOBAL-001`):** For every round depth 1–8, including the **original complete eight-round hash**, the permanent ledger records an exact 3,325-message, full-**3321/3321** graph-rank certificate proving **no universally true nontrivial affine equation** `α·m XOR β·F_r(m) XOR c = 0` across all valid 159-byte messages. This includes arbitrary digest-output parity masks. It excludes **perfect** affine input/output distinguishers, not merely those tested statistically. The quantitative correlation bound that follows from this alone is only `|Corr|≤1−2^-1271`, which is far too weak to certify 128-bit security. This existing certificate was not re-run in the present extension.

**New conditional and empirical findings (2026-11-05, `-024`–`-026`):** A published restricted-block sponge theorem (Lefevre, ToSC 2023, Thm. 1) yields a **stronger *ideal-permutation* indifferentiability bound for inputs of 0–159 bytes**: with at most one padded block, the bound is approximately `2^-626` at total query budget `2^128` and `2^-498` at `2^256`. This is not a proven concrete bound on Krakken's fixed 8R permutation and does not apply to unrestricted multiblock inputs. An original-source one-round result gives a **two-query reduced-round distinguisher** for three constructed `A1=5` families: 32 internal difference bits and four digest bits are fixed. After eight rounds, **the pre-registered four-bit difference pattern matched 773/12288 pairs against an ideal reference of 768/12288**, and the six structured birthday corpora had **12298 versus 12287.95 expected 24-bit prefix collisions** (40 versus 48 expected at 32 bits). No full-R8 deviation survived multiplicity correction. These are scoped analyses, not a 128-bit security certification.

**2026-11-05 local Chi support update (`WORK-CHI-CALL-SUPPORT-028`):** Exact source-derived identity `A_Chi = wt8(Δpost-Chi)` for all two-state pairs (both first and second serial S-box calls counted); hence the `[2,1]` spatial campaign enumerates all **post-Chi activity support locations** using 256 output bytes and 128 two-word byte lanes × 2 endpoint branches. The one-call endpoint algebra permits **`ΔA=0` on a first-only branch**; a source-C-verified concrete pair demonstrates it. This settles the *support-counting lemma* but **does not audit whether the scanner's endpoint equations accept every realizable case**. The full `[2,1]` exclusion is **not proved**. The user reports the ongoing run had reached **starting position `i=176`** on 2026-11-05; this is **not checkpoint-verified in this chat**. If 0–175 are fully closed, that would correspond to **7,546,880/8,355,840 sites (90.32%)**. Only the previously audited archive status through 074 and partial 075 remains independently documented in the uploaded ledgers; do not upgrade later positions to verified closure without their records.

**New exact full-eight-round algebraic results (`-029`, `-030`, 2026-11-05):** Independently source-replayed valid-159-byte hash computations yield (i) full rank **32,897/32,897** of every degree-≤2 Boolean monomial evaluated on all 256 digest bits (32,897 explicit message witnesses), proving no nonzero universally vanishing quadratic digest-only equation; and (ii) full rank **256/256** of 256-bit 12-cube XOR-derivative vectors over 257 explicit 159-byte bases (1,052,672 actual full-eight-round hashes), proving every nonzero digest parity has input algebraic degree **≥12** and excluding every universal `β·H8(m)=Q(m)` with `β≠0`, `deg Q≤11`. These are finite, source-pinned algebraic exclusions **not** quantitative collision, preimage, or general differential-probability bounds. Full write-up and reproducible programs: `KRAKKEN_R8_ALGEBRAIC_THEOREMS_029_030.md` and included verifier package.

**Evidence hierarchy:** Full eight-round statistical compatibility and ideal-model parameter guarantees are positive, *scoped* findings. Actual full-round collision and preimage resistance remain unproved and require further independent cryptanalysis. Full sources and reproductions: `KRAKKEN_SECURITY_GUARANTEES_AND_CONDITIONED_A15.zip`, `SECURITY_RESULTS.md` therein. Inherited security theorem ledger is unchanged.

**New source-verified full-eight-round 22-bit cube theorems (`-031`, `-032`, 2026-11-05):** For all nonzero 256-bit masks on the Krakken-256 digest, and consequently on the first 256 output coordinates of the original eight-round 2048-bit permutation, the Boolean component has global input algebraic **degree ≥19**. A complete 22-message-bit affine family of **4,194,304 valid 159-byte messages** produced **1,330 exact 19th-degree coefficient vectors of rank 256/256**, confirmed by independent NumPy low-pivot and C++ high-pivot ANF/rank implementations, and a direct original-C 524,288-query 19-cube derivative replay. The **first 64 digest bits are injective on this same finite family** (zero 64-bit/full-digest collisions), while **all 262,144 possible 18-bit digest prefixes occur**, each with 2–36 witnesses. These are *actual fixed-source finite-domain* algebraic and prefix/collision theorems, **not** unconditional `2^128` collision or `2^256` preimage work guarantees, nor a general differential probability exponent. Full derivations and source-pinned evidence: `KRAKKEN_R8_CUBE22_THEOREMS_031_032.md`.

**New source-pinned complete-eight-round full-state algebraic theorem (`WORK-PERM-R8-FULLSTATE-DEGREE20-033`, 2026-11-05):** For **every** nonzero mask `β` on **all 2,048 output bits** of the actual eight-round `K8`, the Boolean component `β·K8(x)` has global algebraic degree **at least 20**. An explicit 24-message-bit affine subspace (16,777,216 eight-round permutation inputs) supplies **5,985 degree-20 2048-bit ANF coefficient vectors with full GF(2) rank 2048/2048**. Independent Python low/high and separately implemented C++ high-pivot audits agree; an entire 1,048,576-query, **unmodified-original-C** 20-cube replay exactly matches all 2,048 coefficient bits, and 8,192 original-C full-state checks agree with the bytewise-equivalent analysis-only fast S-box. The first two subcubes also match **4,194,304 previously archived original-C digests** byte for byte. This strictly supersedes `-031`'s bound 19 on the first 256 bits: the **H159 hash digest** inherits degree≥20 for every nonzero output parity. **It is an algebraic-degree exclusion, not a concrete 8-round collision/preimage/differential/linear security-work exponent**; the `[2,1]` scan remains last *user-reported* at position `i=176` and is not resolved here. Proof and exact files: `KRAKKEN_R8_FULLSTATE_DEGREE20_THEOREM_033.md`. **Next unused working theorem ID: `-034`.**

## Executive result board

| Attack family / property | Domain, quantified class | Boundary and precise result | Status / inherited theorem |
|---|---|---|---|
| **Completed `[2,1]` spatial scan (status) and low-k Pressure necessary-model lemma `-038`** | All 8,355,840 enumerated support labels, 255 starting slices, actual pinned scalar source; Pressure `k=1,3,4,5,6,7` | **0 reported unresolved; 4,141/4,141 final-tier SMT replay UNSAT; exact low-k Pressure arithmetic over-approximation.** Not a globally certified `[2,1]` exclusion or eight-round security exponent. | **Computational closeout + source-derived scoped theorem `WORK-PRESSURE-LOWK-OVERAPPROX-038`; full global `[2,1]` theorem pending.** |
| **Eight-round restricted 4-bit differential-hull DDT — NEW exact theorem** | Actual original-C full R8 Krakken-256, a *single* fixed 22-dimensional affine family of 159-byte messages, **all** 4,194,303 nonzero in-family XOR input differences, four digest bits `[11,94,139,210]`, every 4-bit output difference | Exhaustive **67,108,848** 4-bit DDT entries: all counts `258234..266314` out of `2^22` bases; pointwise deviation from `1/16` ≤`4170/2^22≈0.000994206`; maximum TV to uniform over all allowed Δ equals **`0.0023040771484375`**. **Not an unrestricted full-8R DP bound.** | **`WORK-DIFF-H159-R8-CUBE22-4BIT-035`**, two *independent exhaustive* full-domain integer-FWHT decompositions, 12 direct full-domain Δ bucket counts and source-C/archived-data provenance replays. |

| **Complete original single-round carry-free-coordinate linear bounds — NEW exact theorem** | **Actual full 2048-bit one-round `F_r`**, uniform unrestricted state, 32 selected output-bit coordinates, **all 2048-bit input parity masks**, any r=0..7 | **Maximum over all input masks of each fixed coordinate's absolute linear correlation is ≤`2^-360`**, with equality for full-round output bits **395** and **907**. Exact product of 128 disjoint Chi-lane Walsh spectra (80–122 active) after pulling the 32 selected output bits through exact Pressure bit-zero identities and Butterfly transpose; **not a full 8R correlation bound**. | **`WORK-LIN-R1-CARRYFREE-034`**; 320 locally distinct output-mask 16-bit exact FWHT confirmations, 2,304 source-C complete-round selected-bit comparisons, 32 exact rational product bounds. No transfer to 159-byte hash distribution or eight-round linear hulls. |
| **Full original 8R permutation: every nonzero 2048-bit output parity has algebraic degree ≥20 — NEW exact theorem** | **Actual K8**, all 2048-bit inputs, all nonzero 2048-bit output masks; **H159** 256-bit digest corollary | A fixed 24-input-bit affine cube (16,777,216 actual 8R permutation inputs) yields **5,985 exact degree-20 2048-bit ANF coefficients of full rank 2048/2048**. Every nonzero `β` has `deg(β·K8)≥20`; hence no universal `β·K8(x)=Q(x)` for `deg Q≤19`. Also `deg(β·H8(m))≥20` for every nonzero digest mask over valid159 messages. | **`WORK-PERM-R8-FULLSTATE-DEGREE20-033`**; independent Python low/high-pivot and C++ high-pivot all full rank; 8,192 original-C/optimized full-state matches across all eight subcubes; **1,048,576-query original-source complete 20-cube replay** matches all 2048 bits. Analysis-only S-box acceleration proved bytewise equivalent and exhaustively source-checked for 4,194,304 original-C digest values. **Not a concrete collision/preimage/differential security exponent.** |
| **R8 all-digest-parity algebraic degree ≥19 — NEW exact theorem** | **Actual full R8 H159**, every nonzero 256-bit digest parity; also **actual R8 2048-bit permutation**, all nonzero parities supported in first 256 output bits | Explicit 22-bit affine valid-message cube (4,194,304 original-C hashes). The 1,330 19th-degree ANF coefficient vectors containing bit21 span **rank 256/256**. Therefore each nonzero parity has global input ANF degree **≥19**; no universal `β·H8(m)=Q(m)` with `β≠0`, `deg Q≤18`. | **`WORK-HASH-R8-CUBE22-DEGREE19-031`**; two source-C full-cube streams, independent NumPy+reverse-pivot C++ rank 256/256, direct 524,288-call source-C 19-cube replay. Supersedes 12-degree floor `-030` (which remains a valid inherited theorem). **Not collision/preimage security bits.** |
| **R8 finite 22-bit message-subspace prefix/collision exact census — NEW** | **Actual H159**, one explicitly seeded `2^22`-message family only | **0** collisions in the first 64 digest bits (hence zero full-256 collisions) across all 4,194,304 inputs. Every one of **262,144 possible first-18-bit prefixes** occurs, each **2..36 times**. For uniform inputs from that family, max first18-prefix probability is exactly **36/2^22**, giving `H∞≥16.830075` bits for those 18 output bits. | **`WORK-HASH-R8-CUBE22-PREFIX-COLLISION-032`**; full original-C enumeration, exact independent cross-half prefix64 sorting and prefix16/17/18 histograms. **No collision-preimage bound for unrestricted messages.** |
| **Full-R8 universal digest-parity algebraic degree floor — NEW exact finite theorem** | **Actual H8**, all valid 159-byte messages, **all nonzero 256-bit digest parity masks**; fixed 12-message-bit cube (byte 0 + low nibble byte 1) | 257 explicitly generated bases × 4096 messages = **1,052,672 full-source eight-round hashes**; 256 derivative witness rows have exact GF(2) **rank 256/256**. Therefore `deg(β·H8(m))≥12` for every `β≠0`; no universal `β·H8(m)=Q(m)` for any input-only degree `≤11`. | **`WORK-HASH-R8-CUBE12-DEGREE-030`**. Exact finite-witness mathematical theorem; independent Python opposite-pivot full-rank TSV audit and 4/4 original-C 4096-query derivative replays. **Not a collision/preimage exponent.** |
| **Full-R8 no universal quadratic digest-only invariant — NEW exact finite theorem** | **Actual H8**, valid 159-byte messages, all **256 digest bits**, all output-only Boolean equations of degree `≤2` | Explicit **32,897** distinct valid messages produce a **32,897×32,897 GF(2) monomial-evaluation matrix of full rank**. Hence no nonzero universally vanishing polynomial of degree `≤2` in the complete digest. | **`WORK-HASH-R8-QUADRATIC-029`**; exact source-linked GF(2) elimination, independent original-C digest stream replay, **separate full-256 reverse-pivot elimination (PASS 32,897/32,897)**, and Python 64-bit subrank audit. **Not an 8R collision bound.** |
| **Serial-Chi active-call/output-byte support equivalence — NEW local theorem** | **Original full scalar Chi**, every pair of unrestricted 2048-bit states, all 16 two-word cells | `A_Chi = wt8(Δpost-Chi)` exactly; in particular `A=2` iff exactly two distinct post-Chi bytes differ, and `A=1` iff exactly one. Exhaustive spatial support labels `i<j`, `q` and `branch` therefore cover **locations**, but not necessarily all scanner endpoint assignments. First-only endpoint can have `ΔA=0`; explicit original-C witness. | **`WORK-CHI-CALL-SUPPORT-028`**; mathematical proof from bijective ABYSSAL and source equations; repeat independent Python/original-C audit PASS. **Not a global `[2,1]` theorem.** |
| **Selected 12-bit second-to-eighth-round digest-difference surjectivity — NEW exact finite theorem** | **H159**, 3 fixed valid-message input differences conditioned on `A1=5`; 12 digest bit positions `[0,11,23,52,77,94,111,139,154,184,210,242]`; every round depth `r=2..8` | For **every** input difference and round depth, **all 4096/4096 output-difference patterns** are achievable by real valid 159-byte pairs (`3×7×4096 = 86,016` source-C-verified witnesses). Excludes any universal missing-pattern constraint or fixed parity on this projection. Does **not** show uniform probabilities, collision bounds, or arbitrary projections. | **`WORK-DIFF-A15-PROJECTION12-SURJECTIVE-027`**, exact witness existence, separately compiled unmodified original-C verifier. |
| **One-block ideal sponge strengthening — NEW, published conditional theorem** | **H, padded 0–159-byte inputs only**, `b=2048`, `ra=rs=1280`, `ca=cs=768`, `ell=1`; **replace actual K by ideal random permutation** | Lefevre ToSC 2023 Theorem 1 gives `Adv_ideal ≤ [qP(12 ln q+15372)+20q]/2^768 + 3q²/2^2048`; at `q=2^128`, `≤≈2^-626`, at `q=2^256`, `≤≈2^-498`; strictly stronger reference than generic `~q²/2^768` for this limited-input domain | **`WORK-SPONGE-ONEBLOCK-IDEAL-024`**. **Published ideal-model theorem adapted to source-pinned padding, NOT actual fixed-K security**. |
| **Two-query one-round conditional differential distinguisher — NEW, exact actual-source theorem** | **H159, one round only**; each of three specified XOR differences, conditioned on `A1=5` | Exactly **32 predetermined full-state XOR bits** after R1, including digest-position bits `[11,94,139,210]`; all three digest vectors nonzero; **2-query** reduced-one-round hash advantage **15/16** vs random function. Exact original-C replay `12288/12288` for 32-bit pattern. | **`WORK-DIST-A15-R1-TWOQUERY-025`**. Explicit algebraic proof, original C, no R8 claim. |
| **Structure-aware chosen-difference birthday search — NEW empirical** | **H159**, 3 constructed `A1=5` differences × 2 seeds × 131072 pairs = 1,572,864 messages per hash method; R1/R2/R8 and SHA256 control | Full R8 24bit prefix collision pairs **12298** vs ideal **12287.95**, 32bit **40** vs ideal **48**; **6 original-C-verified 32bit truncated collision pairs**, full digests differ. R8 pre-specified 4-bit differential pattern **773/12288** vs ideal **768/12288**; no multiplicity-corrected significance. | **`WORK-EMP-A15-STRUCTURED-BIRTHDAY-026`**, actual 8R empirical only, non-adaptive search, no full-hash security exponent. |
| **Original 8R conditioned chosen-difference digest diagnostics — NEW** | **H159**, three *specified* nonzero XOR differences with `A₁=5` sampled uniformly under the ideal PRNG assumption; 2 independent seeds; 1,572,864 generated chosen pairs per round depth | At R8, mean 256-bit XOR HW **127.974–128.022** across six groups; zero-difference counts on digest prefixes t=12/16 are **384/24 vs ideal 384/24**; no marginal bit bias survives 1,536-test familywise correction. Strong R1 bias disappears in tested R2/4/8 statistics. | **`WORK-EMP-CONDITIONED-A15-R8-023`**, original-C cross-checks, real conditioned seed families. **Empirical only, not a concrete security exponent.** |
| **Conditioned first-round digest 4-bit uniformity — NEW theorem** | **H159**, three explicitly fixed Δ, *uniform base conditioned on `A₁=5`*; one full round reduced hash; **only state/digest bits 11–14** | Four-bit total-variation distance from uniform **≤`(53/2)·2^-392≈2^-387.272`**; all nonzero parity biases ≤`L_s·2^-392`; dependence-safe Fourier conditioning on 32 affine fibers of codimension 40. | **`WORK-LIN-CONDITIONED-A15-022`** derived from inherited **`LIN-RATE-005`** plus fresh independent original-C prefix rank40/40 in all 3 families; **not an R8 result**. |
| **Full-state one-block nonmerging and ideal sponge budget — NEW theorem/reference** | **Actual 8R P and H**, any padded block sequences with exactly one differing rate block; **ideal** sponge reference separately | Full `K` is invertible ⇒ **no complete 2048-bit state collision** for any such pair, across any common suffix; original 0–159-byte valid single-block inputs inject into full state. For **ideal random permutation** `c=768`, `Adv_indiff(N)≤N(N+1)/2^769`; at N=2^128 bound ≈2^-513 and at 2^256 ≈2^-257. | **`WORK-SPONGE-INJECTIVITY-021`** source algebra + Python independent full 8-round inversion; **actual H256 digest collisions not excluded and ideal-model bound does NOT apply to fixed `K`**. |
| **Quantified reduced-1R distinguisher + full-R8 birthday-reference experiment — NEW** | **H159 reduced 1R**, exact 12-bit cube; and **full H8** on 159-/161-byte messages | Earlier 25-mask 1R integral implies **4096-query random-permutation distinguishing advantage ≥1−2⁻²⁵−4096·4095/2²⁰⁴⁹**; the single digest-only bit 11 gives reduced-one-round random-function advantage **1/2**. Full 8R collision-prefix counts for four 131072-message corpora match ideal birthday scales; four 32-bit prefix collision pairs independently replayed in unchanged original C, with distinct 256-bit digests. | **`WORK-DIST-REDUCED-R1-020`**. Mathematical corollary is **one-round only**; full eight-round tests are **finite empirical evidence** and establish no security exponent. |
| **Universal linear-mask byte integrals — NEW** | **H**: all 159 one-byte coordinate-cube families, every valid base, **all 2048-bit linear masks** | **Every family has nontrivial balances after complete R1 (dimension 2–26), and none after complete R2 (dimension 0)** | **Verified analytic + full scalar-C finite certificate**; working ID `WORK-INT-ALL159-001` |
| **Nonlinear nibble integrals — NEW** | **H**: 159 input-byte cubes × 512 aligned 4-bit full-state output projections; all 65,536 Boolean truth tables for each | **After complete R2, only constant predicates have base-independent cube XOR parity**, 81,408/81,408 families | **Verified finite full scalar-C certificates**, independent affine-rank audit; working ID `WORK-INT-NIBBLE-ALL159-002` |
| **Cross-byte nonlinear 4+4 integrals — NEW** | **H**: all 159 one-byte coordinate-input cubes × **32 explicitly selected two-byte 4+4-bit output windows**; every Boolean function of the mixed 8-bit projection | **After complete R2, only constant predicates have base-independent cube XOR parity**, 5,088/5,088 selected families at maximal affine-difference rank 255; 361 first-round linear-mask spaces (415 directions) are lost | **Verified original scalar-C finite spanning certificate**, independent opposite-pivot full replay and Python/ctypes checks; working ID `WORK-INT-MIXED44-ALL159-004` |
| **Nonlinear full-byte integrals — NEW** | **H**: 159 coordinate-input-byte cubes × 256 aligned output bytes; **every Boolean truth table on each output byte** | **All 40,704 families: after complete R2, only constant predicates have base-independent cube parity** (rank 255/255); 232 linear-byte R1 balances are lost | **Verified scalar-C finite spanning certificate** and low-pivot full-source replay; working ID `WORK-INT-BYTE-ALL159-003` |
| **Nonlinear nibble R1→R2 transitions — NEW** | Same H families, restricted at R1 to linear output-nibble predicates | **232 position/nibble pairs across 71 input positions have a nonzero universal R1 linear balance; all lose every nonconstant base-independent predicate at R2** | R1 inherited `WORK-INT-ALL159-001` exact mask classification; R2 new finite certificates |
| Digest-position linear byte integrals — NEW | Same 159 families, masks supported only on first 256 state bits (reduced-round digest coordinates) | R1: 33 positions have nonzero universal masks (27 with dimension 1; six with dimension 2); R2: all 159 have dimension 0 | Corollary of `WORK-INT-ALL159-001` and independent digest-rank audit |
| **Two-Chi-cell diagonal-1 → Butterfly → Pressure: complete-round differential probability bound — NEW** | **P unrestricted uniform round input**; every unordered pair of distinct aligned Chi cells (8,128 pairs); exactly two active input cells each with aligned byte differences `(0x01,0x01)` after linear prefix | For **any full 2048-bit prescribed complete-round output XOR difference**, **DP < 1/4**; worst source-certified integer upper bound **274865743872 / 2^40 ≈ 0.249988937750459** at site pair `(0,4)`; all **131,096,512** attainable two-cell Chi-output difference profiles covered; 56 pairs have some deterministic low5 Pressure projection patterns, still excluded by the full composition cap | **`WORK-DIFF-COMPOSE-TWOCHI-DIAG1-009`**; original-C exhaustive integer-upward-bound scan, independent NumPy full recount, Python arbitrary-precision exact rational spot certificates, 2048 source Butterfly basis checks, 384 original-C complete-round replays. **Not arbitrary two-cell differences, restricted H or multiround security** |
| **Chi → Butterfly → Pressure: certified complete-round differential bound — NEW** | **P unrestricted uniform round input**; all nonzero fixed input differences whose linear-prefix image activates exactly **one aligned 16-bit Chi cell** (128 × 65,535 distinct differences) | For any prescribed full 2048-bit **complete-round** output difference, class-dependent exact rational upper bounds are at most **0.444226843** (`Chi` MDP `2^-6`), **0.311414343** (`2^-7`), or **0.054090124** (`2^-12`); universally **<1/2**, and tighter **<1/3** or **<1/16** by class | `WORK-DIFF-COMPOSE-ONECHI-008`; exact GMP certificate of all 8,388,480 one-cell suffix patterns, independent NumPy full recount, original-C replay, and existing `DIFF-CHI-002`. **No multiplication of dependent Chi/Pressure probabilities; no multiround or valid-hash security claim** |
| **Pressure full-word affine rulebook (14–16 exact parity circuits) — NEW** | **U**: a standalone original Krakken two-addition 64-bit Pressure shear, *every fixed 256-bit input/output XOR-difference profile* | The complete derivative-**affine relaxation** reduces to two difference-LSB checks, certain zero-row checks, and **14–16 guarded parity circuits** depending on 3 low difference bits; eight 126-row libraries have rank 111/112. For uniform standalone `(a,c)`, any prescribed differential has probability **≤2⁻ᵏ**, with `k` the rank of its consistent projected `(c,A)` equations; **not** a conditional H probability. Independent audit reproduces all eight finite library circuit counts and compares against full 256-variable elimination on 12,000 profiles. | **`WORK-PRESS-FULLWORD-AFFINE-RULEBOOK-019`**; independent reconstructed matrix/circuit certificate + 10,000 direct Pressure-difference identities. Existing fixed-three-delta `A₁=5⇒A₂≥4` endpoint scan independently rechecked (124,502/124,502 rejected), but **all fail elementary zero rows: none needs parity circuits**. No new global activity floor, hash probability exponent, or exact Pressure feasibility claim. |
| **Pressure low-five-bit differential feasibility & 16-pair composition — NEW** | **U**: 16 unrestricted Pressure arithmetic shear pairs; all five 5-bit projected XOR input/output profiles; fixed 2048-bit Pressure input differences and uniform independent component bases | **2,523,208/33,554,432 possible**, **31,031,224 impossible**; **837,816 additional exclusions** beyond lifted exact low4; precise projected local probabilities, with exact 16-shear product bound for the *standalone Pressure map*. Example fixed 2048-bit input difference gives any full Pressure output differential probability **≤2^-96** | `WORK-PRESS-DIFF-LOW5-007`; full 2^30 C enumeration, independent NumPy full-table replay (SHA identical), original-C source checks, carry-state DP and independent k6/k7 spot proofs; **not** a global Krakken-round bound |
| **Pressure low-four-bit differential feasibility — NEW** | **U**: each of the 16 unrestricted two-word (2×64-bit) A/C or B/D shears; every five-nibble projected XOR input/output difference profile | **Exactly 105,032/1,048,576 possible; 943,544 impossible; 35,000 exclusions beyond lifted exact low-three-bit test**; exactly seven nonzero deterministic *low4 projections*; all other nonzero projected input differences have individual local output probability ≤1/2 under uniform local bases | `WORK-PRESS-DIFF-LOW4-006`, exact exhaustive finite C + independent NumPy full-table audit, and 48,192 original-C branch replay checks; **local projection only**, not a full-word or multiround probability bound |
| **Truncated differentials — carry-free Pressure-bit refinement (NEW)** | **P**, 128 aligned one-cell pre-Chi difference sites × every nonzero 8-bit diagonal difference | Previous site `(p,y,j)=(0,0,0)` zero-output guarantee **200 → 210 bits** at complete R1; all 128 sites gain **1,056 aggregate additional guaranteed zero-coordinate incidences**, 123/128 sites improved. Specified bit-11 deterministic relation refuted by counterexample separately at R2–R8 | `WORK-DIFF-TRUNC-LSB-005`, derived strengthening of `DIFF-TRUNC-001`; independent source-pinned analytic-basis enumeration and C replay. **Attack-side result**, not a general R2 differential exclusion |
| **Reduced Experiment 5: MDS/Chi/Butterfly/Pressure R1=4 ⇒ R2≥2 — NEW** | **H159, reduced construction only**, same five-layer ablation as `-011` | If **A₁=4**, then **A₂≥2** (all four post-Chi output bytes share a row; Butterfly stage 0 creates both row parities; subsequent layers preserve both). Thus **N_active(2)≥6** and per-depth 1..8 lower bounds **[4,6,7,9,10,12,13,15]**. Exact two-round optimum **unknown** | **`WORK-REDUCED-MDS-BFLY-PRESS-ACT-012`**; analytic source-indexed proof including odd-row rotation-invariance exception; 65,280 stage-0 checks, 2,048 source-C Butterfly basis comparisons, 8,192 original-C four-byte suffix checks, independent finite activity DP. **Reduced variant only, not full hash or an 8R probability bound.** |
| **Reduced Tentacle→Chi→Butterfly→Pressure exact first-round activity — NEW** | **H159, reduced construction only** (`Tentacle MDS→serial Chi→Butterfly→Pressure→Iota`; no Theta/Rho/Pi/InkCloud) | **Exactly A₁,min=4** for valid 159-byte messages (universal proof + new original-C witness); **Aᵣ=1⇒Aᵣ₊₁≥2**; original conservative total **ΣAᵣ≥14** is **superseded by ≥15** from `WORK-REDUCED-MDS-BFLY-PRESS-ACT-012`; independent C witness `[4,254,256,256,253,256,256,255]` total **1,790** | **`WORK-REDUCED-MDS-BFLY-PRESS-ACT-011`**; independently audited 12,869/12,869 Tentacle minors, source-pinned two-execution 159-byte witness and 8R reduced-round replay; existing Butterfly rank certificate. Reported 1,778 upper witness **not supplied/independently replayed**; no full-Krakken or DP security claim. |
| **Reduced Chi→Butterfly→Pressure activity — NEW** | **Reduced U**: serial Chi, Butterfly, Pressure, Iota/round constants only; **no Theta/MDS/Rho/Pi/InkCloud** between Chi calls; every nonzero pair of reduced states | **Aᵣ=1 ⇒ Aᵣ₊₁≥8** byte S-box calls with Pressure; **≥16** for the distinct reduced Chi→Butterfly→Iota variant without Pressure; exact 65,280/65,280 single-byte Butterfly differences hit **all 32 state words**, certified by 8,192/8,192 byte-to-word GF(2) rank-8 maps; Pressure even/odd invertible shears force ≥8 next Chi calls | **`WORK-REDUCED-BFLY-PRESS-ACT-010`**; original C exhaustive, independent Python source-basis rank, analytic Pressure/Chi proof. **Reduced construction only; not original eight-round P/H, nor a differential probability bound** |
| **Original full Chi→Chi one-call / three-cell low-bit impossibility gate — NEW** | **P unrestricted**, any adjacent full rounds; first Chi exactly one active S-box, next pre-Chi support contained in three selected cells | Exhaustive exact GF(2) Pressure low-bit gate eliminates **10,138,251,288 / 22,285,025,280 named `(source byte,difference,3 next-Chi cells)` configurations (45.4936%)**. The remaining **12,146,773,992** pass only the necessary-condition relaxation. **Does not prove `Aᵣ=1⇒Aᵣ₊₁≥4`**. | **`WORK-DIFF-FULL-ONECHI-THREECELL-LSB-016`**, source-pinned original-C 2,048 prefix basis checks, 8,192 direct Pressure/Ink/next-prefix replays, 341,376×256 exact rank scans, full independent opposite-pivot recount and record match. No real-trail SAT claimed. |
| **Original full inter-round 1/2-call Pressure-support gate — NEW** | **P unrestricted**, any adjacent rounds; `A_r=1` or `A_r=2` | **`A_r=1 ⇒ B_r=16, W_(r+1)≥16`**, with ≥8 active even and ≥8 odd input words next round. **`A_r=2 ⇒ B_r≥8, W_(r+1)≥8`**; for 30,720/32,640 post-Chi two-byte support pairs, stronger **`B_r=16`**. Exact byte-position/rank classification, and a genuine 2-call C witness attaining 8 groups. **Does not imply `A_(r+1)≥8`!** | `WORK-DIFF-FULL-INTERROUND-SPARSE-015`; 2,048 original-C/Python Butterfly basis matches, 522,240 128-bit projection ranks with independent opposite-pivot recount, two original-C unrestricted full-round witnesses; support theorem only, not probability or hash claim. |
| **Original full round, all single-byte full-state differences and single-word paired gate — NEW** | **P unrestricted**, all 256 state-byte positions × 255 nonzero differences; separate all 32 one-word source positions | **Exactly 52** minimum active byte-S-box calls within Chi for the one-byte class (65,280 cases; source-C matching unrestricted-state witness). For every nonzero single-64-bit-word difference entering a round, **all 16 Chi word-pairs are active**, hence **at least 16 Chi S-box calls** (512/512 paired maps rank64). Individual word projections can have rank **8**; not all 32 words necessarily remain active. | `WORK-DIFF-FULL-WIDETRAIL-014`; independent C/Python complete-byte DDT audit, 2,048/2,048 prefix+inverse basis agreement, 512 paired-map ranks, 1,024 individual-map ranks, original-C attainment. **One-round only; neither multiround probability nor hash security bound.** |
| **Original full Krakken, one-byte message XOR differences — NEW** | **H159**, all 159 valid variable message-byte positions and all 255 nonzero XOR byte values; every base message | **First Chi has at least 52 active ABYSSAL calls** for all 40,545 `(position, difference)` classes; inherited full-P `1→≥3` rule gives cumulative activity floors **R2≥53, R4≥57, R8≥65** for this *restricted* family. An unrestricted-base pair attains the first-round local floor 52, but no H159 attaining message pair is asserted | **`WORK-DIFF-FULL-SINGLEBYTE-013`**; full finite exact S-box DDT + independently checked GF(2)-linear prefix and original-C Chi witness. No new A₂ bound alone, and no differential probability / generic message claim. |
| Differential activity across consecutive rounds | **P**: unrestricted nonzero full-state differences | Aᵣ=1 ⇒ Aᵣ₊₁≥3; `[1,1]` and `[1,2]` excluded | Inherited `DIFF-PERM-002`, `DIFF-PERM-003` |
| Tightened eight-round activity bound | P unrestricted; H valid 159-byte first hash block | ΣAᵣ≥**15** on P; ΣAᵣ≥**18** on H; **19** for three studied H differences conditioned on A₁=5 | Derived arithmetic corollary `WORK-DIFF-ACT-2026-11-03`, inherited `DIFF-PERM-003`, `DIFF-RATE-001/003`; **not** full-trail probability |
| Special local Pressure translations | U unrestricted Pressure inputs, all 65,535 nonzero directions in defined 16-D translation space | Local deterministic directions exist; universal deterministic continuation is disrupted by complete R2 | Inherited `PRESS-TRANS-001`; valid-message reachability remains open |
| Differential-linear perfect mask continuations | 128 fixed unrestricted input differences, all nonzero output linear masks | Specified perfect correlations eliminated at complete R2 | Inherited `DL-002` |
| Nonlinear integral predicates | One saved H kernel cube, 16 specified 8-bit projections, arbitrary Boolean functions of each | Nonconstant universal predicates exist at R1; at complete R2–R8 only constants remain | Inherited `INT-NONLINEAR-001` |
| Algebraic mixed relations | Specified 4-bit/4-bit observation windows on H, all Boolean equations | Defined perfect relations exist at R1 for selected windows; at complete R2–R8 they are absent | Inherited `ALG-REL-001` |
| Perfect affine relations | H, all fixed message/state affine masks | No nontrivial perfect affine relation after each complete R1–R8 | Inherited `LIN-GLOBAL-001`; nonperfect statistical correlations not excluded |
| Perfect rotational covariance | P and specified round/correction model; all 63 nonzero common rotations | All excluded at complete R1 | Inherited `ROT-001`; not a general rotational-bias bound |
| Sparse differential `[2,1]` | **P unrestricted**; 8,355,840 spatial sites in the original low0/3/4/5/6 model plus targeted low7 refinements | **Last independently archived checkpoint (as documented here):** positions 031–074 all complete, 075 partial at 22,000; linked 500/500 low7 survivors UNSAT across 036/044/066/074. Conditional historical aggregate completed 000–074: **4,185,600/8,355,840 (50.09%)**, examined including 075 partial **4,207,600 (50.36%)**. **New user-reported progress (2026-11-05):** run at `i=176`; if 0–175 closed, cumulative **7,546,880 (90.32%)**, but later checkpoint files have **not been supplied/audited**. | **Ongoing; no global theorem.** Local Chi support equivalence now proved by `WORK-CHI-CALL-SUPPORT-028`. Still audit scanner endpoint equations (including zero input-word difference), Pressure model soundness, remaining parent/child checkpoint integrity and UNSAT claims. |

**Reading the board:** H = exactly 159 bytes with fixed `0x86` padding and zero initial capacity; P = unrestricted permutation input; U = unrestricted Pressure-state model. `Chi2` is a checkpoint **inside** round two, whereas `R2` is a complete round. Statements about an exact subclass do not say that an entire broad attack *technique* is impossible. Several attack-side structures (including exact local serial-Chi and Pressure translations) are known and retained as part of the security assessment.

---


---



## WORK-DIFF-FULL-ONECHI-THREECELL-LSB-016 — Exhaustive 16-bit one-call → three-cell Pressure feasibility gate

# Krakken full permutation — an exact 16-bit inter-round gate for one-to-three-cell differential supports

**Working theorem ID:** `WORK-DIFF-FULL-ONECHI-THREECELL-LSB-016`  
**Research date:** 2026-11-04  
**Source:** original unmodified `krakken.c` SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, original `krakken.h` SHA-256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

## Precise theorem

Take two arbitrary distinct 2048-bit Krakken states entering any two *adjacent original full rounds*. Suppose exactly **one byte S-box call** is active in serial Chi of the first round. Then its post-Chi output difference is one nonzero byte `d` at some byte position `s` in `{0,...,255}`. Suppose further that the **input difference to the next round's Chi** is supported in the *union of any three specified 16-bit serial-Chi input cells* `(i,j,k)`, `0 ≤ i < j < k < 128`. Each such cell contains the two byte inputs to the first and second serial-Chi calls, in their original rotated indexing.

**Necessary condition:** A source-pinned, exactly computed GF(2) relation of 16 bit-zero equations must hold between `(s,d)` and `(i,j,k)`. Among all

`256 × 255 × C(128,3) = 22,285,025,280`

named configurations, **10,138,251,288 are incompatible with this necessary condition** and therefore contain **no real original-Krakken adjacent-round pair** with the specified post-Chi byte difference and next-Chi support. The remaining **12,146,773,992** pass *only the relaxation*. This is **45.493559736%** of the named configurations excluded and **54.506440264%** still unresolved.

The next-round support may be *contained* in the selected three cells; the certificate does not require all three cells to be active. This makes exclusions valid also for any smaller support contained in an excluded triple. The 341,376 triple supports **overlap**; these counts are **not** counts of distinct differential trails. No global improvement to `A_r=1 ⇒ A_(r+1)≥3` is claimed.

## Derivation from original Pressure — no probabilistic assumptions

For each `c=0,...,7`, the original Pressure shear uses the independent two-word branches `(a,c_word)=(state[4c],state[4c+2])` and `(b,d_word)=(state[4c+1],state[4c+3])`. Internally, the second addition in each branch has the form

`c' = c_word + (a' XOR (a' << 31)) (mod 2^64)`  
`d' = d_word + (b' XOR (b' << 31)) (mod 2^64)`.

Consequently, for **every base state**, the least-significant bits obey

`c'_0 XOR a'_0 = c_word,0`  
`d'_0 XOR b'_0 = d_word,0`.

The original Pressure rotates the output `b'` by 7 bits and `d'` by 19 bits. Iota's XOR constants cancel in state differences. InkCloud rotates each output word by 11 bits and permutes words with destination `(7*i) mod 32`; it is linear and invertible. The next-round prefix

`L = Pi ∘ Rho ∘ Tentacle ∘ Theta`

is also GF(2)-linear and invertible. Therefore the 16 bit-zero shear identities can be expressed exactly as a **linear** map

`E: Δ(pre-Chi of round r+1) -> GF(2)^16`

where E reverses `L` and InkCloud and reads XORs of output bit-zero of each shear, including undoing the respective 7/19-bit rotations. The 16-bit expected right-hand side is the linear map

`R(Δ(post-Chi of r)) = (Δ Butterfly(state)[4c+2]_0, Δ Butterfly(state)[4c+3]_0)_(c=0..7)`.

Every real adjacent-round differential pair satisfies `E(next pre-Chi difference) = R(one-byte post-Chi difference)`.

For each next-Chi input cell `i`, construct the image of its two eight-bit input coordinates under E. For the selected triple, call the span of all **48** corresponding image vectors `W_(i,j,k) ⊆ GF(2)^16`, of rank `w`. For first-round post-Chi byte position `s`, let `Q_s` be the eight-column GF(2) matrix mapping `d ∈ GF(2)^8` to the 16-bit `R` value. Its rank is at most 5 in these actual maps. Necessarily,

`Q_s(d) ∈ W_(i,j,k)`.

Thus, without iterating over 255 difference values individually, the **exact number** of nonzero values `d` that survive the relaxation for any `(s,i,j,k)` equals

`2^(8 + rank(W) - rank([W,Q_s])) - 1`.

This follows from rank-nullity applied to the preimage `Q_s^{-1}(W)`. It is an integer identity, not a heuristic, average-case assumption, or probabilistic estimate.

## Exhaustive certificate results

| Quantity | Exact count |
|---|---:|
| Distinct three-cell support choices | **341,376** |
| Post-Chi source-byte positions | **256** |
| Nonzero post-Chi output-byte difference values | **255** |
| Total named configurations | **22,285,025,280** |
| Impossible under the exact low-bit necessary equations | **10,138,251,288** |
| Pass the low-bit relaxation only | **12,146,773,992** |
| Excluded percentage | **45.493559736%** |
| Three-cell supports whose image already spans all 16 low-bit coordinates | **36,297** |

There are **5,984** triples whose E-image is the zero space. For example, for source byte `s=0` and output difference `d=0x01`, `R=0x0010` and triple support `(0,1,3)` is **provably impossible**, because `0x0010` is not in that triple's E-image. Conversely, `(0,1,2)` **passes** this necessary equation. It is *not* a claim that a real two-round trail attains the latter shape.

There are 16 source-byte positions whose one-byte output differences always project to zero under R; as expected, the bit-zero gate alone cannot exclude any triple for these source positions. This is one reason it cannot prove `A_(r+1)≥4` globally.

## Independent reproducibility audit

1. `make_maps.py` pins the exact original C/H SHA-256 values, compiles original C, and checks **all 2,048 bit-basis vectors** of the complete `L` prefix against an independent Python implementation and its inverse.
2. For **8,192** deterministic random source-byte differences and unrestricted Pressure base states, it directly replays the **original scalar C** `Butterfly`, `Pressure`, `InkCloud`, and next prefix, confirming all 16 bit-zero identities and the independent `Q_s` basis map.
3. It saves **all 128×16 and 256×8 exact GF(2) vectors** in `gate_maps.json` and generates `gate_maps.h` for independent finite enumeration.
4. `scan_three_cells.c` exhausts the 341,376 cell triples and all 256 source-byte positions, counting the exact number of surviving nonzero differences via binary ranks; **87,392,256** combined triple/source rank tests stand in for 22.285 billion value-specific checks.
5. An entirely separate run of the same complete enumeration with **opposite GF(2) pivot order** (`scan_three_cells_lowpivot.c`) gives **byte-for-byte identical JSON output** (`gate_scan.json`).

To reproduce on Ubuntu: `make test`. Python 3, GCC, and pthreads are required. No SMT solver is required for this certificate.

## Exact scope and next stage

The scan assumes **one active Chi call in an unrestricted full-permutation round**, **not** a valid 159-byte first-hash-block input (which already has `A1≥5`). It allows *all* two-byte values for each chosen next-Chi input cell, ignoring ABYSSAL's exact derivative compatibility and the actual non-bit-zero Pressure carry constraints. Its UNSAT-equivalent algebraic exclusions are sound; its surviving configurations are only potential shapes, not actual trails. Full `[1,3]` exclusion remains open; therefore the inherited **`A_r=1 ⇒ A_(r+1)≥3`** bound is unchanged.

**Useful next computation:** stratify those 12.147 billion relaxed survivors by real three-call endpoint shapes (`AAA`, `AAB`/`ABA`/`BAA`, `ABB`, and two-cell patterns), enforce one-call/two-call serial-Chi derivative constraints and *joint* 2–5-bit Pressure carry relations, and resolve outstanding cases using exact SMT. Avoid naive per-site runs; first quotient any proved positional symmetries.


---

## WORK-DIFF-FULL-INTERROUND-SPARSE-015 — Sparse serial-Chi calls force cross-round word support

**Scope:** Unmodified eight-round original permutation P, unrestricted 2048-bit state pairs entering any adjacent rounds. Let `A_r` be active **byte-S-box calls** in serial Chi of round r; `B_r` count nonzero **two-word Pressure shear pairs** after Butterfly (16 disjoint even/odd branches); and `W_(r+1)` count nonzero **64-bit words after InkCloud, before next Theta**.

**Theorem:**

- `A_r=1 ⇒ B_r=16, W_(r+1)≥16`, with at least eight nonzero even-indexed and eight odd-indexed words before next Theta.
- `A_r=2 ⇒ B_r≥8, W_(r+1)≥8`. For **30,720/32,640** possible two-output-byte position pairs, `B_r=16` is guaranteed; only **1,920** exceptional supports allow some cancellation.

**Exact two-byte position classification:** For distinct post-Chi byte positions `i<j` set `u=i//8`, `v=j//8`. Let `G(i,j)` be the number of the 16 Pressure-pair projection maps with full rank 16 over their 16 input bits. If `(i mod 8) != (j mod 8)` or `(u>>1)&1 != (v>>1)&1`, `G=16`. Otherwise `G=16-2^(4-popcount(u XOR v))`. Histogram of `G` over all 32,640 supports: **8:512, 12:768, 14:512, 15:128, 16:30,720**. All other Pressure pair projections are rank eight (8,320); rank-16 count is 513,920. Both independent high- and low-pivot GF(2) elimination agree on **522,240/522,240** projection ranks. Original C and independent Python agree on **all 2,048 Butterfly basis outputs**.

**Sharp Pressure-pair counterexample:** Post-Chi output difference bytes 0 and 8 both `0x01` yields **exactly eight nonzero Pressure input/output pairs** (`A_r=2`) through original C; source-inverse prefix and serial-Chi reconstruction gives a genuine unrestricted round-start state pair. Single-call C witness also replayed. The `B` lower bound is tight; `W` lower bound not asserted exact.

**Why it holds:** Each active bijective S-box call produces one nonzero post-Chi output byte; Butterfly is a full-state linear map. The finite rank certificate forces the stated number of nonzero two-word groups. Every even and odd Pressure shear is independently bijective, so no nonzero group maps to zero. Iota cancels in differences and InkCloud preserves word nonzeroness and index parity (`i→7i mod 32`, plus `ROTL11`).

**Critical limitation:** This is a structural **inter-round support theorem, not a bound on next-round Chi calls**. Full Theta/Tentacle/Rho/Pi can cancel dispersed word differences. In particular neither `A_r=1 ⇒ A_(r+1)≥16` nor `A_r=2 ⇒ A_(r+1)≥8` has been proved. The inherited full-P `A_r=1⇒A_(r+1)≥3` remains the direct adjacent-round activity bound; the `[2,1]` scan is not superseded. No universal valid-hash activity, characteristic/hull DP, or security-bit bound follows.

**Reproduction:** `KRAKKEN_FULL_INTERROUND_SPARSE_CERTIFICATES.zip`, containing `THEOREM.md`, `audit.json`, `verify_interround.py`, pinned original scalar C/H, and independently checked prefix reference. Run `make test`.

## WORK-DIFF-FULL-WIDETRAIL-014 — Full original Krakken: 52-call exact byte bound, 16-pair single-word gate

**Date: 2026-11-04. Status: exact finite one-round certificate with independent pure-Python and original-C reproductions.** Package: `KRAKKEN_FULL_WIDETRAIL_CERTIFICATES.zip`; detailed proof: `THEOREM.md` within the archive. Original source/header SHA-256 fingerprints are unchanged.

**Theorem A (unrestricted full-state single-byte input differences).** For every nonzero XOR byte difference at any of the full 2048-bit state's **256 byte positions**, and every unrestricted base state, the immediately following original `Theta→Tentacle→Rho→Pi→serial Chi` activates **at least 52 of the 256 byte-S-box calls**. The minimum 52 is attained for an unrestricted state pair, e.g. position 72 and byte difference `0x08`. The producer enumerated all **65,280** difference classes and computed the *exact* minimal Chi activity by independently attainable S-box DDT support transitions in each serial-Chi byte lane; a separate Python implementation reproduced the complete histogram and all position minima, and original-C serial Chi replay confirmed the attained 52. This extends the earlier `WORK-DIFF-FULL-SINGLEBYTE-013` valid-message *lower bound* to all 256 unrestricted state bytes and gives an unrestricted-state matching witness. It does **not** assert a matching valid-159-message witness.

**Theorem B (one active 64-bit word entering a round).** For each of the 32 possible source words, and for each of the 16 serial-Chi two-word input pairs after the original linear prefix, the GF(2) map from the source **64-bit difference** to the target **128-bit word-pair difference** has column rank **64/64** (**512/512** maps). Therefore every such pair is nonzero under **every nonzero one-word source difference**, so at least one byte-S-box call per pair is active: **A_r≥16**. This property applies at any round where the *input* difference is confined to one word; it does not assume or imply that such a difference persists across rounds. The 16-call result is a bound, not a claimed optimum.

**Nontrivial caveat and potential research direction.** Individual word projections are not uniformly injective: of the **1,024** 64→64 maps, **96 have rank 8**, **288 rank 56**, **160 rank 63**, and **480 rank 64**. Example: original input word 0 difference `0x02` gives zero original post-Theta/Tentacle words 21–23. The rank-8 cancellation is an interaction between Theta bit rotations and the Whirlpool-polynomial `0x11D` MDS arithmetic. It **invalidates** any shortcut that assumes all 32 word projections activate, while the 128-bit paired maps still guarantee all 16 Chi word-pairs active. This observation is a structural property, **not an exploit or a practical break**. Adapted wide-trail work must model the Theta→MDS interaction and Rho's non-byte-aligned rotations exactly.

**Certificate.** Original compiled C vs independent Python linear prefix and inverse on **2,048/2,048** full-state GF(2) basis bits; exact independent 65,280-byte histogram; ranks of all 512 paired maps and 1,024 individual maps; original-C two-state witness with exactly 52 active calls; explicit C-confirmed cancellation. No stronger two-round/full-eight-round activity or probability statement is inferred. A local DDT minimum is meaningful for unrestricted bases because the full linear prefix is invertible; the same unrestricted witness need not satisfy the sponge's message-domain restrictions.

## WORK-REDUCED-MDS-BFLY-PRESS-ACT-012 — Strengthened two-round and eight-round activity bounds for the Tentacle/Chi/Butterfly/Pressure ablation

**Date: 2026-11-04; status: proved analytically from pinned source structure; independently source-checked and activity-DP audited.** The reviewer-proposed improvement to the reduced model's activity floor is **accepted within the stated domain**. Evidence: `KRAKKEN_REDUCED_MDS_R1FOUR_R2TWO_CERTIFICATES.zip` (pinned C/H, analytic proof, check program and audit results). Full original Krakken and the ongoing `[2,1]` campaign remain separate.

**Theorem.** For the *reduced* round `Tentacle MDS -> serial Chi -> Butterfly -> Pressure -> Iota`, starting with two different exactly 159-byte messages (same padding `0x86`, zero capacity), let `A_r` be the number of byte S-box calls with nonzero input difference. Then

```
    A_1 >= 4;   A_1 == 4  =>  A_2 >= 2;
    A_r >= 1;   A_r == 1  =>  A_(r+1) >= 2.

    r:             1   2   3   4   5    6    7    8
    total lower:   4   6   7   9  10   12   13   15
```

Thus `N_min(2) >= 6`, `N_min(8) >= 15`, and for `1<=r<=8` the derived closed form is `N_active(r) >= 4 + (r-1) + ceil((r-1)/2)`. The older `N_active(8)>=14` from `-011` is valid but **weaker and superseded**. **Useful exact-SMT reduction:** A two-round trail with total activity at most six must have **exactly** `(A_1,A_2)=(4,2)` or `(5,1)`; there is no third case under these rules. To test attainability of six, solve these two branches separately and replay any SAT witness in the actual C model. Only source/model-audited UNSAT for **both** branches proves `N_min(2)>=7`. None of the inequalities from round two onward is asserted to be attainable. In particular the formally permitted sequence `[4,2,1,2,1,2,1,2]` of total 15 is *only a relaxation witness*, not a real two-execution differential trail. The previously certified first-round equality `A_1=4` remains attainable, but the exact R2 optimum remains unknown.

**Key proof and a necessary subtlety.** The existing `-011` MDS branch-number proof establishes that any nonzero first-round input difference produces, in some `(row,byte-lane)`, at least four distinct active pre-Chi byte coordinates, each requiring a distinct output S-box byte in the inverse serial-Chi mapping. If the total Chi activity is *exactly* four, **all four post-Chi active output bytes belong to that same row**. This does **not** require that they occupy four different words; several may be in one word. Crucially, no word can contain eight nonzero bytes, since only four active output bytes exist in the entire state.

Butterfly stage 0 mixes adjacent `(even word,odd word)` pairs by `(a,b) -> (a XOR b, b XOR ROTL64(a XOR b,13))`. For a nonzero difference `d` in one even member and zero odd member, both output members differ. For a nonzero difference `d` in one **odd** member and zero even member, the output differences are `(d, d XOR ROTL64(d,13))`. The second could vanish only when `ROTL64(d,13)=d`, and as `gcd(13,64)=1`, a nonzero rotation-fixed 64-bit word must be all ones; that would require eight active bytes and is **impossible in the four-call case**. Thus stage 0 creates a nonzero difference in *both* even-row and odd-row parity groups.

Butterfly's subsequent stages use distances 2,4,8,16 and are invertible *within each parity group*; they cannot annihilate either. Pressure is invertible separately on `(row0,row2)` and `(row1,row3)` word-pairs; Tentacle is invertible within each row; Iota cancels from differences. Therefore the next Chi input has a nonzero difference in both parity groups, and since serial Chi is bijective independently per row, each group activates >=1 S-box call: `A_2>=2`.

**Verification, bounded scope.** Pinned original scalar C/H hashes are identical to `-011`. The new reproducibility script checks 65,280/65,280 stage-0 single-byte parity cases, 2,048/2,048 original-C-vs-independent-Python full Butterfly basis mappings, and 8,192/8,192 *unrestricted-base*, arbitrarily selected four-byte single-row suffix pairs through original-C Butterfly/Pressure/Tentacle/Chi. All pass with at least two next Chi calls. Its independent necessary-condition DP returns exactly `[4,6,7,9,10,12,13,15]`. The source replays are **consistency tests**, not an exhaustive SMT search over all valid message pairs. The reviewer-reported witness upper bounds (two rounds 255, eight rounds 1778) remain unverified here because those exact witness input messages were not supplied; earlier independently certified eight-round reduced witness totals 1790, and first-round-four witness has 254 R2 calls. Neither lower nor upper activity counts imply a differential probability bound.

---

## WORK-REDUCED-MDS-BFLY-PRESS-ACT-011 — Exact first-round minimum four and conditional eight-round lower bound in the Tentacle/Chi/Butterfly/Pressure ablation

**Date 2026-11-03; status: analytic and finite original-C certified for the stated reduced model.** Evidence: `KRAKKEN_REDUCED_MDS_ACTIVITY_CERTIFICATES.zip`. This is an additional *reduced-construction* working theorem, not a change to the permanent security ledger or to the eight-round full Krakken activity lower bounds. It is independent of the ongoing `[2,1]` campaign.

**Defined construction.** Each of eight rounds is precisely `tentacle_mds_scalar(state); chi_scalar(state); butterfly_diffusion_scalar(state); pressure_arx_scalar(state); beta_iota_scalar(state, ir);`. All functions are from the pinned unchanged original scalar C/H (`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` / `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`). The original `Theta`, `Rho`, `Pi`, and `InkCloud` are **not present**. For first-round input quantification: any two distinct exactly 159-byte messages, fixed `0x86` at byte 159 and initial zero capacity. `A_r` counts **byte S-box input-difference activations** at serial Chi in reduced round r.

**Theorem.** For every such nonzero valid-message XOR difference, `A_1>=4`; a concrete valid-message pair with `A_1=4` exists, so the **exact minimum is 4**. For any nonzero state difference entering adjacent rounds, `A_r=1 => A_(r+1)>=2`. Consequently, for valid 159-byte messages and `1<=r<=8`,

```
   N_active(r) >= 4+(r-1)+floor((r-1)/2),
   N_active(8) >= 14.
```

These are **necessary activity bounds only**; no probability/hull/security exponent or claim of true eight-round optimality follows.

**Proof — MDS and first Chi.** The source MDS operates separately on each `(row y, byte lane j)` vector of eight columns, with `M[c,k]=mds_coeffs[(k-c)&7]`, GF256 field polynomial `0x11d`. An independent GF256 Gaussian-minor program rechecked all `sum_{k=1}^8 binom(8,k)^2 = 12,869` square minors as nonsingular, so its byte branch number is 9. Valid 159-byte message differences affect at most **five input columns** (`c=0..4`) within every `(y,j)` lane, never the fixed padding byte. Any nonzero such vector therefore produces at least `9-5=4` different byte coordinates after MDS.

The serial-Chi cell satisfies `u=S(a XOR R(b))`, `v=S(b XOR R(u))` with `R=ROTL64(.,32)` and bytewise bijective `S`. Its inverse is `b=S^-1(v) XOR R(u)`, `a=S^-1(u) XOR R(S^-1(v)) XOR u`. A difference in *one* output S-box byte `u_j` can affect its inverse inputs only in byte coordinates `a_j` and `b_(j+4 mod 8)`; one `v_j` affects only `b_j` and `a_(j+4 mod 8)`. Thus **one active byte S-box call can account for at most one pre-Chi nonzero coordinate in any fixed `(row y, byte lane j)`**. Any nonzero input row/lane necessarily gives four such coordinates after MDS. Hence `A_1>=4` universally.

**Constructive matching witness — original C.** Independently found valid 159-byte messages with XOR difference in **only five byte positions**: offsets `0,32,64,96,128`, respective differences **`FE 43 B7 13 09`**; padded byte 159 is `86` in both. After MDS the *only* different bytes are at row `y=0`, byte lane 0, columns `1,3,5,7` with values `EC DB EA ED`. The baseline was explicitly solved over GF256 so each first-S-box output difference equals the corresponding input byte difference, canceling the second serial-Chi S-box inputs. Exact original-C replay gives **four** active first calls (row0, pairs0..3, byte4), **zero** active second calls. Complete message hexes and generated certificates are in `first_round_four_sbox_witness.json`. This verifies attainable equality, not just an approximate search result.

**Proof — the `1→2` rule and eight-round corollary.** A single active S-box call produces a single nonzero post-Chi byte difference. The previously certified full-rank Butterfly mapping spreads any such byte difference into **all 32 words**. Each of Pressure's eight columns applies separate bijective two-word shears to rows `(0,2)` and `(1,3)`; hence after Pressure there is nonzero activity in an even row and in an odd row. Iota does not change XOR differences. The following MDS, which acts independently and invertibly on each row, cannot annihilate all even-row activity or all odd-row activity. The next Chi must therefore have two distinct active row-specific cells and **at least two byte S-box calls**. Since all layers are bijective, every round of a nonzero trail has at least one active call. No pair of consecutive activity counts can both be 1, giving the stated sum bound. The older reduced *without MDS* `1→8` theorem is not transferred to this new round definition.

**Source replay beyond R1.** Applying all five specified original scalar layer functions for all eight reduced rounds to the *new, independently constructed* pair gives per-round counts **`[4,254,256,256,253,256,256,255]`**, total **1,790**. This is a **certified witness upper bound**, not the claimed minimum. The external reviewer report separately describes a better **1,778**-call witness over eight rounds and two million sampled pairs, but those specific witness inputs/executables were **not provided**, so the 1,778 claim remains **reviewer-reported, not independently replayed here**. The reported improvement in solver difficulty is a useful ablation observation, not itself cryptographic evidence.

**Reproduction.** Run `python3 check_mds.py`, `python3 construct_first_round_witness.py`, and `python3 eight_round_witness.py` inside the certificate archive after extraction. The Python witness script compiles a shared library from the pinned original C/H and invokes the actual layer functions. The earlier `KRAKKEN_REDUCED_BFLY_PRESSURE_ACTIVITY_CERTIFICATES.zip` supplies the independent exhaustive 8,192 rank-8 source-byte-to-word Butterfly proof on which the `1→2` corollary relies.

---

## WORK-REDUCED-BFLY-PRESS-ACT-010 — Provable 1→8 active byte S-box growth in the Chi/Butterfly/Pressure-only reduced permutation

**Date:** 2026-11-03. **Construction and quantification:** This is a theorem for the reduced consecutive-round sequence `Chi → Butterfly → Pressure → Iota → Chi` with the **unchanged original layer functions**, and with `Theta`, `TentacleMDS`, `Rho`, `Pi`, and `InkCloud` omitted between successive Chi invocations. It holds for **all bases**, every nonzero byte difference in any of the 256 post-Chi byte positions, and every adjacent pair of rounds of this reduced construction. It is **not** a new theorem for the full Krakken permutation.

**Theorem.** Denote by `A_r` the number of byte S-box calls whose **input** XOR difference is nonzero in the serial-Chi mapping of reduced round `r`. Then

```text
A_r = 1  ==>  A_(r+1) >= 8.
```

**Proof.** Exactly one active S-box call yields exactly one nonzero byte in the *post-Chi* difference (the Abyssal S-box is bijective, and inactive calls produce zero output difference). Butterfly is bit-linear. For every one of the `32×8=256` input-byte sites and every one of the 32 destination words, the eight source-byte basis-bit responses form an independent set in `GF(2)^64`: all **8,192** byte-to-destination-word matrices have rank **8**. Therefore any nonzero single-byte difference spreads into **all 32 words**, independent of the base state. This also agrees with direct original-C enumeration of all `32×8×255=65,280` possible nonzero one-byte input differences.

Now in each Pressure four-word column `(a,b,c,d)`, the even-word shear `(a,c)→(A,C)` and odd-word shear `(b,d)→(B,D)` are separately bijective. Explicitly, the unrotated even shear has `A=a+(c⊕(c>>17))`, `C=c+(A⊕(A<<31))` modulo `2^64`, and its inverse computes `c=C−(A⊕(A<<31))`, then `a=A−(c⊕(c>>17))`. The odd shear is analogous, and its output rotations are invertible. Since every input word differs, each shear has a **nonzero two-word output difference**; hence each of the eight Pressure columns contains at least one nonzero even-row and one nonzero odd-row output difference. Iota is an XOR of common constants and does not change the differences.

At the next Chi, adjacent columns `(2p,2p+1)` are paired separately at the four row indices `y`, for `p=0..3`. In each of the four paired-column blocks, the Pressure argument forces a nonzero input difference in at least one even-row Chi pair and one odd-row Chi pair, giving two **distinct** nonzero 128-bit Chi input pairs. Any nonzero Chi input pair `(Δa,Δb)` activates at least one byte S-box: either `Δa⊕ROTL32(Δb)≠0` activates a first-call S-box, or this difference is zero, in which case `Δb≠0` activates a second-call S-box. Thus the next Chi has at least `4×2=8` active byte S-box calls. QED.

**Verification:** All **2,048** 2048-bit Butterfly basis responses in an independent Python implementation agree with the pinned original C; the 8,192 GF(2) ranks are all 8. The original C exhaustive 65,280-case test reports **zero failures** and precisely 32 affected output words per nonzero byte difference. A separate original-C **4,096-pair** suffix replay (`Butterfly→Pressure→Iota→Chi`) checked shear noncancellation and S-box activity, with observed next-Chi activity from **159 to 256** calls; these trials are sanity checks, not the universal proof. Source/header SHA-256: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` / `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

**Direct Butterfly-only ablation corollary:** If **Pressure is also omitted**, leaving reduced `Chi→Butterfly→Iota→Chi`, all 32 words are still nonzero at next Chi, so all **16** distinct paired 128-bit Chi input cells are nonzero. By the same serial-Chi input argument each forces at least one byte S-box call; thus `A_r=1 ⇒ A_(r+1)≥16` in this **different, Butterfly-only reduced construction**. The 16 versus 8 figures are guaranteed lower bounds, not measured exact minima or an ordering of cryptographic security: Pressure may introduce additional resistance while allowing different truncated word-support patterns.

**Limited abstract corollary:** All complete reduced rounds are bijective, so nonzero differences imply `A_r≥1`. The `1→8` rule alone yields an eight-round **necessary** activity floor `Σ_(r=1)^8 A_r≥15`. It is not an optimality certificate (the abstract sequence `2,2,2,2,2,2,2,1` may not correspond to any real trail) and provides no characteristic/hull probability bound.

**New conditional first-round activity corollary (2026-11-03, following external reduced-variant review):** For any trail in this *same reduced construction* with `A_1 = 1`, the first two rounds necessarily contribute at least `1+8=9`. For any subsequent `t >= 1` consecutive rounds, the established `1→>=8` rule and per-round `A>=1` imply a minimum of `2t-1` calls (pair every nonterminal `A=1` with its successor; at most the terminal round can be an unpaired one). Therefore, for `r>=3`,

```text
A_1 = 1  ==>  sum_(i=1)^r A_i >= 1 + 8 + [2(r-2)-1] = 2r+4.
```

In particular, an **eight-round reduced trail beginning with one active S-box has >=20 total active S-box calls**, and its first two rounds have >=9. This conditional strengthening does **not** upgrade the unrestricted minimum of >=15 because the minimum may be attained by trails starting with two or more active S-box calls. No claim of attainability is made. This is a direct combinatorial deduction from the already certified reduced-round `1→8` theorem, not a new C/SMT enumeration.

**Constructive valid-159-byte first-round witness:** In the reduced variant (no linear prefix before Chi), take two 159-byte messages whose XOR difference is `0x01` at message byte offsets **0 and 36**, and zero everywhere else. These positions correspond to Chi-paired words `state[0]` byte 0 and `state[4]` byte 4; the 32-bit rotation cancels their difference at the first S-box, while the second S-box input changes in exactly one byte. Thus `A_1=1` for **every base message** with this fixed XOR difference, not merely for a sampled witness. Independent direct original-C `chi_scalar` executions for values `0x01` and `0xa5` both produced exactly one changed output byte at word 4 byte 4. The conditional `>=20` eight-round corollary therefore covers a **nonempty valid-message-difference class**.

**External reduced-variant experiment comparison (reviewed as a report, not independently replayed here):** A reviewer reports 4,000,000 concrete 159-byte-domain input-pair tests and an eight-round *witness* with per-round counts `(16,14,252,254,252,254,251,251)` (sum `1544`). Such a replayable witness would give `N_min(8)<=1544`, whereas the proven universal lower bound remains `>=15`. Large observed later-round activity is **not** a rigorous minimum. The reduced-implementation ZIP, witness inputs, and differential-count logs underlying this external report were not supplied in the reviewed text; therefore its sample counts, exact hash-collision retest, and `N_min(8)<=1544` witness are **reported but not independently audited** in this working document. The already certified original-C Butterfly and Pressure activity theorem remains independent of those unprovided artifacts.

**Scope guardrail:** Restoring any of the omitted layers—especially the full original `InkCloud` word shuffle and the linear prefix before the next Chi—can change the row support and invalidate this specific proof. It does **not** supersede the inherited full-permutation `DIFF-PERM-003` rule `A_r=1⇒A_(r+1)≥3` or the full-permutation/valid-hash eight-round activity floors of 15/18. The two versions must be studied separately.

**Reproducible certificate archive:** `KRAKKEN_REDUCED_BFLY_PRESSURE_ACTIVITY_CERTIFICATES.zip` contains original pinned C/H, independently implemented `verify_basis.py`, `basis_certificate.json`, direct C enumeration `audit_butterfly.c`, source-based suffix replay `audit_full_reduced_pair.c`, and `README.md`.

---

## WORK-DIFF-COMPOSE-TWOCHI-DIAG1-009 — Two active serial-Chi cells: certified complete-round DP below 1/4

# Krakken: exact two-Chi-cell diagonal class, complete-round differential upper bound

Working ID **`WORK-DIFF-COMPOSE-TWOCHI-DIAG1-009`**, 2026-11-03. This is an independently replayable, **strictly scoped one-round theorem**, not a global permutation, eight-round, or hash security claim. The ongoing `[2,1]` differential spatial campaign is a distinct problem and was not changed by this experiment.

## Theorem

Let `L = Pi ∘ Rho ∘ TentacleMDS ∘ Theta` be the first four invertible linear layers of the unchanged Krakken-2048 Abyssal round; let `C`, `B`, and `P` be serial Chi, Butterfly and Pressure; let `R_r` be the affine bijective Iota/Ink suffix. Let `F_r=R_r∘P∘B∘C∘L` denote **one complete round** at any round index `r=0..7`. Choose any **two distinct aligned 16-bit Chi cells** `s<t`, from the 128 cells. Prescribe `d=L(Δ)` such that at each of those cells the two aligned Chi input bytes both have XOR difference **`0x01`**, and all other pre-Chi differences are zero. The pairing of the two byte positions includes the 32-bit rotation used inside the original serial Chi (source site map below). Every such `Δ` is a unique nonzero full-state difference because `L` is invertible.

For uniform unrestricted 2048-bit base `X` and **any fixed full 2048-bit output difference `Γ`**,

```
Pr[F_r(X) XOR F_r(X XOR Δ) = Γ] <= T_{s,t} < 1/4.
```

There are `C(128,2)=8,128` possible cell pairs. The largest **certified dyadic upper bound** on their `T_{s,t}` is

```
274865743872 / 2^40 = 0.24998893775045872...
```

and occurs at cell pair `(0,4)`. The strict inequality is checked **exactly** in integer arithmetic: `274865743872 < 2^38 = 274877906944`. This excludes probability-1/4-or-higher **full-output XOR differentials on this particular input-difference class**, not arbitrary differential distinguishers. There is no claim about restricted valid 159-byte hash bases, multi-round trails or full differential hulls over varied input differences.

## Proof without assuming Chi and Pressure are independent

At any single aligned Chi cell the original source computes `u=S(x XOR y)` and `v=S(y XOR u)` with the appropriate 32-bit positional rotation. An input byte XOR difference `(dx,dy)=(1,1)` cancels in the input of the first S-box; hence `Δu=0` exactly, while the input of the second S-box has fixed difference 1. Define

```
c(v) = #{z in 0..255 : S(z) XOR S(z XOR 1) = v}.
```

For this pinned S-box, precisely 127 nonzero `v` have `c(v)>0`: one has count 4, the other 126 have count 2; `Σ_v c(v)=256`. Uniform independent input cells imply the *joint* intermediate Chi difference event `(v,w)` has exact probability `c(v)c(w)/2^16`. The other 126 Chi cells have zero differences, and the two active cells' first output bytes also have zero differences.

For each pair `(s,t)` and intermediate output-byte differences `(v,w)`, write `δ(s,t,v,w)` for the resulting full 2048-bit post-Chi XOR difference, supported in exactly those two second output bytes. Butterfly is bit-linear, so its induced Pressure input XOR difference is `B(δ)`. For each of the 16 disjoint Pressure arithmetic shears, take its five-bit projected input XOR difference triple `d_j`. Define `M[d_j]` as the **largest** entry of that row of the previously source-pinned, exact five-bit Pressure local DDT, whose rows each sum to `32768`. Then

```
Q_{s,t}(v,w) = product_{j=0}^{15} M[d_j] / 2^240
```

is a rigorous upper bound on any specified **full-output** Pressure differential for fixed `B(δ)` under **unconditional uniform unrestricted** Pressure inputs. The product here is legitimate for standalone Pressure: its 16 shears have disjoint input words.

The *full-round* bound **does not multiply** the Chi probabilities by `Q`. Because `U=C(L(X))` is itself uniform (Chi and L are bijective), for the simultaneous event `E_(v,w)` of the specified Chi intermediate difference and specified final output difference we have two separate unconditional bounds:

```
Pr[E_(v,w)] <= c(v)c(w) / 2^16
Pr[E_(v,w)] <= Q_{s,t}(v,w).
```

The second inequality is inclusion of events over uniform `U`, **not** an unjustified assumption about the distribution of Pressure inputs after conditioning on the Chi differential. The events indexed by `(v,w)` are disjoint and cover the event of interest. Summing their individual minimum bounds proves

```
Pr[ΔF_r=Γ] <= Σ_{v,w in support(c)} min(c(v)c(w)/2^16, Q_{s,t}(v,w)) = T_{s,t}.
```

This has **127²=16,129 summands** for each of the 8,128 pairs: **131,096,512** exact finite profiles. Affine constants in Iota cancel under XOR difference and Ink applies a fixed invertible permutation/rotation to the difference, so the result holds at the complete-round output.

## Rigorous dyadic integer upper bound for every pair

The complete Pressure product `Q` has denominator `2^240`. Rather than construct 131 million 240-bit integer products, the source-pinned native-C scanner calculates a *provable upward-rounded approximation on an exact `2^-40` grid*:

```
h_0 = 2^40;
h_(j+1) = ceil(h_j * M[d_j] / 32768), for j=0,...,15.
```

Since `0 <= M[d_j]/32768 <= 1`, induction gives `Q <= h_16 / 2^40`. The Chi cap is **exactly integral** on the same grid: `c(v)c(w) * 2^24`. Thus the reported integer numerator

```
N^+_(s,t) = Σ_{v,w} min(c(v)c(w)*2^24, h_16)
```

is a rigorous upper bound `T_(s,t) <= N^+_(s,t)/2^40` (with `T` defined as the min-union sum using exact `Q`). A symmetric **downward** rounded recurrence provides a rigorous lower bracket for each `T`. No floating-point comparisons enter the proof. The C scanner uses `uint64` and every intermediate product is at most `2^40 * 2^15 = 2^55`, avoiding overflow. The maximum upper-minus-lower bracket width across all 8128 pairs is just `16125/2^40 ≈ 1.47e-8`.

Every row in `twocell_diagonal_bounds.csv` contains pair `(s,t)`, the exact upward and downward integer numerators, the count of intermediate cases where all 16 low5 Pressure projections are deterministic, the maximal dyadic Pressure-profile bound, and the number of enumerated profiles. **All 8128 rowwise upper numerators are strictly less than `2^38`**. Largest is `274865743872` at `(0,4)`.

## Additional verified structural findings

The map from two arbitrary local 16-bit Chi-output cells to low-bit Pressure *input* projections can have a nonzero kernel, even though Butterfly itself is invertible. For all `C(128,2)` pairs, independently computed GF(2) ranks (32 input bits; 16 shears, each with 3 projected 4- or 5-bit input slices) are:

| GF(2) rank | Four-bit projection count | Five-bit projection count |
|---:|---:|---:|
| 32 | 7,672 | **7,952** |
| 31 | 264 | **144** |
| 30 | 160 | **32** |
| 28 | 24 | 0 |
| 27 | 8 | 0 |

Thus **456** pairs have noninjective four-bit projections and **176** remain noninjective even on five-bit projections. These are **linear-projection** statements, not claims that the complete two-cell map is noninvertible. Within the much narrower S-box-reachable *diagonal-one* intermediate difference support considered in the probability theorem, **56** pairs admit at least one profile where every one of the 16 *five-bit Pressure* projections is deterministic (80 profiles total, counting pair/profile incidence). These do not invalidate the `<1/4` complete-round cap; the exact joint Chi output probability still constrains the contribution from those cases.

## Reproduction and verification

Pinned original scalar `krakken.c` SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, `krakken.h` SHA-256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`; exact previous Pressure low5 DDT SHA-256 `68189c4b03bb68960967149db031cc0e5969a216d2eab335d05b8a504f7c2067`.

1. `twocell_diagonal_bound.c`: builds Butterfly projections by calling the **original scalar C**; verifies all 32768 full finite-DDT row sums; performs the 131,096,512-profile complete C integer scan; saves one auditable CSV row per pair and flags any bound >=1/4 when inspected via the Python verifier. (The C scanner immediately rejects >=1 but reports counts >=1/4 for independent audit.)
2. `twocell_diagonal_numpy_verify.py`: independently reimplements Butterfly in Python, compares **2048 original-C Butterfly basis responses**, derives an independent `low-pivot` GF(2) rank audit for **all 8128 pairs** (reproducing earlier high-pivot low4 ranks), and uses vectorized exact `uint64` dyadic ceil/floor arithmetic to reproduce **every row of all 8128 CSV bounds** with zero mismatches. It asserts all 8128 bounds are `<1/4` and checks the saved checksum/source hashes.
3. `twocell_exact_spot.py`: source-C Butterfly + **arbitrary-precision Python integers** independently obtain **exact rational sums with denominator `2^240` for ten selected pairs**, including the worst pair `(0,4)`, and certify their location within the full-scan upper/lower integer brackets.
4. `twocell_diagonal_fullround_replay.py`: **invert the entire original 2048-bit linear round prefix** (GF(2) rank 2048); for 12 selected site pairs and 32 independent unrestricted states each, verify exact two-cell Chi output support, Butterfly difference propagation, every live Pressure low5 output transition has nonzero original-table count, and layer-by-layer composition matches the **original complete `krakken_permute_scalar_rounds(..., 1)` API** on both inputs. Total **384 full-round input pairs**, no discrepancies. The random replay is implementation checking, not the probability proof.
5. `twocell_rank_pilot.py`, `twocell_rank_pilot.json`: earlier independent high-pivot rank pilot covering all two-cell pairs and showing the 456 low4-deficient sites; cross-checked by opposite-pivot independent NumPy verifier.

On Linux with Python 3, NumPy, GCC and pthread:

```bash
# Run from this extracted certificate package directory.
gcc -O3 -std=c11 -pthread -fPIC -shared krakken.c -o libkrakken_comp.so
gcc -O3 -march=native -std=c11 -pthread twocell_diagonal_bound.c krakken.c -o twocell_diagonal_bound
./twocell_diagonal_bound pressure_low5_counts.bin twocell_diagonal_bounds.csv 2> twocell_diagonal_scan.log
OPENBLAS_NUM_THREADS=1 python3 twocell_diagonal_numpy_verify.py
python3 twocell_exact_spot.py
python3 twocell_diagonal_fullround_replay.py
```

Verify `sha256sum twocell_diagonal_bounds.csv` matches `twocell_diagonal_numpy_audit.json`. The certificate archive has per-member SHA-256 manifest and ZIP integrity check. No solver is required. No mutation of the separate `[2,1]` campaign is involved.

### Limitations

These are **one-round, unrestricted uniform-base, full-output, fixed-difference** results. The input difference must be the inverse-linear-prefix image of `(0x01,0x01)` in exactly two distinct aligned Chi cells, not arbitrary nonzero values or arbitrary cells/bit patterns. The bound is **not** a security level for the eight-round permutation or the 159-byte hash, and not a bound for all differentials or all differential hulls. In particular, independently multiplying such a one-round bound across rounds would be invalid due to intermediate dependencies.

---

## WORK-DIFF-COMPOSE-ONECHI-008 — Exact differential upper bounds for complete Krakken rounds on one-Chi-cell input differences

**Status:** New **proved, finite-certified complete-round differential probability upper bound** for the unrestricted 2048-bit permutation on the specified input-difference class, from the unchanged scalar C. Evidence package: `KRAKKEN_CHI_BUTTERFLY_PRESSURE_COMPOSITION_CERTIFICATES.zip`. This combines the inherited exact serial-Chi DDT theorem `DIFF-CHI-002` with the already proved complete five-bit Pressure DDT `WORK-PRESS-DIFF-LOW5-007` and the exact linear Butterfly response. It is independent of the ongoing `[2,1]` campaign. **The full-round result is for the uniform unrestricted input distribution; it is not a direct bound for the restricted 159-byte hash domain or for eight-round differentials.**

### The exact scoped theorem

Write a complete round with its round-index constant as

\[
F_r=R_r\circ P\circ B\circ C\circ L,
\qquad L=\Pi\circ\rho\circ\operatorname{TentacleMDS}\circ\Theta.
\]

Here `C` is the disjoint serial-Chi mapping on 128 aligned 16-bit byte cells; `B` the bit-linear Butterfly; `P` the 16-shear Pressure; and `R_r` the Iota XOR/InkCloud affine bijection. The linear prefix `L` is invertible (Theta is involutory; MDS is nonsingular; Rho and Pi are bijective). Consider **any nonzero fixed full-round input difference** `Δ` such that `d=L(Δ)` has support in *exactly one* local 16-bit Chi cell, `s`, and let `X` be uniform on unrestricted `GF(2)^2048`. The local input difference `d` belongs to one of the following **exact** `DIFF-CHI-002` classes:

| Class of one-cell Chi input difference | Count of local input differences *per site* | Exact worst-over-128-sites complete-round differential upper bound | Simple rational certificate |
|---|---:|---:|---|
| Sharp local Chi maximum DP `2^-6` | 510 | **0.44422684208987734…** | **<1/2** |
| Sharp local Chi maximum DP `2^-7` | 32,130 | **0.31141434208987734…** | **<1/3** |
| Sharp local Chi maximum DP `2^-12` | 32,895 | **0.05409012333987733…** | **<1/16** |

Formally, for **every output difference** `Γ` of the **complete 2048-bit round**,

\[
\Pr_{X\gets\mathrm{Unif}(\{0,1\}^{2048})}
  [F_r(X)\oplus F_r(X\oplus\Delta)=\Gamma]
\le T_{s,k}\le\max_{t=0}^{127}T_{t,k}
\]

with `k ∈ {6,7,12}` specified by the *fixed Chi input difference*, and **all 128 sites** covered. All numerical upper bounds come from exact integer numerators with common denominator **`2^240`**; the worst site in every Chi class is site `64` (`lane_a=0`, byte_a=4; `lane_b=4`, byte_b=0). The exact maximum numerators are in the certificate. The conservative class-independent corollary for this specified one-cell input-difference family is **`DP_round(Δ,Γ)<1/2`**. The statement applies to any single round constant; it does **not** imply exponential decay when iterating rounds.

### Composition proof without a false independence assumption

Let `d=L(Δ)` and set `U=C(L(X))`. Both `L` and `C` are permutations on unrestricted full states, hence `U` is **uniform without conditioning**. Since `d` is nonzero only in one Chi cell `s`, the intermediate output difference `δ=C(L(X))⊕C(L(X)⊕d)` is nonzero and confined to the same cell: it takes one of **65,535** possible values. For a fixed one-cell output difference `δ`, linearity of Butterfly gives exactly `B(δ)` as Pressure's input difference. The independent Pressure shears, on a **uniform unrestricted** Pressure base, give a full-output differential probability bound

\[
Q_s(\delta)=\prod_{j=1}^{16}
  \frac{M_j(B(\delta))}{32768},
\]

where each `M_j` is the **maximum count over all 1,024 five-bit output profiles**, with the exact three-slice input profile read from the 64 MiB low5 Pressure DDT table. This is a valid upper bound for **every specified full Pressure output difference**, not a claim of a global probability for one *unfixed* difference.

For a prescribed final difference `Γ`, partition the actual event by the intermediate Chi-output difference `δ` into disjoint events `E_δ`. Without making any assumption about Chi/Pressure conditional independence,

\[
\Pr(E_\delta)\le\Pr[\Delta C=\delta]\le2^{-k}
\quad\text{and}\quad
\Pr(E_\delta)\le
\Pr_{U\,\mathrm{uniform}}[P(B(U))\oplus P(B(U\oplus\delta))=\Gamma']
\le Q_s(\delta).
\]

The **second** inequality holds because `E_δ` is a subset of an *unconditional* event over the uniform `U`; conditioning on a Chi output difference is **not** performed. The final suffix `R_r` only relabels the target difference `Γ'`. Therefore

\[
\Pr[\Delta F_r=\Gamma]
\le\sum_{\delta\in\{0,1\}^{16}\setminus\{0\}}
      \min(2^{-k},Q_s(\delta))
       =:T_{s,k}.
\]

This is a **union bound of minima**, not the unjustified product of a Chi probability and a Pressure probability. The cap `2^-k` is certified from the inherited exact local Chi DDT. Each Pressure `Q_s(δ)` is the product of 16 counts over `32768=2^15`, hence has denominator `2^240`; every summand is the exact integer `min(∏_j M_j, 2^(240-k))/2^240`. An independent source-backed GMP program sums all terms **exactly**, over all sites, without floating-point rounding. As an additional check, the untruncated pressure-only site sum `Σδ Q_s(δ)` is at most **0.94422684208987733…**; the Chi caps tighten it to the three table values above.

### Finite verification and restricted scope

- **128 × 65,535 = 8,388,480** nonzero one-Chi-cell output-difference candidates, with **at least one** nondeterministic five-bit Pressure shear after Butterfly in every case. Total nondeterministic-shear incidences: **122,946,848** across all candidates. The largest *single fixed-δ* suffix bound is **5/16**; this is **not** the complete-round DP bound for an unconditioned Chi input difference.
- Separate source-based `C + GMP` audit constructs **2,048 original-C Butterfly basis responses**, verifies **512** independent whole-state Butterfly linearity cases, and exhaustively computes **all 128 × 4** exact raw/capped site sums (common denominator `2^240`). It independently recomputes the original Abyssal byte S-box DDT to verify the **510/32,130/32,895** Chi input-difference class counts.
- A differently implemented NumPy Butterfly and full vectorized scan independently recounts **every one of the 8,388,480 cases**, verifying the complete nondeterministic-shear histogram and six probability-weight thresholds, and cross-checking **every exact GMP site sum** (maximum finite double-precision discrepancy `1.67e-16`). Exact inequalities `<1/2`, `<1/3`, `<1/16` are tested directly on the GMP integers, not inferred from floating-point approximations.
- Original-scalar-source tests: **4,096** local Chi pair supports and Butterfly linearity replays, **65,536** Pressure projected output transitions verified feasible in the exact five-bit table, and **256** full-round API/layer-order comparisons. All passed. Original source/header and the complete 64 MiB finite table have SHA-256 checksums in the accompanying README.
- Counts such as **8,388,275** of 8,388,480 one-cell `δ` with fixed-δ `Q_s(δ)≤2^-6` are **combinatorial**; they are *not* averages over the actual Chi DDT, input-message distribution, or multiround trail probabilities.

**Interpretation:** This provides a conservative quantitative differential bound for a **complete one-round Krakken transformation** on a precisely specified class of unrestricted input differences—an upgrade from separate S-box and Pressure component properties. It does **not** establish a general one-round maximum DP across all 2048-bit input differences, a complete multi-round characteristic/hull bound, a restricted 159-byte hash-domain bound, or any full-cipher security level. It is not permissible to multiply these bounds from round to round because the intermediate difference and base become correlated.

---

## WORK-PRESS-DIFF-LOW5-007 — Exact Pressure five-low-bit differential table and sixteen-pair projected bound

**Status:** New **exact standalone Pressure component** result from the unmodified
Krakken scalar C/header, independent of and without interrupting the `[2,1]`
activity campaign. Certificate: `KRAKKEN_PRESSURE_LOW5_CERTIFICATES.zip`.
This extends `WORK-PRESS-DIFF-LOW4-006`; it does not replace the earlier
low-two/low-three/low-four relations.

### Exact five-bit theorem and independent audit

For either independent Pressure arithmetic shear, before the B/D output
rotations, take `x=a&31`, `y=c&31`, and `z=(c>>17)&31` (or the analogous
`b,d` pair). The original 64-bit source gives the exact 5-bit projection

```text
U = (x + (y XOR z)) mod 32,
V = (y + U) mod 32.
```

These three 5-bit input slices are disjoint and freely assignable for the
unrestricted component; `A<<31` has no effect on the low five bits. For a
prescribed five-component XOR differential profile
`(dx,dy,dz,dU,dV)`, define `N` as the number of the `32^3` local bases
`(x,y,z)` producing that pair of output differences. The exhaustive source-
pinned native-C generator evaluates **32^6 = 1,073,741,824** complete
local base/difference pairs and counts all **32^5 = 33,554,432**
profiles, storing the full count table as little-endian `uint16`.
An independently written NumPy implementation recomputes and agrees on
**every count**. Its full marginal reduction (summing output-high-bit
and input-difference-high-bit extensions) reconstructs the earlier
four-bit table exactly, including both counts and feasible support.

| Verified projected quantity | Exact result |
|---|---:|
| Five-bit profiles in total | 33,554,432 |
| **Feasible** | **2,523,208** |
| **Impossible** | **31,031,224** |
| Candidates admitted by lifting exact low4 alone | 3,361,024 |
| **New exclusions beyond low4** | **837,816** |
| Local bases for every prescribed five-bit input difference | 32,768 |
| Exhaustively evaluated local base/difference pairs | 1,073,741,824 |
| Nonzero input profiles with deterministic low5 output | 7 |
| Input profiles with maximum individual local probability 1/64 | 4,576 |
| Largest individual probability for other nonzero input profiles | 1/2 |

Exactly seven **nonzero projected input differences** have a deterministic
projected output: packed `(dx<<10)|(dy<<5)|dz` values
`0010`, `0200`, `0210`, `4000`, `4010`, `4200`, `4210` (hex).
They toggle only one or more most-significant bits of the three input
5-bit slices. Including the zero input difference gives eight deterministic
input profiles. All other 32,760 projected input differences have maximum
output multiplicity ≤16,384/32,768=**1/2** under uniform component bases;
**4,576** have a sharper maximum exactly **512/32,768=1/64**.
All counts are even by the XOR-pair involution on local bases.

**Source verification and independent algorithm.** The original pinned
64-bit scalar `pressure_arx_scalar` was replayed for 32,768 systematic
nibble-triple bases plus 50,000 full-word test bases in **both** A/C and
rotated B/D shears, totaling **165,536** branch checks with zero
mismatches. An independent **four-carry bitwise dynamic program** counts
any specified low-k differential profile exactly for `1≤k≤17`: its state
tracks the two addition carries in both executions and processes eight
possible `(x_i,y_i,z_i)` input-bit combinations per bit. The algorithm
matches **10,006** saved full-table five-bit counts and independently
matches full-base brute-force enumeration on **120 six-bit** and **32
seven-bit** selected profiles. The carry DP provides a way to query wider
projections without producing exponentially larger complete tables; the
complete six-/seven-bit support spaces have **not** been exhaustively
classified here.

### Exact composition of the 16 independent shears *within Pressure*

The 32 original input words split into 16 disjoint pairs `(a,c)` and `(b,d)`.
For a **fixed full 2048-bit XOR input difference Δ** and a uniformly
random unrestricted 2048-bit Pressure input `X`, the 16 sets of local
base slices are **independent uniform**. Let `d_j` be each pair's three
5-bit projected input differences; let `e_j` be its two projected output
differences (undo B/D rotations by 7 and 19 bits first). Then, for a
specified vector of projected Pressure output differences `e`,

```text
Pr[all 16 specified projected output differences | fixed Δ]
       = product_{j=1}^{16} N(d_j,e_j) / (32768^16).
```

For a specified **full-word output difference Γ**, the full-word event
implies its 16 output projections. Consequently the genuinely sound,
source-pinned component-only **full-output differential upper bound** is

```text
Pr_X[Pressure(X) XOR Pressure(X XOR Δ) = Γ]
    <= product_{j=1}^{16} max_e N(d_j,e) / (32768^16).
```

Each shear with a non-deterministic projected input profile contributes a
factor **at most 1/2**, so if `m` of the 16 projected input profiles are
non-deterministic this proves `DP_Pressure(Δ,Γ)≤2^-m`. The full count
histogram often yields a much sharper, Δ-specific factor than 1/2.
For instance, choose Δ on every one of the eight columns as

```text
Δa = Δb = 0,
Δc = Δd = 0x0000000000120002.
```

Every pair then has `(dx,dy,dz)=(0,2,9)`, whose maximum five-bit
output count is **512** out of 32,768. Thus **for this fixed full-state
input difference, any particular full 2048-bit Pressure output
XOR difference Γ obeys**

```text
DP_Pressure(Δ,Γ) <= (512/32768)^16 = 2^-96.
```

The projected choice `(dU,dV)=(9,9)` at every pair attains `2^-96`
for the **16 projected observations**, not necessarily for any one full
2048-bit output difference. A reusable source-aware gate
`pressure_low5_gate.py` computes these exact projected event probabilities
and Δ-specific full-output upper bounds from 32 input and 32 output
64-bit XOR-difference lanes, correctly undoing B/D rotations. It was
checked on **1,024** actual full 32-lane Pressure differential pairs from
the original C (zero false rejections), as well as 512 deliberately
corrupted projection checks.

**Quantifier restrictions, essential for security interpretation:** This is
an exact component-level probability statement **only** for a **fixed
input difference** to Pressure and uniformly distributed unrestricted
Pressure input bases. Earlier Chi and Butterfly layers can cause the
Pressure input difference to depend on the base state and become
correlated with it. The product above therefore **cannot** be applied
naively to arbitrary full-round Krakken characteristics or to the
valid 159-byte hash domain. No multi-round differential-hull or hash
security-bit claim follows. Strong local projections and deterministic
special directions must both be considered in the composed analysis.

**Certificate integrity:** 64 MiB little-endian count-table SHA-256
`68189c4b03bb68960967149db031cc0e5969a216d2eab335d05b8a504f7c2067`;
previous low4 count table SHA-256
`c94b1ee648395e3d17bf431356b4cb85a011ae7d033fbf03c50ced6dbd4dced5`;
original source SHA-256
`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`,
header SHA-256
`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

---

## WORK-PRESS-DIFF-LOW4-006 — Exact Pressure four-low-bit differential profile table (independent component study)

**Status:** New exhaustive **local** theorem, source-pinned to the unmodified scalar `krakken.c`/`krakken.h`. This extends the **low-bit projection** from `PRESS-DIFF-001` (two bits) and `PRESS-DIFF-002` (three bits) without re-proving either, and is **not** a result of the ongoing `[2,1]` scan. The table and code are in `KRAKKEN_PRESSURE_LOW4_CERTIFICATES.zip`.

### Exact theorem and proof

Consider either local arithmetic shear pair in a Pressure column *before output rotations*:

```text
A = a + (c XOR (c >> 17))                 (mod 2^64)
C = c + (A XOR (A << 31))                 (mod 2^64).
```

At the low four bits write `x=a&15`, `y=c&15`, `z=(c>>17)&15`. Because `4<=17`, the slices `y,z` are disjoint and arbitrary. Since the 31-bit left shift has zero low four bits, the **exact** projected map is

```text
U = (x + (y XOR z)) mod 16
V = (y + U) mod 16.
```

Define a prescribed projected differential profile as five four-bit values `(dx,dy,dz,dU,dV)` and call it feasible when **some** local base `(x,y,z) ∈ {0,…,15}^3` has the requested XOR input/output differences. The C enumerator tests every `16^3` base for every `16^3` projected input difference, totaling **16,777,216 exact comparisons**, and records a count for each `16^5 = 1,048,576` profile. An independently ordered NumPy implementation recomputes and matches **every one of the 1,048,576 counts**, not just the Boolean supports. Because the projected variables are genuinely independently assignable within a full 64-bit state, this is the exact existential projection of the unrestricted Pressure difference relation.

| Certified quantity | Value |
|---|---:|
| All projected five-nibble profiles | 1,048,576 |
| **Exactly feasible** | **105,032** |
| **Exactly impossible** | **943,544** |
| Exact three-bit feasible profiles recovered by projection | 4,376 |
| Four-bit profiles admitted by *lifting the exact three-bit relation alone* | 140,032 |
| **Additional four-bit exclusions beyond that lifted relation** | **35,000** |
| Distinct local bases per fixed projected input difference | 4,096 |
| All local base/difference pairs independently counted | 16,777,216 |

**Exact restricted probabilities.** With an unrestricted uniform local Pressure base, for a fixed 12-bit projected input difference, the probability of the particular 8-bit projected output difference is its saved transition count divided by 4096. Exactly **seven** nonzero projected input differences yield deterministic low-four-bit output differences: `008, 080, 088, 800, 808, 880, 888` (hex packed as `dx dy dz`), corresponding to toggling only one or more *highest bits* in the three input nibbles. All other nonzero input profiles have every projected output probability ≤**1/2**, and the bound is attained (`dx dy dz=011`, `dU dV=01`, count 2048). These deterministic **four-bit projections** are **not** deterministic 64-bit output differences.

**Source correspondence.** For the first A/C Pressure pair the low-four-bit formula follows directly from the source; the B/D pair uses the same formula after undoing the source's 7- and 19-bit output rotations. An original-C harness exercised **4,096 systematically enumerated local bases** and **20,000 deterministic full-word random controls** for each branch, totaling **48,192 successful branch-level checks**. The full-table digest is `c94b1ee648395e3d17bf431356b4cb85a011ae7d033fbf03c50ced6dbd4dced5` (little-endian `uint16` counts indexed by the concatenated five nibbles). The original scalar source and header SHA-256 remain `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` and `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

**Scope guardrails:** Passing this exact low-four-bit gate is **not sufficient** for an actual full-word Pressure transition, still less for a reachable `[2,1]` trail. Earlier Chi/Butterfly layers may induce nonuniform or correlated internal bases. No global product-of-local-probabilities argument or 8-round security-bit bound follows. The certificate is useful as a **future additional necessary filter**, independently of and without modifying the currently running six-/seven-bit `[2,1]` campaign.

---

## WORK-INT-ALL159-001 — Complete two-round boundary for all one-byte **universal linear-mask integral** classes

**Status:** NEW, original-scalar-source-pinned **analytic sufficient-mask derivation + exhaustive finite spanning certificates**, with complete original-C replay and independent opposite-pivot rank audit. This is an extension of `INT-BYTE-001`, `INT-BYTE-002`, and `DIV-BYTE-001`; **no permanent ledger ID assigned yet**.

### Exact theorem statement

Let `F_r(m)` be the full 2048-bit state after `r` **complete** rounds of the uploaded scalar Krakken permutation with XRBD enabled, initialized from the first block of any exactly 159-byte message `m`, padded by fixed byte `0x86`. For each message-byte coordinate `p∈{0,…,158}` and each fixed choice `b` of the other message bytes, define the 256-point XOR cube sum

```text
S_(r,p)(b) = XOR_(v=0..255) F_r(b with byte p set to v).
U_(r,p)    = { beta in GF(2)^2048 :
                 for every valid base b, beta · S_(r,p)(b) = 0 }.
```

Then **for every one of the 159 byte positions**, exactly:

```text
                2 <= dim U_(1,p) <= 26
                     dim U_(2,p) = 0.
```

The dimension depends on `p`; the exact value for each byte is in the appendix. In aggregate these are **2,309 position-specific independent universal R1 mask directions** (not one joint vector space). The R1 dimension distribution has minimum 2 (bytes 009, 018), maximum 26 (bytes 154, 157), and median 14. The byte-zero case recovers `dim U_(1,0)=7` from existing `DIV-BYTE-001`, including its single-coordinate mask at state bit 907.

**Digest-coordinate refinement.** Let `D` be the 256-bit first-state-output-coordinate mask space, corresponding to the 32-byte reduced-round output projection. The source-verified intersection dimensions are:

| `dim(U_(1,p) ∩ D)` | Byte positions | After R2 |
|---:|---:|---|
| 0 | 126 | `dim(U_(2,p) ∩ D)=0` |
| 1 | 27 | `dim(U_(2,p) ∩ D)=0` |
| 2 | 6 | `dim(U_(2,p) ∩ D)=0` |

For quick lookup, the 33 byte positions with nonzero reduced-round digest-coordinate R1 balances are given as `position (dimension)`:

045 (1), 060 (1), 068 (1), 076 (1), 084 (1), 097 (1), 098 (1), 100 (1), 103 (2), 105 (1), 106 (2), 108 (1), 111 (2), 113 (1), 114 (1), 116 (1), 119 (2), 121 (1), 122 (1), 124 (1), 127 (2), 132 (1), 133 (1), 135 (1), 140 (1), 143 (1), 148 (1), 151 (1), 153 (1), 154 (1), 156 (2), 157 (1), 158 (1).

**Interpretation:** Every defined one-byte cube family has at least one nontrivial universal full-state linear integral after one complete round, but **no nonzero universal linear mask after two complete rounds**. In 33 families, an R1 universal mask can be restricted entirely to the first 256 output bits; none can after R2. This is a precise *loss of this class of balances at R2*, not a proof that all integral/partition attacks terminate there.

### Why the R1 lower bounds are valid for **every** base, not just sampled bases

1. The exact first-round linear prefix `L = Pi ◦ Rho ◦ MDS ◦ Theta` maps the eight coordinate basis directions of message byte `p` to eight fixed state directions. These were obtained from the pinned scalar C functions for every `p`.
2. The serial-Chi component at word pair `(a,b)` and byte offsets `(t, (t+4) mod 8)` is the 16-bit permutation
   `g(x,y) = (S(x XOR y), S(y XOR S(x XOR y)))`, where `S` is the pinned Abyssal byte S-box. **The four-byte offset is critical**: both word-level Chi rotations are by 32 bits. An exhaustive check of all 65,536 local inputs against original `chi_scalar` passed.
3. Each cell receives eight cube directions with local rank ≤8. If local rank is <8, its eighth derivative is identically zero because its 256 values are repeated an even number of times. If local rank is 8, its derivative was evaluated by eight exact XOR transforms on the complete 65,536-element truth table of `g`. Across all 159 positions and 128 local cells, only **52 distinct rank-eight local direction subspaces** were needed; each was exhaustively evaluated across **all** local bases.
4. After the linear Butterfly layer, one low-bit output of each of Pressure's four words is affine in the inputs to Pressure, with the following **exact** bit identities (indices denote input bit positions):

   ```text
   output a bit 0             = a0 XOR c0 XOR c17
   output rotl(b,7) bit 7     = b0 XOR d0 XOR d17
   output c bit 0             = a0 XOR c17
   output rotl(d,19) bit 19   = b0 XOR d17
   ```

   Thus 8 Pressure chains give **32 linear observations** of the post-Chi state. Round constants contribute only fixed affine terms, and InkCloud is a word permutation and rotation, so these 32 observations correspond to 32 explicitly known full-round output positions. The identities were checked against original C on 4,000 arbitrary full-state samples (32 bits per sample) in addition to their direct source-level derivation.
5. For every position, the span of **all** transformed local eighth derivatives was computed as a subspace of `GF(2)^32`, treating local bases as arbitrary (an overapproximation of actual reachable bases). Its orthogonal complement gives `k_p` linearly independent, **universally** balanced full-state R1 masks, because each annihilates every local component contribution separately. The resulting dimensions `k_p` range 2..26.
6. Separately, source-replayed first-round cube-sum witnesses for position `p` have rank **`2048-k_p`**, certifying `dim(U_(1,p)) ≤ k_p`. Combining the analytic inclusion with this finite upper bound gives **exactly `dim(U_(1,p))=k_p`**. Their 256-bit digest-coordinate projections were also rank-tested independently to obtain the 0/1/2 digest-only classification above.
7. Source-replayed second-round cube-sum witnesses for every position have rank **2048**, hence their joint orthogonal complement is zero. Therefore `U_(2,p)={0}` for all positions.

**Universal-quantifier argument:** the sample bases are used only to *find finite spanning witnesses*. A mask claimed universally balanced must annihilate **every** cube sum and thus every saved witness; full rank refutes any nonzero such mask. Conversely the first-round masks are established by exact local derivatives over **all possible local Chi bases**, not by accepting a pattern seen in a finite sample.

### Source, implementation and certificate audit

Pinned authoritative source supplied on 2026-11-03 (exact matches to earlier theorem ledger):

- `krakken.c` SHA-256: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`.
- `krakken.h` SHA-256: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.
- Eight-round scalar implementation, little-endian byte interpretation (`uint64_t[32]` / 256-byte sponge state). The statement concerns this pinned definition and the 159-byte domain, not arbitrary variable-length messages or every disk-encryption API path.

| Reproduction step | Verified result |
|---|---:|
| Local two-byte serial-Chi table against original C | **65,536/65,536 passed** |
| Distinct rank-eight local direction spaces fully differentiated | **52** |
| Universal-R1 mask dimensions vs finite R1 ranks | **159/159 exact matches** |
| First-round cube sums recomputed using pinned scalar C | **323,323/323,323 match** |
| Second-round cube sums recomputed using pinned scalar C | **325,632/325,632 match** |
| Total original-scalar round-count-specific cube evaluations | **166,132,480** |
| Independent **lowest-pivot** GF(2) rank audit (producer used highest-pivot) | **159/159 R1 and 159/159 R2 pass** |
| Stored R1 rows annihilated by analytically derived masks | **All 323,323 rows, every mask** |
| Digest-only mask dimensions vs independent 256-bit projected rank | **159/159 agree** |
| R1 saved rank range / R2 saved rank | **2022–2046 / 2048 for every p** |

`KRAKKEN_INTEGRAL_ALL159_FULL_CERTIFICATES.tar` contains the original saved *R2* witnesses from the prior candidate computation (SHA-256 `a6529807b5efe5c299f45723b82c834b35ec6419a168216511cb0943f06a41e5`). The newly source-replayed *R1* witnesses are recorded in the separate `krakken_integral_round1_pilot/pNNN.r1.bin` files; package them alongside this theorem for independent third-party replay. The single living research report is **this file**; large certificate binaries need not be pasted into it.

The exact local-derivative source script, independent original-C replay implementation, low-pivot rank checker, 159-position rank CSV and numerical mask vectors are supplied separately with the audit package. Core artifact SHA-256 fingerprints:

- Analytic `r1_analysis.json`: `56a7bbd5d103b007a4a8630b9ec55de3bfe9a896390ff11fbab578e6727da86b`.
- Opposite-pivot `rank_audit.csv`: `28b90e589d97bbbbef71d2ea9f50e280de16e2ba48696db63a16cb43483b4038`.
- `krakken_integral_r1_exact.py`: `1b5eeada52f07172fee81a3f48ffee8d4aa34436b4aec79e4b0bf8d61a3aac1f`.
- `krakken_integral_scalar_replay.c`: `259a1a074e26d791f268c723f2b6c04298a0d8f19fcf955f82eab7a6b4845a49`.
- `krakken_integral_rank_audit.c`: `0e90803b63c2590e7cd0047ffa4efc8811896fb1cbf19134fd978b0c7dca6a00`.

**Limitations:** This result excludes *universal linear-mask XOR balances* for the **159 coordinate-byte cubes**. It does not eliminate arbitrary linear-combination input directions, higher-dimensional/special-base integral distinguishers, nonlinear output predicates, statistical/nonperfect balances, chosen internal states, multiblock inputs with differing prefixes, collision/preimage attacks or attacks that may reappear at later rounds. Full rank of a 2048-bit cube-sum span is also not a claim that 2048-bit outputs are random or independent. The source-verified replays establish scalar agreement on the saved cube inputs only, not functional equivalence between scalar and Krakken-Disk AVX2 for every state or round count. Independent *external* reproduction is not yet recorded.

### Distribution of exact universal R1 full-state mask dimensions

| dim U₁,p | Number of byte positions |
|---:|---:|
| 2 | 2 |
| 4 | 5 |
| 5 | 5 |
| 6 | 4 |
| 7 | 5 |
| 8 | 5 |
| 9 | 3 |
| 10 | 2 |
| 11 | 12 |
| 12 | 11 |
| 13 | 11 |
| 14 | 17 |
| 15 | 15 |
| 16 | 10 |
| 17 | 9 |
| 18 | 1 |
| 19 | 6 |
| 20 | 7 |
| 21 | 8 |
| 22 | 9 |
| 23 | 3 |
| 24 | 3 |
| 25 | 4 |
| 26 | 2 |

### Position-level certificate summary (complete 159-byte index)

In each triplet: `p` = message-byte index; `U₁,p` = exact first-round universal full-state linear-mask dimension; `digest` = dimension supported entirely on the first 256 output bits. At second round **both dimensions are 0 for every position**.

| Byte p | dim U₁,p | dim digest U₁,p | Byte p | dim U₁,p | dim digest U₁,p | Byte p | dim U₁,p | dim digest U₁,p |
|---|---|---|---|---|---|---|---|---|
| 000 | 7 | 0 | 001 | 7 | 0 | 002 | 4 | 0 |
| 003 | 5 | 0 | 004 | 8 | 0 | 005 | 8 | 0 |
| 006 | 7 | 0 | 007 | 8 | 0 | 008 | 4 | 0 |
| 009 | 2 | 0 | 010 | 6 | 0 | 011 | 4 | 0 |
| 012 | 4 | 0 | 013 | 8 | 0 | 014 | 5 | 0 |
| 015 | 7 | 0 | 016 | 6 | 0 | 017 | 4 | 0 |
| 018 | 2 | 0 | 019 | 5 | 0 | 020 | 6 | 0 |
| 021 | 6 | 0 | 022 | 5 | 0 | 023 | 5 | 0 |
| 024 | 14 | 0 | 025 | 14 | 0 | 026 | 12 | 0 |
| 027 | 15 | 0 | 028 | 14 | 0 | 029 | 17 | 0 |
| 030 | 15 | 0 | 031 | 14 | 0 | 032 | 15 | 0 |
| 033 | 14 | 0 | 034 | 12 | 0 | 035 | 15 | 0 |
| 036 | 14 | 0 | 037 | 16 | 0 | 038 | 14 | 0 |
| 039 | 11 | 0 | 040 | 13 | 0 | 041 | 12 | 0 |
| 042 | 13 | 0 | 043 | 11 | 0 | 044 | 13 | 0 |
| 045 | 13 | 1 | 046 | 13 | 0 | 047 | 12 | 0 |
| 048 | 16 | 0 | 049 | 16 | 0 | 050 | 14 | 0 |
| 051 | 15 | 0 | 052 | 16 | 0 | 053 | 17 | 0 |
| 054 | 16 | 0 | 055 | 14 | 0 | 056 | 17 | 0 |
| 057 | 15 | 0 | 058 | 14 | 0 | 059 | 15 | 0 |
| 060 | 15 | 1 | 061 | 16 | 0 | 062 | 15 | 0 |
| 063 | 13 | 0 | 064 | 14 | 0 | 065 | 11 | 0 |
| 066 | 15 | 0 | 067 | 11 | 0 | 068 | 12 | 1 |
| 069 | 15 | 0 | 070 | 13 | 0 | 071 | 14 | 0 |
| 072 | 14 | 0 | 073 | 11 | 0 | 074 | 15 | 0 |
| 075 | 11 | 0 | 076 | 12 | 1 | 077 | 15 | 0 |
| 078 | 13 | 0 | 079 | 14 | 0 | 080 | 14 | 0 |
| 081 | 11 | 0 | 082 | 15 | 0 | 083 | 11 | 0 |
| 084 | 12 | 1 | 085 | 15 | 0 | 086 | 13 | 0 |
| 087 | 14 | 0 | 088 | 11 | 0 | 089 | 8 | 0 |
| 090 | 13 | 0 | 091 | 7 | 0 | 092 | 9 | 0 |
| 093 | 12 | 0 | 094 | 10 | 0 | 095 | 11 | 0 |
| 096 | 22 | 0 | 097 | 19 | 1 | 098 | 21 | 1 |
| 099 | 20 | 0 | 100 | 17 | 1 | 101 | 22 | 0 |
| 102 | 21 | 0 | 103 | 19 | 2 | 104 | 25 | 0 |
| 105 | 23 | 1 | 106 | 23 | 2 | 107 | 24 | 0 |
| 108 | 22 | 1 | 109 | 25 | 0 | 110 | 24 | 0 |
| 111 | 22 | 2 | 112 | 22 | 0 | 113 | 19 | 1 |
| 114 | 21 | 1 | 115 | 20 | 0 | 116 | 17 | 1 |
| 117 | 22 | 0 | 118 | 21 | 0 | 119 | 19 | 2 |
| 120 | 22 | 0 | 121 | 19 | 1 | 122 | 21 | 1 |
| 123 | 20 | 0 | 124 | 17 | 1 | 125 | 22 | 0 |
| 126 | 21 | 0 | 127 | 19 | 2 | 128 | 20 | 0 |
| 129 | 18 | 0 | 130 | 20 | 0 | 131 | 20 | 0 |
| 132 | 16 | 1 | 133 | 21 | 1 | 134 | 21 | 0 |
| 135 | 20 | 1 | 136 | 17 | 0 | 137 | 14 | 0 |
| 138 | 16 | 0 | 139 | 16 | 0 | 140 | 13 | 1 |
| 141 | 17 | 0 | 142 | 17 | 0 | 143 | 16 | 1 |
| 144 | 12 | 0 | 145 | 9 | 0 | 146 | 10 | 0 |
| 147 | 11 | 0 | 148 | 9 | 1 | 149 | 12 | 0 |
| 150 | 12 | 0 | 151 | 11 | 1 | 152 | 25 | 0 |
| 153 | 23 | 1 | 154 | 26 | 1 | 155 | 24 | 0 |
| 156 | 22 | 2 | 157 | 26 | 1 | 158 | 25 | 1 |

---

## WORK-INT-NIBBLE-ALL159-002 — Universal nonlinear nibble-integral obstruction by complete round two

**Status:** NEW **source-pinned finite spanning theorem** for a specified nonlinear integral class. The proof uses 159 × 512 exact parity-histogram *affine difference* rank certificates, an independent GF(2) audit, and exhaustive original scalar-C replay of every saved cube. It extends `WORK-INT-ALL159-001` in a different direction: arbitrary Boolean predicates on **one aligned four-bit output nibble**, rather than arbitrary **linear** masks across 2048 output bits. **No new permanent registry ID assigned.**

### Precisely quantified theorem

Let `H` denote valid padded 159-byte first-block messages with zero initial capacity. For input-byte position `p=0,...,158`, choose any fixed values `b` for the other 158 message bytes. Form the complete 256-message coordinate cube by varying byte `p` through all values `v=0,...,255`. Let `F_2` be the full **2048-bit state** after **two complete rounds** of the pinned XRBD-enabled scalar permutation. For output-nibble index `q=0,...,511`, let `N_q` extract output bits `4q,...,4q+3` from `F_2` in the native little-endian state layout.

For *every* such `(p,q)` and every Boolean truth table `f: GF(2)^4 -> GF(2)`, define the cube parity

```text
  I_(p,q,f)(b) = XOR_(v=0..255) f( N_q( F_2(b with byte p set to v) ) ).
```

The certificate establishes:

```text
  For every p in 0..158 and q in 0..511:

    I_(p,q,f)(b) is independent of b   IF AND ONLY IF   f is constant.

  In particular, no nonconstant f has universal XOR parity 0 or 1.
```

Thus all **81,408** defined position/nibble projection families exclude every one of their **65,534 nonconstant nibble Boolean predicates** as a *universal base-independent* cube-parity relation at **complete R2**. Constant functions give parity zero because the cube size is even (256). This is not a statement about arbitrary joint nibble functions, unrestricted nonlinear state predicates, special-base cubes, other input-direction subspaces, or R3–R8.

### Short proof: 16-entry parity histograms and affine spanning

For each `(p,q)` and other-byte assignment `b`, construct a 16-bit vector `h_(p,q)(b)` whose bit `z` is the parity of the number of cube members yielding nibble value `z`. Each `h` has **even** Hamming weight since 256 is even. The even-weight subspace

```text
  E = {x in GF(2)^16 : x dot (1,1,...,1) = 0}
```

has dimension 15. For a Boolean truth table represented by vector `f in GF(2)^16`, the cube parity equals the dot product `f dot h_(p,q)(b)`.

For each of the 81,408 families, the certificate saves actual valid-message bases `b_0,...,b_k` whose **differences**

```text
  h_(p,q)(b_i) XOR h_(p,q)(b_0)
```

span rank **15**, thus span all of `E`. If the cube parity for `f` were fixed, equal either zero or one, for **every** valid base `b`, then `f` would be orthogonal to all these witnessed differences. Therefore `f in E^perp = span{(1,1,...,1)}`, i.e. `f` is constant. Conversely, constant truth tables have zero parity over every 256-message cube. The proof is exact and finite once the stored C-computed histogram witnesses are verified; no random-distribution assumption enters the implication.

**Important distinction:** Merely finding rank 15 in the *linear* span of the histograms would exclude universal zero balances but might leave universal one-parity relations. This theorem explicitly checks the **affine difference span**, which eliminates both.

### Certificate and source audit

| Check | Result |
|---|---:|
| Pinned scalar `krakken.c` SHA-256 | `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` |
| Pinned `krakken.h` SHA-256 | `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c` |
| Complete byte-coordinate input cube families | **159** |
| Disjoint aligned output nibbles per family | **512** |
| Total independently certified projections | **81,408** |
| Independent *low-pivot* affine difference rank | **15 / 15 in all 81,408** |
| Deterministic valid-base witnesses | **4,225** (24–32 per input byte position) |
| Original scalar-C source replay of full cubes | **4,225 / 4,225**, each of 256 members |
| Two-round scalar permutation calls in replay | **1,081,600** |
| Replay histogram discrepancies | **0** |

The C producer computes all 512 parity histograms at once for each actual 256-message cube; it uses high-bit GF(2) pivots and stops only after **all 512 affine difference ranks** reach 15 for the input byte position. Each certificate stores the 159-byte base and all 512 16-bit histogram values. A **separate C replay** recomputes every histogram from the saved base with the original scalar round function. An **independent Python verifier** checks source hashes, strict headers and record counts, even parity, and every 16-bit difference rank using **low-bit pivots**, producing `rank_audit.json`. Every stored base is a valid 159-byte message context; the varied byte and fixed `0x86` padding are handled explicitly.

Reproduction package: `KRAKKEN_NONLINEAR_NIBBLE_R2_CERTIFICATES.zip` includes the producer/verifiers, original source pins, all 159 compact witness files, replay logs and audits. The producer and replay independently ran successfully on this exact pinned source revision. This is internal source-based verification, not external peer review.

### Exact first-round obstruction witnessed at 232 of these nibble projections

The previously proved complete first-round universal **linear-mask** spaces `U_(1,p)` were intersected with each of the 512 four-dimensional output-nibble mask spaces. Because `U_(1,p)` was already exactly characterized by analytic local derivatives and finite first-round rank certificates, these intersections are exact (not a sample extrapolation):

| First-round intersection dimension | `(input-byte p, output-nibble q)` combinations | R2 for every combination |
|---:|---:|---|
| 0 | **81,176** | No nonconstant base-independent nibble parity |
| 1 | **232** | No nonconstant base-independent nibble parity |
| 2–4 | **0** | No nonconstant base-independent nibble parity |

Those **232 R1 universal nonzero linear nibble balances** occur across **71 distinct input-byte positions**; **33** use output nibbles wholly contained within the first 256 state bits (the reduced-round digest-position projection). Therefore we have a precise **R1-exists → R2-absent** boundary for these **232** individual integral projection families. For the other 81,176 pairs the inherited linear-mask analysis shows no **linear** R1 nibble balance, but it does **not** exclude nonlinear R1 predicates—do not claim all pairs "start at R1". The R2 nonlinear absence covers all 81,408 either way.

Source for the R1 comparison: `r1_analysis.json` and `krakken_nibble_r1_intersections.py`; complete details in `r1_nibble_intersections.json`. This is a derived corollary of the existing exact R1 mask theorem, not a new local derivative theorem.

### Security interpretation and exact limitations

This theorem closes **fixed Boolean truth tables on one 4-bit output nibble** as universal base-independent parity integrals after two complete rounds for the 159 specified valid-message coordinate-byte cube families. The conclusion holds for *all* valid bases because finitely many verified bases are sufficient to refute any purported universal predicate. It **does not** bound statistical biases or the probability of a zero sum over specially selected bases, and it does not imply arbitrary nonlinear integral, division-property, chosen-internal-state, or full eight-round resistance. Functions combining several nibbles are outside its quantified class.

---

## WORK-INT-BYTE-ALL159-003 — Nonlinear **full-output-byte** integrals: complete R2 obstruction for all 159 coordinate-byte cubes

**Status:** NEW, source-pinned **finite spanning theorem**, with complete original scalar-C replay, an independent GF(2) elimination direction, and cross-certification against `WORK-INT-NIBBLE-ALL159-002`. This is a strict enlargement of the *nonlinear output predicate* class from one 4-bit aligned nibble to one **8-bit aligned output byte**, including all 32 reduced-round digest-position byte coordinates. The permanent theorem ledger is unchanged.

### Precisely quantified result

Retain domain **H**: exactly 159 message bytes, fixed `0x86` pad, zero initial capacity, XRBD enabled. Let `F₂(m)` be Krakken's **complete two-round** 2048-bit state. For input-byte position `p∈{0,…,158}` and each fixed valid choice `b` of the other 158 message bytes, vary byte `p` over all `v∈GF(2)^8`. For output-byte index `q∈{0,…,255}`, let `B_q` extract **aligned** state byte `q` (bits `8q,…,8q+7`). For any arbitrary Boolean truth table `f:GF(2)^8→GF(2)`, set

```text
     I_(p,q,f)(b) = XOR_(v=0..255) f( B_q( F₂(b with byte p set to v) ) ).
```

Then the following **holds for all 40,704 position/projection pairs**:

```text
For every p = 0..158 and q = 0..255:
  I_(p,q,f)(b) is independent of all other message bytes b
    if and only if f is one of the two constant Boolean functions.

Equivalently: all 2^256 − 2 nonconstant Boolean truth tables
on each individual aligned output byte fail to have universal
base-independent cube parity after complete round 2.
```

The two constant functions have cube parity zero because there are **256**, an even number, messages in each cube. The quantifier covers **all bases**, not just the sampled contexts, because a finite full-rank *difference* certificate refutes the existence of any nonconstant universal predicate.

### Exact mathematical proof from finite base witnesses

For each `(p,q,b)`, let `h_(p,q)(b)∈GF(2)^256` be the **parity histogram** of the 256 output-byte values encountered over the cube: bit `z` records whether `z` occurs an odd number of times. Since there are 256 cube members,

```text
  h_(p,q)(b) dot (1,1,...,1) = 0.
```

Hence every `h` lies in the even-parity subspace `E⊆GF(2)^256` with dimension **255**. The cube parity for any truth table `f` is `f dot h_(p,q)(b)`. For each of the 40,704 `(p,q)` combinations, the source-pinned certificate contains actual valid-message base contexts `b₀,…,b_k` for which the vectors

```text
    { h_(p,q)(b_i) XOR h_(p,q)(b₀) : i ≥ 1 }
```

have **rank exactly 255**. Thus they span **all** of `E`. If `f dot h_(p,q)(b)` were constant for every valid `b` (zero **or one**), then `f` would annihilate these differences; therefore `f∈E^⊥`, the 1-dimensional space generated by the all-ones truth table. Its only two elements are the two constant functions. Conversely, a constant truth table always gives cube XOR parity zero. **QED, conditional only on correctness of the source-pinned finite witness recomputations.**

The **affine difference rank**, not merely the linear span of the histograms, is essential to exclude hypothetical universal *parity-one* nonconstant predicates.

### Complete verification record

| Audit item | Confirmed result |
|---|---:|
| Input-coordinate byte cubes | **159 / 159** |
| Aligned output bytes per cube | **256** (including digest-position bytes `q=0..31`) |
| Position/output projection families | **40,704 / 40,704** |
| Maximum allowed affine-difference rank | **255** |
| Minimum and maximum measured ranks across all families | **255 / 255** |
| Saved valid-message base contexts | **42,149** (262–271 per position; median 265) |
| Original scalar-C two-round permutations in complete replay | **10,790,144** |
| Earlier nibble-certificate cube bases crosschecked | **4,225** |
| Exact output-nibble parity histograms crosschecked | **2,163,200** |
| Mismatches or rank failures | **0** |
| Python/ctypes independent reconstruction | **Four spaced `(input byte, output byte)` cases, all rank 255** |

Pinned SHA-256 `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`; `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. The producer computes exact two-round C cube histograms using **high-bit GF(2) elimination**. The separate verifier reads the saved **159-byte base contexts**, recomputes every byte-value histogram from the original C implementation, and checks the independent **low-bit GF(2) elimination**. For the shared bases, projecting the 8-bit histograms to either 4-bit nibble reproduces the earlier independently saved nibble histograms exactly. Python spot checks separately reconstruct four byte histograms using `ctypes` and Python integers.

**Reproducibility artifacts:** `KRAKKEN_NONLINEAR_BYTE_R2_CERTIFICATES.zip`, including `krakken_byte_hist_producer.c`, `krakken_byte_hist_replay.c`, `independent_python_spotcheck.py`, `r1_byte_intersections.py`, all 159 compact saved-base witness files, `byte_rank_audit.json` with per-position hashes and counts, `producer.log`, `replay.log`, `r1_analysis.json`, `r1_byte_intersections.json`, and source-pinned `krakken.c`/`krakken.h`. Because the witness files store exact **base messages** instead of precomputed histograms, the independent verifier must reconstruct the histograms to audit the theorem. An early base-generator typo was caught in cross-auditing and corrected before these final certificates and replays; no inconsistent seed data is counted as verified.

### Exact documented R1→R2 transition for 232 output-byte families

The earlier `WORK-INT-ALL159-001` proved **exact first-round universal linear-mask spaces** `U_(1,p)` for every input-byte family. Intersecting each with the 8-dimensional linear coordinate space of one output byte yields:

| Dimension of universal **linear** R1 mask subspace within one output byte | `(p,q)` count | Complete R2 |
|---:|---:|---|
| 0 | **40,472** | No nonconstant universal byte-local Boolean parity |
| 1 | **232** | No nonconstant universal byte-local Boolean parity |
| 2–8 | **0** | No nonconstant universal byte-local Boolean parity |

The **232** nonzero linear first-round byte-local balances occur across **71** input-byte positions; **33** of the `(p,q)` pairs use one of the first 32 output bytes, corresponding to the reduced-round digest coordinates. These precisely characterized **linear** R1 structures cannot continue as **any nonconstant** universal Boolean predicate on that same output byte after complete R2.

The other **40,472** pairs lack proven universal *linear* first-round byte-local balances, but their nonlinear first-round predicates have not been exhaustively characterized. Do **not** claim that every one of the 40,704 families loses an existing first-round nonlinear structure. The proven uniform R2 absence is stronger than that historical qualification.

### Security meaning and scope boundaries

This is an exact **round-two stopping boundary** for the defined family of *base-independent complete coordinate-byte cube parities of arbitrary Boolean functions of one aligned output byte*. It extends single-nibble nonlinear certificates to functions mixing all **eight bits** of each output byte. It does **not** exclude functions jointly depending on bits from different output bytes, non-aligned arbitrary 8-bit selections, nonlinear *entire-state* functions, special-base balances, statistical/nonperfect biases, different or multi-byte cube directions, generalized hash-domain attacks, or actual eight-round security. No attack work-factor or security-bit estimate is derived. Source-based exhaustive replay is not independent external peer review.

---

## WORK-INT-MIXED44-ALL159-004 — Selected cross-byte 4+4 nonlinear integral predicates vanish by complete round two

**Status:** NEW, original scalar-source-pinned **finite spanning certificate** for a precisely specified cross-byte predicate family. Producer uses high-order GF(2) pivots, the complete independent scalar-C replay uses low-order pivots, and separate Python/`ctypes` spot checks reconstruct the histograms. This extends aligned-byte `WORK-INT-BYTE-ALL159-003` by allowing predicates to mix bits from **two distinct** state bytes. It is not a claim about every cross-byte pairing. **No permanent theorem ID assigned.**

### Exact result and proof

Let `p = 0..158` designate a varied message byte in the fixed-length 159-byte first-block hash domain **H**. Let `t = 0..31` index one of the **32 explicitly selected mixed 4+4-bit output projections** `W_t`, listed in `mixed_pairs.h` within the certificate package. Each window extracts a low or high nibble from *one* output byte and another low or high nibble from a *different* output byte. These span adjacent, distant, digest and capacity locations, with selected windows chosen to include known first-round sparse-mask supports. They are not all possible cross-byte windows.

For a valid choice `b` of the other message bytes and an eight-bit output value `z`, define the two-round cube parity histogram

```text
  h_(p,t,b)[z] = XOR_(v=0..255)
      [ W_t(F_2(b with message-byte p replaced by v)) = z ]

  h_(p,t,b) in GF(2)^256 ; parity(h_(p,t,b)) = 0.
```

For every `(p,t)` the saved original scalar-C witness bases establish

```text
   rank_GF2 { h_(p,t,b) XOR h_(p,t,b0) : b in saved finite bases } = 255,
```

which is the **entire 255-dimensional even-parity subspace** of `GF(2)^256`. A Boolean predicate truth table `f:GF(2)^8->GF(2)` has constant cube parity for *every* valid base only if it is orthogonal to all these histogram differences. Their orthogonal complement contains **only the two constant truth tables**, each of which has zero cube parity because the cube size is even. Therefore, for this exact class,

> **For all 159 byte-coordinate input cubes, all 32 selected split-byte output projections, and all nonconstant eight-bit Boolean functions of those projections, cube XOR parity cannot be base-independent after two complete Krakken rounds.**

A finite collection of full-rank witnesses disproves universal invariance for all other-message-byte assignments, without exhaustively enumerating the full message domain. It does not exclude special-base balances or statistical (nonuniversal) effects.

### Source-pinned evidence and first-round boundary

| Evidence | Verified value |
|---|---:|
| Coordinate input-byte cube families | **159** |
| Selected mixed 4+4 output windows per input position | **32** |
| Total `(input byte, selected cross-byte window)` families | **5,088** |
| Affine histogram-difference rank for **every** family | **255 / 255** |
| Actual 159-byte message bases used | **41,696** |
| Prior independent aligned-byte base witnesses reused exactly | **41,664** |
| Additional valid bases needed | **32** |
| Producer scalar-C two-round evaluations | **10,674,176** |
| Independent opposite-pivot C replay evaluations | **10,674,176** |
| Independent Python/`ctypes` check | **Four full-rank families; 268,544 additional two-round evaluations; 12 first-round mask/witness checks** |
| Certificate/replay discrepancies | **0** |

The source SHA-256 remains `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`; the header SHA-256 remains `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. Inputs have zero initial capacity, fixed byte `0x86` at message-buffer position 159, XRBD enabled, and use the *original first two complete rounds*, not a reduced or simplified Pressure model.

Combining the **previously established exact** universal linear-mask basis at complete R1 with each selected output window produces this inherited R1 intersection table:

| Universal **linear** R1 mask-space dimension restricted to one mixed window | Number of `(p,t)` pairs | After complete R2 |
|---:|---:|---|
| 0 | **4,727** | No nonconstant universal Boolean predicate |
| 1 | **307** | No nonconstant universal Boolean predicate |
| 2 | **54** | No nonconstant universal Boolean predicate |

Thus **361** specifically enumerated window families across **104** different message-byte positions have genuine first-round universal linear balances, representing **415 window-specific independent mask directions**. All 361 are excluded at R2 even for arbitrary nonlinear eight-bit predicates on the same split-byte windows. For example, the low nibbles of output bytes `(113,0)` for input-byte `p=0` have a one-dimensional R1 linear space, while the low nibbles of `(113,241)` for `p=24` have a two-dimensional R1 linear space; both examples pass the full rank-255 R2 certificate, and their R1 masks were spot-replayed against the original C source.

**Critical scope boundary:** The 32 selected windows are a small, named subclass of the `4×C(256,2)=130,560` distinct split-nibble pairs of output bytes. The theorem does **not** exclude all cross-byte predicates or all 16-bit Boolean functions of two full output bytes, all integrals, new structures at later rounds, or general eight-round distinguishers. R1 *nonlinear* predicate spaces have not been classified for all 5,088 windows. The 4,727 windows with no inherited **linear** balance do not establish that no nonlinear R1 balance existed. The complete R2 absence, however, covers every nonconstant Boolean predicate of each selected eight-bit window.

**Reproducibility:** `KRAKKEN_CROSSBYTE_MIXED44_CERTIFICATES.zip`, containing `mixed_pairs.h`, scalar source, original aligned-byte base records, 159 new cross-byte base records, independent source-level replay, Python/`ctypes` check, exact first-round intersection program, two audit logs, SHA-256 certificate report, and full reproduction instructions. The certificate archive and original ledger remain separate from this living summary. All audits are **internal**, not independent external review.

---

## WORK-DIFF-TRUNC-LSB-005 — Stronger one-round truncated-differential zero sets, with exact limits at R2–R8

**2026-11-03; status: new analytic refinement with finite original-C basis audit and explicit full-C counterexamples.** This is an **attack-side** improvement of permanent theorem `DIFF-TRUNC-001`, not a separately counted attack family. It was prompted by `EXTENDED_REPORT.md` (SHA-256 `c0fffde32853c75ecf32c52c41c2853a9e64ac0db3970896b068c320cdf36db7`). Only that report was attached; its named supporting `extended-results.json`, `peak-validation.json` and `one-round-proof.json` were not provided, so its broader statistical campaign is **reported, not independently audited here**. We independently reconstructed the deterministic construction and its complete-round counterexamples from source.

### Precise domain and construction

Use unrestricted 2,048-bit permutation inputs **P**, rather than valid first-block hash inputs **H**. At the input to the first serial-Chi layer, choose one of the **128** sites `(p,y,j)` with `p=0..3`, `y=0..3`, `j=0..7`. XOR a nonzero common byte difference `d∈{1,…,255}` into byte `j` of first lane `ca=8p+y` and byte `(j+4) mod 8` of its paired second lane `cb=8p+4+y`. Inverting the bijective linear prefix `L=Pi∘Rho∘Tentacle∘Theta` defines a unique round-input XOR difference `Delta`. This is precisely the unrestricted one-cell class already analyzed in `DIFF-TRUNC-001`.

The first serial-Chi S-box input is unchanged because the two byte differences cancel after the 32-bit rotation. The first Chi output is therefore unchanged, and the second Chi output difference is confined to one byte of lane `cb`. Consequently, **eight basis-bit responses under the linear Butterfly are sufficient** to bound the differential support entering Pressure for *every* base state and *every* nonzero `d` in the stated site.

### Analytic carry-free lemma and new guarantee

For one Pressure chain, write input low bits as `a0,b0,c0,d0` and bits 17 as `c17,d17`. With `A=a+(c⊕(c>>17))`, `B=b+(d⊕(d>>17))`, `C=c+(A⊕(A<<31))`, `D=d+(B⊕(B<<31))`, the *least significant output bits* are affine/linear over GF(2):

```
A_0 = a_0 XOR c_0 XOR c_17
B_0 = b_0 XOR d_0 XOR d_17
C_0 = a_0 XOR c_17
D_0 = b_0 XOR d_17
```

Carries cannot propagate into bit zero, and the shifts by 31 have zero bit zero. In particular, if any of these linear forms evaluates to zero on **all eight possible post-Chi one-byte difference basis responses**, that bit is guaranteed unchanged for *every* allowed XOR difference at the Pressure input, independent of the base state. Propagate through Pressure's two output rotations and the fixed InkCloud shuffle to obtain exact raw one-round output coordinates. Union these guarantees with the conservative unchanged-low-prefix sets of `DIFF-TRUNC-001`.

The source-pinned finite enumeration of the `128 × 8` Butterfly basis responses gives:

| Quantity | Result |
|---|---:|
| Aligned first-Chi sites | 128 |
| Nonzero diagonal byte differences per site | 255 |
| Old conservative guaranteed-zero output-bit incidences, summed over sites | 6,700 |
| New union of prefix and carry-free guaranteed-zero incidences | **7,756** |
| **Additional guaranteed-zero incidences** | **1,056** |
| Sites gaining at least one newly guaranteed coordinate | **123 / 128** |
| Sites without an increment | 5 |
| Largest increment at one site | 17 |

Here an *incidence* is a `(site, guaranteed output coordinate)` pair, **not** a different cryptanalytic attack, and there is no claim that all other output bits can change. The guarantee holds for all 255 byte differences at each site, but the incidence sum does not multiply by 255.

**Exact reference site:** `(p,y,j)=(0,0,0)`. `DIFF-TRUNC-001` guaranteed **200** zero raw-output bits there. The 22 coordinates of the uploaded report's one-round distinguisher are

```
11, 94, 139, 210, 350, 395, 466, 651, 722, 862, 907,
978, 1035, 1118, 1291, 1374, 1547, 1630, 1803, 1886, 1931, 2002
```

Of these 22, **12 are already in** the earlier 200-bit conservative guaranteed set; the **10 new coordinates** are

```
94, 139, 210, 350, 466, 722, 1118, 1291, 1374, 1630
```

Therefore **the combined guarantee has 210 distinct zero-output coordinates** for *all 255 nonzero byte differences* at this same site. The report's selected difference is `d=1`. The random-permutation comparison for its 22-bit event is approximately `2^-22`, as noted in the report; the stronger 210-bit guarantee can also be formulated as a random-permutation distinguisher with a much smaller false-positive probability for the specified fixed difference. This is a **one-round unrestricted-permutation** observation, not a valid-hash-input distinguisher.

### Independent source and computation audit

Original source fingerprints:

- `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
- `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`

We compiled these exact sources into a local shared library and used the **original C Butterfly** to enumerate all 1,024 site/basis responses. Python code independently applied the bit-zero formulas and the original conservative prefix bounds. It recovered **exactly the report's list of 22 coordinates**, the earlier theorem's reference-site 200-bit conservative set (including the same 15 wholly zero bytes), and the 210-bit combined set. The 128-site enumeration gave the totals above.

As an implementation replay, 128 sites × four nonzero difference values `01,80,a5,ff` = **512 unrestricted pre-Chi input pairs** were run through the original scalar C suffix `Chi→Butterfly→Pressure→Iota→Ink`. Every newly derived and previously guaranteed coordinate remained zero. Sampling checks implementation agreement; the universal guarantee follows from the analytic equations and exhaustive eight-basis support calculation.

For the selected `d=1` reference input difference, an independent GF(2) inversion of the actual `L` (rank **2048**) reconstructed the full round-input XOR difference. Fresh C executions then produced **one explicit counterexample at each of rounds 2,3,4,5,6,7,8** where raw output bit 11 of the difference was **nonzero**. The counterexamples show **the particular all-base deterministic bit-11 relation fails** at every depth 2–8. They do *not* prove the absence of other truncated differential patterns, correlations, or distinguishers at those depths, and do not imply that a 210-bit R1 condition must monotonically weaken across all later rounds.

The replay inputs, per-site coordinate increments, original pinned C source and buildable scripts are in `KRAKKEN_DIFF_TRUNC_LSB_EVIDENCE.zip`. This package is additional evidence; future updates should continue to modify **this single Markdown research ledger** rather than modifying the permanent theorem registry implicitly.

### Statistical triage from uploaded report (not a theorem)

`EXTENDED_REPORT.md` reports 30 groups × 8 depths × 2,304 output masks (=552,960 discovery comparisons, 8,192 sampled bases each), 44 fresh-validated one-round correlations and **no selected fresh-validated two-to-eight-round bias** under its thresholds. Its separate integral screen tests 32 chosen eight-dimensional cube geometries and found no zero-coordinate candidates passing 32 fresh validation cubes at depths 2–8. Its avalanche test observes individual-bit influences for all input/output bit pairs. All are **finite screens with explicitly limited masks, cubes, sample sizes and detection thresholds**. Non-detection is not an algebraic attack-family exclusion or a security-bit lower bound. The new report should **not** be counted as proving differential, linear, integral, or rotational attack families impossible at round two.

---

## WORK-DIFF-FULL-SINGLEBYTE-013 — All 40,545 one-byte valid-message differences force at least 52 original-round Chi calls

**Original full production eight-round Krakken**, not a reduced variant. For every two 159-byte first-block messages differing by a nonzero XOR value in exactly one of the **159 variable message bytes**, the original first Chi layer has **at least 52 active byte S-box calls**, independently of the valid message base. This is an exhaustive finite mathematical lower bound for the *defined one-byte input-difference family*, **not** a general full-message minimum. It strengthens the applicable one-round floor 5 only on that family.

Let `L = Pi ∘ Rho ∘ TentacleMDS ∘ Theta`. Each nonzero one-byte message difference `d` at position `p` produces a fixed pre-Chi difference `L(d e_p)`. For each one of 128 aligned Chi two-S-box byte sites, let `α = Δa[t] XOR Δb[(t+4)%8]` and `β=Δb[(t+4)%8]`. The **exact minimum local active-call count** over unrestricted pre-Chi bases is `ℓ(α,β) = [β≠0]` when `α=0`, otherwise `1+[β∉D_S(α)]`, with `D_S(α)={S(x) XOR S(x XOR α): x∈GF(256)}`. Each local bound holds for all valid message bases even though those bases need not be independent. Exact enumeration of **159×255=40,545** sums yields global minimum **52**, attained by this local relaxation at precisely 16 differences `(p∈72..87,d=0x08)`. A concrete **unrestricted-full-state** base achieving 52 is source-C replayed; no claim that the base is valid-H159 reachable.

By inherited exact *original full P* rules `A_r≥1` and `A_r=1⇒A_(r+1)≥3`, the corresponding eight cumulative activity floors for the one-byte family are **`[52,53,55,57,59,61,63,65]`**. **Arithmetic correction (2026-11-05):** The originally reported R3/R5/R7 floors `56/60/64` exceeded the consequences of the stated premises. A suffix of `t` rounds contributes at least `2t−1`; the corrected sequence shown above follows, with abstract counterexample `(52,2,1)` for R3. The R1≥52 and eight-round ≥65 statements are unaffected. The abstract sequence is not an actual permutation trail. The independent recurrence audit is `krakken_onebyte_multiround_arithmetic_audit.py` / `KRAKKEN_ONEBYTE_MULTIROUND_ARITHMETIC_AUDIT.json`.

The new work proves **no higher bound for A₂ itself**, no exact multiround optimum, and **no characteristic/hull probability bound**. It cannot rule out attacks employing multi-byte or general message differences.

**Certificate:** `KRAKKEN_FULL_ONEBYTE_ACTIVITY_CERTIFICATES.zip`, including `KRAKKEN_FULL_ONEBYTE_ACTIVITY_THEOREM.md`, a self-contained Python/C source verifier, full 40,545-byte floor table (SHA-256 `d711d831e97c351e45082e22dcb14b70b6b5528ba6b108706801a44b7cde1c94`), JSON audit, and pinned original C/H. Checks: 1,272 GF(2) input-basis Python vs source-C prefix identities, 2,048 source-C full input-basis inverse identities, exact DDT support, matching original-C unrestricted 52-call witness, 512 independent valid-message C replays, and a complete eight-round source-C concrete witness `[62,254,255,254,255,255,256,256]` (total 1,847). See separate report for complete quantifiers and derivation.

---

## WORK-DIFF-ACT-2026-11-03 — Strengthened eight-round differential activity corollary

**Status:** Derived from existing source-pinned theorems, not a new full-width differential transition proof.

`DIFF-PERM-003` proves for any nonzero unrestricted state difference that `A_r=1 ⇒ A_(r+1)≥3`, because both `[1,1]` and every defined `[1,2]` class have been excluded. Every round of the bijective permutation has `A_r≥1`. For any `R` consecutive rounds, the abstract necessary activity constraints imply

```text
    sum_(r=1..R) A_r ≥ 2R - 1.
```

For eight rounds: `Σ A_r≥15` (P). Combining with the exact input-rate theorem `DIFF-RATE-001` (`A₁≥5` for any nonzero valid 159-byte first-block difference) gives `Σ A_r≥18` (H). For the three differences in `DIFF-RATE-003`, adding the conditioned `A₂≥3` when `A₁=5` yields a bound of 19; the exact quantified three-difference corollary is as specified in the saved activity checker, and is not being generalized to other message differences.

The bound 15/18/19 is a **minimum number of active S-box calls under necessary constraints**, not a probability bound. Serial-Chi calls have dependent input distributions, and Pressure contributes nonlinear carry behavior. One must not multiply a local S-box `2^-6` probability by 18 to claim global `2^-108` security.

Reproducible arithmetic proof: `krakken_multiround_activity_upgrade.py` and `krakken_multiround_activity_upgrade.json` (generated separately); inherited theorem scope and model assumptions remain authoritative.

---

## Attack-family coverage policy and next targets

**A result counts as an exact stopping boundary only for an explicitly quantified property**, such as “for all 159 coordinate-byte cubes and all nonzero linear masks, no *universal* parity balance survives complete R2.” It does **not** justify “integral cryptanalysis is impossible after R2,” still less “most attack families are stopped by R2.” A later round can create a new structure even when a particular early structure is not preserved.

The most useful follow-ups while the `[2,1]` scanner runs are:

1. **Extend cross-byte nonlinear integral coverage.** `WORK-INT-MIXED44-ALL159-004` now closes **32 selected mixed 4+4 windows per one-byte input cube** at complete R2, including 361 families with inherited R1 universal linear balances. There remain 130,560 possible distinct split-nibble two-byte output windows (per input cube). Expand by symmetry classes or carefully chosen additional windows; do **not** generalize from 32 to all pairs. An unrestricted 16-bit truth table on two full output bytes requires up to 65,535 independent histogram differences and is substantially harder.
2. **Generalized cube directions.** Extend beyond the 159 coordinate-byte cubes to structured eight-dimensional affine direction subspaces. Explicitly preserve valid-message reachability and prove each subclass's R1 and R2 balance spaces before claiming a stopping round.
3. **Pressure–Chi composition.** Convert the 16-D deterministic Pressure translation classification into full-round reachable/differential-probability bounds rather than relying on unrestricted local observations.
4. **Broader differential and linear estimates.** Finish necessary-condition soundness and support-completeness audits for `[2,1]`, then study full-width trail probabilities and multiround linear hulls across Pressure.

### Evidence and campaign status

### Earlier `[2,1]` checkpoint audit: first-byte positions 013–023 (2026-11-03; historical snapshot)

**Superseded checkpoint note:** Position 023 was partial **at the time of this earlier audit**. The complete, independently checked `i023(1).json` and positions 024–027 are recorded in the next section; **do not add the 22,000 previously examined 023 sites twice.**

**Classification:** Computational coverage/integrity audit of the *necessary-condition screening campaign*, **not a new attack-family theorem** and not an independent reconstruction of each solver UNSAT proof.

Uploaded records `i013.json`–`i023.json` were reaudited with the original `krakken_21_all_positions_audit.py` against their complete compressed one-byte-per-site decision records. Each zlib+base64 payload decoded to `examined` bytes, reproduced its saved SHA-256, exactly matched all seven classification counts, respected lexicographic `j/q/branch` indexing and the expected site count `256*(255-i)`, and agreed on source, header, solver model fingerprints, and timeout settings across all files. The bundled `krakken_21_all_positions_equiv.py` in `KRAKKEN_21_EQUIVALENCE_SPEEDUP.zip` independently hashes to the fingerprint pinned in the checkpoints (`4330cc4c21e04519dc2d87644ab3231f16d534eddcb8e285b5f0ec1a37f1c120`). Source `krakken.c` and header `krakken.h` match the authoritative pinned hashes.

| First byte `i` | Expected sites | Examined | Remaining | `low6_sat` | `unknown` | Recorded disposition |
|---:|---:|---:|---:|---:|---:|---|
| 013 | 61,952 | 61,952 | 0 | 0 | 0 | **Complete; all screened out** |
| 014 | 61,696 | 61,696 | 0 | 0 | 0 | **Complete; all screened out** |
| 015 | 61,440 | 61,440 | 0 | 0 | 0 | **Complete; all screened out** |
| 016 | 61,184 | 61,184 | 0 | 0 | 0 | **Complete; all screened out** |
| 017 | 60,928 | 60,928 | 0 | 0 | 0 | **Complete; all screened out** |
| 018 | 60,672 | 60,672 | 0 | 0 | 0 | **Complete; all screened out** |
| 019 | 60,416 | 60,416 | 0 | 0 | 0 | **Complete; all screened out** |
| 020 | 60,160 | 60,160 | 0 | 0 | 0 | **Complete; all screened out** |
| 021 | 59,904 | 59,904 | 0 | 0 | 0 | **Complete; all screened out** |
| 022 | 59,648 | 59,648 | 0 | 0 | 0 | **Complete; all screened out** |
| **023** | **59,392** | **22,000** | **37,392** | **0** | **0** | **Partial checkpoint; scanned prefix only** |

**Batch totals:** Positions 013–022 close **608,000** candidate sites: low0 UNSAT 148,459; low3 UNSAT 445,179; low4 UNSAT 9,110; low5 UNSAT 3,627; low6 UNSAT 1,625; six-bit SAT 0; UNKNOWN 0. Partial 023 adds **22,000** screened-out sites (5,148 low0; 16,473 low3; 376 low4; 3 low5), but is **not a closed position**. Thus the 11 uploaded files contain **630,000 examined and excluded sites**, **0 unresolved in their recorded prefixes**, and **37,392 not yet examined in i023**.

**Cumulative accounting (with provenance):** Earlier positions 000–012 cover 828,672 sites *assuming the user-reported completion of 008/009*, which are not rechecked in this upload batch; previously checked 010/012 seven-bit child reports eliminated their 125 six-bit SAT survivors each, while 011 had no survivors. Adding completed 013–022 produces **1,436,672 / 8,355,840 = 17.19%** closed through position 022, conditional on those earlier records. Adding the examined prefix of 023 produces **1,458,672 / 8,355,840 = 17.46%** examined so far. The latter is an **examined** percentage, not a completely closed-position percentage. These counts do not justify a global exclusion of `[2,1]` trails unless necessary-condition soundness, completeness of the targeted activity-support representation, and all remaining cases are established.

### `[2,1]` checkpoint audit: completed positions 023–027 (2026-11-03)

**Classification:** New source-pinned **computational checkpoint/integrity audit**, not a new theorem, not fresh execution of each solver UNSAT query, and not yet a proof that the modeled two-byte support class exhausts every true `[2,1]` differential activity pattern.

The uploaded complete checkpoint `i023(1).json` and `i024.json`–`i027.json` were checked with the original `krakken_21_all_positions_audit.py`. For every file: expected count `256 × (255 − i)`, complete/examined/records_count agreement, strict zlib+base64 decoding, record SHA-256 equality, valid class codes, all seven classification counts from decompressed records, and consistency of unresolved-example fields. All five were complete and had `low6_sat=unknown=0`; no seven-bit continuation was necessary for this batch. The authoritative `krakken(3).c` / `krakken(3).h` hashes and the optimized scanner extracted from `KRAKKEN_21_EQUIVALENCE_SPEEDUP.zip` match all checkpoint fingerprints. Earlier partial `i023.json` contained 22,000 recorded decisions: **the first 22,000 bytes of the new 59,392-decision checkpoint match those older records exactly**, with the same model and configuration hashes.

| `i` | Sites excluded | low0 UNSAT | low3 UNSAT | low4 UNSAT | low5 UNSAT | low6 UNSAT | six-bit SAT | UNKNOWN |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 023 | 59,392 | 13,806 | 44,578 | 877 | 6 | 125 | 0 | 0 |
| 024 | 59,136 | 13,157 | 45,603 | 376 | 0 | 0 | 0 | 0 |
| 025 | 58,880 | 14,873 | 42,374 | 1,007 | 626 | 0 | 0 | 0 |
| 026 | 58,624 | 15,993 | 40,872 | 1,759 | 0 | 0 | 0 | 0 |
| 027 | 58,368 | 14,568 | 41,889 | 1,911 | 0 | 0 | 0 | 0 |
| **Sum** | **294,400** | **72,397** | **215,316** | **5,930** | **632** | **125** | **0** | **0** |

**Cumulative non-overlapping accounting:** previously recorded fully closed sites through 022: **1,436,672**. Add 023–027 **294,400** once, yielding **1,731,072 / 8,355,840 = 20.7169%** excluded over first-byte positions **000–027**. Equivalently, since the prior status already counted 22,000 sites from partial 023, this update adds **272,400 newly examined sites** relative to the earlier **1,458,672 examined** figure. The cumulative status assumes the **user-reported** closures of 008/009, whose reports were not reaudited here. Remaining campaign spatial candidates: **6,624,768**; next first-byte position 028 has **58,112** sites.

**Audit artifact:** `KRAKKEN_21_I023_I027_AUDIT.json` preserves the per-position record digests, counts, source-fingerprint verification, and old/new 023-prefix equality. These hashes protect internal reporting consistency, **not** formal SMT proof certificates or the mathematical soundness of the relaxed necessary equations. No global `[2,1]` exclusion or eight-round security claim follows yet.


### `[2,1]` checkpoint audit: completed positions 028–031 (2026-11-03)

**Classification:** Source-pinned **checkpoint record integrity and campaign-coverage audit**. No new theorem ID is assigned. Every stored necessary-condition solver exclusion remains conditional on model correctness; no solver UNSAT instance was independently re-solved for this update.

All four supplied `i028.json`–`i031.json` checkpoints passed `krakken_21_all_positions_audit.py` with strict base64/zlib decoding, full record SHA-256 verification, position/index order, `expected_sites = 256 × (255-i)`, reported classification totals, `complete=true`, `compiled_C_validated=true`, empty `first_unresolved`, zero `low6_sat` and zero `unknown`. Both original source digests and the SHA-256 of `krakken_21_all_positions_equiv.py` extracted from `KRAKKEN_21_EQUIVALENCE_SPEEDUP.zip` match all four checkpoint fingerprints; all four screening-model hash maps match exactly.

| `i` | Sites excluded | low0 UNSAT | low3 UNSAT | low4 UNSAT | low5 UNSAT | low6 UNSAT | six-bit SAT | UNKNOWN |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 028 | 58,112 | 12,432 | 44,652 | 528 | 125 | 375 | 0 | 0 |
| 029 | 57,856 | 15,453 | 42,278 | 125 | 0 | 0 | 0 | 0 |
| 030 | 57,600 | 13,396 | 42,444 | 9 | 1,376 | 375 | 0 | 0 |
| 031 | 57,344 | 13,351 | 42,986 | 876 | 6 | 125 | 0 | 0 |
| **Sum** | **230,912** | **54,632** | **172,360** | **1,538** | **1,507** | **875** | **0** | **0** |

**Cumulative non-overlapping accounting:** Add **230,912** new exclusions to the earlier **1,731,072** through position 027: **1,961,984 / 8,355,840 = 23.4804%** covered through first-byte position **031**. This agrees with the independent arithmetic identity `256 × Σ_(i=0)^31 (255−i) = 1,961,984`. There remain **6,393,856** configurations in the full spatial campaign; next position **032** contains **57,088** sites. The cumulative figure continues to depend on previously user-reported 008/009 closures, since those checkpoint files are not included in this batch. No seven-bit refinement was needed for 028–031.

**Artifacts and limits:** `KRAKKEN_21_I028_I031_AUDIT.json` contains the per-file SHA-256 values, decompressed record digests, source/model hashes and exact site counts. Hash agreement is an integrity check, not independent UNSAT proof verification. The new results do **not** establish the global `[2,1]` exclusion until all candidate configurations and necessary-condition soundness/coverage obligations are discharged. The earlier 023–027 section is retained as historical evidence and is not double-counted.


### `[2,1]` seven-bit child refinement audit: positions 036, 044, 066 and 074 (2026-11-04)

**Classification:** Independent **JSON case-list integrity and source-fingerprint audit** of four uploaded seven-bit continuation reports, **not** an independent execution or formal verification of Z3 UNSAT proofs and **not** a new `[2,1]` impossibility theorem. The associated `i036.json`, `i044.json`, `i066.json`, and `i074.json` six-bit parent checkpoint files were **not present** in this upload, so their SHA-256 fingerprints and the exact identity of the original survivor sites **cannot yet be independently matched against parent payloads**. The child files specify both expected parent-file and parent-decompressed-record hashes so this linkage can be checked with the final ZIP.

| First byte `i` | Second byte `j` | Parent reported sites | Parent reported excluded | `low6_sat` survivors | Seven-bit UNSAT | Remaining in child report |
|---:|---:|---:|---:|---:|---:|---:|
| 036 | 068 | 56,064 | 55,939 | 125 | **125** | **0** |
| 044 | 076 | 54,016 | 53,891 | 125 | **125** | **0** |
| 066 | 098 | 48,384 | 48,259 | 125 | **125** | **0** |
| 074 | 106 | 46,336 | 46,211 | 125 | **125** | **0** |
| **Total** | — | **204,800** | **204,300** | **500** | **500** | **0** |

**Independent child audit:** All four JSON files parse; `tested=parent_survivors=len(cases)=125` in every file; all listed `(i,j,q,branch)` coordinates are unique, within range, correctly sorted, and exactly match the claimed `(parent_status,low7)=(low6_sat,unsat)` statuses. Each child has `complete_survivors=true`, `sat=0`, `unknown=0`, `remaining_unresolved=0`, `closed_position=true`. Its `parent_examined` exactly equals `256×(255−i)`, and `parent_excluded+parent_unknown+parent_survivors=parent_examined`. Every child hashes to the identical source C/H fingerprints pinned throughout this research, and **all nine available referenced model/audit scripts** match their advertised SHA-256 hashes on disk. The complete independent audit code and JSON result are `KRAKKEN_21_LOW7_I036_I074_AUDIT.py` and `KRAKKEN_21_LOW7_I036_I074_AUDIT.json`.

**New pattern, not yet a symmetry proof:** All four survivor groups have **`j−i=32`**. Their ordered list of **125 `(q,branch)` cases is byte-for-byte equivalent as structured data**: **79** `first` and **46** `second` branch configurations, spanning **79** distinct `q` values. The same ordered list is also present in the previously audited **010→042** and **012→108** seven-bit reports (the latter has `j−i=96`). This recurring class may reflect shift/word symmetry of the **relaxed** model, but six identical survivor patterns do **not** establish such a symmetry theorem or permit reducing the untested campaign without proof.

**Cumulative campaign accounting:** The user reports all positions **000–074** closed, accounting arithmetically for **`256×Σ_(i=0)^74(255−i)=4,185,600`** distinct spatial configurations, **50.09%** of the full 8,355,840; there are **4,170,240** spatial configurations left in positions 075–254. The percentage of **positions** closed is **75/255 = 29.41%**. In this update, only the **four child files** were newly audited; other positions from 032–074 remain **user-reported** until their parent files and any additional refinement files are supplied. **Never double-count** the 500 low7 cases: they are already included in the four parents' 204,800 spatial configurations. Even after the complete campaign, a global theorem additionally requires an audit that the screened necessary conditions are sound and the spatial representation covers every real `[2,1]` trail support.

### `[2,1]` archive parent/child closure audit: positions 031–075 (2026-11-04)

**Audit class:** independent **file/record integrity, campaign coverage, source-hash, and exact low7 parent-child linkage** for user-uploaded `krakken_21_campaign1.tar.gz` (archive SHA-256 `b9e28d2b1d9fa4a05f62081f87d03cf6286606da11a7530d9e124748002f6d58`). This is a new, stronger audit of the earlier 036/044/066/074 child-only reports: all four missing six-bit parent checkpoints are **now present and verified**. It is **not** an independent rerun of millions of SAT/SMT solver decisions, not a check of the global model's soundness or support completeness, and not a full `[2,1]` impossibility proof.

**Archive scope and accounting:** 45 uniquely named files, exactly `i031.json`–`i075.json`, with no gaps. Every position 031–074 is marked complete and contains the mathematically expected `256(255-i)` spatial records. Position 075 is **partial** at **22,000/46,080** and has no recorded six-bit SAT or UNKNOWN among its examined prefix; its remaining **24,080** sites are not excluded by this snapshot. The 44 completed positions contain **2,280,960 sites**. The whole archive records **2,302,960** examined sites, of which six-bit stages label **2,302,460 UNSAT**, **500 low6 SAT (unresolved at that relaxation)**, and **zero UNKNOWN**. Four separate seven-bit refinements resolve precisely those 500 SAT cases as UNSAT, leaving **zero unresolved among the examined archive sites**.

| Six-bit screening stage | Archived classification count (031–075 examined prefix) |
|---|---:|
| `lsb_unsat` | 555,188 |
| `low3_unsat` | 1,692,421 |
| `low4_unsat` | 39,586 |
| `low5_unsat` | 10,140 |
| `low6_unsat` | 5,125 |
| `low6_sat` (then independently refined) | 500 |
| `unknown` | 0 |
| **Total examined** | **2,302,960** |

**Exact parent→child binding — previously pending, now resolved:** For all four problematic positions, the **entire raw parent JSON file hash** equals the `parent_sha256` stored in the corresponding child report; decoded zlib/base64 record hashes equal `parent_records_sha256`; and the **exact ordered set of all 125 `low6_sat` spatial coordinates** equals all 125 child case records, with no duplicates or omissions. The child statuses are **125 UNSAT, zero SAT, zero UNKNOWN**, `complete_survivors=true`, and `remaining_unresolved=0`. All four survivor groups have `j=i+32` and the same 125 `(q,branch)` cases (79 `first`, 46 `second`), but no symmetry theorem is inferred from that observation.

| First byte `i` | Second byte `j` | Parent sites | `low6_sat` | Exact child-matched low7 UNSAT | Unresolved |
|---:|---:|---:|---:|---:|---:|
| 036 | 068 | 56,064 | 125 | 125 | 0 |
| 044 | 076 | 54,016 | 125 | 125 | 0 |
| 066 | 098 | 48,384 | 125 | 125 | 0 |
| 074 | 106 | 46,336 | 125 | 125 | 0 |
| **Total** | — | **204,800** | **500** | **500** | **0** |

**Integrity verification:** All 45 raw decision vectors decode with `base64(...,validate=True)` and zlib; the decoded byte lengths, SHA-256 digests and exact status histograms agree with every parent JSON file. The `complete` flags match expected lengths; the coordinate order and any reported unresolved examples agree with the deterministic `(j,q,branch)` index map. All archive files share a consistent C/H/source-model hash and solver configuration fingerprint. The original scalar C/H match the supplied digests; **all eight referenced scanner-model file hashes** were verified from local files or from `KRAKKEN_21_EQUIVALENCE_SPEEDUP.zip`. Archived `i031.json` is **byte-for-byte identical** to our previously audited i031 checkpoint, resolving the overlapping boundary without double-counting.

**Global progress with provenance:** The archive by itself audits positions **031–074 completed**, and **22,000** sites at partial 075. Conditional on the prior 000–030 recorded closure (notably, 008/009 remain user-reported rather than backed by files in this archive), positions **000–074** amount to **4,185,600 / 8,355,840 = 50.0919%** completed/excluded within the necessary-condition model; 075's partial 22,000 raises *examined* sites to **4,207,600 / 8,355,840 = 50.3552%** with **4,148,240** not yet examined. The positions themselves are only **75/255 = 29.41%** completed; early positions contain more sites. Never add the four 125-case child refinements to the spatial denominator: each child is a reconsideration of an already-counted parent record.

**Reproducible audit artifacts:** `KRAKKEN_21_CAMPAIGN1_AUDIT.py` (self-contained archive audit with four attached low7 child files and original pinned C/H), `KRAKKEN_21_CAMPAIGN1_AUDIT.json` (all per-position SHA-256 values, complete screening counts, explicit parent–child bindings, source/model fingerprints and cumulative accounting). The source/model necessary-condition soundness and exhaustive global `[2,1]` support coverage still require distinct mathematical audits before any full-P transition theorem may be claimed.

---

- `[2,1]` campaign total: 8,355,840 spatial candidates. Positions **000–007** were reviewed as complete and closed in prior runs, totaling **515,072** exclusions, conditional on model soundness. The campaign launched positions 008–254 automatically. Newly uploaded parent checkpoints **010, 011, 012** are complete, source-pinned and have zero UNKNOWN. For 010 and 012 their separate seven-bit child reports each mark all 125 six-bit survivors UNSAT, with zero remaining unresolved, and parent-record digests match; 011 has no six-bit SAT survivors. This establishes **187,392** further recorded exclusions across those three positions, conditional on model soundness. The user reported 008 and 009 closed, but their checkpoint files were not part of this new audit. No solver proof search was rerun here; do not silently promote the report-level campaign to an unrestricted `[2,1]` theorem.
- Reuse source-pinned artifact hashes, source-matched C/Python validation, local Pressure soundness evidence, finite solver UNSAT evidence, and separate seven-bit refinement checkpoints. Relaxed SAT means unresolved; UNKNOWN means unresolved; neither is an exact trail.
- Keep independent review/certificates distinguishable from sampled experiments. Do not infer deployment security from a reduced-round or restricted-domain theorem.

### Living update log

| Date | Working entry | Change | Verification |
|---|---|---|---|
| 2026-11-05 | `WORK-CHI-CALL-SUPPORT-028` | **New exact local source theorem:** serial-Chi active byte-call count equals count of nonzero post-Chi output bytes for every state pair, including both calls within one word pair; all `[2,1]` *support-location labels* are counted. Exact endpoint formulas establish a first-only corner case with `ΔA=0` even though `ΔU≠0`. **Does not establish solver support-completeness or globally exclude `[2,1]`.** | Original source C/H SHA-256 pinned; independent audit replay PASS: S-box permutation, 65,280 S-box derivative pairs, 130,560 algebraic endpoint cases, 104 original-C endpoint cases and 128 original-C full-32-word checks. `KRAKKEN_CHI_SUPPORT_LEMMA.md`, `KRAKKEN_CHI_SUPPORT_AUDIT.py`, `KRAKKEN_CHI_SUPPORT_AUDIT.json`. |
| 2026-11-05 | `[2,1]` position-176 progress (user-reported) | Running campaign reached `i=176`; if all 0–175 finished, counted closed spatial supports = **7,546,880/8,355,840 (90.32%)**; `i=176..254` collectively **808,960** sites. | No checkpoint/log files for this new range supplied in this conversation. Do not represent it as an independently audited closure, and do not claim global `[2,1]` theorem. |
| 2026-11-05 | `WORK-EMP-CONDITIONED-A15-R8-023` | Directly challenged full 8R digest with 1,572,864 chosen `A₁=5` pairs drawn from three previously selected 159-byte Δ families, two independent seeds, at R1/R2/R4/R8. R8 prefix-zero counts t=8/12/16/20 **[6035,384,24,1]** vs ideal **[6144,384,24,1.5]**; mean 256-bit XOR HW per group **127.974–128.022**. Extreme 1R structural bias detected, not present in the measured later rounds. Across 4608 R2/R4/R8 bit checks, most extreme Bonferroni-adjusted binomial p≈0.358. | Source C/H SHA checks; 256 random and 768 conditioned original-C permutation comparisons, 278 original-C hash checks, 768 A1=5 generator controls, all 24 complete JSONL result groups and independent analysis. Finite statistical observations only, not an eight-round security theorem. `KRAKKEN_SECURITY_GUARANTEES_AND_CONDITIONED_A15.zip`. |
| 2026-11-05 | `WORK-LIN-CONDITIONED-A15-022` | For 3 pinned valid159 Δ conditioned on exact `A₁=5`, the four **reduced-one-round** digest-coordinate bits 11–14 have total variation ≤`(53/2)2^-392=2^-387.272...` from uniform. Reason: `A₁=5` partitions into 32 equal codim40 affine fibers, and inherited permanent `LIN-RATE-005` bounds *all* message-parity correlations. | Independently reconstruct 1272 original-C prefix basis outputs and certify rank40 for each Δ, 5 two-root Chi gates and zero extra active gates, local Pressure 4-bit Walsh L1 coefficients; independent original-C full-permutation inverse checks (24). Inherits LIN-RATE-005's source-pinned proof, not re-proved from zero. R1-only, four bits only, no claimed R8 exponent. |
| 2026-11-05 | `WORK-SPONGE-INJECTIVITY-021` | Original full 8R `K` bijective by layer inverses; padded message streams identical outside one rate block never merge to equal **full state**; all distinct valid one-block messages of lengths 0–159 have different full post-absorb states. Exact generic one-block pair capacity/digest-prefix collision formulas supplied for **ideal random K only**. Ideal sponge `c=768` query-budget indifferentiability bound explicitly separated from actual permutation claims. | Source-pinned Θ involution, GF(256) inverse rank8, Sbox permutation, serial Chi/Butterfly/Pressure/Ink inverse algebra; 24 full original-C eight-round inverse replays; sponge indifferentiability sourced to BDPV Theorem 9. Does not prove collision-free 256-bit digest or concrete 128/256-bit security. |
| 2026-11-05 | `WORK-PRESS-FULLWORD-AFFINE-RULEBOOK-019` | Complete source-equation-derived 14–16-circuit check for full-word Pressure **affine** relaxation; standalone uniform-base rank bound `Pr[Δout]≤2⁻ᵏ`. In prior three-delta `-018` residual scan, all 124,502 Chi-compatible endpoints fail first Pressure pair by elementary zero-row constraints; parity circuits contribute no further exclusions there. | Independent eight-library circuit enumeration, 10,000 actual modular-addition derivative identity checks, 12,000 generic-vs-compact consistency checks (4,000 actual transitions), exact prior 1,068,288-assignment scan, source C/H verified. `KRAKKEN_PRESSURE_AFFINE_RULEBOOK_AUDIT.zip`. |
| 2026-11-05 | **Corrigendum:** `WORK-DIFF-FULL-SINGLEBYTE-013` | Fix cumulative activity floors at R3/R5/R7 to **55/59/63** (formerly 56/60/64); corrected R1–R8 sequence **[52,53,55,57,59,61,63,65]**. No change to first-round 52 or eight-round 65. | Independent activity-only dynamic program with explicit abstract minimizers; reviewer-identified arithmetic inconsistency, not an observed cryptanalytic counterexample. |
| 2026-11-04 | `WORK-DIFF-FULL-SINGLEBYTE-013` | Full original H159: all 159×255 fixed single-byte XOR differences force **A₁≥52** for every valid base, by exact local S-box DDT support after linear prefix. With inherited full-P `1→≥3`, necessary cumulative floors **[52,53,55,57,59,61,63,65]**; local floor 52 attained with unrestricted full-state base only. | Reproducible Python+original-C certificate enumerating all 40,545 cases; 1,272 independent relevant linear-basis comparisons, 2,048 inverse basis checks, explicit source-C attainment and 512 valid message pair tests. No claim of new A₂-only or full-hash probability theorem. |
| 2026-11-04 | `[2,1]` parent/child campaign archive audit 031–075 | New parent archive verifies **44 fully closed positions 031–074** (2,280,960 sites) and **partial 075 at 22,000/46,080**; all **500/500** previous low6 SAT cases in 036/044/066/074 are linked exactly by parent-file hash, parent-record hash and all survivor coordinates to seven-bit UNSAT children. **Zero unresolved among 2,302,960 archived examined sites.** Conditional aggregate closed 000–074 **4,185,600 (50.09%)**, examined including partial 075 **4,207,600 (50.36%)**. | 45/45 checkpoint SHA/count/payload checks; original pinned source C/H; eight scanner file fingerprints; i031 exact historical overlap; four 125-case complete parent/child bindings. Audit JSON + reproducible Python script; solver/model-soundness/support-completeness still open. |
| 2026-11-04 | `[2,1]` low7 child audit 036/044/066/074 | Four complete 125-case seven-bit continuation files report **500/500 UNSAT, 0 remaining**; all are `j=i+32`, with exactly identical 79-first/46-second `(q,branch)` patterns (also matching prior child 010 and 012). User-reported total closed through 074: **4,185,600/8,355,840 (50.09%)**. | Independent child-case/bookkeeping checks, local source/model SHA-256 verification and reusable audit JSON/Python; **four six-bit parent payloads absent, parent linkage awaits final ZIP**. No independent SMT UNSAT validation or global theorem. |
| 2026-11-04 | `WORK-REDUCED-MDS-BFLY-PRESS-ACT-012` | For reduced Tentacle/Chi/Butterfly/Pressure/Iota and valid 159-byte input, **A₁=4⇒A₂≥2**. Necessary cumulative activity floor increases **R2 5→6** and **R8 14→15**; sequence 1..8 `[4,6,7,9,10,12,13,15]`. Earlier bound 14 superseded; no exact R2 optimum proved. | Analytic original-source byte-support and even/odd parity proof including `ROTL13` all-ones exception, 65,280 stage-0 cases, 2,048 original-C Butterfly basis comparisons, 8,192 source-C suffix replay pairs, exact activity DP; supporting ZIP. |
| 2026-11-03 | `WORK-REDUCED-BFLY-PRESS-ACT-010` | Reduced **Chi→Butterfly→Pressure→Iota** adjacent-round activity: **1→≥8** byte S-box calls. Exact 65,280/65,280 one-byte Butterfly supports reach all 32 output words; eight Pressure columns retain even/odd shear activity; four next Chi column pairs force ≥8 total. **Not full original P/H.** | All 8,192 byte-to-word GF(2) matrices rank 8; 2,048 independent Python-vs-C bit bases; original-C exhaustive 65,280; 4,096 source-C suffix sample comparisons; analytic inverse/Chi activation proof. |
| 2026-11-03 | `WORK-DIFF-COMPOSE-TWOCHI-DIAG1-009` | Exact class of two distinct active Chi cells, each with aligned `(0x01,0x01)` input-byte difference after L: all 8,128 cell pairs, 131,096,512 exact joint Chi intermediate candidates; **one complete round specified full-output DP < 1/4** with worst conservative dyadic upper bound `274865743872/2^40`, including 56 pairs with deterministic low5 Pressure projection candidates; low4/low5 two-cell projection deficiencies 456/176 | Original scalar-C all-pair exact upward-rounded integer scan; independent Python Butterfly and low-pivot rank check; NumPy exact uint64 full all-pair recount; ten exact `2^-240` Python-big-int spot sums; GF2 linear prefix inversion rank 2048, 384 original-C complete-round pair replays; archived source/table hashes |
| 2026-11-03 | `WORK-DIFF-COMPOSE-ONECHI-008` | First certified complete-round full-output DP bound for differences supported on exactly one 16-bit Chi cell after the invertible linear prefix: all 128 × 65,535 cases, class-dependent exact upper bounds <1/2, <1/3, <1/16 | Source-backed GMP exact 2^240-denominator site-sum certificate, independent NumPy full recount of all 8,388,480 candidates, original-C replay (4,096 Chi/Butterfly, 65,536 Pressure, 256 full-round); uses Chi caps via union of minima—not false probability products |
| 2026-11-03 | `WORK-PRESS-DIFF-LOW5-007` | Exhaustive 5-bit Pressure projection: 2,523,208/33,554,432 profiles feasible, 837,816 newly excluded beyond lifted low4; exact conditional 16-shear projected product for standalone Pressure and Δ-specific full-output DP upper bounds (explicit example ≤2^-96). Carry-state DP independently extends queries through low17 bits | C 2^30 local base/difference enumeration; independent full NumPy 2^25-count match and full low4 marginal; 165,536 original-C branch checks; 10,006 independent carry-DP low5 table comparisons, 120 low6 and 32 low7 independent full-base checks; 1,024 full Pressure source gate replays; strict fixed-Δ unrestricted uniform Pressure-base scope |
| 2026-11-03 | `WORK-PRESS-DIFF-LOW4-006` | Pressure local four-low-bit differential relation: 105,032 feasible five-nibble profiles out of 1,048,576; excludes 35,000 additional profiles beyond lifted exact low-three-bit relation. Seven nonzero deterministic low4 directions; all other projected input differences have single-output probability ≤1/2 on uniform local bases | Full 16,777,216 pair C enumeration; independent NumPy replay of all 1,048,576 counts (identical SHA-256); 48,192 original-C branch-level source checks; strict local projected-domain scope |
| 2026-11-03 | `WORK-DIFF-TRUNC-LSB-005` | Refinement of known unrestricted one-round diagonal-Chi truncated differential: 128 sites, 123 newly strengthened; 1,056 additional guaranteed zero-coordinate incidences, reference site 200→210. Same specific bit-11 property refuted separately at complete rounds 2–8 | Analytic carry-free Pressure-bit equations; 1,024 original-C Butterfly basis responses; 512 suffix pair replays; GF(2) full-prefix inversion (rank 2048); seven full-C counterexamples |
| 2026-11-03 | `WORK-INT-MIXED44-ALL159-004` | For all 159 input-byte coordinate cubes × 32 selected two-byte 4+4-bit output windows, complete R2 excludes every nonconstant universal Boolean predicate of the mixed 8-bit observation; 361 specified R1 universal linear-mask spaces disappear | 5,088/5,088 rank-255 finite certificates; 41,696 valid bases; 10,674,176 producer scalar-C and 10,674,176 independent C replay permutations; Python/ctypes spot checks; zero mismatches |
| 2026-11-03 | `WORK-INT-BYTE-ALL159-003` | All 159 byte-cube families × 256 aligned output bytes: every nonconstant 8-bit Boolean predicate has base-dependent cube parity at complete R2; 232 inherited linear byte-local R1 balances are lost | 40,704/40,704 affine-difference rank-255 certificates; 42,149 valid-base witnesses; 10,790,144 scalar-C two-round replay calls; 2,163,200 prior-nibble histogram crosschecks; independent low-pivot verifier and Python spot checks |
| 2026-11-03 | `WORK-INT-NIBBLE-ALL159-002` | All 159 byte-cube families × 512 aligned output nibbles: every nonconstant Boolean nibble predicate lacks base-independent parity after complete R2; 232 earlier nonzero linear-nibble R1 balances disappear | 81,408/81,408 rank-15 affine-difference certificates; 4,225 scalar-C cube replays (1,081,600 two-round calls); independent low-pivot rank audit |
| 2026-11-03 | `WORK-INT-ALL159-001` | New exact **all-159 one-byte cube** universal linear-mask R1/R2 classification; exact per-position R1 dimensions 2–26, R2 zero; digest-only R1 masks at 33 positions | Analytic local derivative proof; 648,955 original-C cube replays; low-pivot rank audit; digest-only rank audit |
| 2026-11-03 | `WORK-DIFF-ACT-2026-11-03` | Eight-round active-call bounds strengthened to P≥15, H≥18; stated selected conditional class ≥19 | Inherited `DIFF-PERM-003` + rate theorems; independent activity arithmetic checker |
| 2026-11-03 | `[2,1]` campaign | 010 and 012: parent six-bit SAT 125 each, all resolved seven-bit UNSAT; 011 zero six-bit SAT/UNKNOWN; positions 008–009 reported closed but files not checked in this update | Verified uploaded checkpoint structure and child-parent record digest matches; no fresh solver rerun and no global `[2,1]` theorem |
| 2026-11-03 | `[2,1]` campaign audit 028–031 | Four complete positions with 230,912 recorded exclusions, no six-bit SAT or UNKNOWN. Conditional cumulative 000–031: **1,961,984 / 8,355,840 (23.48%)**. | Original compressed-record auditor and SHA-256 digests, original scalar source/header hashes, archived optimized-scanner fingerprint; no SMT re-solving or global activity-model soundness proof. |
| 2026-11-03 | `[2,1]` campaign audit 023–027 | Five positions fully closed (294,400 site records, six-bit SAT=0, UNKNOWN=0). Replaces earlier partial 023 without double-counting: first 22,000 records match. Conditional cumulative 000–027: **1,731,072 / 8,355,840 (20.72%)**. | Original checkpoint auditor, compressed-record SHA checks, original scalar C/header and optimized-scanner fingerprints; no independent SMT re-solving or model-completeness certificate. |
| 2026-11-03 | `[2,1]` campaign audit 013–023 | Ten more positions 013–022 completely excluded (608,000 sites); 023 is partial (22,000 of 59,392), all examined cases excluded. 000–022 cumulative 1,436,672/8,355,840 (17.19%) conditional on earlier user-reported 008/009. | Original audit script independently decoded all 11 records and matched counts/SHA-256; archived optimized scanner and pinned scalar source hashes matched. No solver UNSAT recomputation. |

| 2026-11-04 | `WORK-DIFF-FULL-ONECHI-THREECELL-LSB-016` | Original full P, unrestricted pair of adjacent rounds with exactly one active Chi call: exact 16-bit Pressure LSB gate excludes **10,138,251,288/22,285,025,280** named one-byte-to-three-Chi-cell candidate support configurations (**45.4936%**); the remaining **12,146,773,992** are unresolved relaxed survivors. The global `1⇒≥4` remains open. | Full source C/H SHA checks, 2,048 GF(2) prefix/inverse basis tests, 8,192 direct original-C Pressure/InkCloud/next-prefix replays, 87,392,256 triple/source rank analyses, full opposite-pivot audit with byte-identical JSON. Supporting `KRAKKEN_FULL_ONECHI_THREECELL_LOWBIT_CERTIFICATES.zip`. |
| 2026-11-04 | `WORK-DIFF-FULL-INTERROUND-SPARSE-015` | Full original P: `A_r=1 ⇒ B_r=16, W_(r+1)≥16` (≥8 even + ≥8 odd); `A_r=2 ⇒ B_r≥8, W_(r+1)≥8`, with 30,720/32,640 byte-support pairs forcing all 16 Pressure groups. Exact algebraic byte-position classification; 2-call 8-group counterexample. | 2,048 original-C vs Python Butterfly basis comparisons; exact 522,240 pair projection rank matrices with two independent elimination orders; original-C two-state unrestricted 1-call and 2-call replays. No new `A_(r+1)` bound or numerical probability claim. |

**Update convention:** Append verified new discoveries to this file, add or amend board rows and audit status, and retain old claims with explicit corrections rather than deleting or silently overstating them. When ready for public review, assign a new permanent theorem ID in the authoritative append-only inventory and cite this source-pinned evidence. No global eight-round security-bit claim is made here.

---

## WORK-INT-VALID159-CUBE12-017 — One-round 12-bit valid-message integral, 25 guaranteed masks; explicit R2 counterexamples

**Status:** NEW source-pinned analytic theorem with original-C finite verification; distinct from earlier all-159 *one-byte* cube studies. Original permanent security theorem registry unchanged.

Let `F_r(m)` be the original full Krakken's 2048-bit state after `r` complete rounds for a padded **exactly 159-byte** message. Consider the 4,096-point cube that varies **all eight bits of byte 0 and the low four bits of byte 1**, holding every other message bit fixed but arbitrary. Then exact analysis of `Pi ∘ Rho ∘ Tentacle ∘ Theta` over those 12 cube basis bits identifies exactly **two** rank-12 Chi cells out of 128; all other Chi cells have input projection rank at most 11. The first serial-Chi S-box call in any cell depends on at most 8 cube coordinates, so its complete cube XOR is always zero. The second call also has zero complete-cube XOR in every cell of rank at most 11. Therefore only the two rank-12 cells' second-call outputs could influence the cube sum after Chi.

Pressure supplies 32 exact affine-in-input-bits observations (four per arithmetic branch). Propagating these observations backward through Butterfly and restricting them to the 16 possibly nonzero second-call bits from the two rank-12 cells gives binary rank **7**. Consequently, there exists an **explicit 25-dimensional subspace of universally balanced one-round full-state linear masks** on these 32 observations. Three single-coordinate universal balances are **state output bits `11,907,1374`**; in particular bit **11** lies within the first 256 reduced-round digest coordinates:

`for every valid 159-byte base b, XOR_{x in GF(2)^12} F_1(b,x)[bit 11] == 0`.

This is a **universal theorem for this 12-bit input cube after ONE round**, not a full eight-round distinguisher. It is not just the previously known single-byte integral: the byte-0-only cube had 61 zero and 67 one parities for output bit 11 across 128 separate valid bases, whereas the 12-bit cube produced 128/128 zero parities in a holdout, in agreement with the algebraic proof.

**Round-two stopping evidence for exactly these masks:** a 16-base, 4,096-point original-C full-state replay at both R1 and R2 validates all 25 R1 universal masks; for each of those **specific** 25 masks, at least one saved complete R2 cube XOR sum has odd mask parity (2–12 odd examples per mask). This finitely refutes any claim that those same 25 masks remain universal at R2. It does **not** exclude every other conceivable two-round integral relation.

**Additional selected valid-message empirical screens:** six fixed input differences × four depths × 288 predefined digest-parity masks × 16,384 sampled pairs found no Bonferroni-corrected bias at familywise alpha 0.01 (maximum absolute normal z=3.84375). Six selected 12-bit message-cube geometries across exact lengths 159, 161, 319 and 320, four depths, and 20 randomized bases found no digest-coordinate single-bit parity constant across all bases at R2, R4 or R8. These are finite screens, not universal exclusions, and were not conditioned on `A1=5`.

**Reproduce:** `KRAKKEN_VALID_MESSAGE_DLIN_INTEGRAL_CERTIFICATES.zip` contains `THEOREM.md`, pinned original `krakken.c`/`krakken.h`, `prove_r1_cube12.py`, `cube12_proof.json`, `cube12_masks.h`, `verify_cube12_original.c`, `cube12_original_c_replay.json`, `audit_saved_results.py`, `audit_summary.json`, `krakken_valid_probe.c`, `krakken_fast.c`, `results.json`, `holdout.json`, `README.md` and `Makefile`. Exact source C SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` and header `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. The 25 proof vectors have independent high- and low-pivot rank 25 and the two-cell projected response rank is independently checked at seven. All 25 R1 masks were checked against **16 original-C complete-cube replays** (65,536 messages per round), followed by explicit R2 counterexample audits.

**Security scope:** A reduced one-round universal integral *does not constitute a successful eight-round hash attack*. No collision, preimage, eight-round differential bias, global activity minimum, security bits, or all-integral exclusion is inferred.


---

## WORK-DIFF-FULL-A15-FIXED3-A2-018 — Exact three-line `A₁=5 ⇒ A₂≥4` full-P exclusion

**Status:** New finite, source-pinned, bounded-family theorem (2026-11-05). The original permanent ledger is unchanged. Complete proof and executable certificate: `KRAKKEN_PRESSURE_VALID159_A15_A2_GATE_CERTIFICATES.zip` (`krakken_pressure_message_gate/README.md`).

**Claim (precise domain):** Let `Δ₀, Δ₁, Δ₂` be **exactly the three explicit 159-byte message XOR differences** in the attached `delta_id_map.json` and earlier billion-witness checkpoint. For any two valid 159-byte messages with any one of these fixed differences whose original first complete round has **exactly five active serial-Chi byte S-box calls**, the **next full round** has at least **four** active calls. Thus **`A₁=5 ⇒ A₂≥4` and `A₁+A₂≥9` for these three fixed Δ values only**. The three lines share a 24-nonzero-byte pattern shifted one byte; they do not cover every valid difference with `A₁=5`. No claim about `A₂≥244`, global minimum, or differential probability is made.

**Reason it is a valid exclusion:** The five active pre-Chi1 cells each have nonzero first-call input difference, so `A₁=5` forces each second call's input difference to zero. This fixes post-Chi1 output difference independently of base, checked among nine actual original-C message pairs. In each of Pressure's 16 independent word pairs, the two modular additions give **32 exact bit-zero identities**. Their original-C-verified map through inverse InkCloud and inverse next-round linear prefix excludes most proposed second-Chi differences supported on any three 16-bit Chi input cells. Where both relevant input-difference bit-zeros vanish, selected **additional exact bit-one identities** provide 42/42/41 equations for Δ₀/Δ₁/Δ₂. The remaining affine endpoint assignments are exhausted, with exact ABYSSAL DDT support used to retain every locally possible `A₂≤3` pattern. Finally, exact full-width, base-independent factored modular-addition derivative equations for both coupled Pressure additions reject every such pattern. These are all necessary conditions, so a false positive relaxation cannot invalidate an exclusion.

| Stage | Δ₀ | Δ₁ | Δ₂ | Total |
|---|---:|---:|---:|---:|
| Possible three-cell supports | 341,376 | 341,376 | 341,376 | 1,024,128 |
| Survive previous 16-bit gate | 64,556 | 53,706 | 52,304 | 170,566 |
| Survive new 32-bit zero gate | 757 | 1,272 | 883 | 2,912 |
| Survive 42/42/41-bit gate | 46 | 27 | 25 | **98** |
| Exhaustive affine endpoint assignments across 98 supports | 130,176 | 292,224 | 645,888 | **1,068,288** |
| Assignments with local `A₂≤3` DDT support | 17,891 | 43,846 | 62,765 | **124,502** |
| Pass exact full-word Pressure necessity | **0** | **0** | **0** | **0** |

**Learned-cut reuse:** The 79 previously independently certified full-word Pressure derivative-affine contradiction guards match 102,054 of the 124,502 relaxed endpoint assignments (81.97%). Full-word factored equations reject all 124,502 independently. This measures reusable exclusion on **valid-message-difference-anchored but hypothetical second-round endpoint profiles**, not an attack probability or realizable-trail distribution.

**Checks:** Source SHA-256 C `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, header `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. Original C: 9 conditioned valid-message pairs; 768+1,024 full-width Pressure-pair differential replays. Independent opposite-pivot re-enumeration of all **3×341,376** three-cell supports agrees on exact rank spectra and survivor counts. The 98 survivor supports' complete affine spaces are enumerated, and 4,096 independent checks reproduce the full-word factored necessity from exact derivative-affine equations (including 2,048 actual modular additions). `make check` requires only Python and a C compiler.

**Limit:** Three special differences only, exactly 159-byte first-block message domain. For every other difference and any other message length or later absorption block, no stronger bound is claimed. All 98 support classes are excluded only after their exact candidate values and full-word necessary equations are checked; neither the 32-bit nor the 41/42-bit gate alone proves `A₂≥4`. The numerical hash security margin remains an open question.

---

## WORK-PRESS-FULLWORD-AFFINE-RULEBOOK-019 — Exact universal compact gate for Pressure's derivative-affine relaxation

**Status:** Source-equation-derived, finite library completeness theorem independently audited on 2026-11-05; builds on reviewer-provided `STRUCTURAL_FINDINGS.md`. **Original permanent ledger unchanged.** Original Krakken C/H SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` / `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

**Precise universal scope:** For one original Pressure shear `(a,c)→(A,C)` with `A=a+(c⊕(c≫17)) mod 2⁶⁴`, `C=c+(A⊕(A≪31)) mod 2⁶⁴`, and any prescribed four-word XOR difference `(da,dc,dA,dC)`, set `f=dc⊕(dc≫17)`, `g=dA⊕(dA≪31)` and `R(x,y,z)=((x⊕y⊕z)≫1)⊕xy⊕xz⊕yz⊕x⊕y` for bits 0..62. Check `dA₀=da₀⊕f₀` and `dC₀=dc₀⊕g₀`. Eliminate the private `a_i` and `C_i` derivative variables for `i=1..62`; all surviving nontrivial rows are the guarded forms `U_i: c_i⊕c_(i+17)⊕A_i=R(da,f,dA)_i` and `V_i:c_i⊕A_i⊕A_(i-31)=R(dc,g,dC)_i` with out-of-range coordinates omitted, along with two bit-zero rows. Rows whose left-hand side is zero but RHS is one reject immediately. The guarding patterns are stated and checked in the source note and independent code.

Only three difference LSBs `(da₀,dc₀,dc₁₇)` select one of eight immutable 126-row GF(2) libraries on `(c,A)`; their matrix ranks are `[111,112,112,111,112,111,111,112]`, dependency dimensions `[15,14,14,15,14,15,15,14]`, and numbers of inclusion-minimal dependent subsets (**matroid circuits**) `[15,14,14,16,14,15,15,14]`. Thirteen share the exact five-row identity `U_i ⊕ U_(i+48) ⊕ V_i ⊕ V_(i+17) ⊕ V_(i+48)=0` for `i=1..13`. For *any subset* of enabled rows, inconsistency holds exactly when an enabled circuit has odd RHS XOR. This is complete for the derivative-**affine necessary-condition system**, not for the actual nonlinear addition graphs.

**Independent checks:** The new standalone program enumerates every nonzero full-library dependency in each of eight matrices, extracts all minimal circuits, validates 13 loops for all eight configurations, checks 10,000 independently sampled actual modular-addition derivative equations, and compares the compact gate to a separately built, unrestricted 256-variable GF(2) elimination on **12,000 profiles**, including 4,000 genuine Pressure transitions, with **zero disagreements**. The exact original `WORK-DIFF-FULL-A15-FIXED3-A2-018` residual 98-support scan was independently rerun: **1,068,288** endpoint assignments, **124,502** locally `A₂≤3`-compatible assignments, **zero** passing this compact gate on the **first** Pressure word pair. But **86,842** fail first at a trivial first-addition zero row and **37,660** at a trivial second-addition zero row: **zero** require one of the 14–16 parity circuits. This is a confirmation/algorithmic simplification of `-018`, not a stronger activity bound. All three delta restrictions of `-018` remain.

**Standalone probability lemma:** For uniformly random independent input words `(a,c)`, `(c,A)` is exactly uniform because `a↦A` is a bijection at fixed `c`. If the projected necessary system has consistent rank `k` on these 128 coordinates, the set of possible base pairs has size at most `2^(128−k)` and hence `Pr[specified full Pressure XOR differential]≤2^(−k)`; contradiction gives probability zero. This bound is **only for standalone uniform Pressure inputs**. It cannot be applied to `A₁=5`-conditioned valid hash-message bases, or multiplied across rounds, without an independently proved distributional argument.

**Reproduce:** `KRAKKEN_PRESSURE_AFFINE_RULEBOOK_AUDIT.zip` bundles the reviewer note, independent Python rulebook / generic 256-variable comparison, the earlier original-C-anchored three-delta endpoint files, the rerun script, counters and instructions. `make -C krakken_pressure_message_gate libkrakken.so; python3 structural_affine_check.py; python3 verify_018_compact_gate.py`. The reviewer reports **~42× faster** on a selected Python microbenchmark; the independent audit verifies correctness, **not** that timing or a full campaign-wide speedup.


---

## WORK-DIST-REDUCED-R1-020 — Quantified one-round permutation distinguisher and full-round birthday-reference study

**Date:** 2026-11-05. **Mathematical status:** Exact distinguishing-advantage *corollary* of the pre-existing `WORK-INT-VALID159-CUBE12-017` proof; the universal mask space is not new. **Empirical status:** Reproducible valid-message collision and avalanche comparisons for original eight-round Krakken and reduced 1/2/4-round diagnostic variants. **Original permanent ledger unchanged.** Full report and complete reproducibility materials: `KRAKKEN_RANDOMNESS_COLLISION_SECURITY_STUDY.zip`, section `THEOREMS_AND_RESULTS.md`.

**Theorem (reduced one round only):** For any fixed valid 159-byte message base, vary the eight bits of byte 0 and the low four bits of byte 1 over all 4096 settings. `-017` proved 25 independent 2048-bit XOR-balanced linear masks on the output of one complete Krakken round. A 4096-query distinguisher checking these mask parities therefore accepts the reduced one-round permutation with probability one. For a uniformly random 2048-bit permutation queried on the 4096 distinct inputs, the probability all 25 parities vanish is at most `2^-25 + 4096*4095/2^2049`: couple samples without replacement to 4096 independent output words and bound the probability of a collision in the latter. The consequent distinguishing advantage is at least `1−2^-25−4096*4095/2^2049`, exceeding 0.9999999701. Within this exact 25-mask span, the digest-only balanced mask subspace has dimension one, supported on output bit 11; hence a one-round reduced 256-bit digest version has a 4096-query distinguishing advantage **1/2** versus an ideal random 256-bit function. `distinguisher_corollary.py` independently reconstructs 25-mask independence, the one digest-visible mask, and the exact formula from the source-pinned `cube12_proof.json`.

**Empirical full eight-round controls:** Ten settings per seed (SHA-256 control, and Krakken 1/2/4/8 rounds, lengths 159/161), two independent seeds, each with 131072 guaranteed-distinct messages: 2,621,440 collision-measurement hashes. For the complete eight-round Krakken, the 24-bit prefix collision-pair counts are `478,496` (159-byte datasets) and `482,529` (161-byte datasets), versus exact ideal `E=511.996` per corpus; 32-bit prefix pair counts `[1,4,1,4]` versus ideal E≈2. Four explicit original-C-verified **full-R8 32-bit prefix** collision witness pairs are saved and have distinct full 256-bit digests: they are not full-hash collisions. Chosen-difference avalanche includes 24 settings ×8192 message pairs, means near 128 changed digest bits; no tested output-bit bias passes multiplicity correction over 6144 comparisons. Largest raw 24-bit collision outlier across 20 settings is R4 159-byte, 574 pairs (normal p≈0.00614, Bonferroni adjusted ≈0.123), followed by independent-seed 500. No reduced/full eight-round security-bit bound follows from these experiments.

**Conditional ideal-sponge reference:** If the full 2048-bit internal permutation were sampled uniformly at random, a capacity-768 sponge falls under the Bertoni et al. ideal-permutation indifferentiability bound `N(N+1)/2^769` (N according to the theorem's query-cost model; *Cryptographic Sponge Functions*, 2011, Theorem 9). Ideal digest generic collision/preimage reference costs are about `2^128`/`2^256`. These **do not apply as actual lower bounds** to the known deterministic eight-round Krakken permutation without a separate proven connection to the ideal-permutation model.

**Reproduce:** `KRAKKEN_RANDOMNESS_COLLISION_SECURITY_STUDY.zip` contains `THEOREMS_AND_RESULTS.md`, `random_collision.c`, original C/H, test-only fast S-box C, `analyze_results.py`, two complete JSONL datasets, `results_summary.json`, four explicit original-C-replayed witnesses, and the source-pinned inherited one-round exact theorem/replay files plus `distinguisher_corollary.py`. The underlying original source hashes remain C `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, H `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. Original permanent ledger not modified.


---

## WORK-SPONGE-INJECTIVITY-021 — Exact complete-state nonmerging and conditional ideal-sponge budget

**Date:** 2026-11-05; source:** original `krakken.c` SHA256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, original `krakken.h` SHA256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. Mathematical status: complete actual eight-round permutation invertibility, *not* truncation-security theorem.

**Actual-source theorem:** The entire eight-round `K` is bijective, because Theta is an involution, the 8×8 GF(256) MDS matrix is invertible, Rho/Pi/InkCloud are permutations/rotations, each serial-Chi Sbox stage is invertible, each Butterfly stage is invertible, both Pressure shears invert by modular subtraction, and Iota is a constant XOR. For a message padded to rate blocks `M_j`, absorption `S_{j+1}=K(S_j⊕(M_j||0^768))` is injective in `S_j` at each fixed block. Two equal-length padded block sequences with one differing rate block and an otherwise identical prefix and suffix have **different complete final 2048-bit states**. The original padding gives an injective mapping of 0..159-byte valid message strings to one padded 160-byte block, so **all distinct such one-block messages have distinct complete post-absorb states**. To merge the full state with equal padded block count, at least two padded rate blocks must differ. This **does not rule out equality of the first 256 output bits** and does not claim actual digest collision resistance.

**Validation:** Independently constructed all nine layer inverses in Python, verified an inverse 8×8 MDS matrix over GF(256)/`0x11D`, checked all 256 Sbox outputs distinct, and recovered **24 random original-C eight-round states**. Reproduction: `audit_affine_theorem.py` in `KRAKKEN_SECURITY_GUARANTEES_AND_CONDITIONED_A15.zip`.

**Ideal-model reference only:** In the ideal 2048-bit permutation model, the exact pair probability of a `t`-bit projection match for **two distinct one-block inputs** equals `(2^(2048-t)−1)/(2^2048−1)`. For the full digest t=256 this is approximately 2^-256 per pair; for the hidden capacity t=768 approximately 2^-768. The standard sponge indifferentiability query-budget reference for c=768 is `N(N+1)/2^769` (BDPV, *Cryptographic Sponge Functions*, Theorem 9; `https://keccak.team/files/CSF-0.1.pdf`). Its approximate values at `N=2^128` and `N=2^256` are respectively `2^-513` and `2^-257`. **Those results assume an ideal random permutation, not the known fixed Krakken rounds.** The design-level generic hash reference remains approximately 2^128 collisions and 2^256 single-target preimages for a 256-bit output; this is **not a concrete fixed-K lower bound**.

## WORK-LIN-CONDITIONED-A15-022 — First-round four-digest-bit near-uniformity, even conditioned on A₁=5

**Date:** 2026-11-05. **Source:** original C/H hashes above, plus permanent `LIN-RATE-005` (already independently certified in the permanent research ledger); **new theorem is a corollary**, not a full re-proof of the original hard Fourier/rank bound.

Let `Δ` be exactly one of three 159-byte input XOR differences in the source-pinned `krakken_a15_seed_pairs.txt`. With uniform valid159 base `m`, condition on the event `A₁(m,m⊕Δ)=5`. Under the actual original one-round Krakken permutation, define `Y(m)=(bit11,bit12,bit13,bit14)` of its first 256 output bits. For nonzero `s∈F₂^4`, inherited `LIN-RATE-005` certifies, uniformly over **every 1272-bit input mask α**, `|E_m(-1)^(α·m⊕s·Y)|≤L_s·2^-432`, with integer coefficients `L_s=[1,2,2,3,3,3,3,4,4,5,5,4,4,5,5]`, whose sum is 53.

The **actual fixed-Δ conditional event** is the disjoint union of 32 affine fibers `Lm=b`, one per selection of two allowed ABYSSAL roots at each of five first Chi gates; each fiber has codimension 40. Original-C linear prefix basis reconstructs and independently confirms **rank40/40** for all three differences. On each fiber, the orthogonality identity for the conditioning indicator writes any output Walsh expectation as a sum of `2^40` of the correlations covered by `LIN-RATE-005`, giving `|E[(-1)^(s·Y) | Lm=b]| ≤L_s·2^-392`. The uniform mixture of the 32 fibers satisfies the same inequality. Invert the four-bit Fourier transform to obtain

`TV(Law(Y | A₁=5, Δ), Uniform(F₂^4)) ≤ (1/2)∑_{s≠0} L_s·2^-392 = (53/2)·2^-392 = 2^-387.2720795454 < 2^-387`.

**Scope:** exactly three fixed differences and four specified **reduced-one-round** digest bits, uniform message bases under the stated conditional event. This theorem does not extend numerically to the actual eight-round digest, other bits, or all differences. It does not contradict preexisting reduced-one-round cube-integral distinguishers. **All 15 local Pressure Walsh coefficients independently re-enumerated; all three source-C rank40 instances independently reverified.** Supporting `affine_bound_audit.json` and `audit_affine_theorem.py`.

## WORK-EMP-CONDITIONED-A15-R8-023 — Original eight-round hash chosen-difference diagnostics (empirical)

**Date:** 2026-11-05. **Scientific status:** source-pinned **finite experiment**, **not a mathematical lower bound or security proof**.

For each of the **three fixed differences above**, generate **262144 genuine conditioned `A₁=5` valid159 message pairs per seed** under two different deterministic PRNG seeds, for a total of **1,572,864 chosen pairs per depth** (depths R1, R2, R4, R8). Inspect the XOR of first 256 output bits, its Hamming weight, all individual output-bit difference biases, and prefix-zero events of t=8/12/16/20 bits. Six R8 groupwise mean Hamming weights lie in **[127.9739685,128.0219650]**, versus ideal mean 128. The aggregate R8 zero-prefix counts `[6035,384,24,1]` compare with ideal-function expected `[6144,384,24,1.5]`. The R1 8-bit zero-prefix count is 491316, dramatically different from ideal; at R2/4/8 measured prefix match rates are near ideal references. None of 4608 output-bit tests at rounds 2/4/8 survives familywise Bonferroni adjustment (smallest adjusted two-sided binomial p≈0.358); six R8 groups likewise show no adjusted significant output-bit bias.

**Critical scope:** This covers three *specifically engineered* low-A₁ differences only; uniform-base sampling depends on a pseudorandom generator, not true independent random coins. This does not bound the global eight-round differential probability, prevent a collision attack on the 256-bit digest, or establish collision/preimage security bits. It is more targeted than earlier random-message collision-frequency checks, because it tests an explicitly known sparse first-round structure. No negative result should be advertised as proof of pseudorandomness.

**Reproduction/source fidelity:** `KRAKKEN_SECURITY_GUARANTEES_AND_CONDITIONED_A15.zip` contains `conditioned_digest_probe.c` and the unchanged C/H plus a speed-only table-Sbox backend that is crosschecked against original C; `analyze_conditioned.py`, all 24 raw result groups from two seeds, and `conditioned_results_summary.json`. Startup crosschecks: **256 random full/reduced permutation states, 86 random full hashes, 768 conditioned A₁=5 original-C permutation comparisons, 192 conditioned original-C full hashes, and 768 A₁=5 generator self-tests**. Supporting independent original-C prefix-rank audit validates all five gates at every fixed difference.


---

## WORK-SPONGE-ONEBLOCK-IDEAL-024 — Published restricted-block ideal-sponge bound for Krakken H159

**Proof status:** Mathematically established in the **ideal-random-permutation** model by Charlotte Lefevre, *Indifferentiability of the Sponge Construction with a Restricted Number of Message Blocks*, ToSC 2023 (DOI `10.46586/tosc.v2023.i1.224-243`), Theorem 1, plus exact Krakken wrapper/padding parameter identification. **Not a fixed-permutation Krakken security lower bound.** For messages of **0–159 bytes**, the unchanged Krakken wrapper absorbs exactly one 160-byte padded rate block (`ell=1`); `b=2048`, `ra=rs=1280`, `ca=cs=768`. Projection of full squeeze output onto its first 256 bits cannot increase indifferentiability advantage. For `q=q_P+q_C>=1`, the published bound simplifies to

`Adv_R-iff <= (q_P*(12 ln(q)+15372)+20q)/2^768 + 3q²/2^2048`.

Conservative `q_P<=q` substitution gives approximately **`2^-625.994` at `q=2^128`** and **`2^-497.903` at `q=2^256`**. The restriction excludes messages of **160 bytes or longer**, and the proof assumes a publicly queryable **ideal** permutation; it does not imply any numerical security exponent for actual Krakken. Arbitrary-message sponge parameters remain as previously described. Independent source-pinned parameter script: `restricted_sponge_bound.py`, result `oneblock_indifferentiability.json` in `KRAKKEN_A15_ONEBLOCK_IDEAL_AND_STRUCTURED_BIRTHDAY.zip`.

## WORK-DIST-A15-R1-TWOQUERY-025 — Exact one-round conditional 32-bit differential; two-query distinguisher

**Proof status:** Actual original-source algebraic theorem for **only three specific `A1=5` valid159 difference families**, **only one full round**. Each fixed first linear-prefix difference has exactly five mandatory first S-box calls and zero mandatory second-only calls. Therefore any base attaining `A1=5` forces all second calls inactive, and for each active serial-Chi cell `delta(u)=delta(y)`, `delta(v)=0`; the complete post-Chi1 difference is fixed. Butterfly is GF2-linear. In every 4-word Pressure branch, the two carry-free bit0 additions and dependent shears fix `delta(A0),delta(B0),delta(C0),delta(D0)` independent of base. Iota and InkCloud carry them to 32 fixed XOR bits of the one-round **2048-bit output** (see detailed certificate `SECURITY_RESULTS.md`). Four lie in the digest at absolute bit offsets `[11,94,139,210]`. Their prescribed XOR difference vectors by delta ID are **`[0,0,1,1]`, `[0,0,0,1]`, `[0,1,0,0]`** (all nonzero). Thus a **2-query** one-round **256-bit digest** test has distinguishing advantage **`15/16`** versus an ideal random function. With 32 observed state bits it has advantage `1−2^2016/(2^2048−1)` versus a uniformly random permutation. These particular deltas also **cannot produce one-round digest collisions when A1=5**. **None of this is an attack on actual eight-round Krakken.** Independent original C replay accepted all 32-bit constraints for **12,288/12,288** fresh conditioned pairs; same four digest-bit test at R2/R4/R8 observed **`803/786/773`** matches versus ideal `768`, with original C. Proof and exact masks: `audit_round1_fixed_differential.py`, `round1_fixed_differential.json`, `verify_fixed_differential.c`, `fixedxor_originalC_4096.jsonl` in the reproduction bundle.

## WORK-EMP-A15-STRUCTURED-BIRTHDAY-026 — Full-eight-round structure-aware birthday collision experiment

**Status: finite original-C-validated empirical cryptanalysis, not a theorem of collision resistance.** Six datasets of 262144 valid159 messages each, constructed as **131072 exact first-round-A1=5 pairs**, 3 pinned XOR differences × 2 deterministic seeds, then **all** unordered colliding digest prefix pairs counted. For R8 full Krakken, first-24-bit collision counts `[2030,2064,2132,2010,2041,2021]` sum **12298**, versus ideal expectation **12287.95**. First-32-bit counts `[8,9,9,7,4,3]` sum **40**, versus ideal **48**. SHA-256 controls on the **same messages** gave 12347/43; two-round reduced Krakken 12318/48; one-round reduced 12219/52. Six 32bit-prefix full-R8 collisions were saved and checked via the unmodified original C; all have **distinct full 256bit digests**. No measured R8 prefix-collision count was significant after familywise 18-test Bonferroni adjustment (approximate minimum adjusted p≈0.833). R8 deliberate within-pair first-8/12-bit matches totaled `3039/207` vs ideal `3072/192`; SHA256 `3052/210`. R1 within-pair first8-bit matches total **245684**, confirming that *ordinary all-pair birthday histograms can coexist with a spectacular reduced-round chosen-difference distinguisher*. This experiment is a **non-adaptive structure-informed** search; it neither bounds adaptive attacker success nor certifies 128-bit collision resistance. Reproducible C benchmark, SHA controls, original source hashes, raw data, independent witnesses, numerical interpretation: `KRAKKEN_A15_ONEBLOCK_IDEAL_AND_STRUCTURED_BIRTHDAY.zip`.


---

## WORK-DIFF-A15-PROJECTION12-SURJECTIVE-027 — Full-source-verified 12-bit projection coverage at R2–R8

# WORK-DIFF-A15-PROJECTION12-SURJECTIVE-027 — Finite 12-bit difference projection coverage

**2026-11-05 · source-pinned finite existential certificate for actual original Krakken C.**

Let `Delta_d` be one of the three exact 159-byte message XOR differences in `KRAKKEN_A15_BILLION_PACKAGE/krakken_a15_seed_pairs.txt`, indexed `d=0,1,2`. Consider valid messages `(m,m XOR Delta_d)` for which exactly five byte S-box calls are active in first-round Chi (`A1=5`). Take a 256-bit digest under `r` complete Krakken rounds for `r in {2,3,4,5,6,7,8}`. Define `pi12` to be the 12-bit projection at digest bit indices

`[0, 11, 23, 52, 77, 94, 111, 139, 154, 184, 210, 242]`.

**Exact finite theorem (existential coverage, not distributional uniformity):** For every one of the three fixed message differences `Delta_d`, every round depth `r` in `{2,3,4,5,6,7,8}`, and every `z in {0,1}^12`, there exists a valid 159-byte pair satisfying `A1=5` with

`pi12(H_r(m) XOR H_r(m XOR Delta_d)) = z`.

**Proof:** Each of the 21 `(r,d)` conditions has an explicit exhaustive 4,096-entry witness table, one entry for each possible projected difference pattern. Each entry identifies a deterministic RNG seed and pair index in the conditional affine generator. `verify_cover12.c`, compiled separately with `-DOUTPUT_ROUNDS=r`, regenerates all cited pairs, independently checks `A1=5` with the unmodified original C layer implementations, and evaluates the full permutation using `krakken_permute_scalar_rounds` loaded from a separately compiled original-source shared library. All 21×4,096 = **86,016 independently checked witness rows** passed. This is a finite, reproducible proof of **existence** of all 4,096 projected patterns for each indexed difference/depth; sampling was merely the method used to find witnesses, and plays no role in the verification of the theorem. The 12 output bits are all in the first 256 digest bits; not hidden capacity bits.

**Meaning:** Neither a missing 12-bit difference value, nor any nontrivial exact equality restricting these 12 selected digest-difference bits, can hold across the entire fixed-difference conditioned input family for any of the seven depths. In particular there is no nonzero linear mask of these 12 bits which has a *fixed parity across all pairs* in the given family. This rules out a precisely defined class of deterministic differential-projection distinguishers. It does **not** prove that the 4,096 patterns are equally likely, that their probabilities are bounded close to `2^-12`, that arbitrary 12-bit projections work, that a stronger nonlinear predicate involving different coordinates is impossible, or that eight-round Krakken has 128-bit collision resistance.

The one-round chosen-difference structure is noticeably different: the earlier exact theorem `WORK-DIST-A15-R1-TWOQUERY-025` forces four of these 12 digest positions, including 11/94/139/210, to take specific difference values, so surjectivity is impossible at R1.

## Regeneration and checks

`krakken.c` SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`.

`krakken.h` SHA-256 `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

From the included source directory, after `make all`:

```sh
for r in 2 3 4 5 6 7 8; do
  if [ "$r" = 8 ]; then suffix=""; else suffix="_r$r"; fi
  cc -O3 -std=c11 -Wno-unused-function -Wno-misleading-indentation -DOUTPUT_ROUNDS=$r \
    -I KRAKKEN_A15_BILLION_PACKAGE -o verify_cover12_r${r} \
    verify_cover12.c krakken_fast.c -lpthread -ldl -lm
  ./verify_cover12_r${r} cover12_certificate${suffix}.tsv
 done
```

The verifier requires `libkrakken_original.so` from original C (`make all`). For exact replay, use the saved certificate tables; **no trust in the fast test backend is necessary** for their verification. `cover12.c` is provided to regenerate witness tables with new seeds; those search outputs include 21 non-tab-separated informational header lines, which must be filtered to four-field TSV rows before passing them to the verifier.



---

## WORK-CHI-CALL-SUPPORT-028 — Exact serial-Chi active-call/output-byte support equivalence

**Status:** canonical working theorem `WORK-CHI-CALL-SUPPORT-028`, source-derived exact local theorem with independently written Python algebraic checks and original-C finite replay. **Not** a proof that the global adjacent-round `[2,1]` trail is impossible. 2026-11-05.

**Authoritative source fingerprints**

- `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
- `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`

## 1. Exact local lemma (all states, no statistical assumptions)

Each word pair in Krakken's original Chi layer obeys

\[
U=S(A\oplus R(B)),\qquad V=S(B\oplus R(U)),\qquad R=\operatorname{ROL}_{32},
\]

where `S` acts independently on all eight bytes and is a permutation of `GF(2)^8`. The supplied S-box has exactly 256 distinct outputs.

For an arbitrary two-state XOR differential, write `Delta X=Delta A XOR R(Delta B)` for the first S-box input difference and `Delta Y=Delta B XOR R(Delta U)` for the second S-box input difference. Let `wt8` count nonzero bytes of a word. Because the byte S-box is bijective, a nonzero S-box input difference occurs **if and only if** its output difference is nonzero. Consequently,

\[
A_{\rm Chi} = \operatorname{wt8}(\Delta X)+\operatorname{wt8}(\Delta Y)
            = \operatorname{wt8}(\Delta U)+\operatorname{wt8}(\Delta V).
\]

This holds for each two-word Chi pair, and therefore for the entire 32-word state after summing all 16 pairs. In particular, **exactly two active byte S-box calls** is equivalent to **exactly two distinct nonzero post-Chi state bytes**, even if the calls are in the same word pair. **Exactly one active byte S-box call** is equivalent to **exactly one nonzero post-Chi state byte**.

Thus all possible *output-support indices* of a `[2,1]` two-Chi-layer activity pattern are represented by choosing `i<j` among 256 post-Chi1 bytes, then `q` among 128 byte lanes of two-word pairs and `branch` among the two post-Chi2 word sides. The count is `C(256,2) * 128 * 2 = 8,355,840`. This establishes **support location/counting completeness only**.

## 2. Exact one-call endpoint parameterization

For a byte lane `t`, let `e_t(z)` denote the 64-bit word whose byte `t` equals `z` and whose other bytes are zero. Let `DDT_S(alpha,beta)>0` mean that some S-box input base `x` satisfies `S(x) XOR S(x XOR alpha)=beta`; necessarily `alpha!=0, beta!=0`. The following conditions are both necessary and locally realizable for exactly one active call:

**First-only branch** (`Delta U=e_t(beta)`, `Delta V=0`):

\[
\Delta B=R(e_t(\beta)),\qquad
\Delta A=e_t(\alpha\oplus\beta),\qquad
\mathrm{DDT}_S(\alpha,\beta)>0.
\]

The value `Delta A` **may be zero** if `alpha=beta`. `Delta B` is nonzero.

**Second-only branch** (`Delta U=0`, `Delta V=e_t(beta)`):

\[
\Delta B=e_t(\alpha),\qquad
\Delta A=R(e_t(\alpha)),\qquad
\mathrm{DDT}_S(\alpha,\beta)>0.
\]

Here both input words have one nonzero byte, at lanes separated by the 32-bit rotation. In either branch, the DDT constraint can be *relaxed* to arbitrary nonzero `alpha,beta` for a sound necessary-condition screen, provided no true assignment is excluded elsewhere.

**Derivation:** In the first-only branch, `Delta V=0` forces `Delta Y=0`, hence `Delta B=R(Delta U)`. Since `R^2=identity`, `Delta X=Delta A XOR Delta U=e_t(alpha)` and the formula for `Delta A` follows. The second-only branch has `Delta U=0`, hence `Delta X=0`, giving `Delta A=R(Delta B)`; the single second S-box input difference fixes `Delta B=e_t(alpha)`. These implications use only the original Chi equations and the S-box bijection.

## 3. Constructive source-C-verified corner case

The original S-box satisfies `S(0x65)=0xA4`, `S(0x67)=0xA6`. Hence the derivative at input difference `alpha=0x02` has output difference `beta=0x02`.

Choose the word pair with first input word `A=0x65` and second `B=0`, and a paired execution with `A'=0x65` and `B'=0x0000000200000000`. Put all other 30 state words equal to zero. The original compiled scalar `chi_scalar()` gives

\[
\Delta A=0,\quad\Delta B=\mathtt{0x0000000200000000};\qquad
\Delta U=\mathtt{0x02},\quad\Delta V=0.
\]

This proves there exist valid first-only one-call endpoints where **one pre-Chi word is entirely inactive**. Any scanner model that requires both input words to differ for every first-only branch misses valid endpoints and cannot be called support-complete.

Exhaustive S-box derivative enumeration also finds **141** nonzero input differences `alpha` for which the original S-box permits `beta=alpha` at some base, comprising **282** `(alpha,x)` occurrences. Such endpoints are not isolated to the demonstrated value `0x02`.

## 4. Independent reproducibility

Run beside the unchanged scalar source/header:

```bash
python3 KRAKKEN_CHI_SUPPORT_AUDIT.py --source krakken.c --header krakken.h --output KRAKKEN_CHI_SUPPORT_AUDIT.json
```

The audit performs **65,280 exact byte-S-box derivative evaluations** and checks **130,560** algebraically constructed first/second one-call endpoint cases. It also compiles the *unmodified original* `krakken.c` in a temporary directory, validates 104 sampled/corner-case endpoint pairs through `chi_scalar`, and checks active-call versus output-byte counts for 128 independently generated pairs of full 32-word states. Results on the uploaded source: all PASS, S-box maximum differential uniformity 4. Original-C checks are finite execution evidence; the local support lemma itself follows mathematically from the bijectivity and source equations.

## 5. What remains before a global `[2,1]` theorem

The structural lemma does **not** audit the scanner's exact endpoint constraints, inverse linear transport, lower-bit Pressure over-approximations, solver UNSAT correctness, or new checkpoint evidence beyond the provided ledgers. Before promoting a global result, verify that the existing q/branch endpoint constructor includes **both complete formulas above**, especially `Delta A=0` on first-only branches; independently audit all lower-bit necessary conditions against actual 64-bit Pressure; validate every completed six-bit parent and required seven-bit refinement, with no unresolved SAT/UNKNOWN; and seek independently checkable UNSAT evidence where feasible.

**Conditional multiround corollary, only if the universal `[2,1]` exclusion is eventually proved:** Combining the inherited `A_r=1 -> A_{r+1}>=3`, universal `A_r>=1`, and the additional `A_r=2 -> A_{r+1}>=2` for eight rounds gives `sum A_r>=16` for unrestricted P. For the valid-159-byte first-block domain with `A_1>=5`, the same abstract lower bound stays at `sum A_r>=18` (e.g. abstract sequence `[5,1,3,1,3,1,3,1]` satisfies the constraints). These are only **activity counts**, not differential probabilities or concrete hash-security exponents.


---

# Krakken-256: two exact eight-round algebraic exclusions (`-029`, `-030`)

**Date:** 2026-11-05. **Construction:** the actual eight-round `krakken_hash_scalar` for **exactly 159 message bytes**, as compiled on an x86-64 little-endian machine from the unmodified sources. No ideal-permutation assumption. These are *finite-witness mathematical certificates*, not claims of 128-bit collision security or 256-bit preimage security.

**Pinned scalar C:** `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` SHA-256.  
**Pinned H:** `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c` SHA-256.  
**Sponge:** initial zero 2048-bit state; absorb 159 message bytes followed by fixed byte `0x86`; eight complete permutation rounds; expose the first 256 bits of the state as a digest. The 159-byte domain has `1272` unrestricted message bits.

## WORK-HASH-R8-QUADRATIC-029 — No nonzero quadratic digest-only annihilator

**Claim (actual eight-round hash, H159).** For any Boolean polynomial

\[
P(y_0,\dots,y_{255})=c\oplus\bigoplus_i a_i y_i\oplus\bigoplus_{i<j}b_{ij}y_i y_j
\]

of total degree at most two, if `P(H_8(m))=0` for **every** 159-byte message `m`, then all its coefficients are zero. This includes *all 256 digest coordinates and all 32,640 unordered coordinate pairs*, not a selected subset. The claim extends to a polynomial equated to a universal constant by moving the constant to the left.

**Finite-witness proof.** The monomial evaluation feature vector

\[
\Phi(y)=(1,\ y_0,\ldots,y_{255},\ y_0y_1,\ldots,y_{254}y_{255})\in\mathbb F_2^{32897}
\]

has dimension `1+256+C(256,2)=32,897`. Set `SEED=0xC317975AC01D2026`; for each `i=0,...,32896`, construct a unique 159-byte message by putting the little-endian 64-bit index in bytes `0..7`, seeding SplitMix64 from `SEED XOR ((i+1)*0xD1342543DE82EF95 mod 2^64)`, and using successive little-endian SplitMix64 outputs to fill bytes `8..158`. (See exact algorithm in C++/independent Python attached.) The 32,897-by-32,897 binary matrix with row `i=\Phi(H_8(m_i))` has **GF(2) rank 32,897**, verified by exact bit-vector elimination on original-C outputs. All 32,897 successive indices yielded pivots. If a nonzero universal polynomial existed, its coefficient vector would be in this matrix's right kernel, contradicting full rank. The message-family seed is only a reproducibility convention, not a statistical or cryptographic assumption in the deduction.

**Reproduction:** `krakken_quadratic_image_audit.cpp` compiled and linked with **unchanged original** `krakken.c` outputs `result=PASS bits=256 monomial_dimension=32897 rank=32897 samples=32897`. The independent `krakken_r8_quadratic_independent_check.py` separately regenerates **all 32,897 digests using ctypes and original C**, hashes their concatenation with SHA-256, and checks GF(2) rank `2081/2081` on the complete 64-bit degree-two subcertificate using an independent Python-int rightmost-pivot algorithm. **Independent full-256 rank confirmation PASS:** `krakken_r8_quadratic_reverse_rank.cpp` reads the independent Python/original-C digest archive and performs a separately coded **highest-bit-pivot** elimination (the primary certificate uses lowest-bit pivots); it also obtains **32,897/32,897**, after checking the archive length. The independent rank tester does not call or reuse the primary rank implementation. `KRAKKEN_R8_QUADRATIC_32897_DIGESTS.bin` (32,897 × 32 bytes = 1,052,704 bytes) is the independent Python/original-C digest archive; `KRAKKEN_R8_QUADRATIC_256_PIVOTS.txt` lists the indices accepted by the primary rank verifier (all `0..32896`). The digest stream SHA-256 is **`b9c0d7cf14ff388b144e025faf501b7f7334274be13d4d01a4193607f9f89e64`**.

**Interpretation:** An exact, nontrivial *output-only* Boolean polynomial relation of degree `≤2` is impossible for full R8 H159. This is **not** a bound on nonlinear input-output relations, on approximate probability biases, on output collisions, on preimages, or on all possible high-degree algebraic relations.

## WORK-HASH-R8-CUBE12-DEGREE-030 — Every nonzero digest parity has degree at least 12

**Claim (actual eight-round hash, H159).** Let `H_8(m)\in\mathbb F_2^{256}` be the digest, and define the 12-dimensional input cube to vary exactly **all eight bits of message byte 0 and the low nibble of message byte 1**. Write `E(u)` for embedding `u\in\mathbb F_2^{12}` in these coordinates. For any 159-byte base `m` with these bits set to zero, define

\[
D_SH_8(m)=\bigoplus_{u\in\mathbb F_2^{12}}H_8(m\oplus E(u))\in\mathbb F_2^{256}.
\]

The 256-bit derivative vectors from the **257 explicit base messages indexed `0..256`** have full span `\mathbb F_2^{256}`. More precisely, a recorded 256-row submatrix of these derivative vectors has **exact rank 256/256** over GF(2).

Consequently, for *every* nonzero output mask `beta\in\mathbb F_2^{256}`, the Boolean component `m\mapsto beta·H_8(m)` has algebraic degree **at least 12** over the 1,272 independent message bits. Equivalently, there exists **no universal equation** `beta·H_8(m)=Q(m)` with `beta != 0` and any Boolean polynomial `Q` of total degree `≤11` in those message bits.

**Finite-witness proof:** If a component had degree below 12, its 12th-order coordinate derivative `D_S(beta·H_8)` would vanish for *every* base (standard Boolean ANF fact). Yet `D_S(beta·H_8)(m)=beta·D_SH_8(m)`, and the source-derived vectors from our 257 bases span 256 dimensions, so a mask orthogonal to every derivative vector must be zero. This contradiction proves the claim without inferring any probability distribution. It also shows that **no nonzero 256-bit digest parity is universally 12-cube-balanced for this fixed cube**. In fact, its ANF includes a monomial containing *all twelve fixed cube variables* (possibly multiplied by other message variables).

**Actual calculations:** each base requires `2^12=4096` original-source eight-round hashes, so 257 bases required **1,052,672 exact full-eight-round hash calls**; the primary program `krakken_cube12_r8_audit.cpp` computed rank **256/256**. Bases are unique: the eight-byte index occupies message bytes `2..9`, initial message byte 0 and low nibble of byte 1 are zero, and other bytes are generated by SplitMix64 with fixed `SEED=0x12C0BE20261105A5` (exact code supplied). These 257 cubes are disjoint sets of valid 159-byte messages. `KRAKKEN_R8_CUBE12_RANK_WITNESSES.tsv` records **256 exact (base-index, derivative-hex) spanning rows**.

**Independent checks:** `krakken_r8_cube12_independent_check.py` independently recomputed the TSV's exact GF(2) rank as **256/256**, using the opposite pivot convention (LSB rather than the primary high-pivot procedure), and recomputed the full 4096-query derivatives at bases **0, 11, 127, and 256** from an independently coded Python message generator calling the unmodified original scalar C via `ctypes`: **4/4 exact matches**. As a control, the same independent checker evaluated the *one-round* version of the same cube at base zero and confirmed that the XOR of **digest bit 11** is zero, matching the inherited one-round 12-cube integral. This one-base R1 check is not an independent re-proof of that universal R1 integral.

**Scope:** Applies to the **actual 8R hash's entire 256-bit digest**, but to **the specific fixed 12-variable input cube** on exactly 159-byte messages. It does not prove algebraic degree close to the maximum 1272, any collision- or preimage-work exponent, resistance to general cube attacks, or a differential-probability bound; it excludes low-degree input-polynomial representations of **single linear combinations of output bits**. It says nothing about unrestricted 2048-bit permutation-output components without domain restriction.

## Why this is complementary to the earlier research

- The earlier `LIN-GLOBAL-001` excluded universal **affine** input/output equations for R1–R8. `-030` extends the excluded **input polynomial degree** up to 11 for *any nonzero output parity* at R8 (on H159), while `-029` excludes **quadratic output-only equations** involving arbitrarily many of the 256 digest bits.
- The earlier `WORK-INT-VALID159-CUBE12-017` proved 25 universal balanced masks for **R1 full-state outputs**, with one digest-only bit-11 mask in their span. `-030` proves that **no digest-only mask whatsoever** remains universally balanced on this specified cube at **R8**.
- Both theorem proofs are existential finite-witness certificates: the search may use a deterministic generator; the *proof* relies on exact full-rank finite matrices, not on any unproven randomness of that generator.
- Neither theorem implies or is meant to imply that Krakken-256's concrete collision resistance is `2^128` or that its preimage resistance is `2^256`. The design-level figures rely on the ideal-permutation model.

## Reproduce (Linux x86-64 little-endian)

Put `krakken.c`, `krakken.h`, and the included audit files together:

```sh
cc -std=c11 -O3 -c krakken.c -o krakken_original.o -pthread
g++ -std=c++17 -O3 -march=native krakken_quadratic_image_audit.cpp krakken_original.o -pthread -o quadratic_audit
g++ -std=c++17 -O3 -march=native krakken_cube12_r8_audit.cpp krakken_original.o -pthread -o cube12_audit
g++ -std=c++17 -O3 -march=native krakken_r8_quadratic_reverse_rank.cpp -o reverse_rank_audit
./quadratic_audit 256 33100 KRAKKEN_R8_QUADRATIC_256_PIVOTS.txt
./cube12_audit 280 KRAKKEN_R8_CUBE12_RANK_WITNESSES.tsv
cc -std=c11 -O3 -shared -fPIC krakken.c -o _krakken_original.so -pthread
python3 krakken_r8_quadratic_independent_check.py
./reverse_rank_audit KRAKKEN_R8_QUADRATIC_32897_DIGESTS.bin
python3 krakken_r8_cube12_independent_check.py
```

**Archival discipline:** Save the two original-source SHA-256 hashes, both source audit programs, both Python independent checks, two JSON summaries, a copy of the derivative TSV and its SHA-256, and the complete canonical theorem ledger. No modification was made to the original source, to its eight-round count, or to the ongoing `[2,1]` scan. These results remain internally reproducible computational certificates, not externally peer-reviewed cryptanalysis.


## WORK-HASH-R8-CUBE22-DEGREE19-031 — Full original R8, all digest parities have ANF degree ≥19

**Scope / precise theorem:** Let `H8` be `krakken_hash_scalar` outputting 256 bits after eight original deterministic Krakken rounds on all valid **159-byte messages**, with mandatory terminal padding byte `0x86`. For every `β∈F_2^256\{0}`, the Boolean function `m↦β·H8(m)` has algebraic degree **at least 19** over the 1272 unrestricted message bits. Thus no universal equation `β·H8(m)=Q(m)` exists for `deg(Q)≤18` and nonzero `β`. **Permutation corollary:** every nonzero output parity supported on the **first 256 coordinates** of the full eight-round 2048-bit permutation output also has degree ≥19 as a function of all 2048 input bits, by restriction to the H159 padded-message subspace; **not all 2048 output masks are covered**.

**Certificate / proof:** In the exact valid159 affine family obtained by fixing all message bits except the **22 least significant bits 0..21**, let `F(x)=H8(m_x)` for `x∈F_2^22`. The remaining fixed message bits are seeded with SplitMix64 using `0x5A7C0C0A611BE291` (full construction in the accompanying reproduction code). For each of `C(21,18)=1330` 18-subsets `T` of bits0..20, the full 22-variable ANF coefficient of the degree-19 monomial `T∪{21}` is the XOR of the two 21-variable half-cube ANF coefficients `c_T(bit21=0)⊕c_T(bit21=1)`. These **1,330 exact 256-bit vectors have rank 256/256 over GF(2)**. Any `β≠0` whose global component degree were ≤18 would annihilate all these coefficients, contradicting full rank. The 256-row spanning witness and source-digest SHA-256 fingerprints are archived. Independent Python NumPy lower-pivot and C++ reverse-pivot elimination both return 256/256; an independent direct original-C 19-cube XOR with 524,288 total original-C queries matches its archived coefficient. Exact report: `KRAKKEN_R8_CUBE22_THEOREMS_031_032.md`; original sources unchanged (C `4d659644...`, H `83f891b6...`).

**Interpretation/limit:** This rules out universal input polynomials of degree ≤18 for any nontrivial output parity, and excludes one nonzero output mask balanced on *every* one of the **1,330 specified 19-cubes**. It does **not** give a collision, preimage, differential-hull, linear-correlation, or generic security-work exponent, nor degree bounds for unrestricted full-state output masks outside first256 coordinates. The earlier `-030` degree≥12 remains correct but is strictly superseded as a floor for H159.

## WORK-HASH-R8-CUBE22-PREFIX-COLLISION-032 — Exact restricted 64-bit injectivity and 18-bit surjectivity

**Scope:** Same `2^22=4,194,304` explicit valid159 affine message family as `-031` and original full eight-round `H8`. **Finite-domain exact statement:** The mapping from these messages to the **first 64 digest bits is injective**, and consequently none of their full 256-bit digests collide. In addition, the first-18-bit projection of the digest is **surjective** onto all `2^18` patterns, with **2 to 36** preimages *within this family* per 18-bit pattern.

**Certificate:** Two separate original-C `2^21`-message streams, one with message bit21=1 and one flipped to0. The source-replayed 64-bit prefix array for their union has **zero duplicates**; complete source-C enumeration covers all `2^22` values of the free input bits. Independent histograms: prefix16 all 65,536 patterns, **36..97** observations/pattern, 134,238,641 collision pairs; prefix17 all 131,072 patterns, **12..59**, 67,112,345 collision pairs; prefix18 all 262,144 patterns, **2..36**, 33,556,703 collision pairs. Therefore for uniform input from *only this fixed finite family*, `Pr[first18(H8(m))=z]∈[2/2^22,36/2^22]` for every z, and the 18-bit prefix min-entropy is ≥`22−log₂(36)=16.830075` bits. Digest archives, signed hashes, exact message generator, cross-source replay, and independent checker are documented in `KRAKKEN_R8_CUBE22_THEOREMS_031_032.md`.

**Limit:** These are exact *restricted-input-family* collision and distribution facts. They do **not** imply first64 injectivity, 18-bit prefix-surjectivity, or 16.83-bit prefix entropy for all messages. They do not show 128-bit global collision hardness, 256-bit preimage hardness, or actual random-oracle equivalence. An initial attempt at the bit21=0 half-cube was rejected when its digest stream mistakenly matched the other half due to an **analysis-harness fixed-byte restoration bug**; it was corrected and rerun, and the two final stream hashes differ. The original Krakken source was unchanged.



## WORK-PERM-R8-FULLSTATE-DEGREE20-033 — Full original eight-round K8, every 2048-bit output parity has ANF degree ≥20

**Precise actual-construction theorem:** Let `K8 : F₂^2048 → F₂^2048` be exactly eight rounds of the pinned original scalar Krakken permutation. For **every** nonzero output mask `β∈F₂^2048`, `deg_x(β·K8(x))≥20`, where degree is over the 2048 Boolean input coordinates. Equivalently, no equality `β·K8(x)=Q(x)` with nonzero β and any input polynomial Q of degree ≤19 can hold on **all** 2048-bit inputs. **Valid159 hash corollary:** For all `β∈F₂^256\{0}`, `deg_m(β·H8(m))≥20` over all valid 159-byte messages; only the first256 permutation output bits are retained by that hash, but the underlying theorem covers **arbitrary** 2048-bit permutation-output parity masks. This supersedes earlier bounds ≥19 (`-031`) and ≥12 (`-030`) as universal degree floors; those certificates remain valid as historical results.

**Exact certificate:** Fix 159 message bytes by SplitMix64 seed `0x5A7C0C0A611BE291`, clear bits0..20 for a baseline, and form `2^24=16,777,216` padded full-state inputs by toggling bits0..23, with fixed byte159=`0x86` and remaining 96 capacity bytes zero. Enumerate all eight 21-dimensional subcubes indexed by toggles of input bits21,22,23. On each subcube compute the **vector-valued exact 21-bit Möbius ANF**, retaining 5,985 output vectors indexed by the `C(21,17)` monomials of degree17. XOR the eight corresponding vectors to obtain the **5,985 coefficients of degree20** supported on `T∪{21,22,23}`. This 5,985×2048 matrix has rank **2048/2048** (independent Python low/high-pivot and independently implemented C++ high-pivot eliminations). Therefore for every nonzero β at least one 20th-degree coefficient of `β·K8` is nonzero on this affine subspace. The global ANF degree cannot be less than 20, since affine restriction cannot increase degree.

**Source and verification:** Original C SHA-256 `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, header `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`; original source unchanged. The main 16,777,216-state enumeration used a **separate analysis-only bytewise-equivalent S-box lookup optimization**, not a mutation of production C. Mathematical equivalence follows from the original byte-independent equality masks; 5,304 tests of original expression versus direct lookup, 8,192 original-C versus optimized complete eight-round 2048-bit outputs spanning all eight subcube labels, and **4,194,304 exhaustive original-C digest comparisons on the first two subcubes** all passed. Crucially, a **complete 1,048,576-query 20-dimensional cube** evaluated directly with **unmodified original krakken.c**, with all **2048 XOR output bits** compared against one archived degree20 ANF coefficient, **passed exactly** (`mask=14811135`). Eight full 5,985-row degree17 coefficient archives and a compact **2048-vector degree20 full-rank basis** are archived (`KRAKKEN_R8_FULLSTATE_DEG20_BASIS.tsv` SHA-256 `bcf09e59470524cc0670a44a8e9addc25901c189b14df8bfe19d5f5619632c43`), together with independently executable checkers and hashes.

**Limits:** Exact construction-specific algebraic exclusion, **not** a differential characteristic/hull bound, collision or preimage-work lower bound, random-oracle indistinguishability guarantee, or estimate of how close the degree is to its 2048-input maximum. It does not imply a 20-bit security level; degree has no such direct interpretation. It excludes universal degree≤19 **input-polynomial** representations of nonzero **output parities**, not arbitrary nonlinear output predicates. It does not affect the separate `[2,1]` scan, last user-reported at `i=176` without new checkpoint files. Full proof, reproducibility and source/evidence separation: `KRAKKEN_R8_FULLSTATE_DEGREE20_THEOREM_033.md`. **Next theorem ID: `-034`.**

## WORK-LIN-R1-CARRYFREE-034 — Exact complete-one-round Walsh bounds on 32 selected output bits

**Actual pinned Krakken source; uniform unrestricted 2048-bit input.** For `F_r=InkCloud∘Iota_r∘Pressure∘Butterfly∘Chi∘Pi∘Rho∘TentacleMDS∘Theta`, each of 32 output coordinates obtained from the bit-zero output of one Pressure word (after its rotations, Iota and Ink) satisfies

```text
max_(α ∈ F₂^2048) | E_X [(-1)^(α·X ⊕ F_r(X)[j])] | ≤ 2^-360,
```

for every complete **single round** r=0,...,7. This is an exact finite-algebraic theorem for the 32 individually fixed coordinate masks, not a claim that any arbitrary output linear mask or the 8-round composition enjoys this ceiling. The upper bound `2^-360` is optimal among these 32 positions: j=395 and j=907 attain equality. Four of the 32 positions belong to the first 256 state/digest coordinates of **one reduced round**, j=11,94,139,210; their separate maxima are all even smaller, but this does not imply the same bound under restricted valid159 hash-message input distribution.

**Proof:** The source Pressure first-bit identities are exactly `A0=a0⊕c0⊕c17`, `C0=a0⊕c17`, `B0=b0⊕d0⊕d17`, `D0=b0⊕d17`. The corresponding round-end bits are affine functions of the Butterfly outputs; pull the masks through the exact GF(2)-transpose Butterfly. Pre-Chi original linear prefix is invertible and maps uniform full states to uniform 256 bytes, divided into 128 independent serial-Chi 16-bit cells. For each cell, the exact S-box Walsh factorization is

```text
W_T(α,γ; μ,ν) = W_S(α, μ⊕α⊕γ) W_S(α⊕γ,ν).
```

Exhaustive local S-box masks and an independent 16-bit `65536`-point FWHT of the 320 resulting distinct nonzero local output-mask pairs establish each local optimum. Product of the 128 normalized optima is **exact** for the complete one-round coordinate, because the input cells are independent under an unconditional uniform state and the input-mask maximization separates across cells. Among the 32 output-coordinate masks, 80–122 local cells are nonzero. For each of j=395 and907, 40 cells have optimal magnitude `2^-3`, another 40 have `2^-6`, yielding exactly `2^-360`. The other 30 products are strictly smaller. 72 independent source-C full-state inputs ×32 coordinates validate 2,304 bit predictions; round constants can only change correlation signs.

**Evidence:** `KRAKKEN_LINEAR_CARRYFREE_THEOREM_034.md` contains complete formulas and the all-coordinate exponent table. `KRAKKEN_LINEAR_CARRYFREE_AUDIT.py` (exact 32 rational products, source-C replay); `KRAKKEN_LINEAR_CARRYFREE_INDEPENDENT.cpp` (exhaustive independent Walsh transform); `KRAKKEN_LINEAR034_DATA/linear034_result.json`, `local_mask_verification.csv`. Pinned source hashes remain `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` / `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

**Limits:** No eight-round linear-hull bound or concrete attack-complexity exponent can be obtained by multiplying these per-round correlations. Unlike input-independent S-box-lane coordinates within a *single* full round, the state distributions conditional on intermediate trails are correlated across rounds. The `-034` bound also does not cover arbitrary one-round output parity masks, differential probabilities, or restricted padded-message inputs. Last user-reported `[2,1]` scan position updated to **183** without file-based checkpoint verification. **Next identifier is `-035`.**

## WORK-DIFF-H159-R8-CUBE22-4BIT-035 — Actual 8-round, exhaustive restricted 4-bit differential-hull ceiling

**Classification: Exact finite-source computational theorem; all 8 original Krakken rounds, valid-159-byte hash inputs.** Fix the 159-byte baseline by SplitMix64 seed `0x5A7C0C0A611BE291` and let only the first 22 message bits vary. The result concerns `Y(m)`, the four digest bits `[11,94,139,210]` (same coordinate labels as the reduced-round `-025`, but **NOT** the same conditioned `A1=5` differential classes). For **every** nonzero 22-bit input XOR delta and **every** four-bit target `t`, define `N(Δ,t)=#{u: Y(u) XOR Y(u XOR Δ)=t}` over all `2^22` valid messages in this *one fixed* affine family.

**Proved bounds across ALL `4,194,303×16=67,108,848` DDT entries:**

```
  258234 ≤ N(Δ,t) ≤ 266314
  258234/4194304 ≤ Pr_u[ΔY=t] ≤ 266314/4194304
  |Pr_u[ΔY=t] − 1/16| ≤ 4170/4194304 ≈ 0.00099420547485
  max_(Δ≠0) TV(Law_u(ΔY), U_4) = 19328/(2*4194304)
                                 = 0.0023040771484375
```

The largest count is **266314** at `Δ=0x2539db`, `t=8`; the smallest count **258234** at `Δ=0x32bd9f`, `t=14`; the worst-TV difference is `Δ=0x3442c9`. Since even the minimum count is positive, every output pattern occurs for *every* permitted nonzero delta. For `t=0` specifically, the delta-wise count range is 258692..265524. These are exact *pair counts*, not statistical expectations, sampled frequencies, or trail-product approximations.

**Mathematical computation:** For each four-bit output mask `s`, let `g_s(u)=(-1)^(s·Y(u))`. Its exact autocorrelation satisfies `C_s(Δ)=WHT(WHT(g_s)^2)(Δ)/2^22` using unnormalized integer Walsh-Hadamard transforms; output-difference counts are `N(Δ,t)=(1/16) sum_s (-1)^(s·t) C_s(Δ)`. The first independent C++ verifier computes all 15 nonzero characters. A **second separately implemented full-domain C++ verifier** instead transforms all 16 **indicator** functions `1_[Y(u)=y]` and uses their cross-correlations, recovering the exact same global maximum/minimum patterns and worst-TV bound. A separate NumPy verifier directly visits **all 2^22 bases** for 12 selected deltas and matches all 192 bins; 28 unmodified-source-C hash replays across the two original digest archives pass. Direct fresh **4096-message original-C** replay exactly reproduces the compact projection's first 4096 bytes. Original C/H and two digest archive full SHA-256 fingerprints match earlier certificates; compact projection (4 MiB) SHA-256 is `09ea0c884f6e7ddfe2e511c3eb5e5bde3155959a38f4f9327b9fbffdb07dc7d2`.

**Scope boundary:** This is a full-eight-round **restricted-input/four-bit-output differential-hull** ceiling, not an upper bound for arbitrary nonzero 2048-bit state differences, not a 256-bit digest-wide DP bound, not a key-attack/hashing collision/preimage work exponent, and not a certificate against all potential distinguishers. The fixed initial message family is one 22-dimensional slice of the 1272-bit valid-message domain. The `-025` three specially conditioned `A1=5` differences may be outside that slice, and the present result does not refute or redo them. Full mathematical report: `KRAKKEN_R8_DIFFERENTIAL_THEOREM_035.md`. Primary and independent executables: `krakken_r8_diff4_035.cpp`, `krakken_r8_diff4_035_independent_fwht.cpp`, `krakken_r8_diff4_035_originalC_generate.cpp`; JSON and text audits and compact archive packaged in `KRAKKEN_R8_DIFF4_035_EVIDENCE.zip`.

**Running `[2,1]` campaign:** last user-reported position `i=183`; unchanged and *not independently checkpoint-audited*. **Next theorem identifier: `-036`.**


## WORK-DIFF-H159-R8-CUBE22-8BIT-036 — Eight-round exact 8-bit differential-hull ceiling on a 22-variable valid159 input family

**Classification: actual source-pinned full eight rounds; exact computer-assisted finite-domain theorem with explicitly restricted input and output domains.** Original scalar source hashes `krakken.c=4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`, `krakken.h=83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`. The domain is the same **one specific** `2^22`-message affine family as `-035`: 159-byte messages, SplitMix64 baseline seed `0x5A7C0C0A611BE291`, first 22 message bits vary, remaining 1250 bits fixed, then mandatory final padded byte `0x86`. Observe output digest coordinates `[11,94,139,210,0,52,128,242]` in the stated order, so the lower four projected output bits are exactly theorem `-035`'s output projection.

For every `0≠Δ∈F₂^22` and `t∈F₂^8`, let `N(Δ,t)=#{u∈F₂^22 : Y(u) XOR Y(u XOR Δ)=t}`. The complete **`(2^22−1)×256=1,073,741,568` entry table** has exact integer global extrema:

```
  minimum N(Δ,t)  = 15308 at Δ=989310,  t=173
  maximum N(Δ,t)  = 17464 at Δ=1913404, t=49
  zero-target t=0 count range: 15458 .. 17354
  maximum TV over all Δ≠0 versus uniform 8-bit output difference:
             46884/(2*4194304) = 0.005589008331298828125
             at Δ=2777555
```

Consequently, **`15308/4194304 ≤ Pr_u(ΔY=t) ≤ 17464/4194304 ≈ 0.0041637420654296875`** for **every** nonzero delta and 8-bit target in this single family, and every target appears at every permitted delta. Maximum pointwise deviation from ideal `1/256` is bounded by `1080/4194304`. All counts are even, consistent with XOR-pair symmetry.

**Proof mechanism:** `C_s(Δ)=WHT(WHT((-1)^(s·Y))²)(Δ)/2^22` for the 256 output characters, followed by eight-bit inverse character transform `N(Δ,t)=(1/256) Σ_s (-1)^(s·t) C_s(Δ)`. The complete computation is exact integer arithmetic, verifies all needed divisions, parity, positivity, and bin sums for every delta; it aborts rather than overflowing compact 16-bit storage for nonzero-delta correlations. The 4-MiB compact witness `KRAKKEN_R8_DIFF8_036_FULL22_PROJECTION.bin` has SHA-256 `ba4dc630cbf72b289c8fc6910307aecdbbe929c677e56c571c2cd817af9af012` and alone suffices to rerun the complete global computation (`krakken_r8_diff8_036_from_projection.cpp`). The full original-C digest archives from `-031/-032` were rehashed and used to derive it, and an independent NumPy implementation reconstructed all 4,194,304 projection bytes. **All 4,194,304 lower-nibble bytes agree with the independently earlier verified 4-bit compact archive from `-035`.** A direct, non-FWHT checker exhaustively counts all `2^22` message-pair bases for **39 distinct deltas ×256 output patterns (9,984 bins)**, including the maximum/minimum/TV-witness histograms; **96** complete 256-bit original-C hash replays match the compact data; a fresh original-C-only first-1024 projection test passes. The results were also reproduced byte-for-byte by a standalone compact-data C++ executable. This is **one full-domain algorithm plus multiple independently constructed partial/source cross-checks**, not a claim that a second distinct full-domain algorithm was run.

**Strict scope:** Actual full 8R and all contributing internal trails, but only on one pinned 22-dimensional affine family and eight selected digest bits. **Not** all 159-byte messages or all unrestricted permutation-state inputs/differences, all 256 digest bits, a maximum full-permutation differential characteristic/hull bound, linear hull, or any `2^128` collision / `2^256` preimage security theorem for fixed Krakken. The `A₁=5` selected conditioned differences remain separate; no conclusion about them is implied. Proof/replay instructions and evidence are in `KRAKKEN_R8_DIFFERENTIAL_THEOREM_036.md` and `KRAKKEN_R8_DIFF8_036_EVIDENCE.zip`.

**`[2,1]` report:** User-reported running position advanced to **`i=191`**; no new solver checkpoints audited. If positions 0..190 finished and excluded all sites, that is **7,823,360 / 8,355,840 = 93.62745%** conditional coverage, with 532,480 remaining configurations. Scanner endpoint completeness and low-bit model soundness still require independent audit. **Next theorem identifier: `-037`.**

## WORK-DIFF-H159-R8-MULTIFAMILY-8BIT-037 — Exact eight-round eight-bit DDT bounds across five distinct 17-variable affine message families

**Classification: exact original-source finite-family theorem, two separately implemented complete-domain integer verifiers and independently replayed original-C inputs.** Five explicitly pinned `2^17`-message valid159 affine families differ in *both active message-bit coordinates and fixed message background* (`reference`: bits0..16, original -036 subfamily; `midword`: bits320..335,479; `tail`: bits1200..1215,64; `strided`: (73j mod1272), j=0..16; `byteoffset`: 8j+3, j=0..15 plus1101). The observed eight original eight-round hash digest positions remain `[11,94,139,210,0,52,128,242]`. Each nonzero internal family delta and each 8-bit target has a frequency among 131072 uniformly chosen base messages. All **`5×(2^17−1)×256 = 167,770,880`** cells were enumerated with exact integer arithmetic.

**Certified extrema over the five named families:** `310 ≤ N_F(Δ,t) ≤ 706` (global minimum `tail`, Δ77768,t253; maximum `tail`, Δ36038,t29), so `0.0023651123046875 ≤ Pr[ΔY=t] ≤ 0.0053863525390625` for each specified F, each nonzero Δ in F's *17-dimensional variable space*, and each t. **Every one of the 256 targets is attainable for every such delta in every family.** Worst total-variation distance from `Uniform(F₂^8)` is `8120 / (2×131072) = 0.030975341796875` (midword delta51609). Exact min-entropy floor for the 8-bit projected output difference over a uniform base in these families: `log₂(131072/706)≈7.53648` bits. All five projected images individually cover all 256 output values, with frequency extrema 438 and 597 across families.

**Evidence hierarchy:** The four new families' 524,288 output bytes were generated by the **unmodified original scalar C hash** with pinned source SHA-256, reference `2^17` bytes were independently regenerated through original C and match the original -036 22-bit dataset's first 131072 entries. Two distinct **full 33,554,176-cell DDT algorithms for each family** agree exactly: (i) output-character autocorrelation FWHT; (ii) two-dimensional `input × output-label` indicator-matrix autocorrelation FWHT. Both perform exact integer divisions and complete DDT row-sum/parity/positivity checks. A separate Python/NumPy checker independently counts **47 full 131072-base differential histograms per family (60,160 bins)** including every extreme and worst-TV witness, and recomputes **250 complete original-C digest outputs** with an independently specified SplitMix64 message generator (50 per family). Evidence and scripts: `KRAKKEN_R8_DIFFERENTIAL_THEOREM_037.md`, `KRAKKEN_R8_DIFF8_MULTIFAMILY_037_EVIDENCE.zip`, `KRAKKEN_037/krakken037_generate.cpp`, `krakken037_analyze.cpp`, `krakken037_independent_full.cpp`, `krakken037_independent_audit.py`, five projections and report JSONs, archive manifest.

**Strict limitations:** Exact eight-round *eight-bit projection* differential-hull facts on **five fixed 17D subsets** of 1272-bit valid159 message space; not unrestricted 2048-bit permutation differences or all 159-byte messages, all output coordinates, arbitrary distinct-family pairs, or a collision/preimage work factor. No independent-round or independent-family probabilistic assumption is made; no concrete universal attack-security exponent follows. This theorem does not strengthen the older -036 22D numerical ceiling for that prior fixed family (different domains and sample sizes). Last `[2,1]` scan position user-reported `i=191`, **not** checkpoint audited. **Next working ID: `-038`.**


## Historical preliminary campaign-status headers (superseded by 2026-11-06 closeout)

> **LATEST AUDITED [2,1] CAMPAIGN STATUS AND NEW THEOREM — 2026-11-06 (supersedes earlier preliminary header).** The user supplied `KRAKKEN_21_MISSING_CORE.zip` containing both missing model scripts and the complete `i000` final JSON, plus duplicate site/refinement TARs and `last_run_summary.json`. **Every one of the 8,355,840 enumerated spatial sites is now recorded as excluded, with zero remaining SAT/UNKNOWN after refinement**, and i000's exact 1,141 low4 cases were independently reconstructed from its SHA-matched low3 parent. All 253 main checkpoints `i002..254` match the exact original-C and model-script SHA-256 fingerprints. **All 4,141 saved high-tier UNSAT refinement decisions were re-solved as UNSAT by a new local Z3 context**: i000 low4 1,141; i001 low5 750 and low6 250; other 2,000 low7, with **zero mismatches**. Additional 12,468 original-C/Python layer checks and 16,000 independent seven-bit Pressure-chain calculations passed. Original files unchanged. **New analytic theorem `WORK-PRESSURE-LOWK-OVERAPPROX-038`:** for k in `{1,3,4,5,6,7}`, the low-k Pressure SMT equations are mathematically *necessary* for every actual full-width XOR differential (proof: reduce both modular shears modulo 2^k; A<<31 vanishes and u'=u XOR Δc XOR (Δc>>17)); complete proof in `KRAKKEN_21_FULL_CAMPAIGN_EXTENDED_AUDIT.md`. This certifies the Pressure arithmetic over-approximation, **not** independently every previously recorded early-stage solver UNSAT or the full global `[2,1]` exclusion; no universal [2,1] theorem or stronger eight-round activity bound is promoted here. **Next unused working theorem ID: -039.** Audit files: `KRAKKEN_21_EXTENDED_AUDIT_RESULTS.json`, `krakken_21_extended_audit.py`, ten batch JSONs, and `KRAKKEN_21_FULL_CAMPAIGN_EXTENDED_AUDIT.md`. Older scan-position and missing-file notes below are superseded.

> **NEW PRELIMINARY ARCHIVE AUDIT — 2026-11-06 (status-only; NOT theorem -038).** Independently inspected user-uploaded `KRAKKEN_21_COMPLETE_AUDIT.zip` containing 689 members, including 19 Python scripts, exact-source `krakken.c/h`, the 253 completed parent position JSON checkpoints `i002..i254` (8,225,536 sites), 15 generic low7 children (1,875 UNSAT), and special `krakken_21_low7_i002.json` (125 additional UNSAT). Parent raw-record SHA-256, lengths, counts, C/H fingerprints, available Python model fingerprints, child/parent SHA-256 linkages, child case-coordinate ordering, and 249 `i006..i254` CLOSED auto-reports passed read-only consistency checks. Position `i001`'s separate full 65,024-site tiered parent and 1,000→250→0 refinement chain pass hash and case-alignment checks. Position `i000`'s 65,280-site closure is documented by `krakken_21_low4_first0_closure.log`, but its completed JSON is missing from the archive. **Together the available data report 8,355,840/8,355,840 examined and ZERO remaining unresolved configurations, conditional on the i000 log.** This is a file-level/bookkeeping audit only, not independent Z3 UNSAT verification or proof of necessary-condition soundness; **do not promote global `[2,1]` exclusion or any 8R S-box bound yet.** Still needed for a soundness audit: `krakken_screen_21.py`, `krakken_screen_21_low2.py`, and ideally `krakken_21_low4_first0_closure.json`. Note that positions 2–6 use the original `krakken_21_all_positions.py` while 7–254 use `krakken_21_all_positions_equiv.py`, each with matching supplied-script hashes. Preliminary audit details: `KRAKKEN_21_PRELIMINARY_AUDIT.md`, `krakken_preliminary_zip_audit.py`, `krakken_preliminary_zip_audit_results.json`. **Next working theorem ID remains -038.** Older scan-position updates below are superseded by this uploaded snapshot.

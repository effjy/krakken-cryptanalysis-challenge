# Krakken research 13 — exchange squares, Yoyo, rotational/DDT hybrids, and rebound audit

Date: 2026-11-18. Source: the five related attack-research ZIPs supplied in `~/Downloads/`, culminating in `krakken_exchange_research_bundle_v5.zip`. Primary ledger: its `ATTACKS.md`, sections 1–14. This document imports useful constructions, experimental evidence, and qualifications after comparison with Research 01–12.

**Main additions:** an explicit four-message H159 exchange square with 32 guaranteed full-state one-round parity checks, four of which lie in the reduced digest; an exact carry-controlled two-round related-input DDT-support test; controlled exchange/Yoyo experiments through eight rounds; and an audit separating a legacy four-stage surrogate from a genuine full-permutation rebound attack.

**No new general differential-probability upper bound or eight-round security-bit claim results from this import.** The established unrestricted/H159 activity floors remain 16/20, and the H159 `A1=5` conditional floor remains 22. Research 12's different, unrestricted conditional 51-call result is unchanged.

**Coverage clarification (follow-up):** the initial version summarized the main additions, leaving several campaign variants and numerical results too compressed. Section 10 now explicitly inventories every performed campaign and control in `ATTACKS.md`; section 11 records the additional measurement tables. Overlapping component theorems remain attributed to earlier research. The standalone `~/Downloads/ATTACKS(4).md` was checked byte for byte against the archived v5 ledger: **they are identical**.

## 1. Provenance, preservation, and verification level

The [reproduction package](reproduce/exchange_bundle_v5_20261118/README.md) preserves all five original ZIPs, their extracted contents, the complete supplied ledger, original aggregate JSONL evidence, a combined working directory, and fresh checks. No supplied C/H or historical ledger was overwritten.

- [Original v5 ATTACKS.md](reproduce/exchange_bundle_v5_20261118/archive/ATTACKS.md).
- [v5 import identity](reproduce/exchange_bundle_v5_20261118/IMPORT_MANIFEST.json) and [earlier bundle identities](reproduce/exchange_bundle_v5_20261118/EARLIER_IMPORTS.json).
- [Embedded checksum checks](reproduce/exchange_bundle_v5_20261118/MANIFEST_CHECKS.json).
- [Evidence/replay report](reproduce/exchange_bundle_v5_20261118/VERIFICATION_REPORT.json).
- [Independent exchange-square audit](reproduce/exchange_bundle_v5_20261118/INDEPENDENT_AUDIT.json).

All ZIP CRC checks passed. All checksum entries in the four supplied checksum lists matched: 26 in v5, 17 in updated, 23 in v3, and 27 in v4. The introductory prose in the updated manifest was treated as prose, not a checksum entry. The v4 ZIP nested in v5 equals the separately downloaded v4 ZIP byte for byte.

All five bundles contain the same original scalar sources as the current project:

```text
krakken.c  4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6
krakken.h  83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c
```

All twelve historical research files included in v5 match the corresponding live Research 01–12 files byte for byte at import. They are context snapshots, not additional new theorems.

Fresh verification performed in this import:

1. Regenerated the H159 witness JSON and header **byte for byte**.
2. Independently reconstructed all 1,272 H159 prefix columns in Python; compared each with original C under **GCC and Clang**; recomputed both half-space ranks using high and low pivots.
3. Replayed 16 separate valid-message quartets per compiler through the original Chi and complete R1 APIs, confirming full post-Chi XOR zero and all 32 final parity bits.
4. Ran the supplied exchange/Yoyo runner on **256 trials per each of seven family/pattern combinations**, through all eight indexed rounds, under GCC and Clang. Their JSONL outputs are **byte-identical**. Each run includes 640 source-equivalence and 256 inverse checks, plus its H159 encoding/hash controls.
5. Ran the two-round DDT runner on **256 pairs per family**. It includes 896 source/inverse checks, **512 explicit original-C two-round comparisons** of constructed states, and a 16,384-pair independent-state null control.
6. Repeated the exhaustive BCT/local-Chi/MDS-minor script and the surrogate-trail script. Both outputs match the saved v4 JSONL **byte for byte**.
7. Independently enumerated the local switch's 65,536 bases to separate 1,536 total closures into 512 swaps and 1,024 four-distinct cases.

The large supplied statistical runs were preserved and their aggregate records checked; they were **not all rerun**. A checksum proves identity, not truth of a security claim. These are within-investigation checks, not external cryptanalytic review or proof-assistant verification.

## 2. What overlaps existing research

| Supplied material | Existing knowledge | Addition retained here |
|---|---|---|
| Abyssal DDT maximum 4, Walsh maximum 32, BCT maximum 6 | Research 01 component and Chi-superbox theorems | Independent counts, controls, and attack-specific witnesses |
| One-round sparse pre-Chi related differences | Existing local Chi/rebound and inverse-prefix analysis | Reproducible public-tail test and measured propagation |
| Pressure LSB linearity; 32 R1 integral coordinates | Existing algebraic/integral results; Research 11 records the same positions | A **two-dimensional, four-message H159 construction**, rather than the prior saved larger cube |
| Rotational structure before Pressure | Existing rotational decomposition and RX work | Chosen carry-controlled states and a fixed second-round DDT-support test |
| Rectangles/boomerangs/shared-chain quartets | Existing local and coordinated-quartet research | Explicit inverse-oracle Yoyo pattern, fixed-external-mask controls, and nondegenerate-count refinement |
| Sparse four-stage S-box/MDS trails | Surrogate-model work is not the full permutation | A concrete model-boundary audit and preserved trail witness |

These constructions belong to established attack families. They are not proofs that an entire attack family stops after a particular round.

## 3. EXCH-H159-001 — four-message valid-domain exchange square

Let L be the exact XOR-linear prefix `Pi o Rho o MDS o Theta`. Index the 16 whole Chi word-pair cells by `k=4*p+y`; their word positions are `(8*p+y, 8*p+y+4)`. This whole-cell index is distinct from the 128 aligned byte-cell indices used in activity campaigns.

Partition whole cells into even indices S and odd indices T. Let V be the 1,272-dimensional H159 message-difference space: only bytes 0–158 vary, while padding and capacity differences are zero. Define

```text
U_S = {A in V : L(A) is zero on every T cell},
U_T = {B in V : L(B) is zero on every S cell}.
```

Both restrictions have binary rank **768**, so each kernel has dimension **504**. The supplied generator constructs explicit nonzero A in U_S and B in U_T. The independent audit confirms their support constraints and both ranks with opposite pivot conventions.

For every base message M, the four distinct valid messages

```text
M,  M XOR A,  M XOR B,  M XOR A XOR B
```

give zero XOR of their four entire post-Chi states. Indeed, within any Chi cell at most one direction is nonzero, so its four inputs consist of two equal pairs. Applying any deterministic cell function preserves the zero four-value XOR. Fixed padding adds only a common affine offset. XRBD is linear, so the pre-Pressure four-state XOR is also zero.

This argument covers **all nonzero A in U_S and B in U_T**, not only the saved witness pair. The two spaces intersect only at zero: a vector in both has L-image supported on neither half, and L is invertible. Thus every such nonzero pair gives independent directions and four distinct messages. No assumption about random S-box outputs is used.

### Propagation through the complete round

For each Pressure column `(a,b,c,d)`, before the final word rotations, write the updated words as `(A,B,C,D)`. Their low bits satisfy exact GF(2)-linear equations:

```text
A[0] = a[0] XOR c[0] XOR c[17]
B[0] = b[0] XOR d[0] XOR d[17]
C[0] = c[0] XOR A[0]
D[0] = d[0] XOR B[0].
```

These equations have no incoming carry at bit zero. Pressure's rotations, fixed XOR constants, and Ink carry the 32 zero quartet parities to the following LSB-first full-state indices:

```text
11,94,139,210,267,350,395,466,523,606,651,722,
779,862,907,978,1035,1118,1163,1234,1291,1374,
1419,1490,1547,1630,1675,1746,1803,1886,1931,2002.
```

Therefore **at least these 32 complete-R1 output bits** always have zero XOR over the four messages. Only **11, 94, 139, 210** lie in the first 256 bits. Consequently the construction gives:

- A four-query full-state reduced-one-round test with 32 guaranteed checks.
- A four-query reduced-one-round digest-position test with **four**, not 32, guaranteed checks.

For a random function with independent 256-bit outputs on the four distinct messages, the latter event has probability exactly **1/16**. For a uniform random 2,048-bit permutation followed by truncation, the probability is negligibly different from 1/16. More precisely, for a prescribed k-bit linear projection and four distinct inputs, it is

```text
2^-k * [1 + 3*(2^k-1)/((2^2048-1)*(2^2048-3))].
```

To see the correction, each nonzero projected character is balanced over the full permutation domain; its expected product on four distinct outputs is `3/((N-1)*(N-3))`, N=2^2048. Fourier inversion gives the formula. This comparison assumes a fixed construction independent of the ideal oracle's responses.

At eight rounds, the first 256 state bits agree with the actual hash API for exactly 159-byte messages, as checked by the supplied controls. The one-round test is a **reduced-round variant**, not a property asserted for the production digest. A zero quartet projection is not a pairwise hash collision.

### Supplied measurements

The initial stream uses seed `0x596f596f45786368` and 16,384 bases; the holdout uses seed `0x444952454354494f` and 32,768 bases. The same fixed A and B are used throughout. Both are deterministic PRNG streams, not an exhaustive population.

| Round | Initial four-bit digest hits / 16,384 | Held-out hits / 32,768 | Held-out mean full XOR weight | Held-out mean digest XOR weight |
|---:|---:|---:|---:|---:|
| 1 | 16,384 | 32,768 | 919.33 | 114.86 |
| 2 | 1,036 | 2,073 | 1023.93 | 127.97 |
| 3 | 968 | 2,049 | 1023.98 | 127.95 |
| 4 | 1,035 | 2,051 | 1024.08 | 128.07 |
| 5 | 956 | 2,025 | 1024.03 | 128.01 |
| 6 | 1,053 | 2,046 | 1024.09 | 127.99 |
| 7 | 968 | 1,945 | 1024.20 | 128.05 |
| 8 | 994 | 2,030 | 1023.78 | 127.95 |

All 49,152 supplied structures meet all 32 one-round checks. No supplied structure at rounds 2–8 meets the full 32-bit test. The four-bit reference expects 1,024 and 2,048 hits respectively. The ledger reports no later-round significance after seven-depth Bonferroni correction; its smallest corrected holdout p-value is about 0.1311 at round 7. These are binomial-reference statistical screens, not exact security bounds for the fixed permutation.

Exactly 32 coordinate positions were always zero in the initial one-round sample. That observation does **not** prove there are no additional universal mixed linear masks or other relations.

[Witness directions and ranks](reproduce/exchange_bundle_v5_20261118/archive/krakken_h159_exchange_vectors.json); [generator](reproduce/exchange_bundle_v5_20261118/archive/krakken_h159_exchange_generate.py); [initial data](reproduce/exchange_bundle_v5_20261118/archive/krakken_yoyo_exchange_results.jsonl); [held-out data](reproduce/exchange_bundle_v5_20261118/archive/krakken_yoyo_exchange_heldout.jsonl).

## 4. EXCH-PERM-001 — unrestricted exchange and inverse-oracle Yoyo

The supplied unrestricted forward construction chooses two pre-Chi states and exchanges a proper nonempty set of whole 128-bit Chi cells to obtain two further states. Applying L inverse gives four ordinary external inputs with XOR zero. Cell separability gives zero post-Chi XOR; the same 32 complete-R1 parity checks follow. It requires four forward queries and public linear preprocessing, with unrestricted inputs.

The inverse-oracle Yoyo variant instead:

1. Queries `F_r(X)` and `F_r(Y)`.
2. Undoes only the last round's public post-Chi tail.
3. Exchanges selected **whole** Chi cells, then reapplies that tail.
4. Uses two inverse-permutation queries to recover X' and Y'.

For r=1, `X XOR Y XOR X' XOR Y'=0` identically: inverting the separable Chi function just exchanges the corresponding pre-Chi cell inputs, and L inverse is linear. For r>=2 the earlier nonlinear rounds prevent this identity from following by the same argument.

The three selected exchange patterns are cell 0; cells {0,5,10,15}; and the eight even cells. Exchanging all cells would merely swap the complete states and is excluded. Degenerate states must also be rejected. This is an inverse-oracle unrestricted-state experiment, not an attack on the H159 hash interface.

For each pattern, the supplied forward test satisfies all 32 R1 parities in 49,152 combined trials. The inverse test has 49,152/49,152 full zero defects at R1. At each depth 2–8, every pattern has zero observed full inverse-quartet closures; holdout mean defect weights range approximately 1023.75–1024.34. No claim about all exchange patterns, chains, or biases follows.

Fresh 256-trial runs of all six unrestricted family/pattern combinations plus H159, under both compilers, agree byte for byte. The runner's general inverse checks passed. Its small Yoyo source-reference block computes forward images but does not explicitly compare them to its saved target arrays; it should not be described as an additional target-by-target inverse certificate. The separate 256 general inverse checks are the relevant supplied inverse consistency tests.

## 5. ROT-DDT-R2-001 — carry-controlled related-input test through two complete rounds

This is the most substantial additional multiround *attack-side* statement. It is distinct from a fixed-XOR-input differential-probability bound.

Let R rotate every word left by eight bits. Define

```text
L = Pi o Rho o MDS o Theta,
H = XRBD o Chi o L,
P = Pressure,  I = Ink,
K0 = the original first-round XOR-constant vector.
```

L, H, and I commute with R. Pressure generally does not. Choose a pre-Pressure state Z for which `P(R(Z))=R(P(Z))`, and set `X=H^-1(Z)`, `Y=R(X)`, excluding X=Y. Then exactly

```text
F1(Y) = R(F1(X)) XOR C,
C = I(K0 XOR R(K0)).
```

The construction uses public preprocessing; it does not claim this relation for arbitrary bases. The supplied families are:

- A: independently select a,b below 2^24 and c=d=0 in every Pressure column. The confined ranges make the rotation equality exact.
- B: select a,b below 2^20 and c,d below 2^8, with the exact Pressure-equality acceptance check.
- C pilot: a,b below 2^31 and c=d=0, accepting only exact-equality columns. The reported pilot averages about 4,099.63 draws per accepted column.

The implementation applies its exact local acceptance test to every accepted column, including families A and B. The rare R-fixed/identical input case is explicitly rejected. Thus the eligible-family guarantee does not rely on a sample-only assertion about carries.

### Second-round relation and test

The round-two linear-prefix inputs obey

```text
L(F1(Y)) = R(L(F1(X))) XOR E,  E=L(C).
```

For each Chi word pair `(a,b)`, its first S-box word input has known rotational XOR difference `E_a XOR ROL32(E_b)`. For the actual constants, all **128 corresponding byte differences are nonzero**. Each nonzero Abyssal input difference has exactly **127 allowed output differences** in its DDT.

Undo the known final-round post-Chi tail on each ordinary two-round output, obtaining U and V. For all 128 first-branch bytes, the corresponding byte of `V_a XOR R(U_a)` must lie in that fixed DDT support. All 128 membership tests hold for every correctly constructed pair. The test does not invert Chi or an additional complete round.

Under an independent ideal permutation, outputs at the two distinct fixed chosen inputs are uniformly distinct; applying the same fixed bijective inverse tail preserves that distribution. The independent-output reference probability of the predeclared support test is

```text
(127/256)^128 = 2^-129.448360...
```

Conditioning the ideal outputs to be distinct changes an event probability by at most `1/(2^2048-1)`. Thus the quoted value is an appropriate approximate **ideal false-positive probability**. It is **not** a maximum differential probability of Krakken, not a probability upper bound for an eight-round trail, and not 129 bits of security. The X/Y relation is rotational and input-dependent in XOR form; these are unrestricted constructed states, not the 21 H159 fixed-difference experiments.

### Evidence

The supplied second campaign has 131,072 pairs per family A and B. Both have 131,072/131,072 full test successes at R2, and zero full successes at R1 or R3–R8. At later rounds the mean supported-byte count returns to approximately the reference `128*127/256=63.5`; the independent-state null gives 63.461975 and no full successes in 16,384 trials.

The independent local replay used 256 pairs per family and reproduced all R2 successes and no full successes at other depths. Its 512 explicit original-C R2 comparisons and 896 startup checks passed. These checks corroborate the construction; the algebra supplies the universal eligible-family claim.

[Attack source](reproduce/exchange_bundle_v5_20261118/earlier_archives/krakken_attack_research_bundle_v4/krakken_rotational_chi_ddt_attack.c); [saved evidence](reproduce/exchange_bundle_v5_20261118/earlier_archives/krakken_attack_research_bundle_v4/krakken_rotational_chi_ddt_results.jsonl); [fresh replay](reproduce/exchange_bundle_v5_20261118/replay/rotational_chi_ddt_gcc_256.jsonl).

The earlier direct rotational-signature experiment remains an empirical one-round test: a fixed 32-bit signature succeeds 262,143/262,144 times, with one recorded failure. It is **not** a deterministic 32-bit invariant. The later carry-controlled construction obtains a different, full first-round relation by restricting inputs.

## 6. REBOUND-MODEL-001 — what the four-round audit establishes

The supplied ledger attributes a historical four-round claim to a legacy eight-byte S-box/MDS solver model. Its recreated model connects **four stand-alone S-box-to-MDS stages**, omitting the actual Theta, Rho, Pi, serial Chi coupling, XRBD, Pressure carries, constants, Ink, and full-state consistency conditions. A satisfying trail in that model is not automatically a characteristic of the actual Krakken permutation.

The supplied exact finite reproducer finds a DDT-compatible sparse-endpoint surrogate trail after 120 seeded attempts. It verifies all 32 bytewise DDT memberships and all four MDS maps. The product of local fractions is `2^-175`, explicitly only a naive Markov-style product for this surrogate. It is **not** a verified probability even for a fixed unkeyed iterated surrogate without a state-consistency/counting argument, and is not a full-permutation security exponent.

The local Chi switch with input difference `(01,01)` and output modification `(00,05)` has, among 65,536 two-byte bases:

| Condition | Bases | Fraction |
|---|---:|---:|
| Closure including swaps | 1,536 | 6/256 |
| Degenerate two-state swaps | 512 | 2/256 |
| Four distinct states and closure | 1,024 | **1/64** |

The independent audit reproduced this exact split. The BCT's 6/256 must not be advertised as the probability of a four-distinct-state quartet.

### Actual full-permutation controls

A middle-selected second-round Chi quartet experiment constructs 16,384 nondegenerate quartets after 1,048,223 local candidate draws. Its ordinary round-two output quartet has mean XOR weight 297.06, but the ordinary round-three and round-four means are 1023.86 and 1024.01. It records no full zero-XOR quartets at R4. External input differences vary with the selected middle state, so this is an outbound diagnostic, not a fixed-external-difference four-round distinguisher. Its ideal-oracle comparison must account for input selection and preprocessing.

A separate conventional fixed-alpha/fixed-beta boomerang experiment uses four precommitted ordinary-output masks and 16,384 trials per depth and mask. Two masks give **64** and **37** nondegenerate R1 closures; the other two give none. All four masks give zero full closures at R2–R8. The counts 64/16,384 and 37/16,384 are sample frequencies, not exact analytic transition probabilities.

The correct conclusion is: **a surrogate four-stage trail is reproduced; a four-round full-permutation rebound distinguisher is not reproduced by these tests**. This is not an exclusion of all four-round rebound attacks. The older code revision/remote history is described as supplied provenance; no independent remote-repository audit was performed during this import.

[Surrogate witness and source](reproduce/exchange_bundle_v5_20261118/earlier_archives/krakken_attack_research_bundle_v4/krakken_rebound_4round_surrogate_results.jsonl); [fixed-mask evidence](reproduce/exchange_bundle_v5_20261118/earlier_archives/krakken_attack_research_bundle_v4/krakken_rebound_fixedmask_results.jsonl); [middle-state evidence](reproduce/exchange_bundle_v5_20261118/earlier_archives/krakken_attack_research_bundle_v4/krakken_rebound_4round_results.jsonl).

## 7. Other useful preserved experiments

### Sparse Chi and public-tail differential test

An unrestricted difference obtained by applying L inverse to a single first-branch pre-Chi byte forces exactly two post-Chi output bytes for every base. Undoing the public post-Chi tail of an R1 output exposes this condition. The supplied sample has 8,192/8,192 successes, with no corresponding R2 success in that probe. For an ideal permutation the probability that a fixed bijective tail transform gives a nonzero difference with at most two nonzero bytes is exactly

```text
[256*255 + C(256,2)*255^2]/(2^2048-1), approximately 2^-2017.017.
```

This is a reduced-round permutation distinguisher using unrestricted inputs; the inverse-prefix difference need not be hash-reachable. Its simple local mechanism overlaps existing Chi/rebound analysis. Hamming-weight screens over rounds 2–8 are finite non-detections, not hull bounds.

### First-branch 256-point integral

Vary one first-branch pre-Chi byte over all 256 values and map the structure through L inverse. Both changing post-Chi output bytes are permutations of the variable byte, so their full-state XOR is zero. XRBD preserves the zero sum, and the Pressure LSB argument gives the same 32 complete-R1 parity bits. This proves an unrestricted 256-query one-round integral for every base. It does not apply automatically to every second-branch variable byte or to valid H159 messages.

The supplied 1,024 structures all pass the R1 32-bit projection; none passes it at R2–R8. A 256-position exploratory scan and a fresh validation of selected position 30 also found no continuation under the measured statistics. The 433 coordinate bits always zero in one R1 sample are an empirical intersection, not 433 proved invariants.

### Linear and rotational controls

The exact byte LAT maximum is 32, giving correlation magnitude 1/8, with examples input mask 01 and output masks 51, 78, AB having signed sum -32. The supplied three-mask tests at 262,144 samples match this after R1 tail peeling and show no significant retained selected correlation at R2–R8. Since the output preprocessing includes nonlinear Pressure inversion, these are **peeled-output** linear tests, not ordinary linear masks on raw permutation outputs.

Byte-aligned common word rotations commute through L, Chi, and XRBD, with Pressure and constants breaking the unrestricted full-round equality. The supplied uncontrolled R1 32-bit rotational signature has one held-out failure at trial 162870 (component 17, lane 17 bit 60). This counterexample must remain visible whenever describing its near-perfect empirical success.

The isolated Tentacle 8x8 byte matrix has branch number nine: all **12,869 square minors** are nonsingular. This was rechecked in the fresh exhaustive local script. It is an isolated byte-slice result, not the complete permutation's branch number or a global active-S-box bound.

## 8. Consequences for the probability-bound research

These additions expose useful reduced-round structure and provide better controlled adversarial tests. They do **not** close the multiround endpoint-counting problem from Research 12:

- The exchange square counts a quartet parity, not a pairwise fixed-difference endpoint.
- The carry-controlled construction proves a related-input test succeeds; its ideal false-positive probability is not an upper bound on Krakken's fixed-difference DP.
- Neither unrestricted construction is automatically reachable from the uniform H159 base populations, including the 21 `A1=5` families.
- Later-round failure of selected tests does not bound untested trails, hull aggregation, or hidden small biases.

The constructions are useful as regression controls for any future endpoint counter: it should reproduce the proved R1 square relations and R2 related-input support constraints under their correct populations. A legitimate next probability theorem still needs an explicitly named input difference/base distribution and a certified bound on a complete-round output projection or endpoint fiber. None is inferred by multiplying local DDT values or by interpreting negative screens as universal resistance.

## 9. Reproduction

Use the [package README](reproduce/exchange_bundle_v5_20261118/README.md) for the focused commands and the original full-run commands. `archive/` and `earlier_archives/` preserve evidence; `replay/` is the writable combined source directory. The supplied helper programs include one another, so the older dependencies are necessary even for v5. Python standard library, GCC/Clang, pthreads, and libm suffice for the verification performed here. The optional supplied report formatter uses SciPy; it is not required to run the attacks or the independent audit.

## 10. Complete performed-attack and control inventory

This section corrects the initial summary's incomplete visibility of the campaigns. **All five related attack bundles were checked**, not just v5's new section. The standalone `ATTACKS(4).md` is preserved as [ATTACKS_download_copy.md](reproduce/exchange_bundle_v5_20261118/ATTACKS_download_copy.md). It is byte-identical to v5 `ATTACKS.md`. Comparing every earlier ledger body against v5 finds no deleted or replaced body material; later versions add sections and some earlier titles differ.

The [complete artifact/record inventory](reproduce/exchange_bundle_v5_20261118/ATTACK_COVERAGE.md) links **all 16 distinct supplied aggregate JSONL datasets** to their programs and identifies every record by line, family, mask, rotation, sample size, and depth where applicable. The [machine-readable coverage check](reproduce/exchange_bundle_v5_20261118/ATTACK_COVERAGE.json) is reproducible with `build_attack_coverage.py`; it rejects an unmapped supplied dataset or conflicting same-named source/data versions. No statistical attack run is repeated by that inventory.

Rows below are separate performed experiments, controls, or component checks—not a count of disjoint attack families. All negative results have the finite scopes stated in the original ledger.

| ATTACKS section | Performed experiment or control | Population and result retained |
|---|---|---|
| 2 | Direct input-bit pilot search | All 2,048 bit positions, eight pairs each; selects bit 805. Exploratory selection, not confirmation. |
| 2, 4 | Inverse-prefix pre-Chi bit pilot search | All 2,048 target positions, eight pairs each; separate selected engineered difference. |
| 3 | Complete Abyssal DDT enumeration | 255 nonzero rows: 32,895 zeros, 32,130 twos, 255 fours. Existing component property independently enumerated. |
| 4–5 | Ordinary bit-0 differential confirmation | 65,536 fresh unrestricted base pairs through R1–R8. |
| 4–5 | Pilot-selected ordinary-bit confirmation | Bit 805, 65,536 fresh pairs through R1–R8; distinct from the pilot. |
| 4–5 | Engineered first-branch differential | Pre-Chi word 0 bit 0; 65,536 pairs, exactly two post-Chi R1 bytes; dense external difference has 159 bits in 40 bytes. |
| 4–5 | Engineered second-branch differential | Pre-Chi word 4 byte difference 02; 65,536 pairs; 518 R1 one-byte post-Chi cases, compared with the exact local 1/128 cancellation probability. |
| 4–5 | Pilot-selected engineered confirmation | 65,536 fresh pairs; external difference has 159 bits in 40 bytes. |
| 5 | Layer-by-layer traces | Three differences—ordinary bit 0 and both engineered branches—at 2,048 pairs each, all eight rounds, all recorded layer checkpoints. |
| 6 | First-branch black-box tail-peeling test | 8,192/8,192 R1 outcomes have at most two peeled active bytes; 0/8,192 at R2. |
| 6 | Second-branch black-box tail-peeling test | Same R1/R2 totals; 70/8,192 R1 outcomes have only one peeled active byte. Separate sample from the 518/65,536 count. |
| 5–6 | Raw-output Hamming-weight classifier | `HW<900` holds for 65,105/65,536 first-branch R1 pairs, with no hits at R2–R8. It does not peel outputs. |
| 6A | Later-round sparse-pattern reappearance audit | Minimum post-Chi byte activities for all three engineered differences through R8; later tail-test failures inferred from recorded states and the validated inverse, not a new direct black-box run. |
| 7 | Output-bit frequency screens | All 2,048 bits for each of five differences and eight depths; no flagged later-round bit under the specified within-test threshold. |
| 10.1 | Exact Abyssal LAT | Maximum nontrivial magnitude 32; 1,275 maximizing nonzero mask pairs. Component result, not a multiround piling-up bound. |
| 10.2 | Three peeled-output linear tests | Input mask 01 and output masks 51, 78, AB; 262,144 states per mask through eight depths. R1 correlation agrees with -1/8; no retained selected R2–R8 signal. |
| 10.2 | Raw bit-11 linear controls | Ordinary output bit 11 measured alongside the peeled tests. These are distinct from the nonlinear output-preprocessed statistics. |
| 10.3–10.4 | First-branch 256-value integral, position 0 | 1,024 structures of 256 unrestricted inputs; 32 proved raw R1 parity checks, all structures pass; zero passes at R2–R8. |
| 10.5 | All-256-pre-Chi-position integral search | One 256-input structure at each position; 208 R1 positions have raw XOR weight below 900, zero positions at later depths in this screen. |
| 10.5 | Fresh confirmation of selected position 30 | 1,024 fresh 256-input structures; R2 raw mean 1023.87; zero R2 32-bit passes. Pilot selection is not reused as confirmation evidence. |
| 11.1 | Exact byte-rotation commutation checks | 1,344 stage/checkpoint comparisons; algebraic commutation before Pressure for all seven nonzero byte-aligned rotations. |
| 11.2 | Ten unrestricted rotational tests | k=1,7,8,16,24,32,40,48,56,63; 65,536 pairs per k, all depths. Includes raw and deconstant outputs, stage errors, and bit screens. |
| 11.3 | Four-rotation bit-probe discovery run | k=8,16,32,56; 65,536 pairs each. Finds 439/234/4/469 sample-stable R1 positions, respectively; these are not universal invariants. |
| 11.3 | Held-out fixed 32-bit rotational signature | Independent 262,144-pair stream: 262,143 R1 successes, one material failure, no full signature successes at R2–R8. |
| 11.4 | Complete byte BCT and local Chi-superbox switch | Exact BCT maximum six; all 65,536 superbox bases give 1,536 closures for the chosen switch. Includes 256 original-C Chi validation states. |
| 11.5 | Conjugated internal-tail boomerang bridge | 65,536 pairs/depth: 1,542 R1 closures, zero at R2–R8. Output perturbation is state-dependent; not a standard fixed-output-mask boomerang. |
| 11.6 | Exhaustive isolated MDS minor test | All 12,869 square minors nonsingular; isolated byte branch number nine. |
| 12.2 | Carry-controlled rotational family A | 262,144 pairs, all eight prefixes; exact full R1 affine rotational relation. Also preserved in a separate 16,384-pair pilot. |
| 12.2 | Carry-controlled rotational family B | Same sizes/depths, exact acceptance gate and R1 relation; separate from family A. |
| 12.2 | Wider carry-controlled family C pilot | 16,384 pairs, exact rejection gate; about 4,099.626 draws per accepted column. This slower pilot is preserved in v3. |
| 12.3–12.4 | Two-round rotational/DDT-support attack | Families A and B, 131,072 pairs each: all 128 support checks pass at R2, zero full passes at other depths. Separate 8,192-pair-per-family pilot is also preserved. |
| 12.4 | Independent-state DDT null | 16,384 pairs, mean 63.461975 supported bytes out of 128; zero full passes. |
| 13.1–13.2 | Legacy four-stage S-box/MDS surrogate search | DDT-compatible witness after 120 attempts; every local support and MDS relation checked. Not a complete Krakken trail. |
| 13.3 | Degenerate versus four-distinct local quartet enumeration | 1,536 closures split into 512 swaps and 1,024 four-distinct cases. |
| 13.4 | Second-round middle-selected rebound/outbound experiment | 16,384 accepted quartets from 1,048,223 candidates; R2 mean quartet XOR weight 297.06; no validated R4 external distinguisher. |
| 13.5 | Four conventional fixed-external-mask boomerang tests | Lane0 bit0, lane4 bit32, fixed tail-derived mask, fixed seeded mask; 16,384 pairs/mask/depth; R1 counts 64,37,0,0, all later full counts zero. |
| 14.2 | H159 complementary-support direction construction | Source-exact rank/kernel calculation and explicit 159-byte A/B directions. All-base four-message R1 theorem, not just an observed sample. |
| 14.3 | H159 square initial and held-out streams | 16,384 plus 32,768 valid-message structures; all R1 parity checks pass; all later raw statistics retained separately. |
| 14.4 | Forward unrestricted exchange, one cell | 16,384 plus 32,768 four-state structures through every depth; guaranteed R1 32-bit parity relation. |
| 14.4 | Forward unrestricted exchange, four cells | Same sizes, selected cells {0,5,10,15}; distinct exchange pattern. |
| 14.4 | Forward unrestricted exchange, eight cells | Same sizes, even-indexed cells; distinct exchange pattern. |
| 14.4 | Inverse-oracle Yoyo, one/four/eight cells | Three separate patterns, each with 16,384 initial and 32,768 held-out trials; exact R1 zero defect, no observed full closure at later depths. |
| 2, 10.6–14.1 | Source/inverse/encoding controls | Reference-versus-accelerated comparisons, inverse-prefix/tail checks, crafted actual-C R2 checks, target-byte checks, and H159 hash-API checks. These validate implementations; they are not additional attack families. |

The proposed directions in sections 8, 11.7, 12.6 and 13.6 of `ATTACKS.md` are **future work**, not performed attacks. The inventory deliberately does not turn those proposals into results.

### Where duplication was intentionally avoided

The DDT/LAT/BCT component properties, isolated MDS branch number, local Chi structure, Pressure LSB equations, and earlier 32-position integral observations overlap existing Research 01/02/11. Their earlier proofs need not be copied again. However, the **specific new campaign records** above—five differential confirmation modes, fresh mask statistics, position scans, rotational probes, and the exact choices of quartet/control—are retained as additional evidence even where the broad attack family was already studied.

The following numerical supplement makes the previously compressed differential, linear, integral, and rotational campaigns visible directly in this ledger. Full signed counts, witness differences, per-bit/per-stage statistics, and pilot data remain in the linked evidence inventory.

## 11. Additional supplied campaign measurements

These tables are transcribed programmatically from the preserved aggregate JSONL evidence by `build_campaign_tables.py`. They are supplied-run results, not newly rerun campaigns or probability certificates. Section 10 and its artifact inventory identify every program and dataset.

### 11.1 Five differential confirmation modes and sparse-pattern audit

Source: `krakken_differential_results.jsonl`. Each mode uses 65,536 fresh base pairs, separate from the eight-pair-per-candidate pilots. Entries are mean ordinary-output XOR Hamming weights out of 2,048.

| Round | Input bit 0 | Selected bit 805 | Engineered first branch | Engineered second branch | Selected engineered |
| --- | --- | --- | --- | --- | --- |
| 1 | 1023.93 | 1023.92 | 771.70 | 775.13 | 780.36 |
| 2 | 1023.95 | 1023.94 | 1024.07 | 1024.04 | 1023.89 |
| 3 | 1024.04 | 1024.04 | 1023.97 | 1023.98 | 1023.92 |
| 4 | 1023.85 | 1024.06 | 1023.97 | 1024.08 | 1023.88 |
| 5 | 1024.11 | 1023.95 | 1023.94 | 1023.86 | 1024.20 |
| 6 | 1024.00 | 1024.14 | 1023.89 | 1024.12 | 1024.07 |
| 7 | 1023.96 | 1024.02 | 1024.13 | 1024.01 | 1024.03 |
| 8 | 1024.09 | 1024.07 | 1024.05 | 1023.93 | 1024.05 |


| Round | First-branch min post-Chi bytes | Second-branch min post-Chi bytes | Selected engineered min post-Chi bytes | First-branch raw HW<900 hits |
| --- | --- | --- | --- | --- |
| 1 | 2 | 1 | 2 | 65105 |
| 2 | 249 | 249 | 248 | 0 |
| 3 | 247 | 249 | 250 | 0 |
| 4 | 249 | 249 | 249 | 0 |
| 5 | 250 | 249 | 248 | 0 |
| 6 | 248 | 248 | 249 | 0 |
| 7 | 249 | 249 | 248 | 0 |
| 8 | 249 | 248 | 249 | 0 |

The R1 second-branch one-byte count in this confirmation is 518/65,536. The separate 8,192-pair oracle probe gives 70 such cases. These are two different samples, not inconsistent estimates. Later-round sparse minima are observed minima, not mathematical lower bounds.

### 11.2 Layer trace of the three selected differential inputs

Source: the same differential dataset, 2,048 pairs per trace. The following are R1 mean XOR weights; all eight rounds of complete layer traces remain in the dataset.

| R1 checkpoint | Input bit 0 | First branch | Second branch |
| --- | --- | --- | --- |
| input_to_round | 1.00 | 159.00 | 144.00 |
| after_theta | 9.00 | 29.00 | 28.00 |
| after_mds | 146.00 | 1.00 | 1.00 |
| after_rho | 146.00 | 1.00 | 1.00 |
| after_pi | 146.00 | 1.00 | 1.00 |
| after_chi | 385.26 | 7.95 | 7.99 |
| after_butterfly | 1024.31 | 294.09 | 296.48 |
| after_pressure | 1024.48 | 769.79 | 778.27 |
| after_iota | 1024.48 | 769.79 | 778.27 |
| after_shuffle | 1024.48 | 769.79 | 778.27 |

### 11.3 Three peeled-output linear masks and raw-output controls

Source: `krakken_linear_integral_results.jsonl`, 262,144 states per selected mask. Input mask is 01; peeled output masks are 51, 78, AB. Output peeling is nonlinear, so these are not ordinary raw-output linear approximations. The final three columns retain the separate raw bit-11 controls from each stream.

| Round | Peeled 51 | Peeled 78 | Peeled AB | Raw bit11, stream 51 | Raw bit11, stream 78 | Raw bit11, stream AB |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | -0.123154 | -0.123154 | -0.125198 | +0.002106 | +0.002106 | +0.002106 |
| 2 | +0.002304 | -0.001076 | +0.001572 | -0.001869 | -0.001869 | -0.001869 |
| 3 | -0.001289 | +0.002068 | +0.000381 | -0.005417 | -0.005417 | -0.005417 |
| 4 | +0.001480 | -0.002022 | -0.002007 | -0.000023 | -0.000023 | -0.000023 |
| 5 | -0.002434 | -0.000504 | -0.001259 | -0.002556 | -0.002556 | -0.002556 |
| 6 | -0.002243 | -0.003075 | +0.003548 | +0.002678 | +0.002678 | +0.002678 |
| 7 | +0.000450 | +0.000137 | -0.000938 | -0.001694 | -0.001694 | -0.001694 |
| 8 | +0.001938 | +0.000595 | -0.002342 | -0.000755 | -0.000755 | -0.000755 |

### 11.4 Integral primary sample, exhaustive position screen, and fresh confirmation

Sources: both `integral_measure` records and `integral_all_256_positions_scan` in the linear/integral dataset. Position 0 and the fresh position-30 confirmation each use 1,024 structures of 256 inputs. The position search uses one 256-input structure for each of 256 positions.

| Round | Position0 32-bit hits /1024 | Position0 raw XOR mean | Scan mean over256 positions | Scan minimum (position) | Scan positions HW<900 | Fresh position30 raw mean | Fresh position30 32-bit hits /1024 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | 1024 | 428.40 | 782.65 | 382 (2) | 208 | 750.82 | 1024 |
| 2 | 0 | 1024.60 | 1023.88 | 960 (30) | 0 | 1023.87 | 0 |
| 3 | 0 | 1024.24 | 1024.18 | 967 (88) | 0 | 1024.86 | 0 |
| 4 | 0 | 1023.70 | 1025.59 | 966 (52) | 0 | 1023.76 | 0 |
| 5 | 0 | 1023.53 | 1023.93 | 968 (219) | 0 | 1023.08 | 0 |
| 6 | 0 | 1022.76 | 1023.57 | 958 (192) | 0 | 1023.33 | 0 |
| 7 | 0 | 1024.05 | 1024.76 | 968 (5) | 0 | 1024.19 | 0 |
| 8 | 0 | 1024.00 | 1023.21 | 968 (93) | 0 | 1023.56 | 0 |

The selected position-30 R2 pilot minimum was 960; the fresh R2 mean returns to 1023.87. Selecting that pilot minimum is not evidence of a persistent bias. Only the correctly scoped first-branch algebra proves the 32-bit integral; a sample-stable extra coordinate is not automatically an invariant.

### 11.5 Ten rotational tests, negative controls, and discovery probes

Source: `krakken_rotational_results.jsonl`, 65,536 pairs per rotation. Deconstant means undoing the known final Ink/constants for the rotational comparison; it is not the same statistic as raw output weight. The final column sums flagged raw bit positions across R2–R8 under the supplied screens.

| Rotation k | R1 raw mean | R1 deconstant mean | R1 raw flagged bits | R2–R8 flagged bits, summed |
| --- | --- | --- | --- | --- |
| 1 | 1024.076 | 1023.986 | 0 | 0 |
| 7 | 1023.972 | 1024.115 | 0 | 0 |
| 8 | 1005.578 | 414.752 | 1376 | 0 |
| 16 | 1019.461 | 693.943 | 736 | 0 |
| 24 | 1035.038 | 786.285 | 544 | 0 |
| 32 | 1032.382 | 816.026 | 448 | 0 |
| 40 | 1035.053 | 786.326 | 544 | 0 |
| 48 | 1019.351 | 694.126 | 736 | 0 |
| 56 | 1005.710 | 414.840 | 1376 | 0 |
| 63 | 1024.083 | 1023.973 | 0 | 0 |


| Discovery rotation | Pairs | Sample-stable R1 positions |
| --- | --- | --- |
| 8 | 65536 | 439 |
| 16 | 65536 | 234 |
| 32 | 65536 | 4 |
| 56 | 65536 | 469 |

The discovery streams select candidate bits; the following held-out stream separately tests one fixed signature. A candidate position being stable in a pilot is not an all-base proof.

| Round | Fixed-signature hits /262144 | Total signature bit errors | Raw rotational mean |
| --- | --- | --- | --- |
| 1 | 262143 | 1 | 1005.606 |
| 2 | 0 | 4196284 | 1024.007 |
| 3 | 0 | 4195731 | 1024.016 |
| 4 | 0 | 4195687 | 1023.986 |
| 5 | 0 | 4194902 | 1024.000 |
| 6 | 0 | 4194302 | 1024.011 |
| 7 | 0 | 4195856 | 1024.106 |
| 8 | 0 | 4192789 | 1023.979 |

The single R1 failure at trial 162870 remains part of the evidence; the signature must not be called deterministic.

### 11.6 Carry-controlled populations, including the slower family-C pilot

Sources: `krakken_rotational_carry_results.jsonl` and the v3 `krakken_rotational_carry_pilot.jsonl`. The main A/B streams and the earlier A/B/C pilots are separate records. The equality here is the constructed full-state R1 affine rotational relation.

| Stream | Family | Pairs | Draws per accepted column | Exact R1 matches | R2 raw rotational-error mean |
| --- | --- | --- | --- | --- | --- |
| main | A | 262144 | 1.000000 | 262144 | 1023.998 |
| main | B | 262144 | 1.000000 | 262144 | 1023.930 |
| pilot | A | 16384 | 1.000000 | 16384 | 1023.816 |
| pilot | B | 16384 | 1.000000 | 16384 | 1023.996 |
| pilot | C | 16384 | 4099.626045 | 16384 | 1024.017 |

The separate second-round DDT test—not these raw means—finds the exact R2 structure. Its earlier 8,192-pair A/B pilot, later 131,072-pair A/B confirmation, and independent-state null are all separately indexed in ATTACK_COVERAGE.md.

### 11.7 Four fixed-external-mask boomerang controls

Source: `krakken_rebound_fixedmask_results.jsonl`. There are 16,384 trials per mask at each depth. These are conventional fixed-external-mask tests; they differ from the conjugated internal-tail bridge and the middle-selected outbound experiment.

| Round | output_lane0_bit0 | output_lane4_bit32 | fwd_tail_zero_reference_chi_byte_delta | fixed_seeded_multiword_mask |
| --- | --- | --- | --- | --- |
| 1 | 64 | 37 | 0 | 0 |
| 2 | 0 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 |
| 4 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 0 |
| 6 | 0 | 0 | 0 | 0 |
| 7 | 0 | 0 | 0 | 0 |
| 8 | 0 | 0 | 0 | 0 |

The nonzero R1 closures exclude degenerate swaps. The 64/16,384 sample frequency equals 1/256 numerically; no exact 1/256 transition theorem is inferred. The internal-middle and four-stage surrogate experiments remain separate, with the limitations in section 6.

This supplement records all these attack variants without treating related controls as independent security assurances. Every additional per-round statistic and witness remains preserved in the complete artifact inventory.

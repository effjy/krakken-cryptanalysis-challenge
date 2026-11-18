# Krakken research 12 — XRBD structure, conditional round-two activity, and Pressure compatibility

Date: 2026-11-18. Scope: the original scalar `krakken.c` / `krakken.h`.

This ledger imports the important additions from the three supplied XRBD studies. All five distinct supplied verification/exploration scripts were executed successfully in separate working copies. Their five generated JSON results match the supplied results **byte for byte**. The statements below distinguish mathematical arguments, exhaustive finite computations, and observations. This is a reproducible research record, not a formal proof-assistant certificate or a certification of overall cryptographic security.

## 1. What changes in our bounds

Write `Ar` for the number of active **byte S-box calls** in round r. Word activity, occupied byte positions, and active S-box calls are different quantities.

| Domain / condition | Recorded activity lower bound | Status |
|---|---:|---|
| General unrestricted eight-round differences | 16 | Existing result, unchanged |
| General H159 eight-round differences | 20 | Existing result, unchanged |
| H159 with A1 = 5 | A2 >= 5; first two rounds >= 10; eight rounds >= 22 | Existing result, unchanged |
| R1 output difference supported on words 0 and 14, both with bit 11 set | **A2 >= 31** | New conditional theorem, all qualifying base pairs |
| Explicit unrestricted fixed-input-difference subevent from Study 01 | **A1 + A2 >= 39; eight rounds >= 51** | New conditional corollaries |

The explicit subevent has probability exactly `2^-48` under a uniform unrestricted initial base state. Its input difference has nonzero capacity bytes and is **not H159**. The 51-call result must therefore not replace the general 16/20/22 results. Neither 31 nor 51 is a claim of an attained minimum or a security level in bits. No independence of consecutive rounds or Pressure carries is assumed in these activity theorems.

## 2. Preserved evidence and source identity

Everything supplied is preserved under [reproduce/xrbd_studies_20261118/](reproduce/xrbd_studies_20261118/README.md), including the three original ZIPs and standalone studies. `archive/` holds their extracted original contents; `replay/` holds separate executable copies and fresh logs.

- [Study 01: structure and one-round event](reproduce/xrbd_studies_20261118/KRAKKEN_XRBD_STUDY_01.md).
- [Study 02: conditional round-two theorem](reproduce/xrbd_studies_20261118/KRAKKEN_XRBD_STUDY_02.md).
- [Study 03: Pressure arithmetic compatibility](reproduce/xrbd_studies_20261118/KRAKKEN_XRBD_STUDY_03.md).
- [Import hashes](reproduce/xrbd_studies_20261118/IMPORT_MANIFEST.json), [embedded-manifest checks](reproduce/xrbd_studies_20261118/MANIFEST_CHECKS.json), and [fresh replay comparisons](reproduce/xrbd_studies_20261118/REPLAY_CHECKS.json).

All ZIP CRC checks and embedded file-hash manifests passed. The three standalone studies equal their archived versions. Every bundled C/H copy equals the current project original byte for byte:

```text
krakken.c  4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6
krakken.h  83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c
```

Both GCC and Clang were available and exercised. The two copies of `verify_round2.py` in Studies 02 and 03 are byte-identical; that checker was executed once, from Study 02. No old campaign was rerun. Matching checksums establish evidence identity; validity also depends on the arguments and checker correctness described below.

## 3. Exact standalone XRBD structure

Use zero-based word indices, `F = 2^64 - 1`, and `R = ROL1`. XRBD has five stages with distances 1, 2, 4, 8, 16 and rotations 13, 23, 37, 41, 53. Each pair transforms as

```text
(a,b) -> (a XOR b, b XOR ROL_r(a XOR b)).
```

Each stage is invertible. For output `(u,v)`, recover `b = v XOR ROL_r(u)`, then `a = u XOR b`.

### XRBD-01: unique one-word to one-word transition

Among all nonzero one-word input differences, the only ones producing a one-word XRBD output are:

```text
input word 31 = F  ->  output word 0 = F,
all other words zero.
```

The constrained kernel for that input/output support pair has dimension one. All other 1,023 source/target word pairs have trivial kernels. Thus the standalone XOR-linear XRBD **word branch number is 2**.

Proof outline: the five stages address distinct index bits, so paths from a single source never reconverge. A source `s` has `2^(5-popcount(s))` unavoidable outputs obtained using only invertible rotations/identities. Unless `s=31`, this already exceeds one. At source 31, output 0 is the source word `x`, while the five outputs with a single index bit set contain `(I XOR ROL_r)x`. For odd r, only 0 and F are fixed by `ROL_r`; suppressing these outputs forces `x=F`. This value suppresses every other nonzero target index as well.

This is a structural limitation of the isolated layer. It does not assert that a one-byte difference has poor diffusion, that the complete round has branch number 2, or that this pattern is reachable from an H159 input.

### XRBD-02: exact single-source activity formula

Let `D = I XOR R` and, for nonzero x, define `nu(x)` as the least positive k for which `D^k x=0`. Since `D^64=0`, `1 <= nu(x) <= 64`.

For each odd rotation r, `I XOR R^r` is D times a unit in the ring `GF(2)[R]/((R+1)^64)`. For source s and target t, let `h=popcount(s AND t)`. The corresponding word is nonzero exactly when `h < nu(x)`: the unique path contributes h such factors, multiplied by invertible commuting factors. Therefore, for `w=popcount(s)`, the exact number of active output words is

```text
W(s,x) = 2^(5-w) * sum(C(w,h), h=0..min(w,nu(x)-1)).
```

The minimum for a fixed source is `2^(5-w)`, attained by x=F. Source weights 0 through 5 give minima 32, 16, 8, 4, 2, 1 respectively. For source 31 the possible counts are exactly 1, 6, 16, 26, 31, 32. Every one of the 2,048 single-bit basis inputs has 32 active output words, consistently with this formula; that observation does not extend to arbitrary full-word differences.

### XRBD-03: invariant subspaces and order three

The 32-dimensional subspace in which each word is either 0 or F is invariant. On its word-indicator bits, each stage uses

```text
M = [[1,1],[1,0]],  T = M tensor M tensor M tensor M tensor M.
T[t,s] = 1 iff (t AND s) == 0.
```

Over GF(2), `M^3=I`, so `T^3=I`. Exact elimination gives a fixed space of dimension 10: 1,024 fixed states; every remaining state of this subspace has period three. These are statements about repeated **standalone XRBD**, not complete Krakken rounds. More generally, for every d dividing 64, the subspace where each word has bit period dividing d is invariant and has dimension `32*d`.

Fresh checks include all 1,024 constrained support pairs, 2,048 original-C basis comparisons per compiler, constant-word controls, periodic-subspace bases, and 256 suffix base pairs per compiler. See [RESULTS.json](reproduce/xrbd_studies_20261118/replay/study01/RESULTS.json).

## 4. Exact one-round collapse event

### SUFFIX-01: propagation through Pressure and Ink

For **any** pair of post-Chi states differing only by F in word 31, XRBD gives F only in word 0. Pressure then yields exactly two nonzero difference words, 0 and 2. Ink sends these to words 0 and 14. Both final differences have bit 11 set.

For the affected Pressure chain, let `f(c)=c XOR (c>>17)` and `g(A)=A XOR ((A<<31) mod 2^64)`. Adding the same `f(c)` to distinct A inputs preserves distinctness, and g is bijective, so both updated words differ. Their low bits differ because the input complement changes parity and g preserves parity. Ink's rotation by 11 sends these differing bit-zero positions to bit 11. No probabilistic assumption enters this suffix statement.

### R1-TRUNC-01: fixed input difference with a probability-2^-48 internal event

Let L be the original round's invertible linear prefix before serial Chi. Fix a pre-Chi difference consisting of byte `FD` repeated in words 27 and 31, zero elsewhere; fix the actual input difference as its inverse image under L.

The first call in the affected serial-Chi pair has zero difference because the repeated-byte value is invariant under rotation by 32. All eight second-call bytes have input difference FD. The original S-box has

```text
DDT[FD,FF] = 4,
successful second-call base inputs: 00, 6C, 91, FD.
```

For a uniform unrestricted initial base, the invertible linear prefix and the invertible serial-Chi coordinate change give eight independent uniform second-call byte coordinates. The event that all eight output differences equal FF therefore has probability **exactly `(4/256)^8 = 2^-48`**. This independence is confined to this explicitly justified first-round coordinate argument; it is not an assumption across rounds.

On this event: A1=8, post-Chi difference is F at word 31 only, and the complete first-round output has exactly words 0 and 14 active, both with bit 11 set. The final truncated support event consequently has probability **at least** `2^-48`; the proof does not exclude other ways to obtain that support.

For comparison, a uniform ideal 2048-bit permutation, at any fixed nonzero input difference, gives exactly this prescribed two-word output support with probability `(2^64-1)^2/(2^2048-1)`, approximately `2^-1920`. Thus this is substantial nonideal **one-round** structure. It is neither an eight-round distinguisher nor a hash collision construction.

The saved [ONE_ROUND_EVENT.json](reproduce/xrbd_studies_20261118/replay/study01/ONE_ROUND_EVENT.json) contains actual full initial-state witnesses and the fixed input difference. Original indexed-round APIs reproduced them with GCC and Clang. The difference has nonzero capacity coordinates, so this event does not establish an H159 transition.

## 5. Solver-free conditional theorem: A2 >= 31

**Theorem R2-COND-31.** For every pair whose complete first-round output difference is zero outside words 0 and 14 and has bit 11 set in each of those two words, the second round has at least 31 active byte S-box calls.

The proof deliberately allows arbitrary two-word values `(u,v)` satisfying the two bit constraints. It relaxes other Pressure compatibility constraints. Its 128 formal input coordinates form a 126-dimensional affine class after fixing the two bits. The original next-round linear prefix has rank 128 on the underlying two-word linear space.

Partition the next Chi input into its 16 paired-word cells and their eight aligned byte positions. For input word differences `(da,db)`, align the second word by `ROL32`: position k is occupied when `(da[k], ROL32(db)[k]) != (0,0)`. Each occupied position forces at least one active serial-Chi byte call: either `da[k] XOR ROL32(db)[k]` is nonzero at the first call, or its cancellation leaves a nonzero second-call difference at the corresponding rotated byte position. The byte correspondence is a permutation, so these assigned calls are distinct across occupied positions. Hence the occupied-position count N is a lower bound on A2.

A paired-word cell is light when it has at most one occupied byte position. The exhaustive proof splits as follows:

1. **At least two light cells:** choose the two cells and their potentially occupied byte positions. This gives `C(16,2)*8*8 = 7,680` cases, including empty cells. Each imposes 224 homogeneous zero-bit equations on the 128 input coordinates. There are 6,968 full-rank exclusions and 712 deficient kernels, maximum dimension 13. Of these patterns, 148 admit the two fixed bit-11 constraints. Exhaustive enumeration gives 35,858 admissible vectors, counted with overlaps, and every one has **N >= 37**. Each kernel generator is checked against its equations; deficient ranks are independently recomputed with the opposite pivot order.
2. **No light cell:** all 16 cells have at least two occupied positions, so N >= 32.
3. **Exactly one light cell, occupied:** N >= 1 + 15*2 = 31.
4. **Exactly one light cell, empty:** the simple count alone would allow 30. This gap is explicitly closed by enumerating all 16 completely inactive-cell kernels (maximum dimension 8). Every admissible vector has **N >= 80**.

Thus N >= 31 throughout the stated class, with no base-state or independence hypothesis. This is not a proof that 31 is attainable.

An additional rank result holds for every nonzero difference supported on words 0 and 14, even without the fixed bit constraints: at least **13 of the 16 first-call input words** are nonzero. Of 560 choices of three zero words, 545 have rank 128 and 15 rank 127; all 1,820 choices of four zero words have rank 128. This is a word-level auxiliary statement, not a 13-byte exact minimum.

Both compilers reproduced the entire 128-column prefix basis and 32 additional controls. The actual first-round witness has N=128 and A2=255. Full finite proof counts and kernels are reproducible from [verify_round2.py](reproduce/xrbd_studies_20261118/archive/study02/verify_round2.py); fresh output is [RESULTS_ROUND2.json](reproduce/xrbd_studies_20261118/replay/study02/RESULTS_ROUND2.json).

### Composition

On the explicit first-round subevent, A1=8, so A1+A2 >= 39. Applying the existing unrestricted adjacent-round floor of four active calls separately to rounds (3,4), (5,6), and (7,8) gives

```text
A1 + ... + A8 >= 39 + 4 + 4 + 4 = 51.
```

This uses deterministic activity inequalities on disjoint windows, not multiplication of differential probabilities. It inherits the existing adjacent-round result as a premise; the new checker verifies the new first-window bound rather than reproving the old premise. Neither this count nor a naive power of the maximum DDT probability is asserted to bound full differential hulls or hash security.

## 6. New exact Pressure compatibility information

Study 03 examines the Pressure input difference F at word 0 only. Let initial chain words be a and c, and define

```text
A0 = a + f(c),             A1 = (a XOR F) + f(c)
C0 = c + g(A0),            C1 = c + g(A1)
DA = A0 XOR A1,            DC = C0 XOR C1,
```

with additions modulo 2^64. Both DA and DC are odd, and Ink gives `u=ROL11(DA)`, `v=ROL11(DC)`.

### PRESS-CARRY-01: exact low-bit reachability

For **1 <= k <= 17**, the low k bits of c and `f(c)` can be assigned independently: choose

```text
c = c_low OR ((t_low XOR c_low) << 17).
```

The two assigned ranges do not overlap. Also, A0 and A1 can realize any desired opposite-parity k-bit values: solve `2*t = A0 + A1 + 1 (mod 2^k)`, then `a=A0-t`. Since k<31, g is the identity on the low k bits. Consequently, exactly the same low-k profiles `(DA,DC)` are reachable as for XOR differences through addition of a common arbitrary k-bit addend, with DA odd.

A four-state automaton tracks the two addition carries, initially `(0,0)`. At each bit, it enumerates the base input bit and common-addend bit, checks the required output difference bit, and updates both carries. This is an exact reachability procedure, not an independent-carry approximation. Every allowed profile lifts to a real full-width standalone Pressure pair by the construction above.

| k | Reachable odd/odd low-k profiles |
|---:|---:|
| 1 | 1 |
| 2 | 4 |
| 3 | 14 |
| 4 | 48 |
| 5 | 164 |
| 6 | 560 |
| 7 | 1,912 |
| 8 | 6,528 |
| 9 | 22,288 |
| 10 | 76,096 |

There are `2^(2*k-2)` nominal odd/odd profiles. At k=10, only about 29.03% are reachable. At k=3, the only forbidden profiles are (1,5) and (5,1). All 14 allowed profiles have supplied 64-bit witnesses; both compilers replayed them. Direct enumeration of `(a,t,c)` for widths 1 through 5 agrees with the automaton's **sets**, not just the counts.

The exact characterization is justified through k=17; the supplied count computation runs through k=10. The independence construction is not justified above k=17. Standalone Pressure reachability does not itself prove reachability within the particular fixed-input-difference event of Section 4.

### PRESS-CARRY-02: full-width sparse exclusions when DA=1

When DA=1, the g-output XOR difference is `1 OR 2^31`. Its ordinary modular difference must therefore belong to `{+1+2^31, +1-2^31, -1+2^31, -1-2^31}` modulo 2^64. Adding the same c preserves this modular difference.

For any candidate DC with support J, the corresponding ordinary difference must be expressible as `sum(sign_j * 2^j, j in J)` modulo 2^64, each sign being plus or minus. Intersecting these necessary possibilities gives:

- DC=1 is impossible.
- If DC has Hamming weight at most two, then **DC = 0x0000000080000001** is the only possibility.
- If all DC bits 31 through 63 are zero, then necessarily **DC = 0x000000007fffffff**: the largest possible signed low-31-bit magnitude is `2^31-1`, attained only using every such bit with the same sign.

The sparse possibility is attained by the standalone Pressure pair with a=0 and c=2^17. Candidate next-round occupancy counts illustrate why arithmetic filtering matters:

| DA | DC | N after Ink and the next linear prefix | Compatibility |
|---|---|---:|---|
| 1 | 1 | 35 | Impossible |
| 1 | 1 OR 2^63 | 37 | Impossible |
| 1 | 1 OR 2^31 | 60 | Actual standalone Pressure witness |

These examples **do not prove A2 >= 60**, nor improve the proven 31. The compatible witness is not certified reachable inside the specific first-round subevent. Fresh GCC and Clang checks each replayed 145 actual Pressure/Ink input pairs. See [PRESSURE_COMPATIBILITY_RESULTS.json](reproduce/xrbd_studies_20261118/replay/study03/PRESSURE_COMPATIBILITY_RESULTS.json).

## 7. Observations and relationship to earlier research

The deterministic 128-pair conditional experiment was also replayed. Every sampled second-round output had all 32 words active; A2 ranged from 252 to 256, with histogram `{252:1, 253:8, 254:19, 255:54, 256:46}`. This is a finite observation, not a universal lower bound or an estimate of the rarest compatible transition. See [R2_EXPLORATION.json](reproduce/xrbd_studies_20261118/replay/study01/R2_EXPLORATION.json).

Earlier research already noted the first-stage constant-word cancellation and strong diffusion for single-byte differences. The additions here are the unique **complete five-stage** collapse classification, exact nilpotency-based activity formula, invariant-space classification, full original-round collapse event, the all-base conditional round-two bound, and exact Pressure compatibility constraints. The eight-byte F difference does not contradict the previous one-byte diffusion theorem. Likewise, a single word at the round input is a different boundary from a single word at the XRBD input after Chi.

The next useful direction suggested by these results is to incorporate the exact carry automaton and full-width modular exclusions into the two-word activity analysis. That would seek a stronger conditional bound while retaining realizability checks. This import does not launch that new campaign or claim that it will improve the general H159 bound.

## 8. Reproduction

See the [reproduction README](reproduce/xrbd_studies_20261118/README.md) for isolated commands and exact evidence layout. The supplied programs use Python standard-library arithmetic and compile the preserved scalar C with GCC and Clang. No MILP/SAT solver or year-long search is needed. The archived JSON files remain untouched; fresh matching outputs and logs are retained separately.

## 9. Reviewer follow-up: probability bounds rather than activity counts

The reviewer's central diagnosis is accepted: the activity floors above do not supply a general eight-round differential-probability bound. However, the older research already contains genuine **one-complete-round** endpoint bounds: `DIFF-RATE-008` in Research 01 proves a common ceiling `<507/512000` for every prescribed full-state R1 difference for three fixed H159 input differences. The general `2^-30` first-Chi/XRBD probability bound in `CHI-RATE-001` stops before Pressure. These stopping points and domains must remain explicit.

A new small finite audit specializes the existing `DIFF-ACT-001` activity-fiber theory to **all 21 classified minimum-first-round differences**. For each fixed difference and a uniform 159-byte base message, it verifies:

- Five jointly uniform first-call input bytes: rank 40, checked with both pivot orders.
- Exactly two favorable derivative roots at each byte, each pair an affine line.
- Therefore **Pr[A1=5] = 2^-35**, with an affine qualifying population of dimension **1,237**.
- The five paired local inputs have rank 80, giving an exact partition into `2^80` equally sized affine fibers, each with `2^1192` messages.
- All 1,272 message-bit prefix columns agree between the independent Python model and the original C under **both GCC and Clang**.

This verifies the probability setup for every explicitly listed difference without repeating the classification campaigns. It is a specialization/certificate of existing theory, not a new multiround endpoint theorem. Source copies, roots, differences, hashes, and logs are in [the probability foundation package](reproduce/probability_foundation_20261118/README.md), with [RESULTS.json](reproduce/probability_foundation_20261118/RESULTS.json).

The key warning is that bounding `Pr[output difference=beta | A1=5]` controls only a population of mass `2^-35`. Without controlling the complement, it cannot give a useful unconditional endpoint bound. Also, uniform H159 bases do not define the reviewer's uniform-full-state MDP.

The next precise target is a certified maximum point probability for a **small projection of the complete second-round output difference**, for one named fixed input difference under an explicitly chosen base distribution. Such a projected bound upper-bounds every full endpoint probability and automatically aggregates all trails. The package's reviewer note supplies exact counting, mixture, Fourier, and conditional-kernel formulas, together with the still-missing proof obligations. No new two-complete-round or eight-round endpoint probability bound has been established in this follow-up.

The exact population result is also preserved separately as [H159-POP-021: exact minimum-first-round population](reproduce/probability_foundation_20261118/H159_EXACT_POPULATION_THEOREM.md), including the affine-space proof and explicit endpoint-count denominators. Its rarity is not a search-hardness claim: qualifying messages can be constructed from the affine equations. Full-state endpoint bounds and hash-difference bounds also require distinct treatment because digest extraction merges full-state endpoints.

# NEW_BOUNDS.md — Krakken-2048 Certified Activity-Bound Corollaries

**2026-11-18 conditional update:** the new all-21-family exclusion proves **A1=5 => A2>=5** for H159 and raises that subclass's eight-round activity floor to **22**. The general H159 floor remains 20. [Research 11 and complete evidence](KRAKKEN_RESEARCH_11.md#all-family-minimum-first-round-continuation--a25-2026-11-18). Earlier 21-call conditional bounds below are superseded, without claiming an attained minimum or security bits.

**2026-11-17 current bound update:** the completed six-cell campaign closes the remaining H159 `[6,1]` case. Together with the prior four-/five-cell and activity premises, the general H159 lower bounds are now **A1+A2>=8** and **eight-round total>=20**. The A1=5 conditional floor remains 21. See [research 11's completed theorem](KRAKKEN_RESEARCH_11.md#completed-six-cell-campaign--global-h159-activity-floors-2026-11-17) and [the frozen completion audit](reproduce/sixcell_20261117/FINAL_AUDIT_at_completion.json). Older 19-call/open-[6,1] entries below are historical; no attained minimum or security-bit bound is asserted.

**Date:** 2026-11-13  
**Status:** **CERTIFIED AS ANALYTIC CONSEQUENCES OF ESTABLISHED KRAKKEN THEOREMS**  
**Scope:** The unchanged, original, indexed eight-round Krakken-2048 permutation and its exactly 159-byte padded-message (H159) first-block domain.  
**Purpose:** Settle which *provable cumulative S-box activity lower bounds* follow from the currently certified transition exclusions; distinguish those bounds from unknown *attainable minima*; identify the exact abstract patterns requiring further cryptanalysis.

**2026-11-13 continuation:** Section 13 adds `NEW-BND-005`, a **22-call eight-round lower bound for archived H159 `delta_id=1` (family 4) conditioned on `A1=5`**; it also proves that the only possible obstruction to a **global H159 20-call floor**, under the existing activity premises, is an actual `[6,1]` first-window trail. The global lower bounds remain **16 unrestricted / 19 H159 / 21 H159 conditioned on `A1=5`**; none is asserted to be attained.

> **Read this distinction first.** `sum A_r >= 16` is a certified theorem. The statement `min sum A_r = 16` is **not** certified. The latter requires a real Krakken input pair achieving 16 calls; none is provided here. Likewise, 19 and 21 are certified **lower bounds**, not exact attained minima. An *abstract admissible sequence* is an integer vector satisfying known necessary conditions—not a realizable differential characteristic.

## 1. Source and archive provenance

The reference implementation is untouched. The relevant SHA-256 fingerprints of the supplied files are:

| Source file | SHA-256 |
|---|---|
| `krakken.c` | `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` |
| `krakken.h` | `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c` |
| `Krakken(3).md` | `8dd4d5310d460e63cea05a072259895c6bc06207d26a80bafc9e1b0e56bbf0dd` |
| `KRAKKEN_SECURITY_THEOREMS_2(3).md` | `348f6976a4daaf3bf0c85600ceb8f88888902e4ab7f333bb842ef32529ebd152` |

The *current-status* entries at the top of `Krakken(3).md` and `KRAKKEN_SECURITY_THEOREMS_2(3).md` record the completed `[2,1]` campaign: **255 starting positions (000–254), 8,355,840 spatial configurations excluded, zero unresolved configurations**. Those entries supersede old narrative portions of the same archives that still speak of an unfinished campaign. The campaign's proof and saved certificates are **accepted as established premises** as directed by the researcher. This work does **not** re-run the original massive SMT/SAT campaign, recheck its complete archived proof objects, or claim a new independent machine-level audit of those objects.

Other input theorems are from the current record's **"Complete H159 minimum-activity classification and second-round bound"** and **"Broad-family, composable eight-round activity bound"** (in `Krakken(3).md`), and the established global `[1,1]`/`[1,2]` exclusions (see `DIFF-PERM-003` and supporting entries in the historic full theorem ledger).

The new mathematical deductions and their small exhaustive *combinatorial* verification are independent of any solver run. All integer bounds and counts in this document were reproduced by `verify_new_bounds.py`; the exact result table and pattern lists are in `NEW_BOUNDS_AUDIT.json`.

## 2. Definitions and accepted theorem premises

For any pair of **distinct** 2,048-bit input states, run both states through the **same original indexed** rounds `R1, ..., R8`, using the fixed original round constants. Let

`A_r = number of active byte-level Abyssal S-box calls at the Chi layer in round r`.

There are **256** byte S-box calls per round (16 serial Chi cells at the 64-bit word-pair level, each with two calls of eight bytes), so the activity is integer-valued and lies in `0..256`. Because every layer and every full round is bijective, distinct initial states remain distinct at each pre-Chi checkpoint. The Chi layer is itself bijective. Consequently, **at least one** S-box call must be active for every such pair in every round:

**U1.** `1 <= A_r <= 256` for all `r = 1..8`.

The established universal adjacent-round exclusions impose:

**U2.** `A_r = 1  =>  A_(r+1) >= 3` for `r = 1..7`. The patterns `[1,1]` and `[1,2]` are impossible.

**U3.** `A_r = 2  =>  A_(r+1) >= 2` for `r = 1..7`. The pattern `[2,1]` is impossible, **globally** and for any unrestricted base state and any allowed round index. This is the researcher's *certified universal theorem*, not a pending scan.

For **H159**, two distinct exactly 159-byte messages are absorbed into the initial state as 159 message bytes, `0x86` at byte 159, and 96 zero capacity bytes. Thus their initial difference is nonzero and supported in bytes `0..158`. Two additional established restrictions apply:

**H1.** `A_1 >= 5`.

**H2.** `A_1 = 5  =>  A_2 >= 4` (all 21 classified first-round-minimal difference families are covered by the established second-round theorem).

These are all the activity premises used by the new corollaries below. In particular, **no** `[1,3]`, `[2,2]`, `[3,1]`, or H159 `[6,1]` exclusion is silently assumed. A lower bound for one individual round should not be mistaken for a bound on a *sum* over a complete trail.

## 3. Lemma NEW-BND-000: every adjacent two-round window costs at least four

**Statement (certified analytic consequence).** For each `r = 1..7`, every actual distinct-input pair satisfies

`A_r + A_(r+1) >= 4`.

**Proof (three exhaustive cases).** If `A_r=1`, U2 requires `A_(r+1)>=3`, giving at least 4. If `A_r=2`, U3 requires `A_(r+1)>=2`, again at least 4. Otherwise `A_r>=3`, and U1 gives `A_(r+1)>=1`, again at least 4. These cases exhaust all integer possibilities. QED.

No independence, probability multiplication, or assumption about the nonlinear pressure carries is involved. The carry-aware necessity and exclusion work has already been incorporated into U2/U3 as a premise.

## 4. NEW-BND-001 — Unrestricted eight-round cumulative floor is at least 16

**Status:** **CERTIFIED analytic theorem conditional only on the established global exclusions U1–U3.**

**Quantifier:** Every pair of distinct unrestricted 2,048-bit states through eight original indexed rounds.

**Theorem:**

`A_1 + A_2 + A_3 + A_4 + A_5 + A_6 + A_7 + A_8 >= 16`.

**Proof.** Apply NEW-BND-000 to four disjoint adjacent pairs:

```text
(A1 + A2) >= 4
(A3 + A4) >= 4
(A5 + A6) >= 4
(A7 + A8) >= 4
-----------------
Sum A1..A8 >= 16.
```

There is no hidden case: exactly four two-round windows cover all eight rounds. QED.

### Can 17 be certified instead?

**Not from U1–U3 alone.** The abstract integer vector

`[2,2,2,2,2,2,2,2]`

satisfies every accepted adjacent-round exclusion and has sum **16**. It is **not** an actual Krakken trail; it is a countermodel to any purported derivation of `>=17` using *only* U1–U3. In fact, **15** abstract eight-round vectors attain 16 while satisfying U1–U3 (listed in Section 8).

Therefore:

- **Certified:** `min_actual_unrestricted(8) >= 16`.
- **Not certified:** `min_actual_unrestricted(8) = 16`.
- **Not certified or refuted:** `min_actual_unrestricted(8) >= 17` as a possible *stronger* fact about real Krakken. To prove it requires additional Krakken-specific constraints excluding **all 15** abstract 16-call patterns; the existing U1–U3 abstraction alone cannot settle it.

## 5. NEW-BND-003 — Valid H159 with A1 exactly five: eight-round floor is at least 21

**Status:** **CERTIFIED new analytic corollary** of U1–U3 and H2. This strengthens the earlier `>=20` *conditional* figure in `Krakken(3).md` by incorporating the certified universal `[2,1]` exclusion.

**Quantifier:** Every pair of distinct, exactly 159-byte padded Krakken messages whose round-1 activity is `A_1=5`.

**Theorem:**

`A_1 = 5  =>  A_1 + A_2 + ... + A_8 >= 21`.

**Proof.** H2 gives `A_2>=4`. Group the final six rounds into three adjacent pairs and apply NEW-BND-000:

```text
 A1                    = 5
 A2                   >= 4
(A3 + A4)             >= 4
(A5 + A6)             >= 4
(A7 + A8)             >= 4
--------------------------
 Sum A1..A8           >= 21.
```

QED.

### Can 22 be certified instead?

**Not from the stated premises alone.** For example, the abstract sequence

`[5,4,1,3,1,3,1,3]`

obeys all the accepted constraints and has total **21**. It is not a known real trail. There are **10** abstract minimizers at 21 (Section 8).

**Important research reduction:** Every one of those 10 minimizing sequences starts with `[5,4]`. Hence proving the *new, universally quantified* H159 exclusion

`A_1=5  =>  A_2>=5`

would immediately strengthen the conditional eight-round lower bound to **22**. The archive currently establishes only `A_2>=4` in this class. A2=4 remains a precisely targeted unresolved frontier, not an established real trail.

## 6. NEW-BND-002 — Unconditional H159 eight-round floor is at least 19

**Status:** **CERTIFIED analytic corollary** of U1–U3 and H1–H2. This *confirms*, rather than newly discovers, the bound of 19 already present in `Krakken(3).md`.

**Quantifier:** Every pair of distinct, exactly 159-byte padded messages, without conditioning on first-round activity.

**Theorem:**

`A_1 + A_2 + ... + A_8 >= 19`.

**Proof (complete first-round split).** There are only two cases:

**Case I: `A_1=5`.** NEW-BND-003 gives total at least **21**, hence at least 19.

**Case II: `A_1>=6`.** Apply NEW-BND-000 to the consecutive pairs `(A2,A3)`, `(A4,A5)`, `(A6,A7)`, and U1 to the final unpaired `A8`:

```text
 A1                   >= 6
(A2 + A3)             >= 4
(A4 + A5)             >= 4
(A6 + A7)             >= 4
 A8                   >= 1
-------------------------
 Sum A1..A8           >= 19.
```

The two cases exhaust H1 (`A1>=5`). QED.

### Can 20 be certified instead?

**Not from U1–U3 and H1–H2 alone.** The abstract vector

`[6,1,3,1,3,1,3,1]`

satisfies every listed necessary activity constraint and has sum **19**. The verifier establishes that it is the **only** such abstract vector with sum 19. This is *not* proof of a real H159 19-call trail, and the actual minimum may well be 20 or higher.

**Important research reduction:** Excluding the valid-message transition `[6,1]` at the first round boundary, i.e.

`For H159: A_1=6  =>  A_2>=2`, 

would exclude the *only* 19-call abstract pattern and immediately prove the unconditional bound `>=20`, given the existing theorems. A proof that `[3,1]` is impossible for unrestricted adjacent rounds would also exclude that sequence. Neither additional exclusion is asserted here.

## 7. NEW-BND-004 — Unique H159 19-call abstract pattern

**Status:** **CERTIFIED exact combinatorial classification** of the solutions of the five accepted constraints, *not* a statement about existence of actual Krakken differentials.

**Claim:** The only vector of eight integers `A_i` satisfying U1–U3 and H1–H2 whose sum is 19 is

`(6,1,3,1,3,1,3,1)`.

**Analytic proof.** If `A1=5`, NEW-BND-003 gives sum >=21, so at total 19 we must have `A1>=6`. The Case-II inequality in Section 6 reaches 19 only when *all* its terms are equalities. Thus `A1=6`, `A8=1`, and each of `(A2,A3)`, `(A4,A5)`, `(A6,A7)` sums to 4.

Because `A8=1`, U2/U3 forbid `A7=1` or `A7=2`; thus `A7>=3`. But `A6+A7=4` and U1 forces `A6=1, A7=3`. Since `A6=1`, the same argument forces `A5>=3`; using `A4+A5=4` gives `(A4,A5)=(1,3)`. Repeating for `A4=1` yields `(A2,A3)=(1,3)`. Therefore the unique vector is `(6,1,3,1,3,1,3,1)`. It satisfies all premises, proving uniqueness *inside the necessary-condition model*. QED.

**Research payoff:** To improve the **unconditional H159 lower bound**, a targeted proof excluding the first adjacent `6 -> 1` transition is sufficient; no eight-round SMT model is required *if that exclusion can be obtained from short-round certificates*.

## 8. The complete sets of boundary patterns in the abstract model

Independent exhaustive integer-composition enumeration (separate algorithm from DP) established the following **necessary-condition survivors**; their existence as integers does not imply existence as Krakken trails.

### Unrestricted: exactly 16 calls (15 patterns)

```text
 1. [1,3,1,3,1,3,1,3]
 2. [1,3,1,3,1,3,2,2]
 3. [1,3,1,3,1,3,3,1]
 4. [1,3,1,3,2,2,2,2]
 5. [1,3,1,3,2,2,3,1]
 6. [1,3,1,3,3,1,3,1]
 7. [1,3,2,2,2,2,2,2]
 8. [1,3,2,2,2,2,3,1]
 9. [1,3,2,2,3,1,3,1]
10. [1,3,3,1,3,1,3,1]
11. [2,2,2,2,2,2,2,2]
12. [2,2,2,2,2,2,3,1]
13. [2,2,2,2,3,1,3,1]
14. [2,2,3,1,3,1,3,1]
15. [3,1,3,1,3,1,3,1]
```

Every sequence totaling 16 necessarily has exactly four active calls in each disjoint round pair `(1,2),(3,4),(5,6),(7,8)`. Thus the enumeration can also be independently verified by trying the three possible pairs `(1,3),(2,2),(3,1)` and checking the boundaries between pairs.

### Unconditional H159: exactly 19 calls (1 pattern)

```text
[6,1,3,1,3,1,3,1]
```

### H159 with A1=5: exactly 21 calls (10 patterns)

```text
 1. [5,4,1,3,1,3,1,3]
 2. [5,4,1,3,1,3,2,2]
 3. [5,4,1,3,1,3,3,1]
 4. [5,4,1,3,2,2,2,2]
 5. [5,4,1,3,2,2,3,1]
 6. [5,4,1,3,3,1,3,1]
 7. [5,4,2,2,2,2,2,2]
 8. [5,4,2,2,2,2,3,1]
 9. [5,4,2,2,3,1,3,1]
10. [5,4,3,1,3,1,3,1]
```

Every candidate at 21 has `A1=5`, `A2=4`, and each of the last three disjoint round pairs sums to four. A real-trail feasibility test must retain all nonlinear and Pressure-carry constraints. The abstract constraints intentionally do not.

## 9. Independently verified prefix lower bounds (rounds 1..8)

The min-plus dynamic program considers **every possible activity count 1..256 for every round**. These are the exact minimum totals of the abstract model at each prefix depth; they are rigorous lower bounds for actual Krakken activity, not generally achieved values.

| Number of consecutive rounds from round 1 | Unrestricted | H159 (unconditional) | H159 with A1=5 |
|---:|---:|---:|---:|
| 1 | 1 | 5 | 5 |
| 2 | 4 | 7 | 9 |
| 3 | 5 | 10 | 10 |
| 4 | 8 | 11 | 13 |
| 5 | 9 | 14 | 14 |
| 6 | 12 | 15 | 17 |
| 7 | 13 | 18 | 18 |
| 8 | **16** | **19** | **21** |

Only the last row is the subject of NEW-BND-001 through NEW-BND-003. The preceding rows are included to help design targeted short-round exclusion campaigns.

## 10. Independent computation and certificate scope

Two different finite algorithms were executed:

1. **Exact full-range min-plus DP** over integer `A_r in {1,...,256}` and all eight depths. It enforces the three universal restrictions plus the H159 first-round rules and records an optimal necessary-condition vector at every prefix depth.
2. **Independent bounded exhaustive integer compositions:** enumerate every positive eight-term integer vector whose total is less than or equal to the boundary under examination (`16`, `19`, or `21`, respectively), applying the same logical premises. Since each component is positive, any such vector automatically has each term `<=21`, so this enumeration is mathematically complete in the relevant low-sum range. All totals below the respective bounds were empty; at the bounds, exactly **15**, **1**, and **10** admissible sequences survived, respectively.

Both methods agree. All checks in `verify_new_bounds.py` completed with result **PASS**, and the exact source hashes, prefix minima, and survivor lists were written to `NEW_BOUNDS_AUDIT.json`.

To reproduce from the directory containing these three files:

```bash
python3 verify_new_bounds.py
```

This is a *new independent proof check of the logical deductions*, **not** another independent audit of the huge `[2,1]` SAT/SMT archive, and **not** a SAT proof that any survivor is physically realizable. No permutation source was edited; no random sampling or heuristic time limit is part of the proof.

## 11. Certification register and next research gates

| ID | Mathematical statement | Proof type | Status |
|---|---|---|---|
| `NEW-BND-000` | `A_r+A_(r+1)>=4` universally | Three-case analytic proof | **CERTIFIED corollary** |
| `NEW-BND-001` | Unrestricted `sum_{r=1}^8 A_r >=16` | Disjoint-pair analytic proof | **CERTIFIED lower bound** |
| `NEW-BND-002` | Valid H159 `sum A_r >=19` | Exhaustive first-round case split | **CERTIFIED lower bound** (reaffirmed) |
| `NEW-BND-003` | Valid H159 with `A1=5`: `sum A_r >=21` | Disjoint-pair analytic proof | **CERTIFIED improved lower bound** |
| `NEW-BND-004` | The only *abstract* H159 vector totaling 19 is `[6,1,3,1,3,1,3,1]` | Equality-case analytic proof and exhaustive check | **CERTIFIED abstract classification** |
| `NEW-BND-AUDIT-001` | Low-total abstract minimizers: 15 / 1 / 10; prefix floors | Independent min-plus DP and exhaustive integer enumeration | **PASS finite arithmetic verification** |

The formal questions **left open** are:

- Is the actual unrestricted eight-round minimum **16**, **17**, or still larger? We have not exhibited an actual 16-call pair, nor excluded all 15 abstract minimizers.
- Is the actual unconditional H159 minimum **19**, **20**, or still larger? The single abstract 19-call pattern might be impossible in the real permutation.
- Is the actual conditional H159 (`A1=5`) minimum **21**, **22**, or still larger? All 10 abstract 21-call patterns might be impossible.

**Priority short-window research targets:** (1) exclude actual valid-H159 `[6,1]` at the first boundary to get unconditional `>=20`; (2) exclude `[5,4]` from the classified minimum-first-round families to get conditional `>=22`; (3) investigate unrestricted `[2,2]` and `[1,3]` boundaries to attack the 15 abstract 16-call patterns. A successful exclusion must prove impossibility for **all bases and all matching differences**, not merely fail to find a candidate by random search.

## 12. Conclusion

The three requested eight-round **certified lower bounds** are **16, 19, and 21**. The new certified improvement in this note is **21 instead of 20** when a valid H159 pair has exactly five first-round active S-box calls. The values 16 and 19 are still the *sharpest bounds derivable from the enumerated established activity implications*, because explicit **abstract** countermodels prevent deriving 17 or 20 from those implications alone. None of the three actual eight-round minimum numbers is established as an attained equality.

This file preserves both facts simultaneously: the rigor of the existing universal exclusions and the distinction between a sharp *necessary-condition model* and the physical behavior of Krakken's nine interacting layers.

---

## 13. 2026-11-13 continuation — Family-specific 22-call certificate and the exact 19-call bottleneck

**Audit classification:** New *analytic corollaries* from previously certified Krakken facts, with independent exact integer-model verification. This section does **not** claim to have independently repeated the historical C/SMT screening, found any realizable low-activity characteristic, or solved the global eight-round minimum. `NEW_BOUNDS_EXTENSION_AUDIT.json` is generated by `verify_new_bounds_extension.py` and records both exact DP and separately implemented bounded-composition verification.

**Additional accepted archived premise (F4).** The latest `Krakken(3).md`, section **"Complete H159 minimum-activity classification and second-round bound"** (2026-11-10), states that for the explicitly archived **`delta_id=1`, family 4** among the 21 H159 first-round-minimal input difference families, a 70-equation necessary gate excludes **all 10,668,000 four-cell round-two supports**. Therefore, for **any valid H159 message pair with precisely that archived input difference and with `A1=5`**, the *real* round-two activity satisfies `A2>=5`. This is a previously certified **family-specific** theorem, *not* a new universal `[5,4]` exclusion. The exact 159-byte delta value and underlying large proof objects remain in the researcher's historical archive, not in this small arithmetic-audit file; the family's archived identifier is required to disambiguate the statement.

### NEW-BND-005 — An improved eight-round floor of 22 for the archived H159 family 4

**Status: CERTIFIED analytic corollary of F4 and NEW-BND-000, accepting the archived F4 certificate as a premise.**

**Precise quantifier:** For every pair of distinct, correctly padded 159-byte H159 messages whose XOR difference is the specific archived `delta_id=1` (family 4), **and** whose first-round activity is `A1=5`, the actual original eight-round Krakken has

\[
\boxed{\sum_{r=1}^{8} A_r\ge22.}
\]

**Proof:** By the conditioning, `A1=5`. The certified family-specific gate F4 establishes `A2>=5`. The global `[1,1]`, `[1,2]`, and `[2,1]` exclusion theorems imply `(A3+A4)>=4`, `(A5+A6)>=4`, `(A7+A8)>=4` by NEW-BND-000. Adding the five disjoint terms yields `5+5+4+4+4=22`. No probability assumptions or cross-round independence are involved. QED.

This does **not** establish `>=22` for all 21 classified `A1=5` families. A sample necessary-condition vector `[5,5,1,3,1,3,1,3]` sums to 22 but has **not** been instantiated as a real Krakken pair. Thus 22 is an unconditional *lower bound within the stated conditioned family*, not its proved exact minimum.

### NEW-BND-006 — Global H159 19-call boundary has a precisely isolated first-window obstruction

**Status: CERTIFIED analytic case distinction, not a new global numeric 20-call theorem.**

For any valid H159 message pair, if its first-round activity satisfies **`A1>=7`**, then `sum(A1..A8)>=20`. Indeed, group `(A2,A3)`, `(A4,A5)`, `(A6,A7)` into three disjoint adjacent pairs, each costing at least four, and use `A8>=1`: `A1+12+1>=20`.

If `A1=6` **and `A2>=2`**, the same decomposition gives `6+2+(A3+A4)+(A5+A6)+(A7+A8)>=6+2+12=20`.

If `A1=5`, NEW-BND-003 already gives `>=21`.

Consequently, **every valid H159 pair has at least 20 active calls unless `A1=6` and `A2=1`**. Such an exceptional input pair, if one exists, is still restricted by the existing `>=19` theorem; this statement is a logically exact reduction, *not* an assertion that the exceptional transition exists. In particular, excluding real H159 `[6,1]` remains sufficient for certifying a global `>=20` floor.

**Important:** The H159 premise F4 does not help with this `[6,1]` exception, because F4 concerns the separate `A1=5` difference family.

### NEW-BND-007 — Parametric conditional composition for a stronger second-round certificate

**Status: CERTIFIED general-purpose analytic lemma.**

For any actual eight-round trail satisfying `A1=5` and `A2>=k`, where **`k>=4`** is a proven integer lower bound for the *specific quantified population* under discussion,

\[
\boxed{\sum_{r=1}^{8} A_r\ge 5+k+12=17+k.}
\]

This is obtained by disjoint pairing of rounds `(3,4)`, `(5,6)`, and `(7,8)`; each contributes at least four. Thus, in the respective scopes: `A2>=4` yields **21**, `A2>=5` yields **22**, `A2>=6` would yield **23**, etc. **No additional `A2>=6` premise is asserted.** The lemma is useful because every newly certified first-window exclusion immediately propagates to an eight-round bound, without a fresh eight-round search.

### Independent finite verification of this extension

The script `verify_new_bounds_extension.py` computes exact minimum totals for the necessary-condition activity model using **two distinct implementations**: (i) full-range min-plus DP with all 256 possible activity values at every round; (ii) bounded exhaustive positive integer compositions at and below each candidate floor. Both return the following model floors and counts of *abstract* minimizers:

| Quantified population / premises | Proved eight-round floor | Abstract patterns at floor | Real attaining trail? |
|---|---:|---:|---|
| Unrestricted U1–U3 | **16** | 15 | Not established |
| All H159 U1–U3,H1–H2 | **19** | 1 | Not established |
| All H159 with `A1=5` | **21** | 10 | Not established |
| Archived family 4 (`delta_id=1`), `A1=5`, F4 | **22** | 10 | Not established |
| H159 with `A1=6`, `A2>=2` | **20** | 4 | Not established |
| H159 with `A1>=7` | **20** | 1 | Not established |

**Reproduce:** Run `python3 verify_new_bounds_extension.py` from the directory containing this document and its prior script. The command writes `NEW_BOUNDS_EXTENSION_AUDIT.json` with source SHA-256 values, complete abstract pattern lists, and result `PASS`. It does not modify `krakken.c` or `krakken.h`.

### Certification register extension

| ID | Scope | Status |
|---|---|---|
| `NEW-BND-005` | Archived H159 `delta_id=1` / family 4, conditioned `A1=5`: `sum A_r>=22` | **CERTIFIED analytic corollary of family-specific archived gate F4** |
| `NEW-BND-006` | H159: `sum A_r>=20` except possibly if `A1=6,A2=1` | **CERTIFIED logical partition; global `>=20` remains OPEN** |
| `NEW-BND-007` | In any stated population, `A1=5` and `A2>=k>=4` imply `sum A_r>=17+k` | **CERTIFIED analytic parametric lemma** |
| `NEW-BND-AUDIT-002` | Independent DP/composition calculations for the above conditions | **PASS** |

**Next proof target (unchanged, but now sharper):** For a *universal H159 improvement* from conditional 21 to 22, close `A2=4` for each of the other **20** `A1=5` input difference families. For an *unconditional H159 improvement* from 19 to 20, exclude the actual first-window transition `[6,1]` globally over valid-message input differences. The existing 245-call actual second-round witness remains an **upper bound** on the unknown `min(A2 | A1=5)`; none of the abstract minimizing vectors above is a realizable-witness claim.


---

## 14. 2026-11-13 continuation — Exact H159 20-call boundary and conditional 21-call gates

**Status:** New *analytic consequences* of the five established necessary-condition premises U1–U3, H1–H2, plus two independently coded exact finite integer-model calculations. No historical theorem is being re-audited. The permutation sources were not changed. **There is no new unconditional global lower bound**: the unrestricted floor remains 16 and the general H159 floor remains 19.

### NEW-BND-008 — Conditional 21-call H159 lower bound and first-window reduction

**Theorem.** For every distinct pair of valid H159 messages, the eight-round total obeys

```text
sum(A1..A8) >= 21
```

**whenever at least one** of the following explicitly quantified conditions holds:

```text
(i)    A1 = 5                       [already established in NEW-BND-003]
(ii)   A1 = 6,  A2 >= 3            [new conditional corollary]
(iii)  A1 = 7,  A2 >= 2            [new conditional corollary]
(iv)   A1 >= 8                     [new conditional corollary]
```

**Proof.** For (i), use H2 and the last three disjoint adjacent-pair inequalities: `5+4+4+4+4=21`. For (ii), the three disjoint suffix pairs `(A3,A4),(A5,A6),(A7,A8)` cost at least 12, giving `6+3+12=21`. For (iii) the same decomposition gives `7+2+12=21`. For (iv), the remaining seven-round suffix has minimum at least 13: the three disjoint pairs `(A2,A3),(A4,A5),(A6,A7)` contribute at least 12 and `A8>=1`, giving `8+12+1=21`. These cases are exhaustive outside the three first-window possibilities below. QED.

Thus, under the accepted theorems, **a real H159 pair totaling at most 20 must have**

```text
(A1,A2) in {(6,1), (6,2), (7,1)}.
```

A successful H159-specific necessary-condition exclusion of *all three* first-window cases would therefore be sufficient to certify the **unconditional H159 `sum(A1..A8)>=21`**. This is *sufficient*, not claimed necessary: it could also be enough to rule out the specific low-total multi-round continuations without eliminating all three first-window transitions. **No such three-case exclusion is currently established by this section.**

The prior `NEW-BND-006` result is unchanged: excluding **only `(6,1)`** suffices for the intermediate unconditional 20-call floor.

### NEW-BND-009 — Exhaustive abstract boundary census at 19 and 20 calls

**Theorem (finite integer model, not existence of real trails).** The U1–U3,H1–H2 model has exactly **one** vector summing to 19 and exactly **14** vectors summing to 20. The 20-call vectors comprise **nine** with first window `(6,1)`, **four** with `(6,2)`, and **one** with `(7,1)`. Consequently **all 15** abstract vectors with total `<=20` share one of those three first windows.

The only 19-call vector, already recorded in `NEW-BND-004`, is:

```text
[6,1,3,1,3,1,3,1]
```

The 14 vectors summing to 20 are:

```text
[6,1,3,1,3,1,3,2]
[6,1,3,1,3,1,4,1]
[6,1,3,1,3,2,2,2]
[6,1,3,1,3,2,3,1]
[6,1,3,1,4,1,3,1]
[6,1,3,2,2,2,2,2]
[6,1,3,2,2,2,3,1]
[6,1,3,2,3,1,3,1]
[6,1,4,1,3,1,3,1]
[6,2,2,2,2,2,2,2]
[6,2,2,2,2,2,3,1]
[6,2,2,2,3,1,3,1]
[6,2,3,1,3,1,3,1]
[7,1,3,1,3,1,3,1]
```

**Audit.** `verify_new_bnd008.py` independently (1) enumerates all positive integer compositions of 19 and 20 with eight entries under the actual transition constraints and (2) computes counts by a different dynamic-programming state recurrence. Both yield 1 and 14. A third check disallows all three exceptional first windows and confirms no 19- or 20-call vector remains. The generated file `NEW_BOUNDS_BND008_009_AUDIT.json` records the patterns, source hashes, counts and exact scope. No SMT query or full-state realization has been performed.

**Priority implied by the exact boundary:** H159 `(6,1)` is still the best immediate target because excluding it alone lifts the global H159 floor 19→20. Subsequent targets `(6,2)` and `(7,1)` would then suffice to lift the floor 20→21. This is an efficient *proof-planning hierarchy*, not a prediction that those transitions can or cannot occur.

### Certification register extension

| ID | Scope | Classification |
|---|---|---|
| `NEW-BND-008` | H159 total >=21 given (i) A1=5, (ii) A1=6/A2>=3, (iii) A1=7/A2>=2 or (iv) A1>=8 | **CERTIFIED conditional corollary** of accepted U1–U3,H1–H2; no new unconditional bound |
| `NEW-BND-009` | Exact abstract-model census: 1 vector at 19, 14 at 20; all use one of (6,1),(6,2),(7,1) | **CERTIFIED arithmetic classification**, not an actual differential existence theorem |
| `NEW-BND-AUDIT-003` | Independent enumeration/DP counts and gate checks | **PASS** |


## 2026-11-14 bounds-workspace cross-reference

[Research 10, section 17](KRAKKEN_RESEARCH_10.md#17-bounds-workspace-review--additional-fixed-family-evidence-2026-11-14)
preserves an additional source-pinned archived UNSAT result for **family ID 18
(the 19th family)**, distinct from the earlier family-4 special case. For its
explicit fixed delta, conditioned on A1=5, the reported A2>=5 yields the
NEW-BND-007 corollary **eight-round activity >=22**. The four-hour SMT proof
was inspected but not rerun; research 10 records that assurance boundary.
The general H159 floor 19 and all-family conditional floor 21 are unchanged.

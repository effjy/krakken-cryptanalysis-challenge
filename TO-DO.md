# Krakken Research TO-DO

This file tracks high-value cryptanalytic work that remains open or only partially explored in the current source-pinned theorem program.

The immediate goal is to use **round 2 as a laboratory**: not just asking whether a perfect structure survives, but measuring the **strongest imperfect structure that survives the second nonlinear layer**.

A surviving structure is a result. The purpose of these searches is to characterize Krakken accurately, whether the outcome strengthens or challenges the current picture.

## Domain notation

Use the theorem program's domain labels consistently:

- **P** — unrestricted 2048-bit permutation inputs.
- **H** — valid padded 159-byte first-block messages with zero initial capacity.

Every new target, search, theorem, or empirical screen should state its domain explicitly.

---

# Immediate searches

These are intended to be approachable, well-defined round-2 investigations. They should not be confused with the much harder global hull targets later in this file.

## Immediate 1 — Truncated two-round differentials

**Domain:** begin with **P** for controlled structural classes; add **H** variants where first-block reachability is relevant.

### Motivation

Most current differential work asks whether complete state differences can remain extremely sparse, especially in the ongoing \([1,2]\) activity campaign.

A full-state difference may become dense while a selected output projection remains unusually predictable. Truncated differentials test that different attack surface.

For a selected projection \(\pi\), study quantities of the form

\[
\Pr\!\left[
\pi\!\left(F_2(x)\oplus F_2(x\oplus\Delta)\right)=\delta
\right].
\]

### Near-term classes

Start with carefully defined projections rather than attempting a global maximum:

- individual bytes;
- individual 64-bit lanes;
- Pressure-chain-aligned byte sets;
- digest-prefix projections;
- selected low-bit projections suggested by Pressure identities;
- projections aligned with unusually low first-round activity.

Candidate input-difference families:

- one-cell or two-cell unrestricted differences in **P**;
- valid-message low-\(A_1\) differences in **H**;
- the six exceptional four-cell valid-message lines;
- Theta-cancelling valid-message differences;
- selected low-dimensional difference spaces.

### Goals

- Establish empirical distributions for complete, named classes.
- Compare against the corresponding random-projection reference.
- Promote any unusually strong projection to exact counting or solver-backed analysis.
- Treat exact-zero, unusually high-probability, and otherwise structured truncated transitions as findings rather than only searching for failures.

---

## Immediate 2 — Nonperfect two-round differential-linear correlations

### P-domain continuation

**Domain:** **P**.

The cleanest first target extends the existing two-round perfect-mask exclusion.

For selected input difference \(\Delta\), study

\[
\max_{\beta\neq 0}
\left|
\mathbb{E}_x
(-1)^{
\beta\cdot
\left(F_2(x)\oplus F_2(x\oplus\Delta)\right)
}
\right|.
\]

Begin with the same 128 fixed **delta=1** input differences already used in the two-round perfect differential-linear theorem, then search manageable output-mask classes.

Questions:

- What is the largest reproducible nonperfect correlation in the defined class?
- Are the strongest masks related to the one-round perfect-kernel structure?
- Do low-activity first-round differences retain stronger derivative biases?
- Can a high-bias empirical candidate be converted into an exact theorem?

### H-domain continuation

**Domain:** **H**.

If a promising unrestricted structure is found, test whether an analogous input-difference class is reachable at the valid first-block hash interface.

The eventual target is a hash-reachable or certified multi-round differential-linear bound, but the near-term task is to close carefully chosen classes first.

---

## Immediate 3 — Continue the open two-round \([1,2]\) campaign in parallel

**Domain:** **P**.

This campaign should continue independently of the new attack classes above rather than blocking them.

### What is already known

- Unrestricted \([1,1]\) trails are impossible.
- The complete **BB** \([1,2]\) class with two distinct second-branch Chi2 calls is excluded.
- The complete same-spatial-pair mixed class is excluded.
- Several fixed-start low-bit subclasses were also classified.

### What remains open

Unrestricted \([1,2]\) is **not globally closed**.

The remaining branch-type classes include:

- **AA**
- distinct mixed **AB**
- distinct mixed **BA**

### Goal

Systematically enumerate/model the remaining two-call Chi2 geometries and either:

1. find an explicit real \([1,2]\) trail, or
2. prove the remaining classes impossible.

A surviving trail is a cryptanalytic finding, not a failed experiment.

If every remaining branch-type class is excluded, Krakken gains a substantially stronger exact two-round activity theorem.

---

# Next defined theorem targets

These are broader than the immediate searches but should still be approached through complete, carefully chosen classes rather than global optimization from the start.

## Next 1 — Multi-block / later-absorb reachability

**Domain:** hash states after at least one completed absorb.

Most of the strongest **H** theorems concern the first valid padded block, where the capacity begins at zero.

Later absorbs begin from a correlated internal state and therefore have a different reachability geometry.

Questions:

- Which first-block impossibility results continue to later absorbs?
- Can one-cell or low-cell Chi input/output differences become reachable after a previous block?
- Can one-round boomerang, rebound, or differential-linear structures be embedded after the first absorb?
- Does the populated capacity create new low-dimensional affine or differential structures?
- How do later-block reachable-state constraints compare with unrestricted **P**?

This should become a dedicated research line once the immediate round-2 searches are underway.

---

## Next 2 — Defined two-round linear-correlation classes

### H-domain linear target

**Domain:** **H**.

For a complete hash-interface screen, permit the input mask \(\alpha=0\) as long as the output mask is nonzero. This includes pure output-bias tests.

Study

\[
\max_{\substack{\alpha,\beta\\ \beta\neq 0}}
\left|
\operatorname{Corr}
\left(
\alpha\cdot m,\,
\beta\cdot F_2(m)
\right)
\right|.
\]

The global all-mask maximum is a long-term target. Near-term work should instead close selected complete mask classes, for example:

- Pressure-chain-aligned masks;
- extensions of the existing one-round 5D and 6D output-mask spaces;
- low-weight digest-prefix masks;
- masks motivated by exact Pressure zero or low-correlation identities;
- structured two-round pullbacks of known one-round masks.

Questions:

- Are there unexpectedly large nonperfect correlations after two rounds?
- Are any nonzero output masks biased even with \(\alpha=0\)?
- Which mask geometries dominate?
- Can an empirical high-bias class be converted into an analytic or exhaustive theorem?

---

## Next 3 — Two-round differential probabilities and differential hulls

### H-domain target

**Domain:** **H** unless explicitly stated otherwise.

### What is already known

- Exact first-Chi minimum activity is \(A_1=5\) for valid 159-byte first-block differences.
- Six special first-round difference lines have exact probability laws.
- Three selected valid-message differences satisfy \(A_1=5\Rightarrow A_2\ge3\).
- Multi-round activity floors exist, but activity counts are **not probability bounds**.

### What remains open

The important question is not only

> How many Chi calls are active?

but also

> What is the highest probability of a complete two-round input/output differential in a defined reachable class?

For a chosen class, study

\[
\max_{\Delta_{\rm in}\neq0,\,\Delta_{\rm out}}
\Pr\!\left[
F_2(x)\oplus F_2(x\oplus\Delta_{\rm in})
=
\Delta_{\rm out}
\right].
\]

Begin with structured families:

- valid-message low-\(A_1\) differences;
- the six exceptional four-cell lines;
- Theta-cancelling message differences;
- selected low-dimensional difference spaces;
- conditioned \(A_1=5\) classes.

Also investigate **differential hulls**: many internal trails may contribute to the same external differential even when no single trail is especially strong.

---

## Next 4 — General two-round coordinated boomerang

**Domain:** existing construction is **P**; hash reachability is a separate **H** problem.

### What is already known

- A coordinated multi-cell unrestricted construction gives an exact four-state zero sum through one complete round.
- 1,344 saved continuations produced no Chi2 or complete-round-two survivor.
- Every one of those fixed reached patterns has at least one zero-count Chi2 cell.
- A first-block rate gate excludes 896 of the 1,344 saved direction pairs for every common background.
- 448 saved direction pairs remain unresolved by that linear first-block gate.

### What remains open

The finite campaign does **not** exhaust:

- the full 128-dimensional direction spaces;
- arbitrary earlier/common backgrounds;
- jointly solved shared-chain Pressure carries;
- all compatible Chi2 rectangle choices.

### Goals

- Find a direction/background choice for which every required Chi2 local rectangle count is positive.
- Solve global compatibility of the corresponding local bases.
- Construct an explicit complete two-round quartet if one exists.
- Otherwise derive a general two-round impossibility theorem.
- Resolve the remaining first-block linear-gate survivors with nonlinear embedding constraints.

---

## Next 5 — Generalized rebound across the round-1 / round-2 boundary

**Domain:** begin in **P**; then test **H** reachability.

### What is already known

- Exact serial-Chi diagonal inbound counts are known.
- Outbound spread through XRBD is characterized for a defined local family.
- Nonzero one-cell first-block hash embedding is excluded.

### What remains open

There is no general complete two-round rebound analysis.

Questions:

- Can inbound and outbound constraints be matched across Pressure?
- Can the middle be solved using multiple active Chi cells rather than a single-cell model?
- Can backward constraints from Chi2 be joined to forward constraints from Chi1?
- Can a multi-cell **H**-reachable inbound retain controlled outbound activity through Chi2?
- Are later-absorb states substantially easier than the first-block hash domain?

---

## Next 6 — Broader integrals and division-property classes

**Domain:** primarily **H**, with **P** analogues where useful.

### What is already known

- A sharp 14-dimensional first-round cube zero-sum threshold is proved at the defined checkpoint.
- A fixed 14-direction family has 32 universal balanced round-one coordinates and none after round two.
- Every one-byte message cube loses universal round-two coordinate balance.
- The byte-0 cube has no universal nonzero linear output-mask balance after round two.
- A defined division-property balance space drops from dimension 7 to 0 across rounds 1 to 2.

### What remains open

These are selected cube/direction families, not an exclusion of all integrals.

Explore:

- multi-byte affine cubes;
- non-coordinate direction sets;
- cubes aligned with Theta cancellations;
- Pressure-chain-aligned directions;
- higher-dimensional cubes;
- nonlinear or generalized integral properties;
- balanced projections other than the coordinate and linear-mask classes already tested.

Treat any exact zero-sum or balanced family that survives as a result.

---

## Next 7 — General invariant / weak subspaces

**Domain:** **H** first, with unrestricted **P** structures analyzed separately.

### What is already known

- All 159 zero-base message-byte subspaces have affine-hull rank 255 after Chi1 and complete rounds 1 and 2.
- A defined Theta-cancelling two-byte family reaches full 255-dimensional affine hull by Pressure1 / complete rounds.

### What remains open

No general theorem excludes all weak or invariant subspaces.

Search for:

- subspaces preserved exactly or approximately by selected layer combinations;
- low-rank affine images through two rounds;
- Pressure-chain-aligned subspaces;
- serial-Chi-compatible affine spaces;
- subspaces that are not simple message-byte coordinate cubes.

---

# Long-term global targets

These are destinations for the theorem program, not assumptions about what can be solved in one search campaign.

## Long-term 1 — Complete message-to-state linear hull

**Domain:** **H**.

For each complete round count \(r\), the eventual target is a useful bound on

\[
\max_{\substack{\alpha,\beta\\ \beta\neq0}}
\left|
\operatorname{Corr}
\left(
\alpha\cdot m,\,
\beta\cdot F_r(m)
\right)
\right|.
\]

Allowing \(\alpha=0\) includes output-bias detection.

The exact signed coset formulation is known, but intermediate-mask interference and the large rate-restricted signed sum remain major proof obligations.

This is an ambitious theorem target, not the next brute-force search.

---

## Long-term 2 — Complete hash-reachable differential hull

**Domain:** **H**.

The eventual target is a certified bound on the maximum probability over all nonzero valid-message input differences and all output differences.

Existing activity floors, selected transition probabilities, and reachability theorems are possible lemmas. They are not yet a global differential-hull bound.

---

## Long-term 3 — General Pressure linear behavior

**Domain:** **U/P** as defined in the theorem program.

### What is already known

Pressure has strong exact results for:

- two special mask families;
- coupled output masks confined to the low \(k\le17\) bits;
- exact-zero families;
- pairwise uniformity identities;
- signed hull identities.

### What remains open

Arbitrary coupled 64-bit output masks are still outside the closed classes.

Important targets:

- extend the joint-carry counter to wider masks;
- classify general mask equivalence/canonicalization;
- search for unexpectedly large full-width Walsh coefficients;
- derive exact-zero rules for broader classes;
- find bounds that compose across multiple rounds without a catastrophic triangle inequality.

---

# Additional attack families worth systematic treatment

The current theorem program overlaps these areas but does not yet give each one a broad dedicated search program.

## Zero-correlation linear structures

**Domain:** state explicitly for every search.

Search for input/output mask classes whose correlation is provably exactly zero after two rounds.

An exact zero-correlation family is itself an attack-side structural result and should be characterized rather than discarded as merely another negative search.

## Slide / related-round structures

**Domain:** **P**.

Exact affine lane-rotation covariance is already excluded in the defined rotational theorem, but broader related-round and related-input transformations remain open.

Round constants should be included explicitly in the model rather than removed unless the experiment is deliberately a control.

## Meet-in-the-middle / splice-and-cut

**Domain:** likely **P** first; **H** reachability later.

This is more naturally aimed at several rounds than only round 2. Revisit once forward and backward constraints around an internal boundary are sufficiently characterized.

## Fixed points and short cycles

**Domain:** **P**.

Still open, but lower priority for the hash interface than the round-2 statistical and reachability questions above.

---

# Round-2 research strategy

The central question should no longer be only:

> Does a perfect or extremely sparse structure survive round 2?

Instead ask:

> **What is the strongest imperfect structure that survives round 2?**

Measure that question across genuinely distinct attack families:

- truncated differential probability;
- differential-linear correlation;
- full-state differential probability;
- linear correlation;
- boomerang compatibility;
- rebound compatibility;
- integral balance;
- subspace rank.

Round 1 repeatedly exposes exact structure. Round 2 repeatedly destroys the easiest versions of it. The next phase is to quantify **how completely** that destruction occurs.

## Recommended work order

### Run now

1. Truncated two-round differential classes
2. Nonperfect two-round differential-linear classes
3. Continue AA / AB / BA \([1,2]\) work in parallel

### Then

4. Multi-block / later-absorb reachability
5. Defined two-round linear mask classes
6. Defined two-round differential-probability / hull classes
7. Generalized rebound
8. Broader integral / division-property / subspace searches
9. Revisit coordinated boomerangs using what the other analyses reveal

### Long-term

10. Complete message-to-state linear hull
11. Complete hash-reachable differential hull
12. Arbitrary full-width Pressure-mask theorem

---

## Research discipline

For every future pass:

- state the domain (**P**, **H**, or another defined model);
- define the complete class being searched;
- record the exact source hashes;
- separate empirical screens from finite exhaustive proofs and analytic theorems;
- treat a surviving structure as a finding;
- do not turn a negative search over one class into a global security claim;
- preserve implementation-audit versus external-reproduction distinctions;
- promote a result to the public theorem ledger only when its stated class is closed.

A closed defined class is not a global attack-family exclusion.

In particular:

- no perfect relation does not imply no useful nonperfect correlation;
- high activity does not imply low differential probability;
- failure of sampled boomerangs does not imply a general two-round impossibility;
- selected integral failures do not exclude all integral structures;
- a zero-correlation or high-probability structured family is a cryptanalytic result, not an inconvenience;
- implementation audits are not independent external cryptanalytic reproduction.

All future claims should retain the theorem program's domain/proof labels and source pin.

# Krakken Research TO-DO

This file tracks high-value cryptanalytic work that remains open or only partially explored in the current source-pinned theorem program.

The immediate goal is to use **round 2 as a laboratory**: not just asking whether perfect structure survives, but measuring the **strongest imperfect structure that survives the second nonlinear layer**.

## Priority 1 — Nonperfect two-round linear correlations

### What is already known

- No nontrivial **perfect affine** message-to-state relation exists after any complete round count 1–8 on the valid 159-byte first-block domain.
- One-round numerical correlation bounds are known for several explicitly defined output-mask classes.
- Pressure has exact Walsh/carry results for several defined low-bit and special-mask families.

### What remains open

A useful all-mask numerical bound for two complete rounds is not known.

Target quantity:

[
max_{alpha
eq 0,,eta
eq 0}
left|operatorname{Corr}(alphacdot m,,etacdot F_2(m))ight|.
]

Questions:

- Are there unexpectedly large nonperfect correlations after two rounds?
- Which input/output mask geometries dominate?
- Do Pressure-chain masks, Chi-pair masks, or structured output projections retain measurable bias?
- Can an empirical high-bias mask be converted into an analytic or exhaustive theorem?
- Can the signed linear-hull structure be bounded without losing everything to a triangle inequality?

This is currently one of the most important open round-2 classes.

---

## Priority 2 — Nonperfect two-round differential-linear correlations

### What is already known

- One-round perfect-mask kernels are characterized for a defined class.
- For 128 specified unrestricted input differences, no perfect two-round output autocorrelation mask survives.

### What remains open

The useful **nonperfect** correlations have not been quantified.

For selected input difference (Delta), study:

[
max_{eta
eq0}
left|
mathbb{E}_x
(-1)^{etacdot(F_2(x)oplus F_2(xoplusDelta))}
ight|.
]

Questions:

- Does any ((Delta,eta)) pair retain a large two-round bias?
- Are the strongest masks related to the one-round perfect-kernel structure?
- Do low-activity first-round differences produce stronger derivative biases?
- Can empirical candidates be confirmed independently and then proved?

A result such as a reproducible two-round correlation around (2^{-4}), (2^{-8}), (2^{-10}), etc. would be far more informative than merely proving the absence of perfect masks.

---

## Priority 3 — Finish the open two-round ([1,2]) differential classes

### What is already known

- Unrestricted ([1,1]) trails are impossible.
- The complete **BB** ([1,2]) class with two distinct second-branch Chi2 calls is excluded.
- The complete same-spatial-pair mixed class is excluded.
- Several fixed-start low-bit subclasses were also classified.

### What remains open

Unrestricted ([1,2]) is **not globally closed**.

The current theorem program explicitly leaves open:

- **AA**
- distinct mixed **AB**
- distinct mixed **BA**

The completed BB and same-pair results do not cover these.

### Goal

Systematically enumerate/model the remaining two-call Chi2 branch-type geometries and either:

1. find an explicit real ([1,2]) trail, or
2. prove the remaining classes impossible.

If every remaining branch-type class is excluded, Krakken would gain a substantially stronger exact two-round activity theorem.

---

## Priority 4 — Two-round differential probabilities and differential hulls

### What is already known

- Exact first-Chi minimum activity is (A_1=5) for valid 159-byte first-block differences.
- Six special first-round difference lines have exact probability laws.
- Three selected valid message differences satisfy (A_1=5 Rightarrow A_2ge3).
- Multi-round activity floors exist, but activity counts are **not probability bounds**.

### What remains open

The important unanswered question is not just:

> How many Chi calls are active?

but:

> What is the highest probability of a complete two-round input/output differential?

Ideal target:

[
max_{Delta_{m in}
eq0,Delta_{m out}}
Pr[
F_2(x)oplus F_2(xoplusDelta_{m in})
=
Delta_{m out}
].
]

A full 2048-bit exhaustive search is impossible, so begin with structured classes:

- valid-message low-(A_1) differences;
- the six exceptional four-cell lines;
- Theta-cancelling message differences;
- selected low-dimensional difference spaces;
- one-cell/two-cell unrestricted constructions;
- conditioned (A_1=5) classes.

Also investigate **differential hulls**: many trails with the same external differences may combine even if no single trail is especially strong.

---

## Priority 5 — General two-round coordinated boomerang

### What is already known

- A coordinated multi-cell unrestricted construction gives an exact four-state zero sum through one complete round.
- 1,344 saved continuations produced no Chi2 or complete-round-two survivor.
- Every one of those 1,344 fixed reached patterns has at least one zero-count Chi2 cell.
- A first-block rate gate excludes 896 of the 1,344 saved direction pairs for every common background.
- 448 saved direction pairs remain unresolved by the linear first-block gate.

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
- Resolve the 448 saved first-block linear-gate survivors with nonlinear embedding constraints.

---

## Priority 6 — Generalized rebound across the round-1 / round-2 boundary

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
- Are later-absorb or unrestricted-permutation states substantially easier than the first-block hash domain?

---

## Priority 7 — Broader integrals and division-property classes

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
- balanced projections other than single coordinates or linear masks already tested.

---

## Priority 8 — General invariant / weak subspaces

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

## Priority 9 — General Pressure linear behavior

### What is already known

Pressure has strong exact results for:

- two special mask families;
- low-bit output masks up to (kle17);
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

## Additional attack families worth systematic treatment

The current theorem program overlaps these areas but does not yet give each one a broad dedicated search program.

### Truncated differentials

Study whether selected subsets of output bytes/words have unusually high-probability difference patterns after two rounds, even when the full difference is dense.

### Zero-correlation linear structures

Search specifically for input/output mask classes whose correlation is provably exactly zero after two rounds.

### Meet-in-the-middle / splice-and-cut

More naturally aimed at several rounds rather than only round 2, but worth considering once forward and backward constraints around the middle are sufficiently characterized.

### Multi-block / later-absorb reachability

Most exact hash-interface work currently focuses on the first block with zero initial capacity. Later absorbs have correlated capacity state and may allow structures unavailable at the first block.

---

# Round-2 research strategy

The main question should no longer be only:

> Does a perfect or extremely sparse structure survive round 2?

Instead ask:

> **What is the strongest imperfect structure that survives round 2?**

Measure that question across multiple attack families:

- linear correlation;
- differential probability;
- differential-linear correlation;
- boomerang compatibility;
- rebound compatibility;
- integral balance;
- subspace rank.

Round 1 repeatedly exposes exact structure. Round 2 repeatedly destroys the easiest versions of it. The next phase is to quantify **how completely** that destruction occurs.

## Recommended order

1. Nonperfect two-round linear correlations
2. Nonperfect two-round differential-linear correlations
3. Finish AA / AB / BA ([1,2]) differential classes
4. Two-round differential probabilities and hulls
5. Generalized rebound
6. Broader integral / subspace searches
7. Revisit coordinated boomerangs using what the other analyses reveal

---

## Scope warning

A closed defined class is not a global attack-family exclusion.

In particular:

- no perfect relation does not imply no useful nonperfect correlation;
- high activity does not imply low differential probability;
- failure of sampled boomerangs does not imply a general two-round impossibility;
- selected integral failures do not exclude all integral structures;
- implementation audits are not independent external cryptanalytic reproduction.

All future claims should retain the theorem program's domain/proof labels and source pin.

# Krakken research 14 — eight-round probability bounds

19 November 2026. H159 denotes all 159-byte messages. Write S(m) for the 2,048-bit state after the padded absorb and eight rounds, and H(m) for its first 256 bits. All probabilities below specify how inputs are selected. The scalar hash absorbs H159 in one padded block ending in 0x86. Sections 14.1–14.3 use the recorded bijectivity of the rounds and the existing Research 04 sample. Sections 14.4–14.5 use two fresh samples. No solver was used.

The new fixed-difference results cover all 21 classified H159 differences that admit five first-round active calls, at each depth from two through eight. Even within the five-call population, finite witnesses exclude every perfect quadratic equation in the paired 32-bit digest prefixes. For two independently drawn pairs with the same fixed difference, the new samples bound the probability of matching full digest differences below 2^-20 at greater than 99% simultaneous confidence across both population panels. The definitions, proofs, results and replay commands are in §§14.4–14.5.

Sections 14.7–14.8 give deterministic rank and prediction bounds at two and eight rounds. Across every contiguous byte cut of the ordinary H159 hash, every nonzero digest parity requires at least 64 products of separate left and right functions. Every individual digest bit requires at least 252. The minimum-activity study gives separate bounds for related-message digest differences. Section 14.9 gives general bit-circuit lower bounds for exact forward evaluation. Section 14.10 follows the same fixed-difference event from round one through eight and gives exact and confidence bounds for quartets with a prescribed second offset. Section 14.11 proves reachability under adaptive parity-based message selection and bounds prediction on the selected branches.

## 14.1 — A deterministic bound for prescribed full-state differences

Fix any nonzero 2,048-bit target b. Choose a nonzero 1,272-bit message difference a uniformly and a base message m independently and uniformly. Then

    Pr[S(m) XOR S(m XOR a) = b] ≤ 1/(2^1272 − 1).

Indeed, for each m there is at most one partner whose state equals S(m) XOR b. Padding embeds H159 injectively, and the complete permutation preserves injectivity. Averaging the count over m proves the result. More precisely, writing T for the image of S, the numerator of the exact probability is |T ∩ (T XOR b)| and the denominator is 2^1272 (2^1272 − 1).

For the fixed target b, at most a fraction 2^k/(2^1272 − 1) of nonzero differences a can give conditional probability at least 2^-k over m, by Markov's inequality. For k = 128 this fraction is about 2^-1144. The exceptional set depends on b. This is a counting theorem for every injective embedding of this size, so it measures the effect of the input model and leaves the worst chosen difference open. Summing it over the 2^1792 states compatible with a digest difference gives a vacuous digest bound.

## 14.2 — A sharper confidence bound on actual digest collisions

Let C_r be the collision probability of the first 64 digest bits at depth r for two independent uniform H159 messages. Research 04 records no repeated prefix at any depth on the same N = 262144 independent uniform draws, under its sampling assumption. The following reporting rule has simultaneous confidence above 99 percent: issue the single assertion “all eight C_r are below 2^-30.5” only when all eight depths pass. This improves the recorded exponent of 29 using the original pass event. This threshold was derived after the experiment.

**Proof.** For a fixed depth write p_j for its prefix masses, C = sum p_j², and A_n for no repeat in n draws. Take an independent Poisson count K of mean λ = 0.99N. Independent Poisson bucket counts give

    Pr(A_K) = exp(−sum h(λp_j)),     h(x) = x − ln(1+x).

Since h(x)/x² = ∫₀¹ v/(1+xv) dv decreases and every λp_j ≤ t = λ√C, summing yields sum h(λp_j) ≥ h(t). Monotonicity in sample size gives Pr(A_N) ≤ (1+t) exp(−t)/Pr(K≤N). Exponential Markov applied to exp(sK) at s = ln(N/λ) gives Pr(K>N) ≤ exp(N−λ−N ln(N/λ)) ≤ exp(−N·0.01²/2), using −ln(1−u) ≥ u+u²/2.

If C ≥ 2^-30.5 then t ≥ 0.99·2^2.75. Since (1+t)exp(−t) decreases, the false-pass probability is below 0.009815. If the joint assertion is false, fix one violating depth before sampling. Passing all eight implies passing this particular depth. The same bound therefore controls issuance of the false joint assertion, including when the depths are dependent. This rule makes no individual claims when any depth fails.

## 14.3 — Digest consequences and search budgets

Under the confidence statement in 14.2, write p for the full eight-round digest distribution. Refining prefix buckets gives sum p_y² < 2^-30.5. Thus collision entropy exceeds 30.5 bits and min-entropy exceeds 15.25 bits, since max p_y ≤ √(sum p_y²).

* For q independent uniform H159 messages, the chance of any genuine digest collision is at most binom(q,2)·2^-30.5 by a union bound. At q = 32768 this is below 0.354. The confidence level concerns the population estimate, while 0.354 concerns a fresh search under that estimate.
* For every prescribed digest XOR b, two independent uniform messages satisfy it with probability sum p_y p_(y XOR b) ≤ sum p_y² by Cauchy–Schwarz. All targets inherit the same ceiling simultaneously. Equivalently, for uniform m and uniform independent message difference a (zero included), the eight-round digest differential averaged over a is below 2^-30.5 for each b. At most a fraction 2^-14.5 of a can have success probability at least 2^-16 for that b. This follows by Markov and leaves open the maximum for a deliberately selected a.

## Comparison with a sponge security claim

The source has a 1,280-bit rate and 768-bit capacity. The classical random-permutation sponge model gives the familiar generic birthday scale of 2^128 for a 256-bit digest. Transferring that scale to the concrete public Krakken permutation requires controlling attacks exploiting its structure. The activity floors of 20 generally and 22 when A1=5 count S-box calls. Turning either count into digest security bits would require controlling dependent transitions and summing over compatible trails and final states. None of the proofs above assumes independence between internal transitions. [Bertoni et al., sponge indifferentiability, discussion](https://keccak.team/files/SpongeIndifferentiability.pdf)

The remaining concrete gap is a bound uniform in the chosen message difference. For digest collisions alone the target b is zero, so that question can already be posed without maximizing over output targets. A bound on its average cannot rule out a single exceptional difference with probability one.

## 14.4 — Fixed-difference list prediction, design before sampling

For classification IDs 0 through 20 in the Research 12 probability foundation, hold the H159 XOR difference fixed and evaluate all prefixes of 2 through 8 complete rounds. Use one fresh sample of 8192 OS-random 159-byte messages shared across all 147 tests. Count distinct first-eight-byte digest XOR values in each test. Report the joint confidence claim only if all 147 tests have no repeat. Threshold for the maximum point probability is 1/1024. Retain the first sample and publish all counts regardless of outcome. This samples the entire H159 domain, without conditioning on the rare event A1=5.

### Conditional extension, design before its independent sample

Repeat the same 147 no-repeat tests with a second fresh sample of 8192 base messages. For each fixed difference, project those bases uniformly onto its A1=5 affine set using Research 12's two-root equations. Use the same maximum-point threshold 1/1024 and report every outcome. Run the paired-prefix quadratic rank test described below on the first 2208 bases in each population. No favorable sample selection.

### Definitions and the conditional sampler

For depth r and classification difference d, define D(m) as the first 64 digest bits of H_r(m) XOR H_r(m XOR d), in output byte order. Each input has 159 message bytes, byte 159 equal to 0x86, and 96 zero capacity bytes before the indexed rounds. Let U be uniform on the H159 domain and U_d uniform on the subset with A1=5. Research 12 gives this subset mass exactly 2^-35 for every listed d.

For each of the five active serial-Chi cells, let x be its first-call input byte and {u,v} the two favorable roots. Write g=u XOR v and choose its least significant set bit j. The linear map L(z)=z XOR (z_j times g) has kernel {0,g}. The root condition is exactly L(x XOR u)=0. The five cells give a combined affine syndrome F(m)=B m XOR c with rank 35. Here c includes both the root offsets and the fixed padding. The implementation derives the columns of B by applying the original scalar linear prefix to the 1,272 unit vectors with zero padding. It evaluates F on actual padded inputs.

Gaussian elimination constructs a linear right inverse J on the image of B. The nonempty affine solution set ensures c belongs to that image. The sampler sends m to m XOR J F(m). Its syndrome is zero and it fixes every solution. Its linear part is a projection onto ker B, so every admissible message has exactly 2^35 preimages. Independent uniform draws remain independent and uniform within that family's admissible population. The code checks rank 35 and directly re-evaluates all five root conditions on **every** constructed message. Reusing seeds between families creates dependence between tests only.

### Exact finite-witness theorem for paired digest equations

For a message m set X = first32(H_r(m)) and Y = first32(H_r(m XOR d)). Consider any square-free Boolean polynomial Q(X,Y) of total degree at most two in their combined 64 bits, including arbitrary cross terms. Its coefficient vector has 1 + 64 + binom(64,2) = 2081 entries. Make a binary matrix with one row per witnessed pair and one column per constant, bit, or product of two distinct bits. A universal identity Q=0 forces the coefficient vector into the matrix kernel. Full column rank therefore excludes every nonzero polynomial at once. This argument needs only correctly evaluated witnesses. Their sampling distribution is immaterial. The Boolean polynomial convention is the algebraic normal form. [Carlet, Boolean Functions for Cryptography and Coding Theory](https://www.math.univ-paris13.fr/~carlet/book-fcts-Bool-vect-crypt-codes.pdf)

In particular, a predictor asserting that a nonzero parity of the partner's 32-bit prefix always equals some quadratic function of the first 32-bit prefix would give precisely such an identity. So would a quadratic identity in the 32-bit digest difference alone, by substituting X XOR Y; this substitution preserves degree and is onto as a formal map. Full rank for the conditioned sample proves exclusion even within A1=5 and hence also on the entire domain. Research 02's digest-only eight-round quadratic test used the bits of one digest. The matrix here uses bits from two related messages, allowing equations that involve both outputs. This excludes a perfect relation. Bounding how often an approximate quadratic equation holds requires a different argument.

**Exact two-parity reachability.** Take any two independent linear forms l₁,l₂ on the 64 paired-prefix bits. Every one of their four joint values occurs among the 2208 witnesses, separately at every tested depth, for every listed d, and in each population. Indeed, the indicator of a desired value (a,b) is the degree-two polynomial (1 XOR l₁ XOR a)(1 XOR l₂ XOR b). Independence makes this polynomial nonzero on the ambient space. Full rank precludes its vanishing on all witnesses. In particular, pick any nonzero parity of the first message's 32-bit prefix and any nonzero parity of its partner's 32-bit prefix. Even after specifying the first parity, **both values** of the partner parity remain attainable. The same argument works for any two independent parities of the first 32 digest-difference bits. These are reachability statements; the four patterns can have unequal frequencies.

### From distinct values to a probability bound

For each (r,d) and population, 8192 different D values certify support size at least 8192 by direct witness. Any fixed list of at most 8191 digest XORs therefore omits a feasible result, even if that list was tailored to the specific family, depth and population. For the uniform distribution on the witnessed bases alone, any list of L targets succeeds with probability at most L/8192.

For the population bound, suppose some target has probability p ≥ 1/1024. A no-repeat sample requires its count to be zero or one. For independent draws its count is binomial and the probability of that event decreases with p. With n=8192 the false-pass probability is at most

    (1 − 1/1024)^8192 + 8 (1 − 1/1024)^8191 < 0.003011.

If any of the 147 parameter pairs violates the proposed ceiling, fix one such pair and one violating target. Passing the entire panel requires passing that pair's test. This controls the chance of a false joint report without assuming independence across pairs or preselecting the heaviest target. Each population panel therefore has simultaneous confidence of at least 99.6989%. A conservative union bound for the two panel reports together gives at least 99.3978%. These are frequentist coverage statements under the independent uniform OS-sample model.

The point ceiling applies to full 256-bit digest XORs because each such event implies its 64-bit prefix event. For a fixed list of L full targets the corresponding success ceiling is min(1,L/1024). In particular, a 16-target list succeeds with probability below 1/64 under either tested population. The same upper bound applies if four bits of side information select one target from a fixed table of sixteen.

For a uniform H159 base, one can also bound the **joint** event that a minimal first round occurs and a prescribed digest XOR follows at depth r. Its probability factors exactly as Pr[A1=5] times Pr[target | A1=5]. Research 12 supplies the first factor and the conditional panel bounds the second, giving a ceiling below 2^-45 at the conditional panel's confidence level. This multiplication is the probability chain rule. A search that constructs its bases inside A1=5 has already imposed the first condition, and only the conditional ceiling applies when those bases are uniform there. Neither panel bounds a search that selects arbitrary favorable bases. The result covers the 21 specified differences, including all trails they induce in each population.

### 14.5 — Matching-difference quartets and a stronger list bound

Choose two independent bases M and N from the same specified population (U or U_d), and consider the four messages M, M XOR d, N, N XOR d. A matching-difference quartet has equal full digest XORs for the two pairs. For each of the 21 prescribed d and each depth 2 through 8, the data give a simultaneous confidence bound **below 2^-20** on its probability. The bound includes coincidences among the four inputs, so it also bounds success with four distinct inputs. On U_d both pairs start with A1=5. A quartet construction that correlates its two bases falls outside this experiment.

**Proof.** Let p_y be the distribution of D(M) and C=sum p_y². Independence of the two bases gives Pr[D(M)=D(N)]=C, and matching both full digest differences implies this event. Apply the distribution-free no-repeat inequality in §14.2 with n=8192, λ=0.95n. If C ≥ 2^-20 then λ√C ≥ 7.6. The Poisson upper-tail calculation there gives Pr[K>n] ≤ exp(−n·0.05²/2). Hence the probability of reporting a passing panel if any parameter violates the ceiling is at most

    8.6 exp(−7.6) / (1 − exp(−10.24)) < 0.004305.

Thus the coverage for each population panel exceeds 99.5695%, and a conservative bound for reporting both panels is above 99.139%. No independence between rounds or families is required. The collision-entropy threshold of 20 bits was derived after the samples, using the same all-distinct pass criterion and a proof valid for every fixed distribution. This is a new application of §14.2 to related-message digest differences.

For any fixed list S of L full digest differences, its projection has at most L prefix values. Cauchy–Schwarz gives Pr[target in S] ≤ √(L C) for L ≥ 1. At this confidence level a 16-entry list therefore succeeds with probability below **1/256**. This covers a table chosen specifically for the family and depth, with any rule selecting among its entries. There is no independence assumption between S-box calls. The table must be fixed across base draws.

### Results and reproduction

| Depth in complete rounds | Differences checked | Distinct XOR prefixes per difference, U | Distinct XOR prefixes per difference, U_d | Paired quadratic matrix rank, both populations |
|---:|---:|---:|---:|---:|
| 2 | 21 | 8192 | 8192 | 2081 / 2081 |
| 3 | 21 | 8192 | 8192 | 2081 / 2081 |
| 4 | 21 | 8192 | 8192 | 2081 / 2081 |
| 5 | 21 | 8192 | 8192 | 2081 / 2081 |
| 6 | 21 | 8192 | 8192 | 2081 / 2081 |
| 7 | 21 | 8192 | 8192 | 2081 / 2081 |
| 8 | 21 | 8192 | 8192 | 2081 / 2081 |

Each entry holds individually for **every** listed difference. GCC scalar and Clang AVX2 produced byte-identical result logs for the unrestricted difference counts and commitments, and for the entire conditional panel including its matrix ranks. There were 2208 rows in each rank matrix. A second implementation of the monomial ordering and elimination reproduced rank 2081 for unrestricted family 0 at all seven depths using the scalar permutation. On the first unrestricted base and its 21 related messages, both public eight-round hash APIs matched all 32 extracted bytes from their padded-state permutation paths, and the derived 64-bit XORs matched the archived witnesses. The two population panels use 8192 source draws each, shared across their respective tests; the table does not count the 294 cases as independent experiments.

The [evidence directory](reproduce/related_digest_14/) contains the two original samples, runners, per-case distinct counts, SHA-256 commitments to the ordered differences, and rank results. Difference IDs and byte strings come from [Research 12's exact population record](reproduce/probability_foundation_20261118/RESULTS.json), SHA-256 28ea7ee7294d34a5a36fecf3305ebca6bc44e89123665bc0da73639adf77fc97. The sample digests are recorded in the first lines of the two respective result files. Commands below assume little-endian x86 with AVX2, run at the repository root. They read the preserved samples.

```bash
dir=reproduce/related_digest_14
export PYTHONDONTWRITEBYTECODE=1
gcc -O3 -march=native -shared -fPIC -pthread krakken.c -o /tmp/kr14s.so
clang -O3 -mavx2 -shared -fPIC -pthread krakken_multi.c -o /tmp/kr14a.so
python3 "$dir/run.py" /tmp/kr14s.so scalar > /tmp/kr14.uniform.scalar
python3 "$dir/run.py" /tmp/kr14a.so avx2 > /tmp/kr14.uniform.avx2
cmp "$dir/results.txt" /tmp/kr14.uniform.scalar
cmp "$dir/results.txt" /tmp/kr14.uniform.avx2
python3 "$dir/quadratic.py" /tmp/kr14a.so avx2 > /tmp/kr14.ranks
cmp "$dir/ranks.txt" /tmp/kr14.ranks
python3 "$dir/check_rank.py" /tmp/kr14s.so scalar > /tmp/kr14.spot
cmp "$dir/rank_spotcheck.txt" /tmp/kr14.spot
python3 "$dir/conditional.py" /tmp/kr14a.so avx2 /tmp/kr14s.so > /tmp/kr14.conditional.avx2
python3 "$dir/conditional.py" /tmp/kr14s.so scalar /tmp/kr14s.so > /tmp/kr14.conditional.scalar
cmp "$dir/conditional.txt" /tmp/kr14.conditional.avx2
cmp "$dir/conditional.txt" /tmp/kr14.conditional.scalar
```

## 14.6 — Nonlinear related-digest prediction, design before sampling

Draw 16,384 fresh 159-byte OS-random messages once and retain them. Use these seeds both directly and projected uniformly onto each of the 21 five-call populations. At depths 2 through 8, examine every ordered pair of four-bit digest positions (64 × 64). From the first digest a predictor reads one fixed nibble. Measure how well an arbitrary lookup table predicts a nibble or a bit of the related digest. Allow the table to select its target position after seeing the source nibble. Also measure total variation from uniform for each fixed pair of positions. Report maxima over the entire panel, including unfavorable results. Use one-sided Hoeffding upper bounds with familywise error at most 1% shared equally between the three statistics. No parameter or sample tuning.

### Exact theorem — every ordered pair of digest nibbles has full support

Number the 64 nibble positions of the 256-bit digest from zero, low nibble first in each byte. For a message m and fixed difference d, let X_i be nibble i of H_r(m) and Y_j be nibble j of H_r(m XOR d). For **each** depth r=2 through 8, **each** of the 21 classification differences, **each** of the two populations U and U_d, and **every** i,j, the image of (X_i,Y_j) is the entire set of 256 possible ordered values.

**Witness proof.** Exhaustively tabulate the 256 cells for each ordered position pair on the saved bases. The minimum count across 1,204,224 tables and 308,281,344 cells was **23**. The 16,384 bases within each population and family were distinct. Hence every prescribed pair has at least 23 distinct base witnesses, including on the five-call affine sets. This coverage check was added after the original scoring design. Existence follows directly from the witnesses and uses no sampling assumption. In particular, given any fixed observed value of X_i, no value of Y_j is impossible. This rules out every exact Boolean relation that forbids even one of those 256 patterns, of any algebraic degree on these eight bits.

### Statistical bounds on predicting the partner digest

A predictor chooses one source nibble position i before seeing the message. Upon observing X_i=x, it uses any lookup rule. For a nibble guess the rule selects *both* a partner position j(x) and a guessed value y(x). For a bit guess it selects *both* a partner bit position and a guessed bit. The rule may be different for every population, difference, and depth. All success probabilities average over a fresh base in that population. Under the independent uniform seed assumption the following statements have **joint confidence at least 99%**.

| Quantity, maximized over both populations, 21 differences, and all seven depths | Upper bound | Reference value for independent uniform digests |
|---|---:|---:|
| Success in predicting a partner nibble after seeing a source nibble | < 9.80% | 6.25% |
| Success in predicting a partner bit after seeing a source nibble | < 56.46% | 50% |
| Total variation distance of any fixed ordered nibble pair from uniform on 256 values | < 0.07490 | 0 |

For fixed i,j, the optimal average guessing probability is the sum over x of Pr[X_i=x] times the largest conditional probability of a Y_j value. It is bounded by the first row, which even permits adaptive choice of j. Equivalently **the average conditional min-entropy of the partner nibble exceeds 3.35 bits out of four**. The average is over the observed source value. This entropy bound need not hold after filtering for one particular x. The third row bounds the one-pair acceptance-probability difference for **any** decision rule on the two fixed-position nibbles, including nonlinear rules.

**Empirical calculation.** For each i, write c(x,j,y) for the number of observations where X_i=x and Y_j=y. The best adaptive nibble predictor on the sample scores exactly the sum over x of max over j,y of c(x,j,y). Maximizing over i then covers every allowed source position. For the bit score, first sum c over values y having a specified bit value, then optimize in the same order. For fixed i,j, empirical total variation equals the sum of the positive excess counts above n/256, divided by n. The per-depth extrema below range over both populations, all 21 differences and all relevant positions. A maximum in one column can come from a different test than a maximum in another. All three score columns use denominator 16,384.

| Rounds | Maximum nibble hits | Maximum bit hits | Maximum TV excess count | Minimum joint cell count |
|---:|---:|---:|---:|---:|
| 2 | 1496 | 9064 | 979 | 26 |
| 3 | 1502 | 9054 | 980 | 26 |
| 4 | 1497 | 9067 | 1005 | 23 |
| 5 | 1492 | 9077 | 1011 | 26 |
| 6 | 1492 | 9066 | 989 | 25 |
| 7 | 1488 | 9070 | 1007 | 26 |
| 8 | 1493 | 9045 | 989 | 26 |

**Confidence proof.** Fix a predictor and parameter case attaining the *population* maximum. Its sample score is binomial, including for adaptive target positions, since it applies one fixed success rule independently to each sampled base. The largest empirical score is at least this particular predictor's sample score. For total variation, fix a population-maximizing case, position pair and acceptance set A. The sample frequency of A is an average of independent Bernoulli variables. Its empirical excess over |A|/256 is bounded above by the maximum empirical total variation. In each instance lower-tail Hoeffding gives an upper confidence bound on the population maximum by adding sqrt(log(300)/(2n)) = 0.0131934 (rounded) to the corresponding empirical maximum. The three predeclared ceilings are 0.104869, 0.567210, and 0.074900, rounded upwards. Adding their three error allowances gives 1%. The argument bounds an overall maximum and does not give individual narrow error bars for fitted predictors. [Hoeffding, Probability Inequalities for Sums of Bounded Random Variables](https://doi.org/10.1080/01621459.1963.10500830)

For the two success probabilities, exact binomial inversion gives the sharper reported ceilings from the same observations. This refinement was derived after collection. For the fixed maximizing rule, its one-sided exact binomial upper endpoint is monotone in its hit count; replacing that count by the maximum observed count can only increase the endpoint. The lower tail at 1502 hits with success probability 0.098 is 0.003137823 or less. At 9077 hits and probability 0.5646 it is 0.003240361 or less. Both are strictly below 1/300, verified with integer arithmetic. Reporting the exact upper endpoints in place of the two Hoeffding endpoints uses the same two error allowances. There is no assumption of independence across families, rounds, positions, or the two populations.

### Data and verification for §14.6

The [study directory](reproduce/nibble_prediction_14/) contains the fresh OS sample, sampler, scorer, per-case output commitments and validation code. Seed SHA-256 is 6185b517de842f4ce78b17ea656e816e6b3be517a06a03a167d07e8ba211f682. For U_d a second implementation constructs the 35 Boolean equations from the scalar linear-prefix columns and the Research 12 roots. With one leading bit per independent equation, it retains 1237 uniform free bits and solves for 35 pivot bits in increasing order. Each admissible base is reached by exactly 2^35 seeds. The first 32 projected messages for every family were checked directly against the five root pairs. Hashes use the same H159 padded-state convention as §14.4.

GCC and Clang AVX2 runs agreed on the three original statistics and ordered-digest commitments in all 294 cases. A GCC scalar replay matched all four statistics and commitments for IDs 0 and 20, both populations and every depth (28 cases). An independently written NumPy scorer matched all four statistics for ID 0 at rounds 2 and 8 in both populations and gave the analytic answers on a uniform-product control and a constant control. The complete scalar panel was not rerun. Each stored digest commitment is SHA-256 of the concatenated array of first digests followed by the concatenated array of partner digests, in seed order.

Replay from the repository root on little-endian x86 with AVX2. The main study and confidence proof need only Python's standard library. The independent score check uses NumPy.

```bash
dir=reproduce/nibble_prediction_14
export PYTHONDONTWRITEBYTECODE=1
gcc -O3 -march=native -fPIC -shared -pthread krakken.c -o /tmp/kr14s.so
clang -O3 -mavx2 -fPIC -shared -pthread -I. "$dir/collect.c" krakken_multi.c -o /tmp/kr14_collect.so
clang -O3 -march=native -fPIC -shared "$dir/score.c" -o /tmp/kr14_score.so
python3 "$dir/study.py" /tmp/kr14_collect.so /tmp/kr14s.so /tmp/kr14_score.so > /tmp/kr14_nibbles.txt
cmp "$dir/results.txt" /tmp/kr14_nibbles.txt
python3 "$dir/bounds.py"
~/venv/krakken/bin/python "$dir/check.py" /tmp/kr14_collect.so /tmp/kr14s.so /tmp/kr14_score.so
gcc -O3 -march=native -DSCALAR -fPIC -shared -pthread -I. "$dir/collect.c" krakken.c -o /tmp/kr14_collect_scalar.so
python3 "$dir/study.py" /tmp/kr14_collect_scalar.so /tmp/kr14s.so /tmp/kr14_score.so 0 20
```

These results concern a single fresh base drawn from its specified population, with one source nibble available to the predictor. They leave open predictors that see more of the digest, correlate multiple bases, choose a different input difference, or select individual messages. The 3.35-bit result is local to one four-bit output.

## 14.7 — A deterministic lower bound across every byte cut of the ordinary digest

Let H_r be the ordinary 256-bit digest of a 159-byte message after r complete rounds, with r equal to **2 or 8**. Cut the message after any of bytes 0 through 157. Write x for the bytes before the cut and y for the remaining bytes. For a nonzero 256-bit mask β, the bit h(x,y) = β·H_r(x,y) is the XOR of the digest coordinates selected by β. Consider an exact representation over GF(2)

    h(x,y) = a(x) XOR b(y) XOR ⨁_{t=1}^k p_t(x) q_t(y).

All local functions may be arbitrary Boolean functions of their entire side. Only k, the number of products joining the two sides, is counted. The bounds below apply to the full H159 domain at **each** of its 158 contiguous byte cuts.

| Digest label | Two rounds, minimum required k | Eight rounds, minimum required k |
|---|---:|---:|
| Every nonzero parity of the entire 256-bit digest | ≥ 64 | ≥ 64 |
| Each individual digest bit, anywhere in the output | ≥ 252 | ≥ 252 |
| Every nonzero parity confined to the first digest byte | ≥ 253 | ≥ 253 |

These are lower bounds for exact representations of the displayed form. A circuit that repeatedly combines intermediate values from both halves is a different computational model. Research 01's SPLIT-LABEL-001 already excluded k=0 at a broader set of depths. The present theorem gives quantitative k at rounds two and eight.

### Why a matrix rank proves a lower bound on k

On a finite Cartesian grid choose anchors x₀,y₀ and form the Boolean matrix

    T_h(i,j) = h(x_i,y_j) XOR h(x₀,y_j) XOR h(x_i,y₀) XOR h(x₀,y₀).

This cancels a and b. Each product contributes the outer product of the vectors p_t(x_i) XOR p_t(x₀) and q_t(y_j) XOR q_t(y₀). Thus rank over GF(2) is at most k. Conversely, any rank factorization supplies exactly rank(T_h) such products on the grid. The missing anchor row and column are absorbed by a and b. On the enumerated grid the rank is therefore the *exact* minimum. On the full domain the same rank gives a lower bound by restriction.

### How one computation covers every nonzero digest parity

In the first grid vary byte 0 through x=0,…,64 and vary bytes 157 and 158 as a little-endian integer y=0,…,16448. All other bytes are zero. For each y>0, concatenate the 64 anchored mixed **256-bit digest vectors**, one for each nonzero x, into a 16,384-bit column. The 16,448 columns have GF(2) rank **16,384** at each depth. Repeat with byte 158 as x and bytes 0 and 1 as y. Both mirrored ranks are again **16,384**.

For any fixed β≠0, suppose the 64 rows of T_h have a nontrivial dependence with coefficients λ₁,…,λ₆₄. Then the concatenated vector (λ₁β,…,λ₆₄β) is nonzero and orthogonal to every witnessed column, contradicting full rank. Thus rank(T_h) ≥ 64 for **all 2^256−1 masks simultaneously**. The first grid works wherever byte 0 is separated from bytes 157 and 158. The mirror covers the cut between bytes 157 and 158 as well. Swapping the two sides preserves the number of cross products.

For the named labels, a simpler square grid varies byte 0 and byte 158 independently through all 256 values, again fixing everything else to zero. Every byte cut separates these endpoints. The 256 single-bit ranks have minimum **252** at each depth. The 255 first-byte parity ranks have minimum **253** at each depth. The full lists are retained in [the ordinary-hash results](reproduce/split_bounds_14/hash_cuts.txt).

**A consequence for the whole digest.** On the first grid, suppose a vector representation uses arbitrary 256-bit coefficient functions U_t(x) and shared scalar features v_t(y), with separate vector-valued terms for x and y. After taking anchored differences, all 16,384 rows belong to the span of the centered features v_t(y) XOR v_t(y₀). Their full rank therefore requires at least **16,384 shared Boolean features of the y side**. The mirrored grid supplies the same conclusion in its specified orientation. This stronger number counts features for the *whole vector* in this particular linear combination model.

**A consequence for message monomials.** Each mixed monomial in the unique Boolean algebraic normal form factors into a left monomial times a right monomial. Grouping by the left monomial gives a representation with one product per distinct nonempty left support participating in a mixed term. The same reasoning works on the right. On the endpoint-byte square, every single output bit therefore uses at least **252 of the 255 possible nonempty bit subsets of each endpoint byte** in terms involving the other byte. This conclusion already holds with every interior message byte fixed to zero.

## 14.8 — Digest differences on the minimum-activity populations

Fix one of the 21 Research 12 differences d and write D(m)=H_r(m) XOR H_r(m XOR d). Split the message after its first 79 bytes. The following exact results hold for **each** d, separately at rounds 2 and 8. All witness pairs have exactly five first-round active S-box calls.

| Property | Two rounds | Eight rounds |
|---|---:|---:|
| Cross products required for every nonzero parity of the full digest difference, on the full A1=5 population | ≥ 16 | ≥ 16 |
| Cross products required for every individual digest-difference bit on that population | ≥ 251 | ≥ 252 |
| Cross products required for each nonzero first-byte parity on that population | ≥ 252 | ≥ 252 |
| Distinct first-96-bit differences on each 65,536-message product grid | 65,536 | 65,536 |

The lower bounds in the first three rows also hold on the unrestricted H159 domain for these fixed d, since a representation on the larger domain must work on the witnesses. For the fourth row, **on the enumerated affine grid**, the digest difference has exactly 16 bits of min-entropy for a uniform base. In fact, for *any* base distribution supported on that grid, output-difference min-entropy equals input min-entropy. Injectivity on the grid proves this directly, even when the two halves are dependent. The full five-call population has dimension 1237. The census establishes injectivity on its specified 16-dimensional subset.

### Witness families and scope of the census

Use the five pairs of derivative roots {u,v} from Research 12. For each first-call byte z, set g=u XOR v, choose its least significant set bit j, and project z XOR u by deleting its component along g using bit j. The five projected bytes form an affine syndrome of rank 35 on message bits. Its zero set is the five-call population. The script constructs an origin in this set and directions in the homogeneous kernel. Each direction is supported wholly in the first 79 bytes or wholly in the last 80. A deterministic SHAKE-256 byte stream, keyed only by the public family ID and the direction label, chooses the vectors before projection. The construction checks their independence on each side and excludes d from the span. The base grid and its translate by d are consequently disjoint.

Use eight independent directions per side for the 256 × 256 grid. Also extend the right-side space to 13 directions and use the first 4161 settings against the first 17 left settings. For every enumerated pair the original scalar linear prefix and serial Chi were used to count active byte inputs for **both** calls in each of the 128 cells. Every count was five. The larger grid certifies stacked mixed rank 4096/4096 at each depth for each d: 16 left differences times 256 digest bits. The proof of §14.7 then gives rank at least 16 for every nonzero β. The square grid supplies the per-bit and per-byte ranks. Its mixed difference vectors also span all 256 output bits separately for every case.

### Exact accuracy bound for arbitrary independent left and right lookup tables

On each 256 × 256 five-call grid, take **any nonzero parity of the low nibble of the digest difference**. Two lookup tables see the left and right settings separately. Their entries can be chosen specifically for the parity, difference, and round count. If the tables' predicted bits are XORed, their success on the uniform grid is **strictly below 145/256 = 56.640625%**. Thus even unlimited local computation on each side leaves more than 43% errors in this model. This quantitative result uses the uniform distribution on each documented grid.

**Proof.** Let M have entries +1 or −1 given by the sign of the true parity on the grid. All 630 sign matrices (21 differences × 2 depths × 15 masks) have certified real operator norm strictly below 34. For sign vectors s,t of the two local tables, the correlation is sᵀMt/256². Both vectors have Euclidean norm 16, giving absolute correlation <34/256. Success equals (1+correlation)/2. If the settings are independent but nonuniform, replace the normalized sign vectors by their signed probability vectors. For example, when neither setting has point mass above 1/128, both Euclidean norms are at most 1/√128, giving success <63.28125%. These are direct norm bounds; the usual spectral bound for rectangles is discussed in [Sherstov's communication complexity lectures](https://web.cs.ucla.edu/~sherstov/teaching/2022-fall/).

**Rectangle corollary.** No A × B with |A||B| ≥ 1156 inside any of these grids admits a perfect split predictor for such a parity. A perfect fit there gives a sign submatrix equal to an outer product with operator norm √(|A||B|), which cannot exceed the norm of M. This rules out, for example, every 34 × 34 perfect rectangle simultaneously, even with different tables for different rectangles.

**Exact norm verification.** Floating point proposes an integer matrix L by rounding 4096 times a Cholesky factor of (34²−16)I−MMᵀ. The certificate checks the integer matrix E = 4096²(34²I−MMᵀ)−LLᵀ. For every row it verifies E_ii > sum over j≠i of |E_ij|. Symmetry and strict positive diagonal dominance imply E is positive definite, and LLᵀ is positive semidefinite. Hence 34²I−MMᵀ is positive definite. The minimum integer row margin across all certificates was **259,240,064** at two rounds and **259,411,636** at eight rounds. The verifier checks the sign entries and factor range. With |L_ij| ≤ 262144, dot products and the full row-margin sum fit signed 64-bit integers. A different floating-point proposal is acceptable only if it passes the same integer check.

### Evidence and replay for §§14.7–14.8

The [evidence directory](reproduce/split_bounds_14/) contains the deterministic generators, integer verifier, per-depth ranks, per-case commitments, and the independent block-elimination implementation. The code uses SHAKE only to specify reproducible five-call witness coordinates. The ordinary-hash theorem uses explicitly numbered input bytes and no pseudorandom directions. All conclusions are deterministic given the implementation. No MILP, SAT solver, statistical assumption, or random-permutation model enters the proofs.

The square grids record SHA-256 of the ordered base messages and of their ordered full digest XORs. The extended grids record the corresponding commitments in [the mixed-rank results](reproduce/split_bounds_14/ranks.txt). Within each family, x is the outer index and y the inner index. The 256 unit-mask ranks and 255 first-byte-mask ranks are stored as one byte per rank in index order, with masks 1 through 255 for the latter list. On a 256 × 256 grid the anchored row and column are zero, so the maximum possible rank is 255.

The main runs used the original Clang AVX2 permutation. For the ordinary-hash theorem, the GCC scalar replay reproduced all digest commitments and endpoint-square ranks. Independent Python block elimination, with reversed byte order relative to the C verifier, confirmed all four 16,384-wide ranks. The five-call checks used the scalar layer functions. GCC scalar replays for families 0 and 20 at both depths matched the AVX2 conditioned results and commitments. A separate high-pivot Python elimination agreed on each 4096-wide certificate for family 0. The ordinary eight-round scalar hash API matched 210 collector results selected across all 21 families and both sides of their pairs. Known-rank matrices, a Hadamard sign matrix and an all-ones sign matrix checked the verifier on both successful and failing controls. These are local computational certificates.

Source hashes used here were 4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6 for krakken.c, 83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c for krakken.h, and 9dd76eb1397ca433572ede8308b37b79e546e2b430f156e9c7b08f4f2ffc71f2 for krakken_multi.c. The commands use little-endian x86 with AVX2, the previous section's padded-state collector and the existing NumPy environment. Run from the repository root.

```bash
dir=reproduce/split_bounds_14
collector=reproduce/nibble_prediction_14/collect.c
py=~/venv/krakken/bin/python
export PYTHONDONTWRITEBYTECODE=1 OPENBLAS_NUM_THREADS=1
gcc -O3 -march=native -fPIC -shared -pthread "$dir/certify.c" krakken.c -o /tmp/kr14rank.so
clang -O3 -mavx2 -fPIC -shared -pthread -I. "$collector" krakken_multi.c -o /tmp/kr14_avx.so
gcc -O3 -march=native -DSCALAR -fPIC -shared -pthread -I. "$collector" krakken.c -o /tmp/kr14_scalar.so
"$py" "$dir/hash_cuts.py" /tmp/kr14_avx.so /tmp/kr14rank.so > /tmp/kr14_cuts.txt
cmp "$dir/hash_cuts.txt" /tmp/kr14_cuts.txt
"$py" "$dir/audit_global.py" /tmp/kr14_scalar.so /tmp/kr14rank.so > /tmp/kr14_cuts_scalar.txt
cmp "$dir/hash_cuts.txt" /tmp/kr14_cuts_scalar.txt
"$py" "$dir/study.py" /tmp/kr14_avx.so /tmp/kr14rank.so > /tmp/kr14_squares.txt
"$py" "$dir/ranks.py" /tmp/kr14_avx.so /tmp/kr14rank.so > /tmp/kr14_ranks.txt
cmp "$dir/results.txt" /tmp/kr14_squares.txt
cmp "$dir/ranks.txt" /tmp/kr14_ranks.txt
"$py" "$dir/check.py" /tmp/kr14_avx.so /tmp/kr14rank.so
```

On a different numerical library, rounded proposed factors can differ. In that case compare the digest commitments and ranks and require a fresh strictly positive integer margin for every sign matrix. The inequalities in §14.8 depend only on those verified margins being positive.

## 14.9 — Whole-function bit-AND lower bounds

There is also a bound in a circuit model that permits intermediate results to mix all message bits and be reused. Inputs are individual bits, arbitrary XOR, constants and fanout are free, and a gate counted here computes the AND of **two bits**. The objective is exact forward evaluation.

**Lemma.** Let G be a d-output Boolean vector function such that every nonzero linear combination of its outputs has algebraic degree at least D, with D≥2. Then the circuit needs at least **d+D−2** two-input AND gates.

**Proof.** Order the AND gates topologically. The j-th gate computes a function of degree at most j+1. To see this, give each AND output its own formal Boolean variable. Each gate is the product of two affine forms in the inputs and earlier gate variables. Substitute gate definitions in reverse order in the squarefree Boolean polynomial ring. A substitution for one variable increases degree by at most one, even with fanout, since each monomial contains that variable at most once. Now quotient the space of Boolean functions by the subspace of functions of degree at most D−1. The d outputs are linearly independent in this quotient by hypothesis. Input affine forms and the first D−2 gates have zero image there. The remaining gates must span at least d dimensions because every output is an affine combination of inputs and gate outputs. This proves the lemma. It combines the scalar degree argument and the vector span argument of Research 01's ALG-CIRCUIT-001 in a higher-degree quotient.

| Function evaluated exactly | Certified common degree floor D for all nonzero output parities | Minimum two-input bit ANDs |
|---|---:|---:|
| Ordinary 256-bit H159 digest at two rounds | 13 | **267** |
| Ordinary 256-bit H159 digest at eight rounds | 20 | **274** |
| Complete 2048-bit permutation at two rounds on unrestricted inputs | 9 | **2055** |
| Complete 2048-bit permutation at eight rounds on unrestricted inputs | 21 | **2067** |

For the first row, compute the vector algebraic normal form on the complete endpoint-byte square of §14.7 using the Boolean Möbius transform. The vectors of coefficients of monomials of degree at least 13 span all 256 digest coordinates. A nonzero β must have a nonzero coefficient among those monomials. Restoring the other input variables cannot lower the full function's degree below its restriction. At both depths the exact ranks for degree thresholds 13, 14, 15, and 16 were **256, 137, 17, and 1**, respectively. This also gives exact counts of masks attaining the higher degrees *on that square*: the number of nonzero masks of restricted degree below t is 2^(256−rank_t)−1.

The other three degree premises are inherited from [Research 02](KRAKKEN_RESEARCH_02.md), respectively WORK-PERM-R8-FULLSTATE-DEGREE20-033 (its stated H159 corollary), WORK-INT-FULL2048-BYTE-ALLMASK-R2-045 and WORK-INT-FULL2048-R8-DEGREE21-CUBE-047. The large earlier certificates were not recomputed for this corollary. GCC scalar and Clang AVX2 gave identical endpoint-square coefficient commitments and threshold ranks. The new results are in [degree.txt](reproduce/split_bounds_14/degree.txt). Replay with the preceding setup:

```bash
"$py" "$dir/degree.py" /tmp/kr14_avx.so /tmp/kr14rank.so
"$py" "$dir/degree.py" /tmp/kr14_scalar.so /tmp/kr14rank.so
```

An AND count measures the cost of exact forward computation in this model. Collision and preimage search have different objectives.

## 14.10 — Fixed-offset four-message probabilities across rounds, design

For each of the 21 five-call differences d, use the first 8192 bases of the §14.8 square (five left and eight right directions). For every nonzero index offset e among its 8191 directions, enumerate the full 256-bit four-message digest XOR at depths 1 through 8. Record full-target multiplicities, zero targets, and low-nibble distributions, including every first-round outcome. Symmetric base pairs count twice.

In a separate population study, draw 16,384 new OS-random H159 bases once. Use them directly and projected uniformly onto each family's five-call set. Fix the three secondary index offsets 1, 256, and 257, chosen before collection to represent a right-only change, left-only change, and their combination. For depths 2 through 8, report a single joint 99% confidence panel for zero full-target probability and maximum full-target probability, with equal error allowances. Record round one separately as a control. Preserve the first sample and all results.

### 14.10.1 — A probability-one first-round event with 34 to 90 fixed state bits

Fix one of the 21 Research 12 H159 differences d. Write Δ_r(m)=S_r(m) XOR S_r(m XOR d) for the full-state difference. On the entire conditional population A1=5, there is a family-specific mask K_d and value v_d for which **Δ₁(m) AND K_d = v_d with probability one**. The masks have 34–90 full-state bits, including 4–16 digest bits. The largest, for classification ID 15, fixes **90 state bits, including 16 digest bits**. Every family's prescribed value has at least one nonzero digest bit. Hence these conditioned pairs cannot collide on the complete digest at one round. These masks certify sufficient fixed coordinates. Their maximality is open.

**Derivation.** Each classified difference has five mandatory first-call S-box activations. Equality A1=5 leaves every second-call input unchanged. In each pair of 64-bit pre-Chi words a,b the second call sees b XOR ROL32(a′), where a′ is the first-call output word. Thus Δa′=ROL32(Δb) and the second-call output difference is zero. This fixes the entire post-Chi difference. Butterfly transports it linearly to the input of Pressure. Research 02's WORK-DIST-A15-R1-TWOQUERY-025 had already used the four carry-free digest bits in three families. Here we use the complete 21-family classification and also follow carries above bit zero.

For addition modulo 2^64, suppose the operand XOR differences dx,dy are known on the low k bits. If both are zero below bit j, the two executions have identical carries into bits 0 through j. The sum difference there is exactly dx XOR dy. Taking j as the first set bit of (dx OR dy) within those k bits, or keeping all k if there is none, gives the low-bit mask used here. For the first Pressure sum A=a+(c XOR (c>>17)), both operand differences are known on 64 bits. For its dependent sum C=c+(A XOR (A<<31)), use the known low bits of ΔA, and similarly for the odd-word branch. The fixed XOR round constants cancel; rotations and Ink relocate the resulting masks. [All masks and prescribed values in output-byte order](reproduce/quartet_probability_14/masks.txt)

By Research 12's exact population mass, the **unconditional** uniform-H159 probability of the ID 15 first-round masked event is at least 2^-35. For a uniform ideal 2048-bit permutation on the same distinct input pair the corresponding probability is 2^1958/(2^2048−1), since the prescribed 90-bit pattern is nonzero. Thus the probability lower bound for the actual one-round state event is about 2^55 times the ideal probability. The 90-bit comparison uses full states; only 16 of those bits are in the digest.

**What survives another round?** On each 65,536-base five-call grid of §14.8, all bases matched their family's complete mask at round 1, and **zero** matched at each depth 2–8. For uniform bases on the entire five-call population, and also on all H159, the new 16,384-base sample found zero full-mask matches at every depth 2–8 for every family. A joint no-hit rule bounds each of these population probabilities below **1/3000** with confidence exceeding 99.57%. Its false-pass calculation is (1−1/3000)^16384 < 0.004245, using a fixed violating case as in §14.10.3. This is a separate post-design analysis of source-derived masks. The whole-population probability was one at R1 on the five-call set. Only the finite grids give an exact zero at later depths. [Per-round counts, including the digest-only masks](reproduce/quartet_probability_14/patterns.txt)

**Partial qualification check.** I also tested what the same proof gives when only a subset of the five roots is required. For s chosen cells the qualifying event has exact probability 2^(-7s) under uniform H159, by the joint rank-40 input theorem in Research 12. For each other active cell, relax both post-Chi output bytes to arbitrary differences. Propagate each of their 16 unit variations through the linear Butterfly map. Retain only low operand bits unchanged by all these variations before applying the carry lemma. Across all 672 family/subset combinations, the largest full-state fixed-bit counts for s=0,1,2,3,4,5 were 0,0,0,14,24,90. All nonempty partial masks were also checked on eight bases conditioned only on the specified cells. Removing root conditions in this relaxation did not improve the family-15 probability ratio. A zero here describes the limitation of the relaxation. [All subset masks and probability exponents](reproduce/quartet_probability_14/partial.txt)

### 14.10.2 — Exact four-message probabilities for all offsets on a conditioned affine family

Write H_r for the first 256 output bits after r complete rounds, D_r(m)=H_r(m) XOR H_r(m XOR d), and

    Q_r(m;d,e) = D_r(m) XOR D_r(m XOR e).

For each fixed d, take the 13-dimensional affine family F_d=x₀+V_d formed by the first 8192 indices of the §14.8 grid. It varies five left directions and all eight right directions. For every nonzero e in V_d the four messages are distinct: d lies outside V_d. Both d-pairs satisfy A1=5. Adding d gives the second parallel copy of F_d and does not change the quartet XOR.

**Full digest theorem.** For every one of the 21 d, every one of the 8191 nonzero secondary directions per family, and **each depth 1 through 8**, the distribution of Q_r on uniform F_d has exactly 4096 distinct values. Every attainable value has probability **2/8192 = 2^-12**. The all-zero value has probability **zero**. In particular, two distinct pairs in the same fixed direction cannot give matching four-message XORs unless they describe the same quartet. Equivalently, in the 14-dimensional union F_d ∪ (F_d XOR d), the 4096 cosets of each plane spanned by d and e give 4096 distinct, nonzero four-message sums.

**Proof by complete enumeration.** Compute the 8192 full digest differences D_r. For each nonzero e, partition indices into 4096 unordered pairs {x,x XOR e}. Compare all four 64-bit words of the XOR key when counting multiplicities. Every one of these 4096 keys was distinct. Zero was absent, also following from the separately certified injectivity of D_r on the 8192 bases. Restoring the two orientations gives multiplicity two per key, the minimum possible maximum. The enumeration covers 1,376,088 family/depth/offset cases. This theorem applies to the stated affine families. Injectivity on a finite grid cannot supply the maximum point probability on the surrounding 1237-dimensional conditional domain. [Full-target census and commitments](reproduce/quartet_probability_14/flat.txt)

**Carry-free digest signature.** Let π select bits 11, 94, 139 and 210 in that order, numbering digest bits from zero, least significant bit first within each byte. These are the four digest-visible projections of the carry-free Pressure bits. At round 1, π(D₁) is fixed for each d on its whole five-call set. Consequently π(Q₁)=0 whenever both d-pairs qualify, including every e considered here. Starting at **two rounds**, all sixteen values of π(Q_r) are attained for **every** tested e and d. This also proves that none of those values can be forbidden on the entire five-call domain for any of the specified directions. Uniform probabilities below use only the exhaustively enumerated affine family.

| Complete rounds | Smallest count of any signature | Largest count of any signature | Largest count of the zero signature | Largest total variation from uniform, numerator |
|---:|---:|---:|---:|---:|
| 1 | 0 | 8192 | 8192 | 7680 |
| 2 | 368 | 676 | 646 | 410 |
| 3 | 370 | 686 | 660 | 406 |
| 4 | 362 | 672 | 646 | 390 |
| 5 | 364 | 700 | 650 | 394 |
| 6 | 368 | 684 | 652 | 388 |
| 7 | 370 | 666 | 650 | 386 |
| 8 | 366 | 666 | 666 | 394 |

All columns use denominator 8192. Each extremum ranges over the 21 differences and all offsets, and the first two also range over all sixteen values. The baseline uniform probability for any one signature is 1/16. For example the largest observed probability of retaining the **zero** signature at round 2 is exactly 646/8192, or about 7.886%. At round 8 it is 666/8192, or 8.130%. Full quartet XOR equality and equality on four selected bits are different events.

**Exact counting method.** For z(x)=π(D_r(x)) and each four-bit mask u, form a_u(x)=(−1)^(u·z(x)). The XOR autocorrelation at e is the inverse Walsh transform of the squared Walsh coefficients of a_u. Applying the 16-point inverse transform across u gives the integer counts for every signature at e. The checker verifies divisibility, nonnegativity and total count 8192 for every row. Direct counts for four directions per case agree. The same computation for the low digest nibble independently reproduces the direct census's extrema and total variation. [Projected counts and table commitments](reproduce/quartet_probability_14/flat_projection.txt)

### 14.10.3 — Population probabilities for three fixed secondary offsets

For each d fix e from grid indices 1, 256 or 257 relative to the origin. These correspond to one right-side direction, one left-side direction, and their XOR. The distribution is either uniform over all H159 bases, or uniform over the **entire** matching 1237-dimensional five-call population. The second difference is fixed before the base is drawn, so the pair bases m and m XOR e are correlated by construction. This differs from the independent-pair result in §14.5.

At each depth 2–8, all 16,384 full quartet XORs were distinct and nonzero in **every one of the 882 cases**. Under the independent uniform seed model, the following two conclusions have simultaneous confidence exceeding **99.27%**, across the specified depths, primary and secondary differences, and both populations:

* The probability of a **zero** 256-bit quartet XOR is below **1/3000**.
* The probability of **any prescribed** 256-bit quartet XOR is below **1/2048 = 2^-11**.

For zero, a fixed case with probability at least 1/3000 passes the no-hit condition with probability at most (1−1/3000)^16384 < 0.004245. For arbitrary targets, fix a violating case and one violating target. Its count must be at most one for the all-distinct condition to pass. The binomial lower tail at p=1/2048 is <0.003015, decreasing with p. Requiring the entire panel to pass controls each null by its one fixed violating case, irrespective of dependence between tests. The sum of the two error bounds is below 0.00726. Each test also meets its preassigned 0.005 allowance. These are confidence bounds on fixed probabilities. They do not model an adaptive choice of bases.

Since e is in the homogeneous kernel of the five-call equations, both d-pairs have A1=5 exactly when the first one does. The Research 12 mass is thus 2^-35 for their **joint** qualification under an unconditional uniform base. By the chain rule, the probability that both qualify **and** a prescribed full quartet target follows at a specified depth 2–8 is **below 2^-46** for the three tested offsets at the confidence level of the arbitrary-target panel. For an algorithm drawing uniformly within the five-call population, only the conditional factor applies.

Two consequences from the retained data use separate reporting rules:

* Across the two populations and three offsets the largest empirical count for any one of the 16 carry-free signatures at any later depth was 1145. Fix the true maximizing case and signature. Its count is binomial and at most the observed overall maximum. The exact lower tail at 1145, n=16384 and p=0.076 is <0.001481. Thus a separate upper confidence bound below **7.6%** for every projected target has coverage above 99.85%, using one-sided binomial inversion. The four-bit observable was selected from the source's carry-free coordinates after the initial full-target study design.
* If two independent base draws each produce a quartet with the same fixed d,e in the same population and at the same depth, the probability that their full quartet XORs match is below **2^-22** at greater than 99.56% confidence, simultaneously across the same later-depth cases. This is the collision probability of the full quartet-XOR distribution. Apply the no-repeat inequality proved in §14.2 with n=16384, λ=0.95n. If C≥2^-22 then λ√C≥7.6, giving false-pass probability at most 8.6 exp(−7.6)/(1−exp(−20.48)) <0.004305. This is a post-collection corollary of the original pass event.

### Evidence and replay for §14.10

[Evidence directory](reproduce/quartet_probability_14/). The seed file has SHA-256 f7d03b3a2b9d7b4dbd627de15b58e4c9911cef898cda8dddc0711f67727061a1. Conditioning uses a linear right inverse of the rank-35 syndrome, including the affine padding offset, as in §14.4. Every conditioned base has equally many preimages. Shared seeds create dependence across cases only. The scalar serial-Chi counter checks every base of the 13-dimensional witness families and all newly sampled conditioned bases. Other vertices qualify by the affine-kernel argument.

The AVX2 collector invokes the original layer functions in round order and retains intermediate outputs. Original scalar full-state round calls matched **2352** independently recomputed 2048-bit checkpoints across all families and depths. An independent five-bit exhaustive addition check covers the carry lemma with wraparound. Full-target counting compares full 256-bit keys; hash-table slot collisions cannot establish target equality. An independent scalar digest and sorting audit reproduced all 168 first-derivative commitments, verified injectivity, and confirmed distinct unordered pair sums for every offset at every depth. Its linear 64-bit projection is sufficient whenever all projected keys differ; on ties the audit compares all 256 bits. The GCC scalar checkpoint collector independently reproduced the complete fresh-sample quartet counts and all ordered quartet-output commitments for classification IDs 0, 15 and 20, at every depth, in both populations and for all three offsets. The projection census uses the standard XOR autocorrelation identity. [Carlet, Boolean Functions for Cryptography and Coding Theory, equation 2.52](https://www.math.univ-paris13.fr/~carlet/book-fcts-Bool-vect-crypt-codes.pdf)

Run from the repository root with the NumPy environment. The library arguments refer in order to the public scalar collector, the scalar layer/checking library from §14.8, and the checkpoint collector. All commands read the retained sample; no resampling is needed.

```bash
dir=reproduce/quartet_probability_14
py=~/venv/krakken/bin/python
export PYTHONDONTWRITEBYTECODE=1 OPENBLAS_NUM_THREADS=1
gcc -O3 -march=native -shared -fPIC -pthread -I. -DSCALAR reproduce/nibble_prediction_14/collect.c krakken.c -o /tmp/q14_public.so
gcc -O3 -march=native -shared -fPIC -pthread reproduce/split_bounds_14/certify.c krakken.c -o /tmp/q14_layers.so
clang -O3 -mavx2 -shared -fPIC -pthread -I. "$dir/snapshots.c" "$dir/census.c" -o /tmp/q14_avx.so
gcc -O3 -march=native -shared -fPIC -pthread -I. "$dir/scalar_snapshots.c" "$dir/census.c" -o /tmp/q14_scalar.so
libs=(/tmp/q14_public.so /tmp/q14_layers.so /tmp/q14_avx.so)
"$py" "$dir/panel.py" "${libs[@]}" flat > /tmp/q14_flat.txt
"$py" "$dir/panel.py" "${libs[@]}" population > /tmp/q14_population.txt
"$py" "$dir/projections.py" "${libs[@]}" flat > /tmp/q14_flat_projection.txt
"$py" "$dir/projections.py" "${libs[@]}" population > /tmp/q14_population_projection.txt
"$py" "$dir/masks.py" "${libs[@]}" > /tmp/q14_masks.txt
"$py" "$dir/partial.py" "${libs[@]}" > /tmp/q14_partial.txt
"$py" "$dir/patterns.py" "${libs[@]}" > /tmp/q14_patterns.txt
"$py" "$dir/audit.py" "${libs[@]}" > /tmp/q14_audit.txt
for name in flat population flat_projection population_projection masks partial patterns audit; do
    cmp "$dir/$name.txt" "/tmp/q14_$name.txt" || exit 1
done
"$py" "$dir/check_masks.py" "${libs[@]}"
"$py" "$dir/summary.py"
"$py" "$dir/panel.py" /tmp/q14_public.so /tmp/q14_layers.so /tmp/q14_scalar.so population 0 15 20
```

## 14.11 — Choosing messages by adaptive parity tests (20 November 2026)

The main case is classification ID 15, for which the five-call condition fixes 90 first-round state difference bits. Work on the entire affine set C of 159-byte bases satisfying A1=5 for that difference d. Let B be bit 11 of the base's one-round digest. Let Y be bits 11, 94, 139 and 210 of the r-round digest difference between the base and its partner, for each r from 2 through 8. Allow observation of B and two arbitrary, possibly adaptive affine parity tests on the message. On a fixed transcript their outcomes impose at most two independent affine equations on C.

**Probability study design, before drawing its random maps.** Use twelve independently generated uniform affine maps of 17 bits into C by projecting OS-random origins and directions. Use the same maps for all seven depths. Require in every map and round an upper envelope ≤0.044 for joint categories (B,Y), a lower envelope ≥0.465 for either B value, and no repeat of the first 96 bits of the full digest difference. The envelopes cover every nonempty local affine slice of codimension at most two. Test the population thresholds 0.046 for joint-category mass, 0.46 for B-branch mass, and 0.46/4096 for a prescribed full-difference mass before observing B, all conditional on the message affine equations. Preserve every map and report failures. This probability study is separate from the deterministic finite-field proof below.

### 14.11.1 — Every consistent branch of a two-test selection rule admits all sixteen outcomes

Fix ID 15 and allow the analyst to learn B, then choose any parity of the 1,272 message bits, then choose a second parity depending on the earlier observations. A parity is the XOR of any selected bits, with an optional constant. For each r=2,…,8, for **every** resulting transcript whose message equations are consistent on C, and for **every** four-bit target z, there exists a message in C realizing that transcript and Y=z. This is a deterministic statement on the entire 1,237-dimensional population. The order can be changed if the same three observations are used. At depth one the difference on these four coordinates is fixed throughout C by §14.10.

Fixing a transcript fixes its masks and answers. The message equations cut out an affine set A of codimension c≤2 in C. It suffices to realize every (B,Y) in {0,1}×{0,…,15} inside each such A. This also rules out any universally missing value on any nonempty union of these transcript branches.

**Covering all parity choices.** Write C as an affine origin plus the image of a surjective linear map P from 1,272 raw bits. The rank-35 root equations of Research 12 give a projection: project raw words along a linear right inverse of their homogeneous syndrome and add the fixed correction for padding and the prescribed roots. Its linear part fixes the kernel pointwise. Thus a set of c independent equations on C pulls back to c independent equations on the raw bits.

Identify the raw bits with 106 words in the field F with 4096 elements. The binary polynomial used for the field is x^12+x^6+x^4+x+1. The certificate checks that multiplication by x cycles through all 4095 nonzero residues, which also verifies this is a field. For a slope t in F use the 12-bit parameter s and the following raw inputs:

    v_t(s) = (s, st, st², …, st^105).

Each binary linear form on these words restricts to a function of the form L(s p(t)), for a polynomial p of degree at most 105 and one fixed nonzero binary linear form L on F. Indeed every binary linear form on one field word has the form a ↦ L(ca): different c give different forms because multiplication by a nonzero field element is bijective. The 106 coefficients encode the raw linear form uniquely. In particular, a nonzero form has a nonzero p and vanishes identically on at most 105 slopes.

For c independent equations, restriction to v_t loses rank only if some nonzero combination vanishes there. At most (2^c−1)·105 ≤ **315** slopes can lose rank. Consequently among **316 distinct slopes** there is one on which the prescribed c answers can be attained. Its local parameter set is a nonempty affine slice of codimension c in twelve variables. The affine origin only changes the right-hand sides. This elementary root count is the entire covering argument. For broader background on preserving rank with a family of linear maps, see [Forbes and Guruswami, Dimension Expanders via Rank Condensers](https://arxiv.org/abs/1411.7455).

**Checking each slope.** On all 4096 local inputs, form the 32 labels (B,Y). For one label let N be its occurrence count and W(u) its unnormalized Walsh coefficient as an indicator function. For two independent local masks u,v, four times the count in a chosen slice is

    N + a W(u) + b W(v) + ab W(u XOR v),    with a,b in {−1,+1}.

For one mask the corresponding numerator is N+aW(u). If N exceeds the sum of the three largest distinct-mask absolute coefficients, all slice counts are positive. Otherwise it suffices to check pairs with a member of {u,v,u XOR v} of magnitude at least N/3: every missed slice must have such a member. The program tests the four signs for each required span. All 316 slopes passed for all 32 labels at **each of the seven depths**. The finite-field argument lifts these finite checks to every allowed global transcript. [Per-slope results](reproduce/affine_selection_14/slopes.txt)

### 14.11.2 — One arbitrary parity combining message bits and the complete first-round base digest

A different exact result covers **all 21** classified differences. Write C_d for the corresponding five-call set. Allow a single affine test on the concatenation (m,H₁(m)), where the observed base digest has all 256 bits. For every such test nonconstant on the ambient product C_d × {0,1}^256, either answer, any of the sixteen Y values, and every r=2,…,8, **there is a witnessing message**. By exchanging the two messages, the statement also holds when the single observed digest belongs to the partner.

**Proof.** For each combination of d, r and Y=z, form binary rows (1,m,H₁(m)) using valid witnesses with that z. Their maximum possible rank is 1+1237+256=1494. All **2352** matrices attained exactly 1494, so the affine hull of each target fiber in these joint coordinates equals the entire ambient product. If a nonconstant test omitted either answer on a fiber, that fiber would lie in a proper affine hyperplane. The contradiction proves the theorem. This works over GF(2), where omitting one binary answer forces the opposite one everywhere. This result allows any parity of the complete base digest mixed with message bits. The two-test theorem in §14.11.1 uses the specified first-round bit B. [All ranks and witness commitments](reproduce/affine_selection_14/joint.txt)

### 14.11.3 — A probability bound for the most favorable allowed branch

For ID 15 and every r=2,…,8, choose any consistent message slice A of codimension at most two in C and either B outcome. Draw the base **uniformly within that selected branch**. Under the independent uniform OS-seed model, the following hold jointly with confidence **greater than 99.9997%**.

| Quantity in any allowed branch | Bound |
|---|---:|
| Probability of any prescribed four-bit difference Y=z | < 10% |
| Probability of any prescribed full 256-bit digest difference, including zero | < 1/4096 |
| Probability of either B outcome before observing it, conditional on the message equations A | > 46% |

Thus a predictor may tailor its four-bit guess to each observed transcript and still has success below 10% when a uniform qualifying base is used. Blind uniform guessing gives 6.25%. The gap allows smaller biases. The exact reachability theorems do not require uniform sampling, while these probability bounds specify how a message is drawn inside the branch. Choosing individual messages using additional information can change that distribution.

**Why small random maps bound a worst-case global filter.** Consider one 17-bit map Φ(s)=O+Σs_i V_i. Its origin is uniform on C, its directions are independently uniform on the direction space of C, and the twelve maps are independent. This follows from the surjective projection above. We do not reject dependent direction choices. For a fixed affine slice A of codimension c≤2, the c equations restricted to the map have full coefficient rank except with probability ≤(2^c−1)2^-17 ≤3/131072. This follows by a union bound over nonzero combinations. On full rank there are M=2^(17−c)≥32768 local parameters mapping into A.

Condition on the origin and directions **only modulo the homogeneous direction space of A**. The remaining components are independent and uniform in that space. For any two different local parameter strings meeting the equations, their images are pairwise independent uniform points in A: the two coefficient rows (1,s) and (1,s′) have rank two. Hence an event of population fraction p on A has empirical-fraction variance p(1−p)/M. Joint independence of all M observations is unnecessary.

**Three false-pass calculations.** In every random map the integer Walsh envelopes bound the empirical rates on *every* nonempty codimension-≤2 slice. The highest joint-label envelope was 5182/131072, the lowest B envelope was 62812/131072, and every map/depth had 131072 distinct 96-bit difference prefixes. These meet the predeclared local acceptance thresholds. To bound a false report, fix one violating global parameter case before drawing the maps. A passing panel must pass for this particular case on each map.

1. If Pr[B=b,Y=z | A]≥0.046, a passing full-rank map must undershoot to ≤0.044. Cantelli's one-sided variance inequality gives error ≤v/(v+g²) with g=0.002 and v=0.046·0.954/32768 at the threshold. The ratio decreases for larger p, since p(1−p)/(p−0.044)² decreases for p>0.044.
2. If Pr[B=b | A]≤0.46, a passing full-rank map must overshoot to ≥0.465. Use g=0.005 and v=1/(4·32768). The complementary event also has this bound since either b can be selected.
3. If a full difference target has mass p≥0.46/4096 on A, its local count has mean μ=Mp≥32768·0.46/4096 and variance ≤μ. No repeated 96-bit prefix implies the count is ≤1. The full-rank error is at most μ/(μ+(μ−1)²), decreasing above μ=1.

For each calculation add 3/131072 for rank loss and raise the resulting bound to the twelfth power. The three false-pass bounds are respectively below 6.209×10^-8, 2.674×10^-8, and 2.288×10^-6. Their sum is below 0.00000238. No independence between target labels, masks, or round depths is assumed. Finally divide the joint-label ceiling by the B-mass floor: 0.046/0.46=0.1. For a full target its intersection with B is bounded by its mass on A, so the same division gives 1/4096. This controls the maximum over the specified selectors; it does not treat the number of possible masks as the number of independent experiments. [Map measurements](reproduce/affine_selection_14/probability.txt)

### Evidence and replay for §14.11

The [evidence directory](reproduce/affine_selection_14/) contains the certificates, generators, probability maps and independent checkers. The twelve random maps use the saved 34,344 OS-random bytes with SHA-256 3a16b492968b36600b4a080aa0ff2da9c066c2720f56150680343ac15c7d79d0, interpreted as little-endian 159-byte words. They are independent of the deterministic slopes and graph witnesses. The graph witness generator uses SHAKE-256 solely to give a reproducible list of 32,768 message seeds. Its rank argument does not require random witnesses. Zero-based digest bit numbers are least-significant-bit first within each byte.

The original-layer scalar replay agreed with all 316 AVX2 slope commitments and all 84 probability-panel rows and commitments. For the joint graph it matched the ID-15 commitments and ranks at all seven depths. The independent slope checker multiplies field words by polynomial shift-and-reduce, checks the projection has rank 1237, and counts five active calls directly on all its witnesses. For potentially exceptional Walsh masks u it checks that the points of each label on each side of u span that local hyperplane (dimension 11). This independently establishes positivity on every further nonconstant parity cut. For the graph theorem, an independent block elimination with reversed byte order reconstructed all 32 ranks for ID 15 at rounds 2 and 8. The probability checker independently computed all seven envelopes on map zero with NumPy and checked 1,024 base/partner digest evaluations against the original scalar round-count entry point. Synthetic constant labels and labels fixed by input coordinates both failed the local coverage test as expected. These are local computer-assisted proofs and statistical certificates.

Reproduction uses the existing NumPy environment and little-endian x86 with AVX2. Run the following commands from the repository root. The first two libraries provide the scalar reference and the conditioned-population checks used in §§14.7–14.10.

```bash
dir=reproduce/affine_selection_14
qdir=reproduce/quartet_probability_14
py=~/venv/krakken/bin/python
export PYTHONDONTWRITEBYTECODE=1 OPENBLAS_NUM_THREADS=1
gcc -O3 -march=native -fPIC -shared -pthread -DSCALAR -I. reproduce/nibble_prediction_14/collect.c krakken.c -o /tmp/sel_public.so
gcc -O3 -march=native -fPIC -shared -pthread reproduce/split_bounds_14/certify.c krakken.c -o /tmp/sel_layers.so
clang -O3 -mavx2 -fPIC -shared -pthread -I. "$qdir/snapshots.c" "$qdir/census.c" -o /tmp/sel_avx.so
gcc -O3 -march=native -fPIC -shared -pthread -I. "$qdir/scalar_snapshots.c" "$qdir/census.c" -o /tmp/sel_scalar.so
gcc -O3 -march=native -fPIC -shared "$dir/block.c" -o /tmp/sel_block.so
avx=(/tmp/sel_public.so /tmp/sel_layers.so /tmp/sel_avx.so /tmp/sel_block.so)
scalar=(/tmp/sel_public.so /tmp/sel_layers.so /tmp/sel_scalar.so /tmp/sel_block.so)
"$py" "$dir/selector.py" "${avx[@]}" 15 > /tmp/sel_slopes.txt
cmp "$dir/slopes.txt" /tmp/sel_slopes.txt
"$py" "$dir/joint.py" "${avx[@]}" > /tmp/sel_joint.txt
cmp "$dir/joint.txt" /tmp/sel_joint.txt
"$py" "$dir/check.py" "${scalar[@]}"
"$py" "$dir/joint_check.py" "${scalar[@]}"
"$py" "$dir/probability.py" "${scalar[@]}" > /tmp/sel_prob.txt
cmp "$dir/probability.txt" /tmp/sel_prob.txt
"$py" "$dir/check_probability.py" "${avx[@]}"
"$py" "$dir/summary.py"
```

## 14.12 — Full-digest collision-hunter checkpoint (22 November 2026)

The operator reported 272,776,683 committed candidates, zero full-digest collision events, and 15,889.20 MiB for the database plus WAL. This entry interprets the reported checkpoint from the hunter source. The live database and running binary were not audited.

**Input domain.** The hunter sends the 32 ASCII bytes of `KHASH-FULL256-COLLISION-HUNT-V1:` followed by a 16-byte unsigned big-endian counter to the full eight-round hash API and requests 32 digest bytes. The tag's terminating C NUL is excluded. The counter starts at zero, increments by one, and resumes from the committed next counter. The reported prefix therefore covers counters 0 through 272,776,682 inclusive, all distinct 48-byte messages. The package's scalar source and header match the research copies byte for byte. Its AVX2 source differs and supports an AES-NI path. On AVX2 startup the hunter compares six test counters against scalar. [Hunter source](/home/user/Downloads/khash_collision_hunter/khash_collision_hunter.c:77)

**Collision accounting.** The SQLite primary key is the entire 32-byte digest. On a duplicate key the hunter retrieves the original counter, requires two different counters, and recomputes both digests with scalar Krakken. A verified match adds a collision record and advances both the event count and the processed-candidate count. A failed verification aborts the batch. Digest rows, collision rows, and next-counter metadata commit together. The displayed unique count is computed as next counter minus collision events. A third message with the same digest would add one further event. [Insertion and commit logic](/home/user/Downloads/khash_collision_hunter/khash_collision_hunter.c:525)

**Finite result.** The reported run found no collision among 37,203,559,257,852,903 unordered pairs of distinct inputs in this prefix. In particular it exhausts the affine family obtained by fixing the first 356 message bits in big-endian order and varying the low 28 counter bits. For every nonzero XOR offset confined to those 28 bits, the observed full-digest collision frequency over that entire family is exactly zero. For independent uniform draws with replacement from the reported prefix itself, digest equality has probability exactly 1/272,776,683, entirely from drawing the same input twice.

For an ideal 256-bit random function evaluated on these distinct inputs, the expected number of colliding pairs is approximately 3.213 × 10^-61. The earlier hypothetical 50.5-bit statistical bound required independent random draws from a broader input distribution. Sequential counter enumeration does not meet that assumption.

# Solver-free diffusion and counting baselines

Reviewed 2026-10-11 from [BOUNDS](../BOUNDS.md) and [RESULTS18](../RESULTS18.md).
The current C/header pins are respectively
`4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6` and
`83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`.

These statements are mathematically proved in their stated domains. Only
the source-specific MDS result receives a new permanent ledger ID:
[LIN-MDS-001](KRAKKEN_SECURITY_THEOREMS.md#lin-mds-001). The other four
are reference/calibration lemmas, not four newly eliminated attack families.
The proposed `BOUND-*` labels in the original note remain provisional.

| Statement | Domain | Result | Role |
|---|---|---|---|
| MDS branch number | Every nonzero eight-byte field vector | Exact9; cumulative MDS input/output incidences≥9R | Source-specific diffusion lemma |
| Random-pair activity | Uniform ordered distinct unrestricted state pairs | Per-round zero-truncated Binomial(256,255/256); total expectation255R/(1−2^-2048) | Exact calibration, not adversarial floor |
| Image distance | Full-state images of all valid159 messages, any R1–R8 | A distinct pair at distance≤304 exists | Generic nonconstructive necessity |
| Differential mass | H full-state injective map, fixed nonzero output difference | Sum over nonzero input differences equals image-translate overlap≤1 | Generic accounting identity |
| Fourier energy | H; full-state masks, or digest masks where specified | Exact energies and threshold counts | Generic accounting; no maximum-correlation bound |

## MDS: exact source-specific branch number

Let coefficients c=(1,1,4,1,8,5,2,9) and
M[i,j]=c[(j−i) mod8] over GF(256), polynomial0x11D.
The scalar layer independently applies M to32 slices: each state row y=0,…,3
and byte offset b=0,…,7 across lanes4j+y. Every square minor is nonsingular.
Counts by size1,…,8 are64,784,3136,4900,3136,784,64,1, total12,869.

For nonzero v of support size t, at least t zero output coordinates
would force a singular t×t minor on those rows and support columns.
Thus wt(Mv)≥9−t, and wt(v)+wt(Mv)≥9. A one-byte input attains9 because
every coefficient is nonzero; for v=(1,0,…,0), Mv=(1,9,2,5,8,1,4,1).

For any distinct full-state pair, all layer-boundary states remain distinct
by the existing bijectivity premises. Each MDS layer therefore has a
nonzero slice. If B_r counts nonzero bytes entering **plus** leaving MDS,
B_r≥9, and sum from r=1 to R is≥9R for R=1,…,8. A sharper local form is
B_r≥9 times the number of nonzero entering slices. These count incidences
at the two boundaries, not distinct bytes or active serial-Chi calls.
The cumulative bound is not claimed sharp. It applies to H pairs as a subcase.

The new independent implementation audit uses carryless polynomial product
and polynomial long division, reverse-column Gauss–Jordan elimination,
all12,869 minors,1536 original-C packed multiplications and2048 original-C
MDS binary basis vectors. Unlike RESULTS18's replay of supplied code,
this is a separate implementation audit. The layer equation itself and
its bytewise linearity follow from the source; basis checks validate routing.
No external reproduction is recorded.

## Exact random-unrestricted-pair activity law

Within a serial-Chi word pair, x=a XOR rot32(b), y=b XOR rot32(S(x))
are the two S-box input words. The inverse is b=y XOR rot32(S(x)),
a=x XOR rot32(b); hence the full256-byte call-input map is bijective.
All preceding transformations are bijections. Before conditioning on distinct
inputs, two independent uniform states give independent uniform difference
bytes in these coordinates, so A_r is Binomial(256,255/256).
Conditioning on distinctness removes exactly A_r=0, probability2^-2048.
Consequently E[A_r]=255/(1−2^-2048), and linearity of expectation gives
E[sum A_r]=255R/(1−2^-2048), without cross-round independence.

For K=256−A, define

`p=(sum_{k=12}^{256} binom(256,k)*255^(256-k)/256^256 −2^-2048)/(1−2^-2048)`.

A union bound proves Pr[every A_r≥245]≥1−Rp, and therefore
Pr[sum A_r≥245R]≥1−Rp. Exact rational arithmetic establishes
8p<5.337351×10^-9, so the eight-round total≥1960 with probability
>0.99999999466. This does not apply to chosen differences or uniformly
sampled H message pairs without a separate distribution theorem.

## Generic full-state image distance

For any R1–R8, F_r is injective on2^1272 valid159 messages, giving a binary
code C of length2048 and size2^1272. Integer arithmetic verifies
V(2048,151)<2^776<V(2048,152). Minimum distance≥305 would give disjoint
radius152 balls and require2^1272 V≤2^2048, a contradiction. Thus some
distinct messages have full-state output Hamming distance≤304.
This supplies no efficient construction or digest collision, and the bound
is not stated sharp. It also holds for injective maps with no cryptographic
strength; it is included to constrain claims about universal avalanche.

## Differential mass and Fourier identities

For H full-state image C_r and fixed Δ≠0, injectivity gives the exact count

`sum_{δ≠0} DP_r(δ,Δ)=|C_r∩(C_r XOR Δ)|/|C_r|≤1`.

Count ordered image pairs by their base point: each translated partner,
when present, specifies exactly one nonzero message difference. Thus at
threshold τ>0 at most floor(1/τ) input differences have point probability
≥τ. At τ=2^-128 the count is≤2^128, not a maximum-DP bound.
Digest truncation loses injectivity and this formula cannot be transferred.

For C(α,β)=E_m (-1)^(α·m XOR β·F_r(m)), Parseval at fixed β gives
`sum_α C(α,β)^2=1`. Orthogonality at fixed α and full-state injectivity give
`sum_β C(α,β)^2=2^776`. At magnitude threshold2^-128, the respective
counts are≤2^256 input masks and≤2^1032 full-state output masks, fractions
≤2^-1016 of their spaces. All masks, including zero, are counted here.
These exact coefficients include the full hull; the identities do not bound
its largest entry. An affine injective map can satisfy them with perfect
correlations and probability-one differentials.

For any digest map G:H→F2^256, the fixed-output-mask Parseval identity still
holds, regardless of injectivity. The fixed-input-mask replacement is

`sum_β C_G(α,β)^2=(2^256/2^2544) sum_y (sum_{m:G(m)=y} (-1)^(α·m))^2`.

At α=0 this is2^256 times the collision probability of two independent
uniform messages. It is not generally the full-state constant2^776.

Writing b_β=C(0,β), character inversion gives the connection

`|C_r∩(C_r XOR Δ)|/|C_r|=2^-776 sum_β (-1)^(β·Δ) b_β²`.

Useful overlap bounds require control of this **signed** sum. Taking absolute
values only recovers≤1. No numerical improvement is claimed here.

## Reproduction and next proof obligation

[Audit script](../scripts/krakken_solver_free_baselines_audit.py) ·
[Exact report](../results/krakken_solver_free_baselines_audit.json).
The analytic proofs above are separate from the finite formula checks;
21 small injective-map overlap/Fourier checks validate the latter implementation.
Original BOUNDS, RESULTS18 and discovery18 artifacts remain unchanged.

```bash
nice -n 10 /home/user/venv/krakken/bin/python -u \
  /home/user/sol/scripts/krakken_solver_free_baselines_audit.py \
  --output /home/user/sol/results/krakken_solver_free_baselines_audit.json
```

**OPEN:** connect MDS slice support to actual serial-Chi call activity across
adjacent rounds, retaining Theta/XRBD cancellations, Rho byte splitting,
valid-message restrictions and necessary Pressure carry equations. No new
A_r+A_(r+1) threshold is proved by these notes. Existing12/15/17 activity
floors retain their solver-backed [1,1] premise. Generic counting/calibration
lemmas do not remove that dependency or establish a security margin.

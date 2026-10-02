# Open Problems / Attack Surface

These are high-value targets, not an exhaustive research agenda.

## 1. Break the full eight-round hash

The obvious prize:

- collision below the generic 2^128 reference for the 256-bit digest;
- preimage or second preimage below the generic 2^256 reference;
- a full-round distinguisher with explicit advantage and complexity;
- a multi-block attack exploiting the absorb/capacity state.

Nothing in the current theorem set closes these questions.

## 2. Quantitative multi-round differential bounds

The project has exact first-round activity results and several two-round exclusions, but activity alone is not a trail probability.

Interesting targets include:

- exact or useful upper bounds on high-probability multi-round trails;
- trail clustering / differential-hull effects;
- conditioned trails whose base-message cost is included;
- backward/rebound constructions from later rounds.

## 3. Complete linear hull

Perfect affine relations have been excluded, and several defined one-round mask spaces have strong numerical bounds.

What remains open is a useful general numerical upper bound on complete-round linear correlation/hull behavior over unrestricted masks.

Pressure's carry structure is a central obstacle.

## 4. Extend the coordinated multi-cell boomerang

The current coordinated construction gives an exact complete-round-one unrestricted four-state zero sum.

The next questions are:

- can directions/backgrounds be chosen so that all required Chi2 local rectangle counts are positive and globally compatible?
- can a complete two-round quartet be constructed?
- can shared Pressure chains be handled by jointly solving carries rather than separating chain supports?
- can any useful survivor be made hash-reachable?

A general two-round impossibility theorem would also be a major result.

## 5. Resolve the saved 448 first-block gate survivors

For the 1,344 saved multi-cell direction pairs from the current finite campaign:

- 896 are excluded by the valid-message first-block linear gate for every background;
- 448 pass those **necessary linear conditions**.

Passing the gate is not a message construction.

Useful results:

- explicit valid four-message embeddings for any survivor;
- nonlinear incompatibility certificates;
- a general theorem that collapses the remaining finite class;
- a method that scales beyond the saved basis/sampled directions.

Do not confuse this finite 448-case frontier with exhaustive coverage of the full direction spaces.

## 6. Pressure beyond the current low-bit theorems

The exact low-bit joint-carry results invite several extensions:

- wider masks;
- general 64-bit coupled output masks;
- exact zeros and canonical reductions;
- differential rather than linear carry structure;
- bounds that compose across complete rounds without catastrophic triangle inequalities.

A reduced-width counterexample already shows that naive absolute-value/triangle approaches can fail, so signed structure matters.

## 7. Multi-block / later-absorb reachability

Most precise hash-interface theorems currently target the first block with zero initial capacity.

Later absorbs have correlated capacity state. That can either frustrate or enable structures that are impossible at the first block.

Interesting targets:

- backward reachability into a chosen round boundary;
- multi-block differential/rebound structures;
- herding/fixed-point-like sponge phenomena;
- capacity-conditioned boomerangs or integrals.

## 8. Independent reproduction

Pick a theorem and reproduce it without reusing its producer implementation.

Especially valuable targets:

- exact `min A1 = 5`;
- Pressure low-17 sharp `1/2` theorem;
- complete `[1,2]` exclusions;
- one-round coordinated multi-cell quartet;
- one-round message/output correlation bounds.

A contradiction with a small explicit counterexample is equally valuable.

## 9. New attacks we did not think of

Please do not constrain yourself to the existing research vocabulary.

If the design has a weird structural weakness, we want to know.

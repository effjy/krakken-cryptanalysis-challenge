# Implementation Notes and Known Reference-Code Caveats

These notes separate **reference/API issues** from mathematical cryptanalysis.

The source is intentionally pinned so existing research remains reproducible. Do not silently "fix" the challenge target when analyzing an existing result.

## Scalar source is the current reference

The repository contains the scalar implementation in `krakken.c` and public declarations/S-box in `krakken.h`.

The header declares AVX2 entry points, but the supplied scalar translation unit does not define them. Unless a separate AVX2 implementation is explicitly added and pinned, cryptanalysis should use the scalar reference.

## `rc_get(round)`

The current helper returns `rc[round]` directly.

It does not itself:

- call `init_rc_vectors()`;
- validate the round index.

Normal scalar permutation entry points initialize constants before round use, but standalone research code that calls `rc_get` must initialize and bound-check explicitly.

## Reduced-round semantics

`krakken_permute_scalar_rounds(state, rounds)` currently behaves as follows:

- `rounds <= 0`: returns without changing the state;
- `rounds > 8`: clamps to 8;
- otherwise runs rounds 0 through `rounds-1`.

Research wrappers should validate the intended round count themselves.

## Byte order / portability

Absorb, squeeze, and some byte views use the native byte representation of the `uint64_t` state array.

The current source-pinned research target is the little-endian execution represented by the supplied test vectors. A portable future revision should define byte encoding explicitly rather than relying on native word layout.

## Constant generation

Round constants are generated with the bundled SHAKE128 code and decoded explicitly little-endian before use.

## What counts as an implementation finding?

Please report:

- undefined behavior;
- bounds errors;
- portability bugs;
- inconsistent scalar/optimized implementations;
- wrong test vectors;
- unexpected padding behavior;
- API behavior that can cause a caller to compute something other than the intended construction.

Those reports matter, but they should be labeled **implementation** unless they create a cryptographic attack on the intended mathematical construction.

## Source pin

Current reference hashes:

- `krakken.c`: `4d659644c80b6ed0aabbce77d6aad6e6f851a90ec536a2131a412b8ac48eccc6`
- `krakken.h`: `83f891b688575c0ed6020dd186b35495e577c203ba418cd80981e49a96236a2c`
- `krakken.c || krakken.h`: `6b3d5a5d416e2923379e0b38305babb4cb0471c1833d7d3a6c4e8356005d8893`

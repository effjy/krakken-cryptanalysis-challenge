# Krakken-2048 Reference Construction

This is a compact reading guide to the scalar C reference. When in doubt, the pinned source code is authoritative.

## State

The internal state is 256 bytes = 2048 bits, represented by 32 64-bit words.

The scalar implementation uses a union exposing both:

- `uint64_t w[32]`
- `uint8_t b[256]`

The current research/certificates use the little-endian byte interpretation of those words.

## Full round

A complete round applies, in order:

1. **Theta**
2. **Tentacle MDS**
3. **Rho**
4. **Pi**
5. **Chi**
6. **Butterfly diffusion / XRBD**
7. **Pressure ARX**
8. **Round-constant XOR**
9. **InkCloud shuffle**

There are 8 full rounds.

## Theta

The 32 words are viewed as 8 columns × 4 rows. For each column, XOR the four words to obtain a column parity. Each word in column `c` is then XORed with:

    rotr64(parity[c-1], 1) XOR parity[c+1]

with column indices modulo 8.

## Tentacle MDS

Each of the four rows is mixed across its 8 words using byte-wise GF(2^8) multiplication with coefficient sequence:

    01 01 04 01 08 05 02 09

The reduction constant used by doubling is `0x1D`.

## Rho

Each of the 32 64-bit words is rotated by its fixed entry in the source `rho[32]` table.

## Pi

For word coordinates `(x,y)`, with `x in 0..7` and `y in 0..3`:

    new_x = (x + 3*y) mod 8

The row coordinate is unchanged.

## Chi / Abyssal serial S-box

Words are processed in adjacent column pairs within each row.

For pair values `a,b`:

    ap = S(a XOR rotl64(b, 32))
    bp = S(b XOR rotl64(ap, 32))

where `S` applies the 8-bit `ABYSSAL_SBOX` independently to each byte of the 64-bit word.

The serial dependence of `bp` on `ap` is important; this is not two parallel S-box calls.

## Butterfly diffusion / XRBD

Five butterfly stages use distances 1, 2, 4, 8, 16 and rotations:

    13, 23, 37, 41, 53

For each paired word `(a,b)`:

    a ^= b
    b ^= rotl64(a, rot)

Research notes may refer to this layer as **XRBD**.

## Pressure ARX

For each group of four words `(a,b,c,d)`:

    a += c ^ (c >> 17)
    b += d ^ (d >> 17)
    c += a ^ (a << 31)
    d += b ^ (b << 31)
    b = rotl64(b, 7)
    d = rotl64(d, 19)

All additions and shifts are on 64-bit words.

## Round constants

Round constants are generated once using the bundled SHAKE128 implementation with domain string:

    Krakken-2048 Abyssal v1 - Primary 

The derived bytes are decoded little-endian into 8 × 32 64-bit words and XORed wordwise at the round-constant layer.

## InkCloud

For each input word index `i`:

    temp[(i * 7) & 31] = rotl64(state[i], 11)

Then `temp` becomes the state.

## Hash interface

The hash rate is 160 bytes.

For every complete 160-byte message block:

1. XOR the block into state bytes 0..159;
2. apply the full eight-round permutation.

A final padded block is always absorbed.

### Padding

For a final remainder `rem < 159`:

- XOR/copy the remainder into the block;
- write `0x06` at byte `rem`;
- write `0x80` at byte 159.

For `rem == 159`:

- byte 159 is `0x86`.

This is why a 159-byte one-block message is represented in the research literature as 159 message bytes followed by fixed `0x86`.

If the input length is an exact multiple of 160 bytes, the implementation absorbs those blocks and then absorbs an additional padding block for `rem == 0`.

## Squeeze

Output is copied from the first 160 state bytes. If more output is requested, the full eight-round permutation is applied again and another rate-sized chunk is emitted.

## Reduced-round helper

`krakken_permute_scalar_rounds(state, rounds)` runs from round index zero for the requested number of rounds, subject to the implementation semantics documented in [IMPLEMENTATION_NOTES.md](IMPLEMENTATION_NOTES.md).

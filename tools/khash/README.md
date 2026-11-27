# khash — standalone streaming Krakken file hashing

This directory contains **everything needed to build `khash` independently of the repository root**:

- `khash.c` — the author's unchanged file-hashing utility.
- `krakken.c`, `krakken.h`, `krakken_multi.c` — **byte-for-byte copies** of the canonical Krakken-2048 source files from the repository root.
- `Makefile` — local standalone build, scalar and optional AVX2.
- `SOURCE_SHA256SUMS` — SHA-256 pins for the three original cryptographic files.
- `test_khash.py` — reference-hash compatibility test (optional Python 3).

**This is an experimental research construction, not a standardized or independently certified hash. Do not rely on it to protect production systems.**

## Build and hash a file

Download all the files from this directory together, then from inside the downloaded directory run:

```sh
sha256sum -c SOURCE_SHA256SUMS
make
./khash /path/to/file
./khash "a file with spaces.bin"
```

Alternatively, if you cloned the complete challenge repository:

```sh
make -C tools/khash
./tools/khash/khash /path/to/file
```

The CLI prints one **256-bit Krakken hash** as 64 lowercase hexadecimal digits and a newline. The file name is **not** hashed. Input is processed in 64 KiB chunks and uses the original eight-round 160-byte-rate sponge, including the `0x06` and `0x80` padding bits. An exact multiple of 160 bytes receives an additional final padded block.

On x86, the Makefile builds the AVX2 backend separately and the program selects it at runtime when supported, with a scalar fallback. On other architectures only scalar is built. To build without AVX2:

```sh
make clean
make ENABLE_AVX2=0
```

Requirements: GCC or Clang, Make, POSIX threads (Linux); Python 3 only for the optional tests.

## Check the copied sources and outputs

From inside this directory:

```sh
sha256sum -c SOURCE_SHA256SUMS
make check
make clean
```

The 19-length test suite compares both command-line builds with the scalar reference API, including message-padding, exact-rate, streaming-buffer boundaries and error handling. CI additionally checks that the three local copies are identical to the repository root files, and verifies that this directory builds **in isolation**. These tests verify implementation behavior; they are not security proofs.

Expected empty-file digest:

```text
e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd
```

For the full cryptanalysis challenge and 16 research ledgers, see the [repository README](../../README.md).

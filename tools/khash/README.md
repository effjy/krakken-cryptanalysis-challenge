# khash — streaming Krakken file hashing

This command-line tool hashes a file using the **exact eight-round Krakken-2048 reference sponge**. It uses the unchanged cryptographic sources in the repository root, not a fork of them. The author's original `khash.c` is preserved byte-for-byte.

> **Experimental research software:** Krakken is not standardized or independently certified. Do not rely on its digest for production security.

## Build and use

From the root of this repository:

```sh
make -C tools/khash
./tools/khash/khash /path/to/file
./tools/khash/khash "a file with spaces.bin"
```

The output is 64 lowercase hexadecimal characters representing a **256-bit Krakken digest (not SHA-256)** followed by a newline. The filename is excluded from the hash. Files are streamed in 64 KiB chunks. The hash rate is 160 bytes, and padding uses the original `0x06` and `0x80` bits, including a new final padded block for exact rate multiples.

On x86, the Makefile compiles the AVX2 source separately and uses runtime CPU detection to select the accelerated implementation. Other targets build the scalar backend. To build scalar-only on any platform:

```sh
make -C tools/khash clean
make -C tools/khash ENABLE_AVX2=0
```

Requirements: GCC or Clang, Make, POSIX threads; Python 3 is needed for the optional comparison tests.

## Verify source identity and compatibility

From the repository root:

```sh
sha256sum -c tools/khash/SOURCE_SHA256SUMS
make -C tools/khash check
make -C tools/khash clean
```

The checksum manifest supplied by the author pins the three original cryptographic source files in the repository root. The 19-case compatibility suite checks padding and buffer boundaries, exact rate multiples, multi-block files, and error behavior. Both CLI backends are compared with the independent reference C hash API. These functional tests do not establish cryptographic security.

Expected empty-file hash:

```text
e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd
```

See [the main challenge page](../../README.md) for scope, test vectors and open research problems.

#!/usr/bin/env python3
"""Differential tests of khash CLI against the unchanged scalar hash API."""
import ctypes
import pathlib
import random
import subprocess
import tempfile

HERE = pathlib.Path(__file__).resolve().parent
EXPECTED_EMPTY = "e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd"
lib = ctypes.CDLL(str(HERE / "libkrakken-reference.so"))
hash_ref = lib.krakken_hash_scalar
hash_ref.argtypes = (ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t)
hash_ref.restype = None


def reference(data):
    output = ctypes.create_string_buffer(32)
    inbuf = ctypes.create_string_buffer(data)
    hash_ref(output, 32, inbuf, len(data))
    return output.raw.hex()


def run_cli(binary, path):
    p = subprocess.run([str(binary), str(path)], capture_output=True, text=True, check=True)
    assert p.stderr == "", (binary, p.stderr)
    return p.stdout


lengths = [0, 1, 7, 31, 158, 159, 160, 161, 319, 320, 321,
           4095, 4096, 4097, 65535, 65536, 65537, 65600, 131072]
rng = random.Random(0x2048)
with tempfile.TemporaryDirectory(prefix="krakken-khash-") as d:
    tmp = pathlib.Path(d)
    for n in lengths:
        data = rng.randbytes(n)
        path = tmp / f"khash data {n} bytes.bin"
        path.write_bytes(data)
        expected = reference(data)
        for binary in (HERE / "khash", HERE / "khash-scalar"):
            actual = run_cli(binary, path)
            assert actual == expected + "\n", (binary, n, actual, expected)
        if n == 0:
            assert expected == EXPECTED_EMPTY, (expected, EXPECTED_EMPTY)

    for binary in (HERE / "khash", HERE / "khash-scalar"):
        missing = tmp / "does not exist"
        p = subprocess.run([str(binary), str(missing)], capture_output=True, text=True)
        assert p.returncode != 0 and p.stdout == "", (binary, "missing file test")
        p = subprocess.run([str(binary)], capture_output=True, text=True)
        assert p.returncode != 0 and p.stdout == "", (binary, "usage test")

print(f"PASS: {len(lengths)} deterministic file lengths match the independent scalar API "
      "using both CLI builds; error paths behave correctly")

# Known-Answer Test Vectors

All values below were generated from the source revision pinned in the repository README on a little-endian system.

The hash vectors use 32-byte output.

## Hash KATs

| Input | Length | Digest |
|---|---:|---|
| empty string | 0 | `e1c646acd24c1211dc58f38fe7cb95ec9ca41b7c57cff233e6faf1fac8b2e0dd` |
| ASCII `abc` | 3 | `5062b998511e180f476907438a27183ffcd657031d141b3659f9f32611d9fe7c` |
| one zero byte | 1 | `6db6a8b8e3716f6cf2b3d922a2d00be8296d3ef539c7cc2239dbf9e7a80b1b9b` |
| 159 zero bytes | 159 | `6a7449835760839e3d2d629fc839eae6376348c8339fd0f34b8c75264083bc93` |
| 160 zero bytes | 160 | `2d87727b66f7d07827cb1ca1a705da694361b935bfb41b3a6b78cec93a837e13` |
| 161 zero bytes | 161 | `3fa9b8338730344013d01a433d1035dbd716331a4010f68b9e679118bf2bc7e9` |
| bytes `00,01,...,9e` | 159 | `3e29183ffec9cee4caad761094f11814a0e336b8edfe29b11f4824d905e2cc26` |

The 159/160/161-byte boundary cases are intentionally included to catch padding and full-block handling mistakes.

## Permutation KAT input

For the permutation vectors below, initialize the 256 state bytes to:

    00 01 02 ... fe ff

interpreted exactly as the native byte view used by the little-endian scalar reference.

### After 1 complete round

    87011486b08d83981981b61f314952fbb00aa05240c554b2c5b54152fe98b39611ec3369f522d32fbad3ca284516d684ba56ff3d3e0da7ab05bb861172c40ec965fb9882c1b2e053e419584a3730eab5aa3a42133fe8690ab2c8353fcc5237584e10f48430508d3a4ed0895f24ee9c645683e0578537a2627b953d6e4d8065728790bfda8bbe1c3285b5f08410e403060bac41f18f2804cf9c47bdfa638b946674df8f47252f74806231d83dbe31b6a825ef5d565120765887094ce6f9dc245fc77e3c3804f484eabd628847764a4c7ebbe011cf6e9de628076c7b03c3ac32985cf350deec4130c92abb0546afdcda99c6db913ffec9bf94457ef33dea46e91b

### After 8 complete rounds

    5a6ac42d33277c9752be5fd42e7b13fb018c83bd017b620ef4d489efe78cb23709804d25ca061f3f840e9c41672b46a7a90b7cfecfed81a0a17f6be62a26624f241e9ac2a47f9b774d643acf8251f4e4c07eaf9fb12caf758633fc33204cfa3e9a311a43950744a573fa00f9590a3db953e6fedd214e7c2a41911094c46a3473ab513ad00ef29b5360ff4a9561f4212f0ae3b7f1f0e179f914d51e936b3d29059f85bc3becc2b801dd6e5ab6a377bec4026f77dc8c8ff379eb0544b24cce320b25a2e72ca7606327ac87fec17b7f42c6b9dc946ad89ba488a37b3c75909994ed6af27f7a0574a2e8d1af3f30bf843c2ac1d344e075c23fc8427a1b427757634c

## Automated check

Run:

    make test

The KAT executable independently computes the listed hash vectors and exits nonzero on a mismatch.

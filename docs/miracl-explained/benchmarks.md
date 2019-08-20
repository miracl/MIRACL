* [What Is Miracl](README.md)
* [Security Advisory](security-advisory.md)
* Benchmarks
* [Miracl Standard Curves](miracl-standard-curves.md)
* [IEEE 1363](ieee-1363.md)
* [Elliptic Curves](elliptic-curves.md)
* [Licensing](licensing.md)
* Reference Manual
	* [Low Level Routines](reference-manual/low-level-routines.md)
	* [Advanced Arithmetic Routines](reference-manual/advanced-arithmetic-routines.md)
	* [Montgomery Arithmetic Routines](reference-manual/montgomery-arithmetic-routines.md)
	* [ZZn2 Arithmetic Routines](reference-manual/zzn2-arithmetic-routines.md)
	* [Encryption Routines](reference-manual/encryption-routines.md)
	* [Elliptic Curve Routines](reference-manual/elliptic-curve-routines.md)
	* [Floating Slash Routines](reference-manual/floating-slash-routines.md)
	* [Structure Reference](reference-manual/structure-reference.md)


Benchmarks
---

* [Overview](#overview)
* [Output of the BMARK Program](#output)
* [Elliptic Curve Point Multiplication](#curve)
* [Pairing-Based Crypto](#pairing)

## Overview <a id="overview"></a>

**Performance is the biggest single issue for implementors, and MIRACL allows a variety of techniques (algorithmic tricks and/or assembly language) to be used to squeeze maximum performance from a particular environment. So use MIRACL in your cryptographic API for a performance boost - you may not need that expensive Cryptographic accelerator!**

This diagram below shows timings for modular exponentiation, that is the calculation of xy mod n, for x, y and n all the same size in-bits - the size shown along the horizontal axis. The exponent y is chosen at random. This is the bottleneck calculation in many cryptographic protocols. Five different methods are implemented for the Intel 80x86/Pentium family. Timings on the horizontal axes are correct in seconds for 8192-bit exponentiation. For 4096-bits divide by 8, for 2048-bits divide by 8 again, etc. For a paper describing the methods in more details see [timings.doc](miracl-explained/timings.doc ':ignore').

The following timings were obtained using the Borland C/C++ Compiler/assembler, for modular exponentiation.

Times in milliseconds for optimal technique:

|          | 512-bits | 1024-bits | 2048-bits | 4096-bits |
|--------------------|----------|-----------|-----------|-----------|
| 33MHz 80486DX   | 370   | 2833   | 17833   | 111000  |
| 60MHz Pentium   | 48    | 353    | 2452   | 18500   |
| 180MHz Pentium Pro | 12    | 90    | 564    | 3551   |
| 233MHz Pentium II | 10    | 80    | 510    | 3250   |

**On a 233 Mhz Pentium II - Best times (without precomputation)**

- A 1024-bit RSA decryption/signature takes 20ms. <sup>*</sup>
- A 2048-bit RSA decryption takes 160 ms. <sup>+</sup>
- A 1024-bit (160-bit exponent) DSS verification takes 16ms. <sup>+</sup>
- A 2048-bit (256-bit exponent) DSS verification takes 79ms <sup>+</sup>
- A 160-bit Elliptic Curve ECS verification takes 11 ms. <sup>*</sup>
- A 256-bit Elliptic Curve ECS verification takes 26ms. <sup>*</sup>
- A 192-bit Elliptic Curve ECS verification takes 9ms (NIST Standard Curve - Special Modulus) <sup>*</sup>
- A 224-bit Elliptic Curve ECS verification takes 13ms (NIST Standard Curve - Special Modulus) <sup>*</sup>

**On 80MHz ARM7TDMI - Best times (without precomputation)**

- A 1024-bit RSA decryption/signature takes 120ms <sup>*</sup>
- A 192-bit Elliptic Curve point multiplication takes 38ms (NIST Standard Curve - Special Modulus) <sup>*</sup>
- A 224-bit Elliptic Curve point multiplication takes 53ms (NIST Standard Curve - Special Modulus) <sup>*</sup>

MIRACL contains fast experimental implementations of [Identity-Based Encryption](http://crypto.stanford.edu/ibe/).

Timings include all number theoretic components of encrypt/decrypt processing. The most time-consuming component is the calculation of the Tate Pairing. The discrete logarithm-bit-length security of a pairing-based system is a function of the product of the _security multiplier k and the-bit length of the base field. In these cases k=2 and the base field is 512-bits, for 1024-bit security.

**On a 1GHz Pentium III**

- A 1024-bit IBE encrypt takes 35ms <sup>*</sup>
- A 1024-bit IBE decrypt takes 27ms <sup>*</sup>
- A 1024-bit IBE encrypt takes 22ms (with precomputation) <sup>*</sup>
- A 1024-bit IBE decrypt takes 17ms (with precomputation) <sup>*</sup>
- A 1024-bit Tate pairing takes 20ms <sup>*</sup>
- A 1024-bit Tate pairing takes 8.6ms (with precomputation) <sup>*</sup>

<sup>* - Using Comba Method for modular multiplication</sup><br />
<sup>+ - Using KCM Method for modular multiplication</sup>

## Output of the BMARK program <a id="output"></a>

Below is the output of the BMARK program, on a single core of a 2.4GHz Intel i5 520 processor, compiled with GCC, with standard /O2 compiler optimisation.

> This is for the standard version of MIRACL, with no special optimizations.

- MIRACL – 64-bit version
- Little Endian processor
- Using some assembly language
- No special optimizations
- Precomputation uses fixed Window size = 8
- So 256 values are precomputed and stored

> No optimizations/assembly language apply to GF(2^m) Elliptic Curves.<br />Times are elapsed real-times - so make sure nothing else is running!

Modular exponentiation benchmarks – calculating g^e mod p. From these figures it should be possible to roughly estimate the time required for your favourite PK algorithm, RSA, DSA, DH, etc.

**Key**

- R – random base-bits/random exponent-bits
- V – random base-bits/(small exponent e)
- S – (small base g) /random exponent-bits
- P – exponentiation with precomputation (fixed base g)
- D – double exponentiation g^e.a^b mod p
- F3 = 257, F4 = 65537
- RSA - Rivest-Shamir-Adleman
- DH - Diffie Hellman Key exchange
- DSA - Digital Signature Algorithm

**512-bit prime**

- R - 54945 iterations of 512/ 160   0.18 ms per iteration
- D - 45015 iterations of 512/ 160   0.22 ms per iteration
- R - 18292 iterations of 512/ 512   0.55 ms per iteration
- S - 67125 iterations of g=3/ 160   0.15 ms per iteration
- P - 281436 iterations of 512/ 160  0.04 ms per iteration

**1024-bit RSA decryption**

1.09 ms

**512-bit DH 160-bit exponent**

- Offline, no precomputation         0.18 ms
- Offline, small base                0.15 ms
- Offline, w. precomputation         0.04 ms
- Online                             0.18 ms

**512-bit DSA 160-bit exponent**

- Signature no precomputation        0.18 ms
- Signature w. precomputation        0.04 ms
- Verification                       0.22 ms

**1024-bit prime**

- R - 17875 iterations of 1024/ 160    0.56 ms per iteration
- D - 14859 iterations of 1024/ 160    0.67 ms per iteration
- V - 1163058 iterations of 1024/e= 3  0.01 ms per iteration
- V - 154892 iterations of 1024/e=F4   0.06 ms per iteration
- S - 22799 iterations of g=3/ 160     0.44 ms per iteration
- P - 89730 iterations of 1024/ 160    0.11 ms per iteration

**2048-bit RSA decryption**

6.62 ms

**1024-bit RSA encryption e=3**

0.01 ms

**1024-bit RSA encryption e=65537**

0.06 ms

**1024-bit DH 160-bit exponent**

- Offline, no precomputation         0.56 ms
- Offline, small base                0.44 ms
- Offline, w. precomputation         0.11 ms
- Online                             0.56 ms

**1024-bit DSA 160-bit exponent**

- Signature no precomputation        0.56 ms
- Signature w. precomputation        0.11 ms
- Verification                       0.67 ms

**2048-bit prime**

- R - 2982 iterations of 2048/ 256   3.35 ms per iteration
- D - 2335 iterations of 2048/ 256   4.28 ms per iteration
- R - 398 iterations of 2048/2048    25.13 ms per iteration
- V - 366871 iterations of 2048/e= 3 0.03 ms per iteration
- V - 48125 iterations of 2048/e=F4  0.21 ms per iteration
- S - 4223 iterations of g=3/ 256    2.37 ms per iteration
- P - 15500 iterations of 2048/ 256  0.65 ms per iteration

**2048-bit RSA encryption e=3**

0.03 ms

**2048-bit RSA encryption e=65537**

0.21 ms

**2048-bit DH 256-bit exponent**

- Offline, no precomputation         3.35 ms
- Offline, small base                2.37 ms
- Offline, w. precomputation         0.65 ms
- Online                             3.35 ms

**2048-bit DSA 256-bit exponent**

- Signature no precomputation        3.35 ms
- Signature w. precomputation        0.65 ms
- Verification                       4.28 ms

## Elliptic Curve Point Multiplication <a id="curve"></a>

Elliptic Curve point multiplication benchmarks – calculating r.P
From these figures it should be possible to roughly estimate the time required for your favourite EC PK algorithm, ECDSA, ECDH, etc.

**Key**
- ER - Elliptic Curve point multiplication r.P
- ED - Elliptic Curve double multiplication r.P + s.Q
- EP - Elliptic Curve multiplication with precomputation
- EC - Elliptic curve GF(p) - p of no special form
- ECDH - Diffie Hellman Key exchange
- ECDSA - Digital Signature Algorithm

**160-bit GF(p) Elliptic Curve**

- ER -  22280 iterations         0.45 ms per iteration
- ED -  17217 iterations         0.58 ms per iteration
- EP -  96332 iterations         0.10 ms per iteration

**160-bit ECDH**

- Offline, no precomputation     0.45 ms
- Offline, w. precomputation     0.10 ms
- Online                         0.45 ms

**160-bit ECDSA**

- Signature no precomputation   0.45 ms
- Signature w. precomputation   0.10 ms
- Verification                 0.58 ms

**192-bit GF(p) Elliptic Curve**

- ER -  17095 iterations         0.58 ms per iteration
- ED -  12936 iterations         0.77 ms per iteration
- EP -  74904 iterations         0.13 ms per iteration

**192-bit ECDH**

- Offline, no precomputation     0.58 ms
- Offline, w. precomputation     0.13 ms
- Online                     0.58 ms

**192-bit ECDSA**

- Signature no precomputation   0.58 ms
- Signature w. precomputation   0.13 ms
- Verification                 0.77 ms

**224-bit GF(p) Elliptic Curve**

- ER - 11832 iterations         0.85 ms per iteration
- ED - 9486 iterations          1.05 ms per iteration
- EP - 52869 iterations         0.19 ms per iteration

**224-bit ECDH**

- Offline, no precomputation     0.85 ms
- Offline, w. precomputation     0.19 ms
- Online                     0.85 ms

**224-bit ECDSA**

- Signature no precomputation    0.85 ms
- Signature w. precomputation    0.19 ms
- Verification                  1.05 ms

**256-bit GF(p) Elliptic Curve**

- ER -   9410 iterations          1.06 ms per iteration
- ED -   7124 iterations          1.40 ms per iteration
- EP -  41546 iterations         0.24 ms per iteration

**256-bit ECDH**

- Offline, no precomputation     1.06 ms
- Offline, w. precomputation     0.24 ms
- Online                     1.06 ms

**256-bit ECDSA**

- Signature no precomputation   1.06 ms
- Signature w. precomputation   0.24 ms
- Verification                  1.40 ms

**163-bit GF(2^m) Elliptic Curve**

- ER -  27160 iterations         0.37 ms per iteration
- ED -  20689 iterations         0.48 ms per iteration
- EP -  107712 iterations         0.09 ms per iteration

**163-bit ECDH**

- Offline, no precomputation     0.37 ms
- Offline, w. precomputation     0.09 ms
- Online                     0.37 ms

**163-bit ECDSA**

- Signature no precomputation   0.37 ms
- Signature w. precomputation   0.09 ms
- Verification                  0.48 ms

**163-bit GF(2^m) Koblitz Elliptic Curve**

- ER -  43413 iterations         0.23 ms per iteration
- ED -  23882 iterations         0.42 ms per iteration
- EP -  111239 iterations         0.09 ms per iteration

**163-bit ECDH**

- Offline, no precomputation     0.23 ms
- Offline, w. precomputation     0.09 ms
- Online                     0.23 ms

**163-bit ECDSA**

- Signature no precomputation   0.23 ms
- Signature w. precomputation   0.09 ms
- Verification                 0.42 ms

**233-bit GF(2^m) Elliptic Curve**

- ER -  16703 iterations         0.60 ms per iteration
- ED -  12460 iterations         0.80 ms per iteration
- EP -  62551 iterations         0.16 ms per iteration

**233-bit ECDH**

- Offline, no precomputation     0.60 ms
- Offline, w. precomputation     0.16 ms
- Online                     0.60 ms

**233-bit ECDSA**

- Signature no precomputation   0.60 ms
- Signature w. precomputation   0.16 ms
- Verification                  0.80 ms

**233-bit GF(2^m) Koblitz Elliptic Curve**

- ER -  27404 iterations         0.36 ms per iteration
- ED -  13872 iterations         0.72 ms per iteration
- EP -  62887 iterations         0.16 ms per iteration

**233-bit ECDH**

- Offline, no precomputation     0.36 ms
- Offline, w. precomputation     0.16 ms
- Online                     0.36 ms

**233-bit ECDSA**

- Signature no precomputation   0.36 ms
- Signature w. precomputation   0.16 ms
- Verification                  0.72 ms

**283-bit GF(2^m) Elliptic Curve**

- ER -   9870 iterations         1.01 ms per iteration
- ED -   7095 iterations         1.41 ms per iteration
- EP -  37435 iterations         0.27 ms per iteration

**283-bit ECDH**

- Offline, no precomputation     1.01 ms
- Offline, w. precomputation     0.27 ms
- Online                     1.01 ms

**283-bit ECDSA**

- Signature no precomputation   1.01 ms
- Signature w. precomputation   0.27 ms
- Verification                  1.41 ms

**283-bit GF(2^m) Koblitz Elliptic Curve**

- ER -  19687 iterations         0.51 ms per iteration
- ED -   8968 iterations         1.12 ms per iteration
- EP -  37505 iterations         0.27 ms per iteration

**283-bit ECDH**

- Offline, no precomputation     0.51 ms
- Offline, w. precomputation     0.27 ms
- Online                     0.51 ms

**283-bit ECDSA**

- Signature no precomputation   0.51 ms
- Signature w. precomputation   0.27 ms
- Verification                 1.12 ms

**571-bit GF(2^m) Elliptic Curve**

- ER -   2227 iterations         4.49 ms per iteration
- ED -   1504 iterations         6.65 ms per iteration
- EP -   8231 iterations         1.21 ms per iteration

**571-bit ECDH**

- Offline, no precomputation     4.49 ms
- Offline, w. precomputation     1.21 ms
- Online                     4.49 ms

**571-bit ECDSA**

- Signature no precomputation   4.49 ms
- Signature w. precomputation   1.21 ms
- Verification                  6.65 ms

**571-bit GF(2^m) Koblitz Elliptic Curve**

- ER -   5035 iterations         1.99 ms per iteration
- ED -   2242 iterations         4.46 ms per iteration
- EP -   8247 iterations         1.21 ms per iteration

**571-bit ECDH**

- Offline, no precomputation     1.99 ms
- Offline, w. precomputation     1.21 ms
- Online                      1.99 ms

**571-bit ECDSA**

- Signature no precomputation   1.99 ms
- Signature w. precomputation   1.21 ms
- Verification                  4.46 ms

## Pairing-Based Crypto <a id="pairing"></a>

Processor: 2.4 GHz Intel i5 520M.<br />
AES refers to equivalent AES-bits of security. For example 128-bits refers to AES with a 128-bit key.<br />
For G1, G2 and GT precomputation, 8-bit windows are used.<br />
All timings are in milli-seconds. Maximum optimization applied.<br />
"One More" refers to the cost of one more pairing in a multi-pairing. The (p) means that precomputation is used.<br />

**+Timings for Type-1 pairings G1 X G1 = GT+**

These pairing friendly curves are used, where _k_ is the embedding degree:
- SSP - Super-singular Curve over GF(_p_) (512-bit modulus _p_, _k_=2)
- SSP - Super-singular Curve over GF(_p_) (1536-bit modulus _p_, _k_=2)
- SS2 - Supersingular Curve over GF(2^_m_) (_m_=379, _k_=4)
- SS2 - Supersingular Curve over GF(2^_m_) (_m_=1223, _k_=4)

| AES/Curve    | 80/SSP | 80/SS2 | 128/SSP | 128/SSP |
|--------------|--------|--------|---------|---------|
| G1 mul       | 1.49   | 0.38   | 13.57   | 2.57    |
| G1 mul (p)   | 0.30   | -      | 3.01    | -       |
| Pairing      | 3.34   | 1.18   | 40.95   | 19.00   |
| Pairing (p)  | 1.65   | -      | 25.22   | -       |
| GT pow       | 0.36   | 0.29   | 3.76    | 2.09    |
| GT Pow (p)   | 0.08   | -      | 0.78    | -       |
| One More     | 2.29   | 1.01   | 20.80   | 17.80   |
| One More (p) | 0.60   | -      | 5.31    | -       |

**+Timings for Type-3 pairings G2 X G1 = GT+**

These pairing friendly curves are used, where _k_ is the embedding degree:
- CP - Cocks-Pinch Curve over GF(_p_) (512-bit modulus _p_, _k_=2)<br />
- MNT - MNT Curve over GF(_p_) (160-bit modulus _p_, _k_=6)<br />
- BN - Barreto-Naehrig Curve over GF(_p_) (256-bit modulus _p_, k=12)<br />
- KSS - Kachisa-Schaefer-Scott Curve over GF(_p_) (512-bit modulus _p_, _k_=18)<br />
- BLS - Barreto-Lynn-Scott Curve over GF(_p_) (640-bit modulus _p_, _k_=24)

| AES/Curve    | 80/CP | 80/MNT | 128/BN | 192/KSS | 256/BLS |
|--------------|-------|--------|--------|---------|---------|
| G1 mul       | 0.51  | 0.19   | 0.22   | 0.7     | 1.26    |
| G1 mul (p)   | 0.1   | 0.04   | 0.07   | 0.24    | 0.43    |
| G2 mul       | 0.51  | 1.15   | 0.44   | 5.53    | 16.04   |
| G2 mul(p)    | 0.1   | 0.35   | 0.19   | 2.81    | 5.44    |
| Pairing      | 1.14  | 1.9    | 2.32   | 20.55   | 33.91   |
| Pairing (p)  | 0.58  | 0.69   | 2.09   | 18.05   | 30.45   |
| GT pow       | 0.12  | 0.24   | 0.95   | 6.2     | 24.87   |
| GT pow (p)   | 0.03  | 0.08   | 0.43   | 2.73    | 6.47    |
| One More     | 0.81  | 1.57   | 0.75   | 4.65    | 6.59    |
| One More (p) | 0.23  | 0.34   | 0.41   | 2.38    | 3.42Ę   |

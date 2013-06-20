MIRACL
======
What is MIRACL?
Multiprecision Integer and Rational Arithmetic Cryptographic Library – the MIRACL Crypto SDK – is a C software library that is widely regarded by developers as the gold standard open source SDK for elliptic curve cryptography (ECC).

Why is it different?
While many other cryptographic SDKs are focused on PC use, MIRACL also enables developers to build security into highly constrained environments, including embedded, mobile apps and SCADA.

MIRACL enables:

Reduced program code
Greatly simplified program development
Developer-designed APIs
Rapid implementation, using inline code wrappers, example programs and other innovations
These unique qualities are the reason MIRACL, and the solutions and services built using it, are in use in hundreds of organizations across the world, including BAE Systems, Hitachi, Intel, Panasonic, Toyota and many others.

Features and Benefits: why MIRACL is the right choice
MIRACL delivers a wide and unique range of benefits, enabling developers to secure even the most constrained environments quickly, easily and effectively. It features, amongst others:

An inline C++ wrapper – greatly simplifying program development
Over 25 example programs in C and C++, covering a wide range of applications, to give development a head start
Optimization of both embedded processors and RAM, to help developers overcome device and memory constraints
Compatibility with industry security technologies including AES encryption, RSA public key cryptography, Diffie-Hellman key exchange, DSA digital signature, and others
A set of tools that enable any new number-theoretic technique to be implemented quickly

The MIRACL library consists of well over 100 routines that cover all aspects of multi-precision arithmetic. Two new data-types are defined - big for large integers and flash (short for floating-slash) for large rational numbers. The large integer routines are based on Knuth’s algorithms, described in Chapter 4 of his classic work ‘The Art of Computer Programming’. Floating-slash arithmetic, which works with rounded fractions, was originally proposed by D. Matula and P. Kornerup. All routines have been thoroughly optimised for speed and efficiency, while at the same time remaining standard, portable C. However optional fast assembly language alternatives for certain time-critical routines are also included, particularly for the popular Intel 80x86 range of processors. A C++ interface is also provided. Full source code is included.


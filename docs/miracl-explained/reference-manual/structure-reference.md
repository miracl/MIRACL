* [What Is Miracl](../README.md)
* [Security Advisory](../security-advisory.md)
* [Benchmarks](../benchmarks.md)
* [Miracl Standard Curves](../miracl-standard-curves.md)
* [IEEE 1363](../ieee-1363.md)
* [Elliptic Curves](../elliptic-curves.md)
* [Licensing](../licensing.md)
* Reference Manual
	* [Low Level Routines](low-level-routines.md)
	* [Advanced Arithmetic Routines](advanced-arithmetic-routines.md)
	* [Montgomery Arithmetic Routines](montgomery-arithmetic-routines.md)
	* [ZZn2 Arithmetic Routines](zzn2-arithmetic-routines.md)
	* [Encryption Routines](encryption-routines.md)
	* [Elliptic Curve Routines](elliptic-curve-routines.md)
	* [Floating Slash Routines](floating-slash-routines.md)
	* Structure Reference


MIRACL Structure Reference
---

## MIRACL Instance Pointer

`#include <miracl.h>`

## Field Documentation

`BOOL ERCON` - errors by default generate an error message and immediately abort the program. Alternatively by setting mip->ERCON=TRUE error control is left to the user.

`int ERNUM` - number of the last error that occurred.

`BOOL EXACT` - initialised to TRUE. Set to FALSE if any rounding takes place during flash arithmetic.

`int INPLEN` - length of input string. Must be used when inputting binary data.

`int IOBASE` - the 'printable' number base to be used for input and output. May be changed at will within a program. Must be greater than or equal to 2 and less than or equal to 256.

`int IOBSIZ` – size of I/O buffer.

`char* IOBUFF` – input/output buffer.

`int NTRY` - number of iterations used in probabilistic primality test by isprime(). Initialised to 6.

`int* PRIMES` – pointer to a table of small prime numbers.

`BOOL RPOINT` - if set to ON numbers are output with a radix point. Otherwise they are output as fractions (the default).

`BOOL TRACER` - if set to ON causes debug information to be printed out, tracing the progress of all subsequent calls to MIRACL routines. Initialised to OFF.

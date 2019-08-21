* [Intro](README.md)
* [Installation](installation.md)
* [The UI](the-ui.md)
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* [Floating Slash Nums](floating-slash-nums.md)
* [The C++ Interface](the-cpp-interface.md)
* [Example Programs](example-progs.md)
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* Instance Variables
* [MIRACL Error Messages](miracl-error-messages.md)
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


Instance Variables
---

These variables are all member of the *miracl* structure defined in *miracl.h* . They are all accessed via the *mip*  - the Miracl Instance Pointer.

| Name            | Description                                                                                                                                                             |
|-----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| BOOL EXACT;     | Initialised to TRUE. Set to FALSE if any rounding takes place during *flash* arithmetic.                                                                                  |
| int INPLEN;     | Length of input string. Must be used when inputting binary data.                                                                                                        |
| int IOBASE;     | The "printable" number base to be used for input and output. May be changed at will within a program. Must be greater than or equal to 2 and less than or equal to 256. |
| int IOBSIZ;     | Size of I/O buffer.                                                                                                                                                     |
| BOOL ERCON;     | Errors by default generate an error message and immediately abort the program. Alternatively by setting mip->ERCON=TRUE error control is left to the user.              |
| int ERNUM;      | Number of the last error that occurred.                                                                                                                                 |
| char IOBUFF[ ]; | Input/Output buffer.                                                                                                                                                    |
| int NTRY;       | Number of iterations used in probabilistic primality test by isprime. Initialised to 6.                                                                                 |
| int *PRIMES;    | Pointer to a table of small prime numbers.                                                                                                                              |
| BOOL RPOINT;    | If set to TRUE numbers are output with a radix point. Otherwise they are output as fractions (the default).                                                             |
| BOOL TRACER;    | If set to ON, causes debug information to be printed out tracing the progress of all subsequent calls to MIRACL routines. Initialised to OFF.                           |

* [Intro](README.md)
* [Installation](installation.md)
* The UI
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* [Floating Slash Nums](floating-slash-nums.md)
* [The C++ Interface](the-cpp-interface.md)
* [Example Programs](example-progs.md)
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* [Instance Variables](instance-variables.md)
* [MIRACL Error Messages](miracl-error-messages.md)
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


The User Interface
---

An example:
```
/*
 * Program to calculate factorials.
 */

#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */

void main()
{
    /* calculate factorial of number */
    big nf;        /* declare "big" variable nf */
    int n;
    miracl *mip=mirsys(5000,10);

    /* base 10, 5000 digits per big  */
    nf=mirvar(1);   /* initialise big variable nf=1  */
    printf("factorial program\n");
    printf("input number n= \n");
    scanf("%d",&n);
    getchar();
    while (n>1)
        premult(nf,n--,nf); /* nf=n!=n*(n-1)*...2*1  */

    printf("n!= \n");
    otnum(nf,stdout); /* output result */
}
```
This program can be used to quickly calculate and print out 1000! (a 2568 digit number) in less a second on a 60MHz Intel Pentium-based computer, a task first performed ‘by H.S. Uhler using a desk calculator and much patience over a period of several years’ [Knuth73]. Many other programs are described in 'Example Programs'.

Any program that wishes to make use of the MIRACL system must have an #include "miracl.h" statement. This tells the compiler to include the C header file *miracl.h* with the main program source file before proceeding with the compilation. This file contains declarations of all the MIRACL routines available to the user. The small sub-header file *mirdef.h* contains hardware/compiler-specific details.

In the main program the MIRACL system must be initialised by a call to the routine *mirsys*, which sets the number base and the maximum size of the *big* and *flash* variables. It also initialises the random number system, and creates several workspace *big* variables for its own internal use. The return value is the Miracl Instance Pointer, or *mip*. This pointer can be used to access various internal parameters associated with the current instance of MIRACL. For example to set the **ERCON** flag, one might write:
```
mip->ERCON=TRUE;
```
The initial call to **mirsys** also initialises the error tracing system which is integrated with the MIRACL package. Whenever an error is detected the sequence of routine calls down to the routine which generated the error is reported, as well as the error itself. A typical error message might be:
```
MIRACL error from routine powltr
called from isprime
called from your program
Raising integer to a negative power
```
Such an error report facilitates debugging, and assisted us during the development of these routines. An associated instance variable **TRACER**, initialised to OFF, if set by the user to ON, will cause a trace of the program's progress through the MIRACL routines to be output to the computer screen.

An instance flag **ERNUM**, initialised to zero, records the number of the last internal MIRACL error to have occurred. If the flag ERCON is set to FALSE (the default), an error message is directed to *stdout* and the program aborts via a call to the system routine *exit(0)*. If your system does not supply such a routine, the programmer must provide one instead. If **ERCON** is set to TRUE no error message is emitted and instead the onus is on the programmer to detect and handle the error. In this case execution continues. The programmer may choose to deal with the error, and reset **ERNUM** to zero. However errors are usually fatal, and if **ERNUM** is non-zero all MIRACL routines called subsequently will “fall-through” and exit immediately. See *miracl.h* for a list of all possible errors.

Every *big* or *flash* variable in the users program must be initialised by a call to the routine **mirvar**, which also allows the variable to be given an initial small integer value.

The full set of arithmetic and number-theoretic routines declared in *miracl.h* may be used on these variables. Full flexibility is (almost always) allowed in parameter usage with these routines. For example the call **multiply(x,y,z)**, multiplies the *big* variable **x** by the big variable **y** to give the result as big variable **z**. Equally valid would be **multiply(x,y,x)**, **multiply(y,y,x)**, or **multiply(x,x,x)**. This last simply squares **x**. Note that the first parameters are by convention always (usually) the inputs to the routines. Routines are provided not only to allow arithmetic on *big* and *flash* numbers, but also to allow these variables to perform arithmetic with the built-in integer and double precision data-types.

Conversion routines are provided to convert from one type to another. For details of each routine see the relevant documentation in the 'MIRACL Routines' section.

Input and output to a file or I/O device is handled by the routines **innum**, **otnum cinnum** and **cotnum**. The first two use the fixed number base specified by the user in the initial call of **mirsys**. The latter pair work in conjunction with the instance variable **IOBASE** which can be assigned dynamically by the user. A simple rule is that if the program is CPU bound, or involves changes of base, then set the base initially to MAXBASE (or 0 if a full-width base is possible - see 'Internal Representation' and use **cinnum** and **cotnum**. If, on the other hand, the program is I/O bound, or needs access to individual digits of numbers (using **getdig**, **putdig** and **numdig**), use **innum** and **otnum**.

Input and output to/from a character string is also supported in a similar fashion by the routines **instr**, **otstr**, **cinstr** and **cotstr**. The input routines can be used to set *big* or *flash* numbers to large constant values. By outputting to a string, formatting can take place prior to actual output to a file or I/O device.

Numbers to bases up to 256 can be represented. Numbers up to base 60 use as many of the symbols 0-9, A-Z, a-x as necessary.

A number base of 64 enforces standard base64 encoding. On output base64 numbers are padded with trailing = symbols if needed, but not otherwise formatted. On input white-space characters are skipped, and padding ignored. Do not use base64 with *flash* numbers. Do not use base64 for outputting negative numbers, as the sign is ignored.

If the base is greater than 60 (and not 64), the symbols used are the ASCII codes 0-255.

A base of 256 is useful when it is necessary to interpret a line of text as a large integer, as is the case for the Public Key Cryptography programs described in 'Example Programs'. The routines **big_to_bytes** and **bytes_to_big** allow for direct conversion from the internal *big* format to/from pure binary.

Strings are normally zero-terminated. However a problem arises when using a base of 256. In this case every digit from 0 - 255 can legitimately occur in a number. So a 0 does not necessarily indicate the end of the string. On input another method must be used to indicate the number of digits in the string.

By setting the instance variable **INPLEN** = 25 (for example), just prior to a call to **innum** or **instr**, input is terminated after 25 bytes are entered. **INPLEN** is initialised to 0, and reset to 0 by the relevant routine before it returns.

For example, initialise MIRACL to use *bigs* of 400 bytes:
```
miracl *mip=mirsys(400,256);  
```
Internal calculations are very efficient using this base.

Input an ASCII string as a base 256 number. This will be zero-terminated, so no need for **INPLEN**:
```
innum(x,stdin);
```
Now it is required to input exactly 1024 random bits:
```
mip->INPLEN=128;
innum(y,stdin);
```
But we want to see output in HEX:
```
mip->IOBASE=16;
cotnum(w,stdout);
```
Now in base64:
```
mip->IOBASE=64;
cotnum(w,stdout);
```
Rational numbers may be input using either a radix point (e.g 0.3333) or as a fraction (e.g. 1/3). Either form can be used on output by setting the instance variable **RPOINT**=ON or =OFF.

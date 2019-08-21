* [Intro](README.md)
* [Installation](installation.md)
* [The UI](the-ui.md)
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* [Floating Slash Nums](floating-slash-nums.md)
* [The C++ Interface](the-cpp-interface.md)
* [Example Programs](example-progs.md)
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* [Instance Variables](instance-variables.md)
* [MIRACL Error Messages](miracl-error-messages.md)
* Hardware Compiler Interface
* [Bibliography](bibliography.md)


The Hardware/Compiler Interface
---

Hardware/compiler details are specified to MIRACL in this header file: *mirdef.h* . For example:
```
/*
 *   MIRACL compiler/hardware definitions - mirdef.h
 *   This version suitable for use with most 32-bit
 *   computers
 *
 *   Copyright (c) 1988-1999 Shamus Software Ltd.
 */

#define MIRACL_32
#define MR_LITTLE_ENDIAN
                     /* this may need to be changed        */

#define mr_utype int /* the underlying type is usually int *
                      * but see mrmuldv.any                */

#define mr_unsign32 unsigned long
                     /* 32 bit unsigned type               */

#define MR_IBITS  32 /* number of bits in an int */

#define MR_LBITS  32 /* number of bits in a long */

#define MR_FLASH 52  /* delete this definition if integer  *
                      * only version of MIRACL required    *
                      * Number of bits per double mantissa */

#define MAXBASE ((mr_small)1<<(MIRACL-1))

#define MRBITSINCHAR 8
                     /* Number of bits in char type        */

/* #define MR_NOASM   * define this if using C code only   *
                      * Note: mr_dltype MUST be defined    */

/* #define mr_dltype long long
                      * double-length type                 */

/*
#define MR_STRIPPED_DOWN * define this to minimize size    *
                      * of library - all error messages    *
                      * lost! USE WITH CARE - see mrcore.c */
```

This file must be edited if porting to a new hardware environment. Assembly language versions of the time-critical routines in *mrmuldv.any* may also have to be written, if not already provided, although in most cases the standard C version *mrmuldv.ccc* can simply be copied to *mrmuldv.c* .

It is best where possible to use the *mirdef.h* file that is generated automatically by the interactive *config.c* program.

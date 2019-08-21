* [Intro](README.md)
* Installation
* [The UI](the-ui.md)
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


Installation
---

* [Overview](#overview)
* [Optimising](#optimising)
* [Upgrading from Version 3](#upgrading)
* [Multi-Threaded Programming](#multi)
* [Constrained Environments](#contrained)

## Overview <a id="overview"></a>

The MIRACL library has been successfully installed on a VAX11/780, on a variety of UNIX workstations (Sun, SPARC, Next, IBM RS/6000), on an IBM PC using the Microsoft C and C++ compilers, Borland’s Turbo C and Borland C++ compilers, the Watcom C compiler and the DJGPP GNU compiler; on ARM based computers, and on an Apple Macintosh. Recently it has been implemented on Itanium and AMD 64-bit processors.

The complete source code for each module in the MIRACL library, and for each of the example programs is provided on the distribution media. Most are written in Standard ANSI C, and should compile using any decent ANSI C compiler. Some modules contain extensive amounts of in-line assembly language, used to optimise performance for certain compiler/processor combinations. However these are invoked transparently by conditional compilation commands and will not interfere with other compilers. The batch files xxdoit.xxx contain the commands used for the creation of a library file and the example programs for several compilers. Print out and examine the appropriate file for your configuration.

Pre-compiled libraries for immediate use with certain popular compilers may be found on the distribution media: ready-to-run versions of only some of the example programs may be included, to conserve space.

To create a library you will need access to a compiler, a text editor, a linker, a librarian utility, and an assembler (optional). Read your compiler documentation for further details. The file *mrmuldv.any*, which contains special assembly language versions of the time-critical routines **muldiv**, **muldvd**, **muldvd2** and **muldvm** together with some portable C versions, which may need to be tailored for your configuration. These modules are particularly required if the compiler does not support a double length type which can hold the product of two word-length integers. Most modern compilers provide this support (often the double length type is called 'long long'), and in this case it is often adequate to use the standard C version of this module *mrmuldv.ccc* which can simply be copied to *mrmuldv.c*. Read this manual carefully, and the comments in *mrmuldv.any* for more details.

The hardware/compiler specific file *mirdef.h* needs to be specified. To assist with this, five example versions of the header are supplied: *mirdef.h16* for use with a 16-bit processor, *mirdef.h32* for 32-bit processors, *mirdef.haf* if using a 32-bit processor in a 16-bit mode, and *mirdef.hpc* for pseudo 32-bit working in a 16-bit environment. Note that the full 32-bit version is fastest, but only possible if using a true 32-bit compiler with a 32-bit processor. Try *mirdef.gcc* for use with **gcc** and **g++** in a Unix environment (no assembler).

To assist with the configuration process, a file *config.c* is provided. When compiled and run on the target processor it automatically generates a *mirdef.h* file and gives general advice on configuration. It also generates a *miracl.lst* file with a list of MIRACL modules to be included in the associated library build. Experimentation with this program is strongly encouraged. When compiling this program DO NOT use any compiler optimization.

The *mirdef.h* file contains some optional definitions: Define **MR_NOFULLWIDTH** if you are unable to supply versions of **muldvd**, **muldvd2** and **muldvm** in *mrmuldv.c*. Define **MR_FLASH** if you wish to use flash variables in your programs.

Either one of **MR_LITTLE_ENDIAN** or **MR_BIG_ENDIAN** must be defined. The *config.c* program automatically determines which is appropriate for your processor.

By omitting the **MR_FLASH** definition big variables can be made much larger, and the library produced will be much smaller, leading to more compact executables. Define **MR_STRIPPED_DOWN** to omit error messages, to save even more space in production code. Use with care!

If you don’t want any assembler, define **MR_NOASM**. This generates standard C code for the four time-critical routines, and generates it in-line. This is faster - saves on function calling overhead - and also gives an optimising compiler something to chew on. Note that if **MR_NOASM** is defined, then the *mrmuldv* module is not required in the MIRACL library.

If using the Microsoft Visual C++ tool, some helpful advice can be found in the file *msvisual.txt*. If using the Linux operating system, check out *linux.txt*. Users of the Borland compiler should look at *borland.txt*.

In the majority of cases where pre-built libraries or specific advice in a *.txt* file is not available, the following procedure will result in a successful build of the MIRACL library:-

1. Compile and run *config.c* on the target processor.

2. Rename the generated file *mirdef.tst* to *mirdef.h*

3. If so advised by the **config** program, extract a suitable *mrmuldv.c* file from *mrmuldv.any* (or copy the standard C version *mrmuldv.ccc* to *mrmuldv.c* and use this). If it is pure assembly language it may be appropriate to name it *mrmuldv.s* or *mrmuldv.asm*.

4. If the fast **KCM** or **Comba** methods for modular multiplication were selected (see below), compile and run the *mex.c* utility on any workstation. Use it to automatically generate either the module *mrcomba.c* or *mrkcm.c*. This will require a processor/compiler-specific *xxx.mcs* file. The compiler must support inline assembly.

5. Make sure that all the MIRACL header files are accessible to the compiler. Typically the flag –I. or /I. allows these headers to be accessed from the current directory.

6. Compile the MIRACL modules listed in the generated file *miracl.lst* and create a library file, typically *miracl.a* or *miracl.lib*. This might be achieved by editing *miracl.lst* into a suitable batch or make file. On UNIX it might be as simple as:
```
gcc –I. –c –O2 mr*.c
ar rc miracl.a mr*.o
```
7. If using the C++ MIRACL wrapper, compile the required modules, for example *zzn.cpp* and/or *big.cpp* etc.

8. Compile and link your application code to any C++ modules it requires and to the MIRACL library.

Remember that MIRACL is portable software. It may be ported to any computer which supports an ANSI C compiler.

Note that MIRACL is a C library, not C++. It should always be built as a C library otherwise you might get compiler errors. To include MIRACL routines in a C program, include the header *miracl.h* at the start of the program, after including the C standard header *stdio.h* . You may also call MIRACL routines directly from a C++ program by:-
```
extern "C"

{
     #include "miracl.h"
}
```
although in most cases it will be preferable to use the C++ wrapper classes described in 'The C++ Interface' section.

## Optimising <a id="optimising"></a>

In the context of MIRACL this means speeding things up. A critical decision to be made when configuring MIRACL is to determine the optimal underlying type to use. Usually this will be the *int* type. In general try to define the maximum possible underlying type, as requested by *config*. If you have a 64-bit processor, you should be able to specify a 64-bit underlying type. In some circumstances it may be faster to use a floating-point **double** underlying type.

Obviously an all-C build of MIRACL will be slowest (but still pretty fast!). It is also the easiest to start with. This requires an integer data type twice the width of the underlying type. In this context note that these days most compilers support a long long integer type which is twice the width of the int. Sometimes it is called **__int64** instead of **long long**.

If your processor is of the extreme RISC variety and supports no integer multiplication/division instruction, or if using a very large modulus, then the Karatsuba-Montgomery-Comba technique for fast modular multiplication may well be faster for exponentiation cryptosystems. Again the *config* program will guide you through this.

It is sometimes faster to implement the *mrmuldv* module in assembly language. This does not require the double-width data type. If you are lucky your compiler will also be supported by automatically invoked inline assembly, which will speed things up even further. See *miracl.h* to see which compilers are supported in this way.

For the ultimate speed, use the extreme techniques implemented in *mrkcm.c*, *mrcomba.c*.  See *kcmcomba.txt* for instructions on how to automatically generate these files using the supplied **mex** utility. See also 'Implementation' for more details.

## Upgrading from Version 3 <a id="upgrading"></a>

Version 4.0 introduces the Miracl Instance Pointer, or **mip**. Previous versions used a number of global and static variables to store internal status information. There are two problems with this. Firstly such globals have to be given obscure names to avoid clashes with other project globals. Secondly it makes multi-threaded applications much more difficult to develop. So from Version 4.0 all such variables, now referred to as instance variables, are members of a structure of type *miracl*, and must be accessed via a pointer to an instance of this structure. This global pointer is now the only static/global variable maintained by the MIRACL library. Its value is returned by the **mirsys** routine, which initialises the MIRACL library.

C++ programmers should note the change in the name of the instance class from miracl to Miracl. The **mip** can be found by taking the address of this instance:
```
Miracl precision=50;
.
mip=&precision;
.
etc
```
## Multi-Threaded Programming <a id="multi"></a>

From version 4.4 MIRACL offers full support for Multi-threaded programming. This comes in various flavours.

The problem to be overcome is that MIRACL has to have access to a lot of instance specific status information via its *mip*. Ideally there should be no global variables, but MIRACL has this one pointer. Unfortunately every thread that uses MIRACL needs to have its own *mip*, pointing to its own independent status. This is a well-known issue that arises with threads.

The first solution is to modify MIRACL so that the *mip*, instead of being a global, is passed as a parameter to every MIRACL function. The MIRACL routines can be automatically modified to support this by defining **MR_GENERIC_MT** in *mirdef.h* . Now (almost all) MIRACL routines are changed such that the *mip* is the first parameter to each function. Some simple functions are exceptions and do not require the *mip* parameter – these are marked with an asterix in 'The MIRACL Routines' section. For an example of a program modified to work with a MIRACL library built in this way, see the program *brent_mt.c* . Note however that this solution does NOT apply to programs written using the MIRACL C++ wrapper described in 'The C++ Interface' section. It only applies to C programs that access the MIRACL routines directly.

An alternative solution is to use Keys, which are a type of thread specific “global” variable. These *Keys* are not part of the C/C++ standard, but are operating system specific extensions, implemented via special function calls. MIRACL provides support for both Microsoft Windows and Unix operating systems. In the former case these Keys are called *Thread-Local Storage*. See [Richter] for more information. For Unix MIRACL supports the POSIX standard interface for multithreading. A very useful reference for both Windows and Unix is [Walmsley]. This support for threads is implemented in the module *mrcore.c*, at the start of the file and in the initialisation routine **mirsys**.

For Windows, define **MR_WINDOWS_MT** in *mirdef.h*, and for Unix define **MR_UNIX_MT**. In either case there are some programming implications.

In the first place the *Key* that is to maintain the mip must be initialised and ultimately destroyed by the programs primary thread. These functions are carried out by calls to the special routines **mr_init_threading** and **mr_end_threading** respectively.

In C++ programs these functions might be associated with the constructor and destructor of a global variable [Walmsley] – this will ensure that they are called at the appropriate time before new threads are forked off from the main thread. They must be called before any thread calls **mirsys** either explicitly, or implicitly by creating a thread-specific instance of the class Miracl.

It is strongly recommended that program development be carried out without support for threads. Only when a program is fully tested and debugged should it be converted into a thread.

Threaded programming may require other OS-specific measures, in terms of linking to special libraries, or access to special heap routines. In this regard it is worth pointing out that all MIRACL heap accesses are via the module *mralloc.c* .

See the example program *threadwn.cpp* for an example of Windows C++ multithreading. Read the comments in this program – it can be compiled and run from a Windows Command prompt. Similarly see *threadux.cpp* for an example of Unix multi-threading.

## Constrained Environments <a id="contrained"></a>

In version 5 of MIRACL there is new support for implementations in very small and constrained environments. Using the *config* utility it is now possible to allow various time/space trade-offs, but the main innovation is the possibility of building and using MIRACL in an environment which does not support a heap. Normally space for big variables is obtained from the heap, but by specifying in the configuration header **MR_STATIC**, a version of the library is built which will always attempt to allocate space not from the heap, but from static memory or from the stack.

The main downside to this is that the maximum size of big variables must be set at compile time, when the library is being created. As always it is best to let the config utility guide you through the process of creating a suitable *mirdef.h* configuration header.

For the C programmer, the allocation of memory from the stack for big variables proceeds as follows:
```
big x,y,z;
char mem[MR_BIG_RESERVE(3)];
memset(mem,0, MR_BIG_RESERVE(3));
```
This allocates space for 3 big variables on the stack, and set that memory to zero. Each individual big variable is then initialised as:
```
x=mirvar_mem(mem,0);
y=mirvar_mem(mem,1);
z=mirvar_mem(mem,2);
```
Allocating all the space for multiple big variables from a single chunk of memory makes sense, as it leads to a faster initialization, and also gives complete control over variable alignment, which compilers sometimes get wrong. Note that in this mode the usual big number initialization function *mirvar* is no longer available, and allocation must be implemented as described above.

Finally this memory chunk may optionally be cleared before leaving a function by a final call to *memset(.)* – this may be important for security reasons. For an example see the program *brent.c* .

This mechanism may be particularly useful when trying to implement a very small program using elliptic curves, which anyway require much smaller big numbers than other cryptographic techniques. To allocate memory from the stack for an elliptic curve point:
```
epoint *x,*y,*z;
char mem[MR_ECP_RESERVE(3)];
memset(mem,0, MR_ECP_RESERVE(3));
```
To initialize these points:
```
x=epoint_init_mem(mem,0);
y=epoint_init_mem(mem,1);
z=epoint_init_mem(mem,2);
```
Again it may be advisable to clear the memory associated with these points before exiting the function.

This mechanism is fully supported for C++ programs as well, where it works in conjunction with the stack allocation method described in 'The C++ Interface' section. See *pk-demo.cpp* for an  example of usage.

In some extreme cases it may be desired to use only the stack for all memory allocation. This allows maximum use and re-use of memory, and avoids any fragmentation of precious RAM. This can be achieved for C programs by defining *MR_GENERIC_MT* in **mirdef.h**. See above for more details on this option.

A typical *mirdef.h* header in this case might look like:
```
/*
 *   MIRACL compiler/hardware definitions - mirdef.h
 *   Copyright (c) 1988-2005 Shamus Software Ltd.
 */


#define MR_LITTLE_ENDIAN
#define MIRACL 32
#define mr_utype int
#define MR_IBITS 32
#define MR_LBITS 32
#define mr_unsign32 unsigned int
#define mr_dltype __int64
#define mr_unsign64 unsigned __int64
#define MR_STATIC 7
#define MR_ALWAYS_BINARY
#define MR_NOASM
#define MAXBASE ((mr_small)1<<(MIRACL-1))
#define MR_BITSINCHAR 8
#define MR_SHORT_OF_MEMORY
#define MR_GENERIC_MT
#define MR_STRIPPED_DOWN
```
For examples of programs which use this kind of header, see *ecsgen_s.c*, *ecsign_s.c* and *ecsver_s.c*, and *ecsgen2s.c*, *ecsign2s.c* and *ecsver2s*. These programs implement very small and fast ECDSA key generation, digital signature, and verification on a Pentium using Microsoft C++. See *ecdh2m.c* and *ecdhp.c* for more nice examples, which use precomputation to speed up EC Diffie-Hellman implementations.

For small 8 and 16-bit processors, see example programs *ecdhp8.c*, *ecdhp16.c*, *ecdh2m8.c* and *ecdh2m16.c* .

> Doing without a heap is a little problematical. Structures can no longer be of variable size, and so various features of MIRACL become unavailable in this mode. For example precomputations such as required for application of the Chinese remainder theorem are no longer supported. However in a constrained environment it could be reasonably assumed that such precomputations are carried out offline, and made available to the constrained program fixed in ROM.

The MIRACL modules are carefully designed so that an application will only pull in the minimal number of modules from the library for any given task. This helps to keep the program size down to a minimum. However if program size is a big issue then extra savings can sometimes be made by manually deleting from the modules functions that are not needed by your particular program (the linker will complain if the function is in fact needed).

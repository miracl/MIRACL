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
* MIRACL Error Messages
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


MIRACL Error Messages
---

* [Number base too big for representation](#toobig)
* [Division by zero attempted](#zero)
* [Overflow - number too big](#overflow)
* [Internal result is negative](#negative)
* [Input format error](#formaterror)
* [Illegal number base](#illegalnumberbase)
* [Illegal parameter usage](#illegalparameterusage)
* [Out of space](#outofspace)
* [Even root of a negative number](#evenroot)
* [Raising integer to negative power](#negpower)
* [Integer operation attempted on flash number](#integer)
* [Flash overflow](#flashoverflow)
* [Numbers too big](#numberstoobig)
* [Log of a non-positive number](#logofpositive)
* [Flash to double conversion failure](#doubleconversion)
* [MIRACL not initialised](#notinitialised)
* [I/O buffer overflow](#bufferoverflow)
* [Illegal modulus](#illegalmodulus)
* [No modulus defined](#nomodulus)
* [Exponent too big](#exponent)
* [Number base must be power of 2](#power)
* [Specified double-length type isn't](#specified)
* [Specified basis is not irreducible](#notirreducible)

## Number base too big for representation <a id="toobig"></a>

**Diagnosis**

An attempt has been made to input or output a number using a number base that is too big. For example, outputting using a number base of 2<sup>32</sup> is clearly impossible. For efficiency, the largest possible internal number base is used, but numbers in this format should be input/output to a much smaller number base £ 256. This error typically arises when using using *innum(.)* or *otnum(.)* after *mirsys(.,0)*.

**Response**

Perform a change of base prior to input/output. For example set the instance variable **IOBASE** to 10, and then use *cinnum(.)* or *cotnum(.)* . To avoid the change in number base, an alternatively is to initialise MIRACL using something like *mirsys*(400,16) which uses an internal base of 16. Now Hex I/O can be performed using *innum*(.) and *otnum*(.) . This will not impact performance on a 32-bit processor as 8 Hex digits will be packed into each computer word.

## Division by zero attempted <a id="zero"></a>

**Diagnosis**

Self-explanatory.

**Response**

Don't do it!

## Overflow - Number too big <a id="overflow"></a>

**Diagnosis**

A number in a calculation is too big to be stored in its fixed length allocation of memory.

**Response**

Specify more storage space for all *big* and *flash* variables by increasing the value of *n* in the initial call to *mirsys*(n.b);

## Internal Result is Negative <a id="negative"></a>

**Diagnosis**

This is an internal error that should not occur using the high-level MIRACL functions. It may be caused by user-induced memory over-runs.

**Response**

Report to <mike.scott@miracl.com>.

## Input Format Error <a id="formaterror"></a>

**Diagnosis**

The number being input contains one or more illegal symbols with respect to the current I/O number base. For example, this error might occur if IOBASE is set to 10, and a Hex number is input.

**Response**

Re-input the number, and be careful to use only legal symbols. Note that for Hex input only upper-case A-F are permissible.

## Illegal number base <a id="illegalnumberbase"></a>

**Diagnosis**

The number base specified in the call to *mirsys*(.) is illegal. For example, a number base of 1 is not allowed.

**Response**

Use a different number base.

## Illegal parameter usage <a id="illegalparameterusage"></a>

**Diagnosis**

The parameters used in a function call are not allowed. In certain cases, certain parameters must be distinct - for example in *divide*(.) the first two parameters must refer to distinct *big* variables.

**Response**

Read the documentation for the function in question.

## Out of space <a id="outofspace"></a>

**Diagnosis**

An attempt has been made by a MIRACL function to allocate too much heap memory.

**Response**

Reduce your memory requirements. Try using a smaller value of *n* in your initial call to *mirsys(n,b)*.

## Even root of a negative number <a id="evenroot"></a>

**Diagnosis**

An attempt has been made to find the square root of a negative number, for example.

**Response**

Don't do it!

## Raising integer to negative power <a id="negpower"></a>

**Diagnosis**

Self-explanatory.

**Response**

Don't do it!

## Integer operation attempted on flash number <a id="integer"></a>

**Diagnosis**

Certain functions should only be used with *big* numbers, and do not make sense for *flash* numbers. Note that this error message is often provoked by memory problems, where for example the memory allocated to a *big* variable is accidentally over-written.

**Response**

Don't do it!

## Flash overflow <a id="flashoverflow"></a>

**Diagnosis**

This error is provoked by Flash overflow or underflow. The result is outside of the representable dynamic range.

**Response**

Use bigger *flash* numbers. Analyse your program carefully for numerical instability.

## Numbers too big <a id="numberstoobig"></a>

**Diagnosis**

The size of *big* or *flash* numbers requested in your call to *mirsys(.)* are simply too big. The length of each *big* and *flash* is encoded into a single computer word. If there is insufficient room for this encoding, this error message occurs.

**Response**

Build a MIRACL library that uses a bigger "underlying type". If not using Flash arithmetic, build a library without it - this allows much bigger big numbers to be used.

## Log of a non-positive number <a id="logofpositive"></a>

**Diagnosis**

An attempt has been made to calculate the logarithm of a non-positive *flash* number.

**Response**

Don't do it!

## Flash to double conversion failure <a id="doubleconversion"></a>

**Diagnosis**

An attempt to convert a Flash number to the standard built-in C *double* type has failed, probably because the Flash number is outside of the dynamic range that can be represented as a *double*.

**Response**

Don't do it!

## I/O buffer overflow <a id="bufferoverflow"></a>

**Diagnosis**

An input output operation has failed because the I/O buffer is not big enough.

**Response**

Allocate a bigger buffer by calling *set_io_buffer_size(.)* after calling *mirsys(.)*.

## MIRACL not initialised - <a id="notinitialised"></a>

**Diagnosis**

Self-explanatory

**Response**

Don't do it!

## Illegal modulus <a id="illegalmodulus"></a>

**Diagnosis**

The modulus specified for use internally for Montgomery reduction, is illegal. Note that this modulus must not be even.

**Response**

Use an odd positive modulus.

## No modulus defined <a id="nomodulus"></a>

**Diagnosis**

No modulus has been specified, yet a function which needs it has been called.

**Response**

Set a modulus for use internally

## Exponent too big <a id="exponent"></a>

**Diagnosis**

An attempt has been made to perform a calculation using a pre-computed table, for an exponent (or multiplier in the case of elliptic curves) bigger than that catered for by the pre-computed table.

**Response**

Re-compute the table to allow bigger exponents, or use a smaller exponent.

## Number base must be power of 2 <a id="power"></a>

**Diagnosis**

A small number of functions require that the number base specified in the initial call to *mirsys(.)* is a power of 2.

**Response**

Use another function, or specify a power-of-2 as the number base in the initial call to *mirsys(.)*

## Specified double-length type isn't <a id="specified"></a>

**Diagnosis**

MIRACL has determined that the double length type specified in *mirdef.h* is in fact not double length. For example if the underlying type is 32-bits, the double length type should be 64 bits.

**Response**

Don't do it!

## Specified basis is not irreducible <a id="notirreducible"></a>

**Diagnosis**

The basis specified for GF(2<sup>m</sup>) arithmetic is not irreducible.

**Response**

Don't do it!

* [What Is Miracl](../README.md)
* [Security Advisory](../security-advisory.md)
* [Benchmarks](../benchmarks.md)
* [Miracl Standard Curves](../miracl-standard-curves.md)
* [IEEE 1363](../ieee-1363.md)
* [Elliptic Curves](../elliptic-curves.md)
* [Licensing](../licensing.md)
* Reference Manual
	* Low Level Routines
	* [Advanced Arithmetic Routines](advanced-arithmetic-routines.md)
	* [Montgomery Arithmetic Routines](montgomery-arithmetic-routines.md)
	* [ZZn2 Arithmetic Routines](zzn2-arithmetic-routines.md)
	* [Encryption Routines](encryption-routines.md)
	* [Elliptic Curve Routines](elliptic-curve-routines.md)
	* [Floating Slash Routines](floating-slash-routines.md)
	* [Structure Reference](structure-reference.md)


Low Level Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void absol* (flash x, flash y)

Gives absolute value of a big or flash number.

**Parameters:**

←|x The number whose absolute value is to be computed<br />
→y = |x|

## void add (big x, big y, big z)

Adds two big numbers.

**Parameters:**

←x<br />
→y<br />
→z = x + y

**Example:**
```
add(x, x, x); // This doubles the value of x
```
## int big_to_bytes (int max, big x, char * ptr, BOOL justify)

Converts a positive big number into a binary octet string. Error checking is carried out to ensure that the
function does not write beyond the limits of ptr if `max > 0`. If `max = 0`, no checking is carried out. If `max > 0 and justify = TRUE`, the output is right-justified, otherwise leading zeros are supressed.

**Parameters:**

←max Maximum number of octets to be written in ptr<br />
←x The original big number<br />
→ptr Destination of the binary octet string<br />
→justify If TRUE, the output is right-justified, otherwise leading zeros are supressed.

**Returns:**

The number of bytes generated in ptr. If justify = TRUE then the return value is max.

**Precondition:**

max must be greater than 0 if justify = TRUE

## void bigbits (int n, big x)

Generates a big random number of given length. Uses the built-in simple random number generator initialised
by irand().

**Parameters:**

←n The desired length of the random big number<br />
→x The random number

## mr_small brand (void)

Generates random integer number.

**Returns:**

A random integer number.

**Precondition:**

First use must be preceded by an initial call to irand().

> This generator is not cryptographically strong. For cryptographic applications, use the strong_rng() routine.

## void bytes_to_big (int len, char * ptr, big x)

Converts a binary octet string to a big number. Binary to big conversion.

**Parameters:**

←len Length of ptr<br />
←ptr Byte array of the binary octet string<br />
→x Big result

**Example:**
```
#include <stdio.h>
#include "miracl.h"

int main()
{
int i, len;
miracl *mip = mirsys(100, 0);
big x, y;
char b[200]; // b needs space allocated to it
x = mirvar(0); // all big variables need to be "mirvar"ed
y = mirvar(0);

expb2(100, x);
incr(x, 3, x); // x = 2^100 + 3

len = big_to_bytes(200, x, b, FALSE);
// Now b contains big number x in raw binary
// It is len bytes in length

// now print out the raw binary number b in hex
for (i = 0; i < len; i++) printf("%02x", b[i]);
printf("n");

// now convert it back to big format, and print it out again
bytes_to_big(len, b, y);
mip->IOBASE = 16;
cotnum(y, stdout);

return 0;
}
```
## int cinnum (flash x, FILE * filep)

Inputs a flash/big number from the keyboard or a file, using as number base the current value of the instance variable miracl::IOBASE. Flash numbers can be entered using either a slash '/' to indicate numerator and denominator, or with a radix point.

**Parameters:**

→x Big/flash number

←filep File descriptor. For input from the keyboard specify stdin, otherwise as the descriptor of
some other opened file.

> To force input of a fixed number of bytes, set the instance variable miracl::INPLEN to the required number, just before calling cinnum().

**Example:**
```
mip->IOBASE = 256;
mip->INPLEN = 14; // this inputs 14 bytes from fp and
cinnum(x, fp); // converts them into big number x
```
## int cinstr (flash x, char * string)

Inputs a flash/big number from a character string, using as number base the current value of the instance
variable miracl::IOBASE. Flash numbers can be input using a slash '/' to indicate numerator and denominator,
or with a radix point.

**Parameters:**

→x<br />
←string

**Returns:**

The number of input characters.

**Example:**
```
// input large hex number into big x
mip->IOBASE = 16;
cinstr(x, "AF12398065BFE4C96DB723A");
```
## int compare* (big x, big y)

Compares two big numbers.

**Parameters:**

←x<br />
→y

**Returns:**

+1 if x > y; 0 if x = y; -1 if x < y

## void convert (int n, big x)

Converts an integer number to big number format.

**Parameters:**

←n<br />
→x

## void copy* (flash x, flash y)

Copies a big/flash number to another.

**Parameters:**

←x<br />
→y= x

**Parameters:**If x and y are the same variable, no operation is performed.

## int cotnum (flash x, FILE * filep)

Outputs a big/flash number to the screen or to a file, using as number base the value currently assigned to
the instance variable miracl::IOBASE. A flash number will be converted to radix-point representation if
the instance variable miracl::RPOINT = ON. Otherwise it will output as a fraction.

**Parameters:**

←x Big/flash number to be output<br />
→filep File descriptor. If stdout then output will be to the screen, otherwise to the file opened with
descriptor filep.

**Returns:**

Number of output characters.

**Example:**
```
// This outputs x in hex, to the file associated with fp
mip->IOBASE = 16;
cotnum(x, fp);
```
## int cotstr (flash x, char * string)

Outputs a big/flash number to the specified string, using as number base the value currently assigned to the
instance variable miracl::IOBASE. A flash number will be converted to radix-point representation if the
instance variable miracl::RPOINT = ON. Otherwise it will be output as a fraction.

**Parameters:**

←x<br />
→string

**Returns:**

Number of output characters.

> There is nothing to prevent this routine from overflowing the limits of the user supplied
> character array string, causing obscure runtime problems. It is the programmer's responsibility to
> ensure that string is big enough to contain the number output to it. Alternatively use the internally
> declared instance string miracl::IOBUFF, which is of size miracl::IOBSIZ. If this array overflows a
> MIRACL error will be flagged.

## void decr (big x, int n, big z)

Decrements a big number by an integer amount.

**Parameters:**

←x<br />
←n<br />
→z = x − n

## void divide (big x, big y, big z)

Divides one big number by another: z = x/y, x = x (mod y). The quotient only is returned if x and z
are the same, the remainder only if y and z are the same.

**Parameters:**

←→x<br />
→y<br />
→z

**Precondition:**

Parameters x and y must be different, and y must be non-zero.

> See also: **normalise()**

## BOOL divisible (big x, big y)

Tests a big number for divisibility by another.

**Parameters:**

←x<br />
→y

**Returns:**

TRUE if y divides x exactly, otherwise FALSE.

**Precondition:**

The parameter y must be non-zero.

## void* ecp_memalloc (int num)

Reserves space for a number elliptic curve points in one heap access. Individual points can subsequently
be initialised from this memory by calling epoint_init_mem().

**Parameters:**

←num The number of elliptic curve points to reserve space for.

**Returns:**

A pointer to the allocated memory.

## void ecp_memkill (char * mem, int num)

Deletes and sets to zero the memory previously allocated by ecp_memalloc().

**Parameters:**

→mem Pointer to the memory to be erased and deleted<br />
←num The size of the memory in elliptic curve points

**Precondition:**

Must be preceded by a call to ecp_memalloc().

## int exsign* (flash x)

Extracts the sign of a big/flash number.

**Parameters:**

←x A big/flash number

**Returns:**

The sign of x, i.e. -1 if x is negative, +1 if x is zero or positive.

## miracl* get_mip ()

Gets the current Miracl Instance Pointer.

**Returns:**

The mip (Miracl Instance Pointer) for the current thread.

**Precondition:**

This function does not exist if MR_GENERIC_MT is defined.

## int getdig (big x, int i)

Extracts a digit from a big number.

**Parameters:**

←x A big number<br />
→i The position of the digit to be extracted from x

**Returns:**

The value of the requested digit.

> Returns rubbish if required digit does not exist.

## unsigned int igcd* (unsigned int x, unsigned int y)

Calculates the Greatest Common Divisor of two integers using Euclid's Method.

**Parameters:**

←x<br />
←y

**Returns:**

The GCD of x and y.

## void incr (big x, int n, big z)

Increments a big number.

**Parameters:**

←x<br />
←n<br />
→z = x + n

**Example:**
```
incr(x, 2, x); // This increments x by 2
```
## BOOL init_big_from_rom (big x, int len, const mr_small * rom, int romsize, int * romptr)

Initialises a big variable from ROM memory.

**Parameters:**

→rx A big number<br />
←len Length of the big number in computer words<br />
←rom Address of ROM memory which stores up to romsize computer words<br />
←romsize<br />
←→romptr A pointer into ROM. This pointer is incremented internally as ROM memory is accessed
to fill x

**Returns:**

TRUE if successful, or FALSE if an attempt is made to read beyond the end of the ROM.

## BOOL init_point_from_rom (epoint * P, int len, const mr_small * rom, int romsize, int * romptr)

Initialises an elliptic curve point from ROM memory.

**Parameters:**

→P An elliptic curve point<br />
←len Length of the two big coordinates of P, in computer words<br />
←rom Address of ROM memory which stores up to romsize computer words<br />
←romsize<br />
←→romptr A pointer into ROM. This pointer is incremented internally as ROM memory is accessed
to fill P

**Returns:**

TRUE if successful, or FALSE if an attempt is made to read beyond the end of the ROM.

## int innum (flash x, FILE * filep)

Inputs a big/flash number from a file or the keyboard, using as number base the value specified in the
initial call to mirsys(). Flash numbers can be entered using either a slash '/' to indicate numerator and
denominator, or with a radix point.

**Parameters:**

→x A big/flash number<br />
←filep A file descriptor. For input from the keyboard specify stdin, otherwise the descriptor of
some other opened file.

**Returns:**

The number of characters input.

**Precondition:**

The number base specified in mirsys() must be less than or equal to 256. If not use cinnum() instead.

> For fastest inputting of ASCII text to a big number, and if a full-width base is possible, use mirsys(...,256) initially. This has the same effect as specifying mirsys(...,0), except that now ASCII bytes may be input directly via innum(x, fp) without the time-consuming change of base implicit in the use of cinnum().

## void insign* (int s, flash x)

Forces a big/flash number to a particular sign.

**Parameters:**

←s The sign the big/flash is to take<br />
→x = s|x|

**Example:**
```
insign(PLUS, x); // force x to be positive
```
## int instr (flash x, char * string)

Inputs a big or flash number from a character string, using as number base the value specified in the
initial call to mirsys(). Flash numbers can be entered using either a slash '/' to indicate numerator and
denominator, or with a radix point.

**Parameters:**

→x<br />
←string

**Returns:**

The number of characters input.

**Precondition:**

The number base specified in mirsys() must be less than or equal to 256. If not use cinstr() instead.

## void irand (mr_unsign32 seed)

Initialises internal random number system. Long integer types are used internally to yield a generator with
maximum period.

**Parameters:**

←seed A seed used to start off the random number generator.

## void lgconv (long n, big x)

Converts a long integer to big number format.

**Parameters:**

←n<br />
→x
## void mad (big x, big y, big z, big w, big q, big r)

Multiplies, adds and divides big numbers. The initial product is stored in a double-length internal variable
to avoid the possibility of overflow at this stage.

**Parameters:**

←x<br />
←y<br />
←z<br />
←w<br />
→q = (xy + z)/w<br />
→r The remainder

> If w and q are not distinct variables then only the remainder is returned; if q and r are not distinct then only the quotient is returned. The addition of z is not done if x and z (or y and z) are the same.

**Precondition:**

Parameters w and r must be distinct. The value of w must not be zero.

**Example:**
```
mad(x, x, x, w, x, x,); // x = x^2 / w
```
## void* memalloc (int num)

Reserves space for big/flash variables in one heap access. Individual big/flash variables can subsequently
be initialised from this memory by calling mirvar_mem().

**Parameters:**

←num The number of big/flash variables to reserve space for.

**Returns:**

A pointer to the allocated memory

## void memkill (char * mem, int len)

Deletes and sets to zero the memory previously allocated by memalloc().

**Parameters:**

→mem A pointer to the memory to be erased and deleted<br />
←len The size of that memory in bigs

**Precondition:**

Must be preceded by a call to memalloc()

## void mirexit (void)

Cleans up after the current instance of MIRACL, and frees all internal variables. A subsequent call to
mirsys() will re-initialise the MIRACL system.

**Precondition:**

Must be called after mirsys().

## void mirkill* (big x)

Securely kills off a big/flash number by zeroising it, and freeing its memory.

**Parameters:**

←x.

## miracl* mirsys (int nd, mr_small nb)

Initialises the MIRACL system for the current program thread, as described below. Must be called before
attempting to use any other MIRACL routines

1. The error tracing mechanism is initialised.
2. The number of computer words to use for each big/flash number is calculated from nd and nb.
3. Sixteen big work variables (four of them double length) are initialised.
4. Certain instance variables are given default initial values.
5. The random number generator is started by calling irand(0L).

**Parameters:**

←nd The number of digits to use for each big/flash variable. If negative, it is taken as indicating the
size of big/flash numbers in 8-bit bytes<br />
→nb The number base

**Returns:**

The Miracl Instance Pointer, via which all instance variables can be accessed, or NULL if there was
not enough memory to create an instance

**Precondition:**

The number base nb should normally be greater than 1 and less than or equal to MAXBASE. A base of
0 implies that the 'full-width' number base should be used. The number of digits nd must be less than
a certain maximum, depending on the underlying type mr_utype and on whether or not MR_FLASH
is defined

**Example:**
```
// This initialises the MIRACL system to use 500 decimal digits for each
// big or flash number
miracl *mip = mirsys(500, 10);
```
## flash mirvar (int iv)

Initialises a big/flash variable by reserving a suitable number of memory locations for it. This memory may
be released by a subsequent call to the function mirkill().

**Parameters:**

←iv An integer initial value for the big/flash number

**Returns:**

A pointer to the reserved memory

**Example:**
```
flash x;
x = mirvar(8); // Creates a flash variable x = 8
```
## flash mirvar_mem (char * mem, int index)

Initialises memory for a big/flash variable from a pre-allocated byte array mem. This array may be created
from the heap by a call to memalloc(), or in some other way. This is quicker than multiple calls to mirvar().

**Parameters:**

←mem A pointer to the pre-allocated array<br />
←index An index into that array. Each index should be unique

**Returns:**

An initialised big/flash variable

**Precondition:**

Sufficient memory must have been allocated and pointed to by mem.

## void multiply (big x, big y, big z)

Multiplies two big numbers.

**Parameters:**

←x<br />
←y<br />
→z = xy

## void negify* (flash x, flash y)

Negates a big/flash number.

**Parameters:**

←x<br />
→y = - x

> negify(x,x) is valid and sets x = - x

## mr_small normalise (big x, big y)

Multiplies a big number such that its most significant word is greater than half the number base. If such
a number is used as a divisor by divide(), the division will be carried out faster. If many divisions by the
same divisor are required, it makes sense to normalise the divisor just once beforehand.

**Parameters:**

←x<br />
→y = nx

**Returns:**

n, the normalising multiplier

> Use with care. Used internally.

## int numdig (big x)

Determines the number of digits in a big number.

**Parameters:**

←x

**Returns:**

The number of digits in x.

## int otnum (flash x, FILE * filep)

Outputs a big/flash number to the screen or to a file, using as number base the value specified in the initial
call to mirsys(). A flash number will be converted to radix-point representation if the instance variable
miracl::RPOINT = ON. Otherwise it will be output as a fraction.

**Parameters:**

←x A big/flash number<br />
←filep A file descriptor. If stdout then output will be to the screen, otherwise to the file opened with descriptor filep

**Returns:**

Number of output characters

**Precondition:**

The number base specified in mirsys() must be less than or equal to 256. If not, use cotnum() instead.

## int otstr (flash x, char * string)

Outputs a big or flash number to the specified string, using as number base the value specified in the initial
call to mirsys(). A flash number will be converted to radix-point representation if the instance variable
miracl::RPOINT = ON. Otherwise it will be output as a fraction.

**Parameters:**

←x A big/flash number<br />
→string A representation of x

**Returns:**

Number of output characters

**Precondition:**

The number base specified in mirsys() must be less than or equal to 256. If not, use cotstr() instead

> There is nothing to prevent this routine from overflowing the limits of the user supplied
> character array string, causing obscure runtime problems. It is the programmer's responsibility to
> ensure that string is big enough to contain the number output to it. Alternatively use the internally
> declared instance string miracl::IOBUFF, which is of size miracl::IOBSIZ. If this array overflows a
> MIRACL error will be flagged.

## void premult (big x, int n, big z)

Multiplies a big number by an integer.

**Parameters:**

←x<br />
←n<br />
→z = nx

## void putdig (int n, big x, int i)

Sets a digit of a big number to a given value.

**Parameters:**

←n The new value for the digit<br />
→x A big number<br />
←i A digit position

**Precondition:**

The digit indicated must exist.

## int remain (big x, int n)

Finds the integer remainder, when a big number is divided by an integer.

**Parameters:**

←x<br />
←n

**Returns:**

The integer remainder.

## void set_io_buffer_size (int len)

Sets the size of the input/output buffer. By default this is set to 1024, but programs that need to handle very
large numbers may require a larger I/O buffer.

**Parameters:**

←len The size of I/O buffer required

> Destroys the current contents of the I/O buffer.

## void set_user_function (BOOL(*)(void) user)

Supplies a user-specified function, which is periodically called during some of the more time-consuming
MIRACL functions, particularly those involved in modular exponentiation and in finding large prime numbers.
The supplied function must take no parameters and return a BOOL value. Normally this should be
TRUE. If FALSE then MIRACL will attempt to abort its current operation. In this case the function should
continue to return FALSE until control is returned to the calling program. The user-supplied function
should normally include only a few instructions, and no loops, otherwise it may adversely impact the speed
of MIRACL functions

Once MIRACL is initialised, this function may be called multiple times with a new supplied function. If
no longer required, call with a NULL parameter.

**Parameters:**

←user A pointer to a user-supplied function, or NULL if not required

**Example:**
```
// Windows Message Pump
static BOOL idle()
{
MSG msg;
if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
{
if (msg.message != WM_QUIT)
{
if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
{
// do a Message Pump
TranslateMessage(&msg);
DispatchMessage(&msg);
}
}
else
return FALSE;
}
return TRUE;
}
...
set_user_function(idle);
```
## int size* (big x)

Tries to convert big number to a simple integer. Also useful for testing the sign of big/flash variable as in:
if (size(x) < 0) ...

**Parameters:**

←x A big number

**Returns:**

The value of x as an integer. If this is not possible (because x is too big) it returns the value plus or
minus MR_TOOBIG.

## int subdiv (big x, int n, big z)

Divides a big number by an integer

**Parameters:**

←x<br />
←n<br />
→z = x/n

**Returns:**

The integer remainder

**Precondition:**

The value of n must not be zero.

## BOOL subdivisible (big x, int n)

Tests a big number for divisibility by an integer.

**Parameters:**

←x<br />
←n

**Returns:**

TRUE if n divides x exactly, otherwise FALSE

**Precondition:**

The value of n must not be zero.

## void subtract (big x, big y, big z)

Subtracts two big numbers.

**Parameters:**

←x<br />
←y<br />
→z = x − y

## void zero* (flash x)

Sets a big/flash number to zero.

**Parameters:**

→x

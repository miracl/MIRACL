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
	* Floating Slash Routines
	* [Structure Reference](structure-reference.md)


Floating Slash Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void build (flash x, int(*)(_MIPT_ big, int) gen)

Uses supplied generator of regular continued fraction expansion to build up a flash number x, rounded if
necessary.

**Parameters:**

→x The flash number created<br />
←gen The generator function

**Example:**
```
int phi(flash w, int n)
{
// rcf generator for golden ratio //
return 1;
}
...
build(x, phi);
...
// This will calculate the golden ratio (1 + sqrt(5)) / 2 in x -- very quickly!
```
## void dconv (double d, flash w)

Converts a double to flash format.

**Parameters:**

←d<br />
→w The flash equivalent of d

## void denom (flash x, big y)

Extracts the denominator of a flash number.

**Parameters:**

←x<br />
→y The denominator of x

## void facos (flash x, flash y)

Calculates arc-cosine of a flash number, using fasin().

**Parameters:**

←x<br />
→y = arccos(x)

**Precondition:**

|x| must be less than or equal to 1.

## void facosh (flash x, flash y)

Calculates hyperbolic arc-cosine of a flash number.

**Parameters:**

←x<br />
→y = arccosh(x)

**Precondition:**

|x| must be greater than or equal to 1.

## void fadd (flash x, flash y, flash z)

Adds two flash numbers.

**Parameters:**

←x<br />
←y<br />
→z = x + y

## void fasin (flash x, flash y)

Calculates arc-sin of a flash number, using fatan().

**Parameters:**

←x<br />
→y = arcsin(x)

**Precondition:**

|x| must be less than or equal to 1.

## void fasinh (flash x, flash y)

Calculates hyperbolic arc-sin of a flash number.

**Parameters:**

←x<br />
→y = arcsinh(x)

## void fatan (flash x, flash y)

Calculates the arc-tangent of a flash number, using an O(n2.5) method based on Newton's iteration.

**Parameters:**

←x<br />
→y = arctan(x)

### void fatanh (flash x, flash y)

Calculates the hyperbolic arc-tangent of a flash number.

**Parameters:**

←x<br />
→y = arctanh(x)

**Precondition:**

x2 must be less than 1

### int fcomp (flash x, flash y)

Compares two flash numbers.

**Parameters:**

←x<br />
←y

**Returns:**

-1 if y > x, +1 if x > y and 0 if x = y

### void fconv (int n, int d, flash x)

Converts a simple fraction to flash format.

**Parameters:**

←n<br />
←d<br />
→x = n/d

### void fcos (flash x, flash y)

Calculates cosine of a given flash angle, using ftan().

**Parameters:**

←x<br />
→y = cos(x)

### void fcosh (flash x, flash y)

Calculates hyperbolic cosine of a given flash angle.

**Parameters:**

←x<br />
→y = cosh(x)

### void fdiv (flash x, flash y, flash z)

Divides two flash numbers.

**Parameters:**

←x<br />
←y<br />
→z = x/y

### double fdsize (flash w)

Converts a flash number to double format.

**Parameters:**

←w

**Returns:**

The value of the parameter x as a double

**Precondition:**

The value of x must be representable as a double.

### void fexp (flash x, flash y)

Calculates the exponential of a flash number using O(n2.5) method.

**Parameters:**

←x<br />
→y = ex

### void fincr (flash x, int n, int d, flash y)

Add a simple fraction to a flash number.

**Parameters:**

←x<br />
←n<br />
←d<br />
→y = x + n/d

**Example:**
```
// This subtracts two-thirds from the value of x
fincr(x, -2, 3, x);
```
### void flog (flash x, flash y)

Calculates the natural log of a flash number using O(n2.5) method.

**Parameters:**

←x<br />
→y = log(x)

### void flop (flash x, flash y, int * op, flash z)

Performs primitive flash operation. Used internally. See source listing comments for more details.

**Parameters:**

←x<br />
←y<br />
←op<br />
→z = Fn(x,y), where the function performed depends on the parameter op.

### void fmodulo (flash x, flash y, flash z)

Finds the remainder when one flash number is divided by another.

**Parameters:**

←x<br />
←y<br />
→z = x (mod y)

### void fmul (flash x, flash y, flash z)

Multiplies two flash numbers.

**Parameters:**

←x<br />
←y<br />
→z = xy

### void fpack (big n, big d, flash x)

Forms a flash number from big numerator and denominator.

**Parameters:**

←n<br />
←d<br />
→x = n/d

**Precondition:**

The denominator must be non-zero. Flash variable x and big variable d must be distinct. The resulting
flash variable must not be too big for the representation.

### void fpi (flash pi)

Calculates π using Gauss-Legendre O(n2 log n) method. Note that on subsequent calls to this routine, π is
immediately available, as it is stored internally. (This routine is disappointingly slow. There appears to be
no simple way to calculate a rational approximation to π quickly).

**Parameters:**

→pi =π

> Internally allocated memory is freed when the current MIRACL instance is ended by a call to mirexit().

### void fpmul (flash x, int n, int d, flash y)

Multiplies a flash number by a simple fraction.

**Parameters:**

←x<br />
←n<br />
←d<br />
→y = xn/d

### void fpower (flash x, int n, flash w)

Raises a flash number to an integer power.

**Parameters:**

←x<br />
←n<br />
→w = xn

### void fpowf (flash x, flash y, flash z)

Raises a flash number to a flash power.

**Parameters:**

←x<br />
←y<br />
→z = xy

### void frand (flash x)

Generates a random flash number.

**Parameters:**

→x A flash random number in the range 0 < x < 1

### void frecip (flash x, flash y)

Calculates reciprocal of a flash number.

**Parameters:**

←x<br />
→y = 1/x

### BOOL froot (flash x, int n, flash w)

Calculates n-th root of a flash number using Newton's O(n2) method.

**Parameters:**

←x<br />
←n<br />
→w = nx

**Returns:**

TRUE for exact root, otherwise FALSE.

### void fsin (flash x, flash y)

Calculates sine of a given flash angle. Uses ftan().

**Parameters:**

←x<br />
→y = sin(x)

### void fsinh (flash x, flash y)

Calculates hyperbolic sine of a given flash angle.

**Parameters:**

←x<br />
→y = sinh(x)

### void fsub (flash x, flash y, flash z)

Subtracts two flash numbers.

**Parameters:**

←x<br />
←y<br />
→z = x − y

### void ftan (flash x, flash y)

Calculates the tan of a given flash angle, using an O(n2.5) method.

**Parameters:**

←x<br />
→y = tan(x)

### void ftanh (flash x, flash y)

Calculates the hyperbolic tan of a given flash angle.

**Parameters:**

←x<br />
→y = tanh(x)

### void ftrunc (flash x, big y, flash z)

Separates a flash number to a big number and a flash remainder.

**Parameters:**

←x<br />
→y = int(x)<br />
→z The fractional remainder. If y is the same as z, only int(x) is returned

### void mround (big num, big den, flash z)

Forms a rounded flash number from big numerator and denominator. If rounding takes place the instance
variable EXACT is set to FALSE. EXACT Is initialised to TRUE in routine mirsys(). This routine is used
internally.

**Parameters:**

←num<br />
←den<br />
→z = R(num/dem)--- the flash number num/dem is rounded if necessary to fit the representation

**Precondition:**

The denominator must be non-zero.

### void numer (flash x, big y)

Extracts the numerator of a flash number.

**Parameters:**

←x<br />
→y the numerator of x

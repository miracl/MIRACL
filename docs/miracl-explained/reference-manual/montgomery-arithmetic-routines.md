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
	* Montgomery Arithmetic Routines
	* [ZZn2 Arithmetic Routines](zzn2-arithmetic-routines.md)
	* [Encryption Routines](encryption-routines.md)
	* [Elliptic Curve Routines](elliptic-curve-routines.md)
	* [Floating Slash Routines](floating-slash-routines.md)
	* [Structure Reference](structure-reference.md)


Montgomery Arithmetic Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void nres (big x, big y)

Converts a big number to n-residue form.

**Parameters:**

←x<br />
→y the n-residue form of x

**Precondition:**

Must be preceded by call to prepare_monty()

> See also: **redc**

## void nres_dotprod (int m, big * x, big * y, big w)

Finds the dot product of two arrays of n-residues. So-called "lazy" reduction is used, in that the sum of
products is only reduced once with respect to the Montgomery modulus. This is quicker---nearly twice as fast.

**Parameters:**

←m<br />
←x An array of m n-residues<br />
←y An array of m n-residues<br />
→w =Σxiyi (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty().

## void nres_double_modadd (big x, big y, big w)

Adds two double length bigs modulo pR, where R = 2n and n is the smallest multiple of the word-length
of the underlying MIRACL type, such that R > p. This is required for lazy reduction.

**Parameters:**

←x<br />
←y<br />
→w = a + b (mod pR)

## void nres_double_modsub (big x, big y, big w)

Subtracts two double length bigs modulo pR, where R = 2n and n is the smallest multiple of the wordlength
of the underlying MIRACL type, such that R > p. This is required for lazy reduction.

**Parameters:**

←x<br />
←y<br />
→w = a − b (mod pR)

## void nres_lazy (big a0, big a1, big b0, big b1, big r, big i)

Uses the method of lazy reduction combined with Karatsuba's method to multiply two zzn2 variables.
Requires just 3 multiplications and two modular reductions.

**Parameters:**

←a0<br />
←a1<br />
←b0<br />
←b1<br />
→r = the "real part" of (a0 + a1i)(b0 + b1i)<br />
→i = the "imaginary part" of (a0 + a1i)(b0 + b1i)

## void nres_lucas (big p, big r, big vp, big v)

Modular Lucas exponentiation of an n-residue.

**Parameters:**

←p An n-residue<br />
←r A big exponent<br />
→vp = Vr−1(p) (mod n) where n is the current Montgomery modulus<br />
→v = Vr(p) (mod n) where n is the current Montgomery modulus

> Only v is returned if v and vp are the same big variable.

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the first parameter to n-residue form.
Note that the exponent is not converted to n-residue form

> See also: **lucas**

## void nres_modadd (big x, big y, big w)

Modular addition of two n-residues.

**Parameters:**

←x<br />
←y<br />
→w = x + y (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by a call to prepare_monty().

## int nres_moddiv (big x, big y, big w)

Modular division of two n-residues.

**Parameters:**

←x<br />
←y<br />
→w = x/y (mod n), where n is the current Montgomery modulus

**Returns:**

GCD of y and n as an integer, if possible, or MR_TOOBIG. Should be 1 for a valid result

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of parameters to n-residue form. Parameters
x and y must be distinct.

## void nres_modmult (big x, big y, big w)

Modular multiplication of two n-residues. Note that this routine will invoke a KCM Modular Multiplier if
MR_KCM has been defined in mirdef.h and set to an appropriate size for the current modulus, or a Comba
fixed size modular multiplier if MR_COMBA is defined as exactly the size of the modulus.

**Parameters:**

←x<br />
←y<br />
→w = xy (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_month() and conversion of parameters to n-residue form.

### void nres_modsub (big x, big y, big w)

Modular subtraction of two n-residues.

**Parameters:**

←x<br />
←y<br />
→w = x − y (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by a call to prepare_monty().

### BOOL nres_multi_inverse (int m, big * x, big * w)

Finds the modular inverses of many numbers simultaneously, exploiting Montgomery's observation that
x−1 = y(xy)−1, y−1 = x(xy)−1. This will be quicker, as modular inverses are slow to calculate, and this
way only one is required.

**Parameters:**

←m The number of inverses required<br />
←x An array of m n-residues whose inverses are wanted<br />
→w An array with the inverses of za x

**Returns:**

TRUE if successful, otherwise FALSE

**Precondition:**

The parameters x and w must be distinct.

### void nres_negate (big x, big w)

Modular negation.

**Parameters:**

←x An n-residue number<br />
→w = −x (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by a call to prepare_monty().

### void nres_powltr (int x, big y, big w)

Modular exponentiation of an n-residue.

**Parameters:**

←x<br />
←y<br />
→w = xy (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty(). Note that the small integer x and the exponent are not
converted to n-residue form.

### void nres_powmod (big x, big y, big w)

Modular exponentiation of an n-residue.

**Parameters:**

←x An n-reside number, the base<br />
←y A big number, the exponent<br />
→w = xy (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the first parameter to n-residue form.
Note that the exponent is not converted to n-residue form

> See also: **nres_powltr, nres_powmod2**

**Example:**
```
prepare_monty(n);
...
nres(x, y); // convert to n-residue form
nres_powmod(y, e, z);
redc(z, w); // convert back to normal form
```
### void nres_powmod2 (big x, big y, big a, big b, big w)

Calculates the product of two modular exponentiations involving n-residues.

**Parameters:**

←x An n-residue number<br />
←y A big integer<br />
←a An n-residue number<br />
←b A big integer<br />
→w = xy ab (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the appropriate parameters to n-residue
form. Note that the exponents are not converted to n-residue form

> See also: **nres_powltr, nres_powmod**

### void nres_powmodn (int n, big * x, big * y, big w)

Calculates the product of n modular exponentiations involving n-residues. Extra memory is allocated
internally by this function.

**Parameters:**

←n The number of n-residue numbers<br />
←x An array of n n-residue numbers<br />
←y An array of n big integers<br />
→w = x[0]y[0]x[1]y[1] · · · x[n − 1]y[n−1) (mod p), where p is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the appropriate parameters to n-residue
form. Note that the exponents are not converted to n-residue forms.

### void nres_premult (big x, int k, big w)

Multiplies an n-residue by a small integer.

**Parameters:**

←x<br />
←k<br />
→w = kx (mod n), where n is the current Montgomery modulus

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the first parameter to n-residue form.
Note that the small integer is not converted to n-residue form

> See also: **nres_modmult**

### BOOL nres_sqroot (big x, big w)

Calculates the square root of an n-residue mod a prime modulus.

**Parameters:**

←x<br />
→w =x (mod n), where n is the current Montgomery modulus

**Returns:**

TRUE if the square root exists, otherwise FALSE

**Precondition:**

Must be preceded by call to prepare_monty() and conversion of the first parameter to n-residue form.

### mr_small prepare_monty (big n)

Prepares a Montgomery modulus for use. Each call to this function replaces the previous modulus (if any).

**Parameters:**

←n A big number which is to be the Montgomery modulus

**Returns:**

None

**Precondition:**

The parameter n must be positive and odd. Allocated memory is freed when the current instance of
MIRACL is terminated by a call to mirexit().

### void redc (big x, big y)

Converts an n-residue back to normal form.

**Parameters:**

←x an n-residue<br />
→y the normal form of the n-residue x

**Precondition:**

Must be preceded by call to prepare_monty()

> See also: **nres**

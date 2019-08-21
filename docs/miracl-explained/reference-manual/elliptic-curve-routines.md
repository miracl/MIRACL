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
	* Elliptic Curve Routines
	* [Floating Slash Routines](floating-slash-routines.md)
	* [Structure Reference](structure-reference.md)


Elliptic Curve Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void ebrick2_end* (ebrick2 * B)

Cleans up after an application of the Comb for GF(2m) elliptic curves.

**Parameters:**

←→B A pointer to the current instance

## BOOL ebrick2_init (ebrick2 * B, big x, big y, big a2, big a6, int m, int a, int b, int c, int window, int nb)

Initialises an instance of the Comb method for GF(2m) elliptic curve multiplication with precomputation.
The field is defined with respect to the trinomial basis tm+ta+1 or the pentanomial basis tm+ta+tb+tc+1.
Internally memory is allocated for 2w elliptic curve points which will be precomputed and sotred. For
bigger w more space is required, but the exponentiation is quicker. Try w = 8.

**Parameters:**

←B A pointer to the current instance<br />
←x x coordinate of the fixed point<br />
←y y coordinate of the fixed point<br />
←a2 The a2 coefficient of the curve y2 + xy = x3 + a2x2 + a6<br />
←a6 the a6 coefficient of the curve y2 + xy = x3 + a2x2 + a6<br />
←m<br />
←a<br />
←b<br />
←c<br />
←window The size w of the window<br />
←nb The maximum number of bits to be used in the exponent

**Returns:**

TRUE if successful, otherwise FALSE

> If MR_STATIC is defined in mirdef.h, then the x and y parameters in this function are replaced by a single mr_small * pointer to a precomputed table. In this case the function returns a void.

## void ebrick_end* (ebrick * B)

Cleans up after an application of the Comb for GF(p) elliptic curves.

**Parameters:**

←→B A pointer to the current instance

## BOOL ebrick_init (ebrick * B, big x, big y, big a, big b, big n, int window, int nb)

Initialises an instance of the Comb method for GF(p) elliptic curve multiplication with precomputation.
Internally memory is allocated for 2w elliptic curve points which will be precomputed and stored. For
bigger w more space is required, but the exponentiation is quicker. Try w = 8.

**Parameters:**

→B A pointer to the current instance<br />
←x x coordinate of the fixed point<br />
←y y coordinate of the fixed point<br />
←a The a coefficient of the curve y2 = x3 + ax + b<br />
←b The b coefficient of the curve y2 = x3 + ax + b<br />
←n The modulus<br />
←window The size w of the window<br />
←nb The maximum number of bits to be used in the exponent

**Returns:**

TRUE if successful, otherwise FALSE

> If MR_STATIC is defined in mirdef.h, then the x and y parameters in this function are replaced by a single mr_small * pointer to a precomputed table. In this case the function returns a void.

## big ecurve2_add (epoint * p, epoint * pa)

Adds two points on a GF(2m) elliptic curve using the special rule for addition. Note that if pa = p, then a
different duplication rule is used. Addition is quicker if p is normalised.

**Parameters:**

←p<br />
←→pa = pa + p

**Returns:**

An ephemeral pointer to the sline slope if curve is super-singular

**Precondition:**

The input points must actually be on the current active curve.

## BOOL ecurve2_init (int m, int a, int b, int c, big a2, big a6, BOOL check, int type)

Initialises the internal parameters of the current active GF(2m) elliptic curve. The curve is assumed to be
of the form y2 + xy = x3 + Ax2 + B. The field is defined with respect to the trinomial basis tm + ta + 1
or the pentanomial basis tm+ta+tb+tc+1. This routine can be called subsequently with the parameters
of a different curve.

**Parameters:**

←m<br />
←a<br />
←b<br />
←c<br />
←a2 The A coefficient on the elliptic curve equation<br />
←a6 The B coefficient on the elliptic curve equation<br />
←check If TRUE a check is made that the specified basis is irreducible. If FALSE, this basis validity
check, which is time-consuming, is supressed<br />
←type Either MR_PROJECTIVE or MR_AFFINE, specifying whether projective or affine coordinates
should be used internally. Normally the former is faster

**Returns:**

TRUE if parameters make sense, otherwise FALSE

> Allocated memory will be freed when the current instance of MIRACL is terminated by a call to mirexit(). Only one elliptic curve, GF(p) or GF(2m) may be active within a single MIRACL instance.

## void ecurve2_mult (big e, epoint * pa, epoint * pt)

Multiplies a point on a GF(2m) elliptic curve by an integer. Uses the addition/subtraction method.

**Parameters:**

←e<br />
←pa<br />
→pt = e × pa

**Precondition:**

The point pa must be on the active curve.

## void ecurve2_mult2 (big e, epoint * p, big ea, epoint * pa, epoint * pt)

Calculates the point e × p + ea × pa on a GF(2m) elliptic curve. This is quicker than doing two separate
multiplications and an addition. Useful for certain cryptosystems.

**Parameters:**

←e<br />
←p<br />
←ea<br />
←pa<br />
→pt = e × p + ea × pa

**Precondition:**

The points p and pa must be on the active curve.

## void ecurve2_multi_add (int m, epoint ** x, epoint ** w)

Simultaneously adds pairs of points on the active GF(2m) curve. This is much quicker than adding them individually, but only when using affine coordinates.

**Parameters:**

←m<br />
←x<br />
→w w[i] = w[i] + x[i] for i = 0 to m - 1

> Only useful when using affine coordinates.

> See also: **ecurve2_init**

## void ecurve2_multn (int n, big * y, epoint ** x, epoint * w)

Calculates the point x[0]y[0] + x[1]y[1] + . . . + x[n − 1]y[n − 1]) on a GF(2m) elliptic curve, for n >= 2.

**Parameters:**

←n<br />
←y an array of n big numbers<br />
←x an array of n elliptic curve points<br />
→w = x[0]y[0] + x[1]y[1] + . . . + x[n − 1]y[n − 1])

**Precondition:**

The points must be on the active curve. The y[] values must all be positive. The underlying number
base must be a power of 2.

## big ecurve2_sub (epoint * p, epoint * pa)

Subtracts two points on a GF(2m) elliptic curve. Actually negates p and adds it to pa. Subtraction is quicker
if p is normalised.

**Parameters:**

←p<br />
←→ pa = pa − p

**Returns:**

An ephemeral pointer to the sline slope

**Precondition:**

The input points must actually be on the current active curve.

## big ecurve_add (epoint * p, epoint * pa)

Adds two points on a GF(p) elliptic curve using the special rule for addition. Note that if pa = p, then a
different duplication rule is used. Addition is quicker if p is normalised.

**Parameters:**

←p<br />
←→pa = pa + p

**Returns:**

An ephemeral pointer to the sline slope

**Precondition:**

The input points must actually be on the current active curve.

## void ecurve_init (big a, big b, big p, int type)

Initialises the internal parameters of the current active GF(p) elliptic curve. The curve is assumed to be
of the form y2 = x3 + Ax + B (mod p), the so-called Weierstrass model. This routine can be called
subsequently with the parameters of a different curve.

**Parameters:**

←a The A coefficient of the elliptic curve<br />
←b The B coefficient of the elliptic curve<br />
←p The modulus<br />
→type Either MR_PROJECTIVE or MR_AFFINE, specifying whether projective or affine coordinates
should be used internally. Normally the former is faster

> Allocated memory will be freed when the current instance of MIRACL is terminated by a call to mirexit(). Only one elliptic curve, GF(p) or GF(2m) may be active within a single MIRACL instance.

## void ecurve_mult (big e, epoint * pa, epoint * pt)

Multiplies a point on a GF(p) elliptic curve by an integer. Uses the addition/subtraction method.

**Parameters:**

←e<br />
←pa<br />
→pt = e × pa

**Precondition:**

The point pa must be on the active curve.

## void ecurve_mult2 (big e, epoint * p, big ea, epoint * pa, epoint * pt)

Calculates the point e × p + ea × pa on a GF(p) elliptic curve. This is quicker than doing two separate
multiplications and an addition. Useful for certain cryptosystems.

**Parameters:**

←e<br />
←p<br />
←ea<br />
←pa<br />
→pt = e × p + ea × pa

**Precondition:**

The points p and pa must be on the active curve.

## void ecurve_multi_add (int m, epoint ** x, epoint ** w)

Simultaneously adds pairs of points on the active GF(p) curve. This is much quicker than adding them
individually, but only when using affine coordinates.

**Parameters:**

←m<br />
←x<br />
→w w[i] = w[i] + x[i] for i = 0 to m - 1

> Only useful when using affine coordinates.

> See also: **ecurve_init, nres_multi_inverse**

## void ecurve_multn (int n, big * y, epoint ** x, epoint * w)

Calculates the point x[0]y[0] + x[1] * y[1] + . . . + x[n − 1]y[n − 1] on a GF(p) elliptic curve, for n >= 2.

**Parameters:**

←n<br />
←y An array of n big numbers<br />
←x An array of n elliptic curve points<br />
→w = x[0]y[0] + x[1]y[1] + . . . + x[n − 1]y[n − 1]

**Precondition:**

The points must be on the active curve. The y[] values must all be positive. The underlying number
base must be a power of 2.

## big ecurve_sub (epoint * p, epoint * pa)

Subtracts two points on a GF(p) elliptic curve. Actually negates p and adds it to pa. Subtraction is quicker
if p is normalised.

**Parameters:**

←p<br />
←→pa = pa − p

**Returns:**

An ephemeral pointer to the sline slope

**Precondition:**

The input points must actually be on the current active curve.

## BOOL epoint2_comp (epoint * a, epoint * b)

Compares two points on the current active GF(2m) elliptic curve.

**Parameters:**

←a<br />
←b

**Returns:**

TRUE if the points are the same, otherwise FALSE.

## void epoint2_copy* (epoint * a, epoint * b)

Copies one point to another on a GF(2m) elliptic curve.

**Parameters:**

←a<br />
←b = a

## int epoint2_get (epoint * p, big x, big y)

Normalises a point and extracts its (x,y) coordinates on the active GF(2m) elliptic curve.

**Parameters:**

←p<br />
→x<br />
→y

**Returns:**

The least significant bit of y. Note that it is possible to reconstruct a point from its x coordinate and
just the least significant bit of y. Often such a 'compressed' description of a point is useful

**Precondition:**

The point p must be on the active curve

> If x and y are not distinct variables on entry then only the value of x is returned.

**Example:**
```
i = epoint2_get(p, x, x); // extract x coordinate and lsb of y/x
```
## void epoint2_getxyz (epoint * p, big x, big y, big z)

Extracts the raw (x,y,z) coordinates of a point on the active GF(2m) elliptic curve.

**Parameters:**

←p<br />
→x<br />
→y<br />
→z

**Precondition:**

The point p must be on the active curve

> If any of x, y, z is NULL then that coordinate is not returned.

## BOOL epoint2_norm (epoint * p)

Normalises a point on the current active GF(2m) elliptic curve. This sets the z coordinate to 1. Point
addition is quicker when adding a normalised point. This function does nothing if affine coordinates are
being used (in which case there is no z coordinate).

**Parameters:**

←p A point on the current active elliptic curve

**Returns:**

TRUE if successful, otherwise FALSE.

## BOOL epoint2_set (big x, big y, int cb, epoint * p)

Sets a point on the current active GF(2m) elliptic curve (if possible).

**Parameters:**

←x The x coordinate of the point<br />
←y The y coordinate of the point

←cb If x and y are not distinct variables then x only is passed to the function, and cb is taken as the
least significant bit of y. In this case the full value of y is reconstructed internally. This is known
as 'point decompression' (and is a bit time-consuming, requiring the extraction of a modular
square root)<br />
→p = (x,y)

**Returns:**

TRUE if the point exists on the current active elliptic curve, otherwise FALSE

**Example:**
```
p = epoint_init();
epoint2_set(x, x, 1, p); // decompress p
```
## BOOL epoint_comp (epoint * a, epoint * b)

Compares two points on the current active GF(p) elliptic curve.

**Parameters:**

←a<br />
←b

**Returns:**

TRUE if the points are the same, otherwise FALSE.

## void epoint_copy* (epoint * a, epoint * b)

Copies one point to another on a GF(p) elliptic curve.

**Parameters:**

←a<br />
←b = a

## void epoint_free* (epoint * p)

Frees memory associated with a point on a GF(p) elliptic curve.

**Parameters:**

←p

## int epoint_get (epoint * p, big x, big y)

Normalises a point and extracts its (x,y) coordinates on the active GF(p) elliptic curve.

**Parameters:**

←p<br />
→x<br />
→y

**Returns:**

The least significant bit of y. Note that it is possible to reconstruct a point from its x coordinate and
just the least significant bit of y. Often such a 'compressed' description of a point is useful

**Precondition:**

The point p must be on the active curve

> If x and y are not distinct variables on entry then only the value of x is returned.

**Example:**
```
i = epoint_get(p, x, x); // extract x coordinate and lsb of y
```
## void epoint_getxyz (epoint * p, big x, big y, big z)

Extracts the raw (x,y,z) coordinates of a point on the active GF(p) elliptic curve.

**Parameters:**

←p<br />
→x<br />
→y<br />
→z

**Precondition:**

The point p must be on the active curve

> If any of x, y, z is NULL then that coordinate is not returned.

## epoint* epoint_init (void)

Assigns memory to a point on a GF(p) elliptic curve, and initialises it to the 'point at infinity'

**Returns:**

A pointer to an elliptic curve point (in fact a pointer to a structure allocated from the heap)

> It is the C programmer's responsibility to ensure that all elliptic curve points initialised by a call to this function are ultimately freed by a call to epoint_free(). If not a memory leak will result.

## epoint* epoint_init_mem (char * mem, int index)

Initialises memory for an elliptic curve point from a pre-allocated byte array mem. This array may be
created from the heap by a call to ecp_memalloc(), or in some other way. This is quicker than multiple
calls to epoint_init().

**Parameters:**

←mem<br />
←index An index into mem. Each index should be unique

**Returns:**

An initialised elliptic curve point

**Precondition:**

Sufficient memory must have been allocated and pointed to by mem.

## BOOL epoint_norm (epoint * p)

Normalises a point on the current active GF(p) elliptic curve. This sets the z coordinate to 1. Point addition is quicker when adding a normalised point. This function does nothing if affine coordinates are being used (in which case there is no z coordinate).

**Parameters:**

←p A point on the current active elliptic curve

**Returns:**

TRUE if successful, otherwise FALSE.

## BOOL epoint_set (big x, big y, int cb, epoint * p)

Sets a point on the current active GF(p) elliptic curve (if possible).

**Parameters:**

←x The x coordinate of the point<br />
←y The y coordinate of the point<br />
←cb If x and y are not distinct variables then x only is passed to the function, and cb is taken as the
least significant bit of y. In this case the full value of y is reconstructed internally. This is known
as 'point decompression' (and is a bit time-consuming, requiring the extraction of a modular
square root)<br />
→p = (x,y)

**Returns:**

TRUE if the point exists on the current active elliptic curve, otherwise FALSE

**Example:**
```
p = epoint_init();
epoint_set(x, x, 1, p); // decompress p
```
## BOOL epoint_x (big x)

Tests to see if the parameter x is a valid coordinate of a point on the curve. It is faster to test an x coordinate
first in this way, rather than trying to directly set it on the curve by calling epoint_set(), as it avoids an
expensive modular square root.

**Parameters:**

←x The integer coordinate x

**Returns:**

TRUE if x is the coordinate of a curve point, otherwise FALSE.

## int mul2_brick (ebrick2 * B, big e, big x, big y)

Carries out a GF(2m) elliptic curve multiplication using the precomputed values stored in the ebrick structure.

**Parameters:**

←B A pointer to the current instance<br />
←e A big exponent<br />
→x The x coordinate of e × G, where G is specified in the initial call to ebrick2_init()<br />
→y The y coordinate of e × G, where G is specified in the initial call to ebrick2_init()

**Returns:**

The least significant bit of y

> If x and y are not distinct variables, only x is returned.

**Precondition:**

Must be preceded by a call to ebrick2_init().

## int mul_brick (ebrick * B, big e, big x, big y)

Carries out a GF(p) elliptic curve multiplication using the precomputed values stored in the ebrick structure.

**Parameters:**

←B A pointer to the current instance<br />
←e A big exponent<br />
→x The x coordinate of eG (mod n), where G and n are specified in the initial call to ebrick_init()<br />
→y The y coordinate of eG (mod n), where G and n are specified in the initial call to ebrick_init()

**Returns:**

The least significant bit of y

> If x and y are not distinct variables, only x is returned.

**Precondition:**

Must be preceded by a call to ebrick_init().

## BOOL point_at_infinity* (epoint * p)

Tests if an elliptic curve point is the 'point at infinity'.

**Parameters:**

←p An elliptic curve point

**Returns:**

TRUE if p is the point at infinity, otherwise FALSE

**Precondition:**

The point must be initialised.    

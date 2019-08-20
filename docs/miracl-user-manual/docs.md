Elliptic Curve Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not visa-versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after the name indicates that the function does not take a *mip* parameter if MR_GENERIC_MT  is defined in *mirdef.h* .

## ebrick_init

Function:

    BOOL ebrick_init(binst,x,y,a,b,n,w,nb)

    ebrick *binst;

    big x,y;

    big a,b,n;

    int w,nb;

| Module | Description | Parameters | Return value |Restrictions|
|-----------|-----------------------|----------------------------------------------|------|------|
|mrebrick.c|Initialises an instance of the Comb method for GF(p) elliptic curve multiplication with precomputation. Internally memory is allocated for 2<sup>w</sup> elliptic curve points which will be precomputed and stored. For bigger w more space is required, but the exponentiation is quicker. Try w=8.|A pointer to the current instance binst, the fixed point G=(x,y) on the curve y<sup>2</sup> =x<sup>3</sup> + ax + b, the modulus n, and the maximum number of bits to be used in the exponent nb.|TRUE if all went well, FALSE if there was a problem.|Note: If MR_STATIC is defined in mirdef.h, then the x and y parameters in this function are replaced by a single mr_small * pointer to a precomputed table. In this case the function returns a void.|

## ebrick2_init

Function:

    BOOL ebrick2_init(binst,x,y,A,B,m,a,b,c,nb)

    ebrick2 *binst;

    big x,y;

    big A,B;

    int m,a,b,c,nb;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Initialises an instance of the Comb method for GF(2<sup>m</sup>) elliptic curve multiplication with precomputation. The field is defined with respect to the trinomial basis t<sup>m</sup>+t<sup>a</sup>+1 or the pentanomial basis t<sup>m</sup>+t<sup>a</sup>+t<sup>b</sup>+t<sup>c</sup>+1. Internally memory is allocated for 2<sup>w</sup> elliptic curve points which will be precomputed and stored. For bigger w more space is required, but the exponentiation is quicker. Try w=8.|A pointer to the current instance binst, the fixed point G=(x,y) on the curve   y<sup>2</sup> + xy = x<sup>3</sup> + Ax<sup>2</sup> + B, the field parameters m, a, b, c, and the maximum number of bits to be used in the exponent nb. Set b = 0 for a trinomial basis.|TRUE if all went well, FALSE if there was a problem.|Note: If MR_STATIC is defined in mirdef.h, then the x and y parameters in this function are replaced by a single mr_small * pointer to a precomputed table. In this case the function returns a void.|

## ebrick_end *

Function:

    void ebrick_end(binst)

    ebrick *binst

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
mrebrick.c|Cleans up after an application of the Comb for GF(p) elliptic curves|A pointer to the current instance|None   |None|  

## ebrick2_end *

Function:

    void ebrick2_end(binst)

    ebrick2 *binst

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Cleans up after an application of the Comb method for GF(2<sup>m</sup>) elliptic curves.|A pointer to the current instance|None   |None|  

## ecurve_add

Function:

    void ecurve_add(p,pa)

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Adds two points on a GF(p) elliptic curve using the special rule for addition. Note that if pa=p, then a different duplication rule is used. Addition is quicker if p is normalised.|Two points on the current active curve, pa and p. On exit pa=pa+p.|None|The input points must actually be on the current active curve.|

## ecurve2_add

Function:

    void ecurve2_add(p,pa)

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Adds two points on a GF(2<sup>m</sup>) elliptic curve using the special rule for addition. Note that if pa=p, then a different duplication rule is used. Addition is quicker if p is normalised.|Two points on the current active curve, pa and p. On exit pa=pa+p.|None|The input points must actually be on the current active curve.|

## ecurve_init

Function:

    void ecurve_init(A,B,p,type)

    big A,B,p;

    int type;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Initialises the internal parameters of the current active GF(p) elliptic curve. The curve is assumed to be of the form  y<sup>2</sup> =x<sup>3</sup> + Ax + B mod p, the so-called Weierstrass model. This routine can be called subsequently with the parameters of a different curve.|Three big numbers A, B and p. The type parameter must be either MR_PROJECTIVE or  MR_AFFINE, and specifies whether projective or affine co-ordinates should be used internally. Normally the former is faster.|None|Allocated memory will be freed when the current instance of MIRACL is terminated by a call to mirexit. However only one elliptic curve, GF(p) or GF(2<sup>m</sup>) may be active within a single MIRACL instance. In addition, a call to a function like powmod will overwrite the stored modulus. This can be restored by a repeat call to ecurve_init|

## ecurve2_init

Function:

    BOOL ecurve2_init(m,a,b,c,A,B,check,type)

    big A,B;

    int m,a,b,c,type;

    BOOL check;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Initialises the internal parameters of the current active elliptic curve. The curve is assumed to be of the form  y<sup>2</sup> + xy =x<sup>3</sup> + Ax<sup>2</sup> + B . The field is defined with respect to the trinomial basis t<sup>m</sup>+t<sup>a</sup>+1 or the pentanomial basis t<sup>m</sup>+t<sup>a</sup>+t<sup>b</sup>+t<sup>c</sup>+1. This routine can be called subsequently with the parameters of a different curve.|The fixed point G=(x,y) on the curve   y<sup>2</sup> + xy = x<sup>3</sup> + Ax<sup>2</sup> + B, the field parameters m, a, b, c. Set b = 0 for a trinomial basis. The type parameter must be either MR_PROJECTIVE or  MR_AFFINE, and specifies whether projective or affine co-ordinates should be used internally. Normally the former is faster. If check is TRUE a check is made that the specified basis is irreducible. If FALSE, this basis validity check, which is time-consuming, is suppressed.|TRUE if parameters make sense, otherwise FALSE.|Allocated memory will be freed when the current instance of MIRACL is terminated by a call to mirexit. However only one elliptic curve, GF(p) or GF(2<sup>m</sup>) may be active within a single MIRACL instance.|

## ecurve_mult

Function:

    void ecurve_mult(k,p,pa)

    big k;

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Multiplies a point on a GP(p) elliptic curve by an integer. Uses the addition/subtraction method.|A big number k, and two points  p and pa. On exit pa=k*p.|None|The point p must be on the active curve.|

## ecurve2_mult

Function:

    void ecurve2_mult(k,p,pa)

    big k;

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Multiplies a point on a GF(2<sup>m</sup>)  elliptic curve by an integer. Uses the addition/subtraction method.|A big number k, and two points  p and pa. On exit pa=k*p.|None|The point p must be on the active curve.|

## ecurve_mult2

Function:

    void ecurve_mult2(k1,p1,k2,p2,pa)

    big k1,k2;

    epoint *p1,*p2,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Calculates the point k1.p1+k2.p2 on a GF(p) elliptic curve. This is quicker than doing two separate multiplications and an addition. Useful for certain cryptosystems. (See ecsver.c for example)|Two big integers k1 and k2, and three points p1, p2 and pa. On exit pa = k1.p1+k2.p2|None|The points p1 and p2 must be on the active curve.|

## ecurve2_mult2

Function:

    void ecurve2_mult2(k1,p1,k2,p2,pa)

    big k1,k2;

    epoint *p1,*p2,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Calculates the point k1.p1+k2.p2 on a GF(2<sup>m</sup>) elliptic curve. This is quicker than doing two separate multiplications and an addition. Useful for certain cryptosystems. (See ecsver2.c for example)|Two big integers k1 and k2, and three points p1, p2 and pa. On exit pa = k1.p1+k2.p2|None|The points p1 and p2 must be on the active curve.|

## ecurve_multi_add

Function:

    void ecurve_multi_add(m,x,w)

    int m;

    epoint x,w;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Simultaneously adds pairs of points on the active GF(p) curve. This is much quicker than adding them individually, but only when using Affine co-ordinates.|An integer m and two arrays of points w and x. On exit w[i]=w[i]+x[i] for i =0 to m-1|None|Only useful when using Affine co-ordinates. See also: ecurve_init and nres_multi_inverse, which is used internally.|

## ecurve2_multi_add

Function:

    void ecurve2_multi_add(m,x,w)

    int m;

    epoint x,w;

| Module | Description | Parameters | Return value | Restrictions |See also|
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Simultaneously adds pairs of points on the active GF(2<sup>m</sup>) curve. This is much quicker than adding them individually, but only when using Affine co-ordinates.|An integer m and two arrays of points w and x. On exit w[i]=w[i]+x[i] for i =0 to m-1|None|Only useful when using Affine co-ordinates.|See also: ecurve2_init|

## ecurve_multn

Function:

    void ecurve_multn(n,k,p,pa)

    int n;

    big *k;

    epoint p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Calculates the point k[0].p[0] + k[1].p[1] + … + k[n-1].p[n-1] on a GF(p) elliptic curve, for n>2.| An integer n, an array of n big numbers k[], and an array of n points. The result is returned in pa.|None|The points must be on the active curve. The k[] values must all be positive. The underlying number base must be a power of 2.|

## ecurve2_multn

Function:

    void ecurve2_multn(n,k,p,pa)

    int n;

    big *k;

    epoint p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2<sup>m</sup>.c|Calculates the point k[0].p[0] + k[1].p[1] + … + k[n-1].p[n-1] on a GF(2<sup>m</sup>) elliptic curve, for n>2.| An integer n, an array of n big numbers k[], and an array of n points. The result is returned in pa.|None|The points must be on the active curve. The k[] values must all be positive. The underlying number base must be a power of 2.|

## ecurve_sub

Function:

    void ecurve_sub(p,pa)

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Subtracts two points on a GF(p) elliptic curve. Actually negates p and adds it to pa. Subtraction is quicker if p is normalised.|Two points on the current active curve, pa and p. On exit pa = pa-p.|None|The input points must actually be on the current active curve.|

## ecurve2_sub

Function:

    void ecurve2_sub(p,pa)

    epoint *p,*pa;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Subtracts two points on a GF(2<sup>m</sup>) elliptic curve. Actually negates p and adds it to pa. Subtraction is quicker if p is normalised.|Two points on the current active curve, pa and p. On exit pa = pa-p.|None| The input points must actually be on the current active curve.

## epoint_comp

Function:

    BOOL epoint_comp(p1,p2) epoint *p1,*p2;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Compares two points on the current active GF(p) elliptic curve.|Two points p1 and p2.|TRUE if the points are the same, otherwise FALSE. |None|

## epoint2_comp

Function: BOOL epoint2_comp(p1,p2)

    epoint *p1,*p2;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Compares two points on the current active GF(2<sup>m</sup>) elliptic curve.|Two points p1 and p2.|TRUE if the points are the same, otherwise FALSE. |None|

## epoint_copy *

Function: void epoint_copy(p1,p2)

    epoint *p1,*p2;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Copies one point to another on a GF(p) elliptic curve.|Two points p1 and p2. On exit p2=p1.|None   |None|

## epoint2_copy *

Function:

    void epoint2_copy(p1,p2)

    epoint *p1,*p2;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Copies one point to another on a GF(2<sup>m</sup>) elliptic curve.|Two points p1 and p2. On exit p2=p1.|None   |None|

## epoint_free *

Function:

    void epoint_free(p) epoint *p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcore.c|Frees memory associated with a point on a GF(p) elliptic curve.|A point p.|None   |None|

## epoint_get

Function:

    int epoint_get(p,x,y)

    epoint *p;

    big x,y;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Normalises a point and extracts its (x,y) co-ordinates on the active GF(p) elliptic curve.|A point p, and two big integers x and y. If x and y are not distinct variables on entry then only the value of x is returned.|The least significant bit of y. Note that it is possible to reconstruct a point from its x co-ordinate and just the least significant bit of y. Often such a "compressed" description of a point is useful. |The point p must be on the active curve.

Example:         

    i=epoint_get(p,x,x);|  /* extract x co-ordinate and lsb of y */

## epoint_getxyz

Function:

    void epoint_getxyz(p,x,y,z)

    epoint *p;

    big x,y,z;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Extracts the raw (x,y,z) co-ordinates of a point on the active GF(p) elliptic curve.|A point p, and three big integers x, y and z. If any of these is NULL that coordinate is not returned.|None| The point p must be on the active curve.

## epoint2_get

Function: int epoint2_get(p,x,y)

    epoint *p;

    big x,y;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Normalises a point and extracts its (x,y) co-ordinates on the active GF(2<sup>m</sup>) elliptic curve.|A point p, and two big integers x and y. If x and y are not distinct variables on entry then only the value of x is returned.|The least significant bit of y/x. Note that it is possible to reconstruct a point from its x co-ordinate and just the least significant bit of y/x. Often such a "compressed" description of a point is useful.| The point p must be on the active curve.

Example:       

    i=epoint_get(p,x,x);|   /* extract x co-ordinate and lsb of y/x */

## epoint2_getxyz

Function:

    void epoint2_getxyz(p,x,y,z)

    epoint *p;

    big x,y,z;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Extracts the raw (x,y,z) co-ordinates of a point on the active GF(2<sup>m</sup>) elliptic curve.|A point p, and three big integers x, y and z. If any of these is NULL that coordinate is not returned.|None| The point p must be on the active curve.

## epoint_init

Function: epoint* epoint_init()

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcore.c|Assigns memory to a point on a GF(p) elliptic curve, and initialises it to the "point at infinity".|None|A point p (in fact a pointer to a structure allocated from the heap).| It is the C programmers responsibility to ensure that all elliptic curve points initialised by a call to this function, are ultimately freed by a call to epoint_free. If not a memory leak will result.

## epoint_init_mem

Function:

    epoint* epoint_init_mem(mem,index)

    char *mem;

    int index;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcore.c|Initialises memory for an elliptic curve point from a pre-allocated byte array mem. This array may be created from the heap by a call to ecp_memalloc, or in some other way. This is quicker than multiple calls to epoint_init|A pointer to the pre-allocated array mem, and an index into that array. Each index should be unique.|An initialised elliptic curve point.| Sufficient memory must have been allocated and pointed to by mem.

## epoint_norm

Function:

    BOOL epoint_norm(p)

    epoint *p;

| Module | Description | Parameters | Return value |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Normalises a point on the current active GF(p) elliptic curve. This sets the z coordinate to 1. Point addition is quicker when adding a normalised point. This function does nothing if affine coordinates are being used (in which case there is no z co-ordinate)|A point on the current active elliptic curve.|TRUE if successful.|

## epoint2_norm

Function:

    BOOL epoint2_norm(p)

    epoint *p;

| Module | Description | Parameters | Return value |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Normalises a point on the current active GF(2<sup>m</sup>) elliptic curve. This sets the z coordinate to 1. Point addition is quicker when adding a normalised point. This function does nothing if affine coordinates are being used (in which case there is no z co-ordinate)|A point on the current active elliptic curve.|TRUE if successful.|

## epoint_set

Function:

    BOOL epoint_set(x,y,lsb,p)

    big x,y;

    int lsb;

    epoint *p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c|Sets a point on the current active GF(p) elliptic curve (if possible).|The integer co-ordinates x and y of the point p. If  x and y are not distinct variables then x only is passed to the function, and lsb is taken as the least significant bit of y. In this case the full value of y is reconstructed internally. This is known as "point decompression" (and is a bit time-consuming, requiring the extraction of a modular square root). On exit p=(x,y).|TRUE if the point exists on the current active point, otherwise FALSE. |None|

Example:

    p=epoint_init();

    epoint_set(x,x,1,p); /* decompress p */

## epoint2_set

Function:

    BOOL epoint2_set(x,y,lsb,p)

    big x,y;

    int lsb;

    epoint *p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Sets a point on the current active GF(2<sup>m</sup>) elliptic curve (if possible).|The integer co-ordinates x and y of the point p. If  x and y are not distinct variables then x only is passed to the function, and lsb is taken as the least significant bit of y/x. In this case the full value of y is reconstructed internally. This is known as "point decompression" (and is a bit time-consuming, requiring the extraction of a field square root). On exit p=(x,y).|TRUE if the point exists on the current active point, otherwise FALSE. |None|

Example:         

    p=epoint_init();

    epoint2_set(x,x,1,p); /* decompress p */

## epoint_x

Function:

    BOOL epoint_x(x)

    big x;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcurve.c| Tests to see if the parameter x is a valid co-ordinate of a point on the curve. It is faster to test an x co-ordinate first in this way, rather than trying to directly set it on the curve by calling epoint_set, as it avoids an expensive modular square root.|The integer coordinate x.|TRUE if x is the coordinate of a curve point, otherwise FALSE |None|

## mul_brick

Function:

    int mul_brick(binst,e,x,y)

    ebrick *binst;

    big e,x,y;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrebrick.c|Carries out a GF(p) elliptic curve multiplication using the precomputed values stored in the ebrick structure.|A pointer to the current instance, a big exponent e and a big number w. On exit (x,y) = e.G mod n, where G and n are specified in the initial call to ebrick_init. If x and y are not distinct variables, only x is returned.|The least significant bit of y.| Must be preceded by a call to ebrick_init.

## mul2_brick

Function:

    int mul2_brick(binst,e,x,y)

    ebrick2 *binst;

    big e,x,y;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrec2m.c|Carries out a GF(2<sup>m</sup>)  elliptic curve multiplication using the precomputed values stored in the ebrick2 structure.|A pointer to the current instance, a big exponent e and a big number w. On exit (x,y) = e.G, where G is specified in the initial call to ebrick2_init. If x and y are not distinct variables, only x is returned.|The least significant bit of y/x.| Must be preceded by a call to ebrick2_init.

## point_at_infinity *

Function:

    BOOL point_at_infinity(p)

    epoint *p;

| Module | Description | Parameters | Return value | Restrictions |
|-----------|-----------------------|----------------------------------------------|------|------|
|mrcore.c|Tests if an elliptic curve point is the "point at infinity".|An elliptic curve point p.|TRUE if p is the point-at-infinity, otherwise FALSE.| The point must be initialised.

* [What Is Miracl](../README.md)
* [Security Advisory](../security-advisory.md)
* [Benchmarks](../benchmarks.md)
* [Miracl Standard Curves](../miracl-standard-curves.md)
* [IEEE 1363](../ieee-1363.md)
* [Elliptic Curves](../elliptic-curves.md)
* [Licensing](../licensing.md)
* Reference Manual
	* [Low Level Routines](low-level-routines.md)
	* Advanced Arithmetic Routines
	* [Montgomery Arithmetic Routines](montgomery-arithmetic-routines.md)
	* [ZZn2 Arithmetic Routines](zzn2-arithmetic-routines.md)
	* [Encryption Routines](encryption-routines.md)
	* [Elliptic Curve Routines](elliptic-curve-routines.md)
	* [Floating Slash Routines](floating-slash-routines.md)
	* [Structure Reference](structure-reference.md)


Advanced Arithmetic Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void bigdig (int n, int b, big x)

Generates a big random number of given length. Uses the built-in simple random number generator initialised
by irand().

**Parameters:**

←n<br />
←b<br />
→x A big random number n digits long to base b

**Precondition:**

The base b must be printable, that is 2 <= b <= 256

**Example:**
```
// This generates a 100 decimal digit random number
bigdig(100, 10, x);
```
## void bigrand (big w, big x)

Generates a big random number. Uses the built-in simple random number generator initialised by irand().

**Parameters:**

←w<br />
→x A big random number in the range 0 <= x < w

## void brick_end* (brick * b)

Cleans up after an application of the Comb method.

**Parameters:**

←b A pointer to the current instance.

## BOOL brick_init (brick * b, big g, big n, int window, int nb)

Initialises an instance of the Comb method for modular exponentiation with precomputation. Internally
memory is allocated for 2w big numbers which will be precomputed and stored. For bigger w more space
is required, but the exponentiation is quicker. Try w = 8.

**Parameters:**

←→b A pointer to the current instance<br />
←g The fixed generator<br />
←n The modulus<br />
←window The window size w<br />
←nb The maximum number of bits to be used in the exponent

**Returns:**

TRUE if successful, otherwise FALSE

> If MR_STATIC is defined in mirdef.h, then the g parameter in this function is replaced by an mr_small pointer to a precomputed table. In this case the function returns a void.

## void crt (big_chinese * c, big * u, big x)

Applies the Chinese Remainder Theorem.

**Parameters:**

←c A pointer to the current instance<br />
←u An array of big remainders<br />
→x The big number which yields the given remainders u when it is divided by the big moduli specified
in a prior call to crt_init()

**Precondition:**

The routine crt_init() must be called first.

## void crt_end* (big_chinese * c)

Cleans up after an application of the Chinese Remainder Theorem.

**Parameters:**

←c A pointer to the current instance.

## BOOL crt_init (big_chinese * c, int r, big * moduli)

Initialises an instance of the Chinese Remainder Theorem. Some internal workspace is allocated.

**Parameters:**

→c A pointer to the current instance<br />
←r The number of co-prime moduli<br />
←moduli An array of at least two big moduli

**Returns:**

TRUE if successful, otherwise FALSE.

## int egcd (big x, big y, big z)

Calculates the Greatest Common Divisor of two big numbers.

**Parameters:**

←x<br />
←y<br />
←z = gcd(x,y)

**Returns:**

GCD as integer, if possible, otherwise MR_TOOBIG.

## void expb2 (int n, big x)

Calculates 2 to the power of an integer as a big.

**Parameters:**

←n<br />
→x = 2n

**Example:**
```
// This calculates and prints out the largest known prime number
// (on a true 32-bit computer with lots of memory!)
expb2(1398269, x);
decr(x, 1, x);
mip->IOBASE = 10;
cotnum(x, stdout);
```
### void expint (int b, int n, big x)

Calculates an integer to the power of an integer as a big.

**Parameters:**

←b<br />
←n<br />
→x = bn

### void fft_mult (big x, big y, big z)

Multiplies two big numbers, using the Fast Fourier Method. See [Pollard71].

**Parameters:**

←x<br />
←y<br />
→z = xy

> Should only be used on a 32-bit computer when x and y are ver large, at least 1000 decimal digits.

### void gprime (int maxp)

Generates all prime numbers up to a certain limit into the instance array miracl::PRIMES, terminated by
zero. This array is used internally by the routines isprime() and nxprime().

**Parameters:**

←maxp A positive integer indicating the maximum prime number to be generated. If maxp = 0 the
miracl::PRIMES array is deleted.

### int hamming (big x)

Calculates the hamming weight of a big number (in fact the number of 1's in its binary representation).

**Parameters:**

←x

**Returns:**

Hamming weight of x.

### mr_small invers* (mr_small x, mr_small y)

Calculates the inverse of an integer modulus a co-prime integer.

**Parameters:**

←x<br />
←y

**Returns:**

x−1 (mod y)

> Result unpredictable if x and y not co-prime.

### BOOL isprime (big x)

Tests whether or not a big number is prime using a probabilistic primality test. The number is assumed
to be prime if it passes this test miracl::NTRY times, where miracl::NTRY is an instance variable with a
default initialisation in routine mirsys().

**Parameters:**

←x

**Returns:**

TRUE if x is (almost certainly) prime, otherwise FALSE

> This routine first test divides x by the list of small primes stored in the instance array miracl::PRIMES.
> The testing of larger primes will be significantly faster in many cases if this list is increased. See
> **gprime()**. By default only the small primes less than 1000 are used.

### int jac (mr_small x, mr_small n)

Calculates the value of the Jacobi symbol. See [Reisel].

**Parameters:**

←x<br />
←n

**Returns:**

The value of (x | n) as +1 or -1, or 0 if symbol undefined

> See also: **jack**

### int jack (big U, big V)

Calculates the value of the Jacobi symbol. See [Reisel].

**Parameters:**

←U<br />
←V

**Returns:**

The value of (U | V) as +1 or -1, or 0 if symbol undefined

> See also: **jac**

### int logb2 (big x)

Calculates the approximate integer log to the base 2 of a big number (in fact the number of bits in it).

**Parameters:**

←x

**Returns:**

Number of bits in x

### void lucas (big p, big r, big n, big vp, big v)

Performs Lucas modular exponentiation. Uses Montgomery arithmetic internally. This function can be
speeded up further for particular moduli, by invoking special assembly language routines to implement
Montgomery arithmetic. See powmod().

**Parameters:**

←p The base<br />
←r The exponent<br />
←n The modulus<br />
→vp = Vr−1(p) (mod n)<br />
→v = Vr(p) (mod n)

> Only v is returned if v and vp are not distinct. The "sister" Lucas function Ur(p) can, if required, be calculated as Ur(p) * [pVr(p) − 2Vr−1(p)]/(p2 − 4) (mod n)

**Precondition:**

The value of n must be odd.

### BOOL multi_inverse (int m, big * x, big n, big * w)

Finds the modular inverses of many numbers simultaneously, exploiting Montgomery's observation that
x−1 = y(xy)−1, y−1 = x(xy)−1. This will be quicker, as modular inverses are slow to calculate, and this
way only one is required.

**Parameters:**

←m The number of inverses required<br />
←x An array of m numbers whose inverses are required<br />
←n The modulus<br />
→w The resulting array of inverses

**Returns:**

TRUE if successful, otherwise FALSE

**Precondition:**

The parameters x and w must be distinct.

### BOOL nroot (big x, int n, big w)

Extracts lower approximation to a root of a big number.

**Parameters:**

←x A big number<br />
←n A positive integer<br />
→w = [nx]

**Returns:**

TRUE if the root is exact, otherwise FALSE

**Precondition:**

The value of n must be positive. If x is negative, then n must be odd

> See also: **sqroot, nres_sqroot**

### BOOL nxprime (big w, big x)

Finds next prime number.

**Parameters:**

←w<br />
←x The next prime number greater than w

**Returns:**

TRUE if successful, otherwise FALSE

> See also: **nxsafeprime**

### BOOL nxsafeprime (int type, int subset, big w, big p)

Finds next safe prime number greater than w. A safe prime number p is defined here to be one for which
q = (p − 1)/2 (type=0) or q = (p + 1)/2 (type=1) is also prime.

**Parameters:**

←type The type of safe prime as above<br />
←subset If subset = 1, then the search is restricted so that the value of the prime q is congruent to 1
mod 4. If subset = 3, then the search is restricted so that the value of q is congruent to 3 mod 4.
If subset = 0 then there is no condition on q: it can be either 1 or 3 mod 4<br />
←w<br />
→p

**Returns:**

TRUE if successful, otherwise FALSE

> See also: **nxprime**

### void pow_brick (brick * b, big e, big w)

Carries out a modular exponentiation, using the precomputed values stored in the brick structure.

**Parameters:**

←b A pointer to the current instance<br />
←e A big exponent<br />
→w = ge (mod n), where g and n are specified in the initial call to brick_init()

**Precondition:**

Must be preceded by a call to brick_init().

### void power (big x, long n, big z, big w)

Raises a big number to an integer power.

**Parameters:**

←x A big number<br />
←n A positive integer<br />
←z A big number<br />
→w = xn (mod z)

**Precondition:**

The value of n must be positive.

### int powltr (int x, big y, big n, big w)

Raises an int to the power of a big number modulus another big number. Uses Left-to-Right binary
method, and will be somewhat faster than powmod() for small x. Uses Montgomery arithmetic internally
if the modulus n is odd.

**Parameters:**

←x<br />
←y<br />
←n<br />
→w = xy (mod n)

**Returns:**

The result expressed as an integer, if possible. Otherwise the value MR_TOOBIG

**Precondition:**

The value of y must be positive. The parameters x and n must be distinct.

### void powmod (big x, big y, big n, big w)

Raises a big number to a big power modulus another big. Uses a sophisticated 5-bit sliding window technique,
which is close to optimal for popular modulus sizes (such as 512 or 1024 bits). Uses Montgomery
arithmetic internally if the modulus n is odd.

This function can be speeded up further for particular moduli, by invoking special assembly language
routines (ir your compiler allows it). A KCM Modular Multiplier will be automatically invoked if MR_-
KCM has been defined in mirdef.h and has been set to an appropriate size. Alternatively a Comba modular
multiplier will be used if MR_COMBA is so defined, and the modulus is of the specified size. Experimental
coprocessor code will be called if MR_PENTIUM is defined. Only one of these conditionals should be
defined.

**Parameters:**

←x<br />
←y<br />
←n<br />
→w = xy (mod n)

**Precondition:**

The value of y must be positive. The parameters x and n must be distinct.

### void powmod2 (big x, big y, big a, big b, big n, big w)

Calculates the product of two modular exponentiations. This is quicker than doing two separate exponentiations,
and is useful for certain cryptographic protocols. Uses 2-bit sliding window.

**Parameters:**

←x<br />
←y<br />
←a<br />
←b<br />
←n<br />
→w = xy ab (mod n)

**Precondition:**

The values of y and b must be positive. The parameters n and w must be distinct. The modulus n must
be odd.

### void powmodn (int n, big * x, big * y, big p, big w)

Calculates the product of n modular exponentiations. This is quicker than doing n separate exponentiations,
and is useful for certain cryptographic protocols. Extra memory is allocated internally for this function.

**Parameters:**

←n<br />
←x<br />
←y<br />
←p<br />
→w = x[0]y[0]x[1]y[1] · · · x[n − 1]y[n−1) (mod p)

**Precondition:**

The values of y[ ] must be positive. The parameters p and w must be distinct. The modulus p must be
odd. The underlying number base must be a power of 2.

### void scrt (small_chinese * c, mr_utype * u, big x)

Applies Chinese Remainder Theorem (for small prime moduli).

**Parameters:**

←c A pointer to the current instance of the Chinese Remainder Theorem<br />
←u An array of remainders<br />
→x The big number which yields the given integer remainders u[ ] when it is divided by the integer
moduli specified in a prior call to scrt_init()

**Precondition:**

The routine scrt_init() must be called first.

### void scrt_end* (small_chinese * c)

Cleans up after an application of the Chinese Remainder Theorem.

**Parameters:**

←c A pointer to the current instance of the Chinese Remainder Theorem.

### BOOL scrt_init (small_chinese * c, int r, mr_utype * moduli)

Initialises an instance of the Chinese Remainder Theorem. Some internal workspace is allocated.

**Parameters:**

→c A pointer to the current instance<br />
←r The number of co-prime moduli<br />
←moduli An array of at least two integer moduli

**Returns:**

TRUE if successful, otherwise FALSE.

### void sftbit (big x, int n, big z)

Shifts a big integer left or right by a number of bits.

**Parameters:**

←x<br />
←n If positive shifts to the left, if negative shifts to the right<br />
→z = x shifted by n bits

### mr_small smul* (mr_small x, mr_small y, mr_small n)

Multiplies two integers mod a third.

**Parameters:**

←x<br />
←y<br />
←n

**Returns:**

xy (mod n)

### mr_small spmd* (mr_small x, mr_small n, mr_small m)

Raises an integer to an integer power modulo a third.

**Parameters:**

←x<br />
←n<br />
←m

**Returns:**

xn (mod m)

### mr_small sqrmp* (mr_small x, mr_small m)

Calculates the square root of an integer modulo an integer prime number.

**Parameters:**

←x<br />
←m A prime number

**Returns:**

x (mod m), or 0 if root does not exist

**Precondition:**

p must be prime, otherwise the result is unpredictable

> See also: **sqroot**

### BOOL sqroot (big x, big p, big w)

Calculates the square root of a big integer mod a big integer prime.

**Parameters:**

←x<br />
←p<br />
→w =x (mod p) if the square root exists, otherwise w = 0. Note that the "other" square root
may be found by subtracting w from p

**Returns:**

TRUE if the square root exists, FALSE otherwise

**Precondition:**

The number p must be prime

> This routine is particularly efficient if p = 3 (mod 4).

### int trial_division (big x, big y)

Dual purpose trial division routine. If x and y are the same big variable then trial division by the small
prime numbers in the instance array miracl::PRIMES is attempted to determine the primality status of the
big number. If x and y are distinct then, after trial division, the unfactored part of x is returned in y.

**Parameters:**

←x<br />
←→y

**Returns:**

If x and y are the same, then a return value of 0 means that the big number is definitely not prime, a
return value of 1 means that it definitely is prime, while a return value of 2 means that it is possibly
prime (and that perhaps further testing should be carried out). If x and y are distinct, then a return value
of 1 means that x is smooth, that it is completely factored by trial division (and y is the largest prime
factor). A return value of 2 means that the unfactored part y is possibly prime.

### int xgcd (big x, big y, big xd, big yd, big z)

Calculates extended Greatest Common Divisor of two big numbers. Can be used to calculate modular
inverses. Note that this routine is much slower than a mad() operation on numbers of similar size.

**Parameters:**

←x<br />
→y<br />
→xd<br />
→yd<br />
→z = gcd(x, y) = (x * xd) + (y * yd)

**Returns:**

GCD as integer, if possible, otherwise MR_TOOBIG

**Precondition:**

If xd and yd are not distinct, only xd is returned. The GCD is only returned if z distinct from both xd
and yd

**Example:**
```
xgcd(x, p, x, x, x,); // x = 1/x mod p (p is prime)
```

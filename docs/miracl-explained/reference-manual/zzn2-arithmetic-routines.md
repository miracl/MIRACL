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
	* ZZn2 Arithmetic Routines
	* [Encryption Routines](encryption-routines.md)
	* [Elliptic Curve Routines](elliptic-curve-routines.md)
	* [Floating Slash Routines](floating-slash-routines.md)
	* [Structure Reference](structure-reference.md)


ZZn2 Arithmetic Routines
---

In these routines a big parameter can also be used wherever a flash is specified, but not vice versa. Further information may be gleaned from the (lightly) commented source code. An asterisk after
the name indicates that the function does not take a mip parameter if MR_GENERIC_MT is defined in
mirdef.h.

## void zzn2_add (zzn2 * x, zzn2 * y, zzn2 * w)

Adds two zzn2 variables.

**Parameters:**

←x<br />
←y<br />
→w = x + y

## BOOL zzn2_compare* (zzn2 * x, zzn2 * y)

Compares two zzn2 variables for equality.

**Parameters:**

←x<br />
←y

**Returns:**

TRUE if x = y, otherwise FALSE.

## void zzn2_conj (zzn2 *x, zzn2 *w)

Finds the conjugate of a zzn2.

**Parameters:**

←x<br />
→w If x = a + bi, then w = a - bi

## void zzn2_copy* (zzn2 * x, zzn2 * w)

Copies one zzn2 to another.

**Parameters:**

←x<br />
→w = x

## void zzn2_from_big (big x, zzn2 * w)

Creates a zzn2 from a big integer. This is converted internally into n-residue format.

**Parameters:**

←x<br />
→w = x

## void zzn2_from_bigs (big x, big y, zzn2 * w)

Creates a zzn2 from two big integers. These are converted internally into n-residue format.

**Parameters:**

←x<br />
←y<br />
→w = x + yi

## void zzn2_from_int (int i, zzn2 * w)

Converts an integer to zzn2 format.

**Parameters:**

←i<br />
→w = i

> See also: **zzn2_from_ints**

## void zzn2_from_ints (int i, int j, zzn2 * w)

Creates a zzn2 from two integers.

**Parameters:**

←i<br />
←j<br />
→w = i + j i

> See also: **zzn2_from_int**

## void zzn2_from_zzn (big x, zzn2 * w)

Creates a zzn2 from a big already in n-residue format.

**Parameters:**

←x<br />
→w = x

### void zzn2_from_zzns (big x, big y, zzn2 * w)

Creates a zzn2 from two bigs already in n-residue format.

**Parameters:**

←x<br />
←y<br />
→w = x + y i

> See also: **zzn2_from_zzn**

### void zzn2_imul (zzn2 * x, int y, zzn2 * w)

Multiplies a zzn2 variable by an integer.

**Parameters:**

←x<br />
←y<br />
→w = xy

### void zzn2_inv (zzn2 * w)

In-place inversion of a zzn2 variable.

**Parameters:**

←→w = 1 / w

### BOOL zzn2_isunity (zzn2 * x)

Tests a zzn2 value for equality to one.

**Parameters:**

←x

**Returns:**

TRUE if x is one, otherwise FALSE.

### BOOL zzn2_iszero* (zzn2 * x)

Tests a zzn2 value for equality to zero.

**Parameters:**

←x

**Returns:**

TRUE if x is zero, otherwise FALSE.

### void zzn2_mul (zzn2 * x, zzn2 * y, zzn2 * w)

Multiplies two zzn2 variables. If x and y are the same variable, a faster squaring method is used.

**Parameters:**

←x<br />
←y<br />
→w = xy

### void zzn2_negate (zzn2 * x, zzn2 * w)

Negates a zzn2

**Parameters:**

←x<br />
→w = -x

### void zzn2_sadd (zzn2 * x, big y, zzn2 * w)

Adds a big in n-residue format to a zzn2.

**Parameters:**

←x<br />
←y<br />
→w = x + y

### void zzn2_smul (zzn2 * x, big y, zzn2 * w)

Multiplies a zzn2 variable by a big in n-residue.

**Parameters:**

←x<br />
←y<br />
→w = xy

### void zzn2_ssub (zzn2 * x, big y, zzn2 * w)

Subtracts a big in n-residue format from a zzn2.

**Parameters:**

←x<br />
←y<br />
→w = x - y

### void zzn2_sub (zzn2 * x, zzn2 * y, zzn2 * w)

Subtracts two zzn2 variables.

**Parameters:**

←x<br />
←y<br />
→w = x - y

### void zzn2_timesi (zzn2 * u)

In-place multiplication of a zzn2 by i, the imaginary square root of the quadratic non-residue.

**Parameters:**

←→u If u = a + bi then on exit u = i2b + ai

### void zzn2_zero* (zzn2 * w)

Sets a zzn2 variable to zero.

**Parameters:**

→w = 0

## Encryption Routines <a id="encryption"></a>

**Functions**
- mr_unsign32 aes_decrypt* (aes *a, char *buff)
- mr_unsign32 aes_encrypt* (aes *a, char *buff)
- void aes_end* (aes *a)
- void aes_getreg* (aes *a, char *ir)
- BOOL aes_init* (aes *a, int mode, int nk, char *key, char *iv)
- void aes_reset* (aes *a, int mode, char *iv)
- void shs256_hash* (sha256 *sh, char hash[32])
- void shs256_init* (sha256 *sh)
- void shs256_process* (sha256 *sh, int byte)
- void shs384_hash* (sha384 *sh, char hash[48])
- void shs384_init* (sha384 *sh)
- void shs384_process* (sha384 *sh, int byte)
- void shs512_hash* (sha512 *sh, char hash[64])
- void shs512_init* (sha512 *sh)
- void shs512_process* (sha512 *sh, int byte)
- void shs_hash* (sha *sh, char hash[20])
- void shs_init* (sha *sh)
- void shs_process* (sha *sh, int byte)
- void strong_bigdig (csprng *rng, int n, int b, big x)
- void strong_bigrand (csprng *rng, big w, big x)
- void strong_init* (csprng *rng, int rawlen, char *raw, mr_unsign32 tod)
- void strong_kill* (csprng *rng)
- int strong_rng* (csprng *rng)

## mr_unsign32 aes_decrypt* (aes * a, char * buff)

Decrypts a 16 or n byte input buffer in situ. If the mode of operation is as a block cipher (MR_ECB or
MR_CBC) then 16 bytes will be decrypted. If the mode of operation is as a stream cipher (MR_CFBn,
MR_OFBn or MR_PCFBn) then n bytes will be decrypted.

**Parameters:**

←a Pointer to an initialised instance of an aes structured defined in miracl.h<br />
←→buff Pointer to the buffer of bytes to be decrypted

**Returns:**

If MR_CFBn and MR_PCFBn modes then n byte(s) that were shifted off the end of the input register
as result of decrypting the n input byte(s), otherwise 0

**Precondition:**

Must be preceded by call to aes_init().

## mr_unsign32 aes_encrypt* (aes * a, char * buff)

Encrypts a 16 or n byte input buffer in situ. If the mode of operation is as a block cipher (MR_ECB or
MR_CBC) then 16 bytes will be encrypted. If the mode of operation is as a stream cipher (MR_CFBn,
MR_OFBn or MR_PCFBn) then n bytes will be encrypted.

**Parameters:**

←a Pointer to an initialised instance of an aes structure defined in miracl.h<br />
←→buff Pointer to the buffer of bytes to be encrypted

**Returns:**

In MR_CFBn and MR_PCFBn modes the n byte(s) that were shifted off the end of the input register
as result of encrypting the n input byte(s), otherwise 0

**Precondition:**

Must be preceded by a call to aes_init().

## void aes_end* (aes * a)

Ends an AES encryption session, and de-allocates the memory associated with it. The internal session key
data is destroyed.

**Parameters:**

←→a Pointer to an initialised instance of an aes structured defined in miracl.h

## void aes_getreg* (aes * a, char * ir)

Reads the current contents of the input chaining register associated with this instance of the AES. This is
the register initialised by the IV in the calls to aes_init() and aes_reset().

**Parameters:**

←a Pointer to an instance of the aes structured, defined in miracl.h<br />
→ir A character array to hold the extracted 16-byte data

**Precondition:**

Must be preceded by a call to aes_init().

## BOOL aes_init* (aes * a, int mode, int nk, char * key, char * iv)

Initialises an Encryption/Decryption session using the Advanced Encryption Standard (AES). This is a
block cipher system that encrypts data in 128-bit blocks using a key of 128, 192 or 256 bits. See [Stinson]
for more background on block ciphers.

**Parameters:**

→a Pointer to an instance of the aes structure defined in miracl.h<br />
←mode The mode of operation to be used: MR_ECB (Electronic Code Book), MR_CBC (Cipher
Block Chaining), MR_CFBn (Cipher Feed-Back where n is 1, 2 or 4), MR_PCFBn (error Propagating
Cipher Feed-Back where n is 1, 2 or 4) or MR_OFBn (Output Feed-Back where n is 1,
2, 4, 8 or 16). The value of n indicates the number of bytes to be processed in each application.
For more information on Modes of Operation, see [Stinson]. MR_PCFBn is an invention of our
own [Scott93]<br />
←nk The size of the key in bytes. It can be either 16, 24 or 32<br />
←key A pointer to the key<br />
←iv A pointer to the Initialisation Vector (IV). A 16-byte initialisation vector should be specified for
all modes other than MR_ECB, in which case it can be NULL

**Returns:**

TRUE if successful, otherwise FALSE.

## void aes_reset* (aes * a, int mode, char * iv)

Resets the AES structure.

**Parameters:**

←a Pointer to an instance of the aes structure defined in miracl.h<br />
←mode an Indication of the new mode of operation<br />
←iv A pointer to a (possibly new) initialisation vector

## void shs256_hash* (sha256 * sh, char hash[32])

Generates a 32 byte (256 bit) hash value into the provided array.

**Parameters:**

←sh Pointer to the current instance<br />
→hash Pointer to array to be filled

## void shs256_init* (sha256 * sh)

Initialises an instance of the Secure Hash Algorithm (SHA-256). Must be called before new use.

**Parameters:**

→sh Pointer to an instance of a structure defined in miracl.h

## void shs256_process* (sha256 * sh, int byte)

Processes a single byte. Typically called many times to provide input to the hashing process. The hash
value of all the processed bytes can be retrieved by a subsequent call to shs256_hash().

**Parameters:**

←sh Pointer to the current instance<br />
←byte Character to be processed

### void shs384_hash* (sha384 * sh, char hash[48])

Generates a 48 byte (384 bit) hash value into the provided array.

**Parameters:**

←sh Pointer to the current instance<br />
→hash Pointer to array to be filled

### void shs384_init* (sha384 * sh)

Initialises an instance of the Secure Hash Algorithm (SHA-384). Must be called before new use.

**Parameters:**

! sh Pointer to an instance of a structure defined in miracl.h

**Precondition:**

The SHA-384 algorithm is only available if 64-bit data-type is defined.

### void shs384_process* (sha384 * sh, int byte)

Processes a single byte. Typically called many times to provide input to the hashing process. The hash
value of all the processed bytes can be retrieved by a subsequent call to shs384_hash().

**Parameters:**

←sh Pointer to the current instance<br />
←byte Character to be processed

### void shs512_hash* (sha512 * sh, char hash[64])

Generates a 64 byte (512 bit) hash value into the provided array.

**Parameters:**

←sh Pointer to the current instance<br />
→hash Pointer to array to be filled

### void shs512_init* (sha512 * sh)

Initialises an instance of the Secure Hash Algorithm (SHA-512). Must be called before new use.

**Parameters:**

→sh Pointer to an instance of a structure defined in miracl.h

**Precondition:**

The SHA-512 algorithm is only available if 64-bit data-type is defined.

### void shs512_process* (sha512 * sh, int byte)

Processes a single byte. Typically called many times to provide input to the hashing process. The hash
value of all the processed bytes can be retrieved by a subsequent call to shs512_hash().

**Parameters:**

←sh Pointer to the current instance<br />
←byte Character to be processed

### void shs_hash* (sha * sh, char hash[20])

Generates a twenty byte (160 bit) hash value into the provided array.

**Parameters:**

←sh Pointer to the current instance<br />
→hash Pointer to array to be filled
### void shs_init* (sha * sh)

Initialises an instance of the Secure Hash Algorithm (SHA-1). Must be called before new use.

**Parameters:**

→sh Pointer to an instance of a structure defined in miracl.h

### void shs_process* (sha * sh, int byte)

Processes a single byte. Typically called many times to provide input to the hashing process. The hash
value of all the processed bytes can be retrieved by a subsequent call to shs_hash().

**Parameters:**

←sh Pointer to the current instance<br />
←byte Character to be processed

### void strong_bigdig (csprng * rng, int n, int b, big x)

Generates a big random number of given length from the cryptographically strong generator rng.

**Parameters:**

←rng A pointer to the random number generator<br />
←n<br />
←b<br />
→x Big random number n digits long to base b

**Precondition:**

The base b must be printable, that is 2 <= b <= 256

### void strong_bigrand (csprng * rng, big w, big x)

Generates a cryptographically strong random big number x using the random number generator rng wuch
that 0 <= x < w.

**Parameters:**

←rng A pointer to the current instance<br />
←w<br />
→x

### void strong_init* (csprng * rng, int rawlen, char * raw, mr_unsign32 tod)

Initialises the cryptographically strong random number generator rng. The array raw (of length rawlen)
and the time-of-day value tod are the two sources used together to seed the generator. The former might be
provided from random keystrokes, the latter from an internal clock. Subsequent calls to strong_rng() will
provide random bytes.

**Parameters:**

→rng<br />
←rawlen<br />
←raw An array of length rawlen<br />
←tod A 32-bit time-of-day value

### void strong_kill* (csprng * rng)

Kills the internal state of the random number generator rng.

**Parameters:**

←rng A pointer to a random number generator

### int strong_rng* (csprng * rng)

Generates a sequence of cryptographically strong random bytes.

**Parameters:**

←rng A pointer to a random number generator

**Returns:**

A random byte.

* [Intro](README.md)
* [Installation](installation.md)
* [The UI](the-ui.md)
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* [Floating Slash Nums](floating-slash-nums.md)
* [The C++ Interface](the-cpp-interface.md)
* Example Programs
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* [Instance Variables](instance-variables.md)
* [MIRACL Error Messages](miracl-error-messages.md)
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


Example Programs
---

* [Simple Programs](#simple)
* [Factoring Programs](#factoring)
* [Discrete Logarithm Programs](#discrete)
* [Public-Key Cryptography](#cryptography)
* [Pairing-Based Cryptography](#pairing)
* ['flash' Programs](#flash)

> The programs described here are of an experimental nature, and in many cases are not completely 'finished off'. For further information read the comments associated with the appropriate source file.

## Simple Programs <a id="simple"></a>
___
### hail.c

This program allows you to investigate so-called hailstone numbers, as described by Gruenberger [Gruen]. The procedure is simple. Starting with any number apply the following rules:

1. If it is odd, multiply it by 3 and add 1.
2. If it is even, divide it by 2.
3. Repeat the process, until the number becomes equal to 1, in which case stop.

It would appear that for any initial number this process always eventually terminates, although it has not been proved that this must happen, or that the process cannot get stuck in an infinite loop. What goes up, it seems, must come down. Try the program for an initial value of 27. Then try it using much bigger numbers, like 10709980568908647 (which has interesting behaviour).

### palin.c

This programs allows one to investigate palindromic reversals [Gruen]. A palindromic number is one which reads the same in both directions. Start with any number and apply the following rules.

1. Add the number to the number obtained by reversing the order of the digits. Make this the new number.
2. Stop the process when the new number is palindromic.

It appears that for most initial numbers this process quickly terminates. Try it for 89. Then try it for 196.

### mersenne.c

This program attempts to generate all prime numbers of the form 2<sup>n</sup>-1. The largest known primes have always been of this form because of the efficiency of this Lucas-Lehmer test. The routine **fft_mult** is used, as it is faster for very large numbers.

## Factoring Programs <a id="factoring"></a>
___
Six different Integer Factorisation programs are included, covering all modern approaches to this classical problem. For more background and information on the algorithms used, see [Scott89c].

### brute.c

This program attempts to factorise a number by brute force division, using a table of small prime numbers. When attempting a difficult factorisation it makes sense to try this approach first. Factorise 12345678901234567890 using this program. Then try it on bigger random numbers.

### brent.c

This program attempts to factorise a number using the Brent-Pollard method. This method is faster at finding larger factors than the simple-minded brute force approach. However it will not always succeed, even for simple factorisations. Use it to factorise R17, that is 11111111111111111 (seventeen ones). Then try it on larger numbers that would not yield to the brute force approach.

### pollard.c

Another factoring program, which implements Pollard's (*p*-1) method, specialises in quickly finding a factor *p* of a number *N* for which (*p-1*) has itself only small factors. Phase 1 of this method will work if all these small factors are less than LIMIT1. If Phase 1 fails then Phase 2 searches for just one final larger factor less than LIMIT2. The constants LIMIT1 and LIMIT2 are set inside the program.

### williams.c

This program is similar to Pollards method, but can find a factor *p* of *N* for which (*p+1*) has only small factors. Again two phases are used. In fact this method is sometimes a (*p+1*) method, and sometimes a (*p-1*) method, so several attempts are made to hit on the (*p+1*) condition. The algorithm is rather more complex than that used in Pollards method, and is somewhat slower.

### lenstra.c###

Lenstra [Monty87] has discovered a new method of factorisation, generically similar to the Pollard and Williams methods, but potentially much more powerful. It works by randomly generating an Elliptic Curve, which can then be used to find a factor *p* of *N*, for which *p+1-d* has only small factors, where *d* depends on the particular curve chosen. If one curve fails then another can be tried, an option not possible with the Pollard/Williams methods. Again this is a two-phase method, and although it has very good asymptotic behaviour, it is much slower than the Pollard/Williams methods for each iteration.

### qsieve.c###

This is a sophisticated Pomerance-Silverman-Montgomery [Pomerance], [Silverman] factoring program. which factors F7 = 2<sup>128</sup>+1

    340282366920938463463374607431768211457

in less than 30 seconds, running on a 60MHz Pentium-based computer. When this number was first factored, it took 90 minutes on an IBM 360 mainframe (Morrison & Brillhart [Morrison]), albeit using a somewhat inferior algorithm.

Its speciality is factoring all numbers (up to about sixty digits long), irrespective of the size of the factors. If the number to be factored is *N*, then the program actually works with a number *k.N*, where *k* is a small Knuth-Schroepel multiplier. The program itself works out the best value of *k* to use. Internally, the program uses a 'factor base' of small primes. The larger the number, the bigger will be this factor base. The program works by accumulating information from a number of simpler factorisations. As it progresses with these it prints out *working...n*. When it thinks it has enough information it prints out *trying*, but these tries may be premature and may not succeed. The program will always terminate before the number *n* in *working...n* reaches the size of the factor base.

This program uses much more memory than any of the other example programs, particularly when factoring bigger numbers. The amount of memory that the program can take is limited by the values defined for MEM, MLF and SSIZE at the beginning of the program. These limit the number of primes in the factor base, the number of 'larger' primes used by the so-called large-prime variation of the algorithm, and the sieve size respectively. They should be increased if possible, or reduced if your computer has insufficient memory. See [Silverman] for more details.

Use **qsieve** to factor 10000000000000000000000000000000009 (thirty-five digits).

### factor.c###

This program combines the above algorithms into a single general purpose program for factoring integers. Each method is used in turn in the attempt to extract factors. The number to be factored is given in the command line, as in **factor 11111111111**. The number can alternatively be specified as a formula, using the switch '-f', as in **factor -f (10#11-1)/9**. The symbol # here means 'to the power of' (# is used instead of ^ as the latter symbol has a special meaning for DOS on an IBM PC). Type **factor** on its own for a full description of this and other switches that can be used to control the input/output of this program.

## Discrete Logarithm Programs <a id="discrete"></a>
___
Two programs implement Pollards algorithms [Pollard78] for extracting discrete logarithms. The discrete logarithm problem is to find *x* given *y*, *r* and *n* in:

Inline image 1

The above is a good example of a one-way function. It is easy to calculate *y* given *x*, but apparently extremely difficult to find *x* given *y*. Pollard's algorithms however perform quite well under certain circumstances, if *x* is known to be small or if *n* is a prime *p* for which *p-1* has only small factors.

### kangaroo.c

This program finds *x* in the above, assuming that *x* is quite small. The value of *r* is fixed (at 16), and the modulus *n* is also fixed inside the program. Initially a 'trap' is set. Subsequently the discrete logarithm can be found (almost certainly) for any number, assuming its discrete logarithm is less than a certain upper limit. The number of steps required will be approximately the square root of this limit.

### genprime.c

A prime number *p* with known factorisation of *p-1* is generated by this program, for use by the *index.c* and *identity.c* programs described below. The factors of *p-1* are output to a file *prime.dat*.

### index.c

This program implements Pollard's rho algorithm for extracting discrete logarithms, when the modulus *n* in the above equation is a prime *p*, and when *p-1* has only relatively small factors. The number of steps required is a function of the square root of the largest of these factors.

## Public-Key Cryptography <a id="cryptography"></a>
___
Public Key Cryptography is a two key cryptographic system with the very desirable feature that the encoding key can be made publicly available, without weakening the strength of the cipher. The first example program demonstrates many popular public-key techniques. Then two functional Public-Key cryptography systems, whose strength appears to depend on the difficulty of factorisation, are presented. The first is the classic RSA system (Rivest, Shamir & Adleman [RSA]). This is fast to encode a message, but painfully slow at decoding. A much faster technique has been invented by Blum and Goldwasser. This probabilistic Public Key system is also stronger than RSA in some senses. For more details see [Brassard], who describes it as 'the best that academia has had to offer thus far'. For both methods the keys are constructed from 'strong' primes to enhance security. Closely associated with PK Cryptography, is the concept of the Digital Signature.  A group of example programs implement the Digital Signature Standard, using classic finite fields and elliptic curves over both the fields GF(*p*) and GF(2*<sup>m</sup>*).

### pk-demo.c

This program carries out a 1024-bit Diffie-Hellman key exchange, and then another Diffie-Hellman type key exchange, but this time based on a 160-bit prime and an elliptic curve. Next a test string is encrypted and decrypted using the El Gamal method. The program finishes with a 1024 bit RSA encryption/decryption of the same string. For a good description of all these techniques see [Stinson]. Anyone attempting to implement a PK system using MIRACL is strongly encouraged to examine this file, and its C++ counter-part **pk-demo.cpp**.

### bmark.c/imratio.c

The benchmarking program *bmark.c* allows the user to quickly determine the time that will be required to implement any of the popular public key methods. It can be compiled and linked with any of the variants of the MIRACL library, as specified in *mirdef.h*, to determine which gives the best performance on a particular platform for a particular PK method. The program *imratio.c* when compiled and run calculates the significant ratios S/M, I/M and J/M, where S is the time for a modular squaring, M the time for a modular multiplication, I the time for a modular inversion, and J the time for a Jacobi symbol calculation.

### genkey.c

This program generates the 'public' encoding key and 'private' decoding keys that are necessary for both the original Rivest-Shamir-Adleman PK system and the superior Blum-Goldwasser method [Brassard]. These keys can take a long time to generate, as they are formed from very large prime numbers, which must be generated carefully for maximum security.

The size of each prime in bits is set inside the program by a #define. The security of the system depends on the difficulty of factoring the encoding 'public' key, which is formed from two such large primes. The largest numbers which can be routinely factored using hundreds of powerful computers are 430 bits long (1996). So a minimum size of 512 bits for each prime gives plenty of security (for now!)

After this program has run, the two keys are created in files PUBLIC.KEY and PRIVATE.KEY.

### encode.c

Messages or files may be encoded with this program, which uses the 'public' encoding key from the file PUBLIC.KEY, generated by the program *genkey*, which must have been run prior to using this program. When run, the user is prompted for a file to encipher. Either supply the name of a text file, or press return to enter a message directly from the keyboard. In the former case the encoded output is sent to a file with the same name, but with the extension .RSA. In the latter case a prompt is issued for an output filename, which must be given. Text entered from the keyboard must be terminated by a CONTROL-Z (end-of-file character). Type out the encoded file and be impressed by how indecipherable it looks.

### decode.c

Messages or files encoded using the RSA system may be decoded using this program, which uses the 'private' decoding key from the file PRIVATE.KEY generated by the program *genkey* which must have been run at some stage prior to using this program.

When run, the user is prompted for the name of the file to be decoded. Type in the filename (without an extension - the program will assume the extension .RSA) and press return. Then the user is asked for an output filename. Either supply a filename or press return, in which case the decoded output will be sent straight to the screen. A problem with the RSA system becomes immediately apparent - decoding takes quite a relatively long time! This is particularly true for larger key sizes and long messages.

### enciph.c

This program works in an identical fashion to the program 'encode', except that it prompts for a random seed before encrypting the data. This random seed is then used internally to generate a larger random number. The encryption process depends on this random number, which means that the same data will not necessarily produce the same cipher-text, which is one of the strengths of this approach. As well as creating a file with a .BLG extension containing the encrypted data, a second small file (with the .KEY extension) is also produced.

### deciph.c

This program works in an identical fashion to the program 'decode'. However it has the advantage that it runs much more quickly. There will be a significant initial delay while a rather complex calculation is carried out. This uses the private key and the data in the .KEY file to recover the large random number used in the encryption process. Thereafter deciphering is as fast as encipherment.

### dssetup.c

A standard method for digital signature has been proposed by the American National Institute of Standards and Technology (NIST), and fully described in the Digital Signature Standard [DSS]. This program generates a prime *q*, another much larger prime *p=2nq+1*, (where *n* is random) and a generator *g*. This information is made common to all. This program generates the common information {*p,q,g*} into a file *common.dss* .

### limlee.c

It has been shown by Lim & Lee [LimLee] that for certain Discrete Logarithm based protocols (but not for the Digital Signature Standard) there is a weakness associated with primes of the kind generated by the *dssetup.c* program described above. To avoid these problems they recommend that *p* is of the form *p*=2.p<sub>1</sub>.p<sub>2</sub>.p<sub>3</sub>…q + 1, where the *p*<sub>i</sub> are primes greater than *q*. This program generates the values (*p,q,g*) into a file *common.dss*, and can be used in place of *dssetup.c* . It is a little slower.

### dssgen.c

Each user who wishes to digitally sign a computer file randomly generates their own private key *x<q* and makes available a public key *y=g<sup>x</sup> mod p*. The security of the system depends on the sizes of *p* and *q* (at least 512 bits and 160 bits respectively). This program generates a single public/private key pair in the files *public.dss* and *private.dss* respectively.

### dssign.c

This program uses the private key from *private.dss* to 'sign' a document stored in a file. First the file data is 'hashed' down to a 160 bit number using SHA, the Standard Hash Algorithm. This is also specified by the NIST and is implemented in the provided module *mrshs.c* . The 160-bit hash is duly 'signed' as described in [DSS], and the signature, in the form of two 160-bit numbers, written out to a file. This file has the same name as the document file, but with the extension *.dss* .

### dssver.c

This program uses the public key from *public.dss* to verify the signature associated with a file, as described in [DSS].

### ecsgen.c, ecsign.c, ecsver.c

The Digital Signature technique can also be implemented using Elliptic Curves over the field GF(*p*)[Jurisic]. Common domain information in the order {*p,A,B,q,X,Y*} is extracted from the file *common.ecs* created using one of the point-counting algorithms described below. These values specify an initial point (*X,Y*) on an elliptic curve *y<sup>2</sup>=x<sup>3</sup>+Ax+B mod p* which has *q* points on it. The advantages are a much smaller public key for the same level of security. Smaller numbers can be used as the discrete logarithm problem is apparently much more difficult in the context of an elliptic curve. This in turn implies that elliptic curve arithmetic is also potentially faster. However the use of smaller numbers is somewhat offset by the more complex calculations involved.

This set of programs has the same functionality as those described above for the standard DSS. Note however that the file extension *.ecs* is used for all the generated files. Read the comments in the source files for more information.

### ecsgen2.c, ecsign2.c, ecsver2.cpp

These programs provide the same functionality as those provided above, but use elliptic curves defined over the field GF(2*<sup>m</sup>*). Domain information in this case is extracted from the file *common2.ecs* in the order {*m,A,B,q,X,Y,a,b,c*}, where (*X,Y*) specifies an initial point on the elliptic curve *y<sup>2</sup>=x<sup>3</sup>+Ax<sup>2</sup>+B* defined over GF(2<sup>*m*</sup>). The parameters of a trinomial or pentanomial basis are also specified, *t<sup>m</sup>+t<sup>a</sup>+1* or *t<sup>m</sup>+t<sup>a</sup>+t<sup>b</sup>+t<sup>c</sup>+1* respectively. In the former case *b* and *c* are zero. Finally *cf.q* specifies the number of points on the curve, the product of a large prime factor *q* and a small cofactor *cf*. The latter is normally 2 or 4. The file *common2.ecs* can be created by the **schoof2** program described below.

### cm.cpp, schoof.cpp, mueller.cpp, process.cpp, sea.cpp, schoof2.cpp

A problem with Elliptic curve cryptography is the construction of suitable curves. This is actually much more difficult than the equivalent problem in the integer finite field as implemented by the program *dssetup.c/dssetup.cpp* . One approach is the Complex Multiplication method, as described in the Annex to the IEEE P1363 Standard Specifications for Public Key Cryptography (available from the Web). This is implemented here by the C++ program *cm.cpp* and its supporting modules *float.cpp*, *complex.cpp*, *flpoly.cpp*, *poly.cpp*, and associated header files.

The program when run uses command line arguments. Type **cm** on its own to get instructions. For example

    cm -f 2#224-2#96+1 -o common.ecs

generates the common information needed to implement elliptic curve cryptography into the file *common.ecs* .

As an alternative to the CM method, a random curve can be generated, and the points on the curve directly counted. This is more time-consuming than complex multiplication, but may lead to more secure, less structured curves. The basic algorithm is due to Schoof [Sch],[Blake] and is only practical due to the use of Fast Fourier Transform methods [Shoup] for the multiplication/division of large degree polynomials. See *mrfast.c* . Its still very slow, much slower than **cm**. Type **schoof** on its own to get instructions. For example:

    schoof –f 2#192-2#64-1 –3 35317045537

counts the points on the curve y<sup>2</sup> = x<sup>3</sup> –3x +35317045537 mod 2<sup>192</sup>-2<sup>64</sup>-1.

This curve is randomly selected (actually 35317045537 is my international phone number). The answer is the prime number:

    6277101735386680763835789423127240467907482257771524603027

Be prepared to wait, or….

Use the suite of **programs**, **mueller**, **process**, and **sea**, which together implement the superior, but more complex, Schoof-Elkies-Atkin method for point counting. See [Blake] for details.

First of all the **mueller** program should be run, to generate the required Modular Polynomials. This needs to be done just once – ever. The greater your collection of Modular Polynomials, the greater the size of prime modulus that can be used for the elliptic curves of interest. Note that this program is particularly hard on memory resources, as well as taking a long time to run. However after an hour at most you should have enough Modular Polynomials to start experimenting. As with all these programs, simply typing the program name without parameters generates instructions for use. Also be sure to read the comments at the start of the source file, in this case *mueller.cpp* .

Next run the **process** application, which processes the file of raw modular polynomials output by **mueller**, for use with a specified prime modulus.

Finally run **sea** to count the points on the curve, and optionally to create a *.ecs* file as described above.

For example:
```
mueller 0 120 –o mueller.raw

process –f 65112*2#144-1 –i mueller.raw –o test160.pol

sea –3 49 –i test160.pol
```
generates all the modular polynomials for primes from 0 to 120, and outputs them to the file *mueller.raw* . Then these polynomials are processed with respect to the prime *p* = 65112.2<sup>144</sup>-1, to create the file *test160.pol*. Finally the main **sea** application counts the points on the curve *y*<sup>2</sup>=*x*<sup>3</sup>-3x+49 mod *p*.

This may be more complicated to use, but its much faster than **schoof**.

Read the comments at the start of *sea.cpp* for more information.

For elliptic curves over GF(2<sup>*m*</sup>), the program **schoof2** can be used, which is quite similar to **schoof**. It is even slower, but just about usable on contemporary hardware. For example:

    schoof2 1 52 191 9 –o common2.ecs

counts the points on the curve  *y<sup>2</sup>+xy=x<sup>3</sup>+x<sup>2</sup>+52*, over the field GF(2<sup>191</sup>). A suitable irreducible basis must also be specified, in this case *t<sup>191</sup>+t<sup>9</sup>+1*. Tables of suitable bases can be found in many documents, for example in Appendix A of the IEEE P1363 standard. See [Menezes] for a description of the method.

For more information on building these applications see the files *cm.txt*, *schoof.txt*, *schoof2.txt* and *sea.txt*.

### crsetup.cpp, crgen.cpp, crencode.cpp, crdecode.cpp

Public key schemes should ideally be immune from *adaptive chosen cipher-text* attacks, whereby an attacker is able to obtain decryptions of any presented cipher-texts other than the particular one they are interested in. Recently Cramer & Shoup [CS] have come up with a Public Key encryption method that is provably immune to such powerful attacks. The program **crsetup** creates various global parameters, and **crgen** generates one set of public and private keys in the files *public.crs* and *private.crs* respectively. To encrypt an ASCII file called for example *fred.txt*, run the **crencode** program that generates a random session key, and uses it to encrypt the file. This session key is in turn encrypted by the public key and stored in the file *fred.key*. The binary encrypted file itself is stored as *fred.crs*. To decrypt the file, run the **crdecode** program, which uses the private key to recover the session key, and hence decode the text to the screen.

A couple of points are worth highlighting. First of all the bulk encryption is carried out using a block cipher method. Such hybrid systems are standard practice, as block ciphers are much faster than public key methods. The block cipher scheme used is the new Advanced Encryption Standard block cipher, which is implemented in *mraes.c* .

Examination of the source code *crdecode.cpp* reveals that decryption is a two-pass process. On the first pass the program determines the validity of the cipher-text, and only after that is known to be valid does the program go on to decrypt the file. So the decryption procedure will not respond at all to arbitrary bit strings concocted by an attacker.

### brick.c, ebrick.c, ebrick2.c

Certain Cryptographic protocols require the exponentiation of a fixed number *g*, that is the calculation of *g<sup>x</sup> mod n*, where *g* and *n* are known in advance. In this case the calculation can be substantially speeded up by a precomputation which generates a small table of *big* numbers. The method was first described by Brickell et al [Brick]. The example program *brick.c* illustrates the method. The GF(*p*) elliptic curve equivalent is provided in *ebrick.c* and the GF(2<sup>*m*</sup>) equivalent in *ebrick2.c* . In a typical application the precomputed tables might be generated using one of these programs (see commented-out code in *ebrick2.c*), which then might be transferred to ROM in an embedded program. The embedded program might use a static build of MIRACL to make use of these tables.

### identity.c

This is a program that allows individuals, issued with certain secret information, to establish mutual keys by performing a calculation involving only the other correspondents publicly known identity. No interchange of data is required [Maurer], and so this is called Non-Interactive Key Exchange. Note that the 'publicly known identity' might, for example, be simply an email address. For a full description see [Scott92]. This example program generates the secret data from the proffered Identity. However before this program is run, the program *genprime.c* must be run twice, to generate a pair of suitable trap-door primes. Copy the output of the program, *prime.dat*, first to *trap1.dat* and then to *trap2.dat* . The product of these primes will be used as the composite modulus used for subsequent calculations.

### Pairing Based Cryptography <a id="pairing"></a>
___
A number of experimental programs are provided to implement cryptographic protocols based on *pairings*. Notably there are examples of Identity-Based Encryption (IBE) and authenticated key exchange. Read the files *pairings.txt*, *ake.txt* and *ibe.txt* for details.

## 'flash' Programs <a id="flash"></a>
___
Several programs demonstrate the use of *flash* variables. One gives an implementation of Gaussian elimination to solve a set of linear equations, involving notoriously ill-conditioned Hilbert matrices. Others show how rational arithmetic can be used to approximate real arithmetic, in, for example the calculation of roots and p. The former program detected an error in the value for the square root of 5 given in Knuth's appendix A [Knuth81]. The correct value is:

    2.23606 79774 99789 69640 91736 68731 27623 54406

The error is in the tenth last digit, which is a 2, and not a 1.

The *roots* program runs particularly fast when calculating the square roots of single precision integers, as a simple form of continued fraction generator can be used. In one test the golden ratio  was calculated to 100,000 decimal places in 3 hours of CPU time on a VAX11/780.

The 'sample' program was used to calculate p correct to 1000 decimal places, taking less than a minute on a 25MHz 80386-based IBM PC to do so.

### roots.c

This program calculates the square root of an input number, using Newtons method. Try using it to calculate the square root of two. The accuracy obtained depends on the size of the flash variables, specified in the initial call to **mirsys**. The tendency of flash arithmetic to prefer simple numbers can be illustrated by requesting, say, the square root of 7. The program calculates this value and then squares it, to give 7 again exactly. On your pocket calculator the same result will only be obtained if clever use is made of extra (hidden) guard digits.

### hilbert.c

Traditionally the inversion of 'Hilbert' matrices is regarded as a tough test for any system of arithmetic. This programs solves the set of linear equations *H.x = b*, where *H* is a Hilbert matrix and *b* is the vector [1,1,1,1,....1], using the classical Gaussian Elimination method.

### sample.c

This program is the same as that used by Brent [Brent78] to demonstrate some of the capabilities of his Fortran Multiprecision arithmetic package.

### ratcalc.c

As a comprehensive and useful demonstration of flash arithmetic this program simulates a standard full-function scientific calculator. Its unique feature (besides its 36-digit accuracy) is its ability to work directly with fractions, and to handle mixed calculations involving both fractions and decimals. By using this program the user will quickly get a feel for flash arithmetic and its capabilities. Note that this program contains some non-portable code (screen handling routines) that must be tailored to each individual computer/terminal combination. The version supplied works only on standard PCs using DOS, or a command prompt window in Windows 'NT/'98.

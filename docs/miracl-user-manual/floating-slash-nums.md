* [Intro](README.md)
* [Installation](installation.md)
* [The UI](the-ui.md)
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* Floating Slash Nums
* [The C++ Interface](the-cpp-interface.md)
* [Example Programs](example-progs.md)
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* [Instance Variables](instance-variables.md)
* [MIRACL Error Messages](miracl-error-messages.md)
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


Floating Slash Numbers
---

The straightforward way to represent rational numbers is as reduced fractions, as a numerator and denominator with all common factors cancelled out. These numbers can then be added, subtracted, multiplied and divided in the obvious way and the result reduced by dividing both numerator and denominator by their Greatest Common Divisor. An efficient GCD subroutine, using Lehmers modification of the classical Euclidean algorithm for multiprecision numbers [Knuth81], is included in the MIRACL package.

An alternative way to represent rationals would be as a finite continued fraction [Knuth81]. Every rational number *p/q* can be written as:
![Equation 1](images/equation_1.png)
or more elegantly as *p/q* = [a<sub>0</sub>/a<sub>1</sub>/a<sub>2</sub>/..../a<sub>n</sub>] where the a<sub>i</sub> are positive integers, usually quite small.

For example:
![Equation 2](images/equation_2.png)
Note that the a<sub>i</sub> elements of the above continued fraction representation are easily found as the quotients generated as a by-product when the Euclidean GCD algorithm is applied to *p* and *q*.

As we are committed to fixed length representation of rationals, a problem arises when the result of some operation exceeds this fixed length. There is a necessity for some scheme of truncation, or rounding. While there is no obvious way to truncate a large fraction, it is a simple matter to truncate the continued fraction representation. The resulting, smaller, fraction is called a best rational approximation, or a convergent, to the original fraction.

Consider truncating 277/642 = [0/2/3/6/1/3/3]. Simply drop the last element from the CF representation, giving [0/2/3/6/1/3] = 85/197, which is a very close approximation to 277/642 (error = 0.0018%). Chopping more terms from the CF expansion gives the successive convergents as 22/51, 19/44, 3/7, 1/2, 0/1. As the fractions get smaller, the error increases. Obviously the truncation rule for a computer implementation should be to choose the biggest convergent that fits the computer representation.

The type of rounding described above is also called ‘Mediant rounding’. If p/q and r/s are two neighbouring representable slash numbers astride a gap, then their mediant is the unrepresentable (p+r)/(q+s). All larger fractions between p/q and the mediant will round to p/q, and those between r/s and the mediant will round to r/s. The mediant itself rounds to the ‘simpler’ of p/q and r/s.

This is theoretically a very good way to round, much better than the rather arbitrary and base-dependent methods used in floating-point arithmetic, and is the method used here. The full theoretical basis of floating-slash arithmetic is described in detail by Matula & Kornerup [Matula85]. It should be noted that our *flash* representation is in fact a cross between the fixed- and floating-slash systems analysed by Matula & Kornerup, as our slash can only float between words, and not between bits. However the characteristics of the *flash* data type will tend to those of floating-slash, as the precision is increased.

The MIRACL routine **mround** implements mediant rounding. If the result of an arithmetic operation is the fraction p/q, then the Euclidean GCD algorithm is applied as before to p and q. However this time the objective is not to use the algorithm to calculate the GCD per se, but to use its quotients to build successive convergents to p/q. This process is stopped when the next convergent is too large to fit the *flash* representation. The complete algorithm is given below (Kornerup & Matula [Korn83])

Given p³0 and q³1:

b<sub>-2</sub>=p          x<sub>-2</sub>=0     y<sub>-2</sub>=1

b<sub>-1</sub>=q          x<sub>-1</sub>=1     y<sub>-1</sub>=0

Now for i=0,1,..... and for b<sub>i-1</sub>>0, find the quotient a<sub>i</sub> and remainder b<sub>i</sub> when b<sub>i-2</sub> is divided by b<sub>i-1</sub>, such that:

b<sub>i</sub> = -a<sub>i</sub>.b<sub>i-1</sub> + b<sub>i-2</sub>

Then calculate

x<sub>i</sub> = a<sub>i</sub>.x<sub>i-1</sub> + x<sub>i-2</sub>

y<sub>i</sub> = a<sub>i</sub>.y<sub>i-1</sub> + y<sub>i-2</sub>

Stop when ? is too big to fit the *flash* representation, and take ? as the rounded result.

If applied to 277/642, this process will give the same sequence of convergents as stated earlier.

Since this rounding procedure must be applied to the result of each arithmetic operation, and since it is potentially rather slow, a lot of effort has been made to optimise its implementation. Lehmer's idea of operating only with the most significant piece of each number for as long as possible [Knuth81] is used, so that for most of the iterations only single-precision arithmetic is needed. Special care is taken to avoid the rounded result overshooting the limits of the **flash** representation [Scott89a]. The application of the basic arithmetic routines to the calculation of elementary functions such as *log(x)*, *exp(x)*, *sin(x)*, *cos(x)*, *tan(x)* etc., uses the fast algorithms described by Brent [Brent76].

In many cases the result given by a program can be guaranteed to be exact. This can be checked by testing the instance variable **EXACT**, which is initialised to TRUE and is only set to FALSE if any rounding takes place.

A disadvantage of using a *flash* type of variable to approximate real arithmetic is the non-uniformity in gap-size between representable values (Matula & Kornerup [Matula85]).

To illustrate this consider a floating-slash system which is constrained to have the product of numerator and denominator less than 256. Observe that the first representable fraction less than 1/1 in such a system is 15/16, a gap of 1/16. The next fraction larger than 0/1 is 1/255, a gap of 1/255. In general, for a *k*-bit floating-slash system, the gap size varies from smaller than 2<sup>-k</sup> to a worst case 2<sup>-k/2</sup>. In practise this means that a real value that falls into one of the larger gaps, will be represented by a fraction which will be accurate to only half its usual precision. Fortunately such large gaps are rare, and increasingly so for higher precision, occurring only near simple fractions. However it does mean that real results can only be completely trusted to half the given decimal places. A partial solution to this problem would be to represent rationals directly as continued fractions. This gives a much better uniformity of gap-size (Kornerup & Matula [Korn85]), but would be very difficult to implement using a high level language.

Arithmetic on *flash* data-types is undoubtedly slower than on an equivalent sized multiprecision floating-point type (e.g. [Brent78]). The advantages of the *flash* approach are its ability to exactly represent rational numbers, and do exact arithmetic on them. Even when rounding is needed, the result often works out correctly, due to the tendency of mediant-rounding to prefer a simple fraction over a complex one. For example the *roots* program (see 'Example Programs' when asked to find the square root of 2 and then square the result, comes back with the exact answer of 2, despite much internal rounding.

Do not mix *flash* arithmetic with the built-in *double* arithmetic. They don’t mix well. If you decide to use *flash* arithmetic, use it throughout, and convert all constants at the start to type *flash*. Even better specify such constants if possible as fractions. So (in C++) it is much preferable to write:

`x=Flash(5,8); // x=5/8`

rather than

`x=.625;`


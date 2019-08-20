* Intro
* [Installation](installation.md)
* [The UI](the-ui.md)
* [Internal Rep](internal-rep.md)
* [Implementation](implementation.md)
* [Floating Slash Nums](floating-slash-nums.md)
* [The C++ Interface](the-cpp-interface.md)
* [Example Programs](example-progs.md)
* [The MIRACL Routines](miracl-explained/reference-manual/low-level-routines.md)
* [Instance Variables](instance-variables.md)
* [MIRACL Error Messages](miracl-error-messages.md)
* [Hardware Compiler Interface](hardware-compiler-interface.md)
* [Bibliography](bibliography.md)


Intro
---

Remember when as a naive young computer user, you received delivery of your brand new state-of-the-art micro; remember your anticipation at the prospect of the computer power now available at your fingertips; remember recalling all those articles which promised that ‘today’s microcomputers are as powerful as yesterdays mainframes’. Remember then slowly and laboriously typing in your first program, to calculate, say, 1000! (i.e. 1000 ´ 999 ´ 998... ´1) - a calculation unimaginable by hand.
```
10 LET X=1
20 FOR I=1 TO 1000
30 X=X*I
40 NEXT I
50 PRINT X
60 END
RUN
```

After a few seconds the result appeared:

`Too big at line 30`

Remember your disappointment.

Now try the MIRACL approach. MIRACL is a portable C library which implements multiprecision integer and rational data-types, and provides the routines to perform basic arithmetic on them.

Run the program **fact** from the distribution media, and type in 1000. There is your answer - a 2568 digit number.

Now compile and run the program **roots**, and ask it to calculate the square root of 2. Virtually instantly your computer comes back with the value correct to 100+ decimal places. Now that’s what I call computing!

Next run the Public Key Cryptography program **enciph**. When it asks the name of a file to be enciphered press return. When it asks for an output filename, type FRED followed by return. Now type in any message, finishing with CONTROL-Z. Your message has been thoroughly enciphered in the file FRED.BLG (type it out and see). Now run ‘deciph’, and type in FRED. Press return for the requested output filename. Your original message appears on the screen.

This type of encipherment, based as it is on the difficulty of factoring large numbers, offers much greater security and flexibility than more traditional methods.

A useful demonstration of the power of MIRACL is given by the program **ratcalc**, a powerful scientific calculator - accurate to 36 decimal places and with the unusual ability to handle fractions directly.

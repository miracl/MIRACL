author: Joud Khoury jkhoury@bbn.com

==============
Introduction
==============
We have implemented a Makelfiles to automate building the standard library.
This make file builds shared objects for Mac and Linux. It takes care of linking the correct 
objects depending on specified curve. It creates a separate library per curve to expose the standard
miracl PFC interface to external applications. 
Note that to optimize the Miracl implementation based on the specific architecture, 
we used the comba optimizations. Comba optimization depends on the modulus p of the curve being used. 
To implement comba we need to specify the number of words n 
which should be n=ceil(p/word size) where word size depends on the architecture (64 bit or 32 bit).  
For the MNT curve for example, where p=160bits n=3 whereas for the CP curve p=512 and hence n=8.
For additional info see https://certivox.jira.com/wiki/display/MIRACLPUBLIC/MIRACL+User%27s+Manual

By default all libraries are compiled with multi-threading and COMBA support 

=============
INSTALLATION
=============
We shall different curves with the make below. Here is a list of the allows curves to specify for <curve> below
	<curve> := [cp | mnt | bn | kss | bls | ss2 ] 
Anytime curve is specified, make sure to set the same curve in the header of the miracl_wrapper.h

First flat unzip the miracl code 
	unzip -j -aa -L miracl.zip

Now we are ready to make:

Makefile with optimizations for Intel and AMD64 architecture (e.g. cluster nodes) with comba optimizations, and multi-threading 
for both osx and linux
	#uninstall first if different version previosuly installed)
		$make clean
	#make a separate library per curve
		$make curve=cp
		$make curve=mnt
		$make curve=bn
		$make curve=kss
		$make curve=bls
	#install each one (same applies for uninstall)
	# libdir and includedir have to specified only when user does not have root access
	#   and in that case LD_LIBRARY_PATH must include libdir
		$sudo make install curve=cp libdir=<libdir> includedir=<includedir>
		$sudo make install curve=mnt libdir=<libdir> includedir=<includedir>
		$sudo make install curve=bn libdir=<libdir> includedir=<includedir>
		$sudo make install curve=kss libdir=<libdir> includedir=<includedir>
		$sudo make install curve=bls libdir=<libdir> includedir=<includedir>
	#test it: first set <curve> correctly in miracl_wrapper.h and build multi-threaded benchmark as follows	 
		$make benchmarkthread curve=<curve> 
		$./benchmarkthread <numthreads>

Makefile withOUT optimizations	
	#same as above except pass comba=n to the make
	
	#To test the single threaded version run (only if single threaded libs were built above i.e. no mthreading flag passed)
		$make cpabe curve=<curve> comba=n
		$./cpabe
		
		
	#To create single-threaded benchmark 
	#set the curve in the header of the miracl_wrapper.h; this is what benchmark.cpp will be linked against, then
	 	$make benchmark curve=<curve> comba=n			
		$./benchmark <iterations>

=============	
Other NOTES
=============
[For record only - do not make these changes, already in the makefile] 
To compile an optimized version of the library, we had to implement the following changes
1- define MR_COMBA n in mirdef.h
2- generate mrcomba.c using mex utility e.g. ./mex n amd64 mrcomba (requires compiling mex.c first)
3- use the correct muldiv.c depending on architecture (check use guide)
4- compile mrcomba.c and muldiv.c and include it in the miracle.a library
5- use the -DZZNS=n flag when compiling the c++ libraries

To compile with multithreading support, pass mthreading=true to the make

We extended the PFC implementations for G1 , G2, and GT to support serialize/deserialize of elements.
We need that for over the network crypto that we do. The spill/restore functionality only serialized
precomputations which we are less interested in (we can pre comp at the destiantions).

- [Completed 10/2012] Update AMD makefile to support compiling all curve linbraries (instead of specifying curve)
- [Completed 10/2012] Update AMD makefile to support multi-threading compile
- [Completed 10/2012] Create same for optimized intel
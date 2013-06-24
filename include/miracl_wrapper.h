/*
	Quick Benchmark utility
	jkhoury@bbn.com

   Compile with modules as specified below

TYPE 1 curves
============
   For MR_PAIRING_SS2 curves
	ss2_pair.cpp ec2.cpp gf2m4x.cpp gf2m.cpp big.cpp miracl.lib

	For MR_PAIRING_SSP curves
	ssp_pair.cpp ecn.cpp zzn2.cpp zzn.cpp big.cpp miracl.lib

TYPE 3 curves
=============
   For MR_PAIRING_CP curve
   cp_pair.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_MNT curve
   mnt_pair.cpp zzn6a.cpp ecn3.cpp zzn3.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_BN curve
   bn_pair.cpp zzn12a.cpp ecn2.cpp zzn4.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_KSS curve
   kss_pair.cpp zzn18.cpp zzn6.cpp ecn3.cpp zzn3.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_BLS curve
   bls_pair.cpp zzn24.cpp zzn8.cpp zzn4.cpp zzn2.cpp ecn4.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

*/
#define TYPE3

#ifdef TYPE3
#define GROUP_NAME G2
//********* choose just one of these pairs **********
//#define MR_PAIRING_CP      // AES-80 security
//#define AES_SECURITY 80

//#define MR_PAIRING_MNT	// AES-80 security
//#define AES_SECURITY 80

#define MR_PAIRING_BN    // AES-128 or AES-192 security ****
#define AES_SECURITY 128
//#define AES_SECURITY 192

//#define MR_PAIRING_KSS    // AES-192 security
//#define AES_SECURITY 192

//#define MR_PAIRING_BLS    // AES-256 security
//#define AES_SECURITY 256
//*********************************************
#include "pairing_3.h"
#endif

#ifdef TYPE1
#define GROUP_NAME G1
//********* choose just one of these **********
#define MR_PAIRING_SS2    // AES-80 or AES-128 security GF(2^m) curve
#define AES_SECURITY 80   // OR
//#define AES_SECURITY 128

//#define MR_PAIRING_SSP    // AES-80 or AES-128 security GF(p) curve
//#define AES_SECURITY 80   // OR
//#define AES_SECURITY 128
//*********************************************
#include "pairing_1.h"
#endif

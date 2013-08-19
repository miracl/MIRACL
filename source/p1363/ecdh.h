/***************************************************************************
                                                                           *
Copyright 2013 CertiVox UK Ltd.                                           *
                                                                           *
This file is part of CertiVox MIRACL Crypto SDK.                           *
                                                                           *
The CertiVox MIRACL Crypto SDK provides developers with an                 *
extensive and efficient set of cryptographic functions.                    *
For further information about its features and functionalities please      *
refer to http://www.certivox.com                                           *
                                                                           *
* The CertiVox MIRACL Crypto SDK is free software: you can                 *
  redistribute it and/or modify it under the terms of the                  *
  GNU Affero General Public License as published by the                    *
  Free Software Foundation, either version 3 of the License,               *
  or (at your option) any later version.                                   *
                                                                           *
* The CertiVox MIRACL Crypto SDK is distributed in the hope                *
  that it will be useful, but WITHOUT ANY WARRANTY; without even the       *
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *
  See the GNU Affero General Public License for more details.              *
                                                                           *
* You should have received a copy of the GNU Affero General Public         *
  License along with CertiVox MIRACL Crypto SDK.                           *
  If not, see <http://www.gnu.org/licenses/>.                              *
                                                                           *
You can be released from the requirements of the license by purchasing     *
a commercial license. Buying such a license is mandatory as soon as you    *
develop commercial activities involving the CertiVox MIRACL Crypto SDK     *
without disclosing the source code of your own applications, or shipping   *
the CertiVox MIRACL Crypto SDK with a closed source product.               *
                                                                           *
***************************************************************************/

/*
 *  MIRACL ECDH header file
 *  Author: M. Scott 2013
 */

#ifndef ECDH_H
#define ECDH_H

#include "miracl.h"
#include "octet.h"

#define EAS 16 /* Symmetric Key size - 128 bits */
#define EGS 32 /* ECCSI Group Size - 256 bits */
#define EFS 32 /* ECCSI Field Size - 256 bits */

#define ECDH_OK                     0
#define ECDH_DOMAIN_ERROR          -1
#define ECDH_INVALID_PUBLIC_KEY    -2
#define ECDH_ERROR                 -3
#define ECDH_INVALID               -4
#define ECDH_DOMAIN_NOT_FOUND      -5
#define ECDH_OUT_OF_MEMORY         -6
#define ECDH_DIV_BY_ZERO           -7
#define ECDH_BAD_ASSUMPTION        -8

extern const mr_small ecrom[];

/* ECp domain parameters */

typedef struct
{
	int nibbles;
    char Q[EFS];
    char A[EFS];
    char B[EFS];
    char R[EGS];
    char Gx[EFS];
    char Gy[EFS];
} ecp_domain;

#define HASH_BYTES 32

#if HASH_BYTES==20
	#define HASHFUNC sha
	#define SHS_INIT shs_init
	#define SHS_PROCESS shs_process
	#define SHS_HASH shs_hash
	#define HASH_BLOCK 64
#endif

#if HASH_BYTES==32
	#define HASHFUNC sha256
	#define SHS_INIT shs256_init
	#define SHS_PROCESS shs256_process
	#define SHS_HASH shs256_hash
	#define HASH_BLOCK 64
#endif

#if HASH_BYTES==48
	#define HASHFUNC sha384
	#define SHS_INIT shs384_init
	#define SHS_PROCESS shs384_process
	#define SHS_HASH shs384_hash
	#define HASH_BLOCK 128
#endif

#if HASH_BYTES==64
	#define HASHFUNC sha512
	#define SHS_INIT shs512_init
	#define SHS_PROCESS shs512_process
	#define SHS_HASH shs512_hash
	#define HASH_BLOCK 128
#endif

/* ECDH Auxiliary Functions */

extern void CREATE_CSPRNG(csprng *,octet *);
extern void KILL_CSPRNG(csprng *);
extern void HASH(octet *,octet *);
extern BOOL HMAC(octet *,octet *,int,octet *);
extern void KDF1(octet *,int,octet *);
extern void KDF2(octet *,octet *,int,octet *);
extern void PBKDF2(octet *,octet *,int,int,octet *);
extern void AES_CBC_IV0_ENCRYPT(octet *,octet *,octet *);
extern BOOL AES_CBC_IV0_DECRYPT(octet *,octet *,octet *);

/* ECDH primitives - support functions */

extern void ECP_DOMAIN_KILL(ecp_domain *);
extern int  ECP_DOMAIN_INIT(ecp_domain *,const void *);
extern int  ECP_KEY_PAIR_GENERATE(ecp_domain *,csprng *,octet *,octet *);
extern int  ECP_PUBLIC_KEY_VALIDATE(ecp_domain *,BOOL,octet *);

/* ECDH primitives */

extern int ECPSVDP_DH(ecp_domain *,octet *,octet *,octet *);
extern int ECPSVDP_DHC(ecp_domain *,octet *,octet *,BOOL,octet *);

/* ECIES functions */
extern void ECP_ECIES_ENCRYPT(ecp_domain *,octet *,octet *,csprng *,octet *,octet *,int,octet *,octet *,octet *);
extern BOOL ECP_ECIES_DECRYPT(ecp_domain *,octet *,octet *,octet *,octet *,octet *,octet *,octet *);

/* ECDSA functions */
extern int ECPSP_DSA(ecp_domain *,csprng *,octet *,octet *,octet *,octet *);
extern int ECPVP_DSA(ecp_domain *,octet *,octet *,octet *,octet *);
#endif


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

/* This file implements a typical thread-safe API for MIRACL */
/* Static build - requires no heap */
/* See comments in ecdh.c for more details on the build */
/* Derived from p1363.c code */ 

/* test driver and function exerciser for ECDH/ECIES/ECDSA Functions */
/* cl /O2 testecc.c ecdh.c octet.c miracl.lib */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ecdh.h"

int main(int argc,char **argv)
{   
    int i,res;
    BOOL result;
	char *pp="M0ng00se";
/* These octets are automatically protected against buffer overflow attacks */
/* Note salt must be big enough to include an appended word */
/* Note ECIES ciphertext C must be big enough to include at least 1 appended block */
/* Recall EFS is field size in bytes. So EFS=32 for 256-bit curve */
	char s0[EGS],s1[EGS],w0[2*EFS+1],w1[2*EFS+1],z0[EFS],z1[EFS],raw[100],key[EAS],salt[32],pw[20],b64[4+((8*EFS+4)/3)],p1[30],p2[30],v[2*EFS+1],m[32],c[64],t[32],cs[EGS],ds[EGS];
	octet S0={0,sizeof(s0),s0};
	octet S1={0,sizeof(s1),s1};
	octet W0={0,sizeof(w0),w0};
	octet W1={0,sizeof(w1),w1};
	octet Z0={0,sizeof(z0),z0};
	octet Z1={0,sizeof(z1),z1};
	octet RAW={0,sizeof(raw),raw};
	octet KEY={0,sizeof(key),key};
	octet SALT={0,sizeof(salt),salt};
	octet PW={0,sizeof(pw),pw};
	octet P1={0,sizeof(p1),p1};
	octet P2={0,sizeof(p2),p2};
	octet V={0,sizeof(v),v};
	octet M={0,sizeof(m),m};
	octet C={0,sizeof(c),c};
	octet T={0,sizeof(t),t};
	octet CS={0,sizeof(cs),cs};
	octet DS={0,sizeof(ds),ds};

    ecp_domain epdom;
    csprng RNG;                /* Crypto Strong RNG */
                              
    RAW.len=100;				/* fake random seed source */
    for (i=0;i<100;i++) RAW.val[i]=i+1;

    CREATE_CSPRNG(&RNG,&RAW);   /* initialise strong RNG */

    SALT.len=8;
    for (i=0;i<8;i++) SALT.val[i]=i+1;  // set Salt

	printf("Alice's Passphrase= %s\n",pp);

	OCTET_JOIN_STRING(pp,&PW);   // set Password from string

/* First set up Elliptic Curve from ROM data */

    ECP_DOMAIN_INIT(&epdom,ecrom);

/* private key S0 of size EGS bytes derived from Password and Salt */

	PBKDF2(&PW,&SALT,1000,EGS,&S0);
	OCTET_TO_BASE64(&S0,b64);
	printf("Alices private key= %s\n",b64);

/* Generate Key pair S/W */

    ECP_KEY_PAIR_GENERATE(&epdom,NULL,&S0,&W0); 
    res=ECP_PUBLIC_KEY_VALIDATE(&epdom,TRUE,&W0);
    if (res!=0)
    {
        printf("ECP Public Key is invalid!\n");
        return 0;
    }
	OCTET_TO_BASE64(&W0,b64);
	printf("Alice's public key= %s\n",b64); 
	OCTET_FROM_BASE64(b64,&W0);

/* Random private key for other party */

	S1.len=3; S1.val[0]=0x01; S1.val[1]=0x23; S1.val[2]=0x45; 

    ECP_KEY_PAIR_GENERATE(&epdom,NULL,&S1,&W1);
    res=ECP_PUBLIC_KEY_VALIDATE(&epdom,TRUE,&W1);
    if (res!=0)
    {
        printf("ECP Public Key is invalid!\n");
        return 0;
    }
	OCTET_TO_BASE64(&W1,b64);
	printf("Servers public key= %s\n",b64); 
	OCTET_FROM_BASE64(b64,&W1);

/* Calculate common key using DH - IEEE 1363 method */

    ECPSVDP_DH(&epdom,&S0,&W1,&Z0);
    ECPSVDP_DH(&epdom,&S1,&W0,&Z1);
    
	if (!OCTET_COMPARE(&Z0,&Z1))
    {
        printf("*** ECPSVDP-DH Failed\n");
        return 0;
    }

	KDF1(&Z0,EAS,&KEY);
	printf("Alice's DH Key=  "); for (i=0;i<EAS;i++) printf("%u ",KEY.val[i]&0xff);
	printf("\n");
	printf("Servers DH Key=  "); for (i=0;i<EAS;i++) printf("%u ",KEY.val[i]&0xff);
	printf("\n");


	printf("Testing ECIES\n");

	P1.len=3; P1.val[0]=0x0; P1.val[1]=0x1; P1.val[2]=0x2; 
	P2.len=4; P2.val[0]=0x0; P2.val[1]=0x1; P2.val[2]=0x2; P2.val[3]=0x3; 

    M.len=17;
    for (i=0;i<=16;i++) M.val[i]=i;    /* fake a message */

	ECP_ECIES_ENCRYPT(&epdom,&P1,&P2,&RNG,&W1,&M,12,&V,&C,&T);

	printf("Ciphertext= \n");
	OCTET_TO_BASE64(&V,b64);
	printf("V= %s\n",b64);
	OCTET_FROM_BASE64(b64,&V);
	OCTET_TO_BASE64(&C,b64);
	printf("C= %s\n",b64);
	OCTET_FROM_BASE64(b64,&C);
	OCTET_TO_BASE64(&T,b64);
	printf("V= %s\n",b64);
	OCTET_FROM_BASE64(b64,&T);

	if (!ECP_ECIES_DECRYPT(&epdom,&P1,&P2,&V,&C,&T,&S1,&M))
	{
		printf("*** ECIES Decryption Failed\n");
		return 0;
	}
	else printf("Decryption succeeded\n");

	printf("Message is "); OCTET_OUTPUT(&M);


	printf("Testing ECDSA\n");

	if (ECPSP_DSA(&epdom,&RNG,&S0,&M,&CS,&DS)!=0)
	{
		printf("***ECDSA Signature Failed\n");
		return 0;
	}
	OCTET_TO_BASE64(&CS,b64);
	printf("Signature C = %s\n",b64);
	OCTET_FROM_BASE64(b64,&CS);
	OCTET_TO_BASE64(&DS,b64);
	printf("Signature D = %s\n",b64);
	OCTET_FROM_BASE64(b64,&DS);

	if (ECPVP_DSA(&epdom,&W0,&M,&CS,&DS)!=0)
	{
		printf("***ECDSA Verification Failed\n");
		return 0;
	}
	else printf("ECDSA Signature/Verification succeeded\n");

    ECP_DOMAIN_KILL(&epdom);

    KILL_CSPRNG(&RNG);
    return 0;
}


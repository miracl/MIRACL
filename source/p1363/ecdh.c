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

/* ECDH/ECIES/ECDSA Functions - see main program below */

/* Note that in production code miracl COMBA mechanism should be invoked for 2-3 times speed up */
/* Use this mirdef.h for 32-bit processor - note no assembly required

#define MR_LITTLE_ENDIAN
#define MIRACL 32
#define mr_utype int
#define mr_dltype long long  
#define mr_unsign64 unsigned long long
#define MR_IBITS 32
#define MR_LBITS 32
#define mr_unsign32 unsigned int
#define MR_ALWAYS_BINARY
#define MR_STATIC 8
#define MR_GENERIC_MT
#define MR_STRIPPED_DOWN
#define MR_NOSUPPORT_COMPRESSION
#define MR_SIMPLE_BASE
#define MR_SIMPLE_IO
#define MR_NOASM
#define MAXBASE ((mr_small)1<<(MIRACL-1))
#define MR_BITSINCHAR 8
*/

/* Use this mirdef.h for 64-bit processor 

#define MR_LITTLE_ENDIAN
#define MIRACL 64
#define mr_utype long long
#define mr_unsign64 unsigned long long
#define MR_IBITS 32
#define MR_LBITS 32
#define mr_unsign32 unsigned int
#define MR_ALWAYS_BINARY
#define MR_STATIC 4
#define MR_GENERIC_MT
#define MR_STRIPPED_DOWN
#define MR_NOSUPPORT_COMPRESSION
#define MR_SIMPLE_BASE
#define MR_SIMPLE_IO
#define MAXBASE ((mr_small)1<<(MIRACL-1))
#define MR_BITSINCHAR 8

*/

/* Link to these files 

mrcore.c
mrarth0.c
mrarth1.c
mrarth2.c
mrio1.c
mrgcd.c
mrxgcd.c
mrarth3.c
mrbits.c
mrmonty.c
mrcurve.c
mraes.c
mrshs256.c
mrstrong.c

For 64-bit build using Microsoft compiler mrmuldv.w64 must be included as well
For 64-bit build using Linux and Intel chips, mrmuldv.g64 must be included as well


To use COMBA speed-up, for 32-bit build add

#define MR_COMBA 8
#define MR_GENERALISED_MERSENNE
#define MR_SPECIAL

For 64-bit build add

#define MR_COMBA 4
#define MR_GENERALISED_MERSENNE
#define MR_SPECIAL


to mirdef.h

Also create mrcomba.c using MEX utility, and add mrcomba.c in build

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ecdh.h"

/* Elliptic Curve parameters - NIST P256 Curve */

#if MIRACL==64

const mr_small ecrom[]={
0xffffffffffffffff,0xffffffff,0x0,0xffffffff00000001,
0x3bce3c3e27d2604b,0x651d06b0cc53b0f6,0xb3ebbd55769886bc,0x5ac635d8aa3a93e7,
0xf3b9cac2fc632551,0xbce6faada7179e84,0xffffffffffffffff,0xffffffff00000000,
0xf4a13945d898c296,0x77037d812deb33a0,0xf8bce6e563a440f2,0x6b17d1f2e12c4247,
0xcbb6406837bf51f5,0x2bce33576b315ece,0x8ee7eb4a7c0f9e16,0x4fe342e2fe1a7f9b};

#endif

#if MIRACL==32

const mr_small ecrom[]={
0xffffffff,0xffffffff,0xffffffff,0x0,0x0,0x0,0x1,0xffffffff,
0x27d2604b,0x3bce3c3e,0xcc53b0f6,0x651d06b0,0x769886bc,0xb3ebbd55,0xaa3a93e7,0x5ac635d8,
0xfc632551,0xf3b9cac2,0xa7179e84,0xbce6faad,0xffffffff,0xffffffff,0x0,0xffffffff,
0xd898c296,0xf4a13945,0x2deb33a0,0x77037d81,0x63a440f2,0xf8bce6e5,0xe12c4247,0x6b17d1f2,
0x37bf51f5,0xcbb64068,0x6b315ece,0x2bce3357,0x7c0f9e16,0x8ee7eb4a,0xfe1a7f9b,0x4fe342e2};

#endif


static void hash(octet *p,int n,octet *x,octet *y,octet *w)
{
    int i,hlen,c[4];
    HASHFUNC sha;
    char hh[HASH_BYTES];

    hlen=HASH_BYTES;

    SHS_INIT(&sha);
    if (p!=NULL)
        for (i=0;i<p->len;i++) SHS_PROCESS(&sha,p->val[i]);
	if (n>0)
    {
        c[0]=(n>>24)&0xff;
        c[1]=(n>>16)&0xff;
        c[2]=(n>>8)&0xff;
        c[3]=(n)&0xff;
		for (i=0;i<4;i++) SHS_PROCESS(&sha,c[i]);
    }
    if (x!=NULL)
        for (i=0;i<x->len;i++) SHS_PROCESS(&sha,x->val[i]);    
    if (y!=NULL)
        for (i=0;i<y->len;i++) SHS_PROCESS(&sha,y->val[i]);    
	
       
    SHS_HASH(&sha,hh);
   
    OCTET_EMPTY(w);
    OCTET_JOIN_BYTES(hh,hlen,w);
    for (i=0;i<hlen;i++) hh[i]=0;
}


/* Hash octet p to octet w */

void HASH(octet *p,octet *w)
{
	hash(p,-1,NULL,NULL,w);
}

/* Initialise a Cryptographically Strong Random Number Generator from 
   an octet of raw random data */


void CREATE_CSPRNG(csprng *RNG,octet *RAW)
{
    strong_init(RNG,RAW->len,RAW->val,0L);
}

void KILL_CSPRNG(csprng *RNG)
{
    strong_kill(RNG);
}

BOOL HMAC(octet *m,octet *k,int olen,octet *tag)
{
/* Input is from an octet m        *
 * olen is requested output length in bytes. k is the key  *
 * The output is the calculated tag */
    int i,hlen,b;
	char h[HASH_BYTES],k0[HASH_BLOCK];
    octet H={0,sizeof(h),h};
	octet K0={0,sizeof(k0),k0};

    hlen=HASH_BYTES; b=HASH_BLOCK;
    if (olen<4 || olen>hlen) return FALSE;

    if (k->len > b) hash(k,-1,NULL,NULL,&K0);
    else            OCTET_COPY(k,&K0);

    OCTET_JOIN_BYTE(0,b-K0.len,&K0);

    OCTET_XOR_BYTE(0x36,&K0);

    hash(&K0,-1,m,NULL,&H);

    OCTET_XOR_BYTE(0x6a,&K0);   /* 0x6a = 0x36 ^ 0x5c */
    hash(&K0,-1,&H,NULL,&H);

    OCTET_EMPTY(tag);
    OCTET_JOIN_BYTES(H.val,olen,tag);

    return TRUE;
}

/* Key Derivation Functions */
/* Input octet z */
/* Output key of length olen */

void KDF1(octet *z,int olen,octet *key)
{
    char h[HASH_BYTES];
	octet H={0,sizeof(h),h};
    int counter,cthreshold;
    int hlen=HASH_BYTES;
  
    OCTET_EMPTY(key);

    cthreshold=MR_ROUNDUP(olen,hlen);

    for (counter=0;counter<cthreshold;counter++)
    {
        hash(z,counter,NULL,NULL,&H);
        if (key->len+hlen>olen) OCTET_JOIN_BYTES(H.val,olen%hlen,key);
        else                    OCTET_JOIN_OCTET(&H,key);
    }
}

void KDF2(octet *z,octet *p,int olen,octet *key)
{
/* NOTE: the parameter olen is the length of the output k in bytes */
    char h[HASH_BYTES];
	octet H={0,sizeof(h),h};
    int counter,cthreshold;
    int hlen=HASH_BYTES;
    
    OCTET_EMPTY(key);

    cthreshold=MR_ROUNDUP(olen,hlen);

    for (counter=1;counter<=cthreshold;counter++)
    {
        hash(z,counter,p,NULL,&H);
        if (key->len+hlen>olen)  OCTET_JOIN_BYTES(H.val,olen%hlen,key);
        else                     OCTET_JOIN_OCTET(&H,key);
    }
}

/* Password based Key Derivation Function */
/* Input password p, salt s, and repeat count */
/* Output key of length olen */

void PBKDF2(octet *p,octet *s,int rep,int olen,octet *key)
{
	int i,j,len,d=MR_ROUNDUP(olen,HASH_BYTES);
	char f[EFS],u[EFS];
	octet F={0,sizeof(f),f};
	octet U={0,sizeof(u),u};
	OCTET_EMPTY(key);

	for (i=1;i<=d;i++)
	{
		len=s->len;
		OCTET_JOIN_LONG(i,4,s);
		HMAC(s,p,EFS,&F);
		s->len=len;
		OCTET_COPY(&F,&U);
		for (j=2;j<=rep;j++)
		{
			HMAC(&U,p,EFS,&U);
			OCTET_XOR(&U,&F);
		}

		OCTET_JOIN_OCTET(&F,key);
	}
	OCTET_CHOP(key,olen,NULL);
}

/* AES encryption/decryption */

void AES_CBC_IV0_ENCRYPT(octet *k,octet *m,octet *c)
{ /* AES CBC encryption, with Null IV and key k */
  /* Input is from an octet string m, output is to an octet string c */
  /* Input is padded as necessary to make up a full final block */
    aes a;
	BOOL fin;
    int i,j,ipt,opt,ch;
    char buff[16];
    int padlen;

	OCTET_CLEAR(c);
	if (m->len==0) return;
    if (!aes_init(&a,MR_CBC,k->len,k->val,NULL)) return;

    ipt=opt=0;
    fin=FALSE;
    forever
    {
        for (i=0;i<16;i++)
        {
            if (ipt<m->len) buff[i]=m->val[ipt++];
            else {fin=TRUE; break;}
        }
        if (fin) break;
        aes_encrypt(&a,buff);
        for (i=0;i<16;i++)
            if (opt<c->max) c->val[opt++]=buff[i];
    }    

/* last block, filled up to i-th index */

    padlen=16-i;
    for (j=i;j<16;j++) buff[j]=padlen;
    aes_encrypt(&a,buff);
    for (i=0;i<16;i++)
        if (opt<c->max) c->val[opt++]=buff[i];
    aes_end(&a);
    c->len=opt;    
}

/* returns TRUE if all consistent, else returns FALSE */

BOOL AES_CBC_IV0_DECRYPT(octet *k,octet *c,octet *m)
{ /* padding is removed */
    aes a;
    int i,ipt,opt,ch;
    char buff[16];
    BOOL fin,bad;
    int padlen;
    ipt=opt=0;

    OCTET_CLEAR(m);
    if (c->len==0) return TRUE;
    ch=c->val[ipt++]; 
   
    if (!aes_init(&a,MR_CBC,k->len,k->val,NULL)) return FALSE;
    fin=FALSE;

    forever
    {
        for (i=0;i<16;i++)
        {
            buff[i]=ch;      
            if (ipt>=c->len) {fin=TRUE; break;}  
            else ch=c->val[ipt++];  
        }
        aes_decrypt(&a,buff);
        if (fin) break;
        for (i=0;i<16;i++)
            if (opt<m->max) m->val[opt++]=buff[i];
    }    
    aes_end(&a);
    bad=FALSE;
    padlen=buff[15];
    if (i!=15 || padlen<1 || padlen>16) bad=TRUE;
    if (padlen>=2 && padlen<=16)
        for (i=16-padlen;i<16;i++) if (buff[i]!=padlen) bad=TRUE;
    
    if (!bad) for (i=0;i<16-padlen;i++)
        if (opt<m->max) m->val[opt++]=buff[i];
 
    m->len=opt;
    if (bad) return FALSE;
    return TRUE;
}


/*** EC GF(p) primitives - support functions ***/
/* destroy the EC GF(p) domain structure */

void ECP_DOMAIN_KILL(ecp_domain *DOM)
{
	int i;
	for (i=0;i<EFS;i++)
	{
		DOM->Q[i]=0;
		DOM->A[i]=0;
		DOM->B[i]=0;
		DOM->Gx[i]=0;
		DOM->Gy[i]=0;
	}
	for (i=0;i<EGS;i++)
		DOM->R[i]=0;
}

/* Initialise the EC GF(p) domain structure
 * It is assumed that the EC domain details are obtained from ROM
 */

int ECP_DOMAIN_INIT(ecp_domain *DOM,const void *rom)
{ /* get domain details from ROM     */

    FILE *fp;
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,2*EFS,16);
#else
    miracl *mr_mip=mirsys(2*EFS,16);
#endif
    BOOL fileinput=TRUE;
    big q,r,gx,gy,a,b;
    int words,promptr,err,res=0;
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 6);
#else
    char mem[MR_BIG_RESERVE(6)];
    memset(mem,0,MR_BIG_RESERVE(6));
#endif
    
	DOM->nibbles=2*EFS;
	words=MR_ROUNDUP(EFS*8,MIRACL);

	if (mr_mip==NULL || mem==NULL) res= ECDH_OUT_OF_MEMORY;
    
    mr_mip->ERCON=TRUE;

    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        r=mirvar_mem(_MIPP_ mem, 3);
        gx=mirvar_mem(_MIPP_ mem, 4);
        gy=mirvar_mem(_MIPP_ mem, 5);

		promptr=0;
		init_big_from_rom(q,words,(const mr_small *)rom,words*5,&promptr);  /* Read in prime modulus q from ROM   */
		init_big_from_rom(b,words,(const mr_small *)rom,words*5,&promptr);  /* Read in curve parameter b from ROM */
 		init_big_from_rom(r,words,(const mr_small *)rom,words*5,&promptr);  /* Read in curve parameter r from ROM */
 		init_big_from_rom(gx,words,(const mr_small *)rom,words*5,&promptr);  /* Read in curve parameter gx from ROM */
		init_big_from_rom(gy,words,(const mr_small *)rom,words*5,&promptr);  /* Read in curve parameter gy from ROM */
		convert(_MIPP_ -3,a);
		add(_MIPP_ q,a,a);

		big_to_bytes(_MIPP_ EFS,q,DOM->Q,TRUE);
		big_to_bytes(_MIPP_ EFS,a,DOM->A,TRUE);
		big_to_bytes(_MIPP_ EFS,b,DOM->B,TRUE);
		big_to_bytes(_MIPP_ EGS,r,DOM->R,TRUE);
		big_to_bytes(_MIPP_ EFS,gx,DOM->Gx,TRUE);
		big_to_bytes(_MIPP_ EFS,gy,DOM->Gy,TRUE);
	}
#ifndef MR_STATIC
    memkill(_MIPP_ mem,6);
#else
    memset(mem,0,MR_BIG_RESERVE(6));
#endif
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Calculate a public/private EC GF(p) key pair. W=S.g mod EC(p),
 * where S is the secret key and W is the public key
 * If RNG is NULL then the private key is provided externally in S
 * otherwise it is generated randomly internally */

int ECP_KEY_PAIR_GENERATE(ecp_domain *DOM,csprng *RNG,octet* S,octet *W)
{
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,DOM->nibbles,16);
#else
	miracl *mr_mip=mirsys(DOM->nibbles,16);
#endif
    big q,a,b,r,gx,gy,s,wx,wy;
    epoint *G,*WP;
    int err,res=0;
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 9);
    char *mem1=(char *)ecp_memalloc(_MIPP_ 2);
#else
    char mem[MR_BIG_RESERVE(9)];
    char mem1[MR_ECP_RESERVE(2)];
    memset(mem,0,MR_BIG_RESERVE(9));
    memset(mem1,0,MR_ECP_RESERVE(2));
#endif
 
    if (mr_mip==NULL || mem==NULL || mem1==NULL) res= ECDH_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
 

    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        r=mirvar_mem(_MIPP_ mem, 3);
        gx=mirvar_mem(_MIPP_ mem, 4);
        gy=mirvar_mem(_MIPP_ mem, 5);
        s=mirvar_mem(_MIPP_ mem, 6);
        wx=mirvar_mem(_MIPP_ mem, 7);
        wy=mirvar_mem(_MIPP_ mem, 8);

		bytes_to_big(_MIPP_ EFS,DOM->Q,q);
		bytes_to_big(_MIPP_ EFS,DOM->A,a);
		bytes_to_big(_MIPP_ EFS,DOM->B,b);
		bytes_to_big(_MIPP_ EGS,DOM->R,r);
		bytes_to_big(_MIPP_ EFS,DOM->Gx,gx);
		bytes_to_big(_MIPP_ EFS,DOM->Gy,gy);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init_mem(_MIPP_ mem1,0);
        WP=epoint_init_mem(_MIPP_ mem1,1);
        epoint_set(_MIPP_ gx,gy,0,G);

        if (RNG!=NULL)
            strong_bigrand(_MIPP_ RNG,r,s);
        else
        {
			bytes_to_big(_MIPP_ S->len,S->val,s);
            divide(_MIPP_ s,r,r);
        }

        ecurve_mult(_MIPP_ s,G,WP);        
        epoint_get(_MIPP_ WP,wx,wy);
       
        if (RNG!=NULL) S->len=big_to_bytes(_MIPP_ 0,s,S->val,FALSE);
        
		W->len=2*EFS+1;	W->val[0]=4;
		big_to_bytes(_MIPP_ EFS,wx,&(W->val[1]),TRUE);
		big_to_bytes(_MIPP_ EFS,wy,&(W->val[EFS+1]),TRUE);
    }

#ifndef MR_STATIC
    memkill(_MIPP_ mem,9);
    ecp_memkill(_MIPP_ mem1,2);
#else
    memset(mem,0,MR_BIG_RESERVE(9));
    memset(mem1,0,MR_ECP_RESERVE(2));
#endif
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* validate an EC GF(p) public key. Set full=TRUE for fuller, 
 * but more time-consuming test */

int ECP_PUBLIC_KEY_VALIDATE(ecp_domain *DOM,BOOL full,octet *W)
{
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,DOM->nibbles,16);
#else
	miracl *mr_mip=mirsys(DOM->nibbles,16);
#endif
    big q,a,b,r,wx,wy;
    epoint *WP;
    BOOL valid;
    int err,res=0;
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 6);
    char *mem1=(char *)ecp_memalloc(_MIPP_ 1);
#else
    char mem[MR_BIG_RESERVE(6)];
    char mem1[MR_ECP_RESERVE(1)];
    memset(mem,0,MR_BIG_RESERVE(6));
    memset(mem1,0,MR_ECP_RESERVE(1));
#endif
 
    if (mr_mip==NULL || mem==NULL || mem1==NULL) res= ECDH_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    
    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        r=mirvar_mem(_MIPP_ mem, 3);
        wx=mirvar_mem(_MIPP_ mem, 4);
        wy=mirvar_mem(_MIPP_ mem, 5);


		bytes_to_big(_MIPP_ EFS,DOM->Q,q);
		bytes_to_big(_MIPP_ EFS,DOM->A,a);
		bytes_to_big(_MIPP_ EFS,DOM->B,b);
		bytes_to_big(_MIPP_ EGS,DOM->R,r);

		bytes_to_big(_MIPP_ EFS,&(W->val[1]),wx);
		bytes_to_big(_MIPP_ EFS,&(W->val[EFS+1]),wy);

        if (mr_compare(wx,q)>=0 || mr_compare (wy,q)>=0) res=ECDH_INVALID_PUBLIC_KEY; 
    }
    if (res==0)
    {
        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        WP=epoint_init_mem(_MIPP_ mem1,0);

        valid=epoint_set(_MIPP_ wx,wy,0,WP);

        if (!valid || WP->marker==MR_EPOINT_INFINITY) res=ECDH_INVALID_PUBLIC_KEY;
        if (res==0 && full)
        {
            ecurve_mult(_MIPP_ r,WP,WP);
            if (WP->marker!=MR_EPOINT_INFINITY) res=ECDH_INVALID_PUBLIC_KEY; 
        }
      
    }
#ifndef MR_STATIC
    memkill(_MIPP_ mem,6);
    ecp_memkill(_MIPP_ mem1,1);
#else
    memset(mem,0,MR_BIG_RESERVE(6));
    memset(mem1,0,MR_ECP_RESERVE(1));
#endif
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** P1363 EC GF(p) primitives ***/
/* See P1363 documentation for specification */

int ECPSVDP_DH(ecp_domain *DOM,octet *S,octet *WD,octet *Z)    
{
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,DOM->nibbles,16);
#else
	miracl *mr_mip=mirsys(DOM->nibbles,16);
#endif
    big q,a,b,s,wx,wy,z;
    BOOL valid;
    epoint *W;
    int err,res=0;
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 7);
    char *mem1=(char *)ecp_memalloc(_MIPP_ 1);
#else
    char mem[MR_BIG_RESERVE(7)];
    char mem1[MR_ECP_RESERVE(1)];
    memset(mem,0,MR_BIG_RESERVE(7));
    memset(mem1,0,MR_ECP_RESERVE(1));
#endif
 
    if (mr_mip==NULL || mem==NULL || mem1==NULL) res= ECDH_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
   
    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        s=mirvar_mem(_MIPP_ mem, 3);
        wx=mirvar_mem(_MIPP_ mem, 4);
        wy=mirvar_mem(_MIPP_ mem, 5);
        z=mirvar_mem(_MIPP_ mem, 6);

		bytes_to_big(_MIPP_ EFS,DOM->Q,q);
		bytes_to_big(_MIPP_ EFS,DOM->A,a);
		bytes_to_big(_MIPP_ EFS,DOM->B,b);

		bytes_to_big(_MIPP_ S->len,S->val,s);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        W=epoint_init_mem(_MIPP_ mem1,0);

		bytes_to_big(_MIPP_ EFS,&(WD->val[1]),wx);
		bytes_to_big(_MIPP_ EFS,&(WD->val[EFS+1]),wy);
       
        valid=epoint_set(_MIPP_ wx,wy,0,W);

        if (!valid) res=ECDH_ERROR;
	}
	if (res==0)
	{
        ecurve_mult(_MIPP_ s,W,W);
        if (W->marker==MR_EPOINT_INFINITY) res=ECDH_ERROR; 
        else
        {
            epoint_get(_MIPP_ W,z,z);
			Z->len=big_to_bytes(_MIPP_ EFS,z,Z->val,TRUE);
        }
    }
#ifndef MR_STATIC
    memkill(_MIPP_ mem,7);
    ecp_memkill(_MIPP_ mem1,1);
#else
    memset(mem,0,MR_BIG_RESERVE(7));
    memset(mem1,0,MR_ECP_RESERVE(1));
#endif
 
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Sign octet F using private key S. Signature in C and D. Must supply RNG */

int ECPSP_DSA(ecp_domain *DOM,csprng *RNG,octet *S,octet *F,octet *C,octet *D)
{
	char h[HASH_BYTES];
	octet H={0,sizeof(h),h};
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,DOM->nibbles,16);
#else
	miracl *mr_mip=mirsys(DOM->nibbles,16);
#endif
    big q,a,b,gx,gy,r,s,f,c,d,u,vx;
    epoint *G,*V;
    int err,res=0;
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 12);
    char *mem1=(char *)ecp_memalloc(_MIPP_ 2);
#else
    char mem[MR_BIG_RESERVE(12)];
    char mem1[MR_ECP_RESERVE(2)];
    memset(mem,0,MR_BIG_RESERVE(12));
    memset(mem1,0,MR_ECP_RESERVE(2));
#endif
    if (mr_mip==NULL || mem==NULL || mem1==NULL) res= ECDH_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;

	hash(F,-1,NULL,NULL,&H); /* hash message */
    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        gx=mirvar_mem(_MIPP_ mem, 3);
        gy=mirvar_mem(_MIPP_ mem, 4);
        r=mirvar_mem(_MIPP_ mem, 5);
        s=mirvar_mem(_MIPP_ mem, 6);
        f=mirvar_mem(_MIPP_ mem, 7);
        c=mirvar_mem(_MIPP_ mem, 8);
        d=mirvar_mem(_MIPP_ mem, 9);
        u=mirvar_mem(_MIPP_ mem, 10);
        vx=mirvar_mem(_MIPP_ mem,11);

		bytes_to_big(_MIPP_ EFS,DOM->Q,q);
		bytes_to_big(_MIPP_ EGS,DOM->R,r);
		bytes_to_big(_MIPP_ EFS,DOM->Gx,gx);
		bytes_to_big(_MIPP_ EFS,DOM->Gy,gy);
		bytes_to_big(_MIPP_ EFS,DOM->A,a);
		bytes_to_big(_MIPP_ EFS,DOM->B,b);
		bytes_to_big(_MIPP_ S->len,S->val,s);
		bytes_to_big(_MIPP_ H.len,H.val,f);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init_mem(_MIPP_ mem1,0);
        V=epoint_init_mem(_MIPP_ mem1,1);
        epoint_set(_MIPP_ gx,gy,0,G);

        do {
            if (mr_mip->ERNUM) break;
            strong_bigrand(_MIPP_ RNG,r,u);
           
            ecurve_mult(_MIPP_ u,G,V);        
            epoint_get(_MIPP_ V,vx,vx);

            copy(vx,c); 
            divide(_MIPP_ c,r,r);
            if (size(c)==0) continue;
            xgcd(_MIPP_ u,r,u,u,u);
            mad(_MIPP_ s,c,f,r,r,d);
            mad(_MIPP_ u,d,u,r,r,d);
  
        } while (size(d)==0);
       
        if (res==0)
        {
			C->len=big_to_bytes(_MIPP_ EGS,c,C->val,TRUE);
			D->len=big_to_bytes(_MIPP_ EGS,d,D->val,TRUE);
        }
    }
#ifndef MR_STATIC
    memkill(_MIPP_ mem,12);
    ecp_memkill(_MIPP_ mem1,2);
#else
    memset(mem,0,MR_BIG_RESERVE(12));
    memset(mem1,0,MR_ECP_RESERVE(2));
#endif

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Verify Signature (C, D) on F using public key W */

int ECPVP_DSA(ecp_domain *DOM,octet *W,octet *F, octet *C,octet *D)
{
	char h[HASH_BYTES];
	octet H={0,sizeof(h),h};
#ifdef MR_GENERIC_AND_STATIC
	miracl instance;
	miracl *mr_mip=mirsys(&instance,DOM->nibbles,16);
#else
	miracl *mr_mip=mirsys(DOM->nibbles,16);
#endif
    big q,r,a,b,gx,gy,wx,wy,f,c,d,h2;
    int bit,err,res=0;
    epoint *G,*WP,*P;
    BOOL compressed,valid; 
#ifndef MR_STATIC
    char *mem=(char *)memalloc(_MIPP_ 12);
    char *mem1=(char *)ecp_memalloc(_MIPP_ 3);
#else
    char mem[MR_BIG_RESERVE(12)];
    char mem1[MR_ECP_RESERVE(3)];
    memset(mem,0,MR_BIG_RESERVE(12));
    memset(mem1,0,MR_ECP_RESERVE(3));
#endif
    if (mr_mip==NULL || mem==NULL || mem1==NULL) res= ECDH_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;

 	hash(F,-1,NULL,NULL,&H); /* hash message */
    if (res==0)
    {
        q=mirvar_mem(_MIPP_ mem, 0);
        a=mirvar_mem(_MIPP_ mem, 1);
        b=mirvar_mem(_MIPP_ mem, 2);
        gx=mirvar_mem(_MIPP_ mem, 3);
        gy=mirvar_mem(_MIPP_ mem, 4);
        r=mirvar_mem(_MIPP_ mem, 5);
        wx=mirvar_mem(_MIPP_ mem, 6);
        wy=mirvar_mem(_MIPP_ mem, 7);
        f=mirvar_mem(_MIPP_ mem, 8);
        c=mirvar_mem(_MIPP_ mem, 9);
        d=mirvar_mem(_MIPP_ mem, 10);
        h2=mirvar_mem(_MIPP_ mem,11);

		bytes_to_big(_MIPP_ EFS,DOM->Q,q);
		bytes_to_big(_MIPP_ EGS,DOM->R,r);
		bytes_to_big(_MIPP_ EFS,DOM->Gx,gx);
		bytes_to_big(_MIPP_ EFS,DOM->Gy,gy);
		bytes_to_big(_MIPP_ EFS,DOM->A,a);
		bytes_to_big(_MIPP_ EFS,DOM->B,b);
		bytes_to_big(_MIPP_ C->len,C->val,c);
		bytes_to_big(_MIPP_ D->len,D->val,d);
		bytes_to_big(_MIPP_ H.len,H.val,f);
        
        if (size(c)<1 || mr_compare(c,r)>=0 || size(d)<1 || mr_compare(d,r)>=0) 
            res=ECDH_INVALID;
    }

    if (res==0)
    {
        xgcd(_MIPP_ d,r,d,d,d);
        mad(_MIPP_ f,d,f,r,r,f);
        mad(_MIPP_ c,d,c,r,r,h2);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init_mem(_MIPP_ mem1,0);
        WP=epoint_init_mem(_MIPP_ mem1,1);
        P=epoint_init_mem(_MIPP_ mem1,2);
        epoint_set(_MIPP_ gx,gy,0,G);

		bytes_to_big(_MIPP_ EFS,&(W->val[1]),wx);
		bytes_to_big(_MIPP_ EFS,&(W->val[EFS+1]),wy);
 
		valid=epoint_set(_MIPP_ wx,wy,0,WP);
       
        if (!valid) res=ECDH_ERROR;
        else
        {
            ecurve_mult2(_MIPP_ f,G,h2,WP,P);
            if (P->marker==MR_EPOINT_INFINITY) res=ECDH_INVALID;
            else
            {
                epoint_get(_MIPP_ P,d,d);
                divide(_MIPP_ d,r,r);
                if (mr_compare(d,c)!=0) res=ECDH_INVALID;
            }
        }
    }
#ifndef MR_STATIC
    memkill(_MIPP_ mem,12);
    ecp_memkill(_MIPP_ mem1,3);
#else
    memset(mem,0,MR_BIG_RESERVE(12));
    memset(mem1,0,MR_ECP_RESERVE(3));
#endif

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return ECDH_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return ECDH_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}


void ECP_ECIES_ENCRYPT(ecp_domain *DOM,octet *P1,octet *P2,csprng *RNG,octet *W,octet *M,int tlen,octet *V,octet *C,octet *T)
{ /* Inputs: Input params, random number generator, his public key, the message to be encrypted and the MAC length */
  /* Outputs: my one-time public key, the ciphertext and the MAC tag */

	int i,len;
	char z[EFS],vz[3*EFS+2],k[32],k1[16],k2[16],l2[8],u[EFS];
	octet Z={0,sizeof(z),z};
	octet VZ={0,sizeof(vz),vz};
	octet K={0,sizeof(k),k};
	octet K1={0,sizeof(k1),k1};
	octet K2={0,sizeof(k2),k2};
	octet L2={0,sizeof(l2),l2};
	octet U={0,sizeof(u),u};

    if (ECP_KEY_PAIR_GENERATE(DOM,RNG,&U,V)!=0) return;  /* one time key pair */
    if (ECPSVDP_DH(DOM,&U,W,&Z)!=0) return;     

    OCTET_COPY(V,&VZ);
    OCTET_JOIN_OCTET(&Z,&VZ);

	KDF2(&VZ,P1,EFS,&K);

/* split key into AES encryption key and MAC key */

	K1.len=K2.len=16;
    for (i=0;i<16;i++) {K1.val[i]=K.val[i]; K2.val[i]=K.val[16+i];} 

	AES_CBC_IV0_ENCRYPT(&K1,M,C);
	
	OCTET_JOIN_LONG((long)P2->len,8,&L2);

	len=C->len;
	OCTET_JOIN_OCTET(P2,C);
    OCTET_JOIN_OCTET(&L2,C);
	HMAC(C,&K2,tlen,T);
	C->len=len;
}

/* ECIES Decryption */

BOOL ECP_ECIES_DECRYPT(ecp_domain *DOM,octet *P1,octet *P2,octet *V,octet *C,octet *T,octet *U,octet *M)
{ /* Inputs: Input params, ciphertext triple V,C,T and recipients private key */
  /* Output: recovered plaintext M */

	int i,len;
	char z[EFS],vz[3*EFS+2],k[32],k1[16],k2[16],l2[8],tag[32];
	octet Z={0,sizeof(z),z};
	octet VZ={0,sizeof(vz),vz};
	octet K={0,sizeof(k),k};
	octet K1={0,sizeof(k1),k1};
	octet K2={0,sizeof(k2),k2};
	octet L2={0,sizeof(l2),l2};
	octet TAG={0,sizeof(tag),tag};

	if (ECPSVDP_DH(DOM,U,V,&Z)!=0) return FALSE;  

    OCTET_COPY(V,&VZ);
    OCTET_JOIN_OCTET(&Z,&VZ);

	KDF2(&VZ,P1,EFS,&K);

/* split key into AES decryption key and MAC key */

	K1.len=K2.len=16;
    for (i=0;i<16;i++) {K1.val[i]=K.val[i]; K2.val[i]=K.val[16+i];} 

	if (!AES_CBC_IV0_DECRYPT(&K1,C,M)) return FALSE;

	OCTET_JOIN_LONG((long)P2->len,8,&L2);

	len=C->len;
	OCTET_JOIN_OCTET(P2,C);
    OCTET_JOIN_OCTET(&L2,C);	
	HMAC(C,&K2,T->len,&TAG);
	C->len=len;

	if (!OCTET_COMPARE(T,&TAG)) return FALSE;
	
	return TRUE;

}


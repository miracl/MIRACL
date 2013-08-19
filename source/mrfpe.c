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
 * Implementation of BPS Format Preserving Encryption
 *
 * See "BPS: a Format Preserving Encryption Proposal" by E. Brier, T. Peyrin and J. Stern
 *
 * http://csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/bps/bps-spec.pdf
 *
 * Uses AES internally
 *
 * Author: M. Scott 2012
 */

#include <stdlib.h> 
#include "miracl.h"

/* Define this to activate test main program */
/* Link with mraes.c */
/* #define FPE_TEST */

#define UINT32 mr_unsign32 /* 32-bit unsigned type */
#define W 8 /* recommended number of rounds */
#define BLOCK_SIZE 16 /* 16 Byte Blocks - AES */
#define ENCRYPT 0
#define DECRYPT 1

static void unpack(UINT32 a,MR_BYTE *b)
{ /* unpack bytes from a word */
    b[0]=MR_TOBYTE(a);
    b[1]=MR_TOBYTE(a>>8);
    b[2]=MR_TOBYTE(a>>16);
    b[3]=MR_TOBYTE(a>>24);
}

/* Little Endian */

static int to_base_256(char *x,int len,int s,MR_BYTE *y)
{ /* x[] of length len to base s is converted to byte array y[] of length BLOCK_SIZE */
	int i,j,m;
	UINT32 c;

	for (i=0;i<BLOCK_SIZE;i++) y[i]=0;
	if (len==0) return 0;	

	m=1; y[0]=x[len-1];
	for (j=len-2;j>=0;j--)
	{ /* multiply by s */
		c=x[j];
		for (i=0;i<m;i++)
		{
			c+=(UINT32)y[i]*s;
			y[i]=c&0xff;
			c>>=8;
		}
		if (c>0) {m++; y[m-1]=c;}
	}
	
	return m;
}

/* Find max_b for chosen cipher and number base */

static int maxb(int s)
{
	MR_BYTE y[BLOCK_SIZE];
	int i,m,n,c;
	m=1; y[0]=1;
	for (n=0;;n++)
	{
		c=0;
		for (i=0;i<m;i++)
		{ /* multiply y by s */
			c+=(UINT32)y[i]*s;
			y[i]=c&0xff;
			c>>=8;
		}
		if (c>0) {m++; y[m-1]=c;}
		if (m==13) break;	/* greater than 2^96 for AES */
	}
	return 2*n;
}

static void from_base_256(int addsub,MR_BYTE *y,int len,int s,char *x)
{ /* y[] of length BLOCK_SIZE is added to or subtracted from base s array x[] of length len. */
	int i,m,n;
	UINT32 c,d;

	m=BLOCK_SIZE;
	n=0; c=0;
	forever
	{
		while (m>0 && y[m-1]==0) m--;
		d=0;
		for (i=m-1;i>=0;i--)
		{ /* divide y by s */
			d=(d<<8)+y[i];
			y[i]=d/s;
			d%=s;
		}
		if (addsub==ENCRYPT)
		{ /* ADD */
			d+=c+x[n]; c=0;
			if ((int)d>=s) 
				{c=1; x[n]=d-s;}
			else x[n]=d;
		}
		else
		{ /* SUB */
			d+=c; c=0;
			if ((UINT32)x[n]>=d) x[n]-=d;
			else
				{x[n]+=(s-d); c=1;}
		}
		n++;
		if (n>=len) break;
	}
}

/* AES instance must be initialised and passed */
/* Format Preserving Encryption/Decryption routine */
/* Array x of length len to base s is encrypted/decrypted in place */

static void BC(int crypt,char *x,int len,int s,aes *a,UINT32 TL,UINT32 TR)
{
	int i,j;
	char *left,*right;
	MR_BYTE buff[BLOCK_SIZE];
	int l,r;
	l=r=len/2;
	if (len%2==1) l++;

	left=&x[0]; right=&x[l];

	for (i=0;i<W;i++)
	{
		if (crypt==ENCRYPT) j=i;
		else j=W-i-1;
		if (j%2==0)
		{
			to_base_256(right,r,s,buff);
			unpack(TR^j,&buff[12]);
			aes_ecb_encrypt(a,buff);
			from_base_256(crypt,buff,l,s,left);
		}
		else
		{
			to_base_256(left,l,s,buff);
			unpack(TL^j,&buff[12]);
			aes_ecb_encrypt(a,buff);
			from_base_256(crypt,buff,r,s,right);
		}
	}
}

/* Algorithm 3 */

/* x is an array of length len of numbers to the base s */
/* a is an initialised AES instance  */
/* TL and TR are 32-bit tweak values */
/* x is replaced in place by encrypted values. The format of x[] is preserved */

void FPE_encrypt(int s,aes *a,UINT32 TL,UINT32 TR,char *x,int len)
{
	int i,j,c,rest,mb=maxb(s);
	if (len<=mb)
	{
		BC(ENCRYPT,x,len,s,a,TL,TR);
		return;
	}
	rest=len%mb;
	c=0; i=0;
	while (len-c>mb)
	{
		if (i!=0) for (j=c;j<c+mb;j++) x[j]=(x[j]+x[j-mb])%s;
		BC(ENCRYPT,&x[c],mb,s,a,TL^(i<<16),TR^(i<<16));
		c+=mb; i++;
	}
	if (len!=c)
	{
		for (j=len-rest;j<len;j++)
			x[j]=(x[j]+x[j-mb])%s;
		BC(ENCRYPT,&x[len-mb],mb,s,a,TL^(i<<16),TR^(i<<16));
	}
}

/* Algorithm 4 */

void FPE_decrypt(int s,aes *a,UINT32 TL,UINT32 TR,char *x,int len)
{
	int i,j,c,rest,mb=maxb(s);
	int b;
	if (len<=mb)
	{
		BC(DECRYPT,x,len,s,a,TL,TR);
		return;
	}
	rest=len%mb;
	c=len-rest; i=c/mb;
	if (len!=c)
	{
		BC(DECRYPT,&x[len-mb],mb,s,a,TL^(i<<16),TR^(i<<16));
		for (j=len-rest;j<len;j++)
			{b=(x[j]-x[j-mb])%s; if (b<0) x[j]=b+s; else x[j]=b;}
	}
	while (c!=0)
	{
		c-=mb; i--;
		BC(DECRYPT,&x[c],mb,s,a,TL^(i<<16),TR^(i<<16));
		if (i!=0) for (j=c;j<c+mb;j++) {b=(x[j]-x[j-mb])%s; if (b<0) x[j]=b+s; else x[j]=b;}
	}
}

/* Test Program */

#ifdef FPE_TEST

int main()
{
	int i,n;
	aes a;
	char key[16];
	char x[256];    /* any length... */
	UINT32 TL,TR;

	TR=0; /* random tweaks */
	TL=0xFFFFFFFF;

/* Set AES key */

	key[0]=0x01; key[1]=0x01; key[2]=0x01; key[3]=0x01; key[4]=0x01; key[5]=0x01; key[6]=0x01; key[7]=0x01;
	key[8]=0x01; key[9]=0x01; key[10]=0x01; key[11]=0x01; key[12]=0x01; key[13]=0x01; key[14]=0x01; key[15]=0x01;

	printf("aes key= ");
	for (i=0;i<16;i++)
		printf("%02x",(unsigned char) key[i]);
	printf("\n");

    aes_init(&a,MR_ECB,16,key,NULL);

	x[0]=1; x[1]=4; x[2]=2; x[3]=5; x[4]=6; x[5]=9; x[6]=8; x[7]=7;
	x[8]=2; x[9]=1; x[10]=5; x[11]=4; x[12]=6; x[13]=5; x[14]=3; x[15]=2;

/* Encrypt/decrypt short string */

	printf("Plaintext=\n");
	for (i=0;i<16;i++) printf("%d ",x[i]);
	printf("\n");
	FPE_encrypt(10,&a,TL,TR,x,16);

	printf("Ciphertext=\n");
	for (i=0;i<16;i++) printf("%d ",x[i]);
	printf("\n");
	FPE_decrypt(10,&a,TL,TR,x,16);

	printf("Plaintext=\n");
	for (i=0;i<16;i++) printf("%d ",x[i]);
	printf("\n");

	printf("maxb= %d\n",maxb(10));

/* Now encrypt/decrypt longer string */

	for (i=0;i<83;i++) x[i]=i%10;

	printf("Plaintext=\n");
	for (i=0;i<83;i++) printf("%d ",x[i]);
	printf("\n");

	FPE_encrypt(10,&a,TL,TR,x,83);

	printf("Ciphertext=\n");
	for (i=0;i<83;i++) printf("%d ",x[i]);
	printf("\n");

	FPE_decrypt(10,&a,TL,TR,x,83);

	printf("Plaintext=\n");
	for (i=0;i<83;i++) printf("%d ",x[i]);
	printf("\n");


n=97;
	for (i=0;i<n;i++) x[i]=i%10;

	printf("Plaintext=\n");
	for (i=0;i<n;i++) printf("%d ",x[i]);
	printf("\n");

	FPE_encrypt(10,&a,TL,TR,x,n);

	printf("Ciphertext=\n");
	for (i=0;i<n;i++) printf("%d ",x[i]);
	printf("\n");

	FPE_decrypt(10,&a,TL,TR,x,n);

	printf("Plaintext=\n");
	for (i=0;i<n;i++) printf("%d ",x[i]);
	printf("\n");

	return 0;
}

#endif

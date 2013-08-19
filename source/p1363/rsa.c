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
/* simplest possible secure rsa implementation */
/* Uses IEEE-1363 standard methods  */
/* See IEEE-1363 section 11.2 IFES, page 57 */
/* cl /O2 rsa.c p1363.c miracl.lib    */
 
#include <stdio.h>
#include "p1363.h"

int main()
{   
    int i,bytes,res;
    octet m,m1,c,e,raw;
    if_public_key pub;
    if_private_key priv;
    csprng RNG;  
                           /* some true randomness needed here */
    OCTET_INIT(&raw,100);  /* should be filled with 100 random bytes */

    CREATE_CSPRNG(&RNG,&raw);   /* initialise strong RNG */

    bytes=IF_KEY_PAIR(NULL,&RNG,1024,65537,&priv,&pub);
                                /* generate random public & private key */
    OCTET_INIT(&m,bytes);       /* allocate space for plaintext and ciphertext */
    OCTET_INIT(&m1,bytes);
    OCTET_INIT(&c,bytes);   OCTET_INIT(&e,bytes);

    OCTET_JOIN_STRING((char *)"Hello World\n",&m);

    EME1_ENCODE(&m,&RNG,1023,NULL,SHA256,&e); /* OAEP encode message m to e  */
                                              /* must be less than 1024 bits */

    IFEP_RSA(NULL,&pub,&e,&c);     /* encrypt encoded message */
    IFDP_RSA(NULL,&priv,&c,&m1);   /* ... and then decrypt it */

    EME1_DECODE(&m1,1023,NULL,SHA256,&m1);    /* decode it */

    OCTET_PRINT_STRING(&m1);       /* print out decrypted/decoded message */

    OCTET_KILL(&m); OCTET_KILL(&m1);   /* clean up afterwards */
    OCTET_KILL(&c); OCTET_KILL(&raw); OCTET_KILL(&e); 

    IF_PUBLIC_KEY_KILL(&pub);          /* kill the keys */
    IF_PRIVATE_KEY_KILL(&priv);
}


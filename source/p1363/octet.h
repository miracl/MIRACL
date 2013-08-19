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


#ifndef OCTET_H
#define OCTET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* portable representation of a big positive number */

typedef struct
{
    int len;
    int max;
    char *val;
} octet;

/* Octet string handlers */

extern void OCTET_OUTPUT(octet *);
extern void OCTET_OUTPUT_STRING(octet *);
extern void OCTET_CLEAR(octet *);
extern int  OCTET_COMPARE(octet *,octet *);
extern void OCTET_JOIN_STRING(char *,octet *);
extern void OCTET_JOIN_BYTES(char *,int,octet *);
extern void OCTET_JOIN_BYTE(int,int,octet *);
extern void OCTET_JOIN_OCTET(octet *,octet *);
extern void OCTET_XOR(octet *,octet *);
extern void OCTET_EMPTY(octet *);
extern void OCTET_PAD(int,octet *);
extern void OCTET_TO_BASE64(octet *,char *);
extern void OCTET_FROM_BASE64(char *,octet *);
extern void OCTET_COPY(octet *,octet *);
extern void OCTET_XOR_BYTE(int,octet *);
extern void OCTET_CHOP(octet *,int,octet *);
extern void OCTET_JOIN_LONG(long,int,octet *);

#endif

/*
	RSA.H - header file for RSA.C

    Copyright (c) J.S.A.Kapp 1994 - 1996.

	RSAEURO - RSA Library compatible with RSAREF 2.0.

	All functions prototypes are the Same as for RSAREF.
	To aid compatiblity the source and the files follow the
	same naming comventions that RSAREF uses.  This should aid
        direct importing to your applications.

	This library is legal everywhere outside the US.  And should
	NOT be imported to the US and used there.

	RSA Routines Header File.

	Revision 1.00 - JSAK.
*/
#ifndef _RSA_H_
#define _RSA_H_
#include "global.h"
#include "rsaeuro.h"

UTIL_API int RSAPublicEncrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PUBLIC_KEY *, R_RANDOM_STRUCT *));
UTIL_API int RSAPrivateEncrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PRIVATE_KEY *));
UTIL_API int RSAPublicDecrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PUBLIC_KEY *));
UTIL_API int RSAPrivateDecrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PRIVATE_KEY *));

#endif
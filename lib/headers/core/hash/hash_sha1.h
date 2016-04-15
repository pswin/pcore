//##############################################################################
//#	title:	SHA
//#	c-date:	Oct-26-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _DGE_HASH_SHA_H
#define _DGE_HASH_SHA_H

#include <QtGlobal>

struct SHA1_CTX
{
	quint32	state[5];
	quint32	count[2];
	quint8	buffer[64];
};

#define SHA1_DIGEST_SIZE 20

void SHA1_Init( SHA1_CTX* context );
void SHA1_Update( SHA1_CTX* context, const quint8* data, const size_t len );
void SHA1_Final( SHA1_CTX* context, quint8 digest[SHA1_DIGEST_SIZE] );

void sha1_32a( const void * key, int len, quint32 seed, void * out );

#endif // _DGE_HASH_SHA_H

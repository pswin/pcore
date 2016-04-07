//##############################################################################
//#	title:	CRC32
//#	c-date:	Oct-26-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _DGE_HASH_CRC32_H
#define _DGE_HASH_CRC32_H

#include "include/pcore/pcore_def.h"
#include <QtGlobal>

PCORE_FORCE_INLINE quint32 hash_crc32( const uchar* key, int len, quint32 seed );


#endif // _DGE_HASH_CRC32_H

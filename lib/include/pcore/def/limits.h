//##############################################################################
//#	title:	limits
//#	c-date:	Oct-19-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_LIMITS_H
#define _PCORE_LIMITS_H

#include <limits>

//=====================================
// constants
//=====================================

//! numerical types
#define PCORE_UINT_MAX		( UINT_MAX )	//! maximum unsigned int
#define PCORE_UINT_MIN		( 0x0 )			//! minimum unsigned int
#define PCORE_INT_MAX		( INT_MAX )		//! maximum singed int
#define PCORE_INT_MIN		( INT_MIN )		//! minimum signed int
#define PCORE_USHORT_MAX	( USHRT_MAX )	//! maximum unsigned short
#define PCORE_USHORT_MIN	( 0x0 )			//! minimum unsigned short
#define PCORE_SHORT_MAX		( SHRT_MAX )	//! maximum signed short
#define PCORE_SHORT_MIN		( SHRT_MIN )	//! minimum signed int
#define PCORE_ULONG_MAX		( ULONG_MAX )	//! maximum unsigned long
#define PCORE_ULONG_MIN		( 0x0 )			//! minimum unsigned long
#define PCORE_LONG_MAX		( LONG_MAX )	//! maximum signed long
#define PCORE_LONG_MIN		( LONG_MIN )	//! minimum signed long
#define PCORE_U_LONG_LONG_MAX	( ULLONG_MAX )	//! maximum unsigned long long
#define PCORE_U_LONG_LONG_MIN	( 0x0 )			//! minimum unsigned long long
#define PCORE_LONG_LONG_MAX	( LLONG_MAX )	//! maximum signed long long
#define PCORE_LONG_LONG_MIN	( LLONG_MIN )	//! minimum signed long long

//! bitwise types
#define PCORE_U64_MAX		( 0xffffffffffffffff )
#define PCORE_U32_MAX		( 0xffffffff )
#define PCORE_U16_MAX		( 0xffff )
#define PCORE_U8_MAX		( 0xff )


#endif _PCORE_LIMITS_H

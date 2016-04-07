//##############################################################################
//#	title:	macros, predefinitions 
//#	c-date:	Jan-01-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_MSVC_COMPILER_H
#define _PCORE_MSVC_COMPILER_H

#include "../config.h"
#include "arch.h"
#include "compiler.h"

#if PCORE_COMPILER == PCORE_COMPILER_MSVC

//=======================================
// disabling libc
//=======================================

#if PCORE_CONFIG_MEM_OVERRID_NEW_DELETE == PCORE_ENABLE
	#pragma comment(linker, "/nodefaultlib:libc.lib")
	#pragma comment(linker, "/nodefaultlib:libcd.lib")
#endif

//=======================================
// version info and version control
//=======================================

// version names
#define PCORE_MSVC_VER_1		800
#define PCORE_MSVC_VER_3		900
#define PCORE_MSVC_VER_4		1000
#define PCORE_MSVC_VER_4_2		1020
#define PCORE_MSVC_VER_5		1100
#define PCORE_MSVC_VER_6		1200
#define PCORE_MSVC_VER_7		1300
#define PCORE_MSVC_VER_7_1		1310	//! 2003
#define PCORE_MSVC_VER_8		1400	//! 2005
#define PCORE_MSVC_VER_9		1500	//! 2008
#define PCORE_MSVC_VER_10		1600	//! 2010
#define PCORE_MSVC_VER_11		1700	//! 2012
#define PCORE_MSVC_VER_12		1800	//!	2013
#define PCORE_MSVC_VER_14		1900	//! 2015

#define PCORE_MSVC_VER_2003	PCORE_MSVC_VER_7_1
#define PCORE_MSVC_VER_2005	PCORE_MSVC_VER_8
#define PCORE_MSVC_VER_2008	PCORE_MSVC_VER_9
#define PCORE_MSVC_VER_2010	PCORE_MSVC_VER_10
#define PCORE_MSVC_VER_2012	PCORE_MSVC_VER_11
#define PCORE_MSVC_VER_2013	PCORE_MSVC_VER_12
#define PCORE_MSVC_VER_2015 PCORE_MSVC_VER_14

//! compiler version
#define PCORE_COMPILER_VERSION	_MSC_VER

#if PCORE_COMPILER_VERSION < PCORE_MSVC_VER_2013
	#error "compiling PCORE failed, PCORE at least need Microsoft Visual studio 2012 for compiling"
#endif

#if PCORE_COMPILER_VERSION >= PCORE_MSVC_VER_2013
	#define PCORE_COMPILER_SUPPORT_CPP11_ALIAS PCORE_ENABLE
#endif

//=======================================
// sizes
//=======================================

#define PCORE_SIZE_CHAR		1
#define PCORE_SIZE_SHORT	2
#define PCORE_SIZE_INT		4
#define PCORE_SIZE_LONG		4
#define PCORE_SIZE_FLOAT	4
#define PCORE_SIZE_DOUBLE	8


#if PCORE_ARCH_WORD_SIZE == 32
	#define PCORE_SIZE_POINTER	4
#elif PCORE_ARCH_WORD_SIZE == 64
	#define PCORE_SIZE_POINTER	8
#endif

//=======================================
// type definition
//=======================================
/*
namespace PCORE
{
	//! type based definitions
	typedef unsigned char	byte_t;
	typedef unsigned char	uchar_t;
	typedef unsigned short	ushort_t;
	typedef unsigned int	uint_t;
	typedef unsigned long	ulong_t;

	//! size based type definitions
	typedef unsigned __int8		u8_t;
	typedef unsigned __int16	u16_t;
	typedef unsigned __int32	u32_t;
	typedef unsigned __int64	u64_t;

	typedef unsigned __int8		s8_t;
	typedef unsigned __int16	s16_t;
	typedef unsigned __int32	s32_t;
	typedef unsigned __int64	s64_t;

	//! pointers
	typedef void*	ptr_t;

	#if  PCORE_SIZE_POINTER == 8
		typedef u64_t	size_t;
	#else
		typedef u32_t	size_t;
	#endif

} // Pcore
*/

//=======================================
// warnings
//=======================================

#if PCORE_CONFIG_WARNINGS == PCORE_DISABLE
	#pragma warning(disable : 4049)
	#pragma warning(disable : 4996) // _CRT_SECURE_NO_WARNING
	#pragma warning(disable : 4244) // conversion to float, possible loss of data
	#pragma warning(disable : 4699) // creating precompiled header
	#pragma warning(disable : 4200) // Zero-length array item at end of structure, a VC-specific extension
	#pragma warning(disable : 4100) // unreferenced formal parameter
	#pragma warning(disable : 4514) // unreferenced inline function has been removed
	#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union
	#pragma warning(disable : 4710) // inline function not expanded
	#pragma warning(disable : 4714) // __forceinline function not expanded
	#pragma warning(disable : 4702) // unreachable code in inline expanded function
	#pragma warning(disable : 4711) // function selected for automatic inlining
	#pragma warning(disable : 4127) // Conditional expression is constant
	#pragma warning(disable : 4512) // assignment operator could not be generated
	#pragma warning(disable : 4245) // conversion from 'enum ' to 'unsigned long', signed/unsigned mismatch
	#pragma warning(disable : 4389) // signed/unsigned mismatch
	#pragma warning(disable : 4251) // needs to have dll-interface to be used by clients of class
	#pragma warning(disable : 4275) // non dll-interface class used as base for dll-interface class
	#pragma warning(disable : 4511) // copy constructor could not be generated
	#pragma warning(disable : 4284) // return type is not a UDT or reference to a UDT
	#pragma warning(disable : 4355) // this used in base initializer list
	#pragma warning(disable : 4291) // typedef-name '' used as synonym for class-name ''
	#pragma warning(disable : 4324) // structure was padded due to __declspec(align())
	#pragma warning(disable : 4996) // 'function': was declared deprecated
	#pragma warning(disable : 4800) // 'function': was declared deprecated
#endif


//=======================================
// macros
//=======================================

#define PCORE_INLINE			inline			//! inline function
#define PCORE_FORCE_INLINE	__forceinline	//! force to inline
#define PCORE_NO_INLINE		__declspec(noinline)	//!
#define PCORE_NAKED_FUNC		void _declspec(naked)	//! naked function ( without epilouge and prologue )

#if PCORE_CONFIG_SIMD == PCORE_ENABLE
	#define PCORE_ALIGN __declspec(align(16))
#else
	#define PCORE_ALIGN
#endif


//=======================================
// DLL import export
//=======================================

#ifdef PCORE_EXPORT
	//#define PCORE_API __declspec( dllexport )
	#define PCORE_API Q_DECL_EXPORT
#else
	// #define PCORE_API  __declspec( dllimport )
	#define PCORE_API  Q_DECL_IMPORT
#endif

#endif // PCORE_COMPILER == PCORE_COMPILER_MSVC
#endif // _PCORE_MSVC_COMPILER_H

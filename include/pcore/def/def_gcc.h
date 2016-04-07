//##############################################################################
//#	title:	macros, predefinations for gcc
//#	c-date:	Apr-01-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_GCC_COMPILER_H
#define _PCORE_GCC_COMPILER_H

#include "../config.h"
#include "arch.h"
#include "compiler.h"

#if PCORE_COMPILER == PCORE_COMPILER_GCC

	//=======================================
	// version info and version control
	//=======================================

	/*! converting format of version to VVRRPP
		V = Version
		R = Reversion
		P = Patch level
	*/

	#if defined(__GNUC_PATCHLEVEL__)
		#define PCORE_COMPILER_VERSION (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100 \
                            + __GNUC_PATCHLEVEL__)
	#else
		#define PCORE_COMPILER_VERSION (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100)
	#endif

	//! Versions
	#define PCORE_GCC_4_4		40400
	#define PCORE_GCC_4_5		40500
	#define PCORE_GCC_4_6		40600
	#define PCORE_GCC_4_7		40700
	#define PCORE_GCC_4_8		40800
	
	
	//! Checking for CPP11 (Cpp0x) support
	#if PCORE_COMPILER_VERSION >= PCORE_GCC_4_6
		#define PCORE_COMPILER_SUPPORT_CPP11_NULLPTR	PCORE_TRUE
	#endif
	
	#if PCORE_COMPILER_VERSION >= PCORE_GCC_4_7
		#define PCORE_COMPILER_SUPPORT_CPP11_ALIAS	PCORE_TRUE
	#endif

	/*! Version control
		PCORE use some C++11 (C++0x) features like as template alias that supported
		in g++ 4.7
	*/
	#if PCORE_COMPILER_VERSION < PCORE_GCC_4_7
		#error "Error: Compiling failed, PCORE at least need G++ 4.7 ."
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


	#if PCORE_ARCH_BIT == 32
		#define PCORE_POINTER_SIZE	4
	#elif PCORE_ARCH_BIT == 64
		#define PCORE_POINTER_SIZE	8
	#endif

	//=======================================
	// type defination
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
		typedef unsigned char		u8_t;
		typedef unsigned short		u16_t;
		typedef unsigned int		u32_t;
		typedef unsigned long long	u64_t;

		typedef unsigned char		s8_t;
		typedef unsigned short		s16_t;
		typedef unsigned int		s32_t;
		typedef unsigned long long	s64_t;

		//! pointers
		typedef void*	ptr_t;

		#if  PCORE_POINTER_SIZE == 8
			typedef unsigned long long	size_t;
		#else
			typedef unsigned int		size_t;
		#endif

	} // Pcore
	*/

	//=======================================
	// macros
	//=======================================

	#define PCORE_INLINE		inline										//! inline function
	#define PCORE_FORCE_INLINE	__inline __attribute__ ((always_inline))	//! force to inline
	#define PCORE_NO_INLINE		__attribute__ ((noinline))					//!
	#define PCORE_NAKED_FUNC	void __attribute__ ((naked))				//! naked function ( without epilouge and prologue )
	
	#if PCORE_CONFIG_SIMD == PCORE_ENABLE
		#define PCORE_ALIGN __attribute__ ((aligned (16)))
	#else
		#define PCORE_ALIGN
	#endif


	//=======================================
	// DLL import export
	//=======================================

	#ifdef PCORE_EXPORT
		//#define PCORE_API __attribute__ ((visibility("default"))) PCORE_ALIGN
		#define PCORE_API Q_DECL_EXPORT
	#else
		//#define PCORE_API __attribute__ ((visibility("default"))) PCORE_ALIGN
		#define PCORE_API Q_DECL_IMPORT
	#endif

#endif // PCORE_COMPILER == PCORE_COMPILER_GCC
#endif // _PCORE_GCC_COMPILER_H

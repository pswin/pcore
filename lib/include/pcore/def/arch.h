//##############################################################################
//#	title:	CPU Architecture
//#	c-date:	Apr-02-2014
//#	author: Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include <QtGlobal>

/*
 * As default useful macros provided, but for saftey and making them more
 * robust, Qt based macros added.
 */

#ifndef _PCORE_ARCH_H
#define _PCORE_ARCH_H

	//=====================================
	// Arch list
	//=====================================
	
	#define PCORE_ARCH_X86_32	1	//! X86
	#define PCORE_ARCH_X86_64	3	//! X86-64
	#define PCORE_ARCH_ARM_32	4	//!	ARM 32-bit
	#define PCORE_ARCH_ARM_64	4	//!	ARM 64-bit
	#define PCORE_ARCH_UNKNOWN	99,	//! Unknown architecture

	//=====================================
	// Big endian or little endian
	//=====================================

	#define PCORE_ARCH_BIG_ENDIAN		1
	#define PCORE_ARCH_LITTLE_ENDIAN	2

	#if Q_BYTE_ORDER == Q_BIG_ENDIAN
		#define PCORE_ARCH_ENDIAN PCORE_ARCH_BIG_ENDIAN
	#else
		#define PCORE_ARCH_ENDIAN PCORE_ARCH_LITTLE_ENDIAN
	#endif

	//=====================================
	// 
	//=====================================
	#if defined ( i386 ) || defined ( __i386 ) || defined ( __i386__ ) || \
		defined ( __i486__ ) || defined ( __i586__ ) || defined ( __i686__ ) || \
		defined ( _M_IX86 ) || defined ( _X86_ ) || defined (Q_PROCESSOR_X86_32)
			#define PCORE_ARCH PCORE_ARCH_I386
			#define PCORE_ARCH_WORD_SIZE	32
	#elif  defined ( __amd64__ ) || defined ( __amd64 ) || defined ( __x86_64__ )  ||\
		defined ( __x86_64 ) || defined ( _M_X64 ) || defined ( _M_AMD64 ) || \
		defined ( _M_IA64 ) || defined ( __ia64__ ) || defined ( _IA64 )  || \
		defined ( __IA64__ ) || defined ( __itanium__ ) || defined ( _M_IA64 )  || \
		defined ( _M_AMD64 ) || defined ( Q_PROCESSOR_X86_64 )
			#define PCORE_ARCH PCORE_ARCH_X86_64
			#define PCORE_ARCH_WORD_SIZE	64
	#elif defined ( __aarch64__ )
		#define PCORE_ARCH  PCORE_ARCH_ARM_64
		#define PCORE_ARCH_WORD_SIZE	64
	#elif defined ( __arm__ ) || defined ( __thumb__ ) || defined ( _M_ARM ) ||\
		defined ( _M_ARMT ) || defined ( Q_PROCESSOR_ARM )
			#define PCORE_ARCH PCORE_ARCH_ARM_32
			#define PCORE_ARCH_WORD_SIZE	32
	#else
		#define PCORE_ARCH PCORE_ARCH_UNKNOWN
		#error "Compiling PCore failed, Unknown architecture"
	#endif

#endif // _PCORE_ARCH_H

//##############################################################################
//#	title:	macros, predefinitions 
//#	c-date:	Jan-01-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_DEF_H
#define _PCORE_DEF_H

	//========================================
	//	includes
	//========================================
	
	#include "config.h"
	#include "def/const.h"
	#include "def/compiler.h"
	#include "def/arch.h"
	#include "def/os.h"
	#include "def/limits.h"
	

	//========================================
	// Version Information
	//========================================
	
	#define PCORE_VERSION_MAJOR		1
	#define PCORE_VERSION_MINOR		0
	#define PCORE_VERSION_PATCH		0
	#define PCORE_VERSION_SUFFIX	""
	#define PCORE_VERSION_NAME		"1.0.0"

	#define PCORE_VERSION	((PCORE_VERSION_MAJOR << 16) | \
							(PCORE_VERSION_MINOR << 8) | PCORE_VERSION_PATCH)


	//========================================
	// Compiler specific include
	//========================================

	#if PCORE_COMPILER == PCORE_COMPILER_MSVC
		#include "def/def_msvc.h"
	#elif PCORE_COMPILER == PCORE_COMPILER_GCC
		#include "def/def_gcc.h"
	#elif PCORE_COMPILER == PCORE_COMPILER_INTEL
		#include "def/def_intel.h"
	#else
		#error "asasas"
	#endif
	

	//==========================================
	// macros
	//==========================================

	#if defined ( _DEBUG ) || defined ( DEBUG ) || defined ( PCORE_DEBUG )
		#define PCORE_DEBUG_MODE PCORE_ENABLE
	#else
		#define PCORE_DEBUG_MODE PCORE_DISABLE
	#endif

	// string convector for constants
	#define PCORE_CHAR_STRING(__str) #__str

	// line number and file name
	#define PCORE_LINE_NUMBER  __LINE__
	#define PCORE_LINE_NUMBER_STR  QString ( PCORE_CHAR_STRING( __LINE__ ) )
	#define PCORE_FILE_NAME QString( __FILE__ )
	#define PCORE_FUNC_NAME QString( __FUNCTION__ )

	// extern
	#define PCORE_EXTERN( __type, __var ) extern "C" { PCORE_API extern __type __var; }
	
	// noop
	#define PCORE_NOOP(__assert_expr)

	// new line
	#define PCORE_NEW_LINE "\r\n"

#endif // _PCORE_DEF_H

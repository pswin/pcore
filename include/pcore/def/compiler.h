//##############################################################################
//#	title:	Compiler detection and version
//#	c-date:	Apr-02-2014
//#	author: Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_COMPILER_H
#define _PCORE_COMPILER_H

	#include <QtGlobal>

	#define PCORE_COMPILER_MSVC		1	// Microsoft Visual C++
	#define PCORE_COMPILER_GCC		2	// GNU C/C++ compilers
	#define PCORE_COMPILER_INTEL	3	// Intel C/C++ compiler
	#define PCORE_COMPILER_UNKNOWN	99	// Unknown compiler


	#if defined ( __GNUC__ ) || defined ( Q_CC_GNU )
		#define PCORE_COMPILER PCORE_COMPILER_GCC
	#elif defined ( _MSC_VER ) || defined ( Q_CC_MSVC )
		#define PCORE_COMPILER PCORE_COMPILER_MSVC
	#elif defined ( __INTEL_COMPILER ) || defined ( Q_CC_INTEL )
		#define PCORE_COMPILER PCORE_COMPILER_INTEL
	#else
		#error "Compiling PCore failed, Unknown compiler."
	#endif

#endif // _PCORE_COMPILER_H

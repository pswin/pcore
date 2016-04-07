//##############################################################################
//#	title:	CPU Architecture
//#	c-date:	Apr-02-2014
//#	author: Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_OS_H
#define _PCORE_OS_H

#include <QtGlobal>

	//=====================================
	// OS list
	//=====================================
	
	#define PCORE_OS_WINDOWS	1	//! Microsoft Windows
	#define PCORE_OS_LINUX		2	//! Linux
	#define PCORE_OS_MAC		3	//! OS X
	#define PCORE_OS_UNKNOWN	99	//! Unknown OS


	//=====================================
	// detection
	//=====================================
	
	#if defined ( _WIN32 ) || defined ( _WIN64 ) || defined ( __WIN32__ ) || \
		defined ( Q_OS_WIN )
			#define PCORE_OS PCORE_OS_WINDOWS
	#elif defined ( __linux__ ) || defined ( __gnu_linux__ ) ||\
		  defined ( Q_OS_LINUX)
			#define PCORE_OS PCORE_OS_LINUX
	#elif defined( __APPLE__ ) && defined( __MACH__ ) || defined( Q_OS_OSX )
		#define PCORE_OS PCORE_OS_MAC
	#else
		#define PCORE_OS PCORE_OS_UNKNOWN
		#error "Compiling Pcore failed, Unknown OS"
	#endif

#endif // _PCORE_OS_H

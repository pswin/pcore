//#############################################################################
//#	title:	compile-time configurations
//#	c-date:	Jan-01-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//#############################################################################

#ifndef _PCORE_CONFIG_H
#define _PCORE_CONFIG_H

#include "def/const.h"


/*=====================================
	General
=====================================*/


//! default setting file
#define PCORE_CONFIG_DEFAULT_SETTING_FILE "setting.ini"


/*=====================================
	Using Typedefs
=====================================*/

#define PCORE_CONFIG_USE_TYPEDEF PCORE_ENABLE

/*=====================================
	SIMD
	this macro can enable or disable 
	SIMD feature in engine
=====================================*/

#define PCORE_CONFIG_SIMD	PCORE_DISABLE


/*=====================================
	Warnings
	compilers warnings for MSVC
=====================================*/

#define PCORE_CONFIG_WARNINGS PCORE_DISABLE


/*=====================================
	Logger
=====================================*/

#define PCORE_DEFAULT_LOGGER PCore::Core::LoggerInterface::Type::QDebug


#endif // _PCORE_CONFIG_H

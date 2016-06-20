//##############################################################################
//#	title:	PCore exception system
//#	c-date:	Apr-15-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_EXCEPTION_H
#define _PCORE_EXCEPTION_H

#include "../pcore_def.h"
#include "../config.h"

#if PCORE_CONFIG_THROW_ERROR == PCORE_ENABLE
	#define PCORE_THROW_EXCEPTION( __type, __desc ) throw ( __type(__desc) );
#else
	#define PCORE_THROW_EXCEPTION( __type, __desc) PCORE_NOOP('');
#endif

#endif // _PCORE_EXCEPTION_H


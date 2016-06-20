//##############################################################################
//#									PCore
//#						Written by: Pouya Shahinfar (Pswin)
//#								http://www.pswin.ir
//##############################################################################

/*
 *	PCore is a library for creating applications based on Qt framework and
 *	PS-Technologies. This library include several class for faciliating
 *	application development, and creating an integrate interface for application
 *	that are developed by Pouya Shahinfar (Pswin).
 */
#ifndef _PCORE_H
#define _PCORE_H


//=====================================
// root
//=====================================

#include "root.h"


//=====================================
// core
//=====================================

#include "core/logger.h"
#include "core/profiler.h"
#include "core/exception.h"
#include "core/compressor.h"
#include "core/system_information.h"
#include "core/hr.h"


//=====================================
// globalization
//=====================================

#include "globalization/locale.h"
#include "globalization/date_parser.h"
#include "globalization/persian_calendar.h"
#include "globalization/hijri_calendar.h"


//=====================================
// cryptography
//=====================================

#include "cryptography/rsa.h"
#include "cryptography/aes.h"
#include "cryptography/des.h"


//=====================================
// math
//=====================================

#include "math/random.h"



#endif // _PCORE_H

//##############################################################################
//#	title:	Global variables
//#	c-date:	Feb-28-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

/*
 *	Diffrent frameworks use diffrent approaches for accessing singleton classes.
 *	Although, At first sight, using things such as singleton design pattern
 *	might look convenient, yet in PCore global variables are used. We suppose
 *	Since in the singlton design pattern for every access to the class's instace
 *	a static mthod is called, the performace of application tend to be decreased.
 *	Therefore, using global varibales would be more appropriate.
 *
 *	Almost all of the this varibales are initialized in Root::init. Hence this
 *	method should be called before using other classes of PCore; Otherwise, your
 *	application are likely to crash.
 */

#ifndef _PCORE_GLOBALS
#define _PCORE_GLOBALS

#include "pcore_def.h"

namespace PCore
{
	namespace core
	{
		class Logger;
		class ProfileManager;
	} // Logger

	class Root;
} // PCore



PCORE_EXTERN( PCore::core::Logger*, pLogger )
PCORE_EXTERN( PCore::core::ProfileManager*, pProfileManager )
PCORE_EXTERN( PCore::Root*, pRoot )


#endif // _PCORE_GLOBALS


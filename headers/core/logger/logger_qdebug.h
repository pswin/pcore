//##############################################################################
//#	title:	QDebug logger interface
//#	c-date:	Feb-28-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_LOGGER_QDEBUG_H
#define _PCORE_LOGGER_QDEBUG_H

#include "include/pcore/core/logger.h"


//==============================================================================
// LoggerQDebug
//==============================================================================
namespace PCore
{
	namespace core
	{
		class QDebugLogger : public LoggerInterface
		{
		public:

			//! constructor
			QDebugLogger ( QObject* _parent );

			//! logMessage
			virtual void logMessage( const LogMessage& _msg ) override;
		}; // LoggerQDebug
	} // core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PQDebugLogger = PCore::core::QDebugLogger;
#endif


#endif // _PCORE_LOGGER_QDEBUG_H


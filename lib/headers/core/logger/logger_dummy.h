//##############################################################################
//#	title:	Dummy logger
//#	c-date:	Feb-02-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_LOGGER_DUMMY_H
#define _PCORE_LOGGER_DUMMY_H

#include "include/pcore/core/logger.h"


//==============================================================================
// Dummy Logger
//==============================================================================

namespace PCore
{
	namespace core
	{
		class DummyLogger : public PCore::core::LoggerInterface
		{
			//=====================================
			// Metadata
			//=====================================
			Q_OBJECT

			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )


			//=====================================
			// public mthods
			//=====================================
		public:
			/*!
			 * \brief Constructor
			 * \param _parent: Pointer to the parent
			 */
			DummyLogger( QObject* _parent = nullptr )
						: LoggerInterface( Type::Dummy, _parent ){}

			/*!
			 * \brief Logs a message
			 * \param _msg: message
			 */
			virtual void logMessage( const LogMessage& _msg ) override {}

		}; // DummyLogger
	} // core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PDummyLogger = PCore::core::DummyLogger;
#endif

#endif // _PCORE_LOGGER_DUMMY_H


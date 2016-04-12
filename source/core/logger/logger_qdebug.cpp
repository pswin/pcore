//##############################################################################
//#	c-date:	Feb-28-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "headers/core/logger/logger_qdebug.h"
#include <QDebug>


#define PCORE_LOG_MESSAGE_FORMAT( __type, __msg ) \
	qDebug() << __type  << ": " << __msg.getMessage(); \
	for ( quint32 i = 0; i < __msg.getParamCount() ; i++ ) \
	{ \
		qDebug() << "\t\t* " << __msg.getParamByIndex( i ).key() << ": "<< __msg.getParamByIndex( i ).value().toString() ;\
	}

namespace PCore
{
	namespace core
	{
		//=====================================
		// constructor
		//=====================================
		QDebugLogger::QDebugLogger( QObject *_parent )
			: LoggerInterface( Type::QDebug, _parent )
		{

		}

		//=====================================
		// logMessage
		//=====================================
		void QDebugLogger::logMessage( const LogMessage& _msg )
		{
			switch ( _msg.getType() )
			{
			case LogMessage::Type::Critical:
				PCORE_LOG_MESSAGE_FORMAT( "Critical", _msg );
				break;
			case LogMessage::Type::Error:
				PCORE_LOG_MESSAGE_FORMAT( "Error", _msg );
				break;
			case LogMessage::Type::Information:
				PCORE_LOG_MESSAGE_FORMAT( "Information", _msg );
				break;
			case LogMessage::Type::Trace:
				PCORE_LOG_MESSAGE_FORMAT( "Trace", _msg );
				break;
			case LogMessage::Type::Warning:
				PCORE_LOG_MESSAGE_FORMAT( "Warning", _msg );
				break;
			default:
				break;
			}
		}




	} // core
} // PCore

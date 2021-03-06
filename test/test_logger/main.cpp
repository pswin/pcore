//##############################################################################
//#	title:	Logger test
//#	c-date:	Apr-15-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include <pcore/pcore.h>
#include <qdebug.h>

using namespace PCore::core;

int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// Loging using macros
	//=====================================

	// critical
	PCORE_LOG_CRITICAL( "This is a critical message." );

	// Error
	PCORE_LOG_ERROR( "This is an error message." );

	// Warning
	PCORE_LOG_WARNING( "This is a warning message." );

	// Info
	PCORE_LOG_INFO( "This is an info message." );

	// Trace
	PCORE_LOG_TRACE( "This is a trace message." );


	//=====================================
	// Loging by creating a log message
	//=====================================

	/*
	 * if you intend to send additional parameters with you log message, you
	 * should create LogMessage manually.
	 */

	// creating log message
	LogMessage msg;
	msg.setMessage( "This is a custom message" );
	msg.setParam( "param 1", 12 );
	msg.setParam( "param 2", "hi" );
	msg.setType( LogMessage::Type::Error );

	// loging it
	pLogger->log( msg );


	//=====================================
	// getting logger information
	//=====================================

	auto logger = pLogger->getLogger( LogMessage::Type::Error );

	qDebug() << "Type:" << logger->property( "type" );
	qDebug() << "Filename:" << logger->property( "filename" );


	//=====================================
	// changing logger file
	//=====================================

	logger->setProperty( "filename", "pcore2.log" );
	PCORE_LOG_ERROR( "Log test in new file." );

	return 0;
}



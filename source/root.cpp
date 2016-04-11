//##############################################################################
//#	c-date:	April-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include "include/pcore/root.h"
#include "include/pcore/globals.h"
#include "include/pcore/core/logger.h"
#include "include/pcore/core/profiler.h"
#include <QSettings>


namespace PCore
{

	//! constructor
	Root::Root( QObject* _parent )
			: QObject( _parent )
	{
		//PCORE_LOG_TRACE( "Root::Root called." );
	}

	//! init
	bool Root::init( const QString& _setting_file )
	{
		// creating an instance of logger
		pLogger = new PCore::core::Logger( _setting_file, this );

		PCORE_LOG_TRACE( "Root::init called." );

		// creating an instance of profile manager
		pProfileManager = new PCore::core::ProfileManager( this );


		PCORE_LOG_INFO( "PCore started successfully." );
		return true;
	}

	QString Root::getVersionString() const
	{
		return PCORE_VERSION_NAME;
	}

	//! getVersion
	QVersionNumber Root::getVersionNumber( void ) const
	{
		return QVersionNumber(	PCORE_VERSION_MAJOR,
								PCORE_VERSION_MINOR,
								PCORE_VERSION_PATCH
							);
	}

} // PCore


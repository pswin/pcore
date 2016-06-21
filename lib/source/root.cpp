//##############################################################################
//#	c-date:	April-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================
#include "include/pcore/root.h"
#include "include/pcore/globals.h"
#include "include/pcore/core/logger.h"
#include "include/pcore/core/profiler.h"
#include "headers/cryptography/cryptography_engine.h"
#include <QSettings>

#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
	#include <QVersionNumber>
#endif


//==============================================================================
// static members
//==============================================================================

static QByteArray NullQByteArray = QByteArray();


//==============================================================================
// codes
//==============================================================================
namespace PCore
{

	//! constructor
	Root::Root( QObject* _parent )
			: QObject( _parent )
	{
		pRoot = this;
	}

	//! init
	bool Root::init( const QString& _setting_file )
	{
		// creating an instance of logger
		pLogger = new PCore::core::Logger( _setting_file, this );

		PCORE_LOG_TRACE( "Root::init called." );


		if ( PCore::cryptography::CryptographyEngine::init() == false )
		{
			PCORE_LOG_ERROR( "Initializing cryptography engine failed." );
		}

		// creating an instance of profile manager
		pProfileManager = new PCore::core::ProfileManager( this );


		PCORE_LOG_INFO( "PCore started successfully." );
		return true;
	}


	//! shutdown
	bool Root::shutdown()
	{
		if ( PCore::cryptography::CryptographyEngine::shutdown() == false )
		{
			PCORE_LOG_ERROR( "Shutdowning cryptography engine failed." );
		}

		return true;
	}


	//! getVersionString
	QString Root::getVersionString() const
	{
		return PCORE_VERSION_NAME;
	}

	#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
		//! getVersionNumber
		QVersionNumber Root::getVersionNumber( void ) const
		{
			return QVersionNumber(	PCORE_VERSION_MAJOR,
									PCORE_VERSION_MINOR,
									PCORE_VERSION_PATCH
								);
		}
	#endif // QT 5.6

} // PCore


//##############################################################################
//#	c-date:	April-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include "include/pcore/root.h"
#include "include/pcore/globals.h"
#include "include/pcore/core/logger.h"
#include <QSettings>


namespace PCore
{

	//! constructor
	Root::Root( QObject* _parent )
			: QObject( _parent )
	{

	}

	//! init
	bool Root::init( const QString& _setting_file )
	{
		// creating an instance of logger
		pLogger = new PCore::core::Logger( _setting_file, this );


		return true;
	}

} // PCore


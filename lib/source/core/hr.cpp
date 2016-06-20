//##############################################################################
//#
//#
//##############################################################################


#include "include/pcore/core/hr.h"
#include <QString>


namespace PCore
{
	namespace core
	{

		//! byteToString
		QString HumanReadable::byteToString( quint64 _bytes, int _fraction )
		{
			if ( _bytes / PCORE_1TB >= 1 )
				return QString::number( _bytes / (double)PCORE_1TB, 'f', _fraction ) + " TB";
			else if ( _bytes / PCORE_1GB >= 1 )
				return QString::number( _bytes / (double)PCORE_1GB, 'f', _fraction ) + " GB";
			else if ( _bytes / PCORE_1MB >= 1 )
				return QString::number( _bytes / (double)PCORE_1MB, 'f', _fraction ) + " MB";
			else if ( _bytes / PCORE_1KB >= 1 )
				return QString::number( _bytes / (double)PCORE_1KB, 'f', _fraction ) + " KB";
			else
				return QString::number( _bytes );
		} // byteToString


		//! freqToString
		QString HumanReadable::freqToString( quint64 _freq, int _fraction )
		{
			if ( _freq / PCORE_1THZ >= 1 )
				return QString::number( _freq / (double)PCORE_1THZ, 'f', _fraction ) + " THz";
			else if ( _freq / PCORE_1GHZ >= 1 )
				return QString::number( _freq / (double)PCORE_1GHZ, 'f', _fraction ) + " GHz";
			else if ( _freq / PCORE_1MHZ >= 1 )
				return QString::number( _freq / (double)PCORE_1MHZ, 'f', _fraction ) + " MHz";
			else if ( _freq / PCORE_1KHZ >= 1 )
				return QString::number( _freq / (double)PCORE_1KHZ, 'f', _fraction ) + " KHz";
			else
				return QString::number( _freq );
		}

	} // core
} // PCore


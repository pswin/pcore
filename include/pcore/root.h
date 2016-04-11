//##############################################################################
//#	title:	Root class, use this class for initializing whole system
//#	c-date:	April-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_ROOT
#define _PCORE_ROOT

#include "pcore_def.h"
#include "config.h"
#include <QObject>
#include <QString>
#include <QVersionNumber>

namespace PCore
{
	class PCORE_API Root : public QObject
	{
		Q_OBJECT

	public:

		//! default constructor
		explicit Root( QObject* _parent = nullptr );


		/*!
		 * \brief initialize the core (Engine)
		 * \param _setting_file: Setting file name and path
		 * \return true if initialization was successful
		 */
		bool init( const QString& _setting_file
								= PCORE_CONFIG_DEFAULT_SETTING_FILE );


		/*!
		 * \brief Returns version number of PCore.
		 * \return Version number of PCore.
		 */
		QVersionNumber getVersionNumber( void ) const;


		/*!
		 * \brief Returns version of PCore in string.
		 * \return Version of PCore in string.
		 */
		QString getVersionString( void ) const;
	}; // Root
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PRoot			= PCore::Root;
#endif


#endif // _PCORE_ROOT


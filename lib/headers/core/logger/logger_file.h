//##############################################################################
//#	title:	File logger interface
//#	c-date:	Feb-29-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_LOGGER_FILE_H
#define _PCORE_LOGGER_FILE_H

#include "include/pcore/core/logger.h"
#include <QString>
#include <QFile>
#include <QTextStream>

//==============================================================================
// FileLogger
//==============================================================================

namespace PCore
{
	namespace core
	{
		class FileLogger : public LoggerInterface
		{
			//=====================================
			// Metadata
			//=====================================
			Q_OBJECT

			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )

			Q_PROPERTY(QString filename READ getFilename WRITE setFile )
			Q_PROPERTY(bool is_open READ isOpen )


			//=====================================
			// public methods
			//=====================================
		public:
			//! constructor
			FileLogger ( QObject* _parent );

			//! destructor
			~FileLogger();

			//! logMessage
			virtual void logMessage( const LogMessage& _msg ) override;

			/*!
			 * \brief returns output flie's name
			 * \return output files name
			 */
			QString getFilename( void ) const { return m_sFilename; }


			/*!
			 * \brief Sets output file
			 * \param _filename: filename of output file
			 */
			void setFile( const QString& _filename );


			/*!
			 * \brief returns true if log file is open
			 */
			bool isOpen( void ) const;


			/*!
			 * \brief Clear content of the file
			 */
			Q_INVOKABLE void clearContent( void );


			//=====================================
			// private members
			//=====================================
		private:
			//! pointer to the file class instance
			QFile*	m_pFile = nullptr;

			//! text stream
			QTextStream m_TextStream;

			//! name of file
			QString m_sFilename = "pcore.log";
		}; // FileLogger
	} // core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PFileLogger = PCore::core::FileLogger;
#endif


#endif // _PCORE_LOGGER_FILE_H


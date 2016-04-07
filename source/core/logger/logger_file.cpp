//##############################################################################
//#	title:	File logger interface
//#	c-date:	Feb-29-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "headers/core/logger_file.h"
#include <QDebug>
#include <QDateTime>

//==============================================================================
// FileLogger
//==============================================================================

#define __PCORE_LOGGER_FILE_HELPER( __type, __msg ) \
			m_TextStream <<  __type << ": " << QDateTime::currentDateTime().toString() << " | " << __msg.getMessage() << " | " ; \
			for ( int i = 0; i < __msg.getParamCount(); i++ )\
			{\
				auto it = __msg.getParamByIndex(i);\
				m_TextStream << it.key() << ": '" << it.value().toString() << "', ";\
			}\
			m_TextStream <<  "\r\n";


namespace PCore
{
	namespace core
	{

		//=====================================
		// constructor
		//=====================================
		FileLogger::FileLogger( QObject* _parent )
			: LoggerInterface( Type::File, _parent )
		{
			try
			{
				m_pFile = new QFile( m_sFilename, this );

				if ( m_pFile->open( QFile::OpenModeFlag::Append |
									QFile::OpenModeFlag::Text ) == false )
				{
					qDebug() << "File logger error in opening file: " << m_sFilename;
					return;
				}

				m_TextStream.setDevice( m_pFile );
			}
			catch ( ... )
			{
				qDebug() << "File logger error in opening file: " << m_sFilename;
			}
		}


		//=====================================
		// destructor
		//=====================================
		FileLogger::~FileLogger()
		{
			if ( m_pFile != nullptr )
			{
				if ( m_pFile->isOpen() == true ) m_pFile->close();
			}
		}


		//=====================================
		// logMessage
		//=====================================
		void FileLogger::logMessage( const LogMessage& _msg )
		{
			switch ( _msg.getType() )
			{
			case LogMessage::Type::Critical:
				__PCORE_LOGGER_FILE_HELPER( "Critical", _msg );
				break;
			case LogMessage::Type::Error:
				__PCORE_LOGGER_FILE_HELPER( "Error", _msg );
				break;
			case LogMessage::Type::Information:
				__PCORE_LOGGER_FILE_HELPER( "Information", _msg );
				break;
			case LogMessage::Type::Warning:
				__PCORE_LOGGER_FILE_HELPER( "Warning", _msg );
				break;
			case LogMessage::Type::Trace:
				__PCORE_LOGGER_FILE_HELPER( "Trace", _msg );
				break;
			}
			m_TextStream.flush();
		} // logMessage


		//=====================================
		// setFile
		//=====================================
		void FileLogger::setFile( const QString& _filename )
		{
			try
			{
				m_sFilename = _filename;

				if ( m_pFile->isOpen() )
				{
					m_pFile->close();
				}

				m_pFile->setFileName( m_sFilename );
				if ( m_pFile->open( QFile::OpenModeFlag::Append |
									QFile::OpenModeFlag::Text ) == false )
				{
					qDebug() << "File logger error in opening file: " << m_sFilename;
				}
			}
			catch ( ... )
			{
				qDebug() << "File logger error in opening file: " << m_sFilename;
			}
		}


		//=====================================
		// isOpen
		//=====================================
		bool FileLogger::isOpen() const
		{
			if ( m_pFile == nullptr ) return false;
			return m_pFile->isOpen();
		}

		//=====================================
		// clearContent
		//=====================================
		void FileLogger::clearContent()
		{
			m_pFile->resize( 0 );
		}

	} // core
} // PCore

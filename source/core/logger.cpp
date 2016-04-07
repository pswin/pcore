//##############################################################################
//#	c-date:	Feb-01-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include "include/pcore/core/logger.h"
#include "headers/core/logger_dummy.h"
#include "headers/core/logger_qdebug.h"
#include "headers/core/logger_file.h"
#include <QSettings>
#include <QDebug>


#define __PCORE_LOGGER_INIT_HELPER( __logger, __name, __definer ) \
		if ( __name == "file" ) \
		{ \
			QString file_name = settings.value( QString("logger/") + __definer + QString("_file"), "pbus.log" ).toString();\
			if ( m_mLoggers.find( file_name ) != m_mLoggers.end() ) \
			{ \
				__logger = m_mLoggers[file_name];\
			}\
			else\
			{\
				PFileLogger* file_logger = new PFileLogger( this );\
				file_logger->setFile( file_name );\
				m_mLoggers[file_name] = file_logger;\
				__logger = file_logger;\
			}\
		}\
		else if ( __name == "qdebug" )\
		{\
			__logger = m_mLoggers["__qdebug"];\
		}\
		else if ( __name == "dummy" )\
		{\
			__logger = m_mLoggers["__dummy"];\
		}\
		else \
		{ \
			__logger = m_mLoggers["__default"];\
		}



namespace PCore
{
	namespace core
	{

		//==============================================================================
		// Logger
		//==============================================================================

		//=====================================
		// constructor
		//=====================================
		PCore::core::Logger::Logger( QString _setting_file, QObject* _parent )
			: QObject( _parent )
		{
			// setting up default loggers
			m_mLoggers["__dummy"] = new PDummyLogger( this );
			m_mLoggers["__qdebug"] = new PQDebugLogger( this );
			m_mLoggers["__default"] = new PQDebugLogger( this );

			// Read from setting
			QSettings settings( _setting_file, QSettings::IniFormat );
			QString logger_critical = settings.value( "logger/critical_type", "file").toString();
			QString logger_error = settings.value( "logger/error_type", "file").toString();
			QString logger_warning = settings.value( "logger/warning_type", "file").toString();
			QString logger_information = settings.value( "logger/information_type", "file").toString();
			QString logger_trace = settings.value( "logger/trace_type", "qdebug").toString();

			// initiating loggers
			__PCORE_LOGGER_INIT_HELPER( m_pLoggerCritical, logger_critical, "critical" );
			__PCORE_LOGGER_INIT_HELPER( m_pLoggerError, logger_error, "error" );
			__PCORE_LOGGER_INIT_HELPER( m_pLoggerInfo, logger_information, "information" );
			__PCORE_LOGGER_INIT_HELPER( m_pLoggerTrace, logger_trace, "trace" );
			__PCORE_LOGGER_INIT_HELPER( m_pLoggerWarning, logger_warning, "warning" );

		}

		//=====================================
		// log
		//=====================================
		void PCore::core::Logger::log( const PCore::core::LogMessage& _msg )
		{
			switch ( _msg.getType() )
			{
			case PLogMessage::Type::Critical:
				m_pLoggerCritical->logMessage( _msg );
				break;
			case PLogMessage::Type::Error:
				m_pLoggerError->logMessage( _msg );
				break;
			case PLogMessage::Type::Information:
				m_pLoggerInfo->logMessage( _msg );
				break;
			case PLogMessage::Type::Trace:
				m_pLoggerTrace->logMessage( _msg );
				break;
			case PLogMessage::Type::Warning:
				m_pLoggerWarning->logMessage( _msg );
				break;
			}
		}

		//==============================================================================
		// Log Message
		//==============================================================================

		//=====================================
		// constructor
		//=====================================
		LogMessage::LogMessage( LogMessage::Type _type )
		{
			m_eType = _type;
		}


		//=====================================
		// constructor
		//=====================================
		LogMessage::LogMessage( const QString& _main_msg,
								LogMessage::Type _type )
		{
			m_sMainMessage = _main_msg;
			m_eType = _type;
		}


		//=====================================
		// constructor
		//=====================================
		LogMessage::LogMessage( const QString& _main_msg,
								const QString& _file_name,
								const QString& _func_name,
								int _line_number,
								LogMessage::Type _type)
		{
			m_sMainMessage = _main_msg;
			m_eType = _type;
			setParam( "filename", _file_name );
			setParam( "function", _func_name );
			setParam( "line number", _line_number );
		}


		//=====================================
		// constructor
		//=====================================
		LogMessage::LogMessage( const QString& _main_msg,
								LogMessage::ParamMap _params,
								LogMessage::Type _type)
		{
			m_sMainMessage = _main_msg;
			m_eType = _type;
			m_mParams = _params;
		}


		//=====================================
		// copy constructor
		//=====================================
		LogMessage::LogMessage( const LogMessage& _msg )
		{
			m_sMainMessage = _msg.m_sMainMessage;
			m_eType = _msg.m_eType;
			m_mParams = _msg.m_mParams;
		}


		//=====================================
		// copy constructor
		//=====================================
		LogMessage::~LogMessage()
		{

		}


		//=====================================
		// setParam
		//=====================================
		void LogMessage::setParam( const QString& _param_name,
								   const QVariant _param_value )
		{
			m_mParams[_param_name] = _param_value;
		}


		//=====================================
		// getParam
		//=====================================
		QVariant LogMessage::getParam(QString& _param_name) const
		{

			if ( m_mParams.find( _param_name) == m_mParams.end() )
			{
				return QVariant();
			}
			return m_mParams[_param_name];
		}


		//=====================================
		// getParam
		//=====================================
		LogMessage::ParamMapConstIterator LogMessage::getParamByIndex( int _index ) const
		{
			if ( _index >= m_mParams.count() )
			{
				return ParamMapConstIterator();
			}

			ParamMapConstIterator it2;
			int i = 0;
			for ( auto it = m_mParams.begin();  i <= _index ; it++, i++ )
			{
				it2 = it;
			}
			return it2;
		}


		//=====================================
		// getParamCount
		//=====================================
		quint32 LogMessage::getParamCount() const
		{
			return m_mParams.count();
		}


		//=====================================
		// hasParam
		//=====================================
		bool LogMessage::hasParam( const QString& _param_name) const
		{
			return m_mParams.find( _param_name ) != m_mParams.end();
		}


		//=====================================
		// removeParam
		//=====================================
		bool LogMessage::removeParam( const QString& _param_name )
		{
			return m_mParams.remove( _param_name ) >= 1;
		}


		//=====================================
		// clearParams
		//=====================================
		void LogMessage::clearParams()
		{
			m_mParams.clear();
		}

		// contructor

	} // core
} // PCore
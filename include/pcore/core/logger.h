//##############################################################################
//#	title:	Logger
//#	c-date:	Feb-01-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_LOGGR_H
#define _PCORE_LOGGR_H

#include <QString>
#include <QMap>
#include <QVariant>
#include "../pcore_def.h"
#include "../globals.h"
#include "../config.h"


//==============================================================================
// Macros
//==============================================================================


#define __PCORE_LOG_MESSAGE_HELPER( __msg, __type ) pLogger->log( \
			PLogMessage( __msg, __FILE__, __FUNCTION__, __LINE__, __type ) );
#define PCORE_LOG_CRITICAL( __msg ) __PCORE_LOG_MESSAGE_HELPER( __msg, PLogMessage::Type::Critical )
#define PCORE_LOG_ERROR( __msg )  __PCORE_LOG_MESSAGE_HELPER( __msg, PLogMessage::Type::Error )
#define PCORE_LOG_WARNING( __msg ) __PCORE_LOG_MESSAGE_HELPER( __msg, PLogMessage::Type::Warning )
#define PCORE_LOG_INFO( __msg ) __PCORE_LOG_MESSAGE_HELPER( __msg, PLogMessage::Type::Information )
#define PCORE_LOG_TRACE( __msg ) __PCORE_LOG_MESSAGE_HELPER( __msg, PLogMessage::Type::Trace )


namespace PCore
{
	namespace core
	{
		//======================================================================
		// LogMessage
		//======================================================================

		class PCORE_API LogMessage
		{
			//=====================================
			// metadata
			//=====================================

			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )

			//Q_PROPERTY( QString message READ getMessage WRITE setMessage )
			//Q_PROPERTY( Type type READ getType WRITE setType )

			//=====================================
			// enums
			//=====================================
		public:

			/*!
			 * \brief Type of messages
			 */
			enum class Type
			{
				Critical,	// Critical or fatal errors, in this type of errors, application should be stoped.
				Error,		// Error, in most of the cases, this type of errors, could be handled by application.
				Warning,	// Warnings
				Information,// Information
				Trace		// Trace, this type of messages are for tracing the operations of application
			};
			//Q_ENUMS( Type )


			//=====================================
			// typedefs
			//=====================================
		public:

			using ParamMap = QMap<QString,QVariant>;
			using ParamMapIterator = ParamMap::iterator;
			using ParamMapConstIterator = ParamMap::const_iterator;

			//=====================================
			// public methods
			//=====================================
		public:

			/*!
			 * \brief Default constructor
			 * \param _type: Type of message
			 */
			explicit LogMessage ( Type _type = Type::Error );

			/*!
			 * \brief Constructor with main message
			 * \param _main_msg: Main message
			 * \param _type: Type of message
			 */
			explicit LogMessage(
					const QString& _main_msg,
					Type _type = Type::Error
				);

			/*!
			 * \brief Constructor
			 * \param _main_msg: Main message.
			 * \param _file_name: name of file that error has accured in it.
			 * \param _func_name: name of function that error has accured in it.
			 * \param _line_number: Line number
			 * \param _type: Type of message
			 */
			LogMessage(
					const QString& _main_msg,
					const QString& _file_name,
					const QString& _func_name,
					int _line_number,
					Type _type = Type::Error
				);

			/*!
			 * \brief Constructor with additional params
			 * \param _main_msg: Main message
			 * \param _params: Additional params
			 * \param _type: Type of message
			 */
			LogMessage(
					const QString& _main_msg,
					ParamMap _params,
					Type _type = Type::Error
				);

			/*!
			 * \brief Copy constructor
			 */
			LogMessage( const LogMessage& _msg );

			/*!
			 * \brief Destructor.
			*/
			~LogMessage( );

			/*!
			 * \brief Sets main message.
			 * \param _msg: Message's content.
			 */
			void setMessage( const QString& _msg ){ m_sMainMessage = _msg; }

			/*!
			 * \brief Returns main message.
			 * \return Returns an string that contain main message.
			 */
			QString getMessage( void ) const { return m_sMainMessage; }

			/*!
			 * \brief Sets type of message.
			 */
			void setType( Type _type ) { m_eType = _type; }

			/*!
			 * \brief Returns type of message.
			 */
			Type getType( void ) const { return m_eType; }

			/*!
			 * \brief Sets a parameter.
			 * \param _param_name: Name of the parameter.
			 * \param _param_value: Value of the parameter.
			 */
			void setParam(
					const QString& _param_name,
					const QVariant _param_value
				);

			/*!
			 * \brief Returns value of the specified parameter.
			 * \param _param_name: Name of the parameter
			 */
			QVariant getParam( QString& _param_name ) const;


			/*!
			* \brief Returns value of the specified index.
			* \param _index: Index of parameter
			*/
			ParamMapConstIterator getParamByIndex( int _index ) const;


			/*!
			* \brief Returns number of parameters in param map.
			*/
			quint32 getParamCount( void ) const;


			/*!
			 * \brief Returns true if specified parameter exists.
			 * \param _param_name: name of the parameter.
			 */
			bool hasParam( const QString& _param_name ) const;

			/*!
			 * \brief Removes an parameter from parameters list.
			 * \param _param_name: name of parameter.
			 * \return Returns true if operations was successful.
			 */
			bool removeParam( const QString& _param_name );

			/*!
			 * \brief Clears all parameters from parameter list.
			 */
			void clearParams( void );


			//=====================================
			// private members
			//=====================================
		private:
			//! main message
			QString m_sMainMessage;
			//! params
			ParamMap m_mParams;
			//! type of message
			Type m_eType;

		}; // LogMessage


		//======================================================================
		// LoggerInterface
		//======================================================================

		class PCORE_API LoggerInterface : public QObject
		{
			//=====================================
			// metadata
			//=====================================
			Q_OBJECT
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )

			Q_PROPERTY( Type type READ getType )

			//=====================================
			// enums
			//=====================================
		public:

			/*!
			 * \brief Type of loggers
			 */
			enum class Type
			{
				File,		// Logs to file.
				Network,	// Logs on network.
				IODevice,	// Logs on an specified device.
				Dummy,		// Ignores log messages.
				QDebug,		// Uses qDebug for logging.
				Custom,		// Custom logger type.
			};
			Q_ENUMS( Type )


			//=====================================
			// public methods
			//=====================================
		public:

			/*!
			 * \brief Constructor.
			 * \param _type: Type of logger.
			 * \param _parent: Pointer to the parent class.
			 */
			explicit LoggerInterface(
						Type _type,
						QObject* _parent = nullptr
					): QObject( _parent ){ m_eType = _type; }

			/*!
			 * \brief Logs a message.
			 * \param _msg: Message
			 */
			virtual void logMessage( const LogMessage& _msg ) = 0;

			/*!
			 * \brief Retutns type of logger.
			 */
			Type getType( void ) const { return m_eType; }


			//=====================================
			// private members
			//=====================================
		private:
			Type m_eType;

		}; // LoggerInterface

		//======================================================================
		// Logger
		//======================================================================
		class PCORE_API Logger : public QObject
		{
			//=====================================
			// Metadata
			//=====================================
			Q_OBJECT
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )


			//=====================================
			// public methods
			//=====================================
		public:
			/*!
			 * \brief Constructor
			 */
			Logger( QString _setting_file ,QObject* _parent = nullptr );



			Q_INVOKABLE void log( const LogMessage& _msg );

			//=====================================
			// private members
			//=====================================
		private:

			//! pointer to the logger interfaces
			LoggerInterface* m_pLoggerCritical	= nullptr;
			LoggerInterface* m_pLoggerError		= nullptr;
			LoggerInterface* m_pLoggerWarning	= nullptr;
			LoggerInterface* m_pLoggerInfo		= nullptr;
			LoggerInterface* m_pLoggerTrace		= nullptr;

			//! pointer to the diffrent interfaces by name
			QMap<QString, LoggerInterface*> m_mLoggers;
		}; // Logger
	} // Core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PLogger			= PCore::core::Logger;
	using PLogMessage		= PCore::core::LogMessage;
	using PLoggerInterface	= PCore::core::LoggerInterface;
#endif

#endif // _PCORE_LOGGR_H


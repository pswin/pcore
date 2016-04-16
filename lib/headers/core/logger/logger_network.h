//##############################################################################
//#	title:	Network based logger
//#	c-date:	Apr-11-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_LOGGER_NETWORK_H
#define _PCORE_LOGGER_NETWORK_H

#include "include/pcore/pcore_def.h"
#include "include/pcore/core/logger.h"
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>


/*! Doc:
 *	NetworkLogger is a logger that sends messages throught network by using
 *	TCP-socket connection. the main advantage of this logger is you can trace
 *	your log messages on a remote computer or see them on local computer while
 *	application is running.
 *
 * Note:
 * IF there is not a valid TCP connection, the logger will ignore the messages.
 */


//==============================================================================
// NetworkLogger
//==============================================================================


namespace PCore
{
	namespace core
	{
		class NetworkLogger : public PCore::core::LoggerInterface
		{
			//=====================================
			// metadata
			//=====================================
			Q_OBJECT

			//! info
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )

			//! properties
			Q_PROPERTY( port_t port READ getPort WRITE setPort )
			Q_PROPERTY( QHostAddress host READ getHost WRITE setHost )
			Q_PROPERTY( bool is_connected READ isConnected )


			//=====================================
			// Typedes
			//=====================================
		public:

			//! Port number type
			using port_t = quint16;


			//=====================================
			// Public methods
			//=====================================
		public:

			/*!
			 * \brief Default constructor
			 * \param _host: Host address
			 * \param _port_number: Port
			 * \param _parent: Parent object
			 */
			NetworkLogger( const QHostAddress _host = PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_HOST,
						   const port_t _port = PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_PORT,
						   QObject* _parent = nullptr
						);


			/*!
			 * Destructor
			*/
			~NetworkLogger();


			/*!
			 * \brief Connect logger to the host.
			 * \return True if connection was successful or false in case of failture.
			 */
			bool connect( void );


			/*!
			 * \brief Returns true if it is connected to the server.
			 * \return True if it is connected to the server.
			 */
			bool isConnected( void ) const;



			/*!
			 * \brief Sets port number. if connection is open, it will close
			 *		that and opens a new one.
			 * \param _port Port.
			 * \return True if a new connection is created or port number is setted.
			 */
			bool setPort( port_t _port );


			/*!
			 * \brief Returns port number
			 * \return Port number
			*/
			port_t getPort( void ) const { return m_Port; }


			/*!
			 * \brief Sets host address. if connection is open, it will close
			 *		that and opens a new one.
			 * \param _port Port.
			 * \return True if a new connection is created or host address is setted.
			*/
			bool setHost( const QHostAddress& _host_addr );


			/*!
			 * \brief Returns address of host
			 * \return Address of host
			 */
			QHostAddress getHost( void ) const { return m_HostAddress; }


			//! logMessage
			virtual void logMessage( const LogMessage &_msg ) override;


			//=====================================
			// private members and methods
			//=====================================
		private:
			//! pointer to the socket instance
			QTcpSocket* m_pSocket = nullptr;

			//! port
			port_t m_Port = PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_PORT;

			//! host
			QHostAddress m_HostAddress = PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_HOST;

			//! lock for multithread protection
			QMutex m_Lock;

		}; // NetworkLogger
	} // core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PNetworkLogger = PCore::core::NetworkLogger;
#endif



#endif // _PCORE_LOGGER_NETWORK_H


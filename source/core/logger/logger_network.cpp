//##############################################################################
//#	title:	Network based logger
//#	c-date:	Apr-11-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "headers/core/logger/logger_network.h"
#include <QDataStream>

namespace PCore
{
	namespace core
	{
		//! Constructor
		NetworkLogger::NetworkLogger( const QHostAddress _host,
					   const port_t _port , QObject* _parent )
			: LoggerInterface( LoggerInterface::Type::Network, _parent )
		{
			m_HostAddress = _host;
			m_Port = _port;
		} // constructor


		//! Destructor
		NetworkLogger::~NetworkLogger()
		{
			if ( m_pSocket != nullptr )
			{
				if ( m_pSocket->isOpen() == true )
				{
					m_pSocket->disconnect();
				}
			}
		} // destructor


		//! connect
		bool NetworkLogger::connect( void )
		{
			if ( m_pSocket == nullptr )
			{
				m_pSocket = new QTcpSocket();
			}
			else
			{
				if ( m_pSocket->isOpen() == true )
				{
					m_pSocket->close();
				}
			}

			m_pSocket->connectToHost( m_HostAddress, m_Port );

			if ( m_pSocket->waitForConnected(
					 PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_WAIT_TIME ) == false )
			{
				PCORE_LOG_CORE_ERROR("NetworkLogger: connection to host :'" +
									 m_HostAddress.toString() + "'' on port" +
									 QString::number( m_Port ) + " Failed."
									 );
				return false;
			}

			return true;
		} // connect


		//! isConnected
		bool NetworkLogger::isConnected() const
		{
			if ( m_pSocket == nullptr ) return false;
			return m_pSocket->isOpen();
		}


		//! setPort
		bool NetworkLogger::setPort( NetworkLogger::port_t _port )
		{
			m_Port = _port;
			if ( isConnected() == true )
			{
				return connect( );
			}
			return true;

		}

		//! setHost
		bool NetworkLogger::setHost( const QHostAddress& _host_addr )
		{
			m_HostAddress = _host_addr;
			if ( isConnected() == true )
			{
				return connect( );
			}
			return true;
		}

		//! logMessage
		void NetworkLogger::logMessage( const LogMessage& _msg )
		{
			if ( m_pSocket == nullptr ) return;
			if ( m_pSocket->isOpen() == false ) return;
			QByteArray ar;
			QDataStream st( &ar, QIODevice::ReadWrite);

			st << (int)st.byteOrder() << (int)_msg.getType() <<
				  QVariant(_msg.getMessage()) << _msg.getParamCount();


			for ( quint32 i = 0; i < _msg.getParamCount(); i++ )
			{
				LogMessage::ParamMapConstIterator it = _msg.getParamByIndex( i );
				st << QVariant(it.key()) << it.value();
			}

			m_pSocket->write( ar );
			m_pSocket->flush();

		} // connect

	} // Core
} // PCore


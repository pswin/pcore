//##############################################################################
//#	c-date:	Apr-17-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include <headers/core/windows/win_wmi.h>
#include <include/pcore/core/logger.h>

#if PCORE_OS == PCORE_OS_WINDOWS


//==============================================================================
// global members
//==============================================================================

bool wmi_initialized = false;


//==============================================================================
// functions
//==============================================================================

// converting QString to BSTR
BSTR qstringToBstr( const QString &qstring )
{
		WCHAR* const pBuffer = new WCHAR[qstring.size()+1];
		qstring.toWCharArray(pBuffer);
		pBuffer[qstring.size()]=0;
		BSTR result = SysAllocString(pBuffer);
		delete [] pBuffer;
		return result;
}

//==============================================================================
// WMI Class
//==============================================================================
namespace PCore
{
	namespace core
	{
		namespace windows
		{
			//! constructor
			WMI::WMI()
			{

				HRESULT hr;
				if ( wmi_initialized == false )
				{
					//! initializing com
					hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );

					if ( hr == S_FALSE || hr == RPC_E_CHANGED_MODE )
					{
						// just ignore the case
					}
					else if ( FAILED( hr ) )
					{
						PCORE_LOG_ERROR( "COM initialization failed" );
						m_bInitialized = false;
						return;
					}


					// process-wide security context setup
					hr = CoInitializeSecurity( NULL,	// we're not a server
											   -1,		// we're not a server
											   NULL,
											   NULL,
											   RPC_C_AUTHN_LEVEL_DEFAULT,
											   RPC_C_IMP_LEVEL_IMPERSONATE,
											   NULL,
											   EOAC_NONE,
											   NULL
											);

					if ( hr == RPC_E_TOO_LATE )
					{
						// just igonre the case
					}
					else if ( FAILED( hr ) )
					{
						PCORE_LOG_ERROR( "Security initialization failed" );
						m_bInitialized = false;
						return;
					}

					// creating COM instance
					hr = CoCreateInstance(
										CLSID_WbemAdministrativeLocator,
										NULL,
										CLSCTX_INPROC_SERVER,
										IID_IWbemLocator,
										reinterpret_cast< void** >( &m_pLocator )
										);

					if ( FAILED( hr ) )
					{
						PCORE_LOG_ERROR( "Creating instace of locator failed." );
						m_bInitialized = false;
						return;
					}

					wmi_initialized == true;
				} // wmi_initialized
				else
				{
					hr = CoGetClassObject(
									CLSID_WbemAdministrativeLocator,
									CLSCTX_INPROC_SERVER, NULL,
									IID_IWbemLocator,
									reinterpret_cast< void** >( &m_pLocator )
								);

					if ( FAILED( hr ) )
					{
						PCORE_LOG_ERROR( "Getting instace of locator failed." );
						m_bInitialized = false;
						return;
					}
				}




				// connecting to local server
				hr = m_pLocator->ConnectServer( qstringToBstr( "root\\cimv2" ),
												NULL, NULL, NULL,
												WBEM_FLAG_CONNECT_USE_MAX_WAIT,
												NULL, NULL, &m_pService );

				if ( FAILED( hr ) )
				{
					PCORE_LOG_ERROR( "Connecting to local server failed." );
					m_bInitialized = false;
					return;
				}

				m_bInitialized = true;

			} // constructor


			//! executeQuery
			bool WMI::executeQuery( const QString& _query )
			{
				if ( m_bInitialized == false ) return false;

				HRESULT hr = m_pService->ExecQuery(
												 qstringToBstr( "WQL" ),
												 qstringToBstr( _query ),
												 WBEM_FLAG_FORWARD_ONLY,
												 NULL,
												 &m_pIterator
												);


				if ( FAILED(hr) )
				{
					PCORE_LOG_ERROR( "WMI: Executing query: '"+_query+"' failed." );
					m_pCurrentRow = nullptr;
					return false;
				}

				return true;
			} // executeQuery

			//! selectAll
			bool WMI::selectAll( const QString& _data_source )
			{
				if ( m_bInitialized == false ) return false;
				QString q = "SELECT * from " + _data_source;
				return this->executeQuery( q );
			}

			//! nextItem
			bool WMI::nextItem( void )
			{
				if ( m_bInitialized == false ) return false;

				ULONG ret_count = 0;
				HRESULT hr  = m_pIterator->Next(
									WBEM_INFINITE,
									1L,
									&m_pCurrentRow,
									&ret_count // Return count
									);

				if ( FAILED(hr) || ret_count == 0 )
				{
					m_pCurrentRow = nullptr;
					return false;
				}

				return true;
			} // nextItem

			//! getString
			QString WMI::getString( const QString& _col_name, bool* _sucsess )
			{
				if ( m_pCurrentRow == nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = false;
					return "";
				}

				_variant_t var;
				HRESULT hr = m_pCurrentRow->Get( qstringToBstr(_col_name),0, &var, NULL, NULL );

				if ( SUCCEEDED(hr)&& var.bstrVal != nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = true;
					return QString::fromUtf16((char16_t*)var.bstrVal);
				}

				return QString();
			} // getString


			//! getInt
			quint32 WMI::getInt( const QString& _col_name, bool* _sucsess )
			{
				if ( m_pCurrentRow == nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = false;
					return 0;
				}

				_variant_t var;
				HRESULT hr = m_pCurrentRow->Get( qstringToBstr(_col_name), 0, &var, NULL, NULL );

				if ( SUCCEEDED(hr) )
				{
					if ( _sucsess != nullptr ) *_sucsess = true;
					return (quint32)var.intVal;
				}

				return 0;
			} // getInt


			//! getShortInt
			quint16 WMI::getShortInt( const QString& _col_name, bool* _sucsess )
			{
				if ( m_pCurrentRow == nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = false;
					return 0;
				}

				_variant_t var;
				HRESULT hr = m_pCurrentRow->Get( qstringToBstr(_col_name), 0, &var, NULL, NULL );

				if ( SUCCEEDED(hr) )
				{
					if ( _sucsess != nullptr ) *_sucsess = true;
					return (quint16)var.intVal;
				}

				return 0;
			} // getShortInt


			//! getLongInt
			quint64 WMI::getLongInt( const QString& _col_name, bool* _sucsess )
			{
				if ( m_pCurrentRow == nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = false;
					return 0;
				}

				_variant_t var;
				HRESULT hr = m_pCurrentRow->Get( qstringToBstr(_col_name), 0, &var, NULL, NULL );


				if ( SUCCEEDED(hr) )
				{
					if ( _sucsess != nullptr ) *_sucsess = true;
					return (quint64)var.llVal;
				}

				return 0;
			} // getLongInt


			//! getDouble
			double WMI::getDouble( const QString& _col_name, bool* _sucsess )
			{
				if ( m_pCurrentRow == nullptr )
				{
					if ( _sucsess != nullptr ) *_sucsess = false;
					return 0;
				}

				_variant_t var;
				HRESULT hr = m_pCurrentRow->Get( qstringToBstr(_col_name), 0, &var, NULL, NULL );


				if ( SUCCEEDED(hr) )
				{
					if ( _sucsess != nullptr ) *_sucsess = true;
					return (double)var.dblVal;
				}

				return 0;
			} // getDouble


		} // windows
	} // core
} // PCore
#endif // PCORE_OS_WINDOWS


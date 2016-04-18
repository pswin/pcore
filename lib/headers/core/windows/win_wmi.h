//##############################################################################
//#	title:	an interface for facilitating use of MS Windows's WMI
//#	c-date:	Apr-17-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_WIN_WMI_H
#define _PCORE_WIN_WMI_H

#include "include/pcore/pcore_def.h"

#if PCORE_OS == PCORE_OS_WINDOWS


//==============================================================================
// headers
//==============================================================================

#ifndef _WIN32_DCOM
	#define _WIN32_DCOM
#endif

#include <windows.h>
#include <objbase.h>
#include <atlbase.h>
#include <wbemidl.h>
#include <comutil.h>


//==============================================================================
// classes
//==============================================================================

namespace PCore
{
	namespace core
	{
		namespace windows
		{
			class WMI
			{
				//=====================================
				// public members
				//=====================================
			public:
				//! constructor
				WMI();

				/*!
				 * \brief Execute a query and return true if it was successful.
				 * \param _str: The query which must be executed.
				 * \return True if execution of query was successful.
				 */
				bool executeQuery(const QString& _query );

				/*!
				 * \brief Select all item from specified data source
				 *		  by _data_source.
				 * \param _data_source: Name of data source.
				 * \return true if execution was successful.
				 */
				bool selectAll(const QString& _data_source );

				/*!
				 * \brief it will go to the next row of data if it was avilable.
				 * \return True if a new raw is abvilable.
				 */
				bool nextItem( void );


				/*!
				 * \brief return a string which is in current row and
				 *			specified column.
				 * \param _col_name: Name of column or class member.
				 * \param _sucsess: specifies getting value was successful or not.
				 * \return
				 */
				QString getString(
									const QString& _col_name,
									bool* _sucsess = nullptr
								);

				/*!
				 * \brief return a quint32 which is in current row and
				 *			specified column.
				 * \param _col_name: Name of column or class member.
				 * \param _sucsess: specifies getting value was successful or not.
				 * \return
				 */
				quint32 getInt(
									const QString& _col_name,
									bool* _sucsess = nullptr
								);

				/*!
				 * \brief return a quint16 which is in current row and
				 *			specified column.
				 * \param _col_name: Name of column or class member.
				 * \param _sucsess: specifies getting value was successful or not.
				 * \return
				 */
				quint16 getShortInt(
									const QString& _col_name,
									bool* _sucsess = nullptr
								);

				/*!
				 * \brief return a quint64 which is in current row and
				 *			specified column.
				 * \param _col_name: Name of column or class member.
				 * \param _sucsess: specifies getting value was successful or not.
				 * \return
				 */
				quint64 getLongInt(
									const QString& _col_name,
									bool* _sucsess = nullptr
								);


				/*!
				 * \brief return a double which is in current row and
				 *			specified column.
				 * \param _col_name: Name of column or class member.
				 * \param _sucsess: specifies getting value was successful or not.
				 * \return
				 */
				double getDouble(
									const QString& _col_name,
									bool* _sucsess = nullptr
								);

				//=====================================
				// private members
				//=====================================
			private:

				//! pointer to the iterator
				CComPtr< IEnumWbemClassObject > m_pIterator;

				//! pointer to the serice instance
				CComPtr< IWbemServices > m_pService;

				//! pointer to the locator
				CComPtr< IWbemLocator > m_pLocator;

				//! current row
				IWbemClassObject* m_pCurrentRow;

				//! is initialized?
				bool m_bInitialized = false;
			}; // WMI
		} // windows
	} // core
} // PCore

#endif // _PCORE_OS_WINDOWS
#endif // _PCORE_WIN_COM_H


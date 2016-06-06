//##############################################################################
//#	title:	Inforamtion classes that is needed of globalization are provided here
//#	c-date:	Jun-06-2016
//#	author:	Pouya Shahnfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_INFO_STRUCTS_H
#define _PCORE_INFO_STRUCTS_H

#include <QString>
#include <QLocale>
#include <QList>
#include <QTimeZone>


namespace PCore
{
	namespace globalization
	{

		//======================================================================
		// Country
		//======================================================================
		struct CountryInfo
		{
			QString				name;			//! Latin name of the country.
			QString				nameNative;		//! Native name of the counry.
			QString				alpha2;			//! ISO 3166-1 alpha-2 code.
			QString				alpha3;			//! ISO 3166-1 alpha-3 code.
			QString				nationality;	//! Nationality
			QString				currency;		//! ISO 4217:2015 based currency code.
			QList<QString>		languages;		//! A list of languages.
			QList<QString>		currencies;		//! A list of currencies.
			QList<QTimeZone>	timeZones;		//! A list of timezones
		}; // CountryInfo


		//======================================================================
		// Language
		//======================================================================
		struct Language
		{
			QString		code;		//! ISO 639-1 based code of the language
			QString		name;		//! Name of the language
			QString		name_native;//! Native name of the language
			QStringList is_macro;	//! is it a macro language or not?
		};


		//==================================================================
		// Currency
		//==================================================================
		struct Currency
		{
			QString code;		//! ISO 4217:2015 based code of currency.
			QString symbol;		//! Symbol of the currency
			QString name;		//! Name of the currency
			QString name_native;//! Native name of the currency
		};


		//==================================================================
		// DateSystem
		//==================================================================
		struct DateSystem
		{
			QString		m_sName;		//! Name of the calander
			QString		m_sNameNative;	//! Native name of the calander
			QString		m_sCountry;		//! Country code in ISO 3166
			QStringList	m_Months;		//! Months name
			QStringList	m_MonthsNative;	//! Native months name
			QStringList	m_Days;			//! Days name
			QStringList	m_DaysNative;	//! Native Days name
		};

	} // Globalization
} // PCore

#endif // _PCORE_INFO_STRUCTS_H

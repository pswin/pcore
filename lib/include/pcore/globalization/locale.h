//##############################################################################
//#	title:	This is a helper class for localization
//#	c-date:	Jun-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_LOCAL_INFO_H
#define _PCORE_LOCAL_INFO_H


//==============================================================================
// Include
//==============================================================================

#include "../pcore_def.h"
#include <QLocale>

/*
 *	Development of this class is postponed to the future
 */

class QString;
class QStringList;


//==============================================================================
// LocalInfo
//==============================================================================

namespace PCore
{
	namespace globalization
	{
		class PCORE_API Locale
		{

			//==================================================================
			// Country
			//==================================================================
		public:
			class PCORE_API Country
			{
				public:

				/*!
				 * \brief Returns name of the country
				 */
				QString getName( void ) const;
				QString name( void ) const;


				/*!
				 * \brief Returns native name of the country
				 */
				QString getNativeName( void ) const;
				QString nativeName( void ) const;


				/*!
				 * \brief Returns calendar system of the country.
				 */
				QString getCalendarSystem( void ) const;
				QString calendarSystem( void ) const;


				/*!
				 * \brief Returns a list of country's languages
				 */
				QStringList getLanguages( void ) const;
				QStringList languages( void ) const;


				/*!
				 * \brief Returns a list of country's currencies.
				 */
				QStringList getCurrencies( void ) const;
				QStringList currencies( void ) const;


				/*!
				 * \brief Returns nationality of the country.
				 */
				QString getNationality( void ) const;
				QString nationality( void ) const;


				/*!
				 * \brief Returns ISO 3166-1 alpha-2 code of the country.
				 */
				QString getAlpha2Code( void ) const;
				QString alpha2Code( void ) const;


				/*!
				 * \brief Returns ISO 3166-1 alpha-3 code of the country.
				 */
				QString getAlpha3Code( void ) const;
				QString alpha3Code( void ) const;


				private:
					//! Alpha 3 based code
					QString m_Alpha3Code;

			}; // country



			//==================================================================
			// Calendar
			//==================================================================
		public:
			class PCORE_API Calendar
			{
			public:

				/*!
				 * \brief Type of calendars
				 */
				enum class Type
				{
					PersianIran			= 0, //! Iranian calendar (Jalali).
					PersianAfghanistan	= 1, //! Afghanistan's calendar.
					Hijri				= 2, //! Hijri Calendar.
					Gregorian 			= 3, //! Gregorian
					Invalid				= -1
				};


				/*!
				 * \brief Days of week
				 */
				enum class Day
				{
					Saturday	= 0,
					Sunday		= 1,
					Monday		= 2,
					Tuesday		= 3,
					Wednesday	= 4,
					Thursday	= 5,
					Friday		= 6
				};


			public:

				/*!
				 * \brief Constructs a calendar object by specified type.
				 * \param _type
				 */
				explicit Calendar( Type _type );


				/*!
				 * \brief Returns name of the country
				 */
				QString getName( void ) const;
				QString name( void ) const;


				/*!
				 * \brief Returns native name of the country
				 */
				QString getNativeName( void ) const;
				QString nativeName( void ) const;


				/*!
				 * \brief Returns day name in English from given day number.
				 * \param _day: Day number.
				 */
				QString getDayName( int _day ) const;
				QString dayName( int _day ) const;


				/*!
				 * \brief Returns short from of the day name in English.
				 * \param _day: Day number.
				 */
				QString getDayNameShort( int _day ) const;
				QString dayNameShort( int _day ) const;


				/*!
				 * \brief Returns short from of the day name in native language
				 * \param _day: Day number.
				 */
				QString getDayNameShortNative( int _day ) const;
				QString dayNameShortNative( int _day ) const;


				/*!
				 * \brief Returns day name in native language from given day number.
				 * \param _day: Day number.
				 */
				QString getDayNameNative( int _day ) const;
				QString dayNameNative( int _day ) const;


				/*!
				 * \brief Returns month name in english from given month number.
				 * \param _month: month number.
				 */
				QString getMonthName( int _month ) const;
				QString monthName( int _month ) const;


				/*!
				 * \brief Returns month name in native language from given month number.
				 * \param _month: month number.
				 */
				QString getMonthNameNative( int _month ) const;
				QString monthNameNative( int _month ) const;


				/*!
				 * \brief Returns month name in short format by given month
				 *			number in english language.
				 * \param _month: month number.
				 */
				QString getMonthNameShort( int _month ) const;
				QString monthNameShort( int _month ) const;


				/*!
				 * \brief Returns month name in short format by given month
				 *			number in native language.
				 * \param _month: month number.
				 */
				QString getMonthNameShortNative( int _month ) const;
				QString monthNameShortNative( int _month ) const;


				/*!
				 * \brief Returns day number by its name, or returns -1 in case
				 *			failure.
				 * \param _name: name of the day.
				 */
				int getDayNumberByName( const QString& _name ) const;
				int dayNumberByName( const QString& _name ) const ;


				/*!
				 * \brief Returns month number by its name, or returns -1 in case
				 *			failure.
				 * \param _name: name of the month.
				 */
				int getMonthNumberByName( const QString& _name ) const;
				int monthNumberByName( const QString& _name ) const;


				/*!
				 * \brief Returns start day of the week
				 */
				Calendar::Day getStartDay( void ) const;
				Calendar::Day startDay( void ) const;


				/*!
				 * \brief Returns type of the calendar.
				 */
				Type getType( void ) const { return m_eType; }
				Type type( void ) const { return m_eType; }

			private:
				Type	m_eType; //! Type of the calendar

			}; // calendar


			//==================================================================
			// static mthods
			//==================================================================
		public:

			/*!
			 * \brief Initialize local information.
			 */
			static bool init( void );


			/*!
			 * \brief Release allocated memory and resources
			 */
			static bool shutdown( void );


			/*!
			 * \brief Returns specified contry by its alpha-2 code
			 * \param _code: ISO 3166-1 alpha-2 code.
			 */
			static Country getContryByAlpha2Code( const QString& _code );


			/*!
			 * \brief Returns calndar by its name
			 * \param _type
			 */
			static Calendar getCalendar( Calendar::Type _type );

		};
	} // globalization
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PLocale = PCore::globalization::Locale;
#endif

#endif // _PCORE_LOCAL_INFO_H

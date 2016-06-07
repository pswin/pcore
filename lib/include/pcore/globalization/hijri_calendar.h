//#############################################################################
//#	title:	Hijri calendar
//#	c-date:	Jun-06-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//#############################################################################


#ifndef _PCORE_HIJRI_CALENDAR_H
#define _PCORE_HIJRI_CALENDAR_H

#include "../pcore_def.h"


//==============================================================================
// defines
//==============================================================================

#include <QMetaType>
#include <QString>
class QDataStream;
class QDebug;
class QVariant;
class QDate;


//==============================================================================
// Hijri Calendar
//==============================================================================

namespace PCore
{
	namespace globalization
	{
		class PCORE_API HijriCalendar
		{
			//=====================================
			// public mehtods
			//=====================================
		public:

			//! default constructor
			constexpr HijriCalendar( );


			/*!
			 * \brief Constructs a date with specified year, month and day.
			 * \param _year: Year.
			 * \param _month: Month.
			 * \param _day: Day.
			 */
			HijriCalendar( int _year, int _month, int _day );


			//! copy-constructor
			HijriCalendar( const HijriCalendar& _date );


			//! Destructor
			~HijriCalendar( ) { }


			/*!
			 * \brief Returns a HijriCalendar object which _num_of_days is added
			 *		  to current object's date.
			 * \param _num_of_days: Day numbers which must be added to current date.
			 * \return Returns a null date if current date is invalid or new date
			 *			is out of range. otherwise returns the new date.
			 */
			HijriCalendar addDays( qint64 _num_of_days ) const;


			/*!
			 * \brief Adds specified number of months to the current date,
			 *			and retuns it as new HijriCalendar object
			 * \param _num_of_months: number of months.
			 * \return Returns a null date if current date is invalid or new date
			 *			is out of range. otherwise returns the new date.
			 */
			HijriCalendar addMonths( int _num_of_months ) const;


			/*!
			 * \brief Adds specified number of years to the current date,
			 *			and retuns it as new HijriCalendar object.
			 * \param _num_of_years: number of years.
			 * \return Returns a null date if current date is invalid or new date
			 *			is out of range. otherwise returns the new date.
			 */
			HijriCalendar addYears( int _num_of_years ) const;


			/*!
			 * \brief Clears content's of the current object.
			 */
			void clear( void );


			/*!
			 * \brief returns the day number of the month of this date.
			 */
			inline int day( void ) const { return m_iDay; }
			inline int getDay( void ) const { return m_iDay; }


			/*!
			 * \brief Returns the weekday (1 = Monday to 7 = Sunday) for this date.
			 */
			inline int dayOfWeek( void ) const;
			inline int getDayOfWeek( void ) const { return dayOfWeek(); }


			/*!
			 * \brief Returns the day of the year (1 to 365 or 366 on leap years)
			 *			for this date.
			 */
			inline int dayOfYear( void ) const;
			inline int getDayOfYear( void ) const { return dayOfYear(); }


			/*!
			 * \brief Returns the number of days in specified month, or zero
			 *			if specified month is invalid.
			 * \param _month: Month number.
			 */
			inline int daysInMonth( int _month ) const;
			inline int getDaysInMonth( int _month ) const
							{ return daysInMonth( _month); }


			/*!
			 * \brief Returns the number of days in specified year, or zero
			 *			if specified year is invalid or out of range.
			 * \param _year: Year number.
			 */
			inline int daysInYear( void ) const;
			inline int getDaysInYear( void ) const { return daysInYear(); }



			/*!
			 * \brief Extracts the date's year, month, and day, and assigns
			 *					them to _year, _month, and _day
			 * \note Puts zero if the date is invalid.
			 */
			void getDate( int* _year, int* _month, int* _day ) const;


			/*!
			 * \brief Returns true if the date is null; otherwise returns false.
			 */
			bool isNull( void ) const  { return m_bIsNull; }


			/*!
			 * \brief Returns true if this date is valid; otherwise returns false.
			 */
			bool isValid( void ) const { return m_bIsValid; }


			/*!
			 * \brief Returns the number corresponding to the month of this date.
			 */
			inline int month( void ) const  { return m_iMonth; }
			inline int getMonth( void ) const  { return m_iMonth; }


			/*!
			 * \brief Sets the date's year, month, and day.
			 * \return True if the date is valid; otherwise returns false.
			 */
			bool setDate( int _year, int _month, int _day );


			/*!
			 * \brief Converts the date to a Julian day.
			 */
			inline qint64 toJulianDay( void ) const;


			/*!
			 * \brief Returns the date as a string.
			 * \param _format: Determines the format of the result.
			 */
			QString toString( const QString& _format ) const;


			/*!
			 * \brief Converts this date to QDate.
			 */
			QDate toQDate( void ) const;


			/*!
			 * \brief Returns the year of this date.
			 */
			inline int year( void ) const { return m_iYear; }
			inline int getYear( void ) const { return m_iYear; }


			//=====================================
			// operators
			//=====================================
		public:

			/*!
			 * \brief Cast current class to QVariant
			 */
			operator QVariant( void ) const;

			/*!
			 * \brief Returns true if this date is different from _date;
			 *				otherwise returns false.
			 */
			bool operator !=( const HijriCalendar& _date );


			/*!
			 * \brief Returns true if this date is earlier than _date;
			 *				otherwise returns false.
			 */
			bool operator < ( const HijriCalendar& _date );

			/*!
			 * \brief Returns true if this date is earlier than or equal to _date;
			 *				otherwise returns false.
			 */
			bool operator <= ( const HijriCalendar& _date );


			/*!
			 * \brief Returns true if this date is equal to _date;
			 *				 otherwise returns false.
			 */
			bool operator == ( const HijriCalendar& _date );


			/*!
			 * \brief Returns true if this date is later than _date;
			 *			otherwise returns false.
			 */
			bool operator >( const HijriCalendar& _date );


			/*!
			 * \brief Returns true if this date is later than or equal to _date;
			 *			otherwise returns false.
			 */
			bool operator >=( const HijriCalendar& _date );


			//=====================================
			// static methods
			//=====================================
		public:

			/*!
			 * \brief Returns the current date, as reported by the system clock
			 */
			static HijriCalendar currentDate( void );
			static HijriCalendar getCurrentDate( void )
											{ return currentDate(); }


			/*!
			 * \brief Converts Julian day to HijriCalendar.
			 * \param _day: Julian day.
			 * \return A HijriCalendar object from specified Julian date.
			 */
			static HijriCalendar fromJulianDay( quint64 _day );


			/*!
			 * \brief Returns a HijriCalendar object represented by the _date.
			 * \param _date: _date in Hijri calendar.
			 * \param _format: fotmat of _date.
			 */
			static HijriCalendar fromString(
										const QString& _date,
										const QString& _format = PCORE_CONFIG_DATE_HIJRI_DEFAULT_FORMAT
									);


			/*!
			 * \brief Converts a QDate object to a HijriCalendar object.
			 * \param _date: QDate object.
			 */
			static HijriCalendar fromQDate( const QDate& _date );


			/*!
			 * \brief Returns true if the specified year is a leap year;
			 *			otherwise returns false.
			 * \param _year: The year.
			 */
			static bool isLeapYear( int _year );


			/*!
			 * \brief Returns true if specified date is valid; otherwise returns false.
			 */
			static bool isValid( int _year, int _month, int _day );


			/*!
			 * \brief Returns the long name of the weekday.
			 * \param _day: The day (from 1 to 7)
			 * \return empty string is _day is invalid
			 */
			static QString longDayName( int _day );
			static QString getLongDayName( int _day ) { return longDayName(_day); }


			/*!
			 * \brief Returns the long name of the month.
			 * \param _month: The month (from 1 to 12)
			 * \return empty string is _day is invalid
			 */
			static QString longMonthName( int _month );
			static QString getLongMonthName( int _month ) { return longMonthName( _month );	}


			/*!
			 * \brief Returns the short name of the weekday.
			 * \return
			 */
			static QString shortDayName( int _day );
			static QString getShortDayName( int _day )
											{ return shortDayName( _day ); }


			/*!
			 * \brief Returns the short name of the month.
			 * \return
			 */
			static QString shortMonthName( int _month );
			static QString getShortMonthName( int _month )
									{ return shortMonthName( _month ); }


			/*!
			 * \brief Converts a gregorian date to Hijri date.
			 * \param _date: Gregorian date.
			 * \return Hijri date from gregorian date.
			 */
			static HijriCalendar fromGregorian( const QDate& _date );


			/*!
			 * \brief Converts specified Hijri date to gregorian date.
			 * \param _date: Hijri date.
			 * \return Gregorian date from Hijri date.
			 */
			static QDate toGregorian( const HijriCalendar& _date );


			//=====================================
			// friend operators
			//=====================================
		public:

			//! QDataStram
			#ifndef QT_NO_DATASTREAM
				friend PCORE_API QDataStream &operator<<( QDataStream &_st,
														  const HijriCalendar& _date );

				friend PCORE_API QDataStream &operator>>( QDataStream &,
														  HijriCalendar& );
			#endif


			//! QDebug
			#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_NO_DATESTRING)
				friend PCORE_API QDebug operator<<( QDebug, const HijriCalendar & );
			#endif


			//=====================================
			// private members
			//=====================================
		private:
			int		m_iDay		= -1;
			int		m_iMonth	= -1;
			int		m_iYear		= -1;
			quint64	m_lJulian	= -1;
			bool	m_bIsValid	= false;
			bool	m_bIsNull	= true;
			bool	m_bLeapYear = false;
		}; // HijriCalendar
	} // globalization
} // PCre


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PHijriCalendar	= PCore::globalization::HijriCalendar;
#endif


//==============================================================================
// MetaType
//==============================================================================

Q_DECLARE_METATYPE( PCore::globalization::HijriCalendar )


#endif // _PCORE_HIJRI_CALENDAR_H


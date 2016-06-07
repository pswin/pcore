//##############################################################################
//#	title:	Hijri calendar
//#	c-date:	Jun-06-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


/*
 *	The algorithm for calculating Hijri date has been written By Dr. J. Thomann,
 *	and It is located in the following addrress which belongs to Zurich
 *	University.
 *
 *	http://www.oriold.uzh.ch/static/hegira.html
 */


//==============================================================================
// Includes
//==============================================================================

#include "include/pcore/globalization/hijri_calendar.h"
#include "include/pcore/globalization/locale.h"
#include "include/pcore/globalization/date_parser.h"
#include <QVariant>
#include <QDebug>
#include <QDataStream>
#include <QDate>


//==============================================================================
// Functions
//==============================================================================

/*!
 * \brief Converts Hijri date to the Julian day.
 * \param _year: Year
 * \param _month: Month
 * \param _day: day
 * \return
 */
PCORE_FORCE_INLINE quint64 hijri_to_julian_day (
									int _year, int _month, int _day )
{
	return ( ( 11 * _year + 3 ) / 30 ) + 354 * _year + 30 * _month -
			(int)( ( _month - 1 ) / 2 ) + _day + 1948440 - 385;
} // hijri_to_julian_day


//==============================================================================
// Core
//==============================================================================
namespace PCore
{
	namespace globalization
	{
		//! constructor
		constexpr HijriCalendar::HijriCalendar()
		{

		}


		//! constructor
		HijriCalendar::HijriCalendar( int _year, int _month, int _day )
		{
			setDate( _year, _month, _day );
		}


		//! copy-constructor
		HijriCalendar::HijriCalendar( const HijriCalendar& _date )
		{
			setDate( _date.m_iYear, _date.m_iMonth, _date.m_iDay );
		}


		//! addDays
		HijriCalendar HijriCalendar::addDays( qint64 _num_of_days ) const
		{
			if ( m_bIsValid == false ) return HijriCalendar();
			return HijriCalendar::fromJulianDay( toJulianDay() + _num_of_days );
		}


		//! addMonths
		HijriCalendar HijriCalendar::addMonths( int _num_of_months ) const
		{
			int m = ( m_iMonth + _num_of_months - 1 ) % 12;
			int y = ( m_iMonth + _num_of_months - 1 ) / 12;

			return HijriCalendar( m_iYear + y, m + 1, m_iDay );
		}


		//! addYears
		HijriCalendar HijriCalendar::addYears( int _num_of_years ) const
		{
			return HijriCalendar( m_iYear + _num_of_years, m_iMonth, m_iDay );
		}


		//! dayOfWeek
		int HijriCalendar::dayOfWeek( void ) const
		{
			if ( m_bIsValid == false ) return -1;
			return ( m_lJulian % 7 ) + 1;
		}


		//! dayOfYear
		int HijriCalendar::dayOfYear() const
		{
			if ( m_bIsValid == false ) return -1;
			return m_lJulian - hijri_to_julian_day( m_iYear, 1, 1 );
		}


		//! daysInMonth
		int HijriCalendar::daysInMonth( int _month ) const
		{
			if ( ( _month < 1 ) || (_month > 12 ) ) return -1;
			if ( ( _month == 12 ) && ( m_bLeapYear == true ) ) return 30;
			return  (_month % 2) + 29;
		}


		//! daysInYear
		int HijriCalendar::daysInYear( void ) const
		{
			if ( m_bLeapYear == true ) return 355;
			return 354;
		}


		//! getDate
		void HijriCalendar::getDate( int* _year, int* _month, int* _day ) const
		{
			if ( _year != nullptr ) *_year = m_iYear;
			if ( _month != nullptr ) *_month = m_iMonth;
			if ( _day != nullptr ) *_day = m_iDay;
		}


		//! setDate
		bool HijriCalendar::setDate( int _year, int _month, int _day )
		{
			if ( isValid( _year, _month, _day ) == false ) return false;

			m_iYear = _year;
			m_iMonth = _month;
			m_iDay = _day;
			m_bIsNull = false;
			m_lJulian = hijri_to_julian_day( _year, _month, _day );
			m_bLeapYear = isLeapYear( m_iYear );
			m_bIsValid = true;

			return true;
		}


		//! toJulianDay
		qint64 HijriCalendar::toJulianDay( void ) const
		{
			return m_lJulian;
		}


		//! toString
		QString HijriCalendar::toString( const QString& _format ) const
		{
			DateParser p( QLocale::Arabic, QLocale::UnitedArabEmirates );
			p.setFormat( _format );
			return p.toString( m_iYear, m_iMonth, m_iDay, dayOfWeek() );
		}


		//! toQDate
		QDate HijriCalendar::toQDate() const
		{
			return QDate::fromJulianDay( toJulianDay() );
		}


		//! to QVariant
		HijriCalendar::operator QVariant() const
		{
			QVariant v;
			v.setValue( *this );
			return v;
		}


		//! operator !=
		bool HijriCalendar::operator !=( const HijriCalendar& _date )
		{
			return m_lJulian != _date.m_lJulian;
		}


		//! operator <
		bool HijriCalendar::operator <( const HijriCalendar& _date )
		{
			return m_lJulian < _date.m_lJulian;
		}


		//! operator ==
		bool HijriCalendar::operator ==( const HijriCalendar& _date )
		{
			return m_lJulian == _date.m_lJulian;
		}


		//! operator >
		bool HijriCalendar::operator >( const HijriCalendar& _date )
		{
			return m_lJulian > _date.m_lJulian;
		}


		//! operator >=
		bool HijriCalendar::operator >=( const HijriCalendar& _date )
		{
			return m_lJulian >= _date.m_lJulian;
		}


		//! currentDate
		HijriCalendar HijriCalendar::currentDate( void )
		{
			return HijriCalendar::fromJulianDay(
									QDate::currentDate().toJulianDay() );
		}


		// fromJulianDay
		HijriCalendar HijriCalendar::fromJulianDay( qint64 _day )
		{
			int day = -1;
			int month = -1;
			int year = -1;
			int l,j,n;

			l = _day - 1948440 + 10632;
			n = ( l - 1 ) / 10631;
			l = l - 10631 * n + 354;
			j = ( (int)( ( 10985 - l ) / 5316 ) ) * ( (int)( ( 50 * l ) / 17719 ) )
					+ ( (int)( l / 5670 ) ) * ( (int)( ( 43 * l ) / 15238 ) );
			l = l - ( (int)( ( 30 - j ) / 15 ) ) * ( (int)( ( 17719 * j ) / 50 ) )
					-( (int)( j / 16 ) ) * ( (int)( ( 15238 * j ) / 43) ) + 29;
			month = (int)( ( 24 * l ) / 709 );
			day = l - (int)( ( 709 * month ) / 24 );
			year = 30 * n + j - 30;
			return HijriCalendar( year, month, day );
		} // fromJulianDay


		//! fromString
		HijriCalendar HijriCalendar::fromString( const QString& _date,
												 const QString& _format )
		{
			DateParser p( QLocale::Arabic, QLocale::UnitedArabEmirates );
			p.setFormat( _format );
			DateParser::Date d = p.parseFromString( _date );

			if ( d.valid == true )
			{
				return HijriCalendar( d.year, d.month, d.day );
			}

			return HijriCalendar();
		} // fromString


		//! fromQDate
		HijriCalendar HijriCalendar::fromQDate( const QDate& _date )
		{
			return HijriCalendar::fromJulianDay( _date.toJulianDay() );
		}


		//! isLeapYear
		bool HijriCalendar::isLeapYear( int _year )
		{
			if ( _year < 1 ) return false;
			return ( ( _year - 1 ) % 30 ) < 11;
		}

		bool HijriCalendar::isValid( int _year, int _month, int _day )
		{
			if ( _year < 1 ) return false;
			if ( ( _month < 1 ) || ( _month > 12 ) ) return false;
			if (  _day < 1 ) return false;

			if ( ( _month == 12 ) && isLeapYear( _year ) )
			{
				if ( _day > 30 ) return false;
			}
			else
			{
				if ( _day > ( ( _month % 2) + 29 )  ) return false;
			}

			return true;
		} // isValid


		//! longDayName
		QString HijriCalendar::longDayName( int _day )
		{
			return Locale::Calendar( Locale::Calendar::Type::Hijri )
					.dayNameNative( _day );
		}


		//! longMonthName
		QString HijriCalendar::longMonthName( int _month )
		{
			return Locale::Calendar( Locale::Calendar::Type::Hijri )
					.monthNameNative( _month );
		}


		//! shortDayName
		QString HijriCalendar::shortDayName( int _day )
		{
			return Locale::Calendar( Locale::Calendar::Type::Hijri )
					.dayNameShortNative( _day );
		}


		//! shortMonthName
		QString HijriCalendar::shortMonthName(int _month)
		{
			return Locale::Calendar( Locale::Calendar::Type::Hijri )
					.monthNameShortNative( _month );
		}


		//! fromGregorian
		HijriCalendar HijriCalendar::fromGregorian(const QDate& _date)
		{
			return HijriCalendar::fromJulianDay( _date.toJulianDay() );
		}


		//! toGregorian
		QDate HijriCalendar::toGregorian( const HijriCalendar& _date )
		{
			return QDate::fromJulianDay( _date.toJulianDay() );
		}


		//! operator<<, QDebug
		QDebug operator<<( QDebug _st, const HijriCalendar &_date )
		{
			_st.nospace() << "HijriCalendar(\"" <<
							 _date.m_iYear << "-" <<
							 _date.m_iMonth << "-" <<
							 _date.m_iDay << "\")";

			return _st.space();
		}


		//! operator<<
		QDataStream& operator<< ( QDataStream &_st, const HijriCalendar& _date )
		{
			_st << _date.m_iYear << _date.m_iMonth << _date.m_iDay;
			return _st;
		}


		//! operator>>
		QDataStream& operator>>( QDataStream &_st, HijriCalendar& _date )
		{
			_st >> _date.m_iYear >> _date.m_iMonth >> _date.m_iDay;
			return _st;
		}
	} // globalization
} // PCore


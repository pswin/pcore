//##############################################################################
//#	c-date:	May-27-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include "include/pcore/globalization/persian_calendar.h"
#include "include/pcore/globalization/date_parser.h"
#include "include/pcore/globalization/locale.h"
#include <QDate>
#include <QString>
#include <QDataStream>
#include <QDebug>
#include <QVariant>


//==============================================================================
// Macros
//==============================================================================

#define PCORE_JULIAN_DIFRENCE		( 1948310 )
#define PCORE_JALALI_ZERO_IN_JULIAN	( 1948310 )
#define PCORE_MIN_JALALI_YEAR		( -1096 )
#define PCORE_MAX_JALALI_YEAR		( 2327 )
#define PCORE_PERSIAN_EPOCH			( 1948320 )


//==============================================================================
// constants
//==============================================================================


const int day_per_month[] = {	31, 31, 31,
								31, 31, 31,
								30, 30, 30,
								30, 30, 29 };

const int day_per_month_leap[] = {	31, 31, 31,
									31, 31, 31,
									30, 30, 30,
									30, 30, 30 };


//==============================================================================
// functions
//==============================================================================


/*!
 * \brief Converts persian year to rhe Julian day.
 * \param _year: The year.
 * \return Return Julian day from given persian date.
 */
PCORE_FORCE_INLINE quint64 persian_to_julian( int _year )
{
	int base = _year - 474;
	int y = 474 + (base + 282000000) % 2820;

	return ((y * 31 - 5) / 128 + (y - 1) * 365
			   + ((_year - y) / 2820) * 1029983 + PCORE_PERSIAN_EPOCH );
} // persian_to_julian


//==============================================================================
// PersianCalendar
//==============================================================================
namespace PCore
{
	namespace globalization
	{

		//======================================================================
		// public methods
		//======================================================================

		//! constructor
		PersianCalendar::PersianCalendar()
		{

		}


		//! construcor
		PersianCalendar::PersianCalendar( int _year, int _month, int _day )
		{
			setDate( _year, _month, _day );
		}


		//! copy-constructor
		PersianCalendar::PersianCalendar( const PersianCalendar &_date )
		{
			setDate( _date.m_iYear, _date.m_iMonth, _date.m_iDay );
		}


		//! addDay
		PersianCalendar PersianCalendar::addDays( qint64 _num_of_days ) const
		{
			return PersianCalendar::fromJulianDay( toJulianDay() + _num_of_days );
		} // addDays


		//! addMonths
		PersianCalendar PersianCalendar::addMonths( int _num_of_months ) const
		{
			if ( m_bIsValid == false ) return PersianCalendar();

			int y = (  ( _num_of_months + m_iMonth - 1 ) / 12 ) + m_iYear;
			int m = ( _num_of_months + m_iMonth - 1 ) % 12;

			return PersianCalendar( y, m + 1 , m_iDay );
		} // addMonths


		//! addYears
		PersianCalendar PersianCalendar::addYears( int _num_of_years ) const
		{
			if ( m_bIsValid == false ) return PersianCalendar();
			return PersianCalendar( _num_of_years + m_iYear, m_iMonth, m_iDay );
		} // addYears


		//! clear
		void PersianCalendar::clear()
		{
			m_iYear		= -1;
			m_iMonth	= -1;
			m_iDay		= -1;
			m_lJulian	= -1;
			m_bIsNull	= true;
			m_bIsValid	= false;
			m_bLeapYear	= false;
		} // clear


		//! dayOfWeek
		int PersianCalendar::dayOfWeek( void ) const
		{
			if ( m_bIsValid == false ) return -1;
			return ( ( toJulianDay() + 2 ) % 7 ) + 1;
		}


		//! dayOfYear
		int PersianCalendar::dayOfYear( void ) const
		{
			if ( m_bIsValid == false ) return -1;
			return toJulianDay() - persian_to_julian( m_iYear ) + 1;
		} // dayOfYear


		// dayInMonth
		int PersianCalendar::daysInMonth( int _month ) const
		{
			if ( ( _month > 12 ) || ( _month < 1 ) ) return 0;

			if ( m_bIsValid == true )
			{
				return day_per_month_leap[ _month - 1 ];
			}
			else
			{
				return day_per_month[ _month - 1 ];
			}
		} // dayInMonth


		// daysInYear
		int PersianCalendar::daysInYear( void ) const
		{
			if ( m_bIsValid == false ) return -1;
			if ( m_bLeapYear == true )
			{
				return 366;
			}
			else
			{
				return 365;
			}
		}


		//! daysInYear
		int PersianCalendar::daysInYear(const PersianCalendar& _date) const
		{
			if ( _date.isValid() == false ) return -1;
			if ( isLeapYear( _date.year() ) )
			{
				return 366;
			}
			else
			{
				return 365;
			}
		} // daysInYear


		//! getDate
		void PersianCalendar::getDate( int *_year, int *_month, int *_day ) const
		{
			if ( isValid() == true )
			{
				if ( _year != nullptr ) *_year = m_iYear;
				if ( _month != nullptr ) *_month = m_iMonth;
				if ( _day != nullptr ) *_day = m_iDay;
			}
			else
			{
				if ( _year != nullptr ) *_year = 0;
				if ( _month != nullptr ) *_month = 0;
				if ( _day != nullptr ) *_day = 0;
			}
		} // getDate


		//! isValid
		bool PersianCalendar::isValid() const
		{
			return m_bIsValid;
		} // isValid


		//! setDate
		bool PersianCalendar::setDate( int _year, int _month, int _day )
		{
			m_iYear = _year;
			m_iMonth = _month;
			m_iDay = _day;
			m_bIsNull = false;

			m_bIsValid = PersianCalendar::isValid( _year, _month, _day );
			if ( m_bIsValid )
			{
				m_lJulian = persian_to_julian( _year ) + dayOfYear();
				m_bLeapYear = PersianCalendar::isLeapYear( m_iYear );
			}
			return m_bIsValid;
		} // setDate


		//! toJulianDay
		qint64 PersianCalendar::toJulianDay( void ) const
		{
			if ( m_bIsValid == false ) return 0;
			return m_lJulian;
		} // toJulianDay


		//! toString
		QString PersianCalendar::toString( const QString &_format ) const
		{
			if ( m_bIsValid == false ) return nullptr;
			DateParser d;
			d.setLocale( QLocale::Persian, QLocale::Iran );
			d.setFormat( _format );
			return d.toString( m_iYear, m_iMonth, m_iDay, dayOfWeek() );
		}


		//! toQDate
		QDate PersianCalendar::toQDate( void ) const
		{
			return QDate::fromJulianDay( toJulianDay() );
		}


		//======================================================================
		// operators
		//======================================================================

		//! cast operator
		PCore::globalization::PersianCalendar::operator QVariant( void ) const
		{
			QVariant v;
			v.setValue( *this );
			return v;
		}


		//! operator !=
		bool PersianCalendar::operator !=( const PersianCalendar &_date )
		{
			return m_lJulian != _date.m_lJulian;
		}

		//! operator <
		bool PersianCalendar::operator <( const PersianCalendar &_date )
		{
			return m_lJulian < _date.m_lJulian;
		}

		//! operator <=
		bool PersianCalendar::operator <=( const PersianCalendar &_date )
		{
			return m_lJulian <= _date.m_lJulian;
		}

		//! operator ==
		bool PersianCalendar::operator ==( const PersianCalendar &_date )
		{
			return m_lJulian == _date.m_lJulian;
		}

		//! operator >
		bool PersianCalendar::operator >( const PersianCalendar &_date )
		{
			return m_lJulian > _date.m_lJulian;
		}

		//! operator >=
		bool PersianCalendar::operator >=( const PersianCalendar &_date )
		{

			return m_lJulian >= _date.m_lJulian;
		}


		//! operator<<, QDebug
		QDebug operator<<(QDebug _st, const PersianCalendar &_date )
		{
			_st.nospace() << "PersianCalendar(\"" <<
							 _date.m_iYear << "-" <<
							 _date.m_iMonth << "-" <<
							 _date.m_iDay << "\")";

			return _st.space();
		}


		//! operator<<
		QDataStream& operator<< (
								QDataStream &_st, const PersianCalendar& _date )
		{
			_st << _date.m_iYear << _date.m_iMonth << _date.m_iDay;
			return _st;
		}


		//! operator>>
		QDataStream& operator>>(
								QDataStream &_st, PersianCalendar& _date)
		{
			_st >> _date.m_iYear >> _date.m_iMonth >> _date.m_iDay;
			return _st;
		}


		//======================================================================
		// static members
		//======================================================================

		//!currentDate
		PersianCalendar PersianCalendar::currentDate()
		{
			return PersianCalendar::fromQDate( QDate::currentDate() );
		}


		//! fromJulianDay
		PersianCalendar PersianCalendar::fromJulianDay( quint64 _day )
		{
			int year_ends[2];
			int curr_jd;
			int month_data[12];
			//int i;

			int day		= -1;
			int month	= -1;
			int year	= -1;

			year = ( _day - PCORE_JALALI_ZERO_IN_JULIAN ) / 365;

			do
			{
				year_ends[0] = persian_to_julian( year ) + 1;
				year_ends[1] = persian_to_julian( year + 1 ) + 1;

				for (int i = 0; i <= 5; i++) month_data[i] = 31;
				for (int i = 6; i <= 10; i++) month_data[i] = 30;

				month_data[11] = ( year_ends[1] - year_ends[0] - 336 );

				year_ends[1] = year_ends[0];
				for ( int i = 0; i < 12; i++ )
				{
					 year_ends[1] += month_data[i];
				}

				if ( year_ends[0] > _day )
				{
					year--;
				}

				if ( year_ends[1] <= _day )
				{
					year++;
				}
			}
			while ( ( year_ends[0] > _day ) || ( year_ends[1] <= _day ) );

			curr_jd = year_ends[0];
			month = -1;
			for ( int i = 0; i < 12; i++ )
			{
				day = _day - curr_jd;
				if ( day < month_data[i] )
				{
					month = i + 1;
					day++;
					return PersianCalendar( year, month, day );
				}
				curr_jd += month_data[i];
			}
			return PersianCalendar( year, month, day );
		}


		//! fromString
		PersianCalendar PersianCalendar::fromString(
												const QString &_date,
												const QString &_format
											)
		{
			DateParser d( QLocale::Persian, QLocale::Iran );
			d.setFormat( _format );
			DateParser::Date date = d.parseFromString( _date );

			if ( date.valid == true )
			{
				return PersianCalendar( date.year, date.month, date.day );
			}
			else
			{
				return PersianCalendar();
			}
		}


		//! fromQDate
		PersianCalendar PersianCalendar::fromQDate( const QDate& _date )
		{
			return fromGregorian( _date );
		}


		//! isLeapYear
		bool PersianCalendar::isLeapYear( int _year )
		{
			if ( _year == 0 ) return false;

			double leap_days_0 = 0;
			double leap_days_1 = 0;

			if ( _year > 0 )
			{
				leap_days_0 = ( (_year + 38) % 2820 ) * 0.24219 + 0.025;
				leap_days_1 = ( (_year + 39) % 2820 )* 0.24219 + 0.025;
			}
			else
			{
				leap_days_0 = ( (_year + 39) % 2820 )* 0.24219 + 0.025;
				leap_days_1 = ( (_year + 40) % 2820 )* 0.24219 + 0.025;
			}

			int frac_0 = (int)(( leap_days_0 - (int)leap_days_0 ) * 1000 );
			int frac_1 = (int)(( leap_days_1 - (int)leap_days_1 ) * 1000 );

			if ( (frac_0 <= 266 ) && ( frac_1 > 266 ) )
			{
				return true;
			}

			return false;
		} // isLeapYear


		//! isValid
		bool PersianCalendar::isValid( int _year, int _month, int _day )
		{
			if ( _year == 0 ) return false;
			if ( _month > 12 || _month < 1 ) return false;

			if ( isLeapYear(_year) == true )
			{
				return ( _day < day_per_month_leap[_month-1]) && ( _day > 0 );
			}
			else
			{
				return ( _day < day_per_month[_month-1]) && ( _day > 0 );
			}
		} // isValid


		//! longDayName
		QString PersianCalendar::longDayName( int _day )
		{
			return Locale::Calendar(Locale::Calendar::Type::PersianIran)
					.dayNameNative( _day );
		}


		//! longMonthName
		QString PersianCalendar::longMonthName( int _month )
		{
			return Locale::Calendar(Locale::Calendar::Type::PersianIran)
					.monthNameNative( _month );
		}


		//! shortDayName
		QString PersianCalendar::shortDayName( int _day )
		{
			return Locale::Calendar(Locale::Calendar::Type::PersianIran)
					.dayNameShortNative( _day );
		}


		//! shortMonthName
		QString PersianCalendar::shortMonthName(int _month)
		{
			return Locale::Calendar(Locale::Calendar::Type::PersianIran)
					.monthNameShortNative( _month );
		}


		//! fromGregorian
		PersianCalendar PersianCalendar::fromGregorian( const QDate &_date )
		{
			return PersianCalendar::fromJulianDay( _date.toJulianDay() );
		}


		//! toGregorian
		QDate PersianCalendar::toGregorian(const PersianCalendar &_date)
		{
			return QDate::fromJulianDay( _date.toJulianDay() );
		}

	} // globalization
} // PCore


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
		constexpr PersianCalendar::PersianCalendar()
		{

		}


		//! construcor
		PersianCalendar::PersianCalendar( int _year, int _month, int _day )
		{
			setDate( _year, _month, _day );
		}


		//! copy-constructor
		PersianCalendar::PersianCalendar(const PersianCalendar &_date)
		{
			setDate( _date.m_iYear, _date.m_iMonth, _date.m_iDay );
		}


		//! addDay
		PersianCalendar PersianCalendar::addDays( qint64 _num_of_days ) const
		{
			qint64 d = _num_of_days + m_iDay;
			int m = m_iMonth;
			int y = m_iYear;

			int days_num = day_per_month[ m ];
			if ( isLeapYear( y ) ) days_num = day_per_month[ m ];

			while ( d > days_num )
			{
				m++;
				d -= days_num;
				if ( m > 12 )
				{
					y++;
					m++;
				}

				days_num = day_per_month[ m ];
				if ( isLeapYear( y ) ) days_num = day_per_month_leap[ m ];
			}

			return PersianCalendar( y, m, d );

		} // addDays


		// addMonths
		PersianCalendar PersianCalendar::addMonths( int _num_of_months ) const
		{
			int y = (_num_of_months + m_iMonth / 12) + m_iYear;
			int m = _num_of_months + m_iMonth % 12;

			return PersianCalendar( y, m , m_iDay );
		} // addMonths


		//! addYears
		PersianCalendar PersianCalendar::addYears( int _num_of_years ) const
		{
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
			return QDate::fromJulianDay( toJulianDay() + 2 ).dayOfWeek();
		}


		//! dayOfYear
		int PersianCalendar::dayOfYear( void ) const
		{
			int p2 = ( m_iMonth -1 ) % 6 * (m_iMonth%1);
			int p1 = ( m_iMonth -1 ) - p2;
			return ( p2 *30 ) + ( p1 * 31 ) + m_iDay;
		} // dayOfYear


		// dayInMonth
		int PersianCalendar::daysInMonth( int _month ) const
		{
			if ( (_month > 12) || (_month < 1) ) return 0;

			if ( isCurrentYearALeapYear() == true )
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
			if ( isCurrentYearALeapYear() == true )
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
			*_year = 0;
			*_month = 0;
			*_day = 0;

			if ( isValid() == true )
			{
				*_year = m_iYear;
				*_month = m_iMonth;
				*_day = m_iDay;
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
			m_bIsValid = checkValidity();
			if ( m_bIsValid )
			{
				m_lJulian = persian_to_julian( _year ) + dayOfYear();
			}
			return m_bIsValid;
		} // setDate


		//! toJulianDay
		qint64 PersianCalendar::toJulianDay( void ) const
		{
			return m_lJulian;
		} // toJulianDay


		//! toString
		QString PersianCalendar::toString( const QString &_format ) const
		{
			DateParser d;
			d.setLocale( QLocale::Persian, QLocale::Iran );
			d.setFormat( _format );
			return d.toString( m_iYear, m_iMonth, m_iDay, dayOfWeek() );
		}


		//! toString
		QString PersianCalendar::toString( const Qt::DateFormat _format ) const
		{
			return QDate::fromJulianDay( toJulianDay() ).toString( _format );
		}


		//! toQDate
		QDate PersianCalendar::toQDate( void ) const
		{
			return QDate::fromJulianDay( toJulianDay() );
		}


		//! weekNumber
		int PersianCalendar::weekNumber( int *_year ) const
		{
			// TODO:
			quint64 jd_start = persian_to_julian( m_iYear );
			return (( toJulianDay() - jd_start)/7)+1;
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
			return toJulianDay() != _date.toJulianDay();
		}

		//! operator <
		bool PersianCalendar::operator <( const PersianCalendar &_date )
		{
			return toJulianDay() < _date.toJulianDay();
		}

		//! operator <=
		bool PersianCalendar::operator <=( const PersianCalendar &_date )
		{
			return toJulianDay() <= _date.toJulianDay();
		}

		//! operator ==
		bool PersianCalendar::operator ==( const PersianCalendar &_date )
		{
			return toJulianDay() == _date.toJulianDay();
		}

		//! operator >
		bool PersianCalendar::operator >( const PersianCalendar &_date )
		{
			return toJulianDay() > _date.toJulianDay();
		}

		//! operator >=
		bool PersianCalendar::operator >=( const PersianCalendar &_date )
		{

			return toJulianDay() >= _date.toJulianDay();
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
		PersianCalendar PersianCalendar::fromJulianDay( qint64 _day )
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
													const Qt::DateFormat _format
												)
		{
			return PersianCalendar::fromJulianDay(
						QDate::fromString( _date, _format ).toJulianDay() );
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

			//if ( leap_years[_year%33] == 1 ) return true;
			//return false;

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


		//======================================================================
		// private methods
		//======================================================================

		//! checkValidity
		bool PersianCalendar::checkValidity()
		{
			if ( ( m_iMonth > 12) || (m_iMonth < 1) ) return false;

			if ( isLeapYear( m_iYear ) == true )
			{
				if ( m_iDay > day_per_month_leap[m_iMonth-1] ) return false;
			}
			else
			{
				if ( m_iDay > day_per_month[m_iMonth-1] ) return false;
			}
			return true;
		}


		//! isCurrentYearALeapYear
		bool PersianCalendar::isCurrentYearALeapYear() const
		{
			return m_bLeapYear;
		}

	} // globalization
} // PCore


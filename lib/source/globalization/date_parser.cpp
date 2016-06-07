//#############################################################################
//#	c-date:	May-27-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//#############################################################################


//==============================================================================
// includes
//==============================================================================

#include "include/pcore/globalization/date_parser.h"
#include "include/pcore/globalization/locale.h"
#include <QString>
#include <QList>
#include <QRegExp>


//==============================================================================
// constants
//==============================================================================


const char* reg_format[] = {
							"(\\d{2,4})",	// Year 4 digit
							"(\\d{4})",		// Year 2 digit
							"(\\d{1,2})",	// Month
							"(\\d{2})",		// Month leading zero
							"(\\w+)",		// Month Name
							"(\\w+)",		// Month Name Long
							"(\\d{1,2})",	// Day
							"(\\d{2})",		// Day leading zero
							"(\\w+)",		// Day Name
							"(\\w+)"		// Day Name Long
						};


//==============================================================================
// Functions
//==============================================================================

/*!
 * \brief Counts number of repeated chars from given index in specified string.
 * \param _str The string.
 * \param _index Index of char in string.
 * \param _max_len: Maximum length that sould be counted.
 */
PCORE_FORCE_INLINE int countRepeat( const QString& _str,
						  int _index,
						  int _max_len
						)
{
	int count = 1;
	const QChar ch( _str.at( _index) );
	const int max = qMin( _index + _max_len, _str.size() );
	while ( ( _str.at(_index + count) == ch ) &&
			( (count + _index) < max ) )
	{
		count++;
	}
	return count;
} // countRepeat


/*!
  Returns a calendar by given country and language
*/
PCORE_FORCE_INLINE PCore::globalization::Locale::Calendar
					get_calendar( QLocale::Country _country,
								QLocale::Language _language )
{
	PCore::globalization::Locale::Calendar
					cal( PCore::globalization::Locale::Calendar::Type::Gregorian );

	switch ( _language )
	{
		case QLocale::Persian:
			if ( _country == QLocale::Afghanistan )
			{
				cal.setType( PCore::globalization::Locale::Calendar::Type::PersianAfghanistan );
			}
			else
			{
				cal.setType( PCore::globalization::Locale::Calendar::Type::PersianIran );
			}
			break;
		case QLocale::Arabic:
			cal.setType( PCore::globalization::Locale::Calendar::Type::Hijri );
			break;
	}

	return cal;
} // get_calendar


//==============================================================================
// Date Parser
//==============================================================================
namespace PCore
{
	namespace globalization
	{
		//! constructor
		DateParser::DateParser( QLocale::Language _lang,
								QLocale::Country _country,
								QLocale::Script _script
							)
		{
			this->setLocale( _lang, _country, _script );
		}

		//! setFormat
		void DateParser::setFormat(const QString& _format)
		{
			m_sFormat = _format;
			m_Nodes.clear();


			int			repeat			= 0;
			int			str_len			= _format.length();
			QString		seprator;

			for ( int index = 0; index < str_len ; index++ )
			{

				switch ( _format[index].unicode() )
				{
					//---------------
					// escape
					//---------------
				case u'\\':
						index++;
						seprator.append( _format.at( index ) );
						continue;
					break;
					//---------------
					// Year
					//---------------
				case u'y':
					if ( seprator.isNull() == false )
					{
						m_Nodes.push_back( Node( Node::Type::Sperator, seprator ) );
						seprator.clear();
					}
					repeat = countRepeat( _format, index, 4 );
					index += repeat -1;

					if ( repeat == 4 )
					{
						m_Nodes.push_back( Node( Node::Type::YearLong ) );
					}
					else if ( repeat == 2 )
					{
						m_Nodes.push_back( Node( Node::Type::Year ) );
					}
					break;
					//---------------
					// Month
					//---------------
				case u'M':
					if ( seprator.isNull() == false )
					{
						m_Nodes.push_back( Node( Node::Type::Sperator, seprator ) );
						seprator.clear();
					}
					repeat = countRepeat( _format, index, 4 );
					index += repeat -1;

					if ( repeat == 4 )
					{
						m_Nodes.push_back( Node( Node::Type::MonthNameFull ) );
					}
					else if ( repeat == 3 )
					{
						m_Nodes.push_back( Node( Node::Type::MonthNameAbbreviated ) );
					}
					else if ( repeat == 2 )
					{
						m_Nodes.push_back( Node( Node::Type::MonthLeadingZero ) );
					}
					else if ( repeat == 1 )
					{
						m_Nodes.push_back( Node( Node::Type::Month ) );
					}
					break;
					//---------------
					// Day
					//---------------
				case u'D':
					if ( seprator.isNull() == false )
					{
						m_Nodes.push_back( Node( Node::Type::Sperator, seprator ) );
						seprator.clear();
					}
					repeat = countRepeat( _format, index, 4 );
					index += repeat-1;
					if ( repeat == 4 )
					{
						m_Nodes.push_back( Node( Node::Type::DayNameFull ) );
					}
					else if ( repeat == 3 )
					{
						m_Nodes.push_back( Node( Node::Type::DayNameAbbreviated ) );
					}
					else if ( repeat == 2 )
					{
						m_Nodes.push_back( Node( Node::Type::DayLeadingZero ) );
					}
					else if ( repeat == 1 )
					{
						m_Nodes.push_back( Node( Node::Type::Day ) );
					}
					break;
				default:
					seprator.append( _format.at( index ) );
				} // switch

			} // for

			if ( seprator.isNull() == false )
			{
				m_Nodes.push_back( Node( Node::Type::Sperator, seprator ) );
			}
		} // setFormat


		//! setLocale
		void DateParser::setLocale( QLocale::Language _lang,
									QLocale::Country _country,
									QLocale::Script _script
								)
		{
			m_eLanguage = _lang;
			m_eCountry = _country;
			m_eScript = _script;
		}


		//! parseDate
		DateParser::Date DateParser::parseFromString( const QString& _date )
		{
			DateParser::Date d;

			// checking for the format
			if ( m_Nodes.size() == 0 ) return d;

			// makeing reqular expression.
			QString reg_exp;
			for( Node it : m_Nodes )
			{
				if ( it.type() != Node::Type::Sperator )
				{
					reg_exp.append( reg_format[(int)it.getType()] );
				}
				else
				{
					QString str = it.getValue();
					str = str.replace( '\\', "\\\\" );
					str = str.replace( '*', "\\*" );
					str = str.replace( '-', "\\-" );
					str = str.replace( '+', "\\+" );
					str = str.replace( '?', "\\?" );
					str = str.replace( '}', "\\}" );
					str = str.replace( '{', "\\{" );
					str = str.replace( '(', "\\(" );
					str = str.replace( ')', "\\)" );
					str = str.replace( '[', "\\[" );
					str = str.replace( ']', "\\]" );
					reg_exp.append( str );
				}
			}


			QRegExp r( reg_exp );
			if ( r.indexIn( _date ) == -1 )
			{
				return d;
			}

			d.valid = true;

			int i = 1;
			QStringList ls = r.capturedTexts();
			Locale::Calendar cal = get_calendar( m_eCountry, m_eLanguage );

			for( Node it : m_Nodes )
			{
				switch ( it.type() )
				{
					case Node::Type::Day:
					case Node::Type::DayLeadingZero:
						d.day = r.cap( i++ ).toInt();
						break;
					case Node::Type::DayNameAbbreviated:
					case Node::Type::DayNameFull:
						d.week_day = (int)cal.dayNumberByName( r.cap(i++) );
						break;
					case Node::Type::Month:
					case Node::Type::MonthLeadingZero:
						d.month = r.cap( i++ ).toInt();
						break;
					case Node::Type::MonthNameAbbreviated:
					case Node::Type::MonthNameFull:
						d.month = cal.monthNumberByName( r.cap(i++) );
						break;
					case Node::Type::Year:
					case Node::Type::YearLong:
						d.year = r.cap( i++ ).toInt();
					break;
				} // switch
			} // for

			return d;
		} // parseFromString


		//! toString
		QString DateParser::toString( int _year, int _month,
											int _day, int _day_of_week )
		{
			if ( m_Nodes.size() == 0 ) return nullptr;

			QString str;
			Locale::Calendar cal = get_calendar( m_eCountry, m_eLanguage );

			for ( Node it : m_Nodes )
			{
				switch ( it.getType() )
				{
				case Node::Type::Sperator:
					str.append( it.getValue() );
					break;
				case Node::Type::Year:
					str.append( QString::number( _year ).right( 2 ) );
					break;
				case Node::Type::YearLong:
					str.append( QString::number( _year ) );
					break;
				case Node::Type::Month:
					str.append( QString::number( _month ) );
					break;
				case Node::Type::MonthLeadingZero:
					if ( _month < 10 )
					{
						str.append( '0' );
					}
					str.append( QString::number( _month ) );
					break;
				case Node::Type::MonthNameAbbreviated:
					str.append( cal.monthNameShortNative( _month ) );
					break;
				case Node::Type::MonthNameFull:
					str.append( cal.monthNameNative( _month ) );
					break;
				case Node::Type::Day:
					str.append( QString::number( _day ) );
					break;
				case Node::Type::DayLeadingZero:
					if ( _day < 10 )
					{
						str.append( '0' );
					}
					str.append( QString::number( _day ) );
					break;
				case Node::Type::DayNameAbbreviated:
					str.append( cal.dayNameShortNative( _day_of_week ) );
					break;
				case Node::Type::DayNameFull:
					str.append( cal.dayNameNative( _day_of_week ) );
					break;

				} // switch
			} // for

			return str;
		} // toString


		//======================================================================
		// Node
		//======================================================================

		// Constructor
		DateParser::Node::Node(DateParser::Node::Type _type, const QString& _value)
		{
			m_eType = _type;
			m_sValue = _value;
		}

	} // globalization
} // PCore


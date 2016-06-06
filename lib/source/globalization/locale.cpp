//##############################################################################
//#	c-date:	Jun-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include "include/pcore/globalization/locale.h"


//==============================================================================
// Constants
//==============================================================================

const char *calendar_name[] = {

							"Persian calendar (Iran)",
							"Persian calendar (Afghanistan)",
							"Islamic calendar",
							"Gregorian calendar"
						};


const char *calendar_name_native[] = {

							"گاهشمار هجری-شمسی",
							"جنتری افغانستان",
							"التقويم الهجري‎‎",
							"Gregorian calendar"
						};


const PCore::globalization::Locale::Calendar::Day start_days[] = {
			PCore::globalization::Locale::Calendar::Day::Saturday,	//! Persian Calendar
			PCore::globalization::Locale::Calendar::Day::Saturday,	//! Afganestan Calendar
			PCore::globalization::Locale::Calendar::Day::Monday,	//! Hijri Calendar
			PCore::globalization::Locale::Calendar::Day::Monday,	//! Georgian Calendar
		};


const char *days_name[] = {
				//! Iranian Calendar Hejri shamsi
				"Shanbeh","Yekshanbeh","Doshanbeh","Sehshanbeh","Chaharshanbeh",
				"Panjshanbeh", "Jomeh",

				//! Afghanistan's calendar
				"Shanbeh","Yekshanbeh","Doshanbeh","Sehshanbeh","Chaharshanbeh",
				"Panjshanbeh", "Jomeh",

				//! Hijri
				"al-lthnayn", "ath-Thalatha'","al-Arbi'a'",
				"al-Khamees", "al-Jum'ah", "as-Sabt", "al-Ahad",

				//! Gregorian
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
				"Saturday", "Sunday"
			};


const char *days_name_short[] = {
				//! Iranian Calendar Hejri shamsi TODO: must be optimized
				"Shanbeh","Yek","Do","Seh","Chahar", "Panj", "Jomeh",

				//! Afghanistan's calendar
				"Shanbeh","Yek","Do","Seh","Chahar", "Panj", "Jomeh",

				//! Hijri  TODO:
				"al-lthnayn", "ath-Thalatha'","al-Arbi'a'",
				"al-Khamees", "al-Jum'ah", "as-Sabt", "al-Ahad",

				//! Gregorian
				"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
			};


const char *days_name_short_native[] = {
				//! Iranian Calendar Hejri shamsi TODO: must be optimized
				"ش","ی","د","س","چ", "پ", "ج",

				//! Afghanistan's calendar
				"ش","ی","د","س","چ", "پ", "ج",

				//! Hijri  TODO:
				"al-lthnayn", "ath-Thalatha'","al-Arbi'a'",
				"al-Khamees", "al-Jum'ah", "as-Sabt", "al-Ahad",

				//! Gregorian
				"Mony", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
			};


const char *days_name_native[] = {
				//! Iranian Calendar Hejri shamsi
				"شنبه","یکشنبه","دوشنبه","شه شنبه","چهارشنبه",
				"پنج شنبه", "جمعه",

				//! Afghanistan's calendar
				"شنبه","یکشنبه","دوشنبه","شه شنبه","چهارشنبه",
				"پنج شنبه", "جمعه",

				//! Hijri
				"الإثْنَين", "الثَلاثاء", "الأربَعاء","الخَميس",
				"الجُمُعة", "السَبْت", "الأحَد",

				//! Gregorian
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
				"Saturday", "Sunday"
				};


const char* months_name[] = {
				//! Iranian Calendar Hejri shamsi
				"Farvardin","Ordibehesht","Khordad","Tir",
				"Mordad", "Shahrivar", "Mehr", "Aban",
				"Azar", "Dey", "Bahman", "Esfand",

				//! Afghanistan's calendar
				"Hamal","Sor","Javza","Saratan",
				"Asad","Sonboleh","Mizan", "Agrab",
				"Ghos", "Jadi", "Dlo", "Hoot",

				//! Hijri
				"Muharram", "Safar","Rabi I", "Rabi II",
				"Jumada I", "Jumada II", "Rajab", "Sha'ban",
				"Ramadan", "Shawwal", "Dhu'l-Qa'dah", "Dhu'l-Hijja",

				//! Gregorian
				"January", "February", "March", "April",
				"May",	"June", "July", "August",
				"September", "October", "November", "December"

				};


const char* months_name_short[] = {
				//! Iranian Calendar Hejri shamsi TODO:
				"Far","Ord","Kho","Tir",
				"Mor", "Sha", "Meh", "Aba",
				"Aza","Dey", "Bah", "Esf",

				//! Afghanistan's calendar TODO
				"Ham","Sor","Jav","Sar","Asa","Son","Miz",
				"Agr", "Gho", "Jad", "Dlo", "Hoo",

				//! Hijri TODO:
				"Muh", "Saf","Ra1", "Ra2", "Ju1", "Jum2", "Raj", "Sha", "Ram",
				"Sha", "DhQ", "DhH",

				//! Gregorian
				"Jan", "Feb", "Mar", "Apr", "May",	"Jun", "Jul",
				"Aug", "Sep", "Oct", "Nov", "Dec"

				};


const char* months_name_native[] = {
				//! Iranian Calendar Hejri shamsi
				"فروردین","اردیبهشت","خرداد","تیر",
				"مرداد", "شهریور", "مهر", "آبان",
				"آذر","دی", "بهمن", "اسفند",

				//! Afghanistan's calendar
				"حَمَل","ثور","جَوزا","سرطان","اسد"," سُنبُله","میزان",
				"عقرب","قوس","جَدْی","دلو","حوت",

				//! Hijri
				"مُحَرَّم", "صَفَر","رَبيع الأوّل", "رَبيع الثاني", "جُمادى الأولى", "جُمادى الآخرة",
				"رَجَب", "شَعْبان", "رَمَضان", "شَوّال", "ذو القعدة",	"ذو الحجة",

				//! Gregorian
				"January", "February", "March", "April", "May",	"June", "July",
				"August", "September", "October", "November", "December"

				};


const char* months_name_short_native[] = {
				//! Iranian Calendar Hejri shamsi TODO:
				"فروردین","اردیبهشت","خرداد","تیر",
				"مرداد", "شهریور", "مهر", "آبان",
				"آذر","دی", "بهمن", "اسفند",

				//! Afghanistan's calendar TODO
				"حَمَل","ثور","جَوزا","سرطان","اسد"," سُنبُله","میزان",
				"عقرب","قوس","جَدْی","دلو","حوت",

				//! Hijri TODO:
				"مُحَرَّم", "صَفَر","رَبيع الأوّل", "رَبيع الثاني", "جُمادى الأولى", "جُمادى الآخرة",
				"رَجَب", "شَعْبان", "رَمَضان", "شَوّال", "ذو القعدة",	"ذو الحجة",

				//! Gregorian
				"Jan", "Feb", "Mar", "Apr", "May",	"Jun", "Jul",
				"Aug", "Sep", "Oct", "Nov", "Dec"

				};


//==============================================================================
// Calendar
//==============================================================================

namespace PCore
{
	namespace globalization
	{

		//! constructor
		Locale::Calendar::Calendar( Locale::Calendar::Type _type )
		{
			m_eType = _type;
		}

		//! getName
		QString Locale::Calendar::getName( void ) const
		{
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;
			return calendar_name[ (int)m_eType ];
		}

		//! name
		QString Locale::Calendar::name( void ) const
		{
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;
			return calendar_name[ (int)m_eType ];
		}

		//! getNativeName
		QString Locale::Calendar::getNativeName( void ) const
		{
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;
			return calendar_name_native[ (int)m_eType ];
		}

		//! nativeName
		QString Locale::Calendar::nativeName( void ) const
		{
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;
			return calendar_name_native[ (int)m_eType ];
		}

		//! getDayName
		QString Locale::Calendar::getDayName( int _day ) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name[ ((int)m_eType*7) + _day - 1 ];
		}


		//! dayName
		QString Locale::Calendar::dayName( int _day ) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name[ ((int)m_eType*7) + _day - 1];
		}

		//! getDayNameShort
		QString Locale::Calendar::getDayNameShort(int _day) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_short[ ((int)m_eType*7) + _day - 1 ];
		}


		//! dayNameShort
		QString Locale::Calendar::dayNameShort(int _day) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_short[ ((int)m_eType*7) + _day - 1 ];
		}


		//! getDayNameShortNative
		QString Locale::Calendar::getDayNameShortNative( int _day ) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_short_native[ ((int)m_eType*7) + _day - 1 ];
		}


		//! getDayNameShortNative
		QString Locale::Calendar::dayNameShortNative( int _day ) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_short_native[ ((int)m_eType*7) + _day - 1 ];
		}


		//! getDayNameNative
		QString Locale::Calendar::getDayNameNative(int _day) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_native[ ((int)m_eType*7) + _day - 1 ];
		}


		//! dayNameNative
		QString Locale::Calendar::dayNameNative( int _day ) const
		{
			if ( ( _day < 1 ) || ( _day > 7 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return days_name_native[ ((int)m_eType*7) + _day - 1 ];
		}


		//! getMonthName
		QString Locale::Calendar::getMonthName( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name[ ((int)m_eType*12) + _month - 1 ];
		}


		//! monthName
		QString Locale::Calendar::monthName( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name[ ((int)m_eType*12) + _month - 1 ];
		}


		//! getMonthNameNative
		QString Locale::Calendar::getMonthNameNative( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_native[ ((int)m_eType*12) + _month - 1 ];
		}


		//! monthNameNative
		QString Locale::Calendar::monthNameNative( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_native[ ((int)m_eType*12) + _month - 1 ];
		}


		//! getMonthNameShort
		QString Locale::Calendar::getMonthNameShort( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_short[ ((int)m_eType*12) + _month - 1 ];
		}


		//! monthNameShort
		QString Locale::Calendar::monthNameShort( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_short[ ((int)m_eType*12) + _month - 1 ];
		}


		//! getMonthNameShortNative
		QString Locale::Calendar::getMonthNameShortNative( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_short_native[ ((int)m_eType*12) + _month - 1 ];
		}


		//! monthNameShortNative
		QString Locale::Calendar::monthNameShortNative( int _month ) const
		{
			if ( ( _month  < 1 ) || ( _month  > 12 ) ) return nullptr;
			if ( m_eType == Calendar::Type::Invalid ) return nullptr;

			return months_name_short_native[ ((int)m_eType*12) + _month - 1 ];
		}


		// getDayByName
		int Locale::Calendar::getDayNumberByName( const QString& _name ) const
		{
			if ( _name.isNull() ) return -1;
			if ( m_eType == Calendar::Type::Invalid ) return -1;

			int index = (int)m_eType * 7;
			QString name = _name.toLower();
			for ( int i = index ; i < index + 7 ; i++ )
			{
				if ( name == QString(days_name[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(days_name_native[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(days_name_short[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(days_name_short_native[i]).toLower() ) return ( i - index ) + 1;
			}
			return -1;
		}


		// dayByName
		int Locale::Calendar::dayNumberByName( const QString& _name ) const
		{
			return getDayNumberByName( _name );
		}


		// getMonthNumberByName
		int Locale::Calendar::getMonthNumberByName( const QString& _name ) const
		{
			if ( _name.isNull() ) return -1;
			if ( m_eType == Calendar::Type::Invalid ) return -1;

			int index = (int)m_eType * 12;
			QString name = _name.toLower();
			for ( int i = index ; i < index + 12 ; i++ )
			{
				if ( name == QString(months_name[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(months_name_native[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(months_name_short[i]).toLower() ) return ( i - index ) + 1;
				if ( name == QString(months_name_short_native[i]).toLower() ) return ( i - index ) + 1;
			}
			return -1;
		}


		// dayByName
		int Locale::Calendar::monthNumberByName( const QString& _name ) const
		{
			return getMonthNumberByName( _name );
		}


		//! startDay
		Locale::Calendar::Day Locale::Calendar::getStartDay( void ) const
		{
			if ( m_eType == Calendar::Type::Invalid ) return Day::Saturday;
			return start_days[(int)m_eType];
		}


		//! startDay
		Locale::Calendar::Day Locale::Calendar::startDay() const
		{
			if ( m_eType == Calendar::Type::Invalid ) return Day::Saturday;
			return start_days[(int)m_eType];
		}

	} // globalization
} // PCore


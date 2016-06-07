//##############################################################################
//#	title:	Test for calendars in globalization
//#	c-date:	May-25-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include <pcore/pcore.h>
#include <QDebug>


using namespace PCore::core;
using namespace PCore::globalization;

int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// Persian Calendar
	//=====================================

	qDebug() << "-------------------------------------";
	qDebug() << "Persian calendar (Jalali)";
	qDebug() << "-------------------------------------\n";

	qDebug() << "From string:        "
			 << PersianCalendar::fromString( "یکشنبه 12 مرداد 1396",
													"DDDD DD MMMM yyyy" );

	qDebug() << "Formated (MM-DD-yy):"
			 << PersianCalendar( 1395, 11, 2 ).toString( "MM-DD-yy" );

	/*
	 * Start day for the Persian calendar is 22nd March 622 A.D in
	 * Gregorian Calendar.
	 */
	qDebug() << "Start Date:         "
			 << PersianCalendar::fromQDate( QDate( 622,3,22 ) )
			 << QDate( 622,3, 22 );


	qDebug() << "Today:              "
			 << PersianCalendar::currentDate( );



	//=====================================
	//  Hijri Calendar
	//=====================================

	qDebug() << "\n\n\n-------------------------------------";
	qDebug() << "Hijri calendar ";
	qDebug() << "-------------------------------------\n";

	qDebug() << "From string:        "
			 << HijriCalendar::fromString( "12 رَمَضان 1437",
													"DD MMMM yyyy" );

	qDebug() << "Formated (MM-DD-yy):"
			 << HijriCalendar( 1422, 11, 2 ).toString( "MM-DD-yy" );


	/*
	 * Start day for the Hijri Calendar is 19 June 622 A.D in Gregorian
	 * Calendar or 16 June 622 A.D in Julian Calander.
	*/
	qDebug() << "Start Date:         "
			 << HijriCalendar::fromQDate( QDate( 622,7,19 ) )
			 << QDate( 622,7,19 );

	qDebug() << "Today:              "
			 << HijriCalendar::currentDate( );


	return 0;
}


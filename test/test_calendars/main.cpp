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

	qDebug() << PersianCalendar::fromString( "یکشنبه 12 مرداد 1396",
													"DDDD DD MMMM yyyy" );
	qDebug() << PersianCalendar( 1395, 11, 2 ).toString( "yy-MM-DD" );
	qDebug() << PersianCalendar::fromQDate( QDate( 622,3,22 ) );
	qDebug() << PersianCalendar::fromQDate( QDate( 1986,5,14 ) );
	qDebug() << PersianCalendar::currentDate( );


	return 0;
}


//##############################################################################
//#	title:	Test for hashing classes
//#	c-date:	Apr-16-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include <pcore/pcore.h>
#include <qDebug>

int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// MD5
	//=====================================

	qDebug() << "MD5:" << PCore::core::Hash::md5( QString("hello") );


	//=====================================
	// SHA1
	//=====================================

	qDebug() << "SHA1:" << PCore::core::Hash::sha1( QString("hello") );


	//=====================================
	// City
	//=====================================

	qDebug() << "City:" << PCore::core::Hash::cityAsString( QString("hello") );


	//=====================================
	// crc32
	//=====================================

	qDebug() << "CRC32:" << PCore::core::Hash::crc32( QString("hello") );


	return 0;
}



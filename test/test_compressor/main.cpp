//##############################################################################
//#	title:	Test for Compressor class
//#	c-date:	Apr-17-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

/* Note:
 *    For executing this sample you need to copy lore.txt to bin directory.
 */

#include <pcore/pcore.h>
#include <qDebug>
#include <QByteArray>
#include <QFile>

using namespace PCore::core;

int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// MD5
	//=====================================


	// read from file
	QFile f( "lore.txt" );
	if ( f.open( QFile::ReadOnly ) == false )
	{
		PCORE_LOG_ERROR( "Can not open 'lore.txt'" );
		return -1;
	}
	QByteArray ar = f.readAll();
	f.close();


	// compressing using Deflate algorithm
	QByteArray res_deflate = Compressor::compress( ar,
												   Compressor::Format::RawDeflate,
												   Compressor::Level::BestCompression
												   );
	// compressing in GZip format
	QByteArray res_gzip = Compressor::compress( ar,
											   Compressor::Format::GZip,
											   Compressor::Level::BestCompression
											   );


	qDebug()<< "Original size:" << ar.size();
	qDebug()<< "Defalte:" << res_deflate.size();
	qDebug()<< "GZip:" << res_gzip.size();


	return 0;
}


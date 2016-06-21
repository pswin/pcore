//##############################################################################
//#	title:	Test for Compressor class
//#	c-date:	Apr-17-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################



#include <pcore/pcore.h>
#include <QDebug>
#include <QByteArray>
#include <QFile>

using namespace PCore::core;

int main()
{

	/* Note:
	 *  For executing this sample you need to copy lore.txt from directory of
	 *  sample to the bin directory.
	 */

	// initializing PCore
	PCORE_INIT();




	// reading from file
	QFile f( "lore.txt" );
	if ( f.open( QFile::ReadOnly ) == false )
	{
		PCORE_LOG_ERROR( "Cannot open 'lore.txt'" );
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


	qDebug()<< "Original size:         " << ar.size();
	qDebug()<< "Compresed with Defalte:" << res_deflate.size();
	qDebug()<< "Compresed with GZip:   " << res_gzip.size();


	return 0;
}


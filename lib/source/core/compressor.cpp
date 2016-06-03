//##############################################################################
//#	c-date:	Apr-13-2016
//#	author:	Pouya Shahinfar
//##############################################################################

#include "include/pcore/core/compressor.h"
#include "include/pcore/core/logger.h"
#include "include/pcore/core/exception.h"
#include <zlib.h>
#include <QFile>


#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096

namespace PCore
{
	namespace core
	{
		//! compress
		QByteArray Compressor::compress(const QByteArray& _in,
										 Compressor::Format _format,
										 Level _level
										)
		{
			z_stream zs;
			memset(&zs, 0, sizeof(zs));

			int compression_level = Z_DEFAULT_COMPRESSION;

			switch ( _level )
			{
				case Level::BestCompression:
					compression_level = Z_BEST_COMPRESSION;
					break;
				case Level::BestSpeed:
					compression_level = Z_BEST_SPEED;
					break;
				default:
					compression_level = Z_DEFAULT_COMPRESSION;
			}


			int ret;
			switch ( _format )
			{
				case Format::RawDeflate:
					ret = deflateInit( &zs, compression_level );
					break;
				case Format::GZip:
					ret = deflateInit2( &zs, compression_level,
									 Z_DEFLATED,
									 MOD_GZIP_ZLIB_WINDOWSIZE + 16,
									 MOD_GZIP_ZLIB_CFACTOR,
									 Z_DEFAULT_STRATEGY);
					break;
				default:
				ret = deflateInit( &zs, compression_level );

			}
			if ( ret != Z_OK )
			{
				PCORE_LOG_ERROR( "Initializing compression structure failed." );
				PCORE_THROW_EXCEPTION( std::runtime_error, "Initializing compression structure failed." );
				return QByteArray();
			}
			zs.next_in = (Bytef*)_in.data();
			zs.avail_in = _in.size();

			char out_buf[ 32 * PCORE_1KB ];
			QByteArray out;

			// retrieve the compressed bytes blockwise
			do {
				zs.next_out = reinterpret_cast<Bytef*>( out_buf );
				zs.avail_out = sizeof( out_buf );

				ret = deflate( &zs, Z_FINISH );

				if ( (uLong)out.size() < zs.total_out )
				{
					out.append( out_buf, zs.total_out - out.size() );
				}
			} while ( ret == Z_OK );

			deflateEnd( &zs );

			if ( ret != Z_STREAM_END )
			{
				QString msg = "Exception during decompression: " +
						QString::number(ret) + ", " + QString( zs.msg );
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return QByteArray();
			}

			return out;
		}

		//! compressFile
		bool Compressor::compressFile(
										const QString& _in_filename,
										const QString& _out_filename,
										Compressor::Format _format,
										Level _level
									)
		{
			QFile input_file( _in_filename );

			if ( input_file.open( QFile::ReadOnly ) == false )
			{
				QString msg = "Error in opening file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			QByteArray ar_in = input_file.readAll();
			input_file.close();

			QByteArray ar_out;
			try
			{
				ar_out = compress( ar_in, _format, _level );
			}
			catch ( ... )
			{
				QString msg = "Error in compressing file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			if ( ar_out.isEmpty() == true )
			{
				QString msg = "Error in compressing file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			QFile out_file( _out_filename );

			if ( out_file.open( QFile::WriteOnly) == false )
			{
				QString msg = "Error in opening file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			out_file.write( ar_out );
			out_file.flush();
			out_file.close();

			return true;
		} // compress


		//! decompress
		QByteArray Compressor::decompress(
										const QByteArray& _in,
										Compressor::Format _format
										)
		{
			z_stream zs;

			memset( &zs, 0, sizeof(zs) );


			int ret;
			switch ( _format )
			{
				case Format::RawDeflate:
					ret = inflateInit( &zs );
					break;
				case Format::GZip:
					ret = inflateInit2( &zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16 );
					break;
				default:
				ret = inflateInit( &zs );
			}

			if (  ret != Z_OK )
			{
				PCORE_LOG_ERROR( "Initializing decompression structure failed." );
				PCORE_THROW_EXCEPTION( std::runtime_error, "Initializing decompression structure failed." );
				return QByteArray();
			}

			zs.next_in = (Bytef*)_in.data();
			zs.avail_in = _in.size();

			char out_buf[ 32 * PCORE_1KB ];
			QByteArray out;


			// get the decompressed bytes blockwise using repeated calls to inflate
			do
			{
				zs.next_out = reinterpret_cast<Bytef*>( out_buf );
				zs.avail_out = sizeof( out_buf );

				ret = inflate( &zs, 0 );

				if ( (uLong)out.size() < zs.total_out )
				{
					out.append( out_buf, zs.total_out - out.size() );
				}
			} while ( ret == Z_OK );

			inflateEnd( &zs );

			if ( ret != Z_STREAM_END )
			{
				  QString msg = "Exception during decompression: "+
						  QString::number( ret ) + ", " + QString( zs.msg );
				  PCORE_LOG_ERROR( msg );
				  PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				  return QByteArray();
			}

			return out;
		} // decompress

		bool Compressor::decompressFile(
										const QString& _in_filename,
										const QString& _out_filename,
										Compressor::Format _format
									)
		{
			QFile input_file( _in_filename );

			if ( input_file.open( QFile::ReadOnly ) == false )
			{
				QString msg = "Error in opening file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			QByteArray ar_in = input_file.readAll();
			input_file.close();

			QByteArray ar_out;
			try
			{
				ar_out = decompress( ar_in, _format );
			}
			catch ( ... )
			{
				QString msg = "Error in decompressing file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			if ( ar_out.isEmpty() == true )
			{
				QString msg = "Error in decompressing file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			QFile out_file( _out_filename );

			if ( out_file.open( QFile::WriteOnly) == false )
			{
				QString msg = "Error in opening file: '" + _in_filename + "'.";
				PCORE_LOG_ERROR( msg );
				PCORE_THROW_EXCEPTION( std::runtime_error, msg.toStdString() );
				return false;
			}

			out_file.write( ar_out );
			out_file.flush();
			out_file.close();

			return true;
		} // decompressFile
	} // decompress



	// Core
} // PCore


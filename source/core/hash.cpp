//##############################################################################
//#	c-date:	Oct-25-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "include/pcore/core/hash.h"
#include "headers/core/hash/hash_city.h"
#include "headers/core/hash/hash_crc32.h"
#include "headers/core/hash/hash_md5.h"
#include "headers/core/hash/hash_sha1.h"


namespace PCore
{
	namespace core
	{

		//! crc32
		quint32 Hash::crc32( const QByteArray& _src, quint32 _seed )
		{
			return hash_crc32( (const uchar*)_src.data(), _src.size(), _seed );
		}

		//! crc32
		quint32 Hash::crc32(const QString& _str, quint32 _seed)
		{
			QByteArray ar = _str.toLocal8Bit();
			return hash_crc32( (const uchar*)ar.data(), ar.size(), _seed );
		}

		//! md5
		QString Hash::md5(const QByteArray& _src)
		{
			char buf[33];
			hash_md5( (unsigned char*)_src.data(),
						_src.size(), (unsigned char*)buf );
			buf[32] = '\0';
			return QString( buf );
		}

		//! md5
		QString Hash::md5(const QString& _src)
		{
			char buf[33];
			QByteArray ar = _src.toLocal8Bit();
			hash_md5( (unsigned char*)ar.data(),
						ar.size(), (unsigned char*)buf );
			buf[32] = '\0';
			return QString( buf );
		}

		//! cityAsString
		QString Hash::cityAsString( const QByteArray& _src )
		{
			return QString::number( CityHash64( _src.data(), _src.size() ) );
		}

		//! cityAsString
		QString Hash::cityAsString( const QString& _src )
		{
			QByteArray ar = _src.toLocal8Bit();
			return QString::number( CityHash64( ar.data(), ar.size() ) );
		}

		//! cityAsUnsignedInt
		quint64 Hash::cityAsUnsignedInt( const QByteArray& _src )
		{
			return CityHash64( _src.data(), _src.size() );
		}

		//! cityAsUnsignedInt
		quint64 Hash::cityAsUnsignedInt( const QString& _src )
		{
			QByteArray ar = _src.toLocal8Bit();
			return CityHash64( ar.data(), ar.size() );
		}

		//! sha1
		QString Hash::sha1( const QByteArray& _src )
		{
			quint8 digest[20];
			SHA1_CTX context;
			SHA1_Init(&context);
			SHA1_Update(&context, (const quint8*)_src.data(), _src.size() );
			SHA1_Final( &context, digest );

			char buf[41];
			unsigned char to_hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
			for (int i = 0; i < 20; i++)
			{
				#if  PCORE_ARCH_ENDIAN == PCORE_ARCH_BIG_ENDIAN
					buf[i * 2 + 1] = to_hex[digest[i] & 0x0F];
					buf[i * 2] = to_hex[digest[i] >> 4];
				#else
					buf[i * 2] = to_hex[digest[i] & 0x0F];
					buf[i * 2 + 1] = to_hex[digest[i] >> 4];
				#endif
			}
			buf[40] = '\0';
			return QString(buf);
		}

		//! sha1
		QString Hash::sha1( const QString& _src )
		{
			QByteArray ar = _src.toLocal8Bit();
			return Hash::sha1( ar );
		}

	} // core
} // PCore


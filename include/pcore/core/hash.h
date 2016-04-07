//##############################################################################
//#	title:	Hashing functions
//#	c-date:	Oct-25-2014
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_HASH_H
#define _PCORE_HASH_H

#include "../pcore_def.h"
#include "string.h"
#include <QtGlobal>
#include <QString>
#include <QByteArray>

namespace PCore
{
	namespace core
	{
		class PCORE_API Hash
		{
		public:

			/*!
			 * \brief Returns CRC32 hashed code from given byte array
			 * \param _src: Source buffer
			 * \param _seed: Seed
			 * \return Returns CRC32 hashed code from given byte array
			 */
			static quint32 crc32( const QByteArray& _src,
								  quint32 _seed = 0
								);


			/*!
			 * \brief Returns CRC32 hashed code from given string
			 * \param _src: Source string
			 * \param _seed: Seed
			 * \return Returns CRC32 hashed code from given string
			 */
			static quint32 crc32( const QString& _str,
										  quint32 _seed = 0
										);


			/*!
			 * \brief Returns MD5 hashed string of given byte array
			 * \param _src: Source byte array
			 * \return Returns MD5 hashed string of given byte array
			 */
			static QString md5( const QByteArray& _src );


			/*!
			 * \brief Returns MD5 hashed string of given string
			 * \param _src: Source string
			 * \return Returns MD5 hashed string of given string
			 */
			static QString md5( const QString& _src );


			/*!
			 * \brief Hashes given byte array by City algorithm
			 * \param _src: Source array
			 * \return Returns hashed byte array as a string
			 */
			static QString cityAsString( const QByteArray& _src );


			/*!
			 * \brief Hashes given string by City algorithm
			 * \param _src: Source string
			 * \return Returns hashed string
			 */
			static QString cityAsString( const QString& _src );


			/*!
			 * \brief  Hashes given byte array by using City algorithm
			 * \param _src: Source byte array
			 * \return Returns hashed array as a unsigned integer
			 */
			static quint64 cityAsUnsignedInt( const QByteArray& _src );

			/*!
			 * \brief  Hashes given string by using City algorithm
			 * \param _src: Source byte array
			 * \return Returns hashed string as a unsigned integer
			 */
			static quint64 cityAsUnsignedInt( const QString& _src );


			/*!
			 * \brief  Hashes given byte array by using SHA1 algorithm
			 * \param _src: Source byte array
			 * \return Hashed string in SHA1 algorithm
			 */
			static QString sha1( const QByteArray& _src );


			/*!
			 * \brief  Hashes given string by using SHA1 algorithm
			 * \param _src: Source byte array
			 * \return Hashed string in SHA1 algorithm
			 */
			static QString sha1( const QString& _src );

		}; // Hash
	} // core
} // PCore


//=====================================
// typedefs
//=====================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PHash = PCore::core::Hash;
#endif


#endif // _PCORE_HASH_H

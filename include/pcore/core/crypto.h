//##############################################################################
//#	title:	File logger interface
//#	c-date:	Apr-04-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_CRYPTO_H
#define _PCORE_CRYPTO_H

#include "../pcore_def.h"
#include <QString>
#include <QByteArray>

namespace PCore
{
	namespace core
	{
		class PCORE_API Crypto
		{
			//=====================================
			// enums
			//=====================================
		public:
			enum class AESBits
			{
				_128,
				_256
			};

			//=====================================
			// public methods
			//=====================================
		public:

			/*!
			 * \brief Encrypts given array to AES coded array
			 * \param _src: Source arrray
			 * \param _key: Key
			 * \param _bits: Bits
			 * \return encrypted array
			 */
			static QByteArray aesEncrypt(	const QByteArray& _src,
											const QString& _key,
											AESBits _bits = AESBits::_128
										);

			/*!
			 * \brief Encrypts given string to AES coded string
			 * \param _src: Source string
			 * \param _key: Key
			 * \param _bits: Bits
			 * \return encrypted string
			 */
			static QString aesEncrypt(	const QString& _src,
										const QString& _key,
										AESBits _bits = AESBits::_128
									);


			/*!
			 * \brief Decrypts given array to AES coded array
			 * \param _src: Source array
			 * \param _key: Key
			 * \param _bits: Bits
			 * \return decrypted array
			 */
			static QByteArray aesDecrypt( const QByteArray& _src,
										  const QString& _key,
										  AESBits _bits = AESBits::_12
										);

			/*!
			 * \brief Encrypts given string to AES coded string
			 * \param _src: Source string
			 * \param _key: Key
			 * \param _bits: Bits
			 * \return decrypted string
			 */
			static QString aesDecrypt( const QString &_src,
									   const QString &_key,
									   AESBits _bits
									   );

		}; // Crypto
	} // core
} // PCore



//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PCrypto = PCore::core::Crypto;
#endif

#endif // _PCORE_CRYPTO_H


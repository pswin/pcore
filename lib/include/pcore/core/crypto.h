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
				_128 = 128,
				_192 = 192,
				_256 = 256
			};

			//=====================================
			// public members
			//=====================================
		public:

			static QByteArray Default_AES_IVEC;
			static QByteArray Default_DES_IVEC;


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
			static QByteArray aesEncrypt(const QByteArray& _src,
											const QByteArray& _key,
											QByteArray *iv = &Crypto::Default_AES_IVEC,
											AESBits _bits = AESBits::_256
										);


			/*!
			 * \brief Decrypts given array to AES coded array
			 * \param _src: Source array
			 * \param _key: Key
			 * \param _bits: Bits
			 * \return decrypted array
			 */
			static QByteArray aesDecrypt(const QByteArray& _src,
										 const QByteArray &_key,
										 const QByteArray *iv = &Crypto::Default_AES_IVEC,
										 AESBits _bits = AESBits::_256
										);


			/*!
			 * \brief Encrypts given array to DES coded array.
			 * \param _src:	Source array.
			 * \param _key: Encryption key.
			 * \return Encoded array.
			 */
			static QByteArray desEncrypt(const QByteArray& _src,
										 const QByteArray& _key,
										 QByteArray &_ivec = Crypto::Default_DES_IVEC
										);


			/*!
			 * \brief Decrypts given array from DES coded array.
			 * \param _src:	Source array.
			 * \param _key: Decryption key.
			 * \return decoded array.
			 */
			static QByteArray desDecrypt(const QByteArray& _src,
										 const QByteArray& _key,
										 const QByteArray& _ivec = Crypto::Default_DES_IVEC
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


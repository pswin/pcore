//##############################################################################
//#	c-date:	Jun-10-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include "include/pcore/cryptography/aes.h"
#include "include/pcore/math/random.h"
#include "include/pcore/core/logger.h"
#include <QByteArray>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <QDebug>


//==============================================================================
// macros
//==============================================================================

#define PCORE_LOG_ERROR_OSSL(__text) \
			PCORE_LOG_ERROR ( __text " '" + \
			QString( ERR_error_string(ERR_get_error(), NULL) ) + "'" )


//! helper macro for calculating block size
#define _PCORE_HELPER_TO_BLOCK(__size,__block_size )\
					(((__size+__block_size)/__block_size) * __block_size )


#define PCORE_AES_SALT_SIZE 16


//==============================================================================
// functions
//==============================================================================


/*!
 * \brief Returns cipher type by specified block size.
 */
inline const EVP_CIPHER* get_cipher_type(
								PCore::cryptography::AES::BlockSize _size )
{
	switch ( _size )
	{
		case PCore::cryptography::AES::BlockSize::_128:
			return EVP_aes_128_cbc();
		case PCore::cryptography::AES::BlockSize::_192:
			return EVP_aes_192_cbc();
		case PCore::cryptography::AES::BlockSize::_256:
			return EVP_aes_256_cbc();
	}

	return EVP_aes_128_cbc();
}


//==============================================================================
// code
//==============================================================================
namespace PCore
{
	namespace cryptography
	{

		//! constructor
		AES::AES( const QByteArray _init_vec,
				  const QByteArray _salt,
				  AES::BlockSize _block_size,
				  QObject* _parent ) :
			QObject( _parent )
		{
			m_IV = _init_vec;
			m_Salt = _salt;
			m_eBlockSize = _block_size;
		}


		//! setPass
		void AES::setPass( const QByteArray& _pass )
		{
			m_Pass = _pass;
		}


		//! setIV
		void AES::setIV( const QByteArray& _iv )
		{
			m_IV = _iv;
		}


		//! getIV
		QByteArray AES::getIV( void ) const
		{
			return m_IV;
		}

		//! setBlockSize
		void AES::setBlockSize( AES::BlockSize _block_size )
		{
			m_eBlockSize = _block_size;
		}


		//! getBlockSize
		AES::BlockSize AES::getBlockSize() const
		{
			return m_eBlockSize;
		}


		//! setSalt
		void AES::setSalt( const QByteArray& _salt )
		{
			m_Salt = _salt;
		}


		//! getSalt
		QByteArray AES::getSalt( void ) const
		{
			return m_Salt;
		}


		//! encrypt
		QByteArray AES::encrypt( const QByteArray& _data, bool _attach_salt )
		{
			return AES::encryptEX( m_Pass, _data, m_IV,
								   m_Salt, m_eBlockSize, _attach_salt );
		}


		//! decrypt
		QByteArray AES::decrypt( const QByteArray& _data )
		{
			return AES::decryptEX( m_Pass, _data, m_IV, m_Salt, m_eBlockSize );
		}


		//======================================================================
		// static methods
		//======================================================================

		//! encryptEX
		QByteArray AES::encryptEX(const QByteArray& _pass,
								   const QByteArray& _data,
								   QByteArray& _iv,
								   QByteArray& _salt,
								   AES::BlockSize _block_size,
								  bool _attach_salt )
		{
			int bsize = (int)_block_size;
			const EVP_CIPHER* cipher = get_cipher_type( _block_size );

			if ( _iv.isNull() == true )
			{
				_iv = math::Random::randomByteArray( bsize / 8 );
			}

			if ( _salt.isNull() == true )
			{
				_salt = math::Random::randomByteArray( PCORE_AES_SALT_SIZE );
			}
			else
			{
				if ( _salt.size() != PCORE_AES_SALT_SIZE )
				{
					PCORE_LOG_ERROR( "Encryption failed, due to wrong salt size.");
					return QByteArray();
				}
			}


			// generating key
			unsigned char* key = new unsigned char[ bsize / 8 ];


			int key_size = EVP_BytesToKey( cipher, EVP_sha1(),
										   (unsigned char*)_salt.constData(),
										   (unsigned char*)_pass.constData(),
										   _pass.length(),
										   1, key,
										   (unsigned char*)_iv.constData() );

			if ( key_size != ( bsize/8 ) )
			{
				PCORE_LOG_ERROR( "Encryption failed; due to wrong key size: " +
								 QString::number( key_size ) );
				return QByteArray();
			}

			EVP_CIPHER_CTX* en = EVP_CIPHER_CTX_new();

			if ( en == nullptr )
			{
				PCORE_LOG_ERROR_OSSL( "Encryption failed:" );
				return QByteArray();
			}

			if( EVP_EncryptInit_ex( en, cipher, NULL,
									key, (unsigned char*)_iv.data() ) == 0 )
			{
				PCORE_LOG_ERROR_OSSL( "Encryption failed:" );
				return QByteArray();
			}

			int out_len = _PCORE_HELPER_TO_BLOCK( _data.size(), AES_BLOCK_SIZE );
			int c_len = out_len;
			int final_len = 0;
			unsigned char *out = new unsigned char[ out_len ];

			if( EVP_EncryptInit_ex( en, NULL, NULL, NULL, NULL ) == 0 )
			{
				PCORE_LOG_ERROR_OSSL( "Encryption failed:" );
				return QByteArray();
			}

			if( EVP_EncryptUpdate( en, out, &c_len,
							(unsigned char *)_data.constData(), _data.size() ) == 0 )
			{
				PCORE_LOG_ERROR_OSSL( "Encryption failed:" );
				return QByteArray();
			}
			final_len += c_len;

			if( EVP_EncryptFinal( en, out + c_len, &c_len ) == 0 )
			{
				PCORE_LOG_ERROR_OSSL( "Encryption failed:" );
				return QByteArray();
			}
			final_len += c_len;

			EVP_CIPHER_CTX_free( en );

			//ciphertext
			QByteArray ar;
			if ( _attach_salt == true )
			{
				ar.append( "Salted__" );
				ar.append( _salt );
			}
			ar.append( (char*)out, final_len );

			delete[] out;

			return ar;
		} // encryptEX


		//! decryptEX
		QByteArray AES::decryptEX( const QByteArray& _pass,
								   const QByteArray& _data,
								   QByteArray& _iv,
								   const QByteArray& _salt,
								   AES::BlockSize _block_size
								  )
		{
			QByteArray in;
			QByteArray salt = _salt;
			int bsize = (int)_block_size;
			const EVP_CIPHER* cipher = get_cipher_type( _block_size );


			if( QString( _data.mid( 0, 8 ) ) == "Salted__" )
			{
				salt = _data.mid( 8, PCORE_AES_SALT_SIZE );
				in = _data.mid( 8 + PCORE_AES_SALT_SIZE );
			}
			else
			{
				if ( _salt.isNull() == false )
				{
					if ( _salt.size() != PCORE_AES_SALT_SIZE )
					{
						PCORE_LOG_ERROR( "Decryption failed, due to wrong salt size.");
						return QByteArray();
					}

					in = _data;
				}
				else
				{
					PCORE_LOG_ERROR( "Could not load salt from data." );
					return QByteArray();
				}
			}


			// generating key
			unsigned char* key = new unsigned char[ bsize / 8 ];
			int key_size = EVP_BytesToKey( cipher, EVP_sha1(),
									(unsigned char*)salt.constData(),
									(unsigned char*)_pass.constData(),
									_pass.length(), 1, key,
									(unsigned char*)_iv.data() );

			if( key_size != ( bsize / 8 ) )
			{
				PCORE_LOG_ERROR( "Decryption failed; due to wrong key size: " +
								 QString::number( key_size ) );
				return QByteArray();
			}

			EVP_CIPHER_CTX *de = EVP_CIPHER_CTX_new();

			if ( de == nullptr )
			{
				PCORE_LOG_ERROR_OSSL( "Decryption failed:" );
			}

			if( EVP_DecryptInit_ex( de, cipher, NULL, key,
									(unsigned char*)_iv.constData() ) == 0 )
			{
				PCORE_LOG_ERROR_OSSL( "Decryption failed:" );
				return QByteArray();
			}

			int out_len = _PCORE_HELPER_TO_BLOCK( in.size(), AES_BLOCK_SIZE );
			int bytes_writen = out_len;
			int final_len = 0;
			unsigned char *out =  new unsigned char[ out_len ];

			//May have to do this multiple times for large data???
			if( EVP_DecryptUpdate( de, out, &bytes_writen,
							(unsigned char *)in.constData(), in.size() ) != 1 )
			{
				PCORE_LOG_ERROR_OSSL( "Decryption failed:" );
				return QByteArray();
			}
			final_len += bytes_writen;

			if( EVP_DecryptFinal_ex( de, out + bytes_writen , &bytes_writen ) != 1 )
			{
				qDebug() <<  bytes_writen + AES_BLOCK_SIZE << out_len << bytes_writen << in.size();
				PCORE_LOG_ERROR_OSSL( "Decryption failed:" );
				return QByteArray();
			}
			final_len += bytes_writen;

			EVP_CIPHER_CTX_free( de );

			QByteArray ar ( (char*)out, final_len );
			delete[] out;
			return ar;
		} // decryptEX

	} // cryptography
} // PCore


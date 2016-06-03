//##############################################################################
//#	c-date: May-25-2016
//#	author:	Pouya Shahinfar (pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include "include/pcore/core/crypto.h"
#include "include/pcore/core/logger.h"


//==============================================================================
// Macros
//==============================================================================

//! block size for diffrent alghoritms
#define PCORE_DES_BLOCK_SIZE 8
#define PCORE_AES_BLOCK_SIZE AES_BLOCK_SIZE

//! helper macro for calculating block size
#define _PCORE_HELPER_TO_BLOCK(__size,__block_size )\
					(((__size+__block_size)/__block_size) * __block_size )


//==============================================================================
// code
//==============================================================================

namespace PCore
{
	namespace core
	{

		//======================================================================
		// static members
		//======================================================================

		QByteArray Crypto::Default_AES_IVEC = QByteArray( "AABBCCDDAABBCCDD" );
		QByteArray Crypto::Default_DES_IVEC = QByteArray( "ABCDEFGH" );


		//======================================================================
		// code
		//======================================================================


		QByteArray Crypto::aesEncrypt(const QByteArray &_src,
										const QByteArray &_key,
										QByteArray* iv,
										Crypto::AESBits _bits )
		{
			if ( _key.length() < ( (int)_bits/8 ) )
			{
				PCORE_LOG_ERROR( "Passwords must be at least " +
								 QString::number( (int)_bits/8 ) + "characters" );
				return QByteArray();
			}

			unsigned char iv_enc[ PCORE_AES_BLOCK_SIZE ];
			if ( iv->isEmpty() == true )
			{
				RAND_bytes( iv_enc, PCORE_AES_BLOCK_SIZE );
				iv->append( (const char*)iv_enc, PCORE_AES_BLOCK_SIZE );
			}
			else
			{
				memcpy( iv_enc, iv->data(), PCORE_AES_BLOCK_SIZE );
			}


			// output buf
			int out_len = _PCORE_HELPER_TO_BLOCK( _src.size(), PCORE_AES_BLOCK_SIZE );

			unsigned char *out = new unsigned char[out_len ];
			memset( out, 0, out_len );

			// creating key
			AES_KEY enc_key;
			AES_set_encrypt_key( (unsigned char*)_key.data(),
												(int)_bits, &enc_key );

			AES_cbc_encrypt( (unsigned char*)_src.data(), out, _src.size(),
							 &enc_key, iv_enc, AES_ENCRYPT );

			QByteArray ar( (const char*)out, out_len );
			delete[] out;
			return ar;
		} // aesEncrypt



		//! aesDecrypt
		QByteArray Crypto::aesDecrypt(const QByteArray &_src,
								const QByteArray &_key,
								const QByteArray *iv,
								Crypto::AESBits _bits )
		{
			if ( _key.length() < ( (int)_bits/8 ) )
			{
				PCORE_LOG_ERROR( "Passwords must be at least " +
								 QString::number( (int)_bits/8 ) + "characters" );
				return QByteArray();
			}

			if ( iv->size() != PCORE_AES_BLOCK_SIZE )
			{
				PCORE_LOG_ERROR( "IV size is less than AES block size." );
				return QByteArray();
			}

			// output buf
			int out_len = _PCORE_HELPER_TO_BLOCK( _src.size(), PCORE_AES_BLOCK_SIZE );
			unsigned char *out = new unsigned char[ out_len ];
			memset( out, 0, out_len );

			// creating key
			AES_KEY dec_key;
			AES_set_decrypt_key( (unsigned char*)_key.data(),
												(int)_bits, &dec_key );

			// decrypt
			AES_cbc_encrypt( (unsigned char*)_src.data(), out, _src.size(),
							 &dec_key, (unsigned char*)iv->data(), AES_DECRYPT );

			QByteArray ar((const char*)out, out_len );
			delete[] out;
			return ar;
		} // aesDecrypt


		//! desEncrypt
		QByteArray Crypto::desEncrypt(
									const QByteArray &_src,
									const QByteArray &_key,
									QByteArray &_ivec )
		{
			if ( _key.length() < 8 )
			{
				PCORE_LOG_ERROR( "DES failed.Key must be at least 8 characters." );
				return QByteArray();
			}


			// ivec
			DES_cblock iv;
			if ( _ivec.isEmpty() )
			{
				RAND_bytes( iv, PCORE_DES_BLOCK_SIZE );
				_ivec.append( (const char*)iv, PCORE_DES_BLOCK_SIZE );
			}
			else
			{
				if ( _ivec.size() != PCORE_DES_BLOCK_SIZE )
				{
					PCORE_LOG_ERROR( "DES failed.IVEC must be at least 8 characters." );
					return QByteArray();
				}

				memcpy( iv, _ivec.data(), PCORE_DES_BLOCK_SIZE );
			}


			DES_cblock key_2;
			DES_key_schedule schedule;
			int out_len = _PCORE_HELPER_TO_BLOCK( _src.size(), PCORE_DES_BLOCK_SIZE ) ;
			unsigned char *out = new unsigned char[ _src.size() ];
			memset( out, 0, out_len );


			// Prepare the key
			memcpy( key_2, _key.data() ,8 );
			DES_set_odd_parity( &key_2 );
			if ( DES_set_key_checked( &key_2, &schedule ) != 0 )
			{
				PCORE_LOG_ERROR( "DES failed. Cannot set key." );
				return QByteArray();
			}

			// Encryption
			DES_ncbc_encrypt( (unsigned char*)_src.data(), out,
							   _src.size() , &schedule, &iv, DES_ENCRYPT );

			QByteArray ar( (const char*)out, out_len );
			delete[] out;
			return ar;
		} // desEncrypt


		//! desDecrypt
		QByteArray Crypto::desDecrypt(	const QByteArray &_src,
										const QByteArray &_key ,
										const QByteArray &_ivec
									)
		{
			if ( _key.length() < 8 )
			{
				PCORE_LOG_ERROR( "DES failed.Key must be at least 8 characters." );
				return QByteArray();
			}

			DES_cblock iv;
			if ( _ivec.size() != PCORE_DES_BLOCK_SIZE )
			{
				PCORE_LOG_ERROR( "DES failed.IVEC must be at least 8 characters." );
				return QByteArray();
			}
			memcpy( iv, _ivec.data(), PCORE_DES_BLOCK_SIZE );


			DES_cblock key_2;
			DES_key_schedule schedule;
			int out_len = _PCORE_HELPER_TO_BLOCK( _src.size(), PCORE_DES_BLOCK_SIZE ) ;
			unsigned char *out = new unsigned char[ out_len ];
			memset( out, 0, out_len );

			// Prepare the key
			memcpy( key_2, _key.data() ,8 );
			DES_set_odd_parity( &key_2 );
			if ( DES_set_key_checked( &key_2, &schedule ) != 0 )
			{
				PCORE_LOG_ERROR( "DES failed. Cannot set key." );
				return QByteArray();
			}


			// Decryption
			DES_ncbc_encrypt( (unsigned char *)_src.data(), out, _src.size(),
							   &schedule, &iv, DES_DECRYPT );

			QByteArray ar( (const char*)out );
			delete[] out;
			return ar;
		} // desDecrypt

	} // core
} // PCore


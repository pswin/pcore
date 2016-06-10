//##############################################################################
//#	c-date:	Jun-09-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "include/pcore/cryptography/rsa.h"
#include "include/pcore/core/logger.h"
#include <QByteArray>
#include <openssl/rsa.h>
#include <openssl/pem.h>

namespace PCore
{
	namespace cryptography
	{
		//! constructor
		Rsa::Rsa( bool _generate_keys, QObject* _parent ) :
			QObject( _parent )
		{
			if ( _generate_keys )
			{
				if ( setPrivateKey( Rsa::generatePrivateKey( ) ) == true )
				{
					setPublicKey( Rsa::generatePublicKey(getPrivateKey()) );
				}

			}
		} //! constructor


		//! copy constructor
		Rsa::Rsa( const Rsa& _obj )
		{
			if ( _obj.getPrivateKey().isEmpty() == false )
			{
				setPrivateKey( _obj.getPrivateKey() );
			}

			if ( _obj.getPublicKey().isEmpty() == false )
			{
				setPublicKey( _obj.getPublicKey() );
			}
		} // copy constructor


		//! move-constructor
		Rsa::Rsa( Rsa&& _obj )
		{
			m_PrivateKey = _obj.m_PrivateKey;
			m_pPrvKey = _obj.m_pPrvKey;
			_obj.m_pPrvKey = nullptr;

			m_PublicKey = _obj.m_PublicKey;
			m_pPubKey = _obj.m_pPubKey;
			_obj.m_pPubKey = nullptr;
		}


		//! destructor
		Rsa::~Rsa()
		{
			if ( m_pPrvKey != nullptr )
			{
				RSA_free( (RSA*)m_pPrvKey );
			}

			if ( m_pPubKey != nullptr )
			{
				RSA_free( (RSA*)m_pPubKey );
			}
		}


		//! encrypt
		QByteArray Rsa::encrypt( const QByteArray& _byte_array ,
								Padding _padding
							   )
		{
			if ( m_pPubKey == nullptr )
			{
				PCORE_LOG_ERROR( "Public key is not seted, encryption failed." );
				return QByteArray();
			}

			if ( _byte_array.isNull() == true )
			{
				PCORE_LOG_ERROR( "Input array for encryption is null." );
				return QByteArray();
			}

			int rsa_len = RSA_size( (RSA*)m_pPubKey );

			unsigned char* out = new unsigned char[ rsa_len ];

			int ret = RSA_public_encrypt(
								_byte_array.size(),
								(const unsigned char*)_byte_array.constData(),
								out, (RSA*)m_pPubKey,
								(int)_padding );

			if ( ret == -1 )
			{
				PCORE_LOG_ERROR( "Encryption failed for an unkown error." );
				return QByteArray();
			}

			QByteArray ar( (const char*)out, ret );
			delete[] out;

			return ar;
		} // encrypt


		//! decrypt
		QByteArray Rsa::decrypt( const QByteArray& _byte_array ,
								 Padding _padding
								)
		{
			if ( m_pPrvKey == nullptr )
			{
				PCORE_LOG_ERROR( "Private key is not seted, decryption failed." );
				return QByteArray();
			}

			if ( _byte_array.isEmpty() == true )
			{
				PCORE_LOG_ERROR( "Input array for decryption is empty." );
				return QByteArray();
			}

			int rsa_len = RSA_size( (RSA*)m_pPrvKey );

			unsigned char* out = new unsigned char[ rsa_len ];

			int ret = RSA_private_decrypt(
								_byte_array.size(),
								(const unsigned char*)_byte_array.constData(),
								out, (RSA*)m_pPrvKey,
								(int)_padding );

			if ( ret == -1 )
			{
				PCORE_LOG_ERROR( "Decryption failed for an unkown error." );
				return QByteArray();
			}

			QByteArray ar( (const char*)out, ret );
			delete[] out;

			return ar;
		} // decrypt


		//! setPublicKey
		bool Rsa::setPublicKey( const QByteArray& _public_key )
		{
			if ( _public_key.isEmpty() == true )
			{
				PCORE_LOG_ERROR( "Loading public key failed, input array is empty." );
				return false;
			}

			BIO* bio = BIO_new_mem_buf( (void*)_public_key.constData() , -1 );

			if ( bio == nullptr )
			{
				PCORE_LOG_ERROR( "Loading public key failed." );
				return false;
			}

			BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL );
			m_pPubKey= PEM_read_bio_RSAPublicKey( bio, NULL, NULL, NULL );

			if( m_pPubKey == nullptr )
			{
				PCORE_LOG_ERROR( "Loading public key failed." );
				BIO_free( bio );
				return false;
			}

			m_PublicKey = _public_key;
			BIO_free( bio );

			return true;
		}  // setPublicKey


		//! getPublicKey
		QByteArray Rsa::getPublicKey() const
		{
			return m_PublicKey;
		}


		//! setPrivateKey
		bool Rsa::setPrivateKey( const QByteArray& _private_key )
		{
			if ( _private_key.isEmpty() == true )
			{
				PCORE_LOG_ERROR( "Loading private key failed, input array is empty." );
				return false;
			}

			BIO* bio = BIO_new_mem_buf((void*)_private_key.constData(), -1);
			BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

			m_pPrvKey = (void*)PEM_read_bio_RSAPrivateKey( bio, NULL, NULL, NULL );

			if( m_pPrvKey == nullptr )
			{
				PCORE_LOG_ERROR( "Loading private key failed." );
				return false;
			}

			m_PrivateKey = _private_key;

			BIO_free(bio);

			return true;
		} // setPrivateKey


		//! getPrivateKey
		QByteArray Rsa::getPrivateKey( void ) const
		{
			return m_PrivateKey;
		}


		//! generatePrivateKey
		QByteArray Rsa::generatePrivateKey( int _len )
		{
			// generating key
			BIGNUM* bne = BN_new();
			int ret = BN_set_word( bne, RSA_F4 );
			if( ret != 1 )
			{
				PCORE_LOG_ERROR( "Private key creation has failed." );
				return QByteArray();
			}

			auto rsa = RSA_new();
			ret = RSA_generate_key_ex( rsa, _len, bne, NULL );

			if ( ret != 1 )
			{
				PCORE_LOG_ERROR( "Private key creation has failed." );
				BN_free( bne );
				return QByteArray();
			}


			// reading key
			BIO *bio = BIO_new( BIO_s_mem() );

			if ( bio == nullptr )
			{
				PCORE_LOG_ERROR( "Private key creation has failed." );
				RSA_free( rsa );
				BN_free ( bne );
				return QByteArray();
			}

			PEM_write_bio_RSAPrivateKey( bio, rsa, NULL, NULL, 0, NULL, NULL );
			int key_len = BIO_pending( bio );
			char* key = new char[ key_len ];
			BIO_read( bio, key, key_len );
			QByteArray ar( key, key_len );


			// releasing resources
			BIO_free_all( bio );
			RSA_free( rsa );
			BN_free ( bne );
			delete[] key;

			return ar;
		} // generatePrivateKey


		//! generatePublicKey
		QByteArray Rsa::generatePublicKey( const QByteArray& _private_key )
		{
			// reading private key
			BIO *bio = BIO_new_mem_buf( (void*)_private_key.constData(), -1 );

			if ( bio == nullptr )
			{
				PCORE_LOG_ERROR( "Generating public key has failed." );
				return QByteArray();
			}

			BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
			RSA* rsa = PEM_read_bio_RSAPrivateKey( bio, NULL, NULL, NULL );


			if ( rsa == nullptr )
			{
				PCORE_LOG_ERROR( "Generating public key has failed." );
				BIO_free_all( bio );
				return QByteArray();
			}


			// generating public key
			BIO* bio_out = BIO_new( BIO_s_mem() );

			if ( bio_out == nullptr )
			{
				PCORE_LOG_ERROR( "Generating public key has failed." );
				BIO_free_all( bio );
				RSA_free( rsa );
				return QByteArray();
			}

			PEM_write_bio_RSAPublicKey( bio_out, rsa );
			int key_len = BIO_pending( bio_out );
			char* key = new char[ key_len ];
			BIO_read( bio_out, key, key_len );
			QByteArray ar( key, key_len );


			// releasing resources
			BIO_free_all( bio );
			BIO_free_all( bio_out );
			RSA_free( rsa );
			delete[] key;

			return ar;
		} // generatePublicKey

	} // cryptography
} // PCore

//##############################################################################
//#	c-date:	Jun-09-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include "include/pcore/cryptography/des.h"
#include "include/pcore/core/logger.h"
#include "include/pcore/math/random.h"
#include <QByteArray>
#include <openssl/des.h>


//==============================================================================
// macros
//==============================================================================

//! Block size
#define PCORE_DES_BLOCK_SIZE 8

//! helper macro for calculating block size
#define _PCORE_HELPER_TO_BLOCK(__size,__block_size )\
					(((__size+__block_size)/__block_size) * __block_size )


//==============================================================================
// code
//==============================================================================

namespace PCore
{
	namespace cryptography
	{

		//! constructor
		DES::DES( QObject* _parent ) :
			QObject( _parent )
		{

		}


		//! setPass
		void DES::setPass( const QByteArray& _pass )
		{
			m_Pass = _pass;
		}


		//! getPass
		QByteArray DES::getPass() const
		{
			return m_Pass;
		}


		//! setIV
		void DES::setIV(const QByteArray& _iv)
		{
			m_IV = _iv;
		}

		//! getIV
		QByteArray DES::getIV( void ) const
		{
			return m_IV;
		}


		//! encrypt
		QByteArray DES::encrypt( const QByteArray& _data )
		{
			return DES::encryptEX( m_Pass, m_IV, _data );
		}


		//! decrypt
		QByteArray DES::decrypt(const QByteArray& _data)
		{
			return DES::decryptEX( m_Pass, m_IV, _data );
		}


		//======================================================================
		// Static mthods
		//======================================================================

		//! encryptEX
		QByteArray DES::encryptEX( const QByteArray& _pass,
								   QByteArray& _iv,
								   const QByteArray& _data )
		{
			if ( _pass.length() < 8 )
			{
				PCORE_LOG_ERROR( "DES failed.Key must be at least 8 characters." );
				return QByteArray();
			}


			if ( _iv.isEmpty() == true )
			{
				_iv = math::Random::randomByteArray( PCORE_DES_BLOCK_SIZE );

			}
			else
			{
				if ( _iv.size() != PCORE_DES_BLOCK_SIZE )
				{
					PCORE_LOG_ERROR( "DES failed. IVEC must be at least 8 characters." );
					return QByteArray();
				}
			}

			// ivec
			DES_cblock iv;
			memcpy( iv, _iv.constData(), PCORE_DES_BLOCK_SIZE );


			DES_cblock key_2;
			DES_key_schedule schedule;
			int out_len = _PCORE_HELPER_TO_BLOCK( _data.size(), PCORE_DES_BLOCK_SIZE ) ;
			unsigned char *out = new unsigned char[ _data.size() ];
			memset( out, 0, out_len );


			// Prepare the key
			memcpy( key_2, _pass.constData() , PCORE_DES_BLOCK_SIZE );
			DES_set_odd_parity( &key_2 );
			if ( DES_set_key_checked( &key_2, &schedule ) != 0 )
			{
				PCORE_LOG_ERROR( "DES failed; cannot set key." );
				return QByteArray();
			}

			// Encryption
			DES_ncbc_encrypt( (unsigned char*)_data.constData(), out,
							   _data.size() , &schedule, &iv, DES_ENCRYPT );

			QByteArray ar( (const char*)out, out_len );
			delete[] out;
			return ar;
		} // encryptEX


		//! decryptEX
		QByteArray DES::decryptEX( const QByteArray& _pass,
								   const QByteArray& _iv,
								   const QByteArray& _data )
		{
			if ( _pass.length() < 8 )
			{
				PCORE_LOG_ERROR( "DES failed.Key must be at least 8 characters." );
				return QByteArray();
			}

			if ( _iv.size() != PCORE_DES_BLOCK_SIZE )
			{
				PCORE_LOG_ERROR( "DES failed.IVEC must be at least 8 characters." );
				return QByteArray();
			}

			// ivec
			DES_cblock iv;
			memcpy( iv, _iv.constData(), PCORE_DES_BLOCK_SIZE );


			DES_cblock key_2;
			DES_key_schedule schedule;
			int out_len = _PCORE_HELPER_TO_BLOCK( _data.size(), PCORE_DES_BLOCK_SIZE ) ;
			unsigned char *out = new unsigned char[ out_len ];
			memset( out, 0, out_len );

			// Prepare the key
			memcpy( key_2, _pass.data() , PCORE_DES_BLOCK_SIZE );
			DES_set_odd_parity( &key_2 );
			if ( DES_set_key_checked( &key_2, &schedule ) != 0 )
			{
				PCORE_LOG_ERROR( "DES failed. Cannot set key." );
				return QByteArray();
			}

			// Decryption
			DES_ncbc_encrypt( (unsigned char *)_data.constData(), out, _data.size(),
							   &schedule, &iv, DES_DECRYPT );

			QByteArray ar( (const char*)out );
			delete[] out;
			return ar;
		} // decryptEX

	} // cryptography
} // PCore


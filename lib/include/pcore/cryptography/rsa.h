//##############################################################################
//#	title:	RSA (Rivest-Shamir-Adleman)
//#	c-date:	Jun-09-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_CRYPTO_RSA_H
#define _PCORE_CRYPTO_RSA_H

#include "../pcore_def.h"
#include <QObject>
class QByteArray;

namespace PCore
{
	namespace cryptography
	{
		//======================================================================
		// RSA Class
		//======================================================================
		class PCORE_API Rsa : public QObject
		{
			//=====================================
			// Metadata
			//=====================================

			Q_OBJECT
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )


			//=====================================
			// enums
			//=====================================
		public:

			/*!
			 * Paddings
			 */
			enum class Padding
			{
				PKCS1		= 1,
				SSL_V23		= 2,
				NO_PADDING	= 3,
				PKCS1_OAEP	= 4,
				X931		= 5
			};


			//=====================================
			// Public methods
			//=====================================
		public:

			/*!
			 * \brief Constructs a RSA object.
			 * \param _generate_keys: Generates private and public keys.
			 */
			Rsa( bool _generate_keys = true, QObject* _parent = nullptr );


			/*!
			 * \brief Copy constructor.
			 */
			Rsa( const Rsa& _obj );


			/*!
			 * \brief Move constructor.
			 */
			Rsa( Rsa&& _obj );


			/*!
			  *\brief Destrcutor.
			 */
			~Rsa( );


			/*!
			 * \brief Encrypts given byte array by using public key, and returns it.
			 * \param _byte_array: Array that should be encrypted.
			 * \param _padding: Padding.
			 * \return Returns encrypted byte array by public key.
			 */
			QByteArray encrypt( const QByteArray& _byte_array,
								Padding _padding = Padding::PKCS1
							);


			/*!
			 * \brief Decrypts given byte array by using private key, and returns it.
			 * \param _byte_array: Array that should be decrypted;
			 * \return Returns decrypted byte array by public key.
			 */
			QByteArray decrypt( const QByteArray& _byte_array,
								Padding _padding = Padding::PKCS1 );


			/*!
			 * \brief Sets the public key.
			 * \param _public_key: Public Key.
			 */
			bool setPublicKey( const QByteArray& _public_key );


			/*!
			 * \brief Returns seted public key.
			 */
			QByteArray getPublicKey( void ) const;


			/*!
			 * \brief Sets the private key.
			 * \param _public_key: Private Key.
			 */
			bool setPrivateKey( const QByteArray& _private_key );


			/*!
			 * \brief Returns seted public key.
			 */
			QByteArray getPrivateKey( void ) const;


			//=====================================
			// Static methods
			//=====================================
		public:

			/*!
			 * \brief Generates a random private key, and returns it.
			 * \param _len: Length of the key.
			 * \return Returns generated private key.
			 */
			static QByteArray generatePrivateKey( int _len = PCORE_1KB );

			/*!
			 * \brief Generates a public key from given private key, and returns it.
			 * \param _private_key: Input private key.
			 * \return Returns generated public key from given private key.
			 */
			static QByteArray generatePublicKey( const QByteArray& _private_key );


			//=====================================
			// Private members
			//=====================================
		private:

			QByteArray	m_PublicKey;	//! Public Key.
			QByteArray	m_PrivateKey;	//! Private Key.

			void*	m_pPrvKey	= nullptr; //! Pointer to private key instance.
			void*	m_pPubKey	= nullptr; //! pointer to public key instance.

		}; // RSA
	} // Cryptography
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PRSA = PCore::cryptography::Rsa;
#endif


#endif // _PCORE_CRYPTO_RSA_H


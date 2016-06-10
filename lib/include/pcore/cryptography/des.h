//##############################################################################
//#	title:	DES
//#	c-date:	Jun-10-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_CRYPTO_DES_H
#define _PCORE_CRYPTO_DES_H

#include "../pcore_def.h"
#include <QObject>
class QByteArray;

namespace PCore
{
	namespace cryptography
	{
		class PCORE_API DES: public QObject
		{
			//=====================================
			// Metadata
			//=====================================

			Q_OBJECT
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )


			//=====================================
			// Public methods
			//=====================================
		public:

			/*!
			 * \brief Constructor
			 */
			DES( QObject* _parent = nullptr );


			/*!
			 * \brief Sets pass phrase (Password)
			 */
			void setPass( const QByteArray& _pass );


			/*!
			 * \brief Returns pass phrase.
			 */
			QByteArray getPass( void ) const;


			/*!
			 * \brief Sets initialization vector.
			 */
			void setIV( const QByteArray& _iv );


			/*!
			 * \brief Returns initialization.
			 */
			QByteArray getIV( void ) const;


			/*!
			 * \brief Encrypts given data, and returns it.
			 * \param _data: Data that should be encrypted.
			 * \return Retruns encrypted data.
			 */
			QByteArray encrypt( const QByteArray& _data );


			/*!
			 * \brief Decrypts given data, and returns it.
			 * \param _data: Data that should be decrypted.
			 * \return Retruns decrypted data.
			 */
			QByteArray decrypt( const QByteArray& _data );


			//=====================================
			// Static members
			//=====================================
		public:

			/*!
			 * \brief Encrypts given _data by specified _pass, and returns it.
			 * \param _pass: Pass phrase (Password).
			 * \param _iv: Initialization vector.
			 * \param _data: Data that should be encrypted.
			 * \return Encrypted _data with specified password.
			 */
			static QByteArray encryptEX( const QByteArray& _pass,
										 QByteArray& _iv,
										 const QByteArray& _data );


			/*!
			 * \brief Decrypts given _data by specified _pass, and returns it.
			 * \param _pass: Pass phrase (Password)
			 * \param _iv: Initialization vector.
			 * \param _data: Data that should be decrypted.
			 * \return Decrypted _data with specified password.
			 */
			static QByteArray decryptEX( const QByteArray& _pass,
										 const QByteArray& _iv,
										 const QByteArray& _data );


			//=====================================
			// private members
			//=====================================
		public:
			QByteArray m_Pass;	//! Pass phrase.
			QByteArray m_IV;	//! Initialization vector.

		}; // DES
	} // cryptography
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PDES = PCore::cryptography::DES;
#endif


#endif // _PCORE_CRYPTO_DES_H

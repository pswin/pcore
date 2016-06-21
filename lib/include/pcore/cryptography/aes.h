//##############################################################################
//#	title:	AES
//#	c-date:	Jun-09-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_CRYPTO_AES_H
#define _PCORE_CRYPTO_AES_H

#include "../pcore_def.h"
#include "../globals.h"
#include <QObject>

namespace PCore
{
	namespace cryptography
	{
		class PCORE_API AES : public QObject
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
			 * Block size
			 */
			enum class BlockSize
			{
				_128	= 128,
				_192	= 192,
				_256	= 256,

			};


			//=====================================
			// Public methods
			//=====================================
		public:

			/*!
			 * \brief Constructs an AES object.
			 * \param _init_vec: Initialization vector.
			 * \param _salt: Salt.
			 * \param _block_size: Size of the blocks.
			 */
			AES( const QByteArray _init_vec	= QByteArray(),
				 const QByteArray _salt		= QByteArray(),
				 BlockSize _block_size		= BlockSize::_128,
				 QObject* _parent			= nullptr
				);


			/*!
			 * \brief Sets pass phrase (Password).
			 * \param _pass: Pass phrase (Password).
			 */
			void setPass( const QByteArray& _pass );



			/*!
			 * \brief Sets IV (Initialization Vector).
			 */
			void setIV( const QByteArray& _iv );


			/*!
			 * \brief Returns IV (Initialization Vector).
			 */
			QByteArray getIV( void ) const;


			/*!
			 * \brief Sets size of blocks.
			 */
			void setBlockSize( BlockSize _block_size );


			/*!
			 * \brief Returns block size.
			 */
			BlockSize getBlockSize( void ) const;


			/*!
			 * \brief Sets salt.
			 */
			void setSalt( const QByteArray& _salt );


			/*!
			 * \brief Returns salt.
			 */
			QByteArray getSalt( void ) const;


			/*!
			 * \brief Encrypts given data, and returns it.
			 * \param _data: Data that should be encrypted.
			 * \param _attach_salt: if it is true, Salt will be attached
			 *				to the encryped data.
			 * \return Retruns encrypted data.
			 */
			QByteArray encrypt( const QByteArray& _data ,
								bool _attach_salt = true
							);



			/*!
			 * \brief Decrypts given data, and returns it.
			 * \param _data: Data that should be decrypted.
			 * \return Retruns decrypted data.
			 */
			QByteArray decrypt( const QByteArray& _data );


			//=====================================
			// static methods
			//=====================================
		public:

			/*!
			 * \brief Encrypts given data with specified params, and returns it.
			 * \param _pass: Pass phrase (Password).
			 * \param _data: Data that should be encrypted.
			 * \param _iv: Initialization vector.
			 * \param _block_size: Size of the blocks.
			 * \return Encrypted data.
			 */
			static QByteArray encryptEX( const QByteArray& _pass,
										 const QByteArray& _data,
										 QByteArray& _iv		 = NullQByteArray,
										 QByteArray& _salt		 = NullQByteArray,
										 BlockSize _block_size	 = BlockSize::_128,
										 bool _attach_salt = true
										);


			/*!
			 * \brief Decrypts given data with specified params, and returns it.
			 * \param _pass: Pass phrase (Password).
			 * \param _data: Data that should be decrypted.
			 * \param _iv: Initialization vector.
			 * \param _block_size: Size of the blocks.
			 * \return decrypted data.
			 */
			static QByteArray decryptEX( const QByteArray& _pass,
										 const QByteArray& _data,
										 QByteArray& _iv		 = NullQByteArray,
										 const QByteArray& _salt = NullQByteArray,
										 BlockSize _block_size	 = BlockSize::_128
										);


			//=====================================
			// private members
			//=====================================
		private:

			QByteArray	m_Pass;		 //! Pass phrase (Password).
			QByteArray	m_IV;		 //! Initialization vector.
			BlockSize	m_eBlockSize;//! Size of the blocks.
			QByteArray	m_Salt;		 //! Salt.


			//! checks inputs
			bool checkInput( void );
		};
	} // cryptography
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PAES = PCore::cryptography::AES;
#endif

#endif // _PCORE_CRYPTO_AES_H

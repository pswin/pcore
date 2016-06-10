//##############################################################################
//#	title:	Cryptography engine
//#	c-date:	Jun-10-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_CRYPTOGRAPHY_ENGINE_H
#define _PCORE_CRYPTOGRAPHY_ENGINE_H

namespace PCore
{
	namespace cryptography
	{
		class CryptographyEngine
		{
		public:

			/*!
			 * \brief Initialize engine.
			 * \return Return true if initialization procedure was successful.
			 */
			static bool init( void );


			/*!
			 * \brief Release allocated resources.
			 * \return Return true if procedure was successful.
			 */
			static bool shutdown( void );
		};
	} // cryptography
} // PCORE


#endif // _PCORE_CRYPTOGRAPHY_ENGINE_H

//##############################################################################
//#	title:	Random number of data generation
//#	c-date:	Jun-10-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_MATH_RANDOM_H
#define _PCORE_MATH_RANDOM_H

#include "../pcore_def.h"
class QByteArray;

namespace PCore
{
	namespace math
	{
		class PCORE_API Random
		{
			//=====================================
			// Static members
			//=====================================
		public:

			/*!
			 * \brief Generates an array of random bytes in given size.
			 * \param _size: Size of array.
			 * \return An array of random bytes in given size.
			 */
			static QByteArray randomByteArray( quint32 _size );
		};
	} // math
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PRandom = PCore::math::Random;
#endif

#endif // _PCORE_MATH_RANDOM_H

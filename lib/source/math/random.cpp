//##############################################################################
//#	c-date:	Jun-10-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


//==============================================================================
// includes
//==============================================================================

#include <QByteArray>
#include <openssl/rand.h>
#include "include/pcore/math/random.h"


//==============================================================================
// random
//==============================================================================
namespace PCore
{
	namespace math
	{

		//! randomByteArray
		QByteArray Random::randomByteArray( quint32 _size )
		{
			unsigned char* arr = new  unsigned char[ _size ];
			RAND_bytes(arr,_size);

			QByteArray out( (char*)arr, _size );
			delete[] arr;
			return out;
		}

	} // math
} // PCore


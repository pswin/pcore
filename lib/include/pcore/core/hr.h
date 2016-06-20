//##############################################################################
//#	title:	This class provides some methods which by using them more human
//#			readable data could be provided
//#	c-date:	Jun-16-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_HUMAN_READABLE_H
#define _PCORE_HUMAN_READABLE_H

#include "../pcore_def.h"
#include "../config.h"
class QString;

namespace PCore
{
	namespace core
	{
		class PCORE_API HumanReadable
		{
		public:
			/*!
			 * \brief Converts bytes to KB, MB, etc.
			 * \param _byte: Bytes.
			 * \param _fraction: Precision of fraction part.
			 */
			static QString byteToString( quint64	_bytes,
										 int		_fraction = 2
										);


			/*!
			 * \brief Converts Hertx to MHz , GHz and etc.
			 * \param _freq: Frequance in Hertz.
			 * \param _fraction: Precision of fraction part
			 */
			static QString freqToString( quint64	_freq,
										 int		_fraction = 2);

		};
	} // core
} // PCore

#endif // _PCORE_HUMAN_READABLE_H

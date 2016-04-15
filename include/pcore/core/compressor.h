//##############################################################################
//#	title:	Compressor and uncompressor
//#	c-date:	Apr-13-2016
//#	author:	Pouya Shahinfar
//##############################################################################

#ifndef _PCORE_COMPRESSOR_H
#define _PCORE_COMPRESSOR_H

#include "../pcore_def.h"
#include <QByteArray>
#include <QString>

namespace PCore
{
	namespace core
	{
		class PCORE_API Compressor
		{

		public:

			/*! For the first phase, PCore only support following formats. But
			 * we intended to extend them.
			*/
			enum class Format
			{
				RawDeflate,		//! Raw deflate format
				Zlib,			//! Zlib
				GZip,			//! GZip
				Default			//! Default format
			};


			/*!
			 * \brief Compression level.
			 */
			enum class Level
			{
				BestSpeed,
				BestCompression,
				Default
			};

		public:

			/*!
			 * \brief Compress given byte array and return it.
			 * \param _byte_ar: Input byte array.
			 * \param _format: Method of compression
			 * \return compressed byte array.
			 */
			static QByteArray compress(
									const QByteArray& _in,
									Format _format = Format::RawDeflate,
									Level _level = Level::Default
								);


			/*!
			 * \brief Compress a single file.
			 * \param _in_filename: Input file name.
			 * \param _out_filename: Output file name.
			 * \param _format: Method of compression.
			 * \return True if compression progress was successful.
			 */
			static bool compressFile(
									const QString& _in_filename,
									const QString& _out_filename,
									Format _format = Format::RawDeflate,
									Level _level = Level::Default
									);


			/*!
			 * \brief Decompress given byte array and return it.
			 * \param _in: Input byte array.
			 * \param _format: Method of decompression
			 * \return
			 */
			static QByteArray decompress(
										  const QByteArray& _in,
										  Format _format = Format::RawDeflate
										);


			/*!
			 * \brief Decompress a single file.
			 * \param _in_filename: Input file name.
			 * \param _out_filename: Output file name.
			 * \param _format: Method of decompression.
			 * \return True if decompression progress was successful.
			 */
			static bool decompressFile(
									const QString& _in_filename,
									const QString& _out_filename,
									Format _format = Format::Default
									);

		}; // Compressor
	} // core
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PCompressor = PCore::core::Compressor;
#endif


#endif // _PCORE_COMPRESSOR_H


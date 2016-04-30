//##############################################################################
//#	title:	Logger
//#	c-date:	Apr-18-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_SYSTEM_INFORMATION_H
#define _PCORE_SYSTEM_INFORMATION_H

#include "../pcore_def.h"
#include <QtGlobal>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QVariant>

/*
 *	Note:
 *		We have tried hard to provide very detailed system information;
 *		Nevertheless, some brands and operating systems do not provide
 *		compelete, or even reliable information. Therefore, do not trust on
 *		information which is provided by this class. We could not grantee them.
 */


namespace PCore
{
	namespace core
	{
		class PCORE_API SystemInformation
		{
			//=====================================
			// Public Enums
			//=====================================
		public:

			enum class AdapterStatus
			{
				Running,	//! Device is running or is in Full power.
				Offline,	//! Device is offline.
				PowerSave,	//! Device is in power save mode.
				Paused,		//! Device is paused.
				Warning,	//! There is a warning.
				Error,		//! There is an error; Thus, it is out of order.
				Unkown		//! Device is in an unkown mode.
			}; // AdapterStatus


			//=====================================
			// Public Structs
			//=====================================
		public:
			/*!
			 *	\brif Processor Information
			 */
			struct ProcessorInformation
			{
				quint16	index = 0;						//! Index
				QString	name;							//! Name of processor
				QString	architecture;					//! Architecture
				quint16	architecture_id = 0;			//! Architecture ID
				QString	micro_architecture_code_name;	//! Code name of micro architecture
				QString	model;							//! Model name
				QString	vendor;							//! Manufacture
				quint32	max_clock = 0;					//! Maximum clock of processor
				QString	family;							//! Family name (Identified by os)
				quint16	family_id = 0;					//! Family ID
				quint32	l1_cache_size = 0;				//! L1 Cache size in bytes
				quint32	l2_cache_size = 0;				//! L2 Cache size in bytes
				quint32	l3_cache_size = 0;				//! L3 Cache size in bytes
				quint32	num_of_logical_cores = 0;		//! Number of logical cores
				quint32	num_of_cores = 0;				//! Number of cores
				quint32	num_of_threads = 0;				//! Number of threads
				quint16	data_width = 0;					//! Width of bus data
				QString	signature;						//! Signature of processor

				QStringList	extensions;					//! A list of extensions and instruction sets
				QMap<QString,QVariant> other_params;	//! other params

			}; // ProcessorInformation


			/*!
			 * \brief Video controller information
			 */
			struct VideoControllerInformation
			{
				quint32	index;							//! Index of adapter.
				QString	name;							//! Name of adapter.
				QString	vendor;							//! Vendor of adapter.
				QString	video_mode_desc;				//! Current video mode description.
				quint32	memory_size;					//! Ram size.
				quint64	current_num_of_colors;			//! Current number of colors.
				quint32	current_bits_per_pixel;			//! Bits per pixel.
				quint32	current_refresh_rate;			//! Current refresh rate.
				quint32	max_refresh_rate;				//! Maximum refresh rate.
				quint32	min_refresh_rate;				//! Minimum refresh rate.
				quint32	current_resolution_vertical;	//! Current vertical resolution.
				quint32	current_resolution_horizantal;	//! Current horizantal resolution.
				bool	is_running;						//! Is running?
			}; // VideoControllerInformation


			//=====================================
			// Public Methods
			//=====================================
		public:

			/*!
			 * \brief Retrieves information of all installed proccessors and return it.
			 * \return information of all installed proccessors and return it.
			 */
			static QList<ProcessorInformation> getProcesses( void );


			/*!
			 * \brief Retrieves information of all installed video controllers and return it.
			 * \return information of all installed video controllers and return it.
			 */
			static QList<VideoControllerInformation> getVideoControllers( void );

		}; // System Information
	} // core
} // PCore



#endif // _PCORE_SYSTEM_INFORMATION_H
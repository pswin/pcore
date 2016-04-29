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
				QString	name;
				quint32	memory;
				quint32 max_memory;
				quint64	num_of_colors;
				quint32	bits_per_pixel;
				quint32	refresh_rate;
				quint32 max_refresh_rate;
				quint32 min_refresh_rate;
				quint32 resolution_vertical;
				quint32 resolution_horizantal;
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

		}; // System Information
	} // core
} // PCore



#endif // _PCORE_SYSTEM_INFORMATION_H

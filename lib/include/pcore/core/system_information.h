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

			/*!
			 * \brief Power status of device
			 */
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

			//==================================================================
			// Processor information
			//==================================================================
			class PCORE_API Processor
			{
				//=====================================
				// public enums
				//=====================================
			public:

				/*!
				 * \brief Architecture of processor.
				 */
				enum class Architecture
				{
					X86,		//! X86
					X86_64,		//! X86_64
					ARM,		//! ARM
					ARM_64,		//! 64 bit ARM
					SPARC,		//! SPARC
					SPARC_64,	//! SPARC 64 bit
					PowerPC,	//! PowerPC
					PowerPC_64,	//! 64 bit Power PC
					MIPS,		//! MIPS
					MIPS_64,	//! MIPS 64 bit
					Other,		//! Other type of architecures
					Unkown		//! Unkown
				}; // Architecture


				/*!
				 * \brief PowerMode of the CPU.
				 */
				enum class PowerMode
				{
					Preformance,	//! Performace mode.
					Powersave,		//! PowerSave, Idle.
					Unkown			//! Unkown.
				};


				//=====================================
				// public structs
				//=====================================
			public:
				/*!
				 * \brief Cache level information.
				 */
				struct CacheLevel
				{
					quint32	size					= 0; //! Total size.
					quint32	data_size				= 0; //! Size of data cache in bytes.
					quint32	instrction_size			= 0; //! Size of instructio cache in bytes.
					quint16	ways_of_associativity	= 0; //! Ways of associativity.
					quint16	line_size				= 0; //! Line size.
				}; // CacheLevel


				/*!
				 * \brief Frequence information
				 */
				struct Freq
				{
					quint32	current	= 0; //! Current frequence in Mhz
					quint32	max		= 0; //! Maximum frequence in Mhz
					quint32	min		= 0; //! Minimum frequence in Mhz
				};

				/*!
				 * \brief Core information.
				 */
				struct Core
				{
					Freq						freq;									//! Frequence info.
					QMap<quint16,CacheLevel>	cache_levels;							//! Cache levels.
					quint32						cache_size		= 0;					//! Total Cache Size.
					AdapterStatus				status			= AdapterStatus::Unkown;//! Adapter Status.
					PowerMode					power_mode		= PowerMode::Unkown;	//! Power mode.
				};

				/*!
				 * \brief Bus information
				 */
				struct Bus
				{
					quint16	data_width			= 0; //! Width of data bus
					quint16	address_width		= 0; //! Width of physical address bus
					quint16	virutal_address_with= 0; //! Width of virual address bus
				};


				//=====================================
				// public members
				//=====================================
			public:
				QString					name;				//! Name of processor.
				Architecture			arch;				//! Architecture.
				QString					arch_name;			//! Architecture name.
				QString					model;				//! Model name.
				QString					vendor;				//! Manufacturer.
				QMap<quint16,Core>		cores;				//! Cores information.
				Bus						bus;				//! Bus information.
				quint16					total_cores		= 0;//! Total number of cores.
				quint32					total_cache		= 0;//! Total cache size.
				quint16					logical_cores	= 0;//! Number of logical cores.
				quint16					threads			= 0;//! Number of threads.
				QMap<QString,QVariant>	other_params;		//! other params.
				QStringList				extensions;			//! A list of extensions and instruction sets.

				//=====================================
				// static methods
				//=====================================
			public:

				/*!
				 * \brief returns architecture name in string.
				 * \param _arch: architecture type.
				 * \return architecture name.
				 */
				static QString getString( Processor::Architecture _arch );

				/*!
				 * \brief Returns power mode in string.
				 * \param _mode: power mode.
				 * \return power mode.
				 */
				static QString getString( Processor::PowerMode _mode );

			}; // Processor


			//==================================================================
			// Storage information
			//==================================================================
			class PCORE_API Storage
			{
				//=====================================
				// public enums
				//=====================================
			public:

				/*!
				 * \brief Type of storage
				 */
				enum class Type
				{
					FixedDisk,		//! Disk drive.
					ExternalDisk,	//! External hard disk
					Tape,			//! Tape drive.
					Floppy,			//! Floppy disk drive.
					FlashDisk,		//! Flash disk
					RemovableMedia,	//! Removable media
					Unknown
				}; // Type


				/*!
				 * \brief Interface type.
				 */
				enum class Interface
				{
					SCSI,
					HDC,
					ATA,
					SATA,
					USB,
					_1394,
					Unknown
				}; // Interface type


				//=====================================
				// public members
				//=====================================
			public:
				QString		name;								//! Name of storage.
				QString		model;								//! Model name (if exists).
				QString		vendor;								//! Manufacturer.
				QString		serial;								//! Serial.
				quint64		capacity			= 0;			//! Capacity of storage.
				quint32		heads				= 0;			//! Total number of heads.
				quint64		cylinders			= 0;			//! Total number of cylinders.
				quint32		tracks_per_cylinder	= 0;			//! Tracks per cylinder.
				quint32		sectors_per_track	= 0;			//! Sectors per track.
				quint32		bytes_per_sector	= 0;			//! Bytes per sector.
				quint64		block_size			= 0;			//! Size of every block.
				bool		is_random_access	= false;		//! Is a random access device.
				bool		is_sequential		= false;		//! Is a sequential device.
				bool		is_writable			= false;		//! Is a writable device.
				bool		is_removeable		= false;		//! Is a removeable device.
				Type		type				= Type::Unknown;//! Type of storage.
				Interface	interface_type		= Interface::Unknown;//! Type of interface.
				QStringList	partitions;							//! list of partitions.


				//=====================================
				// static methods
				//=====================================
			public:

				/*!
				 * \brief Returns name of interface.
				 * \param _interface: interface type.
				 * \return name of specified interface.
				 */
				static QString getString( Storage::Interface _interface );

				/*!
				 * \brief Returns name of Storage::Type.
				 * \param _interface: storage type.
				 * \return name of Sotrage::Type.
				 */
				static QString getString( Storage::Type _interface );
			}; // Storage


			//==================================================================
			// VideoController
			//==================================================================
			class VideoControllerInformation
			{
				//=====================================
				// public structs
				//=====================================
			public:

				/*!
				 * \brief Resolution information
				 */
				struct Resolution
				{
					quint32 vertial			= 0; //! Vertical.
					quint32 horizantal		= 0; //! Horizantal.
					quint16	bits_per_pixel	= 0; //! Bits per pixel
				};

				//=====================================
				// public members
				//=====================================
			public:

				QString	name;							//! Name of adapter.
				QString model;							//! Model of device
				QString	vendor;							//! Manufacturer of adapter.
				QString	video_mode_desc;				//! Current video mode description.
				quint32	memory_size;					//! Ram size.
				quint64	current_num_of_colors;			//! Current number of colors.
				quint32	current_bits_per_pixel;			//! Bits per pixel.
				quint32	current_refresh_rate;			//! Current refresh rate.
				quint32	max_refresh_rate;				//! Maximum refresh rate.
				quint32	min_refresh_rate;				//! Minimum refresh rate.
				quint32	current_resolution_vertical;	//! Current vertical resolution.
				quint32	current_resolution_horizantal;	//! Current horizantal resolution.
				bool	is_running;						//! Is Current adapter?
				QList<Resolution> supported_resolutions;//! list of supported resolutions.
			}; // VideoControllerInformation


			//==================================================================
			// Monitor
			//==================================================================
			struct MonitorInformation
			{
				quint32	index;					//! Index of storage.
				QString	name;					//! Name of storage.
				QString model;					//! Model of device.
				QString connected_to;			//! Video controler which is connected to.
				quint32	screen_height;			//! Screen height
				quint32	screen_width;			//! Screen width
			};


			/*!
			 * \brief Sound card information
			 */
			struct SoundCardInformation
			{
				quint32	index;					//! Index of storage.
				QString	name;					//! Name of storage.
				QString model;					//! Model of device.
				QString vendor;					//! Manufacturer.
			};


			//=====================================
			// Public Methods
			//=====================================
		public:

			/*!
			 * \brief Retrieves information of all installed proccessors and return it.
			 * \return information of all installed proccessors.
			 */
			static QList<Processor> getProcesses( void );


			/*!
			 * \brief Retrieves information of all installed video controllers and return it.
			 * \return information of all installed video controllers.
			 */
			static QList<VideoControllerInformation> getVideoControllers( void );


			/*!
			 * \brief Retrieves information of all installed storages and return it.
			 * \return information of all installed storages.
			 */
			static QList<Storage> getStorages( void );


			/*!
			 * \brief Retrieves a list of monitors.
			 * \return information of all connected monitors.
			 */
			static QList<MonitorInformation> getMonitors( void );


			/*!
			 * \brief Retrieves a list of sound cards.
			 * \return information of all installed sound cards.
			 */
			static QList<SoundCardInformation> getSoundCards( void );

		}; // System Information
	} // core
} // PCore



#endif // _PCORE_SYSTEM_INFORMATION_H

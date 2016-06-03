//##############################################################################
//#	title:	System information
//#	c-date:	Apr-17-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "include/pcore/pcore_def.h"


#if PCORE_OS == PCORE_OS_WINDOWS

//==============================================================================
// headers
//==============================================================================

#include <include/pcore/core/system_information.h>
#include <include/pcore/core/logger.h>
#include <include/pcore/core/bit_operations.h>
#include <headers/core/windows/win_wmi.h>
#include <headers/core/arch/amd/sys_info/sys_info_amd.h>
#include <headers/core/arch/intel/sys_info/sys_info_intel.h>
#include <QDebug>

using namespace PCore::core;
using PCore::core::SystemInformation;


//==============================================================================
// functions
//==============================================================================


/*!
 * \brief Retrieves architecture's name by specified ID.
 * \param _id: ID of architecture.
 * \return Architecture's name.
 */
QString get_arch_name_by_id ( int _id )
{
	switch ( _id )
	{
		case 0:
			return "x86";
		case 1:
			return "MIPS";
		case 2:
			return "Alpha";
		case 3:
			return "PowerPC";
		case 5:
			return "ARM";
		case 6:
			return "ia64";
		case 9:
			return "x86_64";
		default:
			return "Unkown";
	}
} // get_arch_by_id



/*!
 * \brief Returns architecture by specified id.
 * \param _id: id of architecture.
 */
SystemInformation::Processor::Architecture get_arch_by_id ( int _id )
{
	switch ( _id )
	{
		case 0:
			return SystemInformation::Processor::Architecture::X86;
		case 1:
			return SystemInformation::Processor::Architecture::MIPS;
		case 3:
			return SystemInformation::Processor::Architecture::PowerPC;
		case 5:
			return SystemInformation::Processor::Architecture::ARM;
		case 6:
		case 9:
			return SystemInformation::Processor::Architecture::X86_64;
		default:
			return SystemInformation::Processor::Architecture::Unkown;
	}
} // get_arch_by_id


/*!
 * \brief Retrieves CPU's family name by specified id from Windows's WMI.
 * \param _id: ID of family.
 * \return Processor's family name.
 */
QString get_family_by_id( int _id )
{

	switch ( _id )
	{
	case 1:
	case 2:
		return "Unkown";
	case 3:
		return "x8086";
	case 4:
		return "x80286";
	case 5:
		return "Intel386™ Processor";
	case 6:
		return "Intel486™ Processor";
	case 7:
		return "8087";
	case 8:
		return "80287";
	case 9:
		return "80387";
	case 10:
		return "80487";
	case 11:
		return "Pentium(R) brand";
	case 12:
		return "Pentium(R) Pro";
	case 13:
		return "Pentium(R) II";
	case 14:
		return "Pentium(R) processor with MMX(TM) technology";
	case 15:
		return "Celeron™";
	case 16:
		return "Pentium II Xeon™";
	case 17:
		return "Pentium(R) III";
	case 18:
		return "M1 Family";
	case 19:
		return "M2 Family";
	case 24:
		return "AMD Duron™ Processor Family";
	case 25:
		return "K5 Family";
	case 26:
		return "K6-2 Family";
	case 27:
		return "K6-3";
	case 28:
		return "AMD Athlon™ Processor Family";
	case 29:
		return "AMD Duron™ Processor Family";
	case 30:
		return "AMD29000 Family";
	case 31:
		return "K6-2+";
	case 32:
		return "Power PC Family";
	case 33:
		return "Power PC 601";
	case 34:
		return "Power PC 603";
	case 35:
		return "Power PC 603+";
	case 36:
		return "Power PC 604";
	case 37:
		return "Power PC 620";
	case 38:
		return "Power PC X704";
	case 39:
		return "Power PC 750";
	case 48:
		return "Alpha Family";
	case 49:
		return "Alpha 21064";
	case 50:
		return "Alpha 21066";
	case 51:
		return "Alpha 21164";
	case 52:
		return "Alpha 21164PC";
	case 53:
		return "Alpha 21164a";
	case 54:
		return "Alpha 21264";
	case 55:
		return "Alpha 21364";
	case 64:
		return "MIPS Family";
	case 65:
		return "MIPS R4000";
	case 66:
		return "MIPS R4200";
	case 67:
		return "MIPS R4400";
	case 68:
		return "MIPS R4600";
	case 69:
		return "MIPS R10000";
	case 80:
		return "SPARC Family";
	case 81:
		return "SuperSPARC";
	case 82:
		return "microSPARC II";
	case 83:
		return "microSPARC IIep";
	case 84:
		return "UltraSPARC";
	case 85:
		return "UltraSPARC II";
	case 86:
		return "UltraSPARC IIi";
	case 87:
		return "UltraSPARC III";
	case 88:
		return "UltraSPARC IIIi";
	case 96:
		return "68040";
	case 97:
		return "68xxx Family";
	case 98:
		return "68000";
	case 99:
		return "68010";
	case 100:
		return "68020";
	case 101:
		return "68030";
	case 112:
		return "Hobbit Family";
	case 120:
		return "Crusoe™ TM5000 Family";
	case 121:
		return "Crusoe™ TM3000 Family";
	case 122:
		return "Efficeon™ TM8000 Family";
	case 128:
		return "Weitek";
	case 130:
		return "Itanium™ Processor";
	case 131:
		return "AMD Athlon™ 64 Processor Family";
	case 132:
		return "AMD Opteron™ Processor Family";
	case 144:
		return "PA-RISC Family";
	case 145:
		return "PA-RISC 8500";
	case 146:
		return "PA-RISC 8000";
	case 147:
		return "PA-RISC 7300LC";
	case 148:
		return "PA-RISC 7200";
	case 149:
		return "PA-RISC 7100LC";
	case 150:
		return "PA-RISC 7100";
	case 160:
		return "V30 Family";
	case 176:
		return "Pentium III Xeon™ Processor";
	case 177:
		return "Pentium III Processor with Intel SpeedStep™ Technology";
	case 178:
		return "Pentium 4";
	case 179:
		return "Intel Xeon™";
	case 180:
		return "AS400 Family";
	case 181:
		return "Intel Xeon™ Processor MP";
	case 182:
		return "AMD AthlonXP™ Family";
	case 183:
		return "AMD Athlon™ MP Family";
	case 184:
		return "Intel Itanium 2";
	case 190:
		return "K7";
	case 198:
		return "Intel Core™ i7-2760QM";
	case 200:
		return "IBM390 Family";
	case 201:
		return "G4";
	case 202:
		return "G5";
	case 203:
		return "G6";
	case 204:
		return "z/Architecture base";
	case 250:
		return "i860";
	case 251:
		return "i960";
	case 260:
		return "SH-3";
	case 261:
		return "SH-4";
	case 280:
		return "ARM";
	case 281:
		return "StrongARM";
	case 300:
		return "6x86";
	case 301:
		return "MediaGX";
	case 302:
		return "MII";
	case 320:
		return "WinChip";
	case 350:
		return "DSP";
	case 500:
		return "Video Processor";
	default:
		return "Unkown";
	}
} // get_family_by_id


/*!
 * \note  This code is copied from following link:
 *		https://msdn.microsoft.com/en-gb/library/windows/desktop/aa363147%28v=vs.85%29.aspx
 */
BOOL GetDriveGeometry( LPWSTR wszPath, DISK_GEOMETRY *pdg )
{
  HANDLE hDevice = INVALID_HANDLE_VALUE;  // handle to the drive to be examined
  BOOL bResult   = FALSE;                 // results flag
  DWORD junk     = 0;                     // discard results

  hDevice = CreateFileW(wszPath,          // drive to open
						0,                // no access to the drive
						FILE_SHARE_READ | // share mode
						FILE_SHARE_WRITE,
						NULL,             // default security attributes
						OPEN_EXISTING,    // disposition
						0,                // file attributes
						NULL);            // do not copy file attributes

  if (hDevice == INVALID_HANDLE_VALUE)    // cannot open the drive
  {
	return (FALSE);
  }

  bResult = DeviceIoControl(hDevice,                       // device to be queried
							IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
							NULL, 0,                       // no input buffer
							pdg, sizeof(*pdg),            // output buffer
							&junk,                         // # bytes returned
							(LPOVERLAPPED) NULL);          // synchronous I/O

  CloseHandle(hDevice);

  return (bResult);
} // GetDriveGeometry


/*!
 * \brief Returns type of storage.
 * \param _name: Name of interface in string.
 * \param _interface Type of interface.
 */
inline SystemInformation::Storage::Type get_media_type(
							const QString &_name,
							SystemInformation::Storage::Interface _interface
						)
{

	if ( _name == "External hard disk media" )
	{
		return SystemInformation::Storage::Type::ExternalDisk;
	}
	else if ( _name == "Fixed hard disk media" )
	{
		return SystemInformation::Storage::Type::FixedDisk;
	}
	else if ( _name.toLower() == "removable media" )
	{
		if ( _interface == SystemInformation::Storage::Interface::USB )
		{
			return SystemInformation::Storage::Type::FlashDisk;
		}
		else
		{
			return SystemInformation::Storage::Type::RemovableMedia;
		}
	}
	else if ( _name == "Unknown" )
	{
		return SystemInformation::Storage::Type::Unknown;
	}
	else
	{
		PCORE_LOG_INFO( "New media type for windows: " + _name );
		return SystemInformation::Storage::Type::Unknown;
	}
} // get_media_type



/*!
 * \brief Returns type of interface by given string
 * \param _str: name of interface
 */
PCore::core::SystemInformation::Storage::Interface get_interface (
															const QString& _str)
{
	if ( _str == "SCSI" )
	{
		return PCore::core::SystemInformation::Storage::Interface::SCSI;
	}
	else if ( _str == "HDC" )
	{
		return PCore::core::SystemInformation::Storage::Interface::HDC;
	}
	else if ( _str == "IDE" )
	{
		return PCore::core::SystemInformation::Storage::Interface::ATA;
	}
	else if ( _str == "USB" )
	{
		return PCore::core::SystemInformation::Storage::Interface::USB;
	}
	else if ( _str == "1394" )
	{
		return PCore::core::SystemInformation::Storage::Interface::_1394;
	}
	else
	{
		PCORE_LOG_INFO( "New interface type for windows: " + _str );
		return PCore::core::SystemInformation::Storage::Interface::Unknown;
	}
} // get_interface


//==============================================================================
// classes
//==============================================================================
namespace PCore
{
	namespace core
	{
		//==============================================================================
		// getProcesses
		//==============================================================================
		QList<SystemInformation::Processor>
										SystemInformation::getProcesses( void )
		{
			PCore::core::windows::WMI wmi;

			if ( wmi.selectAll("Win32_Processor") == false )
			{
				PCORE_LOG_ERROR("Retrieveing processor information failed." );
				return QList<Processor>();
			}


			QList<Processor> list;
			quint16 index = 0;
			while ( wmi.nextItem() == true )
			{
				int max_clock		= wmi.getInt( "MaxClockSpeed" ) * 1000;
				int min_clock		= wmi.getInt( "MinClockSpeed" ) * 1000;
				int current_clock	= wmi.getInt( "CurrentClockSpeed" ) * 1000;
				int l1_cache_size	= 0;
				int l2_cache_size	= wmi.getInt( "L2CacheSize" ) * 1024;
				int l3_cache_size	= wmi.getInt( "L3CacheSize" ) * 1024;
				short bus_width		= wmi.getShortInt( "DataWidth" );
				short load_percent	= wmi.getShortInt( "LoadPercentage" );
				Processor::PowerMode pwd_mode = Processor::PowerMode::Powersave;

				pwd_mode =	 load_percent > 50
							 ? Processor::PowerMode::Preformance
							 : Processor::PowerMode::Powersave;

				Processor info;
				info.model			= wmi.getString( "Name" );
				info.arch			= get_arch_by_id( wmi.getShortInt( "Architecture" ) );
				info.arch_name		= get_arch_name_by_id(  wmi.getShortInt( "Architecture" ) );
				info.vendor			= wmi.getString( "Manufacturer" );
				info.logical_cores	= wmi.getInt( "NumberOfLogicalProcessors" );
				info.total_cores	= wmi.getInt( "NumberOfCores" );
				info.threads		= wmi.getInt( "ThreadCount" );
				info.total_cache	= l1_cache_size + l2_cache_size + l3_cache_size;

				for ( int i = 0; i < info.logical_cores; i++ )
				{
					Processor::Core c;
					Processor::CacheLevel l1,l2,l3;
					c.power_mode		= pwd_mode;

					l1.data_size		= l1_cache_size;
					l1.size				= l1_cache_size;
					c.cache_levels[1]	= l1;

					l2.data_size		= l2_cache_size;
					l2.size				= l2_cache_size;
					c.cache_levels[2]	= l2;

					l3.data_size		= l3_cache_size;
					l3.size				= l3_cache_size;
					c.cache_levels[3]	= l3;

					c.freq.current		= current_clock;
					c.freq.max			= max_clock;
					c.freq.min			= min_clock;

					info.cores[i] = c;
				}



				#if PCORE_ARCH_FAMILY == PCORE_ARCH_FAMILY_X86

					if ( info.vendor == "GenuineIntel" )
					{
						auto a = get_intel_cpuid_info();

						info.other_params[ "model" ] =  a.model ;
						info.other_params[ "stepping" ] = a.stepping ;
						info.other_params[ "processor_type" ] =  a.processor_type ;
						info.other_params[ "extended_model" ] = a.extended_model ;
						info.other_params[ "family" ] = a.family ;
						info.other_params[ "extended_family" ] =  a.extended_family;
						info.other_params[ "brand_id" ] = a.brand_id ;
						info.other_params[ "signature" ] = a.signature ;
						info.other_params[ "serial" ] = a.serial;
						info.extensions = a.extensions;
					}
					else if ( info.vendor == "AuthenticAMD" ||
							  info.vendor == "AMDisbetter!" )
					{
						auto a = get_amd_cpuid_info();

						for ( int i : info.cores.keys() )
						{
							info.cores[i].cache_levels[1].size = a.cache_l1_size;
							info.cores[i].cache_levels[1].data_size = a.cache_l1_size;
							info.cores[i].cache_levels[2].size = a.cache_l2_size;
							info.cores[i].cache_levels[2].data_size = a.cache_l2_size;
							info.cores[i].cache_levels[3].size = a.cache_l2_size;
							info.cores[i].cache_levels[3].data_size = a.cache_l2_size;
						}

						info.other_params[ "model" ] =  a.model ;
						info.other_params[ "stepping" ] = a.stepping ;
						info.other_params[ "extended_model" ] = a.extended_model ;
						info.other_params[ "family" ] = a.family ;
						info.other_params[ "extended_family" ] =  a.extended_family;
						info.other_params[ "brand_id" ] = a.brand_id ;
						info.other_params[ "brand_id_ex" ] = a.brand_id_ex ;
						info.other_params[ "l1_cache_data_size" ] = a.cache_l1_size_data ;
						info.other_params[ "l1_cache_instruction_size" ] = a.cache_l1_size_instruction ;
						info.extensions = a.extensions;
					}

				#endif // PCORE_ARCH_FAMILY_X86

				list.push_back( info );
				index++;
			}

			return list;
		} // getProcesses


		//==============================================================================
		// getVideoControllers
		//==============================================================================
		QList<SystemInformation::VideoControllerInformation>
								SystemInformation::getVideoControllers( void )
		{
			PCore::core::windows::WMI wmi;

			if ( wmi.selectAll("Win32_VideoController") == false )
			{
				PCORE_LOG_ERROR("Retrieveing processes information failed." );
				return QList<VideoControllerInformation>();
			}

			QList<VideoControllerInformation> list;
			while ( wmi.nextItem() == true )
			{
				VideoControllerInformation info;
				info.name					= wmi.getString( "Name" );
				info.model					= wmi.getString( "VideoProcessor" );
				info.vendor					= wmi.getString( "AdapterCompatibility" );
				info.video_mode_desc		= wmi.getString( "VideoModeDescription" );
				info.memory_size			= wmi.getInt( "AdapterRAM" );
				info.current_refresh_rate	= wmi.getInt( "CurrentRefreshRate" );
				info.max_refresh_rate		= wmi.getInt( "MaxRefreshRate" );
				info.min_refresh_rate		= wmi.getInt( "MinRefreshRate" );
				info.is_running				= wmi.getShortInt( "Availability" ) == 3? true: false;
				info.current_num_of_colors	= wmi.getLongInt( "CurrentNumberOfColors" );
				info.current_bits_per_pixel	= wmi.getLongInt( "CurrentBitsPerPixel" );
				info.current_resolution_horizantal	= wmi.getInt( "CurrentHorizontalResolution" );
				info.current_resolution_vertical	= wmi.getInt( "CurrentVerticalResolution" );

				list.push_back( info );
			} // while

			return list;
		} // getVideoControllers


		//==============================================================================
		// getStorages
		//==============================================================================
		QList<SystemInformation::Storage>
									SystemInformation::getStorages()
		{
			PCore::core::windows::WMI wmi;
			QList<Storage> list;
			quint16 index = 0;

			if ( wmi.selectAll("Win32_DiskDrive") == true )
			{
				while ( wmi.nextItem() == true )
				{
					Storage info;
					info.name				= wmi.getString( "Name" );
					info.model				= wmi.getString( "Model" );
					info.vendor				= wmi.getString( "Manufacturer" );
					info.serial				= wmi.getString( "SerialNumber" );
					info.capacity			= wmi.getLongInt( "Size" );
					//info.partitions		= wmi.getInt( "Partitions" );
					info.heads				= wmi.getInt( "TotalHeads" );
					info.cylinders			= wmi.getLongInt( "TotalCylinders" );
					info.tracks_per_cylinder= wmi.getInt( "TracksPerCylinder" );
					info.sectors_per_track	= wmi.getInt( "SectorsPerTrack" );
					info.bytes_per_sector	= wmi.getInt( "BytesPerSector" );
					info.block_size			= wmi.getLongInt( "DefaultBlockSize" );
					info.interface_type		= get_interface( wmi.getString( "InterfaceType" ) );

					DISK_GEOMETRY pdg = { 0 };
					if ( GetDriveGeometry( (LPWSTR)info.name.toStdWString().data(), &pdg ) )
					{
						info.cylinders = pdg.Cylinders.QuadPart;
						info.bytes_per_sector = pdg.BytesPerSector;
						info.sectors_per_track = pdg.SectorsPerTrack;
						info.tracks_per_cylinder =  pdg.TracksPerCylinder;
						info.capacity = pdg.Cylinders.QuadPart *
										pdg.BytesPerSector *
										pdg.SectorsPerTrack *
										pdg.TracksPerCylinder;

					}


					auto cap = wmi.getIntArray( "Capabilities" );
					if ( cap.indexOf( 3 ) >= 0 ) info.is_random_access = true;
					if ( cap.indexOf( 4 ) >= 0 ) info.is_writable = true;
					if ( cap.indexOf( 7 ) >= 0 ) info.is_removeable = true;
					if ( cap.indexOf( 2 ) >= 0 ) info.is_sequential = true;


					info.type = get_media_type(
							wmi.getString( "MediaType" ), info.interface_type );

					index++;
					list.push_back( info );
				} // while
			}
			else
			{
				PCORE_LOG_ERROR("Retrieveing disk informations failed." );
			}

			//----------------------
			// floppy
			//----------------------
			if ( wmi.selectAll("Win32_FloppyDrive") == true )
			{
				while ( wmi.nextItem() == true )
				{
					Storage info;
					info.name				= wmi.getString( "Name" );
					info.model				= "Floppy drive";
					info.vendor				= wmi.getString( "Manufacturer" );
					info.serial				= "";
					info.capacity			= 0;
					info.heads				= 0;
					info.cylinders			= wmi.getLongInt( "TotalCylinders" );
					info.tracks_per_cylinder= wmi.getInt( "TracksPerCylinder" );
					info.sectors_per_track	= wmi.getInt( "SectorsPerTrack" );
					info.bytes_per_sector	= wmi.getInt( "BytesPerSector" );
					info.interface_type		= Storage::Interface::ATA;
					info.type				= Storage::Type::Floppy;

					DISK_GEOMETRY pdg = { 0 };
					if ( GetDriveGeometry( (LPWSTR)info.name.toStdWString().data(), &pdg ) )
					{
						info.cylinders = pdg.Cylinders.QuadPart;
						info.bytes_per_sector = pdg.BytesPerSector;
						info.sectors_per_track = pdg.SectorsPerTrack;
						info.tracks_per_cylinder =  pdg.TracksPerCylinder;
						info.capacity = pdg.Cylinders.QuadPart *
										pdg.BytesPerSector *
										pdg.SectorsPerTrack *
										pdg.TracksPerCylinder;
					}

					info.is_random_access = true;
					info.is_writable = true;
					info.is_removeable = true;
					info.is_sequential = false;

					index++;
					list.push_back( info );
				} // while
			}
			else
			{
				PCORE_LOG_ERROR("Retrieveing floppy informations failed." );
			}



			//----------------------
			// Tape
			//----------------------
			if ( wmi.selectAll("Win32_TapeDrive") == true )
			{
				while ( wmi.nextItem() == true )
				{
					Storage info;
					info.name				= wmi.getString( "Name" );
					info.model				= "Tape drive";
					info.vendor				= wmi.getString( "Manufacturer" );
					info.serial				= "";
					info.capacity			= 0;
					info.heads				= 0;
					info.cylinders			= 0;
					info.tracks_per_cylinder= 0;
					info.sectors_per_track	= 0;
					info.bytes_per_sector	= 0;
					info.interface_type		= Storage::Interface::Unknown;
					info.type				= Storage::Type::Tape;
					// TODO: block size and padding size must be added

					auto cap = wmi.getIntArray( "Capabilities" );
					if ( cap.indexOf( 3 ) >= 0 ) info.is_random_access = true;
					if ( cap.indexOf( 4 ) >= 0 ) info.is_writable = true;
					if ( cap.indexOf( 7 ) >= 0 ) info.is_removeable = true;
					if ( cap.indexOf( 2 ) >= 0 ) info.is_sequential = true;

					index++;
					list.push_back( info );
				} // while
			}
			else
			{
				PCORE_LOG_ERROR("Retrieveing tape informations failed." );
			}

			//----------------------
			// Logical drives
			//----------------------
			PCore::core::windows::WMI wmi_2;
			for ( Storage &st : list )
			{
				QString q1 = "Associators of {Win32_DiskDrive.DeviceID='" +
							 st.name +
							 "'} where AssocClass=Win32_DiskDriveToDiskPartition";

				if ( wmi.executeQuery( q1 ) == true )
				{
					while ( wmi.nextItem() == true )
					{
						QString q = "Associators of {Win32_DiskPartition.DeviceID='" +
									wmi.getString("DeviceID") +
									"'} where AssocClass=Win32_LogicalDiskToPartition";
						if ( wmi_2.executeQuery( q ) == true )
						{
							while ( wmi_2.nextItem() == true )
							{
								st.partitions.push_back( wmi_2.getString("DeviceID") );
							}
						}
						else
						{
							PCORE_LOG_ERROR("Getting list of partitions failed for device:'"
											+ st.name + "'");
						}
					}
				}
				else
				{
					PCORE_LOG_ERROR("Getting list of partitions failed for device:'"
									+ st.name + "'");
				}
			}

			return list;
		} // getStorages


		//==============================================================================
		// getMonitors
		//==============================================================================
		QList<SystemInformation::MonitorInformation> SystemInformation::getMonitors()
		{
			DISPLAY_DEVICE adapter = {0};
			QList<MonitorInformation> list;
			DWORD index_adapter = 0;
			int index_general = 0;

			adapter.cb = sizeof( DISPLAY_DEVICE );

			while( EnumDisplayDevicesW( NULL, index_adapter, &adapter, 0 ) )
			{
				DWORD index_monitor = 0;
				DISPLAY_DEVICE monitor = {0};
				monitor.cb = sizeof( DISPLAY_DEVICE );

				while ( EnumDisplayDevicesW( adapter.DeviceName,
											 index_monitor, &monitor, 0 ) )
				{
					MonitorInformation info;
					info.index = index_general++;
					info.name = QString::fromWCharArray( monitor.DeviceName );
					info.connected_to = QString::fromWCharArray( adapter.DeviceName );
					info.model = QString::fromWCharArray( monitor.DeviceString );

					DEVMODE mode;
					mode.dmSize = sizeof( DEVMODE );
					if ( EnumDisplaySettingsW( adapter.DeviceName,
										ENUM_CURRENT_SETTINGS, &mode) != false )
					{
						info.screen_height = mode.dmPelsHeight;
						info.screen_width = mode.dmPelsWidth;
					}
					list.push_back( info );

					ZeroMemory( &monitor, sizeof(DISPLAY_DEVICE) );
					monitor.cb = sizeof( DISPLAY_DEVICE );
					index_monitor++;
				} // while monitor

				ZeroMemory( &adapter, sizeof(DISPLAY_DEVICE) );
				adapter.cb = sizeof( DISPLAY_DEVICE );
				index_adapter++;
			} // while adapter

			return list;
		} // getMonitors

		//==============================================================================
		// getSoundCards
		//==============================================================================
		QList<SystemInformation::SoundCardInformation>
											SystemInformation::getSoundCards()
		{
			PCore::core::windows::WMI wmi;
			QList<SoundCardInformation> list;
			quint16 index = 0;

			if ( wmi.selectAll("Win32_SoundDevice") == true )
			{
				while ( wmi.nextItem() == true )
				{
					SoundCardInformation info;
					info.index = index;
					info.name = wmi.getString( "DeviceID" );
					info.model = wmi.getString( "ProductName" );
					info.vendor = wmi.getString( "Manufacturer" );


					index++;
					list.push_back( info );
				} // while
			}
			else
			{
				PCORE_LOG_ERROR("Retrieveing sound card informations failed." );
				return list;
			}

			return list;
		} // getSoundCards

	} // core
} // PCore
#endif // PCORE_OS_WINDOWS


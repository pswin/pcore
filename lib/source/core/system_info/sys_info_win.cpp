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



//==============================================================================
// functions
//==============================================================================


/*!
 * \brief Retrieves architecture's name by specified ID.
 * \param _id: ID of architecture.
 * \return Architecture's name.
 */
QString get_arch_by_id ( int _id )
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
			return "x64";
		default:
			return "Unkown";
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
		QList<SystemInformation::ProcessorInformation>
										SystemInformation::getProcesses( void )
		{
			PCore::core::windows::WMI wmi;

			if ( wmi.selectAll("Win32_Processor") == false )
			{
				PCORE_LOG_ERROR("Retrieveing processor information failed." );
				return QList<ProcessorInformation>();
			}


			QList<ProcessorInformation> list;
			quint16 index = 0;
			while ( wmi.nextItem() == true )
			{
				ProcessorInformation info;
				info.index			= index;
				info.name			= wmi.getString( "Name" );
				info.architecture_id= wmi.getShortInt( "Architecture" );
				info.architecture	= get_arch_by_id( info.architecture_id );
				info.vendor			= wmi.getString( "Manufacturer" );
				info.max_clock		= wmi.getInt( "MaxClockSpeed" );
				info.family_id		= wmi.getShortInt( "Family" );
				info.family			= get_family_by_id( info.family_id );
				info.l2_cache_size	= wmi.getInt( "L2CacheSize" );
				info.l3_cache_size	= wmi.getInt( "L3CacheSize" );
				info.num_of_logical_cores	= wmi.getInt( "NumberOfLogicalProcessors" );
				info.num_of_cores	= wmi.getInt( "NumberOfCores" );
				info.num_of_threads	= wmi.getInt( "ThreadCount" );
				info.data_width		= wmi.getShortInt( "DataWidth" );


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

						info.l1_cache_size = a.cache_l1_size;
						info.l2_cache_size = a.cache_l2_size;
						info.l3_cache_size = a.cache_l2_size;

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
			quint16 index = 0;
			while ( wmi.nextItem() == true )
			{
				VideoControllerInformation info;
				info.index = index;
				info.name = wmi.getString( "Name" );
				info.vendor = wmi.getString( "AdapterCompatibility" );
				info.video_mode_desc = wmi.getString( "VideoModeDescription" );
				info.memory_size = wmi.getInt( "AdapterRAM" );
				info.current_refresh_rate = wmi.getInt( "CurrentRefreshRate" );
				info.max_refresh_rate = wmi.getInt( "MaxRefreshRate" );
				info.min_refresh_rate = wmi.getInt( "MinRefreshRate" );
				info.is_running = wmi.getShortInt( "Availability" ) == 3? true: false;
				info.current_num_of_colors = wmi.getLongInt( "CurrentNumberOfColors" );
				info.current_bits_per_pixel = wmi.getLongInt( "CurrentBitsPerPixel" );
				info.current_resolution_horizantal = wmi.getInt( "CurrentHorizontalResolution" );
				info.current_resolution_vertical = wmi.getInt( "CurrentVerticalResolution" );

				index++;
				list.push_back( info );
			} // while

			return list;
		} // getVideoControllers


		//==============================================================================
		// getSorageInformation
		//==============================================================================
		QList<SystemInformation::StorageInformation>
									SystemInformation::getSorageInformation()
		{
			PCore::core::windows::WMI wmi;
			QList<StorageInformation> list;
			quint16 index = 0;

			if ( wmi.selectAll("Win32_DiskDrive") == true )
			{
				while ( wmi.nextItem() == true )
				{
					bool	is_random_access;		 //! Is a random access device.

					StorageInformation info;
					info.index = index;
					info.name = wmi.getString( "Name" );
					info.model = wmi.getString( "Model" );
					info.vendor = wmi.getString( "Manufacturer" );
					info.serial = wmi.getString( "SerialNumber" );
					info.signature = QString::number( wmi.getInt( "Signature" ));
					info.capacity = wmi.getLongInt( "Size" );
					info.num_of_partitions = wmi.getInt( "Partitions" );
					info.heads = wmi.getInt( "TotalHeads" );
					info.cylinders = wmi.getLongInt( "TotalCylinders" );
					info.tracks_per_cylinder = wmi.getInt( "TracksPerCylinder" );
					info.sectors_per_track = wmi.getInt( "SectorsPerTrack" );
					info.bytes_per_sector = wmi.getInt( "BytesPerSector" );


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

					QString interfac = wmi.getString( "InterfaceType" );

					if ( interfac == "SCSI" )
					{
						info.interface_type = InterfaceType::SCSI;
					}
					else if ( interfac == "HDC" )
					{
						info.interface_type = InterfaceType::HDC;
					}
					else if ( interfac == "IDE" )
					{
						info.interface_type = InterfaceType::IDE;
					}
					else if ( interfac == "USB" )
					{
						info.interface_type = InterfaceType::USB;
					}
					else if ( interfac == "1394" )
					{
						info.interface_type = InterfaceType::_1394;
					}
					else
					{
						PCORE_LOG_INFO( "New interface type for windows: " + interfac );
						info.interface_type = InterfaceType::Unknown;
					}


					index++;
					list.push_back( info );
				} // while
			}
			else
			{
				PCORE_LOG_ERROR("Retrieveing disk informations failed." );
				return QList<StorageInformation>();
			}



			return list;
		} // getSorageInformation

	} // core
} // PCore
#endif // PCORE_OS_WINDOWS


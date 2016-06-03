//##############################################################################
//#	title:	System information for Linux based operating systems
//#	c-date:	May-11-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "include/pcore/pcore_def.h"
#include "include/pcore/core/system_information.h"

#if PCORE_OS == PCORE_OS_LINUX

//=====================================
// Headers
//=====================================

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QMap>
#include <QRegExp>
#include <QVariant>

#include <include/pcore/core/logger.h>
#include "headers/core/linux/udev.h"

#include <unistd.h>
#include <sys/utsname.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>


using namespace PCore::core;

//=====================================
// Defines
//=====================================

#define _PCORE_LINUX_SYS_DIR "/sys/devices/system"

//! CPU
#define _PCORE_LINUX_CPU_DIR _PCORE_LINUX_SYS_DIR "/cpu/cpu"
#define _PCORE_LINUX_CPUINFO "/proc/cpuinfo"


//=====================================
// Helper functions
//=====================================


//==============================================================================
// size to uint
//==============================================================================
//! converts size to number
quint64 size_to_uint( const QString& _str, const QString& _unit = "b" )
{
	QString digit;
	QString unit = _unit;
	quint64 unit_rate = 1;

	QRegExp rx( "(\\d+)\\s*(\\w*)" );

	rx.indexIn( _str );

	QStringList ls = rx.capturedTexts(  );

	if ( ls.count() != 0 )
	{
		digit = ls[1];

		if ( ls.count() == 3 )
		{
			unit = ls[2];
		}
	}

	unit = unit.toLower();
	if ( (unit == "k") || (unit == "kb") )
	{
		unit_rate = PCORE_1KB;
	}
	else if ( (unit == "m") || (unit == "mb") )
	{
		unit_rate = PCORE_1MB;
	}
	else if ( (unit == "g") || (unit == "gb") )
	{
		unit_rate = PCORE_1GB;
	}
	else if ( (unit == "t") || (unit == "tb") )
	{
		unit_rate = PCORE_1TB;
	}

	return digit.toLongLong() * unit_rate;

} // size_to_uint


//==============================================================================
// get_range
//==============================================================================

QList<int> get_range( const QString& _str )
{
	QRegExp rx("(\\d+)\\-(\\d*)");

	if ( rx.indexIn( _str ) == -1 ) return QList<int>();

	QStringList ls = rx.capturedTexts(  );

	int from = ls[0].toInt();
	int to = from;
	if ( ls.size() == 2 )
	{
		to = ls[1].toInt();
	}

	QList<int> list;
	for ( int i = from; i <= to; i++ )
	{
		list.push_back( i );
	}

	return list;
} // get_range


//==============================================================================
// get_arch_by_name
//==============================================================================
SystemInformation::Processor::Architecture get_arch_by_name( const QString& _str )
{
	QStringList x86 = { "i686", "i686-AT386", "i386", "x86", "x86pc" };
	QStringList x64 = { "x86_64", "amd64", "ia64" };
	QStringList arm = { "armv7l", "armv6l", "armeb", "arm", "armel" };
	QStringList arm64 = { "armv8", "armv8l", "arm64" };
	QStringList powerpc = { "ppc", "powerpc" };
	QStringList powerpc64 = { "ppc64", "ppc64" };
	QStringList sparc = { "sun4u", "sparc" };
	QStringList sparc64 = { "sparc64" };
	QStringList mips = { "mips", "mipsel" };
	QStringList mips64 = { "mips64" };

	if ( x86.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::X86;
	}
	if ( x64.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::X86_64;
	}
	if ( arm.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::ARM;
	}
	if ( arm64.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::ARM_64;
	}
	if ( powerpc.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::PowerPC;
	}
	if ( powerpc64.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::PowerPC_64;
	}
	if ( sparc.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::SPARC;
	}
	if ( sparc64.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::SPARC_64;
	}
	if ( mips.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::MIPS;
	}
	if ( mips64.indexOf( _str ) >= 0 )
	{
		return PCore::core::SystemInformation::Processor::Architecture::MIPS_64;
	}
	else
	{
		return PCore::core::SystemInformation::Processor::Architecture::Other;
	}
} // get_arch_by_name


//==============================================================================
// get_value_from_file
//==============================================================================
QString get_value_from_file( const QString& _filename )
{
	if ( QFile::exists( _filename) == false )
	{
		PCORE_LOG_ERROR( "Can not find file '" + _filename + "'" );
		return "";
	}

	QFile f ( _filename );
	if ( f.open( QFile::ReadOnly | QFile::Text ) == false )
	{
		PCORE_LOG_ERROR( "Can not open file '" + _filename + "'" );
		return "";
	}

	QString str = f.readAll();

	f.close();

	return str;
} // get_value_from_file


//==============================================================================
// get_cache_info
//==============================================================================
QMap<quint16,SystemInformation::Processor::CacheLevel> get_cache_info( quint16 _id )
{
	QString base_path = _PCORE_LINUX_CPU_DIR + QString::number( _id );
	QMap<quint16,SystemInformation::Processor::CacheLevel> caches;


	QString cache_path = base_path + "/cache/";
	QDir d( cache_path );
	for ( QString it : d.entryList( QDir::Dirs ) )
	{
		if ( (it == ".") || (it == "..") )
		{
			continue;
		}

		QString level_path = cache_path + it + "/";
		quint16 level = get_value_from_file( level_path + "level" ).toShort();

		QString type = get_value_from_file( level_path + "type" );
		quint64 size = size_to_uint( get_value_from_file( level_path + "size" ) );

		if ( type == "Instruction" )
		{
			caches[level].instrction_size = size;
			caches[level].size += size;
		}
		else if ( type == "Data" )
		{
			caches[level].data_size = size;
			caches[level].size += size;
		}
		else
		{
			caches[level].size = size;
		}

		caches[level].line_size =
				get_value_from_file( level_path + "coherency_line_size" ).toShort();

		caches[level].ways_of_associativity =
				get_value_from_file( level_path + "ways_of_associativity" ).toShort();
	} // for

	return caches;
} // get_cach_info


//==============================================================================
// get_total_cache
//==============================================================================

quint32 get_total_cache( quint16 _cpu_id, quint16 _core_num )
{
	QString base_path = _PCORE_LINUX_CPU_DIR + QString::number( _cpu_id );
	quint32 total = 0;

	QString cache_path = base_path + "/cache/";
	QDir d( cache_path );
	for ( QString it : d.entryList( QDir::Dirs ) )
	{
		if ( (it == ".") || (it == "..") )
		{
			continue;
		}

		auto ls = get_range( get_value_from_file( cache_path + it + "/shared_cpu_list" ) );
		int size = size_to_uint( get_value_from_file( cache_path + it + "/size" ) );

		if ( ls.size() == _core_num )
		{
			total += size;
		}
		else
		{
			total += ls.size() * size;
		}
	} // for

	return total;
} // get_total_cache


//==============================================================================
// get_freq_info
//==============================================================================

SystemInformation::Processor::Freq get_freq_info( quint16 _core_id )
{
	SystemInformation::Processor::Freq f;
	QString base_path = _PCORE_LINUX_CPU_DIR + QString::number( _core_id );

	QString freq_path = base_path + "/cpufreq/";
	f.current = get_value_from_file( freq_path + "scaling_cur_freq" ).toUInt();
	f.max = get_value_from_file( freq_path + "cpuinfo_max_freq" ).toUInt();
	f.min = get_value_from_file( freq_path + "cpuinfo_min_freq" ).toUInt();

	return f;
} // get_freq_info


//==============================================================================
// get_power_info
//==============================================================================

SystemInformation::Processor::PowerMode get_power_info( int _core_id )
{
	QString mode = get_value_from_file(
							_PCORE_LINUX_CPU_DIR + QString::number( _core_id ) +
							"/cpufreq/scaling_governor" );

	if ( mode.indexOf("powersave") != -1 )
	{
		return SystemInformation::Processor::PowerMode::Powersave;
	}
	else if ( mode.indexOf("performance") != -1 )
	{
		return SystemInformation::Processor::PowerMode::Preformance;
	}

	return SystemInformation::Processor::PowerMode::Unkown;
} // get_power_info


//==============================================================================
// get_hd_dev_type
//==============================================================================

PCore::core::SystemInformation::Storage::Type getType(
									const PCore::core::Udev::UdevDevice& _dev )
{
	if ( _dev.isNull() ) return SystemInformation::Storage::Type::Unknown;



}

//==============================================================================
// Code
//==============================================================================
namespace PCore
{
	namespace core
	{

		//======================================================================
		// getProcessors
		//======================================================================
		//! getProcesses
		QList<SystemInformation::Processor> SystemInformation::getProcesses( void )
		{
			QList<Processor> list;
			QMap<int, Processor> cpus;

			QFile f( _PCORE_LINUX_CPUINFO );

			if ( f.open( QFile::ReadOnly | QFile::Text ) == false )
			{
				PCORE_LOG_ERROR( "Retrieveing cpu information failed; Because opening '"
								 + QString(_PCORE_LINUX_CPUINFO) + "' failed." );
				return list;
			}

			QTextStream st( &f );
			QString ln;
			Processor current;
			int current_sibling = 0;
			int current_cores = 0;
			int current_physical_id = 0;
			QString current_machine_name = "";
			Processor::Architecture current_arch = Processor::Architecture::Unkown;

			//----------------------
			// getting arch
			//----------------------

			struct utsname uts;
			if ( uname( &uts ) == 0 )
			{
				current_machine_name = uts.machine;
				current_arch = get_arch_by_name( current_machine_name );
			}
			else
			{

				PCORE_LOG_ERROR( "Uname failed." );
			}

			//----------------------
			// Reading cpuinfo
			//----------------------
			ln = st.readLine( );
			while ( (ln = st.readLine() ).isNull() == false )
			{

				if ( ln.isEmpty() == true )
				{
					current.arch_name = current_machine_name;
					current.arch = current_arch;
					current.total_cache = get_total_cache( current_physical_id,
											current.logical_cores );
					cpus[current_physical_id] = current;
			//		current = {};
					continue;
				}

				QList<QString> params = ln.split( ":" );
				QString p1 = params[0];
				p1 = p1.trimmed();

				if ( p1 == "vendor_id" )
				{
					current.vendor = params[1].trimmed();
				}
				else if ( p1 == "physical id" )
				{
					current_physical_id = params[1].trimmed().toInt();
				}
				else if ( p1 == "model name" )
				{
					current.model = params[1].trimmed();
				}
				else if ( p1 == "siblings" )
				{
					current_sibling = params[1].trimmed().toInt();
				}
				else if ( p1 == "cpu cores" )
				{
					current_cores = params[1].trimmed().toInt();
				}
				else if ( p1 == "cpu Mhz" )
				{
					// just ignore it
				}
				else if (  (p1 == "flags") || (p1 == "features") )
				{
					current.extensions = params[1].trimmed().split( " " );
				}
				else if ( p1 == "core id" )
				{
					quint16 core_id = params[1].trimmed().toShort();
					current.cores[ core_id ].cache_levels = get_cache_info( core_id );
					current.cores[ core_id ].freq = get_freq_info( core_id );
					current.cores[ core_id ].power_mode = get_power_info( core_id );
				}
				else if (  (p1 == "address size") )
				{
					QStringList list2 = params[1].trimmed().split(",");

					for ( auto it : list2 )
					{
						QStringList list3 = it.split( " " );
						if ( list3.count() == 3 )
						{
							QString p11 = list3[2].trimmed();
							if ( p11 == "physical" )
							{
								current.bus.address_width = list3[0].trimmed().toShort();
							}
							else if ( p11 == "virtual" )
							{
								current.bus.virutal_address_with = list3[0].trimmed().toShort();
							}
						}
					}
				}
				else
				{
					current.other_params[p1] = params[1].trimmed();
				}

				current.total_cores = current_sibling;
				current.logical_cores =  current_cores;
				current.threads = current_sibling - current_cores;
			} // while


			list = cpus.values();

			return list;
		} // getProcesses


		//! getVideoControllers
		QList<SystemInformation::VideoControllerInformation>
										SystemInformation::getVideoControllers()
		{
			return QList<VideoControllerInformation>();
		} // getVideoControllers

		//! getStorages
		QList<SystemInformation::Storage> SystemInformation::getStorages( void )
		{
			QList<Storage> list;

			Udev dev;
			dev.addMatchClass( "scsi" );
			dev.addMatchProperty( "DEVTYPE", "scsi_device" );

			auto ls = dev.scan();

			for ( auto it : ls )
			{
				SystemInformation::Storage st;
				Udev::UdevDevice block = it.getChildSubsystem( "block" );
				Udev::UdevDevice usb = it.getParentBySubsystemAndDevType( "usb", "usb_device" );

				if ( block.isNull() == false )
				{

					st.name		= block.getNode();
					st.model	= block.getProperty("ID_MODEL");
					st.vendor	= block.getSystemAttribute("device/vendor");
					st.serial	= block.getProperty("ID_SERIAL_SHORT");
					st.capacity	= block.getSystemAttribute("size").toLongLong()/2;

					QString interface  = block.getProperty("ID_BUS");

					if ( usb.isNull() == false && interface == "ata" )
					{
						st.type = Storage::Type::ExternalDisk;
						st.interface = Storage::Interface::USB;
						st.is_random_access = true;
					}
					else if ( usb.isNull() == false && interface == "usb" )
					{
						st.type = Storage::Type::FlashDisk;
						st.interface = Storage::Interface::USB;
						st.is_random_access = true;
					}
					else if ( interface == "ata" )
					{
						if ( block.getProperty("ID_ATA_SATA") == "1" )
						{
							st.interface = Storage::Interface::SATA;
						}
						else if ( block.getProperty("ID_ATA_HDC") == "1" )
						{
							st.interface = Storage::Interface::HDC;
						}
						else if ( block.getProperty("1394") == "1" )
						{
							st.interface = Storage::Interface::_1394;
						}
						else
						{
							st.interface = Storage::Interface::ATA;
						}

						st.is_random_access = true;
						st.type = Storage::Type::FixedDisk;
					}

					if ( ( block.getSystemAttribute( "removable" ) == "1") ||
						 ( st.interface == Storage::Interface::USB ) )
					{
						st.is_removeable = true;
					}

					st.is_writable = true;
					if ( block.getSystemAttribute( "ro" ) == "1" )
					{
						st.is_writable = false;
					}


					if ( block.getProperty("ID_TYPE") == "disk" )
					{
						st.bytes_per_sector = block.getSystemAttribute("queue/hw_sector_size").toUInt();
						st.block_size = block.getSystemAttribute("queue/physical_block_size").toUInt();
						// TODO: cylinders, tracks

						auto ar = it.getSubSystems( "block" );
						for ( auto it2 : ar )
						{
							if ( it2.getSystemAttribute("partition").isNull() == false )
							{
								st.partitions.push_back( it2.getSystemName() );
							}
							it2.release();
						}
					} // if disk
				} // block

				if ( block.getProperty("ID_TYPE") == "disk" )
				list.push_back( st );

				block.release();
				it.release();
			}

			return list;
		} // getStorages

		//! getMonitors
		QList<SystemInformation::MonitorInformation> SystemInformation::getMonitors()
		{
			return QList<MonitorInformation>();
		} // getMonitors

		//! getSoundCards
		QList<SystemInformation::SoundCardInformation> SystemInformation::getSoundCards()
		{
			Udev dev;
			dev.addMatchClass( "sound" );

			auto list = dev.scan();

			for ( auto it : list )
			{
				auto p = it.getParent();

				if ( it.getSystemName().indexOf("card") == 0 )
				{
					auto ls2 = it.getSubSystems( "input" );

					for ( auto it2 : ls2 )
					{
						if ( it2.getNode().isNull() == false )
						qDebug() << it.getSystemName()
								 << it2.getType()
								 << it2.getNode()
								 << it2.getSystemName()
								 << it2.getSystemAttribute("vendor_name")
								 << it2.getSystemAttribute("name")
									;

					}

				}



			}


			return QList<SoundCardInformation>();
		} // getSoundCards


	} // core
} // PCore

#endif // PCORE_OS_LINUX


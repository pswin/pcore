//##############################################################################
//#	title:	Global methods for system info
//#	c-date:	May-19-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "include/pcore/core/system_information.h"


namespace PCore
{
	namespace core
	{

		//======================================================================
		// Processor
		//======================================================================

		//! Processor::Architecture
		QString SystemInformation::Processor::getString(
							SystemInformation::Processor::Architecture _arch )
		{
			switch ( _arch )
			{
				case SystemInformation::Processor::Architecture::X86:
					return "X86";
				case SystemInformation::Processor::Architecture::X86_64:
					return "X86-64";
				case SystemInformation::Processor::Architecture::ARM:
					return "ARM";
				case SystemInformation::Processor::Architecture::ARM_64:
					return "64-bit ARM";
				case SystemInformation::Processor::Architecture::MIPS:
					return "MIPS";
				case SystemInformation::Processor::Architecture::MIPS_64:
					return "64-bit MIPS";
				case SystemInformation::Processor::Architecture::PowerPC:
					return "PowerPC";
				case SystemInformation::Processor::Architecture::PowerPC_64:
					return "64-bit PowerPC";
				case SystemInformation::Processor::Architecture::SPARC:
					return "SPARC";
				case SystemInformation::Processor::Architecture::SPARC_64:
					return "64-bit SPARC";
				case SystemInformation::Processor::Architecture::Other:
				case SystemInformation::Processor::Architecture::Unkown:
				default:
					return "Unkonown";
			}
		} // Processor::Architecture


		//! Processor::PowerMode
		QString SystemInformation::Processor::getString(
								SystemInformation::Processor::PowerMode _mode)
		{
			switch ( _mode )
			{
				case SystemInformation::Processor::PowerMode::Preformance:
					return "Performance";
				case SystemInformation::Processor::PowerMode::Powersave:
					return "Powersave";
				case SystemInformation::Processor::PowerMode::Unkown:
				default:
					return "Unkown";
			}
		} // Processor::PowerMode


		//======================================================================
		// Storage
		//======================================================================

		//! getString ( Storage::Interface )
		QString SystemInformation::Storage::getString(
							SystemInformation::Storage::Interface _interface )
		{
			switch ( _interface )
			{
				case SystemInformation::Storage::Interface::HDC:
					return "HDC";
				case SystemInformation::Storage::Interface::ATA:
					return "IDE";
				case SystemInformation::Storage::Interface::SATA:
					return "SATA";
				case SystemInformation::Storage::Interface::SCSI:
					return "SCSI";
				case SystemInformation::Storage::Interface::USB:
					return "USB";
				case SystemInformation::Storage::Interface::_1394:
					return "1394";
				case SystemInformation::Storage::Interface::Unknown:
				default:
					return "Unknown";
			}
		} // getString( Storage::Interface )

		//! getString ( Storage::Type )
		QString SystemInformation::Storage::getString(
									SystemInformation::Storage::Type _type)
		{
			switch ( _type )
			{
				case SystemInformation::Storage::Type::ExternalDisk:
					return "External hard disk";
				case SystemInformation::Storage::Type::FixedDisk:
					return "Fixed hard disk";
				case SystemInformation::Storage::Type::FlashDisk:
					return "USB flash drive";
				case SystemInformation::Storage::Type::Floppy:
					return "Floppy disk";
				case SystemInformation::Storage::Type::Tape:
					return "Tape";
				case SystemInformation::Storage::Type::RemovableMedia:
					return "Removable media";
				case SystemInformation::Storage::Type::Unknown:
				default:
					return "Unkown";
			}
		} // getString( Storage::Type )

	} // Core
} // PCore


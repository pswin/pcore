//##############################################################################
//#	title:	System informatio fro AMD's processors
//#	c-date:	Apr-22-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "headers/core/arch/amd/sys_info/sys_info_amd.h"

#if PCORE_ARCH_FAMILY == PCORE_ARCH_FAMILY_X86 && \
			PCORE_OS == PCORE_OS_WINDOWS

#include <include/pcore/core/bit_operations.h>
#include <intrin.h>

//==============================================================================
// macros
//==============================================================================

#define _HELPER_CHECK_AND_ADD( __ar, __val, __pos, __name ) \
				if ( PCORE_BIT_CHECK( __val, __pos ) == true ) \
					{__ar.push_back( __name );}


//==============================================================================
// functions
//==============================================================================

//! get_amd_cpuid_info
AMDCPUIDInformation get_amd_cpuid_info( void )
{

	quint32 regs[4];
	AMDCPUIDInformation info;

	__cpuid( (int *)regs, (int)1 );



	//--------------------------------
	// Feature Identifiers
	//--------------------------------

	// brand id for older processors of Intel
	info.brand_id		= PCORE_BIT_READ( regs[1], 0, 8 );

	// signature details
	info.stepping		= (quint16)PCORE_BIT_READ( regs[0], 0, 4 );
	info.model			= (quint16)PCORE_BIT_READ( regs[0], 4, 4 );
	info.family			= (quint16)PCORE_BIT_READ( regs[0], 8, 4 );
	info.extended_model	= (quint16)PCORE_BIT_READ( regs[0], 16, 4 );
	info.extended_family= (quint16)PCORE_BIT_READ( regs[0], 20, 8 );

	// reading extensions
	// EDX
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 0, "fpu" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 1, "vme" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 2, "de" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 3, "pse" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 4, "tsc" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 5, "msr" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 6, "pae" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 7, "mce" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 8, "cx8" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 9, "apic" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 11, "sep" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 12, "mtrr" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 13, "pge" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 14, "mca" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 15, "cmov" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 16, "pat" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 17, "pse-36" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 18, "psn" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 19, "clfsh" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 21, "ds" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 22, "acpi" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 23, "mmx" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 24, "fxsr" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 25, "sse" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 26, "sse2" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 27, "ss" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 28, "htt" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 29, "tm" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 30, "ia64" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 31, "pbe" );

	// ECX
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 0, "sse3" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 1, "pclmulqdq" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 2, "dtes64" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 3, "monitor" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 4, "ds-cpl" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 5, "vmx" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 6, "smx" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 7, "est" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 8, "tm2" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 9, "ssse3" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 10, "cnxt-id" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 11, "sdbg" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 12, "fma" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 13, "cx16" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 14, "xtpr" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 15, "pdcm" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 17, "pcid" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 18, "dca" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 19, "sse4.1" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 20, "sse4.2" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 21, "x2apic" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 22, "movbe" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 23, "popcnt" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 24, "tsc-deadline" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 25, "aes" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 26, "xsave" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 27, "osxsave" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 28, "avx" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 29, "f16c" );
	//_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 30, "rdrnd" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 31, "hypervisor" );


	//--------------------------------
	// Extended Feature Identifiers
	//--------------------------------

	__cpuid( (int *)regs, 0x80000001 );

	info.brand_id_ex = PCORE_BIT_READ( regs[1], 0 , 16 );

	// ECX
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 0, "LahfSahf" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 1, "CmpLegacy" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 2, "SVM" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 3, "ExtApicSpace" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 4, "AltMovCr8" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 5, "ABM" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 6, "SSE4A" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 7, "MisAlignSse" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 8, "3DNowPrefetch" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 9, "OSVW" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 10, "IBS" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 11, "XOP" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 12, "SKINIT" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 13, "WDT" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 15, "LWP" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 16, "FMA4" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 19, "NodeId" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 21, "TBM" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[2], 22, "TopologyExtensions" );

	// EDX
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 11, "SysCallSysRet" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 20, "NX" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 22, "MmxExt" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 25, "FFXSR" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 26, "Page1GB" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 27, "RDTSCP" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 29, "LM" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 30, "3DNowExt" );
	_HELPER_CHECK_AND_ADD( info.extensions, regs[3], 31, "3DNow" );


	//--------------------------------
	// Cache and TLB
	//--------------------------------

	// L1
	__cpuid( (int *)regs, 0x80000005 );

	info.cache_l1_size_data = PCORE_BIT_READ( regs[2], 24, 8 ) * 1024;
	info.cache_l1_size_instruction = PCORE_BIT_READ( regs[3], 24, 8 ) * 1024;
	info.cache_l1_size = info.cache_l1_size_instruction + info.cache_l1_size_data;


	// L2. L3
	__cpuid( (int *)regs, 0x80000006 );

	info.cache_l2_size = PCORE_BIT_READ( regs[2], 16, 16 );
	info.cache_l3_size = PCORE_BIT_READ(regs[3], 18, 14 ) * 512;

	return info;

} // get_cpuid_info



#endif // PCORE_ARCH_FAMILY_X86 && PCORE_OS_WINDOWS


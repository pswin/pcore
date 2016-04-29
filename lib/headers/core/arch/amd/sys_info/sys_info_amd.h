//##############################################################################
//#	title:	System informatio fro AMD's processors
//#	c-date:	Apr-22-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_ARCH_AMD_SYS_INFO_H
#define _PCORE_ARCH_AMD_SYS_INFO_H

#include <QtGlobal>
#include <QStringList>
#include "include/pcore/pcore_def.h"

#if PCORE_ARCH_FAMILY == PCORE_ARCH_FAMILY_X86

//=====================================
// structs
//=====================================

struct AMDCPUIDInformation
{
	quint8		stepping;
	quint8		model;
	quint8		family;
	quint8		extended_model;
	quint8		extended_family;

	quint8		logical_processor_count;
	quint8		brand_id;
	quint16		brand_id_ex;
	
	quint32		cache_l1_size;
	quint32		cache_l1_size_data;
	quint32		cache_l1_size_instruction;
	quint32		cache_l2_size;
	quint32		cache_l3_size;

	

	QStringList	extensions;
};


//=====================================
// functions
//=====================================

/*!
 * \brief Executes CPUID and return CPUID's information about processor
 */
AMDCPUIDInformation get_amd_cpuid_info( void );


#endif // PCORE_ARCH_FAMILY_X86
#endif // _PCORE_ARCH_AMD_SYS_INFO_H


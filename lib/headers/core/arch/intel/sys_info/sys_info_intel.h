//##############################################################################
//#	title:	System informatio fro Intel's processors
//#	c-date:	Apr-21-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_ARCH_INTEL_SYS_INFO_H
#define _PCORE_ARCH_INTEL_SYS_INFO_H

#include <QtGlobal>
#include <QStringList>
#include "include/pcore/pcore_def.h"

#if PCORE_ARCH_FAMILY == PCORE_ARCH_FAMILY_X86

//=====================================
// structs
//=====================================

struct IntelCPUIDInformation
{
	quint16		stepping;
	quint16		model;
	quint16		family;
	quint16		processor_type;
	quint16		extended_model;
	quint16		extended_family;
	QString		serial;
	QString		signature;
	quint16		brand_id;
	QStringList	extensions;
};


//=====================================
// functions
//=====================================

/*!
 * \brief Retrieves micro-architecture name from signature of intel processors
 * \param _signature: signature of processor
 * \return Processor's micro-architecure name
 */
QString intel_get_arch_name( quint32 _signature );

/*!
 * \brief Executes CPUID and return CPUID's information about processor
 */
IntelCPUIDInformation get_intel_cpuid_info( void );


#endif // PCORE_ARCH_FAMILY_X86
#endif // INTEL_SYS_INFO_H

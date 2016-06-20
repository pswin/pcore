//#############################################################################
//#	title:	compile-time configurations
//#	c-date:	Jan-01-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//#############################################################################

#ifndef _PCORE_CONFIG_H
#define _PCORE_CONFIG_H

#include "def/const.h"


/*=====================================
	General
=====================================*/

/*	Setting file:
 *	All settings that is needed for initializing PCore are stroed in setting
 *	file. This macro defines the default setting file which is used for some
 *	arguments default value in functions such as Root::init.
 */
#define PCORE_CONFIG_DEFAULT_SETTING_FILE "setting.ini"



/* Typedefs:
 * PCore's classes are separated by using namespaces to pervent confilicts with
 * other libraries. Nevertheless, you might found it difficult to use namespaces
 * in your code for diffrent reasons. Therefore, a typedef of them in Qt-like
 * nameing convention are provided to facilitate coding and making you code
 * seems more legible. This feature is enabled by default, but if you do not
 * find it convenient, or you find confilicts in you code, you can easily
 * disable them by changing following macros's value to the PCORE_DISABLE.
 */
#define PCORE_CONFIG_USE_TYPEDEF PCORE_ENABLE


/* SIMD:
 * PCore uses SIMD instructions for enabling faster mathematical operations.
 * But, due to this instructions are highly depended on the architecture of CPU.
 * by default they are disabled. Nevertheless, If you were sure your destination
 * platform support SIMD (SSE for x86, NOVA fro ARM, etc.) you can easily enbale
 * this feature by changing following macro's value to PCORE_ENABLE.
 */
#define PCORE_CONFIG_SIMD	PCORE_DISABLE


/* Compiler Warnings
 *	Microsoft Visual Studio tends to produce some warnings during compiling
 *	progress which might not be harmful or essential. So, by disabling them you
 *	will have more clear compile output. Nevertheless, if you are intrested in
 *	them or you want check them, just change the value of this macro PCORE_ENABLE.
 */
#define PCORE_CONFIG_WARNINGS PCORE_DISABLE



/* Throw error
 * If you enable this macro must functoin in case of failture will throw an
 * error. Although PCore has a mechanism for controlling and reporting errors,
 * yet this system could help you to pass errors to the upper layers.
 */
#define PCORE_CONFIG_THROW_ERROR PCORE_DISABLE



/* Locale and language:
 * Default locale and language which is used by the PCore
 */

#define PCORE_CONFIG_DEFAULT_LANGUAGE	QLocale::English
#define PCORE_CONFIG_DEFAULT_COUNTRY	QLocale::UnitedStates


/*=====================================
	Logger
=====================================*/

/*
 *	In case of absence of setting file a default logger will be used. By default
 *	this logger is bond to Qt Application output but you can change it by
 *	modifying this macro.
 */
#define PCORE_DEFAULT_LOGGER PCore::Core::LoggerInterface::Type::QDebug

/*
 * Enabling or disabling diffrent loggers in debuging mode.
 */
#define PCORE_CONFIG_LOG_CRITICAL_DEBUG		PCORE_ENABLE
#define PCORE_CONFIG_LOG_ERROR_DEBUG		PCORE_ENABLE
#define PCORE_CONFIG_LOG_WARNING_DEBUG		PCORE_ENABLE
#define PCORE_CONFIG_LOG_INFO_DEBUG			PCORE_ENABLE
#define PCORE_CONFIG_LOG_TRACE_DEBUG		PCORE_DISABLE

/*
 * Enabling or disabling diffrent loggers in release mode.
 */
#define PCORE_CONFIG_LOG_CRITICAL_RELEASE	PCORE_ENABLE
#define PCORE_CONFIG_LOG_ERROR_RELEASE		PCORE_ENABLE
#define PCORE_CONFIG_LOG_WARNING_RELEASE	PCORE_ENABLE
#define PCORE_CONFIG_LOG_INFO_RELEASE		PCORE_ENABLE
#define PCORE_CONFIG_LOG_TRACE_RELEASE		PCORE_DISABLE

/*
 *	This configuration is for tracing methods execution in case of absence of
 *	debugger or whenever you find it more convenient. You should bare that in
 *	mind, the type of the Function Logger is Trace, therefore, by disabling
 *	trace logger it will not work.
 */
#define PCORE_CONFIG_LOG_TRACE_FUNCTION_START PCORE_DISABLE


/*
 *	This macros define network logger's default TCP-port and host address.
 */
#define PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_PORT	3306
#define PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_HOST	QHostAddress::LocalHost
#define PCORE_CONFIG_LOGGER_NETWORK_DEFAULT_WAIT_TIME 30000 // 30 sec


/*=====================================
	Date and time
=====================================*/

#define PCORE_CONFIG_DATE_PERSIAN_DEFAULT_FORMAT "yyyy/mm/dd"
#define PCORE_CONFIG_DATE_HIJRI_DEFAULT_FORMAT "yyyy/mm/dd"

#endif // _PCORE_CONFIG_H

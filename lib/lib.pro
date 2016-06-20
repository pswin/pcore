################################################################################
#                               PCore Library
#                            By Pouya Shahinfar
#                            pswinpo@gmail.com
################################################################################


#===============================================================================
# Internal libs
#===============================================================================

QT       += network xml
QT       -= gui


#===============================================================================
# Configs
#===============================================================================

CONFIG += C++11


#===============================================================================
# Target
#===============================================================================

TARGET = pcore
TEMPLATE = lib

DESTDIR =  $$PWD/../bin/


unix {
    target.path = /usr/lib
    INSTALLS += target
}


#===============================================================================
# Defines
#===============================================================================

DEFINES += PCORE_EXPORT


#===============================================================================
# Include path
#===============================================================================

INCLUDEPATH += ../


#===============================================================================
# Source/Header files
#===============================================================================

SOURCES += \
    source/core/globals.cpp \
    source/core/logger.cpp \
    source/root.cpp \
    source/core/logger/logger_file.cpp \
    source/core/logger/logger_qdebug.cpp \
    source/core/profiler.cpp \
    source/core/logger/logger_network.cpp \
    source/core/compressor.cpp \
    source/core/windows/win_wmi.cpp \
    source/core/system_info/sys_info_intel.cpp \
    source/core/system_info/sys_info_amd.cpp \
    source/core/system_info/sys_info_win.cpp \
    source/core/system_info/sys_info_linux.cpp \
    source/core/system_info/sys_info_global.cpp \
    source/core/linux/udev.cpp \
    source/globalization/persian_calendar.cpp \
    source/globalization/date_parser.cpp \
    source/globalization/locale.cpp \
    source/globalization/hijri_calendar.cpp \
    source/cryptography/rsa.cpp \
    source/cryptography/cryptography_engine.cpp \
    source/math/random.cpp \
    source/cryptography/aes.cpp \
    source/cryptography/des.cpp \
    source/core/hr.cpp

HEADERS +=\
    include/pcore/pcore.h \
    include/pcore/def/arch.h \
    include/pcore/def/compiler.h \
    include/pcore/def/const.h \
    include/pcore/def/def_gcc.h \
    include/pcore/def/def_msvc.h \
    include/pcore/def/limits.h \
    include/pcore/def/os.h \
    include/pcore/config.h \
    include/pcore/pcore_def.h \
    include/pcore/core/logger.h \
    include/pcore/globals.h \
    include/pcore/root.h \
    include/pcore/core/profiler.h \
    headers/core/logger/logger_network.h \
    headers/core/logger/logger_dummy.h \
    headers/core/logger/logger_file.h \
    headers/core/logger/logger_qdebug.h \
    include/pcore/core/compressor.h \
    include/pcore/core/exception.h \
    include/pcore/core/system_information.h \
    headers/core/windows/win_wmi.h \
    include/pcore/core/bit_operations.h \
    headers/core/arch/intel/sys_info/sys_info_intel.h \
    headers/core/arch/amd/sys_info/sys_info_amd.h \
    source/core/system_info/sys_info_global.h \
    headers/core/linux/udev.h \
    include/pcore/globalization/persian_calendar.h \
    include/pcore/globalization/date_parser.h \
    headers/globalization/info_structs.h \
    include/pcore/globalization/locale.h \
    include/pcore/globalization/hijri_calendar.h \
    include/pcore/cryptography/rsa.h \
    headers/cryptography/cryptography_engine.h \
    include/pcore/cryptography/aes.h \
    include/pcore/math/random.h \
    include/pcore/cryptography/des.h \
    include/pcore/core/hr.h



DISTFILES += \
    plan.txt


#===============================================================================
# Libs
#===============================================================================

#--------------------------------------
# zlib
#--------------------------------------

win32:contains( QMAKE_HOST.arch, x86_64 ) {
    LIBS += -L$$PWD/3rdparty/zlib/bin_x64 -lzdll
} else:win32 {
   LIBS += -L$$PWD/3rdparty/zlib/bin_x86 -lzdll
} else:unix {
   LIBS += -lz
}

win32: {
    INCLUDEPATH += $$PWD/3rdparty/zlib/include
    DEPENDPATH += $$PWD/3rdparty/zlib/include
}


#--------------------------------------
# openssl
#--------------------------------------


win32:contains( QMAKE_HOST.arch, x86_64 ) {
    LIBS += -L$$PWD/3rdparty/openssl/bin_x64 -llibeay32MD -lssleay32MD
} else:win32 {
   LIBS += -L$$PWD/3rdparty/openssl/bin_x86 -llibeay32MD -lssleay32MD
} else:unix {
  LIBS += -lssl -lcrypto
}

win32:contains( QMAKE_HOST.arch, x86_64 ) {
    INCLUDEPATH += $$PWD/3rdparty/openssl/include64
    DEPENDPATH += $$PWD/3rdparty/openssl/include64
} else:win32 {
    INCLUDEPATH += $$PWD/3rdparty/openssl/include
    DEPENDPATH += $$PWD/3rdparty/openssl/include
}


#--------------------------------------
# 7-Zip
#--------------------------------------



#--------------------------------------
# Windows COM
#--------------------------------------

win32: LIBS+= -lwbemuuid -lcomsupp


#--------------------------------------
# udev
#--------------------------------------

unix: {
    LIBS += -ludev
}

RESOURCES +=


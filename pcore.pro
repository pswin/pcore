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
# Target
#===============================================================================

TARGET = pcore
TEMPLATE = lib

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
    source/core/crypto.cpp \
    source/core/crypto/crypto_aes.cpp \
    source/core/hash/hash_city.cpp \
    source/core/hash/hash_crc32.cpp \
    source/core/hash/hash_md5.cpp \
    source/core/hash/hash_sha1.cpp \
    source/core/logger/logger_file.cpp \
    source/core/logger/logger_qdebug.cpp \
    source/core/hash.cpp \
    source/core/profiler.cpp \
    source/core/logger/logger_network.cpp \
    source/core/compressor.cpp

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
    include/pcore/core/crypto.h \
    headers/core/crypto/crypto_aes.h \
    headers/core/hash/hash_city.h \
    headers/core/hash/hash_crc32.h \
    headers/core/hash/hash_md5.h \
    headers/core/hash/hash_sha1.h \
    include/pcore/core/hash.h \
    include/pcore/core/profiler.h \
    headers/core/logger/logger_network.h \
    headers/core/logger/logger_dummy.h \
    headers/core/logger/logger_file.h \
    headers/core/logger/logger_qdebug.h \
    include/pcore/core/compressor.h \
    include/pcore/core/exception.h



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

INCLUDEPATH += $$PWD/3rdparty/zlib/include
DEPENDPATH += $$PWD/3rdparty/zlib/include

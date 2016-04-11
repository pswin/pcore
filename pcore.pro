#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T22:42:23
#
#-------------------------------------------------

QT       += network xml

QT       -= gui

TARGET = pcore
TEMPLATE = lib

DEFINES += PCORE_EXPORT

INCLUDEPATH += ../

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
    source/core/profiler.cpp

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
    headers/core/logger_dummy.h \
    headers/core/logger_file.h \
    headers/core/logger_qdebug.h \
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
    include/pcore/core/profiler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    plan.txt

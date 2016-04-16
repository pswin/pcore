QT          += core network
QT          -= gui
CONFIG      += console

TARGET       = test_logger
TEMPLATE     = app

include(../common.pri)


SOURCES   += \
    main.cpp

QT          += core network
QT          -= gui
CONFIG      += console

TARGET       = test_logger
TEMPLATE     = app
#CONFIG      += c++11

PRJDIR       = $$PWD/../..
#include($$PRJDIR/commondir.pri)

LIBS           += -L$$PRJDIR/bin/
INCLUDEPATH     +=  $$PRJDIR/lib/include/
DESTDIR         = $$PRJDIR/bin/


#HEADERS   +=

SOURCES   += \
    main.cpp


LIBS      += -lpcore

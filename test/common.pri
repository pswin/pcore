
PRJDIR		= $$PWD/..
LIBS		+= -L$$PRJDIR/bin/
INCLUDEPATH	+=  $$PRJDIR/lib/include/
DESTDIR		= $$PRJDIR/bin/

#CONFIG      += c++11

LIBS      += -lpcore
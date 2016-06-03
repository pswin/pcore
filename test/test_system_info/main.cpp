#include "mainwindow.h"
#include <QApplication>
#include <pcore/pcore.h>


int main(int argc, char *argv[])
{
	PCORE_INIT();

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	//! fills process table
	void fillProcessTable( void );

	//! fills video controller's table
	void fillVideoControllerTable( void );

	//! fills storages table
	void fillStorageTable( void );

	//! monitros
	void fillMonitors( void );

	//! sound cards
	void fillSoundCards( void );

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

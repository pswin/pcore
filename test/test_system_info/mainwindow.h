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
	void fillProcessTable();

	//! fills video controller's table
	void fillVideoControllerTable();


private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

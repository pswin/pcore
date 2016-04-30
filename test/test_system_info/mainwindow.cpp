#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pcore/pcore.h>
#include <QStringList>
#include <QDebug>


#define TABLE_SET_HEADER( __table, __index , __str ) \
		__table->setHorizontalHeaderItem( __index, \
		new QTableWidgetItem(QString(__str),QTableWidgetItem::Type) );

#define TABLE_SET_CELL_TEXT( __table, __row, __column, __str ) \
			__table->setItem( __row, __column, new QTableWidgetItem() );\
			__table->item( __row, __column )->setText( __str );

#define TABLE_INSERT_ROW( __table, __index, _property, __value )\
			row_index = __table->rowCount();\
			__table->insertRow( row_index );\
			TABLE_SET_CELL_TEXT( __table, row_index, 0, QString::number(__index) );\
			TABLE_SET_CELL_TEXT( __table, row_index, 1, _property );\
			TABLE_SET_CELL_TEXT( __table, row_index, 2, __value );

#define TABLE_INSERT_ROW_NUM(__table, __index, _property, __value) \
			TABLE_INSERT_ROW( __table, __index, _property, QString::number(__value) );


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	fillProcessTable();
	fillVideoControllerTable();

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::fillProcessTable()
{
	// setting up table widget
	ui->tbl_processor->setColumnCount( 3 );
	ui->tbl_processor->setHorizontalHeaderLabels(
						QStringList({"CPU","Property","Value"}) );
	ui->tbl_processor->setColumnWidth( 0, 30 );
	ui->tbl_processor->setColumnWidth( 1, 100 );
	ui->tbl_processor->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	auto process_list = PCore::core::SystemInformation::getProcesses();

	int row_index = 0;
	for ( auto it : process_list )
	{
		TABLE_INSERT_ROW( ui->tbl_processor, it.index, "Name", it.name );
		TABLE_INSERT_ROW( ui->tbl_processor, it.index, "Vendor", it.vendor );
		TABLE_INSERT_ROW( ui->tbl_processor, it.index, "Architecture", it.architecture );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Architecture ID", it.architecture_id );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Maximum clock", it.max_clock );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Logical cores", it.num_of_logical_cores );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Cores", it.num_of_cores );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Threads", it.num_of_threads);
		TABLE_INSERT_ROW( ui->tbl_processor, it.index, "Family", it.family );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "Family ID", it.family_id );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "L1 Cache Size", it.l1_cache_size );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "L2 Cache Size", it.l2_cache_size );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, it.index, "L3 Cache Size", it.l3_cache_size );
		TABLE_INSERT_ROW( ui->tbl_processor, it.index, "Extensions", it.extensions.join(L' '));
	}
}

void MainWindow::fillVideoControllerTable()
{
	// setting up table widget
	ui->tlb_video->setColumnCount( 3 );
	ui->tlb_video->setHorizontalHeaderLabels(
						QStringList({"GPU","Property","Value"}) );
	ui->tlb_video->setColumnWidth( 0, 30 );
	ui->tlb_video->setColumnWidth( 1, 150 );
	ui->tlb_video->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	auto video_list = PCore::core::SystemInformation::getVideoControllers();

	int row_index = 0;
	for ( auto it : video_list )
	{
		TABLE_INSERT_ROW( ui->tlb_video, it.index, "Name", it.name );
		TABLE_INSERT_ROW( ui->tlb_video, it.index, "Vendor", it.vendor );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Memory Size", it.memory_size );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Current Refresh rate", it.current_refresh_rate );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Max Refresh rate", it.max_refresh_rate );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Min Refresh rate", it.min_refresh_rate );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Current Reolution Ver", it.current_resolution_vertical );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Current Reolution Hor", it.current_resolution_horizantal );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Current Num of Colors", it.current_num_of_colors );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, it.index, "Current Bits per pixel", it.current_bits_per_pixel );
		TABLE_INSERT_ROW( ui->tlb_video, it.index, "Is running", it.is_running? "True": "False" );
	}
}

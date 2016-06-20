//##############################################################################
//#	title:	Main Window
//#	c-date:	May-15-2016
//#	author:	Pooya Shahinfar
//##############################################################################


//==============================================================================
// Includes
//==============================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pcore/pcore.h>
#include <QStringList>
#include <QDebug>


//==============================================================================
// Macros
//==============================================================================

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


#define TABLE_INSERT_ROW_BOOL(__table, __index, _property, __value) \
			TABLE_INSERT_ROW( __table, __index, _property, __value?"True":"False" );


#define TABLE_INSERT_ROW_HR(__table, __index, _property, __value) \
			TABLE_INSERT_ROW( __table, __index, _property, \
			PCore::core::HumanReadable::byteToString(__value) );

#define TABLE_INSERT_ROW_HR_FREQ(__table, __index, _property, __value) \
			TABLE_INSERT_ROW( __table, __index, _property, \
			PCore::core::HumanReadable::freqToString(__value) );


//==============================================================================
// MainWindow
//==============================================================================


//! constructor
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	// setup ui
	ui->setupUi(this);
	this->setWindowTitle( "System information" );

	// fill tables
	fillProcessTable();
	fillVideoControllerTable();
	fillStorageTable();
	fillMonitors();
	fillSoundCards();

}

//! destructor
MainWindow::~MainWindow()
{
	delete ui;
}


//=====================================
// fillProcessTable
//=====================================
void MainWindow::fillProcessTable( void )
{
	// setting up table widget
	ui->tbl_processor->setColumnCount( 3 );
	ui->tbl_processor->setHorizontalHeaderLabels(
						QStringList({"CPU","Property","Value"}) );
	ui->tbl_processor->setWordWrap( true );
	ui->tbl_processor->setColumnWidth( 0, 30 );
	ui->tbl_processor->setColumnWidth( 1, 100 );
	ui->tbl_processor->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	// getting list of processors
	auto processor_list = PCore::core::SystemInformation::getProcesses();

	// filling the table
	int row = 0;
	int row_index = 0;
	for ( auto it : processor_list )
	{
		row++;
		TABLE_INSERT_ROW( ui->tbl_processor, row, "Model", it.model );
		TABLE_INSERT_ROW( ui->tbl_processor, row, "Vendor", it.vendor );
		TABLE_INSERT_ROW( ui->tbl_processor, row, "Architecture", it.arch_name );
		TABLE_INSERT_ROW_HR_FREQ( ui->tbl_processor, row, "Max clock", it.cores[0].freq.max );
		TABLE_INSERT_ROW_HR_FREQ( ui->tbl_processor, row, "Min clock", it.cores[0].freq.min );
		TABLE_INSERT_ROW_HR_FREQ( ui->tbl_processor, row, "Current clock", it.cores[0].freq.current );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, row, "Total cores", it.total_cores );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, row, "Logical cores", it.logical_cores );
		TABLE_INSERT_ROW_NUM( ui->tbl_processor, row, "Threads", it.threads );
		TABLE_INSERT_ROW_HR( ui->tbl_processor, row, "Total cache", it.total_cache );

		for ( int i : it.cores[0].cache_levels.keys() )
		{
			TABLE_INSERT_ROW_HR( ui->tbl_processor, row_index,
								"Cache L" + QString::number(i) + " Size"
								 , it.cores[0].cache_levels[i].size );
		}

		for ( int i : it.cores.keys() )
		{
			TABLE_INSERT_ROW( ui->tbl_processor, row_index,
							"Powermode Core " + QString::number(i),
							PCore::core::SystemInformation::Processor::getString(
									it.cores[i].power_mode ) \
							);
		}

		TABLE_INSERT_ROW( ui->tbl_processor, row_index, "Extensions", it.extensions.join(L' '));
	}

	ui->tbl_processor->resizeColumnsToContents();
	ui->tbl_processor->resizeRowsToContents();
} // fillProcessTable


//=====================================
// fillVideoControllerTable
//=====================================
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

	// getting list of video controllers
	auto video_list = PCore::core::SystemInformation::getVideoControllers();

	// filling the table
	int row_index = 0;
	for ( auto it : video_list )
	{
		row_index++;
		TABLE_INSERT_ROW( ui->tlb_video, row_index, "Name", it.name );
		TABLE_INSERT_ROW( ui->tlb_video, row_index, "Model", it.model );
		TABLE_INSERT_ROW( ui->tlb_video, row_index, "Vendor", it.vendor );
		TABLE_INSERT_ROW_HR( ui->tlb_video, row_index, "Memory Size", it.memory_size );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Current Refresh rate", it.current_refresh_rate );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Max Refresh rate", it.max_refresh_rate );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Min Refresh rate", it.min_refresh_rate );
		TABLE_INSERT_ROW( ui->tlb_video, row_index, "Video Mode", it.video_mode_desc );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Current Reolution Ver", it.current_resolution_vertical );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Current Reolution Hor", it.current_resolution_horizantal );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Current Num of Colors", it.current_num_of_colors );
		TABLE_INSERT_ROW_NUM( ui->tlb_video, row_index, "Current Bits per pixel", it.current_bits_per_pixel );
		TABLE_INSERT_ROW( ui->tlb_video, row_index, "Is running", it.is_running? "True": "False" );
	}
} // fillVideoControllerTable


//=====================================
// fillStorageTable
//=====================================
void MainWindow::fillStorageTable()
{
	// setting up table widget
	ui->tbl_storages->setColumnCount( 3 );
	ui->tbl_storages->setHorizontalHeaderLabels(
						QStringList({"Index","Property","Value"}) );
	ui->tbl_storages->setColumnWidth( 0, 30 );
	ui->tbl_storages->setColumnWidth( 1, 150 );
	ui->tbl_storages->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	// getting list of storages
	auto storage_list = PCore::core::SystemInformation::getStorages();

	// filling the table
	int row_index = 0;
	int row = 0;
	for ( auto it : storage_list )
	{
		row++;
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Name", it.name );
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Model", it.model );
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Vendor", it.vendor );
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Serial", it.serial );
		TABLE_INSERT_ROW_HR( ui->tbl_storages, row, "Capacity", it.capacity );
		TABLE_INSERT_ROW_NUM( ui->tbl_storages, row, "Num of partitions", it.partitions.size() );
		TABLE_INSERT_ROW_NUM( ui->tbl_storages, row, "Bytes per sector", it.bytes_per_sector );
		TABLE_INSERT_ROW_BOOL( ui->tbl_storages, row, "Random access", it.is_random_access );
		TABLE_INSERT_ROW_BOOL( ui->tbl_storages, row, "Sequential access", it.is_sequential );
		TABLE_INSERT_ROW_BOOL( ui->tbl_storages, row, "Removeable", it.is_removeable );
		TABLE_INSERT_ROW_BOOL( ui->tbl_storages, row, "Writable", it.is_writable );
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Interface",
									PCore::core::SystemInformation::Storage::getString( it.interface_type ) );
		TABLE_INSERT_ROW( ui->tbl_storages, row, "Type", PCore::core::SystemInformation::Storage::getString(it.type) );
	}

} // fillStorageTable


//=====================================
// fillMoniroTable
//=====================================
void MainWindow::fillMonitors()
{
	// setting up table widget
	ui->tbl_monitors->setColumnCount( 3 );
	ui->tbl_monitors->setHorizontalHeaderLabels(
						QStringList({"Index","Property","Value"}) );
	ui->tbl_monitors->setColumnWidth( 0, 30 );
	ui->tbl_monitors->setColumnWidth( 1, 150 );
	ui->tbl_monitors->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	// get list of monitors
	auto monitor_list = PCore::core::SystemInformation::getMonitors();

	// filling the table
	int row_index = 0;
	for ( auto it : monitor_list )
	{
		TABLE_INSERT_ROW( ui->tbl_monitors, it.index, "Name", it.name );
		TABLE_INSERT_ROW( ui->tbl_monitors, it.index, "Model", it.model );
		TABLE_INSERT_ROW( ui->tbl_monitors, it.index, "Connected to", it.connected_to );
		TABLE_INSERT_ROW_NUM( ui->tbl_monitors, it.index, "Width", it.screen_width );
		TABLE_INSERT_ROW_NUM( ui->tbl_monitors, it.index, "Height", it.screen_height );
	}
} // fillMonitors


//=====================================
// fillSoundCards
//=====================================
void MainWindow::fillSoundCards()
{
	// setting up table widget
	ui->tlb_soundcards->setColumnCount( 3 );
	ui->tlb_soundcards->setHorizontalHeaderLabels(
						QStringList({"Index","Property","Value"}) );
	ui->tlb_soundcards->setColumnWidth( 0, 30 );
	ui->tlb_soundcards->setColumnWidth( 1, 150 );
	ui->tlb_soundcards->horizontalHeader()->setSectionResizeMode( 2,
														QHeaderView::Stretch );

	// getting list of sound adaptrers
	auto soundcard_list = PCore::core::SystemInformation::getSoundCards();

	// filling the table
	int row_index = 0;
	for ( auto it : soundcard_list )
	{
		TABLE_INSERT_ROW( ui->tlb_soundcards, it.index, "Name", it.name );
		TABLE_INSERT_ROW( ui->tlb_soundcards, it.index, "Model", it.model );
		TABLE_INSERT_ROW( ui->tlb_soundcards, it.index, "Vendor", it.vendor );
	}
} // fillSoundCards





#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDateTime>
#include "ImportNewData.h"
#include "ImportData.h"
#include "import.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
    //for the import button in the main window
	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
    //to connect the signal sent from the import window
	connect(&import_win, SIGNAL(dataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)),
						 this, SLOT(onDataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)));
}

MainWindow::~MainWindow() {
	delete ui;
}

/**
* @brief Set up variables to import
* Select the write algorithm to import according to the origin
* @param name The name of the stock
* @param firstDate The date of the first value to import.
* @param lastDate The date of the last value to import.
*/
void MainWindow::onDataEntered(const QString &name, const QDateTime &fDate ,const QDateTime &lDate, const QString &origin){
    MainWindow::stockName = name;
    qDebug() << name;
	MainWindow::firstDate = fDate;
	qDebug() << fDate.toString("yyyy-MM-dd");
	MainWindow::lastDate = lDate;
	qDebug() << lDate.toString("yyyy-MM-dd");
    MainWindow::origin = origin;
    qDebug() << origin;
    //if (source == "Yahoo")
        ImportNewData algo1 = ImportNewData();
    //else
    //    ImportData algo1 = ImportData();;
     algo1.import(MainWindow::stockName, fileName, MainWindow::origin, MainWindow::firstDate, MainWindow::lastDate);
}

/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
*/
void MainWindow::setImportCSV(){
    MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));
    qDebug() << MainWindow::fileName;
    import_win.show();
}

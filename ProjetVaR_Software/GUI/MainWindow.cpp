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
* @param startDate The date of the first value to import.
* @param endDate The date of the last value to import.
*/
void MainWindow::onDataEntered(const QString &name, const QDateTime &fDate ,const QDateTime &lDate, const QString &origin){
    MainWindow::stockName = name;
    MainWindow::startDate = fDate;
    MainWindow::endDate = lDate;
    MainWindow::origin = origin;
    ImportNewData algo = ImportNewData();
    //if (origin == "Yahoo")
    //    algo = ImportNewData();
    //else
    //    algo = ImportData();;
    algo.import(MainWindow::stockName, fileName, MainWindow::origin, MainWindow::startDate, MainWindow::endDate);
}

/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
*/
void MainWindow::setImportCSV(){
    MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("Texte CSV (*.csv; *.txt)") );
    import_win.show();
}

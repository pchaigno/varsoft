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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
	connect(&import_win, SIGNAL(dataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)),
						 this, SLOT(onDataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)));
	//connect(&import_win, SIGNAL(firstDateEntered(const QDateTime&)),
		//				 this, SLOT(onFirstDateEntered(const QDateTime&)));
	//connect(&import_win, SIGNAL(lastDateEntered(const QDateTime&)),
		//				 this, SLOT(onLastDateEntered(const QDateTime&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO Handle the import of differents source files ?

//Sauvegarder les données importées dans un Asset, l'envoyer dans le AssetFactory

//faire une super classe Importation, avec pour l'instant qu'une classe Yahoo héritant

void MainWindow::onDataEntered(const QString &text, const QDateTime &fDate ,const QDateTime &lDate, const QString &source){
	MainWindow::stockName = text;
	qDebug() << text;
	MainWindow::firstDate = fDate;
	qDebug() << fDate.toString("yyyy-MM-dd");
	MainWindow::lastDate = lDate;
	qDebug() << lDate.toString("yyyy-MM-dd");
	MainWindow::source = source;
    qDebug() << source;
	this->importCSV();
}

void MainWindow::importCSV()
{
		ImportNewData algo1 = ImportNewData();
        algo1.import(MainWindow::stockName, fileName, MainWindow::source, MainWindow::firstDate, MainWindow::lastDate);
}

void MainWindow::setImportCSV(){
	MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));
	import_win.show();
}

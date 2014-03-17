#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importCSV()));
    connect(ui->addPushButton, SIGNAL(clicked()), this, SLOT(newPortfolio()));
    portfolioModel = new PortfolioItemModel(this);
    ui->listView->setModel(portfolioModel);
}

MainWindow::~MainWindow() {
    delete ui;
}
/**
 * @brief MainWindow::newPortfolio open the New portfolio window
 */
void MainWindow::newPortfolio()
{
   NewPortfolioWizard * fen = new NewPortfolioWizard(this);
   connect(fen,SIGNAL(newPortfolioCreated(Portfolio*)),portfolioModel,SLOT(addPortfolio(Portfolio*)));
   fen->show();
}

//TODO Handle the import of differents source files ?
//TODO Add a screen to the select the range of data that sould be imported

//TODO Sauvegarder dans un nouveau fichier les données importées(sélectionnées)
//Sauvegarder les données importées dans un Asset, l'envoyer dans le AssetFactory
//Une seule source de fichier
//externaliser le traitement des fichiers
//faire une super classe Importation, avec pour l'instant qu'une classe Yahoo héritant
void MainWindow::importCSV() {
	QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));
	QString data;
	QFile importedCSV(fileName);
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();
	int z;

	if(importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split("\r\n");
		importedCSV.close();
	}
	qDebug() << "Données importées";

	//////CREATION DU FICHIER DES DONNEES IMPORTEES
	QFile file("Qt.txt");
	// On ouvre notre fichier en lecture seule et on vérifie l'ouverture
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}
	QTextStream flux(&file);
	flux.setCodec("UTF-8");




	//TODO : Add rows automaticaly according to the file imported
	// Try to import with a file with a size lower or equals to 9*9

	// x = 1 to avoid the first line with labels
	// rowOfData.size()-1 to avoid a blank line a the end of the file
	for(int x=1; x<rowOfData.size()-1; x++) {
		rowData = rowOfData.at(x).split(",");

		//TODO : find the index of the column we want to import
		/*
		for (int y = 0; y < rowData.size(); y++) {
		/*
			if((x==0) && (rowData[y] == "Adj Close")) {
				z = y;
				break;
			}

		*/
		qDebug() << rowData[6];
		//  ui->tableWidget->insertRow(indice);
		QTableWidgetItem* item = new QTableWidgetItem();
		// the index of the interesting column is always the same for yahoo files
		item->setText(rowData[6]);

		// Écriture des différentes lignes dans le fichier, mais il devient imcompatible avec l'importation
		flux << rowData[0] << "," << rowData[6] << "\n";
		ui->tableWidget->setItem(x-1,0,item);
    }
}


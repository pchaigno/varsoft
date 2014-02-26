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
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importCSV()));
	//connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(import()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO Handle the import of differents source files ?
//TODO Add a screen to the select the range of data that sould be imported

//TODO Sauvegarder dans un nouveau fichier les données importées(sélectionnées)
//Sauvegarder les données importées dans un Asset, l'envoyer dans le AssetFactory
//Une seule source de fichier
//externaliser le traitement des fichiers
//faire une super classe Importation, avec pour l'instant qu'une classe Yahoo héritant
void MainWindow::import(){
	Import* import_win = new Import(this);
	import_win->show();
}

void MainWindow::importCSV()
{
		QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));

		ImportNewData algo1 = ImportNewData();
		algo1.import(fileName);
		//
		//Importator importator = Importator(algo1);

		//importator.execute(fileName);
		/*

		QString data;
		QFile importedCSV(fileName);
		QStringList rowOfData;
		QStringList rowData;
		//QDateTime firstDate;
		//QDateTime lastDate;
		data.clear();
		rowOfData.clear();
		rowData.clear();

		if (importedCSV.open(QFile::ReadOnly))
			{
				data = importedCSV.readAll();
				rowOfData = data.split("\r\n");
				importedCSV.close();
			}
		qDebug() << "Données importées";

//////CREATION DU FICHIER DES DONNEES IMPORTEES
		//Faire des noms aléatoires et uniques
		QString name = "Qt.txt";
		QFile file(name);
		// On ouvre notre fichier en lecture seule et on vérifie l'ouverture
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;
		QTextStream flux(&file);
		flux.setCodec("UTF-8");

		//TODO : Add rows automaticaly according to the file imported
		// Try to import with a file with a size lower or equals to 9*9

		// x = 1 to avoid the first line with labels
		// rowOfData.size()-1 to avoid a blank line a the end of the file
		for (int x =1; x < rowOfData.size()-1; x++)
		{
           rowData = rowOfData.at(x).split(",");

			   qDebug() << rowData[6];
               //  ui->tableWidget->insertRow(indice);
               QTableWidgetItem* item = new QTableWidgetItem();
			   // the index of the interesting column is always the same for yahoo files
			   item->setText(rowData[6]);

			   // Écriture des différentes lignes dans le fichier, mais il devient imcompatible avec l'importation
			   flux << rowData[0] << "," << rowData[6] << "\n";
			   ui->tableWidget->setItem(x-1,0,item);
		}
		//obligé de faire des conversions pour passer de QString à QDateTime
		//firstDate = rowOfData.at(1).split(",")[0];
		//lastDate = rowOfData.at(rowOfData.size()-1).split(",")[0];

		//Asset a1 = Asset("name",name,firstDate,lastDate);
		*/
}


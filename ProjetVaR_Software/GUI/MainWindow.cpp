#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importCSV()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO Handle the import of differents source files ?
//TODO Detects the differents fields to select Adjust Close one
//TODO Add a screen to the select the range of data that sould be imported

//TODO Sauvegarder dans un nouveau fichier les données importées(sélectionnées)
//Sauvegarder les données importées dans un Asset, l'envoyer dans le AssetFactory
//Une seule source de fichier
//externaliser le traitement des fichiers
//faire une super classe Importation, avec pour l'instant qu'une classe Yahoo héritant

void MainWindow::importCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    int z;

       if (importedCSV.open(QFile::ReadOnly))
       {
           data = importedCSV.readAll();
           rowOfData = data.split("\r\n");
           importedCSV.close();
       }
       qDebug() << "Données importées";

       //TODO : Add rows automaticaly according to the file imported
       // Try to import with a file with a size lower or equals to 9*9

       for (int x =1; x < rowOfData.size(); x++)
       {
           rowData = rowOfData.at(x).split(",");

           //TODO : find the index of the column we want to import

           for (int y = 0; y < rowData.size(); y++)
           {
                /*
               if ((x==0) && (rowData[y] == "Adj Close")){
                   z = y;
                   break;
               }

           */
               qDebug() << rowData;
               //  ui->tableWidget->insertRow(indice);
               QTableWidgetItem* item = new QTableWidgetItem();
               item->setText(rowData[y]);
               ui->tableWidget->setItem(x-1,y,item);
           }
       }
}


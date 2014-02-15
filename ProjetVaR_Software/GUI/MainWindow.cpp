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
    model = new ModelVaR();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

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

       if (importedCSV.open(QFile::ReadOnly))
       {
           data = importedCSV.readAll();
           rowOfData = data.split("\n");
           importedCSV.close();
       }
       qDebug() << "Données importées";

       //TODO : Add rows automaticaly according to the file imported
       // Try to import with a file with a size lower or equals to 9*9
       for (int x =1; x < rowOfData.size(); x++)
       {
           rowData = rowOfData.at(x).split(",");
           for (int y = 0; y < rowData.size(); y++)
           {
               qDebug() << rowData;
               QTableWidgetItem* item = new QTableWidgetItem();
               item->setText(rowData[y]);
               ui->tableWidget->setItem(x-1,y,item);
           }
       }
}


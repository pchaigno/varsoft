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
    connect(ui->removePushButton, SIGNAL(clicked()), ui->listView, SLOT(removeSelectedPortfolio()));
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

void MainWindow::showPortfolio(Portfolio* portfolio){
    //portfolio->getComposition().size() => number of assets
    //we need to add two colums more for : the dates and the values of the porfolio
    QMap<Asset*, int> values = portfolio->getComposition();
    QVector< QVector<QString> > matrix(values.size()+2);
    QMap<QDateTime, double> dates = getValuesByDates(QDateTime& startDate, QDateTime& endDate);
    for (int i=0; i<values.size(); i++)
       //dates.size() => numberOfDates
       matrix[i].fill("", dates.size());

    //Dates and values are added
    int i =0;
    for(QMap<QDateTime, double>::const_iterator it=this->dates.begin(); it!=this->dates.end(); ++it) {
        matrix[0][i]=it.key().toString("YYYY-mm-dd");
        matrix[1][i]=QString(it.value());
        i++;
    }
    //each asset's value is added
    int j =2;
    for(QMap<Asset*, int>::const_iterator it=this->values.begin(); it!=this->values.end(); ++it) {
        //get all the values
        k =0;
        QVector<double> val = it.key()->getValues(it.key()->getFirstDate(),it.key()->getLastDate());
        for(int i=0; i < dates.size(); i++){
            // no verification upon the date's existance
            matrix[j][k] = val.at(k);
            k++;
        }
        j++;
    }
    //send the matrix for showing
    //
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


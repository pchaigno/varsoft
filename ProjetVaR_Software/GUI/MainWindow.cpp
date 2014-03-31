/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
#include "PortfolioViewModel.h"
#include "QDateTime"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), portfolioModel(new PortfolioItemModel(this))  {
    ui->setupUi(this);

    //for the import button in the main window
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
    //to connect the signal sent from the import window
    connect(&import_win, SIGNAL(dataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)),
                         this, SLOT(onDataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)));

    ui->listView->setModel(portfolioModel);
    connect(ui->removePushButton, SIGNAL(clicked()), ui->listView, SLOT(removeSelectedPortfolio()));

    connect(ui->listView,SIGNAL(portfolioSelected(Portfolio*)),this,SLOT(showPortfolio(Portfolio*)));
}

MainWindow::~MainWindow() {
	delete ui;
	delete portfolioModel;
}

/**
 * @brief MainWindow::newPortfolio open the PortfolioWizard
 */
void MainWindow::newPortfolio() {
   NewPortfolioWizard * fen = new NewPortfolioWizard(this);
   connect(fen,SIGNAL(newPortfolioCreated(Portfolio*)),portfolioModel,SLOT(addPortfolio(Portfolio*)));
   fen->setAttribute(Qt::WA_DeleteOnClose);
   fen->show();
}

void MainWindow::showPortfolio(Portfolio * portfolio){
/*
//void MainWindow::showPortfolio(Portfolio* portfolio){
    QString assetFolder = "../../CSV_examples/";

    // FIRST ASSET DEFINITION
    QDateTime startDate1(QDate(2014, 1, 1), QTime(0, 0, 0));
    QDateTime endDate1(QDate(2014, 1, 6), QTime(0, 0, 0));
    Asset* asset1 = new Asset("asset1", assetFolder+"asset1.txt", "YAHOO", startDate1, endDate1);

    // SECOND ASSET DEFINITION
    QDateTime startDate2(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate2(QDate(2014, 1, 7), QTime(0, 0, 0));
    Asset* asset2 = new Asset("asset2", assetFolder+"asset2.txt", "YAHOO", startDate2, endDate2);

    // THIRD ASSET DEFINITION
    QDateTime startDate3(QDate(2014, 1, 3), QTime(0, 0, 0));
    QDateTime endDate3(QDate(2014, 1, 8), QTime(0, 0, 0));
    Asset* asset3 = new Asset("asset3", assetFolder+"asset3.txt", "YAHOO", startDate3, endDate3);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
    assets.insert(asset1, 1);
    assets.insert(asset2, 2);
    assets.insert(asset3, 3);

    QVector<Report*> reports;
    Portfolio* portfolio = new Portfolio("Father", assets, reports);
*/
    // set the model
    PortfolioViewModel* pfm = new PortfolioViewModel(portfolio);
    ui->tableView->setModel(pfm);
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
    MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("Texte CSV (*.csv *.txt)") );
	import_win.show();
}

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
#include "ImportNewData.h"
#include "GetStartEndDates.h"
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDateTime>
#include "ImportNewData.h"
#include "ImportData.h"
#include "import.h"
#include "QDateTime"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), portfolioListModel(new PortfolioItemModel(this)) {
	ui->setupUi(this);

	//for the import button in the main window
	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
	ui->listView->setModel(portfolioListModel);
	connect(ui->removePushButton, SIGNAL(clicked()), ui->listView, SLOT(removeSelectedPortfolio()));

	connect(ui->listView,SIGNAL(portfolioSelected(Portfolio*)),this,SLOT(showPortfolio(Portfolio*)));
}

MainWindow::~MainWindow() {
	delete ui;
	delete portfolioListModel;
	foreach (Portfolio *portfolio, portfoliosModels.keys()) {
		delete portfoliosModels[portfolio];
	}
}

/**
 * @brief MainWindow::newPortfolio open the PortfolioWizard
 */
void MainWindow::newPortfolio() {
   NewPortfolioWizard * fen = new NewPortfolioWizard(this);
   connect(fen,SIGNAL(newPortfolioCreated(Portfolio*)),this,SLOT(addPortfolio(Portfolio*)));
   fen->setAttribute(Qt::WA_DeleteOnClose);
   fen->show();
}

/**
 * @brief Set the model of the specified portfolio to the TableView to display it.
 * @param portfolio
 */
void MainWindow::showPortfolio(Portfolio * portfolio){
	// set the model
	ui->tableView->setModel(portfoliosModels[portfolio]);
}

/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
* The last import path is saved when a new import is done
*/
void MainWindow::setImportCSV(){
    QString fileName;
    if (this->path != "")
		fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), this->path, ("CSV Texte (*.csv *.txt);;Tous les fichiers (*.*)") );
    else
		fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("CSV Texte (*.csv *.txt);;Tous les fichiers (*.*)") );
    if(fileName != "")
        this->path = fileName.left(fileName.lastIndexOf("/"));
    if (fileName != "")
    {
        //get startDate and endDate before calling the import function
        GetStartEndDates* gsed = new GetStartEndDates();
        gsed->retreiveDates(fileName);
        Import* importDialog = new Import(fileName,gsed->getStartDate(),gsed->getEndDate(),this);
        importDialog->show();
    }
}

/**
 * @brief Add the portfolio to the ListView,
 * create the TableModel, and add it to the Map "portfoliosModels"
 * @param portfolio
 */
void MainWindow::addPortfolio(Portfolio * portfolio) {
	portfoliosModels[portfolio] = new PortfolioViewModel(portfolio);
	portfolioListModel->addPortfolio(portfolio);
}

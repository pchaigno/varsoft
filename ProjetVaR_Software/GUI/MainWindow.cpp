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

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), portfolioModel(new PortfolioItemModel(this)) {
	ui->setupUi(this);
	//for the import button in the main window
	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
	//to connect the signal sent from the import window
	connect(&import_win, SIGNAL(dataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)),
						 this, SLOT(onDataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)));
	ui->listView->setModel(portfolioModel);
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

/**
* @brief Set up variables to import
* Select the write algorithm to import according to the origin
* @param name The name of the stock
* @param startDate The date of the first value to import.
* @param endDate The date of the last value to import.
*/
void MainWindow::onDataEntered(const QString &name, const QDateTime &lDate ,const QDateTime &fDate, const QString &origin){
	MainWindow::stockName = name;
    MainWindow::startDate = lDate;
    MainWindow::endDate = fDate;
	MainWindow::origin = origin;
	ImportNewData algo = ImportNewData();
	algo.import(MainWindow::stockName, fileName, MainWindow::origin, MainWindow::startDate, MainWindow::endDate);
}

/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
*/
void MainWindow::setImportCSV(){
    MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("Texte CSV (*.csv *.txt)") );
    //TODO: ne pas ouvrir la fenêtre de paramétrage de l'importation si elle a été annulée
    if (MainWindow::fileName != "")
        import_win.show();
}

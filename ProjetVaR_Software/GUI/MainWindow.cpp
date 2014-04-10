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

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), portfolioModel(new PortfolioItemModel(this)) {
	ui->setupUi(this);
	//for the import button in the main window
	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(setImportCSV()));
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
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
*/
void MainWindow::setImportCSV(){
    QString fileName;
    if (this->path != "")
		fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), this->path, ("CSV Texte (*.csv *.txt)") );
    else
		fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("CSV Texte (*.csv *.txt)") );
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

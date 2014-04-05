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
	//to connect the signal sent from the import window
	connect(&import_win, SIGNAL(dataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)),
						 this, SLOT(onDataEntered(const QString&, const QDateTime&, const QDateTime&, const QString&)));

    connect(ui->actionGenerate_Stats_Report,SIGNAL(triggered()),this,SLOT(generateStatsReport()));

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
 * @brief Generate the statistics report of the selected portfolio
 */
void MainWindow::generateStatsReport()
{
    // retrieve the current portfolio
    Portfolio * port = ui->listView->getCurrentPortfolio();
    // build the stats report
    Report * report = buildReport(new StatisticsReportFactory(port));
    port->getReports().append(report);
    // generate it in Docx format
    generateReport(new DocxGenerator(report));
}
/**
 * @brief Build a report with the specified factory
 * @param factory
 * @return The report
 */
Report *MainWindow::buildReport(ReportFactory * factory)
{
    return factory->buildReport();
}
/**
 * @brief Generate the report file with the specified ReportGenerator
 * @param gen
 */
void MainWindow::generateReport(ReportGenerator *gen)
{
    gen->start();
}

/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
*/
void MainWindow::setImportCSV(){
	MainWindow::fileName = QFileDialog::getOpenFileName(this, ("Ouvrir fichier"), "C:/", ("Texte CSV (*.csv *.txt)") );
	import_win.show();
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

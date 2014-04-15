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
    connect(ui->removePushButton, SIGNAL(clicked()), this, SLOT(removeSelectedPortfolio()));

	connect(ui->listView,SIGNAL(portfolioSelected(Portfolio*)),this,SLOT(showPortfolio(Portfolio*)));

	layoutReports = new FlowLayout;
	ui->reportScrollArea->setLayout(layoutReports);

}

MainWindow::~MainWindow() {
	delete ui;
	delete portfolioListModel;
	foreach (Portfolio *portfolio, portfoliosModels.keys()) {
		delete portfoliosModels[portfolio];
        delete portfolio;
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
	updateReportWidgets(portfolio);
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
 * @brief Display a message in the status bar when the generating of a report is done
 * and delete the reportGenerator which called this slot.
 */
void MainWindow::reportGenerationDone()
{
    this->statusBar()->showMessage("Generation done.",1500);
	ReportGenerator * obj = qobject_cast<ReportGenerator*>(sender());
	if (obj)
	{
		delete obj;
	}
}

/**
 * Clear all the ReportWidget in the Report tab
 * and fill it with the ReportWidget of the current portfolio
 */
void MainWindow::updateReportWidgets()
{
	updateReportWidgets(getCurrentPortfolio());
}
/**
 * @brief Same as updateReportWidgets() but with the ReportWidgets of the given portfolio
 * @param portfolio
 */
void MainWindow::updateReportWidgets(Portfolio *portfolio)
{
	//remove all the reportWidget in the layout
	clearLayout(layoutReports,false);

	//add the
	QList<ReportWidget*> listReportWidget = portfolioReportWidgets[portfolio];
	foreach(ReportWidget * reportWidget, listReportWidget)
	{
		layoutReports->addWidget(reportWidget);
	}
}
/**
 * @brief add a ReportWidget to the given portfolio
 * @param portfolio
 * @param reportWidget
 */
void MainWindow::addReportWidget(Portfolio *portfolio, ReportWidget *reportWidget)
{
	portfolioReportWidgets[portfolio].append(reportWidget);
	reportWidget->setParent(NULL);
	layoutReports->addWidget(reportWidget);
	if (ui->tabWidget->currentWidget()!=ui->tabReports)
		updateReportWidgets(portfolio);
	connect(reportWidget,SIGNAL(deleteRequest()),this,SLOT(deleteReportWidget()));
}
/**
 * @brief same as deleteReportWidget(ReportWidget* reportWidget) but
 * called by a signal emit by a ReportWidget. If the sender of the signal is not a ReportWidget*
 * the slot does nothing.
 */
void MainWindow::deleteReportWidget()
{
	ReportWidget * obj = qobject_cast<ReportWidget*>(sender());
	if (obj)
		deleteReportWidget(obj);
}
/**
 * @brief delete the given ReportWidget and update the list of ReportWidget
 * @param reportWidget
 */
void MainWindow::deleteReportWidget(ReportWidget* reportWidget)
{
	Report * report = reportWidget->getReport();
	portfolioReportWidgets[getCurrentPortfolio()].removeOne(reportWidget);
	getCurrentPortfolio()->removeReport(report);
	updateReportWidgets();
	delete reportWidget;
}
/**
 * @brief Remove all the ReportWidget of the current selected portfolio
 * @param portfolio
 */
void MainWindow::clearReportWidgets(Portfolio *portfolio)
{
	foreach(ReportWidget * reportWidget, portfolioReportWidgets[portfolio])
	{
		deleteReportWidget(reportWidget);
	}
	portfolioReportWidgets[portfolio].clear();
	portfolioReportWidgets.remove(portfolio);
}

void MainWindow::errorInGeneratedFiles()
{
	showError("Error in the generation, report has not been created.");
}

void MainWindow::showError(const QString & errorMsg)
{
	QMessageBox::critical(this,"Error",errorMsg);
}
/**
 * @brief Clear all the item in the given layout
 * @param layout
 * @param deleteWidgets
 */
void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
	while (QLayoutItem* item = layout->takeAt(0))
	{
		if (deleteWidgets)
		{
			if (QWidget* widget = item->widget())
				delete widget;
		}
		else
			item->widget()->setParent(NULL);
		if (QLayout* childLayout = item->layout())
			clearLayout(childLayout, deleteWidgets);
		delete item;
	}
}

void MainWindow::disableGenerationButton()
{
	ui->actionGenerate_Stats_Report->setEnabled(false);
}

void MainWindow::enableGenerationButton()
{
	ui->actionGenerate_Stats_Report->setEnabled(true);
}

/**
 * @brief Return the current portfolio (the one which is selected in the list of portfolio)
 * Throw a NoneSelectedPortfolioException if none portfolio has been selected.
 * @return the current portfolio
 */
Portfolio *MainWindow::getCurrentPortfolio()
{
    Portfolio * port = ui->listView->getCurrentPortfolio();
    if (port==NULL)
        throw NoneSelectedPortfolioException("None current portfolio.");
    return port;
}
/**
 * @brief Generates the statistics report of the selected portfolio and add it to the vector
 * of report of the selected portfolio.
 */
void MainWindow::generateStatsReport()
{
    try
	{
		// get the current portfolio
		Portfolio * port = this->getCurrentPortfolio();
        // build the stats report
		Report * report = buildReport(port, new StatisticsReportFactory(port));
        // generate it in Docx format
        generateReport(new DocxGenerator(report));
    }
	catch (ReportException & e)
	{
		showError(e.what());
	}
    catch (NoneSelectedPortfolioException& )
    {
		showError("None portfolio selected");
    }
}
/**
 * @brief Build a report with the specified factory and delete the factory if deleteAfter is false (by default).
 * The report is added to the porttoflio and to the portfolioReportWidgets for the given portfolio, and emit the signal newReportCreated().
 * @param portfolio the owner of the report
 * @param factory the factory which will be used to make the report
 * @param deleteAfter delete the ReportFactory if false (by default), otherwise the factory is not deleted
 * @return The report created by the given factory
 */
Report *MainWindow::buildReport(Portfolio *portfolio, ReportFactory * factory, bool deleteAfter)
{
	//build the report
    Report * report = factory->buildReport();
	// add it to the portfolio
	portfolio->addReport(report);
	//create the ReportWidget for the portfolio
	ReportWidget * reportWidget = ReportWidgetFactory::buildReportWidget(report);
	//add the ReportWidget to the layout
	addReportWidget(portfolio,reportWidget);

	if (!deleteAfter) // delete the factory if it's necessary
        delete factory;
    return report;
}
/**
 * @brief Generate the report file with the specified ReportGenerator.
 * This slot starts a thread for the generating.
 * Show a message in the display bar and connect the finish signal of the thread
 * to the slot reportGenerationDone of MainWindow.
 * @param gen
 */
void MainWindow::generateReport(ReportGenerator *gen)
{
	disableGenerationButton();
	this->statusBar()->showMessage("Generation of the report ...",0);

	//notify the report that the generation has been finished
	connect(gen,SIGNAL(finished()),gen->getReport(),SLOT(filesGenerationFinish()));
	connect(gen,SIGNAL(finished()),this,SLOT(enableGenerationButton()));
	//display an error in dialog
	connect(gen,SIGNAL(error(QString)),this,SLOT(showError(QString)));
	//display a message in the status bar if the generation was good
	connect(gen->getReport(),SIGNAL(filesOk()),this,SLOT(reportGenerationDone()));
	//display a error if not
	connect(gen->getReport(),SIGNAL(filesNotOk()),this,SLOT(errorInGeneratedFiles()));
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
	portfolioReportWidgets[portfolio] = QList<ReportWidget*>();
}

/**
 * @brief Remove the portfolio selected from the PortfolioListView and delete its PortfolioViewModel
 */
void MainWindow::removeSelectedPortfolio()
{
	try
	{
		//get the current portfolio
		Portfolio * portfolio = this->getCurrentPortfolio();
		//delete its ReportWidget
		clearReportWidgets(portfolio);
		//remove the portfolio in the ListView
		ui->listView->removeSelectedPortfolio();
		//delete the model
		delete portfoliosModels[portfolio];
		portfoliosModels.remove(portfolio);
	}
	catch (NoneSelectedPortfolioException& )
	{
		QMessageBox::critical(this,"Error","None portfolio selected");
	}
}

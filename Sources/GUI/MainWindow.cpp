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

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), portfolioListModel(new PortfolioListModel(this)) {
	ui->setupUi(this);
	this->path = "C:/";

	connect(ui->addPushButton,SIGNAL(clicked()),this,SLOT(openNewPortfolioDialog()));

	connect(ui->actionCreateAsset, SIGNAL(triggered()), this, SLOT(openImportDialog()));

	SessionFolderDialog* sessionFolderDialog = new SessionFolderDialog(this);
	connect(sessionFolderDialog,SIGNAL(sessionBuild(QList<Portfolio*>)),this,SLOT(buildSession(QList<Portfolio*>)));
	sessionFolderDialog->setAttribute(Qt::WA_DeleteOnClose);
	sessionFolderDialog->show();

	connect(ui->actionGenerate_Stats_Report,SIGNAL(triggered()),this,SLOT(generateStatsReport()));
	connect(ui->actionGenerate_Correlation_Report,SIGNAL(triggered()),this,SLOT(openCorrelationDialog()));

	ui->listView->setModel(portfolioListModel);
	connect(ui->removePushButton, SIGNAL(clicked()), ui->listView, SLOT(removeSelectedPortfolio()));
	connect(ui->actionSauvegarder, SIGNAL(triggered()), this, SLOT(save()));

	connect(ui->actionGenerate_VaR,SIGNAL(triggered()),this,SLOT(openVarDialog()));

	connect(ui->actionDocXGenerator_path,SIGNAL(triggered()),this,SLOT(openDocxGenPathDialog()));

	dataModel = new DataModel();
	ui->tableView->setModel(dataModel);
	portfolioViewMediator = new PortfolioViewMediator(ui->listView,dataModel,ui->reportScrollArea);

	connect(ui->actionDocXGenerator_path,SIGNAL(triggered()),this,SLOT(openDocxGenPathDialog()));

	connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importArchive()));
	connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportArchive()));

	//for QSettings
	QCoreApplication::setOrganizationName("INSA Rennes");
	QCoreApplication::setOrganizationDomain("insa-rennes.fr");
	QCoreApplication::setApplicationName("VaRSoft");

	readSettings();

	initResources();
}

MainWindow::~MainWindow() {
	delete ui;
	delete portfolioListModel;
}

/**
 * @brief Saves the settings of the window
 */
void MainWindow::writeSettings() {
	QSettings settings;

	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
}

/**
 * @brief Read and set the settings of the window
 */
void MainWindow::readSettings() {
	QSettings settings;

	settings.beginGroup("MainWindow");
	resize(settings.value("size", QSize(400, 400)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	settings.endGroup();
}

/**
 * @brief Creates the folders that the application needs to work
 */
void MainWindow::initResources() {
	createFolderIfDoesnotExist(RES_FOLDER);
	createFolderIfDoesnotExist(TEMPLATE_FOLDER);
	createFolderIfDoesnotExist(REPORT_FOLDER);
}

void MainWindow::createFolderIfDoesnotExist(QString folder) {
	QFile dir(folder);
	if (!dir.exists())
		QDir().mkpath(folder);
}

/**
 * @brief Event called when the application is closed.
 * It saves thr settings
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event) {
	Q_UNUSED(event);
	writeSettings();
}

/**
 * @brief Open the window to change the DocXGenerator path
 */
void MainWindow::openDocxGenPathDialog() {
	DocxGenPathDialog * fen = new DocxGenPathDialog(this);
	fen->setAttribute(Qt::WA_DeleteOnClose);
	fen->show();
}

/**
 * @brief MainWindow::newPortfolio open the PortfolioWizard
 */
void MainWindow::openNewPortfolioDialog() {
	NewPortfolioWizard * fen = new NewPortfolioWizard(this);
	connect(fen,SIGNAL(newPortfolioCreated(Portfolio*)),portfolioListModel,SLOT(addPortfolio(Portfolio*)));
	fen->setAttribute(Qt::WA_DeleteOnClose);
	fen->show();
}

void MainWindow::buildSession(QList<Portfolio *> listPorfolio)
{
	foreach(Portfolio * portfolio, listPorfolio)
	{
		portfolioListModel->addPortfolio(portfolio);
	}
}

/**
 * @brief Return the current portfolio (the one which is selected in the list of portfolio)
 * Throw a NoneSelectedPortfolioException if none portfolio has been selected.
 * @return the current portfolio
 */
Portfolio *MainWindow::getCurrentPortfolio() const {
	Portfolio * port = ui->listView->getCurrentPortfolio();
	if (port==NULL)
		throw NoneSelectedPortfolioException("None current portfolio.");
	return port;
}

/**
 * @brief Generates the statistics report of the selected portfolio and add it to the vector
 * of report of the selected portfolio.
 */
void MainWindow::generateStatsReport() {
	try {
		// get the current portfolio
		Portfolio * port = this->getCurrentPortfolio();

		GenerateReport(new StatisticsReportFactory(port),port);

	} catch (ReportAlreadyCreatedException & e) {

	} catch (ReportException & e) {
		showError(e.what());
	} catch (NoneSelectedPortfolioException& ) {
		showError("None portfolio selected");
	}
}

void MainWindow::openVarDialog()
{
	try
	{
		Portfolio * port = this->getCurrentPortfolio();
		VarDialog * fen = new VarDialog(port);
		fen->setAttribute(Qt::WA_DeleteOnClose);
		fen->show();
	} catch (NoneSelectedPortfolioException& ) {
		showError("None portfolio selected");
	}
}

/** Display the window to set up the correlation test
 * @brief MainWindow::showCorrelationWindow
 */
void MainWindow::openCorrelationDialog(){
	try {
		// get the current portfolio
		Portfolio * port = this->getCurrentPortfolio();

		CorrelationDialog* correlationDialog = new CorrelationDialog(port,this);
		correlationDialog->setAttribute(Qt::WA_DeleteOnClose);
		correlationDialog->show();

	} catch (ReportException & e) {
		showError(e.what());
	} catch (NoneSelectedPortfolioException& ) {
		showError("None portfolio selected");
	}
}


/**
* @brief Allows to browse the computer to select the file to import
* Shows the window to set up the import file
* The last import path is saved when a new import is done
*/
void MainWindow::openImportDialog() {
	Import* importDialog = new Import(this);
	importDialog->setAttribute(Qt::WA_DeleteOnClose);
	importDialog->show();
}

void MainWindow::showError(const QString &errorMsg)
{
	QMessageBox::critical(this,"Error",errorMsg);
}

/**
 * @brief Saves the portfolios to the last location used for the database.
 * Ask for the location if none was selected before in a new window.
 */
void MainWindow::save() {
	SessionSaver::getInstance()->saveSession(this->portfolioListModel->getPortfolios());
}

/**
 * @brief Opens a dialog to ask the user for the location of the archive to export.
 */
void MainWindow::exportArchive() {
	QString archivePath = QFileDialog::getSaveFileName(this, ("Export to an archive"), this->path, ("ZIP archive (*.zip)") );
	if(archivePath != "") {
		ExportManager exportManager = ExportManager(archivePath);
		exportManager.exportArchive(this->portfolioListModel->getPortfolios());
	}
}

void MainWindow::importArchive() {
	QString archivePath = QFileDialog::getOpenFileName(this, ("Import an archive"), this->path, ("ZIP archive (*.zip)") );
	if(archivePath != "") {
		ImportManager importManager = ImportManager(archivePath);
		importManager.importArchive();
		buildSession(importManager.getPortfolios());
	}
}

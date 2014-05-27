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
#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QComboBox>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <ReportFactory>
#include <Report>
#include <Import>
#include "windows/ImportDialog.h"
#include "windows/NewPortfolioWizard.h"
#include "portfolio/PortfolioListModel.h"
#include "report/ReportGenerator.h"
#include "portfolio/DataModel.h"
#include "exceptions/NoneSelectedPortfolioException.h"
#include "exceptions/ReportException.h"
#include <QMessageBox>
#include "FlowLayout.h"
#include "portfolio/report/ReportWidget.h"
#include "portfolio/report/ReportWidgetFactory.h"
#include "windows/DocxGenPathDialog.h"
#include "ui_MainWindow.h"
#include <QDate>
#include "portfolio/report/ReportView.h"
#include "portfolio/PortfolioViewMediator.h"
#include "CreateAsset.h"
#include "windows/CorrelationDialog.h"
#include "SessionSaver.h"
#include "windows/VarDialog.h"
#include "Constantes.h"
#include "ImportManager.h"
#include "ExportManager.h"
#include "SessionFolderDialog.h"

namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

	void writeSettings();
	void readSettings();
	void initResources();
	void createFolderIfDoesnotExist(QString folder);
	void closeEvent(QCloseEvent *event);

private slots:
	void generateStatsReport();

	void openVarDialog();
	void openCorrelationDialog();
	void openImportDialog();
	void openDocxGenPathDialog();
	void openNewPortfolioDialog();



	void showError(const QString& errorMsg);


	void save();

	void importArchive();
	void exportArchive();

private:
	Portfolio *getCurrentPortfolio() const;

	Ui::MainWindow *ui;
	QString stockName;
	QDate startDate;
	QDate endDate;
	QString fileName;
	QString origin;
	QString path;
	PortfolioListModel * portfolioListModel;
	DataModel * dataModel;
	PortfolioViewMediator* portfolioViewMediator;
	QString savePath;
};

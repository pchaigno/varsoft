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
#include "ImportDialog.h"
#include "NewPortfolioWizard.h"
#include "PortfolioItemModel.h"
#include "ReportFactory.h"
#include "ReportGenerator.h"
#include "StatisticsReportFactory.h"
#include "DocxGenerator.h"
#include "PortfolioViewModel.h"
#include "NoneSelectedPortfolioException.h"
#include "ReportException.h"
#include <QMessageBox>
#include "FlowLayout.h"
#include "ReportWidget.h"
#include "ReportWidgetFactory.h"
#include "DocxGenPathDialog.h"
#include "ui_MainWindow.h"
#include <QDate>
#include "ImportNewData.h"
#include "GetStartEndDates.h"
#include "SessionSaver.h"

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
	void docxGenPath();
	void newPortfolio();
	void showPortfolio(Portfolio* portfolio);
	void setImportCSV();
	void generateStatsReport();

	void save();
	void saveAs();
	void saveAs(QString savePath);

	void addPortfolio(Portfolio *);
	void removeSelectedPortfolio();
	void reportGenerationDone();
	void updateReportWidgets();
	void updateReportWidgets(Portfolio * portfolio);
	void addReportWidget(Portfolio * portfolio, ReportWidget * reportWidget);
	void deleteReportWidget();
	void deleteReportWidget(ReportWidget* reportWidget);
	void clearReportWidgets(Portfolio * portfolio);

	void showError(const QString&errorMsg);

	void disableGenerationButton();
	void enableGenerationButton();

	void deleteReportGenerator();

private:
	Portfolio *getCurrentPortfolio();
	Report* buildReport(Portfolio * portfolio, ReportFactory * factory, bool deleteAfter=false);
	void generateReport(ReportGenerator * gen);
	void clearLayout(QLayout* layout, bool deleteWidgets = true);
	ReportWidget *getReportWidgetFromReport(Report * report, Portfolio * portfolio=NULL);

	Ui::MainWindow *ui;
	QString stockName;
	QDate startDate;
	QDate endDate;
	QString fileName;
	QString origin;
	QString path;
	QString savePath;
	PortfolioItemModel * portfolioListModel;
	QHash<Portfolio*, PortfolioViewModel*> portfoliosModels;
	QHash<Portfolio*, QList<ReportWidget*> > portfolioReportWidgets;
	FlowLayout * layoutReports;
};

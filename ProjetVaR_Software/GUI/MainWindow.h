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
#include <QDateTime>
#include <QDialog>
#include <QComboBox>
#include "import.h"
#include <string>
#include "NewPortfolioWizard.h"
#include "PortfolioItemModel.h"
#include "ReportFactory.h"
#include "ReportGenerator.h"
#include "StatisticsReportFactory.h"
#include "DocxGenerator.h"
#include "PortfolioViewModel.h"
#include "NoneSelectedPortfolioException.h"
#include <QMessageBox>
#include "FlowLayout.h"
#include "ReportWidget.h"
#include <QDebug>
#include "ReportWidgetFactory.h"

namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

private slots:
	void newPortfolio();
	void showPortfolio(Portfolio* portfolio);
	void setImportCSV();
    void generateStatsReport();

	void addPortfolio(Portfolio *);
    void removeSelectedPortfolio();

	void onDataEntered(const QString &text, const QDateTime &fDate, const QDateTime &lDate, const QString &source);
    void reportGenerationDone();
	void updateReportWidgets();
	void updateReportWidgets(Portfolio * portfolio);
	void addReportWidget(Portfolio * portfolio, ReportWidget * reportWidget);
	void deleteReportWidget();
	void deleteReportWidget(ReportWidget* reportWidget);
	void clearReportWidgets(Portfolio * portfolio);


	void disableGenerationButton();
	void enableGenerationButton();

private:
    Portfolio *getCurrentPortfolio();
	Report* buildReport(Portfolio * portfolio, ReportFactory * factory, bool deleteAfter=false);
    void generateReport(ReportGenerator * gen);
	void clearLayout(QLayout* layout, bool deleteWidgets = true);

	Ui::MainWindow *ui;
	Import import_win;
	QString stockName;
	QDateTime startDate;
	QDateTime endDate;
	QString fileName;
	QString origin;
	PortfolioItemModel * portfolioListModel;
	QHash<Portfolio*, PortfolioViewModel*> portfoliosModels;
	QHash<Portfolio*, QList<ReportWidget*> > portfolioReportWidgets;
	FlowLayout * layoutReports;
};

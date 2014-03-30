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
    void showPortfolio();
    //void showPortfolio(Portfolio* portfolio);
	void setImportCSV();

	void onDataEntered(const QString &text, const QDateTime &fDate ,const QDateTime &lDate, const QString &source);

private:
	Ui::MainWindow *ui;
	Import import_win;
	QString stockName;
	QDateTime startDate;
	QDateTime endDate;
	QString fileName;
	QString origin;
	PortfolioItemModel * portfolioModel;
};

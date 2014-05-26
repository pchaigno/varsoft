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

#include "ui_correlation.h"
#include "Portfolio.h"
#include "RInterface.h"
#include "CorrelationResults.h"
#include "CorrelationResultsDialog.h"
#include <QDate>
#include <QDialog>
#include <QException>

namespace Ui {
	class Correlation;
}
class Correlation : public QDialog
{
	Q_OBJECT
public:
	Correlation(Portfolio *portfolio, QWidget *parent = 0);
	~Correlation();
private:
	Ui::Correlation *ui;
	QString fileName;
	Portfolio *portfolio;
	QList<CorrelationResults> *results;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

public slots:
	void quit();
};


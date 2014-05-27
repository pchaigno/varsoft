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

#include "ui_correlationRes.h"
#include "CorrelationResultsDialog.h"
#include "CorrelationResults.h"
#include "CorrelationDialog.h"
#include "MainWindow.h"
#include "Constantes.h"
#include "reportFactory/CorrelationReportFactory.h"
#include <QDialog>
#include <QException>

namespace Ui {
	class CorrelationResultsDialog;
}
class CorrelationResultsDialog : public QDialog
{
	Q_OBJECT
public:
	explicit CorrelationResultsDialog(Portfolio *port,QList<CorrelationResults> *results, QString testType, QPair<double,double> res, int lag, QString date, int period, QWidget *parent = 0);
	~CorrelationResultsDialog();
private:
	Ui::CorrelationResultsDialog *ui;
	QList<CorrelationResults> *results;
	QPair<double, double> pair;
	QString type;
	Portfolio *portfolio;
	QString date;
	int timeLag;
	int period;
private slots:
	void on_generate_clicked();
	void on_save_clicked();
	void on_quit_clicked();
	void on_testAgain_clicked();

};


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

#include "VarDialog.h"
#include "ui_VarDialog.h"

VarDialog::VarDialog(Portfolio *portfolio, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::VarDialog)
{
	ui->setupUi(this);
	this->portfolio=portfolio;
	connect(ui->generate,SIGNAL(clicked()),this,SLOT(accept()));
	connect(ui->annuler,SIGNAL(clicked()),this,SLOT(reject()));

	initDates();
}

VarDialog::~VarDialog()
{
	delete ui;
}

void VarDialog::accept()
{
	int currentMethod = ui->tabWidget->currentIndex();
	VaRAlgorithm * algo;
	QDate date;
	GarchModel *model=NULL;
	try
	{
		switch(currentMethod)
		{
		case HISTORICAL:
			date = ui->date_historical->date();
			algo = new VaRHistorical(*portfolio,ui->risk_historical->value(),ui->timeHorizon_historical->value(),ui->period_historical->value());
			break;
		case RISKMETRICS:
			date = ui->date_riskmetrics->date();
			algo = new VaRRiskmetrics(*portfolio,ui->risk_riskmetrics->value(),ui->timeHorizon_riskmetrics->value(),ui->period__riskmetrics->value());
			break;
		case GARCHMETHOD:
			date = ui->date_garch->date();
			GarchModel modelR = RInterface::computeGarchModel(*portfolio, qMakePair(ui->startdate_garch->date(),ui->enddate_garch->date()));
			model = &modelR;
			algo = new VaRGarch(*portfolio,ui->risk_garch->value(),ui->timeHorizon_garch->value(),modelR, ui->scenario_garch->value(),ui->iteration_garch->value());
			break;
		}
		double var = algo->execute(date);
		if (QMessageBox::question(this,"Value-at-risk","Value-at-risk :"+QString::number(var)+"\n Do you want to generate the report ?")==QMessageBox::Yes)
		{
			GenerateReport(new VaRReportFactory(portfolio,var,algo,date));
			if (currentMethod==GARCHMETHOD)
			{
				GenerateReport(new GarchReportFactory(portfolio,*model));
			}
		}
		this->QDialog::accept();
	}
	catch(std::exception & e)
	{
		QMessageBox::warning(this,"Error",e.what());
	}
}

void VarDialog::initDates()
{
	QDate date = portfolio->retrieveEndDate();
	ui->date_garch->setDate(date);
	ui->date_historical->setDate(date);
	ui->date_riskmetrics->setDate(date);

	QDate date2 = portfolio->retrieveStartDate();

	ui->startdate_garch->setDate(date2);
	ui->enddate_garch->setDate(date);
}

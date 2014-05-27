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
#include "VaRReportFactory.h"

/**
 * @brief Constructor
 */
VaRReportFactory::VaRReportFactory(Portfolio *portfolio, double var, VaRAlgorithm * varAlgo, QDate date): ReportFactory() {
	this->portfolio=portfolio;
	this->var=var;
	this->varAlgo=varAlgo;
	this->date=date;
}

Report *VaRReportFactory::createReport() {
	QString file = this->getReportDir()+QString("VaRReport");
	QDate startDate = portfolio->retrieveStartDate();
	QDate endDate = portfolio->retrieveEndDate();
	file += "_"+portfolio->getName()+"_"+startDate.toString("dd-MM-yy")+"_"+endDate.toString("dd-MM-yy")+"_"+varAlgo->getNameMethod();
	return new VaRReport(file);
}

ReportDataJson *VaRReportFactory::createJson() {

	ReportDataJson* data = new ReportDataJson();
	data->addText("portfolioName",portfolio->getName());
	data->addText("portfolioEndDateValue",portfolio->retrieveValuesByDate().take(portfolio->retrieveEndDate()));
	data->addText("portfolioEndDate",portfolio->retrieveEndDate().toString("dd/MM/yyyy"));

	data->addText("var",var);
	data->addText("risk",varAlgo->getRisk());
	data->addText("timeHorizon", varAlgo->getTimeHorizon());

	data->addText("date",date.toString("dd/MM/yyyy"));

	varAlgo->setParamJson(data);

	data->addText("method",varAlgo->getNameMethod());

	return data;

}

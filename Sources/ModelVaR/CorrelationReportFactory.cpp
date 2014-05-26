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
#include "CorrelationReportFactory.h"

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
CorrelationReportFactory::CorrelationReportFactory(Portfolio *port, QList<CorrelationResults> *results):
	ReportFactory() {
	this->portfolio = port;
	this->results = results;
}

Report *CorrelationReportFactory::createReport() {
	QString file = this->getReportDir()+QString("correlationReport");
	QDate startDate = portfolio->retrieveStartDate();
	QDate endDate = portfolio->retrieveEndDate();
	file += "_"+portfolio->getName()+"_"+startDate.toString("dd-MM-yy")+"_"+endDate.toString("dd-MM-yy");
	return new CorrelationReport(file);
}

ReportDataJson *CorrelationReportFactory::createJson() {

	ReportDataJson* data = new ReportDataJson();
	data->addText("portefeuilleName",portfolio->getName());
	data->addText("dateDeb",portfolio->retrieveStartDate().toString("dd/MM/yyyy"));
	QDate startDate = portfolio->retrieveStartDate();
	QDate endDate = portfolio->retrieveEndDate();
	data->addText("dateFin",endDate.toString("dd/MM/yyyy"));
	data->addText("date",startDate.toString("dd/MM/yyyy"));
	QMap<QDate, double> valuesPortfolio = portfolio->retrieveValuesByDate();

	data->addText("val",QString::number(valuesPortfolio[endDate]));

	QList<QMap<QString,QString> > listResults;
	for(int i =0; i < results->size(); i++) {
			QMap<QString,QString> map;
			map["Type"]=results->at(i).getType();
			map["Qte"]=results->at(i).getDate();
			map["Unit"]=QString::number(results->at(i).getTimeLag());
			map["Total"]=QString::number(results->at(i).getPeriod());
			map["Pvalue"]=QString::number(results->at(i).getPValue());
			map["Statvalue"]=QString::number(results->at(i).getStatValue());
			listResults.append(map);
	}

	data->addList("asset",listResults);
	return data;

}

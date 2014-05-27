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
#include "GarchReportFactory.h"

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
GarchReportFactory::GarchReportFactory(Portfolio *portfolio, GarchModel &garch): ReportFactory(), garchModel(garch) {
	this->portfolio=portfolio;
}

Report *GarchReportFactory::createReport() {
	QString file = this->getReportDir()+QString("garModelReport");
	QDate startDate = portfolio->retrieveStartDate();
	QDate endDate = portfolio->retrieveEndDate();
	file += "_"+portfolio->getName()+"_"+startDate.toString("dd-MM-yy")+"_"+endDate.toString("dd-MM-yy");
	return new GarchReport(file);
}

ReportDataJson *GarchReportFactory::createJson() {

	ReportDataJson* data = new ReportDataJson();
	data->addText("portfolioName",portfolio->getName());
	data->addText("startDate",portfolio->retrieveStartDate().toString("dd/MM/yyyy"));
	data->addText("endDate",portfolio->retrieveEndDate().toString("dd/MM/yyyy"));


	data->addText("omega",garchModel.getOmega());
	data->addText("alpha",garchModel.getAlpha());
	data->addText("beta",garchModel.getBeta());
	data->addText("nbOfResiduals",garchModel.getResiduals().count());

	return data;
}

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

#include "ReportCreatorSingleton.h"
ReportCreatorSingleton *ReportCreatorSingleton::instance = NULL;

ReportCreatorSingleton::ReportCreatorSingleton()
{
}


void ReportCreatorSingleton::generate(ReportFactory *factory)
{
	Report * report;
	try
	{
		//build the report
		report = factory->buildReport();
	}
	catch (ReportAlreadyCreatedException & e)
	{
		int button = QMessageBox::information(NULL,"Report already created","This report has already been created.\nDo you want to regenerate it ?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
		if (button==QMessageBox::Yes)
		{
			factory->getPortfolio()->removeReport(*(e.getReport()));
			report = factory->buildReport();
		}
		else
		{
			throw e;
		}
	}

	factory->getPortfolio()->addReport(report);

	QSettings settings;
	DocxGenerator * generator = new DocxGenerator(report,settings.value("DocXGenPath","Resources/DocxGenerator/DocXGenerator.jar").toString());
	connect(generator,SIGNAL(finished()),this,SLOT(deleteGenerator()));
	connect(generator,SIGNAL(error(QString)),this,SLOT(showError(QString)));
	generator->start();
}

void ReportCreatorSingleton::deleteGenerator()
{
	ReportGenerator* gen = qobject_cast<ReportGenerator*>(sender());
	if (gen)
		delete gen;
}

void ReportCreatorSingleton::showError(const QString& errorMsg)
{
	QMessageBox::critical(NULL,"Error",errorMsg);
}

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
#include "ReportFactory.h"

/**
 * @brief ReportFactory::ReportFactory
 */
ReportFactory::ReportFactory(Portfolio *portfolio) {
	this->portfolio=portfolio;
}

/**
 * @brief Create the appropriate report and create its Json before returning it.
 * @return the report which just generated
 */
Report *ReportFactory::buildReport() {
	Report * report = createReport();
	if (report->filesAvailable())
		throw ReportAlreadyCreatedException(report,"Report files are available on the disk, maybe this report has already been created before.");
	report->setDataJson(createJson());
	return report;
}

Portfolio *ReportFactory::getPortfolio() const
{
	return portfolio;
}

/**
 * @brief Get the path of the directory where the reports are placed.
 * Create the directory if it does not exist.
 * @return
 */
QString ReportFactory::getReportDir() const {
	QString resourcesFolder = SessionSaver::getSessionFolder()+QDir::separator()+QString("Resources");
	QString path = resourcesFolder + QDir::separator() + QString("Reports");

	if (!QDir(path).exists()) {
		if (!QDir(resourcesFolder).mkpath("Reports"))
			throw ReportException("Error when creating the Report directory.");
	}

	return QString("Resources/Reports/");
}

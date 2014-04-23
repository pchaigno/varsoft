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
#include "StatisticsReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
StatisticsReport::StatisticsReport() {

}

StatisticsReport::StatisticsReport(QString file) : Report(file)
{

}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 */
StatisticsReport::StatisticsReport(int id,  QString file): Report(id,file) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
    return STATISTICS;
}
/**
 * @brief StatisticsReport::getTemplateFile
 * Getter of the templateFile path
 * @return a QString of the template path
 */
QString StatisticsReport::getTemplateFile() const
{
	return QString("../Resources/ReportTemplate/statisticTemplate.docx");
}

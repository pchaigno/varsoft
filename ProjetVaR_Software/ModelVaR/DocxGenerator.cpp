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
#include "DocxGenerator.h"

/**
 * @brief Constructor
 * @param location The path to the DOCX file to generate.
 * @param templateFile The template file of the report
 * @param data the json data
 */
DocxGenerator::DocxGenerator()
{

}

DocxGenerator::DocxGenerator(Report *report) {
    this->report=report;
}

/**
 * @brief Generates the DOCX file
 */
void DocxGenerator::generate() {
    QProcess docx;
    qDebug() << "avant" << QFile::exists(report->getTemplateFile()) << QFile::exists("../DocxGenerator/DocxGenerator.jar");
    docx.start("java", QStringList() << "-jar" << "../DocxGenerator/DocxGenerator.jar" << report->getTemplateFile() << report->getDOCXFile());
    docx.waitForStarted();

    QString data = report->getDataJson().toString();
    qint64 i = docx.write(data.toLatin1(),data.length());
    qDebug() << i;
    docx.closeWriteChannel();

    docx.waitForFinished();
    qDebug() << "appres" << QFile::exists(report->getTemplateFile()) << QFile::exists(report->getDOCXFile()) << report->getDOCXFile();
}

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
 * @param docxPath
 * @param pdfPath
 */
ReportFactory::ReportFactory(QString docxFile, QString pdfFile):
	docxGenerator(DocxGenerator(docxFile)) {
	this->docxFile = docxFile;
	this->pdfFile = pdfFile;
}

/**
 * @brief Generates the report.
 * @return The report.
 */
Report ReportFactory::generateReport() {
	this->docxGenerator = this->generateDOCX();
	this->generatePDF();
	return Report(this->docxFile, this->pdfFile);
}

/**
 * @brief Generates the PDF.
 * Converts the DOCX file to a PDF.
 */
void ReportFactory::generatePDF() {
	this->docxGenerator.convertToPDF();
}

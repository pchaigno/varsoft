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
#include "Report.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
Report::Report() {

}

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(QString docxFile, QString pdfFile) {
	this->init(-1, docxFile, pdfFile);
}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(int id, QString docxFile, QString pdfFile) {
	this->init(id, docxFile, pdfFile);
}

/**
 * @brief Method called by the constructor to initiate the values.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
void Report::init(int id, QString docxFile, QString pdfFile) {
	this->id = id;
	this->docxFile = docxFile;
	this->pdfFile = pdfFile;
}

/**
 * @brief Accessor to id.
 * @return The id of the report in the database.
 */
int Report::getId() const {
	return this->id;
}

/**
 * @brief Updates the report's id.
 * @param id The id.
 * @throw IdAlreadyAttributedException If an id was already attributed.
 */
void Report::setId(int id) {
	if(this->id != -1) {
		// TODO Improve error message.
		throw IdAlreadyAttributedException("An id has already been attributed to this report.");
	}
	this->id = id;
}

/**
 * @brief Accessor to the DOCX file.
 * @return The location of the DOCX file on the disk.
 */
QString Report::getDOCXFile() const {
	return this->docxFile;
}

/**
 * @brief Accessor to the PDF file.
 * @return The location of the PDF file on the disk.
 */
QString Report::getPDFFile() const {
	return this->pdfFile;
}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType Report::getType() const {
	return NONE;
}

/**
 * @brief Checks if two reports are equal.
 * @param report The second report.
 * @return True if the two reports are equal.
 */
bool Report::operator==(const Report& report) const {
	if(this->id == -1) {
		return this->docxFile==report.docxFile && this->pdfFile==report.pdfFile;
	}
	return this->id == report.id;
}

/**
 * @brief Deserializes the report from a JSON document.
 * @param json The JSON document.
 */
void Report::fromJSON(const QJsonObject &json) {
	this->id = json["id"].toInt();
	this->docxFile = json["docxFile"].toString();
	this->pdfFile = json["pdfFile"].toString();
}

/**
 * @brief Serializes the report into a JSON document.
 * @param json The JSON document.
 */
void Report::toJSON(QJsonObject &json) const {
	json["id"] = this->id;
	json["docxFile"] = this->docxFile;
	json["pdfFile"] = this->pdfFile;
}

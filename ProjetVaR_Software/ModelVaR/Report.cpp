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
Report::Report(QString file) {
    this->init(-1, file);
}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(int id, QString file) {
    this->init(id, file);
}

Report::~Report()
{
}

/**
 * @brief Method called by the constructor to initiate the values.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
void Report::init(int id, QString file) {
    this->id = id;
    this->file = file;
    dataJson=NULL;
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
 * @brief Accessor to the file without the extension
 * @return
 */
QString Report::getFile() const
{
    return this->file;
}
/**
 * @brief Accessor of the Json data of the report
 * @return
 */
ReportDataJson *Report::getDataJson() const
{
    return dataJson;
}
/**
 * @brief Setter of the Json data of the report
 * @param data the new json data
 */
void Report::setDataJson(ReportDataJson* data)
{
    dataJson=data;
}

/**
 * @brief Checks if two reports are equal.
 * @param report The second report.
 * @return True if the two reports are equal.
 */
bool Report::operator==(const Report& report) const {
	if(this->id == -1) {
		return this->file==report.file;
	}
	return this->id == report.id;
}

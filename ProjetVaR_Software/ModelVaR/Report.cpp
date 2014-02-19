#include "Report.h"

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(string docxFile, string pdfFile) {
	this->init(-1, docxFile, pdfFile);
}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(int id, string docxFile, string pdfFile) {
	this->init(id, docxFile, pdfFile);
}

/**
 * @brief Method called by the constructor to initiate the values.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
void Report::init(int id, string docxFile, string pdfFile) {
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
	if(this->id == -1) {
		throw IdAlreadyAttributedException("An id has already been attributed to this report.");
	}
	this->id = id;
}

/**
 * @brief Accessor to the DOCX file.
 * @return The location of the DOCX file on the disk.
 */
string Report::getDOCXFile() const {
	return this->docxFile;
}

/**
 * @brief Accessor to the PDF file.
 * @return The location of the PDF file on the disk.
 */
string Report::getPDFFile() const {
	return this->pdfFile;
}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType Report::getType() const {
	return NONE;
}
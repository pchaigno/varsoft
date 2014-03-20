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

QJsonDocument Report::getDataJson() const
{
    return dataJson;
}

QString Report::getTemplateFile() const
{
    return "A ENLEVER PLUS TARD";
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

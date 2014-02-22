#include "Report.h"

/**
* @brief Empty constructor
* Should only be used by Qt containers.
*/
Report::Report() {

}

/**
 * @brief A report.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(QString docxPath, QString pdfPath) {
	this->docxPath = docxPath;
	this->pdfPath = pdfPath;
}

/**
 * @brief Accessor to the DOCX path.
 * @return The location of the DOCX file on the disk.
 */
QString Report::getDOCXPath() const {
	return this->docxPath;
}

/**
 * @brief Accessor to the PDF path.
 * @return The location of the PDF file on the disk.
 */
QString Report::getPDFPath() const {
	return this->pdfPath;
}

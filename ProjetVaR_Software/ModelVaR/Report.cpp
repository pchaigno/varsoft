#include "Report.h"

/**
 * @brief A report.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
Report::Report(string docxPath, string pdfPath) {
	this->docxPath = docxPath;
	this->pdfPath = pdfPath;
}

/**
 * @brief Accessor to the DOCX path.
 * @return The location of the DOCX file on the disk.
 */
string Report::getDOCXPath() const {
	return this->docxPath;
}

/**
 * @brief Accessor to the PDF path.
 * @return The location of the PDF file on the disk.
 */
string Report::getPDFPath() const {
	return this->pdfPath;
}
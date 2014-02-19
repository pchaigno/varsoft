#include "BacktestingReportFactory.h"

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
BacktestingReportFactory::BacktestingReportFactory(QString docxPath, QString pdfPath):
	ReportFactory(docxPath, pdfPath) {

}

/**
 * @brief Generates the DOCX file using a DocxGenerator.
 * @return The DocxGenerator used.
 */
DocxGenerator& BacktestingReportFactory::generateDOCX() {
	// TODO
	return this->docxGenerator;
}
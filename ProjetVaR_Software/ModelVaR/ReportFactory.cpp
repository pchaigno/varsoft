#include "ReportFactory.h"

/**
 * @brief ReportFactory::ReportFactory
 * @param docxPath
 * @param pdfPath
 */
ReportFactory::ReportFactory(QString docxPath, QString pdfPath):
	docxGenerator(DocxGenerator(docxPath)) {
	this->docxPath = docxPath;
	this->pdfPath = pdfPath;
}

/**
 * @brief Generates the report.
 * @return The report.
 */
Report ReportFactory::generateReport() {
	this->docxGenerator = this->generateDOCX();
	this->generatePDF();
	return Report(this->docxPath, this->pdfPath);
}

/**
 * @brief Generates the PDF.
 * Converts the DOCX file to a PDF.
 */
void ReportFactory::generatePDF() {
	this->docxGenerator.convertToPDF();
}
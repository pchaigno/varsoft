#include "ReportFactory.h"

/**
 * @brief ReportFactory::ReportFactory
 * @param docxPath
 * @param pdfPath
 */
ReportFactory::ReportFactory(QString docxFile, QString pdfFile){
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
 */
void ReportFactory::generatePDF() {

}

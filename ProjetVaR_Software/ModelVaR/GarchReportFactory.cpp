#include "GarchReportFactory.h"

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
GarchReportFactory::GarchReportFactory(QString docxFile, QString pdfFile):
	ReportFactory(docxFile, pdfFile) {

}

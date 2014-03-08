#include "StatisticsReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
StatisticsReport::StatisticsReport() {

}

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
StatisticsReport::StatisticsReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
StatisticsReport::StatisticsReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
	return STATISTICS;
}

#include "StatisticsReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
StatisticsReport::StatisticsReport() {

}

StatisticsReport::StatisticsReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

StatisticsReport::StatisticsReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
	return STATISTICS;
}

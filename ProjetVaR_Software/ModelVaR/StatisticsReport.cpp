#include "StatisticsReport.h"

StatisticsReport::StatisticsReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
	return STATISTICS;
}

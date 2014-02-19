#include "StatisticsReport.h"

StatisticsReport::StatisticsReport(QString docxPath, QString pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
	return STATISTICS;
}
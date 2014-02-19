#include "StatisticsReport.h"

StatisticsReport::StatisticsReport(string docxPath, string pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
	return STATISTICS;
}
#include "CorrelationReport.h"

CorrelationReport::CorrelationReport(string docxPath, string pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType CorrelationReport::getType() const {
	return CORRELATION;
}
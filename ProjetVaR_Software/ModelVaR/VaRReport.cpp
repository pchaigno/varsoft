#include "VaRReport.h"

VaRReport::VaRReport(string docxPath, string pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType VaRReport::getType() const {
	return VAR;
}
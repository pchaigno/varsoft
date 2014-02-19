#include "VaRReport.h"

VaRReport::VaRReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType VaRReport::getType() const {
	return VAR;
}
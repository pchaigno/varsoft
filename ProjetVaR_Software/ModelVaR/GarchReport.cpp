#include "GarchReport.h"

GarchReport::GarchReport(QString docxPath, QString pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType GarchReport::getType() const {
	return GARCH;
}
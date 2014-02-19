#include "GarchReport.h"

GarchReport::GarchReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType GarchReport::getType() const {
	return GARCH;
}
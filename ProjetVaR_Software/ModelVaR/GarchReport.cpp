#include "GarchReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
GarchReport::GarchReport() {

}

GarchReport::GarchReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

GarchReport::GarchReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType GarchReport::getType() const {
	return GARCH;
}
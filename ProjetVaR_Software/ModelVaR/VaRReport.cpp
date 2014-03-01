#include "VaRReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
VaRReport::VaRReport() {

}

VaRReport::VaRReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

VaRReport::VaRReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType VaRReport::getType() const {
	return VAR;
}
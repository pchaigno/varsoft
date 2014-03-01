#include "CorrelationReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
CorrelationReport::CorrelationReport() {

}

CorrelationReport::CorrelationReport(QString docxPath, QString pdfPath): Report(docxPath, pdfPath) {

}

CorrelationReport::CorrelationReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType CorrelationReport::getType() const {
	return CORRELATION;
}

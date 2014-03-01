#include "BacktestingReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
BacktestingReport::BacktestingReport() {

}

BacktestingReport::BacktestingReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

BacktestingReport::BacktestingReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType BacktestingReport::getType() const {
	return BACKTESTING;
}
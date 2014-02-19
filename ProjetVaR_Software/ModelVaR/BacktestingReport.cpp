#include "BacktestingReport.h"

BacktestingReport::BacktestingReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType BacktestingReport::getType() const {
	return BACKTESTING;
}
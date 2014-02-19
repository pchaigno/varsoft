#include "BacktestingReport.h"

BacktestingReport::BacktestingReport(QString docxPath, QString pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType BacktestingReport::getType() const {
	return BACKTESTING;
}
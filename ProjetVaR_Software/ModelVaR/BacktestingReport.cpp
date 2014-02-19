#include "BacktestingReport.h"

BacktestingReport::BacktestingReport(string docxPath, string pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType BacktestingReport::getType() const {
	return BACKTESTING;
}
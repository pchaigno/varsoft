#pragma once

#include "Report.h"

class BacktestingReport: public Report {
public:
	BacktestingReport(string docxPath, string pdfPath);
};
#pragma once

#include "Report.h"

class BacktestingReport: public Report {
public:
	BacktestingReport(QString docxPath, QString pdfPath);
	virtual ReportType getType() const;
};
#pragma once

#include <QString>
#include "Report.h"

class BacktestingReport: public Report {
public:
	BacktestingReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
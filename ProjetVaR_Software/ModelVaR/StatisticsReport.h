#pragma once

#include "Report.h"

class StatisticsReport: public Report {
public:
	StatisticsReport(string docxPath, string pdfPath);
	virtual ReportType getType() const;
};
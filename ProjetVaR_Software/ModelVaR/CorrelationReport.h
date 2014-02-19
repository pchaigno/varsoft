#pragma once

#include "Report.h"

class CorrelationReport: public Report {
public:
	CorrelationReport(string docxPath, string pdfPath);
	virtual ReportType getType() const;
};
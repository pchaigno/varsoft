#pragma once

#include "Report.h"

class VaRReport: public Report {
public:
	VaRReport(string docxPath, string pdfPath);
	virtual ReportType getType() const;
};
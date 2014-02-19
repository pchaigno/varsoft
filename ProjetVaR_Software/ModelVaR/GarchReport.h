#pragma once

#include "Report.h"

class GarchReport: public Report {
public:
	GarchReport(string docxPath, string pdfPath);
	virtual ReportType getType() const;
};
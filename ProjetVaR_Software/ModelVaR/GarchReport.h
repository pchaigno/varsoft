#pragma once

#include "Report.h"

class GarchReport: public Report {
public:
	GarchReport(QString docxPath, QString pdfPath);
	virtual ReportType getType() const;
};
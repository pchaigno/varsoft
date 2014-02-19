#pragma once

#include "Report.h"

class CorrelationReport: public Report {
public:
	CorrelationReport(QString docxPath, QString pdfPath);
	virtual ReportType getType() const;
};
#pragma once

#include <QString>
#include "Report.h"

class CorrelationReport: public Report {
public:
	CorrelationReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
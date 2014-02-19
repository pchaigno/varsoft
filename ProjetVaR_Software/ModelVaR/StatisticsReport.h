#pragma once

#include "Report.h"
#include <QString>

class StatisticsReport: public Report {
public:
	StatisticsReport(QString docxPath, QString pdfPath);
	virtual ReportType getType() const;
};
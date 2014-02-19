#pragma once

#include "Report.h"
#include <QString>

class StatisticsReport: public Report {
public:
	StatisticsReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
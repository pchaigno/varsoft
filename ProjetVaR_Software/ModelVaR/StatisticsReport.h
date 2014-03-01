#pragma once

#include "Report.h"
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT StatisticsReport: public Report {
public:
    StatisticsReport();
	StatisticsReport(QString docxFile, QString pdfFile);
	StatisticsReport(int id, QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
#pragma once

#include "Report.h"
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT StatisticsReport: public Report {
public:
	StatisticsReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
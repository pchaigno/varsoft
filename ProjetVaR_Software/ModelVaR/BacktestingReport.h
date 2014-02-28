#pragma once

#include <QString>
#include "Report.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT BacktestingReport: public Report {
public:
	BacktestingReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
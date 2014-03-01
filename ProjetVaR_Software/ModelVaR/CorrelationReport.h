#pragma once

#include <QString>
#include "Report.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT CorrelationReport: public Report {
public:
    CorrelationReport();
	CorrelationReport(QString docxFile, QString pdfFile);
	CorrelationReport(int id, QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
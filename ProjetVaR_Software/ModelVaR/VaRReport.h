#pragma once

#include "Report.h"
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT VaRReport: public Report {
public:
	VaRReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
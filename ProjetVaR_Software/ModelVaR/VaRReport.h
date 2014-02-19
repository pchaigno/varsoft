#pragma once

#include "Report.h"
#include <QString>

class VaRReport: public Report {
public:
	VaRReport(QString docxPath, QString pdfPath);
	virtual ReportType getType() const;
};
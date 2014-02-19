#pragma once

#include "Report.h"
#include <QString>

class VaRReport: public Report {
public:
	VaRReport(QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
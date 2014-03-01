#pragma once

#include "Report.h"
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT GarchReport: public Report {
public:
    GarchReport();
	GarchReport(QString docxFile, QString pdfFile);
	GarchReport(int id, QString docxFile, QString pdfFile);
	virtual ReportType getType() const;
};
#pragma once

#include "ReportFactory.h"
#include <QString>

class VaRReportFactory: public ReportFactory {
public:
	VaRReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};
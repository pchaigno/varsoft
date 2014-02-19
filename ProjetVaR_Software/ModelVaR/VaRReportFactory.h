#pragma once

#include "ReportFactory.h"

class VaRReportFactory: public ReportFactory {
public:
    VaRReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};
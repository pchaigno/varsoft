#pragma once

#include "ReportFactory.h"

class VaRReportFactory: public ReportFactory {
public:
	VaRReportFactory(string docxPath, string pdfPath);
	virtual DocxGenerator& generateDOCX();
};
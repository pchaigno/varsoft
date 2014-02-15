#pragma once

#include "ReportFactory.h"

class GarchReportFactory: public ReportFactory {
public:
	GarchReportFactory(string docxPath, string pdfPath);
	virtual DocxGenerator& generateDOCX();
};
#pragma once

#include "ReportFactory.h"

class CorrelationReportFactory: public ReportFactory {
public:
	CorrelationReportFactory(string docxPath, string pdfPath);
	virtual DocxGenerator& generateDOCX();
};
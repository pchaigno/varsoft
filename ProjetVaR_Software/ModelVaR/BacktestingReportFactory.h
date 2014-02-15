#pragma once

#include "ReportFactory.h"

class BacktestingReportFactory: public ReportFactory {
public:
	BacktestingReportFactory(string docxPath, string pdfPath);
	virtual DocxGenerator& generateDOCX();
};
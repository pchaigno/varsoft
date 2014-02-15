#pragma once

#include "ReportFactory.h"

class StatisticsReportFactory: public ReportFactory {
public:
	StatisticsReportFactory(string docxPath, string pdfPath);
	virtual DocxGenerator& generateDOCX();
};
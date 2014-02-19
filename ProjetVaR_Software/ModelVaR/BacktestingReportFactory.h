#pragma once

#include "ReportFactory.h"

class BacktestingReportFactory: public ReportFactory {
public:
	BacktestingReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};
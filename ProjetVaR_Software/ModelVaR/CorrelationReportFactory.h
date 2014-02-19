#pragma once

#include "ReportFactory.h"

class CorrelationReportFactory: public ReportFactory {
public:
	CorrelationReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};
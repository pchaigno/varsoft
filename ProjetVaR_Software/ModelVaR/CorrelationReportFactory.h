#pragma once

#include "ReportFactory.h"
#include <QString>

class CorrelationReportFactory: public ReportFactory {
public:
	CorrelationReportFactory(QString docxFile, QString pdfFile);
	virtual DocxGenerator& generateDOCX();
};

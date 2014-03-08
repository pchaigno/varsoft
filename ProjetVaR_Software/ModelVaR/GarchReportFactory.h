#pragma once

#include "ReportFactory.h"

class GarchReportFactory: public ReportFactory {
public:
	GarchReportFactory(QString docxFile, QString pdfFile);
	virtual DocxGenerator& generateDOCX();
};

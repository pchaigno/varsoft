#ifndef H_VARREPORTFACTORY
#define H_VARREPORTFACTORY

#include "ReportFactory.h"

class VaRReportFactory: public ReportFactory {
public:
    VaRReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};

#endif

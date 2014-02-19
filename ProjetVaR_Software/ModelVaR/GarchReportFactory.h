#ifndef H_GARCHREPORTFACTORY
#define H_GARCHREPORTFACTORY

#include "ReportFactory.h"

class GarchReportFactory: public ReportFactory {
public:
    GarchReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};
#endif

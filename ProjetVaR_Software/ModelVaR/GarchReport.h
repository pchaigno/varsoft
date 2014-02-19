#ifndef H_GARCHREPORT
#define H_GARCHREPORT

#include "Report.h"
#include <QString>

class GarchReport: public Report {
public:
    GarchReport(QString docxPath, QString pdfPath);
};
#endif

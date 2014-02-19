#ifndef H_BACKTESTINGREPORT
#define H_BACKTESTINGREPORT

#include <QString>
#include "Report.h"

class BacktestingReport: public Report {
public:
    BacktestingReport(QString docxPath, QString pdfPath);
};
#endif

#pragma once

#include <QString>
#include "Report.h"

class BacktestingReport: public Report {
public:
    BacktestingReport(QString docxPath, QString pdfPath);
};

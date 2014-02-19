#pragma once

#include "Report.h"
#include <QString>

class GarchReport: public Report {
public:
    GarchReport(QString docxPath, QString pdfPath);
};

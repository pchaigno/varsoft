#pragma once

#include "Report.h"
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT VaRReport: public Report {
public:
    VaRReport();
    VaRReport(QString docxFile, QString pdfFile);
    VaRReport(int id, QString docxFile, QString pdfFile);
    virtual ReportType getType() const;
    virtual QString getTemplateFile() const;
};

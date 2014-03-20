#pragma once

#include <QString>
#include <QProcess>
#include <QJsonDocument>
#include "Report.h"
#include "ReportGenerator.h"

class DocxGenerator: public ReportGenerator {
public:
    DocxGenerator(Report * report);
    virtual void generate();
private:
    Report * report;
};

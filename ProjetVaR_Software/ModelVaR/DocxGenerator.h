#pragma once

#include <QString>
#include <QProcess>
#include <QJsonDocument>
#include "Report.h"
#include "ReportGenerator.h"
#include <QDebug>
#include <QFile>

class DocxGenerator: public ReportGenerator {
public:
    DocxGenerator();
    DocxGenerator(Report * report);
    virtual void generate();
private:
    Report * report;
};

#pragma once

#include <QString>

class Report {
private:
    QString docxPath;
    QString pdfPath;

public:
    Report(QString docxPath, QString pdfPath);
    QString getDOCXPath() const;
    QString getPDFPath() const;
};
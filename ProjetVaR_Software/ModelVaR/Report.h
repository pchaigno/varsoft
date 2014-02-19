#ifndef H_REPORT
#define H_REPORT

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
#endif

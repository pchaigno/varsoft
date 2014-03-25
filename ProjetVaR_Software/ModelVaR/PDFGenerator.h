#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H

#include "ReportGenerator.h"
#include "Report.h"
#include <QProcess>

class PDFGenerator : public ReportGenerator
{
public:
    PDFGenerator();
    PDFGenerator(Report * report);
    virtual void generate();
private:
    Report * report;
};

#endif // PDFGENERATOR_H

#include "PDFGenerator.h"

PDFGenerator::PDFGenerator()
{
}

PDFGenerator::PDFGenerator(Report *report)
{
    this->report=report;
}

void PDFGenerator::generate()
{
    QProcess docx;
    docx.start("java", QStringList() << "-jar" << "../DocxGenerator/DocxGenerator.jar" << report->getTemplateFile() << report->getPDFFile() << "-pdf");
    docx.waitForStarted();

    QString data = report->getDataJson().toString();
    docx.write(data.toLatin1(),data.length());
    docx.closeWriteChannel();

    docx.waitForFinished();
}

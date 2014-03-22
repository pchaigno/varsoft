#include "DocxGenerator.h"

/**
 * @brief Constructor
 * @param location The path to the DOCX file to generate.
 * @param templateFile The template file of the report
 * @param data the json data
 */
DocxGenerator::DocxGenerator()
{

}

DocxGenerator::DocxGenerator(Report *report) {
    this->report=report;
}

/**
 * @brief Generates the DOCX file
 */
void DocxGenerator::generate() {
    QProcess docx;
    qDebug() << "avant" << QFile::exists(report->getTemplateFile()) << QFile::exists("../../DocxGenerator/bin/DocXGenerator.class");
    docx.start("java", QStringList() << "../../DocxGenerator/bin/DocxGenerator" << report->getTemplateFile() << report->getDOCXFile());
    docx.waitForStarted();

    docx.write(report->getDataJson().toString().toLatin1());
    docx.closeWriteChannel();

    docx.waitForFinished();
    qDebug() << "appres" << QFile::exists(report->getTemplateFile()) << QFile::exists(report->getDOCXFile());
}

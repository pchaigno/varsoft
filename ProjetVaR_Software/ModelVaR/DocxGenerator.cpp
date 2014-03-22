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
    qDebug() << "avant" << QFile::exists(report->getTemplateFile()) << QFile::exists("../DocxGenerator/DocxGenerator.jar");
    docx.start("java", QStringList() << "-jar" << "../DocxGenerator/DocxGenerator.jar" << report->getTemplateFile() << report->getDOCXFile());
    docx.waitForStarted();

    QString data = report->getDataJson().toString();
    qint64 i = docx.write(data.toLatin1(),data.length());
    qDebug() << i;
    docx.closeWriteChannel();

    docx.waitForFinished();
    qDebug() << "appres" << QFile::exists(report->getTemplateFile()) << QFile::exists(report->getDOCXFile()) << report->getDOCXFile();
}

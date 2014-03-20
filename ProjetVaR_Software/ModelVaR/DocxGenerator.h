#pragma once

#include <QString>
#include <QProcess>
#include <QJsonDocument>
#include "ReportGenerator.h"

class DocxGenerator: public ReportGenerator {
public:
    DocxGenerator(QString location, QString templateFile,QJsonDocument doc);
	virtual void generate();
	void convertToPDF();

private:
    QString location, templateFile;
    QJsonDocument doc;
};

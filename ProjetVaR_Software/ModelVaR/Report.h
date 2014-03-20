#pragma once

#include <QString>
#include "IdAlreadyAttributedException.h"
#include "ModelVaR_global.h"
#include <QJsonDocument>

enum ReportType {
	NONE = 0,
	BACKTESTING,
	CORRELATION,
	GARCH,
	STATISTICS,
	VAR
};

class MODELVARSHARED_EXPORT Report {
private:
	int id;
	QString docxFile;
	QString pdfFile;
    QJsonDocument dataJson;

public:
	Report();
	Report(QString docxFile, QString pdfFile);
	Report(int id, QString docxFile, QString pdfFile);
	void init(int id, QString docxFile, QString pdfFile);

	int getId() const;
	void setId(int id);
	QString getDOCXFile() const;
	QString getPDFFile() const;
    // TODO Any way to make it abstract? (virtual ReportType getType() const = 0;)
	virtual ReportType getType() const;

    QJsonDocument getDataJson() const;
    virtual QString getTemplateFile() const = 0;


	bool operator==(const Report& report) const;
};

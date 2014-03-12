#pragma once

#include <QDateTime>
#include "IdAlreadyAttributedException.h"
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>
#include <stdexcept>
#include "ModelVaR_global.h"
#include "CannotOpenFileException.h"

class MODELVARSHARED_EXPORT Asset {
private:
	int id;
	QString file;
	QString name;
	QString origin;
	QDateTime firstDate;
	QDateTime lastDate;

public:
	Asset();
	Asset(QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate);
	Asset(int id, QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate);
	void init(int id, QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate);

	int getId() const;
	void setId(int id);
	QString getFile() const;
	QString getName() const;
	QString getOrigin() const;
	QDateTime getFirstDate() const;
	QDateTime getLastDate() const;
	void changeName(QString name);
	QVector<double> getValues();
	QVector<double> getValues(const QDateTime &startDate, const QDateTime &endDate);

	bool operator==(const Asset& asset) const;
};

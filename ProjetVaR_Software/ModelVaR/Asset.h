#pragma once

#include <QString>
#include <QDateTime>
#include "IdAlreadyAttributedException.h"

class Asset {
private:
	int id;
	QString file;
	QString name;
	QString origin;
	QDateTime firstDate;
	QDateTime lastDate;

public:
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
};
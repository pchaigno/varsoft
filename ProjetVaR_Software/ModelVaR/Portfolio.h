#pragma once

#include <QString>
#include <QVector>
#include "Report.h"
#include <QMap>
#include "Asset.h"
#include <QDateTime>
#include "IdAlreadyAttributedException.h"

class Portfolio {
private:
	int id;
	QString name;
	Portfolio* parent;
	QMap<Asset*, int> assets;
	QVector<Report> reports;

public:
	Portfolio();
	Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);
	Portfolio(QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);
	Portfolio(Portfolio* parent, int id, QString name, QMap<Asset *, int> &assets, QVector<Report>& reports);
	Portfolio(int id, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);
    void init(Portfolio* parent, int id, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);

	QString getName() const;
	int getId() const;
	void setId(int id);
	int getParentId() const;
	QVector<Report> getReports() const;
	void changeName(QString name);

	QDateTime retrieveFirstDate() const;
	QDateTime retrieveLastDate() const;
};

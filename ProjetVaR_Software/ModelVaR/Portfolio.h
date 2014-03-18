#pragma once

#include <QString>
#include <QVector>
#include "Report.h"
#include <QMap>
#include "Asset.h"
#include <QDateTime>
#include "IdAlreadyAttributedException.h"
#include "ModelVaR_global.h"
#include "PortfolioCalculationException.h"

class MODELVARSHARED_EXPORT Portfolio {
private:
	int id;
	QString name;
	Portfolio* parent;
	QMap<Asset*, int> composition;
	QVector<Report*> reports;

public:
	Portfolio();
	Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports);
	Portfolio(QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports);
	Portfolio(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports);
	Portfolio(int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports);
	void init(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports);

	QString getName() const;
	int getId() const;
	void setId(int id);
	int getParentId() const;
	QVector<Report*> getReports() const;
	QVector<Asset*> getAssets() const;
	QMap<Asset*, int> getComposition() const;
	void changeName(QString name);
	QDateTime retrieveFirstDate() const;
	QDateTime retrieveLastDate() const;
	static QVector<double> getReturns(QVector<double> &values);
	QVector<double> getValues() const;
	QVector<double> getValues(const QDateTime &startDate, const QDateTime &endDate) const;
	QMap<QDateTime, double> getValuesByDates(const QDateTime& startDate, const QDateTime& endDate) const;

	bool operator==(const Portfolio& portfolio) const;
};

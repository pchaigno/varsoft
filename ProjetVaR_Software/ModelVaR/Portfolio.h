/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <QString>
#include <QVector>
#include "Report.h"
#include <QMap>
#include "Asset.h"
#include <QDateTime>
#include <QDebug>
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
	QVector<double> retrieveReturns(QDateTime endingPeriodDate, int period) const;
	QVector<double> retrieveValues() const;
	QVector<double> retrieveValues(const QDateTime &startDate, const QDateTime &endDate) const;
	QMap<QDateTime, double> retrieveValuesByDate(const QDateTime& startDate, const QDateTime& endDate) const;

	bool operator==(const Portfolio& portfolio) const;
};

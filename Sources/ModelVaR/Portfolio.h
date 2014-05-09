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
#include <QDate>
#include "IdAlreadyAttributedException.h"
#include "InvalidDefinitionPeriodException.h"
#include "ModelVaR_global.h"
#include "PortfolioCalculationException.h"
#include <string>
#include <sstream>

class MODELVARSHARED_EXPORT Portfolio: public Savable {
private:
	int id;
	QString name;
	Portfolio* parent;
	QMap<Asset*, int> composition;
	QList<Report*> reports;

public:
	Portfolio();
	Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	~Portfolio();
	void init(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);

	QString getName() const;
	int getId() const;
	void setId(int id);
	int getParentId() const;

	QList<Report*> getReports() const;
	void addReport(Report* report);
	void removeReport(Report * report);

	QVector<Asset*> getAssets() const;
	QMap<Asset*, int> getComposition() const;
	void changeName(QString name);
	QDate retrieveStartDate() const;
	QDate retrieveEndDate() const;
	QVector<double> retrieveValues() const;
	QVector<double> retrieveValues(const QDate &startPeriod, const QDate &endPeriod) const;
	QMap<QDate, double> retrieveValuesByDate() const;
	QMap<QDate, double> retrieveValuesByDate(const QDate& startPeriod, const QDate& endPeriod) const;
	QVector<double> retrieveReturns() const;
	QVector<double> retrieveReturns(const QDate& startPeriod, const QDate& endPeriod) const;
	QVector<double> retrieveReturns(const QDate& endPeriod, int nbValues) const;

	bool operator==(const Portfolio& portfolio) const;
};

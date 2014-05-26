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
#include <QDebug>
#include <QtCore/qmath.h>
#include "IdAlreadyAttributedException.h"
#include "InvalidDefinitionPeriodException.h"
#include "ModelVaR_global.h"
#include "PortfolioCalculationException.h"
#include "MathFunctions.h"
#include <string>
#include <sstream>
#include "AssetsFactory.h"
#include <QJsonArray>
#include "NonexistentAssetException.h"
#include <QtCore/qmath.h>

class MODELVARSHARED_EXPORT Portfolio: public Savable {
private:
	int id;
	QString name;
	Portfolio* parent;
	QMap<Asset*, int> composition;
	QList<Report*> reports;

public:
	Portfolio();
	//Portfolio(Portfolio &port);
	Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	void init(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QList<Report*>& reports);
	Portfolio(const QJsonObject& json, QMap<QString, Portfolio*>& deserializedPortfolios);
	~Portfolio();

	QString getName() const;
	int getId() const;
	void setId(int id);
	Portfolio* getParent() const;
	int getParentId() const;

	QList<Report*> getReports() const;
	void addReport(Report* report);
	void removeReport(Report * report);

	QList<Asset*> getAssets() const;
	QMap<Asset*, int> getComposition() const;
	int getWeight(Asset* const asset) const;
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
	double retrieveReturnHorizon(const QDate& date, int horizon) const;
	QVector<double> retrieveLogReturns(const QDate& startPeriod, const QDate& endPeriod) const;
	QVector<double> retrieveLogReturns(const QDate& endPeriod, int nbValues) const;
	QVector<QVector<double> > computeCorrelationMatrix(const QDate& startDate, const QDate& endDate) const;

	bool operator==(const Portfolio& portfolio) const;

	void fromJSON(const QJsonObject &json, QMap<QString, Portfolio*>& portfoliosDeserialized);
	QJsonObject toJSON() const;
};

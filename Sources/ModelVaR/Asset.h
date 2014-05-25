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

#include "exceptions/IdAlreadyAttributedException.h"
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>
#include <stdexcept>
#include "ModelVaR_global.h"
#include "exceptions/CannotOpenFileException.h"
#include <QDate>
#include "Savable.h"
#include <QJsonObject>

class MODELVARSHARED_EXPORT Asset: public Savable {
private:
	int id;
	QString file;
	QString name;
	QString origin;
	QDate startDate;
	QDate endDate;

public:
	Asset();
	Asset(QString name, QString file, QString origin, QDate startDate, QDate endDate);
	Asset(int id, QString name, QString file, QString origin, QDate startDate, QDate endDate);
	void init(int id, QString name, QString file, QString origin, QDate startDate, QDate endDate);
	Asset(const QJsonObject& json);
	~Asset();

	int getId() const;
	void setId(int id);
	QString getFile() const;
	QString getName() const;
	QString getOrigin() const;
	QDate getStartDate() const;
	QDate getEndDate() const;
	void changeName(QString name);
	QVector<double> retrieveValues() const;
	QVector<double> retrieveValues(const QDate &startPeriod, const QDate &endPeriod) const;
	QMap<QDate, double> retrieveValuesByDate(const QDate& startPeriod, const QDate& endPeriod) const;

	bool operator==(const Asset& asset) const;

	void fromJSON(const QJsonObject &json);
	QJsonObject toJSON() const;
};

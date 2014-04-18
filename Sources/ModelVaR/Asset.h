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
	QDateTime startDate;
	QDateTime endDate;

public:
	Asset();
	Asset(QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate);
	Asset(int id, QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate);
	void init(int id, QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate);

	int getId() const;
	void setId(int id);
	QString getFile() const;
	QString getName() const;
	QString getOrigin() const;
	QDateTime getStartDate() const;
	QDateTime getEndDate() const;
	void changeName(QString name);
	QVector<double> retrieveValues() const;
	QVector<double> retrieveValues(const QDateTime &startDate, const QDateTime &endDate) const;
	QMap<QDateTime, double> retrieveValuesByDate(const QDateTime& startDate, const QDateTime& endDate) const;

	bool operator==(const Asset& asset) const;
};

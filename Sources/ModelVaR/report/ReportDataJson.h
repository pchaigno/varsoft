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

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QTemporaryFile>
#include <QPixmap>
#include <QDir>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT ReportDataJson {
public:
	ReportDataJson();
	~ReportDataJson();

	void addText(QString key, QString value);
	void addText(QString key, int value);
	void addText(QString key, double value);
	void addImage(QString key, QString path);
	void addImage(QString key, QUrl path);
	void addImage(QString key, QPixmap img);
	void addList(QString key, QList<QMap<QString,QString> > list);

	QString toString();

	bool operator==(const ReportDataJson & other) const;

private:
	QJsonObject texts;
	QJsonObject images;
	QJsonObject lists;

	QList<QTemporaryFile*> tempFileList;
};

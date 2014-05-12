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
#include "ReportDataJson.h"

ReportDataJson::ReportDataJson() {

}

ReportDataJson::~ReportDataJson() {
	qDeleteAll(tempFileList);
	tempFileList.clear();
}

/**
 * @brief Add the value with the given key to the Json document.
 * @param key The key in the template document.
 * @param value The value of the key in the generated document.
 */
void ReportDataJson::addText(QString key, QString value) {
	texts[key]=value;
}

/**
 * @brief Add the path of an image with the given key to the Json document.
 * @param key The key in the template document.
 * @param path The path of the image which will be displayed in the generated document.
 */
void ReportDataJson::addImage(QString key, QString path) {
	images[key]=path;
}

/**
 * @brief Same as addImage(QString key, QString path)
 * @param key
 * @param path
 */
void ReportDataJson::addImage(QString key, QUrl path) {
	images[key]=path.toLocalFile();
}

/**
 * @brief Creates a temporary file in the temp folder of the system
 * and set the path of the image with the given key to the json document.
 * The temporary file is deleted when this object(ReportDataJson) has been deleted.
 * @param key The key in the template document.
 * @param img a QPixmap of the image
 */
void ReportDataJson::addImage(QString key, QPixmap img) {
	QTemporaryFile* tmpfile = new QTemporaryFile(QDir::tempPath()+"/XXXXXXXXX.png");
	tempFileList.append(tmpfile);
	tmpfile->open();
	img.save(tmpfile,"PNG");
	images[key]=tmpfile->fileName();
}

/**
 * @brief ReportDataJson::addList
 * @param key
 * @param list
 */
void ReportDataJson::addList(QString key, QList<QMap<QString, QString> > list) {
	QJsonArray jsonArray;
	QMap<QString, QString> map;
	foreach(map, list) {
		QJsonObject jsonMap;
		foreach(QString key, map.keys()) {
			jsonMap[key]=map[key];
		}
		jsonArray.append(jsonMap);
	}
	lists[key]=jsonArray;
}

/**
 * @brief Gets the json string in compact format
 * @return the json document
 */
QString ReportDataJson::toString() {
	QJsonDocument data;
	QJsonObject document;
	document["text"]=texts;
	document["images"]=images;
	document["list"]=lists;
	data.setObject(document);
	return data.toJson();
}

bool ReportDataJson::operator==(const ReportDataJson &other) const {
	return this->texts==other.texts && this->images==other.images && this->lists==other.lists;
}

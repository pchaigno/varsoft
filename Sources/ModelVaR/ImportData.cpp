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
#include "ImportData.h"

/**
* @brief Import method for our own CSV files
* @param name The name of the stock
* @param file The file where are located the values.
* @param origin The origin of the file with the values.
* @param startDate The date of the first value defined.
* @param endDate The date of the last value defined.
*/
void ImportData::import(const QString &name, const QString &file, const QString &origin, const QDateTime &startDate, const QDateTime &endDate) const {
	QString fileName = file;
	QString data;
	QFile importedCSV(fileName);
	QStringList rowOfData;
	QStringList rowData;

	data.clear();
	rowOfData.clear();
	rowData.clear();

	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split("\n");
		importedCSV.close();
	}

	for (int x =0; x < rowOfData.size(); x++) {
		rowData = rowOfData.at(x).split(",");

		qDebug() << rowData[1];
	}
}

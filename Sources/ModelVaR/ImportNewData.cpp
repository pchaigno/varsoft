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
#include "ImportNewData.h"

/**
* @brief Creates a new file with selected data
* @param asset The asset created
* @param file The file where are located the values.
* @throw ImportException The data is not valid
*/
void ImportNewData::import(const Asset &asset, const QString& file) const {
	QString data;
	QFile importedCSV(file);
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();
	QRegExp date_regex("^(20|19)[0-9]{2}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$");
	QRegExp value_regex("^([0-9]+)([.])([0-9][0-9])$");
	QDate previousDate = QDate::fromString("2999-01-01", "yyyy-MM-dd");
	int data_index;
	if (asset.getOrigin() == "ProjectVaR") {
		data_index = 1;
	} else {
		data_index = 6;
	}

	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
		importedCSV.close();
	}

	//FILE CREATION OF IMPORTED DATA
	// Do unique names
	QFile fileCreated(asset.getFile());
	// The file is open in write-only mode and we check the opening
	if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}
	QTextStream flux(&fileCreated);
	flux.setCodec("UTF-8");
	QDate endDate = asset.getEndDate();
	QDate startDate = asset.getStartDate();
	rowData = rowOfData.at(0).split(",");
	if (!(rowData.count() < data_index)) {
		if (!((QString) rowData[0]).isEmpty() && !((QString)rowData[data_index]).isEmpty()) {
			flux << rowData[0] << "," << rowData[data_index] << "\n";
			// x = 1 to avoid the first line with labels
			for (int x =1; x < rowOfData.size()-1; x++) {
				rowData = rowOfData.at(x).split(",");
				//Check dates and values are correct
				if(date_regex.exactMatch(rowData[0]) && value_regex.exactMatch(rowData[data_index])) {
					QDate currentDate = QDate::fromString(rowData[0], "yyyy-MM-dd");
					//checks the order of dates
					if(previousDate > currentDate) {
						previousDate = currentDate;
						//checks if we are on still in the range of dates
						if ((endDate >= currentDate)) {
							if(startDate > currentDate) {
								break;
							}
							flux << rowData[0] << "," << rowData[data_index] << "\n";
						}
					} else {
						throw CreateAssetException("Dates are not sorted");
						return;
					}

				} else {
					throw CreateAssetException("The data is invalid");
					return;
				}
			}
		} else {
			throw CreateAssetException("Header is missing");
			return;
		}
	} else {
		throw CreateAssetException("Wrong file type");
		return;
	}
	fileCreated.close();
}

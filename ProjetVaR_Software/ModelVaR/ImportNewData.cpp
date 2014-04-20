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
#include "SessionSaver.h"
#include "SQLiteManager.h"
#include "SessionBuilder.h"

/**
* @brief Import method for Yahoo files
* @param name The name of the stock
* @param file The file where are located the values.
* @param origin The origin of the file with the values.
* @param startDate The date of the first value defined.
* @param endDate The date of the last value defined.
* @throw BadFile The file is not handled
*/
void ImportNewData::import(const QString &name, const QString &file, const QString &origin, const QDateTime &startDate, const QDateTime &endDate) const{
	QString data;
	QFile importedCSV(file);
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();
	QRegExp date_regex("^(20|19)[0-9]{2}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$");
	QRegExp value_regex("^([0-9]+)([.])([0-9][0-9])$");
	QDateTime previousDate = QDateTime::fromString("2999-01-01","yyyy-MM-dd");
	int data_index;
	if (origin == "ProjectVaR")
        data_index = 1;
	else
		data_index = 6;

	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
		importedCSV.close();
	}

	//FILE CREATION OF IMPORTED DATA
	// Do random names
	QString namealea = name+".csv";
	QFile fileCreated(namealea);
	// The file is open in write-only mode and we check the opening
	if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text)) {
	   return;
	}
	QTextStream flux(&fileCreated);
	flux.setCodec("UTF-8");
	rowData = rowOfData.at(0).split(",");
	if (!((QString) rowData[0]).isEmpty() && !((QString)rowData[data_index]).isEmpty()){
		flux << rowData[0] << "," << rowData[data_index] << "\n";
	}
	// x = 1 to avoid the first line with labels
	for (int x =1; x < rowOfData.size()-1; x++) {
		rowData = rowOfData.at(x).split(",");
		//TODO : Check that the date is correct
		/*
		if((rowData.count() >= data_index)) {
			 QMessageBox::warning(0, "Warning","The file is not valid");
			 fileCreated.close();
			 fileCreated.remove();
			 return;
		}
		*/
		if(date_regex.exactMatch(rowData[0]) && value_regex.exactMatch(rowData[data_index])){
			QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
			//checks the order of dates
			if(previousDate > currentDate){
				previousDate = currentDate;
				//checks if we are on still in the range of dates
				if ((endDate >= currentDate)) {
					if(startDate >= currentDate) {
						break;
					}
					flux << rowData[0] << "," << rowData[data_index] << "\n";
				}
			}
			else{
				QMessageBox::warning(0, "Warning","Dates are not sorted");
				return;
			}

		}
		else{
			QMessageBox::warning(0, "Warning","The data is invalid");
			return;
		}
	}
	fileCreated.close();
    Asset a = Asset(name,namealea,origin,endDate,startDate);
	SessionSaver::getInstance()->saveAsset(a);
}

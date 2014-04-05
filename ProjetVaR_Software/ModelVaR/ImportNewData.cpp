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
#include <QMessageBox>
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
void ImportNewData::import(const QString &name, const QString &file, const QString &origin, const QDate &startDate, const QDate &endDate) const{
	QString data;
	QFile importedCSV(file);
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();

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

	// x = 1 to avoid the first line with labels
	// rowOfData.size()-1 to avoid a blank line a the end of the file

	for (int x =1; x < rowOfData.size()-1; x++) {
		rowData = rowOfData.at(x).split(",");
		//TODO : Check that the date is correct
		if(!(rowData.count() >= 6)) {
			 QMessageBox::warning(0, "Attention","Le fichier que vous avez essayé d'importer n'est pas valide");
			 fileCreated.close();
			 fileCreated.remove();
			 break;
		}

		QDate currentDate = QDate::fromString(rowData[0], "yyyy-MM-dd");
		if ((startDate >= currentDate)) {
			if(endDate >= currentDate) {
				break;
			}
			flux << rowData[0] << "," << rowData[6] << "\n";
		}
	}
	fileCreated.close();

	Asset a = Asset(name,namealea,origin,startDate,endDate);
	SessionSaver::getInstance()->saveAsset(a);
}

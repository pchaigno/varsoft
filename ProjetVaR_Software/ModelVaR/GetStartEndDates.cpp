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

#include "GetStartEndDates.h"

void GetStartEndDates::retreiveDates(const QString &file){
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
    rowData = rowOfData.at(1).split(",");
    this->startDate = QDate::fromString(rowData[0],"yyyy-MM-dd");
    rowData = rowOfData.at(rowOfData.size()-1).split(",");
    this->endDate = QDate::fromString(rowData[0],"yyyy-MM-dd");
}

QDate GetStartEndDates::getStartDate(){
    return this->endDate;
}

QDate GetStartEndDates::getEndDate(){
    return this->startDate;
}


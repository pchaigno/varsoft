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
#include "Asset.h"

/**
* @brief Empty constructor
* Should only be used by Qt containers.
*/
Asset::Asset() {

}

/**
 * @brief Constructor with default id.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param origin The origin of the file with the values.
 * @param startDate The date of the first value defined.
 * @param endDate The date of the last value defined.
 */
Asset::Asset(QString name, QString file, QString origin, QDate startDate, QDate endDate) {
	this->init(-1, name, file, origin, startDate, endDate);
}

/**
 * @brief Constructor
 * @param id The ID of the asset in the database.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param origin The origin of the file with the values.
 * @param startDate The date of the first value defined.
 * @param endDate The date of the last value defined.
 */
Asset::Asset(int id, QString name, QString file, QString origin, QDate startDate, QDate endDate) {
	this->init(id, name, file, origin, startDate, endDate);
}

/**
 * @brief Method called by all constructor to initiate the values.
 * @param id The ID of the asset in the database.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param origin The origin of the file with the values.
 * @param startDate The date of the first value defined.
 * @param endDate The date of the last value defined.
 */
void Asset::init(int id, QString name, QString file, QString origin, QDate startDate, QDate endDate) {
	if(startDate > endDate) {
		throw std::invalid_argument("The start and end dates for the asset are inverted.");
	}
	this->id = id;
	this->name = name;
	this->file = file;
	this->origin = origin;
	this->startDate = startDate;
	this->endDate = endDate;
}

/**
 * @brief Builds the asset from a JSON document.
 * @param json The JSON document.
 */
Asset::Asset(const QJsonObject& json) {
	this->fromJSON(json);
}

/**
 * @brief Accessor to id.
 * @return The id of the asset in the database.
 */
int Asset::getId() const {
	return this->id;
}

/**
 * @brief Updates the asset's id.
 * @param id The id.
 * @throw IdAlreadyAttributedException If an id was already attributed.
 */
void Asset::setId(int id) {
	if(this->id != -1) {
		// TODO Improve error message.
		throw IdAlreadyAttributedException("An id has already been attributed to this asset.");
	}
	this->id = id;
}

/**
 * @brief Accessor to file.
 * @return The file where are located the values.
 */
QString Asset::getFile() const {
	return this->file;
}

/**
 * @brief Accessor to name.
 * @return The name of the asset.
 */
QString Asset::getName() const {
	return this->name;
}

/**
 * @brief Accessor to origin
 * @return The origin of the file with the values.
 */
QString Asset::getOrigin() const {
	return this->origin;
}

/**
 * @brief Accessor to the first date defined.
 * @return The date of the first value defined.
 */
QDate Asset::getStartDate() const {
	return this->startDate;
}

/**
 * @brief Accessor to the last date defined.
 * @return The date of the last value defined.
 */
QDate Asset::getEndDate() const {
	return this->endDate;
}

/**
 * @brief Change the asset's name.
 * @param name The new name.
 */
void Asset::changeName(QString name) {
	this->name = name;
}

/**
 * @brief Retrieve the asset values between its startDate and endDate attributes
 * @return The values of the asset in the chronological order
 */
QVector<double> Asset::retrieveValues() const {
	return this->retrieveValues(this->startDate, this->endDate);
}

/**
 * @brief Retrieves the asset values between startDate and endDate from the asset file.
 * Fills in values for dates missing (public holidays).
 * Skips week-ends' days.
 * @param startPeriod Starts retrieving values from this date.
 * @param endPeriod Retrieves to this date maximum.
 * @return The values of the asset between the two dates in the chronogical order.
 */
QVector<double> Asset::retrieveValues(const QDate& startPeriod, const QDate& endPeriod) const {
	return this->retrieveValuesByDate(startPeriod, endPeriod).values().toVector();
}

/**
 * @brief Retrieves the asset values between startDate and endDate from the asset file.
 * Fills in values for dates missing (public holidays).
 * Skips week-ends' days.
 * @param startPeriod Starts retrieving values from this date.
 * @param endPeriod Retrieves to this date maximum.
 * @return The values of the asset for each dates between the two dates in the chronogical order.
 */
QMap<QDate, double> Asset::retrieveValuesByDate(const QDate& startPeriod, const QDate& endPeriod) const {
	// Throws an exception if the startDate is after the endDate.
	if(startPeriod > endPeriod) {
		throw std::invalid_argument("startPeriod: "+ startPeriod.toString().toStdString() + " is after endPeriod: " +
									endPeriod.toString().toStdString());
	}

	// Nothing to return if the dates are outside the asset's period of definition.
	if(startPeriod>this->endDate || endPeriod<this->startDate) {
		return QMap<QDate, double>();
	}

	// If the user entered dates too large, we must resize:
	// We make copies of the period's dates to keep them const.
	QDate realStartPeriod = QDate(startPeriod);
	QDate realEndPeriod = QDate(endPeriod);
	if(realStartPeriod < this->startDate) {
		realStartPeriod = this->startDate;
	}
	if(realEndPeriod > this->endDate) {
		realEndPeriod = this->endDate;
	}

	// Opens the file stream:
	QFile inputFile(this->getFile());
	if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw CannotOpenFileException("Could not open file: " + this->getFile().toStdString());
	}
	QTextStream in(&inputFile);

	// Skips the first line as it's only a header.
	in.readLine();

	// Loops over each line:
	QMap<QDate, double> values;
	QDate lastDate, date = QDate();
	bool endDetected = false;
	while(!in.atEnd()) {
		QString line = in.readLine();
		QRegExp rx("\\s*,\\s*");
		QStringList row = line.split(rx);
		lastDate = date;
		date = QDate::fromString(row.value(0), "yyyy-MM-dd");
		QString value = row.value(1);

		// Searches for the end of the period:
		if(date > realEndPeriod) {
			continue;
		}

		// If we've reached the start of the period, we stop:
		if(date < realStartPeriod) {
			// Fills the days missing if there are any:
			while(lastDate.addDays(-1)!=date && lastDate!=realStartPeriod) {
				if(lastDate.addDays(-1).dayOfWeek() < 6) {
				// It's a weekday.
					values.insert(lastDate.addDays(-1), value.toDouble());
				}
				lastDate = lastDate.addDays(-1);
			}
			break;
		}

		if(!endDetected) {
		// The end of the searched period as just been detected.
			endDetected = true;
			// Fills the days missing at the end of the period if there are any:
			QDate lastMissingDay = QDate(realEndPeriod);
			while(lastMissingDay != date) {
				if(lastMissingDay.dayOfWeek() < 6) {
				// It's a weekday.
					values.insert(lastMissingDay, value.toDouble());
					lastDate = QDate(lastMissingDay);
				}
				lastMissingDay = lastMissingDay.addDays(-1);
			}
		}

		// Fills the days missing if there are any:
		// If lastDate is null it means that we still are on the first date.
		// Therefore there aren't any missing days...
		while(!lastDate.isNull() && lastDate.addDays(-1)!=date) {
			if(lastDate.addDays(-1).dayOfWeek() < 6) {
			// It's a weekday.
				values.insert(lastDate.addDays(-1), value.toDouble());
			}
			lastDate = lastDate.addDays(-1);
		}

		if(date.dayOfWeek() < 6) {
		// It's a weekday.
			values.insert(date, value.toDouble());
		}
	}

	inputFile.close();
	return values;
}

/**
 * @brief Checks if two assets are equal.
 * @param asset The second asset.
 * @return True if the two assets are equal.
 */
bool Asset::operator==(const Asset& asset) const {
	return this->name == asset.name;
}

/**
 * @brief Deserializes the asset from a JSON document.
 * @param json The JSON document.
 */
void Asset::fromJSON(const QJsonObject &json) {
	this->id = -1;
	this->file = json["file"].toString();
	this->name = json["name"].toString();
	this->origin = json["origin"].toString();
	this->startDate = QDate::fromJulianDay((int)json["startDate"].toDouble());
	this->endDate = QDate::fromJulianDay((int)json["endDate"].toDouble());
}

/**
 * @brief Serializes the asset into a JSON document.
 * @param json The JSON document.
 */
QJsonObject Asset::toJSON() const {
	QJsonObject json;
	json["file"] = this->file;
	json["name"] = this->name;
	json["origin"] = this->origin;
	json["startDate"] = (double)this->startDate.toJulianDay();
	json["endDate"] = (double)this->endDate.toJulianDay();
	return json;
}

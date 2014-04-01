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
Asset::Asset(QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate) {
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
Asset::Asset(int id, QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate) {
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
void Asset::init(int id, QString name, QString file, QString origin, QDateTime startDate, QDateTime endDate) {
	this->id = id;
	this->name = name;
	this->file = file;
	this->origin = origin;
	this->startDate = startDate;
	this->endDate = endDate;
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
QDateTime Asset::getStartDate() const {
	return this->startDate;
}

/**
 * @brief Accessor to the last date defined.
 * @return The date of the last value defined.
 */
QDateTime Asset::getEndDate() const {
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
 * @brief Retrieve the asset values between startDate and endDate. It reads the
 * corresponding file located in the database
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The values of the asset in the chronological order, empty if parameters
 * don't match any dates in the file
 */
QVector<double> Asset::retrieveValues(const QDateTime& startDate, const QDateTime& endDate) const {
	QVector<double> values;
	QFile inputFile(this->getFile());

	// Throw an exception if the startDate is after the endDate.
	if(startDate > endDate) {
		throw std::invalid_argument("startDate: "+ startDate.toString().toStdString() + " is after endDate: " +
									endDate.toString().toStdString());
	}

	if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw CannotOpenFileException("Could not open file: " + this->getFile().toStdString());
	} else {
		QTextStream in(&inputFile);

		bool startDetected = false;

		// Loop over each line
		while(!in.atEnd()) {
			QString line = in.readLine();
			QRegExp rx("\\s*,\\s*");
			QStringList row = line.split(rx);
			QString date = row.value(0);
			QString value = row.value(1);
			QDateTime readDate = QDateTime::fromString(date,"yyyy-MM-dd");

			// If the ending date has not been read yet, it goes at the start of the loop
			// and read the next line
			if(!startDetected && readDate > endDate) {
				continue;
			}

			// If execution reaches that point, it means that the start date has been read
			if(startDetected == false) {
				startDetected = true;
			}

			// If the end date has been reached, it exits the loop
			// Otherwise it reads the file till the end
			if(readDate < startDate) {
				break;
			}

			// Building the vector
			values.push_front(value.toDouble());


		}
		inputFile.close();
	}

	return values;
}

/**
 * @brief Retrieve the associations of dates and asset values between startDate and endDate.
 * It reads the corresponding file located in the database
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The date and value associations of the asset in the chronological order
 */
// BUG
QMap<QDateTime, double> Asset::retrieveValuesByDate(const QDateTime& startDate, const QDateTime& endDate) const {
	QMap<QDateTime, double> values;
	QFile inputFile(this->getFile());

	// Throw an exception if the startDate is after the endDate.
	if(startDate > endDate) {
		throw std::invalid_argument("startDate: "+ startDate.toString().toStdString() + " is after endDate: " +
									endDate.toString().toStdString());
	}

	if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw CannotOpenFileException("Could not open file: " + this->getFile().toStdString());
	} else {
		QTextStream in(&inputFile);

		bool startDetected = false;

		// Loop over each line
		while(!in.atEnd()) {
			QString line = in.readLine();
			QRegExp rx("\\s*,\\s*");
			QStringList row = line.split(rx);
			QString date = row.value(0);
			QString value = row.value(1);
			QDateTime readDate = QDateTime::fromString(date,"yyyy-MM-dd");

			// If the ending date has not been read yet, it goes at the start of the loop
			// and read the next line
			if(!startDetected && readDate > endDate) {
				continue;
			}

			// If execution reaches that point, it means that the start date has been read
			if(startDetected == false) {
				startDetected = true;
			}

			// If the end date has been reached, it exits the loop
			// Otherwise it reads the file till the end
			if(readDate < startDate) {
				break;
			}

			// Building the vector
			values.insert(readDate, value.toDouble());
		}
		inputFile.close();
	}

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

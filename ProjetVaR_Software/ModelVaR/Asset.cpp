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
 * @param firstDate The date of the first value defined.
 * @param lastDate The date of the last value defined.
 */
Asset::Asset(QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate) {
	this->init(-1, name, file, origin, firstDate, lastDate);
}

/**
 * @brief Constructor
 * @param id The ID of the asset in the database.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param origin The origin of the file with the values.
 * @param firstDate The date of the first value defined.
 * @param lastDate The date of the last value defined.
 */
Asset::Asset(int id, QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate) {
	this->init(id, name, file, origin, firstDate, lastDate);
}

/**
 * @brief Method called by all constructor to initiate the values.
 * @param id The ID of the asset in the database.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param origin The origin of the file with the values.
 * @param firstDate The date of the first value defined.
 * @param lastDate The date of the last value defined.
 */
void Asset::init(int id, QString name, QString file, QString origin, QDateTime firstDate, QDateTime lastDate) {
	this->id = id;
	this->name = name;
	this->file = file;
	this->origin = origin;
	this->firstDate = firstDate;
	this->lastDate = lastDate;
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
QDateTime Asset::getFirstDate() const {
	return this->firstDate;
}

/**
 * @brief Accessor to the last date defined.
 * @return The date of the last value defined.
 */
QDateTime Asset::getLastDate() const {
	return this->lastDate;
}

/**
 * @brief Change the asset's name.
 * @param name The new name.
 */
void Asset::changeName(QString name) {
	this->name = name;
}



/**
 * @brief Getter of the asset values between its firstDate and lastDate
 * @return The values of the asset in the chronlogical order
 */
QVector<double> Asset::getValues() {
    return this->getValues(this->firstDate, this->lastDate);
}

/**
 * @brief Getter of the asset values.
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The values of the asset in the chronological order
 */
QVector<double> Asset::getValues(const QDateTime& startDate, const QDateTime& endDate) {
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

			// Building the vector
            values.push_front(value.toDouble());

			// If the end date has been reached, it exits the loop
			// Otherwise it reads the file till the end
            if(readDate <= startDate) {
				break;
			}
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

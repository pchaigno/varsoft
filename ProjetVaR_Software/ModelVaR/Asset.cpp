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
	if(id != -1) {
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

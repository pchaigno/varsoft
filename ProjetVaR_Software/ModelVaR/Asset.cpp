#include "Asset.h"

/**
 * @brief An asset.
 * @param name The name of the asset.
 * @param file The file where are located the values.
 * @param firstDate The date of the first value defined.
 * @param lastDate The date of the last value defined.
 */
Asset::Asset(string name, string file, time_t firstDate, time_t lastDate) {
	this->name = name;
	this->file = file;
	this->firstDate = firstDate;
	this->lastDate = lastDate;
}

/**
 * @brief Accessor to file.
 * @return The file where are located the values.
 */
string Asset::getFile() const {
	return this->file;
}

/**
 * @brief Accessor to name.
 * @return The name of the asset.
 */
string Asset::getName() const {
	return this->name;
}

/**
 * @brief Accessor to the first date defined.
 * @return The date of the first value defined.
 */
time_t Asset::getFirstDate() const {
	return this->firstDate;
}

/**
 * @brief Accessor to the last date defined.
 * @return The date of the last value defined.
 */
time_t Asset::getLastDate() const {
	return this->lastDate;
}

/**
 * @brief Change the asset's name.
 * @param name The new name.
 */
void Asset::changeName(string name) {
	this->name = name;
}
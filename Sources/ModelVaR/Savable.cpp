#include "Savable.h"

/**
 * @brief Constructor
 * @param fromDatabase True if the object comes from the database.
 */
Savable::Savable(bool fromDatabase) {
	this->saveStatus = fromDatabase? UPTODATE : ABSENT;
}

/**
 * @brief Checks if the object's copy in the database is up-to-date.
 * @return True if it's up-to-date.
 */
bool Savable::isUpToDate() const {
	return this->saveStatus == UPTODATE;
}

/**
 * @brief Checks if the object's copy in memory has been modified.
 * @return True if it has been modified.
 */
bool Savable::isModified() const {
	return this->saveStatus == MODIFIED;
}

/**
 * @brief Checks if the object has a copy in the database.
 * @return True if it's absent from the database.
 */
bool Savable::isAbsent() const {
	return this->saveStatus == ABSENT;
}

/**
 * @brief Sets the object as modified compared to the copy in the database.
 */
void Savable::setStatusToModified() {
	this->saveStatus = MODIFIED;
}

/**
 * @brief Sets the object as up-to-date compared to the copy in the database.
 */
void Savable::setStatusToUpToDate() {
	this->saveStatus = UPTODATE;
}

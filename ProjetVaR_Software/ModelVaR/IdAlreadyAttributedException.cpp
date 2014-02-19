#include "IdAlreadyAttributedException.h"

/**
 * @brief Constructor
 * @param message The error message.
 */
IdAlreadyAttributedException::IdAlreadyAttributedException(string message) {
	this->message = message;
}

const char* IdAlreadyAttributedException::what() const throw() {
	return this->message.c_str();
}
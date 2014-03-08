#pragma once

#include <exception>
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT CannotOpenFileException: public std::exception {
public:
	CannotOpenFileException(std::string msg) {
		this->msg = msg;
	}

	virtual ~CannotOpenFileException() throw() {

	}

	virtual const char * what() const throw() {
		return this->msg.c_str();
	}

private:
	std::string msg;
};

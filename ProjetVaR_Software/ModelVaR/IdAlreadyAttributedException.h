#pragma once

#include <exception>
#include <QString>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT IdAlreadyAttributedException: public std::exception
{
public:
	IdAlreadyAttributedException(std::string msg) {
		this->msg = msg;
	}

	virtual ~IdAlreadyAttributedException() throw() {

	}

	virtual const char * what() const throw() {
		return this->msg.c_str();
	}

private:
	std::string msg;
};

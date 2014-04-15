#pragma once

#include <exception>
#include <string>

class ReportException : public std::exception
{
public:
	ReportException(std::string msg) {
		this->msg = msg;
	}

	virtual ~ReportException() throw() {

	}

	virtual const char * what() const throw() {
		return this->msg.c_str();
	}

private:
	std::string msg;
};

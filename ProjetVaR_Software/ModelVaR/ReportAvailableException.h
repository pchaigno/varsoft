#ifndef REPORTAVAILABLEEXCEPTION_H
#define REPORTAVAILABLEEXCEPTION_H

#include <exception>
#include <string>

class ReportAvailableException : public std::exception
{
public:
	ReportAvailableException(std::string msg) {
		this->msg = msg;
	}

	virtual ~ReportAvailableException() throw() {

	}

	virtual const char * what() const throw() {
		return this->msg.c_str();
	}

private:
	std::string msg;
};

#endif // REPORTAVAILABLEEXCEPTION_H

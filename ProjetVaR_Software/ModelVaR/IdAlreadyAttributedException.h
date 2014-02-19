#pragma once

#include <exception>
#include <string>

using namespace std;

class IdAlreadyAttributedException: public exception {
private:
	string message;

public:
	IdAlreadyAttributedException(string message);
	virtual const char* what() const throw();
};
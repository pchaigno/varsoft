#pragma once

#include <string>
#include <ctime>
#include "IdAlreadyAttributedException.h"

using namespace std;

class Asset {
private:
	int id;
	string file;
	string name;
	string origin;
	time_t firstDate;
	time_t lastDate;

public:
	Asset(string name, string file, string origin, time_t firstDate, time_t lastDate);
	Asset(int id, string name, string file, string origin, time_t firstDate, time_t lastDate);
	void init(int id, string name, string file, string origin, time_t firstDate, time_t lastDate);

	int getId() const;
	void setId(int id);
	string getFile() const;
	string getName() const;
	string getOrigin() const;
	time_t getFirstDate() const;
	time_t getLastDate() const;
	void changeName(string name);
};
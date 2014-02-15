#pragma once

#include <string>
#include <ctime>

using namespace std;

class Asset {
private:
	string file;
	string name;
	time_t firstDate;
	time_t lastDate;

public:
	Asset(string name, string file, time_t firstDate, time_t lastDate);
	string getFile() const;
	string getName() const;
	time_t getFirstDate() const;
	time_t getLastDate() const;
	void changeName(string name);
};
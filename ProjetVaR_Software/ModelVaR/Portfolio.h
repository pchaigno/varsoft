#pragma once

#include <string>
#include <map>
#include "Asset.h"

using namespace std;

class Portfolio {
private:
	string name;
	Portfolio* parent;
	map<Asset*, int> assets;

public:
	Portfolio(const Portfolio& portfolio);
	Portfolio(Portfolio* parent, string name, map<Asset*, int>& assets);
	Portfolio(string name, map<Asset*, int>& assets);

	string getName() const;
	void changeName(string name);

	time_t retrieveFirstDate() const;
	time_t retrieveLastDate() const;

	Portfolio& operator=(const Portfolio& portfolio);
};
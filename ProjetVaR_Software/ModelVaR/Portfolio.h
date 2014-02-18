#pragma once

#include <string>
#include <vector>
#include "Report.h"
#include <map>
#include "Asset.h"
#include <climits>

using namespace std;

class Portfolio {
private:
	string name;
	Portfolio* parent;
	map<Asset*, int> assets;
	vector<Report> reports;

public:
	Portfolio(const Portfolio& portfolio);
	Portfolio(Portfolio* parent, string name, map<Asset*, int>& assets, vector<Report>& reports);
	Portfolio(string name, map<Asset*, int>& assets, vector<Report>& reports);

	string getName() const;
	vector<Report> getReports() const;
	void changeName(string name);

	time_t retrieveFirstDate() const;
	time_t retrieveLastDate() const;

	Portfolio& operator=(const Portfolio& portfolio);
};
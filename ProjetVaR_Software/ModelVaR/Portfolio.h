#pragma once

#include <string>
#include <vector>
#include "Report.h"
#include <map>
#include "Asset.h"
#include "IdAlreadyAttributedException.h"
#include <climits>

using namespace std;

class Portfolio {
private:
	int id;
	string name;
	Portfolio* parent;
	map<Asset*, int> assets;
	vector<Report> reports;

public:
	Portfolio(const Portfolio& portfolio);
	Portfolio(Portfolio* parent, string name, map<Asset*, int>& assets, vector<Report>& reports);
	Portfolio(string name, map<Asset*, int>& assets, vector<Report>& reports);
	Portfolio(Portfolio* parent, int id, string name, map<Asset*, int>& assets, vector<Report>& reports);
	Portfolio(int id, string name, map<Asset*, int>& assets, vector<Report>& reports);
	void init(Portfolio* parent, int id, string name, map<Asset*, int>& assets, vector<Report>& reports);

	string getName() const;
	int getId() const;
	void setId(int id);
	int getParentId() const;
	vector<Report> getReports() const;
	void changeName(string name);

	time_t retrieveFirstDate() const;
	time_t retrieveLastDate() const;

	Portfolio& operator=(const Portfolio& portfolio);
};
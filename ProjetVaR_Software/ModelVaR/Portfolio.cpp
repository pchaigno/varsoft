#include "Portfolio.h"

/**
 * @brief Constructor with parent.
 * @param parent The older version of the portfolio.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, string name, map<Asset*, int>& assets) {
	this->parent = parent;
	this->name = name;
	this->assets = assets;
}

/**
 * @brief Constructor
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 */
Portfolio::Portfolio(string name, map<Asset*, int>& assets) {
	this->parent = NULL;
	this->name = name;
	this->assets = assets;
}

/**
 * @brief Accessor to name.
 * @return The name of the portfolio.
 */
string Portfolio::getName() const {
	return this->name;
}

/**
 * @brief Changes the name of the portfolio.
 * @param name The new name.
 */
void Portfolio::changeName(string name) {
	this->name = name;
}

/**
 * @brief Retrieves the first date defined for this portfolio.
 * The first date defined for a portfolio is the first date
 * where every asset of the portfolio is defined.
 * @return The first date defined for this portfolio.
 */
time_t Portfolio::retrieveFirstDate() const {
	time_t maxFirstDate = 0;
	for(map<Asset*,int>::iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
		time_t firstDate = it->first->getFirstDate();
		if(firstDate > maxFirstDate) {
			maxFirstDate = firstDate;
		}
	}
	return maxFirstDate;
}

/**
 * @brief Retrieves the last date defined for this portfolio.
 * The last date defined for a portfolio is the last date
 * where every asset of the portfolio is defined.
 * @return The last date defined for this portfolio.
 */
time_t Portfolio::retrieveLastDate() const {
	time_t minLastDate = INT_MAX;
	for(map<Asset*,int>::iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
		time_t lastDate = it->first->getLastDate();
		if(lastDate < minLastDate) {
			minLastDate = lastDate;
		}
	}
	return minLastDate;
}
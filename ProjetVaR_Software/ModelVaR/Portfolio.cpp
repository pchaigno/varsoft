#include "Portfolio.h"

/**
 * @brief Constructor with parent.
 * @param parent The older version of the portfolio.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports) {
	this->parent = parent;
	this->name = name;
	this->assets = assets;
	this->reports = reports;
}

/**
 * @brief Constructor
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(QString name, QMap<Asset*, int>& assets, QVector<Report>& reports) {
	this->parent = NULL;
	this->name = name;
	this->assets = assets;
	this->reports = reports;
}

/**
 * @brief Accessor to name.
 * @return The name of the portfolio.
 */
QString Portfolio::getName() const {
	return this->name;
}

/**
 * @brief Accessor to reports.
 * @return The reports for this portfolio.
 */
QVector<Report> Portfolio::getReports() const {
	return this->reports;
}

/**
 * @brief Changes the name of the portfolio.
 * @param name The new name.
 */
void Portfolio::changeName(QString name) {
	this->name = name;
}

/**
 * @brief Retrieves the first date defined for this portfolio.
 * The first date defined for a portfolio is the first date
 * where every asset of the portfolio is defined.
 * @return The first date defined for this portfolio.
 */
QDateTime Portfolio::retrieveFirstDate() const {
    QDateTime maxFirstDate = 0;
    for(QMap<Asset*,int>::const_iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
        QDateTime firstDate = it->first->getFirstDate();
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
QDateTime Portfolio::retrieveLastDate() const {
    QDateTime minLastDate = INT_MAX;
    for(QMap<Asset*,int>::const_iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
        QDateTime lastDate = it->first->getLastDate();
		if(lastDate < minLastDate) {
			minLastDate = lastDate;
		}
	}
	return minLastDate;
}

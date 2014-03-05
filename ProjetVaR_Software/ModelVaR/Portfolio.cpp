#include "Portfolio.h"

/**
* @brief Empty constructor
* Should only be used by Qt containers.
*/
Portfolio::Portfolio() {

}

/**
 * @brief Constructor with parent.
 * @param parent The older version of the portfolio.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, QString name, QMap<Asset*, int> &assets, QVector<Report>& reports) {
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
    QDateTime maxFirstDate;
    maxFirstDate.setTime_t(0);
    for(QMap<Asset*, int>::const_iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
        QDateTime firstDate = it.key()->getFirstDate();
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
    QDateTime minLastDate;
    minLastDate.setTime_t(INT_MAX);
    for(QMap<Asset*, int>::const_iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
        QDateTime lastDate = it.key()->getLastDate();
		if(lastDate < minLastDate) {
			minLastDate = lastDate;
		}
	}
	return minLastDate;
}

/**
 * @brief Retrieves the values of a portfolio according to
 * the specified dates as QVectors
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The values of the portfolio
 */
QVector<double> Portfolio::getValues(const QDateTime & startDate, const QDateTime & endDate) const {
    int length = startDate.daysTo(endDate)+1;
    QVector<double> portfolioValues(length, 0);

    for(QMap<Asset*, int>::const_iterator it=this->assets.begin(); it!=this->assets.end(); ++it) {
        QVector<double> assetValues = it.key()->getValues(startDate, endDate);
        int weight = it.value();

        // We make sure that every asset has the same size and thus the values of the portfolio are
        // well defined
        if(assetValues.size() != length) {
            throw PortfolioCalculationException("Impossible");
        }

        for(QVector<double>::size_type i = 0; i != portfolioValues.size(); i++)
            portfolioValues[i] += assetValues[i]*weight;
    }

    return portfolioValues;
}

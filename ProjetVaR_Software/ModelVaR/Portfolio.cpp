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
 * @param composition The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports) {
	this->init(parent, -1, name, composition, reports);
}

/**
 * @brief Constructor
 * @param name The name of the portfolio.
 * @param composition The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports) {
	this->init(NULL, -1, name, composition, reports);
}

/**
 * @brief Constructor with parent.
 * @param parent The older version of the portfolio.
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param composition The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports) {
	this->init(parent, id, name, composition, reports);
}

/**
 * @brief Constructor
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param composition The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports) {
	this->init(NULL, id, name, composition, reports);
}

/**
 * @brief Method called by all constructors to initiate the object.
 * @param parent The older version of the portfolio.
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param composition The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
void Portfolio::init(Portfolio* parent, int id, QString name, QMap<Asset*, int>& composition, QVector<Report*>& reports) {
	this->parent = parent;
	this->id = id;
	this->name = name;
	this->composition = composition;
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
 * @brief Accessor to id.
 * @return The ID of the portfolio.
 */
int Portfolio::getId() const {
	return this->id;
}

/**
 * @brief Updates the portfolio's id.
 * @param id The id.
 * @throw IdAlreadyAttributedException If an id was already attributed.
 */
void Portfolio::setId(int id) {
	if(this->id != -1) {
		// TODO Improve error message.
		throw IdAlreadyAttributedException("An id has already been attributed to this portfolio.");
	}
	this->id = id;
}

/**
 * @brief Accessor to the ID of the parent of this portfolio.
 * @return The ID of the parent portfolio or -1 if there is no parent.
 */
int Portfolio::getParentId() const {
	if(this->parent == NULL) {
		return -1;
	}
	return this->parent->getId();
}

/**
 * @brief Accessor to reports.
 * @return The reports for this portfolio.
 */
QVector<Report*> Portfolio::getReports() const {
	return this->reports;
}

/**
 * @brief Accessor to the assets.
 * @return The assets composing the portfolio.
 */
QVector<Asset*> Portfolio::getAssets() const {
	QVector<Asset*> assets;
	for(QMap<Asset*, int>::const_iterator it=this->composition.begin(); it!=this->composition.end(); ++it) {
		assets.append(it.key());
	}
	return assets;
}

/**
 * @brief Accessor to the composition of the portfolio.
 * @return The weight for each asset of the portfolio.
 */
QMap<Asset*, int> Portfolio::getComposition() const {
	return this->composition;
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
	for(QMap<Asset*, int>::const_iterator it=this->composition.begin(); it!=this->composition.end(); ++it) {
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
	for(QMap<Asset*, int>::const_iterator it=this->composition.begin(); it!=this->composition.end(); ++it) {
		QDateTime lastDate = it.key()->getLastDate();
		if(lastDate < minLastDate) {
			minLastDate = lastDate;
		}
	}
	return minLastDate;
}

/**
 * @brief Retrieves the values of a portfolio on its largest time range
 * @return The values of the portfolio in the chronological order
 */
QVector<double> Portfolio::retrieveValues() const {
	return this->retrieveValues(this->retrieveFirstDate(), this->retrieveLastDate());
}

/**
 * @brief Retrieves the values of a portfolio according to
 * the specified dates. It reads each file corresponding to the assets
 * constituing the portfolio
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The values of the portfolio in the chronological order
 */
QVector<double> Portfolio::retrieveValues(const QDateTime& startDate, const QDateTime& endDate) const {
	return this->retrieveValuesByDate(startDate, endDate).values().toVector();
}

/**
 * @brief Retrieve the associations of dates and portfolio values between startDate and endDate.
 * It reads the corresponding files located in the database.
 * @param startDate The starting date
 * @param endDate The ending date
 * @return The date value associations of the portfolio in the chronological order
 */
QMap<QDateTime, double> Portfolio::retrieveValuesByDate(const QDateTime& startDate, const QDateTime& endDate) const {

	QMap<QDateTime, double> result;

	// Portfolio dates definition
	QDateTime firstDate;
	for(QMap<Asset*, int>::const_iterator assetIt=this->composition.begin(); assetIt!=this->composition.end(); ++assetIt) {
		QList<QDateTime> dates = assetIt.key()->retrieveValuesByDate(startDate, endDate).keys();

		// If a asset values vector is empty, we have no choice but to return
		// an empty map
		if(dates.isEmpty()) {
			return result;
		}

		// Check that all assets have the initial date in common
		if(firstDate.isNull()) {
			firstDate = *dates.begin();
		} else if(firstDate != *dates.begin()) {
			throw PortfolioCalculationException("All portfolio assets must share the first date");
		}

		// Portofolio dates construction
		for(QList<QDateTime>::const_iterator dateIt=dates.begin(); dateIt!=dates.end(); ++dateIt) {
			//if result.
			result.insert(*dateIt, 0);
		}
	}

	// Calculation of portfolio values
	for(QMap<Asset*, int>::const_iterator assetIt=this->composition.begin(); assetIt!=this->composition.end(); ++assetIt) {

		QMap<QDateTime, double> assetValuesByDates = assetIt.key()->retrieveValuesByDate(startDate, endDate);
		int weight = assetIt.value();

		for(QMap<QDateTime, double>::const_iterator portfolioIt=result.begin(); portfolioIt!=result.end(); portfolioIt++) {
			// Check that the asset has the date of the portfolio
			if(assetValuesByDates.contains(portfolioIt.key())) {
				result.insert(portfolioIt.key(), portfolioIt.value() + assetValuesByDates.value(portfolioIt.key())*weight);
			// Take the latest available value of the asset
			} else {
				QDateTime latestCommonDate = portfolioIt.key().addDays(-1);
				while(latestCommonDate >= assetValuesByDates.begin().key() && !assetValuesByDates.contains(latestCommonDate)) {
					latestCommonDate = latestCommonDate.addDays(-1);
				}
				result.insert(portfolioIt.key(), portfolioIt.value() + assetValuesByDates.value(latestCommonDate)*weight);
			}
		}
	}

	return result;
}

/**
 * @brief Calculates the returns associated with the values
 * @param values Values in a chronological order
 * @return The returns in a chronological order
 */
QVector<double> Portfolio::getReturns(QVector<double> &values) {
	QVector<double> returns;

	for(int i=1; i < values.size(); i++) {
		returns.push_back(values.at(i) - values.at(i-1));
	}

	return returns;
}

/**
 * @brief Checks if two portfolios are equal.
 * @param a The first portfolio.
 * @param b The second asset.
 * @return True if the two assets are equal.
 */
bool Portfolio::operator==(const Portfolio& portfolio) const {
	return this->name == portfolio.name;
}

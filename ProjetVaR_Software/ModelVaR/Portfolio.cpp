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
Portfolio::Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports) {
	this->init(parent, -1, name, assets, reports);
}

/**
 * @brief Constructor
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(QString name, QMap<Asset*, int>& assets, QVector<Report>& reports) {
	this->init(NULL, -1, name, assets, reports);
}

/**
 * @brief Constructor with parent.
 * @param parent The older version of the portfolio.
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(Portfolio* parent, int id, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports) {
	this->init(parent, id, name, assets, reports);
}

/**
 * @brief Constructor
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
Portfolio::Portfolio(int id, QString name, QMap<Asset *, int> &assets, QVector<Report>& reports) {
	this->init(NULL, id, name, assets, reports);
}

/**
 * @brief Method called by all constructors to initiate the object.
 * @param parent The older version of the portfolio.
 * @param id The id of the portfolio in the database.
 * @param name The name of the portfolio.
 * @param assets The assets composing the portfolio.
 * @param reports The reports of the portfolio.
 */
void Portfolio::init(Portfolio* parent, int id, QString name, QMap<Asset *, int> &assets, QVector<Report>& reports) {
	this->parent = parent;
	this->id = id;
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
	if(this->id == -1) {
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

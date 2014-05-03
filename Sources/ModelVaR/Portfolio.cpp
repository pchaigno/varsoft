/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
 * @brief Builds the portfolio from a JSON document.
 * The assets must be deserialized and saved to the database before the portfolio.
 * @param json The JSON document.
 * @param portfoliosDeserialized The portfolios already deserialized.
 * This last param should contain the parent portfolio if one is needed.
 * Portfolios should be deserialized by id order so that for every portfolio, the parent will always be deserilized first.
 */
Portfolio::Portfolio(const QJsonObject& json, QMap<int, Portfolio*>& deserializedPortfolios) {
	this->fromJSON(json, deserializedPortfolios);
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
 * @brief Accessor to the parent portfolio.
 * @return The parent portfolio or null if none exists.
 */
Portfolio* Portfolio::getParent() const {
	return this->parent;
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
 * @brief Accessor to the weight of an asset.
 * @param asset The asset.
 * @return The weight of the asset or -1 if this asset doesn't exist in the portfolio.
 */
int Portfolio::getWeight(Asset* const asset) const {
	return this->composition.value(asset, -1);
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
 * for which every asset of the portfolio is defined.
 * @return The first date defined for this portfolio.
 */
QDate Portfolio::retrieveStartDate() const {
	QDate maxStartDate = QDate(0, 0, 0);
	for(QMap<Asset*, int>::const_iterator it=this->composition.begin(); it!=this->composition.end(); ++it) {
		QDate startDate = it.key()->getStartDate();
		if(startDate > maxStartDate) {
			maxStartDate = startDate;
		}
	}
	return maxStartDate;
}

/**
 * @brief Retrieves the last date defined for this portfolio.
 * The first date defined for a portfolio is the last date
 * for which every asset of the portfolio is defined.
 * @return The last date defined for this portfolio.
 */
QDate Portfolio::retrieveEndDate() const {
	QDate minEndDate = QDate::currentDate().addDays(100);
	for(QMap<Asset*, int>::const_iterator it=this->composition.begin(); it!=this->composition.end(); ++it) {
		QDate endDate = it.key()->getEndDate();
		if(endDate < minEndDate) {
			minEndDate = endDate;
		}
	}
	return minEndDate;
}

/**
 * @brief Retrieves the values of the portfolio on its largest time range.
 * @return The values of the portfolio in the chronological order
 */
QVector<double> Portfolio::retrieveValues() const {
	return this->retrieveValues(this->retrieveStartDate(), this->retrieveEndDate());
}

/**
 * @brief Retrieves the values of the portfolio between the specified dates.
 * Calls the eponymous method in Asset.
 * For a pair of dates, all assets should return the same number of values.
 * Therefore it's safe to sum them all directly.
 * @param startPeriod Starts retrieving values from this date.
 * @param endPeriod Retrieves to this date maximum.
 * @return The values of the portfolio in the chronological order.
 */
QVector<double> Portfolio::retrieveValues(const QDate& startPeriod, const QDate& endPeriod) const {
	return this->retrieveValuesByDate(startPeriod, endPeriod).values().toVector();
}

/**
 * @brief Retrieves the values of the portfolio on its largest time range.
 * Calls the eponymous method in Asset.
 * For a pair of dates, all assets should return the same number of values.
 * Therefore it's safe to sum them all directly.
 * @return The values of the portfolio by date in the chronological order.
 */
QMap<QDate, double> Portfolio::retrieveValuesByDate() const {
	return this->retrieveValuesByDate(this->retrieveStartDate(), this->retrieveEndDate());
}

/**
 * @brief Retrieves the values of the portfolio between the specified dates.
 * Calls the eponymous method in Asset.
 * For a pair of dates, all assets should return the same number of values.
 * Therefore it's safe to sum them all directly.
 * @param startPeriod Starts retrieving values from this date.
 * @param endPeriod Retrieves to this date maximum.
 * @return The values of the portfolio by date in the chronological order.
 */
QMap<QDate, double> Portfolio::retrieveValuesByDate(const QDate& startPeriod, const QDate& endPeriod) const {
	// If the user entered dates too large, we must resize:
	// We make copies of the period's dates to keep them const.
	QDate realStartPeriod = QDate(startPeriod);
	QDate realEndPeriod = QDate(endPeriod);
	QDate startDate = this->retrieveStartDate();
	QDate endDate = this->retrieveEndDate();
	if(realStartPeriod < startDate) {
		realStartPeriod = startDate;
	}
	if(realEndPeriod > endDate) {
		realEndPeriod = endDate;
	}

	QMap<QDate, double> values;
	for(QMap<Asset*, int>::const_iterator assetIt=this->composition.begin(); assetIt!=this->composition.end(); ++assetIt) {
		QMap<QDate, double> assetValues = assetIt.key()->retrieveValuesByDate(realStartPeriod, realEndPeriod);
		int weight = assetIt.value();

		if(values.size() == 0) {
		// First asset retrieved.
			for(QMap<QDate, double>::const_iterator assetValuesIt=assetValues.begin(); assetValuesIt!=assetValues.end(); assetValuesIt++) {
				values.insert(assetValuesIt.key(), assetValuesIt.value() * weight);
			}

		} else {
		// Not the first asset retrieved.

			// All retrieveValuesBydate on assets should return the same number of values:
			if(values.size() != assetValues.size()) {
				std::ostringstream oss;
				oss << "All assets don't return the same number of values (" << values.size() << " != " << assetValues.size() << ")";
				throw InvalidDefinitionPeriodException(oss.str());
			}

			// Sums:
			for(QMap<QDate, double>::const_iterator assetValuesIt=assetValues.begin(); assetValuesIt!=assetValues.end(); assetValuesIt++) {
				double sum = values.value(assetValuesIt.key()) + assetValuesIt.value() * weight;
				values.insert(assetValuesIt.key(), sum);
			}
		}
	}

	return values;
}

/**
 * @brief Retrieves the returns of the portfolio for its whole definition period.
 * Calls the retrieveValues method and computes the differences.
 * Reads the asset file for each call.
 * @return The returns in a chronological order.
 */
QVector<double> Portfolio::retrieveReturns() const {
	return this->retrieveReturns(this->retrieveStartDate(), this->retrieveEndDate());
}

/**
 * @brief Retrieves the returns of the portfolio between the specified dates.
 * Calls the retrieveValues method and computes the differences.
 * Reads the asset file for each call.
 * @param startPeriod Starts retrieving values from this date.
 * @param endPeriod Retrieves to this date maximum.
 * @return The returns in a chronological order.
 */
QVector<double> Portfolio::retrieveReturns(const QDate& startPeriod, const QDate& endPeriod) const {
	QVector<double> values = this->retrieveValues(startPeriod, endPeriod);
	QVector<double> returns = QVector<double>();
	for(int i=1; i<values.size(); i++) {
		returns.append(values[i] - values[i-1]);
	}
	return returns;
}

/**
 * @brief Retrieves nb_values returns of the portfolio before endPeriod.
 * The returned vector can be smaller than asked (if there aren't enough values).
 * @param endPeriod Retrieves to this date maximum.
 * @param nbValues The number of desired returns.
 * @return The returns in a chronological order.
 */
QVector<double> Portfolio::retrieveReturns(const QDate& endPeriod, int nbValues) const {
	// Computes the start date of the period:
	// The period should contain nb_values returns.
	// The date computed could be before the start date of the portfolio,
	// in which case retrieveReturns will return less returns than expected.
	QDate startPeriod = QDate(endPeriod);
	// We reduce to the last Monday:
	int nbDaysToMonday = startPeriod.dayOfWeek()-1;
	if(nbDaysToMonday < nbValues) {
		// Linear to the last Monday:
		startPeriod = startPeriod.addDays(-nbDaysToMonday);
		nbValues -= nbDaysToMonday;

		// We gets 5 values in a week:
		int nbWeeks = nbValues / 5;
		startPeriod = startPeriod.addDays(-nbWeeks * 7);
		nbValues = nbValues % 5;

		if(nbValues > 0) {
			// We reduce to the last Friday:
			startPeriod = startPeriod.addDays(-3);
			nbValues--;

			if(nbValues > 0) {
				// Linear to the end:
				startPeriod = startPeriod.addDays(-nbValues);
			}
		}
	} else {
		// No weekend between the two dates so it's linear.
		startPeriod = startPeriod.addDays(-nbValues);
	}

	return this->retrieveReturns(startPeriod, endPeriod);
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

/**
 * @brief Deserializes the portfolio from a JSON document.
 * The assets must be deserialized and saved to the database before the portfolio.
 * @param json The JSON document.
 * @param portfoliosDeserialized The portfolios already deserialized.
 * This last param should contain the parent portfolio if one is needed.
 * Portfolios should be deserialized by id order so that for every portfolio, the parent will always be deserilized first.
 */
void Portfolio::fromJSON(const QJsonObject &json, QMap<int, Portfolio*>& portfoliosDeserialized) {
	this->id = (int)json["id"].toDouble();
	this->name = json["name"].toString();
	this->parent = portfoliosDeserialized[(int)json["parent"].toDouble()];
	// Deserializes the composition:
	QVariantMap jsonComposition = json["composition"].toObject().toVariantMap();
	Asset* asset;
	foreach(const QString assetName, jsonComposition.keys()) {
		asset = AssetsFactory::getInstance()->retrieveAsset(assetName);
		// Throws an exception if asset non-deserialized yet.
		if(asset == NULL) {
			throw NonexistentAssetException("The asset named " + assetName + " doesn't exist in the database.");
		}
		this->composition[asset] = jsonComposition[assetName].toInt();
	}
	// Deserializes the reports:
	this->reports.clear();
	QJsonArray jsonReports = json["reports"].toArray();
	for(int i=0; i<jsonReports.size(); i++) {
		QJsonObject jsonReport = jsonReports[i].toObject();
		Report* report;
		switch((int)jsonReport["type"].toDouble()) {
			case GARCH:
				report = new GarchReport();
				break;
			case VAR:
				report = new VaRReport();
				break;
			case STATISTICS:
				report = new StatisticsReport();
				break;
			case CORRELATION:
				report = new CorrelationReport();
				break;
			case BACKTESTING:
				report = new BacktestingReport();
				break;
			default:
				// TODO Throw exception?
				break;
		}
		report->fromJSON(jsonReport);
		this->reports.append(report);
	}

	portfoliosDeserialized[this->id] = this;
}

/**
 * @brief Serializes the asset into a JSON document.
 * @param json The JSON document.
 */
void Portfolio::toJSON(QJsonObject &json) const {
	json["id"] = this->id;
	json["name"] = this->name;
	json["parent"] = this->getParentId();
	// Serializes the composition:
	QVariantMap jsonComposition;
	foreach(Asset* asset, this->composition.keys()) {
		jsonComposition[asset->getName()] = this->composition[asset];
	}
	json["composition"] = QJsonObject::fromVariantMap(jsonComposition);
	// Serializes the reports:
	QJsonArray jsonReports;
	foreach(const Report* report, this->reports) {
		QJsonObject jsonReport;
		report->toJSON(jsonReport);
		jsonReports.append(jsonReport);
	}
	json["reports"] = jsonReports;
}

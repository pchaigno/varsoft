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
#include "PortfolioViewModel.h"

PortfolioViewModel::PortfolioViewModel(QObject *parent): QAbstractTableModel(parent) {

}

PortfolioViewModel::PortfolioViewModel(Portfolio* portfolio, QObject *parent): QAbstractTableModel(parent) {
	this->portfolio = portfolio;
	createDataStructure();
}

/**
 * @brief Return the size of the vector datesRow + 1
 * (this method is called by Qt and should never be called by user, see Qt'doc)
 * @param parent
 * @return
 */
int PortfolioViewModel::rowCount(const QModelIndex &parent) const {
	return parent.isValid() ? 0 : datesRow.count()+1;
}

/**
 * @brief The return the vertical size of the private attribute mydata.
 * (this method is called by Qt and should never be called by user, see Qt'doc)
 * @param parent
 * @return
 */
int PortfolioViewModel::columnCount(const QModelIndex &parent) const {
	return parent.isValid() ? 0 : mydata.count();
}

/**
 * @brief Return the value contained in the internal structure.
 * Contains values of assets and fo portfolio for each dates.
 * (this method is called by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @param role
 * @return
 */
QVariant PortfolioViewModel::data(const QModelIndex &index, int role) const {
	if(!index.isValid())
		return QVariant();

	if(role == Qt::DisplayRole)	{
		if (index.column() < mydata.count() && index.row() < mydata[index.column()].count()) {
			return QVariant(mydata[index.column()][index.row()]);
		}
	}
	return QVariant();
}

/**
 * @brief Return the date of the portfolio for vertical header
 * and the name of the assets for the horinzontal header.
 * (this method is called by Qt and should never be called by user, see Qt'doc)
 * @param section
 * @param orientation
 * @param role
 * @return the QString for the specified section and orientation
 */
QVariant PortfolioViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Horizontal) {
		return QString("%1").arg(headers.at(section));
	} else {
		if (section == 0) {
			return QString("Weights");
		} else {
			return QString("%1").arg(datesRow.at(section-1).toString("dd-MM-yyyy"));
		}
	}

	return QVariant();
}

/**
 * @brief PortfolioItemModel::flags
 * Define the flags for the model, here is ItemIsSelectable and ItemIsEnable
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @return the flags
 */
Qt::ItemFlags PortfolioViewModel::flags(const QModelIndex &index) const {
	Q_UNUSED(index);
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

/**
 * @brief Setter of the portfolio.
 * Create the internal structure of the given portfolio.
 * @param portfolio the new portfolio
 */
void PortfolioViewModel::setPortfolio(Portfolio *portfolio) {
	this->portfolio = portfolio;
	createDataStructure();
}

/**
 * Create the internal data structure with the data of the Portfolio.
 * It creates a vector for the vertical and horizontal header,
 * put the values of the portfolio in the first columns, et the
 * values of each assets of the portfolio to others columns in the private attribute mydata.
 */
void PortfolioViewModel::createDataStructure() {
	QMap<Asset*, int> compo = portfolio->getComposition();
	QDateTime startDate = portfolio->retrieveStartDate();
	QDateTime endDate = portfolio->retrieveEndDate();
	QMap<QDateTime, double> dates;
	try {
		dates = portfolio->retrieveValuesByDate(startDate, endDate);
	} catch (std::exception & ) {
		QDateTime tmp = startDate;
		startDate = endDate;
		endDate = tmp;
		//bug des dates dans import ...
		dates = portfolio->retrieveValuesByDate(startDate, endDate);
	}

	mydata.clear();

	//set the horizontal headers with the name of portfolio and assets
	headers.clear();
	headers.append(portfolio->getName());
	foreach(Asset* asset, compo.keys()) {
		headers.append(asset->getName());
	}

	// set the vertical headers with the dates
	datesRow.clear();
	foreach(QDateTime date, dates.keys()) {
		datesRow.append(date);
	}

	qStableSort(datesRow.begin(), datesRow.end(), qGreater<QDateTime>());

	// put the first column of the table with the value of th portfolio for each date
	QVector<QString> columns;
	columns.clear();
	columns.resize(1+datesRow.count());
	foreach(QDateTime date, dates.keys()) {
		int index = datesRow.indexOf(date);
		columns[index+1] = QString::number(dates[date]);
	}
	mydata += columns;


	//put the value of each assets
	foreach(Asset* asset, compo.keys()) {
		columns.clear();
		columns.resize(1+datesRow.count());
		QMap<QDateTime, double> valvector = asset->retrieveValuesByDate(startDate, endDate);

		columns[0] = QString::number(compo[asset]); // number of asset in portfolio
		foreach(QDateTime date, valvector.keys()) {
			int index = datesRow.indexOf(date);
			columns[index+1] = QString::number(valvector[date]);
		}
		mydata += columns;
	}
}

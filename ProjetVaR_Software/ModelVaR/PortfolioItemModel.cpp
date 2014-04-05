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
#include "PortfolioItemModel.h"

PortfolioItemModel::PortfolioItemModel(QObject *parent): QAbstractListModel(parent) {

}

/**
 * @brief Return the number of row, or 0 if parent is not valid.
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param parent
 * @return the number of row
 */
int PortfolioItemModel::rowCount(const QModelIndex &parent) const {
	return parent.isValid() ? 0 : portfolioList.count();
}

/**
 * @brief Define the flags for the model, here is ItemIsSelectable and ItemIsEnable
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @return the flags
 */
Qt::ItemFlags PortfolioItemModel::flags(const QModelIndex &index) const {
	Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

/**
 * @brief Get the portfolio at the given ModelIndex, or NULL if the ModelIndex is not valid.
 * @param index the ModelIndex of the portfolio
 * @return A pointer to the Portfolio
 */
Portfolio *PortfolioItemModel::getPortfolio(const QModelIndex &index)
{
    return index.isValid() ? portfolioList[index.row()] : NULL;
}

Portfolio *PortfolioItemModel::getPortfolio(const QModelIndex &index)
{
    return index.isValid() ? portfolioList[index.row()] : NULL;
}
/**
 * @brief Return the data associate by the index with the specified role
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @param role
 * @return the data at index
 */
QVariant PortfolioItemModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() < 0 || index.row() >= portfolioList.count()) {
		return QVariant();
	}

	switch (role) {
		case Qt::DisplayRole:
			return QVariant(portfolioList[index.row()]->getName());
			break;
	}
	return QVariant();
}

/**
 * @brief Define the header
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param section
 * @param orientation
 * @param role
 * @return the header
 */
QVariant PortfolioItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		return QString("Portfolio");
	}

	return QAbstractListModel::headerData(section, orientation, role);
}

/**
 * @brief Add a portfolio to the model
 * @param portfolio the Portfolio to add
 */
void PortfolioItemModel::addPortfolio(Portfolio * portfolio) {
	if (portfolio==NULL) {
		throw std::invalid_argument("portfolio cannot be NULL");
	}
	const int count = portfolioList.count();
	beginInsertRows(QModelIndex(), count, count);
	portfolioList << portfolio;
	endInsertRows();
}
/**
 * @brief Insert a portfolio to the model at the specified row
 * @param portfolio the portfolio to insert
 * @param row
 */
void PortfolioItemModel::insertPortfolio(Portfolio *portfolio, int row) {
	if (portfolio==NULL) {
		throw std::invalid_argument("portfolio cannot be NULL");
	}

	if (row < 0 || row > portfolioList.count()) {
		throw std::invalid_argument("row out of bound");
	}

	beginInsertRows(QModelIndex(), row, row);
	portfolioList.insert(row,portfolio);
	endInsertRows();
}

/**
 * @brief Remove the portfolio from the model and delete the portfolio.
 * @param portfolio
 * @return true if the portfolio has been removed, false otherwise
 */
bool PortfolioItemModel::removePortfolio(Portfolio *portfolio) {
	if (portfolio==NULL) {
		throw std::invalid_argument("portfolio cannot be NULL");
	}

	int pos = portfolioList.indexOf(portfolio);
	return removePortfolio(pos);
}
/**
 * @brief Remove the portfolio at the specified row from the model and delete the portfolio.
 * @param row
 * @return true if the portfolio has been removed, false otherwise
 */
bool PortfolioItemModel::removePortfolio(int row) {
	if (row < 0 || row > portfolioList.count()-1) {
		throw std::invalid_argument("row out of bound");
	}

	beginRemoveRows(QModelIndex(),row,row);
	Portfolio * portfolio = portfolioList.at(row);
	bool res = portfolioList.removeOne(portfolio);
	if (res) {
		delete portfolio;
	}
	endRemoveRows();
	return res;
}

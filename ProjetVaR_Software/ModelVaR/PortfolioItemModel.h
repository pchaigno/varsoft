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
#pragma once

#include <QAbstractListModel>
#include "Portfolio.h"
#include <stdexcept>
#include <QDebug>

#ifdef UNITTEST
	class TestPortfolioItemModel;
#endif

class MODELVARSHARED_EXPORT PortfolioItemModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit PortfolioItemModel(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

#ifdef UNITTEST
	friend class TestPortfolioItemModel;
#endif

    Portfolio *getPortfolio(const QModelIndex & index);

signals:

public slots:
	void addPortfolio(Portfolio *portfolio);
	void insertPortfolio(Portfolio*portfolio,int row);

	bool removePortfolio(Portfolio*portfolio);
	bool removePortfolio(int row);

private:
	QList<Portfolio*> portfolioList;

};

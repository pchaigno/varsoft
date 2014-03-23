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
#include "PortfolioListView.h"

PortfolioListView::PortfolioListView(QWidget *parent) :
    QListView(parent)
{
}

/**
 * @brief Redefinition of the model's setter
 * @param model
 */
void PortfolioListView::setModel(PortfolioItemModel *model)
{
    this->QListView::setModel(model);
}
/**
 * @brief Redefinition of the model's getter
 * @return the model
 */
PortfolioItemModel *PortfolioListView::model() const
{
    return (PortfolioItemModel*)QListView::model();
}

void PortfolioListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QListView::currentChanged(current,previous);
    this->current=current;
    emit portfolioSelected(model()->getPortfolio(current));
}

Portfolio *PortfolioListView::getCurrentPortfolio() const
{
    return model()->getPortfolio(current);
}

/**
 * @brief Remove the selected items
 */
void PortfolioListView::removeSelectedPortfolio()
{
    QModelIndexList selectedItem = this->selectedIndexes();
    foreach(QModelIndex index, selectedItem)
    {
        model()->removePortfolio(index.row());
    }
}

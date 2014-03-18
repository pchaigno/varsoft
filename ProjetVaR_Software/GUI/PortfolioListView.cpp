#include "PortfolioListView.h"

PortfolioListView::PortfolioListView(QWidget *parent) :
    QListView(parent)
{
}

void PortfolioListView::setModel(PortfolioItemModel *model)
{
    this->QListView::setModel(model);
}

PortfolioItemModel *PortfolioListView::model()
{
    return (PortfolioItemModel*)QListView::model();
}

void PortfolioListView::removeSelectedPortfolio()
{
    QModelIndexList selectedItem = this->selectedIndexes();
    foreach(QModelIndex index, selectedItem)
    {
        model()->removePortfolio(index.row());
    }
}

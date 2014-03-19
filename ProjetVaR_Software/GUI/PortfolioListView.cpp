#include "PortfolioListView.h"

PortfolioListView::PortfolioListView(QWidget *parent) :
    QListView(parent)
{
}

/**
 * @brief PortfolioListView::setModel
 * Redefinition of the model's setter
 * @param model
 */
void PortfolioListView::setModel(PortfolioItemModel *model)
{
    this->QListView::setModel(model);
}
/**
 * @brief PortfolioListView::model
 * Redefinition of the model's getter
 * @return the model
 */
PortfolioItemModel *PortfolioListView::model() const
{
    return (PortfolioItemModel*)QListView::model();
}

/**
 * @brief PortfolioListView::removeSelectedPortfolio
 * Remove the selected items
 */
void PortfolioListView::removeSelectedPortfolio()
{
    QModelIndexList selectedItem = this->selectedIndexes();
    foreach(QModelIndex index, selectedItem)
    {
        model()->removePortfolio(index.row());
    }
}

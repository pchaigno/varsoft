#include "PortfolioItemModel.h"

PortfolioItemModel::PortfolioItemModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
/**
 * @brief PortfolioItemModel::rowCount
 * Return the number of row, or 0 if parent is not valid.
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param parent
 * @return the number of row
 */
int PortfolioItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : portfolioList.count();
}

/**
 * @brief PortfolioItemModel::flags
 * Define the flags for the model, here is ItemIsSelectable and ItemIsEnable
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @return the flags
 */
Qt::ItemFlags PortfolioItemModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
/**
 * @brief PortfolioItemModel::data
 * Return the data associate by the index with the specified role
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @param role
 * @return the data at index
 */
QVariant PortfolioItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= portfolioList.count())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant(portfolioList[index.row()]->getName());
        break;
    }
    return QVariant();
}
/**
 * @brief PortfolioItemModel::headerData
 * Define the header
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param section
 * @param orientation
 * @param role
 * @return the header
 */
QVariant PortfolioItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("Portfolio");
    }

    return QAbstractListModel::headerData(section, orientation, role);
}

/**
 * @brief PortfolioItemModel::addPortfolio
 * Add a portfolio to the model
 * @param portfolio the Portfolio to add
 */
void PortfolioItemModel::addPortfolio(Portfolio * portfolio)
{
    if (portfolio==0)
        throw std::invalid_argument("portfolio cannot be NULL");
    const int count = portfolioList.count();
    beginInsertRows(QModelIndex(), count, count);
    portfolioList << portfolio;
    endInsertRows();
}
/**
 * @brief PortfolioItemModel::insertPortfolio
 * Insert a portfolio to the model at the specified row
 * @param portfolio the portfolio to insert
 * @param row
 */
void PortfolioItemModel::insertPortfolio(Portfolio *portfolio, int row)
{
    beginInsertRows(QModelIndex(), row, row);
    portfolioList.insert(row,portfolio);
    endInsertRows();
}

/**
 * @brief PortfolioItemModel::removePortfolio
 * Remove the portfolio from the model and delete the portfolio.
 * @param portfolio
 * @return true if the portfolio has been removed, false otherwise
 */
bool PortfolioItemModel::removePortfolio(Portfolio *portfolio)
{
    int pos = portfolioList.indexOf(portfolio);
    return removePortfolio(pos);
}
/**
 * @brief PortfolioItemModel::removePortfolio
 * Remove the portfolio at the specified row from the model and delete the portfolio.
 * @param row
 * @return true if the portfolio has been removed, false otherwise
 */
bool PortfolioItemModel::removePortfolio(int row)
{
    beginRemoveRows(QModelIndex(),row,row);
    Portfolio * portfolio = portfolioList.at(row);
    bool res = portfolioList.removeOne(portfolio);
    if (res)
        delete portfolio;
    endRemoveRows();
    return res;
}

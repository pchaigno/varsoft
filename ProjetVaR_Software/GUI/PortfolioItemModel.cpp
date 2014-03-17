#include "PortfolioItemModel.h"

PortfolioItemModel::PortfolioItemModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int PortfolioItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : portfolioList.count();
}

Qt::ItemFlags PortfolioItemModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

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

QVariant PortfolioItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void PortfolioItemModel::addPortfolio(Portfolio * portfolio)
{
    const int count = portfolioList.count();
    beginInsertRows(QModelIndex(), count, count);
    portfolioList << portfolio;
    endInsertRows();
}

void PortfolioItemModel::insertPortfolio(Portfolio *portfolio, int row)
{
    beginInsertRows(QModelIndex(), row, row);
    portfolioList.insert(row,portfolio);
    endInsertRows();
}

void PortfolioItemModel::removePortfolio(Portfolio *portfolio)
{
    int pos = portfolioList.indexOf(portfolio);
    removePortfolio(pos);
}

void PortfolioItemModel::removePortfolio(int row)
{
    beginRemoveRows(QModelIndex(),row,row);
    portfolioList.removeOne(portfolioList.at(row));
    endRemoveRows();
}

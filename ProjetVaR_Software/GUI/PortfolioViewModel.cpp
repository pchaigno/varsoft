#include "PortfolioViewModel.h"

PortfolioViewModel::PortfolioViewModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

PortfolioViewModel::PortfolioViewModel(QVector<QVector<QString> > portfolio, QObject *parent) :
    QAbstractTableModel(parent)
{
    mydata = portfolio;
}

QVariant PortfolioViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= mydata.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        return QVariant(mydata[index.row()][index.column()]);
    }
    return QVariant();
}


QVariant PortfolioViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
           return QVariant();

       if (orientation == Qt::Horizontal)
           return QString("Column %1").arg(section);
       else
           return QString("Row %1").arg(section);
}

/**
 * @brief PortfolioItemModel::flags
 * Define the flags for the model, here is ItemIsSelectable and ItemIsEnable
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @return the flags
 */
Qt::ItemFlags PortfolioViewModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void PortfolioViewModel::addPortfolio(QVector<QVector<QString> > portfolio)
{
    if(std::find(mydata.begin(),mydata.end(),portfolio)!=mydata.end())
        return;
    beginInsertRows(QModelIndex(),mydata.size(),mydata.size());
    /*BOOST_SCOPE_EXIT(this_){
        this_->endInsertRows();
    }BOOST_SCOPE_EXIT_END*/
    mydata << portfolio;
    endInsertRows();
    /*
    const int count = assetList.count();
    beginInsertRows(QModelIndex(), count, count);
    assetList << asset;
    endInsertRows();
    */
}

bool PortfolioViewModel::removePortfolio()
{
    beginRemoveRows(QModelIndex(),0,0);
    /*BOOST_SCOPE_EXIT(this_){
        this_->endRemoveRows();
    }BOOST_SCOPE_EXIT_END//*/
    mydata.erase(mydata.begin(),0);
    endRemoveRows();
    return true;
    /*
    beginRemoveRows(QModelIndex(),row,row);
    Asset * asset = assetList.at(row);
    bool res = assetList.removeOne(asset);
    if (res)
        delete asset;
    endRemoveRows();
    */
}

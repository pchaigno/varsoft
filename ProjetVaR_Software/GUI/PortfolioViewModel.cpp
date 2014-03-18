#include "PortfolioViewModel.h"

PortfolioViewModel::PortfolioViewModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QVariant PortfolioViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= mydata.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return QVariant(mydata[index.row()]->getName());
            break;
        }
    }
    return QVariant();
}


QVariant PortfolioViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("Asset");
    }
    return QAbstractTableModel::headerData(section, orientation, role);
    //return QVariant();
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

void PortfolioViewModel::addAsset(Asset* asset)
{
    if(std::find(mydata.begin(),mydata.end(),data)!=mydata.end())
        return;
    beginInsertRows(QModelIndex(),mydata.size(),mydata.size());
    /*BOOST_SCOPE_EXIT(this_){
        this_->endInsertRows();
    }BOOST_SCOPE_EXIT_END*/
    mydata.push_back(std::move(asset));
    endInsertRows();
    /*
    const int count = assetList.count();
    beginInsertRows(QModelIndex(), count, count);
    assetList << asset;
    endInsertRows();
    */
}

void PortfolioViewModel::removeAsset(int row)
{
    beginRemoveRows(QModelIndex(),row,row);
    /*BOOST_SCOPE_EXIT(this_){
        this_->endRemoveRows();
    }BOOST_SCOPE_EXIT_END//*/
    mydata.erase(std::next(mydata.begin(),row));
    endRemoveRows();
    /*
    beginRemoveRows(QModelIndex(),row,row);
    Asset * asset = assetList.at(row);
    bool res = assetList.removeOne(asset);
    if (res)
        delete asset;
    endRemoveRows();
    */
}

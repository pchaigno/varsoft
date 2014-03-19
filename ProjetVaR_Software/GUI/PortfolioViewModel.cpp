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
        return QVariant(mydata[index.row()]);
    }
    return QVariant();
}


QVariant PortfolioViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QList l = new QList();
        l.append("Date");
        l.append("Valeur");
        l.append("Action1");
        return QStringList(l);
    }
    return QAbstractTableModel::headerData(section, orientation, role);
    //renvoyer une QStringlist avec toutes nos strings

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

void PortfolioViewModel::addPortfolio(Portfolio* portfolio)
{
    if(std::find(mydata.begin(),mydata.end(),portfolio)!=mydata.end())
        return;
    beginInsertRows(QModelIndex(),mydata.size(),mydata.size());
    /*BOOST_SCOPE_EXIT(this_){
        this_->endInsertRows();
    }BOOST_SCOPE_EXIT_END*/
    mydata.push_back(std::move(portfolio));
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
    mydata.erase(std::next(mydata.begin(),0));
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

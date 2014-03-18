#ifndef PORTFOLIOVIEWMODEL_H
#define PORTFOLIOVIEWMODEL_H

#include "QAbstractTableModel"
#include "Asset.h"

class PortfolioViewModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef std::vector<QString>::const_iterator const_iterator;
    explicit PortfolioViewModel(QObject *parent = 0);
    enum {DATE=0,VALUE};

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addAsset(Asset* asset)const;
    void removeAsset(Asset* asset)const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    const_iterator begin()const{return data.begin();}
    const_iterator end()const{return data.end();}

private:
    std::vector<Asset*> mydata;
    QList<Asset*> assetList;
};

#endif // PORTFOLIOVIEWMODEL_H

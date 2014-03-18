#ifndef PORTFOLIOITEMMODEL_H
#define PORTFOLIOITEMMODEL_H

#include <QAbstractListModel>
#include "Portfolio.h"

class PortfolioItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PortfolioItemModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void insertPortfolio(Portfolio*portfolio,int row);
    bool removePortfolio(int row);

signals:

public slots:
    void addPortfolio(Portfolio *portfolio);
    bool removePortfolio(Portfolio*portfolio);

private:
    QList<Portfolio*> portfolioList;

};

#endif // PORTFOLIOITEMMODEL_H

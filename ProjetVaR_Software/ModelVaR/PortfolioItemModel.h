#ifndef PORTFOLIOITEMMODEL_H
#define PORTFOLIOITEMMODEL_H

#include <QAbstractListModel>
#include "Portfolio.h"
#include <stdexcept>

#ifdef UNITTEST
class TestPortfolioItemModel;
#endif

class MODELVARSHARED_EXPORT PortfolioItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PortfolioItemModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

#ifdef UNITTEST
 friend class TestPortfolioItemModel;
#endif

signals:

public slots:
    void addPortfolio(Portfolio *portfolio);
    void insertPortfolio(Portfolio*portfolio,int row);

    bool removePortfolio(Portfolio*portfolio);
    bool removePortfolio(int row);

private:
    QList<Portfolio*> portfolioList;

};

#endif // PORTFOLIOITEMMODEL_H

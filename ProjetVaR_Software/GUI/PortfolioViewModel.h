#ifndef PORTFOLIOVIEWMODEL_H
#define PORTFOLIOVIEWMODEL_H

#include "QAbstractTableModel"
#include "Asset.h"


class PortfolioViewModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PortfolioViewModel(QObject *parent = 0);
    explicit PortfolioViewModel(QVector< QVector<QString> >* portfolio, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:
    void addPortfolio(QVector<QVector<QString>> portfolio);
    bool removePortfolio();

private:
    QVector<QVector<QString>> mydata;
};

#endif // PORTFOLIOVIEWMODEL_H

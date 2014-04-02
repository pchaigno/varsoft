#ifndef PORTFOLIOVIEWMODEL_H
#define PORTFOLIOVIEWMODEL_H

#include "QAbstractTableModel"
#include "Asset.h"
#include "Portfolio.h"
#include <QDebug>

class PortfolioViewModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PortfolioViewModel(QObject *parent = 0);
    explicit PortfolioViewModel(Portfolio* portfolio, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setPortfolio(Portfolio * portfolio);

signals:

public slots:

private:
    void createDataStructure();
    Portfolio * portfolio;
    QVector<QString> headers;
    QVector<QDateTime> datesRow;
    QVector<QVector<QString> > mydata;
};

#endif // PORTFOLIOVIEWMODEL_H

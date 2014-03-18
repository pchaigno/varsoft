#ifndef PORTFOLIOLISTVIEW_H
#define PORTFOLIOLISTVIEW_H

#include <QListView>
#include "PortfolioItemModel.h"
#include <QDebug>

class PortfolioListView : public QListView
{
    Q_OBJECT
public:
    explicit PortfolioListView(QWidget *parent = 0);

    void setModel(PortfolioItemModel * model);
    PortfolioItemModel *model();

signals:

public slots:
    void removeSelectedPortfolio();

};

#endif // PORTFOLIOLISTVIEW_H

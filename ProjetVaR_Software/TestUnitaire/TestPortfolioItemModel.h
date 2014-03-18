#ifndef TESTPORTFOLIOITEMMODEL_H
#define TESTPORTFOLIOITEMMODEL_H

#include <QObject>
#include <QtTest>
#include <exception>
#include "PortfolioItemModel.h"

class TestPortfolioItemModel : public QObject
{
    Q_OBJECT
public:
    explicit TestPortfolioItemModel();

signals:

private Q_SLOTS:
    void init();
    void cleanup();
    void testAdd();
    void testInsert();
    void testRemove();
    void testData();


private:
    PortfolioItemModel * model;

};

#endif // TESTPORTFOLIOITEMMODEL_H

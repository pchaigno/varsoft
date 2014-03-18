#include "TestPortfolioItemModel.h"

TestPortfolioItemModel::TestPortfolioItemModel() :
    QObject()
{
}
/**
 * @brief TestPortfolioItemModel::init
 * Create a model before each tests.
 */
void TestPortfolioItemModel::init()
{
    model = new PortfolioItemModel();
}
/**
 * @brief TestPortfolioItemModel::cleanup
 * Delete the model after each tests.
 */
void TestPortfolioItemModel::cleanup()
{
    delete model;
}

/**
 * @brief TestPortfolioItemModel::testAdd
 * Add few portfolio to the model, test the number of portfolios of
 * the private attribute "QList portfolioList" and test the adding of
 * the null pointer.
 */
void TestPortfolioItemModel::testAdd()
{
    QMap<Asset*,int> compo;
    QVector<Report*> reports;
    Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);

    model->addPortfolio(portfolioTest);
    QCOMPARE(model->portfolioList.count(),1);
    model->addPortfolio(portfolioTest);
    model->addPortfolio(portfolioTest);
    model->addPortfolio(portfolioTest);
    QCOMPARE(model->portfolioList.count(),4);

    try
    {
        model->addPortfolio(0);
    } catch (std::exception  & e)
    {
        return;
    }
    QFAIL("NullPointerException not handled.");
}
/**
 * @brief TestPortfolioItemModel::testInsert
 * Add 2 portfolios to the model and insert one in the middle, test it. It's ready =)
 * test also the inserting of a portfolio at row=0 and at the row=count.
 */
void TestPortfolioItemModel::testInsert()
{
    QMap<Asset*,int> compo;
    QVector<Report*> reports;
    Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);

    model->addPortfolio(portfolioTest);
    model->addPortfolio(portfolioTest);

    portfolioTest = new Portfolio(QString("test2"),compo,reports);
    model->insertPortfolio(portfolioTest,1);
    QModelIndex index = model->index(1);
    QVariant data = model->data(index,Qt::DisplayRole);
    QCOMPARE(data.toString(),QString("test2"));

    portfolioTest = new Portfolio(QString("test3"),compo,reports);
    model->insertPortfolio(portfolioTest,0);
    index = model->index(0);
    data = model->data(index,Qt::DisplayRole);
    QCOMPARE(data.toString(),QString("test3"));

    portfolioTest = new Portfolio(QString("test4"),compo,reports);
    model->insertPortfolio(portfolioTest,model->portfolioList.count());
    index = model->index(model->portfolioList.count()-1);
    data = model->data(index,Qt::DisplayRole);
    QCOMPARE(data.toString(),QString("test4"));
}
/**
 * @brief TestPortfolioItemModel::testRemove
 * Add a portfolio, remove it, and the model should be empty.
 */
void TestPortfolioItemModel::testRemove()
{
    QMap<Asset*,int> compo;
    QVector<Report*> reports;
    Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);
    model->addPortfolio(portfolioTest);
    model->removePortfolio(portfolioTest);
    QCOMPARE(model->portfolioList.count(),0);
}
/**
 * @brief TestPortfolioItemModel::testData
 * Add a portfolio, test the first element.
 * Do it again for fun ...
 */
void TestPortfolioItemModel::testData()
{
    QMap<Asset*,int> compo;
    QVector<Report*> reports;
    Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);
    model->addPortfolio(portfolioTest);

    QModelIndex index = model->index(0);
    QVariant data = model->data(index,Qt::DisplayRole);
    QCOMPARE(data.toString(),QString("test"));

    portfolioTest = new Portfolio(QString("test2"),compo,reports);

    model->addPortfolio(portfolioTest);
    index = model->index(1);
    data = model->data(index,Qt::DisplayRole);
    QCOMPARE(data.toString(),QString("test2"));
}

/*
     ____  ____  ____  ____  ____  _________  ____  ____  ____  ____  ____
    ||B ||||e ||||n ||||j ||||i ||||       ||||R ||||o ||||c ||||k ||||s ||
    ||__||||__||||__||||__||||__||||_______||||__||||__||||__||||__||||__||
    |/__\||/__\||/__\||/__\||/__\||/_______\||/__\||/__\||/__\||/__\||/__\|
*/

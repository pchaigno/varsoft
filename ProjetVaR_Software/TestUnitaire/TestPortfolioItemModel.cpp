/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "TestPortfolioItemModel.h"

TestPortfolioItemModel::TestPortfolioItemModel(): QObject() {

}

/**
 * @brief Create a model before each tests.
 */
void TestPortfolioItemModel::init() {
	model = new PortfolioItemModel();
}

/**
 * @brief Delete the model after each tests.
 */
void TestPortfolioItemModel::cleanup() {
	delete model;
}

/**
 * @brief Add few portfolio to the model, test the number of portfolios of
 * the private attribute "QList portfolioList" and test the adding of
 * the null pointer.
 */
void TestPortfolioItemModel::testAdd() {
	QMap<Asset*,int> compo;
	QVector<Report*> reports;
	Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);

	model->addPortfolio(portfolioTest);
	QCOMPARE(model->portfolioList.count(),1);
	model->addPortfolio(portfolioTest);
	model->addPortfolio(portfolioTest);
	model->addPortfolio(portfolioTest);
	QCOMPARE(model->portfolioList.count(),4);

	// test add null pointer
	try {
		model->addPortfolio(0);
	} catch (std::exception  & e) {
		return;
	}
	QFAIL("NullPointerException not handled.");
}

/**
 * @brief Add 2 portfolios to the model and insert one in the middle, test it. It's ready =)
 * test also the inserting of a portfolio at row=0 and at the row=count.
 */
void TestPortfolioItemModel::testInsert() {
	QMap<Asset*,int> compo;
	QVector<Report*> reports;
	Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);

	model->addPortfolio(portfolioTest);
	model->addPortfolio(portfolioTest);

	//test insert in the middle
	portfolioTest = new Portfolio(QString("test2"),compo,reports);
	model->insertPortfolio(portfolioTest,1);
	QModelIndex index = model->index(1);
	QVariant data = model->data(index,Qt::DisplayRole);
	QCOMPARE(data.toString(),QString("test2"));

	//test insert at the beginning
	portfolioTest = new Portfolio(QString("test3"),compo,reports);
	model->insertPortfolio(portfolioTest,0);
	index = model->index(0);
	data = model->data(index,Qt::DisplayRole);
	QCOMPARE(data.toString(),QString("test3"));

	//test insert at the end
	portfolioTest = new Portfolio(QString("test4"),compo,reports);
	model->insertPortfolio(portfolioTest,model->portfolioList.count());
	index = model->index(model->portfolioList.count()-1);
	data = model->data(index,Qt::DisplayRole);
	QCOMPARE(data.toString(),QString("test4"));

	//test insert null pointer
	bool success=false;
	try {
		model->insertPortfolio(0,1);
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("NullPointerException not handled.");
	}

	//test insert after the end (count+1)
	success=false;
	try {
		portfolioTest = new Portfolio(QString("test5"),compo,reports);
		model->insertPortfolio(portfolioTest,model->portfolioList.count()+1);
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("Row error not handled.");
	}

	//test insert negative row
	success=false;
	try {
		portfolioTest = new Portfolio(QString("test5"),compo,reports);
		model->insertPortfolio(portfolioTest,-1);
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("Row error not handled.");
	}
}

/**
 * @brief Add a portfolio, remove it, and the model should be empty.
 */
void TestPortfolioItemModel::testRemove() {
	QMap<Asset*,int> compo;
	QVector<Report*> reports;
	Portfolio* portfolioTest = new Portfolio(QString("test"),compo,reports);
	model->addPortfolio(portfolioTest);
	model->removePortfolio(portfolioTest);
	QCOMPARE(model->portfolioList.count(),0);


	model->addPortfolio(portfolioTest);
	model->addPortfolio(portfolioTest);

	//test remove null pointer
	bool success=false;
	try {
		model->removePortfolio((Portfolio*)0);
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("NullPointerException not handled.");
	}

	//test remove after the end
	success=false;
	try {
		model->removePortfolio(model->portfolioList.count());
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("Row error not handled.");
	}

	//test remove negative row
	success=false;
	try	{
		model->removePortfolio(-1);
	} catch (std::exception  & e) {
		success=true;
	}
	if (!success) {
		QFAIL("Row error not handled.");
	}
}
/**
 * @brief Add a portfolio, test the first element.
 * Do it again for fun ...
 */
void TestPortfolioItemModel::testData() {
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

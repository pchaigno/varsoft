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
#include "NewPortfolioWizard.h"
#include "ui_NewPortfolioWizard.h"

NewPortfolioWizard::NewPortfolioWizard(QWidget *parent) :
	QWizard(parent), ui(new Ui::NewPortfolioWizard) {
	ui->setupUi(this);
	showAssetPage = new ShowAssetsWizardPage(this);
	setWeightPage = new SetWeightAssetWizardPage(this);
	this->addPage(showAssetPage);
	this->addPage(setWeightPage);
}

NewPortfolioWizard::~NewPortfolioWizard() {
	delete ui;
	delete showAssetPage;
	delete setWeightPage;
}

/**
 * @brief Call when the user press the valid button.
 * Create the portfolio and emit the signal newPortfolioCreated(Portfolio* portfolioCreated)
 */
void NewPortfolioWizard::accept() {
	QMap<Asset*,int> composition;
	QMap<QString, Asset*> assetsMap = SessionBuilder::getInstance()->buildAssets();
	QMap<QString,int> weightsByName = setWeightPage->getWeights();

	foreach (const QString &str, weightsByName.keys()) {
		composition[assetsMap[str]]=weightsByName[str];
	}

	QVector<Report*> report;
	Portfolio * portfolio = new Portfolio(field("name").toString(),composition,report);
	emit newPortfolioCreated(portfolio);
	this->QWizard::accept();
}

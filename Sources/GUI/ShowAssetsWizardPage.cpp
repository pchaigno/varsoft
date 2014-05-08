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
#include "ShowAssetsWizardPage.h"
#include "ui_ShowAssetsWizardPage.h"

ShowAssetsWizardPage::ShowAssetsWizardPage(QWidget *parent) :
	QWizardPage(parent), ui(new Ui::ShowAssetsWizardPage) {
	ui->setupUi(this);

	setupAssets();

	connect(ui->allLeftButton,SIGNAL(clicked()),this,SLOT(allLeftButtonClicked()));
	connect(ui->allRightButton,SIGNAL(clicked()),this,SLOT(allRightButtonClicked()));
	connect(ui->rightButton,SIGNAL(clicked()),this,SLOT(rightButtonClicked()));
	connect(ui->leftButton,SIGNAL(clicked()),this,SLOT(leftButtonClicked()));

	connect(ui->nameLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(completeChanged()));
}

ShowAssetsWizardPage::~ShowAssetsWizardPage() {
	delete ui;
}

/**
 * @brief Registre the field name and the right list of Assets.
 */
void ShowAssetsWizardPage::initializePage() {
	registerField("name*",ui->nameLineEdit);
	registerField("listAssets",ui->rightAssets);
}

/**
 * @brief Clear then fill the listView on the left with the list of assets from the DB
 */
void ShowAssetsWizardPage::setupAssets() {
	ui->leftAssets->clear();

	QMap<QString, Asset*> assetsMap = SessionBuilder::getInstance()->buildAssets();

	QMap<QString, Asset*>::iterator it;
	for (it = assetsMap.begin(); it != assetsMap.end(); ++it) {
		ui->leftAssets->addItem(it.key());
	}
}

/**
 * @brief Check if the user has entered a name for the portfolio and has selected Assets.
 * @return true if the user has entered a name and selected assets, false otherwise.
 */
bool ShowAssetsWizardPage::isComplete() const {
	if (!ui->nameLineEdit->text().isEmpty() && ui->rightAssets->count()>0) {
		return true;
	}
	return false;
}

/**
 * @brief Return a QList with the Assets's name selected (in the right list).
 * @return A QList fill with QString of Assets's name.
 */
QList<QString> ShowAssetsWizardPage::getListAssetsSelected() const {
	QList<QString> res;
	for(int i = 0; i < ui->rightAssets->count(); ++i) {
		res << ui->rightAssets->item(i)->text();
	}
	return res;
}

/**
 * @brief Copy the right list of assets to the left list and clear the right list.
 */
void ShowAssetsWizardPage::allLeftButtonClicked() {
	for(int i = 0; i < ui->rightAssets->count(); ++i) {
		QListWidgetItem* item = ui->rightAssets->item(i);
		ui->leftAssets->addItem(item->text());
	}
	ui->rightAssets->clear();
	emit completeChanged();
}

/**
 * @brief Copy the left list of assets to the right list and clear the left list.
 */
void ShowAssetsWizardPage::allRightButtonClicked() {
	for(int i = 0; i < ui->leftAssets->count(); ++i) {
		QListWidgetItem* item = ui->leftAssets->item(i);
		ui->rightAssets->addItem(item->text());
	}
	ui->leftAssets->clear();
	emit completeChanged();
}

/**
 * @brief Add the selected items from the left list of assets to the right list and remove it in the left list.
 */
void ShowAssetsWizardPage::rightButtonClicked() {
	QList<QListWidgetItem *> itemsSelected = ui->leftAssets->selectedItems();
	for(int i = 0; i < itemsSelected.count(); i++) {
		if (ui->rightAssets->findItems(itemsSelected.at(i)->text(),Qt::MatchExactly).count()==0) {
			ui->rightAssets->addItem(itemsSelected.at(i)->text());
			delete itemsSelected.at(i);
		}
	}
	emit completeChanged();
}

/**
 * @brief Add the selected items from the right list of assets to the left list and remove it in the right list.
 */
void ShowAssetsWizardPage::leftButtonClicked() {
	QList<QListWidgetItem *> itemsSelected = ui->rightAssets->selectedItems();
	for(int i = 0; i < itemsSelected.count(); i++) {
		if (ui->leftAssets->findItems(itemsSelected.at(i)->text(),Qt::MatchExactly).count()==0) {
			ui->leftAssets->addItem(itemsSelected.at(i)->text());
			delete itemsSelected.at(i);
		}
	}
	emit completeChanged();
}

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
#include "SetWeightAssetWizardPage.h"
#include "ui_SetWeightAssetWizardPage.h"

SetWeightAssetWizardPage::SetWeightAssetWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SetWeightAssetWizardPage)
{
    ui->setupUi(this);
}

SetWeightAssetWizardPage::~SetWeightAssetWizardPage()
{
    delete ui;
}
/**
 * @brief Load the formLayout with the list of the selected assets.
 */
void SetWeightAssetWizardPage::initializePage()
{
    QList<QString> listAssets = getAssetsSelected();
    foreach(QString str, listAssets)
    {
        QSpinBox* spinBox = new QSpinBox();
        weights[str]=spinBox;
        ui->weightFormLayout->addRow(str,spinBox);
    }
}
/**
 * @brief Clear the formLayout
 */
void SetWeightAssetWizardPage::cleanupPage()
{
    weights.clear();
    clearLayout(ui->weightFormLayout);
}

/**
 * @brief Clear the specified layout.
 * @param layout The layout to clear.
 * @param deleteWidgets If true, it delete widgets in the layout, otherwise it just clear the layout without call delete on widgets. True by default.
 */
void SetWeightAssetWizardPage::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

/**
 * @brief Retrieve the list of the assets selected in the previous page of the wizard.
 * @return QList of String
 */
QList<QString> SetWeightAssetWizardPage::getAssetsSelected() const
{
    return qobject_cast<ShowAssetsWizardPage *>(wizard()->page(wizard()->startId()))->getListAssetsSelected();
}

/**
 * @brief Retrieve the weights entered by the user in a map.
 * @return a map with the weights associate to the name of the asset
 */
QMap<QString, int> SetWeightAssetWizardPage::getWeights() const
{
    QMap<QString, int>  res;
    foreach (const QString &str, weights.keys())
    {
        res[str]=weights.value(str)->value();
    }
    return res;
}


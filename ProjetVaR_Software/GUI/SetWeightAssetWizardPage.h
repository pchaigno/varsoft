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
#ifndef SETWEIGHTASSETWIZARDPAGE_H
#define SETWEIGHTASSETWIZARDPAGE_H

#include <QWizardPage>
#include <QDebug>
#include <QListWidget>
#include "ShowAssetsWizardPage.h"
#include <QSpinBox>
#include <QMap>
#include <QSignalMapper>

namespace Ui {
class SetWeightAssetWizardPage;
}

class SetWeightAssetWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SetWeightAssetWizardPage(QWidget *parent = 0);
    ~SetWeightAssetWizardPage();

    void initializePage();
    void cleanupPage();
    QList<QString> getAssetsSelected() const;
    QMap<QString,int> getWeights() const;

private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    QMap<QString,QSpinBox*> weights;
    Ui::SetWeightAssetWizardPage *ui;
};

#endif // SETWEIGHTASSETWIZARDPAGE_H

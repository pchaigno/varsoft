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
    QList<QString> getAssetsSelected();

    QMap<QString,int> getWeights();


private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    QMap<QString,QSpinBox*> weights;

    QSignalMapper * mapper;

    Ui::SetWeightAssetWizardPage *ui;
};

#endif // SETWEIGHTASSETWIZARDPAGE_H
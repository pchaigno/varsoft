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

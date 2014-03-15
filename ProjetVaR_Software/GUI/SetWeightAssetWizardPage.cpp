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
 * @brief SetWeightAssetWizardPage::initializePage
 * Load the formLayout with the list of the selected assets.
 */
void SetWeightAssetWizardPage::initializePage()
{
    QList<QString> listAssets = getAssetsSelected();
    foreach(QString str, listAssets)
        ui->weightFormLayout->addRow(str,new QDoubleSpinBox());
}
/**
 * @brief SetWeightAssetWizardPage::cleanupPage
 * Clear the formLayout
 */
void SetWeightAssetWizardPage::cleanupPage()
{
    clearLayout(ui->weightFormLayout);
}

/**
 * @brief SetWeightAssetWizardPage::clearLayout
 * Clear the specified layout.
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
 * @brief SetWeightAssetWizardPage::getAssetsSelected
 * Retrieve the list of the assets selected in the previous page of the wizard.
 * @return QList of String
 */
QList<QString> SetWeightAssetWizardPage::getAssetsSelected()
{
    return qobject_cast<ShowAssetsWizardPage *>(wizard()->page(wizard()->startId()))->getListAssetsSelected();
}

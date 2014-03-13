#include "NewPortfolioWizard.h"
#include "ui_NewPortfolioWizard.h"

NewPortfolioWizard::NewPortfolioWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewPortfolioWizard)
{
    ui->setupUi(this);
    setupAssets();
}

NewPortfolioWizard::~NewPortfolioWizard()
{
    delete ui;
}
/**
 * @brief NewPortfolioWizard::setupAssets
 * clear then fill the listView on the left with the list of assets from the DB
 */
void NewPortfolioWizard::setupAssets()
{
    ui->leftAssets->clear();

    QMap<QString, Asset*> assetsMap = SessionBuilder::getInstance()->buildAssets();

    QMap<QString, Asset*>::iterator it;
    for (it = assetsMap.begin(); it != assetsMap.end(); ++it)
    {
        ui->leftAssets->addItem(it.key());
    }
}

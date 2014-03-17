#include "NewPortfolioWizard.h"
#include "ui_NewPortfolioWizard.h"

NewPortfolioWizard::NewPortfolioWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewPortfolioWizard)
{
    ui->setupUi(this);
    showAssetPage = new ShowAssetsWizardPage(this);
    setWeightPage = new SetWeightAssetWizardPage(this);
    this->addPage(showAssetPage);
    this->addPage(setWeightPage);
}

NewPortfolioWizard::~NewPortfolioWizard()
{
    delete ui;
    delete showAssetPage;
    delete setWeightPage;
}

void NewPortfolioWizard::accept()
{
    QMap<Asset*,int> composition;
    QMap<QString, Asset*> assetsMap = SessionBuilder::getInstance()->buildAssets();
    QMap<QString,int> weightsByName = setWeightPage->getWeights();

    foreach (const QString &str, weightsByName.keys())
    {
        composition[assetsMap[str]]=weightsByName[str];
    }

    QVector<Report*> report;
    Portfolio * portfolio = new Portfolio(field("name").toString(),composition,report);
    emit newPortfolioCreated(portfolio);
    this->QWizard::accept();
}


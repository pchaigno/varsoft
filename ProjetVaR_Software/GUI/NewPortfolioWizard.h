#ifndef NEWPORTFOLIOWIZARD_H
#define NEWPORTFOLIOWIZARD_H

#include <QWizard>
#include "ShowAssetsWizardPage.h"
#include "SetWeightAssetWizardPage.h"
#include "Portfolio.h"

namespace Ui {
class NewPortfolioWizard;
}

class NewPortfolioWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewPortfolioWizard(QWidget *parent = 0);
    ~NewPortfolioWizard();

    void accept();

signals:
    void newPortfolioCreated(Portfolio *);


private:
    Ui::NewPortfolioWizard *ui;
    ShowAssetsWizardPage *showAssetPage;
    SetWeightAssetWizardPage * setWeightPage;
};

#endif // NEWPORTFOLIOWIZARD_H

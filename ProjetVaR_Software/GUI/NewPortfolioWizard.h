#ifndef NEWPORTFOLIOWIZARD_H
#define NEWPORTFOLIOWIZARD_H

#include <QWizard>
#include "ShowAssetsWizardPage.h"
#include "SetWeightAssetWizardPage.h"

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


private:
    Ui::NewPortfolioWizard *ui;
};

#endif // NEWPORTFOLIOWIZARD_H

#ifndef SETWEIGHTASSETWIZARDPAGE_H
#define SETWEIGHTASSETWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class SetWeightAssetWizardPage;
}

class SetWeightAssetWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SetWeightAssetWizardPage(QWidget *parent = 0);
    ~SetWeightAssetWizardPage();

private:
    Ui::SetWeightAssetWizardPage *ui;
};

#endif // SETWEIGHTASSETWIZARDPAGE_H

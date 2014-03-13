#include "NewPortfolioWizard.h"
#include "ui_NewPortfolioWizard.h"

NewPortfolioWizard::NewPortfolioWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewPortfolioWizard)
{
    ui->setupUi(this);
}

NewPortfolioWizard::~NewPortfolioWizard()
{
    delete ui;
}

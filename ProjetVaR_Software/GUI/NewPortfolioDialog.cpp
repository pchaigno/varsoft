#include "NewPortfolioDialog.h"
#include "ui_NewPortfolioDialog.h"

NewPortfolioDialog::NewPortfolioDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPortfolioDialog)
{
    ui->setupUi(this);
}

NewPortfolioDialog::~NewPortfolioDialog()
{
    delete ui;
}

#ifndef NEWPORTFOLIODIALOG_H
#define NEWPORTFOLIODIALOG_H

#include <QDialog>

namespace Ui {
class NewPortfolioDialog;
}

class NewPortfolioDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPortfolioDialog(QWidget *parent = 0);
    ~NewPortfolioDialog();

private:
    Ui::NewPortfolioDialog *ui;
};

#endif // NEWPORTFOLIODIALOG_H

#ifndef DOCXGENPATHDIALOG_H
#define DOCXGENPATHDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QFileDialog>

namespace Ui {
class DocxGenPathDialog;
}

class DocxGenPathDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DocxGenPathDialog(QWidget *parent = 0);
	~DocxGenPathDialog();

public slots:
	void browse();
	void accept();

private:
	Ui::DocxGenPathDialog *ui;
};

#endif // DOCXGENPATHDIALOG_H

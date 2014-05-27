/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.
 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VARDIALOG_H
#define VARDIALOG_H

#include <QDialog>
#include "Portfolio.h"
#include "QMessageBox"
#include "Constantes.h"
#include "reportFactory/VaRReportFactory.h"
#include "reportFactory/GarchReportFactory.h"
#include "math/GarchModel.h"
#include "math/VaRAlgorithm.h"
#include "math/VaRGarch.h"
#include "math/VaRHistorical.h"
#include "math/VaRRiskmetrics.h"
#include "math/RInterface.h"

namespace Ui {
class VarDialog;
}

class VarDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit VarDialog(Portfolio * portfolio, QWidget *parent = 0);
	~VarDialog();
	
public slots:
	void accept();
private:
	void initDates();

	Ui::VarDialog *ui;
	Portfolio * portfolio;
};

#endif // VARDIALOG_H

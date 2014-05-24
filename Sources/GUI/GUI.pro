#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:16
#
#-------------------------------------------------

QT += core gui printsupport sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

GTCONFIG +=console

TARGET = GUI
TEMPLATE = app

SOURCES += main.cpp\
		MainWindow.cpp \
		NewPortfolioWizard.cpp \
		SetWeightAssetWizardPage.cpp \
		ShowAssetsWizardPage.cpp \
		PortfolioListView.cpp \
		ReportWidget.cpp \
		FlowLayout.cpp \
		ReportWidgetFactory.cpp \
		DocxGenPathDialog.cpp \
		ImportDialog.cpp \
		ReportListScrollArea.cpp

HEADERS += MainWindow.h \
		NewPortfolioWizard.h \
		SetWeightAssetWizardPage.h \
		ShowAssetsWizardPage.h \
		PortfolioListView.h \
		NoneSelectedPortfolioException.h \
		ReportWidget.h \
		FlowLayout.h \
		ReportWidgetFactory.h \
		DocxGenPathDialog.h \
		Constantes.h \
		ImportDialog.h \
		ReportListScrollArea.h

FORMS += MainWindow.ui \
		NewPortfolioWizard.ui \
		SetWeightAssetWizardPage.ui \
		ShowAssetsWizardPage.ui\
		import.ui \
		ReportWidget.ui \
		DocxGenPathDialog.ui \
		ReportListScrollArea.ui



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR

RESOURCES += \
	Resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/release/ -lqcustomplotd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/debug/ -lqcustomplotd
else:unix: LIBS += -L$$OUT_PWD/../qcustomplot/ -lqcustomplotd

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

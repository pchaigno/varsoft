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
    qcustomplot.cpp \
    import.cpp \
    NewPortfolioWizard.cpp \
    SetWeightAssetWizardPage.cpp \
    ShowAssetsWizardPage.cpp \
    PortfolioListView.cpp \

HEADERS  += MainWindow.h \
    qcustomplot.h \
    NewPortfolioWizard.h \
    SetWeightAssetWizardPage.h \
    ShowAssetsWizardPage.h \
    PortfolioListView.h \
    PortfolioViewModel.h \
    import.h

FORMS    += MainWindow.ui \
    NewPortfolioWizard.ui \
    SetWeightAssetWizardPage.ui \
    ShowAssetsWizardPage.ui\
    import.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR

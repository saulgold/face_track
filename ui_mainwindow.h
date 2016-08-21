/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *webcam_label;
    QPushButton *selectFileButton;
    QLabel *skinLabel;
    QCustomPlot *chart_FFT;
    QPushButton *saveDataButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(979, 532);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        webcam_label = new QLabel(centralWidget);
        webcam_label->setObjectName(QStringLiteral("webcam_label"));
        webcam_label->setGeometry(QRect(20, 20, 671, 461));
        selectFileButton = new QPushButton(centralWidget);
        selectFileButton->setObjectName(QStringLiteral("selectFileButton"));
        selectFileButton->setGeometry(QRect(720, 10, 75, 23));
        skinLabel = new QLabel(centralWidget);
        skinLabel->setObjectName(QStringLiteral("skinLabel"));
        skinLabel->setGeometry(QRect(700, 130, 81, 71));
        chart_FFT = new QCustomPlot(centralWidget);
        chart_FFT->setObjectName(QStringLiteral("chart_FFT"));
        chart_FFT->setGeometry(QRect(0, 20, 671, 191));
        saveDataButton = new QPushButton(centralWidget);
        saveDataButton->setObjectName(QStringLiteral("saveDataButton"));
        saveDataButton->setGeometry(QRect(720, 40, 80, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 979, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        webcam_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        selectFileButton->setText(QApplication::translate("MainWindow", "select file", 0));
        skinLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        saveDataButton->setText(QApplication::translate("MainWindow", "save data", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

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
#include <QtWidgets/QLCDNumber>
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
    QCustomPlot *chart_FFT;
    QPushButton *saveDataButton;
    QLCDNumber *lcd_tracked;
    QLabel *label;
    QPushButton *playButton;
    QLabel *label_3;
    QPushButton *pushButton;
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
        chart_FFT = new QCustomPlot(centralWidget);
        chart_FFT->setObjectName(QStringLiteral("chart_FFT"));
        chart_FFT->setGeometry(QRect(0, 20, 671, 191));
        saveDataButton = new QPushButton(centralWidget);
        saveDataButton->setObjectName(QStringLiteral("saveDataButton"));
        saveDataButton->setGeometry(QRect(720, 40, 80, 21));
        lcd_tracked = new QLCDNumber(centralWidget);
        lcd_tracked->setObjectName(QStringLiteral("lcd_tracked"));
        lcd_tracked->setGeometry(QRect(810, 170, 141, 101));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(720, 170, 91, 101));
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(720, 80, 80, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(590, 470, 47, 13));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(730, 410, 80, 21));
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
        saveDataButton->setText(QApplication::translate("MainWindow", "save data", 0));
        label->setText(QApplication::translate("MainWindow", "Heart Rate/BPM", 0));
        playButton->setText(QApplication::translate("MainWindow", "PLAY", 0));
        label_3->setText(QApplication::translate("MainWindow", "tracked", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

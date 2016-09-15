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
    QLabel *skinLabel;
    QCustomPlot *chart_FFT;
    QPushButton *saveDataButton;
    QLCDNumber *lcd_tracked;
    QLabel *label;
    QLabel *tick_label;
    QLCDNumber *tick_freq_lcd;
    QPushButton *playButton;
    QLCDNumber *lcd_static;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *lcd_time;
    QLabel *label_5;
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
        lcd_tracked = new QLCDNumber(centralWidget);
        lcd_tracked->setObjectName(QStringLiteral("lcd_tracked"));
        lcd_tracked->setGeometry(QRect(330, 270, 141, 101));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 270, 91, 101));
        tick_label = new QLabel(centralWidget);
        tick_label->setObjectName(QStringLiteral("tick_label"));
        tick_label->setGeometry(QRect(680, 210, 81, 20));
        tick_freq_lcd = new QLCDNumber(centralWidget);
        tick_freq_lcd->setObjectName(QStringLiteral("tick_freq_lcd"));
        tick_freq_lcd->setGeometry(QRect(760, 210, 151, 23));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush2(QColor(255, 255, 220, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        tick_freq_lcd->setPalette(palette);
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(720, 80, 80, 21));
        lcd_static = new QLCDNumber(centralWidget);
        lcd_static->setObjectName(QStringLiteral("lcd_static"));
        lcd_static->setGeometry(QRect(500, 270, 141, 101));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(380, 380, 47, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(590, 470, 47, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(550, 380, 47, 13));
        lcd_time = new QLCDNumber(centralWidget);
        lcd_time->setObjectName(QStringLiteral("lcd_time"));
        lcd_time->setGeometry(QRect(710, 270, 141, 101));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(760, 380, 47, 13));
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
        label->setText(QApplication::translate("MainWindow", "Heart Rate/BPM", 0));
        tick_label->setText(QApplication::translate("MainWindow", "tick frequency", 0));
        playButton->setText(QApplication::translate("MainWindow", "PLAY", 0));
        label_2->setText(QApplication::translate("MainWindow", "tracked", 0));
        label_3->setText(QApplication::translate("MainWindow", "tracked", 0));
        label_4->setText(QApplication::translate("MainWindow", "static", 0));
        label_5->setText(QApplication::translate("MainWindow", "time ms", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

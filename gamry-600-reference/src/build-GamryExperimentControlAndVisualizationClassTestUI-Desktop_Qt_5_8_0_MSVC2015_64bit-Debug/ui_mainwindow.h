/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gamrywidget.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *controGroupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEditVinit;
    QLabel *label_2;
    QLineEdit *lineEditTinit;
    QLabel *label_3;
    QLineEdit *lineEditVfinal;
    QLabel *label_4;
    QLineEdit *lineEditTfinal;
    QLabel *SampleRate;
    QLineEdit *lineEditSampleRate;
    QPushButton *startStopButton;
    Gamry::GamryWidget *gamryWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(854, 432);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        controGroupBox = new QGroupBox(centralWidget);
        controGroupBox->setObjectName(QStringLiteral("controGroupBox"));
        controGroupBox->setEnabled(false);
        controGroupBox->setGeometry(QRect(10, 10, 161, 361));
        verticalLayoutWidget = new QWidget(controGroupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 20, 91, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEditVinit = new QLineEdit(verticalLayoutWidget);
        lineEditVinit->setObjectName(QStringLiteral("lineEditVinit"));

        verticalLayout->addWidget(lineEditVinit);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEditTinit = new QLineEdit(verticalLayoutWidget);
        lineEditTinit->setObjectName(QStringLiteral("lineEditTinit"));

        verticalLayout->addWidget(lineEditTinit);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        lineEditVfinal = new QLineEdit(verticalLayoutWidget);
        lineEditVfinal->setObjectName(QStringLiteral("lineEditVfinal"));

        verticalLayout->addWidget(lineEditVfinal);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        lineEditTfinal = new QLineEdit(verticalLayoutWidget);
        lineEditTfinal->setObjectName(QStringLiteral("lineEditTfinal"));

        verticalLayout->addWidget(lineEditTfinal);

        SampleRate = new QLabel(verticalLayoutWidget);
        SampleRate->setObjectName(QStringLiteral("SampleRate"));

        verticalLayout->addWidget(SampleRate);

        lineEditSampleRate = new QLineEdit(verticalLayoutWidget);
        lineEditSampleRate->setObjectName(QStringLiteral("lineEditSampleRate"));

        verticalLayout->addWidget(lineEditSampleRate);

        startStopButton = new QPushButton(controGroupBox);
        startStopButton->setObjectName(QStringLiteral("startStopButton"));
        startStopButton->setGeometry(QRect(10, 270, 141, 23));
        gamryWidget = new Gamry::GamryWidget(centralWidget);
        gamryWidget->setObjectName(QStringLiteral("gamryWidget"));
        gamryWidget->setGeometry(QRect(180, 20, 661, 351));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        controGroupBox->setTitle(QApplication::translate("MainWindow", "Control", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Voltage Intial", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Time Intial", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Voltage Final", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Time Final", Q_NULLPTR));
        SampleRate->setText(QApplication::translate("MainWindow", "SampleRate", Q_NULLPTR));
        startStopButton->setText(QApplication::translate("MainWindow", "PotentioStat  not Detected", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

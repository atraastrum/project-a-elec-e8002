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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Guide;
    QAction *About;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *Start;
    QPushButton *Exit;
    QGroupBox *ChoosingValve;
    QPushButton *Valve1;
    QPushButton *Valve2;
    QGroupBox *MotorSpeed;
    QScrollBar *scrollBar;
    QSpinBox *spinBox;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 400);
        MainWindow->setStyleSheet(QLatin1String("#centralWidget\n"
"{ background-color: #ffc99c; }\n"
"QPushButton\n"
"{\n"
"font: 87 14pt \"Arial\";\n"
"color:white;\n"
"border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 1px;\n"
"background: rgb(0, 170, 255) ;	\n"
"}\n"
"QPushButton:hover {background-color: #1aff6e;}\n"
"QPushButton#Valve1\n"
"{\n"
"font: 87 14pt \"Arial\";}\n"
"QPushButton#Valve2\n"
"{\n"
"font: 87 14pt \"Arial\";}\n"
"QGroupBox\n"
"{font: 75 9pt \"Cambria\";border: 1px solid black;}\n"
""));
        Guide = new QAction(MainWindow);
        Guide->setObjectName(QStringLiteral("Guide"));
        About = new QAction(MainWindow);
        About->setObjectName(QStringLiteral("About"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 30, 61, 71));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Start = new QPushButton(gridLayoutWidget);
        Start->setObjectName(QStringLiteral("Start"));

        gridLayout->addWidget(Start, 0, 0, 1, 1);

        Exit = new QPushButton(gridLayoutWidget);
        Exit->setObjectName(QStringLiteral("Exit"));

        gridLayout->addWidget(Exit, 1, 0, 1, 1);

        ChoosingValve = new QGroupBox(centralWidget);
        ChoosingValve->setObjectName(QStringLiteral("ChoosingValve"));
        ChoosingValve->setGeometry(QRect(110, 20, 110, 80));
        Valve1 = new QPushButton(ChoosingValve);
        Valve1->setObjectName(QStringLiteral("Valve1"));
        Valve1->setGeometry(QRect(20, 20, 75, 23));
        Valve2 = new QPushButton(ChoosingValve);
        Valve2->setObjectName(QStringLiteral("Valve2"));
        Valve2->setGeometry(QRect(20, 50, 75, 23));
        MotorSpeed = new QGroupBox(centralWidget);
        MotorSpeed->setObjectName(QStringLiteral("MotorSpeed"));
        MotorSpeed->setGeometry(QRect(240, 20, 191, 80));
        scrollBar = new QScrollBar(MotorSpeed);
        scrollBar->setObjectName(QStringLiteral("scrollBar"));
        scrollBar->setGeometry(QRect(10, 20, 171, 16));
        scrollBar->setMaximum(200);
        scrollBar->setValue(100);
        scrollBar->setOrientation(Qt::Horizontal);
        spinBox = new QSpinBox(MotorSpeed);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(70, 47, 61, 22));
        spinBox->setMaximum(200);
        spinBox->setValue(100);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 23));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(Guide);
        menuHelp->addSeparator();
        menuHelp->addAction(About);

        retranslateUi(MainWindow);
        QObject::connect(scrollBar, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), scrollBar, SLOT(setValue(int)));
        QObject::connect(Exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FIA Test Bed", Q_NULLPTR));
        Guide->setText(QApplication::translate("MainWindow", "Guide", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        Guide->setStatusTip(QApplication::translate("MainWindow", "User Guide", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        About->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        About->setStatusTip(QApplication::translate("MainWindow", "About the FIA Test Bed", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        Start->setText(QApplication::translate("MainWindow", "Start ", Q_NULLPTR));
        Exit->setText(QApplication::translate("MainWindow", "Exit ", Q_NULLPTR));
        ChoosingValve->setTitle(QApplication::translate("MainWindow", "Choosing Valve", Q_NULLPTR));
        Valve1->setText(QApplication::translate("MainWindow", "Valve1", Q_NULLPTR));
        Valve2->setText(QApplication::translate("MainWindow", "Valve2", Q_NULLPTR));
        MotorSpeed->setTitle(QApplication::translate("MainWindow", "Motor Speed", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

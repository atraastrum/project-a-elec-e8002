# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'test.ui'
#
# Created by: PyQt5 UI code generator 5.6
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(500, 400)
        MainWindow.setMinimumSize(QtCore.QSize(500, 400))
        MainWindow.setMaximumSize(QtCore.QSize(500, 400))
        MainWindow.setStyleSheet("#centralwidget\n"
"{ background-color: rgb(255, 178, 173);}\n"
"QPushButton\n"
"{\n"
"font: 87 14pt \"Arial\";\n"
"color:white;\n"
"border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 1px;\n"
"background: rgb(0, 170, 255) ;    \n"
"}\n"
"QPushButton:hover {background-color: rgb(60, 255, 115); }\n"
"QPushButton#Valve1\n"
"{\n"
"font: 87 13pt \"Arial\";}\n"
"QPushButton#Valve2\n"
"{\n"
"font: 87 13pt \"Arial\";}\n"
"QGroupBox\n"
"{font: 75 9pt \"Cambria\";border: 1px solid black;}\n"
"\n"
"\n"
"\n"
"")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.ChooseValve = QtWidgets.QGroupBox(self.centralwidget)
        self.ChooseValve.setGeometry(QtCore.QRect(119, 40, 111, 80))
        self.ChooseValve.setObjectName("ChooseValve")
        self.Valve1 = QtWidgets.QPushButton(self.ChooseValve)
        self.Valve1.setGeometry(QtCore.QRect(14, 20, 81, 23))
        self.Valve1.setObjectName("Valve1")
        self.Valve2 = QtWidgets.QPushButton(self.ChooseValve)
        self.Valve2.setGeometry(QtCore.QRect(14, 50, 81, 23))
        self.Valve2.setObjectName("Valve2")
        self.MotorSpeed = QtWidgets.QGroupBox(self.centralwidget)
        self.MotorSpeed.setGeometry(QtCore.QRect(259, 40, 191, 80))
        self.MotorSpeed.setObjectName("MotorSpeed")
        self.scrollBar = QtWidgets.QScrollBar(self.MotorSpeed)
        self.scrollBar.setGeometry(QtCore.QRect(10, 20, 171, 16))
        self.scrollBar.setMaximum(200)
        self.scrollBar.setProperty("value", 100)
        self.scrollBar.setOrientation(QtCore.Qt.Horizontal)
        self.scrollBar.setObjectName("scrollBar")
        self.spinBox = QtWidgets.QSpinBox(self.MotorSpeed)
        self.spinBox.setGeometry(QtCore.QRect(70, 50, 61, 22))
        self.spinBox.setMaximum(200)
        self.spinBox.setProperty("value", 100)
        self.spinBox.setObjectName("spinBox")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(40, 49, 61, 71))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.Start = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.Start.setObjectName("Start")
        self.gridLayout.addWidget(self.Start, 0, 0, 1, 1)
        self.Exit = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.Exit.setObjectName("Exit")
        self.gridLayout.addWidget(self.Exit, 1, 0, 1, 1)
        self.SystemTime = QtWidgets.QLabel(self.centralwidget)
        self.SystemTime.setGeometry(QtCore.QRect(10, 340, 180, 20))
        self.SystemTime.setObjectName("SystemTime")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 500, 23))
        self.menubar.setObjectName("menubar")
        self.menuHelp = QtWidgets.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.Guide = QtWidgets.QAction(MainWindow)
        self.Guide.setObjectName("Guide")
        self.About = QtWidgets.QAction(MainWindow)
        self.About.setObjectName("About")
        self.menuHelp.addAction(self.Guide)
        self.menuHelp.addSeparator()
        self.menuHelp.addAction(self.About)
        self.menubar.addAction(self.menuHelp.menuAction())
        # System time
        self.timer = QtCore.QTimer()
        self.timer.setInterval(1000)
        self.timer.timeout.connect(self.displayTime)
        self.timer.start()
        self.retranslateUi(MainWindow)
        self.scrollBar.valueChanged['int'].connect(self.spinBox.setValue)
        self.spinBox.valueChanged['int'].connect(self.scrollBar.setValue)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        MainWindow.setWindowIcon(QtGui.QIcon('Measurement.ico'))


    def displayTime(self):
        self.SystemTime.setText(QtCore.QDateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "FIA Test Bed"))
        self.ChooseValve.setTitle(_translate("MainWindow", "Choose Valve"))
        self.Valve1.setText(_translate("MainWindow", "Valve1"))
        self.Valve2.setText(_translate("MainWindow", "Valve2"))
        self.MotorSpeed.setTitle(_translate("MainWindow", "Motor Speed"))
        self.Start.setText(_translate("MainWindow", "Start"))
        self.Exit.setText(_translate("MainWindow", "Exit"))
        self.SystemTime.setText(_translate("MainWindow", "TextLabel"))
        self.menuHelp.setTitle(_translate("MainWindow", "Help"))
        self.Guide.setText(_translate("MainWindow", "Guide"))
        self.Guide.setStatusTip(_translate("MainWindow", "User Guide"))
        self.About.setText(_translate("MainWindow", "About"))
        self.About.setStatusTip(_translate("MainWindow", "About the FIA Test Bed"))


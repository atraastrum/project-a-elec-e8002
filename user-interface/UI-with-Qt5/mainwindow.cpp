#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    ui.setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/ico"));
    currenttime = new QLabel(this);
    currenttime->setGeometry(QRect(5,360,220,20));
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    timer->start(1000);
}
void MainWindow::timerTime()
{
QDateTime sysTime = QDateTime::currentDateTime();
currenttime->setText(sysTime.toString("yyyy-MM-dd-hh:mm:ss"));
}

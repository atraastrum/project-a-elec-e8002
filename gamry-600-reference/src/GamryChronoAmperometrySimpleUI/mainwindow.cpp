#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpotentiostat.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rpPstat(new Gamry::QPotentiostat)
{
    ui->setupUi(this);
    QObject::connect(rpPstat, &Gamry::QPotentiostat::detected, [] {
      qDebug() << "Device detected\n";
    });
}

MainWindow::~MainWindow()
{
  delete ui;
  delete rpPstat;
}

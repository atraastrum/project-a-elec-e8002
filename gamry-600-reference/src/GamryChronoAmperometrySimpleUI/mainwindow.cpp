#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpotentiostat.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rpPstat(new Gamry::QPotentiostat)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete rpPstat;
}

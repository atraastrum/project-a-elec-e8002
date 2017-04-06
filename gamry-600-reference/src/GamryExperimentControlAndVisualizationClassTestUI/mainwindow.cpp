#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamrywidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //Gamry::GamryWidget* gw = new Gamry::GamryWidget;
}

MainWindow::~MainWindow()
{
  delete ui;
}

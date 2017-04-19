#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamrywidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  vInit{0.5f},
  tInit{5.0f},
  vFinal{-0.1f},
  tFinal{5.0f},
  smpRate{0.01f}
{
  ui->setupUi(this);
  statusBar()->showMessage("Pstat not connected. Polling for device");
  setSignalValuesToLineEdits();

  QObject::connect(ui->gamryWidget, SIGNAL(polling()), this, SLOT(pollingAnimation()));
  QObject::connect(ui->gamryWidget, SIGNAL(detected()), this, SLOT(pstatDetected()));
  QObject::connect(ui->gamryWidget, SIGNAL(experimentStarted()),
                   this, SLOT(experimentStarted()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setSignalValuesToLineEdits()
{
  ui->lineEditVinit->setText(QString::number(vInit));
  ui->lineEditTinit->setText(QString::number(tInit));
  ui->lineEditVfinal->setText(QString::number(vFinal));
  ui->lineEditTfinal->setText(QString::number(tFinal));
  ui->lineEditSampleRate->setText(QString::number(smpRate));
}

void MainWindow::setDisabledSignalLineEdits(bool val)
{
  ui->lineEditVinit->setDisabled(val);
  ui->lineEditTinit->setDisabled(val);
  ui->lineEditVfinal->setDisabled(val);
  ui->lineEditTfinal->setDisabled(val);
  ui->lineEditSampleRate->setDisabled(val);
}

void MainWindow::pollingAnimation()
{
  static unsigned int pointCount = 0;
  ++pointCount;
  if (pointCount == 20)
    pointCount = 0;
  QString message{"Pstat not connected. Polling for device"};
  for (unsigned int i = 0; i < pointCount; ++i)
    message += ".";
  statusBar()->showMessage(message);
}

void MainWindow::pstatDetected()
{
  statusBar()->showMessage("Potentiostat detected you can start the experiment.");
  ui->controGroupBox->setEnabled(true);
  ui->startStopButton->setText("Start experiment");
}

void MainWindow::on_startStopButton_clicked()
{
    if (ui->startStopButton->text() == "Start experiment") {
      ui->controGroupBox->setEnabled(false);
      ui->startStopButton->setText("Initializing Pstat");
      ui->gamryWidget->startExperiment(vInit,tInit,vFinal, tFinal, smpRate);
    } else if (ui->startStopButton->text() == "Stop experiment") {
      ui->gamryWidget->stopExperiment();
    }
}

void MainWindow::experimentStarted()
{
  ui->controGroupBox->setEnabled(true);
  ui->startStopButton->setText("Stop Experiment");
  setDisabledSignalLineEdits();
}

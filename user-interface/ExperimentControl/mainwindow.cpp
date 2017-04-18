#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThreadPool>
#include <QCloseEvent>
#include <QtConcurrent/QtConcurrent>
#include "potentiostat.hpp"
#include <iostream>

#include "../../arduinoSerial/ArduinoSerial.h"

void runExperiment(volatile bool* experimentRunning, float voltage, float time, float sampleRate, QCustomPlot* graphWindow)
{
    float localtime = 0;
    float waittime  = 1000;
    QVector<double> tdatabuffer;
    QVector<double> idatabuffer;

    if (*experimentRunning == false)
        return;

    qDebug() << "run";
    while (true)
    {
        if (*experimentRunning == false)
            return;

        graphWindow->graph(0)->addData(localtime/1000.0f, 1.0f);
        Sleep(waittime);
        localtime += waittime;
        qDebug() << "I'm running";
        if (localtime > time * 1000)
            break;
    }

/*
    Gamry::Potentiostat pStat;
    try {
        pStat.init("asdasd");
        pStat.open();

        // 10 seconds measurement
        pStat.setStepSignal(0.5f, 5.0f, -0.1f, 5.0f, 0.01f);
        pStat.start();

        size_t points_accuired = 0;
        do {
          qDebug() << "Wait 1 sec and pull data...\n";
          Sleep(1000);
          std::vector<Gamry::CookInformationPoint> data = pStat.pullDataItems(100);
          points_accuired = data.size();
          for(int i = 0; i < data.size(); ++i)
          {
            Gamry::CookInformationPoint& item = data[i];
            std::cout << item.Time << ';'
                  << item.Im << ';'
                  << item.Arch << ';'
                  << item.IERange << ';'
                  << item.Overload << ';'
                  << item.Q << ';'
                  << item.StopTest << ';'
                  << item.Vf << ';'
                  << item.Vsig << ';'
                  << item.Vu << ';'
                  << std::endl;
          }

        }while(points_accuired > 0);


        pStat.close();
    } catch (...){
        qDebug() << "Unable to initizlize Pstat. Probably it is not connected.";
    }
    */
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //arduinoSerial= new ArduinoSerial;
    ui->manualControlsGroup->setEnabled(true);
    //ui->autoControlsGroup->setEnabled(true);
}

MainWindow::~MainWindow()
{
    //delete arduinoSerial;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    experimentRunning = false;
    if (QThreadPool::globalInstance()->activeThreadCount())
        QThreadPool::globalInstance()->waitForDone();
    event->accept();
}

void MainWindow::on_startPumpButton_clicked()
{
    if(ui->startPumpButton->text() == "Start Pump")
    {
        ui->startPumpButton->setText("Stop Pump");
        if(arduinoSerial->startPump()) {
            qDebug() << "Pump started\n";
        }
    }
    else if(ui->startPumpButton->text() == "Stop Pump")
    {
        ui->startPumpButton->setText("Start Pump");
        if(arduinoSerial->stopPump())
        {
            qDebug() << "Pump stopped\n";
        }
    }
}

void MainWindow::on_comPortSelect_valueChanged(int arg1)
{
    qDebug() << arg1;
}

void MainWindow::on_comPortSelection_clicked()
{
    int com = ui->comPortSelect->value();
    if(arduinoSerial->setComPort(com))
    {
        const char *data = arduinoSerial->connectionCheck();
        if(strcmp(data, "UNO"))
        {
            ui->manualControlsGroup->setEnabled(true);
            comPortSelected = 1;
        }
    }
}

void MainWindow::on_modeSelection_activated(const QString &arg1)
{
    if(arg1 == "Manual" && comPortSelected==1)
    {
        ui->manualControlsGroup->setEnabled(true);
        ui->autoControlsGroup->setEnabled(false);
    }
    else if(arg1 == "Auto" && comPortSelected==1)
    {
        ui->manualControlsGroup->setEnabled(false);
        ui->autoControlsGroup->setEnabled(true);
    }
}

void MainWindow::on_liquid1Control_clicked()
{
    if(arduinoSerial->openLiquid1())
    {
        qDebug() << "Liquid 1 selected";
    }
}

void MainWindow::on_liquid2Control_clicked()
{
    if(arduinoSerial->openLiquid2())
    {
        qDebug() << "Liquid 2 selected";
    }
}

void MainWindow::on_controlPSTATButton_clicked()
{
  experimentRunning = false;
  if (QThreadPool::globalInstance()->activeThreadCount()) {
    qDebug() << "Waiting for background threads to finnish their work";
    QThreadPool::globalInstance()->waitForDone();
  }
  if (ui->controlPSTATButton->text() == "Stop Potentiostat") {
    ui->controlPSTATButton->setText("Start Potentiostat");
    return;
  }

  ui->controlPSTATButton->setText("Stop Potentiostat");
  startExperiment();
  checkIfDone();
}



void MainWindow::checkIfDone()
{
    static const int PollTimeout = 100;
    if (QThreadPool::globalInstance()->activeThreadCount()){
        ui->graphWindow->replot();
        QTimer::singleShot(PollTimeout, this, SLOT(checkIfDone()));
    }else {
        experimentRunning = true;
        ui->controlPSTATButton->setText("Start Potentiostat");
    }
}

void MainWindow::startExperiment()
{
  experimentRunning = true;
  ui->graphWindow->clearGraphs();
  ui->graphWindow->addGraph();
  ui->graphWindow->xAxis->setRange(0, 10.0f);
  QtConcurrent::run(runExperiment, &experimentRunning, 0.5f, 10.0f, 0.01f, ui->graphWindow);
}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QDebug>
#include <QThreadPool>
#include <QCloseEvent>
#include <QtConcurrent/QtConcurrent>

#include <QIntValidator>
#include <QDoubleValidator>

#include "qcustomplot.h"
#include "potentiostat.hpp"
#include <iostream>

#include "../../arduinoSerial/ArduinoSerial.h"


void runExperiment(volatile bool* experimentRunning, ExperimentSettings settings, QCustomPlot* graphWindow)
{
/*    float localtime = 0;
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
*/

    Gamry::Potentiostat pStat;
    QVector<double> buffer;
    QVector<double> bufferT;
    float totalTimeLeft = settings.totalTime();

    try {
        pStat.init("REF600-20017");
        pStat.open();

        pStat.setStepSignal(settings.vInit, settings.tInit, settings.vFinal, settings.tFinal, settings.sampleRate);
        //pStat.setStepSignal(0.5f, 5.0f, -0.1f, 5.0f, 0.01f);
        pStat.start();


        do {

          Sleep(settings.pollingInterval);

          if (*experimentRunning == false)
              break;

          std::vector<Gamry::CookInformationPoint> data = pStat.pullDataItems(100);

          for(int i = 0; i < data.size(); ++i)
          {
            Gamry::CookInformationPoint& item = data[i];
            graphWindow->graph(0)->addData(item.Time, item.Im);
            buffer.push_back(item.Im);
            bufferT.push_back(item.Time);
            /*std::cout << item.Time << ';'
                  << item.Im << ';'
                  << item.Arch << ';'
                  << item.IERange << ';'
                  << item.Overload << ';'
                  << item.Q << ';'
                  << item.StopTest << ';'
                  << item.Vf << ';'
                  << item.Vsig << ';'
                  << item.Vu << ';'
                  << std::endl;*/

          }

          if (buffer.size()) {
            QVector<double> diff(buffer.size());
            double mean = std::accumulate( buffer.begin(), buffer.end(), 0.0)/buffer.size();
            std::transform(buffer.begin(), buffer.end(), diff.begin(), [mean](double y) { return y - mean; });
            double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
            double stdev = std::sqrt(sq_sum / buffer.size());

            graphWindow->yAxis->setRange(mean - 2.0 * stdev, mean + 2.0 * stdev);
          }

          if (bufferT.size() && bufferT.last() >= totalTimeLeft)
            break;

          qDebug() << "in the loop\n";
        }while(true);


        pStat.close();
    } catch (...){
        qDebug() << "Unable to initizlize Pstat. Probably it is not connected.";
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduinoSerial= new ArduinoSerial;
    ui->manualControlsGroup->setEnabled(false);
    ui->autoControlsGroup->setEnabled(false);
    connect(ui->actionSetup, SIGNAL(triggered()), this, SLOT(Setup()));

    // Adding Validators to Auto Mode LineEdit Objects
    auto intervalInputValidator = new QIntValidator();
    intervalInputValidator->setBottom(1);
    auto voltageInputValidator = new QDoubleValidator();

    ui->intervalInput->setValidator(intervalInputValidator);
    ui->timeInput->setValidator(intervalInputValidator);
    ui->automodeVoltageInput->setValidator(voltageInputValidator);
}

MainWindow::~MainWindow()
{
    delete arduinoSerial;
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
        //std::string data = arduinoSerial->connectionCheck();
        //qDebug() << "check if data is correct";
        //qDebug() << data.c_str();
        //if(data == "UNO")
        //{
            qDebug() << "Enabling manual control";
            ui->manualControlsGroup->setEnabled(true);
            comPortSelected = 1;
        //}
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

void MainWindow::Setup()
{
       Dialog dialog;
       dialog.setModal(true);
       dialog.exec();
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
  ExperimentSettings settings = {0.5f, 50.0f, -0.1f, 50.0f, 0.01f, 100};
  startExperiment(settings);
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
        ui->graphWindow->replot();
        ui->controlPSTATButton->setText("Start Potentiostat");
        ui->measurementStartButton->setText("Start");
    }
}

void MainWindow::startExperiment(ExperimentSettings settings)
{
  experimentRunning = true;
  ui->graphWindow->clearGraphs();
  ui->graphWindow->addGraph();

  ui->graphWindow->xAxis->setRange(0, settings.totalTime());
  QtConcurrent::run(runExperiment, &experimentRunning, settings, ui->graphWindow);
}


void MainWindow::on_measurementStartButton_clicked()
{
  // Starting pstat experiment
  experimentRunning = false;
  if (QThreadPool::globalInstance()->activeThreadCount()) {
    qDebug() << "Waiting for background threads to finnish their work";
    QThreadPool::globalInstance()->waitForDone();
  }

  if (ui->measurementStartButton->text() == "Stop") {
    ui->measurementStartButton->setText("Start");
    return;
  }

  QLocale locale;
  bool ok = false;
  float voltage  = locale.toFloat(ui->automodeVoltageInput->text(), &ok);
  float time     = locale.toFloat(ui->timeInput->text(), &ok);
  float interval = locale.toFloat(ui->intervalInput->text(), &ok);

  if (ok == false) {
    QMessageBox errorMsgBox;
    errorMsgBox.setText("The paramaters for esperiment are invalid. Check them please");
    errorMsgBox.exec();
    return;
  }

  ui->measurementStartButton->setText("Stop");

  ExperimentSettings settings = {voltage, time/2.0f, voltage, time/2.0f, 0.01f, 100};
  startExperiment(settings);
  checkIfDone();
}

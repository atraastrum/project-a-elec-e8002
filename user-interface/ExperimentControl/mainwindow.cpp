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


void runExperiment(QVector<volatile bool*> array, ExperimentSettings settings, QCustomPlot* graphWindow, QVector<Gamry::CookInformationPoint>* data)
{
    volatile bool* experimentRunning = array[0];
    volatile bool* pstatInitialized = array[1];
    volatile bool* delayTimeOut = array[2];

    float totalTimeLeft = settings.totalTime();
#if 0
    Gamry::Potentiostat pStat;
    QVector<double> buffer;
    QVector<double> bufferT;


    try {
        pStat.init("REF600-20017");
        pStat.open();
        Sleep(1000);
        *pstatInitialized = true;

        if (settings.delay > 0) {
          Sleep(static_cast<unsigned int>(settings.delay * 1000.0f));
        }
        *delayTimeOut = true;

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
        }while(true);


        pStat.close();
        *pstatInitialized = false;
        *delayTimeOut = false;
    } catch (...){
        qDebug() << "Unable to initizlize Pstat. Probably it is not connected.";
    }
#endif
#if 1
  qDebug() << "Started thread";
  qDebug() << "Inializing\n";
  Sleep(2000);
  *pstatInitialized = true;
  qDebug() << "Inialized\n";

  if (settings.delay > 0) {
    Sleep(static_cast<unsigned int>(settings.delay * 1000.0f));
  }

  *delayTimeOut = true;

  int wait_time = 100;
  while (true) {
    if (*experimentRunning == false){
      Sleep(100);
      break;
    }
    qDebug() << "Doing Work " << totalTimeLeft;
    Gamry::CookInformationPoint item = {totalTimeLeft, 2,3,4,5,6,7,8,9,10};
    data->push_back(item);
    Sleep(wait_time);
    totalTimeLeft -= static_cast<float>(wait_time)/1000.0f;
    if (totalTimeLeft < 0.f)
        break;
  }

  *pstatInitialized = false;
  *delayTimeOut = false;
  qDebug() << "Stoped thread";
#endif
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    autoModeTimerForLiquids(new QTimer{this})
{
    ui->setupUi(this);
    arduinoSerial= new ArduinoSerial;
    ui->modeSelectionGroupBox->setDisabled(true);

    // For debugging
    //ui->manualControlsGroup->setEnabled(true);
    //ui->autoControlsGroup->setEnabled(true);

    connect(ui->actionSetup, SIGNAL(triggered()), this, SLOT(Setup()));

    // Adding Validators to Auto Mode LineEdit Objects
    auto intervalInputValidator = new QIntValidator();
    intervalInputValidator->setBottom(1);
    auto voltageInputValidator = new QDoubleValidator();

    ui->intervalInput->setValidator(intervalInputValidator);
    ui->timeInput->setValidator(intervalInputValidator);
    ui->automodeVoltageInput->setValidator(voltageInputValidator);

    //For auto control to change liquids
    QObject::connect(autoModeTimerForLiquids, SIGNAL(timeout()), this, SLOT(autoChangeLiquid()));

    ui->notificationLabel->setVisible(false);
    m_aemDotCount = 0;
    m_pstatInitialized = false;
    m_delayTimeOut = false;
    m_lastSizeBeforeAddToTable = 0;

    ui->pstatDataTable->setHorizontalHeaderLabels(QStringList() << "Time" << "Im" <<"Vf" <<"Vu" <<"Q" <<"Vsig" <<"Arch" <<"IERange" << "Overload" << "StopTest" );
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
            ui->modeSelectionGroupBox->setDisabled(false);
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
  ExperimentSettings settings = {0.5f, 50.0f, -0.1f, 50.0f, 0.01f, 100, 0};
  startExperiment(settings);
  checkIfDone();
}



void MainWindow::checkIfDone()
{
    static const int PollTimeout = 100;
    if (QThreadPool::globalInstance()->activeThreadCount()){
        ui->graphWindow->replot();
        addItemsToDataTable();
        QTimer::singleShot(PollTimeout, this, SLOT(checkIfDone()));
    }else {
        experimentRunning = false;
        m_pstatInitialized = false;
        m_delayTimeOut = false;

        ui->graphWindow->replot();
        addItemsToDataTable();

        ui->controlPSTATButton->setText("Start Potentiostat");
    }
}

void MainWindow::startExperiment(ExperimentSettings settings)
{
    experimentRunning = true;
    m_pstatInitialized = false;
    m_delayTimeOut = false;

    allDataFromPstat.clear();
    m_lastSizeBeforeAddToTable = 0;
    ui->graphWindow->clearGraphs();
    ui->graphWindow->addGraph();

    ui->graphWindow->xAxis->setRange(0, settings.totalTime());
    QVector<volatile bool*> vec;
    vec.push_back(&experimentRunning);
    vec.push_back(&m_pstatInitialized);
    vec.push_back(&m_delayTimeOut);
    //volatile bool *array[3] = {&experimentRunning, &m_pstatInitialized, &m_delayTimeOut};
    QtConcurrent::run(runExperiment, vec, settings, ui->graphWindow, &allDataFromPstat);
}

void MainWindow::addItemsToDataTable()
{
    for (m_lastSizeBeforeAddToTable; m_lastSizeBeforeAddToTable < allDataFromPstat.size(); ++m_lastSizeBeforeAddToTable) {
        Gamry::CookInformationPoint item = allDataFromPstat[m_lastSizeBeforeAddToTable];
        ui->pstatDataTable->insertRow(m_lastSizeBeforeAddToTable);
        float data[7] = {item.Time, item.Im, item.Vf, item.Vu, item.Q , item.Vsig, item.Arch,};
        int c = 0;
        for(; c < 7; ++c) {
            auto *newItem = new QTableWidgetItem(QString::number(data[c]));
            ui->pstatDataTable->setItem(m_lastSizeBeforeAddToTable, c, newItem);
        }
        auto *newItem = new QTableWidgetItem(QString::number(item.IERange));
        ui->pstatDataTable->setItem(m_lastSizeBeforeAddToTable, c++, newItem);
        newItem = new QTableWidgetItem(QString::number(item.Overload));
        ui->pstatDataTable->setItem(m_lastSizeBeforeAddToTable, c++, newItem);
        newItem = new QTableWidgetItem(QString::number(item.StopTest));
        ui->pstatDataTable->setItem(m_lastSizeBeforeAddToTable, c++, newItem);
        ui->pstatDataTable->scrollToBottom();
    }
}

void MainWindow::autoChangeLiquid()
{
  static bool setLiquid1 = true;
  if (setLiquid1) {
    arduinoSerial->openLiquid1();
    qDebug() << "LQ1";
    setLiquid1 = false;
  } else {
    arduinoSerial->openLiquid2();
    qDebug() << "LQ2";
    setLiquid1 = true;
  }
}

void MainWindow::waitForPstatToInitializeAndStart()
{

  if (m_pstatInitialized) {
    ui->notificationLabel->setText("Running the pump for " + ui->automodeDelayInput->text() + " seconds\nbefore measuring current");
    //arduinoSerial->startPump();
    //arduinoSerial->openLiquid1();
    waitForDelay();
    return;
  }

  QTimer::singleShot(10, this, SLOT(waitForPstatToInitializeAndStart()));
}

void MainWindow::waitForDelay()
{
  if (m_delayTimeOut) {
    //autoModeTimerForLiquids->start(m_autoInterval);

    ui->notificationLabel->setVisible(false);
    ui->measurementStartButton->setDisabled(false);
    ui->measurementStartButton->setText("Stop");

    return;
  }

  QTimer::singleShot(10, this, SLOT(waitForDelay()));
}

void MainWindow::checkIfDoneAuto()
{
    static const int PollTimeout = 100;
    if (QThreadPool::globalInstance()->activeThreadCount()){
        ui->graphWindow->replot();
        addItemsToDataTable();
        QTimer::singleShot(PollTimeout, this, SLOT(checkIfDoneAuto()));
    }else {
        experimentRunning = false;
        m_pstatInitialized = false;
        m_delayTimeOut = false;

        ui->graphWindow->replot();
        addItemsToDataTable();

        //arduinoSerial->stopPump();
        //arduinoSerial->openLiquid1();

        ui->automodeVoltageInput->setDisabled(false);
        ui->timeInput->setDisabled(false);
        ui->intervalInput->setDisabled(false);
        ui->automodeDelayInput->setDisabled(false);
        ui->measurementStartButton->setText("Start");
    }
}


void MainWindow::on_measurementStartButton_clicked()
{
  experimentRunning = false;
  if (QThreadPool::globalInstance()->activeThreadCount()) {
    ui->autoControlsGroup->setDisabled(true);
    qDebug() << "Waiting for background threads to finnish their work";
    ui->notificationLabel->setText("Experiment is still active \nPlease Wait and do nothing.");
    ui->notificationLabel->setVisible(true);
    QThreadPool::globalInstance()->waitForDone();
    ui->autoControlsGroup->setDisabled(false);
  }
  ui->notificationLabel->setVisible(false);


  QLocale locale;
  bool ok = false;
  m_autoVoltage  = locale.toFloat(ui->automodeVoltageInput->text(), &ok);
  m_autoTime     = locale.toFloat(ui->timeInput->text(), &ok);
  m_autoInterval = locale.toFloat(ui->intervalInput->text(), &ok);
  m_autoDelay = locale.toFloat(ui->automodeDelayInput->text(), &ok);


#if 0
  if (ok == false) {
    QMessageBox errorMsgBox;
    errorMsgBox.setText("The paramaters for esperiment are invalid. Check them please");
    errorMsgBox.exec();
    return;
  }
#endif

  if (ui->measurementStartButton->text() == "Stop") {
    ui->measurementStartButton->setText("Start");
    return;
  }

  ui->automodeVoltageInput->setDisabled(true);
  ui->timeInput->setDisabled(true);
  ui->intervalInput->setDisabled(true);
  ui->automodeDelayInput->setDisabled(true);
  ui->measurementStartButton->setDisabled(true);
  ui->measurementStartButton->setText("Please Wait");
  ui->notificationLabel->setText("Potentiostat is initializing.\nPlease Wait and do nothing.");
  ui->notificationLabel->setVisible(true);
  waitForPstatToInitializeAndStart();


  ExperimentSettings settings = {m_autoVoltage, m_autoTime/2.0f, m_autoVoltage, m_autoTime/2.0f, 0.01f, 100, m_autoDelay};
  //ExperimentSettings settings = {0, 0, 0, 0, 0.01f, 100, 10};
  startExperiment(settings);
  checkIfDoneAuto();
}

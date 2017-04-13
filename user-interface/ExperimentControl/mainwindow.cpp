#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "../../arduinoSerial/ArduinoSerial.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduinoSerial= new ArduinoSerial;
    ui->manualControlsGroup->setEnabled(false);
    ui->autoControlsGroup->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete arduinoSerial;
    delete ui;
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

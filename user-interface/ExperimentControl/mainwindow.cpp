#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "../../arduinoSerial/ArduinoSerial.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduinoSerial= new ArduinoSerial(4);
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

void MainWindow::on_liquid1Button_clicked()
{

}

void MainWindow::on_liquid2Button_clicked()
{

}

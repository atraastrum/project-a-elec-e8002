#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpotentiostat.hpp"
#include "potentiostat.hpp"
#include <QDebug>
#include <QVector>
#include <numeric>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rpPstat(new Gamry::QPotentiostat),
    fTotalExperimentTime{0}
{
  ui->setupUi(this);

  QObject::connect(rpPstat, SIGNAL(detected()), this , SLOT(activateButton()));
  QObject::connect(rpPstat, SIGNAL(dataAvailable(std::vector<Gamry::CookInformationPoint>)),
                      this, SLOT(updatePlot(std::vector<Gamry::CookInformationPoint>))
                   );


  QObject::connect(rpPstat, &Gamry::QPotentiostat::experimentStarted, [this]{
    qDebug() << "Started!!!!!!!!!!!!!!\n";
  });

}

MainWindow::~MainWindow()
{
  delete ui;
  delete rpPstat;
}

void MainWindow::activateButton()
{
  ui->startExperButton->setEnabled(true);
  ui->startExperButton->setText("Start ChronoAmperometry Experiment");
}

void MainWindow::on_startExperButton_clicked()
{
  if (rpPstat->state() == Gamry::QPotentiostat::State::ExperimentNotRunning) {
    qDebug() << "sdfasdfsdf\n";
    ui->startExperButton->setDisabled(true);
    ui->startExperButton->setText("Intializing Potentiostat");
    // Here program will freaze
    rpPstat->startExperiment(0.5f, 5.0f, -0.1f, 5.0f, 0.01f);
    fTotalExperimentTime = 10.0f;
    ui->startExperButton->setText("Stop ChronoAmperometry Experiment");
    ui->currentVsTimePlot->clearGraphs();
    ui->currentVsTimePlot->addGraph();
    ui->currentVsTimePlot->xAxis->setRange(0.0f, fTotalExperimentTime);
    ui->startExperButton->setEnabled(true);
  } else if (rpPstat->state() == Gamry::QPotentiostat::State::ExperimentRunning) {
    rpPstat->stopExperiment();
    ui->startExperButton->setText("Start ChronoAmperometry Experiment");
  }
}

void MainWindow::updatePlot(std::vector<Gamry::CookInformationPoint> data)
{
  static QVector<double> v;
  QVector<double> x, y;
  for(auto item:data)
  {
    x.push_back(item.Time);
    y.push_back(item.Im);
    v.push_back(item.Im);
  }

  QVector<double> diff(v.size());

  double mean = std::accumulate( v.begin(), v.end(), 0.0)/v.size();
  std::transform(v.begin(), v.end(), diff.begin(), [mean](double y) { return y - mean; });
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / v.size());

  ui->currentVsTimePlot->yAxis->setRange(mean - 5.0 * stdev, mean + 5.0 * stdev);
  ui->currentVsTimePlot->graph(0)->addData(x, y, true);
  ui->currentVsTimePlot->replot();
  if (x.back() >= fTotalExperimentTime) {
    rpPstat->stopExperiment();
    ui->startExperButton->setText("Start ChronoAmperometry Experiment");
  }
}

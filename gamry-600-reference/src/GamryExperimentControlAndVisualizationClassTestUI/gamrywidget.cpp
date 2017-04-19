#include "gamrywidget.hpp"
#include <QVBoxLayout>
#include <QPushButton>

#include "../GamryChronoAmperometrySimpleUI/qcustomplot.h"
#include "../GamryChronoAmperometrySimpleUI/qpotentiostat.hpp"

namespace Gamry {
  GamryWidget::GamryWidget(QWidget *parent)
    : QWidget(parent),
      rpMainLayout(new QVBoxLayout),
      rpPlot{new QCustomPlot},
      rpSaveCSVButton{new QPushButton},
      rpPstat{new QPotentiostat},
      totalExperimentTime{0}
  {
    rpSaveCSVButton->setMaximumWidth(400);
    rpSaveCSVButton->setText(tr("Save as CSV file"));
    rpSaveCSVButton->setDisabled(true);

    rpMainLayout->addWidget(rpPlot);
    rpMainLayout->addWidget(rpSaveCSVButton);
    rpMainLayout->setAlignment(rpSaveCSVButton, Qt::AlignRight);
    setLayout(rpMainLayout);

    QObject::connect(rpPstat, SIGNAL(polling()), this, SLOT(emitpollingevent()));
    QObject::connect(rpPstat, SIGNAL(detected()), this, SLOT(emitdetectedevent()));
    QObject::connect(rpPstat, SIGNAL(experimentStarted()),
                     this, SLOT(emitexperimentStarted()));
  }

  GamryWidget::~GamryWidget()
  {
    if (rpPstat)
    {
      if (rpPstat->state() == QPotentiostat::State::ExperimentRunning)
        rpPstat->stopExperiment();
      delete rpPstat;
    }
    qDebug() << "Destructor was called\n";
  }

  void GamryWidget::emitpollingevent()
  {
    emit polling();
  }

  void GamryWidget::emitdetectedevent()
  {
    emit detected();
  }

  void GamryWidget::emitexperimentStarted()
  {
    emit experimentStarted();
  }

  void GamryWidget::updatePlot(std::vector<CookInformationPoint> data)
  {

    QVector<double> x, y;
    for(auto item:data)
    {
      x.push_back(item.Time);
      y.push_back(item.Im);
      buffer.push_back(item.Im);
    }

    QVector<double> diff(buffer.size());

    double mean = std::accumulate( buffer.begin(), buffer.end(), 0.0)/buffer.size();
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), [mean](double y) { return y - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / buffer.size());

    rpPlot->yAxis->setRange(mean - 5.0 * stdev, mean + 5.0 * stdev);
    rpPlot->graph(0)->addData(x, y, true);
    rpPlot->replot();

    if (x.back() >= totalExperimentTime) {
      stopExperiment();
      emit experimentComplited();
    }

  }

  void GamryWidget::startExperiment(float vInit, float tInit, float vFinal, float tFinal, float sampleRate)
  {
    if (rpPstat->state() == QPotentiostat::State::ExperimentNotRunning)
    {
      rpPstat->startExperiment(vInit, tInit, vFinal, tFinal, sampleRate);
      emit experimentStarted();
      totalExperimentTime = tInit + tFinal;
      rpPlot->clearGraphs();
      rpPlot->addGraph();
      rpPlot->xAxis->setRange(0.0f, totalExperimentTime);
    }

  }

  void GamryWidget::stopExperiment()
  {
    if (rpPstat->state() == QPotentiostat::State::ExperimentRunning)
      rpPstat->stopExperiment();
  }
}


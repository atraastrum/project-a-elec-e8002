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
      rpPstat{new QPotentiostat}
  {
    auto saveCSVButton = new QPushButton;
    saveCSVButton->setMaximumWidth(400);
    saveCSVButton->setText(tr("Save as CSV file"));

    rpMainLayout->addWidget(rpPlot);
    rpMainLayout->addWidget(saveCSVButton);
    rpMainLayout->setAlignment(saveCSVButton, Qt::AlignRight);
    setLayout(rpMainLayout);

    QObject::connect(rpPstat, SIGNAL(polling()), this, SLOT(emitpollingevent()));
    QObject::connect(rpPstat, SIGNAL(detected()), this, SLOT(emitdetectedevent()));
    QObject::connect(rpPstat, SIGNAL(experimentStarted()),
                     this, SLOT(emitexperimentStarted()));
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

  void GamryWidget::startExperiment(float vInit, float tInit, float vFinal, float tFinal, float sampleRate)
  {
    if (rpPstat->state() == QPotentiostat::State::ExperimentNotRunning)
      rpPstat->startExperiment(vInit, tInit, vFinal, tFinal, sampleRate);
  }

  void GamryWidget::stopExperiment()
  {
    if (rpPstat->state() == QPotentiostat::State::ExperimentRunning)
      rpPstat->stopExperiment();
  }
}


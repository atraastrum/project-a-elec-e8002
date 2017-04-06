#include "gamrywidget.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include "../GamryChronoAmperometrySimpleUI/qcustomplot.h"

namespace Gamry {
  GamryWidget::GamryWidget(QWidget *parent)
    : QWidget(parent),
      mainLayout(new QVBoxLayout)
  {
    plot = new QCustomPlot;
    auto saveCSVButton = new QPushButton;
    saveCSVButton->setMaximumWidth(400);
    saveCSVButton->setText(tr("Save as CSV file"));


    mainLayout->addWidget(plot);
    mainLayout->addWidget(saveCSVButton);
    mainLayout->setAlignment(saveCSVButton, Qt::AlignRight);
    setLayout(mainLayout);


  }
}


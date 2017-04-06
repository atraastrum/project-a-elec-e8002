#ifndef GAMRYWIDGET_HPP
#define GAMRYWIDGET_HPP

#include <QWidget>

class QCustomPlot;
class QVBoxLayout;

namespace Gamry {

  class GamryWidget : public QWidget
  {
    Q_OBJECT

  public:
    explicit GamryWidget(QWidget *parent = 0);

  signals:

  public slots:
  private:
    QVBoxLayout *mainLayout;
    QCustomPlot* plot;
  };
}


#endif // GAMRYWIDGET_HPP

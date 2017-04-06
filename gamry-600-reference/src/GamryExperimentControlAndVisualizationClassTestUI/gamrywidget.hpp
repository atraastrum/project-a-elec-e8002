#ifndef GAMRYWIDGET_HPP
#define GAMRYWIDGET_HPP

#include <QWidget>

class QCustomPlot;
class QVBoxLayout;


namespace Gamry {
  class QPotentiostat;

  class GamryWidget : public QWidget
  {
    Q_OBJECT

  public:
    explicit GamryWidget(QWidget *parent = 0);

  signals:
    void polling();
    void detected();
    void experimentStarted();

  private slots:
    void emitpollingevent();
    void emitdetectedevent();
    void emitexperimentStarted();

  public slots:
    void startExperiment(float vInit, float tInit, float vFinal, float tFinal, float sampleRate);
    void stopExperiment();

  private:
    QVBoxLayout *rpMainLayout;
    QCustomPlot* rpPlot;
    QPotentiostat* rpPstat;
  };
}


#endif // GAMRYWIDGET_HPP

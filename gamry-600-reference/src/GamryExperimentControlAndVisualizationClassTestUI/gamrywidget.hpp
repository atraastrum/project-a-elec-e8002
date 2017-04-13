#ifndef GAMRYWIDGET_HPP
#define GAMRYWIDGET_HPP

#include <QWidget>
#include "../GamryChronoAmperometrySimpleUI/gamry.hpp"

class QCustomPlot;
class QVBoxLayout;
class QPushButton;

namespace Gamry {
  class QPotentiostat;

  class GamryWidget : public QWidget
  {
    Q_OBJECT

  public:
    explicit GamryWidget(QWidget *parent = 0);
    virtual ~GamryWidget();

  signals:
    void polling();
    void detected();
    void experimentStarted();
    void experimentComplited();

  private slots:
    void emitpollingevent();
    void emitdetectedevent();
    void emitexperimentStarted();
    void updatePlot(std::vector<Gamry::CookInformationPoint> data);


  public slots:
    void startExperiment(float vInit, float tInit, float vFinal, float tFinal, float sampleRate);
    void stopExperiment();

  private:
    QVBoxLayout *rpMainLayout;
    QCustomPlot* rpPlot;
    QPushButton* rpSaveCSVButton;
    QPotentiostat* rpPstat;
    float totalExperimentTime;
    QVector<double> buffer;
  };
}


#endif // GAMRYWIDGET_HPP

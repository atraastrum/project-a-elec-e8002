#ifndef QPOTENTIOSTAT_HPP
#define QPOTENTIOSTAT_HPP

#include <QObject>
#include "gamry.hpp"

namespace Gamry {

  // Defined in potentiostat.hpp
  class DeviceList;
  class Potentiostat;
  struct CookInformationPoint;

  // States:
  // Not intialized, Stoped, Aquring data, Paused
  class QPotentiostat : public QObject
  {
    Q_OBJECT
  public:
    enum class State {DeviceNotDetected, ExperimentRunning, ExperimentNotRunning};

  public:
    explicit QPotentiostat(QObject *parent = 0);
    ~QPotentiostat();

    const State state();

  protected:
    void timerEvent(QTimerEvent *event);

  signals:
    // Emitted when Gamry is detected
    void detected();
    // Emitted when data from gamry Experiment is available
    void dataAvailable(std::vector<Gamry::CookInformationPoint>);
    void experimentStarted();

  public slots:
    // Starts experiment
    void startExperiment(float vInit, float tInit, float vFinal, float tFinal, float sampleRate);
    void stopExperiment();

  private:
    DeviceList* rpDevList;
    Potentiostat* rpPstat;
    State currentState;
    int iTimerIDDevCount;
    int iTimerIDPullData;
  };
}


#endif // QPOTENTIOSTAT_HPP

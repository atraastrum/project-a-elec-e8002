#include "qpotentiostat.hpp"
#include "potentiostat.hpp"
#include <QTimerEvent>
#include <QDebug>

namespace Gamry {
  QPotentiostat::QPotentiostat(QObject *parent)
    : QObject(parent),
      rpPstat(new Potentiostat),
      currentState{State::DeviceNotDetected},
      iTimerIDDevCount{startTimer(1000)}
  {

  }

  QPotentiostat::~QPotentiostat()
  {
    if (rpPstat)
      delete rpPstat;
  }

  void QPotentiostat::startExperiment(float vInit, float tInit, float vFinal,
                                      float tFinal, float sampleRate)
  {
    if (currentState == State::ExperimentNotRunning)
    {
      iTimerIDPullData = startTimer(1000);
      currentState = State::ExperimentRunning;
      rpPstat->open();
      rpPstat->setStepSignal(vInit, tInit, vFinal, tFinal, sampleRate);
      rpPstat->start();
      qDebug() << "Started Experiment\n";
    }
  }

  void QPotentiostat::stopExperiment()
  {
    if (currentState == State::ExperimentRunning)
    {
      killTimer(iTimerIDPullData);
      currentState = State::ExperimentNotRunning;
      rpPstat->close();
      qDebug() << "Stopped Experiment\n";
    }
  }


  const QPotentiostat::State QPotentiostat::state()
  {
    return currentState;
  }

  void QPotentiostat::timerEvent(QTimerEvent *event)
  {
    static int j = 0;
    int id = event->timerId();
    if (id == iTimerIDDevCount)
    {
      if (rpPstat->deviceCount() >= 0 && currentState == State::DeviceNotDetected)
      {
        killTimer(iTimerIDDevCount);
        iTimerIDDevCount = -1;
        currentState = State::ExperimentNotRunning;
        rpPstat->init();
        qDebug() << "Detected potentiostat\n" ;
        emit detected();
      }

      qDebug() << "Polling for device...\n" ;
    } else if (id == iTimerIDPullData)
    {
      qDebug() << "Polling for data...\n" ;

      std::vector<Gamry::CookInformationPoint> buffer = rpPstat->pullDataItems(100);
#if 0
      std::vector<CookInformationPoint> buffer;
      for(int i = 0; i < 2; ++i) {
        CookInformationPoint item = {static_cast<float>(j),
                                     0.0f,
                                     0.0f,
                                     static_cast<float>(i*i),
                                     0.0f,
                                     0.0f,
                                     0,
                                     0,
                                     0
                                    };
        qDebug() << j ;
        buffer.push_back(item);
        ++j;
      }
#endif
      if ( ! buffer.empty() )
        emit dataAvailable(buffer);

    }
  }
}


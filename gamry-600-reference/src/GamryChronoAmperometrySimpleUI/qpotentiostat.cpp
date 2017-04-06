#include "qpotentiostat.hpp"
#include "potentiostat.hpp"
#include <QTimerEvent>
#include <QDebug>

namespace Gamry {
  QPotentiostat::QPotentiostat(QObject *parent)
    : QObject(parent),
      rpDevList(new DeviceList),
      rpPstat(nullptr),
      currentState{State::DeviceNotDetected},
      iTimerIDDevCount{startTimer(1000)}

  {

  }

  QPotentiostat::~QPotentiostat()
  {
    if (rpDevList)
      delete rpDevList;
    if (rpPstat)
    {
      rpPstat->close();
      delete rpPstat;
    }

  }

  void QPotentiostat::startExperiment(float vInit, float tInit, float vFinal,
                                      float tFinal, float sampleRate)
  {
    if (currentState == State::ExperimentNotRunning)
    {
      if (rpPstat == nullptr) {
        if (pStatSectionName.empty())
        {
          qDebug() << "Section name is empty string";
          qDebug() << "Will not start expreriment";
          return;
        }
        rpPstat = new Potentiostat;
        rpPstat->init(pStatSectionName);
        rpPstat->open();
        rpPstat->setStepSignal(vInit, tInit, vFinal, tFinal, sampleRate);
        rpPstat->start();
        emit experimentStarted();
        currentState = State::ExperimentRunning;
        iTimerIDPullData = startTimer(1000);
        qDebug() << "Started Experiment\n";
      }
      else
        qDebug() << "Potentiostat must be nullptr in startExperiment\n";
    }
  }

  void QPotentiostat::stopExperiment()
  {
    if (currentState == State::ExperimentRunning)
    {
      if (rpPstat)
      {
        killTimer(iTimerIDPullData);
        currentState = State::ExperimentNotRunning;
        rpPstat->close();
        delete rpPstat;
        rpPstat = nullptr;
        qDebug() << "Stopped Experiment\n";
      }
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
      if (rpDevList->deviceCount() > 0 && currentState == State::DeviceNotDetected)
      {
        killTimer(iTimerIDDevCount);
        iTimerIDDevCount = -1;
        currentState = State::ExperimentNotRunning;

        qDebug() << "Detected potentiostat";
        std::string pStatSectionName = rpDevList->getSection(0);
        qDebug() << pStatSectionName.c_str();
        emit detected();
      }
      else
      {
        qDebug() << "Polling for device...\n" ;
        emit polling();
      }

    } else if (id == iTimerIDPullData)
    {
      qDebug() << "Polling for data...\n" ;

      //std::vector<Gamry::CookInformationPoint> buffer;
      std::vector<Gamry::CookInformationPoint> buffer = rpPstat->pullDataItems(100);

      if ( ! buffer.empty() )
        emit dataAvailable(buffer);
    }
  }

}


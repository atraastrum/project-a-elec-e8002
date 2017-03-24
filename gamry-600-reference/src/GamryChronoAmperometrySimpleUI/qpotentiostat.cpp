#include "qpotentiostat.hpp"
#include "potentiostat.hpp"
#include <QTimerEvent>
#include <QDebug>

namespace Gamry {
  QPotentiostat::QPotentiostat(QObject *parent)
    : QObject(parent),
      rpPstat(new Potentiostat)
  {
    iTimerIDDevCount = startTimer(1000);
  }

  QPotentiostat::~QPotentiostat()
  {
    if (rpPstat)
      delete rpPstat;
  }

  void QPotentiostat::timerEvent(QTimerEvent *event)
  {
    int id = event->timerId();
    if (id == iTimerIDDevCount)
    {
      if (rpPstat->deviceCount() > 0)
      {
        killTimer(id);
        emit detected();
      }
    }
  }
}


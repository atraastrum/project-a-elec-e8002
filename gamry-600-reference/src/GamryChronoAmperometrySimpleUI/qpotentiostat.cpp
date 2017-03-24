#include "qpotentiostat.hpp"
#include "potentiostat.hpp"

namespace Gamry {
  QPotentiostat::QPotentiostat(QObject *parent)
    : QObject(parent),
      rpPstat(new Potentiostat)
  {

  }

  QPotentiostat::~QPotentiostat()
  {
    if (rpPstat)
      delete rpPstat;
  }
}


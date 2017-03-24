#include "potentiostat.hpp"
#include <QDebug>

namespace Gamry {
  Potentiostat::Potentiostat()
  {
    CoInitialize(nullptr);
    HRESULT hr = spDeviceList.CoCreateInstance(__uuidof(GamryDeviceList));

    if (FAILED(hr))
      throw "Failed 1";

    hr = spPstat.CoCreateInstance(__uuidof(GamryPstat));

   if(FAILED(hr))
     throw "Failed 2";

    hr = spDtaqChrono.CoCreateInstance(__uuidof(GamryDtaqChrono));

    if(FAILED(hr))
      throw "Failed 3";

    hr = spSignalStep.CoCreateInstance(__uuidof(GamrySignalStep));
    if(FAILED(hr))
      throw "Failed 4";

    qDebug() << "End of scope Pontentiostat ctor\n";
  }

  Potentiostat::~Potentiostat()
  {
    CoUninitialize();
    qDebug() << "Destructor of Potentiostat Called\n";
  }

  long Potentiostat::deviceCount()
  {
    return spDeviceList->Count();
  }
}

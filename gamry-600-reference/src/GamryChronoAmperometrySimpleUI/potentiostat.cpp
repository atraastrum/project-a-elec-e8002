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

  void Potentiostat::setStepSignal(float vInit, float tInit, float vFinal, float tFinal, float sampleRate)
  {
    qDebug() << "Initializing  IGamrySignalStep\n";
    spSignalStep->Init(spPstat, vInit, tInit, vFinal, tFinal, sampleRate, PstatMode);
    IGamrySignal* lpSignalBase = nullptr;
    spSignalStep->QueryInterface(&lpSignalBase);
    spPstat->SetSignal(lpSignalBase);
  }

  void Potentiostat::init()
  {
    if (deviceCount() > 0)
    {
      std::string section;
      BSTR sectionBSTR = nullptr;
      long idx = 0;
      SAFEARRAY* psa = nullptr;
      psa = spDeviceList->EnumSections();
      SafeArrayGetElement(psa, &idx, &sectionBSTR);
      if (sectionBSTR) {
          section = _bstr_t(sectionBSTR);
      } else {
        qDebug() << "Unable to get Label for idx " << idx << "\n";
      }
      SafeArrayDestroy(psa);

      spPstat->Init(sectionBSTR);


      qDebug() << "Initializing  IGamryDtaqChrono\n";
      spDtaqChrono->Init(spPstat, ChronoAmp);
    }
  }

  void Potentiostat::open()
  {
    qDebug() << "Opening potentiostat\n";
    spPstat->Open();

    qDebug() << "Switching cell switch off\n";
    spPstat->SetCell (CellOff);

    spPstat->SetCtrlMode (PstatMode);
    spPstat->SetIEStability (StabilityNorm);

    //spPstat->SetIConvention (Cathodic);

    spPstat->SetAnalogOut (0.0);
    spPstat->SetVoltage (0.0);
  }

  void Potentiostat::start()
  {
    qDebug() << "Pstat is initializing signal\n";
    spPstat->InitSignal();

    qDebug() << "Pstat turning cell on...\n";
    spPstat->SetCell(CellOn);

    // Run the Experiment
    qDebug() << "DtaqChrono start running\n";
    spDtaqChrono->Run(VARIANT_TRUE);
  }


}

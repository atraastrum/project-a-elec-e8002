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

  void Potentiostat::close()
  {
    spDtaqChrono->Stop();
    qDebug() << "Pstat turning Cell Of\n";
    spPstat->SetCell(CellOff);
    qDebug() << "Pstat closing\n";
    spPstat->Close(VARIANT_TRUE);
  }

  std::vector<CookInformationPoint> Potentiostat::pullDataItems(size_t point_count)
  {
    std::vector<CookInformationPoint> data;
    // Output Data
    VARIANT dataitem[10];
    long    index[2];

    SAFEARRAY* psa;

    long pointcount = static_cast<long>(point_count);
    spDtaqChrono->Cook(&pointcount, &psa);

    for (int i = 0; i < pointcount; ++i)
    {
      // Indexes are specific locations based on Dtaq. See documentation for details.
      // SafeArray indexing is reversed from normal conventions.
      index[1] = i;
      for (long j = 0; j < 10; ++j) {
        index[0] = j;
        SafeArrayGetElement(psa, index, &(dataitem[j]) );
      }

      data.push_back({dataitem[0].fltVal,
                      dataitem[1].fltVal,
                      dataitem[2].fltVal,
                      dataitem[3].fltVal,
                      dataitem[4].fltVal,
                      dataitem[5].fltVal,
                      dataitem[6].fltVal,
                      dataitem[7].intVal,
                      dataitem[8].intVal,
                      dataitem[9].intVal
                     });
      qDebug() << dataitem[0].fltVal << ";" << dataitem[3].fltVal << ";" << dataitem[3].fltVal << "\n";
    }

    SafeArrayDestroy(psa);

    return data;
  }

}

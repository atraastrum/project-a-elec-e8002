#include <QCoreApplication>


// Import the Gamry Electrochemistry Toolkit: GamryCOM using our TypeLib GUID
// This is created when GamryCOM is registered during installation of the Gamry Software Suite.

#include "gamrypotentiostat.hpp"



#include <atlcom.h>

using namespace ATL;

//#include <atlcom.h>
//#include <atlctl.h>

BOOL CtrlHandler( DWORD fdwCtrlType )
{
  switch( fdwCtrlType )
  {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
      QCoreApplication::quit();
      return( TRUE );

     default:
      return FALSE;
  }
}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  CoInitialize(nullptr);


  CComPtr<IGamryDeviceList> spDeviceList;
  HRESULT hr = spDeviceList.CoCreateInstance(__uuidof(GamryDeviceList));

  if(FAILED(hr)) {
    std::cout << "Failed 1\n";
    return -1;
  }

  CComPtr<IGamryPstat> spPstat;
  hr = spPstat.CoCreateInstance(__uuidof(GamryPstat));


  if(FAILED(hr)) {
    std::cout << "Failed 2\n";
    return -1;
  }

  CComPtr<IGamryDtaqChrono> spDtaqChrono;
  hr = spDtaqChrono.CoCreateInstance(__uuidof(GamryDtaqChrono));

  if(FAILED(hr)) {
    std::cout << "Failed 3\n";
    return -1;
  }

  CComPtr<IGamrySignalStep> spSignalStep;
  hr = spSignalStep.CoCreateInstance(__uuidof(GamrySignalStep));

  if(FAILED(hr)) {
    std::cout << "Failed 4\n";
    return -1;
  }


  long count = spDeviceList->Count();
  if (count > 0) {
    std::cout << "Device found\n" ;

    std::string section;
    long idx = 0;
    BSTR sectionBSTR = nullptr;
    if (idx >=0 && idx < count) {
      SAFEARRAY* psa = nullptr;
      psa = spDeviceList->EnumSections();
      SafeArrayGetElement(psa, &idx, &sectionBSTR);
      if (sectionBSTR) {
        section = _bstr_t(sectionBSTR);
      } else {
        qDebug() << "Unable to get Label for idx " << idx << "\n";
      }
      SafeArrayDestroy(psa);
    }

    std::cout<< section << std::endl;
    spPstat->Init(sectionBSTR);
    BSTR bstrSerial = spPstat->SerialNo();

    if (bstrSerial)
      std::cout << _bstr_t(bstrSerial) << std::endl;

    std::cout << "Initializing  IGamryDtaqChrono\n";
    spDtaqChrono->Init(spPstat, ChronoAmp);

    std::cout << "Initializing  IGamrySignalStep\n";
    spSignalStep->Init(spPstat, 0.5f, 5.0f, -0.1f, 5.0f, 0.01f, PstatMode);

    std::cout << "Opening potentiostat\n";
    spPstat->Open();

    std::cout << "Setting parameters of Pstat\n";
    spPstat->SetCell (CellOff);
    spPstat->SetAnalogOut (0.0);
    spPstat->SetVoltage (0.0);

    std::cout << "Setting signal\n";
    IGamrySignal* lpSignalBase = NULL;
    spSignalStep->QueryInterface(&lpSignalBase);
    spPstat->SetSignal(lpSignalBase);

    std::cout << "Pstat is initializing signal\n";
    spPstat->InitSignal();

    std::cout << "Pstat turning cell on..." << std::endl;
    spPstat->SetCell(CellOn);

    // Run the Experiment
    std::cout << "DtaqChrono start running\n";
    spDtaqChrono->Run(VARIANT_TRUE);

    // Output Data
    VARIANT Voltage_data;
    VARIANT Current_data;

    long index_v[2];
    long index_i[2];
    long PointCount = 0;
    long CurrentPoint = 0;
    const long PointsToCook = 256;

    const int poll_delay = 300;
    const int delay_interval = 100;

    SAFEARRAY * psa;

    std::cout << "Before 100 sec sleep\n";
    Sleep(100000);
    std::cout << "After 100 sec sleep\n";
    CurrentPoint = 0;
    PointCount = PointsToCook;
    spDtaqChrono->Cook(&PointCount, &psa);

    std::cout << "PointCount is " << PointCount << std::endl;

    // Always "Cook" until routine returns no data.
    while (PointCount > 0)
    {
      // Loop through and display each point
      for (int i = 0; i < PointCount; i++)
      {
        CurrentPoint++;

        // Indexes are specific locations based on Dtaq.  See documentation for details.
        // SafeArray indexing is reversed from normal conventions.

        index_v[0] = 1;
        index_v[1] = i;

        index_i[0] = 3;
        index_i[1] = i;

        SafeArrayGetElement(psa, index_v, &Voltage_data);
        SafeArrayGetElement(psa, index_i, &Current_data);

        std::cout << Voltage_data.fltVal << "  " << Current_data.fltVal << "\n";
      }

      SafeArrayDestroy(psa);

      // Cook and loop
      PointCount = PointsToCook;
      spDtaqChrono->Cook(&PointCount, &psa);
    }

    SafeArrayDestroy(psa);
    std::cout << std::endl;
    std::cout << "Experiment complete." << std::endl;

    std::cout << "DtaqChrono stops running\n";
    spDtaqChrono->Stop();

    std::cout << "Pstat turning Cell Of\n";
    spPstat->SetCell(CellOff);
    std::cout << "Pstat closing\n";
    spPstat->Close(VARIANT_TRUE);
  }


  CoUninitialize();

  //QObject::connect(&a, &QCoreApplication::aboutToQuit, [=]{
  //  CoUninitialize();
  //});

  //SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );

  //int r = a.exec();



  return 0;
}






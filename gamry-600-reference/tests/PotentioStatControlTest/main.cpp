#include <QCoreApplication>


// Import the Gamry Electrochemistry Toolkit: GamryCOM using our TypeLib GUID
// This is created when GamryCOM is registered during installation of the Gamry Software Suite.

#include "gamrypotentiostat.hpp"

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

  // Instrument Interactions

  //IGamryPstat* lpPstat = nullptr;

  // CoCreateInstance Creates COM object and get interfaces from the obejct


  CoInitialize(nullptr);

/*  IGamryDeviceList* lpDeviceList = nullptr;
  HRESULT hr = CoCreateInstance(__uuidof(GamryDeviceList), nullptr, CLSCTX_ALL, __uuidof(IGamryDeviceList), reinterpret_cast<void**>(&lpDeviceList));
  if (FAILED(hr)) {
    std::cerr << "FAILED to create interface for IGamryDeviceList: " << hr << std::endl;
    return hr;
  }
*/

  //CoCreateInstance(__uuidof(GamryPstat), NULL, CLSCTX_ALL, __uuidof(IGamryPstat), reinterpret_cast<void**>(&lpPstat));

  GamryPotentiostat::DeviceList dl;
  std::cout << dl.count() << std::endl;

  QObject::connect(&a, &QCoreApplication::aboutToQuit, []{
    std::cout << "Out of Application" << std::endl;
  });

  SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );

  return a.exec();
}





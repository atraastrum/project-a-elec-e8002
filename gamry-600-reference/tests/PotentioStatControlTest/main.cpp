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

class CClient : public _IGamryDeviceListEvents {
public:
  CClient();
  ~CClient();
  virtual void OnDeviceListChanged() = 0;
};

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  CoInitialize(nullptr);

#if 1
  CComPtr<IGamryDeviceList> spDeviceList;
  HRESULT hr = spDeviceList.CoCreateInstance(__uuidof(GamryDeviceList));
  if(FAILED(hr))
    std::cout << "Failed 1\n";

  std::cout << spDeviceList->Count() << std::endl;

  CComPtr<IConnectionPoint> spcp;
  CComQIPtr<IConnectionPointContainer> spcpc(spDeviceList);
  DWORD m_dwCookie;

  hr = spcpc->FindConnectionPoint( __uuidof(_IGamryDeviceListEvents), &spcp);
  if(FAILED(hr))
    std::cout << "Failed 2\n";

 CClient cl{};
 //spcp->Advise(&cl, &m_dwCookie);

#endif
/*
  try {

      std::cout << spDeviceList->Count() << std::endl;
  }catch(...) {
    ;
  }

  CComPtr<_IGamryDeviceListEvents> pControl;
  hr = spDeviceList->QueryInterface(IID_PPV_ARGS(&pControl));
  if(FAILED(hr)){
    std::cout << "asdasdasd";
  }*/

#if 0
  CComPtr<_IGamryDeviceListEvents> spDeviceList;
  HRESULT hr = spDeviceList.CoCreateInstance(__uuidof(GamryDeviceList));
  if(FAILED(hr))
      std::cout << "Failed\n";
#endif

  // Instrument Interactions

  //IGamryPstat* lpPstat = nullptr;

  // CoCreateInstance Creates COM object and get interfaces from the obejct


  //CoInitialize(nullptr);



  /*
  try {
    Gamry::DeviceList dl;
  }catch(Gamry::com_exception err) {
    std::cout << "AAAAA\n";
  }
*/
  //std::cout << dl.count() << std::endl;
  //std::cout << dl.getLabelOfDeviceWithIdx(0) << std::endl;
  //std::cout << dl.getSectionOfDeviceWithIdx(0) << std::endl;




  QObject::connect(&a, &QCoreApplication::aboutToQuit, [=]{
    //std::cout << "Out of Application" << std::endl;
  });

  SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );

  int r = a.exec();


  CoUninitialize();
  return r;
}





CClient::CClient()
{

}

CClient::~CClient()
{

}

void CClient::OnDeviceListChanged() {
  std::cout << "AAAAA\n";
}

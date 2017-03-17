#include "gamrypotentiostat.hpp"

namespace Gamry {


  //Class invariant hr must be greater than zero
  DeviceList::DeviceList()
    : lpDeviceList{nullptr}
  {

    qDebug() << "Call from constructor\n";
    HRESULT hr = CoCreateInstance(__uuidof(GamryDeviceList), nullptr, CLSCTX_ALL, __uuidof(IGamryDeviceList), reinterpret_cast<void**>(&lpDeviceList));
    if (FAILED(hr)){
      throw com_exception{"CoCreateInstance failed in DeviceList::DeviceList", hr};
    }



  }

  DeviceList::~DeviceList()
  {
    if (lpDeviceList) {
      lpDeviceList->Release();
      qDebug() << "DEBUG Released COM object GamryDeviceList\n";
    }

    qDebug() << "destructor was called";
  }

long DeviceList::count() const
{
  //if (hr > 0)
  //  return lpDeviceList->Count();
  //else
    return 0;
}

std::string DeviceList::getLabelOfDeviceWithIdx(long idx)
{
  std::string labelStd;
  BSTR labelBSTR = nullptr;
  if (idx >=0 && idx < count()) {
    SAFEARRAY* psa = nullptr;
    psa = lpDeviceList->EnumLabels();
    SafeArrayGetElement(psa, &idx, &labelBSTR);
    if (labelBSTR) {
      labelStd = _bstr_t(labelBSTR);
    } else {
      qDebug() << "Unable to get Label for idx " << idx << "\n";
    }
    SafeArrayDestroy(psa);
  }

  return labelStd;
}

std::string DeviceList::getSectionOfDeviceWithIdx(long idx)
{
  std::string labelStd;
  BSTR labelBSTR = nullptr;
  if (idx >=0 && idx < count()) {
    SAFEARRAY* psa = nullptr;
    psa = lpDeviceList->EnumSections();
    SafeArrayGetElement(psa, &idx, &labelBSTR);
    if (labelBSTR) {
      labelStd = _bstr_t(labelBSTR);
    } else {
      qDebug() << "Unable to get Label for idx " << idx << "\n";
    }
    SafeArrayDestroy(psa);
  }

  return labelStd;
}

}

Gamry::PotentioStat::PotentioStat(std::string &section)
  :lpPstat{nullptr}
{
  HRESULT hr = CoCreateInstance(__uuidof(GamryPstat), NULL, CLSCTX_ALL, __uuidof(IGamryPstat), reinterpret_cast<void**>(&lpPstat));
  if (FAILED(hr)) {
    std::cerr << "FAILED to create interface for IGamryPstat: " << hr << std::endl;
  }else {
    bstr_t sec{section.c_str()};
    hr = lpPstat->Init(sec.Detach());
    if (hr < 0)
      qDebug() << "Unable to init potentiostat\n";
    qDebug() << "DEBUG Created pointer to GamryPstat";
  }

}

Gamry::PotentioStat::~PotentioStat()
{
  if (lpPstat) {
    lpPstat->Release();
    qDebug() << "potentiostat released\n";
  } else
    qDebug() << "lpStat is null in destructor\n";

}

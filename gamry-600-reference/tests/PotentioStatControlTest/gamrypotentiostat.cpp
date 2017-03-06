#include "gamrypotentiostat.hpp"

namespace GamryPotentiostat {
DeviceList::DeviceList()
  : lpDeviceList{nullptr}
{
  HRESULT hr = CoCreateInstance(__uuidof(GamryDeviceList), nullptr, CLSCTX_ALL, __uuidof(IGamryDeviceList), reinterpret_cast<void**>(&lpDeviceList));
  if (FAILED(hr)) {
    std::cerr << "FAILED to create interface for IGamryDeviceList: " << hr << std::endl;
  }else {
    qDebug() << "DEBUG Created pointer to GamryDeviceList";
  }

}

DeviceList::~DeviceList()
{
  if (lpDeviceList) {
    lpDeviceList->Release();
    qDebug() << "DEBUG Released COM object GamryDeviceList\n";
  }
}

long DeviceList::count() const
{
  return lpDeviceList->Count();
}

std::string DeviceList::getLabelOfDeviceWithIdx(long idx)
{
  std::string labelStd;
  BSTR labelBSTR = nullptr;
  if (idx >=0 && idx < count()) {
    SAFEARRAY* psa = nullptr;
    psa = lpDeviceList->EnumSections();
    SafeArrayGetElement(psa, &idx, labelBSTR);
    labelStd = _bstr_t(labelBSTR);
    SafeArrayDestroy(psa);
  }

  return labelStd;
}
}

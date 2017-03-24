#ifndef POTENTIOSTAT_HPP
#define POTENTIOSTAT_HPP

#import "libid:BD962F0D-A990-4823-9CF5-284D1CDD9C6D" no_namespace
#include <atlbase.h>

namespace Gamry {
  class Potentiostat
  {

  public:
    explicit Potentiostat();
    ~Potentiostat();

  private:
    CComPtr<IGamryDeviceList> spDeviceList;
    CComPtr<IGamryPstat> spPstat;
    CComPtr<IGamryDtaqChrono> spDtaqChrono;
    CComPtr<IGamrySignalStep> spSignalStep;
  };
}


#endif // POTENTIOSTAT_HPP

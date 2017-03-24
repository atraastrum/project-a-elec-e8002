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

    // Returns the count of device connected. Call Count of GAMRYCOMLib::IGamryDeviceList
    long deviceCount();

    // Initializes GAMRYCOMLib::IGamryPstat and GAMRYCOMLib::IGamryDtaqChrono
    void init();

    // Initilize GAMRYCOMLib::IGamryStepSignal and set the signal with GAMRYCOMLib::IGamryPstat::SetSignal.
    // Think and Test what happens if setStepSignal is called before init
    void setStepSignal(float vInit, float tInit, float vFinal, float tFinal, float sampleRate);

    // Opens potentiostat and sets the cell to off position
    // When the the cell is off, the counter electrode is disconnected and no cell current can
    // flow. When the cell switch is in the on position, cell current can flow and counter
    // electrode is connected. This method also set some parameters by calling methods of
    // GAMRYCOMLib::IGamryPstat.
    void open();

    void start();

  private:
    CComPtr<IGamryDeviceList> spDeviceList;
    CComPtr<IGamryPstat> spPstat;
    CComPtr<IGamryDtaqChrono> spDtaqChrono;
    CComPtr<IGamrySignalStep> spSignalStep;
  };
}


#endif // POTENTIOSTAT_HPP

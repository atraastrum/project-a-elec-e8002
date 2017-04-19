#ifndef POTENTIOSTAT_HPP
#define POTENTIOSTAT_HPP

#import "libid:BD962F0D-A990-4823-9CF5-284D1CDD9C6D" no_namespace
#include <atlbase.h>
#include <vector>
#include "gamry.hpp"

namespace Gamry {

  class Potentiostat
  {

  public:
    explicit Potentiostat();
    ~Potentiostat();

    // Initializes GAMRYCOMLib::IGamryPstat and GAMRYCOMLib::IGamryDtaqChrono
    void init(const std::string &sectionName);

    // Initilize GAMRYCOMLib::IGamryStepSignal and set the signal with GAMRYCOMLib::IGamryPstat::SetSignal.
    // Think and Test what happens if setStepSignal is called before init
    void setStepSignal(float vInit, float tInit, float vFinal, float tFinal, float sampleRate);

    // Opens potentiostat and sets the cell to off position
    // When the the cell is off, the counter electrode is disconnected and no cell current can
    // flow. When the cell switch is in the on position, cell current can flow and counter
    // electrode is connected. This method also set some parameters by calling methods of
    // GAMRYCOMLib::IGamryPstat.
    void open();

    // Pontentiostat intializes the signal that was set with setStepSignal method.
    // Switches the cell switch on and run the experiment by calling GAMRYCOMLib::IGamryDtaqChrono::Run
    void start();

    // Swtiches the cell of and close potentiostat so that other programs can use it.
    void close();

    // Retrieve point_count CookInformationPoint points from the data acqusition queue
    std::vector<CookInformationPoint> pullDataItems(size_t point_count);

  private:
    CComPtr<IGamryPstat> spPstat;
    CComPtr<IGamryDtaqChrono> spDtaqChrono;
    CComPtr<IGamrySignalStep> spSignalStep;
  };
}


#endif // POTENTIOSTAT_HPP

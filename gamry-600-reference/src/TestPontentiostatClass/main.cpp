#include <iostream>
#include "../GamryChronoAmperometrySimpleUI/potentiostat.hpp"

int main()
{
  Gamry::Potentiostat pStat;

  if (pStat.deviceCount() > 0) {
    std::cout << "Found device, starting the test\n";
    pStat.init();
    pStat.open();
    // 10 seconds measurement
    pStat.setStepSignal(5.0f, 5.0f, -0.1f, 5.0f, 0.01f);


    size_t points_accuired = 0;
    do {
      Sleep(5000);
      std::vector<Gamry::CookInformationPoint> data = pStat.pullDataItems(100);
      points_accuired = data.size();
    }while(points_accuired > 0);

    pStat.close();
  } else
    std::cout << "Unable to find the device, closing this application\n";

  return 0;
}

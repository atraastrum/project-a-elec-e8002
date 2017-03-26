#include <iostream>
#include <fstream>
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
    std::fstream ofile;

    // CSV file format is used to store tabular data
    ofile.open("data.csv");
    do {
      Sleep(5000);
      std::vector<Gamry::CookInformationPoint> data = pStat.pullDataItems(100);
      points_accuired = data.size();
      for(int i = 0; i < data.size(); ++i)
      {
        Gamry::CookInformationPoint& item = data[i];
        ofile << item.Time << ';'
              << item.Im << ';'
              << item.Arch << ';'
              << item.IERange << ';'
              << item.Overload << ';'
              << item.Q << ';'
              << item.StopTest << ';'
              << item.Vf << ';'
              << item.Vsig << ';'
              << item.Vu << ';'
              << std::endl;
        std::cout << item.Time << ';'
              << item.Im << ';'
              << item.Arch << ';'
              << item.IERange << ';'
              << item.Overload << ';'
              << item.Q << ';'
              << item.StopTest << ';'
              << item.Vf << ';'
              << item.Vsig << ';'
              << item.Vu << ';'
              << std::endl;
      }

    }while(points_accuired > 0);

    ofile.close();
    pStat.close();
  } else
    std::cout << "Unable to find the device, closing this application\n";

  return 0;
}

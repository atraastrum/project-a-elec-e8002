#ifndef GAMRYPOTENTIOSTAT_H
#define GAMRYPOTENTIOSTAT_H
#include <windows.h>
#include <iostream>
#include <QDebug>

#import "libid:BD962F0D-A990-4823-9CF5-284D1CDD9C6D" no_namespace

namespace GamryPotentiostat {
class DeviceList {
public:
  DeviceList();
  ~DeviceList();

  long count() const;
  std::string getLabelOfDeviceWithIdx(long idx);
private:
  IGamryDeviceListPtr lpDeviceList;
};
}

#endif // GAMRYPOTENTIOSTAT_H

#ifndef GAMRYPOTENTIOSTAT_H
#define GAMRYPOTENTIOSTAT_H
#include <windows.h>
#include <iostream>
#include <atlbase.h>
#include <QDebug>

#import "libid:BD962F0D-A990-4823-9CF5-284D1CDD9C6D" no_namespace

namespace Gamry {
  class exception {
  public:
    exception(std::string &msg) : message{msg} {}
    exception(const char* msg) : message{msg} {}

    std::string message;
  };

  class com_exception : public exception {
  public:
    com_exception(std::string &msg, HRESULT error) : exception{msg}, code{error} {}
    com_exception(const char* msg, HRESULT error) : exception{msg}, code{error} {}

    HRESULT code;
  };

  class DeviceList {
  public:
    DeviceList();
    ~DeviceList();

    long count() const;
    std::string getLabelOfDeviceWithIdx(long idx);
    std::string getSectionOfDeviceWithIdx(long idx);

  private:
    IGamryDeviceListPtr lpDeviceList;
  };

  class PotentioStat {
  public:
    PotentioStat(std::string &section);
    ~PotentioStat();
    IGamryPstatPtr getRawPtr() {return lpPstat;}
  private:
    IGamryPstatPtr lpPstat;
  };
}

#endif // GAMRYPOTENTIOSTAT_H

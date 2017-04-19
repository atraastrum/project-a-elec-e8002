#ifndef GAMRY_HPP
#define GAMRY_HPP

namespace Gamry {
struct CookInformationPoint
{
  float Time;    // Time of measurment
  float Vf;      // Measured E vs. Eref
  float Vu;      // Uncompensated voltage
  float Im;      // Applied or Measured? current
  float Q;       //
  float Vsig;    // Signal sent to Contrl Amp
  float Arch;    // Measured Aux channel voltage
  int IERange;   //
  int Overload;  // Hexadecimal number reprsenting overload status
  int StopTest;  //
  };
}



#endif // GAMRY_HPP

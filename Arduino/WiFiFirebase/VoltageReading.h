#ifndef VoltageReading_h
#define VoltageReading_h

#include "Arduino.h"

class VoltageReading
{
  public:
    VoltageReading();
    VoltageReading(double volt, double kR, double uR);
    double voltage;
    double knownR;
    double unkownR;
    String ToJSON();
};

#endif
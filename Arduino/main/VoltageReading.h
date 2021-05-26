#ifndef VoltageReading_h
#define VoltageReading_h

#include "Arduino.h" 
typedef arduino::String String;

class VoltageReading
{
  public:
    double voltage;
    double knownR;
    double unkownR;
    VoltageReading();
    VoltageReading(double volt, double kR, double uR);
    String ToJSON();
};

#endif
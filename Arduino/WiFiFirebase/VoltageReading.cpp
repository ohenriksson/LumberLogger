#include "Arduino.h"
#include "VoltageReading.h"

VoltageReading::VoltageReading(double volt, double kR, double uR){
      voltage = volt;
      knownR = kR;
      unkownR = uR;
    }

String VoltageReading::ToJSON(){
  return "{\"volt\":" + String(voltage, DEC) + ","
    + "\"knownR\":" + String(knownR, DEC) + ","
    + "\"unkownR\":" + String(unkownR, DEC) + "}";
}
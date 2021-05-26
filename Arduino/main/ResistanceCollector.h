#ifndef ResistanceCollector_h
#define ResistanceCollector_h

#include <Arduino.h>
#include "VoltageReading.h"
#include "SensorEnum.h"

typedef arduino::String String;

  const bool DEVMODE = true;
  const int led_pin = 13;
  const int sensorPin = A0; 
  const int enableA = A1; 
  const int enableB = A2; 

  const double DiodeVoltage = 0.7;
  const double AnalogMax = 4096.000;
  const double VoltMax = 3.300;
  const double VoltApplied = 3.300;

  const double resA = 1000000 * 3.3; //3.3M
  const double resB = 1000000 * 220; //220M

class ResistanceCollector {
  private:
    int voltageToggleDelay;
    bool Initiated;

  public:
    void EnableA();
    void DisableAll();
    void EnableB();

    ResistanceCollector();
    ResistanceCollector(int delayToggle);     

    void SetupPins();

      VoltageReading ReadSensor(arduino::String sensor);
      void ReadSensorNTimes(VoltageReading *readings, arduino::String sensor, int nTimes);

      double ConvertToVolt(double analogValue);

      double VoltToOhm(double sensorVolt, double knownR);

      double GetVoltageOver(arduino::String sensor);

      double ReadValueA();

      double ReadValueB();

      double GetKnownResistanceFor(arduino::String sensor);

      void ReadAndPrintValue(arduino::String sensor);
};
#endif
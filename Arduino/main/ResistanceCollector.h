#ifndef ResistanceCollector_h
#define ResistanceCollector_h

#include <Arduino.h>
#include "VoltageReading.h"

#include "SensorEnum.h"

class ResistanceCollector {
  private:
        int voltageToggleDelay;

    public:
        bool Initiated;

        ResistanceCollector();
        ResistanceCollector(int delayToggle);     

        void SetupPins();

        VoltageReading ReadSensor(String sensor);
        void ReadSensorNTimes(VoltageReading *readings, String sensor, int nTimes);


        double ConvertToVolt(double analogValue);

        double VoltToOhm(double sensorVolt, double knownR);

        double ReadValueA();

        double ReadValueB();

        double GetKnownResistanceFor(String sensor);

        void ReadAndPrintValue(String sensor);
};



#endif
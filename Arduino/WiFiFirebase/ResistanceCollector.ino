#include "VoltageReading.h"
#include "SensorEnum.h"
#include "Arduino.h"

class ResistanceCollector {
  private:
    const int led_pin = 13;
    const int sensorPin = A0; 
    const int enableA = A1; 
    const int enableB = A2; 

    const double AnalogMax = 4096.000;
    const double VoltMax = 3.300;
    const double VoltApplied = 3.300;

    int voltageToggleDelay;

    const double resA = 1000000 * 3.3; //3.3M
    const double resB = 1000000 * 220; //220M

    
    void EnableA() {
      digitalWrite(enableA, HIGH);
      digitalWrite(enableB, LOW);
    }

    void DisableAll() {
      digitalWrite(enableA, LOW);
      digitalWrite(enableB, LOW);
    }

    void EnableB() {
      digitalWrite(enableA, LOW);
      digitalWrite(enableB, HIGH);
    }

  public:
    bool Initiated = false;

    ResistanceCollector(int delayToggle) {
      voltageToggleDelay = delayToggle;
    }

    void SetupPins() {
      analogReadResolution(12);
      pinMode(led_pin, OUTPUT);
      pinMode(enableA, OUTPUT);
      pinMode(enableB, OUTPUT);

      Serial.begin(9600);
      //while (!Serial) {
        //; // wait for serial port to connect. Needed for native USB port only
      //}
      Initiated = true;
    }

    double ConvertToVolt(double analogValue) {
      return analogValue / AnalogMax * VoltMax;
    }

    double VoltToOhm(double sensorVolt, double knownR) {
      if (VoltApplied - sensorVolt < 0.3) return 0; //error, prevent overflow
      return knownR * sensorVolt / (VoltApplied - sensorVolt);
    }

    double ReadValueA() {
      EnableA();
      delay(voltageToggleDelay);
      double valueA = analogRead(sensorPin);
      delay(voltageToggleDelay);
      DisableAll();
      return valueA;
    }

    double ReadValueB() {
      EnableB();
      delay(voltageToggleDelay);
      double valueB = analogRead(sensorPin);
      delay(voltageToggleDelay);
      DisableAll();
      return valueB;
    }

    double GetKnownResistanceFor(String sensor){
      if (sensor == SensorEnum::sensorA)
      {
        return resA;
      }
      else if (sensor == SensorEnum::sensorB)
      {
        return resB;
      }
    }

    double GetVoltageOver(String sensor) {
      double volt = 0;
      if (sensor == SensorEnum::sensorA)
      {
        double valueA = ReadValueA();
        volt = ConvertToVolt(valueA);
      }
      else if (sensor == SensorEnum::sensorB)
      {
        double valueB = ReadValueB();
        volt = ConvertToVolt(valueB);
      }

      return volt;
    }

    VoltageReading ReadSensor(String sensor){
      double knownR = GetKnownResistanceFor(sensor);
      double voltNow = GetVoltageOver(sensor);
      double unknownR = VoltToOhm(voltNow, knownR);
      return VoltageReading(voltNow, knownR, unknownR);
    }

    void ReadSensorNTimes(VoltageReading readings[], String sensor, int nTimes){

      if(sensor == SensorEnum::sensorA){
        EnableA();
      }else{
        EnableB();
      }
      
      for(int x=0; x<nTimes; x++){
        delay(voltageToggleDelay);
        double voltNow = analogRead(sensorPin);
        double knownR = GetKnownResistanceFor(sensor);
        double unknownR = VoltToOhm(voltNow, knownR);
        readings[x] = VoltageReading(voltNow, knownR, unknownR);
      }
      DisableAll();
      
    }

    void ReadAndPrintValue(String sensor) {
      double voltNow = GetVoltageOver(sensor);
      double knownR = GetKnownResistanceFor(sensor);
    }
};
#include <Arduino.h>
#include "VoltageReading.h"
#include "SensorEnum.h"
#include "ResistanceCollector.h"

typedef arduino::String String;

    ResistanceCollector :: ResistanceCollector(){}

    ResistanceCollector :: ResistanceCollector(int delayToggle) {
      voltageToggleDelay = delayToggle;
    }

    void ResistanceCollector :: SetupPins() {
      analogReadResolution(12);
      if(DEVMODE){
        pinMode(led_pin, OUTPUT);
      }
      pinMode(sensorPin, INPUT);
      pinMode(enableA, OUTPUT);
      pinMode(enableB, OUTPUT);

      Serial.begin(9600);
      if(DEVMODE){
        while (!Serial) {
          ; // wait for serial port to connect. Needed for native USB port only
        }
      }
      Initiated = true;
    }

    double ResistanceCollector :: ConvertToVolt(double analogValue) {
      return analogValue / AnalogMax * VoltMax;
    }

    double ResistanceCollector :: VoltToOhm(double sensorVolt, double knownR) { //R2 = R1 * u2/(Utot-u2-d1)
      if (VoltApplied - sensorVolt - DiodeVoltage < 0.3) return 0; //error, prevent overflow
      return knownR * sensorVolt / (VoltApplied - sensorVolt - DiodeVoltage);
    }

    double ResistanceCollector :: ReadValueA() {
      EnableA();
      delay(voltageToggleDelay);
      double valueA = analogRead(sensorPin);
      delay(voltageToggleDelay);
      DisableAll();
      return valueA;
    }

    double ResistanceCollector :: ReadValueB() {
      EnableB();
      delay(voltageToggleDelay);
      double valueB = analogRead(sensorPin);
      delay(voltageToggleDelay);
      DisableAll();
      return valueB;
    }

    double ResistanceCollector :: GetKnownResistanceFor(String sensor){
      if (sensor == SensorEnum::sensorA)
      {
        return resA;
      }
      else if (sensor == SensorEnum::sensorB)
      {
        return resB;
      }
    }

    double ResistanceCollector :: GetVoltageOver(arduino::String sensor) {
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

    VoltageReading ResistanceCollector :: ReadSensor(arduino::String sensor){
      double knownR = GetKnownResistanceFor(sensor);
      double voltNow = GetVoltageOver(sensor);
      double unknownR = VoltToOhm(voltNow, knownR);
      return VoltageReading(voltNow, knownR, unknownR);
    }

    void ResistanceCollector :: ReadSensorNTimes(VoltageReading *readings, arduino::String sensor, int nTimes){
      if(sensor == SensorEnum::sensorA){
        if(DEVMODE){
          Serial.print("Reading A");
        }
        EnableA();
      }else{
        if(DEVMODE){
          Serial.print("Reading B");
        }
        EnableB();
      }
      
      for(int x=0; x<nTimes; x++){
        delay(voltageToggleDelay);
        double voltNow = analogRead(sensorPin);
        double knownR = GetKnownResistanceFor(sensor);
        double unknownR = VoltToOhm(voltNow, knownR);
        readings[x] = VoltageReading(voltNow, knownR, unknownR);
        if(DEVMODE){
          Serial.print("Voltage: ");
          Serial.print(voltNow);
        }
      }
      DisableAll();
      Serial.println("");
    }

    void ResistanceCollector :: ReadAndPrintValue(arduino::String sensor) {
      double voltNow = GetVoltageOver(sensor);
      double knownR = GetKnownResistanceFor(sensor);
    }

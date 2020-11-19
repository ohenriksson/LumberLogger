#include "VoltageReading.h"

const int nReads = 100;
double readArray1[100];
double readArray2[100];

ResistanceCollector coll1 = ResistanceCollector(10);
 
void setup() { 
  coll1.SetupPins();
  Serial.println("Resistance setup complete");
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){
  ExecuteReadingsAndPublish();
  delay(1000 * 60 * 60);
}

void ExecuteReadingsAndPublish(){
  String r1Array = "";
  String r2Array = "";
  String jsonRead = "";
  VoltageReading readings[nReads];
  
  readings = coll1.ReadSensorNTimes(*readings, SensorEnum::sensorA, nReads);

  for(int j=0; j<nReads; j++){
    r1Array += "\"" + String(readings.voltage[j], DEC) + "\"";
    r2Array += "\"" + String(readings.voltage[j], DEC) + "\"";

    if(j < nReads-1){
      r1Array += ",";
      r2Array += ",";
    }
  }
  
  jsonRead = "{\"R1\":[" + r1Array  + "]," + "\"R2\":[" + r2Array + "]}";
  FirebaseSet(jsonRead);
}

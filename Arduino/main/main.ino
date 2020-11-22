
#include "VoltageReading.h"
#include "FirebaseCruncher.h"
#include "ResistanceCollector.h"

const int nReads = 100;
ResistanceCollector coll1;
 
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

void ExecuteReadingsAndPublish()
{
  String r1Array = "";
  String r2Array = "";
  String jsonRead = "";
  VoltageReading readingsA [nReads];
  VoltageReading readingsB [nReads];
  
  coll1.ReadSensorNTimes(readingsA, SensorEnum::sensorA, nReads);

  for(int j=0; j<nReads; j++){
    r1Array += "\"" + String(readingsA[j].voltage, DEC) + "\"";
    r2Array += "\"" + String(readingsB[j].voltage, DEC) + "\"";

    if(j < nReads-1){
      r1Array += ",";
      r2Array += ",";
    }
  }
  
  jsonRead = "{\"R1\":[" + r1Array  + "]," + "\"R2\":[" + r2Array + "]}";
  FirebaseSet(jsonRead);
}

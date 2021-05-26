#include "Arduino.h"

#include "publisher.h"
#include "VoltageReading.h"
#include "FirebaseCruncher.h"
#include "ResistanceCollector.h"

ResistanceCollector* coll1 = new ResistanceCollector(10000);

void setup() { 
  coll1->SetupPins();
  Serial.println("Resistance setup complete");
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){
  ExecuteReadingsAndPublish(coll1);
  delay(1000 * 30);
}


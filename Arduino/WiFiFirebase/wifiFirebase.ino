int status = WL_IDLE_STATUS;
int nReads = 10;
double readArray1[nReads];
double readArray2[nReads];

ResistanceCollector coll1 = ResistanceCollector(1);
 
void setup() { 
  coll1.SetupPins();
  Serial.println("Resistance setup complete");
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){
  averageOver64();
  
  delay(1000 * 60 * 60);
}

void averageOver64(){
  string r1Array = "";
  string r2Array = "";
  String jsonRead = "";
  
  doNMeasurements(nReads);

  for(int j=0; j<nReads; j++){
    r1Array += "\"" + String(readArray1[j], DEC) + "\"";
    r2Array += "\"" + String(readArray2[j], DEC) + "\"";

    if(j-1 < nReads){
      r1Array += ",";
      r2Array += ",";
    }
  }
  
  jsonRead = "{\"R1\":[" + r1Array  + "]," + "\"R2\":[" + r2Array + "]}";
  FirebaseSet(jsonRead);
}

double doNMeasurements(int nMeas){
  for(int i=0; i<nMeas; i++){
    doReadingAndPost(i);
  } 
}

void doReadingAndPost(int i){
  VoltageReading read1 = coll1.ReadSensor(SensorEnum::sensorA);
  readArray1[i]=read1.unkownR;
  
  VoltageReading read2 = coll1.ReadSensor(SensorEnum::sensorB);
  readArray2[i]=read2.unkownR;
  


}

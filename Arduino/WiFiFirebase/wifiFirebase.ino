int status = WL_IDLE_STATUS;
double readArray1[5];
double readArray2[5];

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
  double avg = 0;
  double avg2 = 0;
  String jsonRead = "";
  
  for(int i=0; i < 64; i++){
    double sum = 0;
    double sum2 = 0;
    doNMeasurements(5);
    for(int j=0; j<5; j++){
      
      sum += readArray1[j] / 5.0;
      sum2 += readArray2[j] / 5.0;
      if(readArray1[j] == 0){
        sum = 0; //make sure we set it to 0 if any single value is zero (out of bounds anyways)
      }
      if(readArray2[j] == 0){
        sum2 = 0; //make sure we set it to 0 if any single value is zero (out of bounds anyways)
      }
    }
    avg += sum/64;
    avg2 += sum2/64;
  }


  Serial.print(avg);
  Serial.print(" ");
  Serial.print(avg2);
  Serial.print("\n");
  
  jsonRead = "{\"R1\":" + String(avg, DEC) + "," + "\"R2\":" + String(avg2, DEC) + "}";
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

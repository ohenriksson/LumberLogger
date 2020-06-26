int status = WL_IDLE_STATUS;
double readArray1[5];
double readArray2[5];
double spruceArray[] = {22400 , 5890,  2140,  830, 365, 165, 83,  44,  25.1,  15.5,  9.8, 6.3, 4.27,  3.02,  2.14,  1.58,  1.17,  0.91,  0.71}; //7 -> 25

ResistanceCollector coll1 = ResistanceCollector(1);
 
void setup() { 
  coll1.SetupPins();
  Serial.println("Resistance setup complete");
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){

  averageOver(500);

}

void averageOver(int milliS){
  double avg = 0;
  double sum = 0;
  double sum2 = 0;
  
  for(int i=0; i < milliS; i+=10){
    doNMeasurements(5);
     for(int i=0; i<5; i++){
       sum += readArray1[i]/5;
       sum2 += readArray2[i]/5;
    }
  }

  Serial.print(sum);
  Serial.print(" ");
  Serial.print(sum2);
  Serial.print("\n");
}

double doNMeasurements(int nMeas){
  double sum = 0;
  double sum2 = 0;
  
  for(int i=0; i<nMeas; i++){
    doReadingAndPost(i);
  }
  
  for(int i=0; i<nMeas; i++){
    sum += readArray1[i];
    sum2 += readArray2[i];
  }
  
}

void doReadingAndPost(int i){
  VoltageReading read1 = coll1.ReadSensor(SensorEnum::sensorA);
  readArray1[i]=read1.unkownR;
  
  VoltageReading read2 = coll1.ReadSensor(SensorEnum::sensorB);
  readArray2[i]=read2.unkownR;
  
  //String jsonRead2 = read2.ToJSON();
  //Serial.println("json:" + jsonRead1);
  //Serial.println("json:" + jsonRead2);

  //Serial.println("Set values");
  //FirebaseSet(jsonRead1);
  //FirebaseSet(jsonRead2);

}

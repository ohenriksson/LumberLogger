int status = WL_IDLE_STATUS;

ResistanceCollector coll1 = ResistanceCollector();
 
void setup() { 
  coll1.SetupPins();
  Serial.println("Resistance setup complete");
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){
  Serial.println("Get resistance");
  VoltageReading read1 = coll1.ReadSensor(SensorEnum::sensorA);
  String jsonRead1 = read1.ToJSON();
  Serial.println("json:" + jsonRead1);
  VoltageReading read2 = coll1.ReadSensor(SensorEnum::sensorB);
  String jsonRead2 = read2.ToJSON();
  
  Serial.println("json:" + jsonRead2);
  
  //FirebaseGet();
  Serial.println("Set values");
  FirebaseSet(jsonRead1);
  FirebaseSet(jsonRead2);
  delay(10*1000);
}

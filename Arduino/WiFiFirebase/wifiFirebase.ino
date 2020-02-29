int status = WL_IDLE_STATUS;
 
void setup() { 
  FirebaseSetup();
  Serial.println("Setup complete");
} 

void loop(){
  Serial.println("Get values");
  FirebaseGet();
  delay(10*1000);
}

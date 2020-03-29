
int led_pin = 13;
int sensorPin = A0; //A0    // select the input pin for the potentiometer
int enableA = A1; //A1
int enableB = A2; //A2

int sensorValue = 0;  // variable to store the value coming from the sensor


float AnalogMax = 1024.0;
float VoltMax = 3.30;
float VoltNow = 0;
float VoltApplied = 3.28;

double resA = 1000000 * 3.3; //3.3M
double resB = 1000000 * 220; //220M

int delay1 = 2000;
int pauseDelay = 5000;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  EnableA();
  delay(delay1); 
  ReadValue(resA, "sensor A");
  delay(delay1); 
  DisableAll();
  
  delay(pauseDelay);

  EnableB();
  delay(delay1); 
  ReadValue(resB, "sensor B");
  delay(delay1);
  DisableAll(); 
}

float ConvertToVolt(float analogValue){
  return analogValue * (VoltMax / AnalogMax);
}

float VoltToOhm(float sensorVolt, float knownR){
  return knownR * sensorVolt / (VoltApplied - sensorVolt);
}

void ReadValue(int knownR, String sensor){
  Serial.print(sensor + " -- ");
  sensorValue = analogRead(sensorPin);
  
  VoltNow = ConvertToVolt(sensorValue);
  Serial.print(VoltNow);
  Serial.print("V ");
  Serial.print(VoltToOhm(VoltNow, knownR));
  Serial.print("Ohm --- \n ");
}

void EnableA(){
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, LOW);
}

void DisableAll(){
  digitalWrite(enableA, LOW);
  digitalWrite(enableB, LOW);
}

void EnableB(){
  digitalWrite(enableA, LOW);
  digitalWrite(enableB, HIGH);
}

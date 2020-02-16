
int led_pin = 13;
int enableA = 7;
int enableB = 6;

int inputA = 3;
int inputB = 2;

int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorPin = A0;    // select the input pin for the potentiometer

float AnalogMax = 1024.0;
float VoltMax = 3.3;
float VoltNow = 0;
float VoltApplied = 5;

int resA = 1000000;
int resB = 10000;

int delay1 = 1500;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(inputA, OUTPUT);
  pinMode(inputB, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  EnableA();
  delay(100); 
  ReadValue(resA);
  delay(delay1); 
  EnableB();
  delay(100); 
  ReadValue(resB);
  delay(delay1); 
}

float ConvertToVolt(float analogValue){
  return analogValue * (VoltMax / AnalogMax);
}

float VoltToOhm(float sensorVolt, float knownR){
  return knownR * sensorVolt / (VoltApplied - sensorVolt);
}

void ReadValue(int knownR){
  sensorValue = analogRead(sensorPin);
  
  VoltNow = ConvertToVolt(sensorValue);
  Serial.print(VoltNow);
  Serial.print("V ");
  Serial.print(VoltToOhm(VoltNow, knownR));
  Serial.print("Ohm --- \n ");
}

void EnableA(){
  digitalWrite(led_pin, HIGH);
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, LOW);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, LOW);
}

void EnableB(){
  digitalWrite(led_pin, LOW);
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, HIGH);
  digitalWrite(enableA, LOW);
  digitalWrite(enableB, HIGH);
}

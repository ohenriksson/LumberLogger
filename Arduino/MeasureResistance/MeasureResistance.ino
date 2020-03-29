
int led_pin = 13;
int sensorPin = A0; //A0    // select the input pin for the potentiometer
int enableA = A1; //A1
int enableB = A2; //A2

int sensorValueA = 0;  // variable to store the value coming from the sensor
int sensorValueB = 0;  // variable to store the value coming from the sensor

float AnalogMax = 1024.000;
float VoltMax = 3.300;
float VoltNow = 0;
float VoltApplied = 3.300;

double resA = 1000000 * 3.3; //3.3M
double resB = 1000000 * 220; //220M

int delay1 = 1000;
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
  ReadAndPrintValue(resA, "sensor A"); 
  delay(pauseDelay);
  ReadAndPrintValue(resB, "sensor B");
  delay(pauseDelay);
}

float ConvertToVolt(float analogValue){
  return analogValue * (VoltMax / AnalogMax);
}

float VoltToOhm(float sensorVolt, float knownR){
  if(VoltApplied-sensorVolt < 0.01) return 0; //error, prevent overflow
  return knownR * sensorVolt / (VoltApplied - sensorVolt);
}

void ReadAndPrintValue(int knownR, String sensor){

  Serial.print(sensor + " -- ");
  if(sensor == "sensor A")
  {
    ReadValueA();
    VoltNow = ConvertToVolt(sensorValueA);
  }
  else if(sensor == "sensor B")
  {
    ReadValueB();
    VoltNow = ConvertToVolt(sensorValueB);
  } 
  
  Serial.print(VoltNow);
  Serial.print("V ");
  Serial.print(VoltToOhm(VoltNow, knownR));
  Serial.print("Ohm --- \n");
}

int ReadValueA(){
  EnableA();
  delay(delay1); 
  sensorValueA = analogRead(sensorPin);
  delay(delay1);
  DisableAll(); 
}

int ReadValueB(){
  EnableB();
  delay(delay1); 
  sensorValueB = analogRead(sensorPin);
  delay(delay1); 
  DisableAll();
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

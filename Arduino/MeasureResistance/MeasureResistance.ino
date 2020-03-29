
class SensorEnum{
 public:
  static String sensorA;
  static String sensorB;
};
String SensorEnum::sensorA = "sensor A";
String SensorEnum::sensorB = "sensor B";

class ResistanceCollector {
  private:
    const int led_pin = 13;
    const int sensorPin = A0; //A0    // select the input pin for the potentiometer
    const int enableA = A1; //A1
    const int enableB = A2; //A2

    const float AnalogMax = 1024.000;
    const float VoltMax = 3.300;
    const float VoltApplied = 3.300;

    const int delay1 = 2000;
    const int pauseDelay = 5000;

    const double resA = 1000000 * 3.3; //3.3M
    const double resB = 1000000 * 220; //220M

    
    void EnableA() {
      digitalWrite(enableA, HIGH);
      digitalWrite(enableB, LOW);
    }

    void DisableAll() {
      digitalWrite(enableA, LOW);
      digitalWrite(enableB, LOW);
    }

    void EnableB() {
      digitalWrite(enableA, LOW);
      digitalWrite(enableB, HIGH);
    }

  public:
    bool Initiated = false;

    ResistanceCollector() {
    }

    void SetupPins() {
      pinMode(led_pin, OUTPUT);
      pinMode(enableA, OUTPUT);
      pinMode(enableB, OUTPUT);

      Serial.begin(9600);
      while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
      }
      Initiated = true;
    }

    float ConvertToVolt(float analogValue) {
      return analogValue * (VoltMax / AnalogMax);
    }

    float VoltToOhm(float sensorVolt, float knownR) {
      if (VoltApplied - sensorVolt < 0.1) return 0; //error, prevent overflow
      return knownR * sensorVolt / (VoltApplied - sensorVolt);
    }

    int ReadValueA() {
      EnableA();
      delay(delay1);
      float valueA = analogRead(sensorPin);
      delay(delay1/2);
      DisableAll();
      return valueA;
    }

    int ReadValueB() {
      EnableB();
      delay(delay1);
      float valueB = analogRead(sensorPin);
      delay(delay1/2);
      DisableAll();
      return valueB;
    }


    float GetVoltageOver(String sensor) {
      float volt = 0;
      if (sensor == SensorEnum::sensorA)
      {
        float valueA = ReadValueA();
        volt = ConvertToVolt(valueA);
      }
      else if (sensor == SensorEnum::sensorB)
      {
        float valueB = ReadValueB();
        volt = ConvertToVolt(valueB);
      }
      return volt;
    }

    void ReadAndPrintValue(int knownR, String sensor) {
      Serial.print(sensor + " -- ");
      float voltNow = GetVoltageOver(sensor);
      Serial.print(voltNow);
      Serial.print("V ");
      Serial.print(VoltToOhm(voltNow, knownR));
      Serial.print("Ohm --- \n");
    }

    void Loop() {
      ReadAndPrintValue(resA, SensorEnum::sensorA);
      delay(pauseDelay);
      ReadAndPrintValue(resB, SensorEnum::sensorB);
      delay(pauseDelay);
    }
};


ResistanceCollector coll1 = ResistanceCollector();

void setup() {
  coll1.SetupPins();
}

void loop() {
  coll1.Loop();
}

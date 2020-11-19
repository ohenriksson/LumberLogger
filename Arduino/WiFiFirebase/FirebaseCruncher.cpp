#include "FirebaseCruncher.h"
#include "C:/staticVars.h"

#include <Firebase_Arduino_WiFiNINA.h>


FirebaseData firebaseData;
int val = 0;

void FirebaseSetup(){
  delay(1000);
  //Serial.begin(9600);
  Serial.println("Initiating...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, SSID1, PASS1);
  Firebase.reconnectWiFi(true);
}

void FirebaseGet(){
  if (Firebase.getInt(firebaseData, "/Moisture/Logs/s1")){
    if (firebaseData.dataType() == "int"){
      val = firebaseData.intData();
      Serial.println(val);
    }

  } else {
    //Failed, then print out the error detail
    Serial.println(firebaseData.errorReason());
  }
}

void FirebaseSet(String data){

  String jsonData = "{\"data\":" + data + "}";
  Serial.println("jsonData:" + jsonData);

  if (Firebase.pushJSON(firebaseData, "/Moisture/Logs", jsonData)) {
    Firebase.pushTimestamp(firebaseData, "/Moisture/Logs/" + firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());
  } 
  else {
    //Failed, then print out the error detail
    Serial.println(firebaseData.errorReason());
  }
}

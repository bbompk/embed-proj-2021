#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define rxPin D1
#define txPin D2
//#define FIREBASE_HOST "embed-lab-project-1278d-default-rtdb.asia-southeast1.firebasedatabase.app"
//#define FIREBASE_AUTH "qSiFI9OBlWrtxKutCu85LsNu9lQVwbMQsgxUOlaG"

#define FIREBASE_HOST "emb-proj-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Vs9W3BJmKmBeoeOBDY6eJlhWjFZ8lskARTbAymuy"
#define WIFI_SSID "Siriramphai"
#define WIFI_PASSWORD "sr250809"

// Global number of people
int people_number = 0;

SoftwareSerial NodeSerial(rxPin, txPin);

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  NodeSerial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void update_people() {
   // set Float  value
   Firebase.setInt("people", people_number);
   
   // handle error
   if (Firebase.failed()) {
       Serial.print("setting /people number failed:");
       Serial.println(Firebase.error());  
       return;
   }
   delay(100);
}

void loop(){
  if (WiFi.status() == WL_CONNECTED){
    if(NodeSerial.available()) {
      people_number = Firebase.getInt("people");
      while(NodeSerial.available()) {
        int data_rcvd = NodeSerial.read();   // read one byte from serial buffer and save to data_rcvd
    
        if (data_rcvd == 'i') {
          people_number++;
          Serial.println('i');
          Serial.println(people_number);
          update_people();
  //        Serial.println(Firebase.getFloat("people"));
        }
        else if (data_rcvd == 'o' && people_number > 0) {
          people_number--;
          Serial.println('o');
          Serial.println(people_number);
          update_people();
        }
      }
    }else{
      people_number = Firebase.getInt("people");
      if(people_number%2 == 1){
        people_number++;
        update_people();
      }
    }
  }
}

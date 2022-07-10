#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

#define DHT11_PIN D2
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

// Set these to run example.
#define FIREBASE_HOST "data-db1b1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "aBKmOdtovpFGIgx6Z3wXLnkBvvT88SJTX3Hi2Qv8"
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "ojokbucinta"

float pushedTemp;

void setup() {
  Serial.begin(9600);
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
  dht.begin();
}

int id = 0;
String patch = "data/";

void loop() {
  // set value
//  Firebase.setFloat("number", 42.0);
  // handle error
  float temp = dht.readTemperature();

//  Serial.print(temp);
//  Serial.println("");

  pushedTemp = float(temp);
  String patchSuhu = "data/" + String(id) + "/suhu/";
  String patchMessage = "data/" + String(id) + "/message/";
  
  if(Firebase.failed()){
    Serial.println("Gagal terhubung Firebase!!");
  }else{
    if(temp >= 10 && temp <= 30){
       Firebase.setFloat(patchSuhu, pushedTemp);
       Firebase.setString(patchMessage, "Waktunya membuka");
    }else{
       Firebase.pushFloat(patchSuhu, pushedTemp);
       Firebase.pushString(patchMessage, "Belum waktunya membuka");
    }
  }
  delay(2000);
  id++;
  
//  if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//  
//  // update value
//  Firebase.setFloat("number", 43.0);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//
//  // get value 
//  Serial.print("number: ");
//  Serial.println(Firebase.getFloat("number"));
//  delay(1000);
//
//  // remove value
//  Firebase.remove("number");
//  delay(1000);
//
//  // set string value
//  Firebase.setString("message", "hello world");
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /message failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//  
//  // set bool value
//  Firebase.setBool("truth", false);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /truth failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//
//  // append a new value to /logs
//  String name = Firebase.pushInt("logs", n++);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("pushing /logs failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  Serial.print("pushed: /logs/");
//  Serial.println(name);
//  delay(1000);
}

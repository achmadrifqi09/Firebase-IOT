#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

#define DHT11_PIN D2
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);


#define FIREBASE_HOST "data-db1b1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "aBKmOdtovpFGIgx6Z3wXLnkBvvT88SJTX3Hi2Qv8"
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "ojokbucinta"

float pushedTemp;

void setup() {
  Serial.begin(9600);

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

  float temp = dht.readTemperature();


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
  


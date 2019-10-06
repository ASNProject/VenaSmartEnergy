#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "vena3-f6288.firebaseio.com"
#define FIREBASE_AUTH "L8jVztR50AgHymBHqxTliXRMQRU6N8ifMydif8B1"
//#define WIFI_SSID "Miskin ya?Kuota be radue wkwkwkw" // Change the name of your WIFI
//#define WIFI_PASSWORD "arief.dulep" // Change the password of your WIFI
#define WIFI_SSID "R" // Change the name of your WIFI
#define WIFI_PASSWORD "1234567888" // Change the password of your WIFI
 
void setup() {
  // Initialize Serial port
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;

  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("Watt",0);
  Firebase.set("Volt",0);
  Firebase.set("Current",0);
  Firebase.set("Volt1",0);
  Firebase.set("Current1",0);
}
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  //Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  //Pengirim1
  Serial.print("Arus node1 ");
  double data1=root["arusnode"];
  Serial.println(data1);
  Firebase.set("Arusnode1",data1);
  Serial.print("Tegangan node1 ");
  double data2=root["voltnode"];
  Serial.println(data2);
  Firebase.set("Voltnode1",data2);

  //Pengirim 2
  Serial.print("Arus node2 ");
  double data3=root["arusnode1"];
  Serial.println(data1);
  Firebase.set("Arusnode2",data1);
  Serial.print("Tegangan node2 ");
  double data4=root["voltnode1"];
  Serial.println(data2);
  Firebase.set("Voltnode2",data2);
  
}

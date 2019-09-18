#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "vena3-f6288.firebaseio.com"
#define FIREBASE_AUTH "L8jVztR50AgHymBHqxTliXRMQRU6N8ifMydif8B1"
#define WIFI_SSID "Miskin ya?Kuota be radue wkwkwkw" // Change the name of your WIFI
#define WIFI_PASSWORD "arief.dulep" // Change the password of your WIFI


const int sensorIn = A0;
int mVperAmp = 66; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup(){
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
  //Firebase.set("Volt",0);
  Firebase.set("Current",0);

  
pinMode(A0, INPUT);
Serial.begin(9600);
//delay(10);
//Serial.println(F("Init...."));
}

void loop(){
Voltage = getVPP();
VRMS = (Voltage/2.0) *0.707; // sq root
AmpsRMS = (VRMS * 1000)/mVperAmp;
float Wattage = (220*AmpsRMS)-18; //Observed 18-20 Watt when no load was connected, so substracting offset value to get real consumption.

 float hasil = AmpsRMS;
  Serial.print("Hasil = ");
  Serial.print(hasil);
  if (hasil < 0.20){
    Serial.print("\n POOR");  
  }
  else{
    Serial.print("\n GOOD");
  }
  
Serial.print(AmpsRMS);
Serial.println("\n Amps RMS ");
Serial.print(Wattage);
Serial.println("\n Watt ");
Firebase.set("Watt",Wattage);
Firebase.set("Current",AmpsRMS);
Firebase.set("Status",hasil);
delay(100);
}

float getVPP()
{
float result;

int readValue; //value read from the sensor
int maxValue = 0; // store max value here
int minValue = 1024; // store min value here

uint32_t start_time = millis();

while((millis()-start_time) < 1000) //sample for 1 Sec
{
readValue = analogRead(sensorIn);
// see if you have a new maxValue
if (readValue > maxValue)
{
/*record the maximum sensor value*/
maxValue = readValue;
}
if (readValue < minValue)
{
/*record the maximum sensor value*/
minValue = readValue;
}
/* Serial.print(readValue);
Serial.println(" readValue ");
Serial.print(maxValue);
Serial.println(" maxValue ");
Serial.print(minValue);
Serial.println(" minValue ");
delay(1000); */
}

// Subtract min from max
result = ((maxValue - minValue) * 5)/1024.0;

return result;
}

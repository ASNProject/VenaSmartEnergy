#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Komunikasi NRF24L01
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
const byte address1[6] = "00001";

//Variable pengirim 1
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

//Variable pengirim 2
double Voltage1 = 0;
double VRMS1 = 0;
double AmpsRMS1 = 0;

void setup() {
  s.begin(115200);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.openReadingPipe(1, address1);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
// Library ArduinoJson Versi 15.3.2
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
//}
void loop() {
  if (radio.available()) {

  //pengirim1
  radio.read(&AmpsRMS, sizeof(AmpsRMS));
  root["arusnode"] = AmpsRMS;
  radio.read(&Voltage, sizeof(Voltage));
  root["voltnode"] = Voltage;
  double hasil = AmpsRMS;
    Serial.print(AmpsRMS);
  Serial.print("   ");
  Serial.print(Voltage);
  Serial.print("    ");
    Serial.print(AmpsRMS1);
  Serial.print("   ");
  Serial.println(Voltage1);

  //pengirim2
  radio.read(&AmpsRMS1, sizeof(AmpsRMS1));
  root["arusnode1"] = AmpsRMS1;
  radio.read(&Voltage1, sizeof(Voltage1));
  root["voltnode1"] = Voltage1;


    if (s.available()>0){
      root.printTo(s);
    }
    delay(1000);  
  }
}

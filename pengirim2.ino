#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
LiquidCrystal_I2C lcd(0x3F, 16, 2);

RF24 radio(9, 10);
const byte address1[6]="00001";
const int sensorIn = A0;
int mVperAmp = 66; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module

double Voltage1 = 0;
double VRMS1 = 0;
double AmpsRMS1 = 0;


void setup(){
  Serial.begin(9600);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  pinMode(A0, INPUT);
  radio.begin();
  radio.openWritingPipe(address1);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop(){
//const char text[] = "AKU SAYANG KAMU";
//radio.write(&text, sizeof(text));
//delay(1000);

Voltage1 = getVPP();
VRMS1 = (Voltage1/2.0) *0.707; // sq root
AmpsRMS1 = (VRMS1 * 1000)/mVperAmp;
float Wattage1 = (220*AmpsRMS1)-18;

radio.write(&AmpsRMS1, sizeof(AmpsRMS1));
radio.write(&Voltage1, sizeof(Voltage1));
lcd.setCursor(00, 00);
lcd.print("Arus    =");
lcd.setCursor(10, 0);
lcd.print(AmpsRMS1);
lcd.setCursor(0, 1);
lcd.print("Voltage = ");
lcd.setCursor(10,1);
lcd.print(Voltage1);
//radio.write(&VRMS, sizeof(VRMS));
//radio.write(&Wattage, sizeof(Wattage));
//Serial.println(AmpsRMS);
//Serial.println(Wattage);
Serial.println(Voltage1);
//Serial.println(VRMS);
delay(10);


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

}

// Subtract min from max
result = ((maxValue - minValue) * 5)/1024.0;

return result;
}

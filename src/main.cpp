//CamperDisplay (Sender with display)

#include <Arduino.h>
#include <Wire.h>
#include "SerialTransfer.h"
//#include <LiquidCrystal_I2C.h> // Library for LCD


SerialTransfer myTransfer;

//LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

long timestamp = 0;





//init levels 
float startaccuvoltage = 0;
float hhaccuvoltage = 0;
int cleanwaterlevel = 0;
int dirtwaterlevel = 0;

//struct to be sent to CamperDisplay
struct dataReceived
{
  int cleanwaterlevel;
  int dirtwaterlevel;
  float startaccuvoltage;
  float hhaccuvoltage;
} dataInStruct;



//struct to be received by CamperController
struct dataToController 
{
  int water_relay;
  int light1_relay;
  int light2_relay;
  int fridge_relay;
  int frost_relay;
} dataOutStruct;


void setup() {
 Serial.begin(115200);
 Serial1.begin(19200);
 myTransfer.begin(Serial1);

//  lcd.init(); // initialize the lcd
 // lcd.backlight();
//Set pins for relays to output
//  pinMode(water_relay_pin, OUTPUT);


}

void loop() {
  
  //collect and send data every 3 seconds to display
  // collect the data values from ADC logic

if(millis() > timestamp+2000){
  Serial.println("Sending data");


  dataOutStruct.water_relay = 0;
  dataOutStruct.light1_relay = 1;
  dataOutStruct.light2_relay = 1;
  dataOutStruct.fridge_relay = 1;
  dataOutStruct.frost_relay = 0;

  //sent the data
  myTransfer.sendDatum(dataOutStruct); //sendDatum means only one data set. Check examples of serialtransfer.h
  Serial.println("DONE");
  timestamp = millis();
}

  //receive incomming messages
  //sending party determines frequency (at change or at least every 10 seconds or so)
  if(myTransfer.available())
  {
    myTransfer.rxObj(dataInStruct);
    Serial.print("start accu: ");
    Serial.println(dataInStruct.startaccuvoltage);
    Serial.print("huishoud accu: ");
    Serial.println(dataInStruct.hhaccuvoltage);
    Serial.print("Cleanwater level: ");
    Serial.println(dataInStruct.cleanwaterlevel);
    Serial.print("Dirtwater level: ");
    Serial.println(dataInStruct.dirtwaterlevel);

  }

// LCD 
 /* lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Arduino");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("GetStarted.com"); // print message at (2, 1)
  delay(2000);                 // display the above for two seconds

  lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("DIYables");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("www.diyables.io"); // print message at (0, 1)
*/
}
/*
 Cargo/Tanks Monitoring System: Displaying measured values of temperature and humidity
 ps: on this implementation a D1 board was used instead of a D1 mini in order to minimize the amount of jumping wires and protoboards. 

  Actuators:
  1x LCD
  
  Code Description:
  1 - Get values for Temperature and Relative Humidity status from Dweetio
  2 - Display last measure values on the screen 
  
  PS1: it is necessary to wait a couple of seconds until the first valid reading. 
  PS: an unstable connection can jeopardize the recovery from Dweet.io and result in the error "KEY NOT FOUND"
*/

// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(D8, D9, D4, D5, D6, D7); //PINS FOR BOARD D1

////WIFI definitions

const char* ssid      = "wifiname";
const char* password  = "password";

//Dweet definitions
#include "dweetESP8266.h"
#define THIG_NAME "WeatherstationSEAS40"
dweet DweetClient;

char *key1 = "Temperature";  //Variables names to be sent/get to/from Dweet.io
char *key2 = "Humidity"; 

void setup() {
Serial.begin(19200);
delay(10);
lcd.begin(16, 2);

// Print a message to the LCD. 
//
// Connecting to a Wifi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
WiFi.begin(ssid,password);
while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
//}
}

void loop() {
//
////Getting values from dweet
String temp=DweetClient.getDweet(THIG_NAME,key1);
delay(1000); 
String hum=DweetClient.getDweet(THIG_NAME,key2);
delay(1000); 

//Applying conditions to actuators
for(int i=0; i<=3; i++){
        lcd.clear();
     //   delay(1000);
        lcd.clear();
        lcd.print("Temp: " + String(temp) + " Hum: " + String(hum));
        delay(1000);     
    }

delay(1000);

}

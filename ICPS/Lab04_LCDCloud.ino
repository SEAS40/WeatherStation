// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(D7,D8, D1, D2, D3, D4);

////WIFI definitions

const char* ssid      = "MOVISTAR_606C";
const char* password  = "4YTXWFFFJVRM9FWVPYPP";

//Dweet definitions
#include "dweetESP8266.h"
#define THIG_NAME "WeatherstationSEAS40"
dweet DweetClient;

char *key1 = "Temperature";  //Variables names to be sent/get to/from Dweet.io
char *key2 = "Humidity"; 


void setup() {
// set up the LCD's number of columns and rows: 
pinMode(D1,OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D8,OUTPUT);

Serial.begin(74880);
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
        delay(1000);
        lcd.print("Temperature:" + String(temp));
        delay(1000);
       
    }

delay(1000);

}

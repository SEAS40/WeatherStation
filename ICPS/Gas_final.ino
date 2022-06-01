/*
  Cargo/Tanks Monitoring System:: Uploading Data to the Cloud with ESP8266 - CO detector
  V1
  created 25 March 2022
   
  Sensor:
  1x MQ-7 - CO

  Code Description:
  0- Reads 0 if CO is detected and 1 if is not detected
  1- Algebric manipulation to invert the logic. Now it returns 0 if it is NOT detected and 1 if CO is detected  
  2- Send data to the cloud - Dweet 
  */

//WIFI definitions
const char* ssid= "wifiname";
const char* password= "password";

//Dweet definitions
#include "dweetESP8266.h"
#define THIG_NAME "WeatherstationSEAS40" 
dweet DweetClient;

char *key3 = "CO_Sensor"; // this is the name of the parameter sent to Dweet.io
char val3[16]; // it stores a number composed by up to 16 characteres

//MQ7 definitions
int pin_mq=D1;

void setup() {
Serial.begin(115200);
pinMode(pin_mq,INPUT);
delay(10);

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
}

void loop() {
//READING DATA
  boolean mq_state=digitalRead(pin_mq);
  int co = mq_state+pow((-1), mq_state); //inverting. Now if output =0 means that no gas was detected
  
// POSTING DATA
  itoa(co, val3 , 10); // convert an integer value into a char array
  DweetClient.add(key3,val3);
  
  DweetClient.sendAll(THIG_NAME);

// Every 5 seconds a new value is uploaded
  delay(5000);
}

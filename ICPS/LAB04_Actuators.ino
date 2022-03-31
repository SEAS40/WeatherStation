/*
  Lab 4 Excercise: Getting/Sending Data from the Cloudwith ESP8266 - Actuators
  V3
  created 31 March 2022

  Actuators:
  1x Passive Buzzer
  1x LED RGB
  1x SMD RGB

  Code Description:
  0 - Define acceptable and ideal ranges for relative humidity and temperature
  1 - Get values for Temperature, Relative Humidity and CO Sensor status from Dweetio and verify if is valid and not-null
  2 - Activate Buzzer if is out of acceptable range or if CO is detected
  3 - Turn on red light if temperature or humidity is out of acceptable range
  4 - Turn on blue light if temperature or humidity is out of ideal range
  5 - Turn on green light if temperature or humidity is within ideal range
  6 - Send status of actuators to the cloud  
  
  PS1: it is necessary to wait a couple of seconds until the first valid reading. 
  PS: an unstable connection can jeopardize the recovery from Dweet.io and result in the error "KEY NOT FOUND"

  LEGEND
  CO Sensor = 0 - Not detected
  CO Sensore = 1 - Detected

  Buzzer = 0 - OFF
  Buzzer = 1 - ON

  RGB = 0 - Green - within the ideal limits
  RGB = 1 - Blue - within the acceptable limits
  RGB = 2 - Red - out of acceptable limits

*/

//WIFI definitions
const char* ssid= "wifiname";
const char* password= "wifipassword";

//Dweet definitions
#include "dweetESP8266.h"
#define THIG_NAME "WeatherstationSEAS40"
dweet DweetClient;

char *key1 = "Temperature";  //Variables names to be sent/get to/from Dweet.io
char *key2 = "Humidity"; 
char *key3 = "CO_Sensor"; 
char *key4 = "Buzzer"; 
char *key5 = "RGB_Temperature"; 
char *key6 = "RGB_Humidity"; 

char val1[16]; // it stores a number composed by up to 16 characteres
char val2[16]; 
char val3[16]; 

// Humidity and Temperature defininitions
float llh=30; //acceptable lower limit relative humidity
float ulh=70; //acceptable upper limit relative humidity
float llhi=40; //ideal lower limit relative humidity
int ulhi=60; //ideal upper limit relative humidity

float llt=10; //acceptable lower limit temperature
float ult=50; //acceptable upper limit temperature
float llti=20; //ideal lower limit temperature
float ulti=40; //ideal upper limit temperature

// Pins
#define buzzer_pin D0
#define red_h D1
#define green_h D2
#define blue_h D3
#define red_t D5
#define green_t D6
#define blue_t D7

//Buzzer
#include "pitches.h"
int melody= NOTE_A5;
int duration = 3000;

//initial values - to avoid warning/buzzer before the stabilization of connection
float t=21.0;
float h=31.0;
int co=0;
int rgb_h=0;
int rgb_t=0;
int buzzer=0;

void setup() {
Serial.begin(74880);
delay(10);

pinMode(red_h,OUTPUT);
pinMode(green_h,OUTPUT);
pinMode(blue_h,OUTPUT);
pinMode(red_t,OUTPUT);
pinMode(green_t,OUTPUT);
pinMode(blue_t,OUTPUT);
delay(1000);

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
//Getting values from dweet
String temp=DweetClient.getDweet(THIG_NAME,key1);
delay(1000); 
String hum=DweetClient.getDweet(THIG_NAME,key2);
delay(1000); 
String co_detec=DweetClient.getDweet(THIG_NAME,key3);
delay(1000); 

/*Check if the values from Dweet were sucessfully recovered and are valid.
If the values are invalid the code will consider the last valid reading */
if (temp!= "Key not found" && temp!="NaN") {
  t= temp.toFloat(); 
}
if (hum!= "Key not found" && hum!="NaN") {
  h= hum.toFloat(); 
}
if (co_detec!= "Key not found" && co_detec!= "NaN") {
  co= co_detec.toInt(); //0=Not detected and 1=CO detected 
}

//Applying conditions to actuators
//Buzzer
if (t<llt || t>ult || h<llh || h>ulh || co==1) {  //if it is out of the acceptable limits for humidity or temperature or if there is CO detection
  tone (buzzer_pin, melody, duration);
  buzzer=1; //0=OFF and 1=ON 
}
else { 
  noTone(buzzer_pin);
  buzzer=0; //0=OFF and 1=ON 
}

//RGB - Humidity
if (h>llhi && h<ulhi) { //GREEN - Within the ideal limits
  digitalWrite(green_h,HIGH);
  digitalWrite(red_h,LOW);
  digitalWrite(blue_h,LOW);
  rgb_h=0; //0=Ideal and 1=Acceptable and 2=critical
}

else if (h<llh || h>ulh) { //RED - out of acceptable limits
  digitalWrite(green_h,LOW);
  digitalWrite(red_h,HIGH);
  digitalWrite(blue_h,LOW);
  rgb_h=2; //0=Ideal and 1=Acceptable and 2=critical
}
else { // BLUE - within acceptable limits
  digitalWrite(green_h,LOW);
  digitalWrite(red_h,LOW);
  digitalWrite(blue_h,HIGH);
  rgb_h=1; //0=Ideal and 1=Acceptable and 2=critical
}

//RGB - Temperature
if (t>llti && t<ulti) { //GREEN - Within the ideal limits
  digitalWrite(green_t,HIGH);
  digitalWrite(red_t,LOW);
  digitalWrite(blue_t,LOW);
  rgb_t=0; //0=Ideal and 1=Acceptable and 2=critical
}
else if (t<llt || t>ult) { //RED - out of acceptable limits
  digitalWrite(green_t,LOW);
  digitalWrite(red_t,HIGH);
  digitalWrite(blue_t,LOW);
  rgb_t=2; //0=Ideal and 1=Acceptable and 2=critical
}
else { // BLUE - within acceptable limits
  digitalWrite(green_t,LOW);
  digitalWrite(red_t,LOW);
  digitalWrite(blue_t,HIGH);
  rgb_t=1; //0=Ideal and 1=Acceptable and 2=critical
}

//Uploading Actuators Status
  itoa(buzzer, val1 , 10); 
  DweetClient.add(key4,val1);
  
  itoa(rgb_t, val2 , 10); 
  DweetClient.add(key5,val2);

  itoa(rgb_h, val3 , 10); 
  DweetClient.add(key6,val3);

  DweetClient.sendAll(THIG_NAME);

Serial.println();
Serial.println();
Serial.print("Temp_Dweet: ");
Serial.println(temp);
Serial.print("Hum_Dweet: ");
Serial.println(hum);
Serial.print("CO_Dweet: ");
Serial.println(co_detec);
Serial.print("Temp_CurrentValue: ");
Serial.println(t);
Serial.print("Hum_CurrentValue: ");
Serial.println(h);
Serial.print("CO_CurrentValue: ");
Serial.println(co);
Serial.print("Buzzer_CurrentValue: ");
Serial.println(buzzer);
Serial.print("RGBtemp_CurrentValue: ");
Serial.println(rgb_t);
Serial.print("RGBhum_CurrentValue: ");
Serial.println(rgb_h);
Serial.println();

delay(1000);  
}

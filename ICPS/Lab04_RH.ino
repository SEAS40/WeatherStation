/*
  Lab 4 Excercise: Uploading Data to the Cloud with ESP8266 - RH & Temperature
  V1
  created 25 March 2022
   
  Sensor:
  1x DHT11 - Air temperature and relative humidity

  Code Description:
  0- Get values for Temperature and Relative Humidity from the sensor
  1- Send data to the cloud - Dweet 
  
*/

//WIFI definitions
const char* ssid      = "MOVISTAR_606C";
const char* password  = "4YTXWFFFJVRM9FWVPYPP";
//const char* ssid= "Ieza";
//const char* password= "I4ETLAB3";
//const char* ssid      = "iPhone";
//const char* password  = "chocolate";

//Dweet definitions
#include "dweetESP8266.h"
#define THIG_NAME "WeatherstationSEAS40" 
dweet DweetClient;

char *key1 = "Temperature"; //Variables names to be sent to Dweet.io
char *key2 = "Humidity"; 
char val1[16]; // it stores a number composed by up to 16 characteres
char val2[16]; 

//DHT definitions
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin D1
DHT dht(dht_dpin, DHTTYPE);

void setup() {
Serial.begin(9600);
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
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  
// POSTING DATA
  String temp= String(t,2); // converted to String with 2 decimals
  temp.toCharArray(val1,16); // converted to a char array
  DweetClient.add(key1,val1);
  
  String hum= String(h,2);
  hum.toCharArray(val2,16); 
  DweetClient.add(key2,val2);

  DweetClient.sendAll(THIG_NAME);

// Every 5 seconds a new value is uploaded
  delay(5000);
}

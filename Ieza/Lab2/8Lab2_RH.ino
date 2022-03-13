/*
  Lab 2 Excercise: Relative Huminity and Temperature Sensor

  Returns the read of RH and temperature and check if it is within the defined limits.

  V1
  created 09 March 2022
  by Andre Pascual
  Bill Castillo
  Desirae Minnett
  Ieza Ramos
*/

#include "DHT.h"
#define DHTTYPE DHT11

#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);

int llh=30; //lower limit relative huminity
int ulh=70; //upper limit relative huminity
int llt=10; //lower limit temperature
int ult=50; //upper limit temperature


void setup() {
  dht.begin();
  Serial.begin(9600);
  delay(10);
  Serial.println("Initializing ESP8266...");
}

void loop() {
  delay(3000);
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print("Huminity = ");
  Serial.print (h);
  Serial.println ("% ");
  Serial.print ("Temperature = ");
  Serial.print (t);
  Serial.println ("C ");
  if (h > llh && h < ulh) {
    if (t > llt && t<ult){
      Serial.println ("OK!");
    }
    else {
      Serial.println ("TEMPERATURE NOT WITHIN LIMITS!!!");
    }
  }
  else if (t<llt || t>ult) {
    Serial.println("TEMPERATURE AND HUMINITY NOT WITHIN LIMITS!!!");
  }
  else {
    Serial.println("HUMINITY NOT WITHIN LIMITS!!!");
  }
}

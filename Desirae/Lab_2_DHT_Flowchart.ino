/*
  Lab 2 Exercise: DHT sensor implmentation

  Continously reads temperature and relative humidity of DHT sensor,
  displaying the status in relation to set absolute and ideal, upper/ lower limits.
  The intention is to include LED and Buzzer actuators at a later stage, for now these
  intended operations are only printed to the serial monitor. 
  
  Inputs:
  1 - Temperature reading from DHT sensor
  2 - Relative humidity reading from DHT sensor

  Outputs:
  1 - Displays temperature to serial monitor
  2 - Displays relative humidity to serial monitor
  3 - Displays if temperature/ relative humidity falls within ideal/absolute ranges in serial monitor
  3 - Displays status of intended LED to serial monitor
  4 - Displays status of intended buzzer to serial monitor

  V1
  Created 9 March 2022
  by Desirae Minnett
*/

#include "DHT.h"

#define DHTTYPE DHT11

#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);

//Define upper and lower limits for ideal and maximum/minimum values of humidity and temperature
//For now humidity values are manipulated based on room for a response
int uLimTemp =  30;  // Upper abosolute temperature limit
int lLimTemp =  -50; // Lower abosolute temperature limit \\doesnt really exist for wheat
int uLimHumi =  50;  // Upper abosolute humidity limit
int lLimHumi =  40;  // Lower absolute humidity limit
int uiLimTemp = 25;  // Upper ideal temperature limit
int liLimTemp = 20;  // Lower ideal temperature limit
int uiLimHumi = 46;  // Upper ideal humidity limit 
int liLimHumi = 44;  // Lower ideal humidity limit 

void setup( )

{

  dht.begin();
  
  Serial.begin(9600);
  
  delay(10); Serial.println("Initializing ESP8266...");

}

void loop( )

{

  delay(3000);
  
  float h=dht.readHumidity(); float t=dht.readTemperature();

  Serial.print("Current humidity = ");
  
  Serial.print(h);
  
  Serial.print("% ");
  
  Serial.print("temperature ");
  
  Serial.print(t);
  
  Serial.println("C ");

  // Now implement code so serial monitor represents flow chart

  // if temperature and humidity is within absolute ranges
  if(t < uLimTemp && t > lLimTemp && h < uLimHumi && h > lLimHumi)
  {
    //if temperature and humidity is within ideal ranges
    if (t < uiLimTemp && t > liLimTemp && h < uiLimHumi && h > liLimHumi)
    {
      Serial.println("Temperature and humidity OK");
      Serial.println("*solid green LED*");
    }
    //if temperature is within ideal ranges and humidity is not
    else if (t < uiLimTemp && t > liLimTemp && h > uiLimHumi || h < liLimHumi)
    {
      Serial.println("Temperature OK, humidity not in ideal zone");
      Serial.println("*Slow yellow LED*");
      Serial.println("*Slow buzzer activated*");
    }
    //if temperature is not within ideal ranges and humidity is
    else if (t > uiLimTemp || t < liLimTemp && h < uiLimHumi && h > liLimHumi)
    {
      Serial.println("Temperature is not in ideal zone, humidity is OK");
      Serial.println("*Slow yellow LED*");
      Serial.println("*Slow buzzer activated*");
    }
  }
  // if temperature is ok(in absolute or ideal range) and humdity exceeds absolute range
  else if(t < uLimTemp && t > lLimTemp && h > uLimHumi || h < lLimHumi)
  {
    // if temperature is within ideal range
    if (t < uiLimTemp && t >liLimTemp)
    {
      Serial.println("Temperature OK, humidity in the danger zone");
      Serial.println("*Rapid red LED*");
      Serial.println("*rapid buzzer activated*");
    }
    // if temperature is not within ideal range
    else 
    {
      Serial.println("Temperature not in ideal range and humidity is in the danger zone");
      Serial.println("*Rapid red LED*");
      Serial.println("*rapid buzzer activated*");     
    }
  }
  // if humidity is ok(in absolute or ideal range) and temperature exceeds absolute range
  else if(t > uLimTemp || t < lLimTemp && h < uLimHumi && h > lLimHumi)
  {
    // if humidity is within ideal range
    if (t < uiLimTemp && t >liLimTemp)
    {
      Serial.println("Temperature in the danger zone, humidity OK");
      Serial.println("*Rapid red LED*");
      Serial.println("*rapid buzzer activated*");
    }
    // if humidity is not within ideal range
    else 
   {
      Serial.println("Temperature in the danger zone and humidity is not in the ideal range");
      Serial.println("*Rapid red LED*");
      Serial.println("*rapid buzzer activated*");     
    }
  // otherwise temperature and humidity are both in the danger zone, maybe consider hard coding limits?
  }
  else
    {
      Serial.println("Temperature and humidity in the danger zone");
      Serial.println("*Rapid red LED*");
      Serial.println("*Rapid buzzer activated*");      
    }
  Serial.println(" ");
}

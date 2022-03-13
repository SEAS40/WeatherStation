/*
  Lab 2 Excercise: Temperature Sensor, calibrated based on RH sensor

  Returns the read of temperature and check if it is within the defined limits.

  V2
  adapted from code DIGITAL_TEMPERATRUE_MODULE.ino provided by Professor.
  
  created 09 March 2022
  by Andre Pascual
  Bill Castillo
  Desirae Minnett
  Ieza Ramos
*/

byte pin = A0;

//INPUTS

//Temperature limit
int llt=10; //lower limit temperature
int ult=50; //upper limit temperature

//Sensor Parameters. DATASHEET? 
#define RT0 10000 //Ohm
#define T0 65 //Celsius. Nominal temperature. Calibrated based on RH sensor
#define BCOEFFICIENT 3950 // B coefficient. 

//DEFINITIONS
#define RN 10000 //Ohm
#define VCC 5 //supply voltage

//VARIABLES
float VRT, VR, IR, RT, temperature;

void setup()
{   
Serial.begin(9600);
}

void loop()
{
  VRT = analogRead(pin);
  VRT = (5.0 / 1023.00) * VRT; // Conversion to Voltage - 10-bit analog to digital - map input voltages into integers between 0-1023
  VR = VCC - VRT;
  IR= VR/RN; 
  RT = VRT/IR; //Resistance 

  //Steinhart and Hart - EQUATION WITH PARAMETER B - empirical expression for the resistance - temperature relationship
  temperature = RT / RT0; // (R/Ro)
  temperature = log(temperature); // ln(R/Ro)
  temperature /= BCOEFFICIENT; // 1/B * ln(R/Ro)
  temperature += 1.0 / (T0 + 273.15); // + (1/To) - To in Kelvin
  temperature = 1.0 / temperature; // Invert
  temperature -= 273.15; // convert to Celsius

  Serial.print(temperature);
  Serial.println(" oC");

  if (temperature > llt && temperature<ult){
    Serial.println ("OK!");
  }
  else {
    Serial.println ("TEMPERATURE NOT WITHIN LIMITS!!!");
  }
  
  delay(1000);
}

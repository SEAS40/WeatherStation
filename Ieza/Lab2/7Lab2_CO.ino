/*
  Lab 2 Excercise: Gas Sensor

  Returns the read of gas sensor.

  V1
  created 09 March 2022
  by Andre Pascual
  Bill Castillo
  Desirae Minnett
  Ieza Ramos
*/

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc_MQ=analogRead(A0);
  float voltage= adc_MQ*(5.0/1023.0);

  Serial.print("RAW ADC reading:");
  Serial.println (adc_MQ);

  Serial.print ("Voltage:");
  Serial.println(voltage);
  delay(1000);
}

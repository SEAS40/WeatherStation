/*
  Lab 2 Excercise: LDR - Light Dependent Resistance

  If there is barely any light, the embedded LED will be turned on; 
  if the light detected by the LDR is above a threshold, the embedded LED will remain turned off.

  V1
  created 09 March 2022
  by Andre Pascual
  Bill Castillo
  Desirae Minnett
  Ieza Ramos
*/

int sensorPin=A0;
int ledPin = LED_BUILTIN;
int sensorValue=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue=analogRead(sensorPin);
  if (sensorValue>900) {
    digitalWrite(ledPin,LOW);
  }
  else {
    digitalWrite(ledPin,HIGH);
  }

  Serial.println(sensorValue, DEC);

}

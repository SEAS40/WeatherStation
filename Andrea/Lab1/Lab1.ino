//We will turn on the LED with A and turn off with E


byte receivedByte = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(230400);
}


void loop() {
  
if (Serial.available()>0)
{
  //If there is a character, read it
  receivedByte = Serial.read();
  if(receivedByte==65)
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (LOW is the voltage level)
  }
  else if (receivedByte==69)
  {
  Serial.println(receivedByte);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off by making the voltage HIGH
  }
  }

 

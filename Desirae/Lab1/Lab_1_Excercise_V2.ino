/*
  Lab 1 Exercise: LED Control

  Turns on LED when receiving D serial and off when receiving E serial.
  Otherwise an error message is displayed in the serial monitor

  NOTE: This code has been written for LED that has been installed backwards!

  Inputs:
  1 - Characters, specifically D and E for proper function

  Outputs:
  1 - Prints ASCII number coresponding to serial character in serial monitor
  2 - Prints the recieved character in serial monitor (D or E) or displays error message to serial monitor
  3 - LED is set to either on (when D is entered) or off (when E is entered)

  V2
  modified 2 March 2022
  by Desirae Minnett
  modified 2 March 2022
  by Ieza Souza Ramos

  V1
  modified 1 March 2022
  by Desirae Minnett
*/

byte byteVal = 0; //Initialize variable for serial value storage

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(230400); //Sets the same data type? ask what baud does
  delay(5000); //If a long enough delay is not given digital write will not function correctly
  digitalWrite(LED_BUILTIN, HIGH); //This is required or else the LED is on by default, why?
  Serial.println("Enter either D (turn on) or E (turn off)");
}

void loop() 
{

  if(Serial.available() > 0) //Check if serial is coming through port
  {
  byteVal = Serial.read(); //Check value of serial
  
      if(byteVal == 68)
      {
        Serial.println(byteVal); //Print value of serial to window
        Serial.println("D character recieved"); //Lets user know the entry is D
        digitalWrite(LED_BUILTIN, LOW); //Turn on LED (seems backwards?)
      }
      
      else if(byteVal == 69)
      {
        Serial.println(byteVal); //Print value of serial to window
        Serial.println("E character recieved"); //Lets user know the entry is E
        digitalWrite(LED_BUILTIN, HIGH); //Turn off LED (seems backwards?)
      }
      
      else if(byteVal != 10)
      {
        Serial.println(byteVal); //Print value of serial to window
        Serial.println("Invalid entry"); //Lets user know the entry is invalid
      }
  }
}

// Is there any way to stop 10 from appearing in the command window?
// Yes, place inside If statements

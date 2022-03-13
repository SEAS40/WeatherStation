byte byteVal = 0; //Initialize variable for serial value storage



void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  digitalWrite(LED_BUILTIN, HIGH); //This is required or else the LED is on by default, why?
  Serial.begin(230400); //Sets the same data type? ask what baud does
}

void loop() 
{

  if(Serial.available() > 0) //Check if serial is coming through port
  {
  byteVal = Serial.read(); //Check value of serial
  Serial.println(byteVal); //Print value of serial to window
  
      if(byteVal == 68)
      {
        Serial.println("D character recieved");
        digitalWrite(LED_BUILTIN, LOW); //Turn on LED (seems backwards?)
      }
  
      else if(byteVal == 69)
      {
        Serial.println("E character recieved");
        digitalWrite(LED_BUILTIN, HIGH); //Turn off LED (seems backwards?)
      }

//      else if(byteVal != 68 && byteVal != 69) //why wont this or just simply "else" work? (executes when D and E entered)
//      {
//        Serial.println("Invalid entry");
//      }
  }
}

// Is there any way to stop 10 from apperaring in the command window?

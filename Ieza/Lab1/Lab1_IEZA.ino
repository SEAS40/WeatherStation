/*
  Lab 1 Excercise: LED Control

  Turns on LED when receiving I or i serial and off when receiving A or a serial.
  Otherwise an error message is displayed in the serial monitor

  Inputs:
  1 - Characters, specifically I/i and A/a for proper function

  Outputs:
  1 - Prints the received character in serial monitor (I/i or A/a) or displays error message to serial monitor
  2 - LED is set to either on (when I/i is entered) or off (when A/a is entered)

  V3
  modified 2 March 2022
  by Ieza Ramos
  
  V2
  modified 2 March 2022
  by Desirae Minnett
  modified 2 March 2022
  by Ieza Ramos

  V1
  created 27 Feb 2022
  by Ieza Ramos
*/

byte byteVal = 0; //Initialize variable for serial value storage

int OnPins[]={73,105}; //Corresponding ASCII characters to I and i
int OffPins[]={65,97}; //Corresponding ASCII characters to A and a
int sizeOn = sizeof(OnPins) / sizeof(int); //size of array OnPins. Division required because sizeof function returns the number of bytes
int sizeOff = sizeof(OffPins) / sizeof(int); //size of array OffPins

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(230400); 
  delay(2000); 
  digitalWrite(LED_BUILTIN, LOW); //LED ON 
  Serial.println("Type I to turn ON or A to turn OFF");
}

void loop() 
{
  int ref = 0;
  if(Serial.available() > 0)   //Check if serial is coming through port
  {
  byteVal = Serial.read(); //Check value of serial

    for (int i = 0; i < sizeOn; i++) { //check if input is on OnPins array, i.e., is I or i
        if (OnPins[i] == byteVal) {
          ref+=1; //if so, reference int becomes 1
        }
    }

    for (int j = 0; j < sizeOff; j++) { //check if input is on OffPins array, i.e., is A or a
        if (OffPins[j] == byteVal) {
          ref+=2; //if so, reference int becomes 2
        }
    }   

//if sequence to turn the LED on, off or error message accordingly with the arrays check 
      if(ref == 1) { 
        Serial.println("Character 'I' inputed. LED ON"); 
        digitalWrite(LED_BUILTIN, LOW); //LED ON
      }
      
      else if(ref == 2) {
        Serial.println("Character 'A' inputed. LED OFF");
        digitalWrite(LED_BUILTIN, HIGH); //LED OFF
      }
      
      else if(byteVal != 10) //10 is equivalent to enter. This step is required to avoid returninf the error message in every new entry. 
      {
        Serial.println("Invalid entry"); 
      }
  }
 }      

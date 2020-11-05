class Flasher       //Define class name
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                   // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Blink()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};      //End of class function

//Calling flasher class
Flasher led1 (2,  781,  515);    //Green LED
Flasher led2 (3, 2014, 1348);    //Red LED
Flasher led3 (4,  343,  573);
Flasher led4 (5,  678, 1839);
Flasher led5 (6,  342,  534);
Flasher led6 (7, 1478,  326);
Flasher led7 (8, 1859,  351);
Flasher led8 (9,  777,  888);

void setup()
{}          //Do nothing here

void loop()
{
  led1.Blink();  
  led2.Blink();  
  led3.Blink();  
  led4.Blink();  
  led5.Blink();  
  led6.Blink();  
  led7.Blink();  
  led8.Blink();  
}

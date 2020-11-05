class Button       //Define class name
{
    // Class Member Variables
    // These are initialized at startup
    int switchPin;       // the number of the switch pin
    int switchState;     // switchState used to set the switch
    int tempState;
    int countUp;

    // Constructor - creates a Button
  public:
    Button(int pin)
    {
      switchPin = pin;
      pinMode(switchPin, INPUT_PULLUP);
      tempState = HIGH;
      countUp = 0;
    }

    int Press()
    {
      switchState = digitalRead(switchPin);   // Update the actual switch

      if ((switchState == LOW) && (switchState != tempState))
      {
        countUp++;
        tempState = switchState;
      }
      tempState = switchState;
      return countUp;
    }
};      //End of class function

//Calling Button class
Button switch1 (2);    //Red switch
Button switch2 (3);    //Yellow switch
Button switch3 (4);    //White switch
Button switch4 (5);    //Yellow switch
Button switch5 (6);    //Red switch

void setup()
{
  Serial.begin(9600); //Do nothing here
}

void loop()
{
  int A = switch1.Press();
  int B = switch2.Press();
  int C = switch3.Press();
  int D = switch4.Press();
  int E = switch5.Press();
  Serial.println((String)"A = " + A + "\t\t" + "B = " + B + "\t\t" + "C = " + C + "\t\t" + "D = " + D + "\t\t" + "E = " + E);
}

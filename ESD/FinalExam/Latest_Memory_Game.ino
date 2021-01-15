#include <Wire.h>              // Include library for I2C Communication
#include <LiquidCrystal_I2C.h> // Include library for LCD
#define PLAYER_WAIT_TIME 2000  // The time allowed between button presses - 2s 

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

byte sequence[100];           // Storage for the light sequence
byte curLen = 0;              // Current length of the sequence
byte inputCount = 0;          // The number of times that the player has pressed a (correct) button in a given turn
byte lastInput = 0;           // Last input from the player
byte expRd = 0;               // The LED that's suppose to be lit by the player
bool btnDwn = false;          // Used to check if a button is pressed
bool wait = false;            // Is the program waiting for the user to press a button
bool resetFlag = false;       // Used to indicate to the program that once the player lost

byte level = 1;               // Current level
byte potent = 0;              // Potentiometer value
byte analogPin = 0;           // Potentiometer input
byte soundPin = 5;            // Speaker output
byte noPins = 4;              // Number of buttons/LEDs (While working on this, I was using only 2 LEDs)
byte pins[] = {2, 13, 10, 8}; // Button input pins and LED ouput pins 
long inputTime = 0;           // Timer variable for the delay between user inputs

void setup() {
  delay(1000);                    // This is to give me time to breathe after connection the arduino
  lcd.begin();                    // initialize the LCD
  lcd.backlight();                // Turn on the blacklight and print a message.
  lcd.print ("Initialize Game!"); //Print Initialize game in LCD
  Reset();                        // Jump to reset function

}

// Sets all the pins as either INPUT or OUTPUT based on the value of 'dir'
void setPinDirection(byte dir)
{
  for (byte i = 0; i < noPins; i++)
  {
    pinMode(pins[i], dir);
  }
}

//Send the same value to all the LED pins
void writeAllPins(byte val)
{
  for (byte i = 0; i < noPins; i++)
  {
    digitalWrite(pins[i], val);
  }
}

//Makes a beep sound
void beep(byte freq)
{
  tone(soundPin, potent);
  delay(freq);
  noTone(soundPin);
  delay(freq);
}

// Flashes all the LEDs together
// freq is the blink speed - small number -> fast | big number -> slow
void flash(short freq)
{
  setPinDirection(OUTPUT); /// We're activating the LEDS now
  for (int i = 0; i < 5; i++)
  {
    writeAllPins(HIGH);
    beep(50);
    delay(freq);
    writeAllPins(LOW);
    delay(freq);
  }
}

//This function resets all the game variables to their default values
void Reset()
{
  flash(500);
  curLen = 0;
  inputCount = 0;
  lastInput = 0;
  expRd = 0;
  btnDwn = false;
  wait = false;
  resetFlag = false;
  level = 1;
}

// User lost
void Lose()
{
  flash(50);
  lcd.clear();
  lcd.print ("   High Score");  //Show latest high score
  lcd.setCursor(0, 1);
  lcd.print ("    Level ");     //Showing level the user last played
  lcd.print (level);
}


// The arduino shows the user what must be memorized
// Also called after losing to show you what you last sequence was
void playSequence()
{                             //Loop through the stored sequence and light the appropriate LEDs in turn
  lcd.clear();
  lcd.print("     Ready!");   //Remind user to be ready
  lcd.setCursor(0, 1);
  lcd.print("    Level ");    //Show current level
  lcd.print(level);
  delay(1000);

  for (int i = 0; i < curLen; i++)
  {
    digitalWrite(sequence[i], HIGH);    //make LED blinking
    delay(500);
    digitalWrite(sequence[i], LOW);
    delay(250);
    lcd.clear();
  }
  level++;         //Increase to the next level
}

// The events that occur upon a loss
void DoLoseProcess()
{
  Lose();             // Flash all the LEDS quickly (see Lose function)
  delay(1000);
  playSequence();     // Shows the user the last sequence - So you can count remember your best score 
  Reset();            // Reset everything for a new game
}

// Where the magic happens
void loop()
{
  if (!wait)
  {

    potent = analogRead(analogPin);

    //****************//
    // Arduino's turn //
    //****************//
    setPinDirection(OUTPUT);                      // We're using the LEDs

    randomSeed(analogRead(A0));                   
    sequence[curLen] = pins[random(0, noPins)];   // Put a new random value in the next position in the sequence 
    curLen++;                                     // Set the new Current length of the sequence

    playSequence();                               // Show the sequence to the player
    beep(50);                                     // Make a beep for the player to be aware

    wait = true;                                  // Set Wait to true as it's now going to be the turn of the player
    inputTime = millis();                         // Store the time to measure the player's response time
  } else
  {
    //***************//
    // Player's turn //
    //***************//
    setPinDirection(INPUT);                       // We're using the buttons

    if (millis() - inputTime > PLAYER_WAIT_TIME)
    {                                             // If the player takes more than the allowed time,
      DoLoseProcess();                            // All is lost :(
      return;
    }


    if (!btnDwn)                             //While button is not pressed
    {
      expRd = sequence[inputCount];          // Find the value we expect from the player
      lcd.clear();
      lcd.print("Expected: ");               // Print expected button to be pressed on LCD
      lcd.print(expRd);                      

      for (int i = 0; i < noPins; i++)
      { // Loop through the all the pins
        if (pins[i] == expRd)
          continue;                        // Ignore the correct pin
        if (digitalRead(pins[i]) == HIGH)
        { // Is the buttong pressed
          lastInput = pins[i];
          resetFlag = true;                // Set the resetFlag - this means you lost
          btnDwn = true;                   // This will prevent the program from doing the same thing over and over again
          lcd.setCursor(0, 1);
          lcd.print("Read: ");             // Print the input from the user on LCD
          lcd.print(lastInput);              
        }
      }
    }

    if (digitalRead(expRd) == 1 && !btnDwn) // The player pressed the right button
    {
      inputTime = millis();                 // Start calculating time
      lastInput = expRd;
      inputCount++;                         // The user pressed a (correct) button again
      btnDwn = true;                        // This will prevent the program from doing the same thing over and over again
      lcd.setCursor(0, 1);
      lcd.print("Read: ");                  // Read last input from the user
      lcd.print(lastInput);                    
    } else
    {
      if (btnDwn && digitalRead(lastInput) == LOW)  // Check if the player released the button
      {
        btnDwn = false;
        delay(20);
        if (resetFlag)
        { // If this was set to true up above, you lost
          DoLoseProcess();                          // So we do the losing sequence of events
        }
        else
        {
          if (inputCount == curLen)
          { // Has the player finished repeating the sequence
            wait = false;                           // If so, this will make the next turn the program's turn
            inputCount = 0;                         // Reset the number of times that the player has pressed a button
            delay(1500);
          }
        }
      }
    }
  }
}

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library
#include <LCDWIKI_TOUCH.h> //touch screen library
#include <FastLED.h>
#include <EEPROM.h>

//paramters define
#define MODEL ILI9488_18
#define CS   A5
#define CD   A3
#define RST  A4
#define LED  A0   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

//touch screen paramters define
#define TCS   45
#define TCLK  46
#define TDOUT 47
#define TDIN  48
#define TIRQ  49

//LED
#define LED_PIN 25 //pin arduino connect rgb
#define NUM_LEDS 60 //rgb led
#define FADESPEED 255

//Colour
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


//crgb set color individually
CRGB leds[NUM_LEDS];

//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI my_lcd(MODEL, CS, CD, RST, LED); //model,cs,dc,reset,led

//the definiens of touch mode as follow:
LCDWIKI_TOUCH my_touch(TCS, TCLK, TDOUT, TDIN, TIRQ); //tcs,tclk,tdout,tdin,tirq

//define variables
int16_t px, py, buzzer = 24, relay_in = 31, alarm_in = 32, cs = 53, trig = 1, trig2 = 1, n = 890, jj = 0, page=1, m;
char  b[5], trigStatus = '0', trig2Status = '0';
String str;

void setup(void)
{
  bootUp();
}

void loop(void)
{
  Counter();
  Touchscreen();
}

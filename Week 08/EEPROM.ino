#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value = 10;

void setup() {
  Serial.begin(9600);
  value = EEPROM.read(address);
  Serial.println(value, DEC);
}

void loop() {
  Serial.println(value);
  EEPROM.update(address, value);
  value++;
  delay(1000);
}

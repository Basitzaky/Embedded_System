int sensorPin = A2;   // select the input pin for the potentiometer
int ledPin = 6;     // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  // set pin(s) to input and output
  pinMode(sensorPin + A0, INPUT);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for  milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for  milliseconds:
  delay(sensorValue);
  
}

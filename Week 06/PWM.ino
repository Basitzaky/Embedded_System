void setup() {
  pinMode(A3, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  int value = analogRead(A3);
  int led = map(value, 0, 1023, 0, 255);
  analogWrite(6, led);
  Serial.println(led);
}

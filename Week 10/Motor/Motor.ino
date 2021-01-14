int motor = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode ( 9 , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (motor = 0; motor <= 255; motor += 10)
  {
    analogWrite(9, motor);
    delay(15);
  }

  for (motor = 255; motor >= 0; motor -= 10)
  {
    analogWrite(9, motor);
    delay(15);
  }

}

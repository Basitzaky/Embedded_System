int timer = 0, timer2 = 0;

void Led1()
{
  if (timer <= 15 )
    timer++, digitalWrite(2, HIGH);
  if (timer >= 15 )
  {
    timer++, digitalWrite(2, LOW);
    if (timer > 350)
      timer = 0;
  }
}

void Led2()
{
  if (timer2 <= 10 )
    timer2++, digitalWrite(3, HIGH);
  if (timer2 >= 10 )
  {
    timer2++, digitalWrite(3, LOW);
    if (timer2 > 400)
      timer2 = 0;
  }
}

void setup() {
  pinMode (2, OUTPUT), pinMode (3, OUTPUT);
}

void loop() {
  Led2(), Led1();
}

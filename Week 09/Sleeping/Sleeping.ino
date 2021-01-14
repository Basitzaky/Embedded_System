void setup() 
{
  char *adcsra = (char *)0x7A;
  char *acsr = (char *)0x50; *adcsra = 0; *acsr = 1 << 7;
  Sleep();
  for (;;)
  {
    
  }
  
}

void Sleep()
{
  char *smcr = (char *)0x53; *smcr = 5; //Sleep mode = POWER DOWN, Sleep Enable = True
  asm("sleep"); //Invoke in line assembler to sleep
}

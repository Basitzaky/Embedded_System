//Interrupts using Arduino

volatile int output = LOW;                      
int i = 0;   

void setup()                                                      

{
  Serial.begin(9600);
  Serial.println("ArduinoInterrupt");
  delay(3000);                                                     
  pinMode(13,OUTPUT);                                           
                                   
  attachInterrupt(digitalPinToInterrupt(2),buttonPressed1,RISING);  //  function for creating external interrupts at pin2 on Rising (LOW to HIGH)
  attachInterrupt(digitalPinToInterrupt(3),buttonPressed2,RISING);  //  function for creating external interrupts at pin3 on Rising (LOW to HIGH)   
}
                                                                                                                                                                                                                                                                                       
void loop()                                                      
{                                          
   Serial.print("COUNTER: ");                                           
   Serial.print(i);
   Serial.println(" \n ");                                                  
   ++i;                                                            
   delay(1000);   
   digitalWrite(13,output);     //Turns LED ON or OFF depending upon output value
}

void buttonPressed1()           //ISR function excutes when push button at pinD2 is pressed
{                    
   output = LOW;                //Change Output value to LOW                                                                         
   //Serial.println("");
   delay(500);
   Serial.println("Interrupt 1");
   
}

void buttonPressed2()           //ISR function excutes when push button at pinD3 is pressed                             
{                    
   output = HIGH;               //Change Output value to HIGH                                    
   //Serial.println(""); 
   delay(500);                                        
   Serial.println("Interrupt 2");
}

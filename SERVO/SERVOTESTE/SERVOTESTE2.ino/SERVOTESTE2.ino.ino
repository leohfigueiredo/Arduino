#include <Servo.h>

Servo motor;                           

 void setup()
{
   motor.attach(6); 
}

void loop () 
{ 
  motor.write(45); 
  delay(1000); 
  motor.write(125); 
  delay(1000); 
}


#include <Servo.h>

Servo motor;

void setup()
{
   motor.attach(6);
}

void loop ()
{ 
  int i;
  for(i=0;i<180;i++)
  {
    motor.write(i);
    delay(10);
  }
  delay(1000);
  for(i=180;i>0;i--)
  {
  motor.write(i);
  delay(10);
  }
  delay(1000);
}


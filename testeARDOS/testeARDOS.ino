#include <kernel.h>
#include <queue.h>
#include <sema.h>

#define NUM_TASKS  4
void task1(void *p)
{
  char buffer[16];
  unsigned char sreg;
  int n=0;
  while(1)
  {
   
    sprintf(buffer, "Time: %lu  ", OSticks());
    Serial.println(buffer);
    OSSleep(1000);
  }
}

void task2(void *p)
{
  unsigned int pause=(unsigned int) p;
  char buffer[16];
  while(1)
  {
    digitalWrite(13, HIGH);
//    sprintf(buffer, "==>Time: %lu ", OSticks());
  // Serial.println(buffer);
   //Serial.println("LED HIGH");
    
    OSSleep(pause);
  // sprintf(buffer, "==>Time: %lu ", OSticks());
  // Serial.println(buffer);
    digitalWrite(13, LOW);
    //Serial.println("LED LOW");
    OSSleep(pause);
  }
}
void task3(void * p)
{
  char buff1[16];
  int n1=0;
  while(1)
  {
    n1=analogRead(5);
    n1=map(n1,0,1023,0,255);
   sprintf(buff1, "APV: %d ", n1);
   Serial.println(buff1);
    OSSleep(1000);
  }
}
void setup()
{
  OSInit(NUM_TASKS);
  
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  OSCreateTask(0, task3, NULL);    
 OSCreateTask(1, task1, NULL);
  OSCreateTask(2, task2, (void *) 1000);
  OSCreateTask(3, task1, NULL);

  OSRun();
}

void loop()
{
  // Empty
}

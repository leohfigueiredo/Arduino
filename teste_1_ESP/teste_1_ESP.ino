#include "SoftwareSerial.h"


SoftwareSerial Serial2(2 , 3);
void setup()
{
  Serial2.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  Serial2.println("AT");
  delay(1000);

}

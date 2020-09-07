unsigned char relayPin[4] = {7,8,9,10};

void setup()
{
  int i;
  for(i = 0; i < 4; i++)
  {
    pinMode(relayPin[i],OUTPUT);
  }
}

//just an simple demo to close and open 4 relays
// every other 1s.
void loop()
{

  int i=0;
  for(i = 0; i < 4; i++)
  {
    digitalWrite(relayPin[i],HIGH);
    delay(2000); //delay between turning on each relay, 200 milliseconds
  }
  delay(1000);
  for(i = 0; i < 4; i++)
  {
    digitalWrite(relayPin[i],LOW);
    delay(2000); //delay between turning off each relay, 200 milliseconds
  }
  delay(1000);
 
}




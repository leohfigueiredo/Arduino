//  makeabarmillis01
//  works 03JUL2016
long markTime;
long elapsedTime;
byte bar = 0;
byte pinsArray [4] = {7,8,9,10};
boolean gotMark = false;

void setup ()
{
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}
void loop ()
{
  if(gotMark == false)
  {
    markTime = millis();
    gotMark = true;
  }
  elapsedTime = millis();
  if((elapsedTime - markTime) >= 4000) // 2 secs each
  {
    bartime();
  }
}
void bartime ()
{
  gotMark = false;
  if(bar < 4)
  {
    digitalWrite(pinsArray[bar],HIGH);
    bar ++;
  }
  else
  {
    // clear the bar
    digitalWrite(pinsArray[0],LOW);
    digitalWrite(pinsArray[1],LOW);
    digitalWrite(pinsArray[2],LOW);
    digitalWrite(pinsArray[3],LOW);
    bar = 0;  // reset bar
  }
}

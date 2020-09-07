/*
Event logger for open door.


Components:
- SD card shield
- Real time clock
- Button to detect door state
- 220 ohm & 10k ohm resistors
- led

SD card pins:
** MOSI  - pin 11
** MISO  - pin 12
** SCK   - pin 13
** CS    - pin 4 // for this case

RTC pins:
** SDA  - A4
** SCL  - A5

Button + led pins:
** GND + 220ohm on led - digital pin 3
** 5V on button + 10k ohm to GND + digital pin 2



*/
#include <Wire.h>     // lib for RTC
#include "RTClib.h"   // lib for RTC
#include <SPI.h>      // lib for SD
#include <SD.h>       // lib for SD

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 4;
File data;

// set up for RTC
RTC_DS1307 RTC;

// set up for led + button
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
int pbuttonState;

byte ok;  //stop the loop if SD card was not initialized
byte first=1;

void setup() {
  Serial.begin(57600);
  // led + button
  pinMode(ledPin, OUTPUT); 
  pinMode(buttonPin, INPUT); 
  
  // SD
   Serial.print("Initializing SD card...");
   pinMode(10, OUTPUT); // it's needed for SD library to work even if the CS is not connected to pin 10
            // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    ok=0;
    
  }else{
  Serial.println("card initialized.");
  ok=1;  
 }
  // RTC
  Wire.begin();
  RTC.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__));  // set to pc time   

}

void loop() {
 if(ok==1)
{ 
  if(first==1)
  {
  
  buttonState = digitalRead(buttonPin);
  pbuttonState= buttonState;
  call(buttonState);
  first = 0;
  }
  else
  { 
    buttonState = digitalRead(buttonPin);
    if(pbuttonState != buttonState)
    {call(buttonState);
    pbuttonState=buttonState;
    }
  }
  delay(100);
}
}

String time()
{
 String dataString = "";  
 DateTime now = RTC.now();
 dataString += String(now.year(), DEC);
 dataString += String('/');
 dataString += String(now.month(), DEC);
 dataString += String('/');
 dataString += String(now.day(), DEC);
 dataString += String(' ');
 dataString += String(now.hour(), DEC);
 dataString += String(':');
 dataString += String(now.minute(), DEC);
 dataString += String(':');
 dataString += String(now.second(), DEC);

return dataString;       
}

void call(int buttonState)
{
    if (buttonState == LOW) {     
    // door is open    
    digitalWrite(ledPin, HIGH); 
    SDwrite(buttonState);
 
} 
  else {
    // door is closed
    digitalWrite(ledPin, LOW); 
    SDwrite(buttonState);
}
}


void SDwrite(int state)
{
String message = "";
if (state==LOW)  
{message = "OPEN";}
else
{message = "CLOSED";}
    data = SD.open("log.txt", FILE_WRITE);
    if (data) {
    if(state == LOW)
    {Serial.print("Door is open");}
    else
    {Serial.print("Door is closed");}
    data.print(time());
    data.print("   ");
    data.println(message);
  // close the file:
    data.close();
    Serial.println("  :done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening log.txt");
  }  
  
}  

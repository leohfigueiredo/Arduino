
#include <TimeLib.h>


#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

#include <Time.h>
#include <DS1302RTC.h>

// Set pins:  CE, IO,CLK
DS1302RTC RTC(31, 33, 35); // no MEGA, no UNO, deve-se alterar

// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1500 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL 1 // echo data to serial port
#define WAIT_TO_START 0 // Wait for serial input in setup()



int ledPin = 13; // choose the pin for the LED
int inputPin = 2; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
// for the data logging shield, we use digital pin 4 for the SD cs line
const int chipSelect = 4; // chipselect do arduino MEGA, se for UNO, deve alterar
// the logging file
File logfile; // preparação para log de informações 


void error(char *str)
{
Serial.print("error: ");
Serial.println(str);
// red LED indicates error
while(1);
}


void setup(void)
{

    pinMode(10, OUTPUT); // para o mega funcionar com o Ethernet, desligar o chip enable padrão, na porta 10
    digitalWrite(10, HIGH);
    
Serial.begin(9600);
Serial.println();

// use debugging LEDs
#if WAIT_TO_START
Serial.println("Type any character to start");
while (!Serial.available());
#endif //WAIT_TO_START

// initialize the SD card
Serial.print("Initializing SD card...");

// make sure that the default chip select pin is set to
// output, even if you don't use it:
pinMode(10, OUTPUT);

// see if the card is present and can be initialized:
if (!SD.begin(chipSelect)) {
error("Card failed, or not present");
}
Serial.println("card initialized.");
// create a new file
char filename[] = "LOGGER00.CSV";

for (uint8_t i = 0; i < 100; i++) {
  filename[6] = i/10 + '0';
  filename[7] = i%10 + '0';

if (! SD.exists(filename)) {
// only open a new file if it doesn't exist
logfile = SD.open(filename, FILE_WRITE);
break; // leave the loop!
}
}
if (! logfile) {
error("couldnt create file");
}
Serial.print("Logging to: ");
Serial.println(filename);
// connect to RTC
Wire.begin();
if (!RTC.writeEN()) { //lê o estado do RTC - relógio
logfile.println("RTC failed");
#if ECHO_TO_SERIAL
Serial.println("RTC failed");
#endif //ECHO_TO_SERIAL
}
logfile.println("millis,stamp,datetime,status");
#if ECHO_TO_SERIAL
Serial.println("millis,stamp,datetime,status");
#endif //ECHO_TO_SERIAL
}


void loop(void)
{
val = digitalRead(inputPin); // read input value
if (val == HIGH) { // check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState == LOW) {
// we have just turned on
logData();
Serial.print(", ");
Serial.println("botao pressionado!");
logfile.print(", ");
logfile.println("botao solto!!");
logfile.flush();
// We only want to print on the output change, not state
pirState = HIGH;
}
}
else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState == HIGH){
logData();
// we have just turned of
Serial.print(", ");
Serial.println("botao solto!!");
logfile.print(", ");
logfile.println("botao solto!!");
logfile.flush();
// We only want to print on the output change, not state
pirState = LOW;
}
}
}

void logData(){
DateTime now;
// log milliseconds since starting
uint32_t m = millis();
logfile.print(m); // milliseconds since start
logfile.print(", ");
#if ECHO_TO_SERIAL
Serial.print(m); // milliseconds since start
Serial.print(", ");
#endif
now = RTC.get(); // o get é da biblioteca do RTC 1302, pega o horário atual
// log time
logfile.print(now.unixtime()); // seconds since 1/1/1970
logfile.print(", ");
logfile.print('"');
logfile.print(now.year(), DEC);
logfile.print("/");
logfile.print(now.month(), DEC);
logfile.print("/");
logfile.print(now.day(), DEC);
logfile.print(" ");
logfile.print(now.hour(), DEC);
logfile.print(":");
logfile.print(now.minute(), DEC);
logfile.print(":");
logfile.print(now.second(), DEC);
logfile.print('"');
#if ECHO_TO_SERIAL
Serial.print(now.unixtime()); // seconds since 1/1/1970
Serial.print(", ");
Serial.print('"');
Serial.print(now.year(), DEC);
Serial.print("/");
Serial.print(now.month(), DEC);
Serial.print("/");
Serial.print(now.day(), DEC);
Serial.print(" ");
Serial.print(now.hour(), DEC);
Serial.print(":");
Serial.print(now.minute(), DEC);
Serial.print(":");
Serial.print(now.second(), DEC);
Serial.print('"');
#endif //ECHO_TO_SERIAL
}



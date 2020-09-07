/*
  created by Rui Santos,
  http://randomnerdtutorials.com

  Complete Guide for Ultrasonic Sensor
  HC
  -
  SR04

  Ultrasonic sensor Pins:
  VCC: +5VDC
  Trig : Trigger (INPUT)
  -
  Pin11
  Echo: Echo (OUTPUT)
  -
  Pin 12
  GND: GND
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#include "LedControl.h"
#include "binary.h"
/*
  DIN connects to pin 12
  CLK connects to pin 11
  CS connects to pin 10
*/
LedControl lc = LedControl(12, 11, 10, 1);

// delay time to  faces
unsigned long delaytime = 1000;

// happy face
byte hf[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};
// neutral face
byte nf[8] = {B00111100, B01000010, B10100101, B10000001, B10111101, B10000001, B01000010, B00111100};
// sad face
byte sf[8] = {B00111100, B01000010, B10100101, B10000001, B10011001, B10100101, B01000010, B00111100};


int trigPin = 9; //Trig - green Jumper
int echoPin = 8; //Echo - yellow Jumper
long duration, distanceCm, distanceInch;

void setup()
{
  lcd.begin(20, 4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lc.shutdown(0, false);
  // Set brightness to a medium value
  lc.setIntensity(0, 8);
  // Clear the display
  lc.clearDisplay(0);
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void drawFacesSAD() {
  // Display sad face
  lc.setRow(0, 0, sf[0]);
  lc.setRow(0, 1, sf[1]);
  lc.setRow(0, 2, sf[2]);
  lc.setRow(0, 3, sf[3]);
  lc.setRow(0, 4, sf[4]);
  lc.setRow(0, 5, sf[5]);
  lc.setRow(0, 6, sf[6]);
  lc.setRow(0, 7, sf[7]);
  delay(delaytime);
}
void drawFacesNEUTRAL() {
  // Display neutral face
  lc.setRow(0, 0, nf[0]);
  lc.setRow(0, 1, nf[1]);
  lc.setRow(0, 2, nf[2]);
  lc.setRow(0, 3, nf[3]);
  lc.setRow(0, 4, nf[4]);
  lc.setRow(0, 5, nf[5]);
  lc.setRow(0, 6, nf[6]);
  lc.setRow(0, 7, nf[7]);
  delay(delaytime);
}
void drawFacesHAPPY() {
  // Display happy face
  lc.setRow(0, 0, hf[0]);
  lc.setRow(0, 1, hf[1]);
  lc.setRow(0, 2, hf[2]);
  lc.setRow(0, 3, hf[3]);
  lc.setRow(0, 4, hf[4]);
  lc.setRow(0, 5, hf[5]);
  lc.setRow(0, 6, hf[6]);
  lc.setRow(0, 7, hf[7]);
  delay(delaytime);
}
void loop()
{
  // The sensor is triggered by a HIGH pulse of 10 or more
  // Give a short LOW pulse beforehand to ensure a clean  HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  distanceCm = (duration / 2) / 29.1;
  distanceInch = (duration / 2) / 74;
  Serial.print(distanceInch);
  Serial.print("in, ");
  Serial.print(distanceCm);
  Serial.print("cm");
  Serial.println();
  delay(250);
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance to bulkhead"); // Prints string "Distance" on the LCD
  delay(200);
  lcd.setCursor(0, 2); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("  Distance: "); // Prints string "Distance" on the LCD
  lcd.print(distanceCm); // Prints the distance value from the sensor
  lcd.print(" cm  ");
  delay(100);
  lcd.setCursor(0, 3);
  lcd.print("  Distance: ");
  lcd.print(distanceInch);
  lcd.print(" in ");
  delay(200);
  


  if (distanceCm > 3 && distanceCm < 50 )
  {
    drawFacesHAPPY();
    delay(50);

  } else if (distanceCm > 51 && distanceCm < 100)
  {
    drawFacesNEUTRAL();

  }
  else if (distanceCm > 100)
  { drawFacesSAD();
  lcd.clear();

  }



}


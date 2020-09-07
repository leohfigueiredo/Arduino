
/*
------------------------------------------------------------------------------------------------
  Arduino Excel 2.1
    
    created         June 20th 2016 by Roberto Valgolio

    last modified   25/07/2016

    history         25/07/2016  improved protocol with acknowledgement for each message

    notes

    this example code is in the public domain
    any feedback will be appreciated, please write to roberto.valgolio@gmail.com

    This sketch exchanges over serial csv messages with ArduinoExcel_xx.xls app by the same author

------------------------------------------------------------------------------------------------
*/

#include <rExcel.h>

long          idx = 0;                // index
int           outputTiming = 1000;    // packet sending timing in ms      important: this dermines the output timing
float         a0;                     // A0 pin reading
float         rnd;                    // random number

rExcel        myExcel;                // class for Excel data exchanging


void setup(){
  
  //Serial.begin(9600);
  Serial.begin(115200);
  delay(1000);
  
  // rx buffer clearing
  myExcel.clearInput();

  // if analog input pin 5 is unconnected, random analog noise will cause the call to randomSeed() to generate different seed numbers each time the sketch runs
  randomSeed(analogRead(5));
}


void loop() {

  static unsigned long  loopTime = 0;
  static unsigned long  time1 = 0;

  loopTime = millis();

  // Output Task
  // instructions performed each outputTiming ms
  if ((loopTime - time1) >= outputTiming) {

    time1 = loopTime;

    // set your custom values
    a0 = (float)analogRead(0) / 1023.0 * 5.0;               // A0 reading converted to volt
    rnd = (float)random(0, 1000) / 1023.0 * 5.0;            // random value

    // look the following examples and modify the code as you need

    // example1
    myExcel.write("Example", "B5", a0, 2);                  // write the value from A0 pin to worksheet 'Example' cell 'B5' with two digits as decimals
    myExcel.write("Example", "B6", rnd, 2);                 // write a random value to worksheet 'Example' cell 'B6' with two digits as decimals

  }
}   // end of loop


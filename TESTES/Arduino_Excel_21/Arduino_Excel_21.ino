
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
/*
char          worksheet[16];          // worksheet name
char          range[16];              // range set
unsigned int  row;                    // row
unsigned int  column;                 // column
*/
char          value[16];              // written or read value

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
  int ret;

  loopTime = millis();

  // Output Task
  // Arduino acts as client making requests to Excel
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

    // example2
    myExcel.writeIndexed("Example", idx+11, 1,"%date%");    // write %date% (that will be converted in current date) to worksheet 'Example' row 'idx+11' column '1' 
    myExcel.writeIndexed("Example", idx+11, 2,"%time%");    // write %time% (that will be converted in current time) to worksheet 'Example' row 'idx+11' column '2' 
    myExcel.writeIndexed("Example", idx+11, 3, idx);        // write idx to worksheet 'Example' row 'idx+11' column '3' 
    myExcel.writeIndexed("Example", idx+11, 4, a0, 2);      // write the value from A0 pin to worksheet 'Example' row 'idx+11' column '4' with two digits as decimals
    myExcel.writeIndexed("Example", idx+11, 5, rnd, 2);     // write a random value to worksheet 'Example' row 'idx+11' column '5' with two digits as decimals
/*
    // example3
    if (myExcel.get("Test", "B5", value) == 0) {            // get a value from worksheet 'Test' cell 'B5'
      myExcel.write("Test", "D5", value);                   // only as proof that works
      int x = atoi(value);                                  // convert value and put it in a int variable 
      // write here your code
    }

    // example3
    if (myExcel.getIndexed("Test",idx+5, 2, value)) {       // get a value from worksheet 'Test' row 'idx+5' column '2'
      myExcel.writeIndexed("Test", idx+5, 3, value);        // only as proof that works
      // write here your code
    }
*/
    idx++;
  
    if (idx > 59) {
      myExcel.clear("Example","A11:F70");                   // clear cells in A11:F70 area of 'Example' worksheet
      //myExcel.clear("Test","C5:C64");                     // clear cells in C5:C64 area of 'Test' worksheet
      //myExcel.save();                                     // save the Excel file (useful for activites over a long time)
      idx = 0;
    }
  }

/*
  // input task
  // Arduino acts as server waiting requests from Excel
  // usewful for advanced applications, use this instead of get() or getIndexed()
  if (Serial.available() > 0) {
    if ((ret = myExcel.read(worksheet, range, &row, &column, value, 'R')) > 0) {
      Serial.print(XLS_ACK);
      Serial.print("\n");
      // write here your code
      range[0] = 'H';
      myExcel.write(worksheet, range, value);               // only as proof that works
    }
    else {
      // input clearing
      Serial.print(XLS_NAK);
      Serial.print("\n");
      myExcel.clearInput();
    }
  }
*/

}   // end of loop


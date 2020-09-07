#include <virtuabotixRTC.h>


// Creation of the Real Time Clock Object
//SCLK -> 6, I/O -> 7, CE -> 8
virtuabotixRTC myRTC(35, 33, 31);

void setup() {
Serial.begin(9600);

// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year
myRTC.setDS1302Time(00, 39, 10, 1, 16, 4, 2017);
}

void loop() {
// This allows for the update of variables for time or accessing the individual elements.
myRTC.updateTime();

// Start printing elements as individuals
Serial.print("Current Date / Time: ");
Serial.print(myRTC.dayofmonth);
Serial.print("/");
Serial.print(myRTC.month);
Serial.print("/");
Serial.print(myRTC.year);
Serial.print(" ");
Serial.print(myRTC.hours);
Serial.print(":");
Serial.print(myRTC.minutes);
Serial.print(":");
Serial.println(myRTC.seconds);

// Delay so the program doesn't print non-stop
delay( 5000);
}

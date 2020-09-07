// each "event" (LED) gets their own tracking variable
unsigned long previousMillisLED9=0;
unsigned long previousMillisLED10=0;
// different intervals for each LED
int intervalLED9 = 500;
int intervalLED10 = 1000;
// each LED gets a state varaible
boolean LED10state = false;     // the LED will turn ON in the first iteration of loop()
boolean LED9state = false;     // need to seed the light to be OFF
void setup() {
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
}
void loop() {
// get current time stamp
// only need one for both if-statements
unsigned long currentMillis = millis();
// time to toggle LED on Pin 12?
if ((unsigned long)(currentMillis - previousMillisLED9) >= intervalLED9) {
LED9state = !LED9state;
digitalWrite(9, LED9state);
// save current time to pin 12's previousMillis
previousMillisLED9 = currentMillis;
}
// time to toggle LED on Pin 13?
if ((unsigned long)(currentMillis - previousMillisLED10) >= intervalLED10) {
LED10state = !LED10state;
digitalWrite(10, LED10state);
// save current time to pin 12's previousMillis
previousMillisLED10 = currentMillis;
}
}


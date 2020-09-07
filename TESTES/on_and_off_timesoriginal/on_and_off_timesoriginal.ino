// On and Off Times (as int, max=32secs)
const unsigned long onTime = 20000;
const unsigned long offTime = 15000;

const unsigned long onTime1 = 20000;
const unsigned long offTime1 = 15000;

const unsigned long onTime2 = 30000;
const unsigned long offTime2 = 25000;
 
// Tracks the last time event fired
unsigned long previousMillis=5000;
unsigned long previousMillis1=1000;
unsigned long previousMillis2=100;
 
// Interval is how long we wait
long interval = onTime;
long interval1 = onTime1;
long interval2 = onTime2;
 
// Used to track if LED should be on or off
boolean LED7state = true;
boolean LED8state = true;
boolean LED9state = true;
 
// Usual Setup Stuff
void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
 
void loop() {
  // Set Pin 13 to state of LED13state each timethrough loop()
  // If LED13State hasn't changed, neither will the pin
  digitalWrite(7, LED7state);
  digitalWrite(8, LED8state);
  digitalWrite(9, LED9state);
  
  // Grab snapshot of current time, this keeps all timing
  // consistent, regardless of how much code is inside the next if-statement
  unsigned long currentMillis = millis();
 unsigned long currentMillis1 = millis();
 unsigned long currentMillis2 = millis();
 
  // Compare to previous capture to see if enough time has passed
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    // Change wait interval, based on current LED state
    if (LED7state) {
      // LED is currently on, set time to stay off
      interval = offTime;
    } else {
      // LED is currently off, set time to stay on
      interval = onTime;
    }
    // Toggle the LED's state, Fancy, eh!?
    LED7state = !(LED7state);
previousMillis = currentMillis;
    // Save the current time to compare "later"
    
  }
   
 
  // Compare to previous capture to see if enough time has passed
  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
    // Change wait interval, based on current LED state
    if (LED8state) {
      // LED is currently on, set time to stay off
      interval1 = offTime1;
    } else {
      // LED is currently off, set time to stay on
      interval1 = onTime1;
    }
    // Toggle the LED's state, Fancy, eh!?
    LED8state = !(LED8state);
 previousMillis1 = currentMillis1;
    // Save the current time to compare "later"
    
  }
   if ((unsigned long)(currentMillis - previousMillis2) >= interval2) {
    // Change wait interval, based on current LED state
    if (LED9state) {
      // LED is currently on, set time to stay off
      interval2 = offTime2;
    } else {
      // LED is currently off, set time to stay on
      interval2 = onTime2;
    }
    // Toggle the LED's state, Fancy, eh!?
    LED9state = !(LED9state);
 
    // Save the current time to compare "later"
    previousMillis2 = currentMillis;
  }
  
}



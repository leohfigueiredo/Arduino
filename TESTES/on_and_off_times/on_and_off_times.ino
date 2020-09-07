// On and Off Times (as int, max=32secs)
const unsigned int onTime = 10000;
const unsigned int offTime = 5000;

const unsigned int onTime1 = 20000;
const unsigned int offTime1 = 15000;

const unsigned int onTime2 = 30000;
const unsigned int offTime2 = 25000;
 
// Tracks the last time event fired
unsigned long previousMillis=0;
 
// Interval is how long we wait
int interval = onTime;
int interval1 = onTime1;
int interval2 = onTime2;
 
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
 
    // Save the current time to compare "later"
    previousMillis = currentMillis;
  }

  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
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
 
    // Save the current time to compare "later"
    previousMillis = currentMillis;
  }
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
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
    previousMillis = currentMillis1;
  }
}


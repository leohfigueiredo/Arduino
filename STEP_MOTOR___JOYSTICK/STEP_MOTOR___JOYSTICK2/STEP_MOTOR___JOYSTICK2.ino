/*
 * Unipolar stepper motor speed and direction control with Arduino
 *   and joystick
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */


#include <THiNX32Lib.h>

#define __DEBUG__
#define ARDUINO_IDE

// include Arduino stepper motor library
#include <Stepper.h>
 
// define number of steps per revolution
#define STEPS 32
 
// define stepper motor control pins
#define IN1  27
#define IN2  14
#define IN3   12
#define IN4   13
 
// initialize stepper library
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
 
// joystick pot output is connected to Arduino A0
#define joystick  2

const char *apikey = "4721f08a6df1a36b8517f678768effa8b3f2e53a7a1934423c1f42758dd83db5";
const char *owner_id = "cedc16bb6bb06daaa3ff6d30666d91aacd6e3efbf9abbc151b4dcade59af7c12";
const char *ssid = "L&F";
const char *pass = "41992549713";

THiNX thx;

/* Called after library gets connected and registered */
void finalizeCallback () {
  Serial.println("*INO: Finalize callback called. Will fall asleep.");
  ESP.deepSleep(3e9);
}

 
void setup()
{
    Serial.begin(230400);

#ifdef __DEBUG__
  while (!Serial); // wait for debug console connection
  Serial.println("Connecting to predefined WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(2000);
#endif

  // Enter API Key and Owner ID (should be faster)
  thx = THiNX(apikey, owner_id);
thx.setFinalizeCallback(finalizeCallback);
}
 
void loop()
{
  // read analog value from the potentiometer
  int val = analogRead(joystick);
 
  // if the joystic is in the middle ===> stop the motor
  if(  (val > 500) && (val < 523) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
 
  else
  {
    // move the motor in the first direction
    while (val >= 523)
    {
      // map the speed between 5 and 500 rpm
      int speed_ = map(val, 523, 1023, 5, 500);
      // set motor speed
      stepper.setSpeed(speed_);
 
      // move the motor (1 step)
      stepper.step(1);
 
      val = analogRead(joystick);
    }
 
    // move the motor in the other direction
    while (val <= 500)
    {
      // map the speed between 5 and 500 rpm
      int speed_ = map(val, 500, 0, 5, 500);
      // set motor speed
      stepper.setSpeed(speed_);
 
      // move the motor (1 step)
      stepper.step(-1);
 
      val = analogRead(joystick);
    }
 
  }
  thx.loop();
}

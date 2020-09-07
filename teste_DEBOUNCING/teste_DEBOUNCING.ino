#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

boolean start = true;
volatile boolean e_stop = false;

const int buttonPin = 3;    // the number of the pushbutton pin
const int rele00 = 8;      // the number of the LED pin

const int buttonPin1 = 4;    // the number of the pushbutton pin
const int rele02 = 9;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int ledState1 = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int buttonState1;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {

   Serial.begin(9600);
 delay(100);
 lcd.begin (20,4);
 
  pinMode(buttonPin, INPUT);
  pinMode(rele00, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(rele02, OUTPUT);
  
attachInterrupt(0,e_stop_ISR, RISING);

  // set initial LED state
  digitalWrite(rele00, ledState);
  digitalWrite(rele02, ledState1);
}

void loop() {

   if(start == true){


    if(e_stop == false){
Serial.println("tudo ok");
delay(300);
    }
    else{

Serial.println("EMERGENCIA!!!! RESETAR ARDUINO");
digitalWrite (rele00, HIGH); // envia saida para nivel alto
    }

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);



  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(rele00, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
}

 void e_stop_ISR(void){
  detachInterrupt(0);
  e_stop = !e_stop;

}

/* Connect the positive side of your LED to Arduino digital pin 13 Connect the negative side of your LED to a 330 Ohm resistor Connect the other side of the resistor to ground

*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

// First we'll set up constants for the pin numbers.
// This will make it easier to follow the code below.

const int button1Pin = 2; // pushbutton 1 pin
const int led1Pin = 8; // LED 1 pin
const int led2Pin = 9; // LED 2 pin
const int led3Pin = 10; // LED 3 pin

int iState;
bool bWasPressed; //Variable to see if the buton was pressed

void setup()
{
// Set up the pushbutton pins to be an input:
pinMode(button1Pin, INPUT);

// Set up the LED pin to be an output:
pinMode(led1Pin, OUTPUT); 
pinMode(led2Pin, OUTPUT); 
pinMode(led3Pin, OUTPUT); //Default to state 0

iState = 1; bWasPressed = true;

 Serial.begin(9600);
  lcd.begin (20,4);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("PROCESSO         ETO");
  delay(200);
  lcd.setCursor(0,2);
  lcd.print("    INICIALIZADO    ");
  delay(200);
  lcd.setCursor(0,3);
  lcd.print("--****************--");
  delay(200);

// initialize serial communication at 9600 bits per second:
// Serial.begin(9600);

}

void loop()
{
int iBtnState; // variable to hold the pushbutton state // iBtnState: HIGH = button not pressed
// LOW = button is pushed 
iBtnState = digitalRead(button1Pin);


//Now determine whether I need to change state.
if (iBtnState == 1) { //The button is not pressed. If the button was just //released then go on ahead to the next state. 
  if (bWasPressed==1) { //Yes, the button was just released. //Move to the next state. 
    iState++; iState = iState % 4; //Reset the button pressed flag. 
    bWasPressed = false; }
}

else
{ //The button is pressed, just set the flag. 
  bWasPressed = true;
}

//Take action depending on the state of the machine.
switch (iState)
{ case 0: //Turn off all LEDs 
digitalWrite(led1Pin, LOW); 
digitalWrite(led2Pin, HIGH); 
digitalWrite(led3Pin, HIGH); 

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  delay(1000);
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
  delay(1000);

break; 

case 1: //Turn on first LED 
digitalWrite(led1Pin, HIGH);
digitalWrite(led2Pin, HIGH); 
digitalWrite(led3Pin, LOW);  
break; 

case 2: //Turn on second LED 
digitalWrite(led2Pin, HIGH); 
break; 

case 3: //Turn on third LED 
digitalWrite(led1Pin, HIGH);
digitalWrite(led2Pin, HIGH);break;
}

}

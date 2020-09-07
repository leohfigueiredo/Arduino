const int numButtons = 3;
unsigned long debounceDelay = 80;
const int pwLen = 6;
int pwcount = 0;
int arrUser[pwLen]; // will hold user input
int arrPw[pwLen] = {1, 2, 3, 1, 2, 3};
const byte ledRed = 8;
const byte ledGreen = 9;

const int buttonPins[numButtons] = {2, 3, 4};

// structure to hold info for one button
typedef struct {

  int pin;
  unsigned long lastDebounceTime;
  byte buttonState;
  byte lastButtonState;

} buttonInfo;

buttonInfo buttons[numButtons];   // info for all buttons

// Initialize info for all buttons
void initButtons()
{
  for (int i = 0; i < numButtons; i++)
  {
    buttons[i].pin = buttonPins[i];
    pinMode(buttons[i].pin, INPUT);
    buttons[i].lastDebounceTime = 0UL;
    buttons[i].buttonState = 0;

  } // for
}

// check status of a button
void checkButton(int idx)
{
  // read button pin
  buttons[idx].buttonState = digitalRead(buttons[idx].pin);

  if ( (millis() - buttons[idx].lastDebounceTime) > debounceDelay) {
    if (buttons[idx].buttonState != buttons[idx].lastButtonState) {
      if ( buttons[idx].buttonState == HIGH) {
        arrUser[pwcount] = idx + 1;
        pwcount++;
        delay(200);
        Serial.println(idx+1);
      }
    }
    buttons[idx].lastButtonState = buttons[idx].buttonState;
    buttons[idx].lastDebounceTime = millis(); //set the current time
  }



}



void setup() {

  initButtons();  // initialize buttons

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  int i;

  // check sateus of each button
  for (i = 0; i < numButtons; i++) checkButton(i);

  // if we have enough button presses
  if ( pwcount == pwLen )
  {
    bool success = true;

    // check each value
    for ( i = 0; i < pwLen; i++ )
    {
      if ( arrUser[i] != arrPw[i] )
      {

        success = false;  // sequence not correct
        break;            // stop comparing

      } // if
    } // for

    if ( success )
    {
      digitalWrite(ledGreen, LOW);
      Serial.println(F("Correct"));
      delay(2000);
      digitalWrite(ledGreen, HIGH);

    } else {

      digitalWrite(ledRed, LOW);
      Serial.println(F("Wrong"));
      delay(2000);
      digitalWrite(ledRed, HIGH);
    }

    pwcount = 0;

  } // if

}

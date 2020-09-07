

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin4 = 2;     // the number of the pushbutton pin
const int buttonPin3 = 3;
const int buttonPin2 = 4;
const int buttonPin1 = 5;

const long interval1 = 60000; // 1,5 and 15 min intervals
const long interval5 = 300000;
const long interval15 = 900000;


const int ledPin4 =  7;      // the number of the LED pin
const int ledPin3 =  8;
const int ledPin2 =  9;
const int ledPin1 =  10;

// variables will change:
int button4State = 0;         // variable for reading the pushbutton status
int button3State = 0;
int button2State = 0;
int button1State = 0;

long previousMillis1 = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
long previousMillis4 = 0;


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin1, OUTPUT);
 
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin1, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  button4State = digitalRead(buttonPin4);
  button3State = digitalRead(buttonPin3);
  button2State = digitalRead(buttonPin2);
  button1State = digitalRead(buttonPin1);

  unsigned long currentMillis = millis();

 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (button4State == HIGH) {
    // turn LED on:
    digitalWrite(ledPin4, LOW);
    delay(3600000);
  }
     
       if (currentMillis > interval1)
           digitalWrite(ledPin4, HIGH);
     
  else {
    // turn LED off:
    digitalWrite(ledPin4, HIGH);
 
  }
  if (button3State == HIGH) {
    // turn LED on:
    digitalWrite(ledPin3, LOW);
    delay(3600000);
  }
 else {
    // turn LED off:
    digitalWrite(ledPin3, HIGH);
  }
   if (button2State == HIGH) {
    // turn LED on:
    digitalWrite(ledPin2, LOW);
    delay(3600000);
  }
 else {
    // turn LED off:
    digitalWrite(ledPin2, HIGH);
  }
   if (button1State == HIGH) {
    // turn LED on:
    digitalWrite(ledPin1, LOW);
    delay(10000);
  }
 else {
    // turn LED off:
    digitalWrite(ledPin1, HIGH);
    
  }
}

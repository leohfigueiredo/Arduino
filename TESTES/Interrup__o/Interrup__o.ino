const byte ledPin = 7;
const byte interruptPin = 2;
volatile byte state = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
  
}

void blink() {
  state = !state;
    digitalWrite(ledPin, HIGH);
    delay(1000);
}

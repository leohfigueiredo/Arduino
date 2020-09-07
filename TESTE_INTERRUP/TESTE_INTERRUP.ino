int  button_interrupt = 0;    //  Interrupt 0 is on pin 2 !!
int  toggle_on = true;       //  Button click switches state

#define rele00 8
int estadorele00 = 1;

void setup() {
  Serial.begin(9600);
  attachInterrupt( button_interrupt, handle_click, RISING);  // Register handler
  digitalWrite(rele00, estadorele00);
}

void loop() {
  if ( toggle_on ) {
digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
  } else {
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
  }
}

void  handle_click() {

  static unsigned long last_interrupt_time = 0;       //  Zero only at start
  unsigned long interrupt_time = millis();             // Read the clock

  if ( interrupt_time - last_interrupt_time > 200 ) {  // Ignore when < 200 msec
    toggle_on = !toggle_on;
  }

  last_interrupt_time = interrupt_time;
}

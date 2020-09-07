int  button_interrupt = 0;    //  Interrupt 0 is on pin 2 !!
int  button_interrupt1 = 1;    //  Interrupt 0 is on pin 3 !!
int  button_interrupt2 = 2;    //  Interrupt 0 is on pin 19 !!
int  toggle_on = true;
int  toggle_on1 = true;//  Button click switches state
int  toggle_on2 = true;

#define rele00 8 // rele motor 3
#define rele02 9 // rele motor 3

int estadorele00 = 1;
int estadorele02 = 1;

void setup() {
  Serial.begin(9600);
  attachInterrupt( button_interrupt, handle_click, RISING);  // Register handler
  attachInterrupt( button_interrupt1, handle_click, RISING);
  attachInterrupt( button_interrupt2, handle_click, RISING); 

   pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida

digitalWrite(rele00, estadorele00);
digitalWrite(rele02, estadorele02);
}

void loop() {
  if ( toggle_on1 ) {
digitalWrite (rele02, HIGH); // envia saida para nivel alto
  } else {

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


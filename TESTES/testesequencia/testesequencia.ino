unsigned long currentMillis, previousMillis, restartMillis; // time snapshots
const long interval = 1000; // interval in milliseconds
const long restartInterval = 15000; // start all over
byte numberOfLEDs = 4; // four LEDs
byte LED[] {10,9,8,7}; // array for the LEDs
byte pointer; // points to one LED

int porta_botao1 = 2;
//Porta ligada ao botao 2
int porta_botao2 = 3;
//Porta ligada ao botao 3
int porta_botao3 = 4;
//Porta ligada ao botao 4
int porta_botao4 = 5;
 
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;
int estadorele2 = 1;
int estadorele3 = 1;
int estadorele4 = 1;

//Armazena o valor lido dos botoes
int leitura1 = 0;
int leitura2 = 0;
int leitura3 = 0;
int leitura4 = 0;

void setup() {
  for (int x = 0; x < numberOfLEDs; x ++) {
    pinMode (LED[x], OUTPUT); // make all the LED pins an output
  }
}

void loop() {
  if (currentMillis - restartMillis > restartInterval) { // if restart time is reached
    for (int x = 0; x < numberOfLEDs; x ++) {
      digitalWrite (LED[x], LOW); // turn all LEDs off
    }
    delay(interval); // boot with all LEDs off
    pointer = 0; // point to the first LED
    restartMillis = currentMillis; // reset restart timer
  }
  currentMillis = millis(); // update with every loop
  LEDs(); // run LED sequence
  servos();
}

void LEDs() {
  if (currentMillis - previousMillis > interval && pointer < numberOfLEDs) { // condition
    digitalWrite(LED[pointer], HIGH); // turn that LED on
    pointer ++; // point to the next LED
    previousMillis = currentMillis; // start a new interval
  }
}

void servos() {
  // servo code goes here
}

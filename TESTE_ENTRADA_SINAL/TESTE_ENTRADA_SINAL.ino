#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

int entradaChave = 4; // Set up chave SW
int estadoChave = LOW;
int val = 0;
int relayPin = 3; //Set up Pino Relay

void setup() {
pinMode(entradaChave, INPUT);
pinMode(relayPin, OUTPUT);
Serial.begin(9600);
lcd.begin (16,2);
}

void loop() {
val = digitalRead(entradaChave); // read input value
if (val == HIGH) { // check if the input is HIGH
digitalWrite(relayPin, HIGH); // turn Relay ON
delay(150);

if (estadoChave == LOW) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3 ");
  lcd.setCursor(0,1);
  lcd.print("DESLIGADO");

estadoChave = HIGH;
}
} else {
digitalWrite(relayPin, LOW); // turn Relay OFF
delay(150);
if (estadoChave == HIGH) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3 ");
  lcd.setCursor(0,1);
  lcd.print("LIGADO   ");

estadoChave = LOW;
}
}
}

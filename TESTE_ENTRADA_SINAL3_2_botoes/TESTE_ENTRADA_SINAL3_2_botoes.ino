#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

int entradaChave = 3; // Set up chave SW
int estadoChave = LOW;
int val = 0;
int relayPin = 3; //Set up Pino Relay


int entradaChave2 = 5; // Set up chave SW
int estadoChave2 = LOW;
int val2 = 0;
int pinoRele2 = 9; //Set up Pino Relay 
int pinoRele0 = 8; //Set up Pino Relay 


void setup() {
pinMode(entradaChave, INPUT);
pinMode(relayPin, OUTPUT);
pinMode(entradaChave2, INPUT);
pinMode(pinoRele2, OUTPUT);
pinMode(pinoRele0, OUTPUT);

int pinoRele2 = LOW;
delay(1000);
Serial.begin(9600);
lcd.begin (16,2);
}

void loop() {
val = digitalRead(4); // read input value
if (val == HIGH) { // check if the input is HIGH
digitalWrite(3, LOW); // turn Relay ON
digitalWrite(9, HIGH); // turn Relay ON
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
digitalWrite(3, LOW); // turn Relay OFF
digitalWrite(9, HIGH); // turn Relay ON
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

      val2 = digitalRead(entradaChave2); // leitura entrada chave SW
          if (val2 == HIGH) { // checa se a entrada é HIGH
          digitalWrite(pinoRele2, HIGH); // Liga Relé (ON)
          delay(150);
          digitalWrite(pinoRele0, HIGH); // desliga Relé OFF
          delay(150);

if (estadoChave2 == LOW) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 4 ");
  lcd.setCursor(0,1);
  lcd.print("DESLIGADO");

estadoChave2 = HIGH;
}
}
else {
  
      digitalWrite(pinoRele2, LOW); // desliga Relé OFF
      delay(150);
      digitalWrite(pinoRele0, LOW); // desliga Relé OFF
      delay(150);

           
if (estadoChave2 == HIGH) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 4 ");
  lcd.setCursor(0,1);
  lcd.print("LIGADO   ");

estadoChave2 = LOW;
}
}
delay(1000);
}

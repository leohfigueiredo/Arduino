#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

int entradaChave1 = 3; // Set up chave SW
int estadoChave1 = LOW;
int val1 = 0;
int pinoRele0 = 3; //Set up Pino Relay
int pinoRele6 = 13; // Rele de entrada Rele 0


int entradaChave2 = 5; // Set up chave SW
int estadoChave2 = LOW;
int val2 = 0;
int pinoRele2 = 9; //Set up Pino Relay 

int faseSistema;

//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele0 = 1;
int estadorele2 = 1;
int estadorele6 = 1;

void setup() {
pinMode(entradaChave1, INPUT_PULLUP);
pinMode(entradaChave2, INPUT_PULLUP);

pinMode(pinoRele0, OUTPUT);
pinMode(pinoRele2, OUTPUT);
pinMode(pinoRele6, OUTPUT);

digitalWrite(pinoRele6, HIGH);
delay(1500);

estadoChave1 = digitalRead(entradaChave1);

Serial.begin(9600);
lcd.begin (16,2);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3 ");
  lcd.setCursor(0,1);
  lcd.print("LIGADO   ");

}

void loop() {

  

  
if ((estadoChave1 == LOW) && (entradaChave1 == HIGH)){
     
     if (faseSistema < 2) {
       faseSistema = faseSistema + 1;
     } else {
       faseSistema = 0;
     }  
  }

  estadoChave1 = entradaChave1;

  if (faseSistema == 1) {    //SEMAFORO ABERTO (VERDE)
     digitalWrite(pinoRele6, HIGH);
     digitalWrite(pinoRele2, LOW);


if (estadoChave1 == LOW) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3 ");
  lcd.setCursor(0,1);
  lcd.print("DESLIGADO");

estadoChave1 = HIGH;
}
 if (faseSistema == 2) {   //SEMAFORO AMARELO
     digitalWrite(pinoRele6, LOW);
     digitalWrite(pinoRele2, HIGH);
 }
}
else {
  
      digitalWrite(pinoRele0, HIGH); // desliga Relé OFF
      delay(150);
                digitalWrite(pinoRele2, LOW); // desliga Relé (ON)
          delay(150);
    
if (estadoChave1 == HIGH) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3 ");
  lcd.setCursor(0,1);
  lcd.print("LIGADO   ");

estadoChave1 = LOW;
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

}

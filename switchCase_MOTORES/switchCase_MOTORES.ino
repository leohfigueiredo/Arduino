#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

int entradaChave = 4;
int rele6 = 2; //rele de acionamento rele motor 3
int rele2 = 9; // rele de acionamento motor 4
int rele0 = 8; // rele de acionamento motor 3

int entradaChave2 = 4;
int estadoChave2 = LOW;
int val2 = 0;


void setup() {

  pinMode(entradaChave, INPUT);
  pinMode(entradaChave2, INPUT);

  pinMode(rele2, OUTPUT);
  pinMode(rele0, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pins:
  for (int thisPin = 2; thisPin < 11; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  // read the sensor:

  if (rele0 = HIGH) {
    int estadoChave = digitalRead(3);
    // do something different depending on the character received.
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For
    // example 'a' = 97, 'b' = 98, and so forth:

    switch (estadoChave) {
      case HIGH:
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        break;
      case LOW:
        digitalWrite(9, LOW);
        digitalWrite(8, HIGH);
        break;
        default:
        // turn all the LEDs off:
        for (int thisPin = 2; thisPin < 7; thisPin++) {
          digitalWrite(thisPin, LOW);
        }
        
    }
  }
   val2 = digitalRead(entradaChave2); // leitura entrada chave SW
          if (val2 == HIGH) { // checa se a entrada é HIGH
          digitalWrite(rele2, HIGH); // Liga Relé (ON)
          delay(150);
          digitalWrite(rele0, LOW); // desliga Relé OFF
          delay(150);

if (estadoChave2 == LOW) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 4 ");
  lcd.setCursor(0,1);
  lcd.print("DESLIGADO");

estadoChave2 = LOW;
}
}
else {
  
      digitalWrite(rele2, LOW); // desliga Relé OFF
      delay(150);
      digitalWrite(rele0, LOW); // desliga Relé OFF
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



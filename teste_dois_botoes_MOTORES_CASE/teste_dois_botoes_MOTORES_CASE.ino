#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


int botaoinicio = 3; // define pino 9 como entrada botao liga
int chaveSW2 = 4; // define botao 8 como botao desliga
int chaveSW3 = 5;
#define rele00 8 // rele motor 3
#define rele02 9 // rele motor 4
#define pin12 12

int estadorele00 = 1;
int estadorele02 = 1;
int estadorele08 = 1;

void setup() {
 Serial.begin(9600);
 lcd.begin (16,2);

pinMode (pin12,OUTPUT); 
pinMode (botaoinicio, INPUT); // define como entrada
pinMode (chaveSW2, INPUT); // define como entrada
pinMode (chaveSW3, INPUT_PULLUP); // define como entrada
pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida


digitalWrite(rele00, estadorele00);
digitalWrite(rele02, estadorele02);

 lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO ");
  lcd.setCursor(0,1);
  lcd.print("INICIALIZADO");
  delay(3000);
  lcd.clear();
  delay(100); 

    tone(12,262,200); //DO
    delay(700);
    tone(12,262,200); //DO
    delay(500);
    tone(12,294,300); //RE
    delay(500);
    tone(12,262,200); //DO
    delay(500);
    tone(12,349,300); //FA
    delay(500);
    tone(12,330,300); //MI
    delay(200); 

      
}

void loop() {

int valorInicio = digitalRead (botaoinicio);// le o valor de botao
int valorSW2 = digitalRead (chaveSW2); // le o valor de botao1
int valorSW3 = digitalRead (chaveSW3); // le o valor de botao2


    
if (valorInicio == HIGH && valorSW2 == LOW) {// Testa o estado dos botoes
digitalWrite (rele02, HIGH); // envia saida para nivel alto
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
delay (1000);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 3");
  lcd.setCursor(0,1);
  lcd.print("LIGADO");
int estadorele00 = 1;
int estadorele02 = 0;
  
}

if (valorInicio == LOW && valorSW2 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,HIGH); // envia a saida para nivel alto
digitalWrite (rele02,LOW); // envia a saida para nivel baixo
delay (1000);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTOR 4");
  lcd.setCursor(0,1);
  lcd.print("LIGADO");

int estadorele00 = 1;
int estadorele02 = 1;

}

digitalWrite(estadorele00,estadorele02);

if (valorSW3 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
digitalWrite (rele02,LOW); // envia a saida para nivel baixo
delay (1000);
lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTORES 3 E 4");
  lcd.setCursor(0,1);
  lcd.print("LIGADOS");

}

digitalWrite(!estadorele00,!estadorele02);
if (valorSW3 == HIGH) { // Testa saida dos botoes
delay (5000); 
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
delay (5000);
digitalWrite (rele02,HIGH); // envia a saida para nivel alto

digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
delay (100);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("MOTORES");
  lcd.setCursor(0,1);
  lcd.print("DESLIGADOS");
  delay(10000);
  lcd.clear();

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("SEGUIR ARDUINO");
  lcd.setCursor(0,1);
  lcd.print("PROCESSOS");
  delay(10000);
}



}

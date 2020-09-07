#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


int botaoinicio = 3; // define pino 9 como entrada botao liga
int chaveSW2 = 4; // define botao 8 como botao desliga
int chaveSW3 = 5;
#define rele00 8 // rele motor 3
#define rele02 9 // rele motor 3
#define rele08 10 // rele acionamento motor 3 e motor 4

int estadorele00 = 1;
int estadorele02 = 1;
int estadorele08 = 1;

void setup() {

pinMode (botaoinicio, INPUT); // define como entrada
pinMode (chaveSW2, INPUT); // define como entrada
pinMode (chaveSW3, INPUT); // define como entrada
pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida
pinMode (rele08, OUTPUT); // define como saida

digitalWrite(rele00, estadorele00);
digitalWrite(rele02, estadorele02);
digitalWrite(rele08, estadorele08);

Serial.begin(9600);
lcd.begin (16,2);
}

void loop() {

int valorInicio = digitalRead (botaoinicio);// le o valor de botao
int valorSW2 = digitalRead (chaveSW2); // le o valor de botao1
int valorSW3 = digitalRead (chaveSW3); // le o valor de botao2

if (valorInicio == HIGH) {// Testa o estado dos botoes

digitalWrite (rele00,LOW); // envia a saida para nivel baixo

}else{
  digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
}

if (valorSW2 == HIGH) {// Testa o estado dos botoes

digitalWrite (rele02,LOW); // envia a saida para nivel baixo

}else{
  digitalWrite (rele02,HIGH); // envia a saida para nivel baixo
}

if (valorSW3 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
digitalWrite (rele02,LOW); // envia a saida para nivel baixo
}
else{
  digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
  digitalWrite (rele02,HIGH); // envia a saida para nivel baixo
}


}


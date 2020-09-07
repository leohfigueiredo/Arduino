#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);


#define pinBotao 2 //chave SW1

#define RELAY1  8  // motor 3  

int leitura1 = 1; //Armazena o valor lido dos botoes

//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 0;

void setup() {
  // put your setup code here, to run once:

pinMode(pinBotao, INPUT);
pinMode(RELAY1, OUTPUT);   

digitalWrite(RELAY1, HIGH);
}
void loop() {
  leitura1 = digitalRead(pinBotao);

  if (leitura1 != 0){
        while (digitalRead(pinBotao) != 1){
        digitalWrite(RELAY1, HIGH); 
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;   
    digitalWrite(RELAY1, LOW);           
    //Comandos para o rele 1
    
}

  
}

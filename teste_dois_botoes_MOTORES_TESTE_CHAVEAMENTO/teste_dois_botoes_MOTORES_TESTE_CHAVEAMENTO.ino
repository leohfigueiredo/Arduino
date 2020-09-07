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
int i; // CONTAGEM

void setup() {
 Serial.begin(9600);
 lcd.begin (20,4);
 
pinMode (botaoinicio, INPUT); // define como entrada
pinMode (chaveSW2, INPUT); // define como entrada
pinMode (chaveSW3, INPUT); // define como entrada
pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida
pinMode (rele08, OUTPUT); // define como saida



digitalWrite(rele00, estadorele00);
digitalWrite(rele02, estadorele02);
digitalWrite(rele08, estadorele08);

 lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("PROCESSO         ETO");
  delay(1000);
  lcd.setCursor(0,2);
  lcd.print("    INICIALIZADO    ");
  lcd.setCursor(0,3);
  lcd.print("--****************--");
  delay(5000);
  delay(100);
  
  //Faz o efeito de deslocamento para esquerda   
  for (i =0; i <20; i++){     
  lcd.scrollDisplayLeft();     
  delay(20);   }
  delay(1000); 
  //Faz o efeito de deslocamento para esquerda   
  for (i =0; i <20; i++){     
  lcd.scrollDisplayLeft();     
  delay(20);   }
  delay(3000); 

// RUÍDO DE INICIO
    tone(12,262,200); //DO
    delay(1000);
    tone(12,262,200); //DO
    delay(1000);
    tone(12,262,200); //DO
    delay(1000);
    tone(12,349,300); //FA
    delay(1000);
}

void loop() {

int valorInicio = digitalRead (botaoinicio);// le o valor de botao
int valorSW2 = digitalRead (chaveSW2); // le o valor de botao1
int valorSW3 = digitalRead (chaveSW3); // le o valor de botao2

if (valorInicio == HIGH) {// Testa o estado dos botoes

digitalWrite (rele00,LOW); // envia a saida para nivel baixo

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
  delay(1000);

}  if (valorInicio = !valorInicio);{
  digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
    lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  lcd.setCursor(6,2);
  lcd.print("PARADO");
  delay(1000);

}

if (valorSW2 == HIGH) {// Testa o estado dos botoes

digitalWrite (rele02,LOW); // envia a saida para nivel baixo

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");

}else{
  digitalWrite (rele02,HIGH); // envia a saida para nivel baixo

    lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("PARADO");
}

if (valorSW3 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
digitalWrite (rele02,LOW); // envia a saida para nivel baixo

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("MOTORES 3 E 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
}
else{
  digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
  digitalWrite (rele02,HIGH); // envia a saida para nivel baixo

   lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(6,0);
  lcd.print("MOTORES");
  lcd.setCursor(6,1);
  lcd.print("APAGADOS");
  delay(6000);
  lcd.clear();
}


}

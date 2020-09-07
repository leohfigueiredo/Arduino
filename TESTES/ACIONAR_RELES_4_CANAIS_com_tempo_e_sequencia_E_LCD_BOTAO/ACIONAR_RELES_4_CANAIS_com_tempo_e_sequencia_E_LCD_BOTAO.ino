#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

#define RELAY1  3                        

#define RELAY2  9                        

#define RELAY3  10                        

#define RELAY4  11

#define portabotao1 2

void setup()

{    
 lcd.begin (20,4);

//Porta ligada ao botao 1
int porta_botao1 = 2;
//Armazena o valor lido dos botoes
int leitura1 = 0;
//Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT);

//Define pinos para o rele como saida
  pinMode(RELAY1, OUTPUT);       

  pinMode(RELAY2, OUTPUT);

  pinMode(RELAY3, OUTPUT);

  pinMode(RELAY4, OUTPUT);

//Estado inicial dos reles - desligados
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO ");
  lcd.setCursor(0,1);
  lcd.print("INICIALIZADO");
  delay(8000);
  lcd.setBacklight(LOW);
  delay(2000);



}
 void loop()
{
  int leitura1 = 0;

  //Verifica o acionamento do botao 1
  leitura1 = digitalRead(portabotao1);
  if (leitura1 != 0)
  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 1");
  lcd.setCursor(0,1);
  lcd.print("INICIALIZADO");
  
  {while(digitalRead(portabotao1) != 0)
    {
     delay(1000);
     }
     
 
   digitalWrite(RELAY1,LOW);           // Relé 1 ligado (ON)
   delay(1800000);                                      // espera do processo
   digitalWrite(RELAY1,HIGH);          // Relé 1 desligado (OFF)
        
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 2");
  lcd.setCursor(0,1);
  lcd.print("INICIADO    "); 
  
   digitalWrite(RELAY2,LOW);           // Relé 2 ligado (ON)
   delay(1200000);                                      // espera do processo
   digitalWrite(RELAY2,HIGH);          // Relé 2 desligado (OFF)

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 3    ");
  lcd.setCursor(0,1);
  lcd.print("INICIADO"); 
  
   digitalWrite(RELAY3,LOW);           // Relé 3 ligado (ON)
   delay(1500000);                                      // espera do processo
   digitalWrite(RELAY3,HIGH);          // Relé 3 desligado (OFF)
 
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 4   ");
  lcd.setCursor(0,1);
  lcd.print("INICIADO     ");
  
   digitalWrite(RELAY4,LOW);          // Relé 4 ligado (ON)
   delay(1500000);                    // espera do processo
   digitalWrite(RELAY4,HIGH);         // Relé 4 desligado (OFF)  
        
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO   ");
  lcd.setCursor(0,1);
  lcd.print("FINALIZADO   "); 
  
while (1);
 }
}

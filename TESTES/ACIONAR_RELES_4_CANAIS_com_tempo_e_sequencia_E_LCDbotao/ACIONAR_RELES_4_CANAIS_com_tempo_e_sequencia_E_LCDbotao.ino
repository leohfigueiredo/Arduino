#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

#define RELAY1  3                        

#define RELAY2  9                        

#define RELAY3  10                        

#define RELAY4  11

void setup()

{    
 Serial.begin(9600);
 lcd.begin (20,4);


  pinMode(RELAY1, OUTPUT);       

  pinMode(RELAY2, OUTPUT);

  pinMode(RELAY3, OUTPUT);

  pinMode(RELAY4, OUTPUT);

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
  lcd.clear();
  delay(4000); 

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 1");
  lcd.setCursor(0,1);
  lcd.print("INICIADO");

}
 void loop()
{
  
   digitalWrite(RELAY1,LOW);           // Relé 1 ligado (ON)
   delay(3000);                                      // espera do processo
   digitalWrite(RELAY1,HIGH);          // Relé 1 desligado (OFF)
        
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 2");
  lcd.setCursor(0,1);
  lcd.print("INICIADO    ");
  
   digitalWrite(RELAY2,LOW);           // Relé 2 ligado (ON)
   delay(5000);                                      // espera do processo
   digitalWrite(RELAY2,HIGH);          // Relé 2 desligado (OFF)

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 3    ");
  lcd.setCursor(0,1);
  lcd.print("INICIADO");

  
   digitalWrite(RELAY3,LOW);           // Relé 3 ligado (ON)
   delay(4000);                                      // espera do processo
   digitalWrite(RELAY3,HIGH);          // Relé 3 desligado (OFF)
 
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 4   ");
  lcd.setCursor(0,1);
  lcd.print("INICIADO     ");

  
   digitalWrite(RELAY4,LOW);          // Relé 4 ligado (ON)
   delay(7000);                    // espera do processo
   digitalWrite(RELAY4,HIGH);         // Relé 4 desligado (OFF)  
        
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO   ");
  lcd.setCursor(0,1);
  lcd.print("FINALIZADO   ");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO   ");
  lcd.setCursor(0,1);
  lcd.print("FINALIZADO   ");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO   ");
  lcd.setCursor(0,1);
  lcd.print("FINALIZADO   ");
  lcd.clear(); 

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("FAVOR");
  lcd.setCursor(0,1);
  lcd.print("DESLIGAR!!!"); 
  
while (1);
 }

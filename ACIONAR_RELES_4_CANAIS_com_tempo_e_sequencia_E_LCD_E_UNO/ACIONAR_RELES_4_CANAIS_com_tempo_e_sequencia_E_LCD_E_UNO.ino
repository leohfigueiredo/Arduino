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

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("PROCESSO 1");
  lcd.setCursor(0,1);
  lcd.print("INICIALIZADO");
  lcd.setBacklight(LOW);

}
 void loop()
{
char leituraUNO;                        //define variável que lê estado do Arduino Uno

if (Serial.available()>0){              //verifica se existe informação do Arduino Uno
    leituraUNO=Serial.read();             //define a variável que lê e registra a informação

    if (leituraUNO=='L'){               //se a informação for ligado
    digitalWrite(RELAY1,LOW);           // Relé 1 ligado (ON)
    delay(5000);                                      // espera do processo
                        }
    else if (leituraUNO=='D'){            //se a informação for desligado
      digitalWrite(RELAY1,HIGH);          // Relé 1 desligado (OFF)
    }
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

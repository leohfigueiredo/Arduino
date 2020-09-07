#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

boolean start = true;
volatile boolean e_stop = false;
volatile boolean e_stop3 = false;

int botaoinicio = 3; // define pino 9 como entrada botao liga
int chaveSW2 = 4; // define botao 8 como botao desliga
int chaveSW3 = 5;
#define rele00 8 // rele motor 3
#define rele02 9 // rele motor 4
#define pin12 12
#define pin13 13

int estadorele00 = 1;
int estadorele02 = 1;
int estadorele08 = 1;
int i;


void setup() {
 Serial.begin(9600);
 delay(100);
 lcd.begin (20,4);

pinMode (pin12,OUTPUT); 
pinMode (pin13,OUTPUT); 
pinMode (botaoinicio, INPUT); // define como entrada
pinMode (chaveSW2, INPUT); // define como entrada
pinMode (chaveSW3, INPUT_PULLUP); // define como entrada
pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida

attachInterrupt(0,e_stop_ISR, RISING);

digitalWrite(rele00, estadorele00);
digitalWrite(rele02, estadorele02);

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

 if(start == true){


    if(e_stop == false){
Serial.println("tudo ok");
delay(300);
    }
    else{

Serial.println("EMERGENCIA!!!! RESETAR ARDUINO");
digitalWrite (rele02, HIGH); // envia saida para nivel alto
digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
delay (100);
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(3,0);
  lcd.print("EMERGENCIA!!!");
  delay(100);
  lcd.setCursor(3,1);
  lcd.print("RESETAR ARDUINO");
  lcd.setCursor(5,2);
  lcd.print("!!!!!!!!!!!!!!!");
  delay(100);
  
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
    tone(12,349,300); //FA RUÍDO ALARME
    delay(1000);
      
    }  
    }

int valorInicio = digitalRead (botaoinicio);// le o valor de botao
int valorSW2 = digitalRead (chaveSW2); // le o valor de botao1
int valorSW3 = digitalRead (chaveSW3); // le o valor de botao2


    
if (valorInicio == HIGH && valorSW2 == LOW) {// Testa o estado dos botoes
digitalWrite (rele02, HIGH); // envia saida para nivel alto
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
delay (1000);

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


  
int estadorele00 = 1;
int estadorele02 = 0;
  
}

if (valorInicio == LOW && valorSW2 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,HIGH); // envia a saida para nivel alto
digitalWrite (rele02,LOW); // envia a saida para nivel baixo
delay (1000);
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
 


int estadorele00 = 1;
int estadorele02 = 1;

}

digitalWrite(estadorele00,estadorele02);

if (valorSW3 == HIGH) { // Testa saida dos botoes
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
digitalWrite (rele02,LOW); // envia a saida para nivel baixo
delay (1000);

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

digitalWrite(!estadorele00,!estadorele02);
if (valorSW3 == HIGH) { // Testa saida dos botoes
delay (5000); 
digitalWrite (rele00,LOW); // envia a saida para nivel baixo
delay (5000);
digitalWrite (rele02,HIGH); // envia a saida para nivel alto

digitalWrite (rele00,HIGH); // envia a saida para nivel baixo
delay (100);

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(6,0);
  lcd.print("MOTORES");
  lcd.setCursor(6,1);
  lcd.print("APAGADOS");
  delay(6000);
  lcd.clear();

  lcd.setBacklight(HIGH);
  lcd.setCursor(2,0);
  lcd.print("SEGUIR ARDUINO");
  lcd.setCursor(5,1);
  lcd.print("PROCESOS");
  delay(6000);

    tone(12,349,300); //FA
    delay(500); 
    tone(12,349,300); //FA
    delay(500);      
    tone(12,349,300); //FA
    delay(500);
    tone(12,262,200); //DO
    delay(500);
    tone(12,262,200); //DO
    delay(500);
    tone(12,262,200); //DO
    delay(500);

        }
    

 
}
  void e_stop_ISR(void){
  detachInterrupt(0);
  e_stop = !e_stop;

}


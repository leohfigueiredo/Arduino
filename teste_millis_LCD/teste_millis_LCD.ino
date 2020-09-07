/********************************* Exemplo de multi tarefas genérico utilizando a função nativa do arduino -> millis() Código by João Vitor http://arduinolegal.blogspot.com *********************************/ 
#include <LiquidCrystal.h>

LiquidCrystal LCD(13, 12, 11, 10, 9, 8); //================================ //===== LEDS ===================== 
const byte LEDverde = 3; 
const byte LEDvermelho = 2; //================================ //===== Intervalos================ 
const unsigned long LEDverdeInterval = 250; 
const unsigned long LEDvermelhoInterval = 750; 
const unsigned long LCDInterval = 150; 
const unsigned long LCDrandomInterval = 1750; //================================ //===== Timers =================== 
unsigned long LEDverdeTimer; 
unsigned long LEDvermelhoTimer; 
unsigned long LCDTimer; 
unsigned long LCDrandomTimer; //================================ //===== Outras variáveis ========= 
int Rnd = 0; //================================ //===== Setup ==================== 

void setup() { 
  pinMode(LEDverde, OUTPUT); 
  pinMode(LEDvermelho, OUTPUT); 
  LEDverdeTimer = millis(); 
  LEDvermelhoTimer = millis(); 
  LCDTimer = millis(); 
  LCDrandomTimer = millis(); 
  LCD.begin(16, 2); 
  LCD.setCursor(0, 0); 
  LCD.print("#### TESTE ####"); } //================================ //===== Aleatório ================ 
  void Aleatorio() { 
    Rnd = random(0, 6); 
    LCD.setCursor(0, 0); 
    LCD.clear(); 
    char* palavras[] = { "Nova frase", "Coisa nova!", "Viva Alemanha", "Brasil perdeu...", "by Joao Vitor", "Lorem ipsum", }; 
    LCD.print(palavras[Rnd]); //tempo que foi chamado 
    LCDrandomTimer = millis(); } //================================ //===== LEDverdePisca ============ 
    void LEDverdePisca() { 
      
      if (digitalRead(LEDverde) == LOW) { 
        digitalWrite(LEDverde, HIGH); } 
        else { digitalWrite(LEDverde, LOW); } //tempo que foi chamado 
        LEDverdeTimer = millis(); }//LEDverdePisca //================================ //===== LEDvermelhoPisca ========= 
        void LEDvermelhoPisca() { 
          if (digitalRead(LEDvermelho) == LOW) {
digitalWrite(LEDvermelho, HIGH); } 
else { digitalWrite(LEDvermelho, LOW); } //tempo que foi chamado 
LEDvermelhoTimer = millis(); }//LEDvermelhoPisca //================================ //===== LCDControle ============== 
void LCDControle() { 
  LCD.setCursor(0, 1); 
  LCD.print("Tempo exec.: "); 
  LCD.print( millis() / 1000 ); //tempo que foi chamado 
  LCDTimer = millis(); }//LCDControle //================================ //===== Loop ===================== 
  void loop() { // LEDverdePisca 
    if ((millis() - LEDverdeTimer) >= LEDverdeInterval) { LEDverdePisca(); }//fim LEDverdePisca // LEDvermelhoPisca
    if ((millis() - LEDvermelhoTimer) >= LEDvermelhoInterval) { LEDvermelhoPisca(); }//fim LEDvermelhoPisca // LCDControle 
    if ((millis() - LCDTimer) >= LCDInterval) { LCDControle(); } //fim LCDControle // Aleatorio 
    if ((millis() - LCDrandomTimer) >= LCDrandomInterval) { Aleatorio(); } //fim Aleatorio 
    
  
  }


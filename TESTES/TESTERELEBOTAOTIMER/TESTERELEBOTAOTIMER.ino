//Programa : Teste Módulo Rele Arduino - Botoes
#include "TimerOne.h"
int time; 
int secs    = 0;
int minutes = 0;
int hours   = 0;
long interval = 10000; //ms
long previous = 0;
unsigned long current = millis();

//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 7;
//Porta ligada ao pino IN2 do modulo

int porta_botao1 = 2;

 
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;


//Armazena o valor lido dos botoes
 int leitura1 = 0;
void myClock(){
  secs +=1;
  if (secs > 59){
    minutes +=1;
    secs = 0;
  }
  if (minutes > 59){
    hours += 1;
    minutes = 0;
  }
}
void setup()
{
  //Define pinos para o rele como saida
  pinMode(7, OUTPUT);
  Timer1.initialize(5000000); // Inicializa o Timer1 e configura para um período de 0,5 segundos
  Timer1.pwm(7,0);
  Timer1.attachInterrupt(callback); // Configura a função callback() como a função para ser chamada a cada interrupção do Timer1
  Timer1;

   //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT); 
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);

}
void callback()
{
digitalWrite(7, digitalRead(7) ^ 1);
} 
  
 void loop()
{

   
  leitura1 = digitalRead(porta_botao1);
  if (leitura1 != 0)
  {
    while(digitalRead(porta_botao1) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(porta_rele1, estadorele1);
     
  }   
  

  }

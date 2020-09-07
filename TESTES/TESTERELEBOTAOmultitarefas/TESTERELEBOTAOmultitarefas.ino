//Programa : Teste Módulo Rele Arduino - Botoes

 
//Porta ligada ao pino IN1 do modulo
#define porta_rele1 7
//Porta ligada ao pino IN2 do modulo
#define porta_rele2 8
//Porta ligada ao pino IN3 do modulo
#define porta_rele3 9
//Porta ligada ao pino IN4 do modulo
#define porta_rele4 10
//Porta ligada ao botao 1
#define porta_botao1 2
//Porta ligada ao botao 2
#define porta_botao2 3
//Porta ligada ao botao 3
#define porta_botao3 4
//Porta ligada ao botao 4
#define porta_botao4 5
 
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;
int estadorele2 = 1;
int estadorele3 = 1;
int estadorele4 = 1;

//Armazena o valor lido dos botoes
int leitura1 = 0;
int leitura2 = 0;
int leitura3 = 0;
int leitura4 = 0;

void controlaLed1();

void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  pinMode(porta_rele3, OUTPUT); 
  pinMode(porta_rele4, OUTPUT); 
  
  //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT); 
  pinMode(porta_botao2, INPUT);
  pinMode(porta_botao3, INPUT); 
  pinMode(porta_botao4, INPUT);
  
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
  digitalWrite(porta_rele3, HIGH);
  digitalWrite(porta_rele4, HIGH);
}
 
void loop()
{
  controlaLed1();
} 

   //Verifica o acionamento do botao 1

  leitura1 = digitalRead(porta_botao1);
  if (leitura1 != 0)

void controlaLed1() {
static unsigned long delayPisca;  

   if ( (millis() - delayPisca) < 500 ) {
      digitalWrite(porta_rele1, HIGH);
  } else {
      digitalWrite(porta_rele1, LOW);
  }

  if ( (millis() - delayPisca) >= 1000 ) {
    delayPisca = millis(); 
  }
}
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(porta_rele1, estadorele1);  
  }   
  
}
 
   
  //Verifica o acionamento do botao 2
  leitura2 = digitalRead(porta_botao2);
  if (leitura2 != 0)
  {
    while(digitalRead(porta_botao2) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele2 = !estadorele2;
    //Comandos para o rele 2
    digitalWrite(porta_rele2, estadorele2); 
    
  }

     //Verifica o acionamento do botao 3
  leitura3 = digitalRead(porta_botao3);
  if (leitura3 != 0)
  {
    while(digitalRead(porta_botao3) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele3 = !estadorele3;
    //Comandos para o rele 3
    digitalWrite(porta_rele3, estadorele3);
  }
   //Verifica o acionamento do botao 4
  leitura4 = digitalRead(porta_botao4);
  if (leitura4 != 0)
  {
    while(digitalRead(porta_botao4) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele4 = !estadorele4;
    //Comandos para o rele 4
    digitalWrite(porta_rele4, estadorele4);    
}
}



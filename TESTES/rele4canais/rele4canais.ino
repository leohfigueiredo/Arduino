//Programa : Teste Modulo Rele Arduino 2 canais - Lampadas
//Autor : FILIPEFLOP
 
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 7;
//Porta ligada ao pino IN2 do modulo
int porta_rele2 = 8;
//Porta ligada ao pino IN2 do modulo
int porta_rele3 = 9;
//Porta ligada ao pino IN2 do modulo
int porta_rele4 = 10;

int i = 0;


void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  pinMode(porta_rele3, OUTPUT);
  pinMode(porta_rele4, OUTPUT);

  digitalWrite(porta_rele1, LOW);
  digitalWrite(porta_rele2, LOW);
  digitalWrite(porta_rele3, LOW);
  digitalWrite(porta_rele4, LOW);
}
   
void loop()
{

  for(int i=0; i < 4; i++);
{ 
  digitalWrite(porta_rele1, HIGH);  //Liga rele 1
  digitalWrite(porta_rele1, LOW); //Desliga rele 2
  delay(2000);
  
  digitalWrite(porta_rele2, LOW);  //Liga rele 2
  digitalWrite(porta_rele2, HIGH);  //Liga rele 2

 
  delay(4000);
 
  digitalWrite(porta_rele3, HIGH);  //Liga rele 2
  digitalWrite(porta_rele3, LOW); //Desliga rele 1
  
  delay(6000);
  
  digitalWrite(porta_rele4, LOW); //Desliga rele 1
  digitalWrite(porta_rele4, HIGH);  //Liga rele 2
  delay(7000);

} 

}

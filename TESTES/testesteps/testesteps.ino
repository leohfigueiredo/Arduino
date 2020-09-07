int rele1 = 7; // velocidade baixa a direita
int rele2 = 8; // velocidade baixa a esquerda
int rele3 = 9; // bomba dagua
int rele4 = 10; // velocidade alta para centrifugação a direita
int led1 = 3; // avisa processo finalizado
int botao = 2; // botão inicio
int var = 0; // variavel
int estado = 0;


int estadorele1 = 1;
int estadorele2 = 1;
int estadorele3 = 1;
int estadorele4 = 1;

void setup()
{
pinMode(rele1,OUTPUT); // pino do rele1 do tipo saida de sinal
pinMode(rele2,OUTPUT); // pino do rele2 do tipo saida de sinal
pinMode(rele3,OUTPUT); // pino da bomba1 do tipo saida de sinal
pinMode(rele4,OUTPUT); // pino do rele3 do tipo saida de sinal
pinMode(led1,OUTPUT); // pino do led1 do tipo saida de sinal
pinMode(botao,INPUT); // pino do botao1 do tipo de entrada de sinal


digitalWrite(rele1, HIGH);
digitalWrite(rele2, HIGH);
digitalWrite(rele3, HIGH);
digitalWrite(rele4, HIGH);

var=digitalRead(botao); //ler o valor enviado pelo botão: "HIGH" ou "LOW"

if (var == LOW) {
estado = 1 - estado;
delay(20); // de-bouncing
}

if (estado == 1) {

digitalWrite(rele1,HIGH); //liga rele1
delay(1000); // rele1 aciona por 25 segundos
digitalWrite(rele1,LOW); // desliga rele1
delay(100); // espera no sistema
digitalWrite(rele2,HIGH); // liga rele2
delay(3500); // rele2 aciona por 25 segundos
digitalWrite(rele2,LOW); // desliga rele2
delay(100); // espera do sistema
digitalWrite(rele1,LOW); // desliga rele1
delay(3500); // espera no sistema
digitalWrite(rele3,HIGH); // liga bomba
delay(4500); // permanece por 3 minutos e
digitalWrite(rele3,LOW); // desliga bomba
delay(100); // espera do sistema
digitalWrite(rele2,HIGH); // liga rele2
delay(3500); // rele2 aciona por 25 segundos
digitalWrite(rele2,LOW); // desliga rele2
delay(100); // espera do sistema
digitalWrite(rele4,HIGH); // liga rele4 centrifugacao
delay(5000); // aciona motor para centrifugacao por 20 segundos e bomba
digitalWrite(rele4,LOW); // desliga rele4 centrifugacao
delay(100); // tempo de desligado 10 segundos


delay(150); // apos 15 segundos para parada do motor

digitalWrite(led1,HIGH); // liga led pronto
delay(100); // espera no sistema

digitalWrite(led1,LOW);

}
}
void loop(){


}

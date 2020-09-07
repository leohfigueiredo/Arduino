// Projeto 4 - Semáforo interativo
int porta_rele1 = 7; // estabelece o semáforo para carros
int porta_rele2 = 8;
int porta_rele3 = 9;
int porta_rele4 = 10; // estabelece o semáforo para pedestres
int porta_botao1 = 2; // pino do botão
int porta_botao4 = 5;

unsigned long changeTime; // tempo desde que o botão foi pressionado


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

void setup() {
 pinMode(porta_rele1, OUTPUT);
 pinMode(porta_rele2, OUTPUT);
 pinMode(porta_rele3, OUTPUT);
 pinMode(porta_rele4, OUTPUT);
 pinMode(porta_botao1, INPUT); // botão no pino 2
 pinMode(porta_botao4, INPUT);

  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
  digitalWrite(porta_rele3, HIGH);
  digitalWrite(porta_rele4, HIGH);

  //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT); 
  
  pinMode(porta_botao4, INPUT);
}
void loop() {

 changeLights();
 int state = digitalRead(porta_botao1);
 /* verifica se o botão foi pressionado e se transcorreram 5 segundos desde a última vez que 
 isso ocorreu */
 if (state == HIGH && (millis() - changeTime) > 1000) {

// Chama a função para alterar as luzes
 
 }
}
void changeLights() {
 digitalWrite(porta_rele1, HIGH);
 digitalWrite(porta_rele2, LOW); 
 digitalWrite(porta_rele3, LOW);
 digitalWrite(porta_rele4, LOW);
 
 delay(3000); // espera 20 segundos

 digitalWrite(porta_rele1, LOW);
 digitalWrite(porta_rele2, HIGH); 
 digitalWrite(porta_rele3, LOW);
 digitalWrite(porta_rele4, LOW);
 delay(3000); // espera 20 segundos

 digitalWrite(porta_rele1, LOW);
 digitalWrite(porta_rele2, LOW); 
 digitalWrite(porta_rele3, HIGH);
 digitalWrite(porta_rele4, LOW);
 delay(3000); // espera 20 segundos

 digitalWrite(porta_rele1, LOW);
 digitalWrite(porta_rele2, LOW); 
 digitalWrite(porta_rele3, LOW);
 digitalWrite(porta_rele4, HIGH);
 delay(3000); // espera 20 segundos

 changeTime = millis();
 // depois retorna para o loop principal do programa
}



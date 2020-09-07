// Inclusão Servo library
#include <Servo.h>. 
// Define os pinos Trig e Echo do sensor ultra-sônico
const int trigPin = 10;
const int echoPin = 11;
// Variáveis para a duração e distância
long duration;
int distance;
Servo myServo; // Cria um servo object para controlar o servo motor
void setup() {
  pinMode(trigPin, OUTPUT); // Define o trigPin como uma saída
  pinMode(echoPin, INPUT); // Define o echoPin como uma entrada
  Serial.begin(9600);
  myServo.attach(12); // Define em qual pino o servo motor está ligado
}
void loop() {
  // roda o servo motor de 15 a 165 graus
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Chama uma função para calcular a distância medida pelo sensor ultra-sônico para cada grau
  
  Serial.print(i); // Envia o grau atual para a Porta Serial
  Serial.print(","); // Envia o caractere de adição ao lado do valor anterior necessário mais tarde no IDE de processamento para indexação
  Serial.print(distance); // Envia o valor da distância para a Porta Serial
  Serial.print("."); //Envia o caractere de adição ao lado do valor anterior necessário mais tarde no IDE de processamento para indexação
  }
  //Repete as linhas anteriores de 165 para 15 graus
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
// Função para calcular a distância medida pelo sensor ultra-sônico
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Define o trigPin no estado HIGH durante 10 micro segundos
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Lê o echoPin, retorna o tempo de viagem da onda sonora em microssegundos
  distance= duration*0.034/2; // d = ( V * t ) /2 - Onde:    d = Distância entre o sensor e o obstáculo (é o que queremos descobrir).
                              // V = Velocidade do som no ar (340 m/s).
                              //t = Tempo necessário para o sinal ir do sensor até o obstáculo e voltar (é o que o nosso módulo sensor ultrassom mede).

  return distance;
}

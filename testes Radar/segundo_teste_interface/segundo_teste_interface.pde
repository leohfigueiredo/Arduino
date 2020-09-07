// Programa : Informacoes na tela com o processing
// Autor : Arduino e Cia

// Carrega as bibliotecas Serial e Arduino
import processing.serial.*;
import cc.arduino.*;
 
Arduino arduino;

// Definicao das variaveis
int ledPin = 3;
int pinobotao = 7;
int valor = 0;
int x = 0;
int y = 290;
int contador = 0;
 
void setup()
{
 // Abre uma janela no tamanho 500x300
 size(500,300);
 // Habilita o anti-aliasing
 smooth();
 // Define fundo na cor preta
 background(0);
 println(Arduino.list());
 
 // Comunicacao com Arduino
 arduino = new Arduino(this, Arduino.list()[0], 57600);
 // Define o pino do led como saida
 arduino.pinMode(ledPin, Arduino.OUTPUT);
 // Define o pino do botao como entrada
 arduino.pinMode(pinobotao, Arduino.INPUT);
 
 ellipseMode(RADIUS);

 //Carrega a fonte de texto a ser utilizada
 textFont(createFont("Arial Bold",18));
 textAlign(CENTER);
 
 // Cor da linha = branco
 fill(255);
 // Desenha o retangulo no centro da janela
 rect(110,125,275,31);
 
 // Inicio do cabecalho
 // Desenha o retangulo azul
 fill(90,109,238);   // Cor preenchimento
 rect(0,0,width,40);
 // Define o tamanho da fonte
 textSize(31);
 // Define a cor e imprime o texto
 fill(255);  // Cor branca
 text("Arduino e Cia", width/2,30);
 // Final do cabecalho
   
 // Texto Estado Botao
 textSize(25);
 text("Estado botão", 220,90);
 
 // Texto Inicial contador
 fill(0);
 text("Contador : " + contador, width/2, height/2);
}
 
void draw()
{
  valor = arduino.digitalRead(pinobotao);
  stroke(255);
  fill(0);  
  // Atualiza o circulo referente ao Estado Botao
  ellipse(340, 80, 15,15);
  
  // Apaga o led
  arduino.digitalWrite(ledPin, Arduino.LOW);
  
  // Verifica se o botao foi pressionado
  if (valor !=0)
  {
    // Incrementa o contador
    contador = contador+1;
    // Atualiza as informacoes do contador na tela
    fill(255);
    rect(111,126,273,28);
    fill(0);
    text("Contador : " + contador, width/2, height/2);
    // Acende o led
    arduino.digitalWrite(ledPin, Arduino.HIGH);
    // Ajusta o valor de Y para desenho do grafico
    y = 200;
    // Define a cor da linha como vermelho
    stroke(255,7,7);
    // Desenha uma linha vermelha no grafico
    line( x, 290, x, y);
    // Desenha o botao Estado Botao em vermelho
    fill(255,7,7);
    ellipse(340, 80, 14, 14);    
  }
  
  // Atualiza o grafico 
  stroke(0);
  line(x+1,291, x+1, 199);
  stroke(33,223,109);
  line(x,290, x, 245);
   
  // Atualiza o valor de X para desenhar a
  // proxima linha do grafico
  x = x +1;
  // Se o valor de X for igual ao tamanho da tela (500),
  // reinicia a contagem 
  if (x == width)
  {
    x = 0;
    stroke(0);
    line(x,291, x, 199);
  }

  // Aguarda 10 milisegundos e reinicia o processo
  delay(10);
}
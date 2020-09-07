import processing.serial.*;

Serial myPort;
String myText="";

int contador = 0;
int x = 0;
int y = 290;

void setup(){
size(500, 300);
 // Habilita o anti-aliasing
 smooth();
 // Define fundo na cor preta
 background(0);
myPort = new Serial(this, "COM6", 9600);
myPort.bufferUntil('\n');

ellipseMode(RADIUS);
textFont(createFont("Arial Bold",18));


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
 text("BUTTON STATUS", width/2,30);
 // Final do cabecalho
 
  // Texto Inicial contador
 fill(0);
 text("Contador : " + contador, width/2, height/2);


}

void serialEvent (Serial myPort){
myText = myPort.readStringUntil('\n');
}

void draw(){
  stroke(255);
  fill(0);  

text(myText, 120, 120);

myText="";
if(mousePressed && (mouseButton == LEFT)){
myPort.write('1');
}
if (mousePressed && (mouseButton == RIGHT)){
myPort.write('0');
}
}
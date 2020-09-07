int botao = 3; // define pino 9 como entrada botao liga
int botao1 = 4; // define botao 8 como botao desliga
int botao2 = 5;
int saida = 8; // define pino 8 como saida
int saida2 = 9;


void setup() {

pinMode (botao, INPUT); // define como entrada
pinMode (botao1, INPUT); // define como entrada
pinMode (botao2, INPUT); // define como entrada
pinMode (saida, OUTPUT); // define como saida
pinMode (saida2, OUTPUT); // define como saida
}

void loop() {


int valor = digitalRead (botao);// le o valor de botao
int valor2 = digitalRead (botao1); // le o valor de botao1
int valor3 = digitalRead (botao2); // le o valor de botao2

if (valor == HIGH && valor2 == LOW) {// Testa o estado dos botoes
digitalWrite (saida2, HIGH); // envia saida para nivel alto
digitalWrite (saida,LOW); // envia a saida para nivel baixo
delay (1000);
}

if (valor == LOW && valor2 == HIGH) { // Testa saida dos botoes
digitalWrite (saida,HIGH); // envia a saida para nivel baixo
digitalWrite (saida2,LOW); // envia a saida para nivel baixo
delay (1000);

}
if (valor3 == HIGH) { // Testa saida dos botoes
digitalWrite (saida,HIGH); // envia a saida para nivel baixo
digitalWrite (saida2,HIGH); // envia a saida para nivel baixo
delay (1000);
}
}

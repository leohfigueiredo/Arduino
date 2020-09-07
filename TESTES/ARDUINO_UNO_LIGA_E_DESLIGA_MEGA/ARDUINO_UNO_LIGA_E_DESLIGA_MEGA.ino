int botao = 12;     //define pin onde botão está ligado
int estadoBotao;    //define variável que irá ler se o botão está ligado ou desligado



void setup() {
  pinMode(botao, INPUT); //define botão como sinal de entrada
  Serial.begin(9600);


  estadoBotao=digitalRead(botao); //informa se o botão está ligado ou desligado

    if (estadoBotao == HIGH){       //verifica se o botao está ligado ou desligado
      Serial.write('L');          //se estiver ligado, envia o caracter L - ligado     
    }
    else{
      Serial.write('D');          //se estiver desligado, envia o caracter D - Desligado
    }
}


void loop() {

  
}

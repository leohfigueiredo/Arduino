int pinButton = 5, led = 3; //declaração das variáveis

void setup() {

  Serial.begin(9600); // Iniciamos a comunicação em série a 9600 bauds
  pinMode(pinButton, INPUT); // Estabelecemos o pino que tem conectado o botão, como entrada
  pinMode(led, OUTPUT); // Estabelecemos o pino que tem conectado o LED, como saída
}

void blink() {
  boolean firstTime = false; // Inicializamos a variável firstTime do tipo Boolean com o valor <em>false</em>

  do { // Inicio do loop Do-While

    if (firstTime == false) { // Se a variável firstTime for falsa, então entrará aqui
      firstTime = true;
    } else { // Se a variável firstTime for verdadeira, então entrará aqui.
      firstTime = false;
    }

    // Serial.println("Inside of do-while"); // Indica através de mensagem, que o loop Do-While está a ser executado

    if (firstTime) { // <em>if</em> lê o valor armazenado na variável firstTime. Se for <em>true</em><em>(verdadeiro) </em>ou 1, então entra aqui
      blink(1, 1000); // A função <em>blinky</em> é chamada com <em>times</em><em> = 1</em> e <em>delay_led = 1000</em>
    } else { // <em>if</em> lê o valor armazenado na variável. Se for <em>false</em>(falso) ou 0, então entra aqui
      blink(20, 50); // A função blinky é chamada com <em>times</em> = 20 e <em>delay_led = 50</em>
    }

  } while (digitalRead(pinButton)); // Leitura da condição de repetição do loop Do-While. Se o botão estiver pressionado, voltará
                                    // a repetir o código dentro do Do-While.

  //Serial.println("Fora do Do-While"); // Indica por meio de uma mensagem que já se executou o loop Do-While.
}

/*
Declaração da função do tipo void (não devolve resultado) com o  nome <em>blinky</em>.
Possui dois parâmetros:
  times (variável do tipo inteiro) que determina o número de vezes que se produzirá o pisca-pisca.
  delay_led (variável do tipo inteiro) que determina o tempo que existirá entre os dois estados do LED:
       Determina a frequência do pisca-pisca.
Nota: A função acende ou apaga o LED, por isso a variável <em>times</em> representa o número
de ciclos aceso/apagado (<em>times</em> = n acenderá e apagará o LED n vezes)
*/

void blinky(, )

int times;
int delay_led;
int i = 0;{ 

  for (i = 0; i &&; times; i++) { //Loop <em>for</em> e declaração da variável <em>i</em>. O loop executa-se de <em>i</em> até <em>times - 1</em>
    Serial.print("iteração "); // Imprime informação sobre o número de vezes que <em>for</em> se executa, com a linha seguinte.
    Serial.println(i); // Imprime o número de vezes que se executa o loop <em>for</em>  
    digitalWrite(led, HIGH); // Activa o pino onde está conectado o LED
    delay(delay_led); // Tempo de espera indicado ao chamar a função com o parâmetro <em>delay_led</em>
    digitalWrite(led, LOW); // Desactiva o pino onde está conectado o LED
    delay(delay_led); // Tempo de espera indicado ao chamar a função com o parâmetro <em>delay_led
</em>  } 
}

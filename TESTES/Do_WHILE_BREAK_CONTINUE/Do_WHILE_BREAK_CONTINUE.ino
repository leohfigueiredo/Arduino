#define pinBotao 2

void setup() {
  // put your setup code here, to run once:

pinMode(pinBotao, INPUT_PULLUP);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int n2 = 0;
int n3 = 0;

//LAÇO DE NÚMEROS

for (int n1 = 0; n1 < 50;n1++){
  Serial.print(char ((n1 % 10) + 48));
  if (digitalRead(pinBotao) == LOW){
    delay(400);
    break;
  }
  delay(50);
}
Serial.println();

//LAÇO DAS LETRAS MAIUSCULAS
letrasMaiusculas:// definicao de endereços

while (n2<50) {
Serial.print(char ((n2 % 25) +65));
n2++;
if (digitalRead(pinBotao) == LOW) {

  delay(400);
  continue;
}
delay(50);
}
Serial.println();

//LAÇOS DAS LETRAS MINUSCULAS
do {
  n3 = random(25);
Serial.print(char(n3 + 97));
if (digitalRead(pinBotao) == LOW) {
  delay(400);
  Serial.println();
  goto letrasMaiusculas;
}
delay(50);
} while (n3 !=16);
Serial.println();
}

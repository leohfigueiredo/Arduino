int led=8;      // led no pino 8
int botao=2;  // botão no pino 2
int var=0;       // valor instantaneo enviado pelo botão
int var2=0;     // valor guardado
int estado=0;  // guarda o valor 0 ou 1 (HIGH ou LOW)

int estadorele00 = 0;
void setup()
{
      Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(botao,INPUT);

  digitalWrite(led, estadorele00);
}
void loop()
{
  var=digitalRead(botao); // ler o valor enviado pelo botão: "HIGH" ou "LOW"
  if ((var == HIGH) && (var2 == LOW)) {
    estado = 1 - estado;
    delay(20); // de-bouncing
  }
  var2=var;
  if (estado == 1) {
    digitalWrite(led, HIGH);
        Serial.print('H');// liga o led
  } else {
    digitalWrite(led, LOW);
        Serial.print('L');// desliga o led
  }
}

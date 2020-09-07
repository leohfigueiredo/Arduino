int ledPin =  7;       // pino onde esta ligado o LED
int ledState = HIGH;     // ledState usado para amazena o estado atual do led aceso o apagado
long intervalo = 200000;  // intervalo de um segundo
  
void setup() 
{
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);      
}

void loop()
{
   long previousMillis = millis();
   int cnt=0;
   
    if (ledState == LOW)     // se o led estava apagado
        ledState = HIGH;    //
    else                   // se o led estava aceso
        ledState = LOW;   //

    digitalWrite(ledPin, ledState);
       
    // Mantem o led aceso ou apagado por um segundo
  while(millis() - previousMillis < intervalo) 
  {
       // pode-se fazer muita coisa dentro deste laço enquanto aguarda o final do tempo para mudar o estad do led
       // ler um sensor ou algo parecido, por exemplo
       if (cnt % 100 == 0)
       {
       Serial.print("Lendo sensor"); 
       Serial.print(" \n ");
       }
       cnt++;
  }

}

#include <SoftwareSerial.h>
 
//RX pino 2, TX pino 3
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true
 
void setup()
{
  Serial1.begin(9600);
  // Configure na linha abaixo a velocidade inicial do
  // modulo ESP8266
  esp8266.begin(115200);
  sendData("AT+RSTrn", 20000, DEBUG);
  delay(10000);
  Serial1.println("Versao de firmware");
  delay(10000);
  sendData("AT+GMRrn", 20000, DEBUG); // rst
  // Configure na linha abaixo a velocidade desejada para a
  // comunicacao do modulo ESP8266 (9600, 19200, 38400, etc)
  sendData("AT+CIOBAUD=115200rn", 20000, DEBUG);
  Serial1.println("** Final **");
}
 
void loop() {}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
